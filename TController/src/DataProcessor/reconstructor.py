"""
AS7341 10 通道 → 全光谱重建。

使用 ams-OSRAM 官方 Golden Device 校准矩阵将 10 通道
(F1–F8, Clear, NIR) 原始 ADC 值重建为 380–1000 nm
连续全光谱（1 nm 步长，621 点）。

重建流程::

    corrected = factor × max(raw − offset, 0)
    spectrum[λ] = Σ factor[ch] × corrected[ch] × matrix[λ, ch]
"""

from __future__ import annotations

import os
from collections.abc import Sequence

import numpy as np

from DataProcessor._path import CALIBRE_PATH

_DATA_PATH = CALIBRE_PATH

_lazy: dict | None = None


def _load() -> dict:
    global _lazy
    if _lazy is not None:
        return _lazy
    if not os.path.isfile(_DATA_PATH):
        raise FileNotFoundError(f"光谱校准数据未找到: {_DATA_PATH}")
    data = np.load(_DATA_PATH, allow_pickle=True)
    _lazy = {
        k.replace("spectral_", ""): v
        for k, v in data.items()
        if k.startswith("spectral_")
    }
    return _lazy


def is_available() -> bool:
    """检查校准数据文件是否存在。"""
    return os.path.isfile(_DATA_PATH)


def get_wavelengths() -> np.ndarray:
    """返回波长数组 (380–1000 nm, 1 nm 步长)。"""
    return _load()["wavelengths"].copy()


def reconstruct(
    raw_values: Sequence[float] | np.ndarray,
    offsets: np.ndarray | None = None,
    factors: np.ndarray | None = None,
) -> tuple[np.ndarray, np.ndarray]:
    """从 10 通道原始 ADC 值重建全光谱。

    参数
    ----
    raw_values:
        10 元素序列 [F1, F2, F3, F4, F5, F6, F7, F8, Clear, NIR]。
    offsets:
        每通道暗电流/偏移。默认 → Golden Device 参考值。
    factors:
        每通道校正系数。默认 → Golden Device 参考值。

    返回
    ----
    (wavelengths, spectrum)
        两个一维 NumPy 数组 (len = 721)。
        wavelengths — 纳米波长的点
        spectrum   — 相对强度值 (a.u.)
    """
    cal = _load()
    raw = np.asarray(raw_values, dtype=np.float64)
    if raw.shape != (10,):
        raise ValueError(f"需要 10 通道数据，传入形状为 {raw.shape}")

    ofs = cal["offsets"] if offsets is None else np.asarray(offsets, dtype=np.float64)
    fac = cal["factors"] if factors is None else np.asarray(factors, dtype=np.float64)

    corrected = fac * np.maximum(raw - ofs, 0.0)
    spectrum = np.maximum(
        cal["matrix"] @ corrected, 0.0
    )  # (721, 10) @ (10,) 2192 (721,)

    return cal["wavelengths"].copy(), spectrum
