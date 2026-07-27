"""校准选项卡 — 泵校准 + pH 电极校准（ttkbootstrap + matplotlib）。"""

from __future__ import annotations

import os
import tkinter as tk
from tkinter import simpledialog

import numpy as np
import ttkbootstrap as ttk
from Communication import ProtocolHandler
from DataProcessor._path import CALIBRE_PATH

from gui._plot import _BlitPlot

DATA_DIR = os.path.dirname(CALIBRE_PATH)
os.makedirs(DATA_DIR, exist_ok=True)


# ======================================================================
#  工具：线性回归
# ======================================================================


def _linreg(x: np.ndarray, y: np.ndarray) -> tuple[float, float, float]:
    """(slope, intercept, r²) — 普通线性回归。"""
    n = len(x)
    sx, sy = x.sum(), y.sum()
    sxx = (x * x).sum()
    sxy = (x * y).sum()
    slope = (n * sxy - sx * sy) / (n * sxx - sx * sx + 1e-12)
    intercept = (sy - slope * sx) / n
    y_pred = slope * x + intercept
    ss_res = ((y - y_pred) ** 2).sum()
    ss_tot = ((y - y.mean()) ** 2).sum()
    r2 = 1.0 - ss_res / (ss_tot + 1e-12)
    return slope, intercept, r2


def _linreg_origin(x: np.ndarray, y: np.ndarray) -> tuple[float, float]:
    """过原点回归: V = slope × 脉冲, 返回 (slope, r²)。"""
    slope = (x * y).sum() / (x * x).sum()
    y_pred = slope * x
    ss_res = ((y - y_pred) ** 2).sum()
    ss_tot = ((y - y.mean()) ** 2).sum()
    r2 = 1.0 - ss_res / (ss_tot + 1e-12)
    return slope, r2


# ======================================================================
#  泵校准面板
# ======================================================================


