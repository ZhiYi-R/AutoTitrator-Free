#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::FSMC {

class BCR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x000030D0;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCBURSTRW() noexcept -> ValueType { return Reg::Read<F_CBURSTRW>(); }
    static void WriteCBURSTRW(ValueType value) noexcept { Reg::Write<F_CBURSTRW>(value); }
    static auto ReadASYNCWAIT() noexcept -> ValueType { return Reg::Read<F_ASYNCWAIT>(); }
    static void WriteASYNCWAIT(ValueType value) noexcept { Reg::Write<F_ASYNCWAIT>(value); }
    static auto ReadEXTMOD() noexcept -> ValueType { return Reg::Read<F_EXTMOD>(); }
    static void WriteEXTMOD(ValueType value) noexcept { Reg::Write<F_EXTMOD>(value); }
    static auto ReadWAITEN() noexcept -> ValueType { return Reg::Read<F_WAITEN>(); }
    static void WriteWAITEN(ValueType value) noexcept { Reg::Write<F_WAITEN>(value); }
    static auto ReadWREN() noexcept -> ValueType { return Reg::Read<F_WREN>(); }
    static void WriteWREN(ValueType value) noexcept { Reg::Write<F_WREN>(value); }
    static auto ReadWAITCFG() noexcept -> ValueType { return Reg::Read<F_WAITCFG>(); }
    static void WriteWAITCFG(ValueType value) noexcept { Reg::Write<F_WAITCFG>(value); }
    static auto ReadWAITPOL() noexcept -> ValueType { return Reg::Read<F_WAITPOL>(); }
    static void WriteWAITPOL(ValueType value) noexcept { Reg::Write<F_WAITPOL>(value); }
    static auto ReadBURSTEN() noexcept -> ValueType { return Reg::Read<F_BURSTEN>(); }
    static void WriteBURSTEN(ValueType value) noexcept { Reg::Write<F_BURSTEN>(value); }
    static auto ReadFACCEN() noexcept -> ValueType { return Reg::Read<F_FACCEN>(); }
    static void WriteFACCEN(ValueType value) noexcept { Reg::Write<F_FACCEN>(value); }
    static auto ReadMWID() noexcept -> ValueType { return Reg::Read<F_MWID>(); }
    static void WriteMWID(ValueType value) noexcept { Reg::Write<F_MWID>(value); }
    static auto ReadMTYP() noexcept -> ValueType { return Reg::Read<F_MTYP>(); }
    static void WriteMTYP(ValueType value) noexcept { Reg::Write<F_MTYP>(value); }
    static auto ReadMUXEN() noexcept -> ValueType { return Reg::Read<F_MUXEN>(); }
    static void WriteMUXEN(ValueType value) noexcept { Reg::Write<F_MUXEN>(value); }
    static auto ReadMBKEN() noexcept -> ValueType { return Reg::Read<F_MBKEN>(); }
    static void WriteMBKEN(ValueType value) noexcept { Reg::Write<F_MBKEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CBURSTRW = CortexM3::Field<ValueType, 19, 1>;
    using F_ASYNCWAIT = CortexM3::Field<ValueType, 15, 1>;
    using F_EXTMOD = CortexM3::Field<ValueType, 14, 1>;
    using F_WAITEN = CortexM3::Field<ValueType, 13, 1>;
    using F_WREN = CortexM3::Field<ValueType, 12, 1>;
    using F_WAITCFG = CortexM3::Field<ValueType, 11, 1>;
    using F_WAITPOL = CortexM3::Field<ValueType, 9, 1>;
    using F_BURSTEN = CortexM3::Field<ValueType, 8, 1>;
    using F_FACCEN = CortexM3::Field<ValueType, 6, 1>;
    using F_MWID = CortexM3::Field<ValueType, 4, 2>;
    using F_MTYP = CortexM3::Field<ValueType, 2, 2>;
    using F_MUXEN = CortexM3::Field<ValueType, 1, 1>;
    using F_MBKEN = CortexM3::Field<ValueType, 0, 1>;
};

class BTR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFFFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACCMOD() noexcept -> ValueType { return Reg::Read<F_ACCMOD>(); }
    static void WriteACCMOD(ValueType value) noexcept { Reg::Write<F_ACCMOD>(value); }
    static auto ReadDATLAT() noexcept -> ValueType { return Reg::Read<F_DATLAT>(); }
    static void WriteDATLAT(ValueType value) noexcept { Reg::Write<F_DATLAT>(value); }
    static auto ReadCLKDIV() noexcept -> ValueType { return Reg::Read<F_CLKDIV>(); }
    static void WriteCLKDIV(ValueType value) noexcept { Reg::Write<F_CLKDIV>(value); }
    static auto ReadBUSTURN() noexcept -> ValueType { return Reg::Read<F_BUSTURN>(); }
    static void WriteBUSTURN(ValueType value) noexcept { Reg::Write<F_BUSTURN>(value); }
    static auto ReadDATAST() noexcept -> ValueType { return Reg::Read<F_DATAST>(); }
    static void WriteDATAST(ValueType value) noexcept { Reg::Write<F_DATAST>(value); }
    static auto ReadADDHLD() noexcept -> ValueType { return Reg::Read<F_ADDHLD>(); }
    static void WriteADDHLD(ValueType value) noexcept { Reg::Write<F_ADDHLD>(value); }
    static auto ReadADDSET() noexcept -> ValueType { return Reg::Read<F_ADDSET>(); }
    static void WriteADDSET(ValueType value) noexcept { Reg::Write<F_ADDSET>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACCMOD = CortexM3::Field<ValueType, 28, 2>;
    using F_DATLAT = CortexM3::Field<ValueType, 24, 4>;
    using F_CLKDIV = CortexM3::Field<ValueType, 20, 4>;
    using F_BUSTURN = CortexM3::Field<ValueType, 16, 4>;
    using F_DATAST = CortexM3::Field<ValueType, 8, 8>;
    using F_ADDHLD = CortexM3::Field<ValueType, 4, 4>;
    using F_ADDSET = CortexM3::Field<ValueType, 0, 4>;
};

