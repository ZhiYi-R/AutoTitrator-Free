#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::GPIOG {

class CRL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x44444444;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMODE0() noexcept -> ValueType { return Reg::Read<F_MODE0>(); }
    static void WriteMODE0(ValueType value) noexcept { Reg::Write<F_MODE0>(value); }
    static auto ReadCNF0() noexcept -> ValueType { return Reg::Read<F_CNF0>(); }
    static void WriteCNF0(ValueType value) noexcept { Reg::Write<F_CNF0>(value); }
    static auto ReadMODE1() noexcept -> ValueType { return Reg::Read<F_MODE1>(); }
    static void WriteMODE1(ValueType value) noexcept { Reg::Write<F_MODE1>(value); }
    static auto ReadCNF1() noexcept -> ValueType { return Reg::Read<F_CNF1>(); }
    static void WriteCNF1(ValueType value) noexcept { Reg::Write<F_CNF1>(value); }
    static auto ReadMODE2() noexcept -> ValueType { return Reg::Read<F_MODE2>(); }
    static void WriteMODE2(ValueType value) noexcept { Reg::Write<F_MODE2>(value); }
    static auto ReadCNF2() noexcept -> ValueType { return Reg::Read<F_CNF2>(); }
    static void WriteCNF2(ValueType value) noexcept { Reg::Write<F_CNF2>(value); }
    static auto ReadMODE3() noexcept -> ValueType { return Reg::Read<F_MODE3>(); }
    static void WriteMODE3(ValueType value) noexcept { Reg::Write<F_MODE3>(value); }
    static auto ReadCNF3() noexcept -> ValueType { return Reg::Read<F_CNF3>(); }
    static void WriteCNF3(ValueType value) noexcept { Reg::Write<F_CNF3>(value); }
    static auto ReadMODE4() noexcept -> ValueType { return Reg::Read<F_MODE4>(); }
    static void WriteMODE4(ValueType value) noexcept { Reg::Write<F_MODE4>(value); }
    static auto ReadCNF4() noexcept -> ValueType { return Reg::Read<F_CNF4>(); }
    static void WriteCNF4(ValueType value) noexcept { Reg::Write<F_CNF4>(value); }
    static auto ReadMODE5() noexcept -> ValueType { return Reg::Read<F_MODE5>(); }
    static void WriteMODE5(ValueType value) noexcept { Reg::Write<F_MODE5>(value); }
    static auto ReadCNF5() noexcept -> ValueType { return Reg::Read<F_CNF5>(); }
    static void WriteCNF5(ValueType value) noexcept { Reg::Write<F_CNF5>(value); }
    static auto ReadMODE6() noexcept -> ValueType { return Reg::Read<F_MODE6>(); }
    static void WriteMODE6(ValueType value) noexcept { Reg::Write<F_MODE6>(value); }
    static auto ReadCNF6() noexcept -> ValueType { return Reg::Read<F_CNF6>(); }
    static void WriteCNF6(ValueType value) noexcept { Reg::Write<F_CNF6>(value); }
    static auto ReadMODE7() noexcept -> ValueType { return Reg::Read<F_MODE7>(); }
    static void WriteMODE7(ValueType value) noexcept { Reg::Write<F_MODE7>(value); }
    static auto ReadCNF7() noexcept -> ValueType { return Reg::Read<F_CNF7>(); }
    static void WriteCNF7(ValueType value) noexcept { Reg::Write<F_CNF7>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MODE0 = CortexM3::Field<ValueType, 0, 2>;
    using F_CNF0 = CortexM3::Field<ValueType, 2, 2>;
    using F_MODE1 = CortexM3::Field<ValueType, 4, 2>;
    using F_CNF1 = CortexM3::Field<ValueType, 6, 2>;
    using F_MODE2 = CortexM3::Field<ValueType, 8, 2>;
    using F_CNF2 = CortexM3::Field<ValueType, 10, 2>;
    using F_MODE3 = CortexM3::Field<ValueType, 12, 2>;
    using F_CNF3 = CortexM3::Field<ValueType, 14, 2>;
    using F_MODE4 = CortexM3::Field<ValueType, 16, 2>;
    using F_CNF4 = CortexM3::Field<ValueType, 18, 2>;
    using F_MODE5 = CortexM3::Field<ValueType, 20, 2>;
    using F_CNF5 = CortexM3::Field<ValueType, 22, 2>;
    using F_MODE6 = CortexM3::Field<ValueType, 24, 2>;
    using F_CNF6 = CortexM3::Field<ValueType, 26, 2>;
    using F_MODE7 = CortexM3::Field<ValueType, 28, 2>;
    using F_CNF7 = CortexM3::Field<ValueType, 30, 2>;
};

