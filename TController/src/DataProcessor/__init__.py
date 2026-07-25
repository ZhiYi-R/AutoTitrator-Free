"""DataProcessor — 数据处理包。

功能::
    - reconstruct:  AS7341 10 通道光谱 → 全光谱重建
    - EndpointDetector:  滴定终点在线检测（电位 + 光谱共识）

用法::

    from DataProcessor import reconstruct, EndpointDetector
"""

from DataProcessor.reconstructor import reconstruct, is_available, get_wavelengths
from DataProcessor.endpoint import EndpointDetector, savgol_filter
from DataProcessor.calibration import (
    FLOW_RATE, PUMP_SLOPE, PUMP_INTERCEPT, PUMP_STEP_FREQ,
    steps_from_volume, volume_from_steps,
)

__all__ = [
    "reconstruct", "is_available", "get_wavelengths",
    "EndpointDetector", "savgol_filter",
    "FLOW_RATE", "PUMP_SLOPE", "PUMP_INTERCEPT", "PUMP_STEP_FREQ",
    "steps_from_volume", "volume_from_steps",
]
