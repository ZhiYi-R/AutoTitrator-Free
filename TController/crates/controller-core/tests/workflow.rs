//! 工作流状态机测试 — 含 Python 版曾实际发生的 T=1 死锁回归。

use controller_core::processing::calibration::PumpCalibration;
use controller_core::workflow::{PumpCommand, TitrationState, WorkflowEngine};

fn gauss(x: f64, center: f64, sigma: f64) -> f64 {
    (-((x - center).powi(2)) / (2.0 * sigma * sigma)).exp()
}

/// 1 步 = 0.01 mL 的整定（便于精确驱动体积）。
fn engine() -> WorkflowEngine {
    WorkflowEngine::new(
        0.0061,
        PumpCalibration {
            slope: 0.01,
            intercept: 0.0,
        },
    )
}

/// 注入 → 滴定，然后按 0.01 mL 步进喂电位+光谱并逐点 poll。
/// 电位下陷在 `pot_center`，光谱激变在 `spec_center`（幅度 60，σ=0.03）。
/// 返回 (T=1 结果, T=2 结果)。
struct DriveResult {
    t1: Option<(f64, bool)>, // (endpoint, conflict_at_t1)
    /// (停止时泵 2 体积, AMPD 精修后终点)
    t2: Option<(f64, Option<f64>)>,
}

fn drive(
    engine: &mut WorkflowEngine,
    steps: u32,
    pot_center: f64,
    spec_center: f64,
    stop_after_t1: bool,
) -> DriveResult {
    let start = engine.start(5.0);
    assert!(matches!(
        start.commands[..],
        [PumpCommand::MaxCount { pump: 1, .. }]
    ));
    let done = engine.on_pump_done(1);
    assert!(matches!(done.commands[..], [PumpCommand::FreeRun(2)]));
    assert_eq!(engine.state, TitrationState::Titrating);

    let mut out = DriveResult { t1: None, t2: None };
    for i in 1..=steps {
        let vol = i as f64 * 0.01;
        let t = vol / 0.0061;
        let voltage = 1.0 - 0.8 * gauss(vol, pot_center, 0.035);
        engine.on_adc(i, t, voltage);
        let amplitude = 1.0 + 60.0 * gauss(vol, spec_center, 0.03);
        engine.on_spectrum(&[amplitude, 1.0, 1.0, 1.0]);

        let outcome = engine.poll();
        if outcome.first_endpoint.is_some() && out.t1.is_none() {
            out.t1 = Some((outcome.first_endpoint.unwrap(), outcome.conflict_at_t1));
            if stop_after_t1 {
                return out;
            }
        }
        if outcome.state == TitrationState::Done && out.t2.is_none() {
            assert!(matches!(outcome.commands[..], [PumpCommand::FreeStop(2)]));
            out.t2 = Some((engine.pump2_volume(), outcome.refined_endpoint));
            return out;
        }
    }
    out
}

#[test]
fn consensus_happy_path_reaches_t2_with_ampd_refinement() {
    let mut engine = engine();
    let result = drive(&mut engine, 400, 1.0, 1.0, false);
    let (t1_vol, conflict) = result.t1.expect("T=1 must trigger");
    assert!(!conflict);
    assert!((t1_vol - 1.0).abs() < 0.3, "T1 endpoint {t1_vol}");
    let (stop_vol, refined) = result.t2.expect("T=2 must trigger");
    // T=2 判据：实际泵 2 体积到达 2×T1 终点
    assert!(stop_vol >= 2.0 * t1_vol - 0.05, "stop volume {stop_vol}");
    let refined = refined.expect("AMPD refinement");
    assert!((refined - 1.0).abs() < 0.2, "refined {refined}");
    assert_eq!(engine.state, TitrationState::Done);
}

/// 死锁回归（Python 实际发生过）：双模态均确认但未过 NIS 门控 →
/// method=conflict。判据必须按"有电位证据"放行 T=1，否则泵无限运行。
/// 场景：光谱事件先出现在 1.0 mL（此时无电位证据，不得控泵），
/// 电位终点在 3.5 mL 确认 → conflict 放行 T=1。
#[test]
fn spectral_only_does_not_control_then_conflict_still_triggers_t1() {
    let mut engine = engine();

    // 阶段 1：光谱已确认、电位未确认 → spectral_only，绝不 T=1。
    let early = drive(&mut engine, 300, 3.5, 1.0, false);
    assert!(
        early.t1.is_none(),
        "spectral_only 不得控泵（t1={:?}）",
        early.t1
    );
    assert_eq!(engine.state, TitrationState::Titrating);

    // 阶段 2：继续喂到电位终点确认 → conflict（两模态差 2.5 mL，KF 必拒）
    // → 但有电位证据 → T=1 必须触发。
    let mut t1 = None;
    for i in 301..=460u32 {
        let vol = i as f64 * 0.01;
        let t = vol / 0.0061;
        let voltage = 1.0 - 0.8 * gauss(vol, 3.5, 0.035);
        engine.on_adc(i, t, voltage);
        let amplitude = 1.0 + 60.0 * gauss(vol, 1.0, 0.03);
        engine.on_spectrum(&[amplitude, 1.0, 1.0, 1.0]);
        let outcome = engine.poll();
        if outcome.first_endpoint.is_some() {
            t1 = Some((outcome.first_endpoint.unwrap(), outcome.conflict_at_t1));
            break;
        }
    }
    let (vol, conflict) = t1.expect("conflict + potential evidence 必须 T=1");
    assert!(conflict, "KF 门控应拒绝 2.5 mL 偏差 → conflict");
    assert!((vol - 3.5).abs() < 0.4, "conflict 退回电位终点 {vol}");
    assert_eq!(engine.state, TitrationState::Degree1);
}

#[test]
fn manual_stop_refines_and_completes() {
    let mut engine = engine();
    drive(&mut engine, 200, 1.0, 1.0, true); // 到 T=1 即返回
                                             // AMPD 需要足够历史（峰位须被多尺度覆盖；短记录返回 None 属正常行为，
                                             // 与 Python 一致），继续滴到 2.5 mL 再手动停止。
    for i in 201..=250u32 {
        let vol = i as f64 * 0.01;
        let t = vol / 0.0061;
        let voltage = 1.0 - 0.8 * gauss(vol, 1.0, 0.035);
        engine.on_adc(i, t, voltage);
        engine.on_spectrum(&[1.0, 1.0, 1.0, 1.0]);
    }
    assert!(engine.can_manual_stop());
    let outcome = engine.manual_stop();
    assert_eq!(outcome.state, TitrationState::Done);
    assert!(matches!(outcome.commands[..], [PumpCommand::FreeStop(2)]));
    let refined = outcome.refined_endpoint.expect("AMPD refinement");
    assert!((refined - 1.0).abs() < 0.2, "refined {refined}");
    assert!(!engine.can_manual_stop());
}

#[test]
fn abort_returns_to_idle() {
    let mut engine = engine();
    drive(&mut engine, 150, 1.0, 1.0, false);
    let outcome = engine.abort();
    assert_eq!(outcome.state, TitrationState::Idle);
    assert!(outcome.commands.is_empty());
    assert_eq!(engine.endpoint_volume(), None);
}
