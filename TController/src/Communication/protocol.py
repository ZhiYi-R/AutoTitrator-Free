"""
ProtocolHandler — 不可见 QWidget，封装上下位机通信协议。

上行帧 (MCU → Host)::
    AA 55 | 类型(1B) | 数据(NB) | CRC8(类型+数据)

下行帧 (Host → MCU)::
    BB 55 | 命令(1B) | 参数(NB) | CRC8(命令+参数)

使用方法::

    com = ProtocolHandler(port="/dev/ttyUSB0", baudrate=115200)
    com.spectral_data.connect(self.on_spectral)
    com.connect()
    com.send_frerun(1)
"""

from __future__ import annotations

from collections import deque
from enum import IntEnum, auto

import serial
from PySide6.QtCore import QObject, QThread, QTimer, Signal

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
    0x01: 20,  # Spectral — 10 x uint16 LE
    0x02: 6,  # ADC      — 2 x uint16 LE (ADC value + pump2_pos)
    0x81: 0,  # ACK
    0x82: 4,  # Pump1 done
    0x83: 4,  # Pump2 done
    0x84: 4,  # Pump1 stop report
    0x85: 4,  # Pump2 stop report
    0x86: 4,  # Pump1 progress report
    0x87: 4,  # Pump2 progress report
    0xFF: 0,  # NAK
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
#  上行帧解析器（状态机）
# ======================================================================


class _State(IntEnum):
    SYNC = auto()
    TYPE = auto()
    DATA = auto()
    CHECKSUM = auto()


class _UplinkParser(QObject):
    """逐字节状态机，解析 AA 55 上行帧。"""

    frame_ready = Signal(int, bytes)  # type, payload

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.reset()

    def reset(self) -> None:
        self._state = _State.SYNC
        self._type = 0
        self._data = bytearray()
        self._data_len = 0
        self._buf = bytearray()

    def feed(self, data: bytes) -> None:
        for b in data:
            self._feed_byte(b)

    def _feed_byte(self, b: int) -> None:
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
                return
            self._data.clear()
            self._state = _State.CHECKSUM if self._data_len == 0 else _State.DATA

        elif self._state == _State.DATA:
            self._data.append(b)
            if len(self._data) >= self._data_len:
                self._state = _State.CHECKSUM

        elif self._state == _State.CHECKSUM:
            cs = _crc8(bytes([self._type]) + bytes(self._data))
            if cs == b:
                self.frame_ready.emit(self._type, bytes(self._data))
            self.reset()


# ======================================================================
#  后台串口读取线程
# ======================================================================


class _SerialReader(QThread):
    """后台读取串口数据、解析上行帧并存入 FIFO。"""

    frame_ready = Signal(int, bytes)
    raw_data = Signal(bytes)
    error_occurred = Signal(str)
    connection_made = Signal()
    connection_lost = Signal()

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self._port: serial.Serial | None = None
        self._running = False
        self._parser = _UplinkParser()
        self._parser.frame_ready.connect(self._on_frame)

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
            if not self.isRunning():
                self.start()
            self.connection_made.emit()
        except serial.SerialException as exc:
            self.error_occurred.emit(str(exc))

    def close(self) -> None:
        self._running = False
        if self._port and self._port.is_open:
            try:
                self._port.close()
            except Exception:
                pass
        self._port = None
        self.connection_lost.emit()

    @property
    def is_open(self) -> bool:
        return self._port is not None and self._port.is_open

    def write(self, data: bytes) -> None:
        if self._port and self._port.is_open:
            self._port.write(data)

    # ---- 帧分发 ----

    def _on_frame(self, typ: int, payload: bytes) -> None:
        if typ == 0x01 and len(payload) == 20:
            vals = [payload[i] | (payload[i + 1] << 8) for i in range(0, 20, 2)]
            self.spectral_queue.append(vals)
        elif typ == 0x02 and len(payload) == 6:
            val = payload[0] | (payload[1] << 8)
            self.adc_queue.append(val)
        self.frame_ready.emit(typ, payload)

    # ---- 线程主循环 ----

    def run(self) -> None:
        while self._running and self._port and self._port.is_open:
            try:
                if self._port.in_waiting:
                    raw = self._port.read(self._port.in_waiting)
                    self.raw_queue.append(raw)
                    self._parser.feed(raw)
                else:
                    self.msleep(5)
            except serial.SerialException as exc:
                self.error_occurred.emit(str(exc))
                break
            except Exception as exc:
                self.error_occurred.emit(str(exc))
                break
        self.close()


