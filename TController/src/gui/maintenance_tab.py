"""
维护标签页 — 排空管路 / 充满管路 / 清洗管路

所有操作均为 FreeRun 模式，用户肉眼确认后手动停止。
"""

from __future__ import annotations

import tkinter as tk

import ttkbootstrap as ttk

from Communication import ProtocolHandler
from gui import i18n, themes


def _pump_name(pump_id: int) -> str:
    return i18n.tr("pump.inject" if pump_id == 1 else "pump.titrate")


class _OperationPanel(ttk.LabelFrame):
    """单个维护操作面板：泵复选框 + 启停 + 说明。"""

    def __init__(
        self,
        title_key: str,
        info_key: str,
        com: ProtocolHandler,
        parent: tk.Misc | None = None,
    ) -> None:
        super().__init__(parent, text=i18n.tr(title_key))
        self._title_key = title_key
        self._info_key = info_key
        self._com = com
        self._running = False

        inner = ttk.Frame(self, padding=(12, 10))
        inner.pack(fill="both", expand=True)

        # 泵选择（复选框，可多选）
        ctrl = ttk.Frame(inner)
        ctrl.pack(fill="x")

        self._select_label = ttk.Label(ctrl, text=i18n.tr("maint.select_pump"), style="Muted.TLabel")
        self._select_label.pack(side="left")

        self._cb1_var = tk.BooleanVar(value=True)
        self._cb1 = ttk.Checkbutton(ctrl, text=i18n.tr("pump.inject"), variable=self._cb1_var)
        self._cb1.pack(side="left", padx=(10, 0))
        self._cb2_var = tk.BooleanVar(value=True)
        self._cb2 = ttk.Checkbutton(ctrl, text=i18n.tr("pump.titrate"), variable=self._cb2_var)
        self._cb2.pack(side="left", padx=(10, 0))

        btn_frame = ttk.Frame(inner)
        btn_frame.pack(fill="x", pady=(10, 0))

        self._start_btn = ttk.Button(
            btn_frame, text=i18n.tr("common.start"), bootstyle="success", command=self._start
        )
        self._start_btn.pack(side="left")

        self._stop_btn = ttk.Button(
            btn_frame, text=i18n.tr("common.stop"), bootstyle="outline", command=self._stop
        )
        self._stop_btn.pack(side="left", padx=(8, 0))
        self._stop_btn.state(["disabled"])

        # 运行状态提示
        self._status_label = ttk.Label(inner, text="", style="Subtle.TLabel")
        self._status_label.pack(fill="x", pady=(8, 0))

        # 分隔
        ttk.Separator(inner, orient="horizontal").pack(fill="x", pady=8)

        # 操作说明
        self._info_label = ttk.Label(
            inner, text=i18n.tr(info_key), wraplength=600, style="Subtle.TLabel"
        )
        self._info_label.pack(fill="x")

        i18n.subscribe(self._apply_i18n)

    # ---- i18n ----

    def _apply_i18n(self) -> None:
        self.config(text=i18n.tr(self._title_key))
        self._select_label.config(text=i18n.tr("maint.select_pump"))
        self._cb1.config(text=i18n.tr("pump.inject"))
        self._cb2.config(text=i18n.tr("pump.titrate"))
        self._start_btn.config(text=i18n.tr("common.start"))
        self._stop_btn.config(text=i18n.tr("common.stop"))
        self._info_label.config(text=i18n.tr(self._info_key))
        if self._running:
            self._set_running_status()
        else:
            self._status_label.config(text="")

    def _set_running_status(self) -> None:
        pumps = []
        if self._cb1_var.get():
            pumps.append(_pump_name(1))
        if self._cb2_var.get():
            pumps.append(_pump_name(2))
        t = themes.current_tokens()
        self._status_label.config(
            text=i18n.tr("maint.running", pumps=" + ".join(pumps)),
            foreground=t.success,
            font=(themes.UI_FONT, themes.UI_SIZE, "bold"),
        )

    # ---- 操作 ----

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
        self._running = True
        self._start_btn.state(["disabled"])
        self._stop_btn.state(["!disabled"])
        self._set_running_status()

    def _stop(self) -> None:
        # 停止所有泵（运行时可能记不住选了哪些，干脆停止全部）
        self._com.send_frestop(0xFF)
        self._running = False
        self._start_btn.state(["!disabled"])
        self._stop_btn.state(["disabled"])
        self._status_label.config(
            text=i18n.tr("maint.stopped"),
            foreground="",
            font=(themes.UI_FONT, themes.UI_SIZE),
        )

    def set_connected(self, connected: bool) -> None:
        """串口状态变化时启用/禁用控件。"""
        if connected:
            self._start_btn.state(["!disabled"])
            self._status_label.config(text="", foreground="")
        else:
            self._running = False
            self._start_btn.state(["disabled"])
            self._stop_btn.state(["disabled"])
            # 明确的离线引导
            self._status_label.config(
                text=i18n.tr("maint.offline"),
                foreground=themes.current_tokens().accent,
                font=(themes.UI_FONT, themes.UI_SIZE),
            )


class MaintenanceTab(ttk.Frame):
    """维护标签页。"""

    def __init__(self, com: ProtocolHandler, parent: tk.Misc | None = None) -> None:
        super().__init__(parent)
        self._com = com

        inner = ttk.Frame(self)
        inner.pack(fill="both", expand=True, padx=12, pady=12)

        self._title = ttk.Label(inner, text=i18n.tr("maint.title"), style="Section.TLabel")
        self._title.pack(anchor="w")

        self._subtitle = ttk.Label(
            inner,
            text=i18n.tr("maint.subtitle"),
            wraplength=640,
            style="Muted.TLabel",
        )
        self._subtitle.pack(anchor="w", pady=(4, 12))

        # ---- 排空管路 ----
        self._empty_panel = _OperationPanel(
            "maint.empty_title", "maint.empty_info", com=com, parent=inner
        )
        self._empty_panel.pack(fill="x", pady=(0, 8))

        # ---- 充满管路（滴定前） ----
        self._fill_panel = _OperationPanel(
            "maint.fill_title", "maint.fill_info", com=com, parent=inner
        )
        self._fill_panel.pack(fill="x", pady=(0, 8))

        # ---- 清洗管路 ----
        self._wash_panel = _OperationPanel(
            "maint.wash_title", "maint.wash_info", com=com, parent=inner
        )
        self._wash_panel.pack(fill="x", pady=(0, 8))

        i18n.subscribe(self._apply_i18n)

    def _apply_i18n(self) -> None:
        self._title.config(text=i18n.tr("maint.title"))
        self._subtitle.config(text=i18n.tr("maint.subtitle"))

    def set_connected(self, connected: bool) -> None:
        """串口连接状态变化时同步更新各面板。"""
        self._empty_panel.set_connected(connected)
        self._fill_panel.set_connected(connected)
        self._wash_panel.set_connected(connected)


__all__ = ["MaintenanceTab"]
