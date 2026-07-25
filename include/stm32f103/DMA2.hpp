#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::DMA2 {

class ISR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadGIF1() noexcept -> ValueType { return Reg::Read<F_GIF1>(); }
    static auto ReadTCIF1() noexcept -> ValueType { return Reg::Read<F_TCIF1>(); }
    static auto ReadHTIF1() noexcept -> ValueType { return Reg::Read<F_HTIF1>(); }
    static auto ReadTEIF1() noexcept -> ValueType { return Reg::Read<F_TEIF1>(); }
    static auto ReadGIF2() noexcept -> ValueType { return Reg::Read<F_GIF2>(); }
    static auto ReadTCIF2() noexcept -> ValueType { return Reg::Read<F_TCIF2>(); }
    static auto ReadHTIF2() noexcept -> ValueType { return Reg::Read<F_HTIF2>(); }
    static auto ReadTEIF2() noexcept -> ValueType { return Reg::Read<F_TEIF2>(); }
    static auto ReadGIF3() noexcept -> ValueType { return Reg::Read<F_GIF3>(); }
    static auto ReadTCIF3() noexcept -> ValueType { return Reg::Read<F_TCIF3>(); }
    static auto ReadHTIF3() noexcept -> ValueType { return Reg::Read<F_HTIF3>(); }
    static auto ReadTEIF3() noexcept -> ValueType { return Reg::Read<F_TEIF3>(); }
    static auto ReadGIF4() noexcept -> ValueType { return Reg::Read<F_GIF4>(); }
    static auto ReadTCIF4() noexcept -> ValueType { return Reg::Read<F_TCIF4>(); }
    static auto ReadHTIF4() noexcept -> ValueType { return Reg::Read<F_HTIF4>(); }
    static auto ReadTEIF4() noexcept -> ValueType { return Reg::Read<F_TEIF4>(); }
    static auto ReadGIF5() noexcept -> ValueType { return Reg::Read<F_GIF5>(); }
    static auto ReadTCIF5() noexcept -> ValueType { return Reg::Read<F_TCIF5>(); }
    static auto ReadHTIF5() noexcept -> ValueType { return Reg::Read<F_HTIF5>(); }
    static auto ReadTEIF5() noexcept -> ValueType { return Reg::Read<F_TEIF5>(); }
    static auto ReadGIF6() noexcept -> ValueType { return Reg::Read<F_GIF6>(); }
    static auto ReadTCIF6() noexcept -> ValueType { return Reg::Read<F_TCIF6>(); }
    static auto ReadHTIF6() noexcept -> ValueType { return Reg::Read<F_HTIF6>(); }
    static auto ReadTEIF6() noexcept -> ValueType { return Reg::Read<F_TEIF6>(); }
    static auto ReadGIF7() noexcept -> ValueType { return Reg::Read<F_GIF7>(); }
    static auto ReadTCIF7() noexcept -> ValueType { return Reg::Read<F_TCIF7>(); }
    static auto ReadHTIF7() noexcept -> ValueType { return Reg::Read<F_HTIF7>(); }
    static auto ReadTEIF7() noexcept -> ValueType { return Reg::Read<F_TEIF7>(); }

private:
    static constexpr std::uintptr_t Address = 0x40020400;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_GIF1 = CortexM3::Field<ValueType, 0, 1>;
    using F_TCIF1 = CortexM3::Field<ValueType, 1, 1>;
    using F_HTIF1 = CortexM3::Field<ValueType, 2, 1>;
    using F_TEIF1 = CortexM3::Field<ValueType, 3, 1>;
    using F_GIF2 = CortexM3::Field<ValueType, 4, 1>;
    using F_TCIF2 = CortexM3::Field<ValueType, 5, 1>;
    using F_HTIF2 = CortexM3::Field<ValueType, 6, 1>;
    using F_TEIF2 = CortexM3::Field<ValueType, 7, 1>;
    using F_GIF3 = CortexM3::Field<ValueType, 8, 1>;
    using F_TCIF3 = CortexM3::Field<ValueType, 9, 1>;
    using F_HTIF3 = CortexM3::Field<ValueType, 10, 1>;
    using F_TEIF3 = CortexM3::Field<ValueType, 11, 1>;
    using F_GIF4 = CortexM3::Field<ValueType, 12, 1>;
    using F_TCIF4 = CortexM3::Field<ValueType, 13, 1>;
    using F_HTIF4 = CortexM3::Field<ValueType, 14, 1>;
    using F_TEIF4 = CortexM3::Field<ValueType, 15, 1>;
    using F_GIF5 = CortexM3::Field<ValueType, 16, 1>;
    using F_TCIF5 = CortexM3::Field<ValueType, 17, 1>;
    using F_HTIF5 = CortexM3::Field<ValueType, 18, 1>;
    using F_TEIF5 = CortexM3::Field<ValueType, 19, 1>;
    using F_GIF6 = CortexM3::Field<ValueType, 20, 1>;
    using F_TCIF6 = CortexM3::Field<ValueType, 21, 1>;
    using F_HTIF6 = CortexM3::Field<ValueType, 22, 1>;
    using F_TEIF6 = CortexM3::Field<ValueType, 23, 1>;
    using F_GIF7 = CortexM3::Field<ValueType, 24, 1>;
    using F_TCIF7 = CortexM3::Field<ValueType, 25, 1>;
    using F_HTIF7 = CortexM3::Field<ValueType, 26, 1>;
    using F_TEIF7 = CortexM3::Field<ValueType, 27, 1>;
};

class IFCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteCGIF1(ValueType value) noexcept { Reg::Write<F_CGIF1>(value); }
    static void WriteCGIF2(ValueType value) noexcept { Reg::Write<F_CGIF2>(value); }
    static void WriteCGIF3(ValueType value) noexcept { Reg::Write<F_CGIF3>(value); }
    static void WriteCGIF4(ValueType value) noexcept { Reg::Write<F_CGIF4>(value); }
    static void WriteCGIF5(ValueType value) noexcept { Reg::Write<F_CGIF5>(value); }
    static void WriteCGIF6(ValueType value) noexcept { Reg::Write<F_CGIF6>(value); }
    static void WriteCGIF7(ValueType value) noexcept { Reg::Write<F_CGIF7>(value); }
    static void WriteCTCIF1(ValueType value) noexcept { Reg::Write<F_CTCIF1>(value); }
    static void WriteCTCIF2(ValueType value) noexcept { Reg::Write<F_CTCIF2>(value); }
    static void WriteCTCIF3(ValueType value) noexcept { Reg::Write<F_CTCIF3>(value); }
    static void WriteCTCIF4(ValueType value) noexcept { Reg::Write<F_CTCIF4>(value); }
    static void WriteCTCIF5(ValueType value) noexcept { Reg::Write<F_CTCIF5>(value); }
    static void WriteCTCIF6(ValueType value) noexcept { Reg::Write<F_CTCIF6>(value); }
    static void WriteCTCIF7(ValueType value) noexcept { Reg::Write<F_CTCIF7>(value); }
    static void WriteCHTIF1(ValueType value) noexcept { Reg::Write<F_CHTIF1>(value); }
    static void WriteCHTIF2(ValueType value) noexcept { Reg::Write<F_CHTIF2>(value); }
    static void WriteCHTIF3(ValueType value) noexcept { Reg::Write<F_CHTIF3>(value); }
    static void WriteCHTIF4(ValueType value) noexcept { Reg::Write<F_CHTIF4>(value); }
    static void WriteCHTIF5(ValueType value) noexcept { Reg::Write<F_CHTIF5>(value); }
    static void WriteCHTIF6(ValueType value) noexcept { Reg::Write<F_CHTIF6>(value); }
    static void WriteCHTIF7(ValueType value) noexcept { Reg::Write<F_CHTIF7>(value); }
    static void WriteCTEIF1(ValueType value) noexcept { Reg::Write<F_CTEIF1>(value); }
    static void WriteCTEIF2(ValueType value) noexcept { Reg::Write<F_CTEIF2>(value); }
    static void WriteCTEIF3(ValueType value) noexcept { Reg::Write<F_CTEIF3>(value); }
    static void WriteCTEIF4(ValueType value) noexcept { Reg::Write<F_CTEIF4>(value); }
    static void WriteCTEIF5(ValueType value) noexcept { Reg::Write<F_CTEIF5>(value); }
    static void WriteCTEIF6(ValueType value) noexcept { Reg::Write<F_CTEIF6>(value); }
    static void WriteCTEIF7(ValueType value) noexcept { Reg::Write<F_CTEIF7>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020404;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CGIF1 = CortexM3::Field<ValueType, 0, 1>;
    using F_CGIF2 = CortexM3::Field<ValueType, 4, 1>;
    using F_CGIF3 = CortexM3::Field<ValueType, 8, 1>;
    using F_CGIF4 = CortexM3::Field<ValueType, 12, 1>;
    using F_CGIF5 = CortexM3::Field<ValueType, 16, 1>;
    using F_CGIF6 = CortexM3::Field<ValueType, 20, 1>;
    using F_CGIF7 = CortexM3::Field<ValueType, 24, 1>;
    using F_CTCIF1 = CortexM3::Field<ValueType, 1, 1>;
    using F_CTCIF2 = CortexM3::Field<ValueType, 5, 1>;
    using F_CTCIF3 = CortexM3::Field<ValueType, 9, 1>;
    using F_CTCIF4 = CortexM3::Field<ValueType, 13, 1>;
    using F_CTCIF5 = CortexM3::Field<ValueType, 17, 1>;
    using F_CTCIF6 = CortexM3::Field<ValueType, 21, 1>;
    using F_CTCIF7 = CortexM3::Field<ValueType, 25, 1>;
    using F_CHTIF1 = CortexM3::Field<ValueType, 2, 1>;
    using F_CHTIF2 = CortexM3::Field<ValueType, 6, 1>;
    using F_CHTIF3 = CortexM3::Field<ValueType, 10, 1>;
    using F_CHTIF4 = CortexM3::Field<ValueType, 14, 1>;
    using F_CHTIF5 = CortexM3::Field<ValueType, 18, 1>;
    using F_CHTIF6 = CortexM3::Field<ValueType, 22, 1>;
    using F_CHTIF7 = CortexM3::Field<ValueType, 26, 1>;
    using F_CTEIF1 = CortexM3::Field<ValueType, 3, 1>;
    using F_CTEIF2 = CortexM3::Field<ValueType, 7, 1>;
    using F_CTEIF3 = CortexM3::Field<ValueType, 11, 1>;
    using F_CTEIF4 = CortexM3::Field<ValueType, 15, 1>;
    using F_CTEIF5 = CortexM3::Field<ValueType, 19, 1>;
    using F_CTEIF6 = CortexM3::Field<ValueType, 23, 1>;
    using F_CTEIF7 = CortexM3::Field<ValueType, 27, 1>;
};

