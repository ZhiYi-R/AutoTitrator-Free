#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::CRC {

class DR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFFFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDR() noexcept -> ValueType { return Reg::Read<F_DR>(); }
    static void WriteDR(ValueType value) noexcept { Reg::Write<F_DR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40023000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DR = CortexM3::Field<ValueType, 0, 32>;
};

class IDR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadIDR() noexcept -> ValueType { return Reg::Read<F_IDR>(); }
    static void WriteIDR(ValueType value) noexcept { Reg::Write<F_IDR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40023004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_IDR = CortexM3::Field<ValueType, 0, 8>;
};

class CR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteRESET(ValueType value) noexcept { Reg::Write<F_RESET>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40023008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RESET = CortexM3::Field<ValueType, 0, 1>;
};

} // namespace STM32F103::CRC
