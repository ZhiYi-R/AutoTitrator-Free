"""
主题管理模块 — 仪器级灰阶配色（instrument-grade grayscale）。

设计原则：界面主体为中性灰阶，色彩克制地保留给语义状态
（成功/警告/危险）与数据曲线，主操作为石墨色实心按钮。

    Light: bg #F3F4F5 / surface #FFFFFF / primary #3A4149(石墨)
    Dark:  bg #1C1E21 / surface #24262A / primary #B8BEC6(浅石墨)

自定义 ttkbootstrap 主题（instrument-light / instrument-dark）在
本模块导入时注册到 USER_THEMES，使按钮、下拉框、进度条等全部
bootstyle 控件与界面令牌保持同一调色板。控件通过 subscribe()
订阅主题变化以更新直接写入的语义色（foreground 等）。
"""

from __future__ import annotations

import platform
import sys
import tkinter as tk
from collections.abc import Callable
from dataclasses import dataclass

import ttkbootstrap
from matplotlib import font_manager, rcParams
from ttkbootstrap.themes.user import USER_THEMES

# ── 字体 ─────────────────────────────────────────────────────


def ui_font_family() -> str:
    system = platform.system()
    if system == "Windows":
        # Segoe UI 不含 CJK 字形，tk 走 GDI 字体链接回退（雅黑字形 +
        # Segoe 度量）会把中文挤压错位；直接用中英混排的雅黑 UI 字体
        available = {f.name for f in font_manager.fontManager.ttflist}
        for name in ("Microsoft YaHei UI", "Microsoft YaHei", "SimHei"):
            if name in available:
                return name
        return "Microsoft YaHei UI"
    if system == "Darwin":
        return "PingFang SC"
    return "Noto Sans CJK SC"


def mono_font_family() -> str:
    system = platform.system()
    if system == "Windows":
        return "Consolas"
    if system == "Darwin":
        return "Menlo"
    return "DejaVu Sans Mono"


UI_FONT = ui_font_family()
MONO_FONT = mono_font_family()
UI_SIZE = 9


# ── 设计令牌 ─────────────────────────────────────────────────


@dataclass(frozen=True)
class Tokens:
    """一套主题的语义色令牌。"""

    # 表面与文本
    bg: str
    surface: str
    surface_alt: str
    fg: str
    fg_muted: str
    border: str
    muted: str
    # 品牌与语义色
    primary: str
    on_primary: str
    secondary: str
    accent: str
    success: str
    danger: str
    danger_soft: str
    on_filled: str  # 语义填充色（success/accent/danger）上的文字色
    # 图表曲线
    plot_spectrum: str
    plot_potential: str
    plot_endpoint: str
    plot_scatter: str
    plot_scatter_ph: str
    plot_fit: str


LIGHT = Tokens(
    bg="#F3F4F5",
    surface="#FFFFFF",
    surface_alt="#ECEDEF",
    fg="#1F2328",
    fg_muted="#5C626A",
    border="#D4D7DB",
    muted="#E4E6E9",
    primary="#3A4149",
    on_primary="#FFFFFF",
    secondary="#6E747B",
    accent="#9A6B1E",
    success="#2E6B4F",
    danger="#A63D33",
    danger_soft="#F5EAE9",
    on_filled="#FFFFFF",
    plot_spectrum="#3E5C77",
    plot_potential="#4E7A5F",
    plot_endpoint="#A63D33",
    plot_scatter="#3E5C77",
    plot_scatter_ph="#6B5B7E",
    plot_fit="#A63D33",
)

DARK = Tokens(
    bg="#1C1E21",
    surface="#24262A",
    surface_alt="#2B2E33",
    fg="#E3E5E8",
    fg_muted="#9BA1A8",
    border="#3D424A",
    muted="#31353B",
    primary="#B8BEC6",
    on_primary="#1B1D20",
    secondary="#7A818A",
    accent="#C09A5B",
    success="#5E9C77",
    danger="#C05A4E",
    danger_soft="#372B29",
    on_filled="#1B1D20",
    plot_spectrum="#8FA9BF",
    plot_potential="#83A98F",
    plot_endpoint="#CC7B6F",
    plot_scatter="#8FA9BF",
    plot_scatter_ph="#A08FB3",
    plot_fit="#CC7B6F",
)


