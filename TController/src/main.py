"""AutoTitrator 控制器 — 入口。"""

import sys

from gui.main_window import MainWindow
from PySide6.QtGui import QFont, QFontDatabase
from PySide6.QtWidgets import QApplication


def main() -> None:
    app = QApplication(sys.argv)
    app.setApplicationName("TController")
    app.setOrganizationName("AutoTitrator")
    app.setStyle("Fusion")

    mono = QFontDatabase.systemFont(QFontDatabase.SystemFont.FixedFont)
    font = QFont(mono.family() if mono else "monospace", 10)
    app.setFont(font)

    w = MainWindow()
    w.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
