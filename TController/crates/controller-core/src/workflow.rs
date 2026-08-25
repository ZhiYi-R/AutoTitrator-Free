//! 滴定工作流状态机 — Python `gui/main_window.py` 的 `TitrationState` +
//! `_run_detection` 泵控判据的后端化移植。
//!
//! 工作流：空闲 → [开始] 进样泵 MaxCount → 滴定泵 FreeRun → 终点 T=1
//! → 继续 FreeRun 至 2×V_ep → T=2 停泵 + AMPD 精修 → 完成。
//!
//! T=1 的泵控判据是"报告的体积有电位证据支撑"，而不是枚举 method 名字：
//! consensus 已由 KF 融合双模态；potential_only 与 conflict 报告的都是电位
//! 终点（conflict 即"双模态都确认但未过 NIS 门控，退回电位"）。只有
//! spectral_only 不能控泵——它没有电极证据。若按 method 名白名单就会漏掉
//! conflict：两模态持续不一致时 T=1 永不触发，滴定死锁而泵无限运行
//! （Python 版的实际回归，此处固化为测试 `conflict_with_potential_evidence_triggers_t1`）。

use serde::Serialize;

use crate::processing::calibration::PumpCalibration;
use crate::processing::endpoint::{EndpointDetector, EndpointResult, Method};
use crate::protocol::DownlinkCommand;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize)]
#[serde(rename_all = "snake_case")]
#[derive(Default)]
pub enum TitrationState {
    #[default]
    Idle,
    Injecting,
    Titrating,
    Degree1,
    Titrating2,
    Done,
    Error,
}

/// 泵指令（由传输层执行）。
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PumpCommand {
    MaxCount { pump: u8, steps: u32 },
    FreeRun(u8),
    FreeStop(u8),
}

impl From<PumpCommand> for DownlinkCommand {
    fn from(cmd: PumpCommand) -> Self {
        match cmd {
            PumpCommand::MaxCount { pump, steps } => {
                DownlinkCommand::MaxCount { pump, count: steps }
            }
            PumpCommand::FreeRun(p) => DownlinkCommand::FreeRun(p),
            PumpCommand::FreeStop(p) => DownlinkCommand::FreeStop(p),
        }
    }
}

/// 一次 tick 的决策输出。
#[derive(Debug, Clone, Default)]
pub struct WorkflowOutcome {
    pub state: TitrationState,
    pub commands: Vec<PumpCommand>,
    /// T=1 首次报告的终点。
    pub first_endpoint: Option<f64>,
    /// T=2/手动停止时 AMPD 精修后的终点。
    pub refined_endpoint: Option<f64>,
    /// T=1 时 method 为 conflict（界面据此给出不同提示）。
    pub conflict_at_t1: bool,
    /// 本 tick 的检测诊断（JSON 由上层序列化转发）。
    pub detection: Option<EndpointResult>,
}

/// 工作流引擎：状态 + 检测器 + 泵 2 体积，纯逻辑，不含 I/O。
pub struct WorkflowEngine {
    pub state: TitrationState,
    pub detector: EndpointDetector,
    pub calibration: PumpCalibration,
    pump2_volume: f64,
    endpoint_volume: Option<f64>,
}

impl WorkflowEngine {
    pub fn new(flow_rate: f64, calibration: PumpCalibration) -> Self {
        Self {
            state: TitrationState::Idle,
            detector: EndpointDetector::new(flow_rate),
            calibration,
            pump2_volume: 0.0,
            endpoint_volume: None,
        }
    }

    pub fn endpoint_volume(&self) -> Option<f64> {
        self.endpoint_volume
    }

    pub fn pump2_volume(&self) -> f64 {
        self.pump2_volume
    }

    fn titrating(&self) -> bool {
        matches!(
            self.state,
            TitrationState::Titrating | TitrationState::Degree1 | TitrationState::Titrating2
        )
    }

    /// 开始滴定：进样体积（mL）→ MaxCount 步数，状态进入 Injecting。
    pub fn start(&mut self, sample_volume_ml: f64) -> WorkflowOutcome {
        self.detector.reset();
        self.endpoint_volume = None;
        self.pump2_volume = 0.0;
        self.state = TitrationState::Injecting;
        let steps = self.calibration.steps_from_volume(sample_volume_ml);
        WorkflowOutcome {
            state: self.state,
            commands: vec![PumpCommand::MaxCount { pump: 1, steps }],
            ..Default::default()
        }
    }

