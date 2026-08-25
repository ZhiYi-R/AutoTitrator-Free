/**
 * 前后端事件协议类型，与 controller-core (Rust) 语义一致。
 * 当前由 lib/mock/simulator.ts 实现；接入真实后端时仅需替换数据源，
 * 字段名保持 snake_case 序列化语义。
 */

export interface SerialPortInfo {
  portName: string;
  description: string | null;
}

/** 对应 Rust TitrationState（serde rename_all = "snake_case"） */
export type WorkflowState =
  | "idle"
  | "injecting"
  | "titrating"
  | "degree1"
  | "titrating2"
  | "done"
  | "error";

/** 对应 Rust Method */
export type Method = "consensus" | "potential_only" | "spectral_only" | "conflict";

/** 对应 Rust Confidence */
export type Confidence = "high" | "medium" | "low";

/** 对应 Rust TrackerState 字符串 */
export type SpectralState = "IDLE" | "IN_CHANGE" | "END_CONFIRMED";

/** 可靠性状态（Reliability.status 的常见取值） */
export type ReliabilityStatus =
  | "OK"
  | "CONFIRMED"
  | "CANDIDATE"
  | "CONFIRMING"
  | "EARLY_WARNING"
  | "LOW_EVIDENCE"
  | "CONFLICT"
  | "NO_SPECTRUM"
  | "UNOBSERVABLE";

export interface PotentialPoint {
  /** 滴定剂累计体积 mL */
  v: number;
  /** 时间 s */
  t: number;
  /** 电位 V */
  e: number;
}

export interface SpectrumFrame {
  v: number;
  /** 吸光度，与 wavelengths 等长 */
  absorbance: number[];
}

export interface KfSnapshot {
  volume: number;
  std: number;
  nis: number;
}

export interface EndpointResult {
  stage: "t1" | "final";
  volume: number;
  method: Method;
  confidence: Confidence;
  potentialVolume: number | null;
  spectralVolume: number | null;
  reliability: ReliabilityStatus;
  kf: KfSnapshot | null;
  /** AMPD 精修值（final 阶段） */
  refined: number | null;
}

export interface LogEntry {
  t: number;
  level: "info" | "ok" | "warn" | "error";
  text: string;
}

export interface HistoryRun {
  id: string;
  startedAt: number;
  durationS: number;
  sampleVolume: number;
  endpoint: number | null;
  method: Method | null;
  confidence: Confidence | null;
  reliability: ReliabilityStatus | null;
  scenario: ScenarioId;
  aborted: boolean;
}

export type ScenarioId = "normal" | "noisy" | "conflict" | "failure";

/** 管路作业：滴定前预充 / 结束后排空。不进入 TitrationState。 */
export type TubingOp = "prime" | "empty";

/** 泵标定散点：累计步数 ↔ 实测体积。由后端从 calibre.npz 读出。 */
export interface CalPoint {
  steps: number;
  vol: number;
}

export const WAVELENGTHS: number[] = Array.from({ length: 61 }, (_, i) => 380 + i * 12);
