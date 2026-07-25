#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::SDIO {

class POWER {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPWRCTRL() noexcept -> ValueType { return Reg::Read<F_PWRCTRL>(); }
    static void WritePWRCTRL(ValueType value) noexcept { Reg::Write<F_PWRCTRL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40018000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PWRCTRL = CortexM3::Field<ValueType, 0, 2>;
};

class CLKCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLKDIV() noexcept -> ValueType { return Reg::Read<F_CLKDIV>(); }
    static void WriteCLKDIV(ValueType value) noexcept { Reg::Write<F_CLKDIV>(value); }
    static auto ReadCLKEN() noexcept -> ValueType { return Reg::Read<F_CLKEN>(); }
    static void WriteCLKEN(ValueType value) noexcept { Reg::Write<F_CLKEN>(value); }
    static auto ReadPWRSAV() noexcept -> ValueType { return Reg::Read<F_PWRSAV>(); }
    static void WritePWRSAV(ValueType value) noexcept { Reg::Write<F_PWRSAV>(value); }
    static auto ReadBYPASS() noexcept -> ValueType { return Reg::Read<F_BYPASS>(); }
    static void WriteBYPASS(ValueType value) noexcept { Reg::Write<F_BYPASS>(value); }
    static auto ReadWIDBUS() noexcept -> ValueType { return Reg::Read<F_WIDBUS>(); }
    static void WriteWIDBUS(ValueType value) noexcept { Reg::Write<F_WIDBUS>(value); }
    static auto ReadNEGEDGE() noexcept -> ValueType { return Reg::Read<F_NEGEDGE>(); }
    static void WriteNEGEDGE(ValueType value) noexcept { Reg::Write<F_NEGEDGE>(value); }
    static auto ReadHWFC_EN() noexcept -> ValueType { return Reg::Read<F_HWFC_EN>(); }
    static void WriteHWFC_EN(ValueType value) noexcept { Reg::Write<F_HWFC_EN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40018004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLKDIV = CortexM3::Field<ValueType, 0, 8>;
    using F_CLKEN = CortexM3::Field<ValueType, 8, 1>;
    using F_PWRSAV = CortexM3::Field<ValueType, 9, 1>;
    using F_BYPASS = CortexM3::Field<ValueType, 10, 1>;
    using F_WIDBUS = CortexM3::Field<ValueType, 11, 2>;
    using F_NEGEDGE = CortexM3::Field<ValueType, 13, 1>;
    using F_HWFC_EN = CortexM3::Field<ValueType, 14, 1>;
};

class ARG {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCMDARG() noexcept -> ValueType { return Reg::Read<F_CMDARG>(); }
    static void WriteCMDARG(ValueType value) noexcept { Reg::Write<F_CMDARG>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40018008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CMDARG = CortexM3::Field<ValueType, 0, 32>;
};

class CMD {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCMDINDEX() noexcept -> ValueType { return Reg::Read<F_CMDINDEX>(); }
    static void WriteCMDINDEX(ValueType value) noexcept { Reg::Write<F_CMDINDEX>(value); }
    static auto ReadWAITRESP() noexcept -> ValueType { return Reg::Read<F_WAITRESP>(); }
    static void WriteWAITRESP(ValueType value) noexcept { Reg::Write<F_WAITRESP>(value); }
    static auto ReadWAITINT() noexcept -> ValueType { return Reg::Read<F_WAITINT>(); }
    static void WriteWAITINT(ValueType value) noexcept { Reg::Write<F_WAITINT>(value); }
    static auto ReadWAITPEND() noexcept -> ValueType { return Reg::Read<F_WAITPEND>(); }
    static void WriteWAITPEND(ValueType value) noexcept { Reg::Write<F_WAITPEND>(value); }
    static auto ReadCPSMEN() noexcept -> ValueType { return Reg::Read<F_CPSMEN>(); }
    static void WriteCPSMEN(ValueType value) noexcept { Reg::Write<F_CPSMEN>(value); }
    static auto ReadSDIOSuspend() noexcept -> ValueType { return Reg::Read<F_SDIOSuspend>(); }
    static void WriteSDIOSuspend(ValueType value) noexcept { Reg::Write<F_SDIOSuspend>(value); }
    static auto ReadENCMDcompl() noexcept -> ValueType { return Reg::Read<F_ENCMDcompl>(); }
    static void WriteENCMDcompl(ValueType value) noexcept { Reg::Write<F_ENCMDcompl>(value); }
    static auto ReadnIEN() noexcept -> ValueType { return Reg::Read<F_nIEN>(); }
    static void WritenIEN(ValueType value) noexcept { Reg::Write<F_nIEN>(value); }
    static auto ReadCE_ATACMD() noexcept -> ValueType { return Reg::Read<F_CE_ATACMD>(); }
    static void WriteCE_ATACMD(ValueType value) noexcept { Reg::Write<F_CE_ATACMD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001800c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CMDINDEX = CortexM3::Field<ValueType, 0, 6>;
    using F_WAITRESP = CortexM3::Field<ValueType, 6, 2>;
    using F_WAITINT = CortexM3::Field<ValueType, 8, 1>;
    using F_WAITPEND = CortexM3::Field<ValueType, 9, 1>;
    using F_CPSMEN = CortexM3::Field<ValueType, 10, 1>;
    using F_SDIOSuspend = CortexM3::Field<ValueType, 11, 1>;
    using F_ENCMDcompl = CortexM3::Field<ValueType, 12, 1>;
    using F_nIEN = CortexM3::Field<ValueType, 13, 1>;
    using F_CE_ATACMD = CortexM3::Field<ValueType, 14, 1>;
};

class RESPCMD {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadRESPCMD() noexcept -> ValueType { return Reg::Read<F_RESPCMD>(); }

private:
    static constexpr std::uintptr_t Address = 0x40018010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RESPCMD = CortexM3::Field<ValueType, 0, 6>;
};

class RESPI1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadCARDSTATUS1() noexcept -> ValueType { return Reg::Read<F_CARDSTATUS1>(); }

private:
    static constexpr std::uintptr_t Address = 0x40018014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CARDSTATUS1 = CortexM3::Field<ValueType, 0, 32>;
};

class RESP2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadCARDSTATUS2() noexcept -> ValueType { return Reg::Read<F_CARDSTATUS2>(); }

private:
    static constexpr std::uintptr_t Address = 0x40018018;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CARDSTATUS2 = CortexM3::Field<ValueType, 0, 32>;
};

class RESP3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadCARDSTATUS3() noexcept -> ValueType { return Reg::Read<F_CARDSTATUS3>(); }

private:
    static constexpr std::uintptr_t Address = 0x4001801c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CARDSTATUS3 = CortexM3::Field<ValueType, 0, 32>;
};