class PumpCalibWidget(ttk.Frame):
    """单泵校准面板：点动 10000 脉冲 → 输入质量 → 记录 → 拟合。"""

    def __init__(
        self,
        pump_id: int,
        com: ProtocolHandler,
        parent: tk.Misc | None = None,
    ) -> None:
        super().__init__(parent)
        self._pump_id = pump_id
        self._com = com
        self._points: list[tuple[int, float]] = []  # (pulses, volume_mL)

        inner = ttk.Frame(self)
        inner.pack(fill="both", expand=True, padx=8, pady=8)

        # ---- 操作区 ----
        ctrl = ttk.Frame(inner)
        ctrl.pack(fill="x")

        self._jog_btn = ttk.Button(ctrl, text="点动 10000 脉冲", command=self._jog)
        self._jog_btn.pack(side="left")

        ttk.Label(ctrl, text="体积 (mL):").pack(side="left", padx=(8, 4))

        self._vol_input = ttk.Spinbox(
            ctrl, from_=0, to=999, increment=0.01, format="%.6f", width=10
        )
        self._vol_input.set(0)
        self._vol_input.pack(side="left")

        ttk.Button(ctrl, text="记录", command=self._record).pack(side="left", padx=8)
        ttk.Button(ctrl, text="撤销最后", command=self._undo).pack(side="left", padx=4)
        ttk.Button(ctrl, text="清空", command=self._clear_points).pack(
            side="left", padx=4
        )

        # ---- 状态 ----
        self._status_label = ttk.Label(inner, text="就绪")
        self._status_label.pack(anchor="w", pady=(4, 0))

        # ---- 数据表 ----
        table_frame = ttk.Frame(inner)
        table_frame.pack(fill="both", expand=True, pady=4)
        self._table = ttk.Treeview(
            table_frame,
            columns=("idx", "pulses", "volume"),
            show="headings",
            height=6,
        )
        self._table.heading("idx", text="#")
        self._table.heading("pulses", text="脉冲数")
        self._table.heading("volume", text="体积 (mL)")
        self._table.column("idx", width=40, anchor="center")
        self._table.column("pulses", width=100, anchor="center")
        self._table.column("volume", width=120, anchor="center")
        self._table.pack(fill="both", expand=True, side="left")
        sb = ttk.Scrollbar(table_frame, command=self._table.yview)
        sb.pack(side="right", fill="y")
        self._table.configure(yscrollcommand=sb.set)

        # ---- 校准曲线图 ----
        self._plot_widget = _PumpCalibPlot(inner, title=f"泵 {pump_id} 校准曲线")
        self._plot_widget.pack(fill="both", expand=True, pady=4)

        # ---- 校准结果 ----
        self._result_label = ttk.Label(inner, text="尚未拟合", font=("", 9, "bold"))
        self._result_label.pack(anchor="w")

        # ---- 保存 ----
        save_row = ttk.Frame(inner)
        save_row.pack(fill="x", pady=(4, 0))
        ttk.Button(save_row, text="保存校准", command=self._save).pack(side="left")

        # 加载已有数据
        self._load()
        self._update_table()
        self._update_plot()

    # ---- 操作 ----

    def _jog(self) -> None:
        if not self._com.is_open:
            self._status_label.config(text="串口未连接")
            return
        self._jog_btn.state(["disabled"])
        self._status_label.config(text="泵运行中…")
        self._com.request_pump_done_once(self._on_jog_done)
        self._com.send_maxcount(self._pump_id, 10000)
        # 超时保护
        self.after(5000, lambda: self._jog_btn.state(["!disabled"]))

    def _on_jog_done(self, position: int) -> None:
        self._jog_btn.state(["!disabled"])
        self._status_label.config(
            text=f"点动完成，当前位置: {position} 脉冲，请输入体积"
        )

    def _record(self) -> None:
        try:
            vol = float(self._vol_input.get())
        except (ValueError, tk.TclError):
            self._status_label.config(text="体积输入无效")
            return
        if vol <= 0:
            self._status_label.config(text="体积必须大于 0")
            return
        # 累计脉冲数：上一点 + 10000，若无则从 10000 开始
        total_pulses = (self._points[-1][0] + 10000) if self._points else 10000
        self._points.append((total_pulses, vol))
        self._update_table()
        self._update_plot()
        self._vol_input.set(0)
        self._status_label.config(
            text=f"记录 ({len(self._points)}): {total_pulses} 脉冲 → {vol:.6f} mL"
        )

    def _undo(self) -> None:
        if self._points:
            self._points.pop()
            self._update_table()
            self._update_plot()
            self._status_label.config(text=f"撤销，剩余 {len(self._points)} 点")

    def _clear_points(self) -> None:
        self._points.clear()
        self._update_table()
        self._update_plot()
        self._result_label.config(text="尚未拟合")
        self._status_label.config(text="已清空")

    # ---- 显示 ----

    def _update_table(self) -> None:
        for item in self._table.get_children():
            self._table.delete(item)
        for i, (pulses, vol) in enumerate(self._points):
            self._table.insert(
                "", "end", values=(i + 1, pulses, f"{vol:.6f}")
            )

    def _update_plot(self) -> None:
        if len(self._points) < 2:
            self._plot_widget.clear()
            self._result_label.config(text="至少需要 2 个点")
            return
        xs = np.array([p for p, _ in self._points], dtype=np.float64)
        ys = np.array([v for _, v in self._points], dtype=np.float64)

        slope, r2 = _linreg_origin(xs, ys)
        x_fit = np.linspace(0, xs.max() * 1.05, 200)
        y_fit = slope * x_fit
        self._plot_widget.update_data(xs, ys, x_fit, y_fit)

        self._result_label.config(
            text=f"V = {slope:.10f} × 脉冲  (R² = {r2:.6f})  |  点数: {len(self._points)}"
        )

    # ---- 保存 / 加载 ----

    def _save_path(self) -> str:
        return os.path.join(DATA_DIR, "calibre.npz")

    def _save(self) -> None:
        if len(self._points) < 2:
            self._status_label.config(text="至少需要 2 个点才能保存")
            return
        xs = np.array([p for p, _ in self._points], dtype=np.float64)
        ys = np.array([v for _, v in self._points], dtype=np.float64)
        slope, r2 = _linreg_origin(xs, ys)
        pulses = np.array([p for p, _ in self._points], dtype=np.int32)
        volumes = np.array([v for _, v in self._points], dtype=np.float64)
        path = self._save_path()
        # Load existing, merge with new pump data
        _merge = {}
        if os.path.isfile(path):
            try:
                _old = np.load(path, allow_pickle=True)
                for _k in _old:
                    _merge[_k] = _old[_k]
            except Exception:
                pass
        _p = f"pump{self._pump_id}_"
        _merge[f"{_p}pulses"] = pulses
        _merge[f"{_p}volumes"] = volumes
        _merge[f"{_p}slope"] = slope
        _merge[f"{_p}intercept"] = 0.0
        _merge[f"{_p}r2"] = r2
        np.savez_compressed(path, **_merge)
        self._status_label.config(text=f"已保存: {path}")

    def _load(self) -> None:
        path = self._save_path()
        if not os.path.isfile(path):
            return
        try:
            data = np.load(path, allow_pickle=True)
            _p = f"pump{self._pump_id}_"
            if _p + "pulses" in data:
                pulses = data[f"{_p}pulses"]
                volumes = data[f"{_p}volumes"]
                self._points = [
                    (int(p), float(v)) for p, v in zip(pulses, volumes)
                ]
                self._status_label.config(text=f"已加载 {len(self._points)} 个校准点")
            else:
                self._status_label.config(text="暂无泵校准数据")
        except Exception:
            self._status_label.config(text="校准文件读取失败")
        self._update_table()
        self._update_plot()


