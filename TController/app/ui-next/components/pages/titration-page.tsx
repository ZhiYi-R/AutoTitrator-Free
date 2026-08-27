"use client";

/**
 * 滴定工作台：主视图。
 * 左列双图表（电位-体积 / 光谱热图+最新光谱），右列终点结果。
 */
import { Fragment } from "react";
import { Check, ChevronRight, CircleSlash, Droplets } from "lucide-react";
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Badge } from "@/components/ui/badge";
import { Button } from "@/components/ui/button";
import { Separator } from "@/components/ui/separator";
import { ScrollArea } from "@/components/ui/scroll-area";
import { useStore, confidenceTone, methodTone, reliabilityTone, analyteConcentration } from "@/lib/store";
import { useT } from "@/lib/i18n";
import { cn } from "@/lib/utils";
import { toneClass } from "@/lib/tone";
import { PotentialChart } from "@/components/charts/potential-chart";
import { LatestSpectrum, JsDivergenceChart } from "@/components/charts/spectrum-chart";
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

function ResultBlock({ title, r, running, large = false }: { title: string; r: EndpointResult | null; running: boolean; large?: boolean }) {
  const t = useT();
  return (
    <div className="space-y-1">
      <div className="flex items-baseline justify-between">
        <span className="text-[11px] uppercase tracking-wider text-muted-foreground">{title}</span>
        <span className={cn("readout font-semibold", large ? "text-lg" : "text-[13px]")}>
          {r ? (
            <>{r.volume.toFixed(3)} <span className="text-[11px] font-normal text-muted-foreground">mL</span></>
          ) : (
            <span className="font-normal text-muted-foreground/60">{running ? t("results.running") : "—"}</span>
          )}
        </span>
      </div>
      {r ? (
        <div className="flex flex-wrap gap-1">
          <Badge variant="outline" className={toneClass[methodTone(r.method)]}>{t(`method.${r.method}`)}</Badge>
          <Badge variant="outline" className={toneClass[confidenceTone(r.confidence)]}>{t("results.confidence")}: {t(`confidence.${r.confidence}`)}</Badge>
          <Badge variant="outline" className={toneClass[reliabilityTone(r.reliability)]}>{r.reliability}</Badge>
        </div>
      ) : (
        <Badge variant="outline" className="border-transparent bg-muted/40 font-normal text-muted-foreground/50">—</Badge>
      )}
    </div>
  );
}

/** 最终结果明细：五行常驻，数据未产生时 — 占位（保持骨架稳定） */
function FinalDetail({ r }: { r: EndpointResult | null }) {
  const t = useT();
  const rows: Array<[string, string]> = [
    [t("results.potVol"), r?.potentialVolume?.toFixed(3) ?? "—"],
    [t("results.specVol"), r?.spectralVolume?.toFixed(3) ?? "—"],
    [t("results.kf"), r?.kf ? `${r.kf.volume.toFixed(3)} ± ${r.kf.std.toFixed(3)}` : "—"],
    [t("results.kfNis"), r?.kf ? r.kf.nis.toFixed(2) : "—"],
    [t("results.refined"), r?.refined != null ? r.refined.toFixed(3) : "—"],
  ];
  return (
    <div className="grid grid-cols-2 gap-x-3 gap-y-0.5 text-[11px]">
      {rows.map(([k, v]) => (
        <Fragment key={k}>
          <span className="text-muted-foreground">{k}</span>
          <span className={cn("readout text-right", v === "—" && "text-muted-foreground/60")}>{v}</span>
        </Fragment>
      ))}
    </div>
  );
}

/* 最终浓度：c分析物 = c滴定剂 · V终点 · (a/b) ÷ V样品 */
function ConcBlock() {
  const t = useT();
  const final = useStore((s) => s.final);
  const analysis = useStore((s) => s.analysis);
  const sampleVolume = useStore((s) => s.sampleVolume);
  const c = final ? analyteConcentration(analysis, final.volume, sampleVolume) : null;
  /* 计算式放入悬浮提示，原位显示浓度继承的终点置信度 */
  const formula = final && c !== null
    ? `c = ${analysis.titrantConc} × ${final.volume.toFixed(3)} × (${analysis.analyteCoeff}/${analysis.titrantCoeff}) ÷ ${sampleVolume.toFixed(2)}`
    : undefined;
  return (
    <>
      <Separator />
      <div className="flex items-baseline justify-between" title={formula}>
        <span className="text-[11px] uppercase tracking-wider text-muted-foreground">{t("results.concentration")}</span>
        {final && c !== null ? (
          <span className="flex items-baseline gap-2">
            <Badge variant="outline" className={cn("text-[10px]", toneClass[confidenceTone(final.confidence)])}>
              {t("results.confidence")}: {t(`confidence.${final.confidence}`)}
            </Badge>
            <span className="readout text-lg font-semibold">
              {c < 0.01 ? `${Number((c * 1000).toPrecision(3))} mmol/L` : `${Number(c.toPrecision(4))} mol/L`}
            </span>
          </span>
        ) : (
          <span className="text-[11px] text-muted-foreground/60">{final ? t("results.concPending") : "—"}</span>
        )}
      </div>
    </>
  );
}