class CCR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEN() noexcept -> ValueType { return Reg::Read<F_EN>(); }
    static void WriteEN(ValueType value) noexcept { Reg::Write<F_EN>(value); }
    static auto ReadTCIE() noexcept -> ValueType { return Reg::Read<F_TCIE>(); }
    static void WriteTCIE(ValueType value) noexcept { Reg::Write<F_TCIE>(value); }
    static auto ReadHTIE() noexcept -> ValueType { return Reg::Read<F_HTIE>(); }
    static void WriteHTIE(ValueType value) noexcept { Reg::Write<F_HTIE>(value); }
    static auto ReadTEIE() noexcept -> ValueType { return Reg::Read<F_TEIE>(); }
    static void WriteTEIE(ValueType value) noexcept { Reg::Write<F_TEIE>(value); }
    static auto ReadDIR() noexcept -> ValueType { return Reg::Read<F_DIR>(); }
    static void WriteDIR(ValueType value) noexcept { Reg::Write<F_DIR>(value); }
    static auto ReadCIRC() noexcept -> ValueType { return Reg::Read<F_CIRC>(); }
    static void WriteCIRC(ValueType value) noexcept { Reg::Write<F_CIRC>(value); }
    static auto ReadPINC() noexcept -> ValueType { return Reg::Read<F_PINC>(); }
    static void WritePINC(ValueType value) noexcept { Reg::Write<F_PINC>(value); }
    static auto ReadMINC() noexcept -> ValueType { return Reg::Read<F_MINC>(); }
    static void WriteMINC(ValueType value) noexcept { Reg::Write<F_MINC>(value); }
    static auto ReadPSIZE() noexcept -> ValueType { return Reg::Read<F_PSIZE>(); }
    static void WritePSIZE(ValueType value) noexcept { Reg::Write<F_PSIZE>(value); }
    static auto ReadMSIZE() noexcept -> ValueType { return Reg::Read<F_MSIZE>(); }
    static void WriteMSIZE(ValueType value) noexcept { Reg::Write<F_MSIZE>(value); }
    static auto ReadPL() noexcept -> ValueType { return Reg::Read<F_PL>(); }
    static void WritePL(ValueType value) noexcept { Reg::Write<F_PL>(value); }
    static auto ReadMEM2MEM() noexcept -> ValueType { return Reg::Read<F_MEM2MEM>(); }
    static void WriteMEM2MEM(ValueType value) noexcept { Reg::Write<F_MEM2MEM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020408;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EN = CortexM3::Field<ValueType, 0, 1>;
    using F_TCIE = CortexM3::Field<ValueType, 1, 1>;
    using F_HTIE = CortexM3::Field<ValueType, 2, 1>;
    using F_TEIE = CortexM3::Field<ValueType, 3, 1>;
    using F_DIR = CortexM3::Field<ValueType, 4, 1>;
    using F_CIRC = CortexM3::Field<ValueType, 5, 1>;
    using F_PINC = CortexM3::Field<ValueType, 6, 1>;
    using F_MINC = CortexM3::Field<ValueType, 7, 1>;
    using F_PSIZE = CortexM3::Field<ValueType, 8, 2>;
    using F_MSIZE = CortexM3::Field<ValueType, 10, 2>;
    using F_PL = CortexM3::Field<ValueType, 12, 2>;
    using F_MEM2MEM = CortexM3::Field<ValueType, 14, 1>;
};

class CNDTR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadNDT() noexcept -> ValueType { return Reg::Read<F_NDT>(); }
    static void WriteNDT(ValueType value) noexcept { Reg::Write<F_NDT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002040c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NDT = CortexM3::Field<ValueType, 0, 16>;
};

class CPAR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPA() noexcept -> ValueType { return Reg::Read<F_PA>(); }
    static void WritePA(ValueType value) noexcept { Reg::Write<F_PA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020410;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PA = CortexM3::Field<ValueType, 0, 32>;
};

class CMAR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMA() noexcept -> ValueType { return Reg::Read<F_MA>(); }
    static void WriteMA(ValueType value) noexcept { Reg::Write<F_MA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020414;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MA = CortexM3::Field<ValueType, 0, 32>;
};