# ======================================================================
#  泵校准绘图（matplotlib blit）
# ======================================================================


class _PumpCalibPlot(_BlitPlot):
    """泵校准散点 + 拟合线。"""

    def __init__(self, parent: tk.Misc, title: str = "", **kwargs) -> None:
        super().__init__(parent, title=title, **kwargs)
        self._ax.set_xlabel("Pulse")
        self._ax.set_ylabel("Volume (mL)")
        self._ax.grid(True, alpha=0.3)

        # 散点
        self._scatter = self._ax.scatter(
            [], [], c="#2980b9", s=40, zorder=3
        )
        # 拟合线
        (self._fit_line,) = self._ax.plot(
            [], [], color="#e74c3c", linewidth=2, zorder=2
        )

        self._artists = [self._fit_line, self._scatter]
        self._capture_bg()

    def update_data(
        self,
        xs: np.ndarray,
        ys: np.ndarray,
        x_fit: np.ndarray,
        y_fit: np.ndarray,
    ) -> None:
        self._scatter.set_offsets(np.column_stack([xs, ys]))
        self._fit_line.set_data(x_fit, y_fit)

        # 自动范围
        all_x = np.concatenate([xs, x_fit])
        all_y = np.concatenate([ys, y_fit])
        self._ax.set_xlim(float(all_x.min()) * 0.95, float(all_x.max()) * 1.05)
        self._ax.set_ylim(float(all_y.min()) * 0.95, float(all_y.max()) * 1.05)
        self._request_full_redraw()
        self.refresh()

    def clear(self) -> None:
        self._scatter.set_offsets(np.zeros((0, 2)))
        self._fit_line.set_data([], [])
        self._request_full_redraw()
        self.refresh()


# ======================================================================
#  电极校准面板
# ======================================================================


