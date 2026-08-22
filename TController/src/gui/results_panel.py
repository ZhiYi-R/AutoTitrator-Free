"""滴定计算结果面板（ttkbootstrap）— KPI 卡片式结果展示。"""

from __future__ import annotations

import tkinter as tk
from collections.abc import Callable

import ttkbootstrap as ttk

from gui import i18n
from gui.themes import MONO_FONT
from gui.widgets import Card


class ResultsPanel(ttk.Frame):
    """右侧计算面板：参数输入 + 进样进度 + KPI 结果卡片。"""

    def __init__(
        self,
        parent: tk.Misc,
        record_var: tk.BooleanVar | None = None,
        record_command=None,
        **kwargs,
    ) -> None:
        super().__init__(parent, **kwargs)

        layout = ttk.Frame(self)
        layout.pack(fill="both", expand=True, padx=10, pady=10)

        # ---- 标题行：标题 + 记录开关 ----
        title_row = ttk.Frame(layout)
        title_row.pack(fill="x", pady=(0, 6))
        self._title = ttk.Label(
            title_row, text=i18n.tr("results.title"), style="Section.TLabel"
        )
        self._title.pack(side="left")
        if record_var is not None:
            self._rec_cb = ttk.Checkbutton(
                title_row,
                text=i18n.tr("toolbar.record"),
                variable=record_var,
                command=record_command,
            )
            self._rec_cb.pack(side="right")
        else:
            self._rec_cb = None

        # ---- 电极选择 ----
        self._electrode_label = ttk.Label(layout, text=i18n.tr("results.electrode"), style="Muted.TLabel")
        self._electrode_label.pack(anchor="w")
        self._electrode_combo = ttk.Combobox(layout, state="readonly")
        self._electrode_combo.pack(fill="x", pady=(2, 8))
        self._electrode_combo.bind("<<ComboboxSelected>>", self._on_combo_changed)
        self._electrode_data: list[tuple] = []
        self._electrode_values: list[str] = []
        self._electrode_map: dict[str, tuple | None] = {}
        self._on_electrode_cb: Callable[[object], None] | None = None

        # ---- 化学计量数 ----
        self._stoich_group = ttk.LabelFrame(layout, text=i18n.tr("results.stoich"))
        self._stoich_group.pack(fill="x", pady=(0, 6))
        stoich_inner = ttk.Frame(self._stoich_group, padding=(8, 6))
        stoich_inner.pack(fill="both", expand=True)

        self._n_std = self._make_spin(stoich_inner, 0.1, 100.0, 1.0, 0.1, 1)
        self._n_std_label = self._add_form_row(stoich_inner, i18n.tr("results.n_std"), self._n_std)

        self._n_analyte = self._make_spin(stoich_inner, 0.1, 100.0, 1.0, 0.1, 1)
        self._n_analyte_label = self._add_form_row(
            stoich_inner, i18n.tr("results.n_analyte"), self._n_analyte
        )

        # ---- 标准液浓度 ----
        self._conc_group = ttk.LabelFrame(layout, text=i18n.tr("results.conc"))
        self._conc_group.pack(fill="x", pady=(0, 6))
        conc_inner = ttk.Frame(self._conc_group, padding=(8, 6))
        conc_inner.pack(fill="both", expand=True)

        self._c_std = self._make_spin(conc_inner, 0.0001, 100.0, 0.1, 0.01, 4)
        self._c_std_label = self._add_form_row(conc_inner, i18n.tr("results.c_std"), self._c_std)

        # ---- 待测液 ----
        self._sample_group = ttk.LabelFrame(layout, text=i18n.tr("results.sample"))
        self._sample_group.pack(fill="x", pady=(0, 6))
        sample_inner = ttk.Frame(self._sample_group, padding=(8, 6))
        sample_inner.pack(fill="both", expand=True)

        self._v_sample_label = ttk.Label(
            sample_inner, text="—", font=(MONO_FONT, 10)
        )
        self._v_sample_rowlabel = self._add_form_row(
            sample_inner, i18n.tr("results.sample_volume"), self._v_sample_label
        )

        self._v_now_label = ttk.Label(
            sample_inner, text="— V", font=(MONO_FONT, 10)
        )
        self._v_now_rowlabel = self._add_form_row(
            sample_inner, i18n.tr("results.current_voltage"), self._v_now_label
        )

        # ---- 进样进度（默认隐藏）----
        self._inject_group = ttk.LabelFrame(layout, text=i18n.tr("results.inject"))
        inject_inner = ttk.Frame(self._inject_group, padding=(8, 6))
        inject_inner.pack(fill="both", expand=True)
        self._inject_bar = ttk.Progressbar(
            inject_inner, maximum=100, bootstyle="info-striped"
        )
        self._inject_bar.pack(fill="x", pady=(2, 0))
        self._inject_text_label = ttk.Label(
            inject_inner, text="", anchor="center", style="Subtle.TLabel"
        )
        self._inject_text_label.pack(fill="x", pady=(2, 0))
        self._eta_label = ttk.Label(
            inject_inner, text="", anchor="center", style="Subtle.TLabel"
        )
        self._eta_label.pack(fill="x")

        # ---- KPI 卡片：终点体积 ----
        self._ep_card = Card(layout, tone="alt")
        self._ep_card.pack(fill="x", pady=(2, 6))
        ep_body = ttk.Frame(self._ep_card, style="Kpi.TFrame", padding=(10, 8))
        ep_body.pack(fill="both", expand=True)
        self._ep_caption = ttk.Label(
            ep_body, text=i18n.tr("results.endpoint"), style="Kpi.TLabel"
        )
        self._ep_caption.pack(anchor="w")
        ep_value_row = ttk.Frame(ep_body, style="Kpi.TFrame")
        ep_value_row.pack(anchor="w")
        self._v_ep_label = ttk.Label(
            ep_value_row, text="—", style="KpiAccent.TLabel"
        )
        self._v_ep_label.pack(side="left")
        ttk.Label(
            ep_value_row, text=" " + i18n.tr("results.endpoint_unit"), style="KpiUnit.TLabel"
        ).pack(side="left", pady=(6, 0))
        self._ep_unit_label = ep_value_row.winfo_children()[-1]

        # ---- KPI 卡片：Cₓ ----
        self._cx_card = Card(layout, tone="alt")
        self._cx_card.pack(fill="x", pady=(0, 6))
        cx_body = ttk.Frame(self._cx_card, style="Kpi.TFrame", padding=(10, 8))
        cx_body.pack(fill="both", expand=True)
        self._cx_caption = ttk.Label(
            cx_body, text=i18n.tr("results.cx"), style="Kpi.TLabel"
        )
        self._cx_caption.pack(anchor="w")
        cx_value_row = ttk.Frame(cx_body, style="Kpi.TFrame")
        cx_value_row.pack(anchor="w")
        self._c_x_label = ttk.Label(
            cx_value_row, text="—", style="KpiSuccess.TLabel"
        )
        self._c_x_label.pack(side="left")
        ttk.Label(
            cx_value_row, text=" " + i18n.tr("results.cx_unit"), style="KpiUnit.TLabel"
        ).pack(side="left", pady=(6, 0))
        self._cx_unit_label = cx_value_row.winfo_children()[-1]

        # ---- 在线可靠性诊断 ----
        self._diag_group = ttk.LabelFrame(layout, text=i18n.tr("results.diagnostics"))
        self._diag_group.pack(fill="x", pady=(0, 6))
        diag_inner = ttk.Frame(self._diag_group, padding=(8, 6))
        diag_inner.pack(fill="both", expand=True)
        self._diag_status = self._add_diag_row(diag_inner, "results.diag_status")
        self._diag_quality = self._add_diag_row(diag_inner, "results.diag_quality")
        self._diag_consistency = self._add_diag_row(diag_inner, "results.diag_consistency")
        self._diag_nis = self._add_diag_row(diag_inner, "results.diag_nis")
        self._diag_std = self._add_diag_row(diag_inner, "results.diag_std")
        self._diag_delay = self._add_diag_row(diag_inner, "results.diag_delay")

        # Internal state
        self._endpoint_volume: float | None = None
        self._sample_volume: float = 0.0
        self._inject_target: int = 0
        self._inject_target_vol: float = 0.0

        i18n.subscribe(self._apply_i18n)

    # ---- i18n ----

    def _apply_i18n(self) -> None:
        self._title.config(text=i18n.tr("results.title"))
        if self._rec_cb is not None:
            self._rec_cb.config(text=i18n.tr("toolbar.record"))
        self._electrode_label.config(text=i18n.tr("results.electrode"))
        self._stoich_group.config(text=i18n.tr("results.stoich"))
        self._n_std_label.config(text=i18n.tr("results.n_std"))
        self._n_analyte_label.config(text=i18n.tr("results.n_analyte"))
        self._conc_group.config(text=i18n.tr("results.conc"))
        self._c_std_label.config(text=i18n.tr("results.c_std"))
        self._sample_group.config(text=i18n.tr("results.sample"))
        self._v_sample_rowlabel.config(text=i18n.tr("results.sample_volume"))
        self._v_now_rowlabel.config(text=i18n.tr("results.current_voltage"))
        self._inject_group.config(text=i18n.tr("results.inject"))
        self._diag_group.config(text=i18n.tr("results.diagnostics"))
        # 在线诊断行的标题由行内 label 保存，值标签不参与翻译。
        for widget, key in (
            (self._diag_status, "results.diag_status"),
            (self._diag_quality, "results.diag_quality"),
            (self._diag_consistency, "results.diag_consistency"),
            (self._diag_nis, "results.diag_nis"),
            (self._diag_std, "results.diag_std"),
            (self._diag_delay, "results.diag_delay"),
        ):
            label = widget.master.winfo_children()[0]
            label.config(text=i18n.tr(key))
        self._ep_caption.config(text=i18n.tr("results.endpoint"))
        self._ep_unit_label.config(text=" " + i18n.tr("results.endpoint_unit"))
        self._cx_caption.config(text=i18n.tr("results.cx"))
        self._cx_unit_label.config(text=" " + i18n.tr("results.cx_unit"))
        # 电极下拉框首项（Raw Potential）
        if self._electrode_values:
            raw = i18n.tr("results.raw_potential")
            old_first = self._electrode_values[0]
            if old_first != raw:
                self._electrode_values[0] = raw
                self._electrode_map[raw] = self._electrode_map.pop(old_first)
                self._electrode_combo["values"] = self._electrode_values
                if self._electrode_combo.get() == old_first:
                    self._electrode_combo.set(raw)

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
    def _add_form_row(parent: tk.Misc, label: str, widget: tk.Widget) -> ttk.Label:
        row = ttk.Frame(parent)
        row.pack(fill="x", pady=2)
        row.grid_columnconfigure(0, weight=1)
        lbl = ttk.Label(row, text=label)
        lbl.grid(row=0, column=0, sticky="w")
        widget.grid(in_=row, row=0, column=1, sticky="e", padx=(8, 0))
        return lbl

    def _spin_value(self, sb: ttk.Spinbox) -> float:
        try:
            return float(sb.get())
        except (ValueError, tk.TclError):
            return 0.0

    @staticmethod
    def _add_diag_row(parent: tk.Misc, label_key: str) -> ttk.Label:
        row = ttk.Frame(parent)
        row.pack(fill="x", pady=1)
        row.grid_columnconfigure(0, weight=1)
        caption = ttk.Label(row, text=i18n.tr(label_key), style="Muted.TLabel")
        caption.grid(row=0, column=0, sticky="w")
        value = ttk.Label(row, text="—", font=(MONO_FONT, 9))
        value.grid(row=0, column=1, sticky="e", padx=(8, 0))
        return value

    def set_reliability(self, reliability: dict | None) -> None:
        """Update the compact causal reliability readout."""
        data = reliability or {}
        quality = data.get("data_quality") or {}
        consistency = data.get("modal_consistency") or {}
        status = data.get("status") or "—"
        last_frame = quality.get("last_frame", "—")
        self._diag_status.config(text=str(status))
        self._diag_quality.config(text=str(last_frame))
        agreement = consistency.get("agreement_mL")
        self._diag_consistency.config(
            text="—" if agreement is None else f"{float(agreement):.4f} mL"
        )
        nis = data.get("nis")
        self._diag_nis.config(text="—" if nis is None else f"{float(nis):.2f}")
        endpoint_std = data.get("endpoint_std")
        self._diag_std.config(
            text="—" if endpoint_std is None else f"{float(endpoint_std):.4f} mL"
        )
        delay = data.get("spectral_delay")
        self._diag_delay.config(
            text="—" if delay is None else f"{float(delay):+.4f} mL"
        )

    # ---- 公开接口 ----

    def set_electrodes(self, electrode_list: list[tuple]) -> None:
        self._electrode_data = electrode_list
        raw = i18n.tr("results.raw_potential")
        self._electrode_values = [raw]
        self._electrode_map = {raw: None}
        for name, slope, intercept, unit in electrode_list:
            disp = f"{name} ({unit})"
            self._electrode_values.append(disp)
            self._electrode_map[disp] = (name, slope, intercept, unit)
        self._electrode_combo["values"] = self._electrode_values
        if self._electrode_values:
            self._electrode_combo.set(self._electrode_values[0])

    def on_electrode_changed(self, cb: Callable[[object], None]) -> None:
        """注册电极选择变化回调。"""
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
        self._inject_text_label.config(text=f"0.000 / {target_vol:.3f} mL")
        self._eta_label.config(text="")
        self._inject_group.pack(fill="x", pady=(0, 6), before=self._ep_card)

    def update_inject_progress(self, pos: int, volume: float = 0.0) -> None:
        if self._inject_target <= 0:
            return
        pct = min(100, int(pos * 100 / self._inject_target))
        self._inject_bar["value"] = pct
        tv = self._inject_target_vol
        remaining = max(0, self._inject_target - pos)
        eta_sec = remaining // 1000
        if pct < 100 and remaining > 0:
            self._inject_text_label.config(text=f"{volume:.3f} / {tv:.3f} mL  ({pct}%)")
            self._eta_label.config(
                text=i18n.tr("results.eta", eta=f"{eta_sec // 60:02d}:{eta_sec % 60:02d}")
            )
        else:
            self._inject_text_label.config(text=i18n.tr("results.inject_done"))
            self._eta_label.config(text="")

    def hide_inject_progress(self) -> None:
        self._inject_text_label.config(text="")
        self._eta_label.config(text="")
        self._inject_group.pack_forget()
        self._inject_bar["value"] = 0

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