class CCR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEN() noexcept -> ValueType { return Reg::Read<F_EN>(); }
    static void WriteEN(ValueType value) noexcept { Reg::Write<F_EN>(value); }
    static auto ReadTCIE() noexcept -> ValueType { return Reg::Read<F_TCIE>(); }
    static void WriteTCIE(ValueType value) noexcept { Reg::Write<F_TCIE>(value); }
    static auto ReadHTIE() noexcept -> ValueType { return Reg::Read<F_HTIE>(); }
    static void WriteHTIE(ValueType value) noexcept { Reg::Write<F_HTIE>(value); }
    static auto ReadTEIE() noexcept -> ValueType { return Reg::Read<F_TEIE>(); }
    static void WriteTEIE(ValueType value) noexcept { Reg::Write<F_TEIE>(value); }
    static auto ReadDIR() noexcept -> ValueType { return Reg::Read<F_DIR>(); }
    static void WriteDIR(ValueType value) noexcept { Reg::Write<F_DIR>(value); }
    static auto ReadCIRC() noexcept -> ValueType { return Reg::Read<F_CIRC>(); }
    static void WriteCIRC(ValueType value) noexcept { Reg::Write<F_CIRC>(value); }
    static auto ReadPINC() noexcept -> ValueType { return Reg::Read<F_PINC>(); }
    static void WritePINC(ValueType value) noexcept { Reg::Write<F_PINC>(value); }
    static auto ReadMINC() noexcept -> ValueType { return Reg::Read<F_MINC>(); }
    static void WriteMINC(ValueType value) noexcept { Reg::Write<F_MINC>(value); }
    static auto ReadPSIZE() noexcept -> ValueType { return Reg::Read<F_PSIZE>(); }
    static void WritePSIZE(ValueType value) noexcept { Reg::Write<F_PSIZE>(value); }
    static auto ReadMSIZE() noexcept -> ValueType { return Reg::Read<F_MSIZE>(); }
    static void WriteMSIZE(ValueType value) noexcept { Reg::Write<F_MSIZE>(value); }
    static auto ReadPL() noexcept -> ValueType { return Reg::Read<F_PL>(); }
    static void WritePL(ValueType value) noexcept { Reg::Write<F_PL>(value); }
    static auto ReadMEM2MEM() noexcept -> ValueType { return Reg::Read<F_MEM2MEM>(); }
    static void WriteMEM2MEM(ValueType value) noexcept { Reg::Write<F_MEM2MEM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002041c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EN = CortexM3::Field<ValueType, 0, 1>;
    using F_TCIE = CortexM3::Field<ValueType, 1, 1>;
    using F_HTIE = CortexM3::Field<ValueType, 2, 1>;
    using F_TEIE = CortexM3::Field<ValueType, 3, 1>;
    using F_DIR = CortexM3::Field<ValueType, 4, 1>;
    using F_CIRC = CortexM3::Field<ValueType, 5, 1>;
    using F_PINC = CortexM3::Field<ValueType, 6, 1>;
    using F_MINC = CortexM3::Field<ValueType, 7, 1>;
    using F_PSIZE = CortexM3::Field<ValueType, 8, 2>;
    using F_MSIZE = CortexM3::Field<ValueType, 10, 2>;
    using F_PL = CortexM3::Field<ValueType, 12, 2>;
    using F_MEM2MEM = CortexM3::Field<ValueType, 14, 1>;
};

class CNDTR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadNDT() noexcept -> ValueType { return Reg::Read<F_NDT>(); }
    static void WriteNDT(ValueType value) noexcept { Reg::Write<F_NDT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020420;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NDT = CortexM3::Field<ValueType, 0, 16>;
};

class CPAR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPA() noexcept -> ValueType { return Reg::Read<F_PA>(); }
    static void WritePA(ValueType value) noexcept { Reg::Write<F_PA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020424;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PA = CortexM3::Field<ValueType, 0, 32>;
};

class CMAR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMA() noexcept -> ValueType { return Reg::Read<F_MA>(); }
    static void WriteMA(ValueType value) noexcept { Reg::Write<F_MA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020428;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MA = CortexM3::Field<ValueType, 0, 32>;
};

