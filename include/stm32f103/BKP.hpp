#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::BKP {

class DR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD1() noexcept -> ValueType { return Reg::Read<F_D1>(); }
    static void WriteD1(ValueType value) noexcept { Reg::Write<F_D1>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c04;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D1 = CortexM3::Field<ValueType, 0, 16>;
};

class DR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD2() noexcept -> ValueType { return Reg::Read<F_D2>(); }
    static void WriteD2(ValueType value) noexcept { Reg::Write<F_D2>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c08;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D2 = CortexM3::Field<ValueType, 0, 16>;
};

class DR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD3() noexcept -> ValueType { return Reg::Read<F_D3>(); }
    static void WriteD3(ValueType value) noexcept { Reg::Write<F_D3>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c0c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D3 = CortexM3::Field<ValueType, 0, 16>;
};

class DR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD4() noexcept -> ValueType { return Reg::Read<F_D4>(); }
    static void WriteD4(ValueType value) noexcept { Reg::Write<F_D4>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c10;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D4 = CortexM3::Field<ValueType, 0, 16>;
};

class DR5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD5() noexcept -> ValueType { return Reg::Read<F_D5>(); }
    static void WriteD5(ValueType value) noexcept { Reg::Write<F_D5>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c14;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D5 = CortexM3::Field<ValueType, 0, 16>;
};

class DR6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD6() noexcept -> ValueType { return Reg::Read<F_D6>(); }
    static void WriteD6(ValueType value) noexcept { Reg::Write<F_D6>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c18;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D6 = CortexM3::Field<ValueType, 0, 16>;
};

class DR7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD7() noexcept -> ValueType { return Reg::Read<F_D7>(); }
    static void WriteD7(ValueType value) noexcept { Reg::Write<F_D7>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c1c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D7 = CortexM3::Field<ValueType, 0, 16>;
};

class DR8 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD8() noexcept -> ValueType { return Reg::Read<F_D8>(); }
    static void WriteD8(ValueType value) noexcept { Reg::Write<F_D8>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c20;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D8 = CortexM3::Field<ValueType, 0, 16>;
};

class DR9 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD9() noexcept -> ValueType { return Reg::Read<F_D9>(); }
    static void WriteD9(ValueType value) noexcept { Reg::Write<F_D9>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c24;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D9 = CortexM3::Field<ValueType, 0, 16>;
};

class DR10 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD10() noexcept -> ValueType { return Reg::Read<F_D10>(); }
    static void WriteD10(ValueType value) noexcept { Reg::Write<F_D10>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c28;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D10 = CortexM3::Field<ValueType, 0, 16>;
};

class RTCCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCAL() noexcept -> ValueType { return Reg::Read<F_CAL>(); }
    static void WriteCAL(ValueType value) noexcept { Reg::Write<F_CAL>(value); }
    static auto ReadCCO() noexcept -> ValueType { return Reg::Read<F_CCO>(); }
    static void WriteCCO(ValueType value) noexcept { Reg::Write<F_CCO>(value); }
    static auto ReadASOE() noexcept -> ValueType { return Reg::Read<F_ASOE>(); }
    static void WriteASOE(ValueType value) noexcept { Reg::Write<F_ASOE>(value); }
    static auto ReadASOS() noexcept -> ValueType { return Reg::Read<F_ASOS>(); }
    static void WriteASOS(ValueType value) noexcept { Reg::Write<F_ASOS>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c2c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CAL = CortexM3::Field<ValueType, 0, 7>;
    using F_CCO = CortexM3::Field<ValueType, 7, 1>;
    using F_ASOE = CortexM3::Field<ValueType, 8, 1>;
    using F_ASOS = CortexM3::Field<ValueType, 9, 1>;
};

class CR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTPE() noexcept -> ValueType { return Reg::Read<F_TPE>(); }
    static void WriteTPE(ValueType value) noexcept { Reg::Write<F_TPE>(value); }
    static auto ReadTPAL() noexcept -> ValueType { return Reg::Read<F_TPAL>(); }
    static void WriteTPAL(ValueType value) noexcept { Reg::Write<F_TPAL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c30;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TPE = CortexM3::Field<ValueType, 0, 1>;
    using F_TPAL = CortexM3::Field<ValueType, 1, 1>;
};