class CRH {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x44444444;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMODE8() noexcept -> ValueType { return Reg::Read<F_MODE8>(); }
    static void WriteMODE8(ValueType value) noexcept { Reg::Write<F_MODE8>(value); }
    static auto ReadCNF8() noexcept -> ValueType { return Reg::Read<F_CNF8>(); }
    static void WriteCNF8(ValueType value) noexcept { Reg::Write<F_CNF8>(value); }
    static auto ReadMODE9() noexcept -> ValueType { return Reg::Read<F_MODE9>(); }
    static void WriteMODE9(ValueType value) noexcept { Reg::Write<F_MODE9>(value); }
    static auto ReadCNF9() noexcept -> ValueType { return Reg::Read<F_CNF9>(); }
    static void WriteCNF9(ValueType value) noexcept { Reg::Write<F_CNF9>(value); }
    static auto ReadMODE10() noexcept -> ValueType { return Reg::Read<F_MODE10>(); }
    static void WriteMODE10(ValueType value) noexcept { Reg::Write<F_MODE10>(value); }
    static auto ReadCNF10() noexcept -> ValueType { return Reg::Read<F_CNF10>(); }
    static void WriteCNF10(ValueType value) noexcept { Reg::Write<F_CNF10>(value); }
    static auto ReadMODE11() noexcept -> ValueType { return Reg::Read<F_MODE11>(); }
    static void WriteMODE11(ValueType value) noexcept { Reg::Write<F_MODE11>(value); }
    static auto ReadCNF11() noexcept -> ValueType { return Reg::Read<F_CNF11>(); }
    static void WriteCNF11(ValueType value) noexcept { Reg::Write<F_CNF11>(value); }
    static auto ReadMODE12() noexcept -> ValueType { return Reg::Read<F_MODE12>(); }
    static void WriteMODE12(ValueType value) noexcept { Reg::Write<F_MODE12>(value); }
    static auto ReadCNF12() noexcept -> ValueType { return Reg::Read<F_CNF12>(); }
    static void WriteCNF12(ValueType value) noexcept { Reg::Write<F_CNF12>(value); }
    static auto ReadMODE13() noexcept -> ValueType { return Reg::Read<F_MODE13>(); }
    static void WriteMODE13(ValueType value) noexcept { Reg::Write<F_MODE13>(value); }
    static auto ReadCNF13() noexcept -> ValueType { return Reg::Read<F_CNF13>(); }
    static void WriteCNF13(ValueType value) noexcept { Reg::Write<F_CNF13>(value); }
    static auto ReadMODE14() noexcept -> ValueType { return Reg::Read<F_MODE14>(); }
    static void WriteMODE14(ValueType value) noexcept { Reg::Write<F_MODE14>(value); }
    static auto ReadCNF14() noexcept -> ValueType { return Reg::Read<F_CNF14>(); }
    static void WriteCNF14(ValueType value) noexcept { Reg::Write<F_CNF14>(value); }
    static auto ReadMODE15() noexcept -> ValueType { return Reg::Read<F_MODE15>(); }
    static void WriteMODE15(ValueType value) noexcept { Reg::Write<F_MODE15>(value); }
    static auto ReadCNF15() noexcept -> ValueType { return Reg::Read<F_CNF15>(); }
    static void WriteCNF15(ValueType value) noexcept { Reg::Write<F_CNF15>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MODE8 = CortexM3::Field<ValueType, 0, 2>;
    using F_CNF8 = CortexM3::Field<ValueType, 2, 2>;
    using F_MODE9 = CortexM3::Field<ValueType, 4, 2>;
    using F_CNF9 = CortexM3::Field<ValueType, 6, 2>;
    using F_MODE10 = CortexM3::Field<ValueType, 8, 2>;
    using F_CNF10 = CortexM3::Field<ValueType, 10, 2>;
    using F_MODE11 = CortexM3::Field<ValueType, 12, 2>;
    using F_CNF11 = CortexM3::Field<ValueType, 14, 2>;
    using F_MODE12 = CortexM3::Field<ValueType, 16, 2>;
    using F_CNF12 = CortexM3::Field<ValueType, 18, 2>;
    using F_MODE13 = CortexM3::Field<ValueType, 20, 2>;
    using F_CNF13 = CortexM3::Field<ValueType, 22, 2>;
    using F_MODE14 = CortexM3::Field<ValueType, 24, 2>;
    using F_CNF14 = CortexM3::Field<ValueType, 26, 2>;
    using F_MODE15 = CortexM3::Field<ValueType, 28, 2>;
    using F_CNF15 = CortexM3::Field<ValueType, 30, 2>;
};

class IDR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadIDR0() noexcept -> ValueType { return Reg::Read<F_IDR0>(); }
    static auto ReadIDR1() noexcept -> ValueType { return Reg::Read<F_IDR1>(); }
    static auto ReadIDR2() noexcept -> ValueType { return Reg::Read<F_IDR2>(); }
    static auto ReadIDR3() noexcept -> ValueType { return Reg::Read<F_IDR3>(); }
    static auto ReadIDR4() noexcept -> ValueType { return Reg::Read<F_IDR4>(); }
    static auto ReadIDR5() noexcept -> ValueType { return Reg::Read<F_IDR5>(); }
    static auto ReadIDR6() noexcept -> ValueType { return Reg::Read<F_IDR6>(); }
    static auto ReadIDR7() noexcept -> ValueType { return Reg::Read<F_IDR7>(); }
    static auto ReadIDR8() noexcept -> ValueType { return Reg::Read<F_IDR8>(); }
    static auto ReadIDR9() noexcept -> ValueType { return Reg::Read<F_IDR9>(); }
    static auto ReadIDR10() noexcept -> ValueType { return Reg::Read<F_IDR10>(); }
    static auto ReadIDR11() noexcept -> ValueType { return Reg::Read<F_IDR11>(); }
    static auto ReadIDR12() noexcept -> ValueType { return Reg::Read<F_IDR12>(); }
    static auto ReadIDR13() noexcept -> ValueType { return Reg::Read<F_IDR13>(); }
    static auto ReadIDR14() noexcept -> ValueType { return Reg::Read<F_IDR14>(); }
    static auto ReadIDR15() noexcept -> ValueType { return Reg::Read<F_IDR15>(); }

private:
    static constexpr std::uintptr_t Address = 0x40012008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_IDR0 = CortexM3::Field<ValueType, 0, 1>;
    using F_IDR1 = CortexM3::Field<ValueType, 1, 1>;
    using F_IDR2 = CortexM3::Field<ValueType, 2, 1>;
    using F_IDR3 = CortexM3::Field<ValueType, 3, 1>;
    using F_IDR4 = CortexM3::Field<ValueType, 4, 1>;
    using F_IDR5 = CortexM3::Field<ValueType, 5, 1>;
    using F_IDR6 = CortexM3::Field<ValueType, 6, 1>;
    using F_IDR7 = CortexM3::Field<ValueType, 7, 1>;
    using F_IDR8 = CortexM3::Field<ValueType, 8, 1>;
    using F_IDR9 = CortexM3::Field<ValueType, 9, 1>;
    using F_IDR10 = CortexM3::Field<ValueType, 10, 1>;
    using F_IDR11 = CortexM3::Field<ValueType, 11, 1>;
    using F_IDR12 = CortexM3::Field<ValueType, 12, 1>;
    using F_IDR13 = CortexM3::Field<ValueType, 13, 1>;
    using F_IDR14 = CortexM3::Field<ValueType, 14, 1>;
    using F_IDR15 = CortexM3::Field<ValueType, 15, 1>;
};

