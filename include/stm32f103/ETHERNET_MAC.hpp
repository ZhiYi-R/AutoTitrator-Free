#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::ETHERNET_MAC {

class MACCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00008000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRE() noexcept -> ValueType { return Reg::Read<F_RE>(); }
    static void WriteRE(ValueType value) noexcept { Reg::Write<F_RE>(value); }
    static auto ReadTE() noexcept -> ValueType { return Reg::Read<F_TE>(); }
    static void WriteTE(ValueType value) noexcept { Reg::Write<F_TE>(value); }
    static auto ReadDC() noexcept -> ValueType { return Reg::Read<F_DC>(); }
    static void WriteDC(ValueType value) noexcept { Reg::Write<F_DC>(value); }
    static auto ReadBL() noexcept -> ValueType { return Reg::Read<F_BL>(); }
    static void WriteBL(ValueType value) noexcept { Reg::Write<F_BL>(value); }
    static auto ReadAPCS() noexcept -> ValueType { return Reg::Read<F_APCS>(); }
    static void WriteAPCS(ValueType value) noexcept { Reg::Write<F_APCS>(value); }
    static auto ReadRD() noexcept -> ValueType { return Reg::Read<F_RD>(); }
    static void WriteRD(ValueType value) noexcept { Reg::Write<F_RD>(value); }
    static auto ReadIPCO() noexcept -> ValueType { return Reg::Read<F_IPCO>(); }
    static void WriteIPCO(ValueType value) noexcept { Reg::Write<F_IPCO>(value); }
    static auto ReadDM() noexcept -> ValueType { return Reg::Read<F_DM>(); }
    static void WriteDM(ValueType value) noexcept { Reg::Write<F_DM>(value); }
    static auto ReadLM() noexcept -> ValueType { return Reg::Read<F_LM>(); }
    static void WriteLM(ValueType value) noexcept { Reg::Write<F_LM>(value); }
    static auto ReadROD() noexcept -> ValueType { return Reg::Read<F_ROD>(); }
    static void WriteROD(ValueType value) noexcept { Reg::Write<F_ROD>(value); }
    static auto ReadFES() noexcept -> ValueType { return Reg::Read<F_FES>(); }
    static void WriteFES(ValueType value) noexcept { Reg::Write<F_FES>(value); }
    static auto ReadCSD() noexcept -> ValueType { return Reg::Read<F_CSD>(); }
    static void WriteCSD(ValueType value) noexcept { Reg::Write<F_CSD>(value); }
    static auto ReadIFG() noexcept -> ValueType { return Reg::Read<F_IFG>(); }
    static void WriteIFG(ValueType value) noexcept { Reg::Write<F_IFG>(value); }
    static auto ReadJD() noexcept -> ValueType { return Reg::Read<F_JD>(); }
    static void WriteJD(ValueType value) noexcept { Reg::Write<F_JD>(value); }
    static auto ReadWD() noexcept -> ValueType { return Reg::Read<F_WD>(); }
    static void WriteWD(ValueType value) noexcept { Reg::Write<F_WD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RE = CortexM3::Field<ValueType, 2, 1>;
    using F_TE = CortexM3::Field<ValueType, 3, 1>;
    using F_DC = CortexM3::Field<ValueType, 4, 1>;
    using F_BL = CortexM3::Field<ValueType, 5, 2>;
    using F_APCS = CortexM3::Field<ValueType, 7, 1>;
    using F_RD = CortexM3::Field<ValueType, 9, 1>;
    using F_IPCO = CortexM3::Field<ValueType, 10, 1>;
    using F_DM = CortexM3::Field<ValueType, 11, 1>;
    using F_LM = CortexM3::Field<ValueType, 12, 1>;
    using F_ROD = CortexM3::Field<ValueType, 13, 1>;
    using F_FES = CortexM3::Field<ValueType, 14, 1>;
    using F_CSD = CortexM3::Field<ValueType, 16, 1>;
    using F_IFG = CortexM3::Field<ValueType, 17, 3>;
    using F_JD = CortexM3::Field<ValueType, 22, 1>;
    using F_WD = CortexM3::Field<ValueType, 23, 1>;
};

