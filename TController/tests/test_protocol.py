from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parents[1] / "src"))

from Communication.protocol import (  # noqa: E402
    ProtocolHandler,
    _UplinkParser,
    _crc8,
)


def test_crc_and_uplink_parser() -> None:
    payload = bytes(range(11))
    frame = b"\xaa\x55\x20" + payload + bytes([_crc8(b"\x20" + payload)])
    assert _UplinkParser().feed(frame) == [(0x20, payload)]


def test_uplink_parser_resynchronizes_after_repeated_preamble() -> None:
    payload = b"\x01"
    frame = b"\xbb\xbb\xaa\x55\x00" + payload
    frame += bytes([_crc8(b"\x00" + payload)])
    assert _UplinkParser().feed(frame) == [(0x00, payload)]


def test_ack_requires_matching_pending_command() -> None:
    handler = ProtocolHandler()
    handler._pending_cmd = b"pending"
    handler._pending_cmd_id = 0x02
    handler._on_ack(0x05)
    assert handler._pending_cmd == b"pending"
    handler._on_ack(0x02)
    assert handler._pending_cmd is None


def test_send_heartbeat_does_not_overwrite_pending_command() -> None:
    handler = ProtocolHandler()
    pending = b"pending"
    handler._pending_cmd = pending
    handler._pending_cmd_id = 0x02
    handler._reader.write = lambda _data: None

    handler.send_heartbeat()

    assert handler._pending_cmd == pending
    assert handler._pending_cmd_id == 0x02


def test_send_cmd_rejects_invalid_parameter_length() -> None:
    handler = ProtocolHandler()
    try:
        handler.send_cmd(0x02, b"")
    except ValueError:
        pass
    else:
        raise AssertionError("invalid command parameters were accepted")
