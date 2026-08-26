//! 自适应阈值参数 — 基于基线期稳健统计(中位数/MAD)+绝对下限兜底。
//!
//! 设计约束(源自 `endpoint.rs`/`tracker.rs` 现有状态机):
//! * 全部因果:统计只来自基准建立前的样本,不回头修改已发布事件。
//! * 退化安全:零方差(合成测试、恒定信号)下 MAD→0,必须回落到
//!   既有常数下限,保证现有行为不被"更紧的自适应阈值"破坏。
//! * 有界:K 系数与裁剪区间把自适应结果限制在正常量级内,
//!   异常噪声尖峰只会导致退回下限而不是阈值爆炸。

/// 稳健单变量统计:容量上限 ring buffer + 中位数/MAD。
///
/// MAD → σ 当量换算系数 1.4826(正态假设下的 1/Φ⁻¹(3/4))。
#[derive(Debug, Clone)]
pub struct RobustStats {
    cap: usize,
    buf: Vec<f64>,
}

impl RobustStats {
    pub fn new(cap: usize) -> Self {
        Self {
            cap: cap.max(4),
            buf: Vec::new(),
        }
    }

    /// NaN 样本直接丢弃;容量满时覆盖最旧样本。
    pub fn push(&mut self, x: f64) {
        if !x.is_finite() {
            return;
        }
        if self.buf.len() < self.cap {
            self.buf.push(x);
        } else {
            self.buf.remove(0);
            self.buf.push(x);
        }
    }

    pub fn len(&self) -> usize {
        self.buf.len()
    }

    pub fn is_empty(&self) -> bool {
        self.buf.is_empty()
    }

    pub fn ready(&self, min_n: usize) -> bool {
        // 不把 min_n 截到容量:要 9 个样本而容量只有 8 时应永远不武装,
        // 而不是谎报就绪。
        self.buf.len() >= min_n
    }

    pub fn median(&self) -> Option<f64> {
        robust_median(&self.buf)
    }

    /// σ 当量 = 1.4826 × median(|x − median|);零散布返回 None,让调用方兜底。
    pub fn mad_sigma(&self) -> Option<f64> {
        let med = self.median()?;
        let mut dev: Vec<f64> = self.buf.iter().map(|&x| (x - med).abs()).collect();
        robust_median(&dev.as_mut_slice())
            .map(|m| m * 1.4826)
            .filter(|s| *s > 1e-30)
    }
}

fn robust_median(values: &[f64]) -> Option<f64> {
    if values.is_empty() || values.iter().any(|v| !v.is_finite()) {
        return None;
    }
    let mut v = values.to_vec();
    v.sort_by(|a, b| a.partial_cmp(b).unwrap());
    Some(if v.len() % 2 == 1 {
        v[v.len() / 2]
    } else {
        0.5 * (v[v.len() / 2 - 1] + v[v.len() / 2])
    })
}

// ---- 光谱通道 K 与下限(K 待真机回放标定,见 tools/adaptive_tuning_notes.md)----

/// θ_enter = median + K_SPD·σ̂_MAD 的初始倍数。真实滴定事件峰值速度在 O(1)
/// nats/mL² 量级而平台噪声约 2e-12,K 取大值只影响噪声异常的体系。
pub const DEFAULT_K_SPD: f64 = 8.0;
/// θ_base = median + K_BASE·σ̂_MAD。
pub const DEFAULT_K_BASE: f64 = 8.0;
/// 电位通道 offset_enter = max(K_POT·σ̂, floor)。
pub const DEFAULT_K_POT: f64 = 2.5;
/// 光谱速度统计最少样本(推进帧数)才允许武装自适应阈值。
pub const SPD_MIN_SAMPLES: usize = 6;
/// 基准残差统计最少样本。
pub const BASE_MIN_SAMPLES: usize = 5;

