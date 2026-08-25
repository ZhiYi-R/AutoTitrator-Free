"use client";

/**
 * 应用外壳：顶栏工具区 + 左侧导航 + 底部状态条。
 * 仪器布局原则：运行控制始终可见（顶栏），状态始终可见（底栏）。
 */
import { useEffect } from "react";
import { useTheme } from "next-themes";
import {
  Activity,
  FlaskConical,
  Gauge,
  History,
  Maximize2,
  Minus,
  Moon,
  OctagonX,
  Play,
  RotateCcw,
  Settings,
  Square,
  Sun,
  Monitor,
  PanelLeftClose,
  PanelLeftOpen,
  Wrench,
  X,
  Zap,
} from "lucide-react";
import { Button } from "@/components/ui/button";
import { Separator } from "@/components/ui/separator";
import { Input } from "@/components/ui/input";
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from "@/components/ui/select";
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuTrigger,
} from "@/components/ui/dropdown-menu";
import { useStore } from "@/lib/store";
import type { PageId } from "@/lib/store";
import { useT } from "@/lib/i18n";
import { backend } from "@/lib/backend";
import { cn } from "@/lib/utils";
import { TitrationPage } from "@/components/pages/titration-page";
import { CalibrationPage } from "@/components/pages/calibration-page";
import { MaintenancePage } from "@/components/pages/maintenance-page";
import { HistoryPage } from "@/components/pages/history-page";
import { SettingsPage } from "@/components/pages/settings-page";

const NAV: { id: PageId; icon: typeof Gauge; key: "nav.titration" | "nav.calibration" | "nav.maintenance" | "nav.history" | "nav.settings" }[] = [
  { id: "titration", icon: FlaskConical, key: "nav.titration" },
  { id: "calibration", icon: Gauge, key: "nav.calibration" },
  { id: "maintenance", icon: Wrench, key: "nav.maintenance" },
  { id: "history", icon: History, key: "nav.history" },
  { id: "settings", icon: Settings, key: "nav.settings" },
];

function Led({ on, color = "ok" }: { on: boolean; color?: "ok" | "warn" | "danger" }) {
  const map = {
    ok: "bg-[var(--status-ok)] shadow-[0_0_6px_var(--status-ok)]",
    warn: "bg-[var(--status-warn)] shadow-[0_0_6px_var(--status-warn)]",
    danger: "bg-[var(--status-danger)] shadow-[0_0_6px_var(--status-danger)]",
  };
  return (
    <span
      className={cn(
        "inline-block h-2 w-2 rounded-full transition-colors",
        on ? map[color] : "bg-[var(--led-off,var(--input))]"
      )}
    />
  );
}

function tauriWindow() {
  const api = (globalThis as { __TAURI__?: { window?: { getCurrentWindow?: () => {
    minimize: () => Promise<void>;
    toggleMaximize: () => Promise<void>;
    close: () => Promise<void>;
  } } } }).__TAURI__;
  return api?.window?.getCurrentWindow?.() ?? null;
}

function WindowButtons() {
  const t = useT();
  return (
    <div data-no-drag className="flex h-full shrink-0">
      <button
        type="button"
        title={t("win.minimize")}
        className="grid h-8 w-11 place-items-center text-muted-foreground outline-none hover:bg-muted hover:text-foreground focus-visible:ring-2 focus-visible:ring-ring"
        onClick={() => void tauriWindow()?.minimize()}
      >
        <Minus size={13} />
      </button>
      <button
        type="button"
        title={t("win.maximize")}
        className="grid h-8 w-11 place-items-center text-muted-foreground outline-none hover:bg-muted hover:text-foreground focus-visible:ring-2 focus-visible:ring-ring"
        onClick={() => void tauriWindow()?.toggleMaximize()}
      >
        <Maximize2 size={12} />
      </button>
      <button
        type="button"
        title={t("win.close")}
        className="grid h-8 w-11 place-items-center text-muted-foreground outline-none hover:bg-[var(--status-danger)] hover:text-white focus-visible:ring-2 focus-visible:ring-ring"
        onClick={() => void tauriWindow()?.close()}
      >
        <X size={14} />
      </button>
    </div>
  );
}

