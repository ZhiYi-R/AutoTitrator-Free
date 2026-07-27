"""滴定计算结果面板（ttkbootstrap）。"""

from __future__ import annotations

import tkinter as tk
from collections.abc import Callable
from tkinter import font as tkfont

import ttkbootstrap as ttk


class ResultsPanel(ttk.Frame):
    """右侧计算面板：化学计量数输入 + 终点体积/浓度显示 + 进样进度。"""

    def __init__(self, parent: tk.Misc, **kwargs) -> None:
        super().__init__(parent, **kwargs)
        self._maxwidth = 240

        layout = ttk.Frame(self)
        layout.pack(fill="both", expand=True, padx=8, pady=8)

        title = ttk.Label(layout, text="滴定计算", font=("", 11, "bold"))
        title.pack(anchor="w")

        # ---- 电极选择 ----
        self._electrode_combo = ttk.Combobox(layout, state="readonly")
        self._electrode_combo.pack(fill="x", pady=(8, 4))
        self._electrode_combo.bind("<<ComboboxSelected>>", self._on_combo_changed)
        self._electrode_data: list[tuple] = []
        self._electrode_values: list[str] = []  # 显示文本
        self._electrode_map: dict[str, tuple | None] = {}  # 显示文本 → data
        self._on_electrode_cb: Callable[[object], None] | None = None

        # ---- 化学计量数 ----
        stoich_group = ttk.LabelFrame(layout, text="化学计量数")
        stoich_group.pack(fill="x", pady=4)

        self._n_std = self._make_spin(stoich_group, 0.1, 100.0, 1.0, 0.1, 1)
        self._add_form_row(stoich_group, "标准液 (n₁):", self._n_std)

        self._n_analyte = self._make_spin(stoich_group, 0.1, 100.0, 1.0, 0.1, 1)
        self._add_form_row(stoich_group, "待测液 (n₂):", self._n_analyte)

        # ---- 标准液浓度 ----
        conc_group = ttk.LabelFrame(layout, text="标准液浓度")
        conc_group.pack(fill="x", pady=4)

        self._c_std = self._make_spin(conc_group, 0.0001, 100.0, 0.1, 0.01, 4)
        self._add_form_row(conc_group, "C₁ (mol/L):", self._c_std)

        # ---- 待测液 ----
        sample_group = ttk.LabelFrame(layout, text="待测液")
        sample_group.pack(fill="x", pady=4)

        self._v_sample_label = ttk.Label(sample_group, text="—", font=("monospace", 10))
        self._add_form_row(sample_group, "取样体积 (mL):", self._v_sample_label)

        self._v_now_label = ttk.Label(sample_group, text="— V", font=("monospace", 10))
        self._add_form_row(sample_group, "当前电压:", self._v_now_label)

        # ---- 进样进度 ----
        self._inject_group = ttk.LabelFrame(layout, text="进样进度")
        self._inject_group.pack(fill="x", pady=4)
        self._inject_bar = ttk.Progressbar(self._inject_group, maximum=100)
        self._inject_bar.pack(fill="x", padx=8, pady=(4, 0))
        self._eta_label = ttk.Label(
            self._inject_group, text="", anchor="center", font=("", 9)
        )
        self._eta_label.pack(fill="x", padx=8, pady=(0, 4))
        self._inject_group.pack_forget()  # 默认隐藏

        # ---- 分隔 ----
        ttk.Separator(layout, orient="horizontal").pack(fill="x", pady=8)

        # ---- 结果 ----
        result_group = ttk.LabelFrame(layout, text="结果")
        result_group.pack(fill="x", pady=4)

        self._v_ep_label = ttk.Label(
            result_group,
            text="—",
            font=("monospace", 10, "bold"),
            foreground="#e67e22",
        )
        self._add_form_row(result_group, "终点体积 (mL):", self._v_ep_label)

        bold_mono = tkfont.Font(family="monospace", size=11, weight="bold")
        self._c_x_label = ttk.Label(
            result_group,
            text="—",
            font=bold_mono,
            foreground="#27ae60",
        )
        self._add_form_row(result_group, "Cₓ (mol/L):", self._c_x_label)

        # 内部状态
        self._endpoint_volume: float | None = None
        self._sample_volume: float = 0.0
        self._inject_target: int = 0
        self._inject_target_vol: float = 0.0

    # ---- 工具 ----

    @staticmethod
    def _make_spin(
        parent: tk.Misc,
        lo: float,
        hi: float,
        init: float,
        step: float,
        decimals: int,
    ) -> ttk.Spinbox:
        fmt = f"%.{decimals}f"
        sb = ttk.Spinbox(
            parent,
            from_=lo,
            to=hi,
            increment=step,
            format=fmt,
            width=10,
        )
        sb.set(init)
        return sb

    @staticmethod
    def _add_form_row(parent: tk.Misc, label: str, widget: tk.Widget) -> None:
        row = ttk.Frame(parent)
        row.pack(fill="x", padx=8, pady=2)
        ttk.Label(row, text=label).pack(side="left")
        widget.pack(side="right")

    def _spin_value(self, sb: ttk.Spinbox) -> float:
        try:
            return float(sb.get())
        except (ValueError, tk.TclError):
            return 0.0

    # ---- 公开接口 ----

    def set_electrodes(self, electrode_list: list[tuple]) -> None:
        self._electrode_data = electrode_list
        self._electrode_values = ["Raw Potential (V)"]
        self._electrode_map = {"Raw Potential (V)": None}
        for name, slope, intercept, unit in electrode_list:
            disp = f"{name} ({unit})"
            self._electrode_values.append(disp)
            self._electrode_map[disp] = (name, slope, intercept, unit)
        self._electrode_combo["values"] = self._electrode_values
        if self._electrode_values:
            self._electrode_combo.set(self._electrode_values[0])

    def on_electrode_changed(self, cb: Callable[[object], None]) -> None:
        """注册电极选择变化回调（替代 Qt Signal）。"""
        self._on_electrode_cb = cb

    def _on_combo_changed(self, _event: object = None) -> None:
        disp = self._electrode_combo.get()
        data = self._electrode_map.get(disp)
        if self._on_electrode_cb is not None:
            self._on_electrode_cb(data)

    def set_sample_volume(self, vol: float) -> None:
        self._sample_volume = vol
        self._v_sample_label.config(text=f"{vol:.2f}")
        self._recalc()

    def set_endpoint(self, volume: float) -> None:
        self._endpoint_volume = volume
        self._v_ep_label.config(text=f"{volume:.4f}")
        self._recalc()

    def reset_endpoint(self) -> None:
        self._endpoint_volume = None
        self._v_ep_label.config(text="—")
        self._c_x_label.config(text="—")

    def set_current_voltage(self, v: float) -> None:
        self._v_now_label.config(text=f"{v:.4f} V")

    # ---- 进样进度 ----

    def show_inject_progress(self, target_steps: int, target_vol: float = 0.0) -> None:
        self._inject_target = target_steps
        self._inject_target_vol = target_vol
        self._inject_bar["value"] = 0
        self._inject_bar["text"] = f"0.000 / {target_vol:.3f} mL"
        self._eta_label.config(text="")
        self._inject_group.pack(fill="x", pady=4)

    def update_inject_progress(self, pos: int, volume: float = 0.0) -> None:
        if self._inject_target <= 0:
            return
        pct = min(100, int(pos * 100 / self._inject_target))
        self._inject_bar["value"] = pct
        tv = self._inject_target_vol
        remaining = max(0, self._inject_target - pos)
        eta_sec = remaining // 1000
        if pct < 100 and remaining > 0:
            self._inject_bar["text"] = f"{volume:.3f} / {tv:.3f} mL  ({pct}%)"
            self._eta_label.config(
                text=f"ETA {eta_sec // 60:02d}:{eta_sec % 60:02d}"
            )
        else:
            self._inject_bar["text"] = "进样完成 ✓"
            self._eta_label.config(text="")

    def hide_inject_progress(self) -> None:
        self._eta_label.config(text="")
        self._inject_group.pack_forget()
        self._inject_bar["value"] = 0
        self._inject_bar["text"] = "等待开始"

    # ---- 内部 ----

    def _recalc(self) -> None:
        if self._endpoint_volume is None or self._endpoint_volume <= 0:
            self._c_x_label.config(text="—")
            return
        V_ep = self._endpoint_volume
        V_sample = self._sample_volume
        if V_sample <= 0:
            self._c_x_label.config(text="—")
            return

        n_std = self._spin_value(self._n_std)
        n_analyte = self._spin_value(self._n_analyte)
        C_std = self._spin_value(self._c_std)

        Cx = (C_std * V_ep * n_analyte) / (V_sample * n_std)
        self._c_x_label.config(text=f"{Cx:.6f}")


__all__ = ["ResultsPanel"]
