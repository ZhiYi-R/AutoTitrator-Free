//! 上/下行帧定义与编解码。
//!
//! 上行帧（MCU → Host）：`AA 55 | 类型(1B) | 数据(NB) | CRC8(类型+数据)`
//! 下行帧（Host → MCU）：`BB 55 | 命令(1B) | 参数(NB) | CRC8(命令+参数)`

use super::crc::crc8;

/// 上行帧类型 → 载荷长度（与固件协议表一致）。
pub fn uplink_payload_len(frame_type: u8) -> Option<usize> {
    Some(match frame_type {
        0x00 => 1,  // ACK       — echo_cmd(1)
        0x01 => 1,  // NAK       — echo_cmd(1)
        0x10 => 5,  // PumpPos   — pump_id(1) + position(4) LE
        0x11 => 5,  // PumpDone  — pump_id(1) + position(4) LE
        0x20 => 11, // ADC       — sum(4) + samples(2) + shift(1) + pump2_pos(4)
        0x30 => 22, // Spectral  — 10 x uint16 LE + reserved(2)
        0x40 => 4,  // Heartbeat — uptime_ms(4)
        _ => return None,
    })
}

/// 下行命令 → 参数长度。
pub fn downlink_param_len(cmd: u8) -> Option<usize> {
    Some(match cmd {
        0x01 => 5, // MaxCount  — pump_id(1) + count(4)
        0x02 => 1, // FreeRun   — pump_id(1)
        0x03 => 1, // FreeStop  — pump_id(1)
        0x04 => 1, // AbortAll  — pump_id(1), 0xFF=全部
        0x05 => 1, // Heartbeat — 0x01=enable watchdog
        0x06 => 0, // Reset     — 无载荷
        _ => return None,
    })
}

fn u32le(payload: &[u8], off: usize) -> u32 {
    u32::from_le_bytes([
        payload[off],
        payload[off + 1],
        payload[off + 2],
        payload[off + 3],
    ])
}

fn u16le(payload: &[u8], off: usize) -> u16 {
    u16::from_le_bytes([payload[off], payload[off + 1]])
}

/// 解析后的上行帧（对应 Python `_on_frame` 的事件映射）。
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum UplinkFrame {
    Ack(u8),
    Nak(u8),
    /// 泵进度上报（每 1000 脉冲）。
    PumpPos {
        pump: u8,
        position: u32,
    },
    /// 泵运行完成。
    PumpDone {
        pump: u8,
        position: u32,
    },
    /// ADC 过采样结果：16-bit 有效值 + 泵 2 位置。
    Adc {
        value: u16,
        position: u32,
    },
    /// AS7341 光谱：F1..F8/Clear/NIR 十通道原始值。
    Spectral([u16; 10]),
    /// 心跳：MCU uptime_ms。
    Heartbeat(u32),
}

impl UplinkFrame {
    /// 从 `(类型, 载荷)` 解码；类型未知或长度不符返回 `None`（静默丢弃，与 Python 一致）。
    pub fn decode(frame_type: u8, payload: &[u8]) -> Option<Self> {
        Some(match frame_type {
            0x00 if payload.len() == 1 => UplinkFrame::Ack(payload[0]),
            0x01 if payload.len() == 1 => UplinkFrame::Nak(payload[0]),
            0x10 if payload.len() == 5 => UplinkFrame::PumpPos {
                pump: payload[0],
                position: u32le(payload, 1),
            },
            0x11 if payload.len() == 5 => UplinkFrame::PumpDone {
                pump: payload[0],
                position: u32le(payload, 1),
            },
            0x20 if payload.len() == 11 => {
                let acc = u32le(payload, 0);
                let shift = payload[6];
                UplinkFrame::Adc {
                    value: ((acc >> shift) & 0xFFFF) as u16,
                    position: u32le(payload, 7),
                }
            }
            0x30 if payload.len() == 22 => {
                let mut vals = [0u16; 10];
                for (i, v) in vals.iter_mut().enumerate() {
                    *v = u16le(payload, i * 2);
                }
                UplinkFrame::Spectral(vals)
            }
            0x40 if payload.len() == 4 => UplinkFrame::Heartbeat(u32le(payload, 0)),
            _ => return None,
        })
    }
}

/// 下行命令（对应 Python `send_maxcount`/`send_frerun`/…）。
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum DownlinkCommand {
    /// 0x01 — 定量运行：pump_id + 步数。
    MaxCount { pump: u8, count: u32 },
    /// 0x02 — 自由运行。
    FreeRun(u8),
    /// 0x03 — 正常停止（0xFF = 全部）。
    FreeStop(u8),
    /// 0x04 — 紧急停止（语义用于异常，功能等价 0x03）。
    Abort(u8),
    /// 0x05 — 启用心跳看门狗（参数 0x01）。
    EnableWatchdog,
    /// 0x06 — 复位 MCU。
    Reset,
}