class BCR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x000030D0;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCBURSTRW() noexcept -> ValueType { return Reg::Read<F_CBURSTRW>(); }
    static void WriteCBURSTRW(ValueType value) noexcept { Reg::Write<F_CBURSTRW>(value); }
    static auto ReadASYNCWAIT() noexcept -> ValueType { return Reg::Read<F_ASYNCWAIT>(); }
    static void WriteASYNCWAIT(ValueType value) noexcept { Reg::Write<F_ASYNCWAIT>(value); }
    static auto ReadEXTMOD() noexcept -> ValueType { return Reg::Read<F_EXTMOD>(); }
    static void WriteEXTMOD(ValueType value) noexcept { Reg::Write<F_EXTMOD>(value); }
    static auto ReadWAITEN() noexcept -> ValueType { return Reg::Read<F_WAITEN>(); }
    static void WriteWAITEN(ValueType value) noexcept { Reg::Write<F_WAITEN>(value); }
    static auto ReadWREN() noexcept -> ValueType { return Reg::Read<F_WREN>(); }
    static void WriteWREN(ValueType value) noexcept { Reg::Write<F_WREN>(value); }
    static auto ReadWAITCFG() noexcept -> ValueType { return Reg::Read<F_WAITCFG>(); }
    static void WriteWAITCFG(ValueType value) noexcept { Reg::Write<F_WAITCFG>(value); }
    static auto ReadWRAPMOD() noexcept -> ValueType { return Reg::Read<F_WRAPMOD>(); }
    static void WriteWRAPMOD(ValueType value) noexcept { Reg::Write<F_WRAPMOD>(value); }
    static auto ReadWAITPOL() noexcept -> ValueType { return Reg::Read<F_WAITPOL>(); }
    static void WriteWAITPOL(ValueType value) noexcept { Reg::Write<F_WAITPOL>(value); }
    static auto ReadBURSTEN() noexcept -> ValueType { return Reg::Read<F_BURSTEN>(); }
    static void WriteBURSTEN(ValueType value) noexcept { Reg::Write<F_BURSTEN>(value); }
    static auto ReadFACCEN() noexcept -> ValueType { return Reg::Read<F_FACCEN>(); }
    static void WriteFACCEN(ValueType value) noexcept { Reg::Write<F_FACCEN>(value); }
    static auto ReadMWID() noexcept -> ValueType { return Reg::Read<F_MWID>(); }
    static void WriteMWID(ValueType value) noexcept { Reg::Write<F_MWID>(value); }
    static auto ReadMTYP() noexcept -> ValueType { return Reg::Read<F_MTYP>(); }
    static void WriteMTYP(ValueType value) noexcept { Reg::Write<F_MTYP>(value); }
    static auto ReadMUXEN() noexcept -> ValueType { return Reg::Read<F_MUXEN>(); }
    static void WriteMUXEN(ValueType value) noexcept { Reg::Write<F_MUXEN>(value); }
    static auto ReadMBKEN() noexcept -> ValueType { return Reg::Read<F_MBKEN>(); }
    static void WriteMBKEN(ValueType value) noexcept { Reg::Write<F_MBKEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CBURSTRW = CortexM3::Field<ValueType, 19, 1>;
    using F_ASYNCWAIT = CortexM3::Field<ValueType, 15, 1>;
    using F_EXTMOD = CortexM3::Field<ValueType, 14, 1>;
    using F_WAITEN = CortexM3::Field<ValueType, 13, 1>;
    using F_WREN = CortexM3::Field<ValueType, 12, 1>;
    using F_WAITCFG = CortexM3::Field<ValueType, 11, 1>;
    using F_WRAPMOD = CortexM3::Field<ValueType, 10, 1>;
    using F_WAITPOL = CortexM3::Field<ValueType, 9, 1>;
    using F_BURSTEN = CortexM3::Field<ValueType, 8, 1>;
    using F_FACCEN = CortexM3::Field<ValueType, 6, 1>;
    using F_MWID = CortexM3::Field<ValueType, 4, 2>;
    using F_MTYP = CortexM3::Field<ValueType, 2, 2>;
    using F_MUXEN = CortexM3::Field<ValueType, 1, 1>;
    using F_MBKEN = CortexM3::Field<ValueType, 0, 1>;
};

class BTR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFFFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACCMOD() noexcept -> ValueType { return Reg::Read<F_ACCMOD>(); }
    static void WriteACCMOD(ValueType value) noexcept { Reg::Write<F_ACCMOD>(value); }
    static auto ReadDATLAT() noexcept -> ValueType { return Reg::Read<F_DATLAT>(); }
    static void WriteDATLAT(ValueType value) noexcept { Reg::Write<F_DATLAT>(value); }
    static auto ReadCLKDIV() noexcept -> ValueType { return Reg::Read<F_CLKDIV>(); }
    static void WriteCLKDIV(ValueType value) noexcept { Reg::Write<F_CLKDIV>(value); }
    static auto ReadBUSTURN() noexcept -> ValueType { return Reg::Read<F_BUSTURN>(); }
    static void WriteBUSTURN(ValueType value) noexcept { Reg::Write<F_BUSTURN>(value); }
    static auto ReadDATAST() noexcept -> ValueType { return Reg::Read<F_DATAST>(); }
    static void WriteDATAST(ValueType value) noexcept { Reg::Write<F_DATAST>(value); }
    static auto ReadADDHLD() noexcept -> ValueType { return Reg::Read<F_ADDHLD>(); }
    static void WriteADDHLD(ValueType value) noexcept { Reg::Write<F_ADDHLD>(value); }
    static auto ReadADDSET() noexcept -> ValueType { return Reg::Read<F_ADDSET>(); }
    static void WriteADDSET(ValueType value) noexcept { Reg::Write<F_ADDSET>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa000000c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACCMOD = CortexM3::Field<ValueType, 28, 2>;
    using F_DATLAT = CortexM3::Field<ValueType, 24, 4>;
    using F_CLKDIV = CortexM3::Field<ValueType, 20, 4>;
    using F_BUSTURN = CortexM3::Field<ValueType, 16, 4>;
    using F_DATAST = CortexM3::Field<ValueType, 8, 8>;
    using F_ADDHLD = CortexM3::Field<ValueType, 4, 4>;
    using F_ADDSET = CortexM3::Field<ValueType, 0, 4>;
};

