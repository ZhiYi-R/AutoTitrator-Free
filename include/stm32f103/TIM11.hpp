#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::TIM11 {

class CR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCKD() noexcept -> ValueType { return Reg::Read<F_CKD>(); }
    static void WriteCKD(ValueType value) noexcept { Reg::Write<F_CKD>(value); }
    static auto ReadARPE() noexcept -> ValueType { return Reg::Read<F_ARPE>(); }
    static void WriteARPE(ValueType value) noexcept { Reg::Write<F_ARPE>(value); }
    static auto ReadURS() noexcept -> ValueType { return Reg::Read<F_URS>(); }
    static void WriteURS(ValueType value) noexcept { Reg::Write<F_URS>(value); }
    static auto ReadUDIS() noexcept -> ValueType { return Reg::Read<F_UDIS>(); }
    static void WriteUDIS(ValueType value) noexcept { Reg::Write<F_UDIS>(value); }
    static auto ReadCEN() noexcept -> ValueType { return Reg::Read<F_CEN>(); }
    static void WriteCEN(ValueType value) noexcept { Reg::Write<F_CEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40015400;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CKD = CortexM3::Field<ValueType, 8, 2>;
    using F_ARPE = CortexM3::Field<ValueType, 7, 1>;
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
    static constexpr std::uintptr_t Address = 0x40015404;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MMS = CortexM3::Field<ValueType, 4, 3>;
};

class DIER {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCC1IE() noexcept -> ValueType { return Reg::Read<F_CC1IE>(); }
    static void WriteCC1IE(ValueType value) noexcept { Reg::Write<F_CC1IE>(value); }
    static auto ReadUIE() noexcept -> ValueType { return Reg::Read<F_UIE>(); }
    static void WriteUIE(ValueType value) noexcept { Reg::Write<F_UIE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001540c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CC1IE = CortexM3::Field<ValueType, 1, 1>;
    using F_UIE = CortexM3::Field<ValueType, 0, 1>;
};

class SR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCC1OF() noexcept -> ValueType { return Reg::Read<F_CC1OF>(); }
    static void WriteCC1OF(ValueType value) noexcept { Reg::Write<F_CC1OF>(value); }
    static auto ReadCC1IF() noexcept -> ValueType { return Reg::Read<F_CC1IF>(); }
    static void WriteCC1IF(ValueType value) noexcept { Reg::Write<F_CC1IF>(value); }
    static auto ReadUIF() noexcept -> ValueType { return Reg::Read<F_UIF>(); }
    static void WriteUIF(ValueType value) noexcept { Reg::Write<F_UIF>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40015410;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CC1OF = CortexM3::Field<ValueType, 9, 1>;
    using F_CC1IF = CortexM3::Field<ValueType, 1, 1>;
    using F_UIF = CortexM3::Field<ValueType, 0, 1>;
};

class EGR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteCC1G(ValueType value) noexcept { Reg::Write<F_CC1G>(value); }
    static void WriteUG(ValueType value) noexcept { Reg::Write<F_UG>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40015414;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CC1G = CortexM3::Field<ValueType, 1, 1>;
    using F_UG = CortexM3::Field<ValueType, 0, 1>;
};

class CCMR1_Output {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadOC1M() noexcept -> ValueType { return Reg::Read<F_OC1M>(); }
    static void WriteOC1M(ValueType value) noexcept { Reg::Write<F_OC1M>(value); }
    static auto ReadOC1PE() noexcept -> ValueType { return Reg::Read<F_OC1PE>(); }
    static void WriteOC1PE(ValueType value) noexcept { Reg::Write<F_OC1PE>(value); }
    static auto ReadCC1S() noexcept -> ValueType { return Reg::Read<F_CC1S>(); }
    static void WriteCC1S(ValueType value) noexcept { Reg::Write<F_CC1S>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40015418;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_OC1M = CortexM3::Field<ValueType, 4, 3>;
    using F_OC1PE = CortexM3::Field<ValueType, 3, 1>;
    using F_CC1S = CortexM3::Field<ValueType, 0, 2>;
};

class CCMR1_Input {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadIC1F() noexcept -> ValueType { return Reg::Read<F_IC1F>(); }
    static void WriteIC1F(ValueType value) noexcept { Reg::Write<F_IC1F>(value); }
    static auto ReadIC1PSC() noexcept -> ValueType { return Reg::Read<F_IC1PSC>(); }
    static void WriteIC1PSC(ValueType value) noexcept { Reg::Write<F_IC1PSC>(value); }
    static auto ReadCC1S() noexcept -> ValueType { return Reg::Read<F_CC1S>(); }
    static void WriteCC1S(ValueType value) noexcept { Reg::Write<F_CC1S>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40015418;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_IC1F = CortexM3::Field<ValueType, 4, 4>;
    using F_IC1PSC = CortexM3::Field<ValueType, 2, 2>;
    using F_CC1S = CortexM3::Field<ValueType, 0, 2>;
};

class CCER {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCC1NP() noexcept -> ValueType { return Reg::Read<F_CC1NP>(); }
    static void WriteCC1NP(ValueType value) noexcept { Reg::Write<F_CC1NP>(value); }
    static auto ReadCC1P() noexcept -> ValueType { return Reg::Read<F_CC1P>(); }
    static void WriteCC1P(ValueType value) noexcept { Reg::Write<F_CC1P>(value); }
    static auto ReadCC1E() noexcept -> ValueType { return Reg::Read<F_CC1E>(); }
    static void WriteCC1E(ValueType value) noexcept { Reg::Write<F_CC1E>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40015420;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CC1NP = CortexM3::Field<ValueType, 3, 1>;
    using F_CC1P = CortexM3::Field<ValueType, 1, 1>;
    using F_CC1E = CortexM3::Field<ValueType, 0, 1>;
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
    static constexpr std::uintptr_t Address = 0x40015424;
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
    static constexpr std::uintptr_t Address = 0x40015428;
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
    static constexpr std::uintptr_t Address = 0x4001542c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ARR = CortexM3::Field<ValueType, 0, 16>;
};

class CCR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCCR1() noexcept -> ValueType { return Reg::Read<F_CCR1>(); }
    static void WriteCCR1(ValueType value) noexcept { Reg::Write<F_CCR1>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40015434;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CCR1 = CortexM3::Field<ValueType, 0, 16>;
};

} // namespace STM32F103::TIM11
