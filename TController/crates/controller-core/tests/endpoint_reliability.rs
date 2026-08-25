//! Python `tests/test_endpoint_reliability.py` 的移植 — 行为对齐契约。

use controller_core::processing::divergence::js_divergence;
use controller_core::processing::endpoint::{Confidence, EndpointDetector, Method, PotentialState};
use controller_core::processing::tracker::{SpectralFeatureTracker, TrackerState};

fn ones4() -> Vec<f64> {
    vec![1.0; 4]
}

fn gauss(x: f64, center: f64, sigma: f64) -> f64 {
    (-((x - center).powi(2)) / (2.0 * sigma * sigma)).exp()
}

fn baseline_frames(tracker: &mut SpectralFeatureTracker) {
    for i in 1..9 {
        tracker.update(i as f64 * 0.05, &ones4());
    }
}

fn tracker_for_events(supersede_ratio: f64) -> SpectralFeatureTracker {
    SpectralFeatureTracker::with_params(
        0.20,  // alpha
        0.1,   // js_enter
        0.03,  // js_exit
        0.001, // baseline_enter
        4,     // baseline_frames
        0.4,   // baseline_max_volume
        3,     // confirm_frames
        0.05,  // min_event_volume
        1e-8,  // epsilon_volume
        8,     // lookback_frames
        supersede_ratio,
        1e-14,
        true, // use_jsd
    )
}

/// 驱动一次"升起并恢复"的激变；返回新的体积与诊断。
fn feed_excursion(
    tracker: &mut SpectralFeatureTracker,
    mut volume: f64,
    amplitude: f64,
    recovery: usize,
) -> (f64, controller_core::processing::tracker::Diagnostics) {
    let mut diagnostic = Default::default();
    for _ in 0..3 {
        volume += 0.05;
        diagnostic = tracker.update(volume, &[amplitude, 1.0, 1.0, 1.0]);
    }
    for _ in 0..recovery {
        volume += 0.05;
        diagnostic = tracker.update(volume, &ones4());
    }
    (volume, diagnostic)
}

#[test]
fn js_is_symmetric_bounded_and_gain_invariant() {
    let p = [1.0, 2.0, 4.0, 8.0];
    let q = [2.0, 3.0, 5.0, 7.0];
    let pq = js_divergence(&p, &q);
    approx::assert_relative_eq!(pq, js_divergence(&q, &p));
    assert!((0.0..=std::f64::consts::LN_2).contains(&pq));
    // Python np.isclose 默认 rtol=1e-5；放大 17 倍引入 ~1e-9 相对舍入差
    approx::assert_relative_eq!(
        pq,
        js_divergence(&[17.0, 34.0, 68.0, 136.0], &[34.0, 51.0, 85.0, 119.0]),
        max_relative = 1e-6
    );
}

#[test]
fn tracker_handles_invalid_and_repeated_volume_without_infinity() {
    let mut tracker = SpectralFeatureTracker::new();
    let first = tracker.update(0.1, &ones4());
    let repeated = tracker.update(0.1, &[2.0, 1.0, 1.0, 1.0]);
    let invalid = tracker.update(0.1, &[1.0, f64::NAN, 1.0, 1.0]);
    assert!(first.valid_frame);
    assert!(!repeated.volume_sync_valid);
    assert_eq!(repeated.repeated_volume_count, 1);
    assert!(repeated.js_local.is_finite());
    assert!(repeated.js_speed.is_finite());
    assert!(!invalid.valid_frame);
    assert_eq!(invalid.data_quality, "spectrum_nonfinite");
}

#[test]
fn cross_curvature_is_causal() {
    let prefix = [
        vec![1.0, 1.0, 2.0, 1.0, 1.0],
        vec![1.0, 2.0, 2.0, 1.0, 1.0],
        vec![1.0, 3.0, 2.0, 1.0, 1.0],
    ];
    let future = [vec![1.0, 4.0, 1.0, 2.0, 1.0], vec![2.0, 1.0, 1.0, 4.0, 1.0]];
    let mut left = SpectralFeatureTracker::with_params(
        0.20, 0.05, 0.008, 3e-7, 3, 0.2, 4, 0.08, 1e-8, 8, 1.5, 1e-14, true,
    );
    let mut right = SpectralFeatureTracker::with_params(
        0.20, 0.05, 0.008, 3e-7, 3, 0.2, 4, 0.08, 1e-8, 8, 1.5, 1e-14, true,
    );
    let left_values: Vec<_> = prefix
        .iter()
        .enumerate()
        .map(|(i, frame)| left.update((i + 1) as f64 * 0.05, frame))
        .collect();
    let all = [prefix.as_slice(), future.as_slice()].concat();
    let right_values: Vec<_> = all
        .iter()
        .enumerate()
        .map(|(i, frame)| right.update((i + 1) as f64 * 0.05, frame))
        .collect();
    for (before, after) in left_values.iter().zip(right_values.iter()) {
        approx::assert_relative_eq!(before.cross_curvature, after.cross_curvature);
        approx::assert_relative_eq!(before.js_local, after.js_local);
        assert_eq!(before.state, after.state);
    }
}