class BCR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x000030D0;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCBURSTRW() noexcept -> ValueType { return Reg::Read<F_CBURSTRW>(); }
    static void WriteCBURSTRW(ValueType value) noexcept { Reg::Write<F_CBURSTRW>(value); }
    static auto ReadASYNCWAIT() noexcept -> ValueType { return Reg::Read<F_ASYNCWAIT>(); }
    static void WriteASYNCWAIT(ValueType value) noexcept { Reg::Write<F_ASYNCWAIT>(value); }
    static auto ReadEXTMOD() noexcept -> ValueType { return Reg::Read<F_EXTMOD>(); }
    static void WriteEXTMOD(ValueType value) noexcept { Reg::Write<F_EXTMOD>(value); }
    static auto ReadWAITEN() noexcept -> ValueType { return Reg::Read<F_WAITEN>(); }
    static void WriteWAITEN(ValueType value) noexcept { Reg::Write<F_WAITEN>(value); }
    static auto ReadWREN() noexcept -> ValueType { return Reg::Read<F_WREN>(); }
    static void WriteWREN(ValueType value) noexcept { Reg::Write<F_WREN>(value); }
    static auto ReadWAITCFG() noexcept -> ValueType { return Reg::Read<F_WAITCFG>(); }
    static void WriteWAITCFG(ValueType value) noexcept { Reg::Write<F_WAITCFG>(value); }
    static auto ReadWRAPMOD() noexcept -> ValueType { return Reg::Read<F_WRAPMOD>(); }
    static void WriteWRAPMOD(ValueType value) noexcept { Reg::Write<F_WRAPMOD>(value); }
    static auto ReadWAITPOL() noexcept -> ValueType { return Reg::Read<F_WAITPOL>(); }
    static void WriteWAITPOL(ValueType value) noexcept { Reg::Write<F_WAITPOL>(value); }
    static auto ReadBURSTEN() noexcept -> ValueType { return Reg::Read<F_BURSTEN>(); }
    static void WriteBURSTEN(ValueType value) noexcept { Reg::Write<F_BURSTEN>(value); }
    static auto ReadFACCEN() noexcept -> ValueType { return Reg::Read<F_FACCEN>(); }
    static void WriteFACCEN(ValueType value) noexcept { Reg::Write<F_FACCEN>(value); }
    static auto ReadMWID() noexcept -> ValueType { return Reg::Read<F_MWID>(); }
    static void WriteMWID(ValueType value) noexcept { Reg::Write<F_MWID>(value); }
    static auto ReadMTYP() noexcept -> ValueType { return Reg::Read<F_MTYP>(); }
    static void WriteMTYP(ValueType value) noexcept { Reg::Write<F_MTYP>(value); }
    static auto ReadMUXEN() noexcept -> ValueType { return Reg::Read<F_MUXEN>(); }
    static void WriteMUXEN(ValueType value) noexcept { Reg::Write<F_MUXEN>(value); }
    static auto ReadMBKEN() noexcept -> ValueType { return Reg::Read<F_MBKEN>(); }
    static void WriteMBKEN(ValueType value) noexcept { Reg::Write<F_MBKEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CBURSTRW = CortexM3::Field<ValueType, 19, 1>;
    using F_ASYNCWAIT = CortexM3::Field<ValueType, 15, 1>;
    using F_EXTMOD = CortexM3::Field<ValueType, 14, 1>;
    using F_WAITEN = CortexM3::Field<ValueType, 13, 1>;
    using F_WREN = CortexM3::Field<ValueType, 12, 1>;
    using F_WAITCFG = CortexM3::Field<ValueType, 11, 1>;
    using F_WRAPMOD = CortexM3::Field<ValueType, 10, 1>;
    using F_WAITPOL = CortexM3::Field<ValueType, 9, 1>;
    using F_BURSTEN = CortexM3::Field<ValueType, 8, 1>;
    using F_FACCEN = CortexM3::Field<ValueType, 6, 1>;
    using F_MWID = CortexM3::Field<ValueType, 4, 2>;
    using F_MTYP = CortexM3::Field<ValueType, 2, 2>;
    using F_MUXEN = CortexM3::Field<ValueType, 1, 1>;
    using F_MBKEN = CortexM3::Field<ValueType, 0, 1>;
};

class BTR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFFFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACCMOD() noexcept -> ValueType { return Reg::Read<F_ACCMOD>(); }
    static void WriteACCMOD(ValueType value) noexcept { Reg::Write<F_ACCMOD>(value); }
    static auto ReadDATLAT() noexcept -> ValueType { return Reg::Read<F_DATLAT>(); }
    static void WriteDATLAT(ValueType value) noexcept { Reg::Write<F_DATLAT>(value); }
    static auto ReadCLKDIV() noexcept -> ValueType { return Reg::Read<F_CLKDIV>(); }
    static void WriteCLKDIV(ValueType value) noexcept { Reg::Write<F_CLKDIV>(value); }
    static auto ReadBUSTURN() noexcept -> ValueType { return Reg::Read<F_BUSTURN>(); }
    static void WriteBUSTURN(ValueType value) noexcept { Reg::Write<F_BUSTURN>(value); }
    static auto ReadDATAST() noexcept -> ValueType { return Reg::Read<F_DATAST>(); }
    static void WriteDATAST(ValueType value) noexcept { Reg::Write<F_DATAST>(value); }
    static auto ReadADDHLD() noexcept -> ValueType { return Reg::Read<F_ADDHLD>(); }
    static void WriteADDHLD(ValueType value) noexcept { Reg::Write<F_ADDHLD>(value); }
    static auto ReadADDSET() noexcept -> ValueType { return Reg::Read<F_ADDSET>(); }
    static void WriteADDSET(ValueType value) noexcept { Reg::Write<F_ADDSET>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACCMOD = CortexM3::Field<ValueType, 28, 2>;
    using F_DATLAT = CortexM3::Field<ValueType, 24, 4>;
    using F_CLKDIV = CortexM3::Field<ValueType, 20, 4>;
    using F_BUSTURN = CortexM3::Field<ValueType, 16, 4>;
    using F_DATAST = CortexM3::Field<ValueType, 8, 8>;
    using F_ADDHLD = CortexM3::Field<ValueType, 4, 4>;
    using F_ADDSET = CortexM3::Field<ValueType, 0, 4>;
};

