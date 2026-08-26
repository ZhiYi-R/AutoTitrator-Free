//! 因果在线滴定终点检测器 — Python `EndpointDetector` 的移植。
//!
//! 电位通道走既有因果 EWMA 状态机；光谱通道委托 [`SpectralFeatureTracker`]
//! （有界 JS 信号、因果交叉曲率、终点/延迟两状态 KF 融合）。任何特征都不
//! 使用未来样本。
//!
//! 任一模态的终点都可能事后修正（光谱端被更强激变顶替、电位端被 AMPD
//! 微调）；所以观测对变化时 KF 从头重跑：用陈旧状态门控修正值只会拒绝修正。

use serde::Serialize;

use super::adaptive::{AdaptiveParams, RobustStats};
use super::ampd::ampd_peak_idx;
use super::ewma::Ewma;
use super::kf::{EndpointFusionKf, ObservationKind};
use super::tracker::{SpectralFeatureTracker, TrackerState};

// ---- 电位通道参数 ----
// 导数语义(2026-08-27 起):按体积差分 dE/dV(mL⁻¹),不再按时间。
// 动因:上位机时间戳含微突发(dt<50ms 占 15%,min=0),按时间差分让孤立
// 样本爆出 -1159 mV/s 的伪影尖峰(EWMA 尾巴拖成假下陷,曾把 Exp1 终点
// 锁在 0.735mL);体积由泵步数量化,天然免疫计时抖动,且与光谱通道的
// "体积归一化速度"锚定语义同构。
pub const POT_V_ALPHA: f64 = 0.15;
pub const POT_D_ALPHA: f64 = 0.05;
/// 观察期体积（mL）：此前只累计基线统计，不驱动状态机。
pub const POT_OBSERVE_VOL: f64 = 0.1;
/// 体积推进判定地板（mL）：Δv 小于此视为重复帧，导数保持上一值。
pub const POT_DV_FLOOR: f64 = 1e-4;
pub const POT_ENTER_SIGMA: f64 = 2.5;
/// 进入偏移下限/上限（V/mL）。floor=旧固定行为的回落点；
/// max 防观察窗被污染把阈值顶到不可触发。
pub const POT_MIN_ENTER: f64 = 0.02;
pub const POT_MAX_ENTER: f64 = 5.0;
/// 退出偏移固定比例（相对进入偏移）。
pub const POT_EXIT_RATIO: f64 = 0.2;
/// 进入→退出之间的最小确认体积（mL）。
pub const POT_CONFIRM_VOL: f64 = 0.15;
/// 后发更深下陷顶替候选所需强度倍数（与光谱 supersede 同构）。
pub const POT_SUPERSEDE_RATIO: f64 = 1.5;

// KF 质量缩放参考比（V/mL 域重标定：Exp1 实测 ρ≈0.013）。
pub const RHO_REF_POT: f64 = 0.02;

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

// ---- KF 质量缩放 ----
// 观测方差乘性因子 = clamp((ρ/ρ_ref)², 1, 4),ρ = 基线噪声/事件信号。
// 单边放大:只在噪声高于参考值时降低该模态置信;收紧方向(比标定更干净)
// 刻意不改 R——干净数据上的 NIS 数值行为必须与论文既有结果一致,
// 且缺干净双模态基线数据校准收紧方向。
pub const RHO_REF_SPD: f64 = 0.02;

/// 检测器配置（`EndpointDetector::with_params` 的参数包）。
#[derive(Debug, Clone)]
pub struct DetectorParams {
    pub use_jsd: bool,
    pub enable_curvature: bool,
    pub enable_kf: bool,
    /// 自适应阈值参数；`legacy_fixed()` 时行为与固定阈值完全一致。
    pub adaptive: AdaptiveParams,
}

impl Default for DetectorParams {
    fn default() -> Self {
        Self {
            use_jsd: true,
            enable_curvature: true,
            enable_kf: true,
            adaptive: AdaptiveParams::default(),
        }
    }
}

impl DetectorParams {
    pub fn legacy_fixed() -> Self {
        Self {
            adaptive: AdaptiveParams::legacy_fixed(),
            ..Self::default()
        }
    }
}