class RESP4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadCARDSTATUS4() noexcept -> ValueType { return Reg::Read<F_CARDSTATUS4>(); }

private:
    static constexpr std::uintptr_t Address = 0x40018020;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CARDSTATUS4 = CortexM3::Field<ValueType, 0, 32>;
};

class DTIMER {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDATATIME() noexcept -> ValueType { return Reg::Read<F_DATATIME>(); }
    static void WriteDATATIME(ValueType value) noexcept { Reg::Write<F_DATATIME>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40018024;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATATIME = CortexM3::Field<ValueType, 0, 32>;
};

class DLEN {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDATALENGTH() noexcept -> ValueType { return Reg::Read<F_DATALENGTH>(); }
    static void WriteDATALENGTH(ValueType value) noexcept { Reg::Write<F_DATALENGTH>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40018028;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATALENGTH = CortexM3::Field<ValueType, 0, 25>;
};

class DCTRL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDTEN() noexcept -> ValueType { return Reg::Read<F_DTEN>(); }
    static void WriteDTEN(ValueType value) noexcept { Reg::Write<F_DTEN>(value); }
    static auto ReadDTDIR() noexcept -> ValueType { return Reg::Read<F_DTDIR>(); }
    static void WriteDTDIR(ValueType value) noexcept { Reg::Write<F_DTDIR>(value); }
    static auto ReadDTMODE() noexcept -> ValueType { return Reg::Read<F_DTMODE>(); }
    static void WriteDTMODE(ValueType value) noexcept { Reg::Write<F_DTMODE>(value); }
    static auto ReadDMAEN() noexcept -> ValueType { return Reg::Read<F_DMAEN>(); }
    static void WriteDMAEN(ValueType value) noexcept { Reg::Write<F_DMAEN>(value); }
    static auto ReadDBLOCKSIZE() noexcept -> ValueType { return Reg::Read<F_DBLOCKSIZE>(); }
    static void WriteDBLOCKSIZE(ValueType value) noexcept { Reg::Write<F_DBLOCKSIZE>(value); }
    static auto ReadPWSTART() noexcept -> ValueType { return Reg::Read<F_PWSTART>(); }
    static void WritePWSTART(ValueType value) noexcept { Reg::Write<F_PWSTART>(value); }
    static auto ReadPWSTOP() noexcept -> ValueType { return Reg::Read<F_PWSTOP>(); }
    static void WritePWSTOP(ValueType value) noexcept { Reg::Write<F_PWSTOP>(value); }
    static auto ReadRWMOD() noexcept -> ValueType { return Reg::Read<F_RWMOD>(); }
    static void WriteRWMOD(ValueType value) noexcept { Reg::Write<F_RWMOD>(value); }
    static auto ReadSDIOEN() noexcept -> ValueType { return Reg::Read<F_SDIOEN>(); }
    static void WriteSDIOEN(ValueType value) noexcept { Reg::Write<F_SDIOEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001802c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DTEN = CortexM3::Field<ValueType, 0, 1>;
    using F_DTDIR = CortexM3::Field<ValueType, 1, 1>;
    using F_DTMODE = CortexM3::Field<ValueType, 2, 1>;
    using F_DMAEN = CortexM3::Field<ValueType, 3, 1>;
    using F_DBLOCKSIZE = CortexM3::Field<ValueType, 4, 4>;
    using F_PWSTART = CortexM3::Field<ValueType, 8, 1>;
    using F_PWSTOP = CortexM3::Field<ValueType, 9, 1>;
    using F_RWMOD = CortexM3::Field<ValueType, 10, 1>;
    using F_SDIOEN = CortexM3::Field<ValueType, 11, 1>;
};

class DCOUNT {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDATACOUNT() noexcept -> ValueType { return Reg::Read<F_DATACOUNT>(); }

private:
    static constexpr std::uintptr_t Address = 0x40018030;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATACOUNT = CortexM3::Field<ValueType, 0, 25>;
};

class STA {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadCCRCFAIL() noexcept -> ValueType { return Reg::Read<F_CCRCFAIL>(); }
    static auto ReadDCRCFAIL() noexcept -> ValueType { return Reg::Read<F_DCRCFAIL>(); }
    static auto ReadCTIMEOUT() noexcept -> ValueType { return Reg::Read<F_CTIMEOUT>(); }
    static auto ReadDTIMEOUT() noexcept -> ValueType { return Reg::Read<F_DTIMEOUT>(); }
    static auto ReadTXUNDERR() noexcept -> ValueType { return Reg::Read<F_TXUNDERR>(); }
    static auto ReadRXOVERR() noexcept -> ValueType { return Reg::Read<F_RXOVERR>(); }
    static auto ReadCMDREND() noexcept -> ValueType { return Reg::Read<F_CMDREND>(); }
    static auto ReadCMDSENT() noexcept -> ValueType { return Reg::Read<F_CMDSENT>(); }
    static auto ReadDATAEND() noexcept -> ValueType { return Reg::Read<F_DATAEND>(); }
    static auto ReadSTBITERR() noexcept -> ValueType { return Reg::Read<F_STBITERR>(); }
    static auto ReadDBCKEND() noexcept -> ValueType { return Reg::Read<F_DBCKEND>(); }
    static auto ReadCMDACT() noexcept -> ValueType { return Reg::Read<F_CMDACT>(); }
    static auto ReadTXACT() noexcept -> ValueType { return Reg::Read<F_TXACT>(); }
    static auto ReadRXACT() noexcept -> ValueType { return Reg::Read<F_RXACT>(); }
    static auto ReadTXFIFOHE() noexcept -> ValueType { return Reg::Read<F_TXFIFOHE>(); }
    static auto ReadRXFIFOHF() noexcept -> ValueType { return Reg::Read<F_RXFIFOHF>(); }
    static auto ReadTXFIFOF() noexcept -> ValueType { return Reg::Read<F_TXFIFOF>(); }
    static auto ReadRXFIFOF() noexcept -> ValueType { return Reg::Read<F_RXFIFOF>(); }
    static auto ReadTXFIFOE() noexcept -> ValueType { return Reg::Read<F_TXFIFOE>(); }
    static auto ReadRXFIFOE() noexcept -> ValueType { return Reg::Read<F_RXFIFOE>(); }
    static auto ReadTXDAVL() noexcept -> ValueType { return Reg::Read<F_TXDAVL>(); }
    static auto ReadRXDAVL() noexcept -> ValueType { return Reg::Read<F_RXDAVL>(); }
    static auto ReadSDIOIT() noexcept -> ValueType { return Reg::Read<F_SDIOIT>(); }
    static auto ReadCEATAEND() noexcept -> ValueType { return Reg::Read<F_CEATAEND>(); }

private:
    static constexpr std::uintptr_t Address = 0x40018034;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CCRCFAIL = CortexM3::Field<ValueType, 0, 1>;
    using F_DCRCFAIL = CortexM3::Field<ValueType, 1, 1>;
    using F_CTIMEOUT = CortexM3::Field<ValueType, 2, 1>;
    using F_DTIMEOUT = CortexM3::Field<ValueType, 3, 1>;
    using F_TXUNDERR = CortexM3::Field<ValueType, 4, 1>;
    using F_RXOVERR = CortexM3::Field<ValueType, 5, 1>;
    using F_CMDREND = CortexM3::Field<ValueType, 6, 1>;
    using F_CMDSENT = CortexM3::Field<ValueType, 7, 1>;
    using F_DATAEND = CortexM3::Field<ValueType, 8, 1>;
    using F_STBITERR = CortexM3::Field<ValueType, 9, 1>;
    using F_DBCKEND = CortexM3::Field<ValueType, 10, 1>;
    using F_CMDACT = CortexM3::Field<ValueType, 11, 1>;
    using F_TXACT = CortexM3::Field<ValueType, 12, 1>;
    using F_RXACT = CortexM3::Field<ValueType, 13, 1>;
    using F_TXFIFOHE = CortexM3::Field<ValueType, 14, 1>;
    using F_RXFIFOHF = CortexM3::Field<ValueType, 15, 1>;
    using F_TXFIFOF = CortexM3::Field<ValueType, 16, 1>;
    using F_RXFIFOF = CortexM3::Field<ValueType, 17, 1>;
    using F_TXFIFOE = CortexM3::Field<ValueType, 18, 1>;
    using F_RXFIFOE = CortexM3::Field<ValueType, 19, 1>;
    using F_TXDAVL = CortexM3::Field<ValueType, 20, 1>;
    using F_RXDAVL = CortexM3::Field<ValueType, 21, 1>;
    using F_SDIOIT = CortexM3::Field<ValueType, 22, 1>;
    using F_CEATAEND = CortexM3::Field<ValueType, 23, 1>;
};

class ICR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCCRCFAILC() noexcept -> ValueType { return Reg::Read<F_CCRCFAILC>(); }
    static void WriteCCRCFAILC(ValueType value) noexcept { Reg::Write<F_CCRCFAILC>(value); }
    static auto ReadDCRCFAILC() noexcept -> ValueType { return Reg::Read<F_DCRCFAILC>(); }
    static void WriteDCRCFAILC(ValueType value) noexcept { Reg::Write<F_DCRCFAILC>(value); }
    static auto ReadCTIMEOUTC() noexcept -> ValueType { return Reg::Read<F_CTIMEOUTC>(); }
    static void WriteCTIMEOUTC(ValueType value) noexcept { Reg::Write<F_CTIMEOUTC>(value); }
    static auto ReadDTIMEOUTC() noexcept -> ValueType { return Reg::Read<F_DTIMEOUTC>(); }
    static void WriteDTIMEOUTC(ValueType value) noexcept { Reg::Write<F_DTIMEOUTC>(value); }
    static auto ReadTXUNDERRC() noexcept -> ValueType { return Reg::Read<F_TXUNDERRC>(); }
    static void WriteTXUNDERRC(ValueType value) noexcept { Reg::Write<F_TXUNDERRC>(value); }
    static auto ReadRXOVERRC() noexcept -> ValueType { return Reg::Read<F_RXOVERRC>(); }
    static void WriteRXOVERRC(ValueType value) noexcept { Reg::Write<F_RXOVERRC>(value); }
    static auto ReadCMDRENDC() noexcept -> ValueType { return Reg::Read<F_CMDRENDC>(); }
    static void WriteCMDRENDC(ValueType value) noexcept { Reg::Write<F_CMDRENDC>(value); }
    static auto ReadCMDSENTC() noexcept -> ValueType { return Reg::Read<F_CMDSENTC>(); }
    static void WriteCMDSENTC(ValueType value) noexcept { Reg::Write<F_CMDSENTC>(value); }
    static auto ReadDATAENDC() noexcept -> ValueType { return Reg::Read<F_DATAENDC>(); }
    static void WriteDATAENDC(ValueType value) noexcept { Reg::Write<F_DATAENDC>(value); }
    static auto ReadSTBITERRC() noexcept -> ValueType { return Reg::Read<F_STBITERRC>(); }
    static void WriteSTBITERRC(ValueType value) noexcept { Reg::Write<F_STBITERRC>(value); }
    static auto ReadDBCKENDC() noexcept -> ValueType { return Reg::Read<F_DBCKENDC>(); }
    static void WriteDBCKENDC(ValueType value) noexcept { Reg::Write<F_DBCKENDC>(value); }
    static auto ReadSDIOITC() noexcept -> ValueType { return Reg::Read<F_SDIOITC>(); }
    static void WriteSDIOITC(ValueType value) noexcept { Reg::Write<F_SDIOITC>(value); }
    static auto ReadCEATAENDC() noexcept -> ValueType { return Reg::Read<F_CEATAENDC>(); }
    static void WriteCEATAENDC(ValueType value) noexcept { Reg::Write<F_CEATAENDC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40018038;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CCRCFAILC = CortexM3::Field<ValueType, 0, 1>;
    using F_DCRCFAILC = CortexM3::Field<ValueType, 1, 1>;
    using F_CTIMEOUTC = CortexM3::Field<ValueType, 2, 1>;
    using F_DTIMEOUTC = CortexM3::Field<ValueType, 3, 1>;
    using F_TXUNDERRC = CortexM3::Field<ValueType, 4, 1>;
    using F_RXOVERRC = CortexM3::Field<ValueType, 5, 1>;
    using F_CMDRENDC = CortexM3::Field<ValueType, 6, 1>;
    using F_CMDSENTC = CortexM3::Field<ValueType, 7, 1>;
    using F_DATAENDC = CortexM3::Field<ValueType, 8, 1>;
    using F_STBITERRC = CortexM3::Field<ValueType, 9, 1>;
    using F_DBCKENDC = CortexM3::Field<ValueType, 10, 1>;
    using F_SDIOITC = CortexM3::Field<ValueType, 22, 1>;
    using F_CEATAENDC = CortexM3::Field<ValueType, 23, 1>;
};

class MASK {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCCRCFAILIE() noexcept -> ValueType { return Reg::Read<F_CCRCFAILIE>(); }
    static void WriteCCRCFAILIE(ValueType value) noexcept { Reg::Write<F_CCRCFAILIE>(value); }
    static auto ReadDCRCFAILIE() noexcept -> ValueType { return Reg::Read<F_DCRCFAILIE>(); }
    static void WriteDCRCFAILIE(ValueType value) noexcept { Reg::Write<F_DCRCFAILIE>(value); }
    static auto ReadCTIMEOUTIE() noexcept -> ValueType { return Reg::Read<F_CTIMEOUTIE>(); }
    static void WriteCTIMEOUTIE(ValueType value) noexcept { Reg::Write<F_CTIMEOUTIE>(value); }
    static auto ReadDTIMEOUTIE() noexcept -> ValueType { return Reg::Read<F_DTIMEOUTIE>(); }
    static void WriteDTIMEOUTIE(ValueType value) noexcept { Reg::Write<F_DTIMEOUTIE>(value); }
    static auto ReadTXUNDERRIE() noexcept -> ValueType { return Reg::Read<F_TXUNDERRIE>(); }
    static void WriteTXUNDERRIE(ValueType value) noexcept { Reg::Write<F_TXUNDERRIE>(value); }
    static auto ReadRXOVERRIE() noexcept -> ValueType { return Reg::Read<F_RXOVERRIE>(); }
    static void WriteRXOVERRIE(ValueType value) noexcept { Reg::Write<F_RXOVERRIE>(value); }
    static auto ReadCMDRENDIE() noexcept -> ValueType { return Reg::Read<F_CMDRENDIE>(); }
    static void WriteCMDRENDIE(ValueType value) noexcept { Reg::Write<F_CMDRENDIE>(value); }
    static auto ReadCMDSENTIE() noexcept -> ValueType { return Reg::Read<F_CMDSENTIE>(); }
    static void WriteCMDSENTIE(ValueType value) noexcept { Reg::Write<F_CMDSENTIE>(value); }
    static auto ReadDATAENDIE() noexcept -> ValueType { return Reg::Read<F_DATAENDIE>(); }
    static void WriteDATAENDIE(ValueType value) noexcept { Reg::Write<F_DATAENDIE>(value); }
    static auto ReadSTBITERRIE() noexcept -> ValueType { return Reg::Read<F_STBITERRIE>(); }
    static void WriteSTBITERRIE(ValueType value) noexcept { Reg::Write<F_STBITERRIE>(value); }
    static auto ReadDBACKENDIE() noexcept -> ValueType { return Reg::Read<F_DBACKENDIE>(); }
    static void WriteDBACKENDIE(ValueType value) noexcept { Reg::Write<F_DBACKENDIE>(value); }
    static auto ReadCMDACTIE() noexcept -> ValueType { return Reg::Read<F_CMDACTIE>(); }
    static void WriteCMDACTIE(ValueType value) noexcept { Reg::Write<F_CMDACTIE>(value); }
    static auto ReadTXACTIE() noexcept -> ValueType { return Reg::Read<F_TXACTIE>(); }
    static void WriteTXACTIE(ValueType value) noexcept { Reg::Write<F_TXACTIE>(value); }
    static auto ReadRXACTIE() noexcept -> ValueType { return Reg::Read<F_RXACTIE>(); }
    static void WriteRXACTIE(ValueType value) noexcept { Reg::Write<F_RXACTIE>(value); }
    static auto ReadTXFIFOHEIE() noexcept -> ValueType { return Reg::Read<F_TXFIFOHEIE>(); }
    static void WriteTXFIFOHEIE(ValueType value) noexcept { Reg::Write<F_TXFIFOHEIE>(value); }
    static auto ReadRXFIFOHFIE() noexcept -> ValueType { return Reg::Read<F_RXFIFOHFIE>(); }
    static void WriteRXFIFOHFIE(ValueType value) noexcept { Reg::Write<F_RXFIFOHFIE>(value); }
    static auto ReadTXFIFOFIE() noexcept -> ValueType { return Reg::Read<F_TXFIFOFIE>(); }
    static void WriteTXFIFOFIE(ValueType value) noexcept { Reg::Write<F_TXFIFOFIE>(value); }
    static auto ReadRXFIFOFIE() noexcept -> ValueType { return Reg::Read<F_RXFIFOFIE>(); }
    static void WriteRXFIFOFIE(ValueType value) noexcept { Reg::Write<F_RXFIFOFIE>(value); }
    static auto ReadTXFIFOEIE() noexcept -> ValueType { return Reg::Read<F_TXFIFOEIE>(); }
    static void WriteTXFIFOEIE(ValueType value) noexcept { Reg::Write<F_TXFIFOEIE>(value); }
    static auto ReadRXFIFOEIE() noexcept -> ValueType { return Reg::Read<F_RXFIFOEIE>(); }
    static void WriteRXFIFOEIE(ValueType value) noexcept { Reg::Write<F_RXFIFOEIE>(value); }
    static auto ReadTXDAVLIE() noexcept -> ValueType { return Reg::Read<F_TXDAVLIE>(); }
    static void WriteTXDAVLIE(ValueType value) noexcept { Reg::Write<F_TXDAVLIE>(value); }
    static auto ReadRXDAVLIE() noexcept -> ValueType { return Reg::Read<F_RXDAVLIE>(); }
    static void WriteRXDAVLIE(ValueType value) noexcept { Reg::Write<F_RXDAVLIE>(value); }
    static auto ReadSDIOITIE() noexcept -> ValueType { return Reg::Read<F_SDIOITIE>(); }
    static void WriteSDIOITIE(ValueType value) noexcept { Reg::Write<F_SDIOITIE>(value); }
    static auto ReadCEATENDIE() noexcept -> ValueType { return Reg::Read<F_CEATENDIE>(); }
    static void WriteCEATENDIE(ValueType value) noexcept { Reg::Write<F_CEATENDIE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001803c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CCRCFAILIE = CortexM3::Field<ValueType, 0, 1>;
    using F_DCRCFAILIE = CortexM3::Field<ValueType, 1, 1>;
    using F_CTIMEOUTIE = CortexM3::Field<ValueType, 2, 1>;
    using F_DTIMEOUTIE = CortexM3::Field<ValueType, 3, 1>;
    using F_TXUNDERRIE = CortexM3::Field<ValueType, 4, 1>;
    using F_RXOVERRIE = CortexM3::Field<ValueType, 5, 1>;
    using F_CMDRENDIE = CortexM3::Field<ValueType, 6, 1>;
    using F_CMDSENTIE = CortexM3::Field<ValueType, 7, 1>;
    using F_DATAENDIE = CortexM3::Field<ValueType, 8, 1>;
    using F_STBITERRIE = CortexM3::Field<ValueType, 9, 1>;
    using F_DBACKENDIE = CortexM3::Field<ValueType, 10, 1>;
    using F_CMDACTIE = CortexM3::Field<ValueType, 11, 1>;
    using F_TXACTIE = CortexM3::Field<ValueType, 12, 1>;
    using F_RXACTIE = CortexM3::Field<ValueType, 13, 1>;
    using F_TXFIFOHEIE = CortexM3::Field<ValueType, 14, 1>;
    using F_RXFIFOHFIE = CortexM3::Field<ValueType, 15, 1>;
    using F_TXFIFOFIE = CortexM3::Field<ValueType, 16, 1>;
    using F_RXFIFOFIE = CortexM3::Field<ValueType, 17, 1>;
    using F_TXFIFOEIE = CortexM3::Field<ValueType, 18, 1>;
    using F_RXFIFOEIE = CortexM3::Field<ValueType, 19, 1>;
    using F_TXDAVLIE = CortexM3::Field<ValueType, 20, 1>;
    using F_RXDAVLIE = CortexM3::Field<ValueType, 21, 1>;
    using F_SDIOITIE = CortexM3::Field<ValueType, 22, 1>;
    using F_CEATENDIE = CortexM3::Field<ValueType, 23, 1>;
};

class FIFOCNT {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadFIF0COUNT() noexcept -> ValueType { return Reg::Read<F_FIF0COUNT>(); }

private:
    static constexpr std::uintptr_t Address = 0x40018048;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FIF0COUNT = CortexM3::Field<ValueType, 0, 24>;
};

class FIFO {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFIFOData() noexcept -> ValueType { return Reg::Read<F_FIFOData>(); }
    static void WriteFIFOData(ValueType value) noexcept { Reg::Write<F_FIFOData>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40018080;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FIFOData = CortexM3::Field<ValueType, 0, 32>;
};

} // namespace STM32F103::SDIO
