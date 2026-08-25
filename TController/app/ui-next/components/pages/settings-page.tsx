"use client";

/**
 * 设置页：外观/语言顶栏、检测参数工作台、关于底条。
 */
import { useState } from "react";
import { useTheme } from "next-themes";
import { Monitor, Moon, Palette, Pencil, SlidersHorizontal, Sun, Info } from "lucide-react";
import { Card, CardContent, CardTitle } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { useStore } from "@/lib/store";
import type { DetectionParams } from "@/lib/store";
import { useT } from "@/lib/i18n";
import { cn } from "@/lib/utils";

const THEMES = [
  { id: "light", icon: Sun, key: "settings.theme.light" },
  { id: "dark", icon: Moon, key: "settings.theme.dark" },
  { id: "system", icon: Monitor, key: "settings.theme.system" },
] as const;

function Segment<T extends string>({
  value,
  options,
  onChange,
}: {
  value: T;
  options: { id: T; label: string; icon?: typeof Sun }[];
  onChange: (id: T) => void;
}) {
  return (
    <div className="flex overflow-hidden rounded-sm border">
      {options.map(({ id, label, icon: Icon }) => (
        <button
          key={id}
          onClick={() => onChange(id)}
          className={cn(
            "flex h-7 items-center gap-1.5 px-2.5 text-[12px] outline-none transition-colors focus-visible:ring-2 focus-visible:ring-ring",
            value === id ? "bg-foreground text-background" : "text-muted-foreground hover:bg-muted hover:text-foreground"
          )}
        >
          {Icon && <Icon size={12} />}
          {label}
        </button>
      ))}
    </div>
  );
}

function AppearanceBar() {
  const t = useT();
  const { theme, setTheme } = useTheme();
  const lang = useStore((s) => s.lang);
  const setLang = useStore((s) => s.setLang);

  return (
    <div className="flex h-10 shrink-0 flex-wrap items-center gap-3 overflow-x-auto rounded-md border bg-card px-3">
      <span className="flex items-center gap-1.5 text-[13px] font-medium whitespace-nowrap">
        <Palette size={14} /> {t("settings.appearance")}
      </span>
      <span className="text-[10px] tracking-wide text-muted-foreground uppercase">{t("settings.theme")}</span>
      <Segment
        value={(theme ?? "dark") as "light" | "dark" | "system"}
        onChange={setTheme}
        options={THEMES.map(({ id, icon, key }) => ({ id, icon, label: t(key) }))}
      />
      <span className="text-[10px] tracking-wide text-muted-foreground uppercase">{t("settings.lang")}</span>
      <Segment
        value={lang}
        onChange={setLang}
        options={[
          { id: "zh", label: "简体中文" },
          { id: "en", label: "English" },
        ]}
      />
    </div>
  );
}

function formatParam(n: number, digits: number) {
  return n.toFixed(digits);
}

function ParamRow({
  label,
  unit,
  value,
  digits,
  editing,
  draft,
  min,
  step,
  onDraft,
}: {
  label: string;
  unit: string;
  value: number;
  digits: number;
  editing: boolean;
  draft: string;
  min: number;
  step: number;
  onDraft: (raw: string) => void;
}) {
  return (
    <div className="grid min-h-0 flex-1 grid-cols-[minmax(0,1fr)_10rem] items-center gap-6 border-b px-4 last:border-b-0">
      <span className="text-[13px] text-muted-foreground">{label}</span>
      {editing ? (
        <span className="flex h-8 items-stretch overflow-hidden rounded-sm border bg-background ring-1 ring-foreground/20">
          <Input
            type="number"
            min={min}
            step={step}
            inputMode="decimal"
            value={draft}
            onChange={(e) => onDraft(e.target.value)}
            className="h-full w-full rounded-none border-0 bg-transparent px-2 py-0 text-right font-mono text-[12px] leading-8 shadow-none md:text-[12px] md:leading-8 dark:bg-transparent [appearance:textfield] [&::-webkit-inner-spin-button]:appearance-none [&::-webkit-outer-spin-button]:appearance-none"
          />
          <span className="flex items-center bg-muted/60 px-2 font-mono text-[11px] text-muted-foreground whitespace-nowrap">
            {unit}
          </span>
        </span>
      ) : (
        <span className="readout text-right text-[12px] font-medium">
          {formatParam(value, digits)} <span className="font-normal text-muted-foreground">{unit}</span>
        </span>
      )}
    </div>
  );
}