class MACFFR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPM() noexcept -> ValueType { return Reg::Read<F_PM>(); }
    static void WritePM(ValueType value) noexcept { Reg::Write<F_PM>(value); }
    static auto ReadHU() noexcept -> ValueType { return Reg::Read<F_HU>(); }
    static void WriteHU(ValueType value) noexcept { Reg::Write<F_HU>(value); }
    static auto ReadHM() noexcept -> ValueType { return Reg::Read<F_HM>(); }
    static void WriteHM(ValueType value) noexcept { Reg::Write<F_HM>(value); }
    static auto ReadDAIF() noexcept -> ValueType { return Reg::Read<F_DAIF>(); }
    static void WriteDAIF(ValueType value) noexcept { Reg::Write<F_DAIF>(value); }
    static auto ReadPAM() noexcept -> ValueType { return Reg::Read<F_PAM>(); }
    static void WritePAM(ValueType value) noexcept { Reg::Write<F_PAM>(value); }
    static auto ReadBFD() noexcept -> ValueType { return Reg::Read<F_BFD>(); }
    static void WriteBFD(ValueType value) noexcept { Reg::Write<F_BFD>(value); }
    static auto ReadPCF() noexcept -> ValueType { return Reg::Read<F_PCF>(); }
    static void WritePCF(ValueType value) noexcept { Reg::Write<F_PCF>(value); }
    static auto ReadSAIF() noexcept -> ValueType { return Reg::Read<F_SAIF>(); }
    static void WriteSAIF(ValueType value) noexcept { Reg::Write<F_SAIF>(value); }
    static auto ReadSAF() noexcept -> ValueType { return Reg::Read<F_SAF>(); }
    static void WriteSAF(ValueType value) noexcept { Reg::Write<F_SAF>(value); }
    static auto ReadHPF() noexcept -> ValueType { return Reg::Read<F_HPF>(); }
    static void WriteHPF(ValueType value) noexcept { Reg::Write<F_HPF>(value); }
    static auto ReadRA() noexcept -> ValueType { return Reg::Read<F_RA>(); }
    static void WriteRA(ValueType value) noexcept { Reg::Write<F_RA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PM = CortexM3::Field<ValueType, 0, 1>;
    using F_HU = CortexM3::Field<ValueType, 1, 1>;
    using F_HM = CortexM3::Field<ValueType, 2, 1>;
    using F_DAIF = CortexM3::Field<ValueType, 3, 1>;
    using F_PAM = CortexM3::Field<ValueType, 4, 1>;
    using F_BFD = CortexM3::Field<ValueType, 5, 1>;
    using F_PCF = CortexM3::Field<ValueType, 6, 2>;
    using F_SAIF = CortexM3::Field<ValueType, 8, 1>;
    using F_SAF = CortexM3::Field<ValueType, 9, 1>;
    using F_HPF = CortexM3::Field<ValueType, 10, 1>;
    using F_RA = CortexM3::Field<ValueType, 31, 1>;
};

class MACHTHR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadHTH() noexcept -> ValueType { return Reg::Read<F_HTH>(); }
    static void WriteHTH(ValueType value) noexcept { Reg::Write<F_HTH>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_HTH = CortexM3::Field<ValueType, 0, 32>;
};

class MACHTLR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadHTL() noexcept -> ValueType { return Reg::Read<F_HTL>(); }
    static void WriteHTL(ValueType value) noexcept { Reg::Write<F_HTL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002800c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_HTL = CortexM3::Field<ValueType, 0, 32>;
};

class MACMIIAR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMB() noexcept -> ValueType { return Reg::Read<F_MB>(); }
    static void WriteMB(ValueType value) noexcept { Reg::Write<F_MB>(value); }
    static auto ReadMW() noexcept -> ValueType { return Reg::Read<F_MW>(); }
    static void WriteMW(ValueType value) noexcept { Reg::Write<F_MW>(value); }
    static auto ReadCR() noexcept -> ValueType { return Reg::Read<F_CR>(); }
    static void WriteCR(ValueType value) noexcept { Reg::Write<F_CR>(value); }
    static auto ReadMR() noexcept -> ValueType { return Reg::Read<F_MR>(); }
    static void WriteMR(ValueType value) noexcept { Reg::Write<F_MR>(value); }
    static auto ReadPA() noexcept -> ValueType { return Reg::Read<F_PA>(); }
    static void WritePA(ValueType value) noexcept { Reg::Write<F_PA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MB = CortexM3::Field<ValueType, 0, 1>;
    using F_MW = CortexM3::Field<ValueType, 1, 1>;
    using F_CR = CortexM3::Field<ValueType, 2, 3>;
    using F_MR = CortexM3::Field<ValueType, 6, 5>;
    using F_PA = CortexM3::Field<ValueType, 11, 5>;
};

