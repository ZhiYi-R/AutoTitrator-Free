"use client";

/**
 * 最新光谱曲线 + J-S 散度演化曲线。
 * 散度：逐帧相对基线（前 N 帧均值分布）的 D_JS(p̂‖p₀)，nats ——
 * 与 controller-core tracker 的事件判据同口径，终点谱带突变表现为陡峭抬升。
 */
import { useCallback, useEffect, useRef, useState } from "react";
import { useStore } from "@/lib/store";
import { WAVELENGTHS } from "@/lib/types";
import { cssVar, fmt, niceTicks, setupCanvas, thinTicks } from "@/lib/chart-utils";

type SpectrumFrame = { v: number; absorbance: number[] };

const BASELINE_FRAMES = 5;

/** 基线光谱：前 BASELINE_FRAMES 帧吸光度逐通道均值（J-S 散度 p₀ 与基线曲线共用此窗口） */
function baselineSpectrum(spectra: SpectrumFrame[]): number[] | null {
  if (spectra.length === 0) return null;
  const n = WAVELENGTHS.length;
  const k = Math.min(BASELINE_FRAMES, spectra.length);
  const acc = new Float64Array(n);
  for (let i = 0; i < k; i++) {
    for (let r = 0; r < n; r++) acc[r] += spectra[i].absorbance[r] ?? 0;
  }
  return Array.from(acc, (a) => a / k);
}

/** 逐帧相对基线分布的 J-S 散度（nats） */
function jsDivergenceSeries(spectra: SpectrumFrame[]): Array<{ v: number; d: number }> {
  if (spectra.length === 0) return [];
  const n = WAVELENGTHS.length;
  const base = baselineSpectrum(spectra);
  const baseSum = base ? base.reduce((a, b) => a + b, 0) : 0;
  const p0 = base && baseSum > 0 ? base.map((b) => b / baseSum) : null;
  if (!p0) return spectra.map((f) => ({ v: f.v, d: 0 }));
  const js = (abs: number[]) => {
    const s = abs.reduce((a, b) => a + b, 0);
    if (s <= 0) return 0;
    let d = 0;
    for (let i = 0; i < n; i++) {
      const p = (abs[i] ?? 0) / s;
      const q = p0[i];
      const m = (p + q) / 2;
      if (p > 0) d += 0.5 * p * Math.log(p / m);
      if (q > 0) d += 0.5 * q * Math.log(q / m);
    }
    return d;
  };
  return spectra.map((f) => ({ v: f.v, d: js(f.absorbance) }));
}

/** J-S 散度演化：横轴体积、纵轴 D_JS(nats)，与电位图共享体积轴语义 */
export function JsDivergenceChart() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const wrapRef = useRef<HTMLDivElement>(null);
  const spectra = useStore((s) => s.spectra);
  const [size, setSize] = useState({ w: 0, h: 0 });

  useEffect(() => {
    const el = wrapRef.current;
    if (!el) return;
    const ro = new ResizeObserver(() => setSize({ w: el.clientWidth, h: el.clientHeight }));
    ro.observe(el);
    return () => ro.disconnect();
  }, []);

  const draw = useCallback(() => {
    const canvas = canvasRef.current;
    if (!canvas || size.w < 10 || size.h < 10) return;
    const ctx = setupCanvas(canvas);
    if (!ctx) return;

    const W = size.w;
    const H = size.h;
    ctx.clearRect(0, 0, W, H);
    const ml = 36;
    const mr = 8;
    const mt = 8;
    const mb = 18;
    const pw = W - ml - mr;
    const ph = H - mt - mb;
    if (pw < 10 || ph < 10) return;

    const series = jsDivergenceSeries(spectra);

    ctx.strokeStyle = cssVar("--border");
    ctx.strokeRect(ml, mt, pw, ph);
    ctx.font = "9px ui-monospace, monospace";

    /* y 轴：散度，量级随体系变化，刻度小数位自适应 */
    const dMax = Math.max(1e-6, ...series.map((s) => s.d));
    const yTicks = niceTicks(0, dMax, 3);
    const yMax = yTicks[yTicks.length - 1] || 1;
    const dec = yMax < 0.005 ? 4 : yMax < 0.05 ? 3 : 2;
    ctx.textAlign = "right";
    for (const d of yTicks) {
      const y = mt + (1 - d / yMax) * ph;
      ctx.fillStyle = cssVar("--muted-foreground");
      ctx.fillText(fmt(d, dec), ml - 4, y + 3);
      if (d > 0) {
        ctx.strokeStyle = cssVar("--chart-grid");
        ctx.globalAlpha = 0.35;
        ctx.beginPath();
        ctx.moveTo(ml, y);
        ctx.lineTo(ml + pw, y);
        ctx.stroke();
        ctx.globalAlpha = 1;
      }
    }

    /* x 轴：体积（mL），与热图/potential 图同轴语义 */
    const vMax = series.length > 0 ? series[series.length - 1].v : 0;
    if (vMax > 0) {
      ctx.textAlign = "center";
      for (const v of thinTicks(niceTicks(0, vMax, 5), pw, 34)) {
        const x = ml + (v / vMax) * pw;
        ctx.fillStyle = cssVar("--muted-foreground");
        ctx.fillText(fmt(v, 1), x, H - 5);
      }
    }

    if (series.length === 0) return;
    ctx.strokeStyle = cssVar("--curve-derivative");
    ctx.lineWidth = 1.5;
    ctx.beginPath();
    series.forEach((s, i) => {
      const x = ml + (vMax > 0 ? (s.v / vMax) * pw : 0);
      const y = mt + (1 - Math.min(s.d / yMax, 1)) * ph;
      if (i === 0) ctx.moveTo(x, y);
      else ctx.lineTo(x, y);
    });
    ctx.stroke();
  }, [spectra, size]);

  useEffect(() => {
    const raf = requestAnimationFrame(draw);
    return () => cancelAnimationFrame(raf);
  }, [draw]);

  return (
    <div ref={wrapRef} className="absolute inset-0">
      <canvas ref={canvasRef} className="absolute inset-0 h-full w-full" />
    </div>
  );
}

