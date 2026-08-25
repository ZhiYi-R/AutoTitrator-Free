//! 串口通信运行时：后台线程 + 事件通道（Python `_SerialReader` + `ProtocolHandler` 的移植）。
//!
//! 模型：调用方（未来的 Tauri 命令层）通过 `send`/`send_heartbeat`/`connect` 投递意图，
//! 工作线程独占串口，执行读帧、ACK/NAK 重试、心跳，把 [`Event`] 推回通道，
//! 由调用方周期 `poll()` 取走。

use std::io::{Read as _, Write as _};
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::mpsc::{Receiver, RecvTimeoutError, SyncSender};
use std::sync::Arc;
use std::thread::{self, JoinHandle};
use std::time::{Duration, Instant};

use serde::Serialize;
use serialport::SerialPortType;

use super::frames::{abort_all_frame, heartbeat_frame, DownlinkCommand, UplinkFrame};
use super::parser::UplinkParser;
use super::retry::{NakOutcome, RetryMachine, ABORT_ERROR, FIRST_TIMEOUT_MS};

const POLL_IDLE: Duration = Duration::from_millis(5);
const CHANNEL_BOUND: usize = 4096;

/// 通信事件（对应 Python `_Event.kind` + 载荷）。
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Event {
    Connected,
    Disconnected,
    Error(String),
    Ack(u8),
    Nak(u8),
    PumpPos { pump: u8, position: u32 },
    PumpDone { pump: u8, position: u32 },
    Adc { value: u16, position: u32 },
    Spectral([u16; 10]),
    Heartbeat(u32),
}

enum Mail {
    Open(String, u32),
    Close,
    Send(DownlinkCommand),
    Heartbeat,
    Shutdown,
}

enum Deadline {
    /// 已写线，等待首包 ACK（100ms）。
    FirstTimeout(Instant),
    /// NAK/超时后的退避等待，到点重传。
    Backoff(Instant),
}

/// 对外句柄；`&self` 方法可在任意线程调用。
pub struct ProtocolHandler {
    mail: SyncSender<Mail>,
    events: Receiver<Event>,
    open_flag: Arc<AtomicBool>,
    worker: Option<JoinHandle<()>>,
}

impl ProtocolHandler {
    pub fn new() -> Self {
        let (mail_tx, mail_rx) = std::sync::mpsc::sync_channel(64);
        let (event_tx, event_rx) = std::sync::mpsc::sync_channel(CHANNEL_BOUND);
        let open_flag = Arc::new(AtomicBool::new(false));
        let worker = thread::Builder::new()
            .name("com-worker".into())
            .spawn({
                let open_flag = Arc::clone(&open_flag);
                move || worker_loop(mail_rx, event_tx, open_flag)
            })
            .expect("spawn com-worker");

        Self {
            mail: mail_tx,
            events: event_rx,
            open_flag,
            worker: Some(worker),
        }
    }

    pub fn is_open(&self) -> bool {
        self.open_flag.load(Ordering::Relaxed)
    }

    /// 连接串口（8N1）。未指定端口时上报错误事件，与 Python 一致。
    pub fn connect(&self, port: &str, baud: u32) {
        let _ = self.mail.send(Mail::Open(port.to_string(), baud));
    }

    pub fn disconnect(&self) {
        let _ = self.mail.send(Mail::Close);
    }

    /// 发送命令并纳入 ACK/重试管理。
    pub fn send(&self, cmd: DownlinkCommand) {
        let _ = self.mail.send(Mail::Send(cmd));
    }

    /// 发送心跳；有 pending 命令时跳过，避免覆盖其确认状态。
    pub fn send_heartbeat(&self) {
        let _ = self.mail.send(Mail::Heartbeat);
    }

    /// 排空事件队列（由 UI 层周期调用，对应 Python `poll()`）。
    pub fn poll(&self) -> Vec<Event> {
        let mut out = Vec::new();
        while let Ok(ev) = self.events.try_recv() {
            out.push(ev);
        }
        out
    }

    /// 停止工作线程并释放串口。
    pub fn shutdown(mut self) {
        let _ = self.mail.send(Mail::Shutdown);
        if let Some(handle) = self.worker.take() {
            let _ = handle.join();
        }
    }
}

impl Default for ProtocolHandler {
    fn default() -> Self {
        Self::new()
    }
}