class CCR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEN() noexcept -> ValueType { return Reg::Read<F_EN>(); }
    static void WriteEN(ValueType value) noexcept { Reg::Write<F_EN>(value); }
    static auto ReadTCIE() noexcept -> ValueType { return Reg::Read<F_TCIE>(); }
    static void WriteTCIE(ValueType value) noexcept { Reg::Write<F_TCIE>(value); }
    static auto ReadHTIE() noexcept -> ValueType { return Reg::Read<F_HTIE>(); }
    static void WriteHTIE(ValueType value) noexcept { Reg::Write<F_HTIE>(value); }
    static auto ReadTEIE() noexcept -> ValueType { return Reg::Read<F_TEIE>(); }
    static void WriteTEIE(ValueType value) noexcept { Reg::Write<F_TEIE>(value); }
    static auto ReadDIR() noexcept -> ValueType { return Reg::Read<F_DIR>(); }
    static void WriteDIR(ValueType value) noexcept { Reg::Write<F_DIR>(value); }
    static auto ReadCIRC() noexcept -> ValueType { return Reg::Read<F_CIRC>(); }
    static void WriteCIRC(ValueType value) noexcept { Reg::Write<F_CIRC>(value); }
    static auto ReadPINC() noexcept -> ValueType { return Reg::Read<F_PINC>(); }
    static void WritePINC(ValueType value) noexcept { Reg::Write<F_PINC>(value); }
    static auto ReadMINC() noexcept -> ValueType { return Reg::Read<F_MINC>(); }
    static void WriteMINC(ValueType value) noexcept { Reg::Write<F_MINC>(value); }
    static auto ReadPSIZE() noexcept -> ValueType { return Reg::Read<F_PSIZE>(); }
    static void WritePSIZE(ValueType value) noexcept { Reg::Write<F_PSIZE>(value); }
    static auto ReadMSIZE() noexcept -> ValueType { return Reg::Read<F_MSIZE>(); }
    static void WriteMSIZE(ValueType value) noexcept { Reg::Write<F_MSIZE>(value); }
    static auto ReadPL() noexcept -> ValueType { return Reg::Read<F_PL>(); }
    static void WritePL(ValueType value) noexcept { Reg::Write<F_PL>(value); }
    static auto ReadMEM2MEM() noexcept -> ValueType { return Reg::Read<F_MEM2MEM>(); }
    static void WriteMEM2MEM(ValueType value) noexcept { Reg::Write<F_MEM2MEM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020430;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EN = CortexM3::Field<ValueType, 0, 1>;
    using F_TCIE = CortexM3::Field<ValueType, 1, 1>;
    using F_HTIE = CortexM3::Field<ValueType, 2, 1>;
    using F_TEIE = CortexM3::Field<ValueType, 3, 1>;
    using F_DIR = CortexM3::Field<ValueType, 4, 1>;
    using F_CIRC = CortexM3::Field<ValueType, 5, 1>;
    using F_PINC = CortexM3::Field<ValueType, 6, 1>;
    using F_MINC = CortexM3::Field<ValueType, 7, 1>;
    using F_PSIZE = CortexM3::Field<ValueType, 8, 2>;
    using F_MSIZE = CortexM3::Field<ValueType, 10, 2>;
    using F_PL = CortexM3::Field<ValueType, 12, 2>;
    using F_MEM2MEM = CortexM3::Field<ValueType, 14, 1>;
};

class CNDTR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadNDT() noexcept -> ValueType { return Reg::Read<F_NDT>(); }
    static void WriteNDT(ValueType value) noexcept { Reg::Write<F_NDT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020434;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NDT = CortexM3::Field<ValueType, 0, 16>;
};

class CPAR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPA() noexcept -> ValueType { return Reg::Read<F_PA>(); }
    static void WritePA(ValueType value) noexcept { Reg::Write<F_PA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020438;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PA = CortexM3::Field<ValueType, 0, 32>;
};

class CMAR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMA() noexcept -> ValueType { return Reg::Read<F_MA>(); }
    static void WriteMA(ValueType value) noexcept { Reg::Write<F_MA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002043c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MA = CortexM3::Field<ValueType, 0, 32>;
};