class MACMIIDR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMD() noexcept -> ValueType { return Reg::Read<F_MD>(); }
    static void WriteMD(ValueType value) noexcept { Reg::Write<F_MD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MD = CortexM3::Field<ValueType, 0, 16>;
};

class MACFCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFCB_BPA() noexcept -> ValueType { return Reg::Read<F_FCB_BPA>(); }
    static void WriteFCB_BPA(ValueType value) noexcept { Reg::Write<F_FCB_BPA>(value); }
    static auto ReadTFCE() noexcept -> ValueType { return Reg::Read<F_TFCE>(); }
    static void WriteTFCE(ValueType value) noexcept { Reg::Write<F_TFCE>(value); }
    static auto ReadRFCE() noexcept -> ValueType { return Reg::Read<F_RFCE>(); }
    static void WriteRFCE(ValueType value) noexcept { Reg::Write<F_RFCE>(value); }
    static auto ReadUPFD() noexcept -> ValueType { return Reg::Read<F_UPFD>(); }
    static void WriteUPFD(ValueType value) noexcept { Reg::Write<F_UPFD>(value); }
    static auto ReadPLT() noexcept -> ValueType { return Reg::Read<F_PLT>(); }
    static void WritePLT(ValueType value) noexcept { Reg::Write<F_PLT>(value); }
    static auto ReadZQPD() noexcept -> ValueType { return Reg::Read<F_ZQPD>(); }
    static void WriteZQPD(ValueType value) noexcept { Reg::Write<F_ZQPD>(value); }
    static auto ReadPT() noexcept -> ValueType { return Reg::Read<F_PT>(); }
    static void WritePT(ValueType value) noexcept { Reg::Write<F_PT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028018;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FCB_BPA = CortexM3::Field<ValueType, 0, 1>;
    using F_TFCE = CortexM3::Field<ValueType, 1, 1>;
    using F_RFCE = CortexM3::Field<ValueType, 2, 1>;
    using F_UPFD = CortexM3::Field<ValueType, 3, 1>;
    using F_PLT = CortexM3::Field<ValueType, 4, 2>;
    using F_ZQPD = CortexM3::Field<ValueType, 7, 1>;
    using F_PT = CortexM3::Field<ValueType, 16, 16>;
};

class MACVLANTR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadVLANTI() noexcept -> ValueType { return Reg::Read<F_VLANTI>(); }
    static void WriteVLANTI(ValueType value) noexcept { Reg::Write<F_VLANTI>(value); }
    static auto ReadVLANTC() noexcept -> ValueType { return Reg::Read<F_VLANTC>(); }
    static void WriteVLANTC(ValueType value) noexcept { Reg::Write<F_VLANTC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002801c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_VLANTI = CortexM3::Field<ValueType, 0, 16>;
    using F_VLANTC = CortexM3::Field<ValueType, 16, 1>;
};

class MACRWUFFR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028028;
    using Reg = CortexM3::Register<ValueType, Address>;
};

