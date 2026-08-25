"use client";

/**
 * 滴定工作台：主视图。
 * 左列双图表（电位-体积 / 光谱热图+最新光谱），右列终点结果与事件日志。
 */
import { useMemo } from "react";
import { Check, ChevronRight, CircleSlash, Droplets } from "lucide-react";
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Badge } from "@/components/ui/badge";
import { Button } from "@/components/ui/button";
import { ScrollArea } from "@/components/ui/scroll-area";
import { Separator } from "@/components/ui/separator";
import { useStore, confidenceTone, methodTone, reliabilityTone } from "@/lib/store";
import { useT } from "@/lib/i18n";
import { cn } from "@/lib/utils";
import { toneClass } from "@/lib/tone";
import { PotentialChart } from "@/components/charts/potential-chart";
import { SpectrumHeatmap, LatestSpectrum } from "@/components/charts/spectrum-chart";
import { backend } from "@/lib/backend";
import type { EndpointResult, WorkflowState } from "@/lib/types";

/* ---------------- 工作流步进器 ---------------- */

const FLOW: WorkflowState[] = ["injecting", "titrating", "degree1", "titrating2", "done"];

function Stepper() {
  const t = useT();
  const workflow = useStore((s) => s.workflow);
  const tubingOp = useStore((s) => s.tubingOp);
  const sampleInput = useStore((s) => s.sampleInput);
  const pump1Steps = useStore((s) => s.pump1Steps);
  const pumpSlope = useStore((s) => s.pumpSlope);
  const pumpIntercept = useStore((s) => s.pumpIntercept);
  const errIdx = workflow === "error" ? FLOW.indexOf("titrating") : -1;
  const activeIdx = workflow === "error" ? 1 : workflow === "idle" || tubingOp ? -1 : FLOW.indexOf(workflow);
  const injectionVolume = pumpSlope > 0 ? Math.max(0, pump1Steps / pumpSlope + pumpIntercept) : null;
  const injectionProgress = injectionVolume !== null && sampleInput > 0
    ? Math.min(100, Math.max(0, (injectionVolume / sampleInput) * 100))
    : null;

  return (
    <ol className="flex min-w-0 items-stretch overflow-hidden rounded-sm border bg-card">
      {FLOW.map((s, i) => {
        const done = activeIdx > i || workflow === "done";
        const active = activeIdx === i && workflow !== "done";
        const isErr = workflow === "error" && i === errIdx;
        const injection = i === 0;
        return (
          <li
            key={s}
            className={cn(
              "relative overflow-hidden",
              injection
                ? "flex min-w-0 flex-[1.35] flex-col justify-center gap-1 border-r px-3 py-1.5 text-[11px] font-medium last:border-r-0"
                : "flex min-w-0 flex-1 items-center gap-1.5 border-r px-3 py-1.5 text-[11px] font-medium last:border-r-0",
              done && "bg-muted/70 text-foreground",
              active && "bg-foreground text-background",
              !done && !active && !isErr && "text-muted-foreground",
              isErr && "bg-[var(--status-danger)]/10 text-[var(--status-danger)]"
            )}
          >
            {injection && injectionProgress !== null && (
              <span
                aria-hidden="true"
                className={cn(
                  "absolute inset-y-0 left-0 transition-[width] duration-150",
                  active ? "bg-white/20" : "bg-white/10"
                )}
                style={{ width: `${injectionProgress}%` }}
              />
            )}
            <div className="relative z-10 flex min-w-0 items-center justify-between gap-1.5">
              <span className="flex min-w-0 items-center gap-1.5">
                <span className="font-mono text-[10px] opacity-60">{i + 1}</span>
                {done && <Check size={11} />}
                {isErr && <CircleSlash size={11} />}
                <span className="truncate">{t(`state.${s}`)}</span>
              </span>
              {injection && injectionProgress !== null && (
                <span className="readout shrink-0 text-[10px] tabular-nums opacity-75">{injectionProgress.toFixed(0)}%</span>
              )}
            </div>
            {injection && (
              <span className="relative z-10 readout text-[10px] tabular-nums opacity-70">
                {injectionVolume === null ? "—" : `${injectionVolume.toFixed(2)} / ${sampleInput.toFixed(2)} mL`}
              </span>
            )}
            {!injection && i < FLOW.length - 1 && (
              <ChevronRight size={12} className="relative z-10 ml-auto hidden shrink-0 opacity-40 lg:block" />
            )}
          </li>
        );
      })}
    </ol>
  );
}

/* ---------------- 结果面板 ---------------- */