class CCR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEN() noexcept -> ValueType { return Reg::Read<F_EN>(); }
    static void WriteEN(ValueType value) noexcept { Reg::Write<F_EN>(value); }
    static auto ReadTCIE() noexcept -> ValueType { return Reg::Read<F_TCIE>(); }
    static void WriteTCIE(ValueType value) noexcept { Reg::Write<F_TCIE>(value); }
    static auto ReadHTIE() noexcept -> ValueType { return Reg::Read<F_HTIE>(); }
    static void WriteHTIE(ValueType value) noexcept { Reg::Write<F_HTIE>(value); }
    static auto ReadTEIE() noexcept -> ValueType { return Reg::Read<F_TEIE>(); }
    static void WriteTEIE(ValueType value) noexcept { Reg::Write<F_TEIE>(value); }
    static auto ReadDIR() noexcept -> ValueType { return Reg::Read<F_DIR>(); }
    static void WriteDIR(ValueType value) noexcept { Reg::Write<F_DIR>(value); }
    static auto ReadCIRC() noexcept -> ValueType { return Reg::Read<F_CIRC>(); }
    static void WriteCIRC(ValueType value) noexcept { Reg::Write<F_CIRC>(value); }
    static auto ReadPINC() noexcept -> ValueType { return Reg::Read<F_PINC>(); }
    static void WritePINC(ValueType value) noexcept { Reg::Write<F_PINC>(value); }
    static auto ReadMINC() noexcept -> ValueType { return Reg::Read<F_MINC>(); }
    static void WriteMINC(ValueType value) noexcept { Reg::Write<F_MINC>(value); }
    static auto ReadPSIZE() noexcept -> ValueType { return Reg::Read<F_PSIZE>(); }
    static void WritePSIZE(ValueType value) noexcept { Reg::Write<F_PSIZE>(value); }
    static auto ReadMSIZE() noexcept -> ValueType { return Reg::Read<F_MSIZE>(); }
    static void WriteMSIZE(ValueType value) noexcept { Reg::Write<F_MSIZE>(value); }
    static auto ReadPL() noexcept -> ValueType { return Reg::Read<F_PL>(); }
    static void WritePL(ValueType value) noexcept { Reg::Write<F_PL>(value); }
    static auto ReadMEM2MEM() noexcept -> ValueType { return Reg::Read<F_MEM2MEM>(); }
    static void WriteMEM2MEM(ValueType value) noexcept { Reg::Write<F_MEM2MEM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020444;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EN = CortexM3::Field<ValueType, 0, 1>;
    using F_TCIE = CortexM3::Field<ValueType, 1, 1>;
    using F_HTIE = CortexM3::Field<ValueType, 2, 1>;
    using F_TEIE = CortexM3::Field<ValueType, 3, 1>;
    using F_DIR = CortexM3::Field<ValueType, 4, 1>;
    using F_CIRC = CortexM3::Field<ValueType, 5, 1>;
    using F_PINC = CortexM3::Field<ValueType, 6, 1>;
    using F_MINC = CortexM3::Field<ValueType, 7, 1>;
    using F_PSIZE = CortexM3::Field<ValueType, 8, 2>;
    using F_MSIZE = CortexM3::Field<ValueType, 10, 2>;
    using F_PL = CortexM3::Field<ValueType, 12, 2>;
    using F_MEM2MEM = CortexM3::Field<ValueType, 14, 1>;
};

class CNDTR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadNDT() noexcept -> ValueType { return Reg::Read<F_NDT>(); }
    static void WriteNDT(ValueType value) noexcept { Reg::Write<F_NDT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020448;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NDT = CortexM3::Field<ValueType, 0, 16>;
};

class CPAR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPA() noexcept -> ValueType { return Reg::Read<F_PA>(); }
    static void WritePA(ValueType value) noexcept { Reg::Write<F_PA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002044c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PA = CortexM3::Field<ValueType, 0, 32>;
};

class CMAR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMA() noexcept -> ValueType { return Reg::Read<F_MA>(); }
    static void WriteMA(ValueType value) noexcept { Reg::Write<F_MA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020450;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MA = CortexM3::Field<ValueType, 0, 32>;
};

class CCR5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEN() noexcept -> ValueType { return Reg::Read<F_EN>(); }
    static void WriteEN(ValueType value) noexcept { Reg::Write<F_EN>(value); }
    static auto ReadTCIE() noexcept -> ValueType { return Reg::Read<F_TCIE>(); }
    static void WriteTCIE(ValueType value) noexcept { Reg::Write<F_TCIE>(value); }
    static auto ReadHTIE() noexcept -> ValueType { return Reg::Read<F_HTIE>(); }
    static void WriteHTIE(ValueType value) noexcept { Reg::Write<F_HTIE>(value); }
    static auto ReadTEIE() noexcept -> ValueType { return Reg::Read<F_TEIE>(); }
    static void WriteTEIE(ValueType value) noexcept { Reg::Write<F_TEIE>(value); }
    static auto ReadDIR() noexcept -> ValueType { return Reg::Read<F_DIR>(); }
    static void WriteDIR(ValueType value) noexcept { Reg::Write<F_DIR>(value); }
    static auto ReadCIRC() noexcept -> ValueType { return Reg::Read<F_CIRC>(); }
    static void WriteCIRC(ValueType value) noexcept { Reg::Write<F_CIRC>(value); }
    static auto ReadPINC() noexcept -> ValueType { return Reg::Read<F_PINC>(); }
    static void WritePINC(ValueType value) noexcept { Reg::Write<F_PINC>(value); }
    static auto ReadMINC() noexcept -> ValueType { return Reg::Read<F_MINC>(); }
    static void WriteMINC(ValueType value) noexcept { Reg::Write<F_MINC>(value); }
    static auto ReadPSIZE() noexcept -> ValueType { return Reg::Read<F_PSIZE>(); }
    static void WritePSIZE(ValueType value) noexcept { Reg::Write<F_PSIZE>(value); }
    static auto ReadMSIZE() noexcept -> ValueType { return Reg::Read<F_MSIZE>(); }
    static void WriteMSIZE(ValueType value) noexcept { Reg::Write<F_MSIZE>(value); }
    static auto ReadPL() noexcept -> ValueType { return Reg::Read<F_PL>(); }
    static void WritePL(ValueType value) noexcept { Reg::Write<F_PL>(value); }
    static auto ReadMEM2MEM() noexcept -> ValueType { return Reg::Read<F_MEM2MEM>(); }
    static void WriteMEM2MEM(ValueType value) noexcept { Reg::Write<F_MEM2MEM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020458;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EN = CortexM3::Field<ValueType, 0, 1>;
    using F_TCIE = CortexM3::Field<ValueType, 1, 1>;
    using F_HTIE = CortexM3::Field<ValueType, 2, 1>;
    using F_TEIE = CortexM3::Field<ValueType, 3, 1>;
    using F_DIR = CortexM3::Field<ValueType, 4, 1>;
    using F_CIRC = CortexM3::Field<ValueType, 5, 1>;
    using F_PINC = CortexM3::Field<ValueType, 6, 1>;
    using F_MINC = CortexM3::Field<ValueType, 7, 1>;
    using F_PSIZE = CortexM3::Field<ValueType, 8, 2>;
    using F_MSIZE = CortexM3::Field<ValueType, 10, 2>;
    using F_PL = CortexM3::Field<ValueType, 12, 2>;
    using F_MEM2MEM = CortexM3::Field<ValueType, 14, 1>;
};

