"""滴定控制主窗口。"""

from __future__ import annotations

import os
import time
from datetime import datetime
from enum import Enum

import numpy as np
import openpyxl
from Communication import ProtocolHandler
from DataProcessor import PUMP_SLOPE, EndpointDetector, steps_from_volume
from DataProcessor import reconstruct as _reconstruct
from DataProcessor._path import CALIBRE_PATH
from PySide6.QtCore import Qt, QTimer
from PySide6.QtWidgets import (
    QCheckBox,
    QComboBox,
    QDoubleSpinBox,
    QLabel,
    QMainWindow,
    QMenu,
    QMessageBox,
    QPushButton,
    QSplitter,
    QTabWidget,
    QToolBar,
    QVBoxLayout,
    QWidget,
)

from gui.calibration_tab import CalibrationTab
from gui.maintenance_tab import MaintenanceTab
from gui.potential_widget import PotentialWidget
from gui.results_panel import ResultsPanel
from gui.spectrum_widget import SpectrumWidget
from gui.themes import apply_theme


class TitrationState(Enum):
    IDLE = "空闲"
    INJECTING = "进样中…"
    TITRATING = "滴定中…"
    DEGREE_1 = "终点 T=1"
    TITRATING_2 = "滴定至 T=2…"
    DONE = "完成"
    ERROR = "错误"


# ======================================================================

