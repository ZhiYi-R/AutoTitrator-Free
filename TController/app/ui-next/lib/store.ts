import { create } from "zustand";
import type {
  CalPoint,
  Confidence,
  EndpointResult,
  HistoryRun,
  LiveSample,
  LogEntry,
  Method,
  PotentialPoint,
  ReliabilityStatus,
  ScenarioId,
  SerialPortInfo,
  SpectralState,
  SpectrumFrame,
  TubingOp,
  WorkflowState,
} from "@/lib/types";
import type { Lang } from "@/lib/i18n";
import { backend, type BackendSnapshot } from "@/lib/backend";

export type PageId = "titration" | "calibration" | "maintenance" | "history" | "settings";

export interface DetectionParams {
  t1DerivThreshold: number;
  dose: number;
  overTitrate: number;
  consensusTol: number;
}

export const DEFAULT_DETECTION: DetectionParams = {
  t1DerivThreshold: 0.85,
  dose: 0.05,
  overTitrate: 0.8,
  consensusTol: 0.15,
};

/** 浓度计算参数：a·分析物 + b·滴定剂 → 产物，c分析物 = c滴定剂 · V终点 · (a/b) ÷ V样品 */
export interface AnalysisParams {
  titrantConc: number;  /* mol/L */
  analyteCoeff: number; /* a */
  titrantCoeff: number; /* b */
}

export const DEFAULT_ANALYSIS: AnalysisParams = {
  titrantConc: 0.1,
  analyteCoeff: 1,
  titrantCoeff: 1,
};

/** 由终点体积（mL）与样品体积（mL）计算分析物浓度（mol/L）；参数非法时返回 null */
export function analyteConcentration(p: AnalysisParams, endpointMl: number, sampleMl: number): number | null {
  if (p.titrantConc <= 0 || p.analyteCoeff <= 0 || p.titrantCoeff <= 0 || sampleMl <= 0 || endpointMl <= 0) return null;
  return (p.titrantConc * endpointMl * (p.analyteCoeff / p.titrantCoeff)) / sampleMl;
}

export type { CalPoint };

export interface AppState {
  lang: Lang;
  page: PageId;
  navCollapsed: boolean;
  connected: boolean;
  connecting: boolean;
  port: string;
  baud: number;
  ports: SerialPortInfo[];
  workflow: WorkflowState;
  volume: number;
  elapsedMs: number;
  sampleVolume: number;
  sampleInput: number;
  scenario: ScenarioId;
  speed: number;
  tubingOp: TubingOp | null;
  tubingP1: boolean;
  tubingP2: boolean;
  potPoints: PotentialPoint[];
  /** 连接后待机/进样阶段的实时电极走条（时间轴）；滴定数据产生后图表切换体积轴 */
  liveTrace: LiveSample[];
  spectra: SpectrumFrame[];
  spectralState: SpectralState;
  lastE: number | null;
  lastDeriv: number | null;
  t1: EndpointResult | null;
  final: EndpointResult | null;
  pump1Running: boolean;
  pump2Running: boolean;
  pump1Steps: number;
  pump2Steps: number;
  watchdogEnabled: boolean;
  pumpSlope: number;
  pumpIntercept: number;
  pumpR2: number | null;
  rx: number;
  tx: number;
  badFrames: number;
  heartbeatTick: number;
  logs: LogEntry[];
  history: HistoryRun[];
  calPoints: CalPoint[];
  /** 实验数据（CSV/导出）保存目录；Tauri 侧持久化于 settings.json */
  dataDir: string;
  detection: DetectionParams;
  analysis: AnalysisParams;

