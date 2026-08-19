"""
蠕动泵标定数据。

从 data/pump1_calib.json 自动加载，也可通过 update_from_file() 刷新。
"""

from __future__ import annotations

import os

import numpy as np

from DataProcessor._path import CALIBRE_PATH

# ---- 泵运行频率 ----
PUMP_STEP_FREQ = 1000  # Hz, PumpMotor1::Initialize(1000)

# ---- 默认值（JSON 加载失败时回退） ----
PUMP_SLOPE = 6.03752e-6
PUMP_INTERCEPT = 0.0

# ---- 运行时加载 ----
_DATA_FILE = CALIBRE_PATH


def _load() -> None:
    """从 data/calibration.npz 加载泵标定参数，静默失败时保留默认值。"""
    global PUMP_SLOPE, PUMP_INTERCEPT
    if not os.path.isfile(_DATA_FILE):
        return
    try:
        _data = np.load(_DATA_FILE, allow_pickle=True)
        slope = float(_data["pump1_slope"])
        intercept = float(_data["pump1_intercept"])
        
        # 合法性校验：slope 必须为正数，intercept 允许负值但不应过大
        if slope <= 0:
            raise ValueError(f"pump1_slope 必须为正数，当前值为 {slope}")
        if abs(intercept) > 10.0:
            raise ValueError(f"pump1_intercept 绝对值超限（>10.0 mL），当前值为 {intercept}")
        
        PUMP_SLOPE = slope
        PUMP_INTERCEPT = intercept
    except Exception:
        # 静默失败，保留模块级默认值
        pass


_load()

FLOW_RATE = PUMP_SLOPE * PUMP_STEP_FREQ


def steps_from_volume(vol_mL: float) -> int:
    """将体积（mL）转换为泵步数。
    
    使用线性模型反向计算：steps = (volume - intercept) / slope
    """
    if PUMP_SLOPE <= 0:
        raise ValueError(f"PUMP_SLOPE 必须为正数，当前值为 {PUMP_SLOPE}")
    steps = (vol_mL - PUMP_INTERCEPT) / PUMP_SLOPE
    return max(0, int(steps))


def volume_from_steps(steps: int) -> float:
    """将泵步数转换为体积（mL）。
    
    使用线性模型：volume = slope × steps + intercept
    """
    return PUMP_SLOPE * steps + PUMP_INTERCEPT


def update_from_file() -> None:
    """重新从 data/ 加载校准文件（用户在标定界面保存后调用）。"""
    _load()
    global FLOW_RATE
    FLOW_RATE = PUMP_SLOPE * PUMP_STEP_FREQ


__all__ = [
    "FLOW_RATE",
    "PUMP_INTERCEPT",
    "PUMP_SLOPE",
    "PUMP_STEP_FREQ",
    "steps_from_volume",
    "update_from_file",
    "volume_from_steps",
]