class BCR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x000030D0;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCBURSTRW() noexcept -> ValueType { return Reg::Read<F_CBURSTRW>(); }
    static void WriteCBURSTRW(ValueType value) noexcept { Reg::Write<F_CBURSTRW>(value); }
    static auto ReadASYNCWAIT() noexcept -> ValueType { return Reg::Read<F_ASYNCWAIT>(); }
    static void WriteASYNCWAIT(ValueType value) noexcept { Reg::Write<F_ASYNCWAIT>(value); }
    static auto ReadEXTMOD() noexcept -> ValueType { return Reg::Read<F_EXTMOD>(); }
    static void WriteEXTMOD(ValueType value) noexcept { Reg::Write<F_EXTMOD>(value); }
    static auto ReadWAITEN() noexcept -> ValueType { return Reg::Read<F_WAITEN>(); }
    static void WriteWAITEN(ValueType value) noexcept { Reg::Write<F_WAITEN>(value); }
    static auto ReadWREN() noexcept -> ValueType { return Reg::Read<F_WREN>(); }
    static void WriteWREN(ValueType value) noexcept { Reg::Write<F_WREN>(value); }
    static auto ReadWAITCFG() noexcept -> ValueType { return Reg::Read<F_WAITCFG>(); }
    static void WriteWAITCFG(ValueType value) noexcept { Reg::Write<F_WAITCFG>(value); }
    static auto ReadWRAPMOD() noexcept -> ValueType { return Reg::Read<F_WRAPMOD>(); }
    static void WriteWRAPMOD(ValueType value) noexcept { Reg::Write<F_WRAPMOD>(value); }
    static auto ReadWAITPOL() noexcept -> ValueType { return Reg::Read<F_WAITPOL>(); }
    static void WriteWAITPOL(ValueType value) noexcept { Reg::Write<F_WAITPOL>(value); }
    static auto ReadBURSTEN() noexcept -> ValueType { return Reg::Read<F_BURSTEN>(); }
    static void WriteBURSTEN(ValueType value) noexcept { Reg::Write<F_BURSTEN>(value); }
    static auto ReadFACCEN() noexcept -> ValueType { return Reg::Read<F_FACCEN>(); }
    static void WriteFACCEN(ValueType value) noexcept { Reg::Write<F_FACCEN>(value); }
    static auto ReadMWID() noexcept -> ValueType { return Reg::Read<F_MWID>(); }
    static void WriteMWID(ValueType value) noexcept { Reg::Write<F_MWID>(value); }
    static auto ReadMTYP() noexcept -> ValueType { return Reg::Read<F_MTYP>(); }
    static void WriteMTYP(ValueType value) noexcept { Reg::Write<F_MTYP>(value); }
    static auto ReadMUXEN() noexcept -> ValueType { return Reg::Read<F_MUXEN>(); }
    static void WriteMUXEN(ValueType value) noexcept { Reg::Write<F_MUXEN>(value); }
    static auto ReadMBKEN() noexcept -> ValueType { return Reg::Read<F_MBKEN>(); }
    static void WriteMBKEN(ValueType value) noexcept { Reg::Write<F_MBKEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000018;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CBURSTRW = CortexM3::Field<ValueType, 19, 1>;
    using F_ASYNCWAIT = CortexM3::Field<ValueType, 15, 1>;
    using F_EXTMOD = CortexM3::Field<ValueType, 14, 1>;
    using F_WAITEN = CortexM3::Field<ValueType, 13, 1>;
    using F_WREN = CortexM3::Field<ValueType, 12, 1>;
    using F_WAITCFG = CortexM3::Field<ValueType, 11, 1>;
    using F_WRAPMOD = CortexM3::Field<ValueType, 10, 1>;
    using F_WAITPOL = CortexM3::Field<ValueType, 9, 1>;
    using F_BURSTEN = CortexM3::Field<ValueType, 8, 1>;
    using F_FACCEN = CortexM3::Field<ValueType, 6, 1>;
    using F_MWID = CortexM3::Field<ValueType, 4, 2>;
    using F_MTYP = CortexM3::Field<ValueType, 2, 2>;
    using F_MUXEN = CortexM3::Field<ValueType, 1, 1>;
    using F_MBKEN = CortexM3::Field<ValueType, 0, 1>;
};

class BTR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFFFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACCMOD() noexcept -> ValueType { return Reg::Read<F_ACCMOD>(); }
    static void WriteACCMOD(ValueType value) noexcept { Reg::Write<F_ACCMOD>(value); }
    static auto ReadDATLAT() noexcept -> ValueType { return Reg::Read<F_DATLAT>(); }
    static void WriteDATLAT(ValueType value) noexcept { Reg::Write<F_DATLAT>(value); }
    static auto ReadCLKDIV() noexcept -> ValueType { return Reg::Read<F_CLKDIV>(); }
    static void WriteCLKDIV(ValueType value) noexcept { Reg::Write<F_CLKDIV>(value); }
    static auto ReadBUSTURN() noexcept -> ValueType { return Reg::Read<F_BUSTURN>(); }
    static void WriteBUSTURN(ValueType value) noexcept { Reg::Write<F_BUSTURN>(value); }
    static auto ReadDATAST() noexcept -> ValueType { return Reg::Read<F_DATAST>(); }
    static void WriteDATAST(ValueType value) noexcept { Reg::Write<F_DATAST>(value); }
    static auto ReadADDHLD() noexcept -> ValueType { return Reg::Read<F_ADDHLD>(); }
    static void WriteADDHLD(ValueType value) noexcept { Reg::Write<F_ADDHLD>(value); }
    static auto ReadADDSET() noexcept -> ValueType { return Reg::Read<F_ADDSET>(); }
    static void WriteADDSET(ValueType value) noexcept { Reg::Write<F_ADDSET>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa000001c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACCMOD = CortexM3::Field<ValueType, 28, 2>;
    using F_DATLAT = CortexM3::Field<ValueType, 24, 4>;
    using F_CLKDIV = CortexM3::Field<ValueType, 20, 4>;
    using F_BUSTURN = CortexM3::Field<ValueType, 16, 4>;
    using F_DATAST = CortexM3::Field<ValueType, 8, 8>;
    using F_ADDHLD = CortexM3::Field<ValueType, 4, 4>;
    using F_ADDSET = CortexM3::Field<ValueType, 0, 4>;
};

class PCR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000018;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadECCPS() noexcept -> ValueType { return Reg::Read<F_ECCPS>(); }
    static void WriteECCPS(ValueType value) noexcept { Reg::Write<F_ECCPS>(value); }
    static auto ReadTAR() noexcept -> ValueType { return Reg::Read<F_TAR>(); }
    static void WriteTAR(ValueType value) noexcept { Reg::Write<F_TAR>(value); }
    static auto ReadTCLR() noexcept -> ValueType { return Reg::Read<F_TCLR>(); }
    static void WriteTCLR(ValueType value) noexcept { Reg::Write<F_TCLR>(value); }
    static auto ReadECCEN() noexcept -> ValueType { return Reg::Read<F_ECCEN>(); }
    static void WriteECCEN(ValueType value) noexcept { Reg::Write<F_ECCEN>(value); }
    static auto ReadPWID() noexcept -> ValueType { return Reg::Read<F_PWID>(); }
    static void WritePWID(ValueType value) noexcept { Reg::Write<F_PWID>(value); }
    static auto ReadPTYP() noexcept -> ValueType { return Reg::Read<F_PTYP>(); }
    static void WritePTYP(ValueType value) noexcept { Reg::Write<F_PTYP>(value); }
    static auto ReadPBKEN() noexcept -> ValueType { return Reg::Read<F_PBKEN>(); }
    static void WritePBKEN(ValueType value) noexcept { Reg::Write<F_PBKEN>(value); }
    static auto ReadPWAITEN() noexcept -> ValueType { return Reg::Read<F_PWAITEN>(); }
    static void WritePWAITEN(ValueType value) noexcept { Reg::Write<F_PWAITEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000060;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ECCPS = CortexM3::Field<ValueType, 17, 3>;
    using F_TAR = CortexM3::Field<ValueType, 13, 4>;
    using F_TCLR = CortexM3::Field<ValueType, 9, 4>;
    using F_ECCEN = CortexM3::Field<ValueType, 6, 1>;
    using F_PWID = CortexM3::Field<ValueType, 4, 2>;
    using F_PTYP = CortexM3::Field<ValueType, 3, 1>;
    using F_PBKEN = CortexM3::Field<ValueType, 2, 1>;
    using F_PWAITEN = CortexM3::Field<ValueType, 1, 1>;
};

