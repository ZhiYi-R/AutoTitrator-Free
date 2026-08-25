//! 蠕动泵标定 — Python `calibration.py` 的移植。
//!
//! 标定参数从 `calibre.npz` 的 `pump1_slope`/`pump1_intercept` 加载，
//! 加载失败或非法时静默回退默认值。

use std::path::Path;

use ndarray_npy::NpzReader;

/// 泵步进频率（Hz，固件 PumpMotor1::Initialize(1000)）。
pub const PUMP_STEP_FREQ: f64 = 1000.0;
/// 默认斜率（mL/步），npz 缺失/非法时回退。
pub const DEFAULT_PUMP_SLOPE: f64 = 6.03752e-6;
pub const DEFAULT_PUMP_INTERCEPT: f64 = 0.0;

/// 泵线性模型：volume = slope × steps + intercept。
#[derive(Debug, Clone, Copy)]
pub struct PumpCalibration {
    pub slope: f64,
    pub intercept: f64,
}

impl Default for PumpCalibration {
    fn default() -> Self {
        Self {
            slope: DEFAULT_PUMP_SLOPE,
            intercept: DEFAULT_PUMP_INTERCEPT,
        }
    }
}

impl PumpCalibration {
    /// 流速（mL/s）。
    pub fn flow_rate(&self) -> f64 {
        self.slope * PUMP_STEP_FREQ
    }

    /// 体积（mL）→ 泵步数（反向线性；下限 0）。
    pub fn steps_from_volume(&self, volume_ml: f64) -> u32 {
        if self.slope <= 0.0 {
            // Python 会 raise；这里防御性返回 0，调用方负责用 valid() 校验。
            return 0;
        }
        let steps = (volume_ml - self.intercept) / self.slope;
        steps.max(0.0) as u32
    }

    /// 泵步数 → 体积（mL）。
    pub fn volume_from_steps(&self, steps: u32) -> f64 {
        self.slope * steps as f64 + self.intercept
    }

    /// 标定参数是否可用（slope 必须为正）。
    pub fn valid(&self) -> bool {
        self.slope > 0.0
    }

    /// 从 `calibre.npz` 读取 `pump{N}_slope` / `pump{N}_intercept`；
    /// 非法或缺失时静默保留默认值（与 Python `_load` 行为一致）。
    pub fn load_from(path: &Path, pump_id: u8) -> Self {
        let mut this = Self::default();
        if !path.is_file() {
            return this;
        }
        let Ok(file) = std::fs::File::open(path) else {
            return this;
        };
        let Ok(mut npz) = NpzReader::new(file) else {
            return this;
        };
        let read_scalar = |npz: &mut NpzReader<std::fs::File>, key: &str| -> Option<f64> {
            let arr: ndarray::Array1<f64> = npz.by_name(key).ok()?;
            arr.first().copied()
        };
        let slope_key = format!("pump{pump_id}_slope");
        let intercept_key = format!("pump{pump_id}_intercept");
        let (Some(slope), intercept) = (
            read_scalar(&mut npz, &slope_key),
            read_scalar(&mut npz, &intercept_key).unwrap_or(0.0),
        ) else {
            return this;
        };
        // 合法性校验：slope 必为正；intercept 允许负但 |intercept| ≤ 10 mL。
        if slope <= 0.0 || intercept.abs() > 10.0 {
            return this;
        }
        this.slope = slope;
        this.intercept = intercept;
        this
    }

    /// 从 `calibre.npz` 读取泵的累计步数、实测体积点和 R²。
    /// 缺少任一数组时返回空点集；非法值由调用方决定如何展示。
    pub fn load_points_from(path: &Path, pump_id: u8) -> (Vec<(u32, f64)>, Option<f64>) {
        if !path.is_file() {
            return (Vec::new(), None);
        }
        let Ok(file) = std::fs::File::open(path) else {
            return (Vec::new(), None);
        };
        let Ok(mut npz) = NpzReader::new(file) else {
            return (Vec::new(), None);
        };
        let pulses_key = format!("pump{pump_id}_pulses");
        let volumes_key = format!("pump{pump_id}_volumes");
        let r2_key = format!("pump{pump_id}_r2");
        let Ok(pulses) = npz.by_name::<ndarray::OwnedRepr<i32>, ndarray::Ix1>(&pulses_key) else {
            return (Vec::new(), None);
        };
        let Ok(volumes) = npz.by_name::<ndarray::OwnedRepr<f64>, ndarray::Ix1>(&volumes_key) else {
            return (Vec::new(), None);
        };
        let points = pulses
            .iter()
            .zip(volumes.iter())
            .filter_map(|(&steps, &vol)| {
                (steps >= 0 && vol.is_finite()).then_some((steps as u32, vol))
            })
            .collect();
        let r2 = npz
            .by_name::<ndarray::OwnedRepr<f64>, ndarray::Ix0>(&r2_key)
            .ok()
            .and_then(|v| v.first().copied())
            .or_else(|| {
                npz.by_name::<ndarray::OwnedRepr<f64>, ndarray::Ix1>(&r2_key)
                    .ok()
                    .and_then(|v| v.first().copied())
            });
        (points, r2.filter(|v| v.is_finite()))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn default_roundtrip() {
        let cal = PumpCalibration::default();
        approx::assert_relative_eq!(cal.flow_rate(), 6.03752e-3);
        let steps = cal.steps_from_volume(5.0);
        // u32 截断误差 < 1 步（≈6e-6 mL）
        approx::assert_relative_eq!(cal.volume_from_steps(steps), 5.0, epsilon = 1e-4);
    }

    #[test]
    fn intercept_shifts_volume() {
        let cal = PumpCalibration {
            slope: 1e-5,
            intercept: 0.1,
        };
        approx::assert_relative_eq!(cal.volume_from_steps(1000), 0.1 + 1e-2, max_relative = 1e-9);
        // 反向换算扣除 intercept；u32 截断容许 ±1 步的浮点边界
        let steps = cal.steps_from_volume(0.1 + 1e-2);
        assert!((999..=1000).contains(&steps), "steps = {steps}");
    }
}
