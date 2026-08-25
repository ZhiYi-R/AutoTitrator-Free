//! 因果在线滴定终点检测器 — Python `EndpointDetector` 的移植。
//!
//! 电位通道走既有因果 EWMA 状态机；光谱通道委托 [`SpectralFeatureTracker`]
//! （有界 JS 信号、因果交叉曲率、终点/延迟两状态 KF 融合）。任何特征都不
//! 使用未来样本。
//!
//! 任一模态的终点都可能事后修正——光谱端被更强激变顶替、电位端被 AMPD
//! 精修——所以观测对变化时 KF 从头重跑：用陈旧状态门控修正值只会拒绝修正。

use serde::Serialize;

use super::ampd::ampd_peak_idx;
use super::ewma::Ewma;
use super::kf::{EndpointFusionKf, ObservationKind};
use super::tracker::{SpectralFeatureTracker, TrackerState};

// ---- 电位通道参数（Python 同名常量）----
pub const POT_V_ALPHA: f64 = 0.15;
pub const POT_D_ALPHA: f64 = 0.05;
/// 观察期体积（mL）：此前只累计基线统计，不驱动状态机。
pub const POT_OBSERVE_VOL: f64 = 0.1;
pub const POT_ENTER_SIGMA: f64 = 2.5;
pub const POT_EXIT_SIGMA: f64 = 2.5;
pub const POT_MIN_ENTER: f64 = 0.005;
pub const POT_MIN_EXIT: f64 = 0.001;
/// 进入→退出之间的最小确认体积（mL）。
pub const POT_CONFIRM_VOL: f64 = 0.15;

// ---- 光谱通道参数（JS 时代阈值，nats/mL²）----
pub const SPEC_CE_ALPHA: f64 = 0.20;
pub const SPEC_ENTER: f64 = 1e-3;
pub const SPEC_EXIT: f64 = 1e-4;
pub const SPEC_CONFIRM_FRAMES: usize = 10;

pub const SPEC_JS_ENTER: f64 = 0.05;
pub const SPEC_JS_EXIT: f64 = 0.008;
pub const SPEC_BASELINE_ENTER: f64 = 3e-7;
pub const SPEC_BASELINE_FRAMES: usize = 12;
pub const SPEC_BASELINE_MAX_VOL: f64 = 0.30;
pub const SPEC_MIN_EVENT_VOL: f64 = 0.08;
/// 后发激变须强过的倍数才能顶替终点。
pub const SPEC_SUPERSEDE_RATIO: f64 = 1.5;

/// AMPD 精修拒绝的尾部位置上限：最大尺度只覆盖窗口中部，尾部峰支持的尺度
/// 很少；0.75 曾静默拒绝手动停止稍晚于等价点的合法终点，故守在无支撑尾部
/// 之内。
pub const AMPD_MAX_POSITION: f64 = 0.9;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize)]
#[serde(rename_all = "snake_case")]
pub enum PotentialState {
    Idle,
    Tracking,
    EndConfirmed,
}

impl PotentialState {
    pub fn as_str(self) -> &'static str {
        match self {
            PotentialState::Idle => "IDLE",
            PotentialState::Tracking => "TRACKING",
            PotentialState::EndConfirmed => "END_CONFIRMED",
        }
    }
}

/// 电位通道结果（Python `_build_pot_result`）。
#[derive(Debug, Clone, Serialize)]
pub struct PotentialResult {
    pub volume: f64,
    pub time: f64,
    pub min_dvdt: f64,
    pub state: PotentialState,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub endpoint_std: Option<f64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub nis: Option<f64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub innovation: Option<f64>,
}

/// 光谱通道结果（Python `_build_spec_result`；max_ce 为旧导出兼容别名）。
#[derive(Debug, Clone, Serialize)]
pub struct SpectralResult {
    pub volume: f64,
    pub time: f64,
    pub max_ce: f64,
    pub max_js: f64,
    pub js_local: f64,
    pub js_speed: f64,
    pub js_base: f64,
    pub cross_curvature: Option<f64>,
    pub event_maturity: f64,
    pub recovery_frames: usize,
    pub event_count: usize,
    pub superseded_count: usize,
    pub event_peak_speed: f64,
    pub state: TrackerState,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize)]