class CSR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteCTE(ValueType value) noexcept { Reg::Write<F_CTE>(value); }
    static void WriteCTI(ValueType value) noexcept { Reg::Write<F_CTI>(value); }
    static auto ReadTPIE() noexcept -> ValueType { return Reg::Read<F_TPIE>(); }
    static void WriteTPIE(ValueType value) noexcept { Reg::Write<F_TPIE>(value); }
    static auto ReadTEF() noexcept -> ValueType { return Reg::Read<F_TEF>(); }
    static auto ReadTIF() noexcept -> ValueType { return Reg::Read<F_TIF>(); }

private:
    static constexpr std::uintptr_t Address = 0x40006c34;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CTE = CortexM3::Field<ValueType, 0, 1>;
    using F_CTI = CortexM3::Field<ValueType, 1, 1>;
    using F_TPIE = CortexM3::Field<ValueType, 2, 1>;
    using F_TEF = CortexM3::Field<ValueType, 8, 1>;
    using F_TIF = CortexM3::Field<ValueType, 9, 1>;
};

class DR11 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDR11() noexcept -> ValueType { return Reg::Read<F_DR11>(); }
    static void WriteDR11(ValueType value) noexcept { Reg::Write<F_DR11>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c40;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DR11 = CortexM3::Field<ValueType, 0, 16>;
};

class DR12 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDR12() noexcept -> ValueType { return Reg::Read<F_DR12>(); }
    static void WriteDR12(ValueType value) noexcept { Reg::Write<F_DR12>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c44;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DR12 = CortexM3::Field<ValueType, 0, 16>;
};

class DR13 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDR13() noexcept -> ValueType { return Reg::Read<F_DR13>(); }
    static void WriteDR13(ValueType value) noexcept { Reg::Write<F_DR13>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c48;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DR13 = CortexM3::Field<ValueType, 0, 16>;
};

class DR14 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD14() noexcept -> ValueType { return Reg::Read<F_D14>(); }
    static void WriteD14(ValueType value) noexcept { Reg::Write<F_D14>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c4c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D14 = CortexM3::Field<ValueType, 0, 16>;
};

class DR15 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD15() noexcept -> ValueType { return Reg::Read<F_D15>(); }
    static void WriteD15(ValueType value) noexcept { Reg::Write<F_D15>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c50;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D15 = CortexM3::Field<ValueType, 0, 16>;
};

class DR16 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD16() noexcept -> ValueType { return Reg::Read<F_D16>(); }
    static void WriteD16(ValueType value) noexcept { Reg::Write<F_D16>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c54;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D16 = CortexM3::Field<ValueType, 0, 16>;
};

class DR17 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD17() noexcept -> ValueType { return Reg::Read<F_D17>(); }
    static void WriteD17(ValueType value) noexcept { Reg::Write<F_D17>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c58;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D17 = CortexM3::Field<ValueType, 0, 16>;
};

class DR18 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD18() noexcept -> ValueType { return Reg::Read<F_D18>(); }
    static void WriteD18(ValueType value) noexcept { Reg::Write<F_D18>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c5c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D18 = CortexM3::Field<ValueType, 0, 16>;
};

class DR19 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD19() noexcept -> ValueType { return Reg::Read<F_D19>(); }
    static void WriteD19(ValueType value) noexcept { Reg::Write<F_D19>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c60;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D19 = CortexM3::Field<ValueType, 0, 16>;
};

class DR20 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD20() noexcept -> ValueType { return Reg::Read<F_D20>(); }
    static void WriteD20(ValueType value) noexcept { Reg::Write<F_D20>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c64;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D20 = CortexM3::Field<ValueType, 0, 16>;
};

class DR21 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD21() noexcept -> ValueType { return Reg::Read<F_D21>(); }
    static void WriteD21(ValueType value) noexcept { Reg::Write<F_D21>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c68;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D21 = CortexM3::Field<ValueType, 0, 16>;
};

class DR22 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD22() noexcept -> ValueType { return Reg::Read<F_D22>(); }
    static void WriteD22(ValueType value) noexcept { Reg::Write<F_D22>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c6c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D22 = CortexM3::Field<ValueType, 0, 16>;
};

class DR23 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD23() noexcept -> ValueType { return Reg::Read<F_D23>(); }
    static void WriteD23(ValueType value) noexcept { Reg::Write<F_D23>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c70;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D23 = CortexM3::Field<ValueType, 0, 16>;
};

class DR24 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD24() noexcept -> ValueType { return Reg::Read<F_D24>(); }
    static void WriteD24(ValueType value) noexcept { Reg::Write<F_D24>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c74;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D24 = CortexM3::Field<ValueType, 0, 16>;
};

class DR25 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD25() noexcept -> ValueType { return Reg::Read<F_D25>(); }
    static void WriteD25(ValueType value) noexcept { Reg::Write<F_D25>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c78;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D25 = CortexM3::Field<ValueType, 0, 16>;
};

