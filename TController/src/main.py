"""AutoTitrator 控制器 — 入口（ttkbootstrap）。"""

import sys

import ttkbootstrap

from gui import i18n
from gui.main_window import MainWindow
from gui.settings import load_settings
from gui.themes import _setup_matplotlib_fonts, resolve_theme


def main() -> None:
    # 配置 matplotlib 中文字体（解决 CJK Glyph missing 警告）
    _setup_matplotlib_fonts()

    settings = load_settings()
    i18n.set_language(settings["language"])
    theme_mode = settings["theme_mode"]
    theme = resolve_theme(theme_mode)

    root = ttkbootstrap.Window(themename=theme.ttkb_theme)
    # Win10 的 DWM 只在窗口映射时读取标题栏暗色属性：先隐藏，
    # 待 apply_theme 设置完成后再显示，避免启动时标题栏闪白
    root.withdraw()
    root.title(i18n.tr("app.title"))
    root.geometry("1360x920")
    root.minsize(1120, 760)

    mw = MainWindow(root, theme_mode=theme_mode)
    mw.pack(fill="both", expand=True)
    # 应用自定义样式与图表配色（theme_use 之后才能配置样式）
    from gui.themes import apply_theme

    apply_theme(theme_mode, plots=mw._theme_plots())
    root.deiconify()

    if settings["record"] is False:
        mw._rec_var.set(False)
        mw._recording = False
    if isinstance(settings.get("baud"), int):
        mw._baud_cb.set(str(settings["baud"]))

    def _on_close() -> None:
        mw.on_close()
        root.destroy()
        sys.exit(0)

    root.protocol("WM_DELETE_WINDOW", _on_close)
    root.mainloop()


if __name__ == "__main__":
    main()