class ODR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadODR0() noexcept -> ValueType { return Reg::Read<F_ODR0>(); }
    static void WriteODR0(ValueType value) noexcept { Reg::Write<F_ODR0>(value); }
    static auto ReadODR1() noexcept -> ValueType { return Reg::Read<F_ODR1>(); }
    static void WriteODR1(ValueType value) noexcept { Reg::Write<F_ODR1>(value); }
    static auto ReadODR2() noexcept -> ValueType { return Reg::Read<F_ODR2>(); }
    static void WriteODR2(ValueType value) noexcept { Reg::Write<F_ODR2>(value); }
    static auto ReadODR3() noexcept -> ValueType { return Reg::Read<F_ODR3>(); }
    static void WriteODR3(ValueType value) noexcept { Reg::Write<F_ODR3>(value); }
    static auto ReadODR4() noexcept -> ValueType { return Reg::Read<F_ODR4>(); }
    static void WriteODR4(ValueType value) noexcept { Reg::Write<F_ODR4>(value); }
    static auto ReadODR5() noexcept -> ValueType { return Reg::Read<F_ODR5>(); }
    static void WriteODR5(ValueType value) noexcept { Reg::Write<F_ODR5>(value); }
    static auto ReadODR6() noexcept -> ValueType { return Reg::Read<F_ODR6>(); }
    static void WriteODR6(ValueType value) noexcept { Reg::Write<F_ODR6>(value); }
    static auto ReadODR7() noexcept -> ValueType { return Reg::Read<F_ODR7>(); }
    static void WriteODR7(ValueType value) noexcept { Reg::Write<F_ODR7>(value); }
    static auto ReadODR8() noexcept -> ValueType { return Reg::Read<F_ODR8>(); }
    static void WriteODR8(ValueType value) noexcept { Reg::Write<F_ODR8>(value); }
    static auto ReadODR9() noexcept -> ValueType { return Reg::Read<F_ODR9>(); }
    static void WriteODR9(ValueType value) noexcept { Reg::Write<F_ODR9>(value); }
    static auto ReadODR10() noexcept -> ValueType { return Reg::Read<F_ODR10>(); }
    static void WriteODR10(ValueType value) noexcept { Reg::Write<F_ODR10>(value); }
    static auto ReadODR11() noexcept -> ValueType { return Reg::Read<F_ODR11>(); }
    static void WriteODR11(ValueType value) noexcept { Reg::Write<F_ODR11>(value); }
    static auto ReadODR12() noexcept -> ValueType { return Reg::Read<F_ODR12>(); }
    static void WriteODR12(ValueType value) noexcept { Reg::Write<F_ODR12>(value); }
    static auto ReadODR13() noexcept -> ValueType { return Reg::Read<F_ODR13>(); }
    static void WriteODR13(ValueType value) noexcept { Reg::Write<F_ODR13>(value); }
    static auto ReadODR14() noexcept -> ValueType { return Reg::Read<F_ODR14>(); }
    static void WriteODR14(ValueType value) noexcept { Reg::Write<F_ODR14>(value); }
    static auto ReadODR15() noexcept -> ValueType { return Reg::Read<F_ODR15>(); }
    static void WriteODR15(ValueType value) noexcept { Reg::Write<F_ODR15>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001200c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ODR0 = CortexM3::Field<ValueType, 0, 1>;
    using F_ODR1 = CortexM3::Field<ValueType, 1, 1>;
    using F_ODR2 = CortexM3::Field<ValueType, 2, 1>;
    using F_ODR3 = CortexM3::Field<ValueType, 3, 1>;
    using F_ODR4 = CortexM3::Field<ValueType, 4, 1>;
    using F_ODR5 = CortexM3::Field<ValueType, 5, 1>;
    using F_ODR6 = CortexM3::Field<ValueType, 6, 1>;
    using F_ODR7 = CortexM3::Field<ValueType, 7, 1>;
    using F_ODR8 = CortexM3::Field<ValueType, 8, 1>;
    using F_ODR9 = CortexM3::Field<ValueType, 9, 1>;
    using F_ODR10 = CortexM3::Field<ValueType, 10, 1>;
    using F_ODR11 = CortexM3::Field<ValueType, 11, 1>;
    using F_ODR12 = CortexM3::Field<ValueType, 12, 1>;
    using F_ODR13 = CortexM3::Field<ValueType, 13, 1>;
    using F_ODR14 = CortexM3::Field<ValueType, 14, 1>;
    using F_ODR15 = CortexM3::Field<ValueType, 15, 1>;
};