/** 最新一帧光谱：吸光度–波长折线 */
export function LatestSpectrum() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const wrapRef = useRef<HTMLDivElement>(null);
  const spectra = useStore((s) => s.spectra);
  const [size, setSize] = useState({ w: 0, h: 0 });

  useEffect(() => {
    const el = wrapRef.current;
    if (!el) return;
    const ro = new ResizeObserver(() => setSize({ w: el.clientWidth, h: el.clientHeight }));
    ro.observe(el);
    return () => ro.disconnect();
  }, []);

  const draw = useCallback(() => {
    const canvas = canvasRef.current;
    if (!canvas || size.w < 10 || size.h < 10) return;
    const ctx = setupCanvas(canvas);
    if (!ctx) return;
    const W = size.w;
    const H = size.h;
    ctx.clearRect(0, 0, W, H);
    const ml = 36;
    const mr = 10;
    const mt = 8;
    const mb = 18;
    const pw = W - ml - mr;
    const ph = H - mt - mb;
    if (pw < 10 || ph < 10) return;

    ctx.strokeStyle = cssVar("--border");
    ctx.strokeRect(ml, mt, pw, ph);
    ctx.font = "9px ui-monospace, monospace";
    ctx.fillStyle = cssVar("--muted-foreground");
    ctx.textAlign = "center";
    for (const wl of [400, 600, 800, 1000]) {
      const x = ml + ((wl - 380) / 720) * pw;
      ctx.fillText(String(wl), x, H - 4);
    }

    const frame = spectra[spectra.length - 1];
    if (!frame) return;
    /* 基线幽灵曲线：≥2 帧后才画（单帧时基线≈当前帧，无信息量） */
    const baseline = spectra.length >= 2 ? baselineSpectrum(spectra) : null;
    let lo = Infinity;
    let hi = -Infinity;
    for (const a of frame.absorbance) {
      if (a < lo) lo = a;
      if (a > hi) hi = a;
    }
    if (baseline) {
      for (const a of baseline) {
        if (a < lo) lo = a;
        if (a > hi) hi = a;
      }
    }
    const span = Math.max(1e-6, hi - lo);
    ctx.fillStyle = cssVar("--muted-foreground");
    ctx.textAlign = "right";
    ctx.fillText(fmt(hi, 2), ml - 3, mt + 8);
    ctx.fillText(fmt(lo, 2), ml - 3, mt + ph);

    if (baseline) {
      ctx.strokeStyle = cssVar("--muted-foreground");
      ctx.lineWidth = 1;
      ctx.setLineDash([4, 3]);
      ctx.globalAlpha = 0.7;
      ctx.beginPath();
      baseline.forEach((a, i) => {
        const x = ml + ((WAVELENGTHS[i] - 380) / 720) * pw;
        const y = mt + (1 - (a - lo) / span) * ph;
        if (i === 0) ctx.moveTo(x, y);
        else ctx.lineTo(x, y);
      });
      ctx.stroke();
      ctx.setLineDash([]);
      ctx.globalAlpha = 1;
    }

    ctx.strokeStyle = cssVar("--curve-spectrum");
    ctx.lineWidth = 1.5;
    ctx.beginPath();
    frame.absorbance.forEach((a, i) => {
      const x = ml + ((WAVELENGTHS[i] - 380) / 720) * pw;
      const y = mt + (1 - (a - lo) / span) * ph;
      if (i === 0) ctx.moveTo(x, y);
      else ctx.lineTo(x, y);
    });
    ctx.stroke();
  }, [spectra, size]);

  useEffect(() => {
    const raf = requestAnimationFrame(draw);
    return () => cancelAnimationFrame(raf);
  }, [draw]);

  return (
    <div ref={wrapRef} className="absolute inset-0">
      <canvas ref={canvasRef} className="absolute inset-0 h-full w-full" />
    </div>
  );
}
