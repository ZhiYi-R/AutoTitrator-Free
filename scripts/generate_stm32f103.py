#!/usr/bin/env python3
r"""Generate peripheral register headers from a CMSIS-SVD file.

Usage:
    uv run scripts/generate_stm32f103.py
    uv run scripts/generate_stm32f103.py \
        --svd "D:\Tools\STM32CubeProgrammer\SVD\Cores\Cortex-M3.svd" \
        --out include/cortex-m3 \
        --namespace CortexM3

Each generated header contains one pure-static singleton class per register,
with typed field accessors.  Access permissions are derived from the SVD
<access> attributes.
"""

from __future__ import annotations

import argparse
import re
import shutil
from pathlib import Path

from cmsis_svd.model import SVDAccessType
from cmsis_svd.parser import SVDParser

DEFAULT_SVD_PATH = Path(r"D:\Tools\STM32CubeProgrammer\SVD\STM32F103.svd")
DEFAULT_OUTPUT_DIR = Path("include/stm32f103")
DEFAULT_NAMESPACE = "STM32F103"


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

    seen_field_names: set[str] = set()
    for field in reg.fields or []:
        raw_field_name = make_identifier(field.name)
        bit_offset = field.bit_offset or 0
        bit_width = field.bit_width or 1

        # Disambiguate duplicate field names within the same register by
        # appending the bit offset.  This can happen in some SVD files
        # (e.g. Cortex-M3 ID_ISAR2 has two "MultiAccessInt_instrs" fields).
        field_name = raw_field_name
        if raw_field_name in seen_field_names:
            field_name = f"{raw_field_name}_Pos{bit_offset}"
        seen_field_names.add(raw_field_name)

        field_type_name = f"F_{field_name}"

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


def generate_peripheral_header(peripheral, namespace_prefix: str) -> str:
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

namespace {namespace_prefix}::{namespace_name} {{

{body}

}} // namespace {namespace_prefix}::{namespace_name}
"""


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Generate C++ register headers from a CMSIS-SVD file."
    )
    parser.add_argument(
        "--svd",
        type=Path,
        default=DEFAULT_SVD_PATH,
        help=f"Path to the CMSIS-SVD file (default: {DEFAULT_SVD_PATH})",
    )
    parser.add_argument(
        "--out",
        type=Path,
        default=DEFAULT_OUTPUT_DIR,
        help=f"Output directory for generated headers (default: {DEFAULT_OUTPUT_DIR})",
    )
    parser.add_argument(
        "--namespace",
        default=DEFAULT_NAMESPACE,
        help=f"Top-level C++ namespace (default: {DEFAULT_NAMESPACE})",
    )
    args = parser.parse_args()

    svd_parser = SVDParser.for_xml_file(str(args.svd))
    device = svd_parser.get_device()

    if args.out.exists():
        shutil.rmtree(args.out)
    args.out.mkdir(parents=True, exist_ok=True)

    generated: list[str] = []
    for peripheral in device.peripherals:
        header_name = f"{make_identifier(peripheral.name)}.hpp"
        header_path = args.out / header_name
        header_path.write_text(
            generate_peripheral_header(peripheral, args.namespace), encoding="utf-8"
        )
        generated.append(header_name)

    print(f"Generated {len(generated)} peripheral headers in {args.out}:")
    for name in sorted(generated):
        print(f"  {name}")


if __name__ == "__main__":
    main()
