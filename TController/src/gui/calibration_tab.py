"""校准选项卡 — 泵校准 + pH 电极校准。"""

from __future__ import annotations

import os

import numpy as np
import pyqtgraph as pg
from Communication import ProtocolHandler
from DataProcessor._path import CALIBRE_PATH
from PySide6.QtCore import Qt, QTimer
from PySide6.QtGui import QColor
from PySide6.QtWidgets import (
    QAbstractItemView,
    QComboBox,
    QDoubleSpinBox,
    QHBoxLayout,
    QInputDialog,
    QLabel,
    QLineEdit,
    QPushButton,
    QTableWidget,
    QTableWidgetItem,
    QTabWidget,
    QVBoxLayout,
    QWidget,
)

DATA_DIR = os.path.dirname(CALIBRE_PATH)
os.makedirs(DATA_DIR, exist_ok=True)


# ======================================================================
#  工具：线性回归
# ======================================================================


def _linreg(x: np.ndarray, y: np.ndarray) -> tuple[float, float, float]:
    """(slope, intercept, r²) — 普通线性回归。"""
    n = len(x)
    sx, sy = x.sum(), y.sum()
    sxx = (x * x).sum()
    sxy = (x * y).sum()
    slope = (n * sxy - sx * sy) / (n * sxx - sx * sx + 1e-12)
    intercept = (sy - slope * sx) / n
    y_pred = slope * x + intercept
    ss_res = ((y - y_pred) ** 2).sum()
    ss_tot = ((y - y.mean()) ** 2).sum()
    r2 = 1.0 - ss_res / (ss_tot + 1e-12)
    return slope, intercept, r2


def _linreg_origin(x: np.ndarray, y: np.ndarray) -> tuple[float, float]:
    """过原点回归: V = slope × 脉冲, 返回 (slope, r²)。"""
    slope = (x * y).sum() / (x * x).sum()
    y_pred = slope * x
    ss_res = ((y - y_pred) ** 2).sum()
    ss_tot = ((y - y.mean()) ** 2).sum()
    r2 = 1.0 - ss_res / (ss_tot + 1e-12)
    return slope, r2


# ======================================================================
#  泵校准面板
# ======================================================================


