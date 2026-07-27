"""电位–体积/滴定度实时曲线（含在线 EWMA 滤波）。"""

from __future__ import annotations

import pyqtgraph as pg
from DataProcessor import PUMP_SLOPE
from PySide6.QtCore import Qt
from PySide6.QtGui import QColor
from PySide6.QtWidgets import (
    QDoubleSpinBox,
    QHBoxLayout,
    QLabel,
    QVBoxLayout,
    QWidget,
)

VREF = 3.3
ADC_MAX = 65535
ELECTRODE_OFFSET = 1.1


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


class PotentialWidget(QWidget):
    """电位–体积/滴定度曲线（在线 EWMA 平滑）。"""

    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self._titrating = False
        self._times: list[float] = []
        self._volts_raw: list[float] = []  # 原始值
        self._volts_sm: list[float] = []  # EWMA 平滑值
        self._volumes: list[float] = []
        self._endpoint_volume: float | None = None
        self._cal_unit: str | None = None
        self._cal_slope: float | None = None
        self._cal_intercept: float | None = None
        self._endpoint_line: pg.InfiniteLine | None = None

        self._ewma = _EWMA(0.15)  # 可调 alpha

        self.setLayout(QVBoxLayout())
        self.layout().setContentsMargins(0, 0, 0, 0)

        # ── 顶部控制栏 ───────────────────────────────────────────────
        top = QHBoxLayout()
        top.setContentsMargins(8, 4, 8, 0)
        top.addWidget(QLabel("平滑 α:"))
        self._alpha_spin = QDoubleSpinBox()
        self._alpha_spin.setRange(0.01, 1.0)
        self._alpha_spin.setSingleStep(0.05)
        self._alpha_spin.setDecimals(2)
        self._alpha_spin.setValue(0.15)
        self._alpha_spin.valueChanged.connect(self._on_alpha_changed)
        self._alpha_spin.setToolTip("EWMA 平滑系数，越大越跟随原始数据")
        top.addWidget(self._alpha_spin)
        top.addStretch()
        self._info_label = QLabel("")
        self._info_label.setStyleSheet("color: #7f8c8d; font-size: 11px;")
        top.addWidget(self._info_label)

        tw = QWidget()
        tw.setLayout(top)
        self.layout().addWidget(tw)

        # ── 绘图 ─────────────────────────────────────────────────────
        self._plot = pg.PlotWidget(title="电位–体积 / Potential–Volume")
        self._plot.setLabel("bottom", "Time", "s")
        self._plot.setLabel("left", "Potential", "V")
        self._plot.getAxis("bottom").enableAutoSIPrefix(False)
        self._plot.getAxis("left").enableAutoSIPrefix(False)
        self._plot.showGrid(x=True, y=True, alpha=0.3)
        self._plot.setXRange(0, 60)
        self._plot.setYRange(-0.5, 1.5)
        self._plot.addLegend(offset=(10, 10))

        # 平滑后（主曲线）
        self._sm_curve = pg.PlotDataItem(
            x=[],
            y=[],
            name="Filtered",
            pen=pg.mkPen(QColor("#27ae60"), width=1.5),
            fillLevel=0,
            brush=QColor(39, 174, 96, 40),
        )
        self._plot.addItem(self._sm_curve)

        self.layout().addWidget(self._plot)

    # ── 控制 ────────────────────────────────────────────────────────

    def _on_alpha_changed(self, a: float) -> None:
        self._ewma = _EWMA(a)
        # 重算全部历史
        self._volts_sm.clear()
        for v in self._volts_raw:
            self._volts_sm.append(self._ewma(v))
        self._info_label.setText(f"α={a:.2f}")

    # ── 数据馈入 ────────────────────────────────────────────────────

    def append(self, t: float, adc_raw: int, volume: float | None = None) -> None:
        v = adc_raw * VREF / ADC_MAX - ELECTRODE_OFFSET
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
            self._plot.removeItem(self._endpoint_line)
        self._endpoint_line = pg.InfiniteLine(
            pos=1.0 if volume > 0 else 0,
            angle=90,
            pen=pg.mkPen(QColor("#e74c3c"), width=2, style=Qt.PenStyle.DashLine),
            label="T=1",
        )
        self._plot.addItem(self._endpoint_line)
        self._plot.setLabel("bottom", "Titration degree", "T")
        self._plot.setXRange(0, 2.5)

    # ── 刷新 ────────────────────────────────────────────────────────

    def refresh(self) -> None:
        if self._cal_slope is not None:
            unit = self._cal_unit or "pX"
            self._plot.setTitle(f"{unit}–体积 / {unit}–Volume")
            self._plot.setLabel("left", self._cal_unit or "pX", "")
        else:
            self._plot.setTitle("电位–体积 / Potential–Volume")
            self._plot.setLabel("left", "Potential", "V")

        if self._endpoint_volume is not None and self._endpoint_volume > 0:
            self._plot.setLabel("bottom", "Titration degree", "T")
        else:
            self._plot.setLabel("bottom", "Time", "s")

        if not self._times:
            self._sm_curve.setData(x=[], y=[])
            if self._cal_slope is not None:
                self._plot.setYRange(0, 14)
            else:
                self._plot.setYRange(-0.5, 1.5)
            return

        # 计算 x
        if self._endpoint_volume is not None and self._endpoint_volume > 0:
            x_vals = [v / self._endpoint_volume for v in self._volumes]
        elif self._titrating:
            x_vals = list(self._volumes)
            self._plot.setLabel("bottom", "Volume", "mL")
        else:
            x_vals = list(self._times)
            self._plot.setLabel("bottom", "Time", "s")

        # 平滑值
        if self._cal_slope is not None:
            assert self._cal_intercept is not None
            y_sm = [
                self._cal_intercept + self._cal_slope * v * 1000.0
                for v in self._volts_sm
            ]
        else:
            y_sm = self._volts_sm
        self._sm_curve.setData(x=x_vals, y=y_sm)

        # Y 范围（基于平滑值）
        if len(y_sm) > 0:
            y_min = min(y_sm)
            y_max = max(y_sm)
            if y_max > y_min:
                padding = max(0.1, (y_max - y_min) * 0.15)
                self._plot.setYRange(y_min - padding, y_max + padding)

        # X 范围
        if len(x_vals) > 0:
            x_max = max(x_vals) * 1.15
            if self._endpoint_volume is not None and self._endpoint_volume > 0:
                x_max = max(x_max, 1.0)
            else:
                x_max = max(x_max, 0.5)
            self._plot.setXRange(0, x_max)

    def reset(self) -> None:
        self._times.clear()
        self._volts_raw.clear()
        self._volts_sm.clear()
        self._volumes.clear()
        self._ewma.reset()
        self._endpoint_volume = None
        if self._endpoint_line is not None:
            self._plot.removeItem(self._endpoint_line)
            self._endpoint_line = None
        self._plot.setLabel("bottom", "Time", "s")
        self._plot.setXRange(0, 5)
        self._sm_curve.setData(x=[], y=[])

    def shutdown(self) -> None:
        pass