#[serde(rename_all = "lowercase")]
pub enum Confidence {
    High,
    Medium,
    Low,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize)]
#[serde(rename_all = "snake_case")]
pub enum Method {
    /// KF 融合双模态（或 KF 关闭时 |ΔV|<0.3 mL 取均值）。
    Consensus,
    PotentialOnly,
    SpectralOnly,
    /// 双模态均确认但未过 NIS 门控，退回电位。
    Conflict,
}

/// 数据质量子结构。
#[derive(Debug, Clone, Serialize)]
pub struct DataQualityInfo {
    pub potential_samples: usize,
    pub spectral_samples: usize,
    pub valid_spectral_frames: usize,
    pub baseline_ready: bool,
    pub repeated_spectral_volume: usize,
    pub nonmonotonic_volume: usize,
    pub last_frame: String,
}

/// 双模态一致性子结构。
#[derive(Debug, Clone, Serialize)]
pub struct ModalConsistency {
    pub agreement_ml: Option<f64>,
    pub kf_consistent: Option<bool>,
}

/// 在线可靠性（Python `_build_reliability`）。
#[derive(Debug, Clone, Serialize)]
pub struct Reliability {
    pub status: String,
    pub data_quality: DataQualityInfo,
    pub potential_evidence: bool,
    pub spectral_evidence: bool,
    pub modal_consistency: ModalConsistency,
    pub event_maturity: f64,
    pub spectral_events: usize,
    pub spectral_superseded: usize,
    pub endpoint_std: Option<f64>,
    pub spectral_delay: Option<f64>,
    pub nis: Option<f64>,
    pub innovation: Option<f64>,
    pub reason_codes: Vec<String>,
}

/// `detect()` 的最终结果。
#[derive(Debug, Clone, Serialize)]
pub struct EndpointResult {
    pub volume: f64,
    pub time: f64,
    pub confidence: Confidence,
    pub method: Method,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub potential: Option<PotentialResult>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub spectral: Option<SpectralResult>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub warning: Option<String>,
    pub reliability: Reliability,
}

/// 检测器完整诊断（Python `diagnostics()`）。
#[derive(Debug, Clone, Serialize)]
pub struct DetectorDiagnostics {
    pub potential_state: PotentialState,
    pub spectral_state: TrackerState,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub potential: Option<PotentialResult>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub spectral: Option<SpectralResult>,
    pub spectral_features: super::tracker::Diagnostics,
    pub kf: Option<super::kf::KfSnapshot>,
    pub reliability: Reliability,
}

/// 因果终点检测器（电位 + 全场光谱）。
pub struct EndpointDetector {
    flow_rate: f64,
    pub use_jsd: bool,
    pub enable_curvature: bool,
    pub enable_kf: bool,
    spectrum_axis: Option<Vec<f64>>,

    // 电位状态
    pot_v_smooth: Ewma,
    pot_d_smooth: Ewma,
    pot_prev_v: Option<f64>,
    pot_prev_t: Option<f64>,
    pot_state: PotentialState,
    pot_ep_vol: Option<f64>,
    pot_min_d: f64,
    pot_cand_vol: Option<f64>,
    pot_entry_vol: Option<f64>,
    pot_done: bool,
    pot_d_vals: Vec<f64>,
    pot_obs_done: bool,
    pot_enter_th: f64,
    pot_exit_th: f64,
    pot_raw_buf: Vec<f64>,
    pot_vol_buf: Vec<f64>,
    pot_sample_count: usize,
    last_pot_result: Option<PotentialResult>,

    // 光谱状态（委托 tracker）
    spectral: SpectralFeatureTracker,
    spec_ep_vol: Option<f64>,
    spec_max_js: f64,
    last_spec_diag: super::tracker::Diagnostics,
    last_spec_result: Option<SpectralResult>,

