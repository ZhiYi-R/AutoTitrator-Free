"""实时光谱曲线控件（matplotlib blit 加速，i18n + 主题感知）。"""

from __future__ import annotations

import tkinter as tk

import numpy as np
from matplotlib.colors import to_rgb
from matplotlib.patches import Polygon

from gui import i18n, themes
from gui._plot import _BlitPlot

_FILL_ALPHA = 0.18


class SpectrumWidget(_BlitPlot):
    """AS7341 全光谱实时曲线 (380–1100 nm)。"""

    def __init__(self, parent: tk.Misc, **kwargs) -> None:
        super().__init__(parent, title=i18n.tr("plot.spectrum"), **kwargs)

        self._set_xlabel(i18n.tr("plot.wavelength"))
        self._set_ylabel(i18n.tr("plot.intensity"))
        self._ax.set_xlim(380, 1000)
        self._ax.set_ylim(0, 1)
        self._ax.grid(True, alpha=0.25)

        # 填充区域（Polygon，原地更新，blit 友好）
        self._fill = Polygon(
            np.zeros((0, 2)),
            facecolor=self._fill_color(),
            edgecolor="none",
        )
        self._ax.add_patch(self._fill)

        # 主曲线
        t = themes.current_tokens()
        (self._line,) = self._ax.plot(
            [380], [0], color=t.plot_spectrum, linewidth=2
        )

        self._artists = [self._fill, self._line]
        self._capture_bg()

        self._overlay_key: str | None = None
        i18n.subscribe(self._apply_i18n)
        themes.subscribe(self._apply_theme)

    # ── 空状态覆盖层 ───────────────────────────────────────

    def set_overlay(self, key: str | None) -> None:
        """按 i18n key 设置/清除空状态提示。"""
        self._overlay_key = key
        if key is None:
            self.hide_overlay()
        else:
            self.show_overlay(i18n.tr(key))

    # ── 主题 / 语言 ────────────────────────────────────────────

    @staticmethod
    def _fill_color() -> tuple:
        t = themes.current_tokens()
        return (*to_rgb(t.plot_spectrum), _FILL_ALPHA)

    def _apply_i18n(self) -> None:
        self._set_title(i18n.tr("plot.spectrum"))
        self._set_xlabel(i18n.tr("plot.wavelength"))
        self._set_ylabel(i18n.tr("plot.intensity"))
        self.refresh()
        if self._overlay_visible and self._overlay_key:
            self._overlay.config(text=i18n.tr(self._overlay_key))

    def _apply_theme(self) -> None:
        t = themes.current_tokens()
        self._line.set_color(t.plot_spectrum)
        self._fill.set_facecolor(self._fill_color())
        self._request_full_redraw()
        self.refresh()

    # ── 数据馈入 ───────────────────────────────────────────────

    def update_spectrum(
        self, wavelengths: np.ndarray, spectrum: np.ndarray
    ) -> None:
        """更新光谱数据并重绘。"""
        self.hide_overlay()  # 有数据后移除空状态提示
        self._line.set_data(wavelengths, spectrum)

        if len(wavelengths) > 0:
            verts = np.column_stack(
                [
                    np.concatenate([wavelengths, wavelengths[::-1]]),
                    np.concatenate([spectrum, np.zeros_like(spectrum)]),
                ]
            )
            self._fill.set_xy(verts)

        # 自动 Y 范围（量化到 0.05 精度，减少 full redraw 频率）
        y_max = float(np.max(spectrum)) if len(spectrum) > 0 else 1.0
        if y_max > 0:
            new_ylim = (0, round(y_max * 1.15 / 0.05) * 0.05)
            if new_ylim != tuple(self._ax.get_ylim()):
                self._ax.set_ylim(new_ylim)
                self._request_full_redraw()

        self.refresh()


__all__ = ["SpectrumWidget"]
