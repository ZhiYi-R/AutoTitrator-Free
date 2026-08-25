"use client";

/**
 * 光谱演化热图 + 最新光谱曲线。
 * 热图：横轴滴加体积、纵轴波长、灰度=吸光度 —— 终点处 560nm 指示剂谱带
 * 的突变在灰阶图上表现为一条清晰的纵向亮带。
 */
import { useCallback, useEffect, useRef, useState } from "react";
import { useTheme } from "next-themes";
import { useStore } from "@/lib/store";
import { WAVELENGTHS } from "@/lib/types";
import { cssVar, fmt, niceTicks, setupCanvas, thinTicks } from "@/lib/chart-utils";

const M = { l: 28, r: 6, t: 6, b: 16 };
const MAX_COLS = 720;

export function SpectrumHeatmap() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const wrapRef = useRef<HTMLDivElement>(null);
  const spectra = useStore((s) => s.spectra);
  const { resolvedTheme } = useTheme();
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
    const dark = resolvedTheme === "dark";

    const W = size.w;
    const H = size.h;
    ctx.clearRect(0, 0, W, H);
    const pw = W - M.l - M.r;
    const ph = H - M.t - M.b;
    if (pw < 10 || ph < 10) return;

    const grid = cssVar("--chart-grid");
    const text = cssVar("--muted-foreground");
    ctx.strokeStyle = cssVar("--border");
    ctx.strokeRect(M.l, M.t, pw, ph);
    ctx.font = "9px ui-monospace, monospace";

    /* y 轴：波长（窄栏只标关键刻度） */
    for (const wl of thinTicks([400, 600, 800, 1000], ph)) {
      const y = M.t + (1 - (wl - 380) / 720) * ph;
      ctx.fillStyle = text;
      ctx.textAlign = "right";
      ctx.fillText(String(wl), M.l - 6, y + 3);
      ctx.strokeStyle = grid;
      ctx.globalAlpha = 0.35;
      ctx.beginPath();
      ctx.moveTo(M.l, y);
      ctx.lineTo(M.l + pw, y);
      ctx.stroke();
      ctx.globalAlpha = 1;
    }

    if (spectra.length < 2) return;

    /* x 轴：体积 */
    const vMax = spectra[spectra.length - 1].v;
    for (const v of thinTicks(niceTicks(0, vMax, 6), pw, 34)) {
      const x = M.l + (v / vMax) * pw;
      ctx.fillStyle = text;
      ctx.textAlign = "center";
      ctx.fillText(fmt(v, 1), x, H - 6);
    }

    /* 数据范围 */
    let lo = Infinity;
    let hi = -Infinity;
    for (const f of spectra) {
      for (const a of f.absorbance) {
        if (a < lo) lo = a;
        if (a > hi) hi = a;
      }
    }
    const span = Math.max(1e-6, hi - lo);

    /* 离屏位图（列=帧、行=通道），再缩放绘制 */
    const stride = Math.max(1, Math.ceil(spectra.length / MAX_COLS));
    const cols = Math.ceil(spectra.length / stride);
    const off = document.createElement("canvas");
    off.width = cols;
    off.height = WAVELENGTHS.length;
    const octx = off.getContext("2d");
    if (!octx) return;
    const img = octx.createImageData(cols, WAVELENGTHS.length);
    for (let c = 0; c < cols; c++) {
      const f = spectra[c * stride];
      for (let r = 0; r < WAVELENGTHS.length; r++) {
        const t = (f.absorbance[r] - lo) / span;
        const g = dark ? Math.round(30 + t * 215) : Math.round(245 - t * 215);
        const idx = (r * cols + c) * 4;
        img.data[idx] = g;
        img.data[idx + 1] = g;
        img.data[idx + 2] = g;
        img.data[idx + 3] = 255;
      }
    }
    octx.putImageData(img, 0, 0);
    ctx.imageSmoothingEnabled = true;
    /* y 方向翻转：波长小的在上 */
    ctx.save();
    ctx.translate(M.l, M.t + ph);
    ctx.scale(pw / cols, -ph / WAVELENGTHS.length);
    ctx.drawImage(off, 0, 0);
    ctx.restore();
  }, [spectra, size, resolvedTheme]);

  useEffect(() => {
    const raf = requestAnimationFrame(draw);
    return () => cancelAnimationFrame(raf);
  }, [draw]);

  return (
    <div ref={wrapRef} className="absolute inset-0 bg-transparent">
      <canvas ref={canvasRef} className="absolute inset-0 h-full w-full" />
    </div>
  );
}

/** 最新一帧光谱：吸光度–波长折线 */
export function LatestSpectrum() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const wrapRef = useRef<HTMLDivElement>(null);
  const spectra = useStore((s) => s.spectra);
  const { resolvedTheme } = useTheme();
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
    let lo = Infinity;
    let hi = -Infinity;
    for (const a of frame.absorbance) {
      if (a < lo) lo = a;
      if (a > hi) hi = a;
    }
    const span = Math.max(1e-6, hi - lo);
    ctx.textAlign = "right";
    ctx.fillText(fmt(hi, 2), ml - 3, mt + 8);
    ctx.fillText(fmt(lo, 2), ml - 3, mt + ph);

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
  }, [spectra, size, resolvedTheme]);

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