class PumpCalibWidget(QWidget):
    """单泵校准面板：点动 10000 脉冲 → 输入质量 → 记录 → 拟合。"""

    def __init__(
        self, pump_id: int, com: ProtocolHandler, parent: QWidget | None = None
    ) -> None:
        super().__init__(parent)
        self._pump_id = pump_id
        self._com = com
        self._points: list[tuple[int, float]] = []  # (pulses, volume_mL)

        self.setLayout(QVBoxLayout())
        self.layout().setContentsMargins(8, 8, 8, 8)

        # ---- 操作区 ----
        ctrl = QHBoxLayout()
        self._jog_btn = QPushButton("点动 10000 脉冲")
        self._jog_btn.clicked.connect(self._jog)
        ctrl.addWidget(self._jog_btn)

        ctrl.addWidget(QLabel("体积 (mL):"))
        self._vol_input = QDoubleSpinBox()
        self._vol_input.setRange(0, 999)
        self._vol_input.setDecimals(6)
        self._vol_input.setSingleStep(0.01)
        self._vol_input.setValue(0)
        ctrl.addWidget(self._vol_input)

        self._record_btn = QPushButton("记录")
        self._record_btn.clicked.connect(self._record)
        ctrl.addWidget(self._record_btn)

        self._undo_btn = QPushButton("撤销最后")
        self._undo_btn.clicked.connect(self._undo)
        ctrl.addWidget(self._undo_btn)

        self._clear_btn = QPushButton("清空")
        self._clear_btn.clicked.connect(self._clear_points)
        ctrl.addWidget(self._clear_btn)

        ctrl.addStretch()
        self.layout().addLayout(ctrl)

        # ---- 状态 ----
        self._status_label = QLabel("就绪")
        self.layout().addWidget(self._status_label)

        # ---- 数据表 ----
        self._table = QTableWidget(0, 3)
        self._table.setHorizontalHeaderLabels(["#", "脉冲数", "体积 (mL)"])
        self._table.horizontalHeader().setStretchLastSection(True)
        self._table.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers)
        self._table.setSelectionBehavior(QAbstractItemView.SelectionBehavior.SelectRows)
        self.layout().addWidget(self._table, 2)

        # ---- 校准曲线图 ----
        self._plot = pg.PlotWidget(title=f"泵 {pump_id} 校准曲线")
        self._plot.setLabel("bottom", "Pulse", "")
        self._plot.setLabel("left", "Volume", "mL")
        self._plot.showGrid(x=True, y=True, alpha=0.3)
        self._scatter = pg.ScatterPlotItem(pxMode=True, brush=QColor("#2980b9"), size=8)
        self._plot.addItem(self._scatter)
        self._fit_line = pg.PlotDataItem(pen=pg.mkPen(QColor("#e74c3c"), width=2))
        self._plot.addItem(self._fit_line)
        self.layout().addWidget(self._plot, 1)

        # ---- 校准结果 ----
        self._result_label = QLabel("尚未拟合")
        self._result_label.setStyleSheet("font-weight: bold;")
        self.layout().addWidget(self._result_label)

        # ---- 保存 ----
        save_row = QHBoxLayout()
        self._save_btn = QPushButton("保存校准")
        self._save_btn.clicked.connect(self._save)
        save_row.addWidget(self._save_btn)
        save_row.addStretch()
        self.layout().addLayout(save_row)

        # 加载已有数据
        self._load()
        self._update_table()
        self._update_plot()

    # ---- 操作 ----

    def _jog(self) -> None:
        if not self._com.is_open:
            self._status_label.setText("串口未连接")
            return
        self._jog_btn.setEnabled(False)
        self._status_label.setText("泵运行中…")
        self._com.pump_done.connect(
            self._on_jog_done, Qt.ConnectionType.SingleShotConnection
        )
        self._com.send_maxcount(self._pump_id, 10000)
        # 超时保护
        QTimer.singleShot(5000, lambda: self._jog_btn.setEnabled(True))

    def _on_jog_done(self, position: int) -> None:
        self._jog_btn.setEnabled(True)
        self._status_label.setText(f"点动完成，当前位置: {position} 脉冲，请输入体积")

    def _record(self) -> None:
        vol = self._vol_input.value()
        if vol <= 0:
            self._status_label.setText("体积必须大于 0")
            return
        # 累计脉冲数：上一点 + 10000，若无则从 10000 开始
        total_pulses = (self._points[-1][0] + 10000) if self._points else 10000
        self._points.append((total_pulses, vol))
        self._update_table()
        self._update_plot()
        self._vol_input.setValue(0)
        self._status_label.setText(
            f"记录 ({len(self._points)}): {total_pulses} 脉冲 → {vol:.6f} mL"
        )

    def _undo(self) -> None:
        if self._points:
            self._points.pop()
            self._update_table()
            self._update_plot()
            self._status_label.setText(f"撤销，剩余 {len(self._points)} 点")

    def _clear_points(self) -> None:
        self._points.clear()
        self._update_table()
        self._update_plot()
        self._result_label.setText("尚未拟合")
        self._status_label.setText("已清空")

    # ---- 显示 ----

    def _update_table(self) -> None:
        self._table.setRowCount(len(self._points))
        for i, (pulses, vol) in enumerate(self._points):
            self._table.setItem(i, 0, QTableWidgetItem(str(i + 1)))
            self._table.setItem(i, 1, QTableWidgetItem(str(pulses)))
            self._table.setItem(i, 2, QTableWidgetItem(f"{vol:.6f}"))

    def _update_plot(self) -> None:
        if len(self._points) < 2:
            self._scatter.setData([])
            self._fit_line.setData([])
            self._result_label.setText("至少需要 2 个点")
            return
        xs = np.array([p for p, _ in self._points], dtype=np.float64)
        ys = np.array([v for _, v in self._points], dtype=np.float64)
        self._scatter.setData(x=xs, y=ys)

        slope, r2 = _linreg_origin(xs, ys)
        x_fit = np.linspace(0, xs.max() * 1.05, 200)
        y_fit = slope * x_fit
        self._fit_line.setData(x=x_fit, y=y_fit)

        self._result_label.setText(
            f"V = {slope:.10f} × 脉冲  (R² = {r2:.6f})  |  点数: {len(self._points)}"
        )

    # ---- 保存 / 加载 ----

    def _save_path(self) -> str:
        return os.path.join(DATA_DIR, "calibre.npz")

    def _save(self) -> None:
        if len(self._points) < 2:
            self._status_label.setText("至少需要 2 个点才能保存")
            return
        xs = np.array([p for p, _ in self._points], dtype=np.float64)
        ys = np.array([v for _, v in self._points], dtype=np.float64)
        slope, r2 = _linreg_origin(xs, ys)
        pulses = np.array([p for p, _ in self._points], dtype=np.int32)
        volumes = np.array([v for _, v in self._points], dtype=np.float64)
        path = self._save_path()
        # Load existing, merge with new pump data
        _merge = {}
        if os.path.isfile(path):
            try:
                _old = np.load(path, allow_pickle=True)
                for _k in _old:
                    _merge[_k] = _old[_k]
            except Exception:
                pass
        _p = f"pump{self._pump_id}_"
        _merge[f"{_p}pulses"] = pulses
        _merge[f"{_p}volumes"] = volumes
        _merge[f"{_p}slope"] = slope
        _merge[f"{_p}intercept"] = 0.0
        _merge[f"{_p}r2"] = r2
        np.savez_compressed(path, **_merge)
        self._status_label.setText(f"已保存: {path}")

    def _load(self) -> None:
        path = self._save_path()
        if not os.path.isfile(path):
            return
        try:
            data = np.load(path, allow_pickle=True)
            _p = f"pump{self._pump_id}_"
            if _p + "pulses" in data:
                pulses = data[f"{_p}pulses"]
                volumes = data[f"{_p}volumes"]
                self._points = [(int(p), float(v)) for p, v in zip(pulses, volumes)]
                self._status_label.setText(f"已加载 {len(self._points)} 个校准点")
            else:
                self._status_label.setText("暂无泵校准数据")
        except Exception:
            self._status_label.setText("校准文件读取失败")
        self._update_table()
        self._update_plot()


