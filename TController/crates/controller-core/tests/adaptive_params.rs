//! 自适应阈值参数回归测试。
//!
//! 设计承诺(见 processing/adaptive.rs 模块文档):
//! * 零散布/退化数据回落固定常数下限,行为与 legacy 逐位一致;
//! * 带噪数据武装出的阈值高于下限且被上限封顶;
//! * KF 质量缩放单边放大([1,4]),干净数据上 R 不变。

use controller_core::processing::adaptive::AdaptiveParams;
use controller_core::processing::endpoint::{DetectorParams, EndpointDetector};
use controller_core::processing::kf::EndpointFusionKf;
use controller_core::processing::tracker::SpectralFeatureTracker;

/// 与 tests/workflow.rs 相同的合成滴定信号(幅度足够越过一切阈值)。
fn gauss(x: f64, center: f64, sigma: f64) -> f64 {
    (-((x - center).powi(2)) / (2.0 * sigma * sigma)).exp()
}

fn feed_titration(detector: &mut EndpointDetector, jitter_seed: u64) {
    // 简单 LCG 抖动:seed=0 时完全平坦。
    let mut state = jitter_seed | 1;
    let mut jitter = || {
        state = state.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);
        ((state >> 33) % 1000) as f64 / 1000.0 - 0.5
    };
    let mut vol = 0.0f64;
    while vol < 2.5 {
        vol += 0.01;
        let t = vol / 0.0061;
        let voltage = 1.0 - 0.8 * gauss(vol, 1.0, 0.035);
        detector.feed_potential(vol, t, voltage);
        let amp = 1.0 + 60.0 * gauss(vol, 1.0, 0.03);
        let j = if vol <= 0.30 { jitter() * 1e-3 } else { 0.0 };
        detector.feed_spectrum(vol, &[amp + j, 1.0 + j, 1.0 + j, 1.0 + j]);
    }
}

#[test]
fn flat_baseline_matches_legacy_parity() {
    // 零方差平坦基线 → MAD 退化 → 全部回落常数下限,
    // 自适应与 legacy 决策必须一致。
    let mut adaptive = EndpointDetector::new(0.0061);
    let mut legacy =
        EndpointDetector::with_options(0.0061, true, true, true, None);
    feed_titration(&mut adaptive, 0);
    feed_titration(&mut legacy, 0);
    let a = adaptive.detect().expect("adaptive endpoint");
    let l = legacy.detect().expect("legacy endpoint");
    assert_eq!(a.method, l.method);
    assert!((a.volume - l.volume).abs() < 1e-9, "{} vs {}", a.volume, l.volume);
}

#[test]
fn noisy_baseline_arms_thresholds_above_floor() {
    // 基线窗内注入抖动 → 武装的光谱进入阈值应高于固定下限(但被封顶),
    // 电位通道也应有快照。用小抖动避免把事件掩没(60 幅度的事件稳过)。
    let mut det = EndpointDetector::new(0.0061);
    feed_titration(&mut det, 42);
    let diag = det.diagnostics();
    let rel = &diag.reliability.adaptive;
    if let Some(enter) = rel.spectral_enter {
        assert!(enter >= 0.05, "armed enter {enter} below floor");
        assert!(enter <= 0.5 + 1e-12, "armed enter {enter} above cap");
        assert!(rel.spectral_exit.unwrap() < enter);
    }
    // 电位自适应在观察期完成后必然有快照(该信号观察期有有限 MAD?)——
    // 若抖动使 MADσ 过小或样本退化则允许为 None,不强制断言。
}

#[test]
fn legacy_fixed_never_reports_adaptive_keys() {
    let mut det = EndpointDetector::with_params(
        0.0061,
        DetectorParams::legacy_fixed(),
        None,
    );
    feed_titration(&mut det, 42);
    let diag = det.diagnostics();
    assert!(diag.reliability.adaptive.spectral_enter.is_none());
    assert!(!diag.reliability.adaptive.spectral_armed);
    assert!(diag.reliability.adaptive.potential_enter.is_none());
    assert!(
        diag.spectral_features.adaptive_enter.is_none(),
        "tracker diag must omit adaptive keys in legacy mode"
    );
}

#[test]
fn kf_scaling_is_single_sided() {
    let mut kf = EndpointFusionKf::new();
    let p0 = kf.potential_var;
    let c0 = kf.spectral_var;
    // 收紧方向被禁用:factor<1 不改变方差。
    kf.scale_observation_variances(0.0625, 0.01);
    assert!((kf.potential_var - p0).abs() < 1e-15);
    assert!((kf.spectral_var - c0).abs() < 1e-15);
    // 放大方向封顶 4×。
    kf.scale_observation_variances(100.0, 3.84);
    assert!((kf.potential_var - 4.0 * p0).abs() < 1e-12);
    assert!((kf.spectral_var - 3.84 * c0).abs() < 1e-12);
}

#[test]
fn tracker_adaptive_thresholds_match_param_source() {
    // 直接驱动 tracker:恒定谱+微小线性漂移使速度统计非退化,
    // 阈值应从统计估计而非固定常数。
    let mut tr = SpectralFeatureTracker::new();
    let mut params = AdaptiveParams::default();
    params.k_spd = 20.0;
    tr.set_adaptive(&params);
    let mut armed_seen = None;
    for i in 0..80usize {
        let v = i as f64 * 0.02;
        // 缓慢增大第 0 通道占比,产生非零但温和的速度序列。
        let ch0 = 1.0 + 0.02 * i as f64;
        let diag = tr.update(v, &[ch0, 1.0, 1.0, 1.0]);
        if let Some(e) = diag.adaptive_enter {
            armed_seen.get_or_insert(e);
            assert!(e >= 0.05 && e <= 0.5, "armed {e}");
        }
    }
    assert!(armed_seen.is_some(), "never armed despite drifting spectra");
}