class MACPMTCSR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPD() noexcept -> ValueType { return Reg::Read<F_PD>(); }
    static void WritePD(ValueType value) noexcept { Reg::Write<F_PD>(value); }
    static auto ReadMPE() noexcept -> ValueType { return Reg::Read<F_MPE>(); }
    static void WriteMPE(ValueType value) noexcept { Reg::Write<F_MPE>(value); }
    static auto ReadWFE() noexcept -> ValueType { return Reg::Read<F_WFE>(); }
    static void WriteWFE(ValueType value) noexcept { Reg::Write<F_WFE>(value); }
    static auto ReadMPR() noexcept -> ValueType { return Reg::Read<F_MPR>(); }
    static void WriteMPR(ValueType value) noexcept { Reg::Write<F_MPR>(value); }
    static auto ReadWFR() noexcept -> ValueType { return Reg::Read<F_WFR>(); }
    static void WriteWFR(ValueType value) noexcept { Reg::Write<F_WFR>(value); }
    static auto ReadGU() noexcept -> ValueType { return Reg::Read<F_GU>(); }
    static void WriteGU(ValueType value) noexcept { Reg::Write<F_GU>(value); }
    static auto ReadWFFRPR() noexcept -> ValueType { return Reg::Read<F_WFFRPR>(); }
    static void WriteWFFRPR(ValueType value) noexcept { Reg::Write<F_WFFRPR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002802c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PD = CortexM3::Field<ValueType, 0, 1>;
    using F_MPE = CortexM3::Field<ValueType, 1, 1>;
    using F_WFE = CortexM3::Field<ValueType, 2, 1>;
    using F_MPR = CortexM3::Field<ValueType, 5, 1>;
    using F_WFR = CortexM3::Field<ValueType, 6, 1>;
    using F_GU = CortexM3::Field<ValueType, 9, 1>;
    using F_WFFRPR = CortexM3::Field<ValueType, 31, 1>;
};

class MACSR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPMTS() noexcept -> ValueType { return Reg::Read<F_PMTS>(); }
    static void WritePMTS(ValueType value) noexcept { Reg::Write<F_PMTS>(value); }
    static auto ReadMMCS() noexcept -> ValueType { return Reg::Read<F_MMCS>(); }
    static void WriteMMCS(ValueType value) noexcept { Reg::Write<F_MMCS>(value); }
    static auto ReadMMCRS() noexcept -> ValueType { return Reg::Read<F_MMCRS>(); }
    static void WriteMMCRS(ValueType value) noexcept { Reg::Write<F_MMCRS>(value); }
    static auto ReadMMCTS() noexcept -> ValueType { return Reg::Read<F_MMCTS>(); }
    static void WriteMMCTS(ValueType value) noexcept { Reg::Write<F_MMCTS>(value); }
    static auto ReadTSTS() noexcept -> ValueType { return Reg::Read<F_TSTS>(); }
    static void WriteTSTS(ValueType value) noexcept { Reg::Write<F_TSTS>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028038;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PMTS = CortexM3::Field<ValueType, 3, 1>;
    using F_MMCS = CortexM3::Field<ValueType, 4, 1>;
    using F_MMCRS = CortexM3::Field<ValueType, 5, 1>;
    using F_MMCTS = CortexM3::Field<ValueType, 6, 1>;
    using F_TSTS = CortexM3::Field<ValueType, 9, 1>;
};

class MACIMR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPMTIM() noexcept -> ValueType { return Reg::Read<F_PMTIM>(); }
    static void WritePMTIM(ValueType value) noexcept { Reg::Write<F_PMTIM>(value); }
    static auto ReadTSTIM() noexcept -> ValueType { return Reg::Read<F_TSTIM>(); }
    static void WriteTSTIM(ValueType value) noexcept { Reg::Write<F_TSTIM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002803c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PMTIM = CortexM3::Field<ValueType, 3, 1>;
    using F_TSTIM = CortexM3::Field<ValueType, 9, 1>;
};

class MACA0HR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0010FFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMACA0H() noexcept -> ValueType { return Reg::Read<F_MACA0H>(); }
    static void WriteMACA0H(ValueType value) noexcept { Reg::Write<F_MACA0H>(value); }
    static auto ReadMO() noexcept -> ValueType { return Reg::Read<F_MO>(); }

private:
    static constexpr std::uintptr_t Address = 0x40028040;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MACA0H = CortexM3::Field<ValueType, 0, 16>;
    using F_MO = CortexM3::Field<ValueType, 31, 1>;
};

class MACA0LR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFFFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMACA0L() noexcept -> ValueType { return Reg::Read<F_MACA0L>(); }
    static void WriteMACA0L(ValueType value) noexcept { Reg::Write<F_MACA0L>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028044;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MACA0L = CortexM3::Field<ValueType, 0, 32>;
};

