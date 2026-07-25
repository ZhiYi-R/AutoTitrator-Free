#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::ADC1 {

class SR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSTRT() noexcept -> ValueType { return Reg::Read<F_STRT>(); }
    static void WriteSTRT(ValueType value) noexcept { Reg::Write<F_STRT>(value); }
    static auto ReadJSTRT() noexcept -> ValueType { return Reg::Read<F_JSTRT>(); }
    static void WriteJSTRT(ValueType value) noexcept { Reg::Write<F_JSTRT>(value); }
    static auto ReadJEOC() noexcept -> ValueType { return Reg::Read<F_JEOC>(); }
    static void WriteJEOC(ValueType value) noexcept { Reg::Write<F_JEOC>(value); }
    static auto ReadEOC() noexcept -> ValueType { return Reg::Read<F_EOC>(); }
    static void WriteEOC(ValueType value) noexcept { Reg::Write<F_EOC>(value); }
    static auto ReadAWD() noexcept -> ValueType { return Reg::Read<F_AWD>(); }
    static void WriteAWD(ValueType value) noexcept { Reg::Write<F_AWD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012400;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STRT = CortexM3::Field<ValueType, 4, 1>;
    using F_JSTRT = CortexM3::Field<ValueType, 3, 1>;
    using F_JEOC = CortexM3::Field<ValueType, 2, 1>;
    using F_EOC = CortexM3::Field<ValueType, 1, 1>;
    using F_AWD = CortexM3::Field<ValueType, 0, 1>;
};

class CR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadAWDEN() noexcept -> ValueType { return Reg::Read<F_AWDEN>(); }
    static void WriteAWDEN(ValueType value) noexcept { Reg::Write<F_AWDEN>(value); }
    static auto ReadJAWDEN() noexcept -> ValueType { return Reg::Read<F_JAWDEN>(); }
    static void WriteJAWDEN(ValueType value) noexcept { Reg::Write<F_JAWDEN>(value); }
    static auto ReadDUALMOD() noexcept -> ValueType { return Reg::Read<F_DUALMOD>(); }
    static void WriteDUALMOD(ValueType value) noexcept { Reg::Write<F_DUALMOD>(value); }
    static auto ReadDISCNUM() noexcept -> ValueType { return Reg::Read<F_DISCNUM>(); }
    static void WriteDISCNUM(ValueType value) noexcept { Reg::Write<F_DISCNUM>(value); }
    static auto ReadJDISCEN() noexcept -> ValueType { return Reg::Read<F_JDISCEN>(); }
    static void WriteJDISCEN(ValueType value) noexcept { Reg::Write<F_JDISCEN>(value); }
    static auto ReadDISCEN() noexcept -> ValueType { return Reg::Read<F_DISCEN>(); }
    static void WriteDISCEN(ValueType value) noexcept { Reg::Write<F_DISCEN>(value); }
    static auto ReadJAUTO() noexcept -> ValueType { return Reg::Read<F_JAUTO>(); }
    static void WriteJAUTO(ValueType value) noexcept { Reg::Write<F_JAUTO>(value); }
    static auto ReadAWDSGL() noexcept -> ValueType { return Reg::Read<F_AWDSGL>(); }
    static void WriteAWDSGL(ValueType value) noexcept { Reg::Write<F_AWDSGL>(value); }
    static auto ReadSCAN() noexcept -> ValueType { return Reg::Read<F_SCAN>(); }
    static void WriteSCAN(ValueType value) noexcept { Reg::Write<F_SCAN>(value); }
    static auto ReadJEOCIE() noexcept -> ValueType { return Reg::Read<F_JEOCIE>(); }
    static void WriteJEOCIE(ValueType value) noexcept { Reg::Write<F_JEOCIE>(value); }
    static auto ReadAWDIE() noexcept -> ValueType { return Reg::Read<F_AWDIE>(); }
    static void WriteAWDIE(ValueType value) noexcept { Reg::Write<F_AWDIE>(value); }
    static auto ReadEOCIE() noexcept -> ValueType { return Reg::Read<F_EOCIE>(); }
    static void WriteEOCIE(ValueType value) noexcept { Reg::Write<F_EOCIE>(value); }
    static auto ReadAWDCH() noexcept -> ValueType { return Reg::Read<F_AWDCH>(); }
    static void WriteAWDCH(ValueType value) noexcept { Reg::Write<F_AWDCH>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012404;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_AWDEN = CortexM3::Field<ValueType, 23, 1>;
    using F_JAWDEN = CortexM3::Field<ValueType, 22, 1>;
    using F_DUALMOD = CortexM3::Field<ValueType, 16, 4>;
    using F_DISCNUM = CortexM3::Field<ValueType, 13, 3>;
    using F_JDISCEN = CortexM3::Field<ValueType, 12, 1>;
    using F_DISCEN = CortexM3::Field<ValueType, 11, 1>;
    using F_JAUTO = CortexM3::Field<ValueType, 10, 1>;
    using F_AWDSGL = CortexM3::Field<ValueType, 9, 1>;
    using F_SCAN = CortexM3::Field<ValueType, 8, 1>;
    using F_JEOCIE = CortexM3::Field<ValueType, 7, 1>;
    using F_AWDIE = CortexM3::Field<ValueType, 6, 1>;
    using F_EOCIE = CortexM3::Field<ValueType, 5, 1>;
    using F_AWDCH = CortexM3::Field<ValueType, 0, 5>;
};

