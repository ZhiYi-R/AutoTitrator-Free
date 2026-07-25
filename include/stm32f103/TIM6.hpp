#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::TIM6 {

class CR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadARPE() noexcept -> ValueType { return Reg::Read<F_ARPE>(); }
    static void WriteARPE(ValueType value) noexcept { Reg::Write<F_ARPE>(value); }
    static auto ReadOPM() noexcept -> ValueType { return Reg::Read<F_OPM>(); }
    static void WriteOPM(ValueType value) noexcept { Reg::Write<F_OPM>(value); }
    static auto ReadURS() noexcept -> ValueType { return Reg::Read<F_URS>(); }
    static void WriteURS(ValueType value) noexcept { Reg::Write<F_URS>(value); }
    static auto ReadUDIS() noexcept -> ValueType { return Reg::Read<F_UDIS>(); }
    static void WriteUDIS(ValueType value) noexcept { Reg::Write<F_UDIS>(value); }
    static auto ReadCEN() noexcept -> ValueType { return Reg::Read<F_CEN>(); }
    static void WriteCEN(ValueType value) noexcept { Reg::Write<F_CEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40001000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ARPE = CortexM3::Field<ValueType, 7, 1>;
    using F_OPM = CortexM3::Field<ValueType, 3, 1>;
    using F_URS = CortexM3::Field<ValueType, 2, 1>;
    using F_UDIS = CortexM3::Field<ValueType, 1, 1>;
    using F_CEN = CortexM3::Field<ValueType, 0, 1>;
};

class CR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMMS() noexcept -> ValueType { return Reg::Read<F_MMS>(); }
    static void WriteMMS(ValueType value) noexcept { Reg::Write<F_MMS>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40001004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MMS = CortexM3::Field<ValueType, 4, 3>;
};

class DIER {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadUDE() noexcept -> ValueType { return Reg::Read<F_UDE>(); }
    static void WriteUDE(ValueType value) noexcept { Reg::Write<F_UDE>(value); }
    static auto ReadUIE() noexcept -> ValueType { return Reg::Read<F_UIE>(); }
    static void WriteUIE(ValueType value) noexcept { Reg::Write<F_UIE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000100c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_UDE = CortexM3::Field<ValueType, 8, 1>;
    using F_UIE = CortexM3::Field<ValueType, 0, 1>;
};

class SR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadUIF() noexcept -> ValueType { return Reg::Read<F_UIF>(); }
    static void WriteUIF(ValueType value) noexcept { Reg::Write<F_UIF>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40001010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_UIF = CortexM3::Field<ValueType, 0, 1>;
};

class EGR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteUG(ValueType value) noexcept { Reg::Write<F_UG>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40001014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_UG = CortexM3::Field<ValueType, 0, 1>;
};

class CNT {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCNT() noexcept -> ValueType { return Reg::Read<F_CNT>(); }
    static void WriteCNT(ValueType value) noexcept { Reg::Write<F_CNT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40001024;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CNT = CortexM3::Field<ValueType, 0, 16>;
};

class PSC {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPSC() noexcept -> ValueType { return Reg::Read<F_PSC>(); }
    static void WritePSC(ValueType value) noexcept { Reg::Write<F_PSC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40001028;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PSC = CortexM3::Field<ValueType, 0, 16>;
};

class ARR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadARR() noexcept -> ValueType { return Reg::Read<F_ARR>(); }
    static void WriteARR(ValueType value) noexcept { Reg::Write<F_ARR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000102c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ARR = CortexM3::Field<ValueType, 0, 16>;
};

} // namespace STM32F103::TIM6
