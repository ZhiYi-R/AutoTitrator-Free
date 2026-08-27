use chrono::Local;
use std::fs::{self, File, OpenOptions};
use std::io::BufWriter;
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
    /// 实验数据（运行 CSV/导出）保存目录
    pub data_dir: String,
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
            data_dir: "D:\\AutoTitrator\\Data".into(),
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
    /// 检测器当前谱对基线的 D_JS（nats）——判据真值，前端直接绘制
    pub js: Option<f64>,
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
    pub data_dir: String,
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

/// 单次运行的流式 CSV 写入器：按阶段/模态拆四个文件，逐帧追加落盘，
/// 故障时已写行不受内存状态影响。列格式与 `replay_csv` 兼容：
/// 电位 `volume_mL,time_s,potential_V,dE_dV`；光谱 `volume_mL,time_s,ch0..ch9`。
struct RunCsvWriters {
    dir: PathBuf,
    intake_pot: Option<BufWriter<File>>,
    intake_spec: Option<BufWriter<File>>,
    titr_pot: Option<BufWriter<File>>,
    titr_spec: Option<BufWriter<File>>,
}

const SPECTRUM_HEADER: &str = "volume_mL,time_s,ch0,ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9";
const POTENTIAL_HEADER: &str = "volume_mL,time_s,potential_V,dE_dV";

impl RunCsvWriters {
    fn new(dir: PathBuf) -> Self {
        Self {
            dir,
            intake_pot: None,
            intake_spec: None,
            titr_pot: None,
            titr_spec: None,
        }
    }

    /// 惰性打开对应阶段/模态的流；空文件补表头（追加模式不重复表头）。
    fn stream(&mut self, intake: bool, spectral: bool) -> std::io::Result<&mut BufWriter<File>> {
        let (slot, file_name, desc, header) = match (intake, spectral) {
            (true, false) => (
                &mut self.intake_pot,
                "IntakingPotential.csv",
                "电位数据（进样阶段）",
                POTENTIAL_HEADER,
            ),
            (false, false) => (
                &mut self.titr_pot,
                "TitratingPotential.csv",
                "电位数据（滴定阶段）",
                POTENTIAL_HEADER,
            ),
            (true, true) => (
                &mut self.intake_spec,
                "IntakingSpectrum.csv",
                "光谱原始数据（进样阶段）",
                SPECTRUM_HEADER,
            ),
            (false, true) => (
                &mut self.titr_spec,
                "TitratingSpectrum.csv",
                "光谱原始数据（滴定阶段）",
                SPECTRUM_HEADER,
            ),
        };
        if slot.is_none() {
            /* 目录缺失时自愈（运行中被清理/盘符变更等） */
            fs::create_dir_all(&self.dir)?;
            let path = self.dir.join(file_name);
            let file = OpenOptions::new().create(true).append(true).open(&path)?;
            let mut writer = BufWriter::new(file);
            if writer.get_ref().metadata()?.len() == 0 {
                use std::io::Write as _;
                writeln!(writer, "# AutoTitrator {desc}")?;
                writeln!(writer, "# 数据目录: {}", self.dir.file_name().unwrap_or_default().to_string_lossy())?;
                writeln!(writer, "{header}")?;
            }
            *slot = Some(writer);
        }
        Ok(slot.as_mut().expect("slot 刚初始化"))
    }

    fn append_potential(&mut self, intake: bool, t: f64, v: f64, e: f64, deriv: f64) -> std::io::Result<()> {
        use std::io::Write as _;
        writeln!(
            self.stream(intake, false)?,
            "{v:.6},{t:.3},{e:.6},{deriv:.6}"
        )
    }

    fn append_spectrum(&mut self, intake: bool, t: f64, v: f64, raw: &[u16; 10]) -> std::io::Result<()> {
        use std::io::Write as _;
        let writer = self.stream(intake, true)?;
        write!(writer, "{v:.6},{t:.3}")?;
        for value in raw {
            write!(writer, ",{value}")?;
        }
        writeln!(writer)
    }

