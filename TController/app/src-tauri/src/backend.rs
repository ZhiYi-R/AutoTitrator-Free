use std::fs;
use std::path::{Path, PathBuf};
use std::sync::{Arc, Mutex};
use std::time::{Duration, Instant};

use controller_core::processing::{PumpCalibration, Reconstructor};
use controller_core::protocol::{DownlinkCommand, Event, PortInfo, ProtocolHandler};
use controller_core::workflow::{PumpCommand, TitrationState, WorkflowEngine, WorkflowOutcome};
use serde::{Deserialize, Serialize};
use tauri::{AppHandle, Emitter};

const STATE_EVENT: &str = "backend://state";
const DEFAULT_PORT: &str = "COM3";
const DEFAULT_BAUD: u32 = 115_200;

#[derive(Debug, Clone, Serialize, Deserialize)]
#[serde(rename_all = "camelCase")]
pub struct DetectionParams {
    pub t1_deriv_threshold: f64,
    pub dose: f64,
    pub over_titrate: f64,
    pub consensus_tol: f64,
}

impl Default for DetectionParams {
    fn default() -> Self {
        Self {
            t1_deriv_threshold: 0.85,
            dose: 0.05,
            over_titrate: 0.8,
            consensus_tol: 0.15,
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize)]
#[serde(rename_all = "camelCase")]
pub struct CalPoint {
    pub steps: u32,
    pub vol: f64,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
#[serde(rename_all = "camelCase")]
pub struct HistoryRun {
    pub id: String,
    pub started_at: u64,
    pub duration_s: u64,
    pub sample_volume: f64,
    pub endpoint: Option<f64>,
    pub method: Option<String>,
    pub confidence: Option<String>,
    pub reliability: Option<String>,
    pub scenario: String,
    pub aborted: bool,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
#[serde(default, rename_all = "camelCase")]
pub struct BackendSettings {
    pub lang: String,
    pub theme: String,
    pub nav_collapsed: bool,
    pub watchdog_enabled: bool,
    pub detection: DetectionParams,
    pub history: Vec<HistoryRun>,
    pub port: String,
    pub baud: u32,
    pub sample_input: f64,
    pub tubing_p1: bool,
    pub tubing_p2: bool,
}

impl Default for BackendSettings {
    fn default() -> Self {
        Self {
            lang: "zh".into(),
            theme: "dark".into(),
            nav_collapsed: false,
            watchdog_enabled: true,
            detection: DetectionParams::default(),
            history: Vec::new(),
            port: DEFAULT_PORT.into(),
            baud: DEFAULT_BAUD,
            sample_input: 10.0,
            tubing_p1: true,
            tubing_p2: true,
        }
    }
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct KfSnapshot {
    pub volume: f64,
    pub std: f64,
    pub nis: f64,
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct EndpointSnapshot {
    pub stage: String,
    pub volume: f64,
    pub method: String,
    pub confidence: String,
    pub potential_volume: Option<f64>,
    pub spectral_volume: Option<f64>,
    pub reliability: String,
    pub kf: Option<KfSnapshot>,
    pub refined: Option<f64>,
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct PotentialPoint {
    pub v: f64,
    pub t: f64,
    pub e: f64,
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SpectrumFrame {
    pub v: f64,
    pub absorbance: Vec<f64>,
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct LogEntry {
    pub t: u64,
    pub level: String,
    pub text: String,
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct BackendSnapshot {
    pub version: String,
    pub ports: Vec<PortInfo>,
    pub connected: bool,
    pub connecting: bool,
    pub port: String,
    pub baud: u32,
    pub workflow: String,
    pub volume: f64,
    pub elapsed_ms: u64,
    pub sample_volume: f64,
    pub sample_input: f64,
    pub tubing_op: Option<String>,
    pub tubing_p1: bool,
    pub tubing_p2: bool,
    pub pump1_running: bool,
    pub pump2_running: bool,
    pub pump1_steps: u32,
    pub pump2_steps: u32,
    pub pump_slope: u32,
    pub pump_intercept: f64,
    pub pump_r2: Option<f64>,
    pub cal_points: Vec<CalPoint>,
    pub pot_points: Vec<PotentialPoint>,
    pub spectra: Vec<SpectrumFrame>,
    pub spectral_state: String,
    pub last_e: Option<f64>,
    pub last_deriv: Option<f64>,
    pub t1: Option<EndpointSnapshot>,
    pub final_result: Option<EndpointSnapshot>,
    pub watchdog_enabled: bool,
    pub detection: DetectionParams,
    pub rx: u64,
    pub tx: u64,
    pub bad_frames: u64,
    pub heartbeat_tick: u64,
    pub logs: Vec<LogEntry>,
    pub history: Vec<HistoryRun>,
    pub lang: String,
    pub theme: String,
    pub nav_collapsed: bool,
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct BackendInfo {
    pub version: String,
    pub calibre_found: bool,
    pub calibre_path: Option<String>,
    pub ports: Vec<PortInfo>,
}

#[derive(Debug, Clone, Deserialize)]
#[serde(rename_all = "camelCase")]
pub struct DetectionPatch {
    pub t1_deriv_threshold: Option<f64>,
    pub dose: Option<f64>,
    pub over_titrate: Option<f64>,
    pub consensus_tol: Option<f64>,
}

#[derive(Debug, Clone, Deserialize)]
#[serde(rename_all = "camelCase")]
pub struct UiSettingsPatch {
    pub lang: Option<String>,
    pub theme: Option<String>,
    pub nav_collapsed: Option<bool>,
}

#[derive(Debug, Clone, Deserialize)]
#[serde(rename_all = "camelCase")]
pub struct ApplyCalibrationRequest {
    pub points: Vec<CalPoint>,
    pub slope_steps_per_ml: f64,
    pub intercept_ml: f64,
    pub r2: Option<f64>,
}

pub struct BackendRuntime {
    handler: ProtocolHandler,
    workflow: WorkflowEngine,
    calibration: PumpCalibration,
    reconstructor: Option<Reconstructor>,
    settings_path: PathBuf,
    settings: BackendSettings,
    points: Vec<CalPoint>,
    pump_r2: Option<f64>,
    connected: bool,
    connecting: bool,
    port: String,
    baud: u32,
    sample_input: f64,
    tubing_op: Option<String>,
    tubing_p1: bool,
    tubing_p2: bool,
    pump1_running: bool,
    pump2_running: bool,
    pump1_steps: u32,
    pump2_steps: u32,
    volume: f64,
    elapsed_ms: u64,
    run_started: Option<Instant>,
    last_poll: Instant,
    last_heartbeat: Instant,
    last_e: Option<f64>,
    last_deriv: Option<f64>,
    spectral_state: String,
    pot_points: Vec<PotentialPoint>,
    spectra: Vec<SpectrumFrame>,
    t1: Option<EndpointSnapshot>,
    final_result: Option<EndpointSnapshot>,
    logs: Vec<LogEntry>,
    rx: u64,
    tx: u64,
    bad_frames: u64,
    heartbeat_tick: u64,
}

impl BackendRuntime {
    pub fn new() -> Self {
        let (reconstructor, calibre_path) = match Reconstructor::discover() {
            Ok((value, path)) => (Some(value), Some(path)),
            Err(_) => (None, None),
        };
        let settings_path = settings_path(calibre_path.as_deref());
        let settings: BackendSettings = load_json(&settings_path).unwrap_or_default();
        let mut calibration = calibre_path
            .as_deref()
            .map(|path| PumpCalibration::load_from(path, 2))
            .unwrap_or_default();
        let (mut points, mut pump_r2) = calibre_path
            .as_deref()
            .map(|path| PumpCalibration::load_points_from(path, 2))
            .unwrap_or_default();
        if let Some(sidecar) =
            load_json::<CalibrationSidecar>(&calibration_sidecar_path(&settings_path))
        {
            if sidecar.slope_ml_per_step > 0.0 {
                calibration = PumpCalibration {
                    slope: sidecar.slope_ml_per_step,
                    intercept: sidecar.intercept_ml,
                };
                points = sidecar
                    .points
                    .into_iter()
                    .map(|point| (point.steps, point.vol))
                    .collect();
                pump_r2 = sidecar.r2;
            }
        }
        let persisted_port = settings.port.clone();
        let persisted_baud = settings.baud;
        let persisted_sample_input = settings.sample_input;
        let persisted_tubing_p1 = settings.tubing_p1;
        let persisted_tubing_p2 = settings.tubing_p2;
        let workflow = WorkflowEngine::new(calibration.flow_rate(), calibration);
        Self {
            handler: ProtocolHandler::new(),
            workflow,
            calibration,
            reconstructor,
            settings_path,
            settings,
            points: points
                .into_iter()
                .map(|(steps, vol)| CalPoint { steps, vol })
                .collect(),
            pump_r2,
            connected: false,
            connecting: false,
            port: persisted_port,
            baud: persisted_baud,
            sample_input: persisted_sample_input,
            tubing_op: None,
            tubing_p1: persisted_tubing_p1,
            tubing_p2: persisted_tubing_p2,
            pump1_running: false,
            pump2_running: false,
            pump1_steps: 0,
            pump2_steps: 0,
            volume: 0.0,
            elapsed_ms: 0,
            run_started: None,
            last_poll: Instant::now(),
            last_heartbeat: Instant::now(),
            last_e: None,
            last_deriv: None,
            spectral_state: "IDLE".into(),
            pot_points: Vec::new(),
            spectra: Vec::new(),
            t1: None,
            final_result: None,
            logs: Vec::new(),
            rx: 0,
            tx: 0,
            bad_frames: 0,
            heartbeat_tick: 0,
        }
    }

    pub(crate) fn set_sample_input(&mut self, value: f64) {
        self.sample_input = value;
        self.settings.sample_input = value;
        self.save_settings();
    }

    fn save_settings(&self) {
        let _ = save_json(&self.settings_path, &self.settings);
    }

    pub(crate) fn set_tubing_pumps(&mut self, p1: bool, p2: bool) -> Result<(), String> {
        if !p1 && !p2 {
            return Err("至少选择一台泵".into());
        }
        if self.tubing_op.is_some() || self.workflow.can_manual_stop() {
            return Err("当前设备正忙".into());
        }
        self.tubing_p1 = p1;
        self.tubing_p2 = p2;
        self.settings.tubing_p1 = p1;
        self.settings.tubing_p2 = p2;
        self.save_settings();
        Ok(())
    }
    pub(crate) fn start_tubing(&mut self, op: &str) -> Result<(), String> {
        if !self.connected {
            return Err("请先连接设备".into());
        }
        if !matches!(op, "prime" | "empty") {
            return Err("未知管路操作".into());
        }
        if self.tubing_op.is_some() || self.workflow.can_manual_stop() {
            return Err("当前设备正忙".into());
        }
        let mut count = 0;
        if self.tubing_p1 {
            self.handler.send(DownlinkCommand::FreeRun(1));
            self.pump1_running = true;
            count += 1;
        }
        if self.tubing_p2 {
            self.handler.send(DownlinkCommand::FreeRun(2));
            self.pump2_running = true;
            count += 1;
        }
        if count == 0 {
            return Err("至少选择一台泵".into());
        }
        self.tx += count;
        self.tubing_op = Some(op.into());
        self.log(
            "info",
            format!("管路{}开始", if op == "prime" { "预充" } else { "排空" }),
        );
        Ok(())
    }

    pub(crate) fn stop_tubing(&mut self) {
        if self.tubing_op.is_none() {
            return;
        }
        self.handler.send(DownlinkCommand::FreeStop(0xff));
        self.tx += 1;
        self.pump1_running = false;
        self.pump2_running = false;
        self.tubing_op = None;
        self.log("ok", "管路操作已停止");
    }

    pub(crate) fn free_run(&mut self, pump: u8) -> Result<(), String> {
        self.check_manual_pump(pump)?;
        self.handler.send(DownlinkCommand::FreeRun(pump));
        self.tx += 1;
        self.set_pump_running(pump, true);
        self.log("info", format!("泵 {pump} 自由运行"));
        Ok(())
    }

    pub(crate) fn free_stop(&mut self, pump: u8) -> Result<(), String> {
        if !matches!(pump, 1 | 2 | 0xff) {
            return Err("泵编号无效".into());
        }
        self.handler.send(DownlinkCommand::FreeStop(pump));
        self.tx += 1;
        if pump == 0xff {
            self.pump1_running = false;
            self.pump2_running = false;
        } else {
            self.set_pump_running(pump, false);
        }
        self.log("info", format!("泵 {pump} 已停止"));
        Ok(())
    }

    pub(crate) fn jog(&mut self, pump: u8, steps: u32) -> Result<(), String> {
        self.check_manual_pump(pump)?;
        if steps == 0 {
            return Err("步数必须为正数".into());
        }
        let position = match pump {
            1 => self.pump1_steps.saturating_add(steps),
            2 => self.pump2_steps.saturating_add(steps),
            _ => return Err("泵编号无效".into()),
        };
        self.handler
            .send(DownlinkCommand::MaxCount { pump, count: steps });
        self.tx += 1;
        self.set_pump_position(pump, position);
        self.log("ok", format!("泵 {pump} 定步 {steps} 步"));
        Ok(())
    }

    fn check_manual_pump(&self, pump: u8) -> Result<(), String> {
        if !matches!(pump, 1 | 2) {
            return Err("泵编号无效".into());
        }
        if !self.connected {
            return Err("请先连接设备".into());
        }
        if self.tubing_op.is_some() || self.workflow.can_manual_stop() {
            return Err("当前设备正忙".into());
        }
        Ok(())
    }

    fn set_pump_running(&mut self, pump: u8, running: bool) {
        if pump == 1 {
            self.pump1_running = running;
        } else if pump == 2 {
            self.pump2_running = running;
        }
    }

    fn log(&mut self, level: &str, text: impl Into<String>) {
        self.logs.push(LogEntry {
            t: now_ms(),
            level: level.into(),
            text: text.into(),
        });
        if self.logs.len() > 400 {
            let excess = self.logs.len() - 400;
            self.logs.drain(0..excess);
        }
    }

    fn tick(&mut self) {
        let now = Instant::now();
        for event in self.handler.poll() {
            self.handle_event(event);
        }
        if self.connected && now.duration_since(self.last_heartbeat) >= Duration::from_secs(1) {
            self.handler.send_heartbeat();
            self.last_heartbeat = now;
            self.tx += 1;
        }
        if self.run_started.is_some() {
            self.elapsed_ms = now.duration_since(self.run_started.unwrap()).as_millis() as u64;
        }
        if now.duration_since(self.last_poll) >= Duration::from_millis(500) {
            self.last_poll = now;
            let outcome = self.workflow.poll();
            self.apply_outcome(outcome);
        }
    }

    fn handle_event(&mut self, event: Event) {
        match event {
            Event::Connected => {
                self.connected = true;
                self.connecting = false;
                self.log("ok", format!("已连接到 {}", self.port));
                self.settings_path_parent_save();
            }
            Event::Disconnected => {
                self.connected = false;
                self.connecting = false;
                self.pump1_running = false;
                self.pump2_running = false;
                self.log("warn", "连接已断开");
            }
            Event::Error(text) => {
                self.connected = false;
                self.connecting = false;
                self.bad_frames += 1;
                self.log("error", text);
            }
            Event::Ack(_) => {
                self.rx += 1;
            }
            Event::Nak(_) => {
                self.rx += 1;
                self.log("warn", "设备拒绝命令");
            }
            Event::PumpPos { pump, position } => self.set_pump_position(pump, position),
            Event::PumpDone { pump, position } => {
                self.set_pump_position(pump, position);
                let outcome = self.workflow.on_pump_done(pump);
                self.apply_outcome(outcome);
            }
            Event::Adc { value, position } => {
                self.rx += 1;
                self.set_pump_position(2, position);
                let voltage = value as f64 * 3.3 / 65535.0 - 1.1;
                self.last_e = Some(voltage);
                let t = self
                    .run_started
                    .map(|start| start.elapsed().as_secs_f64())
                    .unwrap_or(0.0);
                self.pot_points.push(PotentialPoint {
                    v: self.volume,
                    t,
                    e: voltage,
                });
                if self.pot_points.len() > 6000 {
                    let excess = self.pot_points.len() - 6000;
                    self.pot_points.drain(0..excess);
                }
                self.workflow.on_adc(position, t, voltage);
            }
            Event::Spectral(values) => {
                self.rx += 1;
                let raw: Vec<f64> = values.iter().map(|v| *v as f64).collect();
                let spectrum = self
                    .reconstructor
                    .as_ref()
                    .and_then(|reconstructor| reconstructor.reconstruct(&raw).ok())
                    .map(|(_, values)| downsample_spectrum(&values))
                    .unwrap_or_else(|| raw.clone());
                self.spectra.push(SpectrumFrame {
                    v: self.volume,
                    absorbance: spectrum.clone(),
                });
                if self.spectra.len() > 2000 {
                    let excess = self.spectra.len() - 2000;
                    self.spectra.drain(0..excess);
                }
                self.workflow.on_spectrum(&raw);
            }
            Event::Heartbeat(uptime) => {
                self.heartbeat_tick = uptime as u64;
                self.rx += 1;
            }
        }
    }

    fn set_pump_position(&mut self, pump: u8, position: u32) {
        if pump == 1 {
            self.pump1_steps = position;
        } else if pump == 2 {
            self.pump2_steps = position;
            self.volume = self.calibration.volume_from_steps(position).max(0.0);
        }
    }

    fn apply_outcome(&mut self, outcome: WorkflowOutcome) {
        self.set_workflow(outcome.state);
        for command in outcome.commands {
            self.send_pump_command(command);
        }
        if let Some(result) = outcome.detection {
            let snapshot = endpoint_snapshot("t1", &result, None);
            if outcome.first_endpoint.is_some() {
                self.t1 = Some(snapshot);
            }
        }
        if let Some(volume) = outcome.refined_endpoint {
            if let Some(result) = self.t1.as_ref() {
                self.final_result = Some(EndpointSnapshot {
                    stage: "final".into(),
                    volume,
                    method: result.method.clone(),
                    confidence: result.confidence.clone(),
                    potential_volume: result.potential_volume,
                    spectral_volume: result.spectral_volume,
                    reliability: result.reliability.clone(),
                    kf: result.kf.clone(),
                    refined: Some(volume),
                });
            }
            self.pump2_running = false;
            self.persist_history(false);
        }
    }

    fn set_workflow(&mut self, state: TitrationState) {
        self.pump1_running = matches!(state, TitrationState::Injecting);
        self.pump2_running = matches!(
            state,
            TitrationState::Titrating | TitrationState::Degree1 | TitrationState::Titrating2
        );
        if matches!(
            state,
            TitrationState::Idle | TitrationState::Done | TitrationState::Error
        ) {
            self.pump1_running = false;
            self.pump2_running = false;
        }
    }

    fn send_pump_command(&mut self, command: PumpCommand) {
        let downlink: DownlinkCommand = command.into();
        self.handler.send(downlink);
        self.tx += 1;
    }

    pub(crate) fn start(&mut self) -> Result<(), String> {
        if !self.connected {
            return Err("请先连接设备".into());
        }
        self.clear_run();
        self.run_started = Some(Instant::now());
        let outcome = self.workflow.start(self.sample_input);
        self.apply_outcome(outcome);
        self.log("info", format!("开始滴定，样品 {} mL", self.sample_input));
        Ok(())
    }

    fn clear_run(&mut self) {
        self.elapsed_ms = 0;
        self.volume = 0.0;
        self.pump1_steps = 0;
        self.pump2_steps = 0;
        self.pot_points.clear();
        self.spectra.clear();
        self.t1 = None;
        self.final_result = None;
        self.last_e = None;
        self.last_deriv = None;
        self.spectral_state = "IDLE".into();
        self.run_started = None;
        let outcome = self.workflow.abort();
        self.apply_outcome(outcome);
    }

    pub(crate) fn manual_stop(&mut self) {
        let outcome = self.workflow.manual_stop();
        self.apply_outcome(outcome);
        self.run_started = None;
        self.log("warn", "手动停止");
    }

    pub(crate) fn abort(&mut self) {
        let was_running = self.workflow.can_manual_stop();
        if self.connected {
            self.send_pump_command(PumpCommand::FreeStop(0xff));
        }
        let outcome = self.workflow.abort();
        self.apply_outcome(outcome);
        self.tubing_op = None;
        self.run_started = None;
        if was_running {
            self.persist_history(true);
        }
        self.log("warn", "用户中止，全泵停止");
    }

    pub(crate) fn reset(&mut self) {
        if self.connected {
            self.handler.send(DownlinkCommand::Reset);
            self.tx += 1;
        }
        self.clear_run();
        self.tubing_op = None;
        self.log("info", "设备已复位");
    }

    fn persist_history(&mut self, aborted: bool) {
        let id = format!("{}", now_ms());
        self.settings.history.insert(
            0,
            HistoryRun {
                id,
                started_at: now_ms(),
                duration_s: self.elapsed_ms / 1000,
                sample_volume: self.sample_input,
                endpoint: self
                    .final_result
                    .as_ref()
                    .map(|result| result.volume)
                    .or_else(|| self.t1.as_ref().map(|result| result.volume)),
                method: self
                    .final_result
                    .as_ref()
                    .map(|result| result.method.clone()),
                confidence: self
                    .final_result
                    .as_ref()
                    .map(|result| result.confidence.clone()),
                reliability: self
                    .final_result
                    .as_ref()
                    .map(|result| result.reliability.clone()),
                scenario: "normal".into(),
                aborted,
            },
        );
        self.settings.history.truncate(30);
        self.save_settings();
    }

    fn settings_path_parent_save(&self) {
        self.save_settings();
    }

    pub(crate) fn snapshot(&self) -> BackendSnapshot {
        BackendSnapshot {
            version: controller_core::VERSION.into(),
            ports: controller_core::protocol::list_ports(),
            connected: self.connected,
            connecting: self.connecting,
            port: self.port.clone(),
            baud: self.baud,
            workflow: workflow_name(self.workflow.state),
            volume: self.volume,
            elapsed_ms: self.elapsed_ms,
            sample_volume: self.sample_input,
            sample_input: self.sample_input,
            tubing_op: self.tubing_op.clone(),
            tubing_p1: self.tubing_p1,
            tubing_p2: self.tubing_p2,
            pump1_running: self.pump1_running,
            pump2_running: self.pump2_running,
            pump1_steps: self.pump1_steps,
            pump2_steps: self.pump2_steps,
            pump_slope: if self.calibration.slope > 0.0 {
                (1.0 / self.calibration.slope).round() as u32
            } else {
                0
            },
            pump_intercept: self.calibration.intercept,
            pump_r2: self.pump_r2,
            cal_points: self.points.clone(),
            pot_points: self.pot_points.clone(),
            spectra: self.spectra.clone(),
            spectral_state: self.spectral_state.clone(),
            last_e: self.last_e,
            last_deriv: self.last_deriv,
            t1: self.t1.clone(),
            final_result: self.final_result.clone(),
            watchdog_enabled: self.settings.watchdog_enabled,
            detection: self.settings.detection.clone(),
            rx: self.rx,
            tx: self.tx,
            bad_frames: self.bad_frames,
            heartbeat_tick: self.heartbeat_tick,
            logs: self.logs.clone(),
            history: self.settings.history.clone(),
            lang: self.settings.lang.clone(),
            theme: self.settings.theme.clone(),
            nav_collapsed: self.settings.nav_collapsed,
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize)]
#[serde(rename_all = "camelCase")]
struct CalibrationSidecar {
    points: Vec<CalPoint>,
    slope_ml_per_step: f64,
    intercept_ml: f64,
    r2: Option<f64>,
}

pub fn run_event_loop(app: AppHandle, state: Arc<Mutex<BackendRuntime>>) {
    std::thread::spawn(move || loop {
        let snapshot = {
            let Ok(mut runtime) = state.lock() else { break };
            runtime.tick();
            runtime.snapshot()
        };
        let _ = app.emit(STATE_EVENT, snapshot);
        std::thread::sleep(Duration::from_millis(50));
    });
}

pub fn emit_snapshot(app: &AppHandle, state: &Mutex<BackendRuntime>) {
    if let Ok(runtime) = state.lock() {
        let _ = app.emit(STATE_EVENT, runtime.snapshot());
    }
}

pub fn backend_info() -> BackendInfo {
    let (calibre_found, calibre_path) = match Reconstructor::discover() {
        Ok((_, path)) => (true, Some(path.display().to_string())),
        Err(_) => (false, None),
    };
    BackendInfo {
        version: controller_core::VERSION.into(),
        calibre_found,
        calibre_path,
        ports: controller_core::protocol::list_ports(),
    }
}

pub fn connect(runtime: &mut BackendRuntime, port: String, baud: u32) {
    runtime.port = port.clone();
    runtime.baud = baud;
    runtime.settings.port = port;
    runtime.settings.baud = baud;
    runtime.save_settings();
    runtime.connecting = true;
    runtime.handler.connect(&runtime.port, runtime.baud);
}

pub fn disconnect(runtime: &mut BackendRuntime) {
    runtime.handler.disconnect();
    runtime.connected = false;
    runtime.connecting = false;
}

pub fn set_detection(runtime: &mut BackendRuntime, patch: DetectionPatch) {
    let detection = &mut runtime.settings.detection;
    if let Some(value) = patch.t1_deriv_threshold {
        detection.t1_deriv_threshold = value;
    }
    if let Some(value) = patch.dose {
        detection.dose = value;
    }
    if let Some(value) = patch.over_titrate {
        detection.over_titrate = value;
    }
    if let Some(value) = patch.consensus_tol {
        detection.consensus_tol = value;
    }
    runtime.save_settings();
}

pub fn set_ui_settings(runtime: &mut BackendRuntime, patch: UiSettingsPatch) {
    if let Some(value) = patch.lang {
        runtime.settings.lang = value;
    }
    if let Some(value) = patch.theme {
        runtime.settings.theme = value;
    }
    if let Some(value) = patch.nav_collapsed {
        runtime.settings.nav_collapsed = value;
    }
    runtime.save_settings();
}

pub fn set_watchdog(runtime: &mut BackendRuntime, enabled: bool) {
    runtime.settings.watchdog_enabled = enabled;
    runtime.save_settings();
    if enabled && runtime.connected {
        runtime.handler.send_heartbeat();
        runtime.tx += 1;
    }
}

pub fn apply_calibration(
    runtime: &mut BackendRuntime,
    request: ApplyCalibrationRequest,
) -> Result<(), String> {
    if request.points.len() < 2
        || request.slope_steps_per_ml <= 0.0
        || !request.intercept_ml.is_finite()
    {
        return Err("标定参数无效".into());
    }
    runtime.calibration = PumpCalibration {
        slope: 1.0 / request.slope_steps_per_ml,
        intercept: request.intercept_ml,
    };
    runtime.workflow = WorkflowEngine::new(runtime.calibration.flow_rate(), runtime.calibration);
    runtime.points = request.points;
    runtime.pump_r2 = request.r2;
    let sidecar = CalibrationSidecar {
        points: runtime.points.clone(),
        slope_ml_per_step: runtime.calibration.slope,
        intercept_ml: runtime.calibration.intercept,
        r2: runtime.pump_r2,
    };
    save_json(&calibration_sidecar_path(&runtime.settings_path), &sidecar)
        .map_err(|error| error.to_string())
}

pub fn workflow_name(state: TitrationState) -> String {
    match state {
        TitrationState::Idle => "idle",
        TitrationState::Injecting => "injecting",
        TitrationState::Titrating => "titrating",
        TitrationState::Degree1 => "degree1",
        TitrationState::Titrating2 => "titrating2",
        TitrationState::Done => "done",
        TitrationState::Error => "error",
    }
    .into()
}

fn endpoint_snapshot(
    stage: &str,
    result: &controller_core::processing::EndpointResult,
    refined: Option<f64>,
) -> EndpointSnapshot {
    let method = match result.method {
        controller_core::processing::Method::Consensus => "consensus",
        controller_core::processing::Method::PotentialOnly => "potential_only",
        controller_core::processing::Method::SpectralOnly => "spectral_only",
        controller_core::processing::Method::Conflict => "conflict",
    };
    let confidence = match result.confidence {
        controller_core::processing::Confidence::High => "high",
        controller_core::processing::Confidence::Medium => "medium",
        controller_core::processing::Confidence::Low => "low",
    };
    let potential_volume = result.potential.as_ref().map(|value| value.volume);
    let spectral_volume = result.spectral.as_ref().map(|value| value.volume);
    let kf = result
        .reliability
        .endpoint_std
        .zip(result.reliability.nis)
        .map(|(std, nis)| KfSnapshot {
            volume: result.volume,
            std,
            nis,
        });
    EndpointSnapshot {
        stage: stage.into(),
        volume: result.volume,
        method: method.into(),
        confidence: confidence.into(),
        potential_volume,
        spectral_volume,
        reliability: result.reliability.status.clone(),
        kf,
        refined,
    }
}

fn downsample_spectrum(values: &[f64]) -> Vec<f64> {
    if values.len() <= 61 {
        return values.to_vec();
    }
    (0..61)
        .map(|index| {
            let source = index * (values.len() - 1) / 60;
            values[source]
        })
        .collect()
}

fn now_ms() -> u64 {
    std::time::SystemTime::now()
        .duration_since(std::time::UNIX_EPOCH)
        .unwrap_or_default()
        .as_millis() as u64
}

fn settings_path(calibre_path: Option<&Path>) -> PathBuf {
    calibre_path
        .and_then(Path::parent)
        .map(|path| path.join("settings.json"))
        .or_else(|| {
            std::env::current_exe()
                .ok()
                .and_then(|path| path.parent().map(|parent| parent.join("settings.json")))
        })
        .unwrap_or_else(|| PathBuf::from("settings.json"))
}

fn calibration_sidecar_path(settings_path: &Path) -> PathBuf {
    settings_path.with_file_name("pump2_calibration.json")
}

fn load_json<T: for<'de> Deserialize<'de>>(path: &Path) -> Option<T> {
    fs::read_to_string(path)
        .ok()
        .and_then(|text| serde_json::from_str(&text).ok())
}

fn save_json<T: Serialize>(path: &Path, value: &T) -> std::io::Result<()> {
    if let Some(parent) = path.parent() {
        fs::create_dir_all(parent)?;
    }
    let text = serde_json::to_string_pretty(value).map_err(std::io::Error::other)?;
    fs::write(path, text)
}

pub type SharedBackend = Arc<Mutex<BackendRuntime>>;