# ======================================================================
#  协议封装（对外接口）
# ======================================================================


class ProtocolHandler(QObject):
    """不可见 QObject，封装上下位机串口通信协议。

    串口参数通过构造函数传入，调用 connect() 建立连接。
    接收数据通过 Qt 信号 / pop_xxx() 方法获取，发送命令
    通过 send_xxx() 方法。
    """

    # ---- 数据信号 ----
    spectral_data = Signal(list)
    """10 通道光谱值 [F1, ..., F8, Clear, NIR]。"""

    adc_data = Signal(int, int)
    """ADC 过采样读数 + Pump2 位置 (raw_adc, pump2_pos)。"""

    # ---- 状态信号 ----
    ack_received = Signal()
    nak_received = Signal()
    pump_done = Signal(int)
    """泵完成报告，参数为位置(uint32)。"""
    stop_rpt = Signal(int)
    """泵停止报告，参数为位置(uint32)。"""
    pump1_progress = Signal(int)
    """Pump1 脉冲进度（每 1000 脉冲/次），参数为当前位置(uint32)。"""
    pump2_progress = Signal(int)
    """Pump2 脉冲进度（每 1000 脉冲/次），参数为当前位置(uint32)。"""
    error_occurred = Signal(str)
    connected = Signal()
    disconnected = Signal()

    def __init__(
        self, port: str = "", baudrate: int = 115200, parent: QObject | None = None
    ) -> None:
        super().__init__(parent)
        self._port_name = port
        self._baudrate = baudrate
        self._reader = _SerialReader(self)

        self._reader.frame_ready.connect(self._on_frame_ready)
        self._reader.error_occurred.connect(self.error_occurred)
        self._reader.connection_made.connect(self.connected)
        self._reader.connection_lost.connect(self.disconnected)

        # ACK/NAK 重试
        self._pending_cmd: bytes | None = None
        self._retry_count: int = 0
        self._max_retries: int = 5
        self._retry_timer: QTimer | None = None
        self._backoff_ms: int = 50
        self._ack_received = False

        self.ack_received.connect(self._on_ack)
        self.nak_received.connect(self._on_nak)

    # ---- 连接管理 ----

    @property
    def is_open(self) -> bool:
        return self._reader.is_open

    def connect(self) -> None:  # type: ignore[override]
        if not self._port_name:
            self.error_occurred.emit("未指定串口端口")
            return
        self._reader.open(self._port_name, self._baudrate)

    def disconnect(self) -> None:  # type: ignore[override]
        self._reader.close()

    def reconfigure(self, port: str, baudrate: int) -> None:
        if self.is_open:
            self.disconnect()
        self._port_name = port
        self._baudrate = baudrate

    # ---- FIFO 读取 ----

    def pop_spectral(self) -> list[list[int]]:
        q = self._reader.spectral_queue
        return [q.popleft() for _ in range(len(q))]

    def pop_adc(self) -> list[int]:
        q = self._reader.adc_queue
        return [q.popleft() for _ in range(len(q))]

    # ---- 内部：上行帧分发 ----

    def _on_frame_ready(self, typ: int, payload: bytes) -> None:
        if typ == 0x01 and len(payload) == 20:
            vals = [payload[i] | (payload[i + 1] << 8) for i in range(0, 20, 2)]
            self.spectral_data.emit(vals)
        elif typ == 0x02 and len(payload) == 6:
            val = payload[0] | (payload[1] << 8)
            pos = (
                payload[2] | (payload[3] << 8) | (payload[4] << 16) | (payload[5] << 24)
            )
            self.adc_data.emit(val, pos)
        elif typ == 0x81:
            self.ack_received.emit()
        elif typ == 0xFF:
            self.nak_received.emit()
        elif typ == 0x82 and len(payload) == 4:
            pos = (
                payload[0] | (payload[1] << 8) | (payload[2] << 16) | (payload[3] << 24)
            )
            self.pump_done.emit(pos)
        elif typ in (0x83, 0x84, 0x85) and len(payload) == 4:
            pos = (
                payload[0] | (payload[1] << 8) | (payload[2] << 16) | (payload[3] << 24)
            )
            self.stop_rpt.emit(pos)
        elif typ == 0x86 and len(payload) == 4:
            pos = (
                payload[0] | (payload[1] << 8) | (payload[2] << 16) | (payload[3] << 24)
            )
            self.pump1_progress.emit(pos)
        elif typ == 0x87 and len(payload) == 4:
            pos = (
                payload[0] | (payload[1] << 8) | (payload[2] << 16) | (payload[3] << 24)
            )
            self.pump2_progress.emit(pos)

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
        self._reader.write(self._build_downlink(0x01, params))

    def send_frerun(self, pump_id: int) -> None:
        self._reader.write(self._build_downlink(0x02, bytes([pump_id])))

    def send_frestop(self, pump_id: int = 0xFF) -> None:
        self._reader.write(self._build_downlink(0x03, bytes([pump_id])))

    def send_abort(self, pump_id: int = 0xFF) -> None:
        self._reader.write(self._build_downlink(0x04, bytes([pump_id])))

    def send_reset(self) -> None:
        """下发 MCU 复位指令。"""
        self._reader.write(self._build_downlink(0x06))

    def send_raw(self, data: bytes) -> None:
        """发送已在外部构建好的完整帧。"""
        self._reader.write(data)

    # ---- 心跳 / 看门狗 ----

    def enable_watchdog(self) -> None:
        """启用心跳看门狗（发送 0x05 0x01）。"""
        self.send_cmd(0x05, bytes([0x01]))

    def send_heartbeat(self) -> None:
        """发送心跳帧，维持下位机看门狗（param=0x01 保持使能，复位超时计时器）。"""
        self._reader.write(b"\xbb\x55\x05\x01\x46")

    # ---- 带重试的命令发送 ----

    def _on_ack(self) -> None:
        self._ack_received = True
        self._pending_cmd = None
        self._retry_count = 0
        if self._retry_timer:
            self._retry_timer.stop()

    def _on_first_timeout(self) -> None:
        """首包 100ms 超时：视同 NAK，触发退避重传。"""
        if not self._ack_received and self._pending_cmd is not None:
            self._on_nak()

    def _on_nak(self) -> None:
        if self._pending_cmd is None:
            return
        self._retry_count += 1
        if self._retry_count >= self._max_retries:
            self._send_abort_and_error()
            return
        # 指数退避
        delay = self._backoff_ms * (2 ** (self._retry_count - 1))
        if self._retry_timer is None:
            self._retry_timer = QTimer(self)
            self._retry_timer.setSingleShot(True)
        self._retry_timer.timeout.disconnect()
        self._retry_timer.timeout.connect(self._retry_send)
        self._retry_timer.start(delay)

    def _retry_send(self) -> None:
        if self._pending_cmd:
            self._reader.write(self._pending_cmd)

    def _send_abort_and_error(self) -> None:
        self._pending_cmd = None
        self._retry_count = 0
        if self._retry_timer:
            self._retry_timer.stop()
        self.send_abort(0xFF)
        self.error_occurred.emit("下位机通讯异常")

    def send_cmd(self, cmd: int, params: bytes = b"") -> None:
        """发送命令并启动 ACK/NAK 重试监控（含 100ms 首包超时）。"""
        frame = self._build_downlink(cmd, params)
        self._pending_cmd = frame
        self._ack_received = False
        self._retry_count = 0
        self._reader.write(frame)
        # 启动首包超时定时器
        if self._retry_timer is None:
            self._retry_timer = QTimer(self)
            self._retry_timer.setSingleShot(True)
            self._retry_timer.timeout.connect(self._on_first_timeout)
        self._retry_timer.start(100)

    # ---- 生命周期 ----

    def shutdown(self) -> None:
        self._reader.close()
        self._reader.wait(1000)
