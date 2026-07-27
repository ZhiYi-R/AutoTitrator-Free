"""
路径解析工具：在开发模式与 Nuitka 打包模式下均能正确找到数据文件。

开发模式:  data/calibre.npz 位于仓库根目录
打包模式:  data/calibre.npz 位于可执行文件同级目录

采用文件系统探测，不依赖 sys.frozen 等 packager 特定属性。
"""

from __future__ import annotations

import os
import sys

_CALIBRE = "calibre.npz"


def _find() -> str:
    """按优先级搜索 calibre.npz，返回所在目录。"""
    # 1) exe 同级（Nuitka standalone / onefile 解压目录）
    exe_dir = os.path.dirname(os.path.abspath(sys.executable))
    if os.path.isfile(os.path.join(exe_dir, _CALIBRE)):
        return exe_dir

    # 2) 开发模式：相对此模块的 ../../data/
    dev = os.path.normpath(
        os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "data")
    )
    if os.path.isfile(os.path.join(dev, _CALIBRE)):
        return dev

    # 3) 兜底返回 exe 目录（即使文件不存在，报错信息更清晰）
    return exe_dir


CALIBRE_PATH = os.path.join(_find(), _CALIBRE)
"""calibre.npz 的完整路径（开发/打包均有效）。"""
