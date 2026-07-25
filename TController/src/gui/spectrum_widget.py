"""实时光谱曲线控件。"""

from __future__ import annotations

import numpy as np
import pyqtgraph as pg
from PySide6.QtCore import Qt
from PySide6.QtGui import QColor
from PySide6.QtWidgets import QVBoxLayout, QWidget


class SpectrumWidget(QWidget):
    """AS7341 全光谱实时曲线 (380–1100 nm)。"""

    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setLayout(QVBoxLayout())
        self.layout().setContentsMargins(0, 0, 0, 0)

        self._plot = pg.PlotWidget(title="实时光谱 / Spectrum")
        self._plot.setLabel("bottom", "Wavelength", "nm")
        self._plot.setLabel("left", "Intensity", "a.u.")
        self._plot.getAxis("bottom").enableAutoSIPrefix(False)
        self._plot.getAxis("left").enableAutoSIPrefix(False)
        self._plot.showGrid(x=True, y=True, alpha=0.3)
        self._plot.setXRange(380, 1000)
        self._plot.setYRange(0, 1)
        self._plot.addLegend(offset=(10, 10))

        self._curve = pg.PlotDataItem(
            x=[380],
            y=[0],
            name="Spectrum",
            pen=pg.mkPen(QColor("#2980b9"), width=2),
            fillLevel=0,
            brush=QColor(41, 128, 185, 50),
        )
        self._plot.addItem(self._curve)
        self.layout().addWidget(self._plot)

    def update_spectrum(self, wavelengths: np.ndarray, spectrum: np.ndarray) -> None:
        self._curve.setData(x=wavelengths, y=spectrum)
        y_max = float(np.max(spectrum)) if len(spectrum) > 0 else 1.0
        if y_max > 0:
            self._plot.setYRange(0, y_max * 1.15)