class CR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTSVREFE() noexcept -> ValueType { return Reg::Read<F_TSVREFE>(); }
    static void WriteTSVREFE(ValueType value) noexcept { Reg::Write<F_TSVREFE>(value); }
    static auto ReadSWSTART() noexcept -> ValueType { return Reg::Read<F_SWSTART>(); }
    static void WriteSWSTART(ValueType value) noexcept { Reg::Write<F_SWSTART>(value); }
    static auto ReadJSWSTART() noexcept -> ValueType { return Reg::Read<F_JSWSTART>(); }
    static void WriteJSWSTART(ValueType value) noexcept { Reg::Write<F_JSWSTART>(value); }
    static auto ReadEXTTRIG() noexcept -> ValueType { return Reg::Read<F_EXTTRIG>(); }
    static void WriteEXTTRIG(ValueType value) noexcept { Reg::Write<F_EXTTRIG>(value); }
    static auto ReadEXTSEL() noexcept -> ValueType { return Reg::Read<F_EXTSEL>(); }
    static void WriteEXTSEL(ValueType value) noexcept { Reg::Write<F_EXTSEL>(value); }
    static auto ReadJEXTTRIG() noexcept -> ValueType { return Reg::Read<F_JEXTTRIG>(); }
    static void WriteJEXTTRIG(ValueType value) noexcept { Reg::Write<F_JEXTTRIG>(value); }
    static auto ReadJEXTSEL() noexcept -> ValueType { return Reg::Read<F_JEXTSEL>(); }
    static void WriteJEXTSEL(ValueType value) noexcept { Reg::Write<F_JEXTSEL>(value); }
    static auto ReadALIGN() noexcept -> ValueType { return Reg::Read<F_ALIGN>(); }
    static void WriteALIGN(ValueType value) noexcept { Reg::Write<F_ALIGN>(value); }
    static auto ReadDMA() noexcept -> ValueType { return Reg::Read<F_DMA>(); }
    static void WriteDMA(ValueType value) noexcept { Reg::Write<F_DMA>(value); }
    static auto ReadRSTCAL() noexcept -> ValueType { return Reg::Read<F_RSTCAL>(); }
    static void WriteRSTCAL(ValueType value) noexcept { Reg::Write<F_RSTCAL>(value); }
    static auto ReadCAL() noexcept -> ValueType { return Reg::Read<F_CAL>(); }
    static void WriteCAL(ValueType value) noexcept { Reg::Write<F_CAL>(value); }
    static auto ReadCONT() noexcept -> ValueType { return Reg::Read<F_CONT>(); }
    static void WriteCONT(ValueType value) noexcept { Reg::Write<F_CONT>(value); }
    static auto ReadADON() noexcept -> ValueType { return Reg::Read<F_ADON>(); }
    static void WriteADON(ValueType value) noexcept { Reg::Write<F_ADON>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012408;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TSVREFE = CortexM3::Field<ValueType, 23, 1>;
    using F_SWSTART = CortexM3::Field<ValueType, 22, 1>;
    using F_JSWSTART = CortexM3::Field<ValueType, 21, 1>;
    using F_EXTTRIG = CortexM3::Field<ValueType, 20, 1>;
    using F_EXTSEL = CortexM3::Field<ValueType, 17, 3>;
    using F_JEXTTRIG = CortexM3::Field<ValueType, 15, 1>;
    using F_JEXTSEL = CortexM3::Field<ValueType, 12, 3>;
    using F_ALIGN = CortexM3::Field<ValueType, 11, 1>;
    using F_DMA = CortexM3::Field<ValueType, 8, 1>;
    using F_RSTCAL = CortexM3::Field<ValueType, 3, 1>;
    using F_CAL = CortexM3::Field<ValueType, 2, 1>;
    using F_CONT = CortexM3::Field<ValueType, 1, 1>;
    using F_ADON = CortexM3::Field<ValueType, 0, 1>;
};