#[test]
fn peak_requires_recovery_before_confirmation() {
    let mut tracker = SpectralFeatureTracker::with_params(
        0.20, 0.2, 0.03, 0.001, 4, 0.4, 3, 0.05, 1e-8, 8, 1.5, 1e-14, true,
    );
    baseline_frames(&mut tracker);
    for volume in [0.45, 0.50, 0.55] {
        let diagnostic = tracker.update(volume, &[100.0, 1.0, 1.0, 1.0]);
        assert_eq!(diagnostic.state, TrackerState::InChange);
    }
    let diagnostic = tracker.update(0.60, &ones4());
    assert_eq!(diagnostic.state, TrackerState::InChange);
    let mut diagnostic = diagnostic;
    let mut v = 0.65;
    while v < 2.05 {
        diagnostic = tracker.update(v, &ones4());
        v += 0.05;
    }
    assert_eq!(diagnostic.state, TrackerState::EndConfirmed);
    assert!(diagnostic.candidate_volume.unwrap().is_finite());
}

#[test]
fn detector_keeps_legacy_feed_and_result_keys() {
    let mut detector = EndpointDetector::new(0.0061);
    for index in 1..240 {
        let volume = index as f64 * 0.01;
        let voltage = 1.0 - 0.8 * gauss(volume, 1.0, 0.035);
        detector.feed_potential(volume, volume / 0.0061, voltage);
        detector.feed_spectrum(volume, &[1.0, 2.0, 3.0, 4.0]);
    }
    let result = detector.detect().expect("endpoint expected");
    assert_eq!(detector.potential_state(), PotentialState::EndConfirmed);
    assert!(matches!(
        result.method,
        Method::Consensus | Method::PotentialOnly
    ));
    assert!(matches!(
        result.confidence,
        Confidence::High | Confidence::Medium
    ));
    assert!(result.potential.is_some());
    assert!(
        (result.volume - 1.0).abs() < 0.3,
        "volume={} ",
        result.volume
    );
}

#[test]
fn detector_reset_retains_spectrum_configuration() {
    let mut detector = EndpointDetector::with_options(
        0.0061,
        true,
        true,
        true,
        Some(&[400.0, 500.0, 600.0, 700.0]),
    );
    detector.feed_spectrum(0.1, &ones4());
    detector.reset();
    let diagnostics = detector.diagnostics();
    assert_eq!(diagnostics.spectral_features.sample_count, 0);
    detector.feed_spectrum(0.1, &ones4());
    assert!(detector
        .diagnostics()
        .spectral_features
        .cross_curvature
        .is_finite());
}

/// 生产路径复现：多帧光谱共享同一泵体积。速度滤波必须*保持*电平而不是
/// 喂零——喂零会把活跃激变拖到退出阈值以下，伪造一次恢复。
#[test]
fn repeated_volume_holds_speed_instead_of_injecting_zero() {
    let mut tracker = SpectralFeatureTracker::with_params(
        0.20, 0.05, 0.008, 3e-7, 3, 0.2, 4, 0.08, 1e-8, 8, 1.5, 1e-14, true,
    );
    for index in 1..4 {
        tracker.update(index as f64 * 0.05, &ones4());
    }
    let advancing = tracker.update(0.25, &[4.0, 1.0, 1.0, 1.0]);
    assert!(advancing.js_speed_smooth > 0.0);
    let mut repeated = advancing.clone();
    for _ in 0..5 {
        repeated = tracker.update(0.25, &[4.0, 1.0, 1.0, 1.0]);
        assert!(!repeated.volume_sync_valid);
        approx::assert_relative_eq!(repeated.js_speed_smooth, advancing.js_speed_smooth);
        approx::assert_relative_eq!(repeated.cross_curvature, advancing.cross_curvature);
    }
    assert_eq!(repeated.repeated_volume_count, 5);
    // 之后的前进帧恢复正常归一化（锚定最后同步帧）。
    let resumed = tracker.update(0.30, &[4.0, 1.0, 1.0, 1.0]);
    assert!(resumed.volume_sync_valid);
}

