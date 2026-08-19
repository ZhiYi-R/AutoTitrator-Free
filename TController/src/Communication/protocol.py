"""
ProtocolHandler — 封装上下位机通信协议（threading + queue，无 Qt 依赖）。

上行帧 (MCU → Host)::
    AA 55 | 类型(1B) | 数据(NB) | CRC8(类型+数据)

下行帧 (Host → MCU)::
    BB 55 | 命令(1B) | 参数(NB) | CRC8(命令+参数)

使用方法::

    com = ProtocolHandler(port="/dev/ttyUSB0", baudrate=115200)
    com.on("spectral", on_spectral)
    com.on("adc", on_adc)
    com.connect()
    com.send_frerun(1)

    # GUI 主循环中轮询事件
    com.poll()
"""

from __future__ import annotations

import queue
import threading
import time
from collections import deque
from collections.abc import Callable
from dataclasses import dataclass
from enum import IntEnum, auto
from typing import Any

import serial

# ---- CRC-8 (Maxim-Dallas, poly = 0x31) ----


def _crc8_update(crc: int, data: int) -> int:
    crc ^= data
    for _ in range(8):
        crc = ((crc << 1) ^ 0x31) if (crc & 0x80) else (crc << 1)
    return crc & 0xFF


def _crc8(data: bytes) -> int:
    crc = 0
    for b in data:
        crc = _crc8_update(crc, b)
    return crc


# ---- 上行帧类型 & 载荷长度 ----

_UPLINK: dict[int, int] = {
    0x00: 1,  # ACK       — echo_cmd(1)
    0x01: 1,  # NAK       — echo_cmd(1)
    0x10: 5,  # PumpPos   — pump_id(1) + position(4) LE
    0x11: 5,  # PumpDone  — pump_id(1) + position(4) LE
    0x20: 11,  # ADC      — sum(4) + samples(2) + shift(1) + pump2_pos(4)
    0x30: 22,  # Spectral — 10 x uint16 LE + reserved(2)
    0x40: 4,  # Heartbeat — uptime_ms(4)
}

# ---- 下行命令 & 参数长度 ----

_DOWNLINK: dict[int, int] = {
    0x01: 5,  # MaxCount — pump_id(1) + count(4)
    0x02: 1,  # FreeRun  — pump_id(1)
    0x03: 1,  # FreeStop — pump_id(1)
    0x04: 1,  # AbortAll — pump_id(1), 0xFF=全部
    0x05: 1,  # Heartbeat — 0x01=enable watchdog
    0x06: 0,  # Reset — 无载荷
}

# ---- FIFO 上限 ----

FIFO_SPECTRAL_MAX = 4096
FIFO_ADC_MAX = 16384
FIFO_RAW_CHUNKS = 512


# ======================================================================
#  事件（替代 Qt Signal）
# ======================================================================


@dataclass
class _Event:
    """通信事件，由后台线程写入队列，由 poll() 在主线程消费。"""

    kind: str
    """事件类型：connected / disconnected / error / spectral / adc / ack / nak / pump_done / pump1_progress / pump2_progress / heartbeat"""

    data: Any = None
    """事件数据，类型随 kind 变化。"""


# ======================================================================
#  上行帧解析器（状态机）
# ======================================================================


class _State(IntEnum):
    SYNC = auto()
    TYPE = auto()
    DATA = auto()
    CHECKSUM = auto()


class _UplinkParser:
    """逐字节状态机，解析 AA 55 上行帧。"""

    def __init__(self) -> None:
        self.reset()

    def reset(self) -> None:
        self._state = _State.SYNC
        self._type = 0
        self._data = bytearray()
        self._data_len = 0
        self._buf = bytearray()

    def feed(self, data: bytes) -> list[tuple[int, bytes]]:
        """喂入字节流，返回本批次解析出的 (type, payload) 列表。"""
        frames: list[tuple[int, bytes]] = []
        for b in data:
            frame = self._feed_byte(b)
            if frame is not None:
                frames.append(frame)
        return frames

    def _feed_byte(self, b: int) -> tuple[int, bytes] | None:
        if self._state == _State.SYNC:
            if b == 0xAA:
                self._buf.append(b)
            elif b == 0x55 and self._buf and self._buf[-1] == 0xAA:
                self._state = _State.TYPE
                self._buf.clear()
            else:
                self._buf.clear()

        elif self._state == _State.TYPE:
            self._type = b
            self._data_len = _UPLINK.get(b, 0xFFFF)
            if self._data_len == 0xFFFF:
                self.reset()
                return None
            self._data.clear()
            self._state = _State.CHECKSUM if self._data_len == 0 else _State.DATA

        elif self._state == _State.DATA:
            self._data.append(b)
            if len(self._data) >= self._data_len:
                self._state = _State.CHECKSUM

        elif self._state == _State.CHECKSUM:
            cs = _crc8(bytes([self._type]) + bytes(self._data))
            result: tuple[int, bytes] | None = None
            if cs == b:
                result = (self._type, bytes(self._data))
            self.reset()
            return result

        return None


