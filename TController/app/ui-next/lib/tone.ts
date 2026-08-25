/**
 * 语义色调样式映射。ok/warn/danger/muted 四级，与状态色 token 对应。
 * 用于 Badge / 状态标签的背景+前景+边框一次性赋色。
 */
export const toneClass: Record<string, string> = {
  ok: "border-transparent bg-[var(--status-ok)]/15 text-[var(--status-ok)]",
  warn: "border-transparent bg-[var(--status-warn)]/15 text-[var(--status-warn)]",
  danger: "border-transparent bg-[var(--status-danger)]/15 text-[var(--status-danger)]",
  muted: "bg-muted text-muted-foreground border-transparent",
};