class BSRR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteBS0(ValueType value) noexcept { Reg::Write<F_BS0>(value); }
    static void WriteBS1(ValueType value) noexcept { Reg::Write<F_BS1>(value); }
    static void WriteBS2(ValueType value) noexcept { Reg::Write<F_BS2>(value); }
    static void WriteBS3(ValueType value) noexcept { Reg::Write<F_BS3>(value); }
    static void WriteBS4(ValueType value) noexcept { Reg::Write<F_BS4>(value); }
    static void WriteBS5(ValueType value) noexcept { Reg::Write<F_BS5>(value); }
    static void WriteBS6(ValueType value) noexcept { Reg::Write<F_BS6>(value); }
    static void WriteBS7(ValueType value) noexcept { Reg::Write<F_BS7>(value); }
    static void WriteBS8(ValueType value) noexcept { Reg::Write<F_BS8>(value); }
    static void WriteBS9(ValueType value) noexcept { Reg::Write<F_BS9>(value); }
    static void WriteBS10(ValueType value) noexcept { Reg::Write<F_BS10>(value); }
    static void WriteBS11(ValueType value) noexcept { Reg::Write<F_BS11>(value); }
    static void WriteBS12(ValueType value) noexcept { Reg::Write<F_BS12>(value); }
    static void WriteBS13(ValueType value) noexcept { Reg::Write<F_BS13>(value); }
    static void WriteBS14(ValueType value) noexcept { Reg::Write<F_BS14>(value); }
    static void WriteBS15(ValueType value) noexcept { Reg::Write<F_BS15>(value); }
    static void WriteBR0(ValueType value) noexcept { Reg::Write<F_BR0>(value); }
    static void WriteBR1(ValueType value) noexcept { Reg::Write<F_BR1>(value); }
    static void WriteBR2(ValueType value) noexcept { Reg::Write<F_BR2>(value); }
    static void WriteBR3(ValueType value) noexcept { Reg::Write<F_BR3>(value); }
    static void WriteBR4(ValueType value) noexcept { Reg::Write<F_BR4>(value); }
    static void WriteBR5(ValueType value) noexcept { Reg::Write<F_BR5>(value); }
    static void WriteBR6(ValueType value) noexcept { Reg::Write<F_BR6>(value); }
    static void WriteBR7(ValueType value) noexcept { Reg::Write<F_BR7>(value); }
    static void WriteBR8(ValueType value) noexcept { Reg::Write<F_BR8>(value); }
    static void WriteBR9(ValueType value) noexcept { Reg::Write<F_BR9>(value); }
    static void WriteBR10(ValueType value) noexcept { Reg::Write<F_BR10>(value); }
    static void WriteBR11(ValueType value) noexcept { Reg::Write<F_BR11>(value); }
    static void WriteBR12(ValueType value) noexcept { Reg::Write<F_BR12>(value); }
    static void WriteBR13(ValueType value) noexcept { Reg::Write<F_BR13>(value); }
    static void WriteBR14(ValueType value) noexcept { Reg::Write<F_BR14>(value); }
    static void WriteBR15(ValueType value) noexcept { Reg::Write<F_BR15>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_BS0 = CortexM3::Field<ValueType, 0, 1>;
    using F_BS1 = CortexM3::Field<ValueType, 1, 1>;
    using F_BS2 = CortexM3::Field<ValueType, 2, 1>;
    using F_BS3 = CortexM3::Field<ValueType, 3, 1>;
    using F_BS4 = CortexM3::Field<ValueType, 4, 1>;
    using F_BS5 = CortexM3::Field<ValueType, 5, 1>;
    using F_BS6 = CortexM3::Field<ValueType, 6, 1>;
    using F_BS7 = CortexM3::Field<ValueType, 7, 1>;
    using F_BS8 = CortexM3::Field<ValueType, 8, 1>;
    using F_BS9 = CortexM3::Field<ValueType, 9, 1>;
    using F_BS10 = CortexM3::Field<ValueType, 10, 1>;
    using F_BS11 = CortexM3::Field<ValueType, 11, 1>;
    using F_BS12 = CortexM3::Field<ValueType, 12, 1>;
    using F_BS13 = CortexM3::Field<ValueType, 13, 1>;
    using F_BS14 = CortexM3::Field<ValueType, 14, 1>;
    using F_BS15 = CortexM3::Field<ValueType, 15, 1>;
    using F_BR0 = CortexM3::Field<ValueType, 16, 1>;
    using F_BR1 = CortexM3::Field<ValueType, 17, 1>;
    using F_BR2 = CortexM3::Field<ValueType, 18, 1>;
    using F_BR3 = CortexM3::Field<ValueType, 19, 1>;
    using F_BR4 = CortexM3::Field<ValueType, 20, 1>;
    using F_BR5 = CortexM3::Field<ValueType, 21, 1>;
    using F_BR6 = CortexM3::Field<ValueType, 22, 1>;
    using F_BR7 = CortexM3::Field<ValueType, 23, 1>;
    using F_BR8 = CortexM3::Field<ValueType, 24, 1>;
    using F_BR9 = CortexM3::Field<ValueType, 25, 1>;
    using F_BR10 = CortexM3::Field<ValueType, 26, 1>;
    using F_BR11 = CortexM3::Field<ValueType, 27, 1>;
    using F_BR12 = CortexM3::Field<ValueType, 28, 1>;
    using F_BR13 = CortexM3::Field<ValueType, 29, 1>;
    using F_BR14 = CortexM3::Field<ValueType, 30, 1>;
    using F_BR15 = CortexM3::Field<ValueType, 31, 1>;
};

