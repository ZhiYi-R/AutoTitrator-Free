#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::EXTI {

class IMR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMR0() noexcept -> ValueType { return Reg::Read<F_MR0>(); }
    static void WriteMR0(ValueType value) noexcept { Reg::Write<F_MR0>(value); }
    static auto ReadMR1() noexcept -> ValueType { return Reg::Read<F_MR1>(); }
    static void WriteMR1(ValueType value) noexcept { Reg::Write<F_MR1>(value); }
    static auto ReadMR2() noexcept -> ValueType { return Reg::Read<F_MR2>(); }
    static void WriteMR2(ValueType value) noexcept { Reg::Write<F_MR2>(value); }
    static auto ReadMR3() noexcept -> ValueType { return Reg::Read<F_MR3>(); }
    static void WriteMR3(ValueType value) noexcept { Reg::Write<F_MR3>(value); }
    static auto ReadMR4() noexcept -> ValueType { return Reg::Read<F_MR4>(); }
    static void WriteMR4(ValueType value) noexcept { Reg::Write<F_MR4>(value); }
    static auto ReadMR5() noexcept -> ValueType { return Reg::Read<F_MR5>(); }
    static void WriteMR5(ValueType value) noexcept { Reg::Write<F_MR5>(value); }
    static auto ReadMR6() noexcept -> ValueType { return Reg::Read<F_MR6>(); }
    static void WriteMR6(ValueType value) noexcept { Reg::Write<F_MR6>(value); }
    static auto ReadMR7() noexcept -> ValueType { return Reg::Read<F_MR7>(); }
    static void WriteMR7(ValueType value) noexcept { Reg::Write<F_MR7>(value); }
    static auto ReadMR8() noexcept -> ValueType { return Reg::Read<F_MR8>(); }
    static void WriteMR8(ValueType value) noexcept { Reg::Write<F_MR8>(value); }
    static auto ReadMR9() noexcept -> ValueType { return Reg::Read<F_MR9>(); }
    static void WriteMR9(ValueType value) noexcept { Reg::Write<F_MR9>(value); }
    static auto ReadMR10() noexcept -> ValueType { return Reg::Read<F_MR10>(); }
    static void WriteMR10(ValueType value) noexcept { Reg::Write<F_MR10>(value); }
    static auto ReadMR11() noexcept -> ValueType { return Reg::Read<F_MR11>(); }
    static void WriteMR11(ValueType value) noexcept { Reg::Write<F_MR11>(value); }
    static auto ReadMR12() noexcept -> ValueType { return Reg::Read<F_MR12>(); }
    static void WriteMR12(ValueType value) noexcept { Reg::Write<F_MR12>(value); }
    static auto ReadMR13() noexcept -> ValueType { return Reg::Read<F_MR13>(); }
    static void WriteMR13(ValueType value) noexcept { Reg::Write<F_MR13>(value); }
    static auto ReadMR14() noexcept -> ValueType { return Reg::Read<F_MR14>(); }
    static void WriteMR14(ValueType value) noexcept { Reg::Write<F_MR14>(value); }
    static auto ReadMR15() noexcept -> ValueType { return Reg::Read<F_MR15>(); }
    static void WriteMR15(ValueType value) noexcept { Reg::Write<F_MR15>(value); }
    static auto ReadMR16() noexcept -> ValueType { return Reg::Read<F_MR16>(); }
    static void WriteMR16(ValueType value) noexcept { Reg::Write<F_MR16>(value); }
    static auto ReadMR17() noexcept -> ValueType { return Reg::Read<F_MR17>(); }
    static void WriteMR17(ValueType value) noexcept { Reg::Write<F_MR17>(value); }
    static auto ReadMR18() noexcept -> ValueType { return Reg::Read<F_MR18>(); }
    static void WriteMR18(ValueType value) noexcept { Reg::Write<F_MR18>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40010400;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MR0 = CortexM3::Field<ValueType, 0, 1>;
    using F_MR1 = CortexM3::Field<ValueType, 1, 1>;
    using F_MR2 = CortexM3::Field<ValueType, 2, 1>;
    using F_MR3 = CortexM3::Field<ValueType, 3, 1>;
    using F_MR4 = CortexM3::Field<ValueType, 4, 1>;
    using F_MR5 = CortexM3::Field<ValueType, 5, 1>;
    using F_MR6 = CortexM3::Field<ValueType, 6, 1>;
    using F_MR7 = CortexM3::Field<ValueType, 7, 1>;
    using F_MR8 = CortexM3::Field<ValueType, 8, 1>;
    using F_MR9 = CortexM3::Field<ValueType, 9, 1>;
    using F_MR10 = CortexM3::Field<ValueType, 10, 1>;
    using F_MR11 = CortexM3::Field<ValueType, 11, 1>;
    using F_MR12 = CortexM3::Field<ValueType, 12, 1>;
    using F_MR13 = CortexM3::Field<ValueType, 13, 1>;
    using F_MR14 = CortexM3::Field<ValueType, 14, 1>;
    using F_MR15 = CortexM3::Field<ValueType, 15, 1>;
    using F_MR16 = CortexM3::Field<ValueType, 16, 1>;
    using F_MR17 = CortexM3::Field<ValueType, 17, 1>;
    using F_MR18 = CortexM3::Field<ValueType, 18, 1>;
};