class CNDTR5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadNDT() noexcept -> ValueType { return Reg::Read<F_NDT>(); }
    static void WriteNDT(ValueType value) noexcept { Reg::Write<F_NDT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002045c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NDT = CortexM3::Field<ValueType, 0, 16>;
};

class CPAR5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPA() noexcept -> ValueType { return Reg::Read<F_PA>(); }
    static void WritePA(ValueType value) noexcept { Reg::Write<F_PA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020460;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PA = CortexM3::Field<ValueType, 0, 32>;
};

class CMAR5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMA() noexcept -> ValueType { return Reg::Read<F_MA>(); }
    static void WriteMA(ValueType value) noexcept { Reg::Write<F_MA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020464;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MA = CortexM3::Field<ValueType, 0, 32>;
};

class CCR6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEN() noexcept -> ValueType { return Reg::Read<F_EN>(); }
    static void WriteEN(ValueType value) noexcept { Reg::Write<F_EN>(value); }
    static auto ReadTCIE() noexcept -> ValueType { return Reg::Read<F_TCIE>(); }
    static void WriteTCIE(ValueType value) noexcept { Reg::Write<F_TCIE>(value); }
    static auto ReadHTIE() noexcept -> ValueType { return Reg::Read<F_HTIE>(); }
    static void WriteHTIE(ValueType value) noexcept { Reg::Write<F_HTIE>(value); }
    static auto ReadTEIE() noexcept -> ValueType { return Reg::Read<F_TEIE>(); }
    static void WriteTEIE(ValueType value) noexcept { Reg::Write<F_TEIE>(value); }
    static auto ReadDIR() noexcept -> ValueType { return Reg::Read<F_DIR>(); }
    static void WriteDIR(ValueType value) noexcept { Reg::Write<F_DIR>(value); }
    static auto ReadCIRC() noexcept -> ValueType { return Reg::Read<F_CIRC>(); }
    static void WriteCIRC(ValueType value) noexcept { Reg::Write<F_CIRC>(value); }
    static auto ReadPINC() noexcept -> ValueType { return Reg::Read<F_PINC>(); }
    static void WritePINC(ValueType value) noexcept { Reg::Write<F_PINC>(value); }
    static auto ReadMINC() noexcept -> ValueType { return Reg::Read<F_MINC>(); }
    static void WriteMINC(ValueType value) noexcept { Reg::Write<F_MINC>(value); }
    static auto ReadPSIZE() noexcept -> ValueType { return Reg::Read<F_PSIZE>(); }
    static void WritePSIZE(ValueType value) noexcept { Reg::Write<F_PSIZE>(value); }
    static auto ReadMSIZE() noexcept -> ValueType { return Reg::Read<F_MSIZE>(); }
    static void WriteMSIZE(ValueType value) noexcept { Reg::Write<F_MSIZE>(value); }
    static auto ReadPL() noexcept -> ValueType { return Reg::Read<F_PL>(); }
    static void WritePL(ValueType value) noexcept { Reg::Write<F_PL>(value); }
    static auto ReadMEM2MEM() noexcept -> ValueType { return Reg::Read<F_MEM2MEM>(); }
    static void WriteMEM2MEM(ValueType value) noexcept { Reg::Write<F_MEM2MEM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002046c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EN = CortexM3::Field<ValueType, 0, 1>;
    using F_TCIE = CortexM3::Field<ValueType, 1, 1>;
    using F_HTIE = CortexM3::Field<ValueType, 2, 1>;
    using F_TEIE = CortexM3::Field<ValueType, 3, 1>;
    using F_DIR = CortexM3::Field<ValueType, 4, 1>;
    using F_CIRC = CortexM3::Field<ValueType, 5, 1>;
    using F_PINC = CortexM3::Field<ValueType, 6, 1>;
    using F_MINC = CortexM3::Field<ValueType, 7, 1>;
    using F_PSIZE = CortexM3::Field<ValueType, 8, 2>;
    using F_MSIZE = CortexM3::Field<ValueType, 10, 2>;
    using F_PL = CortexM3::Field<ValueType, 12, 2>;
    using F_MEM2MEM = CortexM3::Field<ValueType, 14, 1>;
};

