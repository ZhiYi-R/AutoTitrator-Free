"""实时光谱曲线控件（matplotlib blit 加速）。"""

from __future__ import annotations

import tkinter as tk

import numpy as np
from matplotlib.patches import Polygon

from gui._plot import _BlitPlot


class SpectrumWidget(_BlitPlot):
    """AS7341 全光谱实时曲线 (380–1100 nm)。"""

    def __init__(self, parent: tk.Misc, **kwargs) -> None:
        super().__init__(parent, title="实时光谱 / Spectrum", **kwargs)

        self._ax.set_xlabel("Wavelength (nm)")
        self._ax.set_ylabel("Intensity (a.u.)")
        self._ax.set_xlim(380, 1000)
        self._ax.set_ylim(0, 1)
        self._ax.grid(True, alpha=0.3)

        # 填充区域（Polygon，原地更新，blit 友好）
        self._fill = Polygon(
            np.zeros((0, 2)),
            facecolor=(41 / 255, 128 / 255, 185 / 255, 0.2),
            edgecolor="none",
        )
        self._ax.add_patch(self._fill)

        # 主曲线
        (self._line,) = self._ax.plot([380], [0], color="#2980b9", linewidth=2)

        self._artists = [self._fill, self._line]
        self._capture_bg()

    def update_spectrum(
        self, wavelengths: np.ndarray, spectrum: np.ndarray
    ) -> None:
        """更新光谱数据并重绘。"""
        self._line.set_data(wavelengths, spectrum)

        # 更新填充区域
        if len(wavelengths) > 0:
            verts = np.column_stack(
                [
                    np.concatenate([wavelengths, wavelengths[::-1]]),
                    np.concatenate([spectrum, np.zeros_like(spectrum)]),
                ]
            )
            self._fill.set_xy(verts)

        # 自动 Y 范围
        y_max = float(np.max(spectrum)) if len(spectrum) > 0 else 1.0
        if y_max > 0:
            new_ylim = (0, y_max * 1.15)
            if new_ylim != self._ax.get_ylim():
                self._ax.set_ylim(new_ylim)
                self._request_full_redraw()

        self.refresh()
