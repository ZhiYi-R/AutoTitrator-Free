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
    global PUMP_SLOPE, PUMP_INTERCEPT
    if not os.path.isfile(_DATA_FILE):
        return
    try:
        _data = np.load(_DATA_FILE, allow_pickle=True)
        PUMP_SLOPE = float(_data["pump1_slope"])
        PUMP_INTERCEPT = float(_data["pump1_intercept"])
    except Exception:
        pass


_load()

FLOW_RATE = PUMP_SLOPE * PUMP_STEP_FREQ


def steps_from_volume(vol_mL: float) -> int:
    return max(0, int(vol_mL / PUMP_SLOPE))


def volume_from_steps(steps: int) -> float:
    return PUMP_SLOPE * steps


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