/// Paper/ExpData B 组回归：一次性闩锁选择了瞬态。
#[test]
fn stronger_late_excursion_supersedes_an_early_transient() {
    let mut tracker = tracker_for_events(1.5);
    baseline_frames(&mut tracker);
    let (volume, weak) = feed_excursion(&mut tracker, 0.40, 3.0, 30);
    assert_eq!(weak.state, TrackerState::EndConfirmed);
    let weak_candidate = weak.candidate_volume.unwrap();
    let (_v, strong) = feed_excursion(&mut tracker, volume, 100.0, 30);
    assert_eq!(strong.state, TrackerState::EndConfirmed);
    let strong_candidate = strong.candidate_volume.unwrap();
    assert_ne!(strong_candidate, weak_candidate);
    assert!(strong_candidate > weak_candidate);
    assert_eq!(strong.event_count, 2);
    assert_eq!(strong.superseded_count, 1);
    assert!(strong.event_peak_speed > weak.event_peak_speed);
    assert_eq!(tracker.endpoint_volume(), Some(strong_candidate));
    assert_eq!(tracker.events().len(), 2);
}

/// 完全相同的两次激变，只有滞回不同：报告的终点不能抖动。
#[test]
fn supersede_ratio_suppresses_a_near_tie() {
    let mut loose = tracker_for_events(1.5);
    let mut tight = tracker_for_events(4.0);
    let mut outcomes = Vec::new();
    for tracker in [&mut loose, &mut tight] {
        baseline_frames(tracker);
        let (volume, _) = feed_excursion(tracker, 0.40, 3.0, 30);
        let (_, final_diag) = feed_excursion(tracker, volume, 4.0, 30);
        outcomes.push(final_diag);
    }
    assert_eq!(outcomes[0].superseded_count, 1);
    assert_eq!(outcomes[1].superseded_count, 0);
    assert!(outcomes[1].candidate_volume.unwrap() < outcomes[0].candidate_volume.unwrap());
    // 两个 tracker 看到相同的两次激变；只是报告的赢家不同。
    assert_eq!(outcomes[0].event_count, 2);
    assert_eq!(outcomes[1].event_count, 2);
}

/// js_speed 除以 ~1e-8，舍入地板量级的散度必须保持 0（放大的不能是算术噪声）。
#[test]
fn round_off_scale_divergence_is_not_normalised() {
    let mut tracker = SpectralFeatureTracker::new();
    tracker.update(0.05, &ones4());
    let tiny = tracker.update(0.10, &[1.0 + 1e-9, 1.0, 1.0, 1.0]);
    assert!(tiny.volume_sync_valid);
    assert_eq!(tiny.js_speed, 0.0);
    let real = tracker.update(0.15, &[2.0, 1.0, 1.0, 1.0]);
    assert!(real.js_speed > 0.0);
}

/// cross_entropy(p,p) 是 p 的熵，原始值永远出不了 IN_CHANGE；
/// cross_entropy_excess（=KL）为 0，旧路径（use_jsd=False）可用。
/// 两种模式的候选体积必须一致。
#[test]
fn legacy_cross_entropy_mode_confirms_an_endpoint() {
    let mut candidates = Vec::new();
    for use_jsd in [true, false] {
        let mut detector = EndpointDetector::with_options(0.0061, use_jsd, true, true, None);
        for index in 1..300 {
            let volume = index as f64 * 0.01;
            let voltage = 1.0 - 0.8 * gauss(volume, 1.0, 0.035);
            detector.feed_potential(volume, volume / 0.0061, voltage);
            let amplitude = 1.0 + 60.0 * gauss(volume, 1.0, 0.03);
            detector.feed_spectrum(volume, &[amplitude, 1.0, 1.0, 1.0]);
        }
        assert_eq!(detector.spectral_state(), TrackerState::EndConfirmed);
        candidates.push(
            detector
                .diagnostics()
                .spectral
                .map(|s| s.volume)
                .expect("spectral result"),
        );
    }
    approx::assert_relative_eq!(candidates[0], candidates[1], epsilon = 1e-9);
}