class SMPR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSMP10() noexcept -> ValueType { return Reg::Read<F_SMP10>(); }
    static void WriteSMP10(ValueType value) noexcept { Reg::Write<F_SMP10>(value); }
    static auto ReadSMP11() noexcept -> ValueType { return Reg::Read<F_SMP11>(); }
    static void WriteSMP11(ValueType value) noexcept { Reg::Write<F_SMP11>(value); }
    static auto ReadSMP12() noexcept -> ValueType { return Reg::Read<F_SMP12>(); }
    static void WriteSMP12(ValueType value) noexcept { Reg::Write<F_SMP12>(value); }
    static auto ReadSMP13() noexcept -> ValueType { return Reg::Read<F_SMP13>(); }
    static void WriteSMP13(ValueType value) noexcept { Reg::Write<F_SMP13>(value); }
    static auto ReadSMP14() noexcept -> ValueType { return Reg::Read<F_SMP14>(); }
    static void WriteSMP14(ValueType value) noexcept { Reg::Write<F_SMP14>(value); }
    static auto ReadSMP15() noexcept -> ValueType { return Reg::Read<F_SMP15>(); }
    static void WriteSMP15(ValueType value) noexcept { Reg::Write<F_SMP15>(value); }
    static auto ReadSMP16() noexcept -> ValueType { return Reg::Read<F_SMP16>(); }
    static void WriteSMP16(ValueType value) noexcept { Reg::Write<F_SMP16>(value); }
    static auto ReadSMP17() noexcept -> ValueType { return Reg::Read<F_SMP17>(); }
    static void WriteSMP17(ValueType value) noexcept { Reg::Write<F_SMP17>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001240c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SMP10 = CortexM3::Field<ValueType, 0, 3>;
    using F_SMP11 = CortexM3::Field<ValueType, 3, 3>;
    using F_SMP12 = CortexM3::Field<ValueType, 6, 3>;
    using F_SMP13 = CortexM3::Field<ValueType, 9, 3>;
    using F_SMP14 = CortexM3::Field<ValueType, 12, 3>;
    using F_SMP15 = CortexM3::Field<ValueType, 15, 3>;
    using F_SMP16 = CortexM3::Field<ValueType, 18, 3>;
    using F_SMP17 = CortexM3::Field<ValueType, 21, 3>;
};

