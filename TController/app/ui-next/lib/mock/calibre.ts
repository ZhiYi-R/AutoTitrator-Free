/**
 * mock 后端的 calibre.npz 镜像。
 * 数值取自项目 data/calibre.npz 的 pump2_*（滴定剂泵）。
 * 浏览器开发模式使用此镜像；Tauri 环境由后端读取真实 npz。
 */
import type { CalPoint } from "@/lib/types";

/** volume = slope × steps + intercept（mL/步），与 controller-core 一致。 */
export const CALIBRE_PUMP2_SLOPE = 6.099737096774193e-6;
export const CALIBRE_PUMP2_INTERCEPT = 0;
export const CALIBRE_PUMP2_R2 = 0.999655550757749;

const PULSES = [
  0, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000, 120000, 130000, 140000, 150000,
] as const;

const VOLUMES = [
  0, 0.064, 0.12713, 0.19421, 0.25165, 0.30748, 0.36944, 0.4316, 0.48854, 0.551, 0.60593, 0.66839, 0.73928, 0.79341,
  0.84804, 0.90779,
] as const;

export const CALIBRE_PUMP2_POINTS: CalPoint[] = PULSES.map((steps, i) => ({
  steps,
  vol: VOLUMES[i],
}));

export function stepsPerMl(slopeMlPerStep: number): number {
  return slopeMlPerStep > 0 ? 1 / slopeMlPerStep : 0;
}
