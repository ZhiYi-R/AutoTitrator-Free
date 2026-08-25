//! 上行帧逐字节状态机解析器（`AA 55` 前导，CRC 校验失败静默丢弃）。

use super::crc::crc8;
use super::frames::uplink_payload_len;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum State {
    Sync,
    Type,
    Data,
    Checksum,
}

/// 逐字节输入，输出 `(类型, 载荷)`；与 Python `_UplinkParser` 逐位一致。
#[derive(Debug)]
pub struct UplinkParser {
    state: State,
    frame_type: u8,
    data: Vec<u8>,
    data_len: usize,
    /// SYNC 态缓存，用于识别 `AA 55` 前导（允许中间夹杂干扰字节后重同步）。
    sync_buf: Vec<u8>,
}

impl Default for UplinkParser {
    fn default() -> Self {
        Self::new()
    }
}

impl UplinkParser {
    pub fn new() -> Self {
        Self {
            state: State::Sync,
            frame_type: 0,
            data: Vec::new(),
            data_len: 0,
            sync_buf: Vec::new(),
        }
    }

    pub fn reset(&mut self) {
        *self = Self::new();
    }

    /// 输入一段字节流，把本批次解析出的帧追加到 `out`。
    pub fn feed(&mut self, bytes: &[u8], out: &mut Vec<(u8, Vec<u8>)>) {
        for &b in bytes {
            if let Some(frame) = self.feed_byte(b) {
                out.push(frame);
            }
        }
    }

    fn feed_byte(&mut self, b: u8) -> Option<(u8, Vec<u8>)> {
        match self.state {
            State::Sync => {
                if b == 0xAA {
                    self.sync_buf.push(b);
                } else if b == 0x55 && self.sync_buf.last() == Some(&0xAA) {
                    self.state = State::Type;
                    self.sync_buf.clear();
                } else {
                    self.sync_buf.clear();
                }
                None
            }
            State::Type => {
                self.frame_type = b;
                match uplink_payload_len(b) {
                    Some(len) => {
                        self.data_len = len;
                        self.data.clear();
                        self.state = if len == 0 {
                            State::Checksum
                        } else {
                            State::Data
                        };
                    }
                    None => self.reset(),
                }
                None
            }
            State::Data => {
                self.data.push(b);
                if self.data.len() >= self.data_len {
                    self.state = State::Checksum;
                }
                None
            }
            State::Checksum => {
                let mut body = vec![self.frame_type];
                body.extend_from_slice(&self.data);
                let ok = crc8(&body) == b;
                let result = ok.then(|| (self.frame_type, std::mem::take(&mut self.data)));
                self.reset();
                result
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parses_a_well_formed_adc_frame() {
        let payload: Vec<u8> = (0..11u8).collect();
        let mut frame = vec![0xAA, 0x55, 0x20];
        frame.extend_from_slice(&payload);
        frame.push(crc8(
            &[0x20]
                .iter()
                .chain(payload.iter())
                .copied()
                .collect::<Vec<u8>>(),
        ));

        let mut out = Vec::new();
        UplinkParser::new().feed(&frame, &mut out);
        assert_eq!(out, vec![(0x20, payload)]);
    }

    #[test]
    fn resynchronizes_after_repeated_preamble_noise() {
        // 复刻 Python 测试：BB BB AA 55 前的干扰不阻碍 ACK 帧解析。
        let payload = vec![0x01];
        let mut frame = vec![0xBB, 0xBB, 0xAA, 0x55, 0x00];
        frame.extend_from_slice(&payload);
        frame.push(crc8(&[0x00, 0x01]));

        let mut out = Vec::new();
        UplinkParser::new().feed(&frame, &mut out);
        assert_eq!(out, vec![(0x00, payload)]);
    }

    #[test]
    fn drops_frame_with_bad_crc_and_recovers() {
        // 心跳帧载荷长度须为 4，否则坏帧会占用后续字节
        let payload = vec![0x05, 0x00, 0x00, 0x00];
        let mut frame = vec![0xAA, 0x55, 0x40];
        frame.extend_from_slice(&payload);
        frame.push(
            crc8(
                &[0x40]
                    .iter()
                    .chain(payload.iter())
                    .copied()
                    .collect::<Vec<u8>>(),
            ) ^ 0xFF,
        );
        frame.extend_from_slice(&{
            // 随后跟一个好帧
            let mut f = vec![0xAA, 0x55, 0x00, 0x02];
            f.push(crc8(&[0x00, 0x02]));
            f
        });

        let mut out = Vec::new();
        UplinkParser::new().feed(&frame, &mut out);
        assert_eq!(out, vec![(0x00, vec![0x02])]);
    }
}
