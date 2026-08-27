//! 把一次真实滴定的 CSV 记录按生产路径回放进 `EndpointDetector`。
//!
//! 用法：
//! ```text
//! cargo run -p controller-core --example replay_csv -- <potential.csv> <spectrum.csv>
//! ```
//!
//! 电位 CSV 列：`volume_mL,time_s,potential_V[,dE_dV]`；
//! 光谱 CSV 列：`volume_mL,time_s,ch0..ch9`（AS7341 原始 ADC 值）。
//! 两个文件按 `time_s` 归并成一条事件流，喂法与 `WorkflowEngine` 一致：
//! 光谱帧用它自己那一行的泵体积，检测器看到的是原始通道而非重建全谱。

use controller_core::processing::endpoint::{EndpointDetector, Method};
use controller_core::processing::endpoint::PotentialState;
use controller_core::processing::tracker::TrackerState;
use controller_core::processing::Reconstructor;

#[derive(Debug, Clone)]
enum Row {
    Potential { volume: f64, time: f64, e: f64 },
    Spectrum { volume: f64, time: f64, channels: Vec<f64> },
}

impl Row {
    fn time(&self) -> f64 {
        match self {
            Row::Potential { time, .. } | Row::Spectrum { time, .. } => *time,
        }
    }
}

fn read_rows(path: &str, spectral: bool) -> Vec<Row> {
    let text = std::fs::read_to_string(path).unwrap_or_else(|e| panic!("{path}: {e}"));
    let mut rows = Vec::new();
    for line in text.lines() {
        let line = line.trim();
        if line.is_empty() || line.starts_with('#') || line.starts_with("volume_mL") {
            continue;
        }
        let cells: Vec<&str> = line.split(',').collect();
        let need = if spectral { 12 } else { 3 };
        if cells.len() < need {
            continue;
        }
        let parse = |i: usize| cells[i].trim().parse::<f64>().ok();
        let (Some(volume), Some(time)) = (parse(0), parse(1)) else {
            continue;
        };
        if spectral {
            let channels: Option<Vec<f64>> = (2..12).map(parse).collect();
            if let Some(channels) = channels {
                rows.push(Row::Spectrum { volume, time, channels });
            }
        } else if let Some(e) = parse(2) {
            rows.push(Row::Potential { volume, time, e });
        }
    }
    rows
}

