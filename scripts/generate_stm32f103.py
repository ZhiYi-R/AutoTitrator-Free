#!/usr/bin/env python3
r"""Generate STM32F103 peripheral register headers from CMSIS-SVD.

Usage:
    uv run scripts/generate_stm32f103.py

Input:
    D:\Tools\STM32CubeProgrammer\SVD\STM32F103.svd

Output:
    include/stm32f103/{Peripheral}.hpp

Each generated header contains one pure-static singleton class per register,
with typed field accessors.  Access permissions are derived from the SVD
<access> attributes.
"""

from __future__ import annotations

import re
import shutil
from pathlib import Path

from cmsis_svd.model import SVDAccessType
from cmsis_svd.parser import SVDParser

SVD_PATH = Path(r"D:\Tools\STM32CubeProgrammer\SVD\STM32F103.svd")
OUTPUT_DIR = Path("include/stm32f103")


def make_identifier(name: str) -> str:
    """Sanitize an SVD name to a valid C++ identifier.

    Keeps original casing as requested by the user.  Prepends an underscore
    if the name starts with a digit.
    """
    sanitized = re.sub(r"[^0-9a-zA-Z_]", "_", name)
    if sanitized and sanitized[0].isdigit():
        sanitized = "_" + sanitized
    return sanitized


def cpp_value_type(width_bits: int) -> str:
    """Map a register width in bits to the matching std::uintX_t."""
    if width_bits <= 8:
        return "std::uint8_t"
    if width_bits <= 16:
        return "std::uint16_t"
    return "std::uint32_t"


def access_to_rw(access: SVDAccessType | None) -> tuple[bool, bool]:
    """Return (can_read, can_write) for a given SVD access type."""
    if access is None:
        return (True, True)
    if access in (SVDAccessType.READ_WRITE, SVDAccessType.READ_WRITE_ONCE):
        return (True, True)
    if access is SVDAccessType.READ_ONLY:
        return (True, False)
    if access in (SVDAccessType.WRITE_ONLY, SVDAccessType.WRITE_ONCE):
        return (False, True)
    return (False, False)


def indent(lines: list[str], spaces: int = 4) -> list[str]:
    """Indent each line by a fixed number of spaces."""
    prefix = " " * spaces
    return [f"{prefix}{line}" for line in lines]


def generate_register_class(peripheral_name: str, reg, base_address: int) -> str:
    """Generate the C++ class for a single SVD register."""
    class_name = make_identifier(reg.name)
    address = base_address + (reg.address_offset or 0)
    width_bits = reg.size or 32
    value_type = cpp_value_type(width_bits)

    can_read, can_write = access_to_rw(reg.access)

    public_lines: list[str] = [f"using ValueType = {value_type};"]
    if reg.reset_value is not None:
        # Reset value is a full-width constant; use appropriate hex width.
        if width_bits <= 8:
            reset_str = f"0x{reg.reset_value:02X}"
        elif width_bits <= 16:
            reset_str = f"0x{reg.reset_value:04X}"
        else:
            reset_str = f"0x{reg.reset_value:08X}"
        public_lines.append(f"static constexpr ValueType ResetValue = {reset_str};")

    public_lines.append("")  # blank line before methods

    if can_read:
        public_lines.append(
            "static auto Read() noexcept -> ValueType { return Reg::Read(); }"
        )
    if can_write:
        public_lines.append(
            "static void Write(ValueType value) noexcept { Reg::Write(value); }"
        )

    private_lines: list[str] = [
        f"static constexpr std::uintptr_t Address = {hex(address)};",
        f"using Reg = CortexM3::Register<ValueType, Address>;",
    ]

    for field in reg.fields or []:
        field_name = make_identifier(field.name)
        field_type_name = f"F_{field_name}"
        bit_offset = field.bit_offset or 0
        bit_width = field.bit_width or 1

        private_lines.append(
            f"using {field_type_name} = CortexM3::Field<ValueType, {bit_offset}, {bit_width}>;"
        )

        f_can_read, f_can_write = access_to_rw(field.access)
        if f_can_read:
            public_lines.append(
                f"static auto Read{field_name}() noexcept -> ValueType {{ return Reg::Read<{field_type_name}>(); }}"
            )
        if f_can_write:
            public_lines.append(
                f"static void Write{field_name}(ValueType value) noexcept {{ Reg::Write<{field_type_name}>(value); }}"
            )

    class_body = (
        ["public:"] + indent(public_lines) + ["", "private:"] + indent(private_lines)
    )

    return f"class {class_name} {{\n" + "\n".join(class_body) + "\n};"


def generate_peripheral_header(peripheral) -> str:
    """Generate the full content for one peripheral header file."""
    namespace_name = make_identifier(peripheral.name)
    classes = [
        generate_register_class(peripheral.name, reg, peripheral.base_address)
        for reg in (peripheral.registers or [])
    ]

    if classes:
        body = "\n\n".join(classes)
    else:
        body = "// No registers defined for this peripheral in the SVD."

    return f"""#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::{namespace_name} {{

{body}

}} // namespace STM32F103::{namespace_name}
"""


def main() -> None:
    parser = SVDParser.for_xml_file(str(SVD_PATH))
    device = parser.get_device()

    if OUTPUT_DIR.exists():
        shutil.rmtree(OUTPUT_DIR)
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    generated: list[str] = []
    for peripheral in device.peripherals:
        header_name = f"{make_identifier(peripheral.name)}.hpp"
        header_path = OUTPUT_DIR / header_name
        header_path.write_text(generate_peripheral_header(peripheral), encoding="utf-8")
        generated.append(header_name)

    print(f"Generated {len(generated)} peripheral headers in {OUTPUT_DIR}:")
    for name in sorted(generated):
        print(f"  {name}")


if __name__ == "__main__":
    main()