class SMPR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSMP0() noexcept -> ValueType { return Reg::Read<F_SMP0>(); }
    static void WriteSMP0(ValueType value) noexcept { Reg::Write<F_SMP0>(value); }
    static auto ReadSMP1() noexcept -> ValueType { return Reg::Read<F_SMP1>(); }
    static void WriteSMP1(ValueType value) noexcept { Reg::Write<F_SMP1>(value); }
    static auto ReadSMP2() noexcept -> ValueType { return Reg::Read<F_SMP2>(); }
    static void WriteSMP2(ValueType value) noexcept { Reg::Write<F_SMP2>(value); }
    static auto ReadSMP3() noexcept -> ValueType { return Reg::Read<F_SMP3>(); }
    static void WriteSMP3(ValueType value) noexcept { Reg::Write<F_SMP3>(value); }
    static auto ReadSMP4() noexcept -> ValueType { return Reg::Read<F_SMP4>(); }
    static void WriteSMP4(ValueType value) noexcept { Reg::Write<F_SMP4>(value); }
    static auto ReadSMP5() noexcept -> ValueType { return Reg::Read<F_SMP5>(); }
    static void WriteSMP5(ValueType value) noexcept { Reg::Write<F_SMP5>(value); }
    static auto ReadSMP6() noexcept -> ValueType { return Reg::Read<F_SMP6>(); }
    static void WriteSMP6(ValueType value) noexcept { Reg::Write<F_SMP6>(value); }
    static auto ReadSMP7() noexcept -> ValueType { return Reg::Read<F_SMP7>(); }
    static void WriteSMP7(ValueType value) noexcept { Reg::Write<F_SMP7>(value); }
    static auto ReadSMP8() noexcept -> ValueType { return Reg::Read<F_SMP8>(); }
    static void WriteSMP8(ValueType value) noexcept { Reg::Write<F_SMP8>(value); }
    static auto ReadSMP9() noexcept -> ValueType { return Reg::Read<F_SMP9>(); }
    static void WriteSMP9(ValueType value) noexcept { Reg::Write<F_SMP9>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012410;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SMP0 = CortexM3::Field<ValueType, 0, 3>;
    using F_SMP1 = CortexM3::Field<ValueType, 3, 3>;
    using F_SMP2 = CortexM3::Field<ValueType, 6, 3>;
    using F_SMP3 = CortexM3::Field<ValueType, 9, 3>;
    using F_SMP4 = CortexM3::Field<ValueType, 12, 3>;
    using F_SMP5 = CortexM3::Field<ValueType, 15, 3>;
    using F_SMP6 = CortexM3::Field<ValueType, 18, 3>;
    using F_SMP7 = CortexM3::Field<ValueType, 21, 3>;
    using F_SMP8 = CortexM3::Field<ValueType, 24, 3>;
    using F_SMP9 = CortexM3::Field<ValueType, 27, 3>;
};

class JOFR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadJOFFSET1() noexcept -> ValueType { return Reg::Read<F_JOFFSET1>(); }
    static void WriteJOFFSET1(ValueType value) noexcept { Reg::Write<F_JOFFSET1>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012414;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_JOFFSET1 = CortexM3::Field<ValueType, 0, 12>;
};

class JOFR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadJOFFSET2() noexcept -> ValueType { return Reg::Read<F_JOFFSET2>(); }
    static void WriteJOFFSET2(ValueType value) noexcept { Reg::Write<F_JOFFSET2>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012418;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_JOFFSET2 = CortexM3::Field<ValueType, 0, 12>;
};

class JOFR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadJOFFSET3() noexcept -> ValueType { return Reg::Read<F_JOFFSET3>(); }
    static void WriteJOFFSET3(ValueType value) noexcept { Reg::Write<F_JOFFSET3>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001241c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_JOFFSET3 = CortexM3::Field<ValueType, 0, 12>;
};

class JOFR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadJOFFSET4() noexcept -> ValueType { return Reg::Read<F_JOFFSET4>(); }
    static void WriteJOFFSET4(ValueType value) noexcept { Reg::Write<F_JOFFSET4>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012420;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_JOFFSET4 = CortexM3::Field<ValueType, 0, 12>;
};

class HTR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000FFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadHT() noexcept -> ValueType { return Reg::Read<F_HT>(); }
    static void WriteHT(ValueType value) noexcept { Reg::Write<F_HT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012424;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_HT = CortexM3::Field<ValueType, 0, 12>;
};