# ======================================================================
#  电极校准面板
# ======================================================================


class PHCalibWidget(QWidget):
    """电极校准：支持多个电极配置，可命名、设单位(pX)和备注。"""

    def __init__(self, com: ProtocolHandler, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self._com = com
        self._current_mv: float = 0.0
        self._data: dict = self._load_data()

        self.setLayout(QVBoxLayout())
        self.layout().setContentsMargins(8, 8, 8, 8)

        # ---- 电极选择 ----
        sel_row = QHBoxLayout()
        sel_row.addWidget(QLabel("电极:"))
        self._electrode_combo = QComboBox()
        self._electrode_combo.currentIndexChanged.connect(self._on_select)
        sel_row.addWidget(self._electrode_combo)

        self._add_elec_btn = QPushButton("+")
        self._add_elec_btn.setFixedWidth(30)
        self._add_elec_btn.setToolTip("添加电极")
        self._add_elec_btn.clicked.connect(self._add_electrode)
        sel_row.addWidget(self._add_elec_btn)
        self._del_elec_btn = QPushButton("—")
        self._del_elec_btn.setFixedWidth(30)
        self._del_elec_btn.setToolTip("删除当前电极")
        self._del_elec_btn.clicked.connect(self._del_electrode)
        sel_row.addWidget(self._del_elec_btn)
        sel_row.addStretch()
        self.layout().addLayout(sel_row)

        # ---- 属性 ----
        attr_row = QHBoxLayout()
        attr_row.addWidget(QLabel("单位:"))
        self._unit_input = QLineEdit("pH")
        self._unit_input.setMaximumWidth(50)
        self._unit_input.textChanged.connect(self._mark_dirty)
        attr_row.addWidget(self._unit_input)
        attr_row.addWidget(QLabel("备注:"))
        self._notes_input = QLineEdit()
        self._notes_input.textChanged.connect(self._mark_dirty)
        attr_row.addWidget(self._notes_input, 1)
        self.layout().addLayout(attr_row)

        # ---- 实时电压 ----
        live_row = QHBoxLayout()
        live_row.addWidget(QLabel("当前电位:"))
        self._live_label = QLabel("--.-- mV")
        self._live_label.setStyleSheet(
            "font-weight: bold; font-size: 14px; color: #2980b9;"
        )
        live_row.addWidget(self._live_label)
        live_row.addStretch()
        self.layout().addLayout(live_row)

        # ---- 输入区 ----
        input_row = QHBoxLayout()
        input_row.addWidget(QLabel("标准值:"))
        self._val_input = QDoubleSpinBox()
        self._val_input.setRange(-10, 20)
        self._val_input.setDecimals(2)
        self._val_input.setValue(7.00)
        self._val_input.setSingleStep(0.1)
        input_row.addWidget(self._val_input)
        self._confirm_btn = QPushButton("确认记录")
        self._confirm_btn.clicked.connect(self._confirm)
        input_row.addWidget(self._confirm_btn)
        self._undo_btn = QPushButton("撤销")
        self._undo_btn.clicked.connect(self._undo)
        input_row.addWidget(self._undo_btn)
        input_row.addStretch()
        self.layout().addLayout(input_row)

        # ---- 数据表 ----
        self._table = QTableWidget(0, 2)
        self._table.setHorizontalHeaderLabels(["标准值", "电位 (mV)"])
        self._table.horizontalHeader().setStretchLastSection(True)
        self._table.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers)
        self.layout().addWidget(self._table, 1)

        # ---- 拟合结果 ----
        self._result_label = QLabel("尚未校准")
        self._result_label.setStyleSheet("font-weight: bold; font-size: 13px;")
        self.layout().addWidget(self._result_label)

        # ---- 校准曲线图 ----
        self._plot = pg.PlotWidget(title="电极校准曲线")
        self._plot.setLabel("bottom", "Potential", "mV")
        self._plot.setLabel("left", "pX", "")
        self._plot.showGrid(x=True, y=True, alpha=0.3)
        self._scatter = pg.ScatterPlotItem(
            pxMode=True, brush=QColor("#8e44ad"), size=10
        )
        self._plot.addItem(self._scatter)
        self._fit_line = pg.PlotDataItem(pen=pg.mkPen(QColor("#e74c3c"), width=2))
        self._plot.addItem(self._fit_line)
        self.layout().addWidget(self._plot, 1)

        # ---- 保存 ----
        self._save_btn = QPushButton("保存")
        self._save_btn.clicked.connect(self._save)
        self.layout().addWidget(self._save_btn)

        # ---- 连接实时数据 ----
        self._com.adc_data.connect(self._on_adc)
        self._rebuild_combo()
        self._dirty = False

    # ---- 数据文件 ----

    @staticmethod
    def _data_path() -> str:
        return os.path.join(DATA_DIR, "calibre.npz")

    @staticmethod
    def _load_data() -> dict:
        path = PHCalibWidget._data_path()
        result = {"electrodes": {}, "current": ""}
        if not os.path.isfile(path):
            return result
        try:
            data = np.load(path, allow_pickle=True)
            if "n_electrodes" not in data:
                return result
            n = int(data["n_electrodes"])
            names = list(data["names"])
            result["current"] = str(data["current"])
            for i in range(n):
                name = str(names[i])
                pts_vals = data[f"points_vals_{i}"]
                pts_mvs = data[f"points_mvs_{i}"]
                points = [
                    (float(pts_vals[j]), float(pts_mvs[j]))
                    for j in range(len(pts_vals))
                ]
                result["electrodes"][name] = {
                    "unit": str(data[f"unit_{i}"]),
                    "notes": str(data[f"notes_{i}"]),
                    "points": points,
                    "slope": float(data[f"slope_{i}"]),
                    "intercept": float(data[f"intercept_{i}"]),
                    "r2": float(data[f"r2_{i}"]),
                }
        except Exception:
            pass
        return result

    def _save_data(self) -> None:
        path = self._data_path()
        # Load existing pump data, merge with electrode data
        _merge = {}
        if os.path.isfile(path):
            try:
                _old = np.load(path, allow_pickle=True)
                for _k in _old:
                    if (
                        not _k.startswith("n_electrodes")
                        and not _k.startswith("names")
                        and not _k.startswith("current")
                        and not _k.startswith("points_")
                        and not _k.startswith("slope_")
                        and not _k.startswith("intercept_")
                        and not _k.startswith("r2_")
                        and not _k.startswith("unit_")
                        and not _k.startswith("notes_")
                    ):
                        _merge[_k] = _old[_k]
            except Exception:
                pass
        electrodes = self._data.get("electrodes", {})
        names = list(electrodes.keys())
        _merge["n_electrodes"] = np.int32(len(names))
        _merge["names"] = np.array(names, dtype=object)
        _merge["current"] = np.array(self._data.get("current", ""), dtype=object)
        for i, name in enumerate(names):
            e = electrodes[name]
            pts = e.get("points", [])
            _merge[f"points_vals_{i}"] = np.array([p for p, _ in pts], dtype=np.float64)
            _merge[f"points_mvs_{i}"] = np.array([m for _, m in pts], dtype=np.float64)
            _merge[f"slope_{i}"] = np.float64(e.get("slope", 0.0))
            _merge[f"intercept_{i}"] = np.float64(e.get("intercept", 0.0))
            _merge[f"r2_{i}"] = np.float64(e.get("r2", 0.0))
            _merge[f"unit_{i}"] = np.array(e.get("unit", "pX"), dtype=object)
            _merge[f"notes_{i}"] = np.array(e.get("notes", ""), dtype=object)
        np.savez_compressed(path, **_merge)

    # ---- 电极选择 ----

    def _rebuild_combo(self) -> None:
        self._electrode_combo.blockSignals(True)
        self._electrode_combo.clear()
        for name in self._data["electrodes"]:
            self._electrode_combo.addItem(name)
        cur = self._data.get("current", "")
        idx = self._electrode_combo.findText(cur)
        if idx >= 0:
            self._electrode_combo.setCurrentIndex(idx)
        self._electrode_combo.blockSignals(False)
        self._load_current()

    def _on_select(self) -> None:
        name = self._electrode_combo.currentText()
        if name:
            self._data["current"] = name
            self._save_data()
        self._load_current()

    def _load_current(self) -> None:
        name = self._electrode_combo.currentText()
        if not name or name not in self._data["electrodes"]:
            self._table.setRowCount(0)
            self._result_label.setText("尚未校准")
            self._scatter.setData([])
            self._fit_line.setData([])
            return
        e = self._data["electrodes"][name]
        self._unit_input.setText(e.get("unit", "pX"))
        self._notes_input.setText(e.get("notes", ""))
        # 填充表格
        self._table.setRowCount(0)
        for val, mv in e.get("points", []):
            r = self._table.rowCount()
            self._table.insertRow(r)
            self._table.setItem(r, 0, QTableWidgetItem(f"{val:.2f}"))
            self._table.setItem(r, 1, QTableWidgetItem(f"{mv:.1f}"))
        self._recalc()

    # ---- 电极管理 ----

    def _add_electrode(self) -> None:
        name, ok = QInputDialog.getText(self, "添加电极", "电极名称:")
        if not ok or not name.strip():
            return
        name = name.strip()
        if name in self._data["electrodes"]:
            name = f"{name} ({len(self._data['electrodes']) + 1})"
        self._data["electrodes"][name] = {
            "unit": "pX",
            "notes": "",
            "points": [],
            "slope": 0.0,
            "intercept": 0.0,
            "r2": 0.0,
        }
        self._data["current"] = name
        self._rebuild_combo()
        self._save_data()

    def _del_electrode(self) -> None:
        name = self._electrode_combo.currentText()
        if not name or name not in self._data["electrodes"]:
            return
        if len(self._data["electrodes"]) <= 1:
            return  # 至少保留一个
        del self._data["electrodes"][name]
        self._data["current"] = next(iter(self._data["electrodes"].keys()))
        self._rebuild_combo()
        self._save_data()

    # ---- 实时电压 ----

    def _on_adc(self, raw: int, _pump2_pos: int = 0) -> None:
        self._current_mv = (raw * 3300.0 / 65535) - 1100.0
        self._live_label.setText(f"{self._current_mv:.1f} mV")

    # ---- 确认 / 撤销 ----

    def _confirm(self) -> None:
        name = self._electrode_combo.currentText()
        if not name:
            return
        val = self._val_input.value()
        mv = self._current_mv
        r = self._table.rowCount()
        self._table.insertRow(r)
        self._table.setItem(r, 0, QTableWidgetItem(f"{val:.2f}"))
        self._table.setItem(r, 1, QTableWidgetItem(f"{mv:.1f}"))
        self._dirty = True
        self._recalc()

    def _undo(self) -> None:
        if self._table.rowCount() > 0:
            self._table.removeRow(self._table.rowCount() - 1)
            self._dirty = True
            self._recalc()

    # ---- 读取数据 ----

    def _get_points(self) -> tuple[np.ndarray, np.ndarray]:
        mvs, vals = [], []
        for r in range(self._table.rowCount()):
            try:
                val = float(self._table.item(r, 0).text())
                mv = float(self._table.item(r, 1).text())
            except (ValueError, TypeError, AttributeError):
                continue
            vals.append(val)
            mvs.append(mv)
        return np.array(mvs, dtype=np.float64), np.array(vals, dtype=np.float64)

    # ---- 计算 ----

    def _mark_dirty(self) -> None:
        self._dirty = True

    def _recalc(self) -> None:
        mvs, vals = self._get_points()
        unit = self._unit_input.text() or "pX"
        self._plot.setLabel("left", unit, "")
        if len(vals) < 2:
            self._result_label.setText("至少需要 2 个点")
            self._scatter.setData([])
            self._fit_line.setData([])
            return
        slope, intercept, r2 = _linreg(mvs, vals)
        self._result_label.setText(
            f"{unit} = {intercept:.4f} + ({slope:.6f}) × E(mV)  (R² = {r2:.6f})"
        )
        margin = max(20, (mvs.max() - mvs.min()) * 0.2)
        x_fit = np.linspace(mvs.min() - margin, mvs.max() + margin, 200)
        y_fit = slope * x_fit + intercept
        self._fit_line.setData(x=x_fit, y=y_fit)
        self._scatter.setData(x=mvs, y=vals)

    # ---- 保存 ----

    def _save(self) -> None:
        name = self._electrode_combo.currentText()
        if not name:
            return
        self._recalc()
        mvs, vals = self._get_points()
        if len(vals) < 2:
            slope, intercept, r2 = 0.0, 0.0, 0.0
        else:
            slope, intercept, r2 = _linreg(mvs, vals)
        self._data["electrodes"][name] = {
            "unit": self._unit_input.text(),
            "notes": self._notes_input.text(),
            "points": [(float(v), float(m)) for v, m in zip(vals, mvs)],
            "slope": slope,
            "intercept": intercept,
            "r2": r2,
        }
        self._save_data()
        self._dirty = False
        self._result_label.setText(
            f"已保存 — {name}: {self._unit_input.text()} = {intercept:.4f} + "
            f"({slope:.6f}) × E  (R² = {r2:.6f})"
        )