function TitleBar() {
  const t = useT();
  const { setTheme } = useTheme();
  return (
    <div data-tauri-drag-region className="flex h-8 shrink-0 items-center border-b bg-card">
      <div className="flex min-w-0 items-center gap-2 px-2.5">
        <div className="grid h-5 w-5 shrink-0 place-items-center rounded-[3px] bg-primary text-primary-foreground">
          <FlaskConical size={12} />
        </div>
        <span className="text-[12px] font-semibold tracking-wide whitespace-nowrap">{t("app.name")}</span>
      </div>
      <div className="min-h-8 min-w-8 flex-1" />
      <div data-no-drag className="flex items-center">
        <LangSwitch />
        <DropdownMenu>
          <DropdownMenuTrigger asChild>
            <Button size="icon" variant="ghost" className="h-8 w-8 rounded-none"><Sun size={13} className="dark:hidden" /><Moon size={13} className="hidden dark:block" /></Button>
          </DropdownMenuTrigger>
          <DropdownMenuContent align="end">
            <DropdownMenuItem onClick={() => setTheme("light")}> <Sun size={14} /> {t("settings.theme.light")}</DropdownMenuItem>
            <DropdownMenuItem onClick={() => setTheme("dark")}> <Moon size={14} /> {t("settings.theme.dark")}</DropdownMenuItem>
            <DropdownMenuItem onClick={() => setTheme("system")}> <Monitor size={14} /> {t("settings.theme.system")}</DropdownMenuItem>
          </DropdownMenuContent>
        </DropdownMenu>
        <WindowButtons />
      </div>
    </div>
  );
}

