/** Canvas 图表公共工具：DPR 适配、刻度、CSS 变量取色 */

export function setupCanvas(canvas: HTMLCanvasElement): CanvasRenderingContext2D | null {
  const rect = canvas.getBoundingClientRect();
  if (rect.width < 4 || rect.height < 4) return null;
  const dpr = window.devicePixelRatio || 1;
  const w = Math.round(rect.width * dpr);
  const h = Math.round(rect.height * dpr);
  if (canvas.width !== w || canvas.height !== h) {
    canvas.width = w;
    canvas.height = h;
  }
  const ctx = canvas.getContext("2d");
  if (!ctx) return null;
  ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
  return ctx;
}

/** 生成 ~count 个“漂亮”刻度值 */
export function niceTicks(min: number, max: number, count = 5): number[] {
  if (!isFinite(min) || !isFinite(max) || max <= min) return [];
  const span = max - min;
  const step0 = span / Math.max(1, count);
  const mag = Math.pow(10, Math.floor(Math.log10(step0)));
  const norm = step0 / mag;
  const step = (norm >= 5 ? 5 : norm >= 2 ? 2 : 1) * mag;
  const ticks: number[] = [];
  for (let v = Math.ceil(min / step) * step; v <= max + step * 1e-6; v += step) {
    ticks.push(Number(v.toFixed(10)));
  }
  return ticks;
}

/** 按可用空间稀疏刻度：保证相邻标签间距 ≥ minGap（px），防止小尺寸下文字重叠 */
export function thinTicks(ticks: number[], spanPx: number, minGap = 13): number[] {
  if (ticks.length < 2 || spanPx <= 0) return ticks;
  const perPx = spanPx / (ticks[ticks.length - 1] - ticks[0] || 1);
  const stride = Math.max(1, Math.ceil(minGap / (Math.abs(perPx) * Math.abs(ticks[1] - ticks[0]) || 1)));
  return ticks.filter((_, i) => i % stride === 0);
}

/** 读取当前主题下的 CSS 变量（含灰阶曲线色与状态色） */
export function cssVar(name: string, fallback = "#888"): string {
  if (typeof window === "undefined") return fallback;
  const v = getComputedStyle(document.documentElement).getPropertyValue(name).trim();
  return v || fallback;
}

export function fmt(v: number, digits = 2): string {
  return v.toFixed(digits);
}

/** 灰阶插值：t∈[0,1]，浅色主题画深、深色主题画亮 */
export function grayRamp(t: number, dark: boolean): string {
  const c = dark ? Math.round(30 + t * 215) : Math.round(245 - t * 215);
  return `rgb(${c},${c},${c})`;
}