# ── ttkbootstrap 自定义主题（与令牌同 palette，导入时注册）──────────

_TTKB_THEMES: dict[str, dict] = {
    "instrument-light": {
        "type": "light",
        "colors": {
            "primary": LIGHT.primary,
            "secondary": LIGHT.secondary,
            "success": LIGHT.success,
            "info": "#546B7A",
            "warning": LIGHT.accent,
            "danger": LIGHT.danger,
            "light": "#F4F5F6",
            "dark": "#21252A",
            "bg": LIGHT.bg,
            "fg": LIGHT.fg,
            "selectbg": "#3F4750",
            "selectfg": "#FFFFFF",
            "border": "#C9CDD2",
            "inputfg": LIGHT.fg,
            "inputbg": "#FFFFFF",
            "active": "#E3E5E8",
        },
    },
    "instrument-dark": {
        "type": "dark",
        "colors": {
            "primary": DARK.primary,
            "secondary": DARK.secondary,
            "success": DARK.success,
            "info": "#6E8B99",
            "warning": DARK.accent,
            "danger": DARK.danger,
            "light": "#2A2D31",
            "dark": "#E2E4E7",
            "bg": DARK.bg,
            "fg": DARK.fg,
            "selectbg": "#4A5058",
            "selectfg": "#F2F3F4",
            "border": DARK.border,
            "inputfg": DARK.fg,
            "inputbg": DARK.surface,
            "active": "#34383E",
        },
    },
}

for _name, _def in _TTKB_THEMES.items():
    USER_THEMES.setdefault(_name, _def)


@dataclass(frozen=True)
class Theme:
    key: str
    ttkb_theme: str
    tokens: Tokens


THEMES: dict[str, Theme] = {
    "light": Theme(key="light", ttkb_theme="instrument-light", tokens=LIGHT),
    "dark": Theme(key="dark", ttkb_theme="instrument-dark", tokens=DARK),
}

MODES = ("light", "dark", "system")

_current_key = "light"
_subs: list[Callable[[], None]] = []


def current_tokens() -> Tokens:
    return THEMES[_current_key].tokens


def current_key() -> str:
    """当前实际生效的主题 key（'light' | 'dark'）。"""
    return _current_key


# ── matplotlib 中文字体设置 ────────────────────────────────────


def _setup_matplotlib_fonts() -> None:
    """配置 matplotlib 中文字体（解决 Glyph missing 警告）。"""
    candidates = []
    system = platform.system()
    if system == "Windows":
        candidates = ["Microsoft YaHei", "SimHei", "Microsoft JhengHei"]
    elif system == "Darwin":
        candidates = ["PingFang SC", "Heiti SC", "STHeiti"]
    else:
        candidates = ["WenQuanYi Micro Hei", "Noto Sans CJK SC", "Droid Sans Fallback"]

    available = {f.name for f in font_manager.fontManager.ttflist}
    for name in candidates:
        if name in available:
            rcParams["font.sans-serif"] = [name, "DejaVu Sans"]
            rcParams["axes.unicode_minus"] = False
            return
    rcParams["axes.unicode_minus"] = False


# ── 系统暗色检测 ─────────────────────────────────────────────


def _system_is_dark() -> bool:
    system = platform.system()
    if system == "Windows":
        try:
            import winreg

            key = winreg.OpenKey(
                winreg.HKEY_CURRENT_USER,
                r"Software\Microsoft\Windows\CurrentVersion\Themes\Personalize",
            )
            value, _ = winreg.QueryValueEx(key, "AppsUseLightTheme")
            winreg.CloseKey(key)
            return value == 0
        except Exception:
            return False
    elif system == "Darwin":
        import os

        return os.environ.get("USER_UI_THEME", "").lower() == "dark"
    return False