class PHCalibWidget(ttk.Frame):
    """电极校准：支持多个电极配置，可命名、设单位(pX)和备注。"""

    def __init__(self, com: ProtocolHandler, parent: tk.Misc | None = None) -> None:
        super().__init__(parent)
        self._com = com
        self._current_mv: float = 0.0
        self._data: dict = self._load_data()

        inner = ttk.Frame(self)
        inner.pack(fill="both", expand=True, padx=8, pady=8)

        # ---- 电极选择 ----
        sel_row = ttk.Frame(inner)
        sel_row.pack(fill="x")
        ttk.Label(sel_row, text="电极:").pack(side="left")
        self._electrode_combo = ttk.Combobox(
            sel_row, state="readonly", width=15
        )
        self._electrode_combo.pack(side="left", padx=4)
        self._electrode_combo.bind(
            "<<ComboboxSelected>>", lambda _e: self._on_select()
        )

        self._add_elec_btn = ttk.Button(sel_row, text="+", width=3, command=self._add_electrode)
        self._add_elec_btn.pack(side="left", padx=2)
        self._del_elec_btn = ttk.Button(sel_row, text="—", width=3, command=self._del_electrode)
        self._del_elec_btn.pack(side="left", padx=2)

        # ---- 属性 ----
        attr_row = ttk.Frame(inner)
        attr_row.pack(fill="x", pady=(4, 0))
        ttk.Label(attr_row, text="单位:").pack(side="left")
        self._unit_var = tk.StringVar(value="pH")
        self._unit_entry = ttk.Entry(attr_row, textvariable=self._unit_var, width=6)
        self._unit_entry.pack(side="left", padx=4)
        self._unit_var.trace_add("write", self._mark_dirty)
        ttk.Label(attr_row, text="备注:").pack(side="left", padx=(8, 0))
        self._notes_var = tk.StringVar()
        self._notes_entry = ttk.Entry(attr_row, textvariable=self._notes_var)
        self._notes_entry.pack(side="left", fill="x", expand=True, padx=4)
        self._notes_var.trace_add("write", self._mark_dirty)

        # ---- 实时电压 ----
        live_row = ttk.Frame(inner)
        live_row.pack(fill="x", pady=4)
        ttk.Label(live_row, text="当前电位:").pack(side="left")
        self._live_label = ttk.Label(
            live_row,
            text="--.-- mV",
            font=("", 12, "bold"),
            foreground="#2980b9",
        )
        self._live_label.pack(side="left", padx=4)

        # ---- 输入区 ----
        input_row = ttk.Frame(inner)
        input_row.pack(fill="x")
        ttk.Label(input_row, text="标准值:").pack(side="left")
        self._val_input = ttk.Spinbox(
            input_row, from_=-10, to=20, increment=0.1, format="%.2f", width=8
        )
        self._val_input.set(7.00)
        self._val_input.pack(side="left", padx=4)
        ttk.Button(input_row, text="确认记录", command=self._confirm).pack(
            side="left", padx=4
        )
        ttk.Button(input_row, text="撤销", command=self._undo).pack(
            side="left", padx=4
        )

        # ---- 数据表 ----
        table_frame = ttk.Frame(inner)
        table_frame.pack(fill="both", expand=True, pady=4)
        self._table = ttk.Treeview(
            table_frame,
            columns=("val", "mv"),
            show="headings",
            height=6,
        )
        self._table.heading("val", text="标准值")
        self._table.heading("mv", text="电位 (mV)")
        self._table.column("val", width=120, anchor="center")
        self._table.column("mv", width=120, anchor="center")
        self._table.pack(fill="both", expand=True, side="left")
        sb = ttk.Scrollbar(table_frame, command=self._table.yview)
        sb.pack(side="right", fill="y")
        self._table.configure(yscrollcommand=sb.set)

        # ---- 拟合结果 ----
        self._result_label = ttk.Label(
            inner, text="尚未校准", font=("", 11, "bold")
        )
        self._result_label.pack(anchor="w")

        # ---- 校准曲线图 ----
        self._plot_widget = _PHCalibPlot(inner, title="电极校准曲线")
        self._plot_widget.pack(fill="both", expand=True, pady=4)

        # ---- 保存 ----
        ttk.Button(inner, text="保存", command=self._save).pack(anchor="w", pady=(4, 0))

        # ---- 连接实时数据 ----
        self._com.on("adc", self._on_adc)
        self._rebuild_combo()
        self._dirty = False

    # ---- 数据文件 ----

    @staticmethod
    def _data_path() -> str:
        return os.path.join(DATA_DIR, "calibre.npz")

    @staticmethod
    def _load_data() -> dict:
        path = PHCalibWidget._data_path()
        result = {"electrodes": {}, "current": ""}
        if not os.path.isfile(path):
            return result
        try:
            data = np.load(path, allow_pickle=True)
            if "n_electrodes" not in data:
                return result
            n = int(data["n_electrodes"])
            names = list(data["names"])
            result["current"] = str(data["current"])
            for i in range(n):
                name = str(names[i])
                pts_vals = data[f"points_vals_{i}"]
                pts_mvs = data[f"points_mvs_{i}"]
                points = [
                    (float(pts_vals[j]), float(pts_mvs[j]))
                    for j in range(len(pts_vals))
                ]
                result["electrodes"][name] = {
                    "unit": str(data[f"unit_{i}"]),
                    "notes": str(data[f"notes_{i}"]),
                    "points": points,
                    "slope": float(data[f"slope_{i}"]),
                    "intercept": float(data[f"intercept_{i}"]),
                    "r2": float(data[f"r2_{i}"]),
                }
        except Exception:
            pass
        return result

    def _save_data(self) -> None:
        path = self._data_path()
        # Load existing pump data, merge with electrode data
        _merge = {}
        if os.path.isfile(path):
            try:
                _old = np.load(path, allow_pickle=True)
                for _k in _old:
                    if (
                        not _k.startswith("n_electrodes")
                        and not _k.startswith("names")
                        and not _k.startswith("current")
                        and not _k.startswith("points_")
                        and not _k.startswith("slope_")
                        and not _k.startswith("intercept_")
                        and not _k.startswith("r2_")
                        and not _k.startswith("unit_")
                        and not _k.startswith("notes_")
                    ):
                        _merge[_k] = _old[_k]
            except Exception:
                pass
        electrodes = self._data.get("electrodes", {})
        names = list(electrodes.keys())
        _merge["n_electrodes"] = np.int32(len(names))
        _merge["names"] = np.array(names, dtype=object)
        _merge["current"] = np.array(self._data.get("current", ""), dtype=object)
        for i, name in enumerate(names):
            e = electrodes[name]
            pts = e.get("points", [])
            _merge[f"points_vals_{i}"] = np.array(
                [p for p, _ in pts], dtype=np.float64
            )
            _merge[f"points_mvs_{i}"] = np.array(
                [m for _, m in pts], dtype=np.float64
            )
            _merge[f"slope_{i}"] = np.float64(e.get("slope", 0.0))
            _merge[f"intercept_{i}"] = np.float64(e.get("intercept", 0.0))
            _merge[f"r2_{i}"] = np.float64(e.get("r2", 0.0))
            _merge[f"unit_{i}"] = np.array(e.get("unit", "pX"), dtype=object)
            _merge[f"notes_{i}"] = np.array(e.get("notes", ""), dtype=object)
        np.savez_compressed(path, **_merge)

    # ---- 电极选择 ----

    def _rebuild_combo(self) -> None:
        values = list(self._data["electrodes"].keys())
        self._electrode_combo["values"] = values
        cur = self._data.get("current", "")
        if cur in values:
            self._electrode_combo.set(cur)
        elif values:
            self._electrode_combo.set(values[0])
        self._load_current()

    def _on_select(self) -> None:
        name = self._electrode_combo.get()
        if name:
            self._data["current"] = name
            self._save_data()
        self._load_current()

    def _load_current(self) -> None:
        name = self._electrode_combo.get()
        if not name or name not in self._data["electrodes"]:
            self._clear_table()
            self._result_label.config(text="尚未校准")
            self._plot_widget.clear()
            return
        e = self._data["electrodes"][name]
        self._unit_var.set(e.get("unit", "pX"))
        self._notes_var.set(e.get("notes", ""))
        # 填充表格
        self._clear_table()
        for val, mv in e.get("points", []):
            self._table.insert("", "end", values=(f"{val:.2f}", f"{mv:.1f}"))
        self._recalc()

    def _clear_table(self) -> None:
        for item in self._table.get_children():
            self._table.delete(item)

    # ---- 电极管理 ----

    def _add_electrode(self) -> None:
        name = simpledialog.askstring("添加电极", "电极名称:", parent=self)
        if not name or not name.strip():
            return
        name = name.strip()
        if name in self._data["electrodes"]:
            name = f"{name} ({len(self._data['electrodes']) + 1})"
        self._data["electrodes"][name] = {
            "unit": "pX",
            "notes": "",
            "points": [],
            "slope": 0.0,
            "intercept": 0.0,
            "r2": 0.0,
        }
        self._data["current"] = name
        self._rebuild_combo()
        self._save_data()

    def _del_electrode(self) -> None:
        name = self._electrode_combo.get()
        if not name or name not in self._data["electrodes"]:
            return
        if len(self._data["electrodes"]) <= 1:
            return  # 至少保留一个
        del self._data["electrodes"][name]
        self._data["current"] = next(iter(self._data["electrodes"].keys()))
        self._rebuild_combo()
        self._save_data()

    # ---- 实时电压 ----

    def _on_adc(self, data: tuple) -> None:
        raw, _pump2_pos = data
        self._current_mv = (raw * 3300.0 / 65535) - 1100.0
        self._live_label.config(text=f"{self._current_mv:.1f} mV")

    # ---- 确认 / 撤销 ----

    def _confirm(self) -> None:
        name = self._electrode_combo.get()
        if not name:
            return
        try:
            val = float(self._val_input.get())
        except (ValueError, tk.TclError):
            return
        mv = self._current_mv
        self._table.insert("", "end", values=(f"{val:.2f}", f"{mv:.1f}"))
        self._dirty = True
        self._recalc()

    def _undo(self) -> None:
        items = self._table.get_children()
        if items:
            self._table.delete(items[-1])
            self._dirty = True
            self._recalc()

    # ---- 读取数据 ----

    def _get_points(self) -> tuple[np.ndarray, np.ndarray]:
        mvs, vals = [], []
        for item in self._table.get_children():
            try:
                row = self._table.item(item, "values")
                val = float(row[0])
                mv = float(row[1])
            except (ValueError, TypeError, IndexError):
                continue
            vals.append(val)
            mvs.append(mv)
        return np.array(mvs, dtype=np.float64), np.array(vals, dtype=np.float64)

    # ---- 计算 ----

    def _mark_dirty(self, *args: object) -> None:
        self._dirty = True

    def _recalc(self) -> None:
        mvs, vals = self._get_points()
        unit = self._unit_var.get() or "pX"
        self._plot_widget.set_ylabel(unit)
        if len(vals) < 2:
            self._result_label.config(text="至少需要 2 个点")
            self._plot_widget.clear()
            return
        slope, intercept, r2 = _linreg(mvs, vals)
        self._result_label.config(
            text=f"{unit} = {intercept:.4f} + ({slope:.6f}) × E(mV)  (R² = {r2:.6f})"
        )
        margin = max(20, (mvs.max() - mvs.min()) * 0.2)
        x_fit = np.linspace(mvs.min() - margin, mvs.max() + margin, 200)
        y_fit = slope * x_fit + intercept
        self._plot_widget.update_data(mvs, vals, x_fit, y_fit)

    # ---- 保存 ----

    def _save(self) -> None:
        name = self._electrode_combo.get()
        if not name:
            return
        self._recalc()
        mvs, vals = self._get_points()
        if len(vals) < 2:
            slope, intercept, r2 = 0.0, 0.0, 0.0
        else:
            slope, intercept, r2 = _linreg(mvs, vals)
        self._data["electrodes"][name] = {
            "unit": self._unit_var.get(),
            "notes": self._notes_var.get(),
            "points": [(float(v), float(m)) for v, m in zip(vals, mvs)],
            "slope": slope,
            "intercept": intercept,
            "r2": r2,
        }
        self._save_data()
        self._dirty = False
        self._result_label.config(
            text=f"已保存 — {name}: {self._unit_var.get()} = {intercept:.4f} + "
            f"({slope:.6f}) × E  (R² = {r2:.6f})"
        )