class DR26 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD26() noexcept -> ValueType { return Reg::Read<F_D26>(); }
    static void WriteD26(ValueType value) noexcept { Reg::Write<F_D26>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c7c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D26 = CortexM3::Field<ValueType, 0, 16>;
};

class DR27 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD27() noexcept -> ValueType { return Reg::Read<F_D27>(); }
    static void WriteD27(ValueType value) noexcept { Reg::Write<F_D27>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c80;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D27 = CortexM3::Field<ValueType, 0, 16>;
};

class DR28 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD28() noexcept -> ValueType { return Reg::Read<F_D28>(); }
    static void WriteD28(ValueType value) noexcept { Reg::Write<F_D28>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c84;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D28 = CortexM3::Field<ValueType, 0, 16>;
};

class DR29 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD29() noexcept -> ValueType { return Reg::Read<F_D29>(); }
    static void WriteD29(ValueType value) noexcept { Reg::Write<F_D29>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c88;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D29 = CortexM3::Field<ValueType, 0, 16>;
};

class DR30 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD30() noexcept -> ValueType { return Reg::Read<F_D30>(); }
    static void WriteD30(ValueType value) noexcept { Reg::Write<F_D30>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c8c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D30 = CortexM3::Field<ValueType, 0, 16>;
};

class DR31 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD31() noexcept -> ValueType { return Reg::Read<F_D31>(); }
    static void WriteD31(ValueType value) noexcept { Reg::Write<F_D31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c90;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D31 = CortexM3::Field<ValueType, 0, 16>;
};

class DR32 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD32() noexcept -> ValueType { return Reg::Read<F_D32>(); }
    static void WriteD32(ValueType value) noexcept { Reg::Write<F_D32>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c94;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D32 = CortexM3::Field<ValueType, 0, 16>;
};

class DR33 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD33() noexcept -> ValueType { return Reg::Read<F_D33>(); }
    static void WriteD33(ValueType value) noexcept { Reg::Write<F_D33>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c98;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D33 = CortexM3::Field<ValueType, 0, 16>;
};

class DR34 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD34() noexcept -> ValueType { return Reg::Read<F_D34>(); }
    static void WriteD34(ValueType value) noexcept { Reg::Write<F_D34>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006c9c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D34 = CortexM3::Field<ValueType, 0, 16>;
};

class DR35 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD35() noexcept -> ValueType { return Reg::Read<F_D35>(); }
    static void WriteD35(ValueType value) noexcept { Reg::Write<F_D35>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006ca0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D35 = CortexM3::Field<ValueType, 0, 16>;
};

class DR36 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD36() noexcept -> ValueType { return Reg::Read<F_D36>(); }
    static void WriteD36(ValueType value) noexcept { Reg::Write<F_D36>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006ca4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D36 = CortexM3::Field<ValueType, 0, 16>;
};

class DR37 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD37() noexcept -> ValueType { return Reg::Read<F_D37>(); }
    static void WriteD37(ValueType value) noexcept { Reg::Write<F_D37>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006ca8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D37 = CortexM3::Field<ValueType, 0, 16>;
};

class DR38 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD38() noexcept -> ValueType { return Reg::Read<F_D38>(); }
    static void WriteD38(ValueType value) noexcept { Reg::Write<F_D38>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006cac;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D38 = CortexM3::Field<ValueType, 0, 16>;
};

class DR39 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD39() noexcept -> ValueType { return Reg::Read<F_D39>(); }
    static void WriteD39(ValueType value) noexcept { Reg::Write<F_D39>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006cb0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D39 = CortexM3::Field<ValueType, 0, 16>;
};

class DR40 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD40() noexcept -> ValueType { return Reg::Read<F_D40>(); }
    static void WriteD40(ValueType value) noexcept { Reg::Write<F_D40>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006cb4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D40 = CortexM3::Field<ValueType, 0, 16>;
};

class DR41 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD41() noexcept -> ValueType { return Reg::Read<F_D41>(); }
    static void WriteD41(ValueType value) noexcept { Reg::Write<F_D41>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006cb8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D41 = CortexM3::Field<ValueType, 0, 16>;
};

class DR42 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadD42() noexcept -> ValueType { return Reg::Read<F_D42>(); }
    static void WriteD42(ValueType value) noexcept { Reg::Write<F_D42>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006cbc;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_D42 = CortexM3::Field<ValueType, 0, 16>;
};

} // namespace STM32F103::BKP