class EMR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMR0() noexcept -> ValueType { return Reg::Read<F_MR0>(); }
    static void WriteMR0(ValueType value) noexcept { Reg::Write<F_MR0>(value); }
    static auto ReadMR1() noexcept -> ValueType { return Reg::Read<F_MR1>(); }
    static void WriteMR1(ValueType value) noexcept { Reg::Write<F_MR1>(value); }
    static auto ReadMR2() noexcept -> ValueType { return Reg::Read<F_MR2>(); }
    static void WriteMR2(ValueType value) noexcept { Reg::Write<F_MR2>(value); }
    static auto ReadMR3() noexcept -> ValueType { return Reg::Read<F_MR3>(); }
    static void WriteMR3(ValueType value) noexcept { Reg::Write<F_MR3>(value); }
    static auto ReadMR4() noexcept -> ValueType { return Reg::Read<F_MR4>(); }
    static void WriteMR4(ValueType value) noexcept { Reg::Write<F_MR4>(value); }
    static auto ReadMR5() noexcept -> ValueType { return Reg::Read<F_MR5>(); }
    static void WriteMR5(ValueType value) noexcept { Reg::Write<F_MR5>(value); }
    static auto ReadMR6() noexcept -> ValueType { return Reg::Read<F_MR6>(); }
    static void WriteMR6(ValueType value) noexcept { Reg::Write<F_MR6>(value); }
    static auto ReadMR7() noexcept -> ValueType { return Reg::Read<F_MR7>(); }
    static void WriteMR7(ValueType value) noexcept { Reg::Write<F_MR7>(value); }
    static auto ReadMR8() noexcept -> ValueType { return Reg::Read<F_MR8>(); }
    static void WriteMR8(ValueType value) noexcept { Reg::Write<F_MR8>(value); }
    static auto ReadMR9() noexcept -> ValueType { return Reg::Read<F_MR9>(); }
    static void WriteMR9(ValueType value) noexcept { Reg::Write<F_MR9>(value); }
    static auto ReadMR10() noexcept -> ValueType { return Reg::Read<F_MR10>(); }
    static void WriteMR10(ValueType value) noexcept { Reg::Write<F_MR10>(value); }
    static auto ReadMR11() noexcept -> ValueType { return Reg::Read<F_MR11>(); }
    static void WriteMR11(ValueType value) noexcept { Reg::Write<F_MR11>(value); }
    static auto ReadMR12() noexcept -> ValueType { return Reg::Read<F_MR12>(); }
    static void WriteMR12(ValueType value) noexcept { Reg::Write<F_MR12>(value); }
    static auto ReadMR13() noexcept -> ValueType { return Reg::Read<F_MR13>(); }
    static void WriteMR13(ValueType value) noexcept { Reg::Write<F_MR13>(value); }
    static auto ReadMR14() noexcept -> ValueType { return Reg::Read<F_MR14>(); }
    static void WriteMR14(ValueType value) noexcept { Reg::Write<F_MR14>(value); }
    static auto ReadMR15() noexcept -> ValueType { return Reg::Read<F_MR15>(); }
    static void WriteMR15(ValueType value) noexcept { Reg::Write<F_MR15>(value); }
    static auto ReadMR16() noexcept -> ValueType { return Reg::Read<F_MR16>(); }
    static void WriteMR16(ValueType value) noexcept { Reg::Write<F_MR16>(value); }
    static auto ReadMR17() noexcept -> ValueType { return Reg::Read<F_MR17>(); }
    static void WriteMR17(ValueType value) noexcept { Reg::Write<F_MR17>(value); }
    static auto ReadMR18() noexcept -> ValueType { return Reg::Read<F_MR18>(); }
    static void WriteMR18(ValueType value) noexcept { Reg::Write<F_MR18>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40010404;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MR0 = CortexM3::Field<ValueType, 0, 1>;
    using F_MR1 = CortexM3::Field<ValueType, 1, 1>;
    using F_MR2 = CortexM3::Field<ValueType, 2, 1>;
    using F_MR3 = CortexM3::Field<ValueType, 3, 1>;
    using F_MR4 = CortexM3::Field<ValueType, 4, 1>;
    using F_MR5 = CortexM3::Field<ValueType, 5, 1>;
    using F_MR6 = CortexM3::Field<ValueType, 6, 1>;
    using F_MR7 = CortexM3::Field<ValueType, 7, 1>;
    using F_MR8 = CortexM3::Field<ValueType, 8, 1>;
    using F_MR9 = CortexM3::Field<ValueType, 9, 1>;
    using F_MR10 = CortexM3::Field<ValueType, 10, 1>;
    using F_MR11 = CortexM3::Field<ValueType, 11, 1>;
    using F_MR12 = CortexM3::Field<ValueType, 12, 1>;
    using F_MR13 = CortexM3::Field<ValueType, 13, 1>;
    using F_MR14 = CortexM3::Field<ValueType, 14, 1>;
    using F_MR15 = CortexM3::Field<ValueType, 15, 1>;
    using F_MR16 = CortexM3::Field<ValueType, 16, 1>;
    using F_MR17 = CortexM3::Field<ValueType, 17, 1>;
    using F_MR18 = CortexM3::Field<ValueType, 18, 1>;
};

