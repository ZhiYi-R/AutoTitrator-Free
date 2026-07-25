"""
维护标签页 — 排空管路 / 充满管路 / 清洗管路

所有操作均为 FreeRun 模式，用户肉眼确认后手动停止。
"""

from __future__ import annotations

from PySide6.QtCore import Qt
from PySide6.QtGui import QFont
from PySide6.QtWidgets import (
    QCheckBox,
    QFrame,
    QGroupBox,
    QHBoxLayout,
    QLabel,
    QPushButton,
    QVBoxLayout,
    QWidget,
)

from Communication import ProtocolHandler


class _OperationPanel(QGroupBox):
    """单个维护操作面板：泵复选框 + 启停 + 说明。"""
    # 泵编号 → 显示名称
    PUMP_NAMES: dict[int, str] = {1: "进样泵", 2: "滴定泵"}

    def __init__(self, title: str, instructions: str, com: ProtocolHandler,
                 parent: QWidget | None = None) -> None:
        super().__init__(title, parent)
        self._com = com

        self.setLayout(QVBoxLayout())
        self.layout().setContentsMargins(12, 16, 12, 12)
        self.layout().setSpacing(8)

        # 泵选择（复选框，可多选）
        ctrl = QHBoxLayout()
        ctrl.setSpacing(8)

        ctrl.addWidget(QLabel("选择泵:"))
        self._cb1 = QCheckBox("进样泵")
        self._cb1.setChecked(True)
        ctrl.addWidget(self._cb1)
        self._cb2 = QCheckBox("滴定泵")
        self._cb2.setChecked(True)
        ctrl.addWidget(self._cb2)

        ctrl.addSpacing(12)
        self._start_btn = QPushButton("启动")
        self._start_btn.setStyleSheet(
            "QPushButton { font-weight: bold; color: #fff; background: #27ae60; }"
            "QPushButton:hover { background: #2ecc71; }"
            "QPushButton:disabled { background: #95a5a6; }"
        )
        self._start_btn.clicked.connect(self._start)
        ctrl.addWidget(self._start_btn)

        self._stop_btn = QPushButton("停止")
        self._stop_btn.setStyleSheet(
            "QPushButton { color: #fff; background: #c0392b; }"
            "QPushButton:hover { background: #e74c3c; }"
            "QPushButton:disabled { background: #95a5a6; }"
        )
        self._stop_btn.setEnabled(False)
        self._stop_btn.clicked.connect(self._stop)
        ctrl.addWidget(self._stop_btn)

        ctrl.addStretch()
        self.layout().addLayout(ctrl)

        # 运行状态提示
        self._status_label = QLabel("")
        self._status_label.setStyleSheet("font-style: italic;")
        self.layout().addWidget(self._status_label)

        # 操作说明
        sep = QFrame()
        sep.setFrameShape(QFrame.Shape.HLine)
        sep.setFrameShadow(QFrame.Shadow.Sunken)
        self.layout().addWidget(sep)

        info = QLabel(instructions)
        info.setWordWrap(True)
        info.setStyleSheet("font-size: 11px;")
        self.layout().addWidget(info)

    def _start(self) -> None:
        pumps = []
        if self._cb1.isChecked(): pumps.append(1)
        if self._cb2.isChecked(): pumps.append(2)
        if not pumps:
            return
        for p in pumps:
            self._com.send_frerun(p)
        label = " + ".join(self.PUMP_NAMES[p] for p in pumps)
        self._start_btn.setEnabled(False)
        self._stop_btn.setEnabled(True)
        self._status_label.setText(f"{label} 运行中… 请观察，完成后点击停止")
        self._status_label.setStyleSheet("color: #27ae60; font-weight: bold;")

    def _stop(self) -> None:
        # 停止所有当前选中的泵（运行时可能记不住，干脆停止全部）
        self._com.send_frestop(0xFF)
        self._start_btn.setEnabled(True)
        self._stop_btn.setEnabled(False)
        self._status_label.setText("已停止")
        self._status_label.setStyleSheet("font-style: italic;")

    def set_connected(self, connected: bool) -> None:
        """串口状态变化时启用/禁用控件。"""
        self._start_btn.setEnabled(connected)
        if not connected:
            self._stop_btn.setEnabled(False)
            self._status_label.setText("")
            self._status_label.setStyleSheet("font-style: italic;")


class MaintenanceTab(QWidget):
    """维护标签页。"""

    def __init__(self, com: ProtocolHandler,
                 parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self._com = com

        self.setLayout(QVBoxLayout())
        self.layout().setContentsMargins(12, 12, 12, 12)
        self.layout().setSpacing(12)

        title = QLabel("维护操作")
        title.setStyleSheet("font-weight: bold; font-size: 15px;")
        self.layout().addWidget(title)

        subtitle = QLabel(
            "以下操作均使用 FreeRun 模式（持续运行直到手动停止）。\n"
            "启动后请肉眼观察管路状态，确认完成后点击「停止」。"
        )
        subtitle.setWordWrap(True)
        subtitle.setStyleSheet("margin-bottom: 4px;")
        self.layout().addWidget(subtitle)

        # ---- 排空管路 ----
        self._empty_panel = _OperationPanel(
            "排空管路",
            instructions=(
                "将管路一端放入废液杯，启动泵排空管内残留液体。\n"
                "肉眼观察管内液体排空后，点击「停止」。"
            ),
            com=com,
        )
        self.layout().addWidget(self._empty_panel)

        # ---- 充满管路（滴定前） ----
        self._fill_panel = _OperationPanel(
            "充满管路（滴定前排气）",
            instructions=(
                "进样泵：将入口放入待测液中，排空管内空气和水。\n"
                "滴定泵：将入口放入滴定液中，排空管内空气和水。\n\n"
                "启动前确认管路连接正确，避免液体交叉污染。\n"
                "待液体连续流出、管内无气泡后，点击「停止」。"
            ),
            com=com,
        )
        self.layout().addWidget(self._fill_panel)

        # ---- 清洗管路 ----
        self._wash_panel = _OperationPanel(
            "清洗管路（去离子水）",
            instructions=(
                "将管路入口端放入去离子水中，出口端放入废液杯。\n"
                "启动泵冲洗管路内部，建议冲洗 30 秒以上。\n"
                "肉眼观察出水干净后，点击「停止」。\n\n"
                "清洗后如需立即使用，请用「充满管路」排出残留水份。"
            ),
            com=com,
        )
        self.layout().addWidget(self._wash_panel)

        self.layout().addStretch()

    def set_connected(self, connected: bool) -> None:
        """串口连接状态变化时同步更新各面板。"""
        self._empty_panel.set_connected(connected)
        self._fill_panel.set_connected(connected)
        self._wash_panel.set_connected(connected)


__all__ = ["MaintenanceTab"]