function ResultBlock({ r }: { r: EndpointResult }) {
  const t = useT();
  return (
    <div className="space-y-1.5">
      <div className="flex items-baseline justify-between">
        <span className="text-[11px] uppercase tracking-wider text-muted-foreground">
          {r.stage === "t1" ? t("results.t1") : t("results.final")}
        </span>
        <span className="readout text-lg font-semibold">
          {r.volume.toFixed(3)} <span className="text-[11px] font-normal text-muted-foreground">mL</span>
        </span>
      </div>
      <div className="flex flex-wrap gap-1">
        <Badge variant="outline" className={toneClass[methodTone(r.method)]}>{t(`method.${r.method}`)}</Badge>
        <Badge variant="outline" className={toneClass[confidenceTone(r.confidence)]}>{t("results.confidence")}: {t(`confidence.${r.confidence}`)}</Badge>
        <Badge variant="outline" className={toneClass[reliabilityTone(r.reliability)]}>{r.reliability}</Badge>
      </div>
      <div className="grid grid-cols-2 gap-x-3 gap-y-1 pt-1 text-[11px]">
        <span className="text-muted-foreground">{t("results.potVol")}</span>
        <span className="readout text-right">{r.potentialVolume?.toFixed(3) ?? "—"}</span>
        <span className="text-muted-foreground">{t("results.specVol")}</span>
        <span className="readout text-right">{r.spectralVolume?.toFixed(3) ?? "—"}</span>
        {r.kf && (
          <>
            <span className="text-muted-foreground">{t("results.kf")}</span>
            <span className="readout text-right">{r.kf.volume.toFixed(3)} ± {r.kf.std.toFixed(3)}</span>
            <span className="text-muted-foreground">{t("results.kfNis")}</span>
            <span className="readout text-right">{r.kf.nis.toFixed(2)}</span>
          </>
        )}
        {r.refined !== null && (
          <>
            <span className="text-muted-foreground">{t("results.refined")}</span>
            <span className="readout text-right">{r.refined.toFixed(3)}</span>
          </>
        )}
      </div>
    </div>
  );
}

function ResultsPanel() {
  const t = useT();
  const t1 = useStore((s) => s.t1);
  const final = useStore((s) => s.final);
  const spectralState = useStore((s) => s.spectralState);
  return (
    <Card className="flex min-h-0 flex-1 flex-col">
      <CardHeader className="flex-row items-center justify-between space-y-0 px-4 py-2.5">
        <CardTitle className="text-[13px]">{t("results.title")}</CardTitle>
        <Badge variant="outline" className={cn("font-mono text-[10px]", toneClass[spectralState === "END_CONFIRMED" ? "ok" : spectralState === "IN_CHANGE" ? "warn" : "muted"])}>
          {t(`spectral.${spectralState}`)}
        </Badge>
      </CardHeader>
      <CardContent className="flex min-h-0 flex-1 flex-col gap-3 overflow-y-auto px-4 pb-3">
        {t1 ? <ResultBlock r={t1} /> : <p className="text-xs text-muted-foreground">{t("results.pending")}</p>}
        {t1 && final && <Separator />}
        {final && <ResultBlock r={final} />}
      </CardContent>
    </Card>
  );
}

/* ---------------- 事件日志 ---------------- */

const levelClass: Record<string, string> = {
  info: "text-muted-foreground",
  ok: "text-[var(--status-ok)]",
  warn: "text-[var(--status-warn)]",
  error: "text-[var(--status-danger)]",
};

function EventLog() {
  const t = useT();
  const logs = useStore((s) => s.logs);
  const clearLogs = useStore((s) => s.clearLogs);
  const items = useMemo(() => [...logs].reverse(), [logs]);
  return (
    <Card className="flex min-h-0 flex-1 flex-col">
      <CardHeader className="flex-row items-center justify-between space-y-0 px-4 py-2.5">
        <CardTitle className="text-[13px]">{t("log.title")}</CardTitle>
        <Button variant="ghost" size="sm" className="h-6 px-2 text-[11px]" onClick={clearLogs}>{t("log.clear")}</Button>
      </CardHeader>
      <ScrollArea className="min-h-0 flex-1 px-4 pb-3">
        <div className="space-y-0.5 font-mono text-[11px] leading-relaxed">
          {items.length === 0 && <p className="text-muted-foreground">—</p>}
          {items.map((l, i) => (
            <div key={i} className="flex gap-2">
              <span className="shrink-0 text-muted-foreground/60">
                {new Date(l.t).toLocaleTimeString("zh-CN", { hour12: false })}
              </span>
              <span className={levelClass[l.level]}>{l.text}</span>
            </div>
          ))}
        </div>
      </ScrollArea>
    </Card>
  );
}

/* ---------------- 页面 ---------------- */

function PumpChip({
  label,
  checked,
  disabled,
  onChange,
}: {
  label: string;
  checked: boolean;
  disabled: boolean;
  onChange: (v: boolean) => void;
}) {
  return (
    <button
      type="button"
      disabled={disabled}
      onClick={() => onChange(!checked)}
      className={cn(
        "h-7 rounded-sm border px-2 text-[11px] outline-none transition-colors focus-visible:ring-2 focus-visible:ring-ring disabled:opacity-50",
        checked ? "border-foreground bg-foreground text-background" : "text-muted-foreground hover:bg-muted"
      )}
    >
      {label}
    </button>
  );
}