# ======================================================================
#  后台串口读取线程
# ======================================================================


class _SerialReader(threading.Thread):
    """后台读取串口数据、解析上行帧并写入事件队列。"""

    def __init__(self, event_queue: queue.Queue[_Event]) -> None:
        super().__init__(daemon=True)
        self._port: serial.Serial | None = None
        self._running = False
        self._parser = _UplinkParser()
        self._event_queue = event_queue

        self.spectral_queue: deque[list[int]] = deque(maxlen=FIFO_SPECTRAL_MAX)
        self.adc_queue: deque[int] = deque(maxlen=FIFO_ADC_MAX)
        self.raw_queue: deque[bytes] = deque(maxlen=FIFO_RAW_CHUNKS)

    # ---- 公开接口 ----

    def open(self, port_name: str, baudrate: int) -> None:
        if self._port and self._port.is_open:
            self.close()
        try:
            self._port = serial.Serial(
                port=port_name,
                baudrate=baudrate,
                bytesize=serial.EIGHTBITS,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                timeout=0.05,
            )
            self._parser.reset()
            self._running = True
            if not self.is_alive():
                self.start()
            self._event_queue.put(_Event("connected"))
        except serial.SerialException as exc:
            self._event_queue.put(_Event("error", str(exc)))

    def close(self) -> None:
        self._running = False
        if self._port and self._port.is_open:
            try:
                self._port.close()
            except Exception:
                pass
        self._port = None
        self._event_queue.put(_Event("disconnected"))

    @property
    def is_open(self) -> bool:
        return self._port is not None and self._port.is_open

    def write(self, data: bytes) -> None:
        if self._port and self._port.is_open:
            self._port.write(data)

    # ---- 帧分发 ----

    @staticmethod
    def _u32(payload: bytes, off: int) -> int:
        return (
            payload[off]
            | (payload[off + 1] << 8)
            | (payload[off + 2] << 16)
            | (payload[off + 3] << 24)
        )

    def _on_frame(self, typ: int, payload: bytes) -> None:
        if typ == 0x00 and len(payload) == 1:
            self._event_queue.put(_Event("ack", payload[0]))
        elif typ == 0x01 and len(payload) == 1:
            self._event_queue.put(_Event("nak", payload[0]))
        elif typ == 0x10 and len(payload) == 5:
            pump_id = payload[0]
            pos = self._u32(payload, 1)
            kind = "pump1_progress" if pump_id == 1 else "pump2_progress"
            self._event_queue.put(_Event(kind, pos))
        elif typ == 0x11 and len(payload) == 5:
            pump_id = payload[0]
            pos = self._u32(payload, 1)
            self._event_queue.put(_Event("pump_done", (pump_id, pos)))
        elif typ == 0x20 and len(payload) == 11:
            acc = self._u32(payload, 0)
            shift = payload[6]
            val = (acc >> shift) & 0xFFFF
            pos = self._u32(payload, 7)
            self.adc_queue.append(val)
            self._event_queue.put(_Event("adc", (val, pos)))
        elif typ == 0x30 and len(payload) == 22:
            # 前 20 字节为 F1..F8/Clear/NIR，末 2 字节保留
            vals = [payload[i] | (payload[i + 1] << 8) for i in range(0, 20, 2)]
            self.spectral_queue.append(vals)
            self._event_queue.put(_Event("spectral", vals))
        elif typ == 0x40 and len(payload) == 4:
            self._event_queue.put(_Event("heartbeat", self._u32(payload, 0)))

    # ---- 线程主循环 ----

    def run(self) -> None:
        while self._running and self._port and self._port.is_open:
            try:
                if self._port.in_waiting:
                    raw = self._port.read(self._port.in_waiting)
                    self.raw_queue.append(raw)
                    frames = self._parser.feed(raw)
                    for typ, payload in frames:
                        self._on_frame(typ, payload)
                else:
                    time.sleep(0.005)
            except serial.SerialException as exc:
                self._event_queue.put(_Event("error", str(exc)))
                break
            except Exception as exc:
                self._event_queue.put(_Event("error", str(exc)))
                break
        self.close()


