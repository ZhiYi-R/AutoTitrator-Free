"""DataProcessor — 数据处理包。

功能::
    - reconstruct:  AS7341 10 通道光谱 → 全光谱重建
    - EndpointDetector:  滴定终点在线检测（电位 + 光谱共识）

用法::

    from DataProcessor import reconstruct, EndpointDetector
"""

from DataProcessor.calibration import (
    FLOW_RATE,
    PUMP_INTERCEPT,
    PUMP_SLOPE,
    PUMP_STEP_FREQ,
    steps_from_volume,
    volume_from_steps,
)
from DataProcessor.endpoint import EndpointDetector, savgol_filter
from DataProcessor.online_features import (
    EndpointFusionKF,
    SpectralFeatureTracker,
    cross_entropy,
    cross_entropy_excess,
    js_divergence,
    normalize_spectrum,
)
from DataProcessor.reconstructor import get_wavelengths, is_available, reconstruct

__all__ = [
    "FLOW_RATE",
    "PUMP_INTERCEPT",
    "PUMP_SLOPE",
    "PUMP_STEP_FREQ",
    "EndpointDetector",
    "EndpointFusionKF",
    "SpectralFeatureTracker",
    "cross_entropy",
    "cross_entropy_excess",
    "get_wavelengths",
    "is_available",
    "js_divergence",
    "normalize_spectrum",
    "reconstruct",
    "savgol_filter",
    "steps_from_volume",
    "volume_from_steps",
]