function ToolBar() {
  const t = useT();
  const {
    connected, connecting, port, baud, ports,
    setPort, setBaud,
    workflow,
    tubingOp,
    sampleInput,
    setSampleInput,
    analysis,
    setAnalysis,
  } = useStore();

  const running = ["injecting", "titrating", "degree1", "titrating2"].includes(workflow);
  const canStart = connected && !running && !tubingOp;
  /* 簇底透明：嵌在卡片色工具条上时不再形成深色内陷块，只靠发丝边框分组 */
  const cluster = "flex h-7 items-stretch overflow-hidden rounded-sm border";
  const cell =
    "h-full rounded-none border-0 py-0 shadow-none font-mono text-[12px] leading-[26px] focus-visible:z-10 focus-visible:ring-2 [&_[data-slot=select-value]]:h-full [&_[data-slot=select-value]]:leading-[26px]";

  return (
    <div className="flex h-9 shrink-0 items-center gap-2 border-b bg-card px-2">
      <div className={cluster} role="group" aria-label={t("toolbar.connection")}>
        <Select value={port} onValueChange={setPort} disabled={connected}>
          <SelectTrigger size="sm" className={cn(cell, "h-full w-[132px] px-2 data-[size=sm]:h-full [&_svg]:size-3")}>
            <SelectValue placeholder={ports.length ? t("toolbar.selectPort") : t("toolbar.noPorts")} />
          </SelectTrigger>
          <SelectContent className="min-w-[280px]">
            {ports.length === 0 ? (
              <SelectItem value="__no_ports__" disabled>{t("toolbar.noPorts")}</SelectItem>
            ) : ports.map((item) => (
              <SelectItem key={item.portName} value={item.portName}>
                <span className="flex min-w-0 items-center gap-2">
                  <span className="font-mono">{item.portName}</span>
                  {item.description && <span className="truncate text-muted-foreground">{item.description}</span>}
                </span>
              </SelectItem>
            ))}
          </SelectContent>
        </Select>
        <Separator orientation="vertical" />
        <Select value={String(baud)} onValueChange={(v) => setBaud(Number(v))} disabled={connected}>
          <SelectTrigger size="sm" className={cn(cell, "h-full w-[78px] px-2 data-[size=sm]:h-full [&_svg]:size-3")}>
            <SelectValue />
          </SelectTrigger>
          <SelectContent>
            {[9600, 115200, 921600].map((b) => <SelectItem key={b} value={String(b)}>{b}</SelectItem>)}
          </SelectContent>
        </Select>
        <Separator orientation="vertical" />
        <Button
          size="sm"
          variant={connected ? "ghost" : "default"}
          className={cn(cell, "gap-1.5 px-2.5")}
          disabled={connecting}
          onClick={() => (connected ? backend.disconnect() : backend.connect())}
        >
          {connecting ? "…" : connected ? t("toolbar.disconnect") : t("toolbar.connect")}
        </Button>
        <Separator orientation="vertical" />
        <span className="flex h-full items-center gap-1.5 px-2 font-mono text-[12px] leading-[26px] text-muted-foreground" title={connected ? "FW v1.4.2 · F103" : undefined}>
          <Led on={connected} />
          <span className="leading-[26px]">{connecting ? t("toolbar.connecting") : connected ? t("toolbar.connected") : t("toolbar.disconnected")}</span>
        </span>
      </div>

      <label className={cluster}>
        <span className="flex h-full items-center bg-muted/60 px-2 font-mono text-[12px] leading-[26px] text-muted-foreground whitespace-nowrap">
          {t("toolbar.sample")}
        </span>
        <Input
          type="number"
          min={1}
          max={50}
          step={0.5}
          value={sampleInput}
          disabled={running}
          onChange={(e) => setSampleInput(Number(e.target.value) || 0)}
          className={cn(
            cell,
            "box-border h-full w-[52px] px-1.5 py-0 font-mono text-[12px] leading-[26px] md:text-[12px] md:leading-[26px]",
            "[appearance:textfield] [&::-webkit-inner-spin-button]:m-0 [&::-webkit-inner-spin-button]:appearance-none [&::-webkit-outer-spin-button]:m-0 [&::-webkit-outer-spin-button]:appearance-none",
            "text-right focus-visible:ring-0"
          )}
          aria-label={t("toolbar.sample")}
        />
        <span className="flex h-full items-center px-2 font-mono text-[12px] leading-[26px] text-muted-foreground">mL</span>
      </label>

      <div className={cluster} role="group" aria-label={t("toolbar.titrantConc")}>
        <span className="flex h-full items-center bg-muted/60 px-2 font-mono text-[12px] leading-[26px] text-muted-foreground whitespace-nowrap">
          {t("toolbar.titrantConc")}
        </span>
        <Input
          type="number"
          min={0}
          step={0.001}
          value={analysis.titrantConc}
          disabled={running}
          onChange={(e) => setAnalysis({ titrantConc: Number(e.target.value) || 0 })}
          className={cn(
            cell,
            "box-border h-full w-[68px] px-1.5 py-0 font-mono text-[12px] leading-[26px] md:text-[12px] md:leading-[26px]",
            "[appearance:textfield] [&::-webkit-inner-spin-button]:m-0 [&::-webkit-inner-spin-button]:appearance-none [&::-webkit-outer-spin-button]:m-0 [&::-webkit-outer-spin-button]:appearance-none",
            "text-right focus-visible:ring-0"
          )}
          aria-label={t("toolbar.titrantConc")}
        />
        <span className="flex h-full items-center px-1.5 font-mono text-[11px] leading-[26px] text-muted-foreground">mol/L</span>
        <Separator orientation="vertical" />
        <span className="flex h-full items-center px-2 font-mono text-[12px] leading-[26px] text-muted-foreground whitespace-nowrap">
          {t("toolbar.stoich")}
        </span>
        {(["analyteCoeff", "titrantCoeff"] as const).map((field, i) => (
          <span key={field} className="flex h-full items-center">
            {i === 1 && <span className="px-0.5 font-mono text-[12px] text-muted-foreground">∶</span>}
            <Input
              type="number"
              min={1}
              step={1}
              value={analysis[field]}
              disabled={running}
              onChange={(e) => setAnalysis({ [field]: Math.max(0, Math.round(Number(e.target.value) || 0)) })}
              className={cn(
                cell,
                "box-border h-full w-[36px] px-1 py-0 font-mono text-[12px] leading-[26px] md:text-[12px] md:leading-[26px]",
                "[appearance:textfield] [&::-webkit-inner-spin-button]:m-0 [&::-webkit-inner-spin-button]:appearance-none [&::-webkit-outer-spin-button]:m-0 [&::-webkit-outer-spin-button]:appearance-none",
                "text-center focus-visible:ring-0"
              )}
              aria-label={`${t("toolbar.stoich")} ${i === 0 ? "a" : "b"}`}
            />
          </span>
        ))}
      </div>

      <div className={cluster} role="group" aria-label={t("toolbar.start")}>
        <Button
          size="sm"
          className={cn(cell, "gap-1 px-2.5 bg-primary text-[12px] text-primary-foreground hover:bg-primary/80")}
          disabled={!canStart}
          onClick={() => backend.start()}
        >
          <Play size={12} /> {t("toolbar.start")}
        </Button>
        <Separator orientation="vertical" />
        <Button
          size="sm"
          variant="ghost"
          className={cn(cell, "gap-1 px-2.5 text-[12px]")}
          disabled={!running && !tubingOp}
          onClick={() => tubingOp ? backend.stopTubing() : backend.manualStop()}
        >
          <Square size={11} /> {t("toolbar.stop")}
        </Button>
        <Separator orientation="vertical" />
        <Button
          size="sm"
          variant="ghost"
          className={cn(cell, "gap-1 px-2.5 text-[12px] text-[var(--status-warn)]")}
          disabled={!running && !tubingOp}
          onClick={() => backend.abort()}
        >
          <OctagonX size={12} /> {t("toolbar.abort")}
        </Button>
      </div>

      <Button
        size="sm"
        variant="outline"
        className="h-7 gap-1 rounded-sm border-[var(--status-warn)]/60 px-2.5 text-[var(--status-warn)] hover:bg-[var(--status-warn)]/10 hover:text-[var(--status-warn)]"
        title={t("toolbar.reset")}
        disabled={running || Boolean(tubingOp)}
          onClick={() => backend.reset()}
      >
        <RotateCcw size={12} /> {t("toolbar.reset")}
      </Button>

      <div className="flex-1" />

      <Button
        size="sm"
        className="h-7 gap-1.5 rounded-sm bg-[var(--status-danger)] font-semibold tracking-wider text-white hover:bg-[var(--status-danger)]/90"
        onClick={() => backend.abort()}
      >
        <Zap size={13} /> {t("toolbar.estop")}
      </Button>
    </div>
  );
}

