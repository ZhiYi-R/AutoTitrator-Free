/**
 * Mock 仪器后端，设计稿阶段的数据源。
 *
 * 对外暴露与真实后端一致的动词语义（connect/start/stop/abort/jog…），
 * 内部用定时器 + 滴定物理模型产生事件流写入 store。
 * 接入 Tauri 真实后端时，仅需把本文件替换为 invoke 桥，
 * store 与 UI 组件无需改动。
 */
import { toast } from "sonner";
import { useStore } from "@/lib/store";
import { translate } from "@/lib/i18n";
import { WAVELENGTHS } from "@/lib/types";
import type { CalPoint, EndpointResult, PotentialPoint, ScenarioId, SpectrumFrame, TubingOp } from "@/lib/types";
import { CALIBRE_PUMP2_INTERCEPT, CALIBRE_PUMP2_POINTS, CALIBRE_PUMP2_R2, CALIBRE_PUMP2_SLOPE, stepsPerMl } from "@/lib/mock/calibre";

/* ---------------- 场景物理参数 ---------------- */

interface ScenarioCfg {
  vEp: number;          // 电位通道真实终点
  vEpSpecOffset: number; // 光谱通道终点偏移（冲突场景 >0）
  noise: number;        // 电位噪声 σ
  peakAmp: number;      // 光谱吸光度变化幅度
  fail: boolean;        // 中途泵故障
}

const SCENARIOS: Record<ScenarioId, ScenarioCfg> = {
  normal:  { vEp: 6.2, vEpSpecOffset: 0.0, noise: 0.003, peakAmp: 0.42, fail: false },
  noisy:   { vEp: 6.4, vEpSpecOffset: 0.0, noise: 0.014, peakAmp: 0.11, fail: false },
  conflict:{ vEp: 6.2, vEpSpecOffset: 0.6, noise: 0.004, peakAmp: 0.36, fail: false },
  failure: { vEp: 6.2, vEpSpecOffset: 0.0, noise: 0.003, peakAmp: 0.42, fail: true },
};

const BASE_TICK_MS = 620;   // 1x 速度下的滴加间隔
const MOCK_PORTS = [{ portName: "COM4", description: "Mock serial device" }];

/* ---------------- 工具 ---------------- */

function gauss(x: number, mu: number, sigma: number): number {
  return Math.exp(-((x - mu) ** 2) / (2 * sigma * sigma));
}
function sigmoid(x: number): number {
  return 1 / (1 + Math.exp(-x));
}
function rand(sigma: number): number {
  // Box-Muller
  const u = Math.random() || 1e-9;
  const v = Math.random();
  return sigma * Math.sqrt(-2 * Math.log(u)) * Math.cos(2 * Math.PI * v);
}

function log(level: "info" | "ok" | "warn" | "error", key: Parameters<typeof translate>[1], vars?: Record<string, string | number>) {
  const { lang, addLog } = useStore.getState();
  addLog(level, translate(lang, key, vars));
}

/* ---------------- 引擎内部状态 ---------------- */

let tickTimer: ReturnType<typeof setInterval> | null = null;
let heartbeatTimer: ReturnType<typeof setInterval> | null = null;
let elapsedTimer: ReturnType<typeof setInterval> | null = null;
let injectionTimer: ReturnType<typeof setInterval> | null = null;
let phaseTimer: ReturnType<typeof setTimeout> | null = null;
let liveTimer: ReturnType<typeof setInterval> | null = null;
let tubingTimer: ReturnType<typeof setInterval> | null = null;

let cfg: ScenarioCfg = SCENARIOS.normal;
let maxDerivVol = 0;
let maxDerivVal = 0;
let t1Fired = false;
let degree1Ticks = 0;
let runStartWall = 0;

function clearTimers() {
  if (tickTimer) clearInterval(tickTimer);
  if (injectionTimer) clearInterval(injectionTimer);
  if (phaseTimer) clearTimeout(phaseTimer);
  if (elapsedTimer) clearInterval(elapsedTimer);
  if (tubingTimer) clearInterval(tubingTimer);
  tickTimer = injectionTimer = elapsedTimer = phaseTimer = tubingTimer = null;
}

/**
 * 连接期间的实时电极采样（1Hz）：待机/进样阶段电极持续有读数，
 * 电位图以时间轴走条呈现，替代空态占位。
 */
function startLiveTrace() {
  if (liveTimer) return;
  liveTimer = setInterval(() => {
    const s = useStore.getState();
    if (!s.connected) return;
    useStore.setState({
      liveTrace: [...s.liveTrace, { t: Date.now(), e: potentialAt(0) }].slice(-240),
      lastE: potentialAt(0),
    });
  }, 1000);
}

