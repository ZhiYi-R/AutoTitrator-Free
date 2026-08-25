"use client";

/**
 * 标定页：泵体积标定（点动给固定脉冲数 → 称量累积体积 → ≥10 点线性拟合）
 * 与光谱标定矩阵信息。
 */
import { useEffect, useMemo, useRef, useState } from "react";
import { Gauge, Plus, Sparkles, Trash2 } from "lucide-react";
import { toast } from "sonner";
import { Card, CardContent, CardTitle } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import { useStore } from "@/lib/store";
import { useT } from "@/lib/i18n";
import { backend } from "@/lib/backend";
import type { CalPoint } from "@/lib/types";
import { cssVar, setupCanvas } from "@/lib/chart-utils";
import { cn } from "@/lib/utils";

/* ---------------- 泵标定：点动 + 多点线性拟合 ---------------- */

const MIN_POINTS = 10;

interface Fit {
  k: number;    /* mL/step */
  b: number;    /* 截距 mL */
  r2: number;
  slope: number; /* steps/mL */
}

function linfit(pts: CalPoint[]): Fit | null {
  const n = pts.length;
  if (n < 2) return null;
  let sx = 0, sy = 0, sxx = 0, sxy = 0;
  for (const p of pts) {
    sx += p.steps; sy += p.vol;
    sxx += p.steps * p.steps; sxy += p.steps * p.vol;
  }
  const den = n * sxx - sx * sx;
  if (Math.abs(den) < 1e-12) return null;
  const k = (n * sxy - sx * sy) / den;
  const b = (sy - k * sx) / n;
  if (k <= 0) return null;
  const my = sy / n;
  let ssTot = 0, ssRes = 0;
  for (const p of pts) {
    ssTot += (p.vol - my) ** 2;
    ssRes += (p.vol - (k * p.steps + b)) ** 2;
  }
  const r2 = ssTot < 1e-12 ? 1 : 1 - ssRes / ssTot;
  return { k, b, r2, slope: 1 / k };
}

/* 散点 + 拟合直线预览 */
function CalScatter({ points, fit, loadedSlope }: { points: CalPoint[]; fit: Fit | null; loadedSlope: number }) {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const wrapRef = useRef<HTMLDivElement>(null);
  const [size, setSize] = useState({ w: 0, h: 0 });

  useEffect(() => {
    const el = wrapRef.current;
    if (!el) return;
    const ro = new ResizeObserver(() => setSize({ w: el.clientWidth, h: el.clientHeight }));
    ro.observe(el);
    return () => ro.disconnect();
  }, []);

  useEffect(() => {
    const raf = requestAnimationFrame(() => {
      const canvas = canvasRef.current;
      if (!canvas || size.w < 10 || size.h < 10) return;
      const ctx = setupCanvas(canvas);
      if (!ctx) return;
      const W = size.w, H = size.h;
      ctx.clearRect(0, 0, W, H);
      const ml = 40, mr = 10, mt = 8, mb = 20;
      const pw = W - ml - mr, ph = H - mt - mb;
      if (pw < 10 || ph < 10) return;

      const loadedK = loadedSlope > 0 ? 1 / loadedSlope : 0;
      const xMax = Math.max(4200, ...points.map((p) => p.steps)) * 1.06;
      const yMax = Math.max(
        0.2,
        ...points.map((p) => p.vol),
        loadedK * xMax,
        fit ? fit.k * xMax + fit.b : 0,
      ) * 1.1;
      const xOf = (x: number) => ml + (x / xMax) * pw;
      const yOf = (y: number) => mt + (1 - y / yMax) * ph;

      ctx.strokeStyle = cssVar("--border");
      ctx.strokeRect(ml, mt, pw, ph);
      ctx.font = "9px ui-monospace, monospace";
      ctx.fillStyle = cssVar("--muted-foreground");
      ctx.textAlign = "center";
      for (const f of [0.25, 0.5, 0.75]) ctx.fillText(String(Math.round(xMax * f)), xOf(xMax * f), H - 6);
      /* 末端刻度右对齐，避免文字越出画布右缘被裁掉 */
      ctx.textAlign = "right";
      ctx.fillText(String(Math.round(xMax)), ml + pw, H - 6);
      for (const f of [0.5, 1]) ctx.fillText((yMax * f).toFixed(2), ml - 4, yOf(yMax * f) + 3);

      if (loadedK > 0) {
        ctx.strokeStyle = cssVar("--curve-derivative");
        ctx.lineWidth = 1.25;
        ctx.setLineDash([5, 4]);
        ctx.beginPath();
        ctx.moveTo(xOf(0), yOf(0));
        ctx.lineTo(xOf(xMax), yOf(loadedK * xMax));
        ctx.stroke();
        ctx.setLineDash([]);
      }
      if (fit && points.length >= 2) {
        ctx.strokeStyle = cssVar("--curve-potential");
        ctx.lineWidth = 1.5;
        ctx.beginPath();
        ctx.moveTo(xOf(0), yOf(Math.max(0, fit.b)));
        ctx.lineTo(xOf(xMax), yOf(fit.k * xMax + fit.b));
        ctx.stroke();
      }
      ctx.fillStyle = cssVar("--foreground");
      for (const p of points) {
        ctx.beginPath();
        ctx.arc(xOf(p.steps), yOf(p.vol), 2.5, 0, Math.PI * 2);
        ctx.fill();
      }
    });
    return () => cancelAnimationFrame(raf);
  }, [points, fit, loadedSlope, size]);

  return (
    <div ref={wrapRef} className="absolute inset-0">
      <canvas ref={canvasRef} className="absolute inset-0 h-full w-full" />
    </div>
  );
}

