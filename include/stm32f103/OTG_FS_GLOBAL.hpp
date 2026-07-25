#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::OTG_FS_GLOBAL {

class FS_GOTGCTL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000800;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSRQSCS() noexcept -> ValueType { return Reg::Read<F_SRQSCS>(); }
    static auto ReadSRQ() noexcept -> ValueType { return Reg::Read<F_SRQ>(); }
    static void WriteSRQ(ValueType value) noexcept { Reg::Write<F_SRQ>(value); }
    static auto ReadHNGSCS() noexcept -> ValueType { return Reg::Read<F_HNGSCS>(); }
    static auto ReadHNPRQ() noexcept -> ValueType { return Reg::Read<F_HNPRQ>(); }
    static void WriteHNPRQ(ValueType value) noexcept { Reg::Write<F_HNPRQ>(value); }
    static auto ReadHSHNPEN() noexcept -> ValueType { return Reg::Read<F_HSHNPEN>(); }
    static void WriteHSHNPEN(ValueType value) noexcept { Reg::Write<F_HSHNPEN>(value); }
    static auto ReadDHNPEN() noexcept -> ValueType { return Reg::Read<F_DHNPEN>(); }
    static void WriteDHNPEN(ValueType value) noexcept { Reg::Write<F_DHNPEN>(value); }
    static auto ReadCIDSTS() noexcept -> ValueType { return Reg::Read<F_CIDSTS>(); }
    static auto ReadDBCT() noexcept -> ValueType { return Reg::Read<F_DBCT>(); }
    static auto ReadASVLD() noexcept -> ValueType { return Reg::Read<F_ASVLD>(); }
    static auto ReadBSVLD() noexcept -> ValueType { return Reg::Read<F_BSVLD>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SRQSCS = CortexM3::Field<ValueType, 0, 1>;
    using F_SRQ = CortexM3::Field<ValueType, 1, 1>;
    using F_HNGSCS = CortexM3::Field<ValueType, 8, 1>;
    using F_HNPRQ = CortexM3::Field<ValueType, 9, 1>;
    using F_HSHNPEN = CortexM3::Field<ValueType, 10, 1>;
    using F_DHNPEN = CortexM3::Field<ValueType, 11, 1>;
    using F_CIDSTS = CortexM3::Field<ValueType, 16, 1>;
    using F_DBCT = CortexM3::Field<ValueType, 17, 1>;
    using F_ASVLD = CortexM3::Field<ValueType, 18, 1>;
    using F_BSVLD = CortexM3::Field<ValueType, 19, 1>;
};

