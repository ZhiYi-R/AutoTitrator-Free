//! 因果光谱特征追踪器 — Python `SpectralFeatureTracker` 的移植。
//!
//! 两个必须知道的行为（源自 Python 文档）：
//!
//! * 体积归一化速度锚定到最后一个*前进*帧。生产中固件每 AS7341
//!   帧上报一帧光谱而体积来自泵，多帧共享同一体积；把零步长喂进速度滤波会
//!   注入 0 并掩盖真实事件，所以体积静止时速度滤波器*保持*电平。
//! * `END_CONFIRMED` 可重入。激变记录进 `events`，报告的终点是最强事件，
//!   只有后续事件强 `supersede_ratio` 倍才顶替。一次性闩锁曾在真实数据
//!   （Paper/ExpData B 组）上把早于真终点 0.97 mL 的瞬态锁成终点，
//!   Kalman 门只能拒绝、无法修复。

use std::collections::VecDeque;

use serde::Serialize;

use super::adaptive::{AdaptiveParams, RobustStats, SPD_MIN_SAMPLES};
use super::divergence::{cross_entropy_excess, finite_vector, js_divergence, EPS, JS_FLOOR};
use super::ewma::Ewma;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize)]
#[serde(rename_all = "SCREAMING_SNAKE_CASE")]
pub enum TrackerState {
    Idle,
    InChange,
    EndConfirmed,
}

/// 基准建立后武装的自适应阈值(legacy/估计失败时为 None,落固定常数)。
///
/// exit 由 enter 按现有比值 0.16 派生;为保证平坦数据下的行为逐位不变,
/// 统计不可用时直接沿用构造参数里的固定值而不是用下限重算。
#[derive(Debug, Clone, Copy, Serialize)]
pub struct ArmedThresholds {
    pub enter: f64,
    pub exit: f64,
    pub base: f64,
}

// ---- 永久变色判别(2026-08-27,源于人工确认的化学模式) ----
//
// 光谱事件的化学语义分两类(变色→褪色模式,用户确认):
//  * 瞬态激变: 谱形升起后回落到事件前水平(base_js 自参照恢复);
//  * 终点永久变色: 谱形升起、回落但停稳在显著高于事件前的水平——
//    指示剂已切换形态,不会回去。
// Exp1 实测:0.13mL 强瞬态恢复比 1.0×;5.37mL 真终点残差比 ~3200×。
// 判据用相对量(对事件前水平的比)抵消累积稀释漂移。

/// 恢复后 base_js 相对事件前水平的最小放大倍数才算"永久"。
pub const RECOVERY_GAP_RATIO: f64 = 3.0;
/// 平台确认路径:episode 内 base_js 的前/后半窗中位数相对差低于此值视为稳定。
pub const PLATEAU_REL_TOL: f64 = 0.35;
/// 平台确认所需的最少 episode 内样本(前后各一半比较)。
pub const PLATEAU_FRAMES: usize = 16;
/// quiet 段 base_js 记录上限(事件前水平的中位数来源)。
const BASE_RING_CAP: usize = 32;

/// 自适应模式下允许延长基准收集的体积上限(mL):
/// 泵速低、帧稀时 0.30 mL 内可能凑不够速度统计样本。
pub const BASELINE_EXTENDED_MAX_VOL: f64 = 0.45;
/// 兜底:越过延长上限仍无足够帧时,至少 3 帧也强行建基准(全走绝对下限)。
pub const BASELINE_MIN_FRAMES_FALLBACK: usize = 3;

impl TrackerState {
    pub fn as_str(self) -> &'static str {
        match self {
            TrackerState::Idle => "IDLE",
            TrackerState::InChange => "IN_CHANGE",
            TrackerState::EndConfirmed => "END_CONFIRMED",
        }
    }
}

/// 一次完成的激变事件（Python `events` 列表元素）。
#[derive(Debug, Clone, Copy, Serialize)]
pub struct ExcursionEvent {
    pub candidate_volume: f64,
    pub entry_volume: f64,
    pub peak_speed: f64,
    pub peak_js: f64,
    /// 提交时的事件前 base_js 中位水平(nats),追溯复评用。
    #[serde(skip_serializing_if = "Option::is_none")]
    pub pre_level: Option<f64>,
    /// 恢复尾 base_js 中位数 − 事件前水平中位数(nats)。≥0 表示残差台阶。
    #[serde(skip_serializing_if = "Option::is_none")]
    pub residual_gap: Option<f64>,
    /// 化学判别:恢复后未回到事件前水平(永久变色)。
    /// None = legacy_fixed 模式不计算。
    #[serde(skip_serializing_if = "Option::is_none")]
    pub permanent: Option<bool>,
}