class BRR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteBR0(ValueType value) noexcept { Reg::Write<F_BR0>(value); }
    static void WriteBR1(ValueType value) noexcept { Reg::Write<F_BR1>(value); }
    static void WriteBR2(ValueType value) noexcept { Reg::Write<F_BR2>(value); }
    static void WriteBR3(ValueType value) noexcept { Reg::Write<F_BR3>(value); }
    static void WriteBR4(ValueType value) noexcept { Reg::Write<F_BR4>(value); }
    static void WriteBR5(ValueType value) noexcept { Reg::Write<F_BR5>(value); }
    static void WriteBR6(ValueType value) noexcept { Reg::Write<F_BR6>(value); }
    static void WriteBR7(ValueType value) noexcept { Reg::Write<F_BR7>(value); }
    static void WriteBR8(ValueType value) noexcept { Reg::Write<F_BR8>(value); }
    static void WriteBR9(ValueType value) noexcept { Reg::Write<F_BR9>(value); }
    static void WriteBR10(ValueType value) noexcept { Reg::Write<F_BR10>(value); }
    static void WriteBR11(ValueType value) noexcept { Reg::Write<F_BR11>(value); }
    static void WriteBR12(ValueType value) noexcept { Reg::Write<F_BR12>(value); }
    static void WriteBR13(ValueType value) noexcept { Reg::Write<F_BR13>(value); }
    static void WriteBR14(ValueType value) noexcept { Reg::Write<F_BR14>(value); }
    static void WriteBR15(ValueType value) noexcept { Reg::Write<F_BR15>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_BR0 = CortexM3::Field<ValueType, 0, 1>;
    using F_BR1 = CortexM3::Field<ValueType, 1, 1>;
    using F_BR2 = CortexM3::Field<ValueType, 2, 1>;
    using F_BR3 = CortexM3::Field<ValueType, 3, 1>;
    using F_BR4 = CortexM3::Field<ValueType, 4, 1>;
    using F_BR5 = CortexM3::Field<ValueType, 5, 1>;
    using F_BR6 = CortexM3::Field<ValueType, 6, 1>;
    using F_BR7 = CortexM3::Field<ValueType, 7, 1>;
    using F_BR8 = CortexM3::Field<ValueType, 8, 1>;
    using F_BR9 = CortexM3::Field<ValueType, 9, 1>;
    using F_BR10 = CortexM3::Field<ValueType, 10, 1>;
    using F_BR11 = CortexM3::Field<ValueType, 11, 1>;
    using F_BR12 = CortexM3::Field<ValueType, 12, 1>;
    using F_BR13 = CortexM3::Field<ValueType, 13, 1>;
    using F_BR14 = CortexM3::Field<ValueType, 14, 1>;
    using F_BR15 = CortexM3::Field<ValueType, 15, 1>;
};