# ======================================================================
#  电极校准绘图（matplotlib blit）
# ======================================================================


class _PHCalibPlot(_BlitPlot):
    """电极校准散点 + 拟合线。"""

    def __init__(self, parent: tk.Misc, title: str = "", **kwargs) -> None:
        super().__init__(parent, title=title, **kwargs)
        self._ax.set_xlabel("Potential (mV)")
        self._ax.set_ylabel("pX")
        self._ax.grid(True, alpha=0.3)

        # 散点
        self._scatter = self._ax.scatter(
            [], [], c="#8e44ad", s=50, zorder=3
        )
        # 拟合线
        (self._fit_line,) = self._ax.plot(
            [], [], color="#e74c3c", linewidth=2, zorder=2
        )

        self._artists = [self._fit_line, self._scatter]
        self._capture_bg()

    def set_ylabel(self, label: str) -> None:
        self._ax.set_ylabel(label)
        self._request_full_redraw()

    def update_data(
        self,
        xs: np.ndarray,
        ys: np.ndarray,
        x_fit: np.ndarray,
        y_fit: np.ndarray,
    ) -> None:
        self._scatter.set_offsets(np.column_stack([xs, ys]))
        self._fit_line.set_data(x_fit, y_fit)

        all_x = np.concatenate([xs, x_fit])
        all_y = np.concatenate([ys, y_fit])
        x_margin = (all_x.max() - all_x.min()) * 0.1 + 1
        y_margin = (all_y.max() - all_y.min()) * 0.1 + 0.1
        self._ax.set_xlim(
            float(all_x.min()) - x_margin, float(all_x.max()) + x_margin
        )
        self._ax.set_ylim(
            float(all_y.min()) - y_margin, float(all_y.max()) + y_margin
        )
        self._request_full_redraw()
        self.refresh()

    def clear(self) -> None:
        self._scatter.set_offsets(np.zeros((0, 2)))
        self._fit_line.set_data([], [])
        self._request_full_redraw()
        self.refresh()