/// 每帧诊断（Python `_last` 字典字段一一对应，JSON 字段名保持 snake_case）。
#[derive(Debug, Clone, Serialize)]
pub struct Diagnostics {
    pub sample_count: usize,
    pub valid_frame: bool,
    pub data_quality: String,
    pub volume: Option<f64>,
    pub delta_volume: f64,
    pub volume_sync_valid: bool,
    pub js_local: f64,
    pub js_local_smooth: f64,
    pub js_speed: f64,
    pub js_speed_smooth: f64,
    pub js_base: f64,
    /// 武装后的自适应阈值;legacy 或统计不可用时为 None(导出时省略键)。
    #[serde(skip_serializing_if = "Option::is_none")]
    pub adaptive_enter: Option<f64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub adaptive_exit: Option<f64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub adaptive_base: Option<f64>,
    pub cross_curvature: f64,
    pub curvature_peak_channel: Option<usize>,
    pub state: TrackerState,
    pub candidate_volume: Option<f64>,
    pub max_js: f64,
    pub event_maturity: f64,
    pub recovery_frames: usize,
    pub baseline_ready: bool,
    pub repeated_volume_count: usize,
    pub nonmonotonic_count: usize,
    pub event_count: usize,
    pub superseded_count: usize,
    pub event_peak_speed: f64,
}

impl Default for Diagnostics {
    fn default() -> Self {
        Self {
            sample_count: 0,
            valid_frame: false,
            data_quality: "no_spectrum".into(),
            volume: None,
            delta_volume: 0.0,
            volume_sync_valid: false,
            js_local: 0.0,
            js_local_smooth: 0.0,
            js_speed: 0.0,
            js_speed_smooth: 0.0,
            js_base: 0.0,
            adaptive_enter: None,
            adaptive_exit: None,
            adaptive_base: None,
            cross_curvature: 0.0,
            curvature_peak_channel: None,
            state: TrackerState::Idle,
            candidate_volume: None,
            max_js: 0.0,
            event_maturity: 0.0,
            recovery_frames: 0,
            baseline_ready: false,
            repeated_volume_count: 0,
            nonmonotonic_count: 0,
            event_count: 0,
            superseded_count: 0,
            event_peak_speed: 0.0,
        }
    }
}

/// 追踪器配置与状态。
#[derive(Debug, Clone)]
pub struct SpectralFeatureTracker {
    // 配置
    pub alpha: f64,
    pub js_enter: f64,
    pub js_exit: f64,
    pub baseline_enter: f64,
    pub baseline_frames: usize,
    pub baseline_max_volume: f64,
    pub confirm_frames: usize,
    pub min_event_volume: f64,
    pub epsilon_volume: f64,
    pub lookback_frames: usize,
    pub supersede_ratio: f64,
    pub js_floor: f64,
    pub use_jsd: bool,

    // 波长轴（严格递增；None → 用通道下标）
    configured_axis: Option<Vec<f64>>,

    // 状态
    smoothed: Option<Vec<f64>>,
    previous_volume: Option<f64>,
    sync_spectrum: Option<Vec<f64>>,
    sync_volume: Option<f64>,
    baseline_sum: Option<Vec<f64>>,
    baseline_count: usize,
    baseline: Option<Vec<f64>>,
    frame_count: usize,
    valid_frame_count: usize,
    invalid_frame_count: usize,
    nonmonotonic_count: usize,
    repeated_volume_count: usize,
    state: TrackerState,
    candidate_volume: Option<f64>,
    entry_volume: Option<f64>,
    peak_value: f64,
    peak_js: f64,
    recovery_frames: usize,
    recent: VecDeque<(f64, f64)>,
    events: Vec<ExcursionEvent>,
    best_event: Option<ExcursionEvent>,
    supersede_count: usize,
    last: Diagnostics,
    js_smooth: Ewma,
    speed_smooth: Ewma,
    curvature_smooth: Ewma,

    // 自适应阈值状态
    /// 参数集(K 系数/下限/上限);enabled=false 时完全复现固定行为。
    pub adaptive_params: AdaptiveParams,
    speed_stats: RobustStats,
    residual_stats: RobustStats,
    baseline_frames_data: Vec<Vec<f64>>,
    armed: Option<ArmedThresholds>,

    // 永久变色判别状态
    /// 非 InChange 帧的 base_js 环形记录(事件前水平来源)。
    quiet_base: VecDeque<f64>,
    /// InChange 期 base_js 记录(平台确认与恢复尾水平)。
    episode_base: VecDeque<f64>,
    /// 进入 episode 时快照的事件前 base_js 中位水平。
    entry_base_level: Option<f64>,
}