class LCKR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadLCK0() noexcept -> ValueType { return Reg::Read<F_LCK0>(); }
    static void WriteLCK0(ValueType value) noexcept { Reg::Write<F_LCK0>(value); }
    static auto ReadLCK1() noexcept -> ValueType { return Reg::Read<F_LCK1>(); }
    static void WriteLCK1(ValueType value) noexcept { Reg::Write<F_LCK1>(value); }
    static auto ReadLCK2() noexcept -> ValueType { return Reg::Read<F_LCK2>(); }
    static void WriteLCK2(ValueType value) noexcept { Reg::Write<F_LCK2>(value); }
    static auto ReadLCK3() noexcept -> ValueType { return Reg::Read<F_LCK3>(); }
    static void WriteLCK3(ValueType value) noexcept { Reg::Write<F_LCK3>(value); }
    static auto ReadLCK4() noexcept -> ValueType { return Reg::Read<F_LCK4>(); }
    static void WriteLCK4(ValueType value) noexcept { Reg::Write<F_LCK4>(value); }
    static auto ReadLCK5() noexcept -> ValueType { return Reg::Read<F_LCK5>(); }
    static void WriteLCK5(ValueType value) noexcept { Reg::Write<F_LCK5>(value); }
    static auto ReadLCK6() noexcept -> ValueType { return Reg::Read<F_LCK6>(); }
    static void WriteLCK6(ValueType value) noexcept { Reg::Write<F_LCK6>(value); }
    static auto ReadLCK7() noexcept -> ValueType { return Reg::Read<F_LCK7>(); }
    static void WriteLCK7(ValueType value) noexcept { Reg::Write<F_LCK7>(value); }
    static auto ReadLCK8() noexcept -> ValueType { return Reg::Read<F_LCK8>(); }
    static void WriteLCK8(ValueType value) noexcept { Reg::Write<F_LCK8>(value); }
    static auto ReadLCK9() noexcept -> ValueType { return Reg::Read<F_LCK9>(); }
    static void WriteLCK9(ValueType value) noexcept { Reg::Write<F_LCK9>(value); }
    static auto ReadLCK10() noexcept -> ValueType { return Reg::Read<F_LCK10>(); }
    static void WriteLCK10(ValueType value) noexcept { Reg::Write<F_LCK10>(value); }
    static auto ReadLCK11() noexcept -> ValueType { return Reg::Read<F_LCK11>(); }
    static void WriteLCK11(ValueType value) noexcept { Reg::Write<F_LCK11>(value); }
    static auto ReadLCK12() noexcept -> ValueType { return Reg::Read<F_LCK12>(); }
    static void WriteLCK12(ValueType value) noexcept { Reg::Write<F_LCK12>(value); }
    static auto ReadLCK13() noexcept -> ValueType { return Reg::Read<F_LCK13>(); }
    static void WriteLCK13(ValueType value) noexcept { Reg::Write<F_LCK13>(value); }
    static auto ReadLCK14() noexcept -> ValueType { return Reg::Read<F_LCK14>(); }
    static void WriteLCK14(ValueType value) noexcept { Reg::Write<F_LCK14>(value); }
    static auto ReadLCK15() noexcept -> ValueType { return Reg::Read<F_LCK15>(); }
    static void WriteLCK15(ValueType value) noexcept { Reg::Write<F_LCK15>(value); }
    static auto ReadLCKK() noexcept -> ValueType { return Reg::Read<F_LCKK>(); }
    static void WriteLCKK(ValueType value) noexcept { Reg::Write<F_LCKK>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012018;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_LCK0 = CortexM3::Field<ValueType, 0, 1>;
    using F_LCK1 = CortexM3::Field<ValueType, 1, 1>;
    using F_LCK2 = CortexM3::Field<ValueType, 2, 1>;
    using F_LCK3 = CortexM3::Field<ValueType, 3, 1>;
    using F_LCK4 = CortexM3::Field<ValueType, 4, 1>;
    using F_LCK5 = CortexM3::Field<ValueType, 5, 1>;
    using F_LCK6 = CortexM3::Field<ValueType, 6, 1>;
    using F_LCK7 = CortexM3::Field<ValueType, 7, 1>;
    using F_LCK8 = CortexM3::Field<ValueType, 8, 1>;
    using F_LCK9 = CortexM3::Field<ValueType, 9, 1>;
    using F_LCK10 = CortexM3::Field<ValueType, 10, 1>;
    using F_LCK11 = CortexM3::Field<ValueType, 11, 1>;
    using F_LCK12 = CortexM3::Field<ValueType, 12, 1>;
    using F_LCK13 = CortexM3::Field<ValueType, 13, 1>;
    using F_LCK14 = CortexM3::Field<ValueType, 14, 1>;
    using F_LCK15 = CortexM3::Field<ValueType, 15, 1>;
    using F_LCKK = CortexM3::Field<ValueType, 16, 1>;
};

} // namespace STM32F103::GPIOG