# ======================================================================
#  光谱重建矩阵热力图
# ======================================================================


class SpectralMatrixWidget(ttk.Frame):
    """光谱重建矩阵热力图 (721 波长 × 10 通道)。"""

    def __init__(self, parent: tk.Misc | None = None) -> None:
        super().__init__(parent)
        inner = ttk.Frame(self)
        inner.pack(fill="both", expand=True, padx=8, pady=8)

        from DataProcessor.reconstructor import is_available

        if not is_available():
            ttk.Label(inner, text="校准数据未加载").pack()
            return

        # Load matrix from calibre.npz
        _p = os.path.join(DATA_DIR, "calibre.npz")
        _d = np.load(_p, allow_pickle=True)
        matrix = _d["spectral_matrix"]  # (721, 10)
        wls = _d["spectral_wavelengths"]  # (721,)
        ch_names = [
            "F1(415)", "F2(445)", "F3(480)", "F4(515)", "F5(555)",
            "F6(590)", "F7(630)", "F8(680)", "Clear", "NIR(910)",
        ]

        # ---- 热力图 ----
        self._plot_widget = _MatrixPlot(
            inner, title="光谱重建矩阵 (721λ × 10ch)"
        )
        self._plot_widget.pack(fill="both", expand=True)
        self._plot_widget.set_data(matrix, wls, ch_names)

        # ---- 说明 ----
        info = ttk.Label(
            inner,
            text=(
                "每列对应一个 AS7341 通道 (F1–F8, Clear, NIR)，"
                "每行对应一个波长 (380–1100 nm)。\n"
                f"矩阵尺寸: {matrix.shape[0]}λ × {matrix.shape[1]}ch, "
                f"值范围: [{matrix.min():.4f}, {matrix.max():.4f}]"
            ),
            wraplength=600,
            font=("", 9),
        )
        info.pack(fill="x", pady=(4, 0))