    kf: Option<EndpointFusionKf>,
    kf_consumed: Option<(Option<f64>, Option<f64>)>,
    last_reliability: Reliability,
}

impl EndpointDetector {
    pub fn new(flow_rate: f64) -> Self {
        Self::with_options(flow_rate, true, true, true, None)
    }

    pub fn with_options(
        flow_rate: f64,
        use_jsd: bool,
        enable_curvature: bool,
        enable_kf: bool,
        wavelengths: Option<&[f64]>,
    ) -> Self {
        let spectral = SpectralFeatureTracker::with_params(
            SPEC_CE_ALPHA,
            if use_jsd { SPEC_JS_ENTER } else { SPEC_ENTER },
            if use_jsd { SPEC_JS_EXIT } else { SPEC_EXIT },
            SPEC_BASELINE_ENTER,
            SPEC_BASELINE_FRAMES,
            SPEC_BASELINE_MAX_VOL,
            SPEC_CONFIRM_FRAMES,
            SPEC_MIN_EVENT_VOL,
            1e-8,
            8,
            SPEC_SUPERSEDE_RATIO,
            super::divergence::JS_FLOOR,
            use_jsd,
        );
        let mut det = Self {
            flow_rate,
            use_jsd,
            enable_curvature,
            enable_kf,
            spectrum_axis: wavelengths.map(|w| w.to_vec()),
            pot_v_smooth: Ewma::new(POT_V_ALPHA),
            pot_d_smooth: Ewma::new(POT_D_ALPHA),
            pot_prev_v: None,
            pot_prev_t: None,
            pot_state: PotentialState::Idle,
            pot_ep_vol: None,
            pot_min_d: 0.0,
            pot_cand_vol: None,
            pot_entry_vol: None,
            pot_done: false,
            pot_d_vals: Vec::new(),
            pot_obs_done: false,
            pot_enter_th: -1e9,
            pot_exit_th: -1e9,
            pot_raw_buf: Vec::new(),
            pot_vol_buf: Vec::new(),
            pot_sample_count: 0,
            last_pot_result: None,
            spectral,
            spec_ep_vol: None,
            spec_max_js: 0.0,
            last_spec_diag: Default::default(),
            last_spec_result: None,
            kf: enable_kf.then(EndpointFusionKf::new),
            kf_consumed: None,
            last_reliability: Reliability {
                status: "UNOBSERVABLE".into(),
                data_quality: DataQualityInfo {
                    potential_samples: 0,
                    spectral_samples: 0,
                    valid_spectral_frames: 0,
                    baseline_ready: false,
                    repeated_spectral_volume: 0,
                    nonmonotonic_volume: 0,
                    last_frame: "no_spectrum".into(),
                },
                potential_evidence: false,
                spectral_evidence: false,
                modal_consistency: ModalConsistency {
                    agreement_ml: None,
                    kf_consistent: None,
                },
                event_maturity: 0.0,
                spectral_events: 0,
                spectral_superseded: 0,
                endpoint_std: None,
                spectral_delay: None,
                nis: None,
                innovation: None,
                reason_codes: Vec::new(),
            },
        };
        if let Some(axis) = det.spectrum_axis.clone() {
            let _ = det.spectral.set_wavelengths(Some(&axis));
        }
        det.reset_state();
        det
    }

    fn reset_state(&mut self) {
        self.pot_v_smooth = Ewma::new(POT_V_ALPHA);
        self.pot_d_smooth = Ewma::new(POT_D_ALPHA);
        self.pot_prev_v = None;
        self.pot_prev_t = None;
        self.pot_state = PotentialState::Idle;
        self.pot_ep_vol = None;
        self.pot_min_d = 0.0;
        self.pot_cand_vol = None;
        self.pot_entry_vol = None;
        self.pot_done = false;
        self.pot_d_vals.clear();
        self.pot_obs_done = false;
        self.pot_enter_th = -1e9;
        self.pot_exit_th = -1e9;
        self.pot_raw_buf.clear();
        self.pot_vol_buf.clear();
        self.pot_sample_count = 0;
        self.last_pot_result = None;

        self.spectral.reset();
        if let Some(axis) = self.spectrum_axis.clone() {
            let _ = self.spectral.set_wavelengths(Some(&axis));
        }
        self.spec_ep_vol = None;
        self.spec_max_js = 0.0;
        self.last_spec_diag = Default::default();
        self.last_spec_result = None;

        if let Some(kf) = self.kf.as_mut() {
            kf.reset();
        }
        self.kf_consumed = None;
        self.last_reliability = self.build_reliability(None, None);
    }

