//! 数据处理层 — Python `DataProcessor` 包的移植。

pub mod ampd;
pub mod adaptive;
pub mod calibration;
pub mod divergence;
pub mod endpoint;
pub mod ewma;
pub mod kf;
pub mod reconstructor;
pub mod savgol;
pub mod tracker;

pub use calibration::{PumpCalibration, DEFAULT_PUMP_SLOPE, PUMP_STEP_FREQ};
pub use endpoint::{
    Confidence, DetectorDiagnostics, EndpointDetector, EndpointResult, Method, Reliability,
};
pub use reconstructor::{ReconError, Reconstructor};
pub use tracker::{SpectralFeatureTracker, TrackerState};
