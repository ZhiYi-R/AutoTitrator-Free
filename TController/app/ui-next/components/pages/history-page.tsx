"use client";

/**
 * 数据记录页：运行历史表格 + CSV 导出。
 * Mock 阶段仅保存摘要；正式版将持久化完整曲线数据。
 */
import { Download, History as HistoryIcon } from "lucide-react";
import { Badge } from "@/components/ui/badge";
import { Button } from "@/components/ui/button";
import { Card, CardContent } from "@/components/ui/card";
import { ScrollArea } from "@/components/ui/scroll-area";
import {
  Table,
  TableBody,
  TableCell,
  TableHead,
  TableHeader,
  TableRow,
} from "@/components/ui/table";
import { useStore, confidenceTone, methodTone } from "@/lib/store";
import { useT } from "@/lib/i18n";
import { cn } from "@/lib/utils";
import { toneClass } from "@/lib/tone";

function fmtDuration(s: number) {
  const mm = Math.floor(s / 60);
  const ss = Math.round(s % 60);
  return `${String(mm).padStart(2, "0")}:${String(ss).padStart(2, "0")}`;
}

function exportCsv(rows: ReturnType<typeof useStore.getState>["history"]) {
  const header = "started_at,duration_s,sample_ml,endpoint_ml,method,confidence,reliability,aborted";
  const lines = rows.map((r) =>
    [
      new Date(r.startedAt).toISOString(),
      r.durationS.toFixed(1),
      r.sampleVolume.toFixed(2),
      r.endpoint === null ? "" : r.endpoint.toFixed(3),
      r.method ?? "",
      r.confidence ?? "",
      r.reliability ?? "",
      r.aborted ? "1" : "0",
    ].join(",")
  );
  const blob = new Blob(["\uFEFF" + [header, ...lines].join("\n")], { type: "text/csv;charset=utf-8" });
  const url = URL.createObjectURL(blob);
  const a = document.createElement("a");
  a.href = url;
  a.download = `autotitrator-runs-${new Date().toISOString().slice(0, 10)}.csv`;
  a.click();
  URL.revokeObjectURL(url);
}

export function HistoryPage() {
  const t = useT();
  const history = useStore((s) => s.history);

  return (
    <div className="flex h-full flex-col gap-2 p-3">
      <div className="flex shrink-0 items-center justify-between">
        <h2 className="text-[13px] font-semibold">{t("history.title")}</h2>
        <Button size="sm" variant="outline" className="h-8 gap-1.5" disabled={history.length === 0} onClick={() => exportCsv(history)}>
          <Download size={13} /> {t("history.export")}
        </Button>
      </div>

      <Card className="flex min-h-0 flex-1 flex-col">
        {history.length === 0 ? (
          <CardContent className="grid flex-1 place-items-center text-muted-foreground">
            <HistoryIcon size={22} className="mb-2 opacity-40" />
            <p className="text-xs">{t("history.empty")}</p>
          </CardContent>
        ) : (
          <ScrollArea className="min-h-0 flex-1">
            <Table>
                <TableHeader>
                  <TableRow className="hover:bg-transparent">
                    <TableHead className="text-[11px]">{t("history.time")}</TableHead>
                    <TableHead className="text-[11px]">{t("history.duration")}</TableHead>
                    <TableHead className="text-right text-[11px]">{t("history.sample")}</TableHead>
                    <TableHead className="text-right text-[11px]">{t("history.endpoint")}</TableHead>
                    <TableHead className="text-[11px]">{t("history.method")}</TableHead>
                    <TableHead className="text-[11px]">{t("history.confidence")}</TableHead>
                    <TableHead className="text-[11px]">{t("history.status")}</TableHead>
                  </TableRow>
                </TableHeader>
                <TableBody>
                  {history.map((r) => (
                    <TableRow key={r.id}>
                      <TableCell className="font-mono text-xs">
                        {new Date(r.startedAt).toLocaleString("zh-CN", { hour12: false })}
                      </TableCell>
                      <TableCell className="readout text-xs">{fmtDuration(r.durationS)}</TableCell>
                      <TableCell className="readout text-right text-xs">{r.sampleVolume.toFixed(1)}</TableCell>
                      <TableCell className="readout text-right text-xs font-semibold">{r.endpoint === null ? "—" : r.endpoint.toFixed(3)}</TableCell>
                      <TableCell>
                        {r.method ? (
                          <Badge variant="outline" className={cn("text-[10px]", toneClass[methodTone(r.method)])}>{t(`method.${r.method}`)}</Badge>
                        ) : (
                          <span className="text-xs text-muted-foreground">—</span>
                        )}
                      </TableCell>
                      <TableCell>
                        {r.confidence ? (
                          <Badge variant="outline" className={cn("text-[10px]", toneClass[confidenceTone(r.confidence)])}>{t(`confidence.${r.confidence}`)}</Badge>
                        ) : (
                          <span className="text-xs text-muted-foreground">—</span>
                        )}
                      </TableCell>
                      <TableCell>
                        <Badge variant="outline" className={cn("text-[10px]", r.aborted ? toneClass.danger : toneClass.ok)}>
                          {r.aborted ? t("history.aborted") : t("history.completed")}
                        </Badge>
                      </TableCell>
                    </TableRow>
                  ))}
                </TableBody>
              </Table>
          </ScrollArea>
        )}
      </Card>
    </div>
  );
}