function DetectionCard() {
  const t = useT();
  const detection = useStore((s) => s.detection);
  const setDetection = useStore((s) => s.setDetection);
  const running = useStore((s) => ["injecting", "titrating", "degree1", "titrating2"].includes(s.workflow));
  const [editing, setEditing] = useState(false);
  const [draft, setDraft] = useState<Record<keyof DetectionParams, string>>({
    t1DerivThreshold: formatParam(detection.t1DerivThreshold, 2),
    dose: formatParam(detection.dose, 3),
    overTitrate: formatParam(detection.overTitrate, 2),
    consensusTol: formatParam(detection.consensusTol, 2),
  });

  const beginEdit = () => {
    setDraft({
      t1DerivThreshold: formatParam(detection.t1DerivThreshold, 2),
      dose: formatParam(detection.dose, 3),
      overTitrate: formatParam(detection.overTitrate, 2),
      consensusTol: formatParam(detection.consensusTol, 2),
    });
    setEditing(true);
  };

  const cancel = () => setEditing(false);

  const apply = () => {
    const t1 = Number(draft.t1DerivThreshold);
    const dose = Number(draft.dose);
    const over = Number(draft.overTitrate);
    const tol = Number(draft.consensusTol);
    if (![t1, dose, over, tol].every(Number.isFinite)) return;
    if (t1 < 0.01 || dose < 0.001 || over < 0 || tol < 0) return;
    setDetection({ t1DerivThreshold: t1, dose, overTitrate: over, consensusTol: tol });
    setEditing(false);
  };

  return (
    <Card className="flex min-h-0 flex-1 flex-col">
      <div className="flex h-10 shrink-0 items-center justify-between gap-3 border-b px-4">
        <CardTitle className="flex items-center gap-2 text-[13px]">
          <SlidersHorizontal size={15} /> {t("settings.detection")}
        </CardTitle>
        {editing ? (
          <div className="flex items-center gap-1">
            <Button size="sm" variant="ghost" className="h-7 rounded-sm" onClick={cancel}>
              {t("settings.cancel")}
            </Button>
            <Button size="sm" className="h-7 rounded-sm" onClick={apply}>
              {t("settings.apply")}
            </Button>
          </div>
        ) : (
          <Button size="sm" variant="outline" className="h-7 gap-1 rounded-sm" disabled={running} onClick={beginEdit}>
            <Pencil size={12} /> {t("settings.edit")}
          </Button>
        )}
      </div>
      <CardContent className="min-h-0 flex-1 px-4 pb-3">
        <div className={cn("flex h-full flex-col overflow-hidden rounded-sm border", editing && "ring-1 ring-foreground/15")}>
          <ParamRow
            label={t("settings.t1")}
            unit="V/mL"
            value={detection.t1DerivThreshold}
            digits={2}
            editing={editing}
            draft={draft.t1DerivThreshold}
            min={0.01}
            step={0.01}
            onDraft={(raw) => setDraft((d) => ({ ...d, t1DerivThreshold: raw }))}
          />
          <ParamRow
            label={t("settings.dose")}
            unit="mL"
            value={detection.dose}
            digits={3}
            editing={editing}
            draft={draft.dose}
            min={0.001}
            step={0.001}
            onDraft={(raw) => setDraft((d) => ({ ...d, dose: raw }))}
          />
          <ParamRow
            label={t("settings.over")}
            unit="mL"
            value={detection.overTitrate}
            digits={2}
            editing={editing}
            draft={draft.overTitrate}
            min={0}
            step={0.01}
            onDraft={(raw) => setDraft((d) => ({ ...d, overTitrate: raw }))}
          />
          <div className="grid min-h-0 flex-1 grid-cols-[minmax(0,1fr)_10rem] items-center gap-6 border-b px-4">
            <span className="text-[13px] text-muted-foreground">{t("settings.window")}</span>
            <span className="readout text-right text-[12px]">380 – 1100 nm · 61 ch</span>
          </div>
          <ParamRow
            label={t("settings.tol")}
            unit="mL"
            value={detection.consensusTol}
            digits={2}
            editing={editing}
            draft={draft.consensusTol}
            min={0}
            step={0.01}
            onDraft={(raw) => setDraft((d) => ({ ...d, consensusTol: raw }))}
          />
        </div>
      </CardContent>
    </Card>
  );
}

function AboutBar() {
  const t = useT();
  const facts = [
    [t("settings.version"), "0.2.0"],
    [t("settings.core"), "controller-core 0.1.0 · Rust"],
    [t("settings.license"), "PolyForm Shield 1.0.0"],
  ];
  return (
    <div className="flex shrink-0 flex-wrap items-center gap-x-5 gap-y-2 rounded-md border bg-card px-3 py-2 text-[12px]">
      <span className="flex items-center gap-1.5 font-medium whitespace-nowrap">
        <Info size={14} /> {t("settings.about")}
      </span>
      {facts.map(([k, v]) => (
        <span key={k} className="flex items-baseline gap-1.5 whitespace-nowrap">
          <span className="text-[10px] tracking-wide text-muted-foreground uppercase">{k}</span>
          <span className="readout">{v}</span>
        </span>
      ))}
    </div>
  );
}

export function SettingsPage() {
  return (
    <div className="flex h-full min-h-0 flex-col gap-2.5 p-2.5">
      <AppearanceBar />
      <DetectionCard />
      <AboutBar />
    </div>
  );
}
