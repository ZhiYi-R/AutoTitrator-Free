"use client";

/**
 * 维护页：两台泵并排工作台（连续运转 / 定步排出）+ 看门狗 / 设备状态条。
 * 运行中禁止手动操作泵，避免与滴定流程冲突。
 */
import { useMemo, useState } from "react";
import { Cpu, Droplets, Play, Square, ShieldCheck, Timer } from "lucide-react";
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { Badge } from "@/components/ui/badge";
import { Separator } from "@/components/ui/separator";
import { ScrollArea } from "@/components/ui/scroll-area";
import { useStore } from "@/lib/store";
import { useT } from "@/lib/i18n";
import { backend } from "@/lib/backend";
import { cn } from "@/lib/utils";

const RUNNING = ["injecting", "titrating", "degree1", "titrating2"];
const pumpBusy = (workflow: string, tubingOp: string | null) => Boolean(tubingOp) || RUNNING.includes(workflow);

function PumpControl({ pump }: { pump: 1 | 2 }) {
  const t = useT();
  const running = useStore((s) => (pump === 1 ? s.pump1Running : s.pump2Running));
  const steps = useStore((s) => (pump === 1 ? s.pump1Steps : s.pump2Steps));
  const slope = useStore((s) => s.pumpSlope);
  const logs = useStore((s) => s.logs);
  const busy = useStore((s) => pumpBusy(s.workflow, s.tubingOp));
  const connected = useStore((s) => s.connected);
  const [jogSteps, setJogSteps] = useState(pump === 1 ? 400 : 200);
  const volume = slope > 0 ? steps / slope : 0;
  const pumpLogs = useMemo(
    () => [...logs].reverse().filter((l) => l.text.includes(`泵${pump}`) || l.text.toLowerCase().includes(`pump ${pump}`)).slice(0, 40),
    [logs, pump],
  );

  return (
    <Card className="flex min-h-0 min-w-0 flex-1 flex-col">
      <CardHeader className="flex-row items-center justify-between space-y-0 px-4 py-2.5">
        <CardTitle className="flex items-center gap-2 text-[13px]">
          <Droplets size={15} /> {pump === 1 ? t("maint.pump1") : t("maint.pump2")}
        </CardTitle>
        <Badge variant="outline" className={cn("font-mono text-[10px]", running ? "border-transparent bg-[var(--status-ok)]/15 text-[var(--status-ok)]" : "text-muted-foreground")}>
          {running ? t("maint.running") : t("maint.stopped")}
        </Badge>
      </CardHeader>
      <CardContent className="flex min-h-0 flex-1 flex-col gap-3 px-4 pb-3">
        <div className="flex flex-wrap items-center gap-2">
          <Button size="sm" variant={running ? "outline" : "default"} className="h-8 gap-1.5 rounded-sm" disabled={!connected || busy}
            onClick={() => (running ? backend.freeStop(pump) : backend.freeRun(pump))}>
            {running ? <Square size={12} /> : <Play size={13} />}
            {running ? t("maint.stop") : t("maint.run")}
          </Button>
          <Separator orientation="vertical" className="h-5" />
          <Input type="number" min={1} max={20000} value={jogSteps} disabled={!connected || busy}
            onChange={(e) => setJogSteps(Number(e.target.value) || 0)}
            aria-label={t("maint.jogSteps")}
            className="h-8 w-24 text-right font-mono" />
          <span className="text-[11px] text-muted-foreground">{t("cal.stepsUnit")}</span>
          <Button size="sm" variant="outline" className="h-8 rounded-sm" disabled={!connected || busy || running}
            onClick={() => backend.jog(pump, jogSteps)}>
            {t("maint.jog")}
          </Button>
        </div>

        <div className="grid grid-cols-3 gap-2">
          <ReadoutTile label={t("maint.steps")} value={steps.toLocaleString()} />
          <ReadoutTile label={t("maint.dispensed")} value={volume.toFixed(3)} unit="mL" />
          <ReadoutTile label={t("maint.slope")} value={slope.toLocaleString()} unit={t("cal.slopeUnit")} />
        </div>

        <div className="flex min-h-0 flex-1 flex-col overflow-hidden rounded-sm border bg-[var(--chart-well)]">
          <div className="shrink-0 border-b px-3 py-1.5 text-[11px] text-muted-foreground">{t("maint.actions")}</div>
          <ScrollArea className="min-h-0 flex-1">
            <div className="space-y-0.5 px-3 py-2 font-mono text-[11px] leading-relaxed">
              {pumpLogs.length === 0 && <p className="text-muted-foreground">{t("maint.noActions")}</p>}
              {pumpLogs.map((l, i) => (
                <div key={`${l.t}-${i}`} className="flex gap-2">
                  <span className="shrink-0 text-muted-foreground/60">
                    {new Date(l.t).toLocaleTimeString("zh-CN", { hour12: false })}
                  </span>
                  <span>{l.text}</span>
                </div>
              ))}
            </div>
          </ScrollArea>
        </div>
      </CardContent>
    </Card>
  );
}