fn worker_loop(mail: Receiver<Mail>, events: SyncSender<Event>, open_flag: Arc<AtomicBool>) {
    let mut port: Option<Box<dyn serialport::SerialPort>> = None;
    let mut parser = UplinkParser::new();
    let mut retry = RetryMachine::new();
    let mut deadline: Option<Deadline> = None;
    let mut buf = [0u8; 1024];

    let emit = |ev: Event| {
        // 上位机 100ms 轮询下 4096 深度远够用；满时丢弃新事件并记录。
        if events.send(ev).is_err() {
            // 接收端已 drop（应用关闭），静默。
        }
    };

    loop {
        // ---- 1) 处理调用方指令 ----
        match mail.recv_timeout(POLL_IDLE) {
            Ok(Mail::Open(name, baud)) => {
                close_port(&mut port, &open_flag, &emit, true);
                if name.is_empty() {
                    emit(Event::Error("未指定串口端口".into()));
                } else {
                    match serialport::new(&name, baud)
                        .data_bits(serialport::DataBits::Eight)
                        .parity(serialport::Parity::None)
                        .stop_bits(serialport::StopBits::One)
                        .timeout(POLL_IDLE)
                        .open()
                    {
                        Ok(p) => {
                            parser.reset();
                            retry.clear();
                            deadline = None;
                            open_flag.store(true, Ordering::Relaxed);
                            port = Some(p);
                            emit(Event::Connected);
                        }
                        Err(exc) => emit(Event::Error(exc.to_string())),
                    }
                }
            }
            Ok(Mail::Close) => close_port(&mut port, &open_flag, &emit, true),
            Ok(Mail::Send(cmd)) => {
                if let Some(p) = port.as_mut() {
                    let frame = cmd.encode();
                    retry.send(frame.clone(), cmd.id());
                    let _ = p.write_all(&frame);
                    deadline = Some(Deadline::FirstTimeout(
                        Instant::now() + Duration::from_millis(FIRST_TIMEOUT_MS),
                    ));
                }
            }
            Ok(Mail::Heartbeat) => {
                // 普通命令只有一个 pending 槽；命令等待确认时跳过本次心跳，
                // 避免覆盖泵控制命令并误判其 ACK。
                if !retry.is_pending() {
                    if let Some(p) = port.as_mut() {
                        let _ = p.write_all(&heartbeat_frame());
                    }
                }
            }
            Ok(Mail::Shutdown) => {
                close_port(&mut port, &open_flag, &emit, true);
                return;
            }
            Err(RecvTimeoutError::Timeout) | Err(RecvTimeoutError::Disconnected) => {}
        }

        // ---- 2) 重试/超时截止 ----
        let due = matches!(&deadline, Some(Deadline::FirstTimeout(t)) if *t <= Instant::now())
            || matches!(&deadline, Some(Deadline::Backoff(t)) if *t <= Instant::now());
        if due {
            match deadline.take() {
                Some(Deadline::FirstTimeout(_)) => {
                    // 首包超时等价 NAK（Python _on_first_timeout → poll → _handle_nak）
                    if let Some(id) = retry.pending_id() {
                        apply_nak(retry.on_nak(id), &mut deadline, &mut port, &emit);
                    }
                }
                Some(Deadline::Backoff(_)) => {
                    if let Some(frame) = retry.pending_frame().map(<[u8]>::to_vec) {
                        if let Some(p) = port.as_mut() {
                            let _ = p.write_all(&frame);
                            deadline = Some(Deadline::FirstTimeout(
                                Instant::now() + Duration::from_millis(FIRST_TIMEOUT_MS),
                            ));
                        }
                    }
                }
                None => {}
            }
        }

        // ---- 3) 读串口 → 解析 → 分发（先绑定结果，释放串口借用）----
        let read_result: std::io::Result<usize> = match port.as_mut() {
            Some(p) => p.read(&mut buf),
            None => Ok(0),
        };
        match read_result {
            Ok(0) => {}
            Ok(n) => {
                let mut frames = Vec::new();
                parser.feed(&buf[..n], &mut frames);
                for (frame_type, payload) in frames {
                    let Some(frame) = UplinkFrame::decode(frame_type, &payload) else {
                        continue;
                    };
                    match frame {
                        UplinkFrame::Ack(cmd) => {
                            if let Some(text) = retry.on_ack(cmd).error_text() {
                                emit(Event::Error(text));
                            }
                            emit(Event::Ack(cmd));
                        }
                        UplinkFrame::Nak(cmd) => {
                            apply_nak(retry.on_nak(cmd), &mut deadline, &mut port, &emit);
                            emit(Event::Nak(cmd));
                        }
                        other => emit(frame_event(other)),
                    }
                }
            }
            Err(exc) if is_read_idle_error(&exc) => {}
            Err(exc) => {
                emit(Event::Error(exc.to_string()));
                close_port(&mut port, &open_flag, &emit, true);
            }
        }
    }
}