    fn flush_all(&mut self) {
        use std::io::Write as _;
        for writer in [&mut self.intake_pot, &mut self.intake_spec, &mut self.titr_pot, &mut self.titr_spec]
            .into_iter()
            .flatten()
        {
            let _ = writer.flush();
        }
    }
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
    pub data_dir: Option<String>,
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
    pot_points: Vec<PotentialPoint>,
    spectra: Vec<SpectrumFrame>,
    /// 本次运行的流式实验数据写入器；None = 不落盘（未配置路径/写入失败停写）
    csv_writers: Option<RunCsvWriters>,
    /// 注入看门狗：上次泵 1 位置与无进度起始时刻
    last_inject_pos: u32,
    inject_stall_since: Option<Instant>,
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
            pot_points: Vec::new(),
            spectra: Vec::new(),
            csv_writers: None,
            last_inject_pos: 0,
            inject_stall_since: None,
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

    /// 运行开始：在数据目录下建本次运行的 Exp-{日期}-{时间} 目录。
    fn open_run_data(&mut self) {
        if self.settings.data_dir.trim().is_empty() {
            self.log("warn", "未配置数据保存路径，本次运行数据不落盘");
            return;
        }
        let dir = Path::new(self.settings.data_dir.trim())
            .join(Local::now().format("Exp-%Y-%m-%d-%H%M%S").to_string());
        match fs::create_dir_all(&dir) {
            Ok(()) => {
                self.csv_writers = Some(RunCsvWriters::new(dir.clone()));
                self.log("info", format!("运行数据目录：{}", dir.display()));
            }
            Err(e) => self.log("error", format!("创建数据目录失败：{e}")),
        }
    }

