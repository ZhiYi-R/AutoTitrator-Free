"""滴定计算结果面板。"""

from __future__ import annotations

from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QFont
from PySide6.QtWidgets import (
    QComboBox,
    QDoubleSpinBox,
    QFormLayout,
    QFrame,
    QGroupBox,
    QLabel,
    QProgressBar,
    QVBoxLayout,
    QWidget,
)


class ResultsPanel(QWidget):
    """右侧计算面板：化学计量数输入 + 终点体积/浓度显示 + 进样进度。"""

    electrode_changed = Signal(object)

    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setMaximumWidth(240)

        layout = QVBoxLayout(self)
        layout.setContentsMargins(8, 8, 8, 8)
        layout.setSpacing(12)

        title = QLabel("滴定计算")
        title.setStyleSheet("font-weight: bold; font-size: 13px;")
        layout.addWidget(title)

        # ---- 电极选择 ----
        self._electrode_combo = QComboBox()
        self._electrode_combo.currentIndexChanged.connect(self._on_combo_changed)
        layout.addWidget(self._electrode_combo)

        # ---- 化学计量数 ----
        stoich_group = QGroupBox("化学计量数")
        stoich_form = QFormLayout(stoich_group)
        stoich_form.setSpacing(6)

        self._n_std = QDoubleSpinBox()
        self._n_std.setRange(0.1, 100.0)
        self._n_std.setValue(1.0)
        self._n_std.setSingleStep(0.1)
        self._n_std.setDecimals(1)
        self._n_std.valueChanged.connect(self._recalc)
        stoich_form.addRow("标准液 (n₁):", self._n_std)

        self._n_analyte = QDoubleSpinBox()
        self._n_analyte.setRange(0.1, 100.0)
        self._n_analyte.setValue(1.0)
        self._n_analyte.setSingleStep(0.1)
        self._n_analyte.setDecimals(1)
        self._n_analyte.valueChanged.connect(self._recalc)
        stoich_form.addRow("待测液 (n₂):", self._n_analyte)

        layout.addWidget(stoich_group)

        # ---- 标准液浓度 ----
        conc_group = QGroupBox("标准液浓度")
        conc_form = QFormLayout(conc_group)
        conc_form.setSpacing(6)

        self._c_std = QDoubleSpinBox()
        self._c_std.setRange(0.0001, 100.0)
        self._c_std.setValue(0.1)
        self._c_std.setSingleStep(0.01)
        self._c_std.setDecimals(4)
        self._c_std.valueChanged.connect(self._recalc)
        conc_form.addRow("C₁ (mol/L):", self._c_std)

        layout.addWidget(conc_group)

        # ---- 待测液 ----
        sample_group = QGroupBox("待测液")
        sample_form = QFormLayout(sample_group)
        sample_form.setSpacing(6)

        self._v_sample_label = QLabel("—")
        self._v_sample_label.setFont(QFont("monospace", 10))
        sample_form.addRow("取样体积 (mL):", self._v_sample_label)
        self._v_now_label = QLabel("— V")
        self._v_now_label.setFont(QFont("monospace", 10))
        sample_form.addRow("当前电压:", self._v_now_label)

        layout.addWidget(sample_group)

        # ---- 进样进度 ----
        self._inject_group = QGroupBox("进样进度")
        inject_layout = QVBoxLayout(self._inject_group)
        inject_layout.setContentsMargins(8, 4, 8, 4)
        self._inject_bar = QProgressBar()
        self._inject_bar.setRange(0, 100)
        self._inject_bar.setValue(0)
        self._inject_bar.setTextVisible(True)
        self._inject_bar.setFormat("等待开始")
        inject_layout.addWidget(self._inject_bar)
        self._eta_label = QLabel("")
        self._eta_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self._eta_label.setStyleSheet("font-size: 11px;")
        inject_layout.addWidget(self._eta_label)
        self._inject_group.setVisible(False)
        layout.addWidget(self._inject_group)

        # ---- 分隔 ----
        sep = QFrame()
        sep.setFrameShape(QFrame.Shape.HLine)
        sep.setFrameShadow(QFrame.Shadow.Sunken)
        layout.addWidget(sep)

        # ---- 结果 ----
        result_group = QGroupBox("结果")
        result_form = QFormLayout(result_group)
        result_form.setSpacing(6)

        self._v_ep_label = QLabel("—")
        self._v_ep_label.setFont(QFont("monospace", 10))
        self._v_ep_label.setStyleSheet("color: #e67e22; font-weight: bold;")
        result_form.addRow("终点体积 (mL):", self._v_ep_label)

        self._c_x_label = QLabel("—")
        self._c_x_label.setFont(QFont("monospace", 11, QFont.Weight.Bold))
        self._c_x_label.setStyleSheet("color: #27ae60; font-weight: bold;")
        result_form.addRow("Cₓ (mol/L):", self._c_x_label)

        layout.addWidget(result_group)

        layout.addStretch()

        # 信号
        self._electrode_data: list = []

        # 内部状态
        self._endpoint_volume: float | None = None
        self._sample_volume: float = 0.0
        self._inject_target: int = 0
        self._inject_target_vol: float = 0.0

    # ---- 公开接口 ----

    def set_electrodes(self, electrode_list: list[tuple]) -> None:
        self._electrode_data = electrode_list
        self._electrode_combo.blockSignals(True)
        self._electrode_combo.clear()
        self._electrode_combo.addItem("Raw Potential (V)", None)
        for name, slope, intercept, unit in electrode_list:
            self._electrode_combo.addItem(f"{name} ({unit})",
                                          (name, slope, intercept, unit))
        self._electrode_combo.blockSignals(False)

    def _on_combo_changed(self, idx: int) -> None:
        data = self._electrode_combo.itemData(idx)
        self.electrode_changed.emit(data)

    def set_sample_volume(self, vol: float) -> None:
        self._sample_volume = vol
        self._v_sample_label.setText(f"{vol:.2f}")
        self._recalc()

    def set_endpoint(self, volume: float) -> None:
        self._endpoint_volume = volume
        self._v_ep_label.setText(f"{volume:.4f}")
        self._recalc()

    def reset_endpoint(self) -> None:
        self._endpoint_volume = None
        self._v_ep_label.setText("—")
        self._c_x_label.setText("—")

    def set_current_voltage(self, v: float) -> None:
        self._v_now_label.setText(f"{v:.4f} V")

    # ---- 进样进度 ----

    def show_inject_progress(self, target_steps: int, target_vol: float = 0.0) -> None:
        self._inject_target = target_steps
        self._inject_target_vol = target_vol
        self._inject_bar.setValue(0)
        self._inject_bar.setFormat(f"0.000 / {target_vol:.3f} mL")
        self._eta_label.setText("")
        self._inject_group.setVisible(True)
    def update_inject_progress(self, pos: int, volume: float = 0.0) -> None:
        if self._inject_target <= 0:
            return
        pct = min(100, int(pos * 100 / self._inject_target))
        self._inject_bar.setValue(pct)
        tv = self._inject_target_vol
        remaining = max(0, self._inject_target - pos)
        eta_sec = remaining // 1000
        if pct < 100 and remaining > 0:
            self._inject_bar.setFormat(f"{volume:.3f} / {tv:.3f} mL  ({pct}%)")
            self._eta_label.setText(f"ETA {eta_sec // 60:02d}:{eta_sec % 60:02d}")
        else:
            self._inject_bar.setFormat("进样完成 \u2713")
            self._eta_label.setText("")

    def hide_inject_progress(self) -> None:
        self._eta_label.setText("")
        self._inject_group.setVisible(False)
        self._inject_bar.setValue(0)
        self._inject_bar.setFormat("等待开始")

    # ---- 内部 ----

    def _recalc(self) -> None:
        if self._endpoint_volume is None or self._endpoint_volume <= 0:
            self._c_x_label.setText("—")
            return
        V_ep = self._endpoint_volume
        V_sample = self._sample_volume
        if V_sample <= 0:
            self._c_x_label.setText("—")
            return

        n_std = self._n_std.value()
        n_analyte = self._n_analyte.value()
        C_std = self._c_std.value()

        Cx = (C_std * V_ep * n_analyte) / (V_sample * n_std)
        self._c_x_label.setText(f"{Cx:.6f}")


__all__ = ["ResultsPanel"]
