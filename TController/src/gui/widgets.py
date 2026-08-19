"""
自定义交互组件 — 阶段指示器 / 滴定度规 / 状态点 / 工具提示 / 消息条 / 工作流引导。

所有组件均为主题与语言感知（通过 themes.subscribe / i18n.subscribe）。
"""

from __future__ import annotations

import tkinter as tk
from collections.abc import Callable
from typing import ClassVar

import ttkbootstrap as ttk

from gui import i18n, themes


def _mix(hex_a: str, hex_b: str, f: float) -> str:
    """线性混合两个 hex 颜色，f=0 → a，f=1 → b。"""
    a = hex_a.lstrip("#")
    b = hex_b.lstrip("#")
    ra, ga, ba = (int(a[i : i + 2], 16) for i in (0, 2, 4))
    rb, gb, bb = (int(b[i : i + 2], 16) for i in (0, 2, 4))
    r = int(ra + (rb - ra) * f)
    g = int(ga + (gb - ga) * f)
    bl = int(ba + (bb - ba) * f)
    return f"#{r:02x}{g:02x}{bl:02x}"


# ======================================================================
#  卡片容器（tk.Frame highlight 边框，主题感知）
# ======================================================================


class Card(tk.Frame):
    """带 1px 边框的表面卡片。ttk Frame 的 relief/borderwidth 在
    ttkbootstrap 主题引擎下不生效，故用 tk.Frame 的 highlight 描边。"""

    _TONES: ClassVar[dict[str, str]] = {
        "surface": "surface", "alt": "surface_alt", "danger": "danger_soft"
    }

    def __init__(self, parent: tk.Misc, tone: str = "surface", **kwargs) -> None:
        self._tone_key = tone
        t = themes.current_tokens()
        super().__init__(
            parent,
            background=self._tone_color(t),
            highlightthickness=1,
            highlightbackground=t.border,
            highlightcolor=t.border,
            bd=0,
            **kwargs,
        )
        themes.subscribe(self._apply_theme)

    def _tone_color(self, t: themes.Tokens) -> str:
        return getattr(t, self._TONES[self._tone_key])

    def _apply_theme(self) -> None:
        t = themes.current_tokens()
        self.configure(
            background=self._tone_color(t),
            highlightbackground=t.border,
            highlightcolor=t.border,
        )


# ======================================================================
#  状态点（连接指示，激活时呼吸）
# ======================================================================


class StatusDot(tk.Canvas):
    """12px 状态点：off / ok（呼吸）/ err。"""

    SIZE = 12

    def __init__(self, parent: tk.Misc, **kwargs) -> None:
        super().__init__(
            parent,
            width=self.SIZE,
            height=self.SIZE,
            bd=0,
            highlightthickness=0,
            **kwargs,
        )
        self._state = "off"
        self._phase = False
        self._job: str | None = None
        self._oval = self.create_oval(1, 1, self.SIZE - 1, self.SIZE - 1, fill="", outline="")
        themes.subscribe(self._apply_theme)
        self._paint()

    def set_state(self, state: str) -> None:
        """state: 'off' | 'ok' | 'err'。"""
        if state == self._state:
            return
        self._state = state
        if state == "ok" and self._job is None:
            self._loop()
        elif state != "ok" and self._job is not None:
            self.after_cancel(self._job)
            self._job = None
        self._paint()

    def _loop(self) -> None:
        self._phase = not self._phase
        self._paint()
        self._job = self.after(800, self._loop)

    def _paint(self) -> None:
        t = themes.current_tokens()
        self.configure(background=t.surface)
        if self._state == "ok":
            color = t.success if self._phase else _mix(t.success, t.surface, 0.55)
        elif self._state == "err":
            color = t.danger
        else:
            color = _mix(t.fg_muted, t.surface, 0.5)
        self.itemconfig(self._oval, fill=color, outline="")

    def _apply_theme(self) -> None:
        self._paint()


# ======================================================================
#  工具提示
# ======================================================================