class RTSR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTR0() noexcept -> ValueType { return Reg::Read<F_TR0>(); }
    static void WriteTR0(ValueType value) noexcept { Reg::Write<F_TR0>(value); }
    static auto ReadTR1() noexcept -> ValueType { return Reg::Read<F_TR1>(); }
    static void WriteTR1(ValueType value) noexcept { Reg::Write<F_TR1>(value); }
    static auto ReadTR2() noexcept -> ValueType { return Reg::Read<F_TR2>(); }
    static void WriteTR2(ValueType value) noexcept { Reg::Write<F_TR2>(value); }
    static auto ReadTR3() noexcept -> ValueType { return Reg::Read<F_TR3>(); }
    static void WriteTR3(ValueType value) noexcept { Reg::Write<F_TR3>(value); }
    static auto ReadTR4() noexcept -> ValueType { return Reg::Read<F_TR4>(); }
    static void WriteTR4(ValueType value) noexcept { Reg::Write<F_TR4>(value); }
    static auto ReadTR5() noexcept -> ValueType { return Reg::Read<F_TR5>(); }
    static void WriteTR5(ValueType value) noexcept { Reg::Write<F_TR5>(value); }
    static auto ReadTR6() noexcept -> ValueType { return Reg::Read<F_TR6>(); }
    static void WriteTR6(ValueType value) noexcept { Reg::Write<F_TR6>(value); }
    static auto ReadTR7() noexcept -> ValueType { return Reg::Read<F_TR7>(); }
    static void WriteTR7(ValueType value) noexcept { Reg::Write<F_TR7>(value); }
    static auto ReadTR8() noexcept -> ValueType { return Reg::Read<F_TR8>(); }
    static void WriteTR8(ValueType value) noexcept { Reg::Write<F_TR8>(value); }
    static auto ReadTR9() noexcept -> ValueType { return Reg::Read<F_TR9>(); }
    static void WriteTR9(ValueType value) noexcept { Reg::Write<F_TR9>(value); }
    static auto ReadTR10() noexcept -> ValueType { return Reg::Read<F_TR10>(); }
    static void WriteTR10(ValueType value) noexcept { Reg::Write<F_TR10>(value); }
    static auto ReadTR11() noexcept -> ValueType { return Reg::Read<F_TR11>(); }
    static void WriteTR11(ValueType value) noexcept { Reg::Write<F_TR11>(value); }
    static auto ReadTR12() noexcept -> ValueType { return Reg::Read<F_TR12>(); }
    static void WriteTR12(ValueType value) noexcept { Reg::Write<F_TR12>(value); }
    static auto ReadTR13() noexcept -> ValueType { return Reg::Read<F_TR13>(); }
    static void WriteTR13(ValueType value) noexcept { Reg::Write<F_TR13>(value); }
    static auto ReadTR14() noexcept -> ValueType { return Reg::Read<F_TR14>(); }
    static void WriteTR14(ValueType value) noexcept { Reg::Write<F_TR14>(value); }
    static auto ReadTR15() noexcept -> ValueType { return Reg::Read<F_TR15>(); }
    static void WriteTR15(ValueType value) noexcept { Reg::Write<F_TR15>(value); }
    static auto ReadTR16() noexcept -> ValueType { return Reg::Read<F_TR16>(); }
    static void WriteTR16(ValueType value) noexcept { Reg::Write<F_TR16>(value); }
    static auto ReadTR17() noexcept -> ValueType { return Reg::Read<F_TR17>(); }
    static void WriteTR17(ValueType value) noexcept { Reg::Write<F_TR17>(value); }
    static auto ReadTR18() noexcept -> ValueType { return Reg::Read<F_TR18>(); }
    static void WriteTR18(ValueType value) noexcept { Reg::Write<F_TR18>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40010408;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TR0 = CortexM3::Field<ValueType, 0, 1>;
    using F_TR1 = CortexM3::Field<ValueType, 1, 1>;
    using F_TR2 = CortexM3::Field<ValueType, 2, 1>;
    using F_TR3 = CortexM3::Field<ValueType, 3, 1>;
    using F_TR4 = CortexM3::Field<ValueType, 4, 1>;
    using F_TR5 = CortexM3::Field<ValueType, 5, 1>;
    using F_TR6 = CortexM3::Field<ValueType, 6, 1>;
    using F_TR7 = CortexM3::Field<ValueType, 7, 1>;
    using F_TR8 = CortexM3::Field<ValueType, 8, 1>;
    using F_TR9 = CortexM3::Field<ValueType, 9, 1>;
    using F_TR10 = CortexM3::Field<ValueType, 10, 1>;
    using F_TR11 = CortexM3::Field<ValueType, 11, 1>;
    using F_TR12 = CortexM3::Field<ValueType, 12, 1>;
    using F_TR13 = CortexM3::Field<ValueType, 13, 1>;
    using F_TR14 = CortexM3::Field<ValueType, 14, 1>;
    using F_TR15 = CortexM3::Field<ValueType, 15, 1>;
    using F_TR16 = CortexM3::Field<ValueType, 16, 1>;
    using F_TR17 = CortexM3::Field<ValueType, 17, 1>;
    using F_TR18 = CortexM3::Field<ValueType, 18, 1>;
};