class SR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000040;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFEMPT() noexcept -> ValueType { return Reg::Read<F_FEMPT>(); }
    static auto ReadIFEN() noexcept -> ValueType { return Reg::Read<F_IFEN>(); }
    static void WriteIFEN(ValueType value) noexcept { Reg::Write<F_IFEN>(value); }
    static auto ReadILEN() noexcept -> ValueType { return Reg::Read<F_ILEN>(); }
    static void WriteILEN(ValueType value) noexcept { Reg::Write<F_ILEN>(value); }
    static auto ReadIREN() noexcept -> ValueType { return Reg::Read<F_IREN>(); }
    static void WriteIREN(ValueType value) noexcept { Reg::Write<F_IREN>(value); }
    static auto ReadIFS() noexcept -> ValueType { return Reg::Read<F_IFS>(); }
    static void WriteIFS(ValueType value) noexcept { Reg::Write<F_IFS>(value); }
    static auto ReadILS() noexcept -> ValueType { return Reg::Read<F_ILS>(); }
    static void WriteILS(ValueType value) noexcept { Reg::Write<F_ILS>(value); }
    static auto ReadIRS() noexcept -> ValueType { return Reg::Read<F_IRS>(); }
    static void WriteIRS(ValueType value) noexcept { Reg::Write<F_IRS>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000064;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FEMPT = CortexM3::Field<ValueType, 6, 1>;
    using F_IFEN = CortexM3::Field<ValueType, 5, 1>;
    using F_ILEN = CortexM3::Field<ValueType, 4, 1>;
    using F_IREN = CortexM3::Field<ValueType, 3, 1>;
    using F_IFS = CortexM3::Field<ValueType, 2, 1>;
    using F_ILS = CortexM3::Field<ValueType, 1, 1>;
    using F_IRS = CortexM3::Field<ValueType, 0, 1>;
};

class PMEM2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFCFCFCFC;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMEMHIZx() noexcept -> ValueType { return Reg::Read<F_MEMHIZx>(); }
    static void WriteMEMHIZx(ValueType value) noexcept { Reg::Write<F_MEMHIZx>(value); }
    static auto ReadMEMHOLDx() noexcept -> ValueType { return Reg::Read<F_MEMHOLDx>(); }
    static void WriteMEMHOLDx(ValueType value) noexcept { Reg::Write<F_MEMHOLDx>(value); }
    static auto ReadMEMWAITx() noexcept -> ValueType { return Reg::Read<F_MEMWAITx>(); }
    static void WriteMEMWAITx(ValueType value) noexcept { Reg::Write<F_MEMWAITx>(value); }
    static auto ReadMEMSETx() noexcept -> ValueType { return Reg::Read<F_MEMSETx>(); }
    static void WriteMEMSETx(ValueType value) noexcept { Reg::Write<F_MEMSETx>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000068;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MEMHIZx = CortexM3::Field<ValueType, 24, 8>;
    using F_MEMHOLDx = CortexM3::Field<ValueType, 16, 8>;
    using F_MEMWAITx = CortexM3::Field<ValueType, 8, 8>;
    using F_MEMSETx = CortexM3::Field<ValueType, 0, 8>;
};

class PATT2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFCFCFCFC;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadATTHIZx() noexcept -> ValueType { return Reg::Read<F_ATTHIZx>(); }
    static void WriteATTHIZx(ValueType value) noexcept { Reg::Write<F_ATTHIZx>(value); }
    static auto ReadATTHOLDx() noexcept -> ValueType { return Reg::Read<F_ATTHOLDx>(); }
    static void WriteATTHOLDx(ValueType value) noexcept { Reg::Write<F_ATTHOLDx>(value); }
    static auto ReadATTWAITx() noexcept -> ValueType { return Reg::Read<F_ATTWAITx>(); }
    static void WriteATTWAITx(ValueType value) noexcept { Reg::Write<F_ATTWAITx>(value); }
    static auto ReadATTSETx() noexcept -> ValueType { return Reg::Read<F_ATTSETx>(); }
    static void WriteATTSETx(ValueType value) noexcept { Reg::Write<F_ATTSETx>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa000006c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ATTHIZx = CortexM3::Field<ValueType, 24, 8>;
    using F_ATTHOLDx = CortexM3::Field<ValueType, 16, 8>;
    using F_ATTWAITx = CortexM3::Field<ValueType, 8, 8>;
    using F_ATTSETx = CortexM3::Field<ValueType, 0, 8>;
};

class ECCR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadECCx() noexcept -> ValueType { return Reg::Read<F_ECCx>(); }

private:
    static constexpr std::uintptr_t Address = 0xa0000074;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ECCx = CortexM3::Field<ValueType, 0, 32>;
};

class PCR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000018;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadECCPS() noexcept -> ValueType { return Reg::Read<F_ECCPS>(); }
    static void WriteECCPS(ValueType value) noexcept { Reg::Write<F_ECCPS>(value); }
    static auto ReadTAR() noexcept -> ValueType { return Reg::Read<F_TAR>(); }
    static void WriteTAR(ValueType value) noexcept { Reg::Write<F_TAR>(value); }
    static auto ReadTCLR() noexcept -> ValueType { return Reg::Read<F_TCLR>(); }
    static void WriteTCLR(ValueType value) noexcept { Reg::Write<F_TCLR>(value); }
    static auto ReadECCEN() noexcept -> ValueType { return Reg::Read<F_ECCEN>(); }
    static void WriteECCEN(ValueType value) noexcept { Reg::Write<F_ECCEN>(value); }
    static auto ReadPWID() noexcept -> ValueType { return Reg::Read<F_PWID>(); }
    static void WritePWID(ValueType value) noexcept { Reg::Write<F_PWID>(value); }
    static auto ReadPTYP() noexcept -> ValueType { return Reg::Read<F_PTYP>(); }
    static void WritePTYP(ValueType value) noexcept { Reg::Write<F_PTYP>(value); }
    static auto ReadPBKEN() noexcept -> ValueType { return Reg::Read<F_PBKEN>(); }
    static void WritePBKEN(ValueType value) noexcept { Reg::Write<F_PBKEN>(value); }
    static auto ReadPWAITEN() noexcept -> ValueType { return Reg::Read<F_PWAITEN>(); }
    static void WritePWAITEN(ValueType value) noexcept { Reg::Write<F_PWAITEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000080;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ECCPS = CortexM3::Field<ValueType, 17, 3>;
    using F_TAR = CortexM3::Field<ValueType, 13, 4>;
    using F_TCLR = CortexM3::Field<ValueType, 9, 4>;
    using F_ECCEN = CortexM3::Field<ValueType, 6, 1>;
    using F_PWID = CortexM3::Field<ValueType, 4, 2>;
    using F_PTYP = CortexM3::Field<ValueType, 3, 1>;
    using F_PBKEN = CortexM3::Field<ValueType, 2, 1>;
    using F_PWAITEN = CortexM3::Field<ValueType, 1, 1>;
};