function ResultsPanel() {
  const t = useT();
  const t1 = useStore((s) => s.t1);
  const final = useStore((s) => s.final);
  const spectralState = useStore((s) => s.spectralState);
  const workflow = useStore((s) => s.workflow);
  const running = ["injecting", "titrating", "degree1", "titrating2"].includes(workflow);
  return (
    <Card className="flex shrink-0 flex-col gap-0 pb-2 pt-2">
      <CardHeader className="flex-row items-center justify-between space-y-0 px-3 py-1.5">
        <CardTitle className="text-[13px]">{t("results.title")}</CardTitle>
        <Badge variant="outline" className={cn("font-mono text-[10px]", toneClass[spectralState === "END_CONFIRMED" ? "ok" : spectralState === "IN_CHANGE" ? "warn" : "muted"])}>
          {t(`spectral.${spectralState}`)}
        </Badge>
      </CardHeader>
      {/* 固定渲染完成态骨架：数据未产生时 — / 进行中 占位，运行全程卡片高度不变 */}
      <CardContent className="flex flex-col gap-2 px-3 pb-2">
        <ResultBlock title={t("results.t1")} r={t1} running={running} />
        <Separator />
        <ResultBlock title={t("results.final")} r={final} running={running} large />
        <FinalDetail r={final} />
        <ConcBlock />
      </CardContent>
    </Card>
  );
}

/* ---------------- 事件日志 ---------------- */

const LOG_LEVEL_CLASS: Record<string, string> = {
  ok: "text-[var(--status-ok)]",
  warn: "text-[var(--status-warn)]",
  error: "text-[var(--status-danger)]",
};

function EventLogPanel() {
  const t = useT();
  const logs = useStore((s) => s.logs);
  return (
    <Card className="flex min-h-0 flex-1 flex-col gap-0 pb-2 pt-2">
      <CardHeader className="px-3 py-1.5">
        <CardTitle className="text-[13px]">{t("log.title")}</CardTitle>
      </CardHeader>
      <CardContent className="min-h-0 flex-1 px-2 pb-2">
        <ScrollArea className="h-full">
          {/* 最新在上：运行中无需自动滚屏 */}
          <div className="space-y-0.5 px-1 font-mono text-[11px] leading-relaxed">
            {logs.length === 0 && <p className="text-muted-foreground">{t("log.empty")}</p>}
            {[...logs].reverse().map((l, i) => (
              <div key={`${l.t}-${i}`} className="flex gap-2">
                <span className="shrink-0 text-muted-foreground/60">
                  {new Date(l.t).toLocaleTimeString("zh-CN", { hour12: false })}
                </span>
                <span className={cn("min-w-0", LOG_LEVEL_CLASS[l.level])}>{l.text}</span>
              </div>
            ))}
          </div>
        </ScrollArea>
      </CardContent>
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
  const liveTrace = useStore((s) => s.liveTrace);
  const connected = useStore((s) => s.connected);
  /* 已连接即视为"有内容"：待机阶段电位图呈现实时走条，不盖空态提示 */
  const hasData = potPoints.length > 0 || spectra.length > 0 || (connected && liveTrace.length > 0);

  return (
    <div className="flex h-full flex-col gap-2.5 p-2.5">
      <Stepper />
      <TubingBar />

      <div className="flex min-h-0 flex-1 gap-3">
        {/* 左：图表列 */}
        <div className="flex min-w-0 flex-1 flex-col gap-3">
          <Card className="relative flex min-h-0 flex-[5] flex-col gap-0 pb-2 pt-2">
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

          <Card className="relative flex min-h-0 flex-[4] flex-col gap-0 pb-2 pt-2">
            <CardHeader className="px-2.5 py-1">
              <CardTitle className="text-[13px]">{t("chart.spectrumTitle")}</CardTitle>
            </CardHeader>
            <CardContent className="flex min-h-0 flex-1 gap-2 px-2">
              <div className="flex min-h-0 min-w-0 flex-[2] flex-col">
                {/* 子图标题 + 图例跟随各自图表，不集中堆在卡片 header */}
                <div className="flex shrink-0 items-center gap-3 pb-1 text-[10px] text-muted-foreground">
                  <span className="font-medium">{t("chart.latest")}</span>
                  <span className="flex items-center gap-1.5"><span className="h-0.5 w-4 rounded-full bg-[var(--curve-spectrum)]" />{t("chart.current")}</span>
                  <span className="flex items-center gap-1.5"><span className="h-px w-4 border-t-2 border-dashed border-muted-foreground" />{t("chart.baseline")}</span>
                </div>
                <div className="relative min-h-0 min-w-0 flex-1 overflow-hidden rounded-sm bg-transparent">
                  <LatestSpectrum />
                  {!hasData && <EmptyHint />}
                </div>
              </div>
              <div className="flex min-h-0 min-w-0 flex-1 flex-col">
                <div className="shrink-0 pb-1 text-[10px] font-medium text-muted-foreground">{t("chart.jsTitle")}</div>
                <div className="relative min-h-0 min-w-0 flex-1 overflow-hidden rounded-sm bg-transparent">
                  <JsDivergenceChart />
                </div>
              </div>
            </CardContent>
          </Card>
        </div>

        {/* 右：终点结果 + 事件日志（日志曾经移至维护页，按信息密度需求回归主视图） */}
        <div className="flex w-80 shrink-0 flex-col gap-2.5">
          <ResultsPanel />
          <EventLogPanel />
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
