"""电位–体积/滴定度实时曲线（在线 EWMA 滤波，matplotlib blit 加速）。"""

from __future__ import annotations

import tkinter as tk

import numpy as np
import ttkbootstrap as ttk
from DataProcessor import PUMP_SLOPE
from matplotlib.colors import to_rgb
from matplotlib.patches import Polygon

from gui import i18n, themes
from gui._plot import _BlitPlot

VREF = 3.3
ADC_MAX = 65535
ELECTRODE_OFFSET = 1.1

_FILL_ALPHA = 0.14


class _EWMA:
    """因果指数移动平均。"""

    __slots__ = ("_a", "_v")

    def __init__(self, alpha: float = 0.15) -> None:
        self._a = alpha
        self._v: float | None = None

    def __call__(self, x: float) -> float:
        if self._v is None:
            self._v = float(x)
        else:
            self._v = self._a * float(x) + (1.0 - self._a) * self._v
        return self._v

    def reset(self) -> None:
        self._v = None

    @property
    def value(self) -> float | None:
        return self._v


class PotentialWidget(_BlitPlot):
    """电位–体积/滴定度曲线（在线 EWMA 平滑）。"""

    def __init__(self, parent: tk.Misc, **kwargs) -> None:
        super().__init__(parent, title=i18n.tr("plot.potential"), **kwargs)

        self._titrating = False
        self._times: list[float] = []
        self._volts_raw: list[float] = []
        self._volts_sm: list[float] = []
        self._volumes: list[float] = []
        self._endpoint_volume: float | None = None
        self._cal_unit: str | None = None
        self._cal_slope: float | None = None
        self._cal_intercept: float | None = None
        self._endpoint_line = None

        self._ewma = _EWMA(0.15)

        # ── 顶部控制栏 ───────────────────────────────────────────────
        self._canvas.get_tk_widget().pack_forget()
        top = ttk.Frame(self)
        top.pack(fill="x", padx=8, pady=(4, 0))

        self._alpha_label = ttk.Label(top, text=i18n.tr("plot.alpha"))
        self._alpha_label.pack(side="left")

        self._alpha_var = tk.StringVar(value="0.15")
        self._alpha_spin = ttk.Spinbox(
            top,
            from_=0.01,
            to=1.0,
            increment=0.05,
            textvariable=self._alpha_var,
            width=5,
            format="%.2f",
            command=self._on_alpha_changed,
        )
        self._alpha_spin.pack(side="left", padx=(4, 8))

        self._info_label = ttk.Label(top, text="", style="Muted.TLabel")
        self._info_label.pack(side="left")

        # ── 绘图区 ───────────────────────────────────────────────────
        self._canvas.get_tk_widget().pack(fill="both", expand=True)
        self._set_xlabel(i18n.tr("plot.time"))
        self._set_ylabel(i18n.tr("plot.potential_v"))
        self._ax.set_xlim(0, 60)
        self._ax.set_ylim(-0.5, 1.5)
        self._ax.grid(True, alpha=0.25)

        # 平滑后主曲线
        t = themes.current_tokens()
        (self._sm_curve,) = self._ax.plot(
            [], [], color=t.plot_potential, linewidth=1.5
        )

        # 填充区域
        self._fill = Polygon(
            np.zeros((0, 2)),
            facecolor=self._fill_color(),
            edgecolor="none",
        )
        self._ax.add_patch(self._fill)

        self._artists = [self._fill, self._sm_curve]
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
        return (*to_rgb(t.plot_potential), _FILL_ALPHA)

    def _apply_i18n(self) -> None:
        self._alpha_label.config(text=i18n.tr("plot.alpha"))
        if self._overlay_visible and self._overlay_key:
            self._overlay.config(text=i18n.tr(self._overlay_key))
        # refresh 内部会通过 _set_title/_set_xlabel/_set_ylabel 缓存写入
        self.refresh()

    def _apply_theme(self) -> None:
        t = themes.current_tokens()
        self._sm_curve.set_color(t.plot_potential)
        self._fill.set_facecolor(self._fill_color())
        if self._endpoint_line is not None:
            self._endpoint_line.set_color(t.plot_endpoint)
        self._request_full_redraw()
        self.refresh()

    # ── 控制 ────────────────────────────────────────────────────────

    def _on_alpha_changed(self) -> None:
        try:
            a = float(self._alpha_var.get())
        except ValueError:
            return
        self._ewma = _EWMA(a)
        # 重算全部历史
        self._volts_sm.clear()
        for v in self._volts_raw:
            self._volts_sm.append(self._ewma(v))
        self._info_label.config(text=f"α={a:.2f}")

    # ── 数据馈入 ────────────────────────────────────────────────────

    def append(self, t: float, adc_raw: int, volume: float | None = None) -> None:
        v = adc_raw * VREF / ADC_MAX - ELECTRODE_OFFSET
        self.hide_overlay()  # 有数据后移除空状态提示
        self._times.append(t)
        self._volts_raw.append(v)
        self._volts_sm.append(self._ewma(v))
        self._volumes.append(volume if volume is not None else t * PUMP_SLOPE * 1000)

    # ── 状态 ────────────────────────────────────────────────────────

    def set_titrating(self, on: bool) -> None:
        self._titrating = on
        if on:
            self._endpoint_volume = None

    def set_calibration(self, unit: str, slope: float, intercept: float) -> None:
        self._cal_unit = unit
        self._cal_slope = slope
        self._cal_intercept = intercept

    def clear_calibration(self) -> None:
        self._cal_unit = None
        self._cal_slope = None
        self._cal_intercept = None

    def set_endpoint(self, volume: float) -> None:
        self._endpoint_volume = volume
        if self._endpoint_line is not None:
            self._endpoint_line.remove()
            self._endpoint_line = None
        t = themes.current_tokens()
        self._endpoint_line = self._ax.axvline(
            x=1.0 if volume > 0 else 0,
            color=t.plot_endpoint,
            linewidth=2,
            linestyle="--",
        )
        self._set_xlabel(i18n.tr("plot.degree"))
        self._ax.set_xlim(0, 2.5)
        if self._endpoint_line not in self._artists:
            self._artists.append(self._endpoint_line)
        self._request_full_redraw()

    # ── 刷新 ────────────────────────────────────────────────────────

    def refresh(self) -> None:
        # 标题和 Y 轴标签（缓存写入，仅变化时触发 full redraw）
        if self._cal_slope is not None:
            unit = self._cal_unit or "pX"
            self._set_title(i18n.tr("plot.px", unit=unit))
            self._set_ylabel(unit)
        else:
            self._set_title(i18n.tr("plot.potential"))
            self._set_ylabel(i18n.tr("plot.potential_v"))

        # X 轴标签
        if self._endpoint_volume is not None and self._endpoint_volume > 0:
            self._set_xlabel(i18n.tr("plot.degree"))
        else:
            self._set_xlabel(i18n.tr("plot.time"))

        if not self._times:
            self._sm_curve.set_data([], [])
            # 空数据：仅在首次或校准状态变化时全量重绘，避免未连接时
            # 每 80ms 都 canvas.draw()（原实现每帧 _request_full_redraw）
            target_ylim = (0, 14) if self._cal_slope is not None else (-0.5, 1.5)
            if tuple(self._ax.get_ylim()) != target_ylim:
                self._ax.set_ylim(target_ylim)
                self._request_full_redraw()
            self._blit()
            return

        # 计算 x
        if self._endpoint_volume is not None and self._endpoint_volume > 0:
            x_vals = [v / self._endpoint_volume for v in self._volumes]
        elif self._titrating:
            x_vals = list(self._volumes)
            self._set_xlabel(i18n.tr("plot.volume"))
        else:
            x_vals = list(self._times)

        # 平滑值
        if self._cal_slope is not None:
            assert self._cal_intercept is not None
            y_sm = [
                self._cal_intercept + self._cal_slope * v * 1000.0
                for v in self._volts_sm
            ]
        else:
            y_sm = self._volts_sm

        self._sm_curve.set_data(x_vals, y_sm)

        # 更新填充区域
        if len(x_vals) > 0:
            verts = np.column_stack(
                [
                    np.concatenate([x_vals, x_vals[::-1]]),
                    np.concatenate([y_sm, np.zeros_like(y_sm)]),
                ]
            )
            self._fill.set_xy(verts)

        # Y 范围（整数对齐量化，减少 full redraw 触发频率）
        if len(y_sm) > 0:
            y_min = min(y_sm)
            y_max = max(y_sm)
            if y_max > y_min:
                padding = max(0.1, (y_max - y_min) * 0.15)
                # 量化到 0.1 精度：数据小幅波动不再触发 set_ylim
                new_ylim = (
                    round(y_min - padding, 1),
                    round(y_max + padding, 1),
                )
                if new_ylim != tuple(self._ax.get_ylim()):
                    self._ax.set_ylim(new_ylim)
                    self._request_full_redraw()

        # X 范围（整数对齐量化）
        if len(x_vals) > 0:
            x_max = max(x_vals) * 1.15
            if self._endpoint_volume is not None and self._endpoint_volume > 0:
                x_max = max(x_max, 1.0)
            else:
                x_max = max(x_max, 0.5)
            # 量化到 0.5 精度：滴定中体积缓慢增长，不再每帧触发 set_xlim
            new_xlim = (0, round(x_max * 2) / 2)
            if new_xlim != tuple(self._ax.get_xlim()):
                self._ax.set_xlim(new_xlim)
                self._request_full_redraw()

        self._blit()

    def reset(self) -> None:
        self._times.clear()
        self._volts_raw.clear()
        self._volts_sm.clear()
        self._volumes.clear()
        self._ewma.reset()
        self._endpoint_volume = None
        if self._endpoint_line is not None:
            self._endpoint_line.remove()
            self._endpoint_line = None
            if self._endpoint_line in self._artists:
                self._artists.remove(self._endpoint_line)
        self._set_xlabel(i18n.tr("plot.time"))
        self._ax.set_xlim(0, 5)
        self._sm_curve.set_data([], [])
        self._request_full_redraw()

    def shutdown(self) -> None:
        pass


__all__ = ["PotentialWidget"]
