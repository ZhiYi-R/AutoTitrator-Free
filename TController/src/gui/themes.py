"""
主题管理模块 — 深色/浅色/跟随系统。
用 QPalette 控制全局配色（保留 Fusion 风格），pyqtgraph API 更新图表。
"""
from __future__ import annotations

from dataclasses import dataclass, field

from PySide6.QtCore import Qt
from PySide6.QtGui import QColor, QPalette
from PySide6.QtWidgets import QApplication


@dataclass
class PlotColors:
    """pyqtgraph 图表配色。"""
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
    plot: PlotColors = field(default_factory=PlotColors)


# ── 调色板 ──────────────────────────────────────────────────

def _make_palette(dark: bool) -> QPalette:
    p = QPalette()
    if dark:
        p.setColor(QPalette.ColorRole.Window, QColor("#1e1e1e"))
        p.setColor(QPalette.ColorRole.WindowText, QColor("#d4d4d4"))
        p.setColor(QPalette.ColorRole.Base, QColor("#252526"))
        p.setColor(QPalette.ColorRole.AlternateBase, QColor("#2d2d2d"))
        p.setColor(QPalette.ColorRole.ToolTipBase, QColor("#2d2d2d"))
        p.setColor(QPalette.ColorRole.ToolTipText, QColor("#d4d4d4"))
        p.setColor(QPalette.ColorRole.Text, QColor("#d4d4d4"))
        p.setColor(QPalette.ColorRole.Button, QColor("#2d2d2d"))
        p.setColor(QPalette.ColorRole.ButtonText, QColor("#d4d4d4"))
        p.setColor(QPalette.ColorRole.BrightText, QColor("#ffffff"))
        p.setColor(QPalette.ColorRole.Link, QColor("#4da6ff"))
        p.setColor(QPalette.ColorRole.Highlight, QColor("#094771"))
        p.setColor(QPalette.ColorRole.HighlightedText, QColor("#ffffff"))
    else:
        p.setColor(QPalette.ColorRole.Window, QColor("#F5F5F5"))
        p.setColor(QPalette.ColorRole.WindowText, QColor("#1a1a1a"))
        p.setColor(QPalette.ColorRole.Base, QColor("#ffffff"))
        p.setColor(QPalette.ColorRole.AlternateBase, QColor("#f8f8f8"))
        p.setColor(QPalette.ColorRole.ToolTipBase, QColor("#ffffff"))
        p.setColor(QPalette.ColorRole.ToolTipText, QColor("#1a1a1a"))
        p.setColor(QPalette.ColorRole.Text, QColor("#1a1a1a"))
        p.setColor(QPalette.ColorRole.Button, QColor("#e8e8e8"))
        p.setColor(QPalette.ColorRole.ButtonText, QColor("#1a1a1a"))
        p.setColor(QPalette.ColorRole.BrightText, QColor("#000000"))
        p.setColor(QPalette.ColorRole.Link, QColor("#2980b9"))
        p.setColor(QPalette.ColorRole.Highlight, QColor("#2980b9"))
        p.setColor(QPalette.ColorRole.HighlightedText, QColor("#ffffff"))
    return p


# ── 主题定义 ─────────────────────────────────────────────────

_LIGHT_PLOT = PlotColors(
    background="#FFFFFF", foreground="#000000",
    curve="#2980b9", curve_fill="rgba(41,128,185,50)",
    curve_potential="#27ae60", curve_potential_fill="rgba(39,174,96,40)",
    endpoint_line="#e74c3c",
    scatter="#2980b9", scatter_ph="#8e44ad", fit_line="#e74c3c",
)

_DARK_PLOT = PlotColors(
    background="#1e1e1e", foreground="#d4d4d4",
    curve="#4da6ff", curve_fill="rgba(77,166,255,50)",
    curve_potential="#2ecc71", curve_potential_fill="rgba(46,204,113,40)",
    endpoint_line="#e74c3c",
    scatter="#4da6ff", scatter_ph="#bb8cf2", fit_line="#e74c3c",
)

THEMES: dict[str, Theme] = {
    "light": Theme(name="浅色", plot=_LIGHT_PLOT),
    "dark": Theme(name="深色", plot=_DARK_PLOT),
}

MODE_NAMES = {"light": "浅色", "dark": "深色", "system": "跟随系统"}


# ── 系统检测 ─────────────────────────────────────────────────

def _system_is_dark() -> bool:
    app = QApplication.instance()
    if app is None:
        return False
    bg = app.palette().color(QPalette.ColorRole.Window)
    luma = 0.2126 * bg.red() + 0.7152 * bg.green() + 0.0722 * bg.blue()
    return luma < 128


# ── 应用主题 ─────────────────────────────────────────────────

def resolve_theme(mode: str) -> tuple[str, Theme]:
    key = "dark" if mode == "system" and _system_is_dark() else (
        mode if mode in THEMES else "light")
    return key, THEMES.get(key, THEMES["light"])


def apply_theme(mode: str, plots: list | None = None) -> str:
    """应用主题，返回实际生效的 key ('light'|'dark')。"""
    key, theme = resolve_theme(mode)
    app = QApplication.instance()
    if app:
        palette = _make_palette(key == "dark")
        app.setPalette(palette)
        app.setStyleSheet("")  # 清除 QSS，避免与 Fusion 冲突
    if plots:
        _apply_plot_colors(theme.plot, plots)
    return key


def _apply_plot_colors(pc: PlotColors, plots: list) -> None:
    for pw in plots:
        if pw is None:
            continue
        pw.setBackground(pc.background)
        for axis_name in ("bottom", "left"):
            ax = pw.getAxis(axis_name)
            if ax:
                ax.setPen(pc.foreground)
                ax.setTextPen(pc.foreground)


__all__ = [
    "Theme", "PlotColors", "THEMES", "MODE_NAMES",
    "resolve_theme", "apply_theme",
]