/// 自适应参数集。
#[derive(Debug, Clone)]
pub struct AdaptiveParams {
    /// false 时所有快照返回 None,行为与固定阈值完全一致。
    pub enabled: bool,
    /// 永久变色判别(恢复缺口/追溯降级)开关。独立于 `enabled`:
    /// 这是化学语义层,不是噪声估计;固定阈值模式下也应生效。
    /// 仅在对照旧实现数值时关闭(legacy_fixed)。
    pub permanent_color: bool,
    // K 系数
    pub k_spd: f64,
    pub k_base: f64,
    pub k_pot: f64,
    /// 电位退出偏移 / 进入偏移(Python 语义:POT_MIN_EXIT:POT_MIN_ENTER=0.2)。
    pub pot_exit_ratio: f64,
    // 自适应结果上限(超过视为统计不可信,退回下限):
    /// θ_enter 上限(nats/mL²)。低于真实事件两个量级仍安全,
    /// 高于此说明窗口混入了事件本身。
    pub spd_enter_max: f64,
    /// θ_base 上限(nats,原始 JS 尺度)。真实事件约 2e-7,
    /// 5e-5 只是病态统计防呆线。
    pub base_enter_max: f64,
    /// 电位 offset_enter 上限(V/s),防观察期异常值抬高门槛。
    pub pot_offset_max: f64,
    // 绝对下限 = 现行生产常数(退化回落目标)。
    pub spd_enter_floor: f64,
    pub base_enter_floor: f64,
    pub pot_offset_floor: f64,
}

impl Default for AdaptiveParams {
    fn default() -> Self {
        Self {
            enabled: true,
            permanent_color: true,
            k_spd: DEFAULT_K_SPD,
            k_base: DEFAULT_K_BASE,
            k_pot: DEFAULT_K_POT,
            pot_exit_ratio: 0.2,
            spd_enter_max: 0.5,
            base_enter_max: 5e-5,
            pot_offset_max: 0.05,
            spd_enter_floor: super::endpoint::SPEC_JS_ENTER,
            base_enter_floor: super::endpoint::SPEC_BASELINE_ENTER,
            pot_offset_floor: super::endpoint::POT_MIN_ENTER,
        }
    }
}

impl AdaptiveParams {
    /// 完全复现既有行为的对照模式(自适应与永久变色判别都关)。
    pub fn legacy_fixed() -> Self {
        Self {
            enabled: false,
            permanent_color: false,
            ..Self::default()
        }
    }

    /// 光谱进入阈值:max(自适应估计, 下限),再配上限裁剪后的兜底逻辑。
    ///
    /// 返回 None 表示 legacy 模式或统计不足。
    pub fn spectral_enter(&self, speed_stats: &RobustStats) -> Option<f64> {
        if !self.enabled || !speed_stats.ready(SPD_MIN_SAMPLES) {
            return None;
        }
        let sigma = speed_stats.mad_sigma()?;
        let est = speed_stats.median()? + self.k_spd * sigma;
        Some(est.clamp(
            self.spd_enter_floor,
            self.spd_enter_floor.max(self.spd_enter_max),
        ))
    }

    /// 光谱退出阈值 = RATIO_EXIT × θ_enter(保持 0.16 现比值);
    /// 拿不到自适应进入阈值时返回 None。
    pub fn spectral_exit(&self, adaptive_enter: f64) -> f64 {
        adaptive_enter * (super::endpoint::SPEC_JS_EXIT / super::endpoint::SPEC_JS_ENTER)
    }

    /// 光谱基准残差阈值;None = legacy 或统计不足(调用方落 `base_enter_floor`)。
    pub fn spectral_base(&self, residual_stats: &RobustStats) -> Option<f64> {
        if !self.enabled || !residual_stats.ready(BASE_MIN_SAMPLES) {
            return None;
        }
        let sigma = residual_stats.mad_sigma()?;
        let est = residual_stats.median()? + self.k_base * sigma;
        Some(est.clamp(self.base_enter_floor, self.base_enter_max))
    }

