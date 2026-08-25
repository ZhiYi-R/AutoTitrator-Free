//! controller-core — TController 上位机后端逻辑的 Rust 移植。
//!
//! 该 crate 保留了从旧 Python 上位机移植时建立的模块边界：
//!
//! | Python                        | Rust                              |
//! |-------------------------------|-----------------------------------|
//! | `Communication/protocol.py`   | [`protocol`]                      |
//! | `DataProcessor/endpoint.py`   | [`processing::endpoint`]          |
//! | `DataProcessor/online_features.py` | [`processing::tracker`] / [`processing::kf`] / [`processing::divergence`] |
//! | `DataProcessor/reconstructor.py`   | [`processing::reconstructor`]     |
//! | `DataProcessor/calibration.py`     | [`processing::calibration`]       |
//! | `gui/main_window.py` 工作流   | [`workflow`]                      |
//!
//! 本 crate 为纯逻辑 + 串口 I/O 线程，不含 UI；Tauri 壳在 `app/src-tauri`。

pub mod processing;
pub mod protocol;
pub mod workflow;

pub const VERSION: &str = env!("CARGO_PKG_VERSION");