impl Default for SpectralFeatureTracker {
    fn default() -> Self {
        Self::new()
    }
}

impl SpectralFeatureTracker {
    pub fn new() -> Self {
        // 生产默认:与 endpoint.rs 共享同一组常数(此前此处是独立字面量,
        // confirm_frames 曾与生产路径不一致),自适应开启。
        Self::with_params(
            super::endpoint::SPEC_CE_ALPHA,
            super::endpoint::SPEC_JS_ENTER,
            super::endpoint::SPEC_JS_EXIT,
            super::endpoint::SPEC_BASELINE_ENTER,
            super::endpoint::SPEC_BASELINE_FRAMES,
            super::endpoint::SPEC_BASELINE_MAX_VOL,
            super::endpoint::SPEC_CONFIRM_FRAMES,
            super::endpoint::SPEC_MIN_EVENT_VOL,
            1e-8, // epsilon_volume
            8,    // lookback_frames
            super::endpoint::SPEC_SUPERSEDE_RATIO,
            JS_FLOOR, true, // use_jsd
        )
    }

    #[allow(clippy::too_many_arguments)]
    pub fn with_params(
        alpha: f64,
        js_enter: f64,
        js_exit: f64,
        baseline_enter: f64,
        baseline_frames: usize,
        baseline_max_volume: f64,
        confirm_frames: usize,
        min_event_volume: f64,
        epsilon_volume: f64,
        lookback_frames: usize,
        supersede_ratio: f64,
        js_floor: f64,
        use_jsd: bool,
    ) -> Self {
        let mut t = Self {
            alpha,
            js_enter,
            js_exit,
            baseline_enter,
            baseline_frames: baseline_frames.max(3),
            baseline_max_volume,
            confirm_frames: confirm_frames.max(1),
            min_event_volume,
            epsilon_volume: epsilon_volume.max(1e-12),
            lookback_frames: lookback_frames.max(1),
            supersede_ratio: supersede_ratio.max(1.0),
            js_floor: js_floor.max(0.0),
            use_jsd,
            configured_axis: None,
            smoothed: None,
            previous_volume: None,
            sync_spectrum: None,
            sync_volume: None,
            baseline_sum: None,
            baseline_count: 0,
            baseline: None,
            frame_count: 0,
            valid_frame_count: 0,
            invalid_frame_count: 0,
            nonmonotonic_count: 0,
            repeated_volume_count: 0,
            state: TrackerState::Idle,
            candidate_volume: None,
            entry_volume: None,
            peak_value: 0.0,
            peak_js: 0.0,
            recovery_frames: 0,
            recent: VecDeque::new(),
            events: Vec::new(),
            best_event: None,
            supersede_count: 0,
            last: Diagnostics::default(),
            js_smooth: Ewma::new(alpha),
            speed_smooth: Ewma::new(alpha),
            curvature_smooth: Ewma::new(alpha),
            adaptive_params: AdaptiveParams::legacy_fixed(),
            speed_stats: RobustStats::new(64),
            residual_stats: RobustStats::new(64),
            baseline_frames_data: Vec::new(),
            armed: None,
            quiet_base: VecDeque::new(),
            episode_base: VecDeque::new(),
            entry_base_level: None,
        };
        t.reset_state();
        t
    }

    /// 设置自适应参数。必须在基准建立前调用(开始新滴定时);
    /// 关闭时一切行为回到固定常数路径。
    pub fn set_adaptive(&mut self, params: &AdaptiveParams) {
        self.adaptive_params = params.clone();
        if !params.enabled {
            self.armed = None;
        }
    }

    fn reset_state(&mut self) {
        self.smoothed = None;
        self.previous_volume = None;
        self.sync_spectrum = None;
        self.sync_volume = None;
        self.baseline_sum = None;
        self.baseline_count = 0;
        self.baseline = None;
        self.frame_count = 0;
        self.valid_frame_count = 0;
        self.invalid_frame_count = 0;
        self.nonmonotonic_count = 0;
        self.repeated_volume_count = 0;
        self.state = TrackerState::Idle;
        self.candidate_volume = None;
        self.entry_volume = None;
        self.peak_value = 0.0;
        self.peak_js = 0.0;
        self.recovery_frames = 0;
        self.recent.clear();
        self.events.clear();
        self.best_event = None;
        self.supersede_count = 0;
        self.last = Diagnostics::default();
        self.js_smooth.reset();
        self.speed_smooth.reset();
        self.curvature_smooth.reset();
        self.speed_stats = RobustStats::new(64);
        self.residual_stats = RobustStats::new(64);
        self.baseline_frames_data.clear();
        self.armed = None;
        self.quiet_base.clear();
        self.episode_base.clear();
        self.entry_base_level = None;
    }