    /// 电位通道进入偏移 = clamp(k_pot·σ̂, floor, pot_offset_max)。
    /// legacy 或 σ̂ 缺失时返回 None(调用方用 std 版公式+固定下限)。
    pub fn potential_offset(&self, obs_stats: &RobustStats) -> Option<f64> {
        if !self.enabled {
            return None;
        }
        let sigma = obs_stats.mad_sigma()?;
        let est = sigma * self.k_pot;
        Some(est.clamp(
            self.pot_offset_floor,
            self.pot_offset_floor.max(self.pot_offset_max),
        ))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn median_even_and_odd() {
        assert_eq!(robust_median(&[3.0, 1.0]), Some(2.0));
        assert_eq!(robust_median(&[5.0, 1.0, 2.0]), Some(2.0));
    }

    #[test]
    fn known_mad_sigma() {
        // [1..=11] 中位数 6,绝对偏差 {5..0..5} 中位数 3 → σ̂≈4.45
        let mut s = RobustStats::new(64);
        for x in 1i32..=11 {
            s.push(x as f64);
        }
        approx::assert_relative_eq!(s.median().unwrap(), 6.0);
        approx::assert_relative_eq!(s.mad_sigma().unwrap(), 4.4478, epsilon = 1e-3);
    }

    #[test]
    fn zero_dispersion_returns_none() {
        let mut s = RobustStats::new(64);
        for _ in 0..10 {
            s.push(2.5);
        }
        assert!(s.ready(6));
        assert_eq!(s.mad_sigma(), None);
    }

    #[test]
    fn nan_is_dropped_and_cap_respected() {
        let mut s = RobustStats::new(8);
        for i in 0..20 {
            s.push(i as f64);
            s.push(f64::NAN);
        }
        assert_eq!(s.len(), 8);
        // ring 保留最后 8 个有效样本 {12..19},偶数长度取均值
        assert_eq!(s.median(), Some(15.5));
        assert!(!s.ready(9));
    }

    #[test]
    fn outlier_is_finite_mean_for_ring_semantics() {
        let mut s = RobustStats::new(16);
        for x in 0..100usize {
            s.push((x % 16) as f64);
        }
        // cap 覆盖旧数据,但仍在 ring 内循环
        assert_eq!(s.len(), 16);
        assert!(s.median().is_some());
    }

    #[test]
    fn legacy_fixed_returns_none_everywhere() {
        let p = AdaptiveParams::legacy_fixed();
        let mut stats = RobustStats::new(64);
        for i in 0..12 {
            stats.push(0.02 + (i as f64 % 3.0) * 0.001);
        }
        assert_eq!(p.spectral_enter(&stats), None);
        assert_eq!(p.spectral_base(&stats), None);
        assert_eq!(p.potential_offset(&stats), None);
    }

    #[test]
    fn adaptive_threshold_clamped_by_floor_and_max() {
        let p = AdaptiveParams::default();
        assert_eq!(p.spd_enter_floor, 0.05);

        // 极小散布 → 回落到下限
        let mut tiny = RobustStats::new(64);
        tiny.push(2e-13);
        tiny.push(3e-13);
        tiny.push(2.5e-13);
        tiny.push(2.2e-13);
        tiny.push(2.8e-13);
        tiny.push(2.4e-13);
        while !tiny.ready(SPD_MIN_SAMPLES) {
            tiny.push(2.5e-13 + (tiny.len() as f64) * 1e-15);
        }
        let enter = p.spectral_enter(&tiny).unwrap();
        assert!((enter - 0.05).abs() < 1e-12, "got {enter}");

        // 大散布(median 0.2,σ̂ 明显)→ 被 spd_enter_max 封顶
        let mut wide = RobustStats::new(64);
        for i in 0..16 {
            wide.push(0.2 + ((i % 2) as f64) * 0.08);
        }
        let enter_wide = p.spectral_enter(&wide).unwrap();
        assert!(enter_wide <= 0.5 + 1e-12, "got {enter_wide}");
        assert!(enter_wide >= 0.05);
    }

    #[test]
    fn insufficient_samples_return_none() {
        let p = AdaptiveParams::default();
        let mut stats = RobustStats::new(64);
        for i in 0..5 {
            stats.push(0.01 + i as f64);
        }
        assert_eq!(p.spectral_enter(&stats), None);
    }
}
