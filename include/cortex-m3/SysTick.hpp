#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace CortexM3::SysTick {

class STCSR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCOUNTFLAG() noexcept -> ValueType { return Reg::Read<F_COUNTFLAG>(); }
    static void WriteCOUNTFLAG(ValueType value) noexcept { Reg::Write<F_COUNTFLAG>(value); }
    static auto ReadCLKSOURCE() noexcept -> ValueType { return Reg::Read<F_CLKSOURCE>(); }
    static void WriteCLKSOURCE(ValueType value) noexcept { Reg::Write<F_CLKSOURCE>(value); }
    static auto ReadTICKINT() noexcept -> ValueType { return Reg::Read<F_TICKINT>(); }
    static void WriteTICKINT(ValueType value) noexcept { Reg::Write<F_TICKINT>(value); }
    static auto ReadENABLE() noexcept -> ValueType { return Reg::Read<F_ENABLE>(); }
    static void WriteENABLE(ValueType value) noexcept { Reg::Write<F_ENABLE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_COUNTFLAG = CortexM3::Field<ValueType, 16, 1>;
    using F_CLKSOURCE = CortexM3::Field<ValueType, 2, 1>;
    using F_TICKINT = CortexM3::Field<ValueType, 1, 1>;
    using F_ENABLE = CortexM3::Field<ValueType, 0, 1>;
};

class STRVR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRELOAD() noexcept -> ValueType { return Reg::Read<F_RELOAD>(); }
    static void WriteRELOAD(ValueType value) noexcept { Reg::Write<F_RELOAD>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RELOAD = CortexM3::Field<ValueType, 0, 24>;
};

class STCVR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCURRENT() noexcept -> ValueType { return Reg::Read<F_CURRENT>(); }
    static void WriteCURRENT(ValueType value) noexcept { Reg::Write<F_CURRENT>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e018;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CURRENT = CortexM3::Field<ValueType, 0, 24>;
};

class STCR {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadNOREF() noexcept -> ValueType { return Reg::Read<F_NOREF>(); }
    static auto ReadSKEW() noexcept -> ValueType { return Reg::Read<F_SKEW>(); }
    static auto ReadTENMS() noexcept -> ValueType { return Reg::Read<F_TENMS>(); }

private:
    static constexpr std::uintptr_t Address = 0xe000e01c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NOREF = CortexM3::Field<ValueType, 31, 1>;
    using F_SKEW = CortexM3::Field<ValueType, 30, 1>;
    using F_TENMS = CortexM3::Field<ValueType, 0, 24>;
};

} // namespace CortexM3::SysTick
