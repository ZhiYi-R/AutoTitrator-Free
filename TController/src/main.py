"""AutoTitrator 控制器 — 入口（ttkbootstrap）。"""

import sys

import ttkbootstrap
from gui.main_window import MainWindow
from gui.themes import _setup_matplotlib_fonts


def main() -> None:
    # 配置 matplotlib 中文字体（解决 CJK Glyph missing 警告）
    _setup_matplotlib_fonts()

    root = ttkbootstrap.Window(themename="litera")
    root.title("多模态自动滴定控制器")
    root.geometry("1280x900")

    mw = MainWindow(root)
    mw.pack(fill="both", expand=True)

    def _on_close() -> None:
        mw.on_close()
        root.destroy()
        sys.exit(0)

    root.protocol("WM_DELETE_WINDOW", _on_close)
    root.mainloop()


if __name__ == "__main__":
    main()