    /// 清空历史但保留配置与波长轴。
    pub fn reset(&mut self) {
        self.reset_state();
    }

    /// 设置波长轴（交叉曲率用）；必须 ≥2 个有限值且严格递增。
    pub fn set_wavelengths(&mut self, wavelengths: Option<&[f64]>) -> Result<(), String> {
        let Some(axis) = wavelengths else {
            self.configured_axis = None;
            return Ok(());
        };
        if axis.len() < 2 || !axis.iter().all(|v| v.is_finite()) {
            return Err("wavelength axis must contain at least two finite values".into());
        }
        if axis.windows(2).any(|w| w[1] <= w[0]) {
            return Err("wavelength axis must be strictly increasing".into());
        }
        self.configured_axis = Some(axis.to_vec());
        Ok(())
    }

    pub fn last(&self) -> &Diagnostics {
        &self.last
    }

    pub fn valid_frame_count(&self) -> usize {
        self.valid_frame_count
    }

    pub fn events(&self) -> &[ExcursionEvent] {
        &self.events
    }

    /// 迄今最强已确认事件的候选体积。
    pub fn endpoint_volume(&self) -> Option<f64> {
        self.best_event.map(|e| e.candidate_volume)
    }

    /// 自适应模式是否开启。
    pub fn adaptive_enabled(&self) -> bool {
        self.adaptive_params.enabled
    }

    /// 基线期速度噪声 MAD σ(nats/mL²);未开启自适应/统计不足/零散布为 None。
    /// KF 质量缩放用。
    pub fn baseline_speed_sigma(&self) -> Option<f64> {
        if !self.adaptive_params.enabled {
            return None;
        }
        self.speed_stats.mad_sigma()
    }    /// 基准收集体积上限:自适应允许延长窗口凑速度统计。
    fn collection_cap(&self) -> f64 {
        if self.adaptive_params.enabled {
            self.baseline_max_volume.max(BASELINE_EXTENDED_MAX_VOL)
        } else {
            self.baseline_max_volume
        }
    }

    /// 求平均、归一化、建基准,并尝试武装自适应阈值。
    ///
    /// 武装失败(统计不足/退化零散布)时 `armed` 保持 None,
    /// 状态机直接沿用构造参数中的固定常数——保证平坦数据行为逐位不变。
    fn establish_baseline(&mut self) {
        let count = self.baseline_count.max(1) as f64;
        let mut base: Vec<f64> = self
            .baseline_sum
            .take()
            .unwrap_or_default()
            .into_iter()
            .map(|v| v / count)
            .collect();
        let total: f64 = super::divergence::np_sum(&base).max(EPS);
        for v in base.iter_mut() {
            *v /= total;
        }
        self.baseline = Some(base.clone());
        self.armed = None;
        if !self.adaptive_params.enabled {
            return;
        }
        for frame in &self.baseline_frames_data {
            self.residual_stats.push(js_divergence(frame, &base));
        }
        if let Some(enter) = self.adaptive_params.spectral_enter(&self.speed_stats) {
            self.armed = Some(ArmedThresholds {
                enter,
                exit: self.adaptive_params.spectral_exit(enter),
                base: self
                    .adaptive_params
                    .spectral_base(&self.residual_stats)
                    .unwrap_or(self.baseline_enter),
            });
        }
    }

    fn enter_th(&self) -> f64 {
        self.armed.map_or(self.js_enter, |a| a.enter)
    }

    /// 平台确认判据:episode 内 base_js 前后半窗中位数收敛(相对差
    /// ≤[`PLATEAU_REL_TOL`])且后半窗显著高于事件前水平——谱形已阶跃持稳。
    fn base_plateau_reached(&self) -> bool {
        if !self.adaptive_params.permanent_color || self.episode_base.len() < PLATEAU_FRAMES {
            return false;
        }
        let half = self.episode_base.len() / 2;
        let (Some(first), Some(second)) = (
            median_of(self.episode_base.iter().take(half).copied()),
            median_of(self.episode_base.iter().skip(half).copied()),
        ) else {
            return false;
        };
        let converged =
            (first - second).abs() <= PLATEAU_REL_TOL * first.max(second).max(1e-30);
        let entry_level = self.entry_base_level.unwrap_or(0.0);
        let elevated = second >= entry_level * RECOVERY_GAP_RATIO + self.base_th();
        converged && elevated
    }

    fn exit_th(&self) -> f64 {
        self.armed.map_or(self.js_exit, |a| a.exit)
    }