class FTSR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTR0() noexcept -> ValueType { return Reg::Read<F_TR0>(); }
    static void WriteTR0(ValueType value) noexcept { Reg::Write<F_TR0>(value); }
    static auto ReadTR1() noexcept -> ValueType { return Reg::Read<F_TR1>(); }
    static void WriteTR1(ValueType value) noexcept { Reg::Write<F_TR1>(value); }
    static auto ReadTR2() noexcept -> ValueType { return Reg::Read<F_TR2>(); }
    static void WriteTR2(ValueType value) noexcept { Reg::Write<F_TR2>(value); }
    static auto ReadTR3() noexcept -> ValueType { return Reg::Read<F_TR3>(); }
    static void WriteTR3(ValueType value) noexcept { Reg::Write<F_TR3>(value); }
    static auto ReadTR4() noexcept -> ValueType { return Reg::Read<F_TR4>(); }
    static void WriteTR4(ValueType value) noexcept { Reg::Write<F_TR4>(value); }
    static auto ReadTR5() noexcept -> ValueType { return Reg::Read<F_TR5>(); }
    static void WriteTR5(ValueType value) noexcept { Reg::Write<F_TR5>(value); }
    static auto ReadTR6() noexcept -> ValueType { return Reg::Read<F_TR6>(); }
    static void WriteTR6(ValueType value) noexcept { Reg::Write<F_TR6>(value); }
    static auto ReadTR7() noexcept -> ValueType { return Reg::Read<F_TR7>(); }
    static void WriteTR7(ValueType value) noexcept { Reg::Write<F_TR7>(value); }
    static auto ReadTR8() noexcept -> ValueType { return Reg::Read<F_TR8>(); }
    static void WriteTR8(ValueType value) noexcept { Reg::Write<F_TR8>(value); }
    static auto ReadTR9() noexcept -> ValueType { return Reg::Read<F_TR9>(); }
    static void WriteTR9(ValueType value) noexcept { Reg::Write<F_TR9>(value); }
    static auto ReadTR10() noexcept -> ValueType { return Reg::Read<F_TR10>(); }
    static void WriteTR10(ValueType value) noexcept { Reg::Write<F_TR10>(value); }
    static auto ReadTR11() noexcept -> ValueType { return Reg::Read<F_TR11>(); }
    static void WriteTR11(ValueType value) noexcept { Reg::Write<F_TR11>(value); }
    static auto ReadTR12() noexcept -> ValueType { return Reg::Read<F_TR12>(); }
    static void WriteTR12(ValueType value) noexcept { Reg::Write<F_TR12>(value); }
    static auto ReadTR13() noexcept -> ValueType { return Reg::Read<F_TR13>(); }
    static void WriteTR13(ValueType value) noexcept { Reg::Write<F_TR13>(value); }
    static auto ReadTR14() noexcept -> ValueType { return Reg::Read<F_TR14>(); }
    static void WriteTR14(ValueType value) noexcept { Reg::Write<F_TR14>(value); }
    static auto ReadTR15() noexcept -> ValueType { return Reg::Read<F_TR15>(); }
    static void WriteTR15(ValueType value) noexcept { Reg::Write<F_TR15>(value); }
    static auto ReadTR16() noexcept -> ValueType { return Reg::Read<F_TR16>(); }
    static void WriteTR16(ValueType value) noexcept { Reg::Write<F_TR16>(value); }
    static auto ReadTR17() noexcept -> ValueType { return Reg::Read<F_TR17>(); }
    static void WriteTR17(ValueType value) noexcept { Reg::Write<F_TR17>(value); }
    static auto ReadTR18() noexcept -> ValueType { return Reg::Read<F_TR18>(); }
    static void WriteTR18(ValueType value) noexcept { Reg::Write<F_TR18>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001040c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TR0 = CortexM3::Field<ValueType, 0, 1>;
    using F_TR1 = CortexM3::Field<ValueType, 1, 1>;
    using F_TR2 = CortexM3::Field<ValueType, 2, 1>;
    using F_TR3 = CortexM3::Field<ValueType, 3, 1>;
    using F_TR4 = CortexM3::Field<ValueType, 4, 1>;
    using F_TR5 = CortexM3::Field<ValueType, 5, 1>;
    using F_TR6 = CortexM3::Field<ValueType, 6, 1>;
    using F_TR7 = CortexM3::Field<ValueType, 7, 1>;
    using F_TR8 = CortexM3::Field<ValueType, 8, 1>;
    using F_TR9 = CortexM3::Field<ValueType, 9, 1>;
    using F_TR10 = CortexM3::Field<ValueType, 10, 1>;
    using F_TR11 = CortexM3::Field<ValueType, 11, 1>;
    using F_TR12 = CortexM3::Field<ValueType, 12, 1>;
    using F_TR13 = CortexM3::Field<ValueType, 13, 1>;
    using F_TR14 = CortexM3::Field<ValueType, 14, 1>;
    using F_TR15 = CortexM3::Field<ValueType, 15, 1>;
    using F_TR16 = CortexM3::Field<ValueType, 16, 1>;
    using F_TR17 = CortexM3::Field<ValueType, 17, 1>;
    using F_TR18 = CortexM3::Field<ValueType, 18, 1>;
};