class MainWindow(QMainWindow):
    """滴定控制主窗口。

    工作流:
      空闲 → [开始] → 进样泵 MaxCount → 滴定泵 FreeRun
      → 终点检测 T=1 → 继续 FreeRun → T=2 → 停止
    """

    def __init__(self) -> None:
        super().__init__()
        self.setWindowTitle("多模态自动滴定控制器")
        self.resize(1280, 900)

        # ---- 串口通信 ----
        self._com = ProtocolHandler(parent=self)
        self._com.connected.connect(self._on_connected)
        self._com.disconnected.connect(self._on_disconnected)
        self._com.error_occurred.connect(self._on_com_error)
        self._com.spectral_data.connect(self._on_spectral_data)
        self._com.adc_data.connect(self._on_adc_data)
        self._com.pump_done.connect(self._on_pump_done)
        self._com.pump1_progress.connect(self._on_pump1_progress)
        self._com.pump2_progress.connect(self._on_pump2_progress)
        self._com.nak_received.connect(self._on_nak)

        self._pump1_volume: float = 0.0  # 泵 1 体积（mL）
        self._pump2_volume: float = 0.0  # 泵 2 体积（mL）

        # ---- 滴定检测 ----
        self._detector = EndpointDetector()
        self._state = TitrationState.IDLE
        self._endpoint_volume: float | None = None
        self._t0: float = 0.0       # 连接时刻
        self._recon_wls: np.ndarray | None = None
        self._adc_buffer: list[int] = []
        self._adc_counter = 0

        # ---- 数据记录 ----
        self._recording = False
        self._rec_spectral: list[tuple[float, list[int]]] = []      # (t, [F1..NIR])
        self._rec_recon: list[tuple[float, np.ndarray]] = []        # (t, full_spec)
        self._rec_recon_wls: np.ndarray | None = None
        self._rec_potential: list[tuple[float, float, float, float]] = []  # (t, raw_v, smooth_v, vol_mL)
        self._rec_raw_adc: list[tuple[float, int, float]] = []       # (t, raw_adc, vol_mL)
        self._rec_ewma_v: float | None = None

        # ---- UI ----
        self._build_toolbar()
        self._build_central()
        self._build_status()
        self._load_electrodes()
        # ---- 定时器 ----
        self._plot_timer = QTimer(self)
        self._plot_timer.setInterval(80)
        self._plot_timer.timeout.connect(self._refresh_plots)
        self._plot_timer.start()

        self._port_scan_timer = QTimer(self)
        self._port_scan_timer.setInterval(2000)
        self._port_scan_timer.timeout.connect(self._scan_ports)
        self._port_scan_timer.start()
        self._scan_ports()

        self._detect_timer = QTimer(self)
        self._detect_timer.setInterval(500)
        self._detect_timer.timeout.connect(self._run_detection)
        self._detect_timer.start()

        # ---- 心跳定时器 ----
        self._heartbeat_timer = QTimer(self)
        self._heartbeat_timer.setInterval(1000)
        self._heartbeat_timer.timeout.connect(self._send_heartbeat)

    # ================================================================
    #  UI 构建
    # ================================================================

    def _build_toolbar(self) -> None:
        tb = QToolBar("控制")
        tb.setMovable(False)
        self.addToolBar(tb)

        # 串口
        tb.addWidget(QLabel("端口:"))
        self._port_cb = QComboBox()
        self._port_cb.setMinimumWidth(160)
        tb.addWidget(self._port_cb)
        self._more_btn = QPushButton("更多")
        self._more_btn.setFixedWidth(40)
        self._more_btn.setToolTip("无描述串口")
        self._more_menu = QMenu(self._more_btn)
        self._more_btn.setMenu(self._more_menu)
        tb.addWidget(self._more_btn)

        tb.addWidget(QLabel("波特率:"))
        self._baud_cb = QComboBox()
        self._baud_cb.addItems(["9600", "19200", "38400", "57600", "115200", "230400"])
        self._baud_cb.setCurrentText("115200")
        tb.addWidget(self._baud_cb)

        self._conn_btn = QPushButton("连接")
        self._conn_btn.clicked.connect(self._toggle_connect)
        tb.addWidget(self._conn_btn)

        tb.addSeparator()

        tb.addWidget(QLabel("进样体积(mL):"))
        self._vol_spin = QDoubleSpinBox()
        self._vol_spin.setRange(1.0, 999.0)
        self._vol_spin.setValue(5.0)
        self._vol_spin.setDecimals(1)
        tb.addWidget(self._vol_spin)

        tb.addSeparator()

        self._start_btn = QPushButton("开始滴定")
        self._start_btn.setStyleSheet(
            "QPushButton { font-weight: bold; color: #fff; background: #27ae60; }"
            "QPushButton:hover { background: #2ecc71; }"
            "QPushButton:disabled { background: #95a5a6; }"
        )
        self._start_btn.clicked.connect(self._start_titration)
        tb.addWidget(self._start_btn)

        self._manual_stop_btn = QPushButton("停止滴定")
        self._manual_stop_btn.setStyleSheet(
            "QPushButton { color: #fff; background: #e67e22; }"
            "QPushButton:hover { background: #f39c12; }"
            "QPushButton:disabled { background: #95a5a6; }"
        )
        self._manual_stop_btn.setToolTip("正常停止滴定，保存已采集数据")
        self._manual_stop_btn.clicked.connect(self._manual_stop)
        self._manual_stop_btn.setEnabled(False)
        tb.addWidget(self._manual_stop_btn)

        self._stop_btn = QPushButton("急停")
        self._stop_btn.setStyleSheet(
            "QPushButton { color: #fff; background: #c0392b; }"
            "QPushButton:hover { background: #e74c3c; }"
            "QPushButton:disabled { background: #95a5a6; }"
        )
        self._stop_btn.setToolTip("MCU 立即复位，滴定中断且不保存数据")
        self._stop_btn.clicked.connect(self._emergency_stop)
        self._stop_btn.setEnabled(False)
        tb.addWidget(self._stop_btn)

        self._reset_btn = QPushButton("复位MCU")
        self._reset_btn.setStyleSheet(
            "QPushButton { color: #fff; background: #7f8c8d; }"
            "QPushButton:hover { background: #95a5a6; }"
            "QPushButton:disabled { background: #bdc3c7; }"
        )
        self._reset_btn.setToolTip("下发 Reset 指令，MCU 立即复位")
        self._reset_btn.clicked.connect(self._reset_mcu)
        tb.addWidget(self._reset_btn)

        tb.addSeparator()

        self._rec_cb = QCheckBox("记录数据")
        self._rec_cb.setChecked(True)
        self._rec_cb.setToolTip("启用后数据写入有界 FIFO，可导出 xlsx")
        self._rec_cb.toggled.connect(self._on_recording_toggled)
        tb.addWidget(self._rec_cb)

        tb.addSeparator()
        tb.addWidget(QLabel("主题:"))
        self._theme_combo = QComboBox()
        self._theme_combo.addItem("浅色", "light")
        self._theme_combo.addItem("深色", "dark")
        self._theme_combo.addItem("跟随系统", "system")
        self._theme_combo.setCurrentIndex(2)  # 默认跟随系统
        self._theme_combo.currentIndexChanged.connect(self._on_theme_changed)
        tb.addWidget(self._theme_combo)



    def _build_central(self) -> None:
        self._main_tabs = QTabWidget()
        self._main_tabs.setTabPosition(QTabWidget.TabPosition.North)

        # ---- 滴定标签页 ----
        titrate_tab = QWidget()
        titrate_tab.setLayout(QVBoxLayout())
        titrate_tab.layout().setContentsMargins(0, 0, 0, 0)

        splitter = QSplitter(Qt.Orientation.Horizontal)
        left = QWidget()
        left.setLayout(QVBoxLayout())
        left.layout().setContentsMargins(4, 4, 4, 4)
        left.layout().setSpacing(4)

        self._spectrum_widget = SpectrumWidget()
        self._potential_widget = PotentialWidget()
        left.layout().addWidget(self._spectrum_widget, 3)
        left.layout().addWidget(self._potential_widget, 3)
        splitter.addWidget(left)

        self._results_panel = ResultsPanel()
        splitter.addWidget(self._results_panel)
        splitter.setStretchFactor(0, 1)
        splitter.setStretchFactor(1, 0)

        titrate_tab.layout().addWidget(splitter)
        self._main_tabs.addTab(titrate_tab, "滴定")

        # ---- 校准标签页 ----
        self._calib_tab = CalibrationTab(self._com)
        self._main_tabs.addTab(self._calib_tab, "校准")

        self._maintenance_tab = MaintenanceTab(self._com)
        self._main_tabs.addTab(self._maintenance_tab, "维护")

        self.setCentralWidget(self._main_tabs)

    def _build_status(self) -> None:
        sb = self.statusBar()
        self._state_label = QLabel("空闲")
        self._state_label.setStyleSheet("font-weight: bold;")
        sb.addWidget(self._state_label, 1)
        self._info_label = QLabel("")
        sb.addPermanentWidget(self._info_label)

    # ================================================================
    #  串口连接
    # ================================================================

    def _scan_ports(self) -> None:
        import serial.tools.list_ports
        current_dev = self._port_cb.currentData()
        self._port_cb.blockSignals(True)
        self._port_cb.clear()

        for p in serial.tools.list_ports.comports():
            if p.vid is not None:
                desc = p.description or ""
                label = f"{p.device} ({desc})" if desc else p.device
                self._port_cb.addItem(label, p.device)

        self._more_menu.clear()
        bare = [p.device for p in serial.tools.list_ports.comports()
                if p.vid is None]
        self._more_btn.setVisible(bool(bare))
        for dev in bare:
            act = self._more_menu.addAction(dev)
            act.setData(dev)
            act.triggered.connect(lambda checked=False, d=dev: self._on_bare_port(d))

        if current_dev:
            idx = self._port_cb.findData(current_dev)
            if idx >= 0:
                self._port_cb.setCurrentIndex(idx)
        self._port_cb.blockSignals(False)

    def _on_bare_port(self, dev: str) -> None:
        for i in range(self._port_cb.count()):
            if self._port_cb.itemData(i) == dev:
                self._port_cb.setCurrentIndex(i)
                return
        self._port_cb.addItem(dev, dev)
        self._port_cb.setCurrentIndex(self._port_cb.count() - 1)

    def _toggle_connect(self) -> None:
        if self._com.is_open:
            self._com.send_abort(0xFF)
            self._com.disconnect()
        else:
            port = self._port_cb.currentData()
            if not port:
                QMessageBox.warning(self, "提示", "请选择串口端口")
                return
            self._com.reconfigure(port, int(self._baud_cb.currentText()))
            self._com.connect()

    def _on_connected(self) -> None:
        self._conn_btn.setText("断开")
        self._t0 = time.monotonic()
        self._state_label.setText("已连接")
        self._state_label.setStyleSheet("font-weight: bold; color: #27ae60;")
        self._start_btn.setEnabled(True)
        self._com.enable_watchdog()
        self._heartbeat_timer.start()
        self._maintenance_tab.set_connected(True)

    def _on_disconnected(self) -> None:
        self._conn_btn.setText("连接")
        self._state_label.setText("未连接")
        self._state_label.setStyleSheet("")
        self._start_btn.setEnabled(False)
        self._stop_btn.setEnabled(False)
        self._set_state(TitrationState.IDLE)
        self._heartbeat_timer.stop()
        self._maintenance_tab.set_connected(False)

    def _on_com_error(self, msg: str) -> None:
        self._state_label.setText(f"错误: {msg}")
        self._state_label.setStyleSheet("font-weight: bold; color: #e74c3c;")
        self._set_state(TitrationState.ERROR)

    def _on_nak(self) -> None:
        self._info_label.setText("NAK")

    def _send_heartbeat(self) -> None:
        if self._com.is_open:
            self._com.send_heartbeat()

    # ================================================================
    #  数据回调
    # ================================================================

    def _on_spectral_data(self, vals: list[int]) -> None:
        t = time.monotonic() - self._t0
        # 始终重建并显示
        if self._recon_wls is None:
            try:
                self._recon_wls, _ = _reconstruct(vals)
            except Exception:
                pass
        if self._recon_wls is not None:
            try:
                _, spec = _reconstruct(vals)
                self._spectrum_widget.update_spectrum(self._recon_wls, spec)
                if self._recording:
                    self._rec_spectral.append((t, list(vals)))
                    if self._rec_recon_wls is None:
                        self._rec_recon_wls = self._recon_wls.copy()
                    self._rec_recon.append((t, spec.copy()))
            except Exception:
                pass
        # 仅在滴定期间馈入检测器
        if self._state in (TitrationState.TITRATING, TitrationState.TITRATING_2,
                           TitrationState.DEGREE_1):
            self._detector.feed_spectrum(self._pump2_volume, np.array(vals, dtype=np.float64))

    def _on_adc_data(self, raw: int, pump2_pos: int) -> None:
        t = time.monotonic() - self._t0
        v = raw * 3.3 / 65535 - 1.1
        # 更新 Pump2 体积（基于固件实际步数）
        old_vol = self._pump2_volume
        self._pump2_volume = PUMP_SLOPE * pump2_pos
        # 调试：泵体积变化时更新 info
        if self._state in (TitrationState.TITRATING, TitrationState.TITRATING_2,
                           TitrationState.DEGREE_1):
            diff = self._pump2_volume - old_vol
            if diff > 0.001:
                self._info_label.setText(
                    f"泵2 vol={self._pump2_volume:.4f} mL  +{diff:.4f}"
                )
        # 缓存用于泵 report 间平均
        self._adc_buffer.append(raw)
        self._results_panel.set_current_voltage(v)
        # 记录原始 ADC 数据
        if self._recording:
            self._rec_raw_adc.append((t, raw, self._pump2_volume))
        # 每次均馈入检测器（保持检测精度）
        if self._state in (TitrationState.TITRATING, TitrationState.TITRATING_2,
                           TitrationState.DEGREE_1):
            vol = self._pump2_volume
            self._detector.feed_potential(vol, t, v)
        self._adc_counter += 1

    def _on_pump1_progress(self, pos: int) -> None:
        self._pump1_volume = PUMP_SLOPE * pos
        self._results_panel.update_inject_progress(pos, volume=self._pump1_volume)
        self._flush_adc_buffer()

    def _on_pump2_progress(self, pos: int) -> None:
        self._pump2_volume = PUMP_SLOPE * pos
        self._flush_adc_buffer()

    def _flush_adc_buffer(self) -> None:
        """将缓存内 ADC 读数平均后更新到电位曲线。"""
        if not self._adc_buffer:
            return
        t = time.monotonic() - self._t0
        raw_avg = int(round(sum(self._adc_buffer) / len(self._adc_buffer)))
        v = raw_avg * 3.3 / 65535 - 1.1
        vol = self._pump1_volume if self._state == TitrationState.INJECTING else self._pump2_volume
        self._potential_widget.append(t, raw_avg, volume=vol)
        # 记录电位数据点（含 EWMA 平滑）
        if self._recording:
            if self._rec_ewma_v is None:
                self._rec_ewma_v = v
            else:
                self._rec_ewma_v = 0.15 * v + 0.85 * self._rec_ewma_v
            self._rec_potential.append((t, v, self._rec_ewma_v, vol))
        self._adc_buffer.clear()

    def _on_pump_done(self, position: int) -> None:
        self._info_label.setText(f"泵完成 pos={position}")
        if self._state == TitrationState.INJECTING:
            # 进样完成 -> 隐藏进度条，清空进样数据，启动滴定泵
            self._results_panel.hide_inject_progress()
            self._potential_widget.reset()
            self._potential_widget.set_titrating(True)
            self._set_state(TitrationState.TITRATING)
            self._com.send_frerun(2)

    # ================================================================
    #  滴定控制
    # ================================================================

    def _set_state(self, state: TitrationState) -> None:
        self._state = state
        self._state_label.setText(state.value)

    def _start_titration(self) -> None:
        if not self._com.is_open:
            QMessageBox.warning(self, "提示", "请先连接串口")
            return

        # 复位检测器
        # 复位所有数据
        self._detector.reset()
        self._endpoint_volume = None
        self._t1_time = 0.0
        self._potential_widget.set_titrating(False)
        self._potential_widget.reset()
        self._results_panel.reset_endpoint()
        self._adc_counter = 0
        # AMPD 在 T=2 统一执行，无需中间标记
        self._pump1_volume = 0.0
        self._pump2_volume = 0.0
        vol_ml = self._vol_spin.value()
        self._info_label.setText(f"进样 {vol_ml:.1f} mL …")
        self._results_panel.set_sample_volume(vol_ml)
        # 进样体积 → MaxCount 步数（标定公式换算）
        steps = steps_from_volume(vol_ml)
        self._results_panel.show_inject_progress(steps, target_vol=vol_ml)
        self._start_btn.setEnabled(False)
        self._com.send_maxcount(1, steps)
        self._set_state(TitrationState.INJECTING)
        self._potential_widget.set_titrating(True)
        self._stop_btn.setEnabled(True)
        self._manual_stop_btn.setEnabled(True)

    def _emergency_stop(self) -> None:
        self._com.send_reset()
        self._set_state(TitrationState.IDLE)
        self._start_btn.setEnabled(True)
        self._stop_btn.setEnabled(False)
        self._manual_stop_btn.setEnabled(False)
        self._info_label.setText("已紧急停止，MCU 复位")
        self._potential_widget.set_titrating(False)
        self._potential_widget.reset()
        self._results_panel.reset_endpoint()

    def _manual_stop(self) -> None:
        """手动停止滴定：停泵、精修终点、保存数据，不复位 MCU。"""
        self._manual_stop_btn.setEnabled(False)
        self._stop_btn.setEnabled(False)

        # 停止滴定泵
        self._com.send_frestop(2)

        # 如果已检测到 T=1，用 AMPD 精修终点
        if self._endpoint_volume:
            ref = self._detector.refine_with_ampd()
            if ref is not None:
                self._endpoint_volume = ref
                self._results_panel.set_endpoint(ref)
                self._potential_widget.set_endpoint(ref)

            self._potential_widget.set_titrating(False)
            self._state_label.setText(f"手动停止 @ {self._endpoint_volume:.4f} mL")
            self._state_label.setStyleSheet("font-weight: bold; color: #e67e22;")

            # 保存数据
            result = self._detector.detect()
            if result is not None:
                self._on_titration_complete(result)
        else:
            self._potential_widget.set_titrating(False)
            self._state_label.setText("手动停止")

        self._set_state(TitrationState.DONE)
        self._start_btn.setEnabled(True)
        self._info_label.setText("已手动停止")

    def _reset_mcu(self) -> None:
        """复位 MCU 并重置上位机状态。"""
        self._com.send_reset()
        self._detector.reset()
        self._set_state(TitrationState.IDLE)
        self._start_btn.setEnabled(True)
        self._stop_btn.setEnabled(False)
        self._manual_stop_btn.setEnabled(False)
        self._potential_widget.set_titrating(False)
        self._potential_widget.reset()
        self._results_panel.reset_endpoint()
        self._endpoint_volume = None
        self._t1_time = 0.0
        self._info_label.setText("已复位（MCU + 上位机）")

    # ================================================================
    #  定时任务
    # ================================================================

    def _refresh_plots(self) -> None:
        self._potential_widget.refresh()

    def _run_detection(self) -> None:
        if self._state not in (TitrationState.TITRATING, TitrationState.TITRATING_2,
                               TitrationState.DEGREE_1):
            return

        result = self._detector.detect()
        if result is None:
            return

        vol = result["volume"]
        self._info_label.setText(f"检测: {vol:.3f} mL, 置信度={result['confidence']}")

        if self._state == TitrationState.TITRATING:
            # 首次到达终点 T=1
            self._endpoint_volume = vol
            self._potential_widget.set_endpoint(vol)
            self._results_panel.set_endpoint(vol)
            self._set_state(TitrationState.DEGREE_1)
            self._state_label.setText(f"终点 T=1 @ {vol:.3f} mL")
            self._state_label.setStyleSheet("font-weight: bold; color: #e67e22;")

        elif self._state in (TitrationState.DEGREE_1, TitrationState.TITRATING_2):
            # 显示当前滴定进度
            if self._endpoint_volume:
                t_val = self._pump2_volume / self._endpoint_volume
                self._state_label.setText(
                    f"T=1 @ {self._endpoint_volume:.3f} mL | "
                    f"T={t_val:.2f}  vol={self._pump2_volume:.3f} mL"
                )
            # 继续滴定到 T=2（用实际累积体积）
            if self._endpoint_volume and self._pump2_volume >= 2.0 * self._endpoint_volume:
                self._com.send_frestop(2)
                # T=2 停泵后用 AMPD 从完整导数曲线精确定位终点
                ref = self._detector.refine_with_ampd()
                if ref is not None:
                    self._endpoint_volume = ref
                    self._results_panel.set_endpoint(ref)
                    self._potential_widget.set_endpoint(ref)
                self._set_state(TitrationState.DONE)
                self._potential_widget.set_titrating(False)
                self._state_label.setText(f"终点: {self._endpoint_volume:.4f} mL")
                self._state_label.setStyleSheet("font-weight: bold; color: #27ae60;")
                self._start_btn.setEnabled(True)
                self._stop_btn.setEnabled(False)
                self._manual_stop_btn.setEnabled(False)
                self._on_titration_complete(result)
            else:
                if self._state == TitrationState.DEGREE_1:
                    self._set_state(TitrationState.TITRATING_2)

    # ================================================================
    #  数据导出
    # ================================================================

    def _on_titration_complete(self, result: dict) -> None:
        """滴定完成时更新 Cx 并自动导出数据。"""
        # 确保 Cx 基于最新终点体积重新计算
        if self._endpoint_volume:
            self._results_panel.set_endpoint(self._endpoint_volume)
        if not self._recording:
            return
        self._export_recording(result)

    def _export_recording(self, result: dict) -> None:
        """将记录的数据写入 ExpResults/ 目录下的 xlsx 文件。"""

        out_dir = os.path.join(os.path.dirname(__file__), "..", "..", "ExpResults")
        os.makedirs(out_dir, exist_ok=True)

        c_std = self._results_panel._c_std.value()
        ts = datetime.now().strftime("%y-%m-%d-%H-%M-%S")
        filename = f"std_conc_{c_std}_{ts}.xlsx"
        filepath = os.path.join(out_dir, filename)

        wb = openpyxl.Workbook()

        # ---- Sheet 1: Raw Spectrum ----
        ws = wb.active
        ws.title = "Raw Spectrum"
        ws.append(["Time (s)", "F1(415)", "F2(445)", "F3(480)", "F4(515)",
                    "F5(555)", "F6(590)", "F7(630)", "F8(680)", "Clear", "NIR(910)"])
        for t, vals in self._rec_spectral:
            ws.append([round(t, 3)] + vals)

        # ---- Sheet 2: Reconstructed Spectrum ----
        if self._rec_recon_wls is not None and self._rec_recon:
            ws2 = wb.create_sheet("Reconstructed Spectrum")
            header = ["Wavelength (nm)"] + [f"t={round(t, 3)}s" for t, _ in self._rec_recon]
            ws2.append(header)
            wls = self._rec_recon_wls
            for i in range(len(wls)):
                row = [round(float(wls[i]), 2)]
                for _, spec in self._rec_recon:
                    row.append(round(float(spec[i]), 4))
                ws2.append(row)

        # ---- Sheet 3: Potential (Filtered) ----
        ws3 = wb.create_sheet("Potential")
        ws3.append(["Time (s)", "Raw Voltage (V)", "Filtered Voltage (V)", "Volume (mL)"])
        for t, rv, fv, vol in self._rec_potential:
            ws3.append([round(t, 3), round(rv, 6), round(fv, 6), round(vol, 6)])

        # ---- Sheet 4: Titration Results ----
        ws4 = wb.create_sheet("Titration Results")
        ws4.append(["Parameter", "Value"])
        ws4.append(["Endpoint Volume (mL)", round(self._endpoint_volume or result.get("volume", 0), 4)])
        ws4.append(["Confidence", result.get("confidence", "")])
        ws4.append(["Method", result.get("method", "")])
        if result.get("potential"):
            ws4.append(["Potential Endpoint (mL)", round(result["potential"].get("volume", 0), 4)])
            ws4.append(["Min dV/dt", result["potential"].get("min_dvdt", "")])
        if result.get("spectral"):
            ws4.append(["Spectral Endpoint (mL)", round(result["spectral"].get("volume", 0), 4)])
            ws4.append(["Max CE", result["spectral"].get("max_ce", "")])
        ws4.append(["C_std (mol/L)", c_std])
        ws4.append(["n_std (标准液)", self._results_panel._n_std.value()])
        ws4.append(["n_analyte (待测液)", self._results_panel._n_analyte.value()])
        ws4.append(["V_sample (mL)", self._results_panel._v_sample_label.text()])
        ws4.append(["Cx (mol/L)", self._results_panel._c_x_label.text()])
        if self._endpoint_volume:
            ws4.append(["Refined Endpoint (mL)", round(self._endpoint_volume, 4)])

        wb.save(filepath)
        self._info_label.setText(f"数据已导出: {filename}")

    # ================================================================

    def _on_recording_toggled(self, on: bool) -> None:
        self._recording = on
        if on:
            self._rec_spectral.clear()
            self._rec_recon.clear()
            self._rec_recon_wls = None
            self._rec_potential.clear()
            self._rec_raw_adc.clear()
            self._rec_ewma_v = None
            self._info_label.setText("数据记录已开始")
        else:
            self._info_label.setText("数据记录已停止")

    def _theme_plots(self) -> list:
        plots = [
            getattr(self._spectrum_widget, "_plot", None),
            getattr(self._potential_widget, "_plot", None),
        ]
        try:
            tabs = self._calib_tab._tabs
            for i in range(tabs.count()):
                w = tabs.widget(i)
                if hasattr(w, "_plot"):
                    plots.append(w._plot)
        except Exception:
            pass
        return [p for p in plots if p is not None]

    def _on_theme_changed(self, idx: int) -> None:
        mode = self._theme_combo.itemData(idx)
        apply_theme(mode, plots=self._theme_plots())

    # ---- 电极选择 ----

    def _load_electrodes(self) -> None:
        path = CALIBRE_PATH
        electrodes = []
        if os.path.isfile(path):
            try:
                import numpy as _np
                data = _np.load(path, allow_pickle=True)
                if "n_electrodes" in data:
                    n = int(data["n_electrodes"])
                    names = list(data["names"])
                    for i in range(n):
                        name = names[i]
                        unit = str(data[f"unit_{i}"])
                        slope = float(data[f"slope_{i}"])
                        intercept = float(data[f"intercept_{i}"])
                        electrodes.append((name, slope, intercept, unit))
            except Exception:
                pass
        self._results_panel.set_electrodes(electrodes)
        self._results_panel.electrode_changed.connect(self._on_electrode_changed)

    def _on_electrode_changed(self, data: tuple | None) -> None:
        if data is None:
            self._potential_widget.clear_calibration()
        else:
            name, slope, intercept, unit = data
            self._potential_widget.set_calibration(unit, slope, intercept)
        self._potential_widget.refresh()

    def closeEvent(self, event) -> None:
        self._plot_timer.stop()
        self._detect_timer.stop()
        self._port_scan_timer.stop()
        self._heartbeat_timer.stop()
        if self._com.is_open:
            self._com.send_reset()
            self._com.shutdown()
        super().closeEvent(event)
