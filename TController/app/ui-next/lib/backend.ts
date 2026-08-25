import type { CalPoint, SerialPortInfo, TubingOp } from "@/lib/types";

export interface BackendSnapshot {
  version: string;
  ports: SerialPortInfo[];
  connected: boolean;
  connecting: boolean;
  port: string;
  baud: number;
  workflow: string;
  volume: number;
  elapsedMs: number;
  sampleVolume: number;
  sampleInput: number;
  tubingOp: TubingOp | null;
  tubingP1: boolean;
  tubingP2: boolean;
  pump1Running: boolean;
  pump2Running: boolean;
  pump1Steps: number;
  pump2Steps: number;
  pumpSlope: number;
  pumpIntercept: number;
  pumpR2: number | null;
  calPoints: CalPoint[];
  potPoints: Array<{ v: number; t: number; e: number }>;
  spectra: Array<{ v: number; absorbance: number[] }>;
  spectralState: string;
  lastE: number | null;
  lastDeriv: number | null;
  t1: RawEndpoint | null;
  finalResult: RawEndpoint | null;
  watchdogEnabled: boolean;
  detection: {
    t1DerivThreshold: number;
    dose: number;
    overTitrate: number;
    consensusTol: number;
  };
  rx: number;
  tx: number;
  badFrames: number;
  heartbeatTick: number;
  logs: Array<{ t: number; level: string; text: string }>;
  history: Array<{
    id: string;
    startedAt: number;
    durationS: number;
    sampleVolume: number;
    endpoint: number | null;
    method: string | null;
    confidence: string | null;
    reliability: string | null;
    scenario: string;
    aborted: boolean;
  }>;
  lang: "zh" | "en";
  theme: string;
  navCollapsed: boolean;
}

interface RawEndpoint {
  stage: "t1" | "final" | string;
  volume: number;
  method: string;
  confidence: string;
  potentialVolume: number | null;
  spectralVolume: number | null;
  reliability: string;
  kf: { volume: number; std: number; nis: number } | null;
  refined: number | null;
}

type TauriApi = {
  core?: { invoke: (command: string, args?: Record<string, unknown>) => Promise<unknown> };
  event?: { listen: (event: string, handler: (event: { payload: unknown }) => void) => Promise<() => void> };
};

function tauriApi(): TauriApi | null {
  return (globalThis as { __TAURI__?: TauriApi }).__TAURI__ ?? null;
}

function isTauriRuntime() {
  const api = tauriApi();
  return Boolean(api?.core?.invoke && api.event?.listen);
}

function invoke<T>(command: string, args?: Record<string, unknown>): Promise<T> {
  const api = tauriApi();
  if (!api?.core?.invoke) return Promise.reject(new Error("Tauri backend unavailable"));
  return api.core.invoke(command, args) as Promise<T>;
}

async function applySnapshot(snapshot: BackendSnapshot) {
  const { applyBackendSnapshot } = await import("@/lib/store");
  applyBackendSnapshot(snapshot);
}

let mockPromise: Promise<typeof import("@/lib/mock/simulator")> | null = null;
function mock() {
  mockPromise ??= import("@/lib/mock/simulator");
  return mockPromise;
}

let initialized = false;
let unlisten: (() => void) | null = null;

async function initialize() {
  if (initialized) return;
  initialized = true;
  if (isTauriRuntime()) {
    const runtimeApi = tauriApi();
    if (!runtimeApi?.event?.listen) return;
    unlisten = await runtimeApi.event.listen("backend://state", (event) => {
      void applySnapshot(event.payload as BackendSnapshot);
    });
    const snapshot = await invoke<BackendSnapshot>("backend_state");
    await applySnapshot(snapshot);
    return;
  }
  await (await mock()).backend.loadPumpCalibration();
}