impl DownlinkCommand {
    pub fn id(&self) -> u8 {
        match self {
            DownlinkCommand::MaxCount { .. } => 0x01,
            DownlinkCommand::FreeRun(_) => 0x02,
            DownlinkCommand::FreeStop(_) => 0x03,
            DownlinkCommand::Abort(_) => 0x04,
            DownlinkCommand::EnableWatchdog => 0x05,
            DownlinkCommand::Reset => 0x06,
        }
    }

    pub fn params(&self) -> Vec<u8> {
        match *self {
            DownlinkCommand::MaxCount { pump, count } => {
                let mut p = vec![pump];
                p.extend_from_slice(&count.to_le_bytes());
                p
            }
            DownlinkCommand::FreeRun(pump)
            | DownlinkCommand::FreeStop(pump)
            | DownlinkCommand::Abort(pump) => vec![pump],
            DownlinkCommand::EnableWatchdog => vec![0x01],
            DownlinkCommand::Reset => Vec::new(),
        }
    }

    /// 编码为完整下行帧（含帧头与 CRC）。
    pub fn encode(&self) -> Vec<u8> {
        let cmd = self.id();
        let params = self.params();
        debug_assert_eq!(
            params.len(),
            downlink_param_len(cmd).unwrap_or(params.len())
        );
        let mut body = vec![cmd];
        body.extend_from_slice(&params);
        let cs = crc8(&body);
        let mut frame = vec![0xBB, 0x55];
        frame.extend_from_slice(&body);
        frame.push(cs);
        frame
    }
}

/// 构建心跳帧（0x05 0x01），不占用命令的 ACK/重试状态。
pub fn heartbeat_frame() -> Vec<u8> {
    DownlinkCommand::EnableWatchdog.encode()
}

/// 构建 AbortAll（0x04 0xFF）帧，用于重试耗尽后的自动急停。
pub fn abort_all_frame() -> Vec<u8> {
    DownlinkCommand::Abort(0xFF).encode()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn downlink_param_lengths_match_protocol_table() {
        // Python 版 send_cmd 按此表校验参数长度；Rust 版命令为强类型，
        // 这里断言编码出的参数长度与表一致，保证帧格式不变。
        assert_eq!(
            DownlinkCommand::MaxCount {
                pump: 1,
                count: 0x1234_5678
            }
            .params()
            .len(),
            5
        );
        assert_eq!(DownlinkCommand::FreeRun(2).params().len(), 1);
        assert_eq!(DownlinkCommand::FreeStop(0xFF).params().len(), 1);
        assert_eq!(DownlinkCommand::Abort(0xFF).params().len(), 1);
        assert_eq!(DownlinkCommand::EnableWatchdog.params().len(), 1);
        assert_eq!(DownlinkCommand::Reset.params().len(), 0);
    }

    #[test]
    fn maxcount_frame_layout() {
        let frame = DownlinkCommand::MaxCount {
            pump: 1,
            count: 0x0102_0304,
        }
        .encode();
        assert_eq!(&frame[..2], &[0xBB, 0x55]);
        assert_eq!(frame[2], 0x01);
        assert_eq!(&frame[3..8], &[0x01, 0x04, 0x03, 0x02, 0x01]);
        assert_eq!(frame[8], crc8(&frame[2..8]));
    }

    #[test]
    fn adc_decode_applies_shift() {
        // sum=0x1_2345_6789, shift=4 → (sum >> 4) & 0xFFFF
        let mut payload = Vec::new();
        payload.extend_from_slice(&0x1234_5678u32.to_le_bytes());
        payload.extend_from_slice(&1234u16.to_le_bytes()); // samples（未用）
        payload.push(4); // shift
        payload.extend_from_slice(&0x0000_00FFu32.to_le_bytes()); // pump2_pos
        match UplinkFrame::decode(0x20, &payload) {
            Some(UplinkFrame::Adc { value, position }) => {
                assert_eq!(value, ((0x1234_5678u32 >> 4) & 0xFFFF) as u16);
                assert_eq!(position, 0xFF);
            }
            other => panic!("unexpected frame: {other:?}"),
        }
    }

    #[test]
    fn spectral_decode_takes_first_ten_u16() {
        let mut payload = Vec::new();
        for i in 0..10u16 {
            payload.extend_from_slice(&(i * 1000).to_le_bytes());
        }
        payload.extend_from_slice(&0xBEEFu16.to_le_bytes()); // reserved(2)
        match UplinkFrame::decode(0x30, &payload) {
            Some(UplinkFrame::Spectral(vals)) => {
                assert_eq!(vals[0], 0);
                assert_eq!(vals[9], 9000);
            }
            other => panic!("unexpected frame: {other:?}"),
        }
    }
}