function LangSwitch() {
  const lang = useStore((s) => s.lang);
  const setLang = useStore((s) => s.setLang);
  return (
    <Button size="sm" variant="ghost" className="h-8 w-8 rounded-none px-0 font-mono text-[11px]" onClick={() => setLang(lang === "zh" ? "en" : "zh")}>
      {lang === "zh" ? "中" : "EN"}
    </Button>
  );
}

function SideNav() {
  const t = useT();
  const page = useStore((s) => s.page);
  const setPage = useStore((s) => s.setPage);
  const collapsed = useStore((s) => s.navCollapsed);
  const toggleNav = useStore((s) => s.toggleNav);
  return (
    <nav
      className={cn(
        "flex shrink-0 flex-col border-r bg-sidebar p-1.5 text-sidebar-foreground transition-[width] duration-150",
        collapsed ? "w-[48px]" : "w-44"
      )}
    >
      {NAV.map(({ id, icon: Icon, key }) => (
        <button
          key={id}
          onClick={() => setPage(id)}
          title={collapsed ? t(key) : undefined}
          className={cn(
            "mb-0.5 flex items-center gap-2.5 rounded-sm py-2 text-left text-[13px] outline-none transition-colors focus-visible:ring-2 focus-visible:ring-ring",
            collapsed ? "justify-center" : "px-2.5",
            page === id
              ? "bg-sidebar-accent font-medium text-sidebar-accent-foreground shadow-[inset_2px_0_0_var(--foreground)]"
              : "text-muted-foreground hover:bg-sidebar-accent/60 hover:text-foreground"
          )}
        >
          <Icon size={15} className="shrink-0" />
          {!collapsed && <span className="min-w-0 truncate">{t(key)}</span>}
        </button>
      ))}
      <div className="mt-auto">
        <button
          onClick={toggleNav}
          title={collapsed ? undefined : t("nav.collapse")}
          className="flex w-full items-center justify-center rounded-sm py-1.5 text-muted-foreground outline-none transition-colors hover:bg-sidebar-accent/60 hover:text-foreground focus-visible:ring-2 focus-visible:ring-ring"
        >
          {collapsed ? <PanelLeftOpen size={14} /> : <PanelLeftClose size={14} />}
        </button>
      </div>
    </nav>
  );
}