    fn base_th(&self) -> f64 {
        self.armed.map_or(self.baseline_enter, |a| a.base)
    }

    fn axis_for(&self, size: usize) -> Vec<f64> {
        match &self.configured_axis {
            Some(axis) if axis.len() == size => axis.clone(),
            _ => (0..size).map(|i| i as f64).collect(),
        }
    }

    fn divergence(&self, p: &[f64], q: &[f64]) -> f64 {
        if self.use_jsd {
            js_divergence(p, q)
        } else {
            cross_entropy_excess(p, q)
        }
    }

    /// 最近因果窗口内的最强 (速度, 体积)。
    ///
    /// 速度滤波滞后于底层激变，首个越过 `js_enter` 的帧可能已在短瞬态的
    /// 下降沿上；用保留窗口播种峰值，让候选定位到窗口内速度最强的帧。
    fn lookback_peak(&self, volume: f64, speed: f64) -> (f64, f64) {
        let mut peak_speed = speed;
        let mut peak_volume = volume;
        for &(past_volume, past_speed) in &self.recent {
            if past_speed > peak_speed {
                peak_speed = past_speed;
                peak_volume = past_volume;
            }
        }
        (peak_speed, peak_volume)
    }

    /// 记录完成的激变并保留最强者。
    ///
    /// 选择规则分层(2026-08-27 起):
    ///  1. **永久事件压过瞬态事件**——不论峰值强度(化学语义:终点=永久变色);
    ///  2. 同层内维持原有滞回:后发事件须强 supersede_ratio 倍才顶替。
    ///
    /// permanent 是提交瞬间的乐观初判:瞬态刚提交时恢复尾可能尚未回落而
    /// 被误判 true(Exp1 实测,0.211 瞬态提交时 post 还带着抬升尾巴)。
    /// 由 [`Self::reevaluate_permanence`] 在后续安静帧用当前水平追溯降级。
    /// legacy_fixed 模式不算 residual(permanent=None),全部落同层,
    /// 行为与旧版逐位一致。
    fn commit_event(&mut self) {
        let Some(candidate) = self.candidate_volume else {
            return;
        };
        // 恢复尾水平 = episode 内最后 confirm_frames+2 个 base_js 的中位数
        // (退出行程的帧也在 episode_base 里,恰好是恢复段)。
        let entry_level = self.entry_base_level.unwrap_or(0.0);
        let tail = self.episode_base.len().saturating_sub(
            self.confirm_frames.saturating_add(2).min(self.episode_base.len()),
        );
        let post_level = median_of(self.episode_base.iter().skip(tail).copied());
        let compute_gap = self.adaptive_params.permanent_color && post_level.is_some();
        let (residual_gap, permanent) = if compute_gap {
            let gap = post_level.unwrap() - entry_level;
            let perm = self.permanence_from(post_level.unwrap(), entry_level);
            (Some(gap), Some(perm))
        } else {
            (None, None)
        };

        let event = ExcursionEvent {
            candidate_volume: candidate,
            entry_volume: self.entry_volume.unwrap_or(candidate),
            peak_speed: self.peak_value,
            peak_js: self.peak_js,
            pre_level: compute_gap.then_some(entry_level),
            residual_gap,
            permanent,
        };
        self.events.push(event);
        let best = self.best_event;
        // 展平双层 Option:legacy 模式 permanent=None 视作瞬态层。
        let ev_perm = event.permanent.unwrap_or(false);
        let best_perm = best.and_then(|b| b.permanent).unwrap_or(false);
        let replace = match (ev_perm, best_perm) {
            // 永久事件无条件压过瞬态;反之瞬态不得顶替永久。
            (true, false) => true,
            (false, true) => false,
            _ => match best {
                None => true,
                Some(best) => event.peak_speed > best.peak_speed * self.supersede_ratio,
            },
        };
        if replace {
            if best.is_some() {
                self.supersede_count += 1;
            }
            self.best_event = Some(event);
        }
        // episode 状态清理交给调用方(state → EndConfirmed)
    }

    /// 永久性判据(单一出处):恢复后 base_js 水平相对事件前水平的放大倍数
    /// ≥[`RECOVERY_GAP_RATIO`],且绝对缺口越过基准门限。
    fn permanence_from(&self, post_level: f64, entry_level: f64) -> bool {
        post_level >= entry_level * RECOVERY_GAP_RATIO + self.base_th()
    }