class SWIER {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSWIER0() noexcept -> ValueType { return Reg::Read<F_SWIER0>(); }
    static void WriteSWIER0(ValueType value) noexcept { Reg::Write<F_SWIER0>(value); }
    static auto ReadSWIER1() noexcept -> ValueType { return Reg::Read<F_SWIER1>(); }
    static void WriteSWIER1(ValueType value) noexcept { Reg::Write<F_SWIER1>(value); }
    static auto ReadSWIER2() noexcept -> ValueType { return Reg::Read<F_SWIER2>(); }
    static void WriteSWIER2(ValueType value) noexcept { Reg::Write<F_SWIER2>(value); }
    static auto ReadSWIER3() noexcept -> ValueType { return Reg::Read<F_SWIER3>(); }
    static void WriteSWIER3(ValueType value) noexcept { Reg::Write<F_SWIER3>(value); }
    static auto ReadSWIER4() noexcept -> ValueType { return Reg::Read<F_SWIER4>(); }
    static void WriteSWIER4(ValueType value) noexcept { Reg::Write<F_SWIER4>(value); }
    static auto ReadSWIER5() noexcept -> ValueType { return Reg::Read<F_SWIER5>(); }
    static void WriteSWIER5(ValueType value) noexcept { Reg::Write<F_SWIER5>(value); }
    static auto ReadSWIER6() noexcept -> ValueType { return Reg::Read<F_SWIER6>(); }
    static void WriteSWIER6(ValueType value) noexcept { Reg::Write<F_SWIER6>(value); }
    static auto ReadSWIER7() noexcept -> ValueType { return Reg::Read<F_SWIER7>(); }
    static void WriteSWIER7(ValueType value) noexcept { Reg::Write<F_SWIER7>(value); }
    static auto ReadSWIER8() noexcept -> ValueType { return Reg::Read<F_SWIER8>(); }
    static void WriteSWIER8(ValueType value) noexcept { Reg::Write<F_SWIER8>(value); }
    static auto ReadSWIER9() noexcept -> ValueType { return Reg::Read<F_SWIER9>(); }
    static void WriteSWIER9(ValueType value) noexcept { Reg::Write<F_SWIER9>(value); }
    static auto ReadSWIER10() noexcept -> ValueType { return Reg::Read<F_SWIER10>(); }
    static void WriteSWIER10(ValueType value) noexcept { Reg::Write<F_SWIER10>(value); }
    static auto ReadSWIER11() noexcept -> ValueType { return Reg::Read<F_SWIER11>(); }
    static void WriteSWIER11(ValueType value) noexcept { Reg::Write<F_SWIER11>(value); }
    static auto ReadSWIER12() noexcept -> ValueType { return Reg::Read<F_SWIER12>(); }
    static void WriteSWIER12(ValueType value) noexcept { Reg::Write<F_SWIER12>(value); }
    static auto ReadSWIER13() noexcept -> ValueType { return Reg::Read<F_SWIER13>(); }
    static void WriteSWIER13(ValueType value) noexcept { Reg::Write<F_SWIER13>(value); }
    static auto ReadSWIER14() noexcept -> ValueType { return Reg::Read<F_SWIER14>(); }
    static void WriteSWIER14(ValueType value) noexcept { Reg::Write<F_SWIER14>(value); }
    static auto ReadSWIER15() noexcept -> ValueType { return Reg::Read<F_SWIER15>(); }
    static void WriteSWIER15(ValueType value) noexcept { Reg::Write<F_SWIER15>(value); }
    static auto ReadSWIER16() noexcept -> ValueType { return Reg::Read<F_SWIER16>(); }
    static void WriteSWIER16(ValueType value) noexcept { Reg::Write<F_SWIER16>(value); }
    static auto ReadSWIER17() noexcept -> ValueType { return Reg::Read<F_SWIER17>(); }
    static void WriteSWIER17(ValueType value) noexcept { Reg::Write<F_SWIER17>(value); }
    static auto ReadSWIER18() noexcept -> ValueType { return Reg::Read<F_SWIER18>(); }
    static void WriteSWIER18(ValueType value) noexcept { Reg::Write<F_SWIER18>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40010410;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SWIER0 = CortexM3::Field<ValueType, 0, 1>;
    using F_SWIER1 = CortexM3::Field<ValueType, 1, 1>;
    using F_SWIER2 = CortexM3::Field<ValueType, 2, 1>;
    using F_SWIER3 = CortexM3::Field<ValueType, 3, 1>;
    using F_SWIER4 = CortexM3::Field<ValueType, 4, 1>;
    using F_SWIER5 = CortexM3::Field<ValueType, 5, 1>;
    using F_SWIER6 = CortexM3::Field<ValueType, 6, 1>;
    using F_SWIER7 = CortexM3::Field<ValueType, 7, 1>;
    using F_SWIER8 = CortexM3::Field<ValueType, 8, 1>;
    using F_SWIER9 = CortexM3::Field<ValueType, 9, 1>;
    using F_SWIER10 = CortexM3::Field<ValueType, 10, 1>;
    using F_SWIER11 = CortexM3::Field<ValueType, 11, 1>;
    using F_SWIER12 = CortexM3::Field<ValueType, 12, 1>;
    using F_SWIER13 = CortexM3::Field<ValueType, 13, 1>;
    using F_SWIER14 = CortexM3::Field<ValueType, 14, 1>;
    using F_SWIER15 = CortexM3::Field<ValueType, 15, 1>;
    using F_SWIER16 = CortexM3::Field<ValueType, 16, 1>;
    using F_SWIER17 = CortexM3::Field<ValueType, 17, 1>;
    using F_SWIER18 = CortexM3::Field<ValueType, 18, 1>;
};

class PR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPR0() noexcept -> ValueType { return Reg::Read<F_PR0>(); }
    static void WritePR0(ValueType value) noexcept { Reg::Write<F_PR0>(value); }
    static auto ReadPR1() noexcept -> ValueType { return Reg::Read<F_PR1>(); }
    static void WritePR1(ValueType value) noexcept { Reg::Write<F_PR1>(value); }
    static auto ReadPR2() noexcept -> ValueType { return Reg::Read<F_PR2>(); }
    static void WritePR2(ValueType value) noexcept { Reg::Write<F_PR2>(value); }
    static auto ReadPR3() noexcept -> ValueType { return Reg::Read<F_PR3>(); }
    static void WritePR3(ValueType value) noexcept { Reg::Write<F_PR3>(value); }
    static auto ReadPR4() noexcept -> ValueType { return Reg::Read<F_PR4>(); }
    static void WritePR4(ValueType value) noexcept { Reg::Write<F_PR4>(value); }
    static auto ReadPR5() noexcept -> ValueType { return Reg::Read<F_PR5>(); }
    static void WritePR5(ValueType value) noexcept { Reg::Write<F_PR5>(value); }
    static auto ReadPR6() noexcept -> ValueType { return Reg::Read<F_PR6>(); }
    static void WritePR6(ValueType value) noexcept { Reg::Write<F_PR6>(value); }
    static auto ReadPR7() noexcept -> ValueType { return Reg::Read<F_PR7>(); }
    static void WritePR7(ValueType value) noexcept { Reg::Write<F_PR7>(value); }
    static auto ReadPR8() noexcept -> ValueType { return Reg::Read<F_PR8>(); }
    static void WritePR8(ValueType value) noexcept { Reg::Write<F_PR8>(value); }
    static auto ReadPR9() noexcept -> ValueType { return Reg::Read<F_PR9>(); }
    static void WritePR9(ValueType value) noexcept { Reg::Write<F_PR9>(value); }
    static auto ReadPR10() noexcept -> ValueType { return Reg::Read<F_PR10>(); }
    static void WritePR10(ValueType value) noexcept { Reg::Write<F_PR10>(value); }
    static auto ReadPR11() noexcept -> ValueType { return Reg::Read<F_PR11>(); }
    static void WritePR11(ValueType value) noexcept { Reg::Write<F_PR11>(value); }
    static auto ReadPR12() noexcept -> ValueType { return Reg::Read<F_PR12>(); }
    static void WritePR12(ValueType value) noexcept { Reg::Write<F_PR12>(value); }
    static auto ReadPR13() noexcept -> ValueType { return Reg::Read<F_PR13>(); }
    static void WritePR13(ValueType value) noexcept { Reg::Write<F_PR13>(value); }
    static auto ReadPR14() noexcept -> ValueType { return Reg::Read<F_PR14>(); }
    static void WritePR14(ValueType value) noexcept { Reg::Write<F_PR14>(value); }
    static auto ReadPR15() noexcept -> ValueType { return Reg::Read<F_PR15>(); }
    static void WritePR15(ValueType value) noexcept { Reg::Write<F_PR15>(value); }
    static auto ReadPR16() noexcept -> ValueType { return Reg::Read<F_PR16>(); }
    static void WritePR16(ValueType value) noexcept { Reg::Write<F_PR16>(value); }
    static auto ReadPR17() noexcept -> ValueType { return Reg::Read<F_PR17>(); }
    static void WritePR17(ValueType value) noexcept { Reg::Write<F_PR17>(value); }
    static auto ReadPR18() noexcept -> ValueType { return Reg::Read<F_PR18>(); }
    static void WritePR18(ValueType value) noexcept { Reg::Write<F_PR18>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40010414;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PR0 = CortexM3::Field<ValueType, 0, 1>;
    using F_PR1 = CortexM3::Field<ValueType, 1, 1>;
    using F_PR2 = CortexM3::Field<ValueType, 2, 1>;
    using F_PR3 = CortexM3::Field<ValueType, 3, 1>;
    using F_PR4 = CortexM3::Field<ValueType, 4, 1>;
    using F_PR5 = CortexM3::Field<ValueType, 5, 1>;
    using F_PR6 = CortexM3::Field<ValueType, 6, 1>;
    using F_PR7 = CortexM3::Field<ValueType, 7, 1>;
    using F_PR8 = CortexM3::Field<ValueType, 8, 1>;
    using F_PR9 = CortexM3::Field<ValueType, 9, 1>;
    using F_PR10 = CortexM3::Field<ValueType, 10, 1>;
    using F_PR11 = CortexM3::Field<ValueType, 11, 1>;
    using F_PR12 = CortexM3::Field<ValueType, 12, 1>;
    using F_PR13 = CortexM3::Field<ValueType, 13, 1>;
    using F_PR14 = CortexM3::Field<ValueType, 14, 1>;
    using F_PR15 = CortexM3::Field<ValueType, 15, 1>;
    using F_PR16 = CortexM3::Field<ValueType, 16, 1>;
    using F_PR17 = CortexM3::Field<ValueType, 17, 1>;
    using F_PR18 = CortexM3::Field<ValueType, 18, 1>;
};

} // namespace STM32F103::EXTI
