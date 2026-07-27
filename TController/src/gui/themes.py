"""
主题管理模块 — 深色/浅色/跟随系统。

ttkbootstrap 内置主题切换（一行 style.theme_use），matplotlib 图表
通过 PlotColors 配色手动更新。
"""

from __future__ import annotations

import platform
from dataclasses import dataclass, field

import ttkbootstrap
from matplotlib import font_manager, rcParams


@dataclass
class PlotColors:
    """matplotlib 图表配色。"""

    background: str = "#FFFFFF"
    foreground: str = "#000000"

    curve: str = "#2980b9"
    curve_fill: str = "rgba(41,128,185,50)"
    curve_potential: str = "#27ae60"
    curve_potential_fill: str = "rgba(39,174,96,40)"
    endpoint_line: str = "#e74c3c"

    scatter: str = "#2980b9"
    scatter_ph: str = "#8e44ad"
    fit_line: str = "#e74c3c"


@dataclass
class Theme:
    name: str
    ttkb_theme: str
    """ttkbootstrap 主题名。"""
    plot: PlotColors = field(default_factory=PlotColors)


# ── 主题定义 ─────────────────────────────────────────────────

_LIGHT_PLOT = PlotColors(
    background="#FFFFFF",
    foreground="#000000",
    curve="#2980b9",
    curve_fill="rgba(41,128,185,50)",
    curve_potential="#27ae60",
    curve_potential_fill="rgba(39,174,96,40)",
    endpoint_line="#e74c3c",
    scatter="#2980b9",
    scatter_ph="#8e44ad",
    fit_line="#e74c3c",
)

_DARK_PLOT = PlotColors(
    background="#1e1e1e",
    foreground="#d4d4d4",
    curve="#4da6ff",
    curve_fill="rgba(77,166,255,50)",
    curve_potential="#2ecc71",
    curve_potential_fill="rgba(46,204,113,40)",
    endpoint_line="#e74c3c",
    scatter="#4da6ff",
    scatter_ph="#bb8cf2",
    fit_line="#e74c3c",
)

THEMES: dict[str, Theme] = {
    "light": Theme(name="浅色", ttkb_theme="litera", plot=_LIGHT_PLOT),
    "dark": Theme(name="深色", ttkb_theme="darkly", plot=_DARK_PLOT),
}

MODE_NAMES = {"light": "浅色", "dark": "深色", "system": "跟随系统"}


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
    # 无中文字体时仅禁用负号回退
    rcParams["axes.unicode_minus"] = False


# ── 系统检测 ─────────────────────────────────────────────────


def _system_is_dark() -> bool:
    """检测系统是否暗色模式。"""
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


# ── 应用主题 ─────────────────────────────────────────────────


def resolve_theme(mode: str) -> tuple[str, Theme]:
    key = (
        "dark"
        if mode == "system" and _system_is_dark()
        else (mode if mode in THEMES else "light")
    )
    return key, THEMES.get(key, THEMES["light"])


def apply_theme(mode: str, plots: list | None = None) -> str:
    """应用主题，返回实际生效的 key ('light'|'dark')。

    Args:
        mode: 'light' | 'dark' | 'system'
        plots: _BlitPlot 实例列表，用于更新 matplotlib 配色
    """
    key, theme = resolve_theme(mode)

    # ttkbootstrap 主题切换
    style = ttkbootstrap.Style.get_instance()
    if style is not None:
        style.theme_use(theme.ttkb_theme)

    # matplotlib 图表配色
    if plots:
        _apply_plot_colors(theme.plot, plots)

    return key


def _apply_plot_colors(pc: PlotColors, plots: list) -> None:
    """更新所有 matplotlib 图表的配色。"""
    for pw in plots:
        if pw is None:
            continue
        ax = getattr(pw, "_ax", None)
        fig = getattr(pw, "_fig", None)
        if ax is not None:
            ax.set_facecolor(pc.background)
            ax.tick_params(colors=pc.foreground)
            for spine in ax.spines.values():
                spine.set_edgecolor(pc.foreground)
            ax.xaxis.label.set_color(pc.foreground)
            ax.yaxis.label.set_color(pc.foreground)
            ax.title.set_color(pc.foreground)
        if fig is not None:
            fig.set_facecolor(pc.background)
        # 标记需要全量重绘
        if hasattr(pw, "_request_full_redraw"):
            pw._request_full_redraw()
        if hasattr(pw, "refresh"):
            pw.refresh()


__all__ = [
    "MODE_NAMES",
    "THEMES",
    "PlotColors",
    "Theme",
    "_setup_matplotlib_fonts",
    "apply_theme",
    "resolve_theme",
]