class Tooltip:
    """悬停 500ms 后显示的小提示框（支持动态文本回调）。"""

    def __init__(self, widget: tk.Widget, text: str | Callable[[], str]) -> None:
        self._w = widget
        self._text = text
        self._tip: tk.Toplevel | None = None
        self._job: str | None = None
        widget.bind("<Enter>", self._schedule, add="+")
        widget.bind("<Leave>", self._hide, add="+")
        widget.bind("<ButtonPress>", self._hide, add="+")

    def _schedule(self, _event: object = None) -> None:
        if self._job is not None:
            self._w.after_cancel(self._job)
        self._job = self._w.after(500, self._show)

    def _show(self) -> None:
        self._job = None
        text = self._text() if callable(self._text) else self._text
        if not text:
            return
        tip = tk.Toplevel(self._w)
        tip.wm_overrideredirect(True)
        tip.wm_attributes("-topmost", True)
        label = tk.Label(
            tip,
            text=text,
            background="#212529",
            foreground="#F8F9FA",
            font=(themes.UI_FONT, themes.UI_SIZE - 1),
            padx=8,
            pady=4,
        )
        label.pack()
        self._w.update_idletasks()
        x = self._w.winfo_rootx() + self._w.winfo_width() // 2
        y = self._w.winfo_rooty() + self._w.winfo_height() + 4
        tip.wm_geometry(f"+{x}+{y}")
        self._tip = tip

    def _hide(self, _event: object = None) -> None:
        if self._job is not None:
            self._w.after_cancel(self._job)
            self._job = None
        if self._tip is not None:
            self._tip.destroy()
            self._tip = None


# ======================================================================
#  工作流阶段指示器
# ======================================================================


class PhaseStepper(tk.Canvas):
    """横向阶段指示器：已完成 ✓ / 当前高亮 / 待执行。"""

    HEIGHT = 54

    def __init__(self, parent: tk.Misc, phases: list[tuple[str, str]], **kwargs) -> None:
        super().__init__(
            parent, height=self.HEIGHT, bd=0, highlightthickness=0, **kwargs
        )
        self._phases = phases
        self._active = 0
        self._done_all = False
        self._error = False
        self.bind("<Configure>", lambda _e: self._draw())
        i18n.subscribe(self._draw)
        themes.subscribe(self._apply_theme)

    def set_phase(self, index: int, error: bool = False, done_all: bool = False) -> None:
        if (index, error, done_all) == (self._active, self._error, self._done_all):
            return
        self._active = index
        self._error = error
        self._done_all = done_all
        self._draw()

    def _apply_theme(self) -> None:
        self._draw()

    def _draw(self) -> None:
        t = themes.current_tokens()
        self.configure(background=t.bg)
        self.delete("all")
        w = self.winfo_width()
        if w < 40:
            return
        n = len(self._phases)
        cy = 19
        x0, x1 = 60, w - 60
        step = (x1 - x0) / max(1, n - 1)

        font_num = (themes.UI_FONT, 8, "bold")
        font_lbl = (themes.UI_FONT, themes.UI_SIZE - 1)
        font_lbl_on = (themes.UI_FONT, themes.UI_SIZE - 1, "bold")

        # 连接线（左侧步骤已完成则着色）
        for i in range(n - 1):
            xa = x0 + i * step
            xb = x0 + (i + 1) * step
            color = t.success if (self._done_all or i < self._active) else t.border
            self.create_line(xa + 13, cy, xb - 13, cy, fill=color, width=2)

        for i, (_key, ikey) in enumerate(self._phases):
            cx = x0 + i * step
            label = i18n.tr(ikey)
            if self._done_all or i < self._active:
                # 完成
                self.create_oval(cx - 11, cy - 11, cx + 11, cy + 11, fill=t.success, outline=t.success)
                self.create_text(cx, cy, text="✓", fill=t.on_filled, font=font_num)
                self.create_text(cx, cy + 24, text=label, fill=t.fg_muted, font=font_lbl)
            elif i == self._active:
                ring = t.danger if self._error else t.primary
                self.create_oval(cx - 14, cy - 14, cx + 14, cy + 14, outline=ring, width=2)
                self.create_oval(cx - 11, cy - 11, cx + 11, cy + 11, fill=ring, outline=ring)
                fg = t.on_filled if self._error else t.on_primary
                self.create_text(cx, cy, text=str(i + 1), fill=fg, font=font_num)
                self.create_text(cx, cy + 24, text=label, fill=ring, font=font_lbl_on)
            else:
                self.create_oval(cx - 11, cy - 11, cx + 11, cy + 11, fill=t.surface, outline=t.border, width=1)
                self.create_text(cx, cy, text=str(i + 1), fill=t.fg_muted, font=font_num)
                self.create_text(cx, cy + 24, text=label, fill=t.fg_muted, font=font_lbl)


