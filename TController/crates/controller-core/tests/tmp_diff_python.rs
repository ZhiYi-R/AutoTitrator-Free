//! 一次性差分测试：在真实滴定数据上与 Python 实现逐帧数值比对。
//!
//! 前置：需要仓库外的本地生成数据 `tmp_diff/dataA_python.json`
//! （输入事件序列 + Python 逐帧特征 + 最终结果，由本地脚本生成，未提交进仓库）。
//! 缺文件时跳过。这是移植验证用的一次性测试，两实现数值一致后即可删除。

use controller_core::processing::endpoint::EndpointDetector;
use serde_json::Value;

const JSON_PATH: &str = concat!(
    env!("CARGO_MANIFEST_DIR"),
    "/../../tmp_diff/dataA_python.json"
);

/// 相对 1e-9 + 绝对 1e-12：两实现的求和顺序差异（NumPy 成对求和 vs 顺序求和）
/// 引入 ~1e-16 相对噪声，留三个数量级裕量。
fn close(a: f64, b: f64) -> bool {
    (a - b).abs() <= 1e-12 + 1e-9 * a.abs().max(b.abs())
}

fn num<'a>(v: &'a Value) -> Option<f64> {
    v.as_f64()
}

struct Report {
    frames_checked: usize,
    pot_checked: usize,
    float_mismatch: usize,
    decision_mismatch: usize,
    first_issues: Vec<String>,
}

impl Report {
    fn issue(&mut self, msg: String, decision: bool) {
        if decision {
            self.decision_mismatch += 1;
        } else {
            self.float_mismatch += 1;
        }
        if self.first_issues.len() < 12 {
            self.first_issues.push(msg);
        }
    }
}

