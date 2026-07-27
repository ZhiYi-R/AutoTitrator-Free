#!/usr/bin/env python3
"""
在线滴定终点检测 — 实时 matplotlib 绘图版。

每帧跳过 stride 步再刷新，控制播放速度。
"""

from __future__ import annotations

import sys
import warnings
from pathlib import Path

import numpy as np
import openpyxl

warnings.filterwarnings("ignore")

PJ = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PJ / "src"))
from DataProcessor.calibration import FLOW_RATE, update_from_file

update_from_file()

DATA = Path(
    "/home/zhiyir/文档/xwechat_files/wxid_l267qu0nkh512_1601/msg/attach/"
    "d819785e5916791e7d3b8b1199d7af8d/2026-06/Rec/"
    "da42816e8394beff/F/1/titration_result.xlsx"
)

print("[1] 加载数据 …")
wb = openpyxl.load_workbook(str(DATA), read_only=True)
rows = list(wb["电位-体积曲线"].iter_rows(min_row=2, values_only=True))
wb.close()
vol = np.array([r[0] for r in rows], dtype=np.float64)
pot = np.array([r[1] for r in rows], dtype=np.float64)
u, inv, cnt = np.unique(np.round(vol, 6), return_inverse=True, return_counts=True)
mp = np.bincount(inv, weights=pot) / cnt
N = len(u)
T = u / FLOW_RATE
print(f"  电位: {N} 步, {u[0]:.4f}–{u[-1]:.4f} mL")


# ── 在线检测器 ─────────────────────────────────────────────────────────
class OD:
    POT_ENTER = -80
    POT_EXIT = -15
    POT_MIN_VOL = 0.5
    POT_CONFIRM_VOL = 0.15

    def __init__(s, fr):
        s.fr = fr
        s.va = 0.15
        s.da = 0.05
        s.vs = None
        s.pvs = None
        s.pt = None
        s.ds = 0.0
        s.ps = "IDLE"
        s.pe = None
        s.md = 0.0
        s.cv = None
        s.ev = None
        s.pd = False
        s.vh = []
        s.dh = []
        s.sh = []

    def feed(s, t0, v0):
        v = t0 * s.fr
        if s.vs is None:
            s.vs = float(v0)
        else:
            s.vs = s.va * float(v0) + (1 - s.va) * s.vs
        if s.pt is not None and s.pvs is not None:
            dt = t0 - s.pt
            dv = s.vs - s.pvs
            dr = dv / dt if dt > 0 else 0
        else:
            dr = 0
        s.ds = s.da * dr + (1 - s.da) * s.ds
        s.pvs = s.vs
        s.pt = t0
        if not s.pd and v > s.POT_MIN_VOL:
            if s.ps == "IDLE":
                if s.ds < s.POT_ENTER:
                    s.ps = "TRACKING"
                    s.md = s.ds
                    s.cv = v
                    s.ev = v
            elif s.ps == "TRACKING":
                if s.ds < s.md:
                    s.md = s.ds
                    s.cv = v
                if s.ds > s.POT_EXIT and (v - s.ev) > s.POT_CONFIRM_VOL:
                    s.pe = s.cv
                    s.ps = "END_CONFIRMED"
                    s.pd = True
        s.vh.append(v)
        s.dh.append(s.ds)
        s.sh.append(s.ps)


# ── 预计算完整 dV/dt（画背景用） ────────────────────────────────────
bd = np.zeros(N)
vs = None
pvs = None
pt = None
ds = 0.0
for i in range(N):
    v0 = float(mp[i])
    t0 = float(T[i])
    if vs is None:
        vs = v0
    else:
        vs = 0.15 * v0 + 0.85 * vs
    if pt is not None and pvs is not None:
        dt = t0 - pt
        dv = vs - pvs
        bd[i] = dv / dt if dt > 0 else 0
    else:
        bd[i] = 0
    pvs = vs
    pt = t0
    ds = 0.05 * bd[i] + 0.95 * ds
    bd[i] = ds

# ── matplotlib 实时绘图 ─────────────────────────────────────────────────
import matplotlib

matplotlib.use("TkAgg")
import matplotlib.pyplot as plt