# ======================================================================
#  协议封装（对外接口）
# ======================================================================


class ProtocolHandler:
    """封装上下位机串口通信协议（threading + queue，无 Qt 依赖）。

    串口参数通过构造函数传入，调用 connect() 建立连接。
    接收数据通过 on() 注册回调 + poll() 轮询，发送命令
    通过 send_xxx() 方法。
    """

    def __init__(self, port: str = "", baudrate: int = 115200) -> None:
        self._port_name = port
        self._baudrate = baudrate
        self._event_queue: queue.Queue[_Event] = queue.Queue()
        self._reader = _SerialReader(self._event_queue)

        # 用户回调
        self._callbacks: dict[str, list[Callable[[Any], None]]] = {}

        # 单次回调（替代 Qt SingleShotConnection）
        self._pump_done_once: Callable[[tuple[int, int]], None] | None = None

        # ACK/NAK 重试
        self._pending_cmd: bytes | None = None
        self._pending_cmd_id: int | None = None
        self._retry_count: int = 0
        self._max_retries: int = 5
        self._backoff_ms: int = 50
        self._ack_received: bool = False
        self._timeout_flag: bool = False
        self._first_timeout_timer: threading.Timer | None = None
        self._retry_timer: threading.Timer | None = None

    # ---- 回调注册 ----

    def on(self, kind: str, callback: Callable[[Any], None]) -> None:
        """注册事件回调。

        kind 取值：connected / disconnected / error / spectral / adc /
        ack / nak / pump_done / pump1_progress / pump2_progress / heartbeat

        pump_done 事件数据为 (pump_id, position) 元组。
        """
        self._callbacks.setdefault(kind, []).append(callback)

    def request_pump_done_once(
        self, callback: Callable[[tuple[int, int]], None]
    ) -> None:
        """注册单次 pump_done 回调（触发后自动清除，替代 SingleShotConnection）。

        回调参数为 (pump_id, position) 元组。
        """
        self._pump_done_once = callback

    # ---- 事件轮询（GUI 主线程调用）----

    def poll(self) -> None:
        """排空事件队列，在 GUI 主线程中周期性调用（如 root.after(50, poll)）。"""
        # 检查首包超时标志（由 Timer 线程设置）
        if self._timeout_flag:
            self._timeout_flag = False
            if not self._ack_received and self._pending_cmd is not None:
                self._handle_nak(self._pending_cmd_id)

        # 排空事件队列
        while True:
            try:
                event = self._event_queue.get_nowait()
            except queue.Empty:
                break
            self._dispatch(event)

    def _dispatch(self, event: _Event) -> None:
        # 内部事件先处理
        if event.kind == "ack":
            self._on_ack(event.data)
        elif event.kind == "nak":
            self._handle_nak(event.data)

        # 单次 pump_done 回调
        if event.kind == "pump_done" and self._pump_done_once is not None:
            cb = self._pump_done_once
            self._pump_done_once = None
            cb(event.data)

        # 用户回调
        for cb in self._callbacks.get(event.kind, []):
            cb(event.data)

    # ---- 连接管理 ----

    @property
    def is_open(self) -> bool:
        return self._reader.is_open

    def connect(self) -> None:
        if not self._port_name:
            self._event_queue.put(_Event("error", "未指定串口端口"))
            return
        self._reader.open(self._port_name, self._baudrate)

    def disconnect(self) -> None:
        self._reader.close()

    def reconfigure(self, port: str, baudrate: int) -> None:
        if self.is_open:
            self.disconnect()
        self._port_name = port
        self._baudrate = baudrate

    # ---- 命令发送（下行帧） ----

    @staticmethod
    def _build_downlink(cmd: int, params: bytes = b"") -> bytes:
        cs = _crc8(bytes([cmd]) + params)
        return b"\xbb\x55" + bytes([cmd]) + params + bytes([cs])

    def send_maxcount(self, pump_id: int, count: int) -> None:
        params = bytes(
            [
                pump_id,
                count & 0xFF,
                (count >> 8) & 0xFF,
                (count >> 16) & 0xFF,
                (count >> 24) & 0xFF,
            ]
        )
        self.send_cmd(0x01, params)

    def send_frerun(self, pump_id: int) -> None:
        self.send_cmd(0x02, bytes([pump_id]))

    def send_frestop(self, pump_id: int = 0xFF) -> None:
        """正常停止泵（0x03）。"""
        self.send_cmd(0x03, bytes([pump_id]))

    def send_abort(self, pump_id: int = 0xFF) -> None:
        """紧急停止泵（0x04），功能等价于 0x03 但语义用于异常情况。"""
        self.send_cmd(0x04, bytes([pump_id]))

    def send_reset(self) -> None:
        """下发 MCU 复位指令。"""
        self.send_cmd(0x06)

    def send_raw(self, data: bytes) -> None:
        """发送已在外部构建好的完整帧。"""
        self._reader.write(data)

    # ---- 心跳 / 看门狗 ----

    def enable_watchdog(self) -> None:
        """启用心跳看门狗（发送 0x05 0x01）。"""
        self.send_cmd(0x05, bytes([0x01]))

    def send_heartbeat(self) -> None:
        """发送心跳帧，维持下位机看门狗（带 ACK 重试，防止丢包导致误触发）。"""
        self.send_cmd(0x05, bytes([0x01]))

    # ---- 带重试的命令发送 ----

    def _on_ack(self, cmd: int) -> None:
        if self._pending_cmd_id != cmd:
            # 收到不匹配的 ACK，可能是重复响应或状态不同步
            if self._pending_cmd_id is not None:
                self._event_queue.put(
                    _Event("error", f"收到意外 ACK 0x{cmd:02X}，期望 0x{self._pending_cmd_id:02X}")
                )
            return
        self._ack_received = True
        self._pending_cmd = None
        self._pending_cmd_id = None
        self._retry_count = 0
        self._cancel_timers()

    def _handle_nak(self, cmd: int) -> None:
        """NAK 处理：指数退避重传（在主线程 poll() 中调用）。"""
        if self._pending_cmd is None or self._pending_cmd_id != cmd:
            return
        self._retry_count += 1
        if self._retry_count >= self._max_retries:
            self._send_abort_and_error()
            return
        # 指数退避
        delay = self._backoff_ms * (2 ** (self._retry_count - 1)) / 1000.0
        self._cancel_timers()
        self._retry_timer = threading.Timer(delay, self._retry_send)
        self._retry_timer.daemon = True
        self._retry_timer.start()

    def _retry_send(self) -> None:
        """重传（Timer 线程调用，仅写串口，线程安全）。"""
        if self._pending_cmd:
            self._reader.write(self._pending_cmd)
            self._first_timeout_timer = threading.Timer(0.1, self._on_first_timeout)
            self._first_timeout_timer.daemon = True
            self._first_timeout_timer.start()

    def _send_abort_and_error(self) -> None:
        self._pending_cmd = None
        self._pending_cmd_id = None
        self._retry_count = 0
        self._cancel_timers()
        self._reader.write(self._build_downlink(0x04, bytes([0xFF])))
        self._event_queue.put(_Event("error", "下位机通讯异常"))

    def _cancel_timers(self) -> None:
        if self._first_timeout_timer is not None:
            self._first_timeout_timer.cancel()
            self._first_timeout_timer = None
        if self._retry_timer is not None:
            self._retry_timer.cancel()
            self._retry_timer = None

    def send_cmd(self, cmd: int, params: bytes = b"") -> None:
        """发送命令并启动 ACK/NAK 重试监控（含 100ms 首包超时）。"""
        expected_len = _DOWNLINK.get(cmd)
        if expected_len is None or len(params) != expected_len:
            raise ValueError(f"invalid parameters for command 0x{cmd:02X}")
        frame = self._build_downlink(cmd, params)
        self._cancel_timers()
        self._pending_cmd = frame
        self._pending_cmd_id = cmd
        self._ack_received = False
        self._retry_count = 0
        self._reader.write(frame)
        # 启动首包超时定时器
        self._first_timeout_timer = threading.Timer(0.1, self._on_first_timeout)
        self._first_timeout_timer.daemon = True
        self._first_timeout_timer.start()

    def _on_first_timeout(self) -> None:
        """首包 100ms 超时（Timer 线程调用，仅设标志，由 poll() 处理）。"""
        self._timeout_flag = True

    # ---- 生命周期 ----

    def shutdown(self) -> None:
        self._cancel_timers()
        self._reader.close()
        self._reader.join(timeout=2.0)


__all__ = ["ProtocolHandler"]