    /// 泵完成回调：泵 1 进样完成 → 启动滴定泵。
    pub fn on_pump_done(&mut self, pump_id: u8) -> WorkflowOutcome {
        if pump_id == 1 && self.state == TitrationState::Injecting {
            self.state = TitrationState::Titrating;
            return WorkflowOutcome {
                state: self.state,
                commands: vec![PumpCommand::FreeRun(2)],
                ..Default::default()
            };
        }
        WorkflowOutcome {
            state: self.state,
            ..Default::default()
        }
    }

    /// ADC 上行帧（1 kHz）：更新泵 2 体积并馈入检测器。
    /// `position` 为固件累计步数；`t` 为连接起点的秒；`voltage` 已换算为伏。
    pub fn on_adc(&mut self, position: u32, t: f64, voltage: f64) {
        self.pump2_volume = self.calibration.volume_from_steps(position);
        if self.titrating() {
            self.detector.feed_potential(self.pump2_volume, t, voltage);
        }
    }

    /// 光谱上行帧：仅在滴定期间馈入检测器。
    pub fn on_spectrum(&mut self, spectrum: &[f64]) {
        if self.titrating() {
            self.detector.feed_spectrum(self.pump2_volume, spectrum);
        }
    }

    /// 周期决策（对应 Python `_run_detection`，500ms 周期）。
    pub fn poll(&mut self) -> WorkflowOutcome {
        if !self.titrating() {
            return WorkflowOutcome {
                state: self.state,
                ..Default::default()
            };
        }

        let Some(result) = self.detector.detect() else {
            return WorkflowOutcome {
                state: self.state,
                ..Default::default()
            };
        };
        let vol = result.volume;
        let method = result.method;
        let potential_evidence = result.reliability.potential_evidence;
        let mut outcome = WorkflowOutcome {
            state: self.state,
            detection: Some(result),
            ..Default::default()
        };

        match self.state {
            TitrationState::Titrating => {
                // 判据 = 有电位证据（见模块文档）；spectral_only 只能候选。
                let can_control = method == Method::Consensus
                    || (matches!(method, Method::PotentialOnly | Method::Conflict)
                        && potential_evidence);
                if !can_control {
                    return outcome;
                }
                self.endpoint_volume = Some(vol);
                self.state = TitrationState::Degree1;
                outcome.state = self.state;
                outcome.first_endpoint = Some(vol);
                outcome.conflict_at_t1 = method == Method::Conflict;
            }
            TitrationState::Degree1 | TitrationState::Titrating2 => {
                if let Some(ep) = self.endpoint_volume {
                    if self.pump2_volume >= 2.0 * ep {
                        let refined = self.detector.refine_with_ampd();
                        if let Some(r) = refined {
                            self.endpoint_volume = Some(r);
                        }
                        self.state = TitrationState::Done;
                        outcome.state = self.state;
                        outcome.commands = vec![PumpCommand::FreeStop(2)];
                        outcome.refined_endpoint = self.endpoint_volume;
                        return outcome;
                    }
                }
                if self.state == TitrationState::Degree1 {
                    self.state = TitrationState::Titrating2;
                    outcome.state = self.state;
                }
            }
            _ => unreachable!("titrating() 已过滤其余状态"),
        }
        outcome
    }

    /// 手动停止：停泵；已有 T=1 时用 AMPD 精修并收尾。
    pub fn manual_stop(&mut self) -> WorkflowOutcome {
        let mut outcome = WorkflowOutcome {
            state: TitrationState::Done,
            commands: vec![PumpCommand::FreeStop(2)],
            ..Default::default()
        };
        if self.endpoint_volume.is_some() {
            outcome.refined_endpoint = self.detector.refine_with_ampd();
            if let Some(r) = outcome.refined_endpoint {
                self.endpoint_volume = Some(r);
            }
        }
        self.state = TitrationState::Done;
        outcome.state = self.state;
        outcome
    }

    /// 急停 / MCU 复位后的状态归零。
    pub fn abort(&mut self) -> WorkflowOutcome {
        self.state = TitrationState::Idle;
        self.endpoint_volume = None;
        self.pump2_volume = 0.0;
        self.detector.reset();
        WorkflowOutcome {
            state: self.state,
            ..Default::default()
        }
    }

    /// 滴定期间是否允许手动停止（连接后 Injecting 起允许）。
    pub fn can_manual_stop(&self) -> bool {
        !matches!(
            self.state,
            TitrationState::Idle | TitrationState::Done | TitrationState::Error
        )
    }
}