    /// 清空全部滤波器与状态，开始新滴定。
    pub fn reset(&mut self) {
        self.reset_state();
    }

    pub fn set_spectrum_axis(&mut self, wavelengths: Option<&[f64]>) {
        self.spectrum_axis = wavelengths.map(|w| w.to_vec());
        let _ = self.spectral.set_wavelengths(self.spectrum_axis.as_deref());
    }

    // ================================================================
    //  数据输入
    // ================================================================

    /// 喂入一个电位点：体积 mL、时间 s、电压 V。
    pub fn feed_potential(&mut self, vol: f64, t: f64, v: f64) {
        let vol = vol;
        let t = t;
        let v_sm = self.pot_v_smooth.push(v);

        let d_raw = match (self.pot_prev_t, self.pot_prev_v) {
            (Some(pt), Some(pv)) if t - pt > 0.0 => (v_sm - pv) / (t - pt),
            _ => 0.0,
        };
        let d_sm = self.pot_d_smooth.push(d_raw);
        self.pot_prev_v = Some(v_sm);
        self.pot_prev_t = Some(t);
        self.pot_sample_count += 1;
        self.pot_raw_buf.push(d_raw);
        self.pot_vol_buf.push(vol);

        if !self.pot_obs_done {
            self.pot_d_vals.push(d_sm);
            if vol >= POT_OBSERVE_VOL {
                let arr = std::mem::take(&mut self.pot_d_vals);
                if arr.len() < 3 {
                    self.pot_d_vals = arr;
                    return;
                }
                let n = arr.len() as f64;
                let mean = super::divergence::np_sum(&arr) / n;
                // ddof=1 样本标准差
                let var = super::divergence::np_sum(
                    &arr.iter()
                        .map(|x| (x - mean) * (x - mean))
                        .collect::<Vec<_>>(),
                ) / (n - 1.0);
                let std = var.sqrt().max(mean.abs() * 0.01).max(1e-6);
                self.pot_enter_th = mean - POT_MIN_ENTER.max(POT_ENTER_SIGMA * std);
                self.pot_exit_th = mean - POT_MIN_EXIT.max(POT_EXIT_SIGMA * std);
                self.pot_obs_done = true;
                self.pot_d_vals.clear();
            }
            return;
        }

        if !self.pot_done {
            match self.pot_state {
                PotentialState::Idle if d_sm < self.pot_enter_th => {
                    self.pot_state = PotentialState::Tracking;
                    self.pot_min_d = d_sm;
                    self.pot_cand_vol = Some(vol);
                    self.pot_entry_vol = Some(vol);
                }
                PotentialState::Tracking => {
                    if d_sm < self.pot_min_d {
                        self.pot_min_d = d_sm;
                        self.pot_cand_vol = Some(vol);
                    }
                    if d_sm > self.pot_exit_th
                        && self.pot_entry_vol.is_some()
                        && self.pot_cand_vol.is_some()
                        && vol - self.pot_entry_vol.unwrap() > POT_CONFIRM_VOL
                    {
                        let cand = self.pot_cand_vol.unwrap();
                        self.pot_ep_vol = Some(cand);
                        self.pot_state = PotentialState::EndConfirmed;
                        self.pot_done = true;
                    }
                }
                _ => {}
            }
        }
    }