/// AMPD 微调拒绝的尾部位置上限：最大尺度只覆盖窗口中部，尾部峰支持的尺度
/// 很少；0.75 曾在稍晚于化学计量点产生假阳性，故将门限放宽到 0.9。
pub const AMPD_MAX_POSITION: f64 = 0.9;
/// AMPD 微调的搜索半径（mL）：只允许把最强事件的候选体积在邻近范围内
/// 重定位。全局检索在非平稳导数上会失效（Exp1 实测：可靠尺度退化到
/// 最大尺度 σ=L−1，4.20mL 以平凡得分胜出、把正确的 5.37 拖回错误位置）。
pub const AMPD_REFINE_WINDOW: f64 = 0.5;

/// 电位通道一次确认的下陷事件（可重入状态机的产物，与光谱 ExcursionEvent 同构）。
#[derive(Debug, Clone, Copy, Serialize)]
pub struct PotentialEvent {
    pub candidate_volume: f64,
    pub entry_volume: f64,
    /// 该事件的导数极小值（V/mL，负值；越深越强）。
    pub peak_depth: f64,
}

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
    /// 武装的进入/退出阈值（V/s），供审计;含自适应与固定两种来源。
    pub enter_th: f64,
    pub exit_th: f64,
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

/// 自适应阈值快照（审计用；legacy/未武装时字段为 None，序列化时省略）。
#[derive(Debug, Clone, Default, Serialize)]
pub struct AdaptiveInfo {
    #[serde(skip_serializing_if = "Option::is_none")]
    pub spectral_enter: Option<f64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub spectral_exit: Option<f64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub spectral_base: Option<f64>,
    /// 光谱自适应阈值是否成功武装。
    pub spectral_armed: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub potential_enter: Option<f64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub potential_exit: Option<f64>,
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
    pub adaptive: AdaptiveInfo,
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
    pub adaptive: AdaptiveParams,
    spectrum_axis: Option<Vec<f64>>,

    // 电位状态
    pot_v_smooth: Ewma,
    pot_d_smooth: Ewma,
    /// 上帧输入体积与平滑电压(体积差分的两个锚点)。
    pot_prev_vol: Option<f64>,
    pot_prev_vsm: Option<f64>,
    pot_state: PotentialState,
    /// 迄今最强（最深）事件的候选体积； None = 尚无已确认事件。
    pot_ep_vol: Option<f64>,
    // 当前 episode（进入 Tracking 后累积,退出时提交）
    pot_min_d: f64,
    pot_cand_vol: Option<f64>,
    pot_entry_vol: Option<f64>,
    pot_d_vals: Vec<f64>,
    pot_obs_done: bool,
    pot_enter_th: f64,
    pot_exit_th: f64,
    pot_d_buf: Vec<f64>,
    pot_vol_buf: Vec<f64>,
    pot_sample_count: usize,
    last_pot_result: Option<PotentialResult>,
    /// 已确认事件列表与最强者(可重入:最强下陷胜出)。
    pot_events: Vec<PotentialEvent>,
    pot_best_event: Option<PotentialEvent>,
    pot_superseded_count: usize,
    // 电位自适应状态
    pot_obs_stats: RobustStats,
    /// 观察期导数中位水平（V/s）。
    pot_level: Option<f64>,
    /// 观察期导数 MAD σ（V/s）；None = 零散布或样本不足，KF 质量缩放跳过。
    pot_noise_sigma: Option<f64>,

    // 光谱状态（委托 tracker）
    spectral: SpectralFeatureTracker,
    spec_ep_vol: Option<f64>,
    spec_max_js: f64,
    last_spec_diag: super::tracker::Diagnostics,
    last_spec_result: Option<SpectralResult>,

    kf: Option<EndpointFusionKf>,
    kf_consumed: Option<(Option<f64>, Option<f64>)>,
    kf_scaled: bool,
    last_reliability: Reliability,
}

impl EndpointDetector {
    pub fn new(flow_rate: f64) -> Self {
        Self::with_params(flow_rate, DetectorParams::default(), None)
    }

    /// 旧签名入口：固定阈值行为（与历史上完全一致），供绝缘测试对照。
    pub fn with_options(
        flow_rate: f64,
        use_jsd: bool,
        enable_curvature: bool,
        enable_kf: bool,
        wavelengths: Option<&[f64]>,
    ) -> Self {
        Self::with_params(
            flow_rate,
            DetectorParams {
                use_jsd,
                enable_curvature,
                enable_kf,
                ..DetectorParams::legacy_fixed()
            },
            wavelengths,
        )
    }