fn main() {
    let args: Vec<String> = std::env::args().skip(1).collect();
    let mut positional = Vec::new();
    let mut dump_path: Option<String> = None;
    let mut fixed = false;
    let mut raw_spectral = false;
    let mut i = 0;
    while i < args.len() {
        if args[i] == "--dump-stats" {
            i += 1;
            dump_path = args.get(i).cloned();
        } else if args[i] == "--fixed" {
            fixed = true;
        } else if args[i] == "--raw" {
            raw_spectral = true;
        } else {
            positional.push(args[i].clone());
        }
        i += 1;
    }
    if positional.len() < 2 {
        eprintln!("用法: replay_csv <potential.csv> <spectrum.csv> [--dump-stats out.json] [--fixed] [--raw]");
        std::process::exit(2);
    }
    // 生产路径：光谱帧经 calibre 重建为 721 点全谱喂检测器；--raw 对照原始 10 通道
    let reconstructor = (!raw_spectral)
        .then(Reconstructor::discover)
        .and_then(|result| result.ok().map(|(reconstructor, _)| reconstructor));
    if reconstructor.is_some() {
        println!("(光谱判据: 721 点完整重建谱，calibre 已加载)");
    } else {
        println!("(光谱判据: 原始 10 通道——calibre 缺失或 --raw)");
    }
    // --fixed: 固定阈值对照(legacy 行为),用于与自适应模式的决策对账。
    let detector_params = if fixed {
        controller_core::processing::endpoint::DetectorParams::legacy_fixed()
    } else {
        controller_core::processing::endpoint::DetectorParams::default()
    };
    let mut rows = read_rows(&positional[0], false);
    rows.extend(read_rows(&positional[1], true));
    rows.sort_by(|a, b| a.time().partial_cmp(&b.time()).unwrap());
    let pot_rows = rows.iter().filter(|r| matches!(r, Row::Potential { .. })).count();
    let spec_rows = rows.len() - pot_rows;
    println!("回放 {pot_rows} 个电位点 + {spec_rows} 帧光谱\n");

    // 生产流速：泵 2 标定默认斜率 × 1 kHz 步进频率。
    let flow_rate = controller_core::processing::calibration::PumpCalibration::default().flow_rate();
    let mut detector = EndpointDetector::with_params(flow_rate, detector_params, None);
    if fixed {
        println!("(对照模式: 固定阈值 legacy_fixed)");
    }

    // 每帧诊断导出（--dump-stats）：含原始平滑速度、基准距离与自适应快照。
    #[derive(serde::Serialize)]
    struct FrameStat {
        v: f64,
        t: f64,
        kind: &'static str,
        js_speed: f64,
        js_base: f64,
        d_pot: f64,
        adv_enter: Option<f64>,
        adv_exit: Option<f64>,
        adv_base: Option<f64>,
        // 状态机与事件诊断
        spec_state: String,
        pot_state: String,
        event_maturity: f64,
        candidate_volume: Option<f64>,
    }
    let mut frames: Vec<FrameStat> = Vec::new();

    let mut last_poll = f64::NEG_INFINITY;
    let mut pot_state = PotentialState::Idle;
    let mut spec_state = TrackerState::Idle;
    let mut pot_endpoint: Option<f64> = None;
    let mut spec_endpoint: Option<f64> = None;
    let mut last_method: Option<Method> = None;
    let mut t1: Option<(f64, f64, Method)> = None; // (触发体积, 报告终点, method)
    let mut volume = 0.0f64;
    let mut max_speed = 0.0f64;
    let mut max_speed_vol = 0.0f64;

    for row in &rows {
        match row {
            Row::Potential { volume: v, time, e } => {
                volume = *v;
                detector.feed_potential(*v, *time, *e);
            }
            Row::Spectrum { volume: v, time: _, channels } => {
                volume = *v;
                /* 生产路径：先经 calibre 重建为 721 点全谱；失败回退原始 10 通道 */
                let feed = reconstructor
                    .as_ref()
                    .and_then(|reconstructor| reconstructor.reconstruct(channels).ok())
                    .map(|(_, full)| full)
                    .unwrap_or_else(|| channels.clone());
                detector.feed_spectrum(*v, &feed);
            }
        }

        let diag = detector.diagnostics();
        frames.push(FrameStat {
            v: volume,
            t: row.time(),
            kind: match row {
                Row::Potential { .. } => "pot",
                Row::Spectrum { .. } => "spec",
            },
            js_speed: diag.spectral_features.js_speed_smooth,
            js_base: diag.spectral_features.js_base,
            d_pot: detector.last_potential_derivative(),
            adv_enter: diag.reliability.adaptive.spectral_enter,
            adv_exit: diag.reliability.adaptive.spectral_exit,
            adv_base: diag.reliability.adaptive.spectral_base,
            spec_state: diag.spectral_state.as_str().to_string(),
            pot_state: diag.potential_state.as_str().to_string(),
            event_maturity: diag.spectral_features.event_maturity,
            candidate_volume: diag.spectral_features.candidate_volume,
        });

        let speed = diag.spectral_features.js_speed_smooth;
        if speed > max_speed {
            max_speed = speed;
            max_speed_vol = volume;
        }

        if detector.potential_state() != pot_state {
            pot_state = detector.potential_state();
            println!("  {volume:7.4} mL  电位状态 -> {}", pot_state.as_str());
        }
        if detector.spectral_state() != spec_state {
            spec_state = detector.spectral_state();
            println!("  {volume:7.4} mL  光谱状态 -> {}", spec_state.as_str());
        }
        if detector.potential_endpoint_volume() != pot_endpoint {
            pot_endpoint = detector.potential_endpoint_volume();
            println!("  {volume:7.4} mL  电位候选 = {pot_endpoint:?}");
        }

        // 上层每 500 ms 决策一次
        if row.time() - last_poll < 0.5 {
            continue;
        }
        last_poll = row.time();
        let Some(result) = detector.detect() else {
            continue;
        };
        if result.spectral.as_ref().map(|s| s.volume) != spec_endpoint {
            spec_endpoint = result.spectral.as_ref().map(|s| s.volume);
            println!("  {volume:7.4} mL  光谱候选 = {spec_endpoint:?}");
        }
        if last_method != Some(result.method) {
            last_method = Some(result.method);
            println!(
                "  {volume:7.4} mL  method={:?} confidence={:?} 报告终点={:.4} status={}",
                result.method, result.confidence, result.volume, result.reliability.status
            );
        }
        // 工作流 T=1 判据（workflow.rs::poll）
        if t1.is_none() {
            let can_control = result.method == Method::Consensus
                || (matches!(result.method, Method::PotentialOnly | Method::Conflict)
                    && result.reliability.potential_evidence);
            if can_control {
                t1 = Some((volume, result.volume, result.method));
                println!(
                    "  {volume:7.4} mL  >>> T=1 触发，报告终点 {:.4} mL（method={:?}）",
                    result.volume, result.method
                );
            }
        }
    }

    println!("\n===== 回放结束（泵 2 停在 {volume:.4} mL）=====");
    println!("光谱平滑速度峰值 {max_speed:.6} @ {max_speed_vol:.4} mL（进入阈值 0.05）");
    match t1 {
        Some((at, reported, method)) => println!(
            "T=1: 在 {at:.4} mL 触发，报告终点 {reported:.4} mL，method={method:?}"
        ),
        None => println!("T=1: 全程未触发（泵不会停，滴定死锁）"),
    }

    let diagnostics = detector.diagnostics();
    println!("\n电位通道: state={} endpoint={:?}",
        diagnostics.potential_state.as_str(),
        diagnostics.potential.as_ref().map(|p| p.volume));
    println!("光谱通道: state={} endpoint={:?} events={} superseded={}",
        diagnostics.spectral_state.as_str(),
        diagnostics.spectral.as_ref().map(|s| s.volume),
        diagnostics.spectral_features.event_count,
        diagnostics.spectral_features.superseded_count);
    println!("光谱末帧: js_speed_smooth={:.6e} js_base={:.6e} baseline_ready={}",
        diagnostics.spectral_features.js_speed_smooth,
        diagnostics.spectral_features.js_base,
        diagnostics.spectral_features.baseline_ready);
    if let Some(kf) = &diagnostics.kf {
        println!("KF: initialized={} endpoint={:?} delay={:?} nis={:?} accepted={} reason={}",
            kf.initialized, kf.endpoint_volume, kf.spectral_delay, kf.nis, kf.accepted, kf.reason);
    }
    println!("可靠性: status={} reasons={:?}",
        diagnostics.reliability.status, diagnostics.reliability.reason_codes);

    match detector.refine_with_ampd() {
        Some(refined) => println!("\nAMPD 微调 -> {refined:.4} mL"),
        None => println!("\nAMPD 微调 -> 被拒（样本不足或峰位超过 0.9 尾部门限）"),
    }
    println!("最终 endpoint_volume() = {:?}", detector.endpoint_volume());

    if let Some(path) = dump_path {
        let json = serde_json::to_string_pretty(&frames).expect("serialize frames");
        std::fs::write(&path, json).unwrap_or_else(|e| panic!("write {path}: {e}"));
        println!("逐帧诊断已导出 -> {path}");
    }
}