plt.rcParams["font.size"] = 9
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 7), sharex=True)
fig.canvas.manager.set_window_title("Titration - Online Endpoint Detection")

for ax in (ax1, ax2):
    ax.set_xlim(0, 2.25)
    ax.grid(True, alpha=0.3)
ax1.set_ylim(29500, 34000)
ax1.set_ylabel("Potential (LSB)")
ax2.set_ylim(-350, 50)
ax2.set_ylabel("dV/dt (LSB/s)")
ax2.set_xlabel("Volume (mL)")
ax2.axhline(-80, color="gray", ls=":", lw=1, alpha=0.6, label="Enter threshold")
ax2.axhline(-15, color="gray", ls="-.", lw=1, alpha=0.6, label="Exit threshold")
ax2.axhline(0, color="black", lw=0.5)
for ax in (ax1, ax2):
    ax.axvline(
        1.089, color="gray", ls=":", lw=1, alpha=0.35, label="Ground truth ~1.089"
    )
ax1.plot(u, mp, "b-", lw=0.4, alpha=0.12)
ax2.plot(u, bd, "g-", lw=0.4, alpha=0.12)

(lp,) = ax1.plot([], [], "b-", lw=1, label="Potential")
(ld,) = ax2.plot([], [], "g-", lw=1, label="dV/dt (EWMA)")
(st,) = ax2.plot([], [], "o", c="orange", ms=3, alpha=0.6, label="TRACKING")
(sc,) = ax2.plot([], [], "o", c="red", ms=3, alpha=0.6, label="CONFIRMED")
ep = ax2.axvline(0, color="red", ls="--", lw=2, alpha=0, label="Endpoint")
tx = ax1.text(
    0.02,
    0.97,
    "",
    transform=ax1.transAxes,
    fontfamily="monospace",
    fontsize=9,
    va="top",
    bbox={"boxstyle": "round,pad=0.3", "fc": "lightyellow", "alpha": 0.9},
)
for ax in (ax1, ax2):
    ax.legend(fontsize=8, loc="lower right")

# ── 逐点回放（每 stride 步刷新一次） ─────────────────────────────────
stride = 50  # 每 stride 步刷新一次画面
interval_s = 0.01  # 帧间隔秒数

print(f"\n[2] 逐点回放 …  stride={stride}, 帧间隔={interval_s}s")
print(f"  理论时长 ≈ {N / stride * interval_s:.0f}s")
plt.ion()
plt.show()

det = OD(FLOW_RATE)
for i in range(N):
    det.feed(float(T[i]), float(mp[i]))
    # 仅当 stride 整数倍或最后一步时刷新
    if (i + 1) % stride != 0 and i != N - 1:
        continue
    vs = np.array(det.vh)
    ds = np.array(det.dh)
    ss = np.array(det.sh)
    lp.set_data(vs, mp[: len(vs)])
    ld.set_data(vs, ds)
    trk = np.where(ss == "TRACKING")[0]
    cnf = np.where(ss == "END_CONFIRMED")[0]
    st.set_data(vs[trk] if len(trk) else [], ds[trk] if len(trk) else [])
    sc.set_data(vs[cnf] if len(cnf) else [], ds[cnf] if len(cnf) else [])
    ep.set_alpha(1) if det.pe is not None else ep.set_alpha(0)
    if det.pe is not None:
        ep.set_xdata([det.pe, det.pe])
    txt = (
        f"Step {i + 1}/{N}  Vol = {u[i]:.4f} mL\nState: {det.ps}  dV/dt = {det.ds:.1f}"
    )
    if det.pe:
        txt += f"\nENDPOINT = {det.pe:.4f} mL"
    elif det.cv and det.ps != "IDLE":
        txt += f"\nCandidate = {det.cv:.4f} mL"
    tx.set_text(txt)
    fig.canvas.draw_idle()
    fig.canvas.start_event_loop(interval_s)

plt.ioff()
print(f"\n✅ 检测完成！终点 = {det.pe} mL")
fig.suptitle(
    f"Detection Complete — Endpoint = {det.pe:.4f} mL", fontsize=13, fontweight="bold"
)
fig.canvas.draw_idle()
plt.show(block=True)