  setLang: (l: Lang) => void;
  setPage: (p: PageId) => void;
  toggleNav: () => void;
  setPort: (p: string) => void;
  setBaud: (b: number) => void;
  setSampleInput: (v: number) => void;
  setScenario: (s: ScenarioId) => void;
  setSpeed: (x: number) => void;
  setTubingPumps: (p1: boolean, p2: boolean) => void;
  setWatchdog: (on: boolean) => void;
  setDetection: (patch: Partial<DetectionParams>) => void;
  setAnalysis: (patch: Partial<AnalysisParams>) => void;
  setDataDir: (dir: string) => void;
  addLog: (level: LogEntry["level"], text: string, opts?: { pump?: 1 | 2 }) => void;
  recordRun: (run: Omit<HistoryRun, "id" | "startedAt">) => void;
  resetRunData: () => void;
}

const initial: Omit<AppState, "setLang" | "setPage" | "toggleNav" | "setPort" | "setBaud" | "setSampleInput" | "setScenario" | "setSpeed" | "setTubingPumps" | "setWatchdog" | "setDetection" | "setAnalysis" | "setDataDir" | "addLog" | "recordRun" | "resetRunData"> = {
  lang: "zh",
  page: "titration",
  navCollapsed: false,
  connected: false,
  connecting: false,
  port: "",
  baud: 115200,
  ports: [{ portName: "COM4", description: "Mock serial device" }],
  workflow: "idle",
  volume: 0,
  elapsedMs: 0,
  sampleVolume: 10,
  sampleInput: 10,
  scenario: "normal",
  speed: 1,
  tubingOp: null,
  tubingP1: true,
  tubingP2: true,
  potPoints: [],
  liveTrace: [],
  spectra: [],
  spectralState: "IDLE",
  lastE: null,
  lastDeriv: null,
  t1: null,
  final: null,
  pump1Running: false,
  pump2Running: false,
  pump1Steps: 0,
  pump2Steps: 0,
  watchdogEnabled: true,
  pumpSlope: 0,
  pumpIntercept: 0,
  pumpR2: null,
  rx: 0,
  tx: 0,
  badFrames: 0,
  heartbeatTick: 0,
  logs: [],
  history: [],
  calPoints: [],
  dataDir: "",
  detection: { ...DEFAULT_DETECTION },
  analysis: { ...DEFAULT_ANALYSIS },
};

function endpoint(raw: BackendSnapshot["t1"]): EndpointResult | null {
  if (!raw) return null;
  return {
    stage: raw.stage === "final" ? "final" : "t1",
    volume: raw.volume,
    method: raw.method as Method,
    confidence: raw.confidence as Confidence,
    potentialVolume: raw.potentialVolume,
    spectralVolume: raw.spectralVolume,
    reliability: raw.reliability as ReliabilityStatus,
    kf: raw.kf,
    refined: raw.refined,
  };
}

export function applyBackendSnapshot(snapshot: BackendSnapshot) {
  const currentPort = useStore.getState().port;
  const availablePort = snapshot.ports.some((item) => item.portName === currentPort)
    ? currentPort
    : snapshot.ports.some((item) => item.portName === snapshot.port)
      ? snapshot.port
      : snapshot.ports[0]?.portName ?? snapshot.port;

  useStore.setState({
    ports: snapshot.ports,
    connected: snapshot.connected,
    connecting: snapshot.connecting,
    port: availablePort,
    baud: snapshot.baud,
    workflow: snapshot.workflow as WorkflowState,
    volume: snapshot.volume,
    elapsedMs: snapshot.elapsedMs,
    sampleVolume: snapshot.sampleVolume,
    sampleInput: snapshot.sampleInput,
    tubingOp: snapshot.tubingOp,
    tubingP1: snapshot.tubingP1,
    tubingP2: snapshot.tubingP2,
    pump1Running: snapshot.pump1Running,
    pump2Running: snapshot.pump2Running,
    pump1Steps: snapshot.pump1Steps,
    pump2Steps: snapshot.pump2Steps,
    pumpSlope: snapshot.pumpSlope,
    pumpIntercept: snapshot.pumpIntercept,
    pumpR2: snapshot.pumpR2,
    calPoints: snapshot.calPoints,
    potPoints: snapshot.potPoints,
    spectra: snapshot.spectra,
    spectralState: snapshot.spectralState as SpectralState,
    lastE: snapshot.lastE,
    lastDeriv: snapshot.lastDeriv,
    t1: endpoint(snapshot.t1),
    final: endpoint(snapshot.finalResult),
    watchdogEnabled: snapshot.watchdogEnabled,
    detection: snapshot.detection,
    rx: snapshot.rx,
    tx: snapshot.tx,
    badFrames: snapshot.badFrames,
    heartbeatTick: snapshot.heartbeatTick,
    logs: snapshot.logs as LogEntry[],
    history: snapshot.history as HistoryRun[],
    lang: snapshot.lang,
    navCollapsed: snapshot.navCollapsed,
  });
}