    /// 在已注册事件中重选 winner(追溯降级后调用)。
    /// 规则与提交时一致:永久层优先,层内峰值最强者;无事件则清空。
    fn reelect_best_event(&mut self) {
        let pick = |events: &[ExcursionEvent]| -> Option<ExcursionEvent> {
            let mut best: Option<ExcursionEvent> = None;
            for e in events {
                let take = match best {
                    None => true,
                    Some(b) => match (e.permanent.unwrap_or(false), b.permanent.unwrap_or(false)) {
                        (true, false) => true,
                        (false, true) => false,
                        _ => e.peak_speed > b.peak_speed,
                    },
                };
                if take {
                    best = Some(*e);
                }
            }
            best
        };
        self.best_event = pick(&self.events);
    }

    /// 追溯复评:用**当前**安静段 base_js 中位水平,按事件提交时的
    /// entry 水平重估 permanent。
    ///
    /// 语义:瞬态提交瞬间恢复尾可能仍在高位(尾巴未落)而被误判 true;
    /// 若它真会褪色,若干安静帧后 quiet_base 中位数回落到事件前水平附近,
    /// 此时 `permanence_from(current_level, event.pre_level)` 变 false →
    /// 降级。真终点不回落,current 维持在高位,复评保持 true 不变。
    /// 只降级不升级(升级由新事件的提交路径完成)。
    fn reevaluate_permanence(&mut self) {
        if !self.adaptive_params.permanent_color || self.quiet_base.is_empty() {
            return;
        }
        let Some(current) = median_of(self.quiet_base.iter().copied()) else {
            return;
        };
        let base_th = self.base_th();
        let demote =
            |e: &mut ExcursionEvent| match (e.permanent, e.pre_level) {
                (Some(true), Some(pre)) => {
                    // permanence_from 的内联版(closure 里不能借 self)。
                    if !(current >= pre * RECOVERY_GAP_RATIO + base_th) {
                        e.permanent = Some(false);
                        e.residual_gap = Some(current - pre);
                    }
                }
                _ => {}
            };
        for e in self.events.iter_mut() {
            demote(e);
        }
        if let Some(best) = self.best_event.as_mut() {
            demote(best);
        }
    }