# ======================================================================
#  滴定度规（T = 0..2）
# ======================================================================


class TGauge(tk.Canvas):
    """滴定度进度规：0 → 2，T=1 标记终点。"""

    HEIGHT = 54
    MAX = 2.0

    def __init__(self, parent: tk.Misc, width: int = 320, **kwargs) -> None:
        super().__init__(
            parent, width=width, height=self.HEIGHT, bd=0, highlightthickness=0, **kwargs
        )
        self._value: float | None = None
        self.bind("<Configure>", lambda _e: self._draw())
        i18n.subscribe(self._draw)
        themes.subscribe(self._apply_theme)

    def set_value(self, value: float | None) -> None:
        if value == self._value:
            return
        self._value = value
        self._draw()

    def _apply_theme(self) -> None:
        self._draw()

    def _draw(self) -> None:
        t = themes.current_tokens()
        self.configure(background=t.bg)
        self.delete("all")
        w = self.winfo_width() or 320
        x0, x1 = 10, w - 86
        cy = 26
        th = 8

        # 标题
        self.create_text(
            x0, 8, anchor="w", text=i18n.tr("gauge.title"), fill=t.fg_muted,
            font=(themes.UI_FONT, themes.UI_SIZE - 1),
        )

        # 轨道
        self.create_rectangle(x0, cy - th // 2, x1, cy + th // 2, fill=t.muted, outline="")

        # 填充
        if self._value is not None:
            v = max(0.0, min(self.MAX, self._value))
            fx = x0 + (x1 - x0) * v / self.MAX
            fill = t.success if v >= self.MAX else t.primary
            self.create_rectangle(x0, cy - th // 2, fx, cy + th // 2, fill=fill, outline="")
        else:
            fx = x0

        # T=1 标记
        mx = x0 + (x1 - x0) * 0.5
        self.create_line(mx, cy - 9, mx, cy + 9, fill=t.accent, width=2)
        self.create_text(
            mx, cy - 15, text=i18n.tr("gauge.t1"), fill=t.accent,
            font=(themes.UI_FONT, themes.UI_SIZE - 1, "bold"),
        )

        # 刻度 0 / 2
        self.create_text(x0, cy + 14, text="0", fill=t.fg_muted, font=(themes.UI_FONT, 8))
        self.create_text(x1, cy + 14, text="2", fill=t.fg_muted, font=(themes.UI_FONT, 8))

        # 数值
        if self._value is not None:
            text = f"T = {self._value:.2f}"
            color = t.success if self._value >= self.MAX else t.fg
        else:
            text = "T = —"
            color = t.fg_muted
        self.create_text(
            x1 + 40, cy, text=text, fill=color, font=(themes.MONO_FONT, 12, "bold"),
        )


# ======================================================================
#  消息条（严重度着色 + 瞬态自动清除）
# ======================================================================


class MessageBar(ttk.Frame):
    """状态栏消息区：图标按严重度着色，非粘性消息 6s 后回退。"""

    GLYPHS: ClassVar[dict[str, str]] = {
        "info": "●", "success": "✓", "warn": "!", "error": "✕"
    }
    _TRANSIENT_MS = 6000

    def __init__(self, parent: tk.Misc, **kwargs) -> None:
        super().__init__(parent, style="Statusbar.TFrame", **kwargs)
        self._icon = ttk.Label(self, text="", style="Status.TLabel", width=2)
        self._icon.pack(side="left", padx=(0, 6))
        self._text = ttk.Label(self, text="", style="Status.TLabel")
        self._text.pack(side="left")

        self._sticky_kind: str | None = None
        self._sticky_text = ""
        self._job: str | None = None
        themes.subscribe(self._repaint_current)

    def _color(self, kind: str) -> str:
        t = themes.current_tokens()
        return {
            "info": t.fg_muted,
            "success": t.success,
            "warn": t.accent,
            "error": t.danger,
        }[kind]

    def _paint(self, kind: str, text: str) -> None:
        self._icon.config(text=self.GLYPHS[kind], foreground=self._color(kind))
        self._text.config(text=text)

    def _repaint_current(self) -> None:
        current = self._text.cget("text")
        if not current:
            return
        kind: str = (
            self._sticky_kind if self._sticky_kind is not None
            else getattr(self, "_cur_kind", "info")
        ) if self._job is None else getattr(self, "_cur_kind", "info")
        self._icon.config(foreground=self._color(kind))

    def show(self, kind: str, text: str, sticky: bool = False) -> None:
        if self._job is not None:
            self.after_cancel(self._job)
            self._job = None
        self._cur_kind = kind
        if sticky:
            self._sticky_kind = kind
            self._sticky_text = text
        self._paint(kind, text)
        if not sticky:
            self._job = self.after(self._TRANSIENT_MS, self._expire)

    def _expire(self) -> None:
        self._job = None
        if self._sticky_kind is not None:
            self._cur_kind = self._sticky_kind
            self._paint(self._sticky_kind, self._sticky_text)
        else:
            self._icon.config(text="")
            self._text.config(text="")

    def set_sticky(self, kind: str | None, text: str = "") -> None:
        """设置/清除粘性基线消息。"""
        self._sticky_kind = kind
        self._sticky_text = text
        if kind is None and self._job is None:
            self._icon.config(text="")
            self._text.config(text="")


# ======================================================================
#  工作流引导（校准页步骤条）
# ======================================================================


class WorkflowHint(ttk.Frame):
    """编号步骤条：done ✓ / active 高亮 / pending 灰。"""

    def __init__(self, parent: tk.Misc, steps: list[str], **kwargs) -> None:
        super().__init__(parent, **kwargs)
        self._steps = steps
        self._active = 0
        self._dots: list[tk.Canvas] = []
        self._labels: list[ttk.Label] = []

        for i, key in enumerate(steps):
            if i:
                ttk.Label(self, text="——", style="Subtle.TLabel").pack(
                    side="left", padx=4
                )
            dot = tk.Canvas(self, width=18, height=18, bd=0, highlightthickness=0)
            dot.pack(side="left")
            self._dots.append(dot)
            lbl = ttk.Label(self, text=i18n.tr(key), style="Subtle.TLabel")
            lbl.pack(side="left", padx=(4, 0))
            self._labels.append(lbl)

        i18n.subscribe(self._apply_i18n)
        themes.subscribe(self._paint)

    def _apply_i18n(self) -> None:
        for lbl, key in zip(self._labels, self._steps):
            lbl.config(text=i18n.tr(key))
        self._paint()

    def set_active(self, idx: int) -> None:
        if idx == self._active:
            return
        self._active = idx
        self._paint()

    def _paint(self) -> None:
        t = themes.current_tokens()
        font = (themes.UI_FONT, 8, "bold")
        for i, dot in enumerate(self._dots):
            dot.configure(background=t.surface)
            dot.delete("all")
            if i < self._active:
                dot.create_oval(1, 1, 17, 17, fill=t.success, outline=t.success)
                dot.create_text(9, 9, text="✓", fill=t.on_filled, font=font)
            elif i == self._active:
                dot.create_oval(1, 1, 17, 17, fill=t.primary, outline=t.primary)
                dot.create_text(9, 9, text=str(i + 1), fill=t.on_primary, font=font)
            else:
                dot.create_oval(1, 1, 17, 17, fill=t.surface, outline=t.border)
                dot.create_text(9, 9, text=str(i + 1), fill=t.fg_muted, font=font)
            style = "Muted.TLabel" if i != self._active else "Section.TLabel"
            self._labels[i].config(style=style if i == self._active else "Subtle.TLabel")


__all__ = [
    "Card",
    "MessageBar",
    "PhaseStepper",
    "StatusDot",
    "TGauge",
    "Tooltip",
    "WorkflowHint",
]