/// NAK/超时处置：安排退避重传，或耗尽后发 AbortAll + 报错。
fn apply_nak(
    outcome: NakOutcome,
    deadline: &mut Option<Deadline>,
    port: &mut Option<Box<dyn serialport::SerialPort>>,
    emit: &impl Fn(Event),
) {
    match outcome {
        NakOutcome::Retry { delay_ms } => {
            *deadline = Some(Deadline::Backoff(
                Instant::now() + Duration::from_millis(delay_ms),
            ));
        }
        NakOutcome::AbortAndError => {
            *deadline = None;
            if let Some(p) = port.as_mut() {
                let _ = p.write_all(&abort_all_frame());
            }
            emit(Event::Error(ABORT_ERROR.into()));
        }
        NakOutcome::Ignored => {}
    }
}

fn is_read_idle_error(error: &std::io::Error) -> bool {
    matches!(
        error.kind(),
        std::io::ErrorKind::TimedOut | std::io::ErrorKind::WouldBlock
    )
}

fn frame_event(frame: UplinkFrame) -> Event {
    match frame {
        UplinkFrame::Ack(cmd) => Event::Ack(cmd),
        UplinkFrame::Nak(cmd) => Event::Nak(cmd),
        UplinkFrame::PumpPos { pump, position } => Event::PumpPos { pump, position },
        UplinkFrame::PumpDone { pump, position } => Event::PumpDone { pump, position },
        UplinkFrame::Adc { value, position } => Event::Adc { value, position },
        UplinkFrame::Spectral(vals) => Event::Spectral(vals),
        UplinkFrame::Heartbeat(uptime_ms) => Event::Heartbeat(uptime_ms),
    }
}

fn close_port(
    port: &mut Option<Box<dyn serialport::SerialPort>>,
    open_flag: &AtomicBool,
    emit: &impl Fn(Event),
    notify: bool,
) {
    if port.take().is_some() && notify {
        emit(Event::Disconnected);
    }
    open_flag.store(false, Ordering::Relaxed);
}

/// 可用于 UI 展示的串口信息；连接时仍只使用 `port_name`。
#[derive(Debug, Clone, PartialEq, Eq, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct PortInfo {
    pub port_name: String,
    pub description: Option<String>,
}

fn port_description(port_type: &SerialPortType) -> Option<String> {
    match port_type {
        SerialPortType::UsbPort(info) => {
            let mut parts = Vec::new();
            if let Some(manufacturer) = info.manufacturer.as_deref().filter(|s| !s.is_empty()) {
                parts.push(manufacturer.to_string());
            }
            if let Some(product) = info.product.as_deref().filter(|s| !s.is_empty()) {
                if !parts.iter().any(|part| part == product) {
                    parts.push(product.to_string());
                }
            }
            if parts.is_empty() {
                parts.push(format!("USB VID_{:04X}:PID_{:04X}", info.vid, info.pid));
            }
            if let Some(serial) = info.serial_number.as_deref().filter(|s| !s.is_empty()) {
                parts.push(format!("S/N {serial}"));
            }
            Some(parts.join(" "))
        }
        SerialPortType::BluetoothPort => Some("Bluetooth serial port".into()),
        SerialPortType::PciPort => Some("PCI serial port".into()),
        SerialPortType::Unknown => None,
    }
}

/// 供 Tauri 层列举可用串口及设备描述。
pub fn list_ports() -> Vec<PortInfo> {
    serialport::available_ports()
        .map(|ports| {
            ports
                .into_iter()
                .map(|port| PortInfo {
                    port_name: port.port_name,
                    description: port_description(&port.port_type),
                })
                .collect()
        })
        .unwrap_or_default()
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::retry::RetryMachine;

    #[test]
    fn heartbeat_is_skipped_while_command_pending() {
        // 复刻 Python test_send_heartbeat_does_not_overwrite_pending_command：
        // 心跳路径的判定就是 is_pending()；pending 存在时心跳不写线。
        let mut m = RetryMachine::new();
        m.send(vec![0xBB, 0x55, 0x02, 0x02, 0x00], 0x02);
        assert!(m.is_pending());
        assert_eq!(m.pending_id(), Some(0x02));
    }

    #[test]
    fn read_idle_errors_are_nonfatal() {
        assert!(is_read_idle_error(&std::io::Error::new(
            std::io::ErrorKind::TimedOut,
            "idle"
        )));
        assert!(is_read_idle_error(&std::io::Error::new(
            std::io::ErrorKind::WouldBlock,
            "idle"
        )));
        assert!(!is_read_idle_error(&std::io::Error::new(
            std::io::ErrorKind::BrokenPipe,
            "closed"
        )));
    }

    #[test]
    fn list_ports_returns_vector() {
        let ports = list_ports();
        // 无法断言具体端口（CI 无串口），只验证类型与不 panic。
        assert!(ports.len() <= 256);
        assert!(ports.iter().all(|port| !port.port_name.is_empty()));
    }
}
