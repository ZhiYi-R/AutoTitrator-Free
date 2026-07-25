#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::IWDG {

class KR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteKEY(ValueType value) noexcept { Reg::Write<F_KEY>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40003000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_KEY = CortexM3::Field<ValueType, 0, 16>;
};

class PR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPR() noexcept -> ValueType { return Reg::Read<F_PR>(); }
    static void WritePR(ValueType value) noexcept { Reg::Write<F_PR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40003004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PR = CortexM3::Field<ValueType, 0, 3>;
};

class RLR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000FFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRL() noexcept -> ValueType { return Reg::Read<F_RL>(); }
    static void WriteRL(ValueType value) noexcept { Reg::Write<F_RL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40003008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RL = CortexM3::Field<ValueType, 0, 12>;
};

class SR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadPVU() noexcept -> ValueType { return Reg::Read<F_PVU>(); }
    static auto ReadRVU() noexcept -> ValueType { return Reg::Read<F_RVU>(); }

private:
    static constexpr std::uintptr_t Address = 0x4000300c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PVU = CortexM3::Field<ValueType, 0, 1>;
    using F_RVU = CortexM3::Field<ValueType, 1, 1>;
};

} // namespace STM32F103::IWDG