class _MatrixPlot(_BlitPlot):
    """光谱矩阵热力图（matplotlib imshow）。"""

    def __init__(self, parent: tk.Misc, title: str = "", **kwargs) -> None:
        super().__init__(parent, title=title, **kwargs)
        self._ax.set_xlabel("Channel")
        self._ax.set_ylabel("Wavelength (nm)")
        self._img = None
        self._artists = []

    def set_data(
        self,
        matrix: np.ndarray,
        wls: np.ndarray,
        ch_names: list[str],
    ) -> None:
        # transpose to (10, 721) so rows=channels, cols=wavelengths
        data = matrix.T
        self._img = self._ax.imshow(
            data,
            aspect="auto",
            origin="lower",
            extent=(-0.5, 9.5, float(wls[0]), float(wls[-1])),
            cmap="viridis",
            interpolation="nearest",
        )
        self._ax.set_xticks(range(10))
        self._ax.set_xticklabels(ch_names, rotation=45, ha="right", fontsize=8)
        self._ax.set_xlim(-0.5, 9.5)
        self._ax.set_ylim(float(wls[0]), float(wls[-1]))
        self._fig.colorbar(self._img, ax=self._ax)
        self._request_full_redraw()
        self._capture_bg()


# ======================================================================
#  校准选项卡
# ======================================================================


class CalibrationTab(ttk.Frame):
    """校准选项卡 — 进样泵 / 滴定泵 / 电极 / 光谱矩阵。"""

    def __init__(self, com: ProtocolHandler, parent: tk.Misc | None = None) -> None:
        super().__init__(parent)
        inner = ttk.Frame(self)
        inner.pack(fill="both", expand=True)

        self._tabs = ttk.Notebook(inner)
        self._tabs.pack(fill="both", expand=True)

        self._pump1 = PumpCalibWidget(1, com, parent=self._tabs)
        self._pump2 = PumpCalibWidget(2, com, parent=self._tabs)
        self._ph = PHCalibWidget(com, parent=self._tabs)
        self._matrix = SpectralMatrixWidget(parent=self._tabs)

        self._tabs.add(self._pump1, text="进样泵")
        self._tabs.add(self._pump2, text="滴定泵")
        self._tabs.add(self._ph, text="电极校准")
        self._tabs.add(self._matrix, text="光谱矩阵")

    @property
    def plots(self) -> list:
        """返回所有绘图 widget，供主题切换使用。"""
        result = []
        for w in (self._pump1, self._pump2, self._ph):
            if hasattr(w, "_plot_widget"):
                result.append(w._plot_widget)
        if hasattr(self._matrix, "_plot_widget"):
            result.append(self._matrix._plot_widget)
        return result


__all__ = ["CalibrationTab"]
