//! ACK/NAK 重试状态机（纯逻辑，无 I/O）— Python `ProtocolHandler` 重试语义的移植。
//!
//! 单 pending 槽：任一时刻只有一条命令等待确认。
//! NAK/超时 → 指数退避重传（50ms 起，最多 5 次）；重试耗尽 → 自动 AbortAll + 报错。

/// 最大重试次数（Python `_max_retries`）。
pub const MAX_RETRIES: u32 = 5;
/// 退避基数（Python `_backoff_ms`）。
pub const BACKOFF_MS: u64 = 50;
/// 首包 ACK 超时（Python `send_cmd` 的 100ms 定时器）。
pub const FIRST_TIMEOUT_MS: u64 = 100;

/// 重试耗尽后上报的错误文本（Python `_send_abort_and_error`）。
pub const ABORT_ERROR: &str = "下位机通讯异常";

/// `on_ack` 的结果。
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum AckOutcome {
    /// ACK 匹配当前 pending 命令，已清除。
    Cleared,
    /// 收到不匹配的 ACK 且仍有 pending —— 状态可能不同步，应上报错误。
    Unexpected { received: u8, expected: u8 },
    /// 无 pending 时收到的 ACK，忽略（可能是重复响应）。
    Ignored,
}

/// `on_nak` / 首包超时的结果。
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum NakOutcome {
    /// 安排重传：先等 `delay_ms` 再写线，随后重新启动首包超时。
    Retry { delay_ms: u64 },
    /// 重试耗尽：pending 已清除，调用方应发送 AbortAll 并上报错误。
    AbortAndError,
    /// 无 pending 或命令号不匹配，忽略。
    Ignored,
}

/// 单命令 ACK/重试状态。
#[derive(Debug, Default)]
pub struct RetryMachine {
    pending_frame: Option<Vec<u8>>,
    pending_id: Option<u8>,
    retry_count: u32,
}

impl RetryMachine {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn is_pending(&self) -> bool {
        self.pending_frame.is_some()
    }

    pub fn pending_id(&self) -> Option<u8> {
        self.pending_id
    }

    /// 待重传的完整帧（重试写线用）。
    pub fn pending_frame(&self) -> Option<&[u8]> {
        self.pending_frame.as_deref()
    }

    /// 发送新命令：无条件覆盖旧 pending（含清除计时器语义，由调用方落地）。
    pub fn send(&mut self, frame: Vec<u8>, cmd_id: u8) {
        self.pending_frame = Some(frame);
        self.pending_id = Some(cmd_id);
        self.retry_count = 0;
    }

    pub fn clear(&mut self) {
        self.pending_frame = None;
        self.pending_id = None;
        self.retry_count = 0;
    }

    /// 收到 ACK（Python `_on_ack`）。
    pub fn on_ack(&mut self, cmd: u8) -> AckOutcome {
        match self.pending_id {
            Some(expected) if expected == cmd => {
                self.clear();
                AckOutcome::Cleared
            }
            Some(expected) => AckOutcome::Unexpected {
                received: cmd,
                expected,
            },
            None => AckOutcome::Ignored,
        }
    }

    /// 收到 NAK 或首包超时（Python `_handle_nak`）。首包超时由调用方
    /// 以当前 pending 命令号调用本方法，行为与 NAK 一致。
    pub fn on_nak(&mut self, cmd: u8) -> NakOutcome {
        if self.pending_frame.is_none() || self.pending_id != Some(cmd) {
            return NakOutcome::Ignored;
        }
        self.retry_count += 1;
        if self.retry_count >= MAX_RETRIES {
            self.clear();
            return NakOutcome::AbortAndError;
        }
        NakOutcome::Retry {
            delay_ms: BACKOFF_MS * (1 << (self.retry_count - 1)),
        }
    }
}

impl AckOutcome {
    /// 不匹配 ACK 的错误文本（Python：收到意外 ACK 0x%02X，期望 0x%02X）。
    pub fn error_text(&self) -> Option<String> {
        match self {
            AckOutcome::Unexpected { received, expected } => Some(format!(
                "收到意外 ACK 0x{received:02X}，期望 0x{expected:02X}"
            )),
            _ => None,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn ack_requires_matching_pending_command() {
        let mut m = RetryMachine::new();
        m.send(vec![0xBB, 0x55, 0x02, 0x02, 0x00], 0x02);

        assert_eq!(
            m.on_ack(0x05),
            AckOutcome::Unexpected {
                received: 0x05,
                expected: 0x02
            }
        );
        assert!(m.is_pending(), "意外 ACK 不得清除 pending");

        assert_eq!(m.on_ack(0x02), AckOutcome::Cleared);
        assert!(!m.is_pending());
    }

    #[test]
    fn ack_without_pending_is_ignored() {
        let mut m = RetryMachine::new();
        assert_eq!(m.on_ack(0x02), AckOutcome::Ignored);
    }

    #[test]
    fn nak_backoff_doubles_per_retry() {
        let mut m = RetryMachine::new();
        m.send(vec![0xBB], 0x02);
        assert_eq!(m.on_nak(0x02), NakOutcome::Retry { delay_ms: 50 });
        assert_eq!(m.on_nak(0x02), NakOutcome::Retry { delay_ms: 100 });
        assert_eq!(m.on_nak(0x02), NakOutcome::Retry { delay_ms: 200 });
        assert_eq!(m.on_nak(0x02), NakOutcome::Retry { delay_ms: 400 });
    }

    // 注：delay 序列 [50,100,200,400] 的断言在 nak_exhaustion_aborts_and_clears
    // 中一并覆盖，此处保持独立验证前两次翻倍。

    #[test]
    fn nak_exhaustion_aborts_and_clears() {
        let mut m = RetryMachine::new();
        m.send(vec![0xBB], 0x02);
        // 前 MAX_RETRIES-1 次：指数退避；第 MAX_RETRIES 次：AbortAll + 报错
        for expected in [50u64, 100, 200, 400] {
            assert_eq!(m.on_nak(0x02), NakOutcome::Retry { delay_ms: expected });
        }
        assert_eq!(m.on_nak(0x02), NakOutcome::AbortAndError);
        assert!(!m.is_pending());
    }

    #[test]
    fn nak_for_other_command_is_ignored() {
        let mut m = RetryMachine::new();
        m.send(vec![0xBB], 0x02);
        assert_eq!(m.on_nak(0x05), NakOutcome::Ignored);
        assert!(m.is_pending());
    }
}