function FitMetrics({
  slope,
  interceptMl,
  r2,
  slopeLabel,
  interceptLabel,
}: {
  slope: number;
  interceptMl: number;
  r2: number | null;
  slopeLabel: string;
  interceptLabel: string;
}) {
  const t = useT();
  return (
    <>
      <span>{slopeLabel} <b className="readout text-foreground">{slope.toLocaleString(undefined, { maximumFractionDigits: 0 })}</b> {t("cal.slopeUnit")}</span>
      <span>{interceptLabel} <b className="readout text-foreground">{(interceptMl * 1000).toFixed(1)}</b> µL</span>
      <span>R² <b className={cn("readout", r2 === null ? "text-muted-foreground" : r2 >= 0.999 ? "text-[var(--status-ok)]" : r2 >= 0.99 ? "text-foreground" : "text-[var(--status-warn)]")}>{r2 === null ? "—" : r2.toFixed(5)}</b></span>
    </>
  );
}

function PumpCalibration() {
  const t = useT();
  const pumpSlope = useStore((s) => s.pumpSlope);
  const pumpIntercept = useStore((s) => s.pumpIntercept);
  const pumpR2 = useStore((s) => s.pumpR2);
  const loadedPoints = useStore((s) => s.calPoints);
  const connected = useStore((s) => s.connected);
  const busy = useStore((s) => ["injecting", "titrating", "degree1", "titrating2"].includes(s.workflow));

  useEffect(() => {
    backend.loadPumpCalibration();
  }, []);

  const [jogSteps, setJogSteps] = useState(400);
  const [measuredText, setMeasuredText] = useState("");
  const [cumSteps, setCumSteps] = useState(0); /* 已指令累计步数 */
  const [draft, setDraft] = useState<CalPoint[] | null>(null);
  const session = draft !== null;
  const points = session ? draft : loadedPoints;

  const measured = Number(measuredText);
  const measuredOk = Number.isFinite(measured) && measured > 0;
  const fit = useMemo(() => linfit(points), [points]);
  const canApply = session && fit !== null && points.length >= MIN_POINTS;
    const cluster = "flex h-8 items-stretch overflow-hidden rounded-sm border";
  const spin =
    "h-full w-[4.5rem] rounded-none border-0 bg-transparent px-1.5 py-0 text-center font-mono text-[12px] leading-8 shadow-none md:text-[12px] md:leading-8 dark:bg-transparent [appearance:textfield] [&::-webkit-inner-spin-button]:appearance-none [&::-webkit-outer-spin-button]:appearance-none";
  const clusterLabel =
    "flex h-full items-center bg-muted/60 px-2 font-mono text-[12px] leading-8 text-muted-foreground whitespace-nowrap";
  const clusterUnit =
    "flex h-full items-center pr-2 font-mono text-[12px] leading-8 text-muted-foreground";

  const jog = () => {
    if (!connected) { toast.warning(t("toast.needConnect")); return; }
    backend.jog(2, jogSteps);
    setCumSteps((s) => s + jogSteps);
  };

  const addPoint = () => {
    if (cumSteps <= 0 || !measuredOk) return;
    const next = [...(draft ?? []), { steps: cumSteps, vol: measured }];
    setDraft(next);
    toast.success(t("toast.pointAdded", { n: next.length, v: measured.toFixed(3) }));
  };

  const removePoint = (i: number) => {
    if (!session) return;
    setDraft((ps) => (ps ?? []).filter((_, idx) => idx !== i));
  };

  const apply = async () => {
    if (!fit || !session || !draft) return;
    const next = Math.round(fit.slope);
    if (!await backend.applyPumpCalibration(draft, next, fit.b, fit.r2)) return;
    setDraft(null);
    setCumSteps(0);
    setMeasuredText("");
    toast.success(t("toast.calApplied", { slope: next.toLocaleString() }));
  };

  return (
    <Card className="flex min-h-0 min-w-0 flex-1 flex-col">
      <div className="flex h-10 shrink-0 items-center justify-between gap-3 border-b px-4">
        <CardTitle className="flex items-center gap-2 text-[13px]"><Gauge size={15} /> {t("cal.pumpTitle")}</CardTitle>
        <div className="flex items-baseline gap-4 font-mono text-[12px]">
          <span className="flex items-baseline gap-1.5">
            <span className="text-[10px] tracking-wide text-muted-foreground uppercase">{t("cal.progress")}</span>
            <b className={cn("readout", session && points.length >= MIN_POINTS ? "text-[var(--status-ok)]" : "text-foreground")}>
              {session ? `${points.length}/${MIN_POINTS}` : String(points.length)}
            </b>
          </span>
          <span className="flex items-baseline gap-1.5">
            <span className="text-[10px] tracking-wide text-muted-foreground uppercase">{t("cal.slope")}</span>
            <b className="readout text-foreground">{pumpSlope.toLocaleString()}</b>
            <span className="text-muted-foreground">{t("cal.slopeUnit")}</span>
          </span>
        </div>
      </div>
      <CardContent className="flex min-h-0 flex-1 flex-col gap-2.5 px-4 pb-3">
        <div className="flex shrink-0 flex-wrap items-center gap-2">
          <div className={cluster} role="group" aria-label={t("cal.steps")}>
            <span className={clusterLabel}>{t("cal.steps")}</span>
            <Input type="number" min={1} max={20000} value={jogSteps} disabled={!connected || busy}
              onChange={(e) => setJogSteps(Number(e.target.value) || 0)} className={spin} aria-label={t("cal.steps")} />
            <span className={clusterUnit}>{t("cal.stepsUnit")}</span>
            <Separator orientation="vertical" />
            <Button size="sm" variant="ghost" className="h-full rounded-none px-2.5" disabled={!connected || busy} onClick={jog}>
              {t("cal.jog")}
            </Button>
          </div>
          <span className="font-mono text-[12px] text-muted-foreground">Σ {cumSteps.toLocaleString()}</span>
          <div className={cluster} role="group" aria-label={t("cal.weigh")}>
            <span className={clusterLabel}>{t("cal.weigh")}</span>
            <Input type="number" min={0} step="any" inputMode="decimal" value={measuredText} disabled={busy} placeholder="0.000"
              onChange={(e) => setMeasuredText(e.target.value)} className={spin} aria-label={t("cal.weigh")} />
            <span className={clusterUnit}>mL</span>
            <Separator orientation="vertical" />
            <Button size="sm" className="h-full rounded-none px-2.5" disabled={busy || cumSteps <= 0 || !measuredOk} onClick={addPoint}>
              <Plus size={13} /> {t("cal.addPoint")}
            </Button>
          </div>
        </div>

        {/* 散点预览 + 点表 */}
        <div className="grid min-h-0 flex-1 grid-cols-[minmax(0,1fr)_18rem] items-stretch gap-3">
          <div className="flex min-h-0 min-w-0 flex-col overflow-hidden rounded-sm border">
            <div className="flex h-8 shrink-0 items-center gap-3 border-b px-2.5 text-[11px] text-muted-foreground">
              <span>{t("cal.fitPreview")}</span>
              <span className="flex items-center gap-1.5">
                <span className="h-px w-4 border-t border-dashed border-[var(--curve-derivative)]" />
                {t("cal.loadedFit")} {pumpSlope.toLocaleString()} {t("cal.slopeUnit")}
              </span>
              {fit && session && (
                <span className="flex items-center gap-1.5">
                  <span className="h-0.5 w-4 bg-[var(--curve-potential)]" />
                  {t("cal.fitSlope")} {fit.slope.toFixed(0)}
                </span>
              )}
            </div>
            <div className="relative min-h-0 flex-1 bg-transparent">
              <CalScatter points={points} fit={session ? fit : null} loadedSlope={pumpSlope} />
            </div>
          </div>
          <div className="flex min-h-0 flex-col overflow-hidden rounded-sm border">
            <div className="grid h-8 shrink-0 grid-cols-[1.5rem_1fr_1fr_1fr_1.25rem] items-center gap-1 border-b px-2 text-[11px] text-muted-foreground">
              <span>#</span>
              <span className="text-right">{t("cal.cumSteps")}</span>
              <span className="text-right">{t("cal.cumVol")}</span>
              <span className="text-right">{t("cal.residual")}</span>
              <span />
            </div>
            <ScrollArea className="min-h-0 flex-1">
              <div className="px-2 py-1 font-mono text-[11px]">
                {points.length === 0 && <p className="px-0.5 py-1 text-muted-foreground">—</p>}
                {points.map((p, i) => {
                  const model = session
                    ? (fit ? fit.k * p.steps + fit.b : null)
                    : (pumpSlope > 0 ? p.steps / pumpSlope : null);
                  const res = model === null ? null : (p.vol - model) * 1000;
                  return (
                    <div key={`${p.steps}-${i}`} className="grid grid-cols-[1.5rem_1fr_1fr_1fr_1.25rem] items-center gap-1 py-0.5">
                      <span className="text-muted-foreground">{i + 1}</span>
                      <span className="text-right">{p.steps.toLocaleString()}</span>
                      <span className="text-right">{p.vol.toFixed(3)}</span>
                      <span className={cn("text-right", res !== null && Math.abs(res) > 20 ? "text-[var(--status-warn)]" : "text-muted-foreground")}>
                        {res === null ? "—" : (res >= 0 ? "+" : "") + res.toFixed(1)}
                      </span>
                      {session ? (
                        <button className="rounded text-muted-foreground outline-none hover:text-[var(--status-danger)] focus-visible:ring-2 focus-visible:ring-ring" onClick={() => removePoint(i)}>
                          <Trash2 size={11} />
                        </button>
                      ) : (
                        <span />
                      )}
                    </div>
                  );
                })}
              </div>
            </ScrollArea>
          </div>
        </div>

        {/* 拟合结果 + 动作 */}
        <div className="flex shrink-0 items-center justify-between">
          <div className="flex items-center gap-4 font-mono text-[11px] text-muted-foreground">
            {session && !fit ? (
              <span>{t("cal.fitPending")}</span>
            ) : (
              <FitMetrics
                slope={session && fit ? fit.slope : pumpSlope}
                interceptMl={session && fit ? fit.b : pumpIntercept}
                r2={session && fit ? fit.r2 : pumpR2}
                slopeLabel={session ? t("cal.fitSlope") : t("cal.slope")}
                interceptLabel={t("cal.fitIntercept")}
              />
            )}
          </div>
          <div className="flex gap-2">
            <Button size="sm" variant="ghost" className="h-8" disabled={!session} onClick={() => { setDraft(null); setCumSteps(0); setMeasuredText(""); }}>
              {t("cal.clearPoints")}
            </Button>
            <Button size="sm" className="h-8" disabled={!canApply} onClick={apply} title={canApply ? undefined : t("cal.needPoints")}>
              {t("cal.apply")}
            </Button>
          </div>
        </div>
      </CardContent>
    </Card>
  );
}