class LTR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadLT() noexcept -> ValueType { return Reg::Read<F_LT>(); }
    static void WriteLT(ValueType value) noexcept { Reg::Write<F_LT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012428;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_LT = CortexM3::Field<ValueType, 0, 12>;
};

class SQR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadL() noexcept -> ValueType { return Reg::Read<F_L>(); }
    static void WriteL(ValueType value) noexcept { Reg::Write<F_L>(value); }
    static auto ReadSQ16() noexcept -> ValueType { return Reg::Read<F_SQ16>(); }
    static void WriteSQ16(ValueType value) noexcept { Reg::Write<F_SQ16>(value); }
    static auto ReadSQ15() noexcept -> ValueType { return Reg::Read<F_SQ15>(); }
    static void WriteSQ15(ValueType value) noexcept { Reg::Write<F_SQ15>(value); }
    static auto ReadSQ14() noexcept -> ValueType { return Reg::Read<F_SQ14>(); }
    static void WriteSQ14(ValueType value) noexcept { Reg::Write<F_SQ14>(value); }
    static auto ReadSQ13() noexcept -> ValueType { return Reg::Read<F_SQ13>(); }
    static void WriteSQ13(ValueType value) noexcept { Reg::Write<F_SQ13>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001242c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_L = CortexM3::Field<ValueType, 20, 4>;
    using F_SQ16 = CortexM3::Field<ValueType, 15, 5>;
    using F_SQ15 = CortexM3::Field<ValueType, 10, 5>;
    using F_SQ14 = CortexM3::Field<ValueType, 5, 5>;
    using F_SQ13 = CortexM3::Field<ValueType, 0, 5>;
};

class SQR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSQ12() noexcept -> ValueType { return Reg::Read<F_SQ12>(); }
    static void WriteSQ12(ValueType value) noexcept { Reg::Write<F_SQ12>(value); }
    static auto ReadSQ11() noexcept -> ValueType { return Reg::Read<F_SQ11>(); }
    static void WriteSQ11(ValueType value) noexcept { Reg::Write<F_SQ11>(value); }
    static auto ReadSQ10() noexcept -> ValueType { return Reg::Read<F_SQ10>(); }
    static void WriteSQ10(ValueType value) noexcept { Reg::Write<F_SQ10>(value); }
    static auto ReadSQ9() noexcept -> ValueType { return Reg::Read<F_SQ9>(); }
    static void WriteSQ9(ValueType value) noexcept { Reg::Write<F_SQ9>(value); }
    static auto ReadSQ8() noexcept -> ValueType { return Reg::Read<F_SQ8>(); }
    static void WriteSQ8(ValueType value) noexcept { Reg::Write<F_SQ8>(value); }
    static auto ReadSQ7() noexcept -> ValueType { return Reg::Read<F_SQ7>(); }
    static void WriteSQ7(ValueType value) noexcept { Reg::Write<F_SQ7>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012430;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SQ12 = CortexM3::Field<ValueType, 25, 5>;
    using F_SQ11 = CortexM3::Field<ValueType, 20, 5>;
    using F_SQ10 = CortexM3::Field<ValueType, 15, 5>;
    using F_SQ9 = CortexM3::Field<ValueType, 10, 5>;
    using F_SQ8 = CortexM3::Field<ValueType, 5, 5>;
    using F_SQ7 = CortexM3::Field<ValueType, 0, 5>;
};

