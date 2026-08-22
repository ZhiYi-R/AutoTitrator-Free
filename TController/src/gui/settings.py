"""
用户设置持久化 — language / theme_mode / baud / record / last_port。

保存于 data/settings.json（与 calibre.npz 同目录，开发/打包模式均可写）。
"""

from __future__ import annotations

import json
import os

from DataProcessor._path import CALIBRE_PATH

from gui.i18n import DEFAULT_LANG, LANGS

SETTINGS_PATH = os.path.join(os.path.dirname(CALIBRE_PATH), "settings.json")

DEFAULTS: dict = {
    "language": DEFAULT_LANG,
    "theme_mode": "system",  # light | dark | system
    "baud": 115200,
    "record": True,
    "last_port": "",  # 上次成功连接的串口设备路径
}


def load_settings() -> dict:
    """读取设置（缺失/损坏时回退默认值）。"""
    merged = dict(DEFAULTS)
    try:
        with open(SETTINGS_PATH, encoding="utf-8") as f:
            data = json.load(f)
        if isinstance(data, dict):
            for k in DEFAULTS:
                if k in data:
                    merged[k] = data[k]
    except (OSError, json.JSONDecodeError):
        pass
    # 合法性兜底
    if merged["language"] not in LANGS:
        merged["language"] = DEFAULT_LANG
    if merged["theme_mode"] not in ("light", "dark", "system"):
        merged["theme_mode"] = "system"
    if merged["baud"] != 115200:
        merged["baud"] = 115200
    return merged


def save_settings(**patch: object) -> None:
    """合并写入设置（单项更新时不覆盖其它键）。"""
    data = load_settings()
    for k, v in patch.items():
        if k in DEFAULTS:
            data[k] = v
    try:
        with open(SETTINGS_PATH, "w", encoding="utf-8") as f:
            json.dump(data, f, ensure_ascii=False, indent=2)
    except OSError:
        pass


__all__ = ["DEFAULTS", "SETTINGS_PATH", "load_settings", "save_settings"]