    pub fn with_params(
        flow_rate: f64,
        params: DetectorParams,
        wavelengths: Option<&[f64]>,
    ) -> Self {
        let DetectorParams {
            use_jsd,
            enable_curvature,
            enable_kf,
            adaptive,
        } = params.clone();
        let mut spectral = SpectralFeatureTracker::with_params(
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
        spectral.set_adaptive(&adaptive);
        let mut det = Self {
            flow_rate,
            use_jsd,
            enable_curvature,
            enable_kf,
            adaptive,
            spectrum_axis: wavelengths.map(|w| w.to_vec()),
            pot_v_smooth: Ewma::new(POT_V_ALPHA),
            pot_d_smooth: Ewma::new(POT_D_ALPHA),
            pot_prev_vol: None,
            pot_prev_vsm: None,
            pot_state: PotentialState::Idle,
            pot_ep_vol: None,
            pot_min_d: 0.0,
            pot_cand_vol: None,
            pot_entry_vol: None,
            pot_d_vals: Vec::new(),
            pot_obs_done: false,
            pot_enter_th: -1e9,
            pot_exit_th: -1e9,
            pot_d_buf: Vec::new(),
            pot_vol_buf: Vec::new(),
            pot_sample_count: 0,
            last_pot_result: None,
            pot_events: Vec::new(),
            pot_best_event: None,
            pot_superseded_count: 0,
            pot_obs_stats: RobustStats::new(256),
            pot_level: None,
            pot_noise_sigma: None,
            spectral,
            spec_ep_vol: None,
            spec_max_js: 0.0,
            last_spec_diag: Default::default(),
            last_spec_result: None,
            kf: enable_kf.then(EndpointFusionKf::new),
            kf_consumed: None,
            kf_scaled: false,
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
                adaptive: AdaptiveInfo::default(),
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
        self.pot_prev_vol = None;
        self.pot_prev_vsm = None;
        self.pot_state = PotentialState::Idle;
        self.pot_ep_vol = None;
        self.pot_min_d = 0.0;
        self.pot_cand_vol = None;
        self.pot_entry_vol = None;
        self.pot_d_vals.clear();
        self.pot_obs_done = false;
        self.pot_enter_th = -1e9;
        self.pot_exit_th = -1e9;
        self.pot_d_buf.clear();
        self.pot_vol_buf.clear();
        self.pot_sample_count = 0;
        self.last_pot_result = None;
        self.pot_events.clear();
        self.pot_best_event = None;
        self.pot_superseded_count = 0;
        self.pot_obs_stats = RobustStats::new(256);
        self.pot_level = None;
        self.pot_noise_sigma = None;

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
        self.kf_scaled = false;
        self.spectral.set_adaptive(&self.adaptive);
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

    /// 输入一个电位点：体积 mL、时间 s、电压 V。
    ///
    /// 导数按体积差分（V/mL）：Δv 低于 [`POT_DV_FLOOR`] 视为重复帧，
    /// 导数保持上一值（与光谱通道的体积锚定语义一致）；
    /// 非单调体积同样保持并计数。时间参数仅用于兼容签名。
    pub fn feed_potential(&mut self, vol: f64, _t: f64, v: f64) {
        let vol = vol;
        let v_sm = self.pot_v_smooth.push(v);

        // 体积域差分:重复/非单调体积 → hold(推入当前电平即无操作)。
        let d_raw = match (self.pot_prev_vol, self.pot_prev_vsm) {
            (Some(pvol), Some(pv_sm)) => {
                let dv = vol - pvol;
                if dv > POT_DV_FLOOR {
                    (v_sm - pv_sm) / dv
                } else {
                    self.pot_d_smooth.hold()
                }
            }
            _ => 0.0,
        };
        let d_sm = self.pot_d_smooth.push(d_raw);
        self.pot_prev_vol = Some(vol);
        self.pot_prev_vsm = Some(v_sm);
        self.pot_sample_count += 1;
        self.pot_d_buf.push(d_sm);
        self.pot_vol_buf.push(vol);

        if !self.pot_obs_done {
            self.pot_d_vals.push(d_sm);
            self.pot_obs_stats.push(d_sm);
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
                // legacy 兜底:均值 ± 相对梯子(MAD 失败时与自适应同构)
                let std_off = (POT_ENTER_SIGMA * std).clamp(POT_MIN_ENTER, POT_MAX_ENTER);
                self.pot_enter_th = mean - std_off;
                self.pot_exit_th = mean - std_off * POT_EXIT_RATIO;

                // 自适应路径:中位水平 + MAD σ → 相对梯子偏移。
                // 零散布(mad_sigma=None)或统计不足时保留上面的 legacy 阈值。
                let sigma_mad = self.pot_obs_stats.mad_sigma();
                self.pot_noise_sigma = sigma_mad;
                let level = self.pot_obs_stats.median();
                self.pot_level = level;
                if let (Some(_sigma), Some(med)) = (sigma_mad, level) {
                    if let Some(offset_enter) = self.adaptive.potential_offset(&self.pot_obs_stats)
                    {
                        let offset_exit = offset_enter * POT_EXIT_RATIO;
                        self.pot_enter_th = med - offset_enter;
                        self.pot_exit_th = med - offset_exit;
                    }
                }
                self.pot_obs_done = true;
                self.pot_d_vals.clear();
            }
            return;
        }

        // 可重入状态机:最强下陷事件胜出,不闩锁。
        match self.pot_state {
            PotentialState::Idle | PotentialState::EndConfirmed => {
                if d_sm < self.pot_enter_th {
                    self.pot_state = PotentialState::Tracking;
                    self.pot_min_d = d_sm;
                    self.pot_cand_vol = Some(vol);
                    self.pot_entry_vol = Some(vol);
                }
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
                    self.commit_potential_event();
                }
            }
        }
    }

    /// 提交当前 episode 并保留最深者(带滞回:近持平不顶替)。
    fn commit_potential_event(&mut self) {
        let event = PotentialEvent {
            candidate_volume: self.pot_cand_vol.unwrap_or_else(|| {
                self.pot_entry_vol.unwrap_or_default()
            }),
            entry_volume: self.pot_entry_vol.unwrap_or_default(),
            peak_depth: self.pot_min_d,
        };
        self.pot_events.push(event);
        match self.pot_best_event {
            None => self.pot_best_event = Some(event),
            // peak_depth 为负,越深越强;后发事件须明显更深才顶替(防抖动)。
            Some(best) if event.peak_depth < best.peak_depth * POT_SUPERSEDE_RATIO => {
                self.pot_best_event = Some(event);
                self.pot_superseded_count += 1;
            }
            _ => {}
        }
        self.pot_ep_vol = self.pot_best_event.map(|e| e.candidate_volume);
        self.pot_state = PotentialState::EndConfirmed;
        self.last_pot_result = None; // 结果重建
    }

    /// 输入一帧原始通道或重建全谱。
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
            enter_th: self.pot_enter_th,
            exit_th: self.pot_exit_th,
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

        let (adaptive_enter, adaptive_exit, adaptive_base) =
            match (self.last_spec_diag.adaptive_enter, self.last_spec_diag.adaptive_exit) {
                (Some(e), Some(x)) => (
                    Some(round8(e)),
                    Some(round8(x)),
                    self.last_spec_diag.adaptive_base.map(round8),
                ),
                _ => (None, None, None),
            };
        let adaptive_info = AdaptiveInfo {
            spectral_enter: adaptive_enter,
            spectral_exit: adaptive_exit,
            spectral_base: adaptive_base,
            spectral_armed: adaptive_enter.is_some(),
            potential_enter: if self.pot_obs_done && self.adaptive.enabled {
                Some(round6(self.pot_enter_th))
            } else {
                None
            },
            potential_exit: if self.pot_obs_done && self.adaptive.enabled {
                Some(round6(self.pot_exit_th))
            } else {
                None
            },
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
            adaptive: adaptive_info,
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

    /// KF 观测方差的一次性质量缩放:ρ = 基线噪声/事件信号,方差 ×(ρ/ρ_ref)²。
    ///
    /// 必须发生在首条观测前(初始化后 KF 拒绝缩放),每 run 至多一次、确定性;
    /// 任一模态统计缺失(零散布/未武装)时该模态因子取 1.0,行为不变。
    fn apply_kf_quality_scaling(&mut self) {
        if self.kf_scaled {
            return;
        }
        self.kf_scaled = true;

        // 电位:信号幅度 = 基线水平与最深下陷之差;噪声 = MAD σ。
        let pot_factor = match (self.pot_noise_sigma, self.pot_level) {
            (Some(sigma), Some(level)) => {
                let signal = (level - self.pot_min_d).abs().max(1e-9);
                let rho = sigma / signal;
                (rho / RHO_REF_POT).powi(2)
            }
            _ => 1.0,
        };

        // 光谱:信号 = 最强事件的峰值速度;噪声 = 基线期速度 MAD σ。
        let spec_factor =
            match (self.speed_stats_snapshot(), self.last_spec_diag.event_peak_speed) {
                (Some(sigma), peak) if peak > 0.0 => {
                    let rho = sigma / peak;
                    (rho / RHO_REF_SPD).powi(2)
                }
                _ => 1.0,
            };

        if pot_factor == 1.0 && spec_factor == 1.0 {
            return;
        }
        if let Some(kf) = self.kf.as_mut() {
            if !kf.is_initialized() && kf.can_scale() {
                kf.scale_observation_variances(pot_factor, spec_factor);
            }
        }
    }

    fn speed_stats_snapshot(&self) -> Option<f64> {
        self.spectral.baseline_speed_sigma()
    }

    fn consume_kf_observations(&mut self, pot_vol: Option<f64>, spec_vol: Option<f64>) {
        let Some(_) = self.kf.as_ref() else {
            return;
        };
        let pair = (pot_vol, spec_vol);
        if self.kf_consumed == Some(pair) {
            return;
        }
        self.apply_kf_quality_scaling();
        // 观测对变化（光谱顶替 / AMPD 微调）→ 重跑滤波器，
        // 避免用陈旧状态门控修正值。
        let Some(kf) = self.kf.as_mut() else {
            return;
        };
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
                            "电位{:.3}mL vs 光谱{:.3}mL 未通过新息一致性门控",
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

    /// 历史样本足够后用 AMPD 离线微调电位终点。
    ///
    /// 输入是**平滑后**的导数缓冲（此前喂未平滑 d_raw,时间戳毛刺的孤立
    /// 尖峰曾把精修引到错误位置）;搜索限制在最强事件候选 ±[`AMPD_REFINE_WINDOW`]
    /// mL 内——精修是"微调",不是全局重定位。无已确认事件或窗口内无峰时
    /// 返回 None 并保持原候选;成功则同步更新最强事件,保证 KF 重跑一致。
    pub fn refine_with_ampd(&mut self) -> Option<f64> {
        if self.pot_d_buf.len() < 20 {
            return None;
        }
        let center = self.pot_best_event?.candidate_volume;
        // 取窗口内的连续切片(体积基本单调;非单调段极少,近似即可)
        let lo = self
            .pot_vol_buf
            .iter()
            .position(|&v| (v - center).abs() <= AMPD_REFINE_WINDOW)?;
        let hi = self
            .pot_vol_buf
            .iter()
            .rposition(|&v| (v - center).abs() <= AMPD_REFINE_WINDOW)?;
        if hi < lo {
            return None;
        }
        let slice = &self.pot_d_buf[lo..=hi];
        let negated: Vec<f64> = slice.iter().map(|d| -d).collect();
        let local_idx = ampd_peak_idx(&negated)?;
        let idx = lo + local_idx;
        if idx as f64 >= self.pot_vol_buf.len() as f64 * AMPD_MAX_POSITION {
            return None;
        }
        let refined = self.pot_vol_buf[idx];
        self.pot_ep_vol = Some(refined);
        if let Some(best) = self.pot_best_event.as_mut() {
            best.candidate_volume = refined;
        }
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
fn round6(x: f64) -> f64 {
    round_to(x, 6)
}
fn round8(x: f64) -> f64 {
    round_to(x, 8)
}

/// Python `round()` 的半偶舍入近似（f64::roundto 不可用时的等价实现）。
fn round_to(x: f64, digits: i32) -> f64 {
    let factor = 10f64.powi(digits);
    (x * factor).round() / factor
}