class SQR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSQ6() noexcept -> ValueType { return Reg::Read<F_SQ6>(); }
    static void WriteSQ6(ValueType value) noexcept { Reg::Write<F_SQ6>(value); }
    static auto ReadSQ5() noexcept -> ValueType { return Reg::Read<F_SQ5>(); }
    static void WriteSQ5(ValueType value) noexcept { Reg::Write<F_SQ5>(value); }
    static auto ReadSQ4() noexcept -> ValueType { return Reg::Read<F_SQ4>(); }
    static void WriteSQ4(ValueType value) noexcept { Reg::Write<F_SQ4>(value); }
    static auto ReadSQ3() noexcept -> ValueType { return Reg::Read<F_SQ3>(); }
    static void WriteSQ3(ValueType value) noexcept { Reg::Write<F_SQ3>(value); }
    static auto ReadSQ2() noexcept -> ValueType { return Reg::Read<F_SQ2>(); }
    static void WriteSQ2(ValueType value) noexcept { Reg::Write<F_SQ2>(value); }
    static auto ReadSQ1() noexcept -> ValueType { return Reg::Read<F_SQ1>(); }
    static void WriteSQ1(ValueType value) noexcept { Reg::Write<F_SQ1>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012434;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SQ6 = CortexM3::Field<ValueType, 25, 5>;
    using F_SQ5 = CortexM3::Field<ValueType, 20, 5>;
    using F_SQ4 = CortexM3::Field<ValueType, 15, 5>;
    using F_SQ3 = CortexM3::Field<ValueType, 10, 5>;
    using F_SQ2 = CortexM3::Field<ValueType, 5, 5>;
    using F_SQ1 = CortexM3::Field<ValueType, 0, 5>;
};

class JSQR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadJL() noexcept -> ValueType { return Reg::Read<F_JL>(); }
    static void WriteJL(ValueType value) noexcept { Reg::Write<F_JL>(value); }
    static auto ReadJSQ4() noexcept -> ValueType { return Reg::Read<F_JSQ4>(); }
    static void WriteJSQ4(ValueType value) noexcept { Reg::Write<F_JSQ4>(value); }
    static auto ReadJSQ3() noexcept -> ValueType { return Reg::Read<F_JSQ3>(); }
    static void WriteJSQ3(ValueType value) noexcept { Reg::Write<F_JSQ3>(value); }
    static auto ReadJSQ2() noexcept -> ValueType { return Reg::Read<F_JSQ2>(); }
    static void WriteJSQ2(ValueType value) noexcept { Reg::Write<F_JSQ2>(value); }
    static auto ReadJSQ1() noexcept -> ValueType { return Reg::Read<F_JSQ1>(); }
    static void WriteJSQ1(ValueType value) noexcept { Reg::Write<F_JSQ1>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40012438;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_JL = CortexM3::Field<ValueType, 20, 2>;
    using F_JSQ4 = CortexM3::Field<ValueType, 15, 5>;
    using F_JSQ3 = CortexM3::Field<ValueType, 10, 5>;
    using F_JSQ2 = CortexM3::Field<ValueType, 5, 5>;
    using F_JSQ1 = CortexM3::Field<ValueType, 0, 5>;
};

class JDR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadJDATA() noexcept -> ValueType { return Reg::Read<F_JDATA>(); }

private:
    static constexpr std::uintptr_t Address = 0x4001243c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_JDATA = CortexM3::Field<ValueType, 0, 16>;
};

class JDR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadJDATA() noexcept -> ValueType { return Reg::Read<F_JDATA>(); }

private:
    static constexpr std::uintptr_t Address = 0x40012440;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_JDATA = CortexM3::Field<ValueType, 0, 16>;
};

class JDR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadJDATA() noexcept -> ValueType { return Reg::Read<F_JDATA>(); }

private:
    static constexpr std::uintptr_t Address = 0x40012444;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_JDATA = CortexM3::Field<ValueType, 0, 16>;
};

class JDR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadJDATA() noexcept -> ValueType { return Reg::Read<F_JDATA>(); }

private:
    static constexpr std::uintptr_t Address = 0x40012448;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_JDATA = CortexM3::Field<ValueType, 0, 16>;
};

class DR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDATA() noexcept -> ValueType { return Reg::Read<F_DATA>(); }
    static auto ReadADC2DATA() noexcept -> ValueType { return Reg::Read<F_ADC2DATA>(); }

private:
    static constexpr std::uintptr_t Address = 0x4001244c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA = CortexM3::Field<ValueType, 0, 16>;
    using F_ADC2DATA = CortexM3::Field<ValueType, 16, 16>;
};

} // namespace STM32F103::ADC1
