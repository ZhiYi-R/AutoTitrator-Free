//! 电位通道可重入回归测试(2026-08-27 重构:体积域差分 + 最强事件胜出)。
//!
//! 动因(Exp1 实测):按时间差分被上位机时间戳毛刺(dt<50ms 占 15%)污染,
//! 0.735mL 处出现伪影假下陷并被一次性闩锁;真实突跃在 5.3–6.3mL 被完全忽略。

use controller_core::processing::endpoint::{DetectorParams, EndpointDetector};

fn gauss(x: f64, center: f64, sigma: f64) -> f64 {
    (-((x - center).powi(2)) / (2.0 * sigma * sigma)).exp()
}

/// 双下陷信号:早浅陷(深 d1)@early,晚深陷(深 d2>d1)@late。
/// depth 为 V/mL 域的导数深度量级(经 EWMA 后约为 -depth×0.8/...)。
fn feed_two_dips(detector: &mut EndpointDetector, early_at: f64, late_at: f64) {
    let mut vol = 0.0f64;
    while vol < 8.4 {
        vol += 0.01;
        let early = 0.35 * gauss(vol, early_at, 0.08);
        let late = 1.20 * gauss(vol, late_at, 0.10);
        let voltage = 1.0 - (early + late);
        detector.feed_potential(vol, vol / 0.0061, voltage);
    }
}

#[test]
fn late_deep_dip_supersedes_early_shallow() {
    let mut det = EndpointDetector::new(0.0061);
    feed_two_dips(&mut det, 1.5, 5.4);
    // 第一确认点附近状态应已 EndConfirmed(可重入),最终候选=最深事件。
    assert!(
        det.potential_endpoint_volume().is_some(),
        "must confirm an event"
    );
    let diag = det.diagnostics();
    let pot = diag.potential.expect("potential result");
    assert!(
        (pot.volume - 5.4).abs() < 0.25,
        "deepest event must win, got {}",
        pot.volume
    );
    assert!(diag.reliability.adaptive.potential_enter.is_some());
    // AMPD 精修后候选仍在晚陷附近(平滑输入,不再被 raw 尖峰带跑)。
    if let Some(refined) = det.refine_with_ampd() {
        assert!(
            (refined - 5.4).abs() < 0.45,
            "AMPD refinement near deep dip, got {refined}"
        );
    }
}

#[test]
fn volume_domain_derivative_is_time_jitter_immune() {
    // 相同电位序列喂两次:一次正常 dt,一次时间戳随机毛刺。
    // 体积域差分必须让两者终点一致(±1e-9),因为 _t 完全不参与。
    let mut a = EndpointDetector::new(0.0061);
    let mut b = EndpointDetector::new(0.0061);
    let mut state: u64 = 7;
    let mut jitter_t = 0.0;
    for index in 1..500usize {
        let volume = index as f64 * 0.01;
        let voltage = 1.0 - 1.2 * gauss(volume, 4.0, 0.08);
        a.feed_potential(volume, volume / 0.0061, voltage);
        state = state.wrapping_mul(6364136223846793005).wrapping_add(1);
        jitter_t += (state >> 40) as f64 % 0.31; // 0..~0.3s 随机步进
        b.feed_potential(volume, jitter_t, voltage);
    }
    let va = a.potential_endpoint_volume().unwrap();
    let vb = b.potential_endpoint_volume().unwrap();
    assert!((va - vb).abs() < 1e-9, "{va} vs {vb}");
    assert!((va - 4.0).abs() < 0.3, "endpoint at dip center, got {va}");
}

#[test]
fn legacy_fixed_mode_confirms_same_event() {
    // 固定阈值模式与自适应模式在同一双陷信号上选出同一最强事件
    // (自适应只是改变阈值来源,不改变"最强者胜出"语义)。
    let mut adaptive = EndpointDetector::new(0.0061);
    let mut fixed = EndpointDetector::with_params(
        0.0061,
        DetectorParams::legacy_fixed(),
        None,
    );
    feed_two_dips(&mut adaptive, 1.5, 5.4);
    feed_two_dips(&mut fixed, 1.5, 5.4);
    let va = adaptive.diagnostics().potential.unwrap().volume;
    let vf = fixed.diagnostics().potential.unwrap().volume;
    assert!((va - vf).abs() < 0.05, "adaptive {va} vs fixed {vf}");
}