class MACA1HR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0000FFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMACA1H() noexcept -> ValueType { return Reg::Read<F_MACA1H>(); }
    static void WriteMACA1H(ValueType value) noexcept { Reg::Write<F_MACA1H>(value); }
    static auto ReadMBC() noexcept -> ValueType { return Reg::Read<F_MBC>(); }
    static void WriteMBC(ValueType value) noexcept { Reg::Write<F_MBC>(value); }
    static auto ReadSA() noexcept -> ValueType { return Reg::Read<F_SA>(); }
    static void WriteSA(ValueType value) noexcept { Reg::Write<F_SA>(value); }
    static auto ReadAE() noexcept -> ValueType { return Reg::Read<F_AE>(); }
    static void WriteAE(ValueType value) noexcept { Reg::Write<F_AE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028048;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MACA1H = CortexM3::Field<ValueType, 0, 16>;
    using F_MBC = CortexM3::Field<ValueType, 24, 6>;
    using F_SA = CortexM3::Field<ValueType, 30, 1>;
    using F_AE = CortexM3::Field<ValueType, 31, 1>;
};

class MACA1LR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFFFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMACA1L() noexcept -> ValueType { return Reg::Read<F_MACA1L>(); }
    static void WriteMACA1L(ValueType value) noexcept { Reg::Write<F_MACA1L>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002804c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MACA1L = CortexM3::Field<ValueType, 0, 32>;
};

class MACA2HR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000050;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadETH_MACA2HR() noexcept -> ValueType { return Reg::Read<F_ETH_MACA2HR>(); }
    static void WriteETH_MACA2HR(ValueType value) noexcept { Reg::Write<F_ETH_MACA2HR>(value); }
    static auto ReadMBC() noexcept -> ValueType { return Reg::Read<F_MBC>(); }
    static void WriteMBC(ValueType value) noexcept { Reg::Write<F_MBC>(value); }
    static auto ReadSA() noexcept -> ValueType { return Reg::Read<F_SA>(); }
    static void WriteSA(ValueType value) noexcept { Reg::Write<F_SA>(value); }
    static auto ReadAE() noexcept -> ValueType { return Reg::Read<F_AE>(); }
    static void WriteAE(ValueType value) noexcept { Reg::Write<F_AE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028050;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ETH_MACA2HR = CortexM3::Field<ValueType, 0, 16>;
    using F_MBC = CortexM3::Field<ValueType, 24, 6>;
    using F_SA = CortexM3::Field<ValueType, 30, 1>;
    using F_AE = CortexM3::Field<ValueType, 31, 1>;
};

class MACA2LR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFFFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMACA2L() noexcept -> ValueType { return Reg::Read<F_MACA2L>(); }
    static void WriteMACA2L(ValueType value) noexcept { Reg::Write<F_MACA2L>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028054;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MACA2L = CortexM3::Field<ValueType, 0, 31>;
};

class MACA3HR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0000FFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMACA3H() noexcept -> ValueType { return Reg::Read<F_MACA3H>(); }
    static void WriteMACA3H(ValueType value) noexcept { Reg::Write<F_MACA3H>(value); }
    static auto ReadMBC() noexcept -> ValueType { return Reg::Read<F_MBC>(); }
    static void WriteMBC(ValueType value) noexcept { Reg::Write<F_MBC>(value); }
    static auto ReadSA() noexcept -> ValueType { return Reg::Read<F_SA>(); }
    static void WriteSA(ValueType value) noexcept { Reg::Write<F_SA>(value); }
    static auto ReadAE() noexcept -> ValueType { return Reg::Read<F_AE>(); }
    static void WriteAE(ValueType value) noexcept { Reg::Write<F_AE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40028058;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MACA3H = CortexM3::Field<ValueType, 0, 16>;
    using F_MBC = CortexM3::Field<ValueType, 24, 6>;
    using F_SA = CortexM3::Field<ValueType, 30, 1>;
    using F_AE = CortexM3::Field<ValueType, 31, 1>;
};

class MACA3LR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0xFFFFFFFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMBCA3L() noexcept -> ValueType { return Reg::Read<F_MBCA3L>(); }
    static void WriteMBCA3L(ValueType value) noexcept { Reg::Write<F_MBCA3L>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002805c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MBCA3L = CortexM3::Field<ValueType, 0, 32>;
};

} // namespace STM32F103::ETHERNET_MAC