function ReadoutTile({ label, value, unit }: { label: string; value: string; unit?: string }) {
  return (
    <div className="rounded-sm border bg-[var(--chart-well)] px-3 py-2">
      <div className="text-[10px] tracking-wide text-muted-foreground uppercase">{label}</div>
      <div className="readout mt-0.5 text-lg font-semibold leading-none">
        {value}
        {unit && <span className="ml-1 text-[11px] font-normal text-muted-foreground">{unit}</span>}
      </div>
    </div>
  );
}

function WatchdogCard() {
  const t = useT();
  const enabled = useStore((s) => s.watchdogEnabled);
  const setWatchdog = useStore((s) => s.setWatchdog);
  return (
    <div className="flex shrink-0 items-center gap-3 rounded-md border bg-card px-3 py-2">
      <ShieldCheck size={15} className="shrink-0 text-muted-foreground" />
      <div className="min-w-0 text-[13px] font-medium">{t("maint.watchdog")}</div>
      <div className="flex-1" />
      <div className={cn("font-mono text-[11px]", enabled ? "text-[var(--status-ok)]" : "text-muted-foreground")}>
        {enabled ? t("maint.watchdogEnabled") : t("maint.watchdogDisabled")}
      </div>
      <button
        type="button"
        aria-pressed={enabled}
        aria-label={enabled ? t("maint.watchdogEnabled") : t("maint.watchdogDisabled")}
        title={enabled ? t("maint.watchdogEnabled") : t("maint.watchdogDisabled")}
        onClick={() => setWatchdog(!enabled)}
        className={cn(
          "h-5 w-5 shrink-0 rounded-full border outline-none transition-colors focus-visible:ring-2 focus-visible:ring-ring",
          enabled
            ? "border-[var(--status-ok)] bg-[var(--status-ok)]"
            : "border-input bg-input hover:border-muted-foreground"
        )}
      />
    </div>
  );
}

function DeviceInfo() {
  const t = useT();
  const { rx, tx, badFrames, heartbeatTick, connected } = useStore();
  /* heartbeatTick 为固件 uptime 秒计数（真实后端由 ms 归一，mock 每秒 +1） */
  const uptime = heartbeatTick;
  const facts = [
    [t("maint.firmware"), "v1.4.2"],
    [t("maint.mcu"), "STM32F103C8T6 · Cortex-M3 @ 72 MHz"],
    [t("maint.uptime"), connected ? `${Math.floor(uptime / 60)}:${String(uptime % 60).padStart(2, "0")}` : "—"],
    [t("statusbar.rx"), String(rx)],
    [t("statusbar.tx"), String(tx)],
    [t("maint.errFrames"), String(badFrames)],
  ];
  return (
    <div className="flex shrink-0 flex-wrap items-center gap-x-5 gap-y-2 rounded-md border bg-card px-3 py-2 text-[12px]">
      <span className="flex items-center gap-1.5 font-medium whitespace-nowrap">
        <Cpu size={14} /> {t("maint.deviceTitle")}
      </span>
      {facts.map(([k, v]) => (
        <span key={k} className="flex items-baseline gap-1.5 whitespace-nowrap">
          <span className="text-[10px] tracking-wide text-muted-foreground uppercase">{k}</span>
          <span className="readout">{v}</span>
        </span>
      ))}
      <span className="ml-auto flex items-center gap-1.5 text-muted-foreground whitespace-nowrap">
        <Timer size={12} /> {t("maint.serialStats")}
      </span>
    </div>
  );
}

export function MaintenancePage() {
  return (
    <div className="flex h-full min-h-0 flex-col gap-2.5 p-2.5">
      <div className="grid min-h-0 flex-1 grid-cols-2 items-stretch gap-2.5">
        <PumpControl pump={1} />
        <PumpControl pump={2} />
      </div>
      <WatchdogCard />
      <DeviceInfo />
    </div>
  );
}