    /// 运行结束（完成/中止/复位）：冲刷并关闭全部流。
    fn close_run_data(&mut self) {
        if let Some(mut writers) = self.csv_writers.take() {
            writers.flush_all();
            self.log("ok", format!("运行数据已写入 {}", writers.dir.display()));
        }
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
        if let Some(start) = self.run_started {
            self.elapsed_ms = now.duration_since(start).as_millis() as u64;
        }
        if now.duration_since(self.last_poll) >= Duration::from_millis(500) {
            self.last_poll = now;
            let outcome = self.workflow.poll();
            self.apply_outcome(outcome);
        }
        /* 注入看门狗：进样中泵 1 位置 20s 无进度（上行帧无重传，PumpDone
           丢失会让工作流永久卡在 Injecting）→ 判定堵转/失联并急停 */
        if self.workflow.state == TitrationState::Injecting && self.pump1_running {
            if self.pump1_steps != self.last_inject_pos {
                self.last_inject_pos = self.pump1_steps;
                self.inject_stall_since = None;
            } else {
                let since = *self.inject_stall_since.get_or_insert(now);
                if now.duration_since(since) >= Duration::from_secs(20) {
                    self.inject_stall_since = None;
                    if self.connected {
                        self.send_pump_command(PumpCommand::FreeStop(0xff));
                    }
                    let mut outcome = self.workflow.abort();
                    outcome.state = TitrationState::Error;
                    self.apply_outcome(outcome);
                    self.run_started = None;
                    self.persist_history(true);
                    self.log("error", "进样泵 20s 无进度，疑似堵转或通信丢失，已急停");
                }
            }
        } else {
            self.inject_stall_since = None;
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
                /* 仅运行期间入列：待机/连接空闲的采样只更新 last_e，
                   否则 v=0 的噪声点会堆积并污染曲线起点 */
                if self.run_started.is_some() {
                    self.pot_points.push(PotentialPoint {
                        v: self.volume,
                        t,
                        e: voltage,
                    });
                    if self.pot_points.len() > 6000 {
                        let excess = self.pot_points.len() - 6000;
                        self.pot_points.drain(0..excess);
                    }
                    /* 流式 CSV：进样/滴定分文件，逐帧落盘 */
                    if let Some(w) = self.csv_writers.as_mut() {
                        let intake = self.workflow.state == TitrationState::Injecting;
                        let deriv = self.workflow.detector.last_potential_derivative();
                        if w.append_potential(intake, t, self.volume, voltage, deriv).is_err() {
                            self.csv_writers = None;
                            self.log("error", "运行数据写入失败，本次运行停写（盘满或目录不可用）");
                        }
                    }
                }
                /* 同理：进样期是残留零点、管路期是冲洗量——都不进检测器/运行体积 */
                if self.workflow.state != TitrationState::Injecting && self.tubing_op.is_none() {
                    self.workflow.on_adc(position, t, voltage);
                }
            }
            Event::Spectral(values) => {
                self.rx += 1;
                let raw: Vec<f64> = values.iter().map(|v| *v as f64).collect();
                /* 检测与判据统一用 721 点完整重建谱（信息完整，见 reconstructor）；
                   重建器缺席（calibre 未部署）回退原始 10 通道 */
                let reconstructed = self
                    .reconstructor
                    .as_ref()
                    .and_then(|reconstructor| reconstructor.reconstruct(&raw).ok())
                    .map(|(_, values)| values);
                let detection_input = reconstructed.clone().unwrap_or_else(|| raw.clone());
                /* 展示谱仅降采样（61 点 UI 网格），纯显示格式化 */
                let display = reconstructed
                    .as_ref()
                    .map(|values| downsample_spectrum(values))
                    .unwrap_or_else(|| raw.clone());
                /* 检测判据：721 点完整重建谱 */
                self.workflow.on_spectrum(&detection_input);
                if self.run_started.is_some() {
                    let js_base =
                        self.workflow.detector.diagnostics().spectral_features.js_base;
                    self.spectra.push(SpectrumFrame {
                        v: self.volume,
                        absorbance: display,
                        js: Some(js_base),
                    });
                    if self.spectra.len() > 2000 {
                        let excess = self.spectra.len() - 2000;
                        self.spectra.drain(0..excess);
                    }
                    /* 流式 CSV：原始 10 通道（测量真值，回放工具输入格式） */
                    if let Some(w) = self.csv_writers.as_mut() {
                        let intake = self.workflow.state == TitrationState::Injecting;
                        let t = self
                            .run_started
                            .map(|start| start.elapsed().as_secs_f64())
                            .unwrap_or(0.0);
                        if w.append_spectrum(intake, t, self.volume, &values).is_err() {
                            self.csv_writers = None;
                            self.log("error", "运行数据写入失败，本次运行停写（盘满或目录不可用）");
                        }
                    }
                }
            }
            Event::Heartbeat(uptime) => {
                /* 固件上报 uptime_ms；统一为秒计数（mock 同语义） */
                self.heartbeat_tick = uptime as u64 / 1000;
                self.rx += 1;
            }
        }
    }

    fn set_pump_position(&mut self, pump: u8, position: u32) {
        if pump == 1 {
            self.pump1_steps = position;
        } else if pump == 2 {
            /* 进样/管路作业期间泵 2 静止或在做预充——上报计数不是本次滴定的
               体积零点，运行体积账户冻结（原始步数照记，供管路已排体积显示）：
               - Injecting：上报的是上次运行的残留计数
               - 管路作业：排出的是预充/排空冲洗量，不属于滴定剂体积 */
            if self.workflow.state == TitrationState::Injecting || self.tubing_op.is_some() {
                return;
            }
            self.pump2_steps = position;
            self.volume = self.calibration.volume_from_steps(position).max(0.0);
        }
    }

    fn apply_outcome(&mut self, outcome: WorkflowOutcome) {
        self.set_workflow(outcome.state);
        for command in outcome.commands {
            self.send_pump_command(command);
        }
        /* 运行终结（完成/故障）：冲刷关闭本次实验数据流 */
        if matches!(outcome.state, TitrationState::Done | TitrationState::Error) {
            self.close_run_data();
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
        if self.tubing_op.is_some() {
            return Err("管路作业进行中".into());
        }
        if self.workflow.can_manual_stop() {
            return Err("滴定进行中".into());
        }
        self.clear_run();
        self.open_run_data();
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
        self.run_started = None;
        self.last_inject_pos = 0;
        self.inject_stall_since = None;
        /* 复位/重开前收尾遗留写入器（正常路径已关闭，此处兜底） */
        self.close_run_data();
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
        /* 中止保留已写行：冲刷关闭，数据停在断点 */
        self.close_run_data();
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
            /* 诊断字段从检测器现算，避免快照字段与引擎内部状态脱节 */
            spectral_state: self.workflow.detector.spectral_state().as_str().into(),
            last_e: self.last_e,
            last_deriv: Some(self.workflow.detector.last_potential_derivative()),
            t1: self.t1.clone(),
            final_result: self.final_result.clone(),
            watchdog_enabled: self.settings.watchdog_enabled,
            detection: self.settings.detection.clone(),
            data_dir: self.settings.data_dir.clone(),
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
    if let Some(value) = patch.data_dir {
        runtime.settings.data_dir = value;
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

#[cfg(test)]
mod tests {
    use super::*;

    fn test_writers(name: &str) -> (RunCsvWriters, PathBuf) {
        let dir = std::env::temp_dir().join(format!("at_csv_test_{}_{}", std::process::id(), name));
        let _ = fs::remove_dir_all(&dir);
        (RunCsvWriters::new(dir.clone()), dir)
    }

    fn read_file(dir: &Path, name: &str) -> String {
        fs::read_to_string(dir.join(name)).unwrap()
    }

    #[test]
    fn streams_split_by_phase_and_modality() {
        let (mut writers, dir) = test_writers("split");
        let raw = [14u16, 50, 73, 103, 118, 124, 158, 126, 336, 27];
        writers.append_potential(true, 0.5, 0.0, 0.2577, 0.0).unwrap();
        writers.append_spectrum(true, 0.6, 0.0, &raw).unwrap();
        writers.append_potential(false, 10.2, 1.5, 0.31, 0.02).unwrap();
        writers.append_spectrum(false, 10.3, 1.5, &raw).unwrap();
        writers.flush_all();

        let titr_pot = read_file(&dir, "TitratingPotential.csv");
        assert!(titr_pot.contains(POTENTIAL_HEADER));
        assert!(titr_pot.contains("1.500000,10.200,0.310000,0.020000"));
        assert!(!titr_pot.contains("进样"));

        let intake_pot = read_file(&dir, "IntakingPotential.csv");
        assert!(intake_pot.contains("0.000000,0.500,0.257700,0.000000"));

        let intake_spec = read_file(&dir, "IntakingSpectrum.csv");
        assert!(intake_spec.contains(SPECTRUM_HEADER));
        assert!(intake_spec.contains("0.000000,0.600,14,50,73,103,118,124,158,126,336,27"));
        assert!(read_file(&dir, "TitratingSpectrum.csv").contains("1.500000,10.300,14"));
    }

    #[test]
    fn csv_layout_is_replay_compatible() {
        // replay_csv 按列解析：电位前 3 列 volume/time/e；光谱 12 列 ch0..ch9
        let (mut writers, dir) = test_writers("layout");
        let raw = [0u16; 10];
        writers.append_potential(false, 1.0, 1.0, 1.0, 0.0).unwrap();
        writers.append_spectrum(false, 1.0, 1.0, &raw).unwrap();
        writers.flush_all();

        for name in ["TitratingPotential.csv", "TitratingSpectrum.csv"] {
            for line in read_file(&dir, name).lines() {
                if line.starts_with('#') || line.starts_with("volume_mL") || line.is_empty() {
                    continue;
                }
                let cells: Vec<&str> = line.split(',').collect();
                assert!(cells[0].parse::<f64>().is_ok(), "{name}: 列 0 非数值");
                assert!(cells[1].parse::<f64>().is_ok(), "{name}: 列 1 非数值");
                if name.contains("Spectrum") {
                    assert_eq!(cells.len(), 12);
                    assert!(cells[2..12].iter().all(|c| c.trim().parse::<f64>().is_ok()));
                } else {
                    assert!(cells[2].parse::<f64>().is_ok());
                }
            }
        }
    }

    #[test]
    fn reopen_appends_without_duplicate_header() {
        let (writers, dir) = test_writers("reopen");
        drop(writers); // 模拟中途崩溃后用同目录重建
        let mut writers = RunCsvWriters::new(dir.clone());
        writers.append_potential(true, 9.9, 0.0, 0.1, 0.0).unwrap();
        writers.flush_all();
        let text = read_file(&dir, "IntakingPotential.csv");
        assert_eq!(text.matches(POTENTIAL_HEADER).count(), 1);
        assert!(text.contains("0.000000,9.900"));
        let _ = fs::remove_dir_all(&dir);
    }
}