class FS_GOTGINT {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSEDET() noexcept -> ValueType { return Reg::Read<F_SEDET>(); }
    static void WriteSEDET(ValueType value) noexcept { Reg::Write<F_SEDET>(value); }
    static auto ReadSRSSCHG() noexcept -> ValueType { return Reg::Read<F_SRSSCHG>(); }
    static void WriteSRSSCHG(ValueType value) noexcept { Reg::Write<F_SRSSCHG>(value); }
    static auto ReadHNSSCHG() noexcept -> ValueType { return Reg::Read<F_HNSSCHG>(); }
    static void WriteHNSSCHG(ValueType value) noexcept { Reg::Write<F_HNSSCHG>(value); }
    static auto ReadHNGDET() noexcept -> ValueType { return Reg::Read<F_HNGDET>(); }
    static void WriteHNGDET(ValueType value) noexcept { Reg::Write<F_HNGDET>(value); }
    static auto ReadADTOCHG() noexcept -> ValueType { return Reg::Read<F_ADTOCHG>(); }
    static void WriteADTOCHG(ValueType value) noexcept { Reg::Write<F_ADTOCHG>(value); }
    static auto ReadDBCDNE() noexcept -> ValueType { return Reg::Read<F_DBCDNE>(); }
    static void WriteDBCDNE(ValueType value) noexcept { Reg::Write<F_DBCDNE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SEDET = CortexM3::Field<ValueType, 2, 1>;
    using F_SRSSCHG = CortexM3::Field<ValueType, 8, 1>;
    using F_HNSSCHG = CortexM3::Field<ValueType, 9, 1>;
    using F_HNGDET = CortexM3::Field<ValueType, 17, 1>;
    using F_ADTOCHG = CortexM3::Field<ValueType, 18, 1>;
    using F_DBCDNE = CortexM3::Field<ValueType, 19, 1>;
};

class FS_GAHBCFG {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadGINT() noexcept -> ValueType { return Reg::Read<F_GINT>(); }
    static void WriteGINT(ValueType value) noexcept { Reg::Write<F_GINT>(value); }
    static auto ReadTXFELVL() noexcept -> ValueType { return Reg::Read<F_TXFELVL>(); }
    static void WriteTXFELVL(ValueType value) noexcept { Reg::Write<F_TXFELVL>(value); }
    static auto ReadPTXFELVL() noexcept -> ValueType { return Reg::Read<F_PTXFELVL>(); }
    static void WritePTXFELVL(ValueType value) noexcept { Reg::Write<F_PTXFELVL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_GINT = CortexM3::Field<ValueType, 0, 1>;
    using F_TXFELVL = CortexM3::Field<ValueType, 7, 1>;
    using F_PTXFELVL = CortexM3::Field<ValueType, 8, 1>;
};

class FS_GUSBCFG {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000A00;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTOCAL() noexcept -> ValueType { return Reg::Read<F_TOCAL>(); }
    static void WriteTOCAL(ValueType value) noexcept { Reg::Write<F_TOCAL>(value); }
    static void WritePHYSEL(ValueType value) noexcept { Reg::Write<F_PHYSEL>(value); }
    static auto ReadSRPCAP() noexcept -> ValueType { return Reg::Read<F_SRPCAP>(); }
    static void WriteSRPCAP(ValueType value) noexcept { Reg::Write<F_SRPCAP>(value); }
    static auto ReadHNPCAP() noexcept -> ValueType { return Reg::Read<F_HNPCAP>(); }
    static void WriteHNPCAP(ValueType value) noexcept { Reg::Write<F_HNPCAP>(value); }
    static auto ReadTRDT() noexcept -> ValueType { return Reg::Read<F_TRDT>(); }
    static void WriteTRDT(ValueType value) noexcept { Reg::Write<F_TRDT>(value); }
    static auto ReadFHMOD() noexcept -> ValueType { return Reg::Read<F_FHMOD>(); }
    static void WriteFHMOD(ValueType value) noexcept { Reg::Write<F_FHMOD>(value); }
    static auto ReadFDMOD() noexcept -> ValueType { return Reg::Read<F_FDMOD>(); }
    static void WriteFDMOD(ValueType value) noexcept { Reg::Write<F_FDMOD>(value); }
    static auto ReadCTXPKT() noexcept -> ValueType { return Reg::Read<F_CTXPKT>(); }
    static void WriteCTXPKT(ValueType value) noexcept { Reg::Write<F_CTXPKT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x5000000c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TOCAL = CortexM3::Field<ValueType, 0, 3>;
    using F_PHYSEL = CortexM3::Field<ValueType, 6, 1>;
    using F_SRPCAP = CortexM3::Field<ValueType, 8, 1>;
    using F_HNPCAP = CortexM3::Field<ValueType, 9, 1>;
    using F_TRDT = CortexM3::Field<ValueType, 10, 4>;
    using F_FHMOD = CortexM3::Field<ValueType, 29, 1>;
    using F_FDMOD = CortexM3::Field<ValueType, 30, 1>;
    using F_CTXPKT = CortexM3::Field<ValueType, 31, 1>;
};

class FS_GRSTCTL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x20000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCSRST() noexcept -> ValueType { return Reg::Read<F_CSRST>(); }
    static void WriteCSRST(ValueType value) noexcept { Reg::Write<F_CSRST>(value); }
    static auto ReadHSRST() noexcept -> ValueType { return Reg::Read<F_HSRST>(); }
    static void WriteHSRST(ValueType value) noexcept { Reg::Write<F_HSRST>(value); }
    static auto ReadFCRST() noexcept -> ValueType { return Reg::Read<F_FCRST>(); }
    static void WriteFCRST(ValueType value) noexcept { Reg::Write<F_FCRST>(value); }
    static auto ReadRXFFLSH() noexcept -> ValueType { return Reg::Read<F_RXFFLSH>(); }
    static void WriteRXFFLSH(ValueType value) noexcept { Reg::Write<F_RXFFLSH>(value); }
    static auto ReadTXFFLSH() noexcept -> ValueType { return Reg::Read<F_TXFFLSH>(); }
    static void WriteTXFFLSH(ValueType value) noexcept { Reg::Write<F_TXFFLSH>(value); }
    static auto ReadTXFNUM() noexcept -> ValueType { return Reg::Read<F_TXFNUM>(); }
    static void WriteTXFNUM(ValueType value) noexcept { Reg::Write<F_TXFNUM>(value); }
    static auto ReadAHBIDL() noexcept -> ValueType { return Reg::Read<F_AHBIDL>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CSRST = CortexM3::Field<ValueType, 0, 1>;
    using F_HSRST = CortexM3::Field<ValueType, 1, 1>;
    using F_FCRST = CortexM3::Field<ValueType, 2, 1>;
    using F_RXFFLSH = CortexM3::Field<ValueType, 4, 1>;
    using F_TXFFLSH = CortexM3::Field<ValueType, 5, 1>;
    using F_TXFNUM = CortexM3::Field<ValueType, 6, 5>;
    using F_AHBIDL = CortexM3::Field<ValueType, 31, 1>;
};

class FS_GINTSTS {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x04000020;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCMOD() noexcept -> ValueType { return Reg::Read<F_CMOD>(); }
    static auto ReadMMIS() noexcept -> ValueType { return Reg::Read<F_MMIS>(); }
    static void WriteMMIS(ValueType value) noexcept { Reg::Write<F_MMIS>(value); }
    static auto ReadOTGINT() noexcept -> ValueType { return Reg::Read<F_OTGINT>(); }
    static auto ReadSOF() noexcept -> ValueType { return Reg::Read<F_SOF>(); }
    static void WriteSOF(ValueType value) noexcept { Reg::Write<F_SOF>(value); }
    static auto ReadRXFLVL() noexcept -> ValueType { return Reg::Read<F_RXFLVL>(); }
    static auto ReadNPTXFE() noexcept -> ValueType { return Reg::Read<F_NPTXFE>(); }
    static auto ReadGINAKEFF() noexcept -> ValueType { return Reg::Read<F_GINAKEFF>(); }
    static auto ReadGOUTNAKEFF() noexcept -> ValueType { return Reg::Read<F_GOUTNAKEFF>(); }
    static auto ReadESUSP() noexcept -> ValueType { return Reg::Read<F_ESUSP>(); }
    static void WriteESUSP(ValueType value) noexcept { Reg::Write<F_ESUSP>(value); }
    static auto ReadUSBSUSP() noexcept -> ValueType { return Reg::Read<F_USBSUSP>(); }
    static void WriteUSBSUSP(ValueType value) noexcept { Reg::Write<F_USBSUSP>(value); }
    static auto ReadUSBRST() noexcept -> ValueType { return Reg::Read<F_USBRST>(); }
    static void WriteUSBRST(ValueType value) noexcept { Reg::Write<F_USBRST>(value); }
    static auto ReadENUMDNE() noexcept -> ValueType { return Reg::Read<F_ENUMDNE>(); }
    static void WriteENUMDNE(ValueType value) noexcept { Reg::Write<F_ENUMDNE>(value); }
    static auto ReadISOODRP() noexcept -> ValueType { return Reg::Read<F_ISOODRP>(); }
    static void WriteISOODRP(ValueType value) noexcept { Reg::Write<F_ISOODRP>(value); }
    static auto ReadEOPF() noexcept -> ValueType { return Reg::Read<F_EOPF>(); }
    static void WriteEOPF(ValueType value) noexcept { Reg::Write<F_EOPF>(value); }
    static auto ReadIEPINT() noexcept -> ValueType { return Reg::Read<F_IEPINT>(); }
    static auto ReadOEPINT() noexcept -> ValueType { return Reg::Read<F_OEPINT>(); }
    static auto ReadIISOIXFR() noexcept -> ValueType { return Reg::Read<F_IISOIXFR>(); }
    static void WriteIISOIXFR(ValueType value) noexcept { Reg::Write<F_IISOIXFR>(value); }
    static auto ReadIPXFR_INCOMPISOOUT() noexcept -> ValueType { return Reg::Read<F_IPXFR_INCOMPISOOUT>(); }
    static void WriteIPXFR_INCOMPISOOUT(ValueType value) noexcept { Reg::Write<F_IPXFR_INCOMPISOOUT>(value); }
    static auto ReadHPRTINT() noexcept -> ValueType { return Reg::Read<F_HPRTINT>(); }
    static auto ReadHCINT() noexcept -> ValueType { return Reg::Read<F_HCINT>(); }
    static auto ReadPTXFE() noexcept -> ValueType { return Reg::Read<F_PTXFE>(); }
    static auto ReadCIDSCHG() noexcept -> ValueType { return Reg::Read<F_CIDSCHG>(); }
    static void WriteCIDSCHG(ValueType value) noexcept { Reg::Write<F_CIDSCHG>(value); }
    static auto ReadDISCINT() noexcept -> ValueType { return Reg::Read<F_DISCINT>(); }
    static void WriteDISCINT(ValueType value) noexcept { Reg::Write<F_DISCINT>(value); }
    static auto ReadSRQINT() noexcept -> ValueType { return Reg::Read<F_SRQINT>(); }
    static void WriteSRQINT(ValueType value) noexcept { Reg::Write<F_SRQINT>(value); }
    static auto ReadWKUPINT() noexcept -> ValueType { return Reg::Read<F_WKUPINT>(); }
    static void WriteWKUPINT(ValueType value) noexcept { Reg::Write<F_WKUPINT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CMOD = CortexM3::Field<ValueType, 0, 1>;
    using F_MMIS = CortexM3::Field<ValueType, 1, 1>;
    using F_OTGINT = CortexM3::Field<ValueType, 2, 1>;
    using F_SOF = CortexM3::Field<ValueType, 3, 1>;
    using F_RXFLVL = CortexM3::Field<ValueType, 4, 1>;
    using F_NPTXFE = CortexM3::Field<ValueType, 5, 1>;
    using F_GINAKEFF = CortexM3::Field<ValueType, 6, 1>;
    using F_GOUTNAKEFF = CortexM3::Field<ValueType, 7, 1>;
    using F_ESUSP = CortexM3::Field<ValueType, 10, 1>;
    using F_USBSUSP = CortexM3::Field<ValueType, 11, 1>;
    using F_USBRST = CortexM3::Field<ValueType, 12, 1>;
    using F_ENUMDNE = CortexM3::Field<ValueType, 13, 1>;
    using F_ISOODRP = CortexM3::Field<ValueType, 14, 1>;
    using F_EOPF = CortexM3::Field<ValueType, 15, 1>;
    using F_IEPINT = CortexM3::Field<ValueType, 18, 1>;
    using F_OEPINT = CortexM3::Field<ValueType, 19, 1>;
    using F_IISOIXFR = CortexM3::Field<ValueType, 20, 1>;
    using F_IPXFR_INCOMPISOOUT = CortexM3::Field<ValueType, 21, 1>;
    using F_HPRTINT = CortexM3::Field<ValueType, 24, 1>;
    using F_HCINT = CortexM3::Field<ValueType, 25, 1>;
    using F_PTXFE = CortexM3::Field<ValueType, 26, 1>;
    using F_CIDSCHG = CortexM3::Field<ValueType, 28, 1>;
    using F_DISCINT = CortexM3::Field<ValueType, 29, 1>;
    using F_SRQINT = CortexM3::Field<ValueType, 30, 1>;
    using F_WKUPINT = CortexM3::Field<ValueType, 31, 1>;
};

class FS_GINTMSK {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMMISM() noexcept -> ValueType { return Reg::Read<F_MMISM>(); }
    static void WriteMMISM(ValueType value) noexcept { Reg::Write<F_MMISM>(value); }
    static auto ReadOTGINT() noexcept -> ValueType { return Reg::Read<F_OTGINT>(); }
    static void WriteOTGINT(ValueType value) noexcept { Reg::Write<F_OTGINT>(value); }
    static auto ReadSOFM() noexcept -> ValueType { return Reg::Read<F_SOFM>(); }
    static void WriteSOFM(ValueType value) noexcept { Reg::Write<F_SOFM>(value); }
    static auto ReadRXFLVLM() noexcept -> ValueType { return Reg::Read<F_RXFLVLM>(); }
    static void WriteRXFLVLM(ValueType value) noexcept { Reg::Write<F_RXFLVLM>(value); }
    static auto ReadNPTXFEM() noexcept -> ValueType { return Reg::Read<F_NPTXFEM>(); }
    static void WriteNPTXFEM(ValueType value) noexcept { Reg::Write<F_NPTXFEM>(value); }
    static auto ReadGINAKEFFM() noexcept -> ValueType { return Reg::Read<F_GINAKEFFM>(); }
    static void WriteGINAKEFFM(ValueType value) noexcept { Reg::Write<F_GINAKEFFM>(value); }
    static auto ReadGONAKEFFM() noexcept -> ValueType { return Reg::Read<F_GONAKEFFM>(); }
    static void WriteGONAKEFFM(ValueType value) noexcept { Reg::Write<F_GONAKEFFM>(value); }
    static auto ReadESUSPM() noexcept -> ValueType { return Reg::Read<F_ESUSPM>(); }
    static void WriteESUSPM(ValueType value) noexcept { Reg::Write<F_ESUSPM>(value); }
    static auto ReadUSBSUSPM() noexcept -> ValueType { return Reg::Read<F_USBSUSPM>(); }
    static void WriteUSBSUSPM(ValueType value) noexcept { Reg::Write<F_USBSUSPM>(value); }
    static auto ReadUSBRST() noexcept -> ValueType { return Reg::Read<F_USBRST>(); }
    static void WriteUSBRST(ValueType value) noexcept { Reg::Write<F_USBRST>(value); }
    static auto ReadENUMDNEM() noexcept -> ValueType { return Reg::Read<F_ENUMDNEM>(); }
    static void WriteENUMDNEM(ValueType value) noexcept { Reg::Write<F_ENUMDNEM>(value); }
    static auto ReadISOODRPM() noexcept -> ValueType { return Reg::Read<F_ISOODRPM>(); }
    static void WriteISOODRPM(ValueType value) noexcept { Reg::Write<F_ISOODRPM>(value); }
    static auto ReadEOPFM() noexcept -> ValueType { return Reg::Read<F_EOPFM>(); }
    static void WriteEOPFM(ValueType value) noexcept { Reg::Write<F_EOPFM>(value); }
    static auto ReadEPMISM() noexcept -> ValueType { return Reg::Read<F_EPMISM>(); }
    static void WriteEPMISM(ValueType value) noexcept { Reg::Write<F_EPMISM>(value); }
    static auto ReadIEPINT() noexcept -> ValueType { return Reg::Read<F_IEPINT>(); }
    static void WriteIEPINT(ValueType value) noexcept { Reg::Write<F_IEPINT>(value); }
    static auto ReadOEPINT() noexcept -> ValueType { return Reg::Read<F_OEPINT>(); }
    static void WriteOEPINT(ValueType value) noexcept { Reg::Write<F_OEPINT>(value); }
    static auto ReadIISOIXFRM() noexcept -> ValueType { return Reg::Read<F_IISOIXFRM>(); }
    static void WriteIISOIXFRM(ValueType value) noexcept { Reg::Write<F_IISOIXFRM>(value); }
    static auto ReadIPXFRM_IISOOXFRM() noexcept -> ValueType { return Reg::Read<F_IPXFRM_IISOOXFRM>(); }
    static void WriteIPXFRM_IISOOXFRM(ValueType value) noexcept { Reg::Write<F_IPXFRM_IISOOXFRM>(value); }
    static auto ReadPRTIM() noexcept -> ValueType { return Reg::Read<F_PRTIM>(); }
    static auto ReadHCIM() noexcept -> ValueType { return Reg::Read<F_HCIM>(); }
    static void WriteHCIM(ValueType value) noexcept { Reg::Write<F_HCIM>(value); }
    static auto ReadPTXFEM() noexcept -> ValueType { return Reg::Read<F_PTXFEM>(); }
    static void WritePTXFEM(ValueType value) noexcept { Reg::Write<F_PTXFEM>(value); }
    static auto ReadCIDSCHGM() noexcept -> ValueType { return Reg::Read<F_CIDSCHGM>(); }
    static void WriteCIDSCHGM(ValueType value) noexcept { Reg::Write<F_CIDSCHGM>(value); }
    static auto ReadDISCINT() noexcept -> ValueType { return Reg::Read<F_DISCINT>(); }
    static void WriteDISCINT(ValueType value) noexcept { Reg::Write<F_DISCINT>(value); }
    static auto ReadSRQIM() noexcept -> ValueType { return Reg::Read<F_SRQIM>(); }
    static void WriteSRQIM(ValueType value) noexcept { Reg::Write<F_SRQIM>(value); }
    static auto ReadWUIM() noexcept -> ValueType { return Reg::Read<F_WUIM>(); }
    static void WriteWUIM(ValueType value) noexcept { Reg::Write<F_WUIM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000018;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MMISM = CortexM3::Field<ValueType, 1, 1>;
    using F_OTGINT = CortexM3::Field<ValueType, 2, 1>;
    using F_SOFM = CortexM3::Field<ValueType, 3, 1>;
    using F_RXFLVLM = CortexM3::Field<ValueType, 4, 1>;
    using F_NPTXFEM = CortexM3::Field<ValueType, 5, 1>;
    using F_GINAKEFFM = CortexM3::Field<ValueType, 6, 1>;
    using F_GONAKEFFM = CortexM3::Field<ValueType, 7, 1>;
    using F_ESUSPM = CortexM3::Field<ValueType, 10, 1>;
    using F_USBSUSPM = CortexM3::Field<ValueType, 11, 1>;
    using F_USBRST = CortexM3::Field<ValueType, 12, 1>;
    using F_ENUMDNEM = CortexM3::Field<ValueType, 13, 1>;
    using F_ISOODRPM = CortexM3::Field<ValueType, 14, 1>;
    using F_EOPFM = CortexM3::Field<ValueType, 15, 1>;
    using F_EPMISM = CortexM3::Field<ValueType, 17, 1>;
    using F_IEPINT = CortexM3::Field<ValueType, 18, 1>;
    using F_OEPINT = CortexM3::Field<ValueType, 19, 1>;
    using F_IISOIXFRM = CortexM3::Field<ValueType, 20, 1>;
    using F_IPXFRM_IISOOXFRM = CortexM3::Field<ValueType, 21, 1>;
    using F_PRTIM = CortexM3::Field<ValueType, 24, 1>;
    using F_HCIM = CortexM3::Field<ValueType, 25, 1>;
    using F_PTXFEM = CortexM3::Field<ValueType, 26, 1>;
    using F_CIDSCHGM = CortexM3::Field<ValueType, 28, 1>;
    using F_DISCINT = CortexM3::Field<ValueType, 29, 1>;
    using F_SRQIM = CortexM3::Field<ValueType, 30, 1>;
    using F_WUIM = CortexM3::Field<ValueType, 31, 1>;
};

class FS_GRXSTSR_Device {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadEPNUM() noexcept -> ValueType { return Reg::Read<F_EPNUM>(); }
    static auto ReadBCNT() noexcept -> ValueType { return Reg::Read<F_BCNT>(); }
    static auto ReadDPID() noexcept -> ValueType { return Reg::Read<F_DPID>(); }
    static auto ReadPKTSTS() noexcept -> ValueType { return Reg::Read<F_PKTSTS>(); }
    static auto ReadFRMNUM() noexcept -> ValueType { return Reg::Read<F_FRMNUM>(); }

private:
    static constexpr std::uintptr_t Address = 0x5000001c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EPNUM = CortexM3::Field<ValueType, 0, 4>;
    using F_BCNT = CortexM3::Field<ValueType, 4, 11>;
    using F_DPID = CortexM3::Field<ValueType, 15, 2>;
    using F_PKTSTS = CortexM3::Field<ValueType, 17, 4>;
    using F_FRMNUM = CortexM3::Field<ValueType, 21, 4>;
};

class FS_GRXSTSR_Host {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadEPNUM() noexcept -> ValueType { return Reg::Read<F_EPNUM>(); }
    static auto ReadBCNT() noexcept -> ValueType { return Reg::Read<F_BCNT>(); }
    static auto ReadDPID() noexcept -> ValueType { return Reg::Read<F_DPID>(); }
    static auto ReadPKTSTS() noexcept -> ValueType { return Reg::Read<F_PKTSTS>(); }
    static auto ReadFRMNUM() noexcept -> ValueType { return Reg::Read<F_FRMNUM>(); }

private:
    static constexpr std::uintptr_t Address = 0x5000001c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EPNUM = CortexM3::Field<ValueType, 0, 4>;
    using F_BCNT = CortexM3::Field<ValueType, 4, 11>;
    using F_DPID = CortexM3::Field<ValueType, 15, 2>;
    using F_PKTSTS = CortexM3::Field<ValueType, 17, 4>;
    using F_FRMNUM = CortexM3::Field<ValueType, 21, 4>;
};

class FS_GRXFSIZ {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000200;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRXFD() noexcept -> ValueType { return Reg::Read<F_RXFD>(); }
    static void WriteRXFD(ValueType value) noexcept { Reg::Write<F_RXFD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000024;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RXFD = CortexM3::Field<ValueType, 0, 16>;
};

class FS_GNPTXFSIZ_Device {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000200;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTX0FSA() noexcept -> ValueType { return Reg::Read<F_TX0FSA>(); }
    static void WriteTX0FSA(ValueType value) noexcept { Reg::Write<F_TX0FSA>(value); }
    static auto ReadTX0FD() noexcept -> ValueType { return Reg::Read<F_TX0FD>(); }
    static void WriteTX0FD(ValueType value) noexcept { Reg::Write<F_TX0FD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000028;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TX0FSA = CortexM3::Field<ValueType, 0, 16>;
    using F_TX0FD = CortexM3::Field<ValueType, 16, 16>;
};

class FS_GNPTXFSIZ_Host {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000200;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadNPTXFSA() noexcept -> ValueType { return Reg::Read<F_NPTXFSA>(); }
    static void WriteNPTXFSA(ValueType value) noexcept { Reg::Write<F_NPTXFSA>(value); }
    static auto ReadNPTXFD() noexcept -> ValueType { return Reg::Read<F_NPTXFD>(); }
    static void WriteNPTXFD(ValueType value) noexcept { Reg::Write<F_NPTXFD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000028;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NPTXFSA = CortexM3::Field<ValueType, 0, 16>;
    using F_NPTXFD = CortexM3::Field<ValueType, 16, 16>;
};

class FS_GNPTXSTS {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00080200;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadNPTXFSAV() noexcept -> ValueType { return Reg::Read<F_NPTXFSAV>(); }
    static auto ReadNPTQXSAV() noexcept -> ValueType { return Reg::Read<F_NPTQXSAV>(); }
    static auto ReadNPTXQTOP() noexcept -> ValueType { return Reg::Read<F_NPTXQTOP>(); }

private:
    static constexpr std::uintptr_t Address = 0x5000002c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_NPTXFSAV = CortexM3::Field<ValueType, 0, 16>;
    using F_NPTQXSAV = CortexM3::Field<ValueType, 16, 8>;
    using F_NPTXQTOP = CortexM3::Field<ValueType, 24, 7>;
};

class FS_GCCFG {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPWRDWN() noexcept -> ValueType { return Reg::Read<F_PWRDWN>(); }
    static void WritePWRDWN(ValueType value) noexcept { Reg::Write<F_PWRDWN>(value); }
    static auto ReadVBUSASEN() noexcept -> ValueType { return Reg::Read<F_VBUSASEN>(); }
    static void WriteVBUSASEN(ValueType value) noexcept { Reg::Write<F_VBUSASEN>(value); }
    static auto ReadVBUSBSEN() noexcept -> ValueType { return Reg::Read<F_VBUSBSEN>(); }
    static void WriteVBUSBSEN(ValueType value) noexcept { Reg::Write<F_VBUSBSEN>(value); }
    static auto ReadSOFOUTEN() noexcept -> ValueType { return Reg::Read<F_SOFOUTEN>(); }
    static void WriteSOFOUTEN(ValueType value) noexcept { Reg::Write<F_SOFOUTEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000038;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PWRDWN = CortexM3::Field<ValueType, 16, 1>;
    using F_VBUSASEN = CortexM3::Field<ValueType, 18, 1>;
    using F_VBUSBSEN = CortexM3::Field<ValueType, 19, 1>;
    using F_SOFOUTEN = CortexM3::Field<ValueType, 20, 1>;
};

class FS_CID {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00001000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRODUCT_ID() noexcept -> ValueType { return Reg::Read<F_PRODUCT_ID>(); }
    static void WritePRODUCT_ID(ValueType value) noexcept { Reg::Write<F_PRODUCT_ID>(value); }

private:
    static constexpr std::uintptr_t Address = 0x5000003c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRODUCT_ID = CortexM3::Field<ValueType, 0, 32>;
};

class FS_HPTXFSIZ {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x02000600;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPTXSA() noexcept -> ValueType { return Reg::Read<F_PTXSA>(); }
    static void WritePTXSA(ValueType value) noexcept { Reg::Write<F_PTXSA>(value); }
    static auto ReadPTXFSIZ() noexcept -> ValueType { return Reg::Read<F_PTXFSIZ>(); }
    static void WritePTXFSIZ(ValueType value) noexcept { Reg::Write<F_PTXFSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000100;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PTXSA = CortexM3::Field<ValueType, 0, 16>;
    using F_PTXFSIZ = CortexM3::Field<ValueType, 16, 16>;
};

class FS_DIEPTXF1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x02000400;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadINEPTXSA() noexcept -> ValueType { return Reg::Read<F_INEPTXSA>(); }
    static void WriteINEPTXSA(ValueType value) noexcept { Reg::Write<F_INEPTXSA>(value); }
    static auto ReadINEPTXFD() noexcept -> ValueType { return Reg::Read<F_INEPTXFD>(); }
    static void WriteINEPTXFD(ValueType value) noexcept { Reg::Write<F_INEPTXFD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000104;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_INEPTXSA = CortexM3::Field<ValueType, 0, 16>;
    using F_INEPTXFD = CortexM3::Field<ValueType, 16, 16>;
};

class FS_DIEPTXF2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x02000400;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadINEPTXSA() noexcept -> ValueType { return Reg::Read<F_INEPTXSA>(); }
    static void WriteINEPTXSA(ValueType value) noexcept { Reg::Write<F_INEPTXSA>(value); }
    static auto ReadINEPTXFD() noexcept -> ValueType { return Reg::Read<F_INEPTXFD>(); }
    static void WriteINEPTXFD(ValueType value) noexcept { Reg::Write<F_INEPTXFD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000108;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_INEPTXSA = CortexM3::Field<ValueType, 0, 16>;
    using F_INEPTXFD = CortexM3::Field<ValueType, 16, 16>;
};

class FS_DIEPTXF3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x02000400;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadINEPTXSA() noexcept -> ValueType { return Reg::Read<F_INEPTXSA>(); }
    static void WriteINEPTXSA(ValueType value) noexcept { Reg::Write<F_INEPTXSA>(value); }
    static auto ReadINEPTXFD() noexcept -> ValueType { return Reg::Read<F_INEPTXFD>(); }
    static void WriteINEPTXFD(ValueType value) noexcept { Reg::Write<F_INEPTXFD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x5000010c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_INEPTXSA = CortexM3::Field<ValueType, 0, 16>;
    using F_INEPTXFD = CortexM3::Field<ValueType, 16, 16>;
};

} // namespace STM32F103::OTG_FS_GLOBAL
