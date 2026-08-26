//! 永久变色判别回归测试(2026-08-27,源于人工确认的"变色→褪色"模式)。
//!
//! 化学语义:终点附近的指示剂事件是"升起→回落但回不到基线"(永久形态切换);
//! 普通激变是"升起→完全回落到事件前水平"(瞬态)。报告的光谱终点必须是
//! 永久事件的候选体积——即使瞬态更强(峰值速度更大)。

use controller_core::processing::adaptive::AdaptiveParams;
use controller_core::processing::tracker::{SpectralFeatureTracker, TrackerState};

fn track<F: Fn(f64) -> Vec<f64>>(spectrum_at: F, n: usize) -> SpectralFeatureTracker {
    // 固定阈值 + 永久变色判别开启(判别独立于自适应阈值估计)。
    let mut tr = SpectralFeatureTracker::new();
    tr.set_adaptive(&AdaptiveParams {
        enabled: false,
        permanent_color: true,
        ..AdaptiveParams::legacy_fixed()
    });
    for i in 0..n {
        let v = i as f64 * 0.01;
        tr.update(v, &spectrum_at(v));
    }
    tr
}

#[test]
fn transient_then_permanent_picks_permanent() {
    // 0.5mL 处强瞬态(ch0 短暂抬升后回落);3.0mL 处弱一些的永久阶跃。
    // 瞬态峰值速度更高,若按旧"最强者胜出"会错报 0.5。
    let spec = |v: f64| -> [f64; 4] {
        let transient = (1.0 - gauss(v, 0.55, 0.06) * 8.0).max(0.2);
        let permanent = if v < 3.0 { 1.0 } else { 1.35 };
        [transient.max(permanent), 1.0, 1.0, 1.0]
    };
    let tr = track(|v| spec(v).to_vec(), 600);
    assert_eq!(tr.last().state, TrackerState::EndConfirmed);
    let endpoint = tr.endpoint_volume().expect("endpoint");
    assert!(
        (endpoint - 3.05).abs() < 0.6,
        "permanent step must win over stronger transient, got {endpoint}"
    );
}

#[test]
fn pure_transient_reports_its_own_candidate() {
    // 只有一个纯瞬态(无永久事件):它就是最强事件,照常报告。
    let spec = |v: f64| -> [f64; 4] {
        [(1.0 - gauss(v, 1.0, 0.08) * 9.0).max(0.15), 1.0, 1.0, 1.0]
    };
    let tr = track(|v| spec(v).to_vec(), 500);
    let endpoint = tr.endpoint_volume().expect("endpoint");
    assert!((endpoint - 1.02).abs() < 0.4, "got {endpoint}");
    // 但其 permanent 标记应最终被追溯降级。
    let events = tr.events();
    assert!(events.iter().any(|e| e.permanent == Some(false)));
}

#[test]
fn late_transient_cannot_dethrone_permanent() {
    // 永久阶跃在 2.0mL 提交(候选 5.13 略偏,因台阶渐变的前段就触发);
    // 之后 5.41mL 更强的纯瞬态不许顶替(化学上终点已过)。
    let spec = |v: f64| -> [f64; 4] {
        let base = if v < 2.0 { 1.0 } else { 1.30 };
        let spike = if (5.0..5.4).contains(&v) { 10.0 } else { 0.0 };
        [base + spike * gauss(v, 5.2, 0.08), 1.0, 1.0, 1.0]
    };
    let tr = track(|v| spec(v).to_vec(), 700);
    let endpoint = tr.endpoint_volume().expect("endpoint");
    // 关键:winner 是阶跃后立即提交的永久事件(~5.13 或 ~2.0 一侧),
    // 绝不能落在瞬态峰位 5.41。
    assert!(
        (endpoint - 5.41).abs() > 0.15,
        "transient peak must NOT win, got {endpoint}"
    );
}

fn gauss(x: f64, center: f64, sigma: f64) -> f64 {
    (-((x - center).powi(2)) / (2.0 * sigma * sigma)).exp()
}