    /// 消费一帧光谱，返回因果诊断。
    pub fn update(&mut self, volume: f64, spectrum: &[f64]) -> Diagnostics {
        self.frame_count += 1;
        let volume = volume;

        let normalized = match finite_vector(spectrum) {
            Ok(n) => n,
            Err(reason) => {
                self.invalid_frame_count += 1;
                let mut diag = self.last.clone();
                diag.sample_count = self.frame_count;
                diag.valid_frame = false;
                diag.data_quality = reason.to_string();
                diag.volume = Some(volume);
                diag.baseline_ready = self.baseline.is_some();
                diag.repeated_volume_count = self.repeated_volume_count;
                diag.nonmonotonic_count = self.nonmonotonic_count;
                self.last = diag.clone();
                return diag;
            }
        };
        self.valid_frame_count += 1;

        let mut smoothed = match &self.smoothed {
            None => normalized,
            Some(prev) => normalized
                .iter()
                .zip(prev)
                .map(|(&n, &p)| self.alpha * n + (1.0 - self.alpha) * p)
                .collect(),
        };
        let denom = super::divergence::np_sum(&smoothed).max(EPS); // Python: smoothed / max(np.sum(smoothed), _EPS)
        for v in smoothed.iter_mut() {
            *v /= denom;
        }

        // 体积步长分类
        let (delta_volume, sync_valid) = match self.previous_volume {
            None => (0.0, false),
            Some(prev) => {
                let dv = volume - prev;
                if dv > self.epsilon_volume {
                    (dv, true)
                } else if dv.abs() <= self.epsilon_volume {
                    self.repeated_volume_count += 1;
                    (dv, false)
                } else {
                    self.nonmonotonic_count += 1;
                    (dv, false)
                }
            }
        };

        // 帧间 JS 仅作诊断：帧重复体积时未归一化，不能驱动事件。
        let local = match &self.smoothed {
            Some(prev) => self.divergence(&smoothed, prev),
            None => 0.0,
        };
        let local_smooth = self.js_smooth.push(local);

        // ---- 体积归一化速度（锚定最后前进帧）----
        let mut speed_raw = 0.0f64;
        let mut curvature = 0.0f64;
        let mut peak_channel: Option<usize> = None;
        let anchor_delta = self.sync_volume.map_or(0.0, |sv| volume - sv);
        let mut advance_sync = false;

        if let Some(sync) = self.sync_spectrum.as_ref() {
            if anchor_delta > self.epsilon_volume {
                let anchor_js = self.divergence(&smoothed, sync);
                if anchor_js > self.js_floor {
                    speed_raw = anchor_js / (anchor_delta * anchor_delta);
                }
                let shape_gradient: Vec<f64> = smoothed
                    .iter()
                    .zip(sync.iter())
                    .map(|(&s, &y)| (s.max(1e-12).ln() - y.max(1e-12).ln()) / anchor_delta)
                    .collect();
                let axis = self.axis_for(smoothed.len());
                if axis.len() == shape_gradient.len() && shape_gradient.len() >= 3 {
                    let grad = gradient_nonuniform(&shape_gradient, &axis);
                    curvature = (super::divergence::np_sum(
                        &grad.iter().map(|g| g * g).collect::<Vec<_>>(),
                    ) / grad.len() as f64)
                        .sqrt();
                    peak_channel = grad
                        .iter()
                        .enumerate()
                        .max_by(|a, b| a.1.abs().partial_cmp(&b.1.abs()).unwrap())
                        .map(|(i, _)| i);
                }
                self.speed_smooth.push(speed_raw);
                self.curvature_smooth.push(curvature);
                // 基准期速度样本:自适应阈值的原材料(仅推进帧,与速度滤波同步)。
                if self.baseline.is_none() {
                    self.speed_stats.push(speed_raw);
                }
                advance_sync = true;
            }
        } else {
            // 首帧：建立体积锚
            advance_sync = true;
        }
        if advance_sync {
            self.sync_spectrum = Some(smoothed.clone());
            self.sync_volume = Some(volume);
        }
        let speed_smooth = self.speed_smooth.hold();
        let curvature_smooth = self.curvature_smooth.hold();

        // ---- 基线 ----
        // 自适应模式额外保留逐帧谱,供基准建立时算残差统计;
        // 收集体积上限在自适应下延长(BASELINE_EXTENDED_MAX_VOL),
        // 凑不够统计样本的兜底见 establish_baseline 的 fallback 路径。
        if self.baseline.is_none() && volume <= self.collection_cap() {
            self.baseline_frames_data.push(smoothed.clone());
            if self.baseline_sum.is_none() {
                self.baseline_sum = Some(vec![0.0; smoothed.len()]);
            }
            if let Some(bs) = self.baseline_sum.as_mut() {
                for (acc, v) in bs.iter_mut().zip(&smoothed) {
                    *acc += v;
                }
            }
            self.baseline_count += 1;
            let stats_ready = !self.adaptive_params.enabled
                || self.speed_stats.ready(SPD_MIN_SAMPLES)
                || (volume > self.collection_cap()
                    && self.baseline_count >= BASELINE_MIN_FRAMES_FALLBACK);
            if self.baseline_count >= self.baseline_frames && stats_ready {
                self.establish_baseline();
            }
        }

        let base_js = match &self.baseline {
            None => 0.0,
            Some(base) => js_divergence(&smoothed, base),
        };

        // ---- 状态机(END_CONFIRMED 可重入;含永久变色判别)----
        if self.baseline.is_some() {
            let enter_th = self.enter_th();
            let exit_th = self.exit_th();
            let base_th = self.base_th();
            match self.state {
                TrackerState::Idle | TrackerState::EndConfirmed => {
                    if speed_smooth >= enter_th && base_js >= base_th {
                        let (peak_speed, peak_volume) = self.lookback_peak(volume, speed_smooth);
                        // 事件前水平快照必须在此帧入列前取(当前帧可能已抬升)。
                        self.entry_base_level =
                            Some(median_of(self.quiet_base.iter().copied()).unwrap_or(0.0));
                        self.state = TrackerState::InChange;
                        self.episode_base.clear();
                        self.episode_base.push_back(base_js);
                        self.entry_volume = Some(volume);
                        self.candidate_volume = Some(peak_volume);
                        self.peak_value = peak_speed;
                        self.peak_js = local;
                        self.recovery_frames = 0;
                    } else {
                        // 安静帧:入列事件前水平 ring,并追溯复评已提交事件的
                        // permanent(瞬态提交瞬间尾巴未落的误判在此降级)。
                        self.quiet_base.push_back(base_js);
                        while self.quiet_base.len() > BASE_RING_CAP {
                            self.quiet_base.pop_front();
                        }
                        if base_js <= base_th {
                            let was = self.best_event.and_then(|b| b.permanent);
                            self.reevaluate_permanence();
                            if self.best_event.and_then(|b| b.permanent) != was
                                && was == Some(true)
                            {
                                // 最强事件被降级 → 在全部事件中重选 winner
                                // (永久层优先,层内最强峰值)。重置计数避免
                                // 每帧递增。
                                self.reelect_best_event();
                                self.supersede_count = 0;
                            }
                        }
                    }
                }
                TrackerState::InChange => {
                    self.episode_base.push_back(base_js);
                    while self.episode_base.len()
                        > PLATEAU_FRAMES.max(self.confirm_frames + 2)
                    {
                        self.episode_base.pop_front();
                    }
                    // 连续性簿记保持原语义:新峰或中途水平都清零恢复计数。
                    if speed_smooth > self.peak_value {
                        self.peak_value = speed_smooth;
                        self.peak_js = local;
                        self.candidate_volume = Some(volume);
                        self.recovery_frames = 0;
                    } else if speed_smooth <= exit_th {
                        self.recovery_frames += 1;
                    } else {
                        self.recovery_frames = 0;
                    }

                    // 提交判定:经典恢复路径(speed 回落 confirm 帧),或
                    // 平台路径(速度噪声大不回落,但 base_js 前后半窗收敛——
                    // 谱形已阶跃并持稳,即"永久变色"形态)。
                    let span_ok = self
                        .entry_volume
                        .is_some_and(|e| volume - e >= self.min_event_volume);
                    let exit_ok = self.recovery_frames >= self.confirm_frames;
                    let plateau_ok = self.base_plateau_reached();
                    if span_ok && (exit_ok || plateau_ok) {
                        self.commit_event();
                        self.state = TrackerState::EndConfirmed;
                        self.episode_base.clear();
                    }
                }
            }
        }

        let maturity = match self.state {
            TrackerState::InChange => {
                (self.recovery_frames as f64 / self.confirm_frames as f64).min(0.99)
            }
            TrackerState::EndConfirmed => 1.0,
            TrackerState::Idle => 0.0,
        };

        let best = self.best_event;
        self.smoothed = Some(smoothed);
        self.previous_volume = Some(volume);
        self.recent.push_back((volume, speed_smooth));
        while self.recent.len() > self.lookback_frames {
            self.recent.pop_front();
        }

        // 诊断快照:armed 为 None 时省略自适应键(与 legacy 导出兼容)。
        let (adaptive_enter, adaptive_exit, adaptive_base) = match &self.armed {
            Some(a) => (Some(a.enter), Some(a.exit), Some(a.base)),
            None => (None, None, None),
        };
        self.last = Diagnostics {
            sample_count: self.frame_count,
            valid_frame: true,
            data_quality: "ok".into(),
            volume: Some(volume),
            delta_volume,
            volume_sync_valid: sync_valid,
            js_local: local,
            js_local_smooth: local_smooth,
            js_speed: speed_raw,
            js_speed_smooth: speed_smooth,
            js_base: base_js,
            adaptive_enter,
            adaptive_exit,
            adaptive_base,
            cross_curvature: curvature_smooth,
            curvature_peak_channel: peak_channel,
            state: self.state,
            candidate_volume: best.map(|e| e.candidate_volume),
            max_js: best.map_or(self.peak_js, |e| e.peak_js),
            event_maturity: maturity,
            recovery_frames: self.recovery_frames,
            baseline_ready: self.baseline.is_some(),
            repeated_volume_count: self.repeated_volume_count,
            nonmonotonic_count: self.nonmonotonic_count,
            event_count: self.events.len(),
            superseded_count: self.supersede_count,
            event_peak_speed: best.map_or(0.0, |e| e.peak_speed),
        };
        self.last.clone()
    }
}