class SR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000040;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFEMPT() noexcept -> ValueType { return Reg::Read<F_FEMPT>(); }
    static auto ReadIFEN() noexcept -> ValueType { return Reg::Read<F_IFEN>(); }
    static void WriteIFEN(ValueType value) noexcept { Reg::Write<F_IFEN>(value); }
    static auto ReadILEN() noexcept -> ValueType { return Reg::Read<F_ILEN>(); }
    static void WriteILEN(ValueType value) noexcept { Reg::Write<F_ILEN>(value); }
    static auto ReadIREN() noexcept -> ValueType { return Reg::Read<F_IREN>(); }
    static void WriteIREN(ValueType value) noexcept { Reg::Write<F_IREN>(value); }
    static auto ReadIFS() noexcept -> ValueType { return Reg::Read<F_IFS>(); }
    static void WriteIFS(ValueType value) noexcept { Reg::Write<F_IFS>(value); }
    static auto ReadILS() noexcept -> ValueType { return Reg::Read<F_ILS>(); }
    static void WriteILS(ValueType value) noexcept { Reg::Write<F_ILS>(value); }
    static auto ReadIRS() noexcept -> ValueType { return Reg::Read<F_IRS>(); }
    static void WriteIRS(ValueType value) noexcept { Reg::Write<F_IRS>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000084;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FEMPT = CortexM3::Field<ValueType, 6, 1>;
    using F_IFEN = CortexM3::Field<ValueType, 5, 1>;
    using F_ILEN = CortexM3::Field<ValueType, 4, 1>;
    using F_IREN = CortexM3::Field<ValueType, 3, 1>;
    using F_IFS = CortexM3::Field<ValueType, 2, 1>;
    using F_ILS = CortexM3::Field<ValueType, 1, 1>;
    using F_IRS = CortexM3::Field<ValueType, 0, 1>;
};

class PMEM3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFCFCFCFC;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMEMHIZx() noexcept -> ValueType { return Reg::Read<F_MEMHIZx>(); }
    static void WriteMEMHIZx(ValueType value) noexcept { Reg::Write<F_MEMHIZx>(value); }
    static auto ReadMEMHOLDx() noexcept -> ValueType { return Reg::Read<F_MEMHOLDx>(); }
    static void WriteMEMHOLDx(ValueType value) noexcept { Reg::Write<F_MEMHOLDx>(value); }
    static auto ReadMEMWAITx() noexcept -> ValueType { return Reg::Read<F_MEMWAITx>(); }
    static void WriteMEMWAITx(ValueType value) noexcept { Reg::Write<F_MEMWAITx>(value); }
    static auto ReadMEMSETx() noexcept -> ValueType { return Reg::Read<F_MEMSETx>(); }
    static void WriteMEMSETx(ValueType value) noexcept { Reg::Write<F_MEMSETx>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000088;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MEMHIZx = CortexM3::Field<ValueType, 24, 8>;
    using F_MEMHOLDx = CortexM3::Field<ValueType, 16, 8>;
    using F_MEMWAITx = CortexM3::Field<ValueType, 8, 8>;
    using F_MEMSETx = CortexM3::Field<ValueType, 0, 8>;
};

class PATT3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFCFCFCFC;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadATTHIZx() noexcept -> ValueType { return Reg::Read<F_ATTHIZx>(); }
    static void WriteATTHIZx(ValueType value) noexcept { Reg::Write<F_ATTHIZx>(value); }
    static auto ReadATTHOLDx() noexcept -> ValueType { return Reg::Read<F_ATTHOLDx>(); }
    static void WriteATTHOLDx(ValueType value) noexcept { Reg::Write<F_ATTHOLDx>(value); }
    static auto ReadATTWAITx() noexcept -> ValueType { return Reg::Read<F_ATTWAITx>(); }
    static void WriteATTWAITx(ValueType value) noexcept { Reg::Write<F_ATTWAITx>(value); }
    static auto ReadATTSETx() noexcept -> ValueType { return Reg::Read<F_ATTSETx>(); }
    static void WriteATTSETx(ValueType value) noexcept { Reg::Write<F_ATTSETx>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa000008c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ATTHIZx = CortexM3::Field<ValueType, 24, 8>;
    using F_ATTHOLDx = CortexM3::Field<ValueType, 16, 8>;
    using F_ATTWAITx = CortexM3::Field<ValueType, 8, 8>;
    using F_ATTSETx = CortexM3::Field<ValueType, 0, 8>;
};

class ECCR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadECCx() noexcept -> ValueType { return Reg::Read<F_ECCx>(); }

private:
    static constexpr std::uintptr_t Address = 0xa0000094;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ECCx = CortexM3::Field<ValueType, 0, 32>;
};

class PCR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000018;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadECCPS() noexcept -> ValueType { return Reg::Read<F_ECCPS>(); }
    static void WriteECCPS(ValueType value) noexcept { Reg::Write<F_ECCPS>(value); }
    static auto ReadTAR() noexcept -> ValueType { return Reg::Read<F_TAR>(); }
    static void WriteTAR(ValueType value) noexcept { Reg::Write<F_TAR>(value); }
    static auto ReadTCLR() noexcept -> ValueType { return Reg::Read<F_TCLR>(); }
    static void WriteTCLR(ValueType value) noexcept { Reg::Write<F_TCLR>(value); }
    static auto ReadECCEN() noexcept -> ValueType { return Reg::Read<F_ECCEN>(); }
    static void WriteECCEN(ValueType value) noexcept { Reg::Write<F_ECCEN>(value); }
    static auto ReadPWID() noexcept -> ValueType { return Reg::Read<F_PWID>(); }
    static void WritePWID(ValueType value) noexcept { Reg::Write<F_PWID>(value); }
    static auto ReadPTYP() noexcept -> ValueType { return Reg::Read<F_PTYP>(); }
    static void WritePTYP(ValueType value) noexcept { Reg::Write<F_PTYP>(value); }
    static auto ReadPBKEN() noexcept -> ValueType { return Reg::Read<F_PBKEN>(); }
    static void WritePBKEN(ValueType value) noexcept { Reg::Write<F_PBKEN>(value); }
    static auto ReadPWAITEN() noexcept -> ValueType { return Reg::Read<F_PWAITEN>(); }
    static void WritePWAITEN(ValueType value) noexcept { Reg::Write<F_PWAITEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa00000a0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ECCPS = CortexM3::Field<ValueType, 17, 3>;
    using F_TAR = CortexM3::Field<ValueType, 13, 4>;
    using F_TCLR = CortexM3::Field<ValueType, 9, 4>;
    using F_ECCEN = CortexM3::Field<ValueType, 6, 1>;
    using F_PWID = CortexM3::Field<ValueType, 4, 2>;
    using F_PTYP = CortexM3::Field<ValueType, 3, 1>;
    using F_PBKEN = CortexM3::Field<ValueType, 2, 1>;
    using F_PWAITEN = CortexM3::Field<ValueType, 1, 1>;
};