    /// 喂入一帧原始通道或重建全谱。
    pub fn feed_spectrum(&mut self, vol: f64, spectrum: &[f64]) {
        let diag = self.spectral.update(vol, spectrum);
        self.last_spec_diag = diag;
        // Python: max(self._spec_max_js, diag["max_js"])
        self.spec_max_js = self.spec_max_js.max(self.last_spec_diag.max_js);
        let candidate = self.spectral.endpoint_volume();
        // tracker 报告迄今最强激变，更强事件可顶替早瞬态，候选会移动。
        if let Some(c) = candidate {
            if Some(c) != self.spec_ep_vol {
                self.spec_ep_vol = Some(c);
                self.last_spec_result = None; // 结果重建
            }
        }
    }

    // ================================================================
    //  结果与可靠性
    // ================================================================

    fn build_pot_result(&mut self) -> Option<PotentialResult> {
        let vol = self.pot_ep_vol?;
        let mut result = PotentialResult {
            volume: vol,
            time: vol / self.flow_rate,
            min_dvdt: round2(self.pot_min_d),
            state: self.pot_state,
            endpoint_std: None,
            nis: None,
            innovation: None,
        };
        if let Some(kf) = &self.kf {
            let snap = kf.snapshot();
            result.endpoint_std = snap.endpoint_std;
            result.nis = snap.nis;
            result.innovation = snap.innovation;
        }
        self.last_pot_result = Some(result.clone());
        Some(result)
    }

    fn build_spec_result(&mut self) -> Option<SpectralResult> {
        let vol = self.spec_ep_vol?;
        let diag = self.last_spec_diag.clone();
        let result = SpectralResult {
            volume: vol,
            time: vol / self.flow_rate,
            max_ce: round8(self.spec_max_js),
            max_js: round8(self.spec_max_js),
            js_local: round8(diag.js_local),
            js_speed: round8(diag.js_speed),
            js_base: round8(diag.js_base),
            cross_curvature: self.enable_curvature.then(|| round8(diag.cross_curvature)),
            event_maturity: diag.event_maturity,
            recovery_frames: diag.recovery_frames,
            event_count: diag.event_count,
            superseded_count: diag.superseded_count,
            event_peak_speed: round8(diag.event_peak_speed),
            state: diag.state,
        };
        self.last_spec_result = Some(result.clone());
        Some(result)
    }

    fn build_reliability(
        &self,
        pot: Option<&PotentialResult>,
        spec: Option<&SpectralResult>,
    ) -> Reliability {
        let pot_confirmed = pot.is_some();
        let spec_confirmed = spec.is_some();
        let diagnostic = &self.last_spec_diag;
        let kf_snap = self.kf.as_ref().map(|kf| kf.snapshot());

        let status = if pot_confirmed && spec_confirmed {
            match &kf_snap {
                Some(snap) if snap.accepted && self.kf.as_ref().is_some_and(|k| k.can_fuse()) => {
                    "CONFIRMED"
                }
                _ => "CONFLICT",
            }
        } else if pot_confirmed || spec_confirmed {
            if pot_confirmed && !self.enable_kf {
                "CONFIRMED"
            } else {
                "CANDIDATE"
            }
        } else if self.pot_state == PotentialState::Tracking
            || diagnostic.state == TrackerState::InChange
        {
            "CONFIRMING"
        } else if self.pot_sample_count == 0 && diagnostic.sample_count == 0 {
            "UNOBSERVABLE"
        } else {
            "EARLY_WARNING"
        };

        let mut reasons: Vec<String> = Vec::new();
        if diagnostic.data_quality != "ok" && diagnostic.data_quality != "no_spectrum" {
            reasons.push(diagnostic.data_quality.clone());
        }
        if diagnostic.repeated_volume_count > 0 {
            reasons.push("repeated_spectral_volume".into());
        }
        if diagnostic.nonmonotonic_count > 0 {
            reasons.push("nonmonotonic_volume".into());
        }
        if let Some(kf) = &self.kf {
            if pot_confirmed && spec_confirmed && !kf.can_fuse() {
                reasons.push("kf_innovation_gate".into());
            }
        }
        if diagnostic.superseded_count > 0 {
            reasons.push("spectral_endpoint_superseded".into());
        }
        if !diagnostic.baseline_ready {
            reasons.push("baseline_pending".into());
        }

        let agreement = match (pot, spec) {
            (Some(p), Some(s)) => Some((p.volume - s.volume).abs()),
            _ => None,
        };

        Reliability {
            status: status.to_string(),
            data_quality: DataQualityInfo {
                potential_samples: self.pot_sample_count,
                spectral_samples: diagnostic.sample_count,
                valid_spectral_frames: self.spectral.valid_frame_count(),
                baseline_ready: diagnostic.baseline_ready,
                repeated_spectral_volume: diagnostic.repeated_volume_count,
                nonmonotonic_volume: diagnostic.nonmonotonic_count,
                last_frame: if diagnostic.sample_count == 0 && !diagnostic.valid_frame {
                    "no_spectrum".to_string()
                } else {
                    diagnostic.data_quality.clone()
                },
            },
            potential_evidence: pot_confirmed,
            spectral_evidence: spec_confirmed,
            modal_consistency: ModalConsistency {
                agreement_ml: agreement,
                kf_consistent: self.kf.as_ref().map(|k| k.can_fuse()),
            },
            event_maturity: diagnostic.event_maturity,
            spectral_events: diagnostic.event_count,
            spectral_superseded: diagnostic.superseded_count,
            endpoint_std: kf_snap.as_ref().and_then(|s| s.endpoint_std),
            spectral_delay: kf_snap.as_ref().and_then(|s| s.spectral_delay),
            nis: kf_snap.as_ref().and_then(|s| s.nis),
            innovation: kf_snap.as_ref().and_then(|s| s.innovation),
            reason_codes: reasons,
        }
    }

