#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::FLASH {

class ACR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000030;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadLATENCY() noexcept -> ValueType { return Reg::Read<F_LATENCY>(); }
    static void WriteLATENCY(ValueType value) noexcept { Reg::Write<F_LATENCY>(value); }
    static auto ReadHLFCYA() noexcept -> ValueType { return Reg::Read<F_HLFCYA>(); }
    static void WriteHLFCYA(ValueType value) noexcept { Reg::Write<F_HLFCYA>(value); }
    static auto ReadPRFTBE() noexcept -> ValueType { return Reg::Read<F_PRFTBE>(); }
    static void WritePRFTBE(ValueType value) noexcept { Reg::Write<F_PRFTBE>(value); }
    static auto ReadPRFTBS() noexcept -> ValueType { return Reg::Read<F_PRFTBS>(); }

private:
    static constexpr std::uintptr_t Address = 0x40022000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_LATENCY = CortexM3::Field<ValueType, 0, 3>;
    using F_HLFCYA = CortexM3::Field<ValueType, 3, 1>;
    using F_PRFTBE = CortexM3::Field<ValueType, 4, 1>;
    using F_PRFTBS = CortexM3::Field<ValueType, 5, 1>;
};

class KEYR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteKEY(ValueType value) noexcept { Reg::Write<F_KEY>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40022004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_KEY = CortexM3::Field<ValueType, 0, 32>;
};

class OPTKEYR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteOPTKEY(ValueType value) noexcept { Reg::Write<F_OPTKEY>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40022008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_OPTKEY = CortexM3::Field<ValueType, 0, 32>;
};

class SR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEOP() noexcept -> ValueType { return Reg::Read<F_EOP>(); }
    static void WriteEOP(ValueType value) noexcept { Reg::Write<F_EOP>(value); }
    static auto ReadWRPRTERR() noexcept -> ValueType { return Reg::Read<F_WRPRTERR>(); }
    static void WriteWRPRTERR(ValueType value) noexcept { Reg::Write<F_WRPRTERR>(value); }
    static auto ReadPGERR() noexcept -> ValueType { return Reg::Read<F_PGERR>(); }
    static void WritePGERR(ValueType value) noexcept { Reg::Write<F_PGERR>(value); }
    static auto ReadBSY() noexcept -> ValueType { return Reg::Read<F_BSY>(); }

private:
    static constexpr std::uintptr_t Address = 0x4002200c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EOP = CortexM3::Field<ValueType, 5, 1>;
    using F_WRPRTERR = CortexM3::Field<ValueType, 4, 1>;
    using F_PGERR = CortexM3::Field<ValueType, 2, 1>;
    using F_BSY = CortexM3::Field<ValueType, 0, 1>;
};

class CR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000080;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPG() noexcept -> ValueType { return Reg::Read<F_PG>(); }
    static void WritePG(ValueType value) noexcept { Reg::Write<F_PG>(value); }
    static auto ReadPER() noexcept -> ValueType { return Reg::Read<F_PER>(); }
    static void WritePER(ValueType value) noexcept { Reg::Write<F_PER>(value); }
    static auto ReadMER() noexcept -> ValueType { return Reg::Read<F_MER>(); }
    static void WriteMER(ValueType value) noexcept { Reg::Write<F_MER>(value); }
    static auto ReadOPTPG() noexcept -> ValueType { return Reg::Read<F_OPTPG>(); }
    static void WriteOPTPG(ValueType value) noexcept { Reg::Write<F_OPTPG>(value); }
    static auto ReadOPTER() noexcept -> ValueType { return Reg::Read<F_OPTER>(); }
    static void WriteOPTER(ValueType value) noexcept { Reg::Write<F_OPTER>(value); }
    static auto ReadSTRT() noexcept -> ValueType { return Reg::Read<F_STRT>(); }
    static void WriteSTRT(ValueType value) noexcept { Reg::Write<F_STRT>(value); }
    static auto ReadLOCK() noexcept -> ValueType { return Reg::Read<F_LOCK>(); }
    static void WriteLOCK(ValueType value) noexcept { Reg::Write<F_LOCK>(value); }
    static auto ReadOPTWRE() noexcept -> ValueType { return Reg::Read<F_OPTWRE>(); }
    static void WriteOPTWRE(ValueType value) noexcept { Reg::Write<F_OPTWRE>(value); }
    static auto ReadERRIE() noexcept -> ValueType { return Reg::Read<F_ERRIE>(); }
    static void WriteERRIE(ValueType value) noexcept { Reg::Write<F_ERRIE>(value); }
    static auto ReadEOPIE() noexcept -> ValueType { return Reg::Read<F_EOPIE>(); }
    static void WriteEOPIE(ValueType value) noexcept { Reg::Write<F_EOPIE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40022010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PG = CortexM3::Field<ValueType, 0, 1>;
    using F_PER = CortexM3::Field<ValueType, 1, 1>;
    using F_MER = CortexM3::Field<ValueType, 2, 1>;
    using F_OPTPG = CortexM3::Field<ValueType, 4, 1>;
    using F_OPTER = CortexM3::Field<ValueType, 5, 1>;
    using F_STRT = CortexM3::Field<ValueType, 6, 1>;
    using F_LOCK = CortexM3::Field<ValueType, 7, 1>;
    using F_OPTWRE = CortexM3::Field<ValueType, 9, 1>;
    using F_ERRIE = CortexM3::Field<ValueType, 10, 1>;
    using F_EOPIE = CortexM3::Field<ValueType, 12, 1>;
};

class AR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteFAR(ValueType value) noexcept { Reg::Write<F_FAR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40022014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FAR = CortexM3::Field<ValueType, 0, 32>;
};

class OBR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x03FFFFFC;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadOPTERR() noexcept -> ValueType { return Reg::Read<F_OPTERR>(); }
    static auto ReadRDPRT() noexcept -> ValueType { return Reg::Read<F_RDPRT>(); }
    static auto ReadWDG_SW() noexcept -> ValueType { return Reg::Read<F_WDG_SW>(); }
    static auto ReadnRST_STOP() noexcept -> ValueType { return Reg::Read<F_nRST_STOP>(); }
    static auto ReadnRST_STDBY() noexcept -> ValueType { return Reg::Read<F_nRST_STDBY>(); }
    static auto ReadData0() noexcept -> ValueType { return Reg::Read<F_Data0>(); }
    static auto ReadData1() noexcept -> ValueType { return Reg::Read<F_Data1>(); }

private:
    static constexpr std::uintptr_t Address = 0x4002201c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_OPTERR = CortexM3::Field<ValueType, 0, 1>;
    using F_RDPRT = CortexM3::Field<ValueType, 1, 1>;
    using F_WDG_SW = CortexM3::Field<ValueType, 2, 1>;
    using F_nRST_STOP = CortexM3::Field<ValueType, 3, 1>;
    using F_nRST_STDBY = CortexM3::Field<ValueType, 4, 1>;
    using F_Data0 = CortexM3::Field<ValueType, 10, 8>;
    using F_Data1 = CortexM3::Field<ValueType, 18, 8>;
};

class WRPR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFFFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadWRP() noexcept -> ValueType { return Reg::Read<F_WRP>(); }

private:
    static constexpr std::uintptr_t Address = 0x40022020;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_WRP = CortexM3::Field<ValueType, 0, 32>;
};

} // namespace STM32F103::FLASH