function stopLiveTrace() {
  if (liveTimer) clearInterval(liveTimer);
  liveTimer = null;
}

function speed() {
  return useStore.getState().speed;
}

/* ---------------- 曲线模型 ---------------- */

function potentialAt(v: number): number {
  const base = -0.12 + 0.92 * sigmoid((v - cfg.vEp) / 0.13) + 0.004 * v;
  return base + rand(cfg.noise);
}

function spectrumAt(v: number): number[] {
  const vSpec = cfg.vEp + cfg.vEpSpecOffset;
  const progress = sigmoid((v - vSpec) / 0.15);
  return WAVELENGTHS.map((wl) => {
    const baseline = 0.18 - 0.00012 * (wl - 380) + 0.08 * gauss(wl, 430, 40);
    const band = cfg.peakAmp * gauss(wl, 560, 55) * progress;
    return Math.max(0, baseline + band + rand(0.0022));
  });
}

function computeDeriv(points: PotentialPoint[]): number | null {
  const n = points.length;
  if (n < 6) return null;
  const a = points[n - 6];
  const b = points[n - 1];
  if (b.v <= a.v) return null;
  return (b.e - a.e) / (b.v - a.v);
}

function spectralStateAt(v: number): "IDLE" | "IN_CHANGE" | "END_CONFIRMED" {
  const vSpec = cfg.vEp + cfg.vEpSpecOffset;
  if (v < vSpec - 0.3) return "IDLE";
  if (v <= vSpec + 0.3) return "IN_CHANGE";
  return "END_CONFIRMED";
}

function buildResult(stage: "t1" | "final", volume: number, refined: number | null): EndpointResult {
  const sc = useStore.getState().scenario;
  const conflict = sc === "conflict";
  const noisy = sc === "noisy";
  const potVol = maxDerivVol > 0 ? Number(maxDerivVol.toFixed(3)) : volume;
  const specVol = Number((potVol + cfg.vEpSpecOffset + (conflict ? 0.05 : 0)).toFixed(3));
  const split = Math.abs(specVol - potVol);
  const disagree = split > useStore.getState().detection.consensusTol;
  const method = disagree ? "conflict" : noisy ? "potential_only" : "consensus";
  const confidence = disagree ? "low" : noisy ? "medium" : "high";
  const reliability = disagree ? "CONFLICT" : noisy ? "LOW_EVIDENCE" : "OK";
  return {
    stage,
    volume: Number(volume.toFixed(3)),
    method,
    confidence,
    potentialVolume: potVol,
    spectralVolume: method === "conflict" ? specVol : potVol + 0.01,
    reliability,
    kf:
      method === "consensus"
        ? { volume: Number(((potVol + specVol) / 2).toFixed(3)), std: noisy ? 0.052 : 0.018, nis: noisy ? 5.4 : 1.9 }
        : null,
    refined,
  };
}

/* ---------------- 滴加循环 ---------------- */

function titrationTick() {
  const st = useStore.getState();
  const { workflow, volume, detection } = st;
  if (workflow !== "titrating" && workflow !== "degree1" && workflow !== "titrating2") return;
  const dose = detection.dose > 0 ? detection.dose : 0.05;

  // 故障场景：中途泵堵转
  if (cfg.fail && volume > cfg.vEp * 0.62 && workflow === "titrating") {
    clearTimers();
    useStore.setState({ workflow: "error", pump2Running: false, badFrames: st.badFrames + 1 });
    log("error", "log.pumpStall");
    const { lang } = useStore.getState();
    toast.error(translate(lang, "toast.error", { msg: "pump stall" }));
    recordHistory(true);
    return;
  }

  const newVol = volume + dose;
  const nowS = (Date.now() - runStartWall) / 1000;

  // 电位点：一个加液周期内 3 个采样
  const pts: PotentialPoint[] = [];
  for (let i = 1; i <= 3; i++) {
    const v = volume + (dose * i) / 3;
    pts.push({ v, t: nowS + i * 0.4, e: potentialAt(v) });
  }
  const frame: SpectrumFrame = { v: newVol, absorbance: spectrumAt(newVol) };

  const potPoints = [...st.potPoints, ...pts].slice(-6000);
  const spectra = [...st.spectra, frame].slice(-2000);
  const deriv = computeDeriv(potPoints);

  if (deriv !== null && deriv > maxDerivVal) {
    maxDerivVal = deriv;
    maxDerivVol = newVol;
  }

  const patch: Partial<ReturnType<typeof useStore.getState>> = {
    volume: newVol,
    potPoints,
    spectra,
    lastE: pts[2].e,
    lastDeriv: deriv,
    spectralState: spectralStateAt(newVol),
    rx: st.rx + 4,
    tx: st.tx + 1,
  };

  // T=1 判定：导数越限
  if (!t1Fired && deriv !== null && deriv > detection.t1DerivThreshold && newVol > 2) {
    t1Fired = true;
    const t1 = buildResult("t1", newVol, null);
    patch.workflow = "degree1";
    patch.t1 = t1;
    degree1Ticks = 0;
    log("warn", "log.t1", { v: t1.volume.toFixed(2) });
    const { lang } = useStore.getState();
    toast.info(translate(lang, "toast.t1", { v: t1.volume.toFixed(2) }));
  } else if (workflow === "degree1") {
    degree1Ticks += 1;
    if (degree1Ticks >= 3) patch.workflow = "titrating2";
  } else if (workflow === "titrating2" && t1Fired && newVol > maxDerivVol + detection.overTitrate) {
    finishRun(patch as Record<string, unknown>);
    return;
  }

  useStore.setState(patch);
}