    /// 当前因果特征与可靠性诊断。
    pub fn diagnostics(&mut self) -> DetectorDiagnostics {
        let pot = self.build_pot_result();
        let spec = self.build_spec_result();
        self.last_reliability = self.build_reliability(pot.as_ref(), spec.as_ref());
        DetectorDiagnostics {
            potential_state: self.pot_state,
            spectral_state: self.last_spec_diag.state,
            potential: pot,
            spectral: spec,
            spectral_features: self.last_spec_diag.clone(),
            kf: self.kf.as_ref().map(|kf| kf.snapshot()),
            reliability: self.last_reliability.clone(),
        }
    }

    fn consume_kf_observations(&mut self, pot_vol: Option<f64>, spec_vol: Option<f64>) {
        let Some(kf) = self.kf.as_mut() else {
            return;
        };
        let pair = (pot_vol, spec_vol);
        if self.kf_consumed == Some(pair) {
            return;
        }
        // 观测对变化（光谱顶替 / AMPD 精修）→ 重跑滤波器，
        // 避免用陈旧状态门控修正值。
        kf.reset();
        if let Some(pv) = pot_vol {
            let token = format!("potential@{pv}");
            kf.observe(ObservationKind::Potential, pv, Some(&token));
        }
        if let Some(sv) = spec_vol {
            let token = format!("spectral@{sv}");
            kf.observe(ObservationKind::Spectral, sv, Some(&token));
        }
        self.kf_consumed = Some(pair);
    }

