//! 上下位机通信协议层 — Python `Communication/protocol.py` 的移植。

pub mod crc;
pub mod frames;
pub mod handler;
pub mod parser;
pub mod retry;

pub use frames::{DownlinkCommand, UplinkFrame};
pub use handler::{list_ports, Event, PortInfo, ProtocolHandler};