async function callMock(method: keyof (typeof import("@/lib/mock/simulator"))["backend"], ...args: unknown[]) {
  const mod = await mock();
  const fn = mod.backend[method] as (...values: unknown[]) => unknown;
  return fn.apply(mod.backend, args);
}

export const backend = {
  initialize,
  connect: async () => {
    if (isTauriRuntime()) {
      const state = (await import("@/lib/store")).useStore.getState();
      await invoke("connect", { port: state.port, baud: state.baud });
    } else {
      await callMock("connect");
    }
  },
  disconnect: async () => {
    if (isTauriRuntime()) await invoke("disconnect");
    else await callMock("disconnect");
  },
  setSampleInput: async (value: number) => {
    if (isTauriRuntime()) await invoke("set_sample_input", { value });
    else await callMock("retune");
  },
  start: async () => {
    if (isTauriRuntime()) await invoke("start_titration");
    else await callMock("start");
  },
  manualStop: async () => {
    if (isTauriRuntime()) await invoke("manual_stop");
    else await callMock("manualStop");
  },
  abort: async () => {
    if (isTauriRuntime()) await invoke("abort");
    else await callMock("abort");
  },
  reset: async () => {
    if (isTauriRuntime()) await invoke("reset");
    else {
      const store = (await import("@/lib/store")).useStore;
      store.setState({ workflow: "idle", volume: 0, elapsedMs: 0, potPoints: [], spectra: [], spectralState: "IDLE", lastE: null, lastDeriv: null, t1: null, final: null });
    }
  },
  startTubing: async (op: TubingOp) => {
    if (isTauriRuntime()) await invoke("start_tubing", { op });
    else await callMock("startTubing", op);
  },
  stopTubing: async () => {
    if (isTauriRuntime()) await invoke("stop_tubing");
    else await callMock("stopTubing");
  },
  freeRun: async (pump: 1 | 2) => {
    if (isTauriRuntime()) await invoke("free_run", { pump });
    else await callMock("freeRun", pump);
  },
  freeStop: async (pump: 1 | 2) => {
    if (isTauriRuntime()) await invoke("free_stop", { pump });
    else await callMock("freeStop", pump);
  },
  jog: async (pump: 1 | 2, steps: number) => {
    if (isTauriRuntime()) await invoke("jog", { pump, steps });
    else await callMock("jog", pump, steps);
  },
  loadPumpCalibration: async () => {
    if (isTauriRuntime()) {
      await applySnapshot(await invoke<BackendSnapshot>("backend_state"));
    } else {
      await callMock("loadPumpCalibration");
    }
  },
  applyPumpCalibration: async (points: CalPoint[], slopeStepsPerMl: number, interceptMl = 0, r2: number | null = null) => {
    if (isTauriRuntime()) {
      await invoke("apply_pump_calibration", {
        request: {
          points,
          slopeStepsPerMl,
          interceptMl,
          r2,
        },
      });
      return true;
    }
    return Boolean(await callMock("applyPumpCalibration", points, slopeStepsPerMl, interceptMl, r2));
  },
  setWatchdog: async (enabled: boolean) => {
    if (isTauriRuntime()) await invoke("set_watchdog", { enabled });
    else await callMock("retune");
  },
  setDetection: async (patch: Record<string, number>) => {
    if (isTauriRuntime()) await invoke("set_detection", { patch });
    else await callMock("retune");
  },
  setUiSettings: async (patch: Record<string, unknown>) => {
    if (isTauriRuntime()) await invoke("set_ui_settings", { patch });
    else await callMock("retune");
  },
  setTubingPumps: async (p1: boolean, p2: boolean) => {
    if (isTauriRuntime()) {
      await invoke("set_tubing_pumps", { p1, p2 });
    } else {
      const store = (await import("@/lib/store")).useStore;
      store.setState({ tubingP1: p1, tubingP2: p2 });
    }
  },
  dispose: () => {
    unlisten?.();
    unlisten = null;
    initialized = false;
  },
};
