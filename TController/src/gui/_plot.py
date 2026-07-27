"""matplotlib blit 加速绘图基类。

提供 _BlitPlot，封装 FigureCanvasTkAgg + blit 逻辑，
供 SpectrumWidget / PotentialWidget / 校准曲线复用。
"""

from __future__ import annotations

import tkinter as tk

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure


class _BlitPlot(tk.Frame):
    """matplotlib blit 加速绘图基类。

    blit 流程：
      1. 首帧或坐标轴变化时：canvas.draw() + copy_from_bbox() 捕获背景
      2. 后续帧：restore_region(bg) + draw_artist(artists) + blit()
    """

    def __init__(self, parent: tk.Misc, title: str = "", **kwargs) -> None:
        super().__init__(parent, **kwargs)

        self._fig = Figure(figsize=(5, 3), dpi=100)
        self._ax = self._fig.add_subplot(111)
        self._ax.set_title(title)
        self._canvas = FigureCanvasTkAgg(self._fig, master=self)
        self._canvas.get_tk_widget().pack(fill="both", expand=True)

        self._bg = None
        self._artists: list = []
        self._needs_full_redraw = True

    def _capture_bg(self) -> None:
        """捕获背景（坐标轴/网格/标签/标题）。"""
        self._canvas.draw()
        self._bg = self._canvas.copy_from_bbox(self._ax.bbox)

    def _blit(self) -> None:
        """恢复背景 + 重绘 artist + blit 到屏幕。"""
        if self._bg is None or self._needs_full_redraw:
            self._capture_bg()
            self._needs_full_redraw = False
        self._canvas.restore_region(self._bg)
        for a in self._artists:
            self._ax.draw_artist(a)
        self._canvas.blit(self._ax.bbox)

    def _request_full_redraw(self) -> None:
        """标记需要全量重绘（坐标轴范围/标签变化时调用）。"""
        self._needs_full_redraw = True

    def refresh(self) -> None:
        """子类实现：更新数据 → 调用 _blit()。"""
        self._blit()