def resolve_theme(mode: str) -> Theme:
    key = (
        "dark"
        if mode == "system" and _system_is_dark()
        else (mode if mode in THEMES else "light")
    )
    return THEMES[key]


# ── Windows 原生标题栏/边框 ──────────────────────────────────


def set_native_titlebar(dark: bool, root: tk.Misc) -> None:
    """切换 Windows 原生窗口边框（非客户区）的暗色模式。

    tkinter/ttk 只绘制客户区，标题栏由 DWM 绘制，需通过
    DwmSetWindowAttribute(DWMWA_USE_IMMERSIVE_DARK_MODE) 显式切换。
    注意（Win10 实测 21H2）：DWM 只在窗口映射时读取该属性——
    启动时须在 deiconify 之前调用；已映射的窗口需要
    hide→set→show 循环才能在运行时切换。Win11 无此限制。
    """
    if platform.system() != "Windows":
        return
    try:
        import ctypes

        u32 = ctypes.windll.user32
        dwm = ctypes.windll.dwmapi
        # withdrawn 且尚未处理事件时，框架窗口可能尚未创建，先强制空闲处理
        root.update_idletasks()
        hwnd = u32.GetParent(root.winfo_id()) or int(root.wm_frame(), 16)

        mapped = bool(root.winfo_viewable())
        needs_remap = mapped and sys.getwindowsversion().build < 22000
        if needs_remap:
            u32.ShowWindow(hwnd, 0)  # SW_HIDE

        value = ctypes.c_int(1 if dark else 0)
        # 20 = Win10 18985+/Win11；19 = 早期 Win10
        for attr in (20, 19):
            if dwm.DwmSetWindowAttribute(
                hwnd, attr, ctypes.byref(value), ctypes.sizeof(value)
            ) == 0:
                break
        # 强制非客户区重绘
        u32.SetWindowPos(hwnd, 0, 0, 0, 0, 0, 0x0001 | 0x0002 | 0x0004 | 0x0020)

        if needs_remap:
            u32.ShowWindow(hwnd, 5)  # SW_SHOW
            u32.SetForegroundWindow(hwnd)
    except Exception:
        pass


# ── 自定义样式（每次主题切换后重新配置）──────────────────────


def _configure_styles(style: ttkbootstrap.Style, t: Tokens) -> None:
    ui = (UI_FONT, UI_SIZE)
    mono_big = (MONO_FONT, 15, "bold")

    style.configure(".", font=ui)

    # 工具栏 / 状态栏
    style.configure("Toolbar.TFrame", background=t.surface)
    style.configure("Toolbar.TLabel", background=t.surface, foreground=t.fg_muted, font=ui)
    style.configure("Statusbar.TFrame", background=t.surface)
    style.configure("Status.TLabel", background=t.surface, foreground=t.fg_muted, font=ui)
    style.configure(
        "Conn.TLabel", background=t.surface, foreground=t.fg_muted, font=(UI_FONT, UI_SIZE, "bold")
    )

    # 状态芯片（状态栏左侧）
    chips = {
        "ChipIdle": (t.muted, t.fg_muted),
        "ChipRun": (t.primary, t.on_primary),
        "ChipWarn": (t.accent, t.on_filled),
        "ChipOk": (t.success, t.on_filled),
        "ChipErr": (t.danger, t.on_filled),
    }
    for name, (bgc, fgc) in chips.items():
        style.configure(
            f"{name}.TLabel",
            background=bgc,
            foreground=fgc,
            font=(UI_FONT, UI_SIZE, "bold"),
            padding=(10, 3),
        )

    # KPI 卡片（结果面板）
    style.configure("Kpi.TFrame", background=t.surface_alt, borderwidth=1, relief="solid")
    style.configure("Kpi.TLabel", background=t.surface_alt, foreground=t.fg_muted, font=(UI_FONT, 8))
    style.configure("KpiAccent.TLabel", background=t.surface_alt, foreground=t.accent, font=mono_big)
    style.configure("KpiSuccess.TLabel", background=t.surface_alt, foreground=t.success, font=mono_big)
    style.configure("KpiUnit.TLabel", background=t.surface_alt, foreground=t.fg_muted, font=(UI_FONT, 8))

    # 文本层级
    style.configure("Section.TLabel", foreground=t.fg, font=(UI_FONT, 11, "bold"))
    style.configure("Muted.TLabel", foreground=t.fg_muted, font=ui)
    style.configure("Subtle.TLabel", foreground=t.fg_muted, font=(UI_FONT, 8))
    style.configure("TLabelframe.Label", foreground=t.fg)

    # 工具栏分组卡片 / 急停区
    style.configure("GroupCard.TFrame", background=t.surface, borderwidth=1, relief="solid")
    style.configure(
        "GroupCaption.TLabel", background=t.surface, foreground=t.fg_muted, font=(UI_FONT, 8)
    )
    style.configure("GroupLabel.TLabel", background=t.surface, foreground=t.fg, font=ui)
    style.configure("EstopZone.TFrame", background=t.danger_soft, borderwidth=1, relief="solid")
    style.configure("EstopZoneBody.TFrame", background=t.danger_soft)
    style.configure("EstopZone.TLabel", background=t.danger_soft, foreground=t.danger, font=(UI_FONT, 8))

    # 图表空状态覆盖层
    style.configure("Overlay.TLabel", background=t.surface, foreground=t.fg_muted, font=(UI_FONT, 11))

    # 选项卡 / 表格
    style.configure("TNotebook.Tab", padding=(14, 7), font=ui)
    style.configure("Treeview", rowheight=26)
    style.configure("Treeview.Heading", font=(UI_FONT, UI_SIZE - 1, "bold"))