    /// 返回向后兼容的终点结果（含诊断）。
    pub fn detect(&mut self) -> Option<EndpointResult> {
        let mut pot = self.build_pot_result();
        let mut spec = self.build_spec_result();
        if pot.is_none() && spec.is_none() {
            self.last_reliability = self.build_reliability(None, None);
            return None;
        }

        self.consume_kf_observations(
            pot.as_ref().map(|p| p.volume),
            spec.as_ref().map(|s| s.volume),
        );
        // 消费首个观测后重建子结果，使导出的 NIS/std 描述刚消费的观测。
        pot = self.build_pot_result();
        spec = self.build_spec_result();
        let reliability = self.build_reliability(pot.as_ref(), spec.as_ref());
        self.last_reliability = reliability.clone();

        match (pot, spec) {
            (Some(pot), Some(spec)) => {
                let can_fuse = self.kf.as_ref().is_some_and(|k| k.can_fuse());
                if can_fuse {
                    let volume = self.kf.as_ref().unwrap().endpoint_volume();
                    Some(EndpointResult {
                        volume: round3(volume),
                        time: round3(volume / self.flow_rate),
                        confidence: Confidence::High,
                        method: Method::Consensus,
                        potential: Some(pot),
                        spectral: Some(spec),
                        warning: None,
                        reliability,
                    })
                } else if self.kf.is_none() && (pot.volume - spec.volume).abs() < 0.3 {
                    let volume = (pot.volume + spec.volume) / 2.0;
                    Some(EndpointResult {
                        volume: round3(volume),
                        time: round3((pot.time + spec.time) / 2.0),
                        confidence: Confidence::High,
                        method: Method::Consensus,
                        potential: Some(pot),
                        spectral: Some(spec),
                        warning: None,
                        reliability,
                    })
                } else {
                    Some(EndpointResult {
                        volume: round3(pot.volume),
                        time: round3(pot.time),
                        confidence: Confidence::Low,
                        method: Method::Conflict,
                        warning: Some(format!(
                            "电位{:.3}mL vs 光谱{:.3}mL 未通过创新一致性门控",
                            pot.volume, spec.volume
                        )),
                        potential: Some(pot),
                        spectral: Some(spec),
                        reliability,
                    })
                }
            }
            (Some(pot), None) => Some(EndpointResult {
                volume: round3(pot.volume),
                time: round3(pot.time),
                confidence: Confidence::Medium,
                method: Method::PotentialOnly,
                potential: Some(pot),
                spectral: None,
                warning: None,
                reliability,
            }),
            (None, Some(spec)) => Some(EndpointResult {
                volume: round3(spec.volume),
                time: round3(spec.time),
                confidence: Confidence::Medium,
                method: Method::SpectralOnly,
                potential: None,
                spectral: Some(spec),
                warning: None,
                reliability,
            }),
            (None, None) => None,
        }
    }

    /// 历史样本足够后用 AMPD 离线精修电位终点。
    pub fn refine_with_ampd(&mut self) -> Option<f64> {
        if self.pot_raw_buf.len() < 20 {
            return None;
        }
        let negated: Vec<f64> = self.pot_raw_buf.iter().map(|d| -d).collect();
        let idx = ampd_peak_idx(&negated)?;
        if idx as f64 >= self.pot_vol_buf.len() as f64 * AMPD_MAX_POSITION {
            return None;
        }
        let refined = self.pot_vol_buf[idx];
        self.pot_ep_vol = Some(refined);
        Some(refined)
    }

    pub fn potential_state(&self) -> PotentialState {
        self.pot_state
    }

    /// 电位通道终点体积（未确认时 `None`）。
    pub fn potential_endpoint_volume(&self) -> Option<f64> {
        self.pot_ep_vol
    }

    /// 最近一次 `feed_potential` 后的平滑导数（EWMA 后的 dV/dt）。
    pub fn last_potential_derivative(&self) -> f64 {
        self.pot_d_smooth.hold()
    }

    pub fn spectral_state(&self) -> TrackerState {
        self.last_spec_diag.state
    }

    pub fn endpoint_volume(&self) -> Option<f64> {
        if self.kf.as_ref().is_some_and(|k| k.can_fuse()) {
            return Some(self.kf.as_ref().unwrap().endpoint_volume());
        }
        self.pot_ep_vol.or(self.spec_ep_vol)
    }
}

fn round2(x: f64) -> f64 {
    round_to(x, 2)
}
fn round3(x: f64) -> f64 {
    round_to(x, 3)
}
fn round8(x: f64) -> f64 {
    round_to(x, 8)
}

/// Python `round()` 的半偶舍入近似（f64::roundto 不可用时的等价实现）。
fn round_to(x: f64, digits: i32) -> f64 {
    let factor = 10f64.powi(digits);
    (x * factor).round() / factor
}