function finishRun(patch: Record<string, unknown>) {
  const st = useStore.getState();
  const refined = Number((maxDerivVol + rand(0.008)).toFixed(3));
  const final = buildResult("final", refined, refined);
  useStore.setState({
    ...patch,
    workflow: "done",
    final,
    pump2Running: false,
  });
  clearTimers();
  log("ok", "log.done", { v: refined.toFixed(2), m: final.method });
  /* 数据落盘演示：真实后端把运行记录写为 dataDir 下的 CSV */
  if (st.dataDir) log("info", "log.dataWritten", { dir: st.dataDir });
  const { lang } = useStore.getState();
  toast.success(translate(lang, "toast.done", { v: refined.toFixed(2) }));
  recordHistory(false);
}

function recordHistory(aborted: boolean) {
  const st = useStore.getState();
  st.recordRun({
    durationS: Math.round(st.elapsedMs / 1000),
    sampleVolume: st.sampleVolume,
    endpoint: st.final?.volume ?? (t1Fired ? maxDerivVol : null),
    method: st.final?.method ?? null,
    confidence: st.final?.confidence ?? null,
    reliability: st.final?.reliability ?? null,
    scenario: st.scenario,
    aborted,
  });
}

/* ---------------- 泵标定（calibre.npz 由后端读取；此处为 mock 镜像） ---------------- */

let pumpCal: {
  points: CalPoint[];
  slopeMlPerStep: number;
  intercept: number;
  r2: number | null;
} = {
  points: CALIBRE_PUMP2_POINTS.map((p) => ({ ...p })),
  slopeMlPerStep: CALIBRE_PUMP2_SLOPE,
  intercept: CALIBRE_PUMP2_INTERCEPT,
  r2: CALIBRE_PUMP2_R2,
};

function publishPumpCal() {
  useStore.setState({
    pumpSlope: Math.round(stepsPerMl(pumpCal.slopeMlPerStep)),
    pumpIntercept: pumpCal.intercept,
    pumpR2: pumpCal.r2,
    calPoints: pumpCal.points.map((p) => ({ ...p })),
  });
}

publishPumpCal();
useStore.setState({ ports: MOCK_PORTS, port: MOCK_PORTS[0].portName });

/* ---------------- 对外动作（真实后端接线时替换内部实现） ---------------- */