class SR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000040;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFEMPT() noexcept -> ValueType { return Reg::Read<F_FEMPT>(); }
    static auto ReadIFEN() noexcept -> ValueType { return Reg::Read<F_IFEN>(); }
    static void WriteIFEN(ValueType value) noexcept { Reg::Write<F_IFEN>(value); }
    static auto ReadILEN() noexcept -> ValueType { return Reg::Read<F_ILEN>(); }
    static void WriteILEN(ValueType value) noexcept { Reg::Write<F_ILEN>(value); }
    static auto ReadIREN() noexcept -> ValueType { return Reg::Read<F_IREN>(); }
    static void WriteIREN(ValueType value) noexcept { Reg::Write<F_IREN>(value); }
    static auto ReadIFS() noexcept -> ValueType { return Reg::Read<F_IFS>(); }
    static void WriteIFS(ValueType value) noexcept { Reg::Write<F_IFS>(value); }
    static auto ReadILS() noexcept -> ValueType { return Reg::Read<F_ILS>(); }
    static void WriteILS(ValueType value) noexcept { Reg::Write<F_ILS>(value); }
    static auto ReadIRS() noexcept -> ValueType { return Reg::Read<F_IRS>(); }
    static void WriteIRS(ValueType value) noexcept { Reg::Write<F_IRS>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa00000a4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FEMPT = CortexM3::Field<ValueType, 6, 1>;
    using F_IFEN = CortexM3::Field<ValueType, 5, 1>;
    using F_ILEN = CortexM3::Field<ValueType, 4, 1>;
    using F_IREN = CortexM3::Field<ValueType, 3, 1>;
    using F_IFS = CortexM3::Field<ValueType, 2, 1>;
    using F_ILS = CortexM3::Field<ValueType, 1, 1>;
    using F_IRS = CortexM3::Field<ValueType, 0, 1>;
};

class PMEM4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFCFCFCFC;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMEMHIZx() noexcept -> ValueType { return Reg::Read<F_MEMHIZx>(); }
    static void WriteMEMHIZx(ValueType value) noexcept { Reg::Write<F_MEMHIZx>(value); }
    static auto ReadMEMHOLDx() noexcept -> ValueType { return Reg::Read<F_MEMHOLDx>(); }
    static void WriteMEMHOLDx(ValueType value) noexcept { Reg::Write<F_MEMHOLDx>(value); }
    static auto ReadMEMWAITx() noexcept -> ValueType { return Reg::Read<F_MEMWAITx>(); }
    static void WriteMEMWAITx(ValueType value) noexcept { Reg::Write<F_MEMWAITx>(value); }
    static auto ReadMEMSETx() noexcept -> ValueType { return Reg::Read<F_MEMSETx>(); }
    static void WriteMEMSETx(ValueType value) noexcept { Reg::Write<F_MEMSETx>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa00000a8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MEMHIZx = CortexM3::Field<ValueType, 24, 8>;
    using F_MEMHOLDx = CortexM3::Field<ValueType, 16, 8>;
    using F_MEMWAITx = CortexM3::Field<ValueType, 8, 8>;
    using F_MEMSETx = CortexM3::Field<ValueType, 0, 8>;
};

class PATT4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFCFCFCFC;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadATTHIZx() noexcept -> ValueType { return Reg::Read<F_ATTHIZx>(); }
    static void WriteATTHIZx(ValueType value) noexcept { Reg::Write<F_ATTHIZx>(value); }
    static auto ReadATTHOLDx() noexcept -> ValueType { return Reg::Read<F_ATTHOLDx>(); }
    static void WriteATTHOLDx(ValueType value) noexcept { Reg::Write<F_ATTHOLDx>(value); }
    static auto ReadATTWAITx() noexcept -> ValueType { return Reg::Read<F_ATTWAITx>(); }
    static void WriteATTWAITx(ValueType value) noexcept { Reg::Write<F_ATTWAITx>(value); }
    static auto ReadATTSETx() noexcept -> ValueType { return Reg::Read<F_ATTSETx>(); }
    static void WriteATTSETx(ValueType value) noexcept { Reg::Write<F_ATTSETx>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa00000ac;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ATTHIZx = CortexM3::Field<ValueType, 24, 8>;
    using F_ATTHOLDx = CortexM3::Field<ValueType, 16, 8>;
    using F_ATTWAITx = CortexM3::Field<ValueType, 8, 8>;
    using F_ATTSETx = CortexM3::Field<ValueType, 0, 8>;
};

class PIO4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFCFCFCFC;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadIOHIZx() noexcept -> ValueType { return Reg::Read<F_IOHIZx>(); }
    static void WriteIOHIZx(ValueType value) noexcept { Reg::Write<F_IOHIZx>(value); }
    static auto ReadIOHOLDx() noexcept -> ValueType { return Reg::Read<F_IOHOLDx>(); }
    static void WriteIOHOLDx(ValueType value) noexcept { Reg::Write<F_IOHOLDx>(value); }
    static auto ReadIOWAITx() noexcept -> ValueType { return Reg::Read<F_IOWAITx>(); }
    static void WriteIOWAITx(ValueType value) noexcept { Reg::Write<F_IOWAITx>(value); }
    static auto ReadIOSETx() noexcept -> ValueType { return Reg::Read<F_IOSETx>(); }
    static void WriteIOSETx(ValueType value) noexcept { Reg::Write<F_IOSETx>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa00000b0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_IOHIZx = CortexM3::Field<ValueType, 24, 8>;
    using F_IOHOLDx = CortexM3::Field<ValueType, 16, 8>;
    using F_IOWAITx = CortexM3::Field<ValueType, 8, 8>;
    using F_IOSETx = CortexM3::Field<ValueType, 0, 8>;
};

