//! 因果光谱特征追踪器 — Python `SpectralFeatureTracker` 的移植。
//!
//! 两个必须知道的行为（源自 Python 文档）：
//!
//! * 体积归一化速度锚定到最后一个*前进*帧而非上一帧。生产中固件每 AS7341
//!   帧上报一帧光谱而体积来自泵，多帧共享同一体积；把零步长喂进速度滤波会
//!   注入 0 并淹没真实事件，所以体积静止时速度滤波器*保持*电平。
//! * `END_CONFIRMED` 可重入。激变记录进 `events`，报告的终点是最强事件，
//!   只有后续事件强 `supersede_ratio` 倍才顶替。一次性闩锁曾在真实数据
//!   （Paper/ExpData B 组）上把早于真终点 0.97 mL 的瞬态锁成终点，
//!   Kalman 门只能拒绝、无法修复。

use std::collections::VecDeque;

use serde::Serialize;

use super::divergence::{cross_entropy_excess, finite_vector, js_divergence, EPS, JS_FLOOR};
use super::ewma::Ewma;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize)]
#[serde(rename_all = "SCREAMING_SNAKE_CASE")]
pub enum TrackerState {
    Idle,
    InChange,
    EndConfirmed,
}

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
}

impl Default for SpectralFeatureTracker {
    fn default() -> Self {
        Self::new()
    }
}

impl SpectralFeatureTracker {
    pub fn new() -> Self {
        Self::with_params(
            0.20,  // alpha
            0.05,  // js_enter
            0.008, // js_exit
            3e-7,  // baseline_enter
            12,    // baseline_frames
            0.30,  // baseline_max_volume
            4,     // confirm_frames
            0.08,  // min_event_volume
            1e-8,  // epsilon_volume
            8,     // lookback_frames
            1.5,   // supersede_ratio
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
        };
        t.reset_state();
        t
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
    /// 下降沿上；用保留窗口播种峰值，使候选落在真实最大值而非穿越点。
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

    /// 记录完成的激变并保留最强者（带滞回：近持平不顶替）。
    fn commit_event(&mut self) {
        let Some(candidate) = self.candidate_volume else {
            return;
        };
        let event = ExcursionEvent {
            candidate_volume: candidate,
            entry_volume: self.entry_volume.unwrap_or(candidate),
            peak_speed: self.peak_value,
            peak_js: self.peak_js,
        };
        self.events.push(event);
        match self.best_event {
            None => self.best_event = Some(event),
            Some(best) if event.peak_speed > best.peak_speed * self.supersede_ratio => {
                // 后发事件须明显更强才接管，报告终点不抖动。
                self.best_event = Some(event);
                self.supersede_count += 1;
            }
            _ => {}
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
        if self.baseline.is_none() && volume <= self.baseline_max_volume {
            if self.baseline_sum.is_none() {
                self.baseline_sum = Some(vec![0.0; smoothed.len()]);
            }
            if let Some(bs) = self.baseline_sum.as_mut() {
                for (acc, v) in bs.iter_mut().zip(&smoothed) {
                    *acc += v;
                }
            }
            self.baseline_count += 1;
            if self.baseline_count >= self.baseline_frames {
                let count = self.baseline_count as f64;
                let mut base: Vec<f64> = self
                    .baseline_sum
                    .take()
                    .expect("baseline_sum checked")
                    .into_iter()
                    .map(|v| v / count)
                    .collect();
                let total: f64 = super::divergence::np_sum(&base).max(EPS);
                for v in base.iter_mut() {
                    *v /= total;
                }
                self.baseline = Some(base);
            }
        }

        let base_js = match &self.baseline {
            None => 0.0,
            Some(base) => js_divergence(&smoothed, base),
        };

        // ---- 状态机（END_CONFIRMED 可重入）----
        if self.baseline.is_some() {
            match self.state {
                TrackerState::Idle | TrackerState::EndConfirmed => {
                    if speed_smooth >= self.js_enter && base_js >= self.baseline_enter {
                        let (peak_speed, peak_volume) = self.lookback_peak(volume, speed_smooth);
                        self.state = TrackerState::InChange;
                        self.entry_volume = Some(volume);
                        self.candidate_volume = Some(peak_volume);
                        self.peak_value = peak_speed;
                        self.peak_js = local;
                        self.recovery_frames = 0;
                    }
                }
                TrackerState::InChange => {
                    if speed_smooth > self.peak_value {
                        self.peak_value = speed_smooth;
                        self.peak_js = local;
                        self.candidate_volume = Some(volume);
                        self.recovery_frames = 0;
                    } else if speed_smooth <= self.js_exit {
                        self.recovery_frames += 1;
                        if let Some(entry) = self.entry_volume {
                            if volume - entry >= self.min_event_volume
                                && self.recovery_frames >= self.confirm_frames
                            {
                                self.state = TrackerState::EndConfirmed;
                                self.commit_event();
                            }
                        }
                    } else {
                        self.recovery_frames = 0;
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