export const backend = {
  connect() {
    const { port, baud, connecting, connected } = useStore.getState();
    if (connecting || connected) return;
    useStore.setState({ connecting: true });
    phaseTimer = setTimeout(() => {
      useStore.setState({ connecting: false, connected: true, rx: 12, tx: 8 });
      log("ok", "log.connected");
      const { lang } = useStore.getState();
      toast.success(translate(lang, "toast.connected", { port: `${port} @ ${baud}` }));
      heartbeatTimer = setInterval(() => {
        const s = useStore.getState();
        if (s.connected) useStore.setState({ heartbeatTick: s.heartbeatTick + 1, rx: s.rx + 1 });
      }, 1000);
      startLiveTrace();
    }, 600);
  },

  disconnect() {
    if (heartbeatTimer) clearInterval(heartbeatTimer);
    heartbeatTimer = null;
    stopLiveTrace();
    clearTimers();
    this.abort(true);
    useStore.setState({ connected: false, pump1Running: false, pump2Running: false, tubingOp: null });
    const { lang } = useStore.getState();
    toast.message(translate(lang, "toast.disconnected"));
  },

  start() {
    const st = useStore.getState();
    if (!st.connected) {
      toast.warning(translate(st.lang, "toast.needConnect"));
      return;
    }
    if (st.tubingOp) {
      toast.warning(translate(st.lang, "toast.tubingBusy"));
      return;
    }
    if (st.workflow === "injecting" || st.workflow === "titrating" || st.workflow === "degree1" || st.workflow === "titrating2") {
      return;
    }
    st.resetRunData();
    cfg = SCENARIOS[st.scenario];
    t1Fired = false;
    maxDerivVol = 0;
    maxDerivVal = 0;
    degree1Ticks = 0;
    runStartWall = Date.now();
    /* 滴定正式采样开始，实时走条让位（体积轴成为主图） */
    useStore.setState({ liveTrace: [] });
    stopLiveTrace();
    const sample = st.sampleInput;
    const injectionDuration = 2600 / speed();
    const injectionTargetSteps = pumpCal.slopeMlPerStep > 0
      ? Math.max(0, Math.round((sample - pumpCal.intercept) / pumpCal.slopeMlPerStep))
      : 0;
    const injectionStarted = Date.now();
    useStore.setState({ workflow: "injecting", sampleVolume: sample, pump1Running: true, pump1Steps: 0 });
    injectionTimer = setInterval(() => {
      const elapsed = Date.now() - injectionStarted;
      const progress = Math.min(1, elapsed / injectionDuration);
      useStore.setState({ pump1Steps: Math.round(injectionTargetSteps * progress) });
      if (progress >= 1 && injectionTimer) {
        clearInterval(injectionTimer);
        injectionTimer = null;
      }
    }, 50);
    log("info", "log.inject", { v: sample.toFixed(1) });
    const { lang } = useStore.getState();
    toast.info(translate(lang, "toast.runStarted", { v: sample.toFixed(1) }));

    phaseTimer = setTimeout(() => {
      if (injectionTimer) {
        clearInterval(injectionTimer);
        injectionTimer = null;
      }
      useStore.setState({ workflow: "titrating", pump1Running: false, pump1Steps: injectionTargetSteps, pump2Running: true });
      log("info", "log.injectDone");
      tickTimer = setInterval(titrationTick, BASE_TICK_MS / speed());
      elapsedTimer = setInterval(() => {
        const s = useStore.getState();
        useStore.setState({ elapsedMs: s.elapsedMs + 500 * s.speed });
      }, 500);
    }, 2600 / speed());
  },

  /** 手动停止：停泵并直接精修出结果 */
  manualStop() {
    const st = useStore.getState();
    if (!["titrating", "degree1", "titrating2"].includes(st.workflow)) return;
    clearTimers();
    const refined = maxDerivVol > 0 ? Number((maxDerivVol + rand(0.01)).toFixed(3)) : null;
    const final = refined !== null ? buildResult("final", refined, refined) : null;
    useStore.setState({ workflow: "done", final, pump2Running: false, pump1Running: false });
    log("info", "log.manualStop");
    recordHistory(false);
  },

  /** 中止 / 急停：全泵停止，回到待机，保留已采集曲线 */
  abort(silent = false) {
    const st = useStore.getState();
    const running = ["injecting", "titrating", "degree1", "titrating2"].includes(st.workflow);
    clearTimers();
    useStore.setState({ workflow: "idle", pump1Running: false, pump2Running: false, tubingOp: null });
    if (running) {
      log("warn", "log.aborted");
      recordHistory(true);
    } else if (!silent) {
      log("warn", "log.aborted");
    }
  },

  /** 变速：运行中立即生效 */
  retune() {
    const st = useStore.getState();
    if (tickTimer) {
      clearInterval(tickTimer);
      tickTimer = setInterval(titrationTick, BASE_TICK_MS / speed());
    }
    void st;
  },

  /* ---- 工作台：管路预充 / 排空（FreeRun，肉眼确认后手动停） ---- */
  startTubing(op: TubingOp) {
    const st = useStore.getState();
    if (!st.connected) {
      toast.warning(translate(st.lang, "toast.needConnect"));
      return;
    }
    if (st.tubingOp || ["injecting", "titrating", "degree1", "titrating2"].includes(st.workflow)) {
      toast.warning(translate(st.lang, "toast.tubingBusy"));
      return;
    }
    const pumps = [st.tubingP1 && 1, st.tubingP2 && 2].filter(Boolean) as (1 | 2)[];
    if (pumps.length === 0) {
      toast.warning(translate(st.lang, "toast.needPump"));
      return;
    }
    useStore.setState({
      tubingOp: op,
      pump1Running: pumps.includes(1),
      pump2Running: pumps.includes(2),
      tx: st.tx + pumps.length,
    });
    log("info", op === "prime" ? "log.primeStart" : "log.emptyStart", { p: pumps.join("+") });
    /* 管路步进累计：1000 步/秒/泵（与固件 PUMP_STEP_FREQ 一致） */
    if (tubingTimer) clearInterval(tubingTimer);
    tubingTimer = setInterval(() => {
      const s = useStore.getState();
      if (!s.tubingOp) return;
      useStore.setState({
        pump1Steps: s.tubingP1 ? s.pump1Steps + 250 : s.pump1Steps,
        pump2Steps: s.tubingP2 ? s.pump2Steps + 250 : s.pump2Steps,
      });
    }, 250);
  },
  stopTubing() {
    const st = useStore.getState();
    if (!st.tubingOp) return;
    const op = st.tubingOp;
    if (tubingTimer) clearInterval(tubingTimer);
    tubingTimer = null;
    useStore.setState({ tubingOp: null, pump1Running: false, pump2Running: false, tx: st.tx + 1 });
    log("ok", op === "prime" ? "log.primeStop" : "log.emptyStop");
  },

  /* ---- 维护页：泵手动控制 ---- */
  freeRun(pump: 1 | 2) {
    const { connected, lang, tubingOp, workflow } = useStore.getState();
    if (!connected) return;
    if (tubingOp || ["injecting", "titrating", "degree1", "titrating2"].includes(workflow)) return;
    useStore.setState(pump === 1
      ? { pump1Running: true, tx: useStore.getState().tx + 1 }
      : { pump2Running: true, tx: useStore.getState().tx + 1 });
    useStore.getState().addLog("info", translate(lang, "log.pumpRun", { p: pump }), { pump });
  },
  freeStop(pump: 1 | 2) {
    const { lang } = useStore.getState();
    useStore.setState(pump === 1
      ? { pump1Running: false, tx: useStore.getState().tx + 1 }
      : { pump2Running: false, tx: useStore.getState().tx + 1 });
    useStore.getState().addLog("info", translate(lang, "log.pumpStop", { p: pump }), { pump });
  },
  jog(pump: 1 | 2, steps: number) {
    const { connected, lang } = useStore.getState();
    if (!connected || steps <= 0) return;
    const vol = pumpCal.slopeMlPerStep * steps + pumpCal.intercept;
    useStore.setState(pump === 1
      ? { pump1Steps: useStore.getState().pump1Steps + steps, tx: useStore.getState().tx + 1 }
      : { pump2Steps: useStore.getState().pump2Steps + steps, tx: useStore.getState().tx + 1 });
    useStore.getState().addLog("ok", translate(lang, "log.pumpJog", { p: pump, n: steps, v: vol.toFixed(3) }), { pump });
  },

  /** 从后端重新读出当前载入的泵标定（mock：回放 calibre 镜像）。 */
  loadPumpCalibration() {
    publishPumpCal();
    /* 数据保存路径：mock 侧持久化于 localStorage，默认为系统文档目录语义 */
    const KEY = "autotitrator.dataDir";
    const stored = typeof localStorage !== "undefined" ? localStorage.getItem(KEY) : null;
    useStore.setState({
      ports: MOCK_PORTS,
      port: useStore.getState().port || MOCK_PORTS[0].portName,
      dataDir: stored ?? "D:\\AutoTitrator\\Data",
    });
  },

  /** 持久化数据保存路径（mock：localStorage；Tauri 侧为 settings.json）。 */
  setDataDir(dir: string) {
    try { localStorage.setItem("autotitrator.dataDir", dir); } catch { /* 隐私模式等 */ }
    const { lang } = useStore.getState();
    if (dir) useStore.getState().addLog("ok", translate(lang, "log.dataDirSet", { dir }));
  },

  /** 把本次会话拟合写回后端标定文件，再镜像到 store。 */
  applyPumpCalibration(points: CalPoint[], slopeStepsPerMl: number, interceptMl = 0, r2: number | null = null) {
    if (points.length < 2 || !(slopeStepsPerMl > 0)) return false;
    pumpCal = {
      points: points.map((p) => ({ steps: p.steps, vol: p.vol })),
      slopeMlPerStep: 1 / slopeStepsPerMl,
      intercept: interceptMl,
      r2,
    };
    publishPumpCal();
    return true;
  },
};