#[test]
fn matches_python_on_titration_data_a() {
    let Ok(text) = std::fs::read_to_string(JSON_PATH) else {
        eprintln!("跳过：未找到 {JSON_PATH}（该数据由仓库外的本地脚本生成）");
        return;
    };
    let data: Value = serde_json::from_str(&text).expect("parse json");
    let flow = data["flow_rate"].as_f64().expect("flow_rate");
    let events = data["events"].as_array().expect("events");
    let py_frames = data["frames"].as_array().expect("frames");
    let py_pot = data["pot_progress"].as_array().expect("pot_progress");
    let py_final = &data["final"];

    let mut det = EndpointDetector::new(flow);
    let scale = 3.3f64 / 65535.0;
    let mut rep = Report {
        frames_checked: 0,
        pot_checked: 0,
        float_mismatch: 0,
        decision_mismatch: 0,
        first_issues: Vec::new(),
    };

    let mut frame_i = 0usize;
    let mut pot_i = 0usize;

    for ev in events {
        let kind = ev[0].as_str().expect("kind");
        let vol = ev[1].as_f64().expect("vol");
        if kind == "pot" {
            let lsb = ev[2].as_f64().expect("lsb");
            det.feed_potential(vol, vol / flow, lsb * scale - 1.1);
            let py = &py_pot[pot_i];
            pot_i += 1;
            rep.pot_checked += 1;
            let idx = pot_i;

            let py_state = py[0].as_str().unwrap_or("?");
            if det.potential_state().as_str() != py_state {
                rep.issue(
                    format!(
                        "pot[{idx}] state {} vs {py_state}",
                        det.potential_state().as_str()
                    ),
                    true,
                );
            }
            match (det.potential_endpoint_volume(), num(&py[1])) {
                (Some(a), Some(b)) if close(a, b) => {}
                (None, None) => {}
                (a, b) => rep.issue(format!("pot[{idx}] ep_vol {a:?} vs {b:?}"), true),
            }
            let pyd = num(&py[2]).unwrap_or(f64::NAN);
            if !close(det.last_potential_derivative(), pyd) {
                rep.issue(
                    format!(
                        "pot[{idx}] d_sm {:.12e} vs {:.12e}",
                        det.last_potential_derivative(),
                        pyd
                    ),
                    false,
                );
            }
        } else {
            let spec: Vec<f64> = ev[2]
                .as_array()
                .expect("spectrum")
                .iter()
                .map(|v| v.as_f64().expect("ch"))
                .collect();
            det.feed_spectrum(vol, &spec);
            let f = det.diagnostics().spectral_features;
            let py = &py_frames[frame_i];
            frame_i += 1;
            rep.frames_checked += 1;
            let idx = frame_i;

            // 决策字段必须完全一致
            if f.state.as_str() != py["state"].as_str().unwrap_or("?") {
                rep.issue(
                    format!(
                        "frame[{idx}] state {} vs {}",
                        f.state.as_str(),
                        py["state"].as_str().unwrap_or("?")
                    ),
                    true,
                );
            }
            for key in [
                "event_count",
                "superseded_count",
                "recovery_frames",
                "repeated_volume_count",
                "nonmonotonic_count",
                "sample_count",
            ] {
                let mine = py[key].as_u64().unwrap_or(u64::MAX);
                let theirs = match key {
                    "event_count" => f.event_count as u64,
                    "superseded_count" => f.superseded_count as u64,
                    "recovery_frames" => f.recovery_frames as u64,
                    "repeated_volume_count" => f.repeated_volume_count as u64,
                    "nonmonotonic_count" => f.nonmonotonic_count as u64,
                    _ => f.sample_count as u64,
                };
                if mine != theirs {
                    rep.issue(format!("frame[{idx}] {key} {theirs} vs {mine}"), true);
                }
            }
            match (f.candidate_volume, num(&py["candidate_volume"])) {
                (Some(a), Some(b)) if close(a, b) => {}
                (None, None) => {}
                (a, b) => rep.issue(format!("frame[{idx}] candidate {a:?} vs {b:?}"), true),
            }

            // 浮点特征字段（容差内）
            for (key, mine) in [
                ("js_local", f.js_local),
                ("js_local_smooth", f.js_local_smooth),
                ("js_speed", f.js_speed),
                ("js_speed_smooth", f.js_speed_smooth),
                ("js_base", f.js_base),
                ("cross_curvature", f.cross_curvature),
            ] {
                let theirs = num(&py[key]).unwrap_or(f64::NAN);
                if !close(mine, theirs) {
                    rep.issue(
                        format!("frame[{idx}] {key} {mine:.9e} vs {theirs:.9e}"),
                        false,
                    );
                }
            }
        }
    }

    // ---- 最终结果 ----
    let py_pot_vol = num(&py_final["potential_volume"]).unwrap_or(f64::NAN);
    if !close(
        det.potential_endpoint_volume().unwrap_or(f64::NAN),
        py_pot_vol,
    ) {
        rep.issue(
            format!(
                "final potential_volume {:?} vs {py_pot_vol}",
                det.potential_endpoint_volume()
            ),
            true,
        );
    }
    let py_spec_vol = num(&py_final["spectral_volume"]).unwrap_or(f64::NAN);
    let my_spec_vol = det.endpoint_volume();
    // endpoint_volume 在 KF 可融合时返回融合值；光谱通道单独看 diagnostics
    let diag = det.diagnostics();
    let my_spec = diag.spectral.as_ref().map(|s| s.volume).unwrap_or(f64::NAN);
    if !close(my_spec, py_spec_vol) {
        rep.issue(
            format!("final spectral_volume {my_spec} vs {py_spec_vol}"),
            true,
        );
    }

    if let Some(py_detect) = py_final["detect"].as_object() {
        let result = det.detect().expect("detect");
        let py_method = py_detect["method"].as_str().unwrap_or("?");
        let py_conf = py_detect["confidence"].as_str().unwrap_or("?");
        let py_vol = num(&py_detect["volume"]).unwrap_or(f64::NAN);
        // 双方都对体积做了 round(·,3)，边界处允许 1 个最小刻度差
        if (result.volume - py_vol).abs() > 1.5e-3 {
            rep.issue(format!("detect volume {} vs {py_vol}", result.volume), true);
        }
        let my_method = match result.method {
            controller_core::processing::endpoint::Method::Consensus => "consensus",
            controller_core::processing::endpoint::Method::PotentialOnly => "potential_only",
            controller_core::processing::endpoint::Method::SpectralOnly => "spectral_only",
            controller_core::processing::endpoint::Method::Conflict => "conflict",
        };
        if my_method != py_method {
            rep.issue(format!("detect method {my_method} vs {py_method}"), true);
        }
        let my_conf = match result.confidence {
            controller_core::processing::endpoint::Confidence::High => "high",
            controller_core::processing::endpoint::Confidence::Medium => "medium",
            controller_core::processing::endpoint::Confidence::Low => "low",
        };
        if my_conf != py_conf {
            rep.issue(format!("detect confidence {my_conf} vs {py_conf}"), true);
        }
    }

    let py_status = py_final["reliability_status"].as_str().unwrap_or("?");
    if diag.reliability.status != py_status {
        rep.issue(
            format!("reliability {} vs {py_status}", diag.reliability.status),
            true,
        );
    }

    if let Some(py_kf) = py_final["kf"].as_object() {
        if let Some(my_kf) = &diag.kf {
            if let (Some(a), Some(b)) = (my_kf.endpoint_volume, num(&py_kf["endpoint_volume"])) {
                if !close(a, b) {
                    rep.issue(format!("kf endpoint_volume {a:.9} vs {b:.9}"), false);
                }
            }
            if let (Some(a), Some(b)) = (my_kf.endpoint_std, num(&py_kf["endpoint_std"])) {
                if !close(a, b) {
                    rep.issue(format!("kf endpoint_std {a:.9} vs {b:.9}"), false);
                }
            }
            if let (Some(a), Some(b)) = (my_kf.nis, num(&py_kf["nis"])) {
                if !close(a, b) {
                    rep.issue(format!("kf nis {a:.9} vs {b:.9}"), false);
                }
            }
        } else {
            rep.issue("kf missing on rust side".into(), true);
        }
    }

    // refine_with_ampd：Python 在该数据上返回 None
    let py_refine = num(&py_final["refine_with_ampd"]);
    let my_refine = det.refine_with_ampd();
    match (my_refine, py_refine) {
        (None, None) => {}
        (Some(a), Some(b)) if close(a, b) => {}
        (a, b) => rep.issue(format!("refine_with_ampd {a:?} vs {b:?}"), true),
    }

    println!(
        "== 差分比对：{} 电位点, {} 光谱帧；浮点失配 {}, 决策失配 {} ==",
        rep.pot_checked, rep.frames_checked, rep.float_mismatch, rep.decision_mismatch
    );
    for msg in &rep.first_issues {
        println!("  {msg}");
    }

    assert_eq!(
        rep.decision_mismatch, 0,
        "决策字段（状态/计数/终点）必须与 Python 完全一致"
    );
    assert_eq!(rep.float_mismatch, 0, "浮点特征存在超出容差(1e-9)的失配");
    let _ = my_spec_vol;
}
