#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::OTG_FS_DEVICE {

class FS_DCFG {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x02200000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDSPD() noexcept -> ValueType { return Reg::Read<F_DSPD>(); }
    static void WriteDSPD(ValueType value) noexcept { Reg::Write<F_DSPD>(value); }
    static auto ReadNZLSOHSK() noexcept -> ValueType { return Reg::Read<F_NZLSOHSK>(); }
    static void WriteNZLSOHSK(ValueType value) noexcept { Reg::Write<F_NZLSOHSK>(value); }
    static auto ReadDAD() noexcept -> ValueType { return Reg::Read<F_DAD>(); }
    static void WriteDAD(ValueType value) noexcept { Reg::Write<F_DAD>(value); }
    static auto ReadPFIVL() noexcept -> ValueType { return Reg::Read<F_PFIVL>(); }
    static void WritePFIVL(ValueType value) noexcept { Reg::Write<F_PFIVL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000800;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DSPD = CortexM3::Field<ValueType, 0, 2>;
    using F_NZLSOHSK = CortexM3::Field<ValueType, 2, 1>;
    using F_DAD = CortexM3::Field<ValueType, 4, 7>;
    using F_PFIVL = CortexM3::Field<ValueType, 11, 2>;
};

class FS_DCTL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRWUSIG() noexcept -> ValueType { return Reg::Read<F_RWUSIG>(); }
    static void WriteRWUSIG(ValueType value) noexcept { Reg::Write<F_RWUSIG>(value); }
    static auto ReadSDIS() noexcept -> ValueType { return Reg::Read<F_SDIS>(); }
    static void WriteSDIS(ValueType value) noexcept { Reg::Write<F_SDIS>(value); }
    static auto ReadGINSTS() noexcept -> ValueType { return Reg::Read<F_GINSTS>(); }
    static auto ReadGONSTS() noexcept -> ValueType { return Reg::Read<F_GONSTS>(); }
    static auto ReadTCTL() noexcept -> ValueType { return Reg::Read<F_TCTL>(); }
    static void WriteTCTL(ValueType value) noexcept { Reg::Write<F_TCTL>(value); }
    static auto ReadSGINAK() noexcept -> ValueType { return Reg::Read<F_SGINAK>(); }
    static void WriteSGINAK(ValueType value) noexcept { Reg::Write<F_SGINAK>(value); }
    static auto ReadCGINAK() noexcept -> ValueType { return Reg::Read<F_CGINAK>(); }
    static void WriteCGINAK(ValueType value) noexcept { Reg::Write<F_CGINAK>(value); }
    static auto ReadSGONAK() noexcept -> ValueType { return Reg::Read<F_SGONAK>(); }
    static void WriteSGONAK(ValueType value) noexcept { Reg::Write<F_SGONAK>(value); }
    static auto ReadCGONAK() noexcept -> ValueType { return Reg::Read<F_CGONAK>(); }
    static void WriteCGONAK(ValueType value) noexcept { Reg::Write<F_CGONAK>(value); }
    static auto ReadPOPRGDNE() noexcept -> ValueType { return Reg::Read<F_POPRGDNE>(); }
    static void WritePOPRGDNE(ValueType value) noexcept { Reg::Write<F_POPRGDNE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000804;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RWUSIG = CortexM3::Field<ValueType, 0, 1>;
    using F_SDIS = CortexM3::Field<ValueType, 1, 1>;
    using F_GINSTS = CortexM3::Field<ValueType, 2, 1>;
    using F_GONSTS = CortexM3::Field<ValueType, 3, 1>;
    using F_TCTL = CortexM3::Field<ValueType, 4, 3>;
    using F_SGINAK = CortexM3::Field<ValueType, 7, 1>;
    using F_CGINAK = CortexM3::Field<ValueType, 8, 1>;
    using F_SGONAK = CortexM3::Field<ValueType, 9, 1>;
    using F_CGONAK = CortexM3::Field<ValueType, 10, 1>;
    using F_POPRGDNE = CortexM3::Field<ValueType, 11, 1>;
};

class FS_DSTS {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000010;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadSUSPSTS() noexcept -> ValueType { return Reg::Read<F_SUSPSTS>(); }
    static auto ReadENUMSPD() noexcept -> ValueType { return Reg::Read<F_ENUMSPD>(); }
    static auto ReadEERR() noexcept -> ValueType { return Reg::Read<F_EERR>(); }
    static auto ReadFNSOF() noexcept -> ValueType { return Reg::Read<F_FNSOF>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000808;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SUSPSTS = CortexM3::Field<ValueType, 0, 1>;
    using F_ENUMSPD = CortexM3::Field<ValueType, 1, 2>;
    using F_EERR = CortexM3::Field<ValueType, 3, 1>;
    using F_FNSOF = CortexM3::Field<ValueType, 8, 14>;
};

class FS_DIEPMSK {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRCM() noexcept -> ValueType { return Reg::Read<F_XFRCM>(); }
    static void WriteXFRCM(ValueType value) noexcept { Reg::Write<F_XFRCM>(value); }
    static auto ReadEPDM() noexcept -> ValueType { return Reg::Read<F_EPDM>(); }
    static void WriteEPDM(ValueType value) noexcept { Reg::Write<F_EPDM>(value); }
    static auto ReadTOM() noexcept -> ValueType { return Reg::Read<F_TOM>(); }
    static void WriteTOM(ValueType value) noexcept { Reg::Write<F_TOM>(value); }
    static auto ReadITTXFEMSK() noexcept -> ValueType { return Reg::Read<F_ITTXFEMSK>(); }
    static void WriteITTXFEMSK(ValueType value) noexcept { Reg::Write<F_ITTXFEMSK>(value); }
    static auto ReadINEPNMM() noexcept -> ValueType { return Reg::Read<F_INEPNMM>(); }
    static void WriteINEPNMM(ValueType value) noexcept { Reg::Write<F_INEPNMM>(value); }
    static auto ReadINEPNEM() noexcept -> ValueType { return Reg::Read<F_INEPNEM>(); }
    static void WriteINEPNEM(ValueType value) noexcept { Reg::Write<F_INEPNEM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000810;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRCM = CortexM3::Field<ValueType, 0, 1>;
    using F_EPDM = CortexM3::Field<ValueType, 1, 1>;
    using F_TOM = CortexM3::Field<ValueType, 3, 1>;
    using F_ITTXFEMSK = CortexM3::Field<ValueType, 4, 1>;
    using F_INEPNMM = CortexM3::Field<ValueType, 5, 1>;
    using F_INEPNEM = CortexM3::Field<ValueType, 6, 1>;
};

class FS_DOEPMSK {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRCM() noexcept -> ValueType { return Reg::Read<F_XFRCM>(); }
    static void WriteXFRCM(ValueType value) noexcept { Reg::Write<F_XFRCM>(value); }
    static auto ReadEPDM() noexcept -> ValueType { return Reg::Read<F_EPDM>(); }
    static void WriteEPDM(ValueType value) noexcept { Reg::Write<F_EPDM>(value); }
    static auto ReadSTUPM() noexcept -> ValueType { return Reg::Read<F_STUPM>(); }
    static void WriteSTUPM(ValueType value) noexcept { Reg::Write<F_STUPM>(value); }
    static auto ReadOTEPDM() noexcept -> ValueType { return Reg::Read<F_OTEPDM>(); }
    static void WriteOTEPDM(ValueType value) noexcept { Reg::Write<F_OTEPDM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000814;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRCM = CortexM3::Field<ValueType, 0, 1>;
    using F_EPDM = CortexM3::Field<ValueType, 1, 1>;
    using F_STUPM = CortexM3::Field<ValueType, 3, 1>;
    using F_OTEPDM = CortexM3::Field<ValueType, 4, 1>;
};

class FS_DAINT {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadIEPINT() noexcept -> ValueType { return Reg::Read<F_IEPINT>(); }
    static auto ReadOEPINT() noexcept -> ValueType { return Reg::Read<F_OEPINT>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000818;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_IEPINT = CortexM3::Field<ValueType, 0, 16>;
    using F_OEPINT = CortexM3::Field<ValueType, 16, 16>;
};

class FS_DAINTMSK {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadIEPM() noexcept -> ValueType { return Reg::Read<F_IEPM>(); }
    static void WriteIEPM(ValueType value) noexcept { Reg::Write<F_IEPM>(value); }
    static auto ReadOEPINT() noexcept -> ValueType { return Reg::Read<F_OEPINT>(); }
    static void WriteOEPINT(ValueType value) noexcept { Reg::Write<F_OEPINT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x5000081c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_IEPM = CortexM3::Field<ValueType, 0, 16>;
    using F_OEPINT = CortexM3::Field<ValueType, 16, 16>;
};

class DVBUSDIS {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x000017D7;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadVBUSDT() noexcept -> ValueType { return Reg::Read<F_VBUSDT>(); }
    static void WriteVBUSDT(ValueType value) noexcept { Reg::Write<F_VBUSDT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000828;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_VBUSDT = CortexM3::Field<ValueType, 0, 16>;
};

class DVBUSPULSE {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x000005B8;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDVBUSP() noexcept -> ValueType { return Reg::Read<F_DVBUSP>(); }
    static void WriteDVBUSP(ValueType value) noexcept { Reg::Write<F_DVBUSP>(value); }

private:
    static constexpr std::uintptr_t Address = 0x5000082c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DVBUSP = CortexM3::Field<ValueType, 0, 12>;
};

class DIEPEMPMSK {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadINEPTXFEM() noexcept -> ValueType { return Reg::Read<F_INEPTXFEM>(); }
    static void WriteINEPTXFEM(ValueType value) noexcept { Reg::Write<F_INEPTXFEM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000834;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_INEPTXFEM = CortexM3::Field<ValueType, 0, 16>;
};

class FS_DIEPCTL0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }
    static auto ReadUSBAEP() noexcept -> ValueType { return Reg::Read<F_USBAEP>(); }
    static auto ReadNAKSTS() noexcept -> ValueType { return Reg::Read<F_NAKSTS>(); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static auto ReadSTALL() noexcept -> ValueType { return Reg::Read<F_STALL>(); }
    static void WriteSTALL(ValueType value) noexcept { Reg::Write<F_STALL>(value); }
    static auto ReadTXFNUM() noexcept -> ValueType { return Reg::Read<F_TXFNUM>(); }
    static void WriteTXFNUM(ValueType value) noexcept { Reg::Write<F_TXFNUM>(value); }
    static void WriteCNAK(ValueType value) noexcept { Reg::Write<F_CNAK>(value); }
    static void WriteSNAK(ValueType value) noexcept { Reg::Write<F_SNAK>(value); }
    static auto ReadEPDIS() noexcept -> ValueType { return Reg::Read<F_EPDIS>(); }
    static auto ReadEPENA() noexcept -> ValueType { return Reg::Read<F_EPENA>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000900;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 2>;
    using F_USBAEP = CortexM3::Field<ValueType, 15, 1>;
    using F_NAKSTS = CortexM3::Field<ValueType, 17, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_STALL = CortexM3::Field<ValueType, 21, 1>;
    using F_TXFNUM = CortexM3::Field<ValueType, 22, 4>;
    using F_CNAK = CortexM3::Field<ValueType, 26, 1>;
    using F_SNAK = CortexM3::Field<ValueType, 27, 1>;
    using F_EPDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_EPENA = CortexM3::Field<ValueType, 31, 1>;
};

class DIEPCTL1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEPENA() noexcept -> ValueType { return Reg::Read<F_EPENA>(); }
    static void WriteEPENA(ValueType value) noexcept { Reg::Write<F_EPENA>(value); }
    static auto ReadEPDIS() noexcept -> ValueType { return Reg::Read<F_EPDIS>(); }
    static void WriteEPDIS(ValueType value) noexcept { Reg::Write<F_EPDIS>(value); }
    static void WriteSODDFRM_SD1PID(ValueType value) noexcept { Reg::Write<F_SODDFRM_SD1PID>(value); }
    static void WriteSD0PID_SEVNFRM(ValueType value) noexcept { Reg::Write<F_SD0PID_SEVNFRM>(value); }
    static void WriteSNAK(ValueType value) noexcept { Reg::Write<F_SNAK>(value); }
    static void WriteCNAK(ValueType value) noexcept { Reg::Write<F_CNAK>(value); }
    static auto ReadTXFNUM() noexcept -> ValueType { return Reg::Read<F_TXFNUM>(); }
    static void WriteTXFNUM(ValueType value) noexcept { Reg::Write<F_TXFNUM>(value); }
    static auto ReadStall() noexcept -> ValueType { return Reg::Read<F_Stall>(); }
    static void WriteStall(ValueType value) noexcept { Reg::Write<F_Stall>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadNAKSTS() noexcept -> ValueType { return Reg::Read<F_NAKSTS>(); }
    static auto ReadEONUM_DPID() noexcept -> ValueType { return Reg::Read<F_EONUM_DPID>(); }
    static auto ReadUSBAEP() noexcept -> ValueType { return Reg::Read<F_USBAEP>(); }
    static void WriteUSBAEP(ValueType value) noexcept { Reg::Write<F_USBAEP>(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000920;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EPENA = CortexM3::Field<ValueType, 31, 1>;
    using F_EPDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_SODDFRM_SD1PID = CortexM3::Field<ValueType, 29, 1>;
    using F_SD0PID_SEVNFRM = CortexM3::Field<ValueType, 28, 1>;
    using F_SNAK = CortexM3::Field<ValueType, 27, 1>;
    using F_CNAK = CortexM3::Field<ValueType, 26, 1>;
    using F_TXFNUM = CortexM3::Field<ValueType, 22, 4>;
    using F_Stall = CortexM3::Field<ValueType, 21, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_NAKSTS = CortexM3::Field<ValueType, 17, 1>;
    using F_EONUM_DPID = CortexM3::Field<ValueType, 16, 1>;
    using F_USBAEP = CortexM3::Field<ValueType, 15, 1>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
};

class DIEPCTL2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEPENA() noexcept -> ValueType { return Reg::Read<F_EPENA>(); }
    static void WriteEPENA(ValueType value) noexcept { Reg::Write<F_EPENA>(value); }
    static auto ReadEPDIS() noexcept -> ValueType { return Reg::Read<F_EPDIS>(); }
    static void WriteEPDIS(ValueType value) noexcept { Reg::Write<F_EPDIS>(value); }
    static void WriteSODDFRM(ValueType value) noexcept { Reg::Write<F_SODDFRM>(value); }
    static void WriteSD0PID_SEVNFRM(ValueType value) noexcept { Reg::Write<F_SD0PID_SEVNFRM>(value); }
    static void WriteSNAK(ValueType value) noexcept { Reg::Write<F_SNAK>(value); }
    static void WriteCNAK(ValueType value) noexcept { Reg::Write<F_CNAK>(value); }
    static auto ReadTXFNUM() noexcept -> ValueType { return Reg::Read<F_TXFNUM>(); }
    static void WriteTXFNUM(ValueType value) noexcept { Reg::Write<F_TXFNUM>(value); }
    static auto ReadStall() noexcept -> ValueType { return Reg::Read<F_Stall>(); }
    static void WriteStall(ValueType value) noexcept { Reg::Write<F_Stall>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadNAKSTS() noexcept -> ValueType { return Reg::Read<F_NAKSTS>(); }
    static auto ReadEONUM_DPID() noexcept -> ValueType { return Reg::Read<F_EONUM_DPID>(); }
    static auto ReadUSBAEP() noexcept -> ValueType { return Reg::Read<F_USBAEP>(); }
    static void WriteUSBAEP(ValueType value) noexcept { Reg::Write<F_USBAEP>(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000940;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EPENA = CortexM3::Field<ValueType, 31, 1>;
    using F_EPDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_SODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_SD0PID_SEVNFRM = CortexM3::Field<ValueType, 28, 1>;
    using F_SNAK = CortexM3::Field<ValueType, 27, 1>;
    using F_CNAK = CortexM3::Field<ValueType, 26, 1>;
    using F_TXFNUM = CortexM3::Field<ValueType, 22, 4>;
    using F_Stall = CortexM3::Field<ValueType, 21, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_NAKSTS = CortexM3::Field<ValueType, 17, 1>;
    using F_EONUM_DPID = CortexM3::Field<ValueType, 16, 1>;
    using F_USBAEP = CortexM3::Field<ValueType, 15, 1>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
};

class DIEPCTL3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEPENA() noexcept -> ValueType { return Reg::Read<F_EPENA>(); }
    static void WriteEPENA(ValueType value) noexcept { Reg::Write<F_EPENA>(value); }
    static auto ReadEPDIS() noexcept -> ValueType { return Reg::Read<F_EPDIS>(); }
    static void WriteEPDIS(ValueType value) noexcept { Reg::Write<F_EPDIS>(value); }
    static void WriteSODDFRM(ValueType value) noexcept { Reg::Write<F_SODDFRM>(value); }
    static void WriteSD0PID_SEVNFRM(ValueType value) noexcept { Reg::Write<F_SD0PID_SEVNFRM>(value); }
    static void WriteSNAK(ValueType value) noexcept { Reg::Write<F_SNAK>(value); }
    static void WriteCNAK(ValueType value) noexcept { Reg::Write<F_CNAK>(value); }
    static auto ReadTXFNUM() noexcept -> ValueType { return Reg::Read<F_TXFNUM>(); }
    static void WriteTXFNUM(ValueType value) noexcept { Reg::Write<F_TXFNUM>(value); }
    static auto ReadStall() noexcept -> ValueType { return Reg::Read<F_Stall>(); }
    static void WriteStall(ValueType value) noexcept { Reg::Write<F_Stall>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadNAKSTS() noexcept -> ValueType { return Reg::Read<F_NAKSTS>(); }
    static auto ReadEONUM_DPID() noexcept -> ValueType { return Reg::Read<F_EONUM_DPID>(); }
    static auto ReadUSBAEP() noexcept -> ValueType { return Reg::Read<F_USBAEP>(); }
    static void WriteUSBAEP(ValueType value) noexcept { Reg::Write<F_USBAEP>(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000960;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EPENA = CortexM3::Field<ValueType, 31, 1>;
    using F_EPDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_SODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_SD0PID_SEVNFRM = CortexM3::Field<ValueType, 28, 1>;
    using F_SNAK = CortexM3::Field<ValueType, 27, 1>;
    using F_CNAK = CortexM3::Field<ValueType, 26, 1>;
    using F_TXFNUM = CortexM3::Field<ValueType, 22, 4>;
    using F_Stall = CortexM3::Field<ValueType, 21, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_NAKSTS = CortexM3::Field<ValueType, 17, 1>;
    using F_EONUM_DPID = CortexM3::Field<ValueType, 16, 1>;
    using F_USBAEP = CortexM3::Field<ValueType, 15, 1>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
};

class DOEPCTL0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00008000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteEPENA(ValueType value) noexcept { Reg::Write<F_EPENA>(value); }
    static auto ReadEPDIS() noexcept -> ValueType { return Reg::Read<F_EPDIS>(); }
    static void WriteSNAK(ValueType value) noexcept { Reg::Write<F_SNAK>(value); }
    static void WriteCNAK(ValueType value) noexcept { Reg::Write<F_CNAK>(value); }
    static auto ReadStall() noexcept -> ValueType { return Reg::Read<F_Stall>(); }
    static void WriteStall(ValueType value) noexcept { Reg::Write<F_Stall>(value); }
    static auto ReadSNPM() noexcept -> ValueType { return Reg::Read<F_SNPM>(); }
    static void WriteSNPM(ValueType value) noexcept { Reg::Write<F_SNPM>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static auto ReadNAKSTS() noexcept -> ValueType { return Reg::Read<F_NAKSTS>(); }
    static auto ReadUSBAEP() noexcept -> ValueType { return Reg::Read<F_USBAEP>(); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000b00;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EPENA = CortexM3::Field<ValueType, 31, 1>;
    using F_EPDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_SNAK = CortexM3::Field<ValueType, 27, 1>;
    using F_CNAK = CortexM3::Field<ValueType, 26, 1>;
    using F_Stall = CortexM3::Field<ValueType, 21, 1>;
    using F_SNPM = CortexM3::Field<ValueType, 20, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_NAKSTS = CortexM3::Field<ValueType, 17, 1>;
    using F_USBAEP = CortexM3::Field<ValueType, 15, 1>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 2>;
};

class DOEPCTL1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEPENA() noexcept -> ValueType { return Reg::Read<F_EPENA>(); }
    static void WriteEPENA(ValueType value) noexcept { Reg::Write<F_EPENA>(value); }
    static auto ReadEPDIS() noexcept -> ValueType { return Reg::Read<F_EPDIS>(); }
    static void WriteEPDIS(ValueType value) noexcept { Reg::Write<F_EPDIS>(value); }
    static void WriteSODDFRM(ValueType value) noexcept { Reg::Write<F_SODDFRM>(value); }
    static void WriteSD0PID_SEVNFRM(ValueType value) noexcept { Reg::Write<F_SD0PID_SEVNFRM>(value); }
    static void WriteSNAK(ValueType value) noexcept { Reg::Write<F_SNAK>(value); }
    static void WriteCNAK(ValueType value) noexcept { Reg::Write<F_CNAK>(value); }
    static auto ReadStall() noexcept -> ValueType { return Reg::Read<F_Stall>(); }
    static void WriteStall(ValueType value) noexcept { Reg::Write<F_Stall>(value); }
    static auto ReadSNPM() noexcept -> ValueType { return Reg::Read<F_SNPM>(); }
    static void WriteSNPM(ValueType value) noexcept { Reg::Write<F_SNPM>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadNAKSTS() noexcept -> ValueType { return Reg::Read<F_NAKSTS>(); }
    static auto ReadEONUM_DPID() noexcept -> ValueType { return Reg::Read<F_EONUM_DPID>(); }
    static auto ReadUSBAEP() noexcept -> ValueType { return Reg::Read<F_USBAEP>(); }
    static void WriteUSBAEP(ValueType value) noexcept { Reg::Write<F_USBAEP>(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b20;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EPENA = CortexM3::Field<ValueType, 31, 1>;
    using F_EPDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_SODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_SD0PID_SEVNFRM = CortexM3::Field<ValueType, 28, 1>;
    using F_SNAK = CortexM3::Field<ValueType, 27, 1>;
    using F_CNAK = CortexM3::Field<ValueType, 26, 1>;
    using F_Stall = CortexM3::Field<ValueType, 21, 1>;
    using F_SNPM = CortexM3::Field<ValueType, 20, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_NAKSTS = CortexM3::Field<ValueType, 17, 1>;
    using F_EONUM_DPID = CortexM3::Field<ValueType, 16, 1>;
    using F_USBAEP = CortexM3::Field<ValueType, 15, 1>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
};

class DOEPCTL2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEPENA() noexcept -> ValueType { return Reg::Read<F_EPENA>(); }
    static void WriteEPENA(ValueType value) noexcept { Reg::Write<F_EPENA>(value); }
    static auto ReadEPDIS() noexcept -> ValueType { return Reg::Read<F_EPDIS>(); }
    static void WriteEPDIS(ValueType value) noexcept { Reg::Write<F_EPDIS>(value); }
    static void WriteSODDFRM(ValueType value) noexcept { Reg::Write<F_SODDFRM>(value); }
    static void WriteSD0PID_SEVNFRM(ValueType value) noexcept { Reg::Write<F_SD0PID_SEVNFRM>(value); }
    static void WriteSNAK(ValueType value) noexcept { Reg::Write<F_SNAK>(value); }
    static void WriteCNAK(ValueType value) noexcept { Reg::Write<F_CNAK>(value); }
    static auto ReadStall() noexcept -> ValueType { return Reg::Read<F_Stall>(); }
    static void WriteStall(ValueType value) noexcept { Reg::Write<F_Stall>(value); }
    static auto ReadSNPM() noexcept -> ValueType { return Reg::Read<F_SNPM>(); }
    static void WriteSNPM(ValueType value) noexcept { Reg::Write<F_SNPM>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadNAKSTS() noexcept -> ValueType { return Reg::Read<F_NAKSTS>(); }
    static auto ReadEONUM_DPID() noexcept -> ValueType { return Reg::Read<F_EONUM_DPID>(); }
    static auto ReadUSBAEP() noexcept -> ValueType { return Reg::Read<F_USBAEP>(); }
    static void WriteUSBAEP(ValueType value) noexcept { Reg::Write<F_USBAEP>(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b40;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EPENA = CortexM3::Field<ValueType, 31, 1>;
    using F_EPDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_SODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_SD0PID_SEVNFRM = CortexM3::Field<ValueType, 28, 1>;
    using F_SNAK = CortexM3::Field<ValueType, 27, 1>;
    using F_CNAK = CortexM3::Field<ValueType, 26, 1>;
    using F_Stall = CortexM3::Field<ValueType, 21, 1>;
    using F_SNPM = CortexM3::Field<ValueType, 20, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_NAKSTS = CortexM3::Field<ValueType, 17, 1>;
    using F_EONUM_DPID = CortexM3::Field<ValueType, 16, 1>;
    using F_USBAEP = CortexM3::Field<ValueType, 15, 1>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
};

class DOEPCTL3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEPENA() noexcept -> ValueType { return Reg::Read<F_EPENA>(); }
    static void WriteEPENA(ValueType value) noexcept { Reg::Write<F_EPENA>(value); }
    static auto ReadEPDIS() noexcept -> ValueType { return Reg::Read<F_EPDIS>(); }
    static void WriteEPDIS(ValueType value) noexcept { Reg::Write<F_EPDIS>(value); }
    static void WriteSODDFRM(ValueType value) noexcept { Reg::Write<F_SODDFRM>(value); }
    static void WriteSD0PID_SEVNFRM(ValueType value) noexcept { Reg::Write<F_SD0PID_SEVNFRM>(value); }
    static void WriteSNAK(ValueType value) noexcept { Reg::Write<F_SNAK>(value); }
    static void WriteCNAK(ValueType value) noexcept { Reg::Write<F_CNAK>(value); }
    static auto ReadStall() noexcept -> ValueType { return Reg::Read<F_Stall>(); }
    static void WriteStall(ValueType value) noexcept { Reg::Write<F_Stall>(value); }
    static auto ReadSNPM() noexcept -> ValueType { return Reg::Read<F_SNPM>(); }
    static void WriteSNPM(ValueType value) noexcept { Reg::Write<F_SNPM>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadNAKSTS() noexcept -> ValueType { return Reg::Read<F_NAKSTS>(); }
    static auto ReadEONUM_DPID() noexcept -> ValueType { return Reg::Read<F_EONUM_DPID>(); }
    static auto ReadUSBAEP() noexcept -> ValueType { return Reg::Read<F_USBAEP>(); }
    static void WriteUSBAEP(ValueType value) noexcept { Reg::Write<F_USBAEP>(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b60;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EPENA = CortexM3::Field<ValueType, 31, 1>;
    using F_EPDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_SODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_SD0PID_SEVNFRM = CortexM3::Field<ValueType, 28, 1>;
    using F_SNAK = CortexM3::Field<ValueType, 27, 1>;
    using F_CNAK = CortexM3::Field<ValueType, 26, 1>;
    using F_Stall = CortexM3::Field<ValueType, 21, 1>;
    using F_SNPM = CortexM3::Field<ValueType, 20, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_NAKSTS = CortexM3::Field<ValueType, 17, 1>;
    using F_EONUM_DPID = CortexM3::Field<ValueType, 16, 1>;
    using F_USBAEP = CortexM3::Field<ValueType, 15, 1>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
};

class DIEPINT0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000080;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTXFE() noexcept -> ValueType { return Reg::Read<F_TXFE>(); }
    static auto ReadINEPNE() noexcept -> ValueType { return Reg::Read<F_INEPNE>(); }
    static void WriteINEPNE(ValueType value) noexcept { Reg::Write<F_INEPNE>(value); }
    static auto ReadITTXFE() noexcept -> ValueType { return Reg::Read<F_ITTXFE>(); }
    static void WriteITTXFE(ValueType value) noexcept { Reg::Write<F_ITTXFE>(value); }
    static auto ReadTOC() noexcept -> ValueType { return Reg::Read<F_TOC>(); }
    static void WriteTOC(ValueType value) noexcept { Reg::Write<F_TOC>(value); }
    static auto ReadEPDISD() noexcept -> ValueType { return Reg::Read<F_EPDISD>(); }
    static void WriteEPDISD(ValueType value) noexcept { Reg::Write<F_EPDISD>(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000908;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TXFE = CortexM3::Field<ValueType, 7, 1>;
    using F_INEPNE = CortexM3::Field<ValueType, 6, 1>;
    using F_ITTXFE = CortexM3::Field<ValueType, 4, 1>;
    using F_TOC = CortexM3::Field<ValueType, 3, 1>;
    using F_EPDISD = CortexM3::Field<ValueType, 1, 1>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
};

class DIEPINT1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000080;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTXFE() noexcept -> ValueType { return Reg::Read<F_TXFE>(); }
    static auto ReadINEPNE() noexcept -> ValueType { return Reg::Read<F_INEPNE>(); }
    static void WriteINEPNE(ValueType value) noexcept { Reg::Write<F_INEPNE>(value); }
    static auto ReadITTXFE() noexcept -> ValueType { return Reg::Read<F_ITTXFE>(); }
    static void WriteITTXFE(ValueType value) noexcept { Reg::Write<F_ITTXFE>(value); }
    static auto ReadTOC() noexcept -> ValueType { return Reg::Read<F_TOC>(); }
    static void WriteTOC(ValueType value) noexcept { Reg::Write<F_TOC>(value); }
    static auto ReadEPDISD() noexcept -> ValueType { return Reg::Read<F_EPDISD>(); }
    static void WriteEPDISD(ValueType value) noexcept { Reg::Write<F_EPDISD>(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000928;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TXFE = CortexM3::Field<ValueType, 7, 1>;
    using F_INEPNE = CortexM3::Field<ValueType, 6, 1>;
    using F_ITTXFE = CortexM3::Field<ValueType, 4, 1>;
    using F_TOC = CortexM3::Field<ValueType, 3, 1>;
    using F_EPDISD = CortexM3::Field<ValueType, 1, 1>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
};

class DIEPINT2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000080;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTXFE() noexcept -> ValueType { return Reg::Read<F_TXFE>(); }
    static auto ReadINEPNE() noexcept -> ValueType { return Reg::Read<F_INEPNE>(); }
    static void WriteINEPNE(ValueType value) noexcept { Reg::Write<F_INEPNE>(value); }
    static auto ReadITTXFE() noexcept -> ValueType { return Reg::Read<F_ITTXFE>(); }
    static void WriteITTXFE(ValueType value) noexcept { Reg::Write<F_ITTXFE>(value); }
    static auto ReadTOC() noexcept -> ValueType { return Reg::Read<F_TOC>(); }
    static void WriteTOC(ValueType value) noexcept { Reg::Write<F_TOC>(value); }
    static auto ReadEPDISD() noexcept -> ValueType { return Reg::Read<F_EPDISD>(); }
    static void WriteEPDISD(ValueType value) noexcept { Reg::Write<F_EPDISD>(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000948;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TXFE = CortexM3::Field<ValueType, 7, 1>;
    using F_INEPNE = CortexM3::Field<ValueType, 6, 1>;
    using F_ITTXFE = CortexM3::Field<ValueType, 4, 1>;
    using F_TOC = CortexM3::Field<ValueType, 3, 1>;
    using F_EPDISD = CortexM3::Field<ValueType, 1, 1>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
};

class DIEPINT3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000080;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTXFE() noexcept -> ValueType { return Reg::Read<F_TXFE>(); }
    static auto ReadINEPNE() noexcept -> ValueType { return Reg::Read<F_INEPNE>(); }
    static void WriteINEPNE(ValueType value) noexcept { Reg::Write<F_INEPNE>(value); }
    static auto ReadITTXFE() noexcept -> ValueType { return Reg::Read<F_ITTXFE>(); }
    static void WriteITTXFE(ValueType value) noexcept { Reg::Write<F_ITTXFE>(value); }
    static auto ReadTOC() noexcept -> ValueType { return Reg::Read<F_TOC>(); }
    static void WriteTOC(ValueType value) noexcept { Reg::Write<F_TOC>(value); }
    static auto ReadEPDISD() noexcept -> ValueType { return Reg::Read<F_EPDISD>(); }
    static void WriteEPDISD(ValueType value) noexcept { Reg::Write<F_EPDISD>(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000968;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TXFE = CortexM3::Field<ValueType, 7, 1>;
    using F_INEPNE = CortexM3::Field<ValueType, 6, 1>;
    using F_ITTXFE = CortexM3::Field<ValueType, 4, 1>;
    using F_TOC = CortexM3::Field<ValueType, 3, 1>;
    using F_EPDISD = CortexM3::Field<ValueType, 1, 1>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
};

class DOEPINT0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000080;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadB2BSTUP() noexcept -> ValueType { return Reg::Read<F_B2BSTUP>(); }
    static void WriteB2BSTUP(ValueType value) noexcept { Reg::Write<F_B2BSTUP>(value); }
    static auto ReadOTEPDIS() noexcept -> ValueType { return Reg::Read<F_OTEPDIS>(); }
    static void WriteOTEPDIS(ValueType value) noexcept { Reg::Write<F_OTEPDIS>(value); }
    static auto ReadSTUP() noexcept -> ValueType { return Reg::Read<F_STUP>(); }
    static void WriteSTUP(ValueType value) noexcept { Reg::Write<F_STUP>(value); }
    static auto ReadEPDISD() noexcept -> ValueType { return Reg::Read<F_EPDISD>(); }
    static void WriteEPDISD(ValueType value) noexcept { Reg::Write<F_EPDISD>(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b08;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_B2BSTUP = CortexM3::Field<ValueType, 6, 1>;
    using F_OTEPDIS = CortexM3::Field<ValueType, 4, 1>;
    using F_STUP = CortexM3::Field<ValueType, 3, 1>;
    using F_EPDISD = CortexM3::Field<ValueType, 1, 1>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
};

class DOEPINT1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000080;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadB2BSTUP() noexcept -> ValueType { return Reg::Read<F_B2BSTUP>(); }
    static void WriteB2BSTUP(ValueType value) noexcept { Reg::Write<F_B2BSTUP>(value); }
    static auto ReadOTEPDIS() noexcept -> ValueType { return Reg::Read<F_OTEPDIS>(); }
    static void WriteOTEPDIS(ValueType value) noexcept { Reg::Write<F_OTEPDIS>(value); }
    static auto ReadSTUP() noexcept -> ValueType { return Reg::Read<F_STUP>(); }
    static void WriteSTUP(ValueType value) noexcept { Reg::Write<F_STUP>(value); }
    static auto ReadEPDISD() noexcept -> ValueType { return Reg::Read<F_EPDISD>(); }
    static void WriteEPDISD(ValueType value) noexcept { Reg::Write<F_EPDISD>(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b28;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_B2BSTUP = CortexM3::Field<ValueType, 6, 1>;
    using F_OTEPDIS = CortexM3::Field<ValueType, 4, 1>;
    using F_STUP = CortexM3::Field<ValueType, 3, 1>;
    using F_EPDISD = CortexM3::Field<ValueType, 1, 1>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
};

class DOEPINT2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000080;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadB2BSTUP() noexcept -> ValueType { return Reg::Read<F_B2BSTUP>(); }
    static void WriteB2BSTUP(ValueType value) noexcept { Reg::Write<F_B2BSTUP>(value); }
    static auto ReadOTEPDIS() noexcept -> ValueType { return Reg::Read<F_OTEPDIS>(); }
    static void WriteOTEPDIS(ValueType value) noexcept { Reg::Write<F_OTEPDIS>(value); }
    static auto ReadSTUP() noexcept -> ValueType { return Reg::Read<F_STUP>(); }
    static void WriteSTUP(ValueType value) noexcept { Reg::Write<F_STUP>(value); }
    static auto ReadEPDISD() noexcept -> ValueType { return Reg::Read<F_EPDISD>(); }
    static void WriteEPDISD(ValueType value) noexcept { Reg::Write<F_EPDISD>(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b48;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_B2BSTUP = CortexM3::Field<ValueType, 6, 1>;
    using F_OTEPDIS = CortexM3::Field<ValueType, 4, 1>;
    using F_STUP = CortexM3::Field<ValueType, 3, 1>;
    using F_EPDISD = CortexM3::Field<ValueType, 1, 1>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
};

class DOEPINT3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000080;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadB2BSTUP() noexcept -> ValueType { return Reg::Read<F_B2BSTUP>(); }
    static void WriteB2BSTUP(ValueType value) noexcept { Reg::Write<F_B2BSTUP>(value); }
    static auto ReadOTEPDIS() noexcept -> ValueType { return Reg::Read<F_OTEPDIS>(); }
    static void WriteOTEPDIS(ValueType value) noexcept { Reg::Write<F_OTEPDIS>(value); }
    static auto ReadSTUP() noexcept -> ValueType { return Reg::Read<F_STUP>(); }
    static void WriteSTUP(ValueType value) noexcept { Reg::Write<F_STUP>(value); }
    static auto ReadEPDISD() noexcept -> ValueType { return Reg::Read<F_EPDISD>(); }
    static void WriteEPDISD(ValueType value) noexcept { Reg::Write<F_EPDISD>(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b68;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_B2BSTUP = CortexM3::Field<ValueType, 6, 1>;
    using F_OTEPDIS = CortexM3::Field<ValueType, 4, 1>;
    using F_STUP = CortexM3::Field<ValueType, 3, 1>;
    using F_EPDISD = CortexM3::Field<ValueType, 1, 1>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
};

class DIEPTSIZ0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000910;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 2>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 7>;
};

class DOEPTSIZ0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSTUPCNT() noexcept -> ValueType { return Reg::Read<F_STUPCNT>(); }
    static void WriteSTUPCNT(ValueType value) noexcept { Reg::Write<F_STUPCNT>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b10;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STUPCNT = CortexM3::Field<ValueType, 29, 2>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 1>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 7>;
};

class DIEPTSIZ1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000930;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MCNT = CortexM3::Field<ValueType, 29, 2>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
};

class DIEPTSIZ2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000950;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MCNT = CortexM3::Field<ValueType, 29, 2>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
};

class DIEPTSIZ3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000970;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MCNT = CortexM3::Field<ValueType, 29, 2>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
};

class DTXFSTS0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadINEPTFSAV() noexcept -> ValueType { return Reg::Read<F_INEPTFSAV>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000918;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_INEPTFSAV = CortexM3::Field<ValueType, 0, 16>;
};

class DTXFSTS1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadINEPTFSAV() noexcept -> ValueType { return Reg::Read<F_INEPTFSAV>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000938;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_INEPTFSAV = CortexM3::Field<ValueType, 0, 16>;
};

class DTXFSTS2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadINEPTFSAV() noexcept -> ValueType { return Reg::Read<F_INEPTFSAV>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000958;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_INEPTFSAV = CortexM3::Field<ValueType, 0, 16>;
};

class DTXFSTS3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadINEPTFSAV() noexcept -> ValueType { return Reg::Read<F_INEPTFSAV>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000978;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_INEPTFSAV = CortexM3::Field<ValueType, 0, 16>;
};

class DOEPTSIZ1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRXDPID_STUPCNT() noexcept -> ValueType { return Reg::Read<F_RXDPID_STUPCNT>(); }
    static void WriteRXDPID_STUPCNT(ValueType value) noexcept { Reg::Write<F_RXDPID_STUPCNT>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b30;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RXDPID_STUPCNT = CortexM3::Field<ValueType, 29, 2>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
};

class DOEPTSIZ2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRXDPID_STUPCNT() noexcept -> ValueType { return Reg::Read<F_RXDPID_STUPCNT>(); }
    static void WriteRXDPID_STUPCNT(ValueType value) noexcept { Reg::Write<F_RXDPID_STUPCNT>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b50;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RXDPID_STUPCNT = CortexM3::Field<ValueType, 29, 2>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
};

class DOEPTSIZ3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRXDPID_STUPCNT() noexcept -> ValueType { return Reg::Read<F_RXDPID_STUPCNT>(); }
    static void WriteRXDPID_STUPCNT(ValueType value) noexcept { Reg::Write<F_RXDPID_STUPCNT>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000b70;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RXDPID_STUPCNT = CortexM3::Field<ValueType, 29, 2>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
};

} // namespace STM32F103::OTG_FS_DEVICE