function Readout({ label, value, unit }: { label: string; value: string; unit?: string }) {
  return (
    <span className="flex items-baseline gap-1.5">
      <span className="text-[10px] tracking-wide uppercase">{label}</span>
      <b className="text-foreground tabular-nums">{value}</b>
      {unit && <span>{unit}</span>}
    </span>
  );
}

function StatusBar() {
  const t = useT();
  const { workflow, elapsedMs, volume, lastE, lastDeriv, spectra, rx, tx, heartbeatTick, connected, tubingOp } = useStore();
  const mm = Math.floor(elapsedMs / 60000);
  const ss = Math.floor((elapsedMs % 60000) / 1000);
  const tone =
    workflow === "error" ? "text-[var(--status-danger)]" :
    workflow === "done" ? "text-[var(--status-ok)]" :
    tubingOp ? "text-[var(--status-ok)]" :
    workflow === "idle" ? "text-muted-foreground" : "text-foreground";
  return (
    <footer className="flex h-8 shrink-0 items-center gap-3 border-t bg-card px-3 font-mono text-[11px] text-muted-foreground">
      <span className={cn("min-w-10 font-semibold tracking-wide", tone)}>{tubingOp ? t(`state.${tubingOp}`) : t(`state.${workflow}`)}</span>
      <span className="tabular-nums">{String(mm).padStart(2, "0")}:{String(ss).padStart(2, "0")}</span>
      <Separator orientation="vertical" className="h-3.5" />
      <Readout label={t("statusbar.volume")} value={volume.toFixed(2)} unit="mL" />
      <Readout label={t("statusbar.potential")} value={lastE === null ? "—" : lastE.toFixed(3)} unit="V" />
      <Readout label={t("statusbar.derivative")} value={lastDeriv === null ? "—" : lastDeriv.toFixed(2)} />
      <Readout label={t("statusbar.frames")} value={String(spectra.length)} />
      <div className="flex-1" />
      <span>{t("statusbar.rx")} {rx}</span>
      <span>{t("statusbar.tx")} {tx}</span>
      <span className="flex items-center gap-1.5">
        <Activity size={11} className={heartbeatTick % 2 === 0 && connected ? "text-[var(--status-ok)]" : "text-muted-foreground"} />
        {t("statusbar.heartbeat")}
      </span>
    </footer>
  );
}

export function AppShell() {
  const page = useStore((s) => s.page);
  useEffect(() => {
    void backend.initialize();
  }, []);
  return (
    <div className="flex h-screen flex-col overflow-hidden">
      <TitleBar />
      <ToolBar />
      <div className="flex min-h-0 flex-1">
        <SideNav />
        <main className="min-w-0 flex-1 overflow-hidden bg-background">
          {page === "titration" && <TitrationPage />}
          {page === "calibration" && <CalibrationPage />}
          {page === "maintenance" && <MaintenancePage />}
          {page === "history" && <HistoryPage />}
          {page === "settings" && <SettingsPage />}
        </main>
      </div>
      <StatusBar />
    </div>
  );
}
