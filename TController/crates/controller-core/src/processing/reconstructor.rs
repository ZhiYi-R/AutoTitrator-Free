//! AS7341 10 通道 → 全光谱重建 — Python `reconstructor.py` 的移植。
//!
//! ams-OSRAM Golden Device 校准矩阵（`calibre.npz`）：
//! `corrected = factor × max(raw − offset, 0)`，
//! `spectrum[λ] = Σ_ch corrected[ch] × matrix[λ, ch]`（380–1100 nm，1 nm 步长，721 点）。

use std::path::{Path, PathBuf};

use ndarray::Array2;
use ndarray_npy::NpzReader;
use thiserror::Error;

/// 重建错误。
#[derive(Debug, Error)]
pub enum ReconError {
    #[error("光谱校准数据未找到: {0}")]
    FileNotFound(PathBuf),
    #[error("校准数据读取失败: {0}")]
    Read(String),
    #[error("需要 10 通道数据，传入长度为 {0}")]
    BadChannelCount(usize),
    #[error("原始通道值不应包含负数")]
    NegativeValue,
    #[error("原始通道值包含 NaN 或 Inf")]
    NonFinite,
}

/// Golden Device 校准数据（数值部分）。
#[derive(Debug, Clone)]
pub struct Reconstructor {
    /// 380–1100 nm（721 点）。
    pub wavelengths: Vec<f64>,
    /// (721, 10) 重建矩阵。
    pub matrix: Array2<f64>,
    pub offsets: Vec<f64>,
    pub factors: Vec<f64>,
}

impl Reconstructor {
    /// 从 `calibre.npz` 加载数值键（对象键如电极元数据不在此层处理）。
    pub fn load(path: &Path) -> Result<Self, ReconError> {
        if !path.is_file() {
            return Err(ReconError::FileNotFound(path.to_path_buf()));
        }
        let file = std::fs::File::open(path)
            .map_err(|e| ReconError::Read(format!("{}: {e}", path.display())))?;
        let mut npz = NpzReader::new(file).map_err(|e| ReconError::Read(e.to_string()))?;

        let read_f64_1d =
            |npz: &mut NpzReader<std::fs::File>, key: &str| -> Result<Vec<f64>, ReconError> {
                let arr: ndarray::Array1<f64> = npz
                    .by_name(key)
                    .map_err(|e| ReconError::Read(format!("{key}: {e}")))?;
                Ok(arr.to_vec())
            };

        let matrix: ndarray::Array2<f64> = npz
            .by_name("spectral_matrix")
            .map_err(|e| ReconError::Read(format!("spectral_matrix: {e}")))?;
        let wl_i32: ndarray::Array1<i32> = npz
            .by_name("spectral_wavelengths")
            .map_err(|e| ReconError::Read(format!("spectral_wavelengths: {e}")))?;
        let offsets = read_f64_1d(&mut npz, "spectral_offsets")?;
        let factors = read_f64_1d(&mut npz, "spectral_factors")?;

        Ok(Self {
            wavelengths: wl_i32.iter().map(|&v| v as f64).collect(),
            matrix,
            offsets,
            factors,
        })
    }

    /// 按开发/打包规则探测 `calibre.npz`：
    /// 1. 环境变量 `AUTOTITRATOR_CALIBRE`；
    /// 2. 可执行文件同级目录；
    /// 3. 开发模式：最终 workspace 的 `TController/data/`（编译期锚定）。
    pub fn discover() -> Result<(Self, PathBuf), ReconError> {
        let candidates: Vec<PathBuf> = {
            let mut v = Vec::new();
            if let Ok(p) = std::env::var("AUTOTITRATOR_CALIBRE") {
                v.push(PathBuf::from(p));
            }
            v.push(
                std::env::current_exe()
                    .ok()
                    .and_then(|e| e.parent().map(|d| d.join("calibre.npz")))
                    .unwrap_or_default(),
            );
            v.push(PathBuf::from(concat!(
                env!("CARGO_MANIFEST_DIR"),
                "/../../../TController/data/calibre.npz"
            )));
            v
        };
        for path in candidates {
            if path.is_file() {
                return Ok((Self::load(&path)?, path));
            }
        }
        Err(ReconError::FileNotFound(PathBuf::from("calibre.npz")))
    }

    /// 从 10 通道原始 ADC 值重建全光谱，返回 `(波长, 谱)`。
    pub fn reconstruct(&self, raw: &[f64]) -> Result<(Vec<f64>, Vec<f64>), ReconError> {
        if raw.len() != 10 {
            return Err(ReconError::BadChannelCount(raw.len()));
        }
        if raw.iter().any(|&v| v < 0.0) {
            return Err(ReconError::NegativeValue);
        }
        if !raw.iter().all(|v| v.is_finite()) {
            return Err(ReconError::NonFinite);
        }
        let corrected: Vec<f64> = raw
            .iter()
            .zip(&self.offsets)
            .zip(&self.factors)
            .map(|((&r, &o), &f)| f * (r - o).max(0.0))
            .collect();
        // spectrum = max(matrix @ corrected, 0)
        let mut spectrum = vec![0.0f64; self.matrix.nrows()];
        for (row_out, row) in spectrum.iter_mut().zip(self.matrix.rows()) {
            *row_out = row
                .iter()
                .zip(&corrected)
                .map(|(&m, &c)| m * c)
                .sum::<f64>()
                .max(0.0);
        }
        Ok((self.wavelengths.clone(), spectrum))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn discover_and_reconstruct_roundtrip() {
        let (rec, path) = Reconstructor::discover().expect("calibre.npz");
        assert!(path.is_file());
        assert_eq!(rec.wavelengths.len(), 721);
        assert_eq!(rec.matrix.dim(), (721, 10));

        let raw = [1000.0f64; 10];
        let (wls, spectrum) = rec.reconstruct(&raw).unwrap();
        assert_eq!(wls.len(), spectrum.len());
        assert!(spectrum.iter().all(|v| v.is_finite() && *v >= 0.0));

        assert!(matches!(
            rec.reconstruct(&[1.0; 10][..9]),
            Err(ReconError::BadChannelCount(9))
        ));
        assert!(matches!(
            rec.reconstruct(&[-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]),
            Err(ReconError::NegativeValue)
        ));
    }
}
