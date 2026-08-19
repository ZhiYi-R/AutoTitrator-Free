"""
i18n 模块 — 轻量运行时国际化（zh_CN / en_US）。

词条文件位于 gui/locales/<lang>.json（嵌套结构，加载时展平为点分键）。

用法::

    from gui.i18n import tr, set_language, subscribe

    label = ttk.Label(parent, text=tr("toolbar.connect"))
    subscribe(my_refresh_callback)      # 语言切换后刷新静态文本
    set_language("en_US")               # 切换并通知所有订阅者

带参数的词条使用命名占位符::

    tr("status.endpoint_t1", vol="1.234")
"""

from __future__ import annotations

import json
import os
from collections.abc import Callable

_LOCALES_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "locales")

# 语言代码 → 该语言下的自称（显示用，不翻译）
LANGS: dict[str, str] = {
    "zh_CN": "简体中文",
    "en_US": "English",
}

DEFAULT_LANG = "zh_CN"
FALLBACK_LANG = "zh_CN"


def _flatten(node: dict, prefix: str = "") -> dict[str, str]:
    """嵌套 dict → {'a.b.c': 'text'}。"""
    out: dict[str, str] = {}
    for k, v in node.items():
        key = f"{prefix}.{k}" if prefix else k
        if isinstance(v, dict):
            out.update(_flatten(v, key))
        else:
            out[key] = str(v)
    return out


class _Translator:
    def __init__(self) -> None:
        self._lang = DEFAULT_LANG
        self._dicts: dict[str, dict[str, str]] = {}
        self._subs: list[Callable[[], None]] = []
        for code in LANGS:
            self._load(code)

    def _load(self, code: str) -> None:
        path = os.path.join(_LOCALES_DIR, f"{code}.json")
        try:
            with open(path, encoding="utf-8") as f:
                self._dicts[code] = _flatten(json.load(f))
        except (OSError, json.JSONDecodeError):
            self._dicts[code] = {}

    # ---- 语言 ----

    @property
    def language(self) -> str:
        return self._lang

    def set_language(self, code: str) -> bool:
        """切换语言；若有变化则通知订阅者。返回是否实际切换。"""
        if code not in LANGS or code == self._lang:
            return False
        self._lang = code
        self._notify()
        return True

    # ---- 翻译 ----

    def tr(self, key: str, **kwargs: object) -> str:
        table = self._dicts.get(self._lang, {})
        text = table.get(key)
        if text is None:
            text = self._dicts.get(FALLBACK_LANG, {}).get(key, key)
        if kwargs:
            try:
                return text.format(**kwargs)
            except (KeyError, IndexError, ValueError):
                return text
        return text

    # ---- 订阅（语言切换后刷新静态文本）----

    def subscribe(self, cb: Callable[[], None]) -> None:
        if cb not in self._subs:
            self._subs.append(cb)

    def unsubscribe(self, cb: Callable[[], None]) -> None:
        if cb in self._subs:
            self._subs.remove(cb)

    def _notify(self) -> None:
        for cb in list(self._subs):
            try:
                cb()
            except Exception:  # 单个控件刷新失败不应阻断其它控件
                import traceback

                traceback.print_exc()


_inst = _Translator()

tr = _inst.tr
set_language = _inst.set_language
subscribe = _inst.subscribe
unsubscribe = _inst.unsubscribe


def current_language() -> str:
    return _inst.language


__all__ = [
    "DEFAULT_LANG",
    "LANGS",
    "current_language",
    "set_language",
    "subscribe",
    "tr",
    "unsubscribe",
]