class SpectralMatrixWidget(QWidget):
    """光谱重建矩阵热力图 (721 波长 × 10 通道)。"""

    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setLayout(QVBoxLayout())
        self.layout().setContentsMargins(8, 8, 8, 8)

        import numpy as np
        from DataProcessor.reconstructor import is_available

        if not is_available():
            self.layout().addWidget(QLabel("校准数据未加载"))
            return

        # Load matrix from calibre.npz
        _p = os.path.join(DATA_DIR, "calibre.npz")
        _d = np.load(_p, allow_pickle=True)
        matrix = _d["spectral_matrix"]  # (721, 10)
        wls = _d["spectral_wavelengths"]  # (721,)
        ch_names = [
            "F1(415)",
            "F2(445)",
            "F3(480)",
            "F4(515)",
            "F5(555)",
            "F6(590)",
            "F7(630)",
            "F8(680)",
            "Clear",
            "NIR(910)",
        ]

        # ---- 热力图 ----
        self._plot = pg.PlotWidget(title="光谱重建矩阵 (721λ × 10ch)")
        self._plot.setLabel("bottom", "Channel", "")
        self._plot.setLabel("left", "Wavelength", "nm")
        self._plot.getAxis("bottom").setTicks(
            [[(i, n) for i, n in enumerate(ch_names)]]
        )
        self._plot.getAxis("bottom").setTickSpacing(1, 1)

        # ImageItem: transpose to (10, 721) so rows=channels, cols=wavelengths
        img = pg.ImageItem(matrix.T, axisOrder="row-major")
        img.setRect(
            pg.QtCore.QRectF(
                -0.5, float(wls[0]) - 0.5, 10, float(wls[-1]) - float(wls[0]) + 1
            )
        )
        # Set colormap: rdylbu-like
        cmap = pg.colormap.get("viridis")
        if cmap is not None:
            img.setColorMap(cmap)
        self._plot.addItem(img)

        # Colorbar
        bar = pg.ColorBarItem(values=(matrix.min(), matrix.max()), colorMap=cmap)
        bar.setImageItem(img)
        self._plot.addItem(bar)

        self._plot.setXRange(-0.5, 9.5)
        self._plot.setYRange(float(wls[0]), float(wls[-1]))

        self.layout().addWidget(self._plot)

        # ---- 说明 ----
        info = QLabel(
            "每列对应一个 AS7341 通道 (F1–F8, Clear, NIR)，每行对应一个波长 (380–1100 nm)。\n"
            f"矩阵尺寸: {matrix.shape[0]}λ × {matrix.shape[1]}ch, "
            f"值范围: [{matrix.min():.4f}, {matrix.max():.4f}]"
        )
        info.setWordWrap(True)
        self.layout().addWidget(info)


class CalibrationTab(QWidget):
    """校准选项卡 — 进样泵 / 滴定泵 / 电极 / 光谱矩阵。"""

    def __init__(self, com: ProtocolHandler, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setLayout(QVBoxLayout())
        self.layout().setContentsMargins(0, 0, 0, 0)

        self._tabs = QTabWidget()
        self._tabs.addTab(PumpCalibWidget(1, com), "进样泵")
        self._tabs.addTab(PumpCalibWidget(2, com), "滴定泵")
        self._tabs.addTab(PHCalibWidget(com), "电极校准")
        self._tabs.addTab(SpectralMatrixWidget(), "光谱矩阵")
        self.layout().addWidget(self._tabs)


__all__ = ["CalibrationTab"]