export const useStore = create<AppState>()((set, get) => ({
  ...initial,
  setLang: (lang) => {
    set({ lang });
    void backend.setUiSettings({ lang });
  },
  setPage: (page) => set({ page }),
  toggleNav: () => {
    const navCollapsed = !get().navCollapsed;
    set({ navCollapsed });
    void backend.setUiSettings({ navCollapsed });
  },
  setPort: (port) => set({ port }),
  setBaud: (baud) => set({ baud }),
  setSampleInput: (sampleInput) => {
    set({ sampleInput, sampleVolume: sampleInput });
    void backend.setSampleInput(sampleInput);
  },
  setScenario: (scenario) => set({ scenario }),
  setSpeed: (speed) => set({ speed }),
  setTubingPumps: (tubingP1, tubingP2) => {
    set({ tubingP1, tubingP2 });
    void backend.setTubingPumps(tubingP1, tubingP2);
  },
  setWatchdog: (watchdogEnabled) => {
    set({ watchdogEnabled });
    void backend.setWatchdog(watchdogEnabled);
  },
  setDetection: (patch) => {
    const detection = { ...get().detection, ...patch };
    set({ detection });
    void backend.setDetection(patch);
  },
  /* 浓度计算只在上位机进行，参数不下发固件 */
  setAnalysis: (patch) => {
    set({ analysis: { ...get().analysis, ...patch } });
  },
  setDataDir: (dataDir) => {
    const dir = dataDir.trim();
    set({ dataDir: dir });
    void backend.setUiSettings({ dataDir: dir });
  },
  /* 运行事件全量入 store（工作台「事件日志」消费）；无泵标记的照旧镜像到 console */
  addLog: (level, text, opts) => {
    set({ logs: [...get().logs, { t: Date.now(), level, text }].slice(-400) });
    if (!opts?.pump) console.debug(`[autotitrator:${level}] ${text}`);
  },
  recordRun: (run) => {
    const entry: HistoryRun = { ...run, id: Math.random().toString(36).slice(2, 9), startedAt: Date.now() };
    set({ history: [entry, ...get().history].slice(0, 30) });
  },
  resetRunData: () => {
    set({ workflow: "idle", volume: 0, elapsedMs: 0, potPoints: [], liveTrace: [], spectra: [], spectralState: "IDLE", lastE: null, lastDeriv: null, t1: null, final: null });
    void backend.reset();
  },
}));

/** 结果面板展示用的方法/置信度徽标色调 */
export function confidenceTone(c: Confidence | null): "ok" | "warn" | "danger" | "muted" {
  if (c === "high") return "ok";
  if (c === "medium") return "warn";
  if (c === "low") return "danger";
  return "muted";
}

export function methodTone(m: Method | null): "ok" | "warn" | "danger" | "muted" {
  if (m === "consensus") return "ok";
  if (m === "potential_only" || m === "spectral_only") return "warn";
  if (m === "conflict") return "danger";
  return "muted";
}

export function reliabilityTone(r: ReliabilityStatus | null): "ok" | "warn" | "danger" | "muted" {
  if (r === "OK" || r === "CONFIRMED") return "ok";
  if (r === "LOW_EVIDENCE" || r === "NO_SPECTRUM" || r === "CANDIDATE" || r === "CONFIRMING" || r === "EARLY_WARNING") return "warn";
  if (r === "CONFLICT") return "danger";
  return "muted";
}