function TubingBar() {
  const t = useT();
  const connected = useStore((s) => s.connected);
  const workflow = useStore((s) => s.workflow);
  const tubingOp = useStore((s) => s.tubingOp);
  const p1 = useStore((s) => s.tubingP1);
  const p2 = useStore((s) => s.tubingP2);
  const setTubingPumps = useStore((s) => s.setTubingPumps);
  const titrating = ["injecting", "titrating", "degree1", "titrating2"].includes(workflow);
  const busy = titrating || Boolean(tubingOp);
  const canPrime = connected && !busy;
  const canEmpty = connected && !titrating && !tubingOp && (workflow === "done" || workflow === "idle");

  return (
    <div className="flex h-10 shrink-0 flex-wrap items-center gap-2 overflow-x-auto rounded-sm border bg-card px-3">
      <span className="flex items-center gap-1.5 text-[12px] font-medium whitespace-nowrap">
        <Droplets size={13} /> {t("tubing.prime")} / {t("tubing.empty")}
      </span>
      <PumpChip label={t("tubing.p1")} checked={p1} disabled={busy} onChange={(v) => setTubingPumps(v, p2)} />
      <PumpChip label={t("tubing.p2")} checked={p2} disabled={busy} onChange={(v) => setTubingPumps(p1, v)} />
      <Separator orientation="vertical" className="h-5" />
      {tubingOp ? (
        <>
          <span className="text-[11px] text-[var(--status-ok)]">{t("tubing.running")}</span>
          <Button size="sm" variant="outline" className="h-7 rounded-sm" onClick={() => backend.stopTubing()}>
            {t("tubing.stop")}
          </Button>
        </>
      ) : (
        <>
          <Button size="sm" variant="outline" className="h-7 rounded-sm" disabled={!canPrime} onClick={() => backend.startTubing("prime")}>
            {t("tubing.prime")}
          </Button>
          <Button size="sm" variant="outline" className="h-7 rounded-sm" disabled={!canEmpty} onClick={() => backend.startTubing("empty")}>
            {t("tubing.empty")}
          </Button>
        </>
      )}
    </div>
  );
}

export function TitrationPage() {
  const t = useT();
  const potPoints = useStore((s) => s.potPoints);
  const spectra = useStore((s) => s.spectra);
  const hasData = potPoints.length > 0 || spectra.length > 0;

  return (
    <div className="flex h-full flex-col gap-2.5 p-2.5">
      <Stepper />
      <TubingBar />

      <div className="flex min-h-0 flex-1 gap-3">
        {/* 左：图表列 */}
        <div className="flex min-w-0 flex-1 flex-col gap-3">
          <Card className="relative flex min-h-0 flex-[5] flex-col">
            <CardHeader className="flex-row items-center justify-between space-y-0 px-2.5 py-1 pb-0.5">
              <CardTitle className="text-[13px]">{t("chart.potentialTitle")}</CardTitle>
              <div className="flex items-center gap-3 text-[11px] text-muted-foreground">
                <span className="flex items-center gap-1.5"><span className="h-0.5 w-4 bg-[var(--curve-potential)]" />E(V)</span>
                <span className="flex items-center gap-1.5"><span className="h-px w-4 border-t border-dashed border-[var(--curve-derivative)]" />dE/dV</span>
              </div>
            </CardHeader>
            <CardContent className="relative min-h-0 flex-1 p-0">
              <PotentialChart />
              {!hasData && <EmptyHint />}
            </CardContent>
          </Card>

          <Card className="relative flex min-h-0 flex-[4] flex-col">
            <CardHeader className="px-2.5 py-1">
              <CardTitle className="text-[13px]">{t("chart.spectrumTitle")}</CardTitle>
            </CardHeader>
            <CardContent className="flex min-h-0 flex-1 gap-2 px-2 pb-2">
              <div className="relative min-h-0 min-w-0 flex-[3] overflow-hidden rounded-sm bg-transparent">
                <LatestSpectrum />
                {!hasData && <EmptyHint />}
              </div>
              <div className="relative min-h-0 w-36 shrink-0 overflow-hidden rounded-sm bg-transparent">
                <SpectrumHeatmap />
              </div>
            </CardContent>
          </Card>
        </div>

        {/* 右：结果 + 日志 */}
        <div className="flex w-80 shrink-0 flex-col gap-3">
          <ResultsPanel />
          <EventLog />
        </div>
      </div>
    </div>
  );
}

function EmptyHint() {
  const t = useT();
  return (
    <div className="pointer-events-none absolute inset-0 grid place-items-center">
      <div className="text-center">
        <div className="text-[12px] text-muted-foreground">{t("chart.empty")}</div>
        <div className="mt-1 text-[11px] text-muted-foreground/70">{t("chart.emptyHint")}</div>
      </div>
    </div>
  );
}