class CNDTR6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadNDT() noexcept -> ValueType { return Reg::Read<F_NDT>(); }
    static void WriteNDT(ValueType value) noexcept { Reg::Write<F_NDT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020470;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NDT = CortexM3::Field<ValueType, 0, 16>;
};

class CPAR6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPA() noexcept -> ValueType { return Reg::Read<F_PA>(); }
    static void WritePA(ValueType value) noexcept { Reg::Write<F_PA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020474;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PA = CortexM3::Field<ValueType, 0, 32>;
};

class CMAR6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMA() noexcept -> ValueType { return Reg::Read<F_MA>(); }
    static void WriteMA(ValueType value) noexcept { Reg::Write<F_MA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020478;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MA = CortexM3::Field<ValueType, 0, 32>;
};

class CCR7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEN() noexcept -> ValueType { return Reg::Read<F_EN>(); }
    static void WriteEN(ValueType value) noexcept { Reg::Write<F_EN>(value); }
    static auto ReadTCIE() noexcept -> ValueType { return Reg::Read<F_TCIE>(); }
    static void WriteTCIE(ValueType value) noexcept { Reg::Write<F_TCIE>(value); }
    static auto ReadHTIE() noexcept -> ValueType { return Reg::Read<F_HTIE>(); }
    static void WriteHTIE(ValueType value) noexcept { Reg::Write<F_HTIE>(value); }
    static auto ReadTEIE() noexcept -> ValueType { return Reg::Read<F_TEIE>(); }
    static void WriteTEIE(ValueType value) noexcept { Reg::Write<F_TEIE>(value); }
    static auto ReadDIR() noexcept -> ValueType { return Reg::Read<F_DIR>(); }
    static void WriteDIR(ValueType value) noexcept { Reg::Write<F_DIR>(value); }
    static auto ReadCIRC() noexcept -> ValueType { return Reg::Read<F_CIRC>(); }
    static void WriteCIRC(ValueType value) noexcept { Reg::Write<F_CIRC>(value); }
    static auto ReadPINC() noexcept -> ValueType { return Reg::Read<F_PINC>(); }
    static void WritePINC(ValueType value) noexcept { Reg::Write<F_PINC>(value); }
    static auto ReadMINC() noexcept -> ValueType { return Reg::Read<F_MINC>(); }
    static void WriteMINC(ValueType value) noexcept { Reg::Write<F_MINC>(value); }
    static auto ReadPSIZE() noexcept -> ValueType { return Reg::Read<F_PSIZE>(); }
    static void WritePSIZE(ValueType value) noexcept { Reg::Write<F_PSIZE>(value); }
    static auto ReadMSIZE() noexcept -> ValueType { return Reg::Read<F_MSIZE>(); }
    static void WriteMSIZE(ValueType value) noexcept { Reg::Write<F_MSIZE>(value); }
    static auto ReadPL() noexcept -> ValueType { return Reg::Read<F_PL>(); }
    static void WritePL(ValueType value) noexcept { Reg::Write<F_PL>(value); }
    static auto ReadMEM2MEM() noexcept -> ValueType { return Reg::Read<F_MEM2MEM>(); }
    static void WriteMEM2MEM(ValueType value) noexcept { Reg::Write<F_MEM2MEM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020480;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EN = CortexM3::Field<ValueType, 0, 1>;
    using F_TCIE = CortexM3::Field<ValueType, 1, 1>;
    using F_HTIE = CortexM3::Field<ValueType, 2, 1>;
    using F_TEIE = CortexM3::Field<ValueType, 3, 1>;
    using F_DIR = CortexM3::Field<ValueType, 4, 1>;
    using F_CIRC = CortexM3::Field<ValueType, 5, 1>;
    using F_PINC = CortexM3::Field<ValueType, 6, 1>;
    using F_MINC = CortexM3::Field<ValueType, 7, 1>;
    using F_PSIZE = CortexM3::Field<ValueType, 8, 2>;
    using F_MSIZE = CortexM3::Field<ValueType, 10, 2>;
    using F_PL = CortexM3::Field<ValueType, 12, 2>;
    using F_MEM2MEM = CortexM3::Field<ValueType, 14, 1>;
};

class CNDTR7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadNDT() noexcept -> ValueType { return Reg::Read<F_NDT>(); }
    static void WriteNDT(ValueType value) noexcept { Reg::Write<F_NDT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020484;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NDT = CortexM3::Field<ValueType, 0, 16>;
};

class CPAR7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPA() noexcept -> ValueType { return Reg::Read<F_PA>(); }
    static void WritePA(ValueType value) noexcept { Reg::Write<F_PA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40020488;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PA = CortexM3::Field<ValueType, 0, 32>;
};

class CMAR7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMA() noexcept -> ValueType { return Reg::Read<F_MA>(); }
    static void WriteMA(ValueType value) noexcept { Reg::Write<F_MA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002048c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MA = CortexM3::Field<ValueType, 0, 32>;
};

} // namespace STM32F103::DMA2
