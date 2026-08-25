"use client";

/**
 * 电位–体积曲线：主曲线 E(V) + 右轴一阶导数 dE/dV + 终点标记 + 十字线。
 * 纯 Canvas 绘制（灰阶配色，主题自适应），可承载数千点实时追加。
 */
import { useCallback, useEffect, useMemo, useRef, useState } from "react";
import { useTheme } from "next-themes";
import { useStore } from "@/lib/store";
import { cssVar, fmt, niceTicks, setupCanvas, thinTicks } from "@/lib/chart-utils";

const M = { l: 46, r: 46, t: 12, b: 26 }; // 边距

export function PotentialChart() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const wrapRef = useRef<HTMLDivElement>(null);
  const potPoints = useStore((s) => s.potPoints);
  const t1 = useStore((s) => s.t1);
  const final = useStore((s) => s.final);
  const { resolvedTheme } = useTheme();
  const [size, setSize] = useState({ w: 0, h: 0 });
  const [hoverX, setHoverX] = useState<number | null>(null);

  useEffect(() => {
    const el = wrapRef.current;
    if (!el) return;
    const ro = new ResizeObserver(() => setSize({ w: el.clientWidth, h: el.clientHeight }));
    ro.observe(el);
    return () => ro.disconnect();
  }, []);

  /* 一阶导数序列（5 点窗口差分） */
  const deriv = useMemo(() => {
    const out: { v: number; d: number }[] = [];
    for (let i = 5; i < potPoints.length; i++) {
      const a = potPoints[i - 5];
      const b = potPoints[i];
      if (b.v > a.v) out.push({ v: b.v, d: (b.e - a.e) / (b.v - a.v) });
    }
    return out;
  }, [potPoints]);

  const draw = useCallback(() => {
    const canvas = canvasRef.current;
    if (!canvas || size.w < 10 || size.h < 10) return;
    const ctx = setupCanvas(canvas);
    if (!ctx) return;

    const grid = cssVar("--chart-grid");
    const gridStrong = cssVar("--border");
    const text = cssVar("--muted-foreground");
    const colE = cssVar("--curve-potential");
    const colD = cssVar("--curve-derivative");
    const accent = cssVar("--foreground");

    const W = size.w;
    const H = size.h;
    ctx.clearRect(0, 0, W, H);
    const pw = W - M.l - M.r;
    const ph = H - M.t - M.b;
    if (pw < 10 || ph < 10) return;

    /* 量程 */
    const vMax = Math.max(1, potPoints.length ? potPoints[potPoints.length - 1].v * 1.04 : 10);
    let eMin = Infinity;
    let eMax = -Infinity;
    for (const p of potPoints) {
      if (p.e < eMin) eMin = p.e;
      if (p.e > eMax) eMax = p.e;
    }
    if (!potPoints.length) {
      eMin = -0.2;
      eMax = 1.0;
    }
    const ePad = Math.max(0.05, (eMax - eMin) * 0.08);
    eMin -= ePad;
    eMax += ePad;
    let dMax = 0.1;
    for (const p of deriv) if (p.d > dMax) dMax = p.d;
    dMax *= 1.15;

    const xOf = (v: number) => M.l + (v / vMax) * pw;
    const yOfE = (e: number) => M.t + (1 - (e - eMin) / (eMax - eMin)) * ph;
    const yOfD = (d: number) => M.t + (1 - d / dMax) * ph;

    /* 网格与刻度 */
    ctx.font = "10px ui-monospace, monospace";
    ctx.lineWidth = 1;
    for (const v of thinTicks(niceTicks(0, vMax, 6), pw, 34)) {
      const x = xOf(v);
      ctx.strokeStyle = grid;
      ctx.beginPath();
      ctx.moveTo(x, M.t);
      ctx.lineTo(x, M.t + ph);
      ctx.stroke();
      ctx.fillStyle = text;
      ctx.textAlign = "center";
      ctx.fillText(fmt(v, 1), x, H - 8);
    }
    for (const e of thinTicks(niceTicks(eMin, eMax, 5), ph)) {
      const y = yOfE(e);
      ctx.strokeStyle = grid;
      ctx.beginPath();
      ctx.moveTo(M.l, y);
      ctx.lineTo(M.l + pw, y);
      ctx.stroke();
      ctx.fillStyle = text;
      ctx.textAlign = "right";
      ctx.fillText(fmt(e, 2), M.l - 6, y + 3);
    }
    ctx.textAlign = "left";
    for (const d of thinTicks(niceTicks(0, dMax, 4), ph)) {
      if (d === 0) continue;
      ctx.fillStyle = text;
      ctx.fillText(fmt(d, 1), M.l + pw + 6, yOfD(d) + 3);
    }
    /* 轴框 */
    ctx.strokeStyle = gridStrong;
    ctx.strokeRect(M.l, M.t, pw, ph);

    /* 导数曲线（右轴，虚线，与实线电位拉开） */
    if (deriv.length > 1) {
      ctx.strokeStyle = colD;
      ctx.lineWidth = 1.25;
      ctx.setLineDash([4, 3]);
      ctx.beginPath();
      deriv.forEach((p, i) => {
        const x = xOf(p.v);
        const y = yOfD(Math.max(0, p.d));
        if (i === 0) ctx.moveTo(x, y);
        else ctx.lineTo(x, y);
      });
      ctx.stroke();
      ctx.setLineDash([]);
    }

    /* 电位主曲线 */
    if (potPoints.length > 1) {
      ctx.strokeStyle = colE;
      ctx.lineWidth = 2.25;
      ctx.lineJoin = "round";
      ctx.beginPath();
      potPoints.forEach((p, i) => {
        const x = xOf(p.v);
        const y = yOfE(p.e);
        if (i === 0) ctx.moveTo(x, y);
        else ctx.lineTo(x, y);
      });
      ctx.stroke();
    }

    /* 终点标记 */
    const marks: { v: number; label: string }[] = [];
    if (t1) marks.push({ v: t1.volume, label: "T1" });
    if (final && final.volume !== t1?.volume) marks.push({ v: final.volume, label: "EP" });
    marks.forEach((mk, i) => {
      const x = xOf(mk.v);
      ctx.strokeStyle = accent;
      ctx.setLineDash([4, 4]);
      ctx.lineWidth = 1;
      ctx.beginPath();
      ctx.moveTo(x, M.t);
      ctx.lineTo(x, M.t + ph);
      ctx.stroke();
      ctx.setLineDash([]);
      ctx.fillStyle = accent;
      ctx.textAlign = "center";
      ctx.font = "bold 10px ui-monospace, monospace";
      ctx.fillText(
        `${mk.label} ${mk.v.toFixed(2)}`,
        Math.min(Math.max(x, M.l + 30), W - M.r - 30),
        M.t + 10 + i * 12,
      );
    });

    /* 十字线 */
    if (hoverX !== null && potPoints.length > 1) {
      const v = ((hoverX - M.l) / pw) * vMax;
      if (v >= 0 && v <= vMax) {
        let best = potPoints[0];
        let bd = Infinity;
        for (const p of potPoints) {
          const d = Math.abs(p.v - v);
          if (d < bd) {
            bd = d;
            best = p;
          }
        }
        const x = xOf(best.v);
        ctx.strokeStyle = cssVar("--ring");
        ctx.setLineDash([2, 3]);
        ctx.beginPath();
        ctx.moveTo(x, M.t);
        ctx.lineTo(x, M.t + ph);
        ctx.stroke();
        ctx.setLineDash([]);
        ctx.fillStyle = colE;
        ctx.beginPath();
        ctx.arc(x, yOfE(best.e), 3, 0, Math.PI * 2);
        ctx.fill();
        const label = `V=${best.v.toFixed(2)} mL  E=${best.e.toFixed(3)} V`;
        ctx.font = "10px ui-monospace, monospace";
        const tw = ctx.measureText(label).width + 12;
        const bx = Math.min(x + 8, W - M.r - tw);
        ctx.fillStyle = cssVar("--popover");
        ctx.strokeStyle = gridStrong;
        ctx.beginPath();
        ctx.roundRect(bx, M.t + 16, tw, 18, 3);
        ctx.fill();
        ctx.stroke();
        ctx.fillStyle = cssVar("--popover-foreground");
        ctx.textAlign = "left";
        ctx.fillText(label, bx + 6, M.t + 28);
      }
    }
  }, [potPoints, deriv, t1, final, size, hoverX, resolvedTheme]);

  useEffect(() => {
    const raf = requestAnimationFrame(draw);
    return () => cancelAnimationFrame(raf);
  }, [draw]);

  return (
    <div ref={wrapRef} className="absolute inset-0 bg-transparent">
      <canvas
        ref={canvasRef}
        className="absolute inset-0 h-full w-full"
        onMouseMove={(e) => {
          const rect = e.currentTarget.getBoundingClientRect();
          setHoverX(e.clientX - rect.left);
        }}
        onMouseLeave={() => setHoverX(null)}
      />
    </div>
  );
}
