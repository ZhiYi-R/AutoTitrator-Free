"""AutoTitrator 通信协议封装包。

提供 ProtocolHandler（不可见 QWidget），封装上下位机间的
二进制帧协议（上行 AA 55 / 下行 BB 55 + XOR Checksum）。

典型用法::

    from Communication import ProtocolHandler
    com = ProtocolHandler(port="/dev/ttyUSB0", baudrate=115200)
    com.spectral_data.connect(self.on_spectral)
    com.connect()
"""

from Communication.protocol import ProtocolHandler

__all__ = ["ProtocolHandler"]

