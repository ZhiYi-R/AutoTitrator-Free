"""
维护标签页 — 排空管路 / 充满管路 / 清洗管路

所有操作均为 FreeRun 模式，用户肉眼确认后手动停止。
"""

from __future__ import annotations

import tkinter as tk
from typing import Final

import ttkbootstrap as ttk
from Communication import ProtocolHandler


class _OperationPanel(ttk.LabelFrame):
    """单个维护操作面板：泵复选框 + 启停 + 说明。"""

    # 泵编号 → 显示名称
    PUMP_NAMES: Final[dict[int, str]] = {1: "进样泵", 2: "滴定泵"}

    def __init__(
        self,
        title: str,
        instructions: str,
        com: ProtocolHandler,
        parent: tk.Misc | None = None,
    ) -> None:
        super().__init__(parent, text=title)
        self._com = com

        inner = ttk.Frame(self)
        inner.pack(fill="both", expand=True, padx=12, pady=(16, 12))

        # 泵选择（复选框，可多选）
        ctrl = ttk.Frame(inner)
        ctrl.pack(fill="x")

        ttk.Label(ctrl, text="选择泵:").pack(side="left")

        self._cb1_var = tk.BooleanVar(value=True)
        ttk.Checkbutton(ctrl, text="进样泵", variable=self._cb1_var).pack(
            side="left", padx=(8, 0)
        )
        self._cb2_var = tk.BooleanVar(value=True)
        ttk.Checkbutton(ctrl, text="滴定泵", variable=self._cb2_var).pack(
            side="left", padx=(8, 0)
        )

        ctrl.pack_propagate(False)

        btn_frame = ttk.Frame(inner)
        btn_frame.pack(fill="x", pady=(8, 0))

        self._start_btn = ttk.Button(btn_frame, text="启动", command=self._start)
        self._start_btn.pack(side="left", padx=(12, 0))

        self._stop_btn = ttk.Button(btn_frame, text="停止", command=self._stop)
        self._stop_btn.pack(side="left", padx=(8, 0))
        self._stop_btn.state(["disabled"])

        # 运行状态提示
        self._status_label = ttk.Label(inner, text="", font=("", 9, "italic"))
        self._status_label.pack(fill="x", pady=(8, 0))

        # 分隔
        ttk.Separator(inner, orient="horizontal").pack(fill="x", pady=8)

        # 操作说明
        info = ttk.Label(inner, text=instructions, wraplength=600, font=("", 9))
        info.pack(fill="x")

    def _start(self) -> None:
        pumps = []
        if self._cb1_var.get():
            pumps.append(1)
        if self._cb2_var.get():
            pumps.append(2)
        if not pumps:
            return
        for p in pumps:
            self._com.send_frerun(p)
        label = " + ".join(self.PUMP_NAMES[p] for p in pumps)
        self._start_btn.state(["disabled"])
        self._stop_btn.state(["!disabled"])
        self._status_label.config(
            text=f"{label} 运行中… 请观察，完成后点击停止",
            foreground="#27ae60",
            font=("", 9, "bold"),
        )

    def _stop(self) -> None:
        # 停止所有当前选中的泵（运行时可能记不住，干脆停止全部）
        self._com.send_frestop(0xFF)
        self._start_btn.state(["!disabled"])
        self._stop_btn.state(["disabled"])
        self._status_label.config(text="已停止", font=("", 9, "italic"))

    def set_connected(self, connected: bool) -> None:
        """串口状态变化时启用/禁用控件。"""
        if connected:
            self._start_btn.state(["!disabled"])
        else:
            self._start_btn.state(["disabled"])
            self._stop_btn.state(["disabled"])
            self._status_label.config(text="", font=("", 9, "italic"))


class MaintenanceTab(ttk.Frame):
    """维护标签页。"""

    def __init__(self, com: ProtocolHandler, parent: tk.Misc | None = None) -> None:
        super().__init__(parent)
        self._com = com

        inner = ttk.Frame(self)
        inner.pack(fill="both", expand=True, padx=12, pady=12)

        title = ttk.Label(inner, text="维护操作", font=("", 13, "bold"))
        title.pack(anchor="w")

        subtitle = ttk.Label(
            inner,
            text=(
                "以下操作均使用 FreeRun 模式（持续运行直到手动停止）。\n"
                "启动后请肉眼观察管路状态，确认完成后点击「停止」。"
            ),
            wraplength=600,
            font=("", 9),
        )
        subtitle.pack(anchor="w", pady=(4, 12))

        # ---- 排空管路 ----
        self._empty_panel = _OperationPanel(
            "排空管路",
            instructions=(
                "将管路一端放入废液杯，启动泵排空管内残留液体。\n"
                "肉眼观察管内液体排空后，点击「停止」。"
            ),
            com=com,
            parent=inner,
        )
        self._empty_panel.pack(fill="x", pady=4)

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
            parent=inner,
        )
        self._fill_panel.pack(fill="x", pady=4)

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
            parent=inner,
        )
        self._wash_panel.pack(fill="x", pady=4)

    def set_connected(self, connected: bool) -> None:
        """串口连接状态变化时同步更新各面板。"""
        self._empty_panel.set_connected(connected)
        self._fill_panel.set_connected(connected)
        self._wash_panel.set_connected(connected)


__all__ = ["MaintenanceTab"]