/// 非均匀间距一阶差分（`np.gradient(y, x)` 语义：
/// 内部中心差分，端点单侧差分）。
pub fn gradient_nonuniform(y: &[f64], x: &[f64]) -> Vec<f64> {
    let n = y.len();
    debug_assert_eq!(n, x.len());
    if n == 0 {
        return Vec::new();
    }
    if n == 1 {
        return vec![0.0];
    }
    let mut out = vec![0.0; n];
    out[0] = (y[1] - y[0]) / (x[1] - x[0]);
    out[n - 1] = (y[n - 1] - y[n - 2]) / (x[n - 1] - x[n - 2]);
    for i in 1..n - 1 {
        out[i] = (y[i + 1] - y[i - 1]) / (x[i + 1] - x[i - 1]);
    }
    out
}

/// 小样本中位数(空/含 NaN 返回 None)。
fn median_of<I: Iterator<Item = f64>>(values: I) -> Option<f64> {
    let mut v: Vec<f64> = values.filter(|x| x.is_finite()).collect();
    if v.is_empty() {
        return None;
    }
    v.sort_by(|a, b| a.partial_cmp(b).unwrap());
    Some(if v.len() % 2 == 1 {
        v[v.len() / 2]
    } else {
        0.5 * (v[v.len() / 2 - 1] + v[v.len() / 2])
    })
}
