"""AutoTitrator 通信协议封装包。

提供 ProtocolHandler，封装上下位机间的
二进制帧协议（上行 AA 55 / 下行 BB 55 + CRC8 Checksum）。

典型用法::

    from Communication import ProtocolHandler
    com = ProtocolHandler(port="/dev/ttyUSB0", baudrate=115200)
    com.on("spectral", on_spectral)
    com.connect()
    com.poll()  # GUI 主循环中周期性调用
"""

from Communication.protocol import ProtocolHandler

__all__ = ["ProtocolHandler"]