class BWTR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0FFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACCMOD() noexcept -> ValueType { return Reg::Read<F_ACCMOD>(); }
    static void WriteACCMOD(ValueType value) noexcept { Reg::Write<F_ACCMOD>(value); }
    static auto ReadDATLAT() noexcept -> ValueType { return Reg::Read<F_DATLAT>(); }
    static void WriteDATLAT(ValueType value) noexcept { Reg::Write<F_DATLAT>(value); }
    static auto ReadCLKDIV() noexcept -> ValueType { return Reg::Read<F_CLKDIV>(); }
    static void WriteCLKDIV(ValueType value) noexcept { Reg::Write<F_CLKDIV>(value); }
    static auto ReadDATAST() noexcept -> ValueType { return Reg::Read<F_DATAST>(); }
    static void WriteDATAST(ValueType value) noexcept { Reg::Write<F_DATAST>(value); }
    static auto ReadADDHLD() noexcept -> ValueType { return Reg::Read<F_ADDHLD>(); }
    static void WriteADDHLD(ValueType value) noexcept { Reg::Write<F_ADDHLD>(value); }
    static auto ReadADDSET() noexcept -> ValueType { return Reg::Read<F_ADDSET>(); }
    static void WriteADDSET(ValueType value) noexcept { Reg::Write<F_ADDSET>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000104;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACCMOD = CortexM3::Field<ValueType, 28, 2>;
    using F_DATLAT = CortexM3::Field<ValueType, 24, 4>;
    using F_CLKDIV = CortexM3::Field<ValueType, 20, 4>;
    using F_DATAST = CortexM3::Field<ValueType, 8, 8>;
    using F_ADDHLD = CortexM3::Field<ValueType, 4, 4>;
    using F_ADDSET = CortexM3::Field<ValueType, 0, 4>;
};

class BWTR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0FFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACCMOD() noexcept -> ValueType { return Reg::Read<F_ACCMOD>(); }
    static void WriteACCMOD(ValueType value) noexcept { Reg::Write<F_ACCMOD>(value); }
    static auto ReadDATLAT() noexcept -> ValueType { return Reg::Read<F_DATLAT>(); }
    static void WriteDATLAT(ValueType value) noexcept { Reg::Write<F_DATLAT>(value); }
    static auto ReadCLKDIV() noexcept -> ValueType { return Reg::Read<F_CLKDIV>(); }
    static void WriteCLKDIV(ValueType value) noexcept { Reg::Write<F_CLKDIV>(value); }
    static auto ReadDATAST() noexcept -> ValueType { return Reg::Read<F_DATAST>(); }
    static void WriteDATAST(ValueType value) noexcept { Reg::Write<F_DATAST>(value); }
    static auto ReadADDHLD() noexcept -> ValueType { return Reg::Read<F_ADDHLD>(); }
    static void WriteADDHLD(ValueType value) noexcept { Reg::Write<F_ADDHLD>(value); }
    static auto ReadADDSET() noexcept -> ValueType { return Reg::Read<F_ADDSET>(); }
    static void WriteADDSET(ValueType value) noexcept { Reg::Write<F_ADDSET>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa000010c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACCMOD = CortexM3::Field<ValueType, 28, 2>;
    using F_DATLAT = CortexM3::Field<ValueType, 24, 4>;
    using F_CLKDIV = CortexM3::Field<ValueType, 20, 4>;
    using F_DATAST = CortexM3::Field<ValueType, 8, 8>;
    using F_ADDHLD = CortexM3::Field<ValueType, 4, 4>;
    using F_ADDSET = CortexM3::Field<ValueType, 0, 4>;
};

class BWTR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0FFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACCMOD() noexcept -> ValueType { return Reg::Read<F_ACCMOD>(); }
    static void WriteACCMOD(ValueType value) noexcept { Reg::Write<F_ACCMOD>(value); }
    static auto ReadDATLAT() noexcept -> ValueType { return Reg::Read<F_DATLAT>(); }
    static void WriteDATLAT(ValueType value) noexcept { Reg::Write<F_DATLAT>(value); }
    static auto ReadCLKDIV() noexcept -> ValueType { return Reg::Read<F_CLKDIV>(); }
    static void WriteCLKDIV(ValueType value) noexcept { Reg::Write<F_CLKDIV>(value); }
    static auto ReadDATAST() noexcept -> ValueType { return Reg::Read<F_DATAST>(); }
    static void WriteDATAST(ValueType value) noexcept { Reg::Write<F_DATAST>(value); }
    static auto ReadADDHLD() noexcept -> ValueType { return Reg::Read<F_ADDHLD>(); }
    static void WriteADDHLD(ValueType value) noexcept { Reg::Write<F_ADDHLD>(value); }
    static auto ReadADDSET() noexcept -> ValueType { return Reg::Read<F_ADDSET>(); }
    static void WriteADDSET(ValueType value) noexcept { Reg::Write<F_ADDSET>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa0000114;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACCMOD = CortexM3::Field<ValueType, 28, 2>;
    using F_DATLAT = CortexM3::Field<ValueType, 24, 4>;
    using F_CLKDIV = CortexM3::Field<ValueType, 20, 4>;
    using F_DATAST = CortexM3::Field<ValueType, 8, 8>;
    using F_ADDHLD = CortexM3::Field<ValueType, 4, 4>;
    using F_ADDSET = CortexM3::Field<ValueType, 0, 4>;
};

class BWTR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0FFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACCMOD() noexcept -> ValueType { return Reg::Read<F_ACCMOD>(); }
    static void WriteACCMOD(ValueType value) noexcept { Reg::Write<F_ACCMOD>(value); }
    static auto ReadDATLAT() noexcept -> ValueType { return Reg::Read<F_DATLAT>(); }
    static void WriteDATLAT(ValueType value) noexcept { Reg::Write<F_DATLAT>(value); }
    static auto ReadCLKDIV() noexcept -> ValueType { return Reg::Read<F_CLKDIV>(); }
    static void WriteCLKDIV(ValueType value) noexcept { Reg::Write<F_CLKDIV>(value); }
    static auto ReadDATAST() noexcept -> ValueType { return Reg::Read<F_DATAST>(); }
    static void WriteDATAST(ValueType value) noexcept { Reg::Write<F_DATAST>(value); }
    static auto ReadADDHLD() noexcept -> ValueType { return Reg::Read<F_ADDHLD>(); }
    static void WriteADDHLD(ValueType value) noexcept { Reg::Write<F_ADDHLD>(value); }
    static auto ReadADDSET() noexcept -> ValueType { return Reg::Read<F_ADDSET>(); }
    static void WriteADDSET(ValueType value) noexcept { Reg::Write<F_ADDSET>(value); }

private:
    static constexpr std::uintptr_t Address = 0xa000011c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACCMOD = CortexM3::Field<ValueType, 28, 2>;
    using F_DATLAT = CortexM3::Field<ValueType, 24, 4>;
    using F_CLKDIV = CortexM3::Field<ValueType, 20, 4>;
    using F_DATAST = CortexM3::Field<ValueType, 8, 8>;
    using F_ADDHLD = CortexM3::Field<ValueType, 4, 4>;
    using F_ADDSET = CortexM3::Field<ValueType, 0, 4>;
};

} // namespace STM32F103::FSMC
