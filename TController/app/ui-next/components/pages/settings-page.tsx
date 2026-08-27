"use client";

/**
 * 设置页：系统（主题/语言/数据保存路径）、检测参数工作台、关于底条。
 */
import { useState } from "react";
import { useTheme } from "next-themes";
import { Check, FolderOpen, Info, Monitor, Moon, Pencil, SlidersHorizontal, Sun, X } from "lucide-react";
import { Card, CardContent, CardTitle } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { useStore } from "@/lib/store";
import type { DetectionParams } from "@/lib/store";
import { backend } from "@/lib/backend";
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

/** 参数行骨架：与检测参数卡同规格（label 左、控件右、发丝分隔线） */
function Row({ label, children }: { label: string; children: React.ReactNode }) {
  return (
    <div className="grid grid-cols-[minmax(0,1fr)_auto] items-center gap-6 border-b px-4 py-2.5 last:border-b-0">
      <span className="min-w-0">
        <span className="block text-[13px] text-muted-foreground">{label}</span>
      </span>
      {children}
    </div>
  );
}

/** 系统卡：主题 / 语言 / 数据保存路径 */
function SystemCard() {
  const t = useT();
  const { theme, setTheme } = useTheme();
  const lang = useStore((s) => s.lang);
  const setLang = useStore((s) => s.setLang);
  const dataDir = useStore((s) => s.dataDir);
  const setDataDir = useStore((s) => s.setDataDir);

  const [editingPath, setEditingPath] = useState(false);
  const [pathDraft, setPathDraft] = useState("");

  const savePath = () => {
    if (pathDraft.trim()) setDataDir(pathDraft);
    setEditingPath(false);
  };
  /* 浏览文件夹：Tauri 对接 dialog.open；浏览器 mock 无法弹系统对话框，保持当前值 */
  const browsePath = async () => {
    const api = (globalThis as { __TAURI__?: { dialog?: { open?: (opts: { directory: boolean }) => Promise<string | null> } } }).__TAURI__;
    const picked = await api?.dialog?.open?.({ directory: true });
    if (typeof picked === "string" && picked) setDataDir(picked);
  };

  return (
    <Card className="flex shrink-0 flex-col gap-0 pb-0 pt-2">
      <div className="flex h-10 shrink-0 items-center justify-between gap-3 border-b px-4">
        <CardTitle className="flex items-center gap-2 text-[13px]">
          <FolderOpen size={15} /> {t("settings.system")}
        </CardTitle>
      </div>
      {/* 行直铺卡内：分隔线贯穿卡宽，无内嵌表格外壳 */}
      <CardContent className="px-0 pb-0">
        <Row label={t("settings.theme")}>
          <Segment
            value={(theme ?? "dark") as "light" | "dark" | "system"}
            onChange={(id) => {
              setTheme?.(id);
              void backend.setUiSettings({ theme: id });
            }}
            options={THEMES.map(({ id, icon, key }) => ({ id, icon, label: t(key) }))}
          />
        </Row>
        <Row label={t("settings.lang")}>
          <Segment
            value={lang}
            onChange={setLang}
            options={[
              { id: "zh", label: "简体中文" },
              { id: "en", label: "English" },
            ]}
          />
        </Row>
        <Row label={t("settings.dataDir")}>
          {editingPath ? (
            <span className="flex items-center gap-1">
              <Input
                value={pathDraft}
                onChange={(e) => setPathDraft(e.target.value)}
                onKeyDown={(e) => {
                  if (e.key === "Enter") savePath();
                  if (e.key === "Escape") setEditingPath(false);
                }}
                autoFocus
                spellCheck={false}
                className="h-8 w-[24rem] rounded-sm font-mono text-[12px]"
                aria-label={t("settings.dataDir")}
              />
              <Button size="sm" variant="ghost" className="h-8 w-8 px-0" title={t("settings.cancel")} onClick={() => setEditingPath(false)}>
                <X size={13} />
              </Button>
              <Button size="sm" className="h-8 w-8 px-0" title={t("settings.savePath")} disabled={!pathDraft.trim()} onClick={savePath}>
                <Check size={13} />
              </Button>
            </span>
          ) : (
            <span className="flex items-center gap-2">
              <span className="max-w-[22rem] truncate rounded-sm border bg-muted/40 px-2.5 py-1.5 font-mono text-[12px]" title={dataDir}>
                {dataDir || "—"}
              </span>
              <Button size="sm" variant="outline" className="h-8 gap-1 rounded-sm" onClick={() => void browsePath()}>
                <FolderOpen size={12} /> {t("settings.browse")}
              </Button>
            </span>
          )}
        </Row>
      </CardContent>
    </Card>
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
    <div className="grid grid-cols-[minmax(0,1fr)_13rem] items-center gap-6 border-b px-4 py-2.5 last:border-b-0">
      <span className="text-[13px] text-muted-foreground">{label}</span>
      {editing ? (
        <span className="flex h-8 items-stretch overflow-hidden rounded-sm border ring-1 ring-foreground/20">
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
        <span className="readout text-right text-[13px] font-medium">
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
    <Card className="flex shrink-0 flex-col gap-0 pb-0 pt-2">
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
      <CardContent className="px-0 pb-0">
        <div className={cn("flex flex-col", editing && "ring-1 ring-foreground/15")}>
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
          <div className="grid grid-cols-[minmax(0,1fr)_13rem] items-center gap-6 border-b px-4 py-2.5">
            <span className="text-[13px] text-muted-foreground">{t("settings.window")}</span>
            <span className="readout text-right text-[13px]">380 – 1100 nm · 61 ch</span>
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
      <SystemCard />
      <DetectionCard />
      <AboutBar />
    </div>
  );
}