/* ---------------- 光谱标定矩阵 ---------------- */

function SpectralCalibration() {
  const t = useT();
  const [loadedAt, setLoadedAt] = useState(() => new Date());
  const facts = [
    [t("cal.specRange"), "380 – 1100 nm（Δ12）"],
    [t("cal.specChannels"), "61"],
    [t("cal.specCond"), "18.4"],
    [t("cal.specLoaded"), loadedAt.toLocaleTimeString("zh-CN", { hour12: false })],
  ];
  return (
    <div className="flex h-10 shrink-0 items-center gap-3 overflow-x-auto rounded-md border bg-card px-3 text-[12px]">
      <span className="flex shrink-0 items-center gap-1.5 font-medium whitespace-nowrap">
        <Sparkles size={14} /> {t("cal.specTitle")}
      </span>
      {facts.map(([k, v]) => (
        <span key={k} className="flex shrink-0 items-baseline gap-1.5 whitespace-nowrap">
          <span className="text-[10px] tracking-wide text-muted-foreground uppercase">{k}</span>
          <span className="readout">{v}</span>
        </span>
      ))}
      <div className="flex-1" />
      <Button
        size="sm"
        variant="outline"
        className="h-7 shrink-0 rounded-sm"
        onClick={() => { setLoadedAt(new Date()); toast.success(t("toast.calReloaded")); }}
      >
        {t("cal.reload")}
      </Button>
    </div>
  );
}

/* ---------------- 页面：光谱状态条 + 泵标定工作台 ---------------- */

export function CalibrationPage() {
  return (
    <div className="flex h-full min-h-0 flex-col gap-2.5 p-2.5">
      <SpectralCalibration />
      <PumpCalibration />
    </div>
  );
}