# ── 应用主题 ─────────────────────────────────────────────────


def apply_theme(mode: str, plots: list | None = None) -> str:
    """应用主题，返回实际生效的 key ('light'|'dark')。

    Args:
        mode: 'light' | 'dark' | 'system'
        plots: _BlitPlot 实例列表，用于更新 matplotlib 配色
    """
    global _current_key
    theme = resolve_theme(mode)
    _current_key = theme.key

    style = ttkbootstrap.Style.get_instance()
    if style is not None:
        style.theme_use(theme.ttkb_theme)
        _configure_styles(style, theme.tokens)

    if plots:
        _apply_plot_colors(theme.tokens, plots)

    for cb in tuple(_subs):
        try:
            cb()
        except Exception:
            import traceback

            traceback.print_exc()

    return theme.key


def _apply_plot_colors(t: Tokens, plots: list) -> None:
    """更新所有 matplotlib 图表的背景/文本配色。"""
    for pw in plots:
        if pw is None:
            continue
        ax = getattr(pw, "_ax", None)
        fig = getattr(pw, "_fig", None)
        if ax is not None:
            ax.set_facecolor(t.surface)
            ax.tick_params(colors=t.fg_muted)
            for spine in ax.spines.values():
                spine.set_edgecolor(t.border)
            ax.xaxis.label.set_color(t.fg_muted)
            ax.yaxis.label.set_color(t.fg_muted)
            ax.title.set_color(t.fg)
        if fig is not None:
            fig.set_facecolor(t.surface)
        if hasattr(pw, "_request_full_redraw"):
            pw._request_full_redraw()
        if hasattr(pw, "refresh"):
            pw.refresh()


def subscribe(cb: Callable[[], None]) -> None:
    """订阅主题变化（切换完成后回调，用于更新语义色）。"""
    if cb not in _subs:
        _subs.append(cb)


def unsubscribe(cb: Callable[[], None]) -> None:
    if cb in _subs:
        _subs.remove(cb)


__all__ = [
    "DARK",
    "LIGHT",
    "MODES",
    "MONO_FONT",
    "THEMES",
    "UI_FONT",
    "UI_SIZE",
    "Tokens",
    "_setup_matplotlib_fonts",
    "apply_theme",
    "current_tokens",
    "resolve_theme",
    "subscribe",
    "unsubscribe",
]
