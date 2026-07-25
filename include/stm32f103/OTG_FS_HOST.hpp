#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::OTG_FS_HOST {

class FS_HCFG {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFSLSPCS() noexcept -> ValueType { return Reg::Read<F_FSLSPCS>(); }
    static void WriteFSLSPCS(ValueType value) noexcept { Reg::Write<F_FSLSPCS>(value); }
    static auto ReadFSLSS() noexcept -> ValueType { return Reg::Read<F_FSLSS>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000400;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FSLSPCS = CortexM3::Field<ValueType, 0, 2>;
    using F_FSLSS = CortexM3::Field<ValueType, 2, 1>;
};

class HFIR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0000EA60;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFRIVL() noexcept -> ValueType { return Reg::Read<F_FRIVL>(); }
    static void WriteFRIVL(ValueType value) noexcept { Reg::Write<F_FRIVL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000404;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FRIVL = CortexM3::Field<ValueType, 0, 16>;
};

class FS_HFNUM {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00003FFF;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadFRNUM() noexcept -> ValueType { return Reg::Read<F_FRNUM>(); }
    static auto ReadFTREM() noexcept -> ValueType { return Reg::Read<F_FTREM>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000408;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FRNUM = CortexM3::Field<ValueType, 0, 16>;
    using F_FTREM = CortexM3::Field<ValueType, 16, 16>;
};

class FS_HPTXSTS {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00080100;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPTXFSAVL() noexcept -> ValueType { return Reg::Read<F_PTXFSAVL>(); }
    static void WritePTXFSAVL(ValueType value) noexcept { Reg::Write<F_PTXFSAVL>(value); }
    static auto ReadPTXQSAV() noexcept -> ValueType { return Reg::Read<F_PTXQSAV>(); }
    static auto ReadPTXQTOP() noexcept -> ValueType { return Reg::Read<F_PTXQTOP>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000410;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PTXFSAVL = CortexM3::Field<ValueType, 0, 16>;
    using F_PTXQSAV = CortexM3::Field<ValueType, 16, 8>;
    using F_PTXQTOP = CortexM3::Field<ValueType, 24, 8>;
};

class HAINT {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadHAINT() noexcept -> ValueType { return Reg::Read<F_HAINT>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000414;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_HAINT = CortexM3::Field<ValueType, 0, 16>;
};

class HAINTMSK {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadHAINTM() noexcept -> ValueType { return Reg::Read<F_HAINTM>(); }
    static void WriteHAINTM(ValueType value) noexcept { Reg::Write<F_HAINTM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000418;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_HAINTM = CortexM3::Field<ValueType, 0, 16>;
};

class FS_HPRT {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPCSTS() noexcept -> ValueType { return Reg::Read<F_PCSTS>(); }
    static auto ReadPCDET() noexcept -> ValueType { return Reg::Read<F_PCDET>(); }
    static void WritePCDET(ValueType value) noexcept { Reg::Write<F_PCDET>(value); }
    static auto ReadPENA() noexcept -> ValueType { return Reg::Read<F_PENA>(); }
    static void WritePENA(ValueType value) noexcept { Reg::Write<F_PENA>(value); }
    static auto ReadPENCHNG() noexcept -> ValueType { return Reg::Read<F_PENCHNG>(); }
    static void WritePENCHNG(ValueType value) noexcept { Reg::Write<F_PENCHNG>(value); }
    static auto ReadPOCA() noexcept -> ValueType { return Reg::Read<F_POCA>(); }
    static auto ReadPOCCHNG() noexcept -> ValueType { return Reg::Read<F_POCCHNG>(); }
    static void WritePOCCHNG(ValueType value) noexcept { Reg::Write<F_POCCHNG>(value); }
    static auto ReadPRES() noexcept -> ValueType { return Reg::Read<F_PRES>(); }
    static void WritePRES(ValueType value) noexcept { Reg::Write<F_PRES>(value); }
    static auto ReadPSUSP() noexcept -> ValueType { return Reg::Read<F_PSUSP>(); }
    static void WritePSUSP(ValueType value) noexcept { Reg::Write<F_PSUSP>(value); }
    static auto ReadPRST() noexcept -> ValueType { return Reg::Read<F_PRST>(); }
    static void WritePRST(ValueType value) noexcept { Reg::Write<F_PRST>(value); }
    static auto ReadPLSTS() noexcept -> ValueType { return Reg::Read<F_PLSTS>(); }
    static auto ReadPPWR() noexcept -> ValueType { return Reg::Read<F_PPWR>(); }
    static void WritePPWR(ValueType value) noexcept { Reg::Write<F_PPWR>(value); }
    static auto ReadPTCTL() noexcept -> ValueType { return Reg::Read<F_PTCTL>(); }
    static void WritePTCTL(ValueType value) noexcept { Reg::Write<F_PTCTL>(value); }
    static auto ReadPSPD() noexcept -> ValueType { return Reg::Read<F_PSPD>(); }

private:
    static constexpr std::uintptr_t Address = 0x50000440;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PCSTS = CortexM3::Field<ValueType, 0, 1>;
    using F_PCDET = CortexM3::Field<ValueType, 1, 1>;
    using F_PENA = CortexM3::Field<ValueType, 2, 1>;
    using F_PENCHNG = CortexM3::Field<ValueType, 3, 1>;
    using F_POCA = CortexM3::Field<ValueType, 4, 1>;
    using F_POCCHNG = CortexM3::Field<ValueType, 5, 1>;
    using F_PRES = CortexM3::Field<ValueType, 6, 1>;
    using F_PSUSP = CortexM3::Field<ValueType, 7, 1>;
    using F_PRST = CortexM3::Field<ValueType, 8, 1>;
    using F_PLSTS = CortexM3::Field<ValueType, 10, 2>;
    using F_PPWR = CortexM3::Field<ValueType, 12, 1>;
    using F_PTCTL = CortexM3::Field<ValueType, 13, 4>;
    using F_PSPD = CortexM3::Field<ValueType, 17, 2>;
};

class FS_HCCHAR0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }
    static auto ReadEPNUM() noexcept -> ValueType { return Reg::Read<F_EPNUM>(); }
    static void WriteEPNUM(ValueType value) noexcept { Reg::Write<F_EPNUM>(value); }
    static auto ReadEPDIR() noexcept -> ValueType { return Reg::Read<F_EPDIR>(); }
    static void WriteEPDIR(ValueType value) noexcept { Reg::Write<F_EPDIR>(value); }
    static auto ReadLSDEV() noexcept -> ValueType { return Reg::Read<F_LSDEV>(); }
    static void WriteLSDEV(ValueType value) noexcept { Reg::Write<F_LSDEV>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadDAD() noexcept -> ValueType { return Reg::Read<F_DAD>(); }
    static void WriteDAD(ValueType value) noexcept { Reg::Write<F_DAD>(value); }
    static auto ReadODDFRM() noexcept -> ValueType { return Reg::Read<F_ODDFRM>(); }
    static void WriteODDFRM(ValueType value) noexcept { Reg::Write<F_ODDFRM>(value); }
    static auto ReadCHDIS() noexcept -> ValueType { return Reg::Read<F_CHDIS>(); }
    static void WriteCHDIS(ValueType value) noexcept { Reg::Write<F_CHDIS>(value); }
    static auto ReadCHENA() noexcept -> ValueType { return Reg::Read<F_CHENA>(); }
    static void WriteCHENA(ValueType value) noexcept { Reg::Write<F_CHENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000500;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
    using F_EPNUM = CortexM3::Field<ValueType, 11, 4>;
    using F_EPDIR = CortexM3::Field<ValueType, 15, 1>;
    using F_LSDEV = CortexM3::Field<ValueType, 17, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_MCNT = CortexM3::Field<ValueType, 20, 2>;
    using F_DAD = CortexM3::Field<ValueType, 22, 7>;
    using F_ODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_CHDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_CHENA = CortexM3::Field<ValueType, 31, 1>;
};

class FS_HCCHAR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }
    static auto ReadEPNUM() noexcept -> ValueType { return Reg::Read<F_EPNUM>(); }
    static void WriteEPNUM(ValueType value) noexcept { Reg::Write<F_EPNUM>(value); }
    static auto ReadEPDIR() noexcept -> ValueType { return Reg::Read<F_EPDIR>(); }
    static void WriteEPDIR(ValueType value) noexcept { Reg::Write<F_EPDIR>(value); }
    static auto ReadLSDEV() noexcept -> ValueType { return Reg::Read<F_LSDEV>(); }
    static void WriteLSDEV(ValueType value) noexcept { Reg::Write<F_LSDEV>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadDAD() noexcept -> ValueType { return Reg::Read<F_DAD>(); }
    static void WriteDAD(ValueType value) noexcept { Reg::Write<F_DAD>(value); }
    static auto ReadODDFRM() noexcept -> ValueType { return Reg::Read<F_ODDFRM>(); }
    static void WriteODDFRM(ValueType value) noexcept { Reg::Write<F_ODDFRM>(value); }
    static auto ReadCHDIS() noexcept -> ValueType { return Reg::Read<F_CHDIS>(); }
    static void WriteCHDIS(ValueType value) noexcept { Reg::Write<F_CHDIS>(value); }
    static auto ReadCHENA() noexcept -> ValueType { return Reg::Read<F_CHENA>(); }
    static void WriteCHENA(ValueType value) noexcept { Reg::Write<F_CHENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000520;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
    using F_EPNUM = CortexM3::Field<ValueType, 11, 4>;
    using F_EPDIR = CortexM3::Field<ValueType, 15, 1>;
    using F_LSDEV = CortexM3::Field<ValueType, 17, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_MCNT = CortexM3::Field<ValueType, 20, 2>;
    using F_DAD = CortexM3::Field<ValueType, 22, 7>;
    using F_ODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_CHDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_CHENA = CortexM3::Field<ValueType, 31, 1>;
};

class FS_HCCHAR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }
    static auto ReadEPNUM() noexcept -> ValueType { return Reg::Read<F_EPNUM>(); }
    static void WriteEPNUM(ValueType value) noexcept { Reg::Write<F_EPNUM>(value); }
    static auto ReadEPDIR() noexcept -> ValueType { return Reg::Read<F_EPDIR>(); }
    static void WriteEPDIR(ValueType value) noexcept { Reg::Write<F_EPDIR>(value); }
    static auto ReadLSDEV() noexcept -> ValueType { return Reg::Read<F_LSDEV>(); }
    static void WriteLSDEV(ValueType value) noexcept { Reg::Write<F_LSDEV>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadDAD() noexcept -> ValueType { return Reg::Read<F_DAD>(); }
    static void WriteDAD(ValueType value) noexcept { Reg::Write<F_DAD>(value); }
    static auto ReadODDFRM() noexcept -> ValueType { return Reg::Read<F_ODDFRM>(); }
    static void WriteODDFRM(ValueType value) noexcept { Reg::Write<F_ODDFRM>(value); }
    static auto ReadCHDIS() noexcept -> ValueType { return Reg::Read<F_CHDIS>(); }
    static void WriteCHDIS(ValueType value) noexcept { Reg::Write<F_CHDIS>(value); }
    static auto ReadCHENA() noexcept -> ValueType { return Reg::Read<F_CHENA>(); }
    static void WriteCHENA(ValueType value) noexcept { Reg::Write<F_CHENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000540;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
    using F_EPNUM = CortexM3::Field<ValueType, 11, 4>;
    using F_EPDIR = CortexM3::Field<ValueType, 15, 1>;
    using F_LSDEV = CortexM3::Field<ValueType, 17, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_MCNT = CortexM3::Field<ValueType, 20, 2>;
    using F_DAD = CortexM3::Field<ValueType, 22, 7>;
    using F_ODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_CHDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_CHENA = CortexM3::Field<ValueType, 31, 1>;
};

class FS_HCCHAR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }
    static auto ReadEPNUM() noexcept -> ValueType { return Reg::Read<F_EPNUM>(); }
    static void WriteEPNUM(ValueType value) noexcept { Reg::Write<F_EPNUM>(value); }
    static auto ReadEPDIR() noexcept -> ValueType { return Reg::Read<F_EPDIR>(); }
    static void WriteEPDIR(ValueType value) noexcept { Reg::Write<F_EPDIR>(value); }
    static auto ReadLSDEV() noexcept -> ValueType { return Reg::Read<F_LSDEV>(); }
    static void WriteLSDEV(ValueType value) noexcept { Reg::Write<F_LSDEV>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadDAD() noexcept -> ValueType { return Reg::Read<F_DAD>(); }
    static void WriteDAD(ValueType value) noexcept { Reg::Write<F_DAD>(value); }
    static auto ReadODDFRM() noexcept -> ValueType { return Reg::Read<F_ODDFRM>(); }
    static void WriteODDFRM(ValueType value) noexcept { Reg::Write<F_ODDFRM>(value); }
    static auto ReadCHDIS() noexcept -> ValueType { return Reg::Read<F_CHDIS>(); }
    static void WriteCHDIS(ValueType value) noexcept { Reg::Write<F_CHDIS>(value); }
    static auto ReadCHENA() noexcept -> ValueType { return Reg::Read<F_CHENA>(); }
    static void WriteCHENA(ValueType value) noexcept { Reg::Write<F_CHENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000560;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
    using F_EPNUM = CortexM3::Field<ValueType, 11, 4>;
    using F_EPDIR = CortexM3::Field<ValueType, 15, 1>;
    using F_LSDEV = CortexM3::Field<ValueType, 17, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_MCNT = CortexM3::Field<ValueType, 20, 2>;
    using F_DAD = CortexM3::Field<ValueType, 22, 7>;
    using F_ODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_CHDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_CHENA = CortexM3::Field<ValueType, 31, 1>;
};

class FS_HCCHAR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }
    static auto ReadEPNUM() noexcept -> ValueType { return Reg::Read<F_EPNUM>(); }
    static void WriteEPNUM(ValueType value) noexcept { Reg::Write<F_EPNUM>(value); }
    static auto ReadEPDIR() noexcept -> ValueType { return Reg::Read<F_EPDIR>(); }
    static void WriteEPDIR(ValueType value) noexcept { Reg::Write<F_EPDIR>(value); }
    static auto ReadLSDEV() noexcept -> ValueType { return Reg::Read<F_LSDEV>(); }
    static void WriteLSDEV(ValueType value) noexcept { Reg::Write<F_LSDEV>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadDAD() noexcept -> ValueType { return Reg::Read<F_DAD>(); }
    static void WriteDAD(ValueType value) noexcept { Reg::Write<F_DAD>(value); }
    static auto ReadODDFRM() noexcept -> ValueType { return Reg::Read<F_ODDFRM>(); }
    static void WriteODDFRM(ValueType value) noexcept { Reg::Write<F_ODDFRM>(value); }
    static auto ReadCHDIS() noexcept -> ValueType { return Reg::Read<F_CHDIS>(); }
    static void WriteCHDIS(ValueType value) noexcept { Reg::Write<F_CHDIS>(value); }
    static auto ReadCHENA() noexcept -> ValueType { return Reg::Read<F_CHENA>(); }
    static void WriteCHENA(ValueType value) noexcept { Reg::Write<F_CHENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000580;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
    using F_EPNUM = CortexM3::Field<ValueType, 11, 4>;
    using F_EPDIR = CortexM3::Field<ValueType, 15, 1>;
    using F_LSDEV = CortexM3::Field<ValueType, 17, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_MCNT = CortexM3::Field<ValueType, 20, 2>;
    using F_DAD = CortexM3::Field<ValueType, 22, 7>;
    using F_ODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_CHDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_CHENA = CortexM3::Field<ValueType, 31, 1>;
};

class FS_HCCHAR5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }
    static auto ReadEPNUM() noexcept -> ValueType { return Reg::Read<F_EPNUM>(); }
    static void WriteEPNUM(ValueType value) noexcept { Reg::Write<F_EPNUM>(value); }
    static auto ReadEPDIR() noexcept -> ValueType { return Reg::Read<F_EPDIR>(); }
    static void WriteEPDIR(ValueType value) noexcept { Reg::Write<F_EPDIR>(value); }
    static auto ReadLSDEV() noexcept -> ValueType { return Reg::Read<F_LSDEV>(); }
    static void WriteLSDEV(ValueType value) noexcept { Reg::Write<F_LSDEV>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadDAD() noexcept -> ValueType { return Reg::Read<F_DAD>(); }
    static void WriteDAD(ValueType value) noexcept { Reg::Write<F_DAD>(value); }
    static auto ReadODDFRM() noexcept -> ValueType { return Reg::Read<F_ODDFRM>(); }
    static void WriteODDFRM(ValueType value) noexcept { Reg::Write<F_ODDFRM>(value); }
    static auto ReadCHDIS() noexcept -> ValueType { return Reg::Read<F_CHDIS>(); }
    static void WriteCHDIS(ValueType value) noexcept { Reg::Write<F_CHDIS>(value); }
    static auto ReadCHENA() noexcept -> ValueType { return Reg::Read<F_CHENA>(); }
    static void WriteCHENA(ValueType value) noexcept { Reg::Write<F_CHENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005a0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
    using F_EPNUM = CortexM3::Field<ValueType, 11, 4>;
    using F_EPDIR = CortexM3::Field<ValueType, 15, 1>;
    using F_LSDEV = CortexM3::Field<ValueType, 17, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_MCNT = CortexM3::Field<ValueType, 20, 2>;
    using F_DAD = CortexM3::Field<ValueType, 22, 7>;
    using F_ODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_CHDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_CHENA = CortexM3::Field<ValueType, 31, 1>;
};

class FS_HCCHAR6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }
    static auto ReadEPNUM() noexcept -> ValueType { return Reg::Read<F_EPNUM>(); }
    static void WriteEPNUM(ValueType value) noexcept { Reg::Write<F_EPNUM>(value); }
    static auto ReadEPDIR() noexcept -> ValueType { return Reg::Read<F_EPDIR>(); }
    static void WriteEPDIR(ValueType value) noexcept { Reg::Write<F_EPDIR>(value); }
    static auto ReadLSDEV() noexcept -> ValueType { return Reg::Read<F_LSDEV>(); }
    static void WriteLSDEV(ValueType value) noexcept { Reg::Write<F_LSDEV>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadDAD() noexcept -> ValueType { return Reg::Read<F_DAD>(); }
    static void WriteDAD(ValueType value) noexcept { Reg::Write<F_DAD>(value); }
    static auto ReadODDFRM() noexcept -> ValueType { return Reg::Read<F_ODDFRM>(); }
    static void WriteODDFRM(ValueType value) noexcept { Reg::Write<F_ODDFRM>(value); }
    static auto ReadCHDIS() noexcept -> ValueType { return Reg::Read<F_CHDIS>(); }
    static void WriteCHDIS(ValueType value) noexcept { Reg::Write<F_CHDIS>(value); }
    static auto ReadCHENA() noexcept -> ValueType { return Reg::Read<F_CHENA>(); }
    static void WriteCHENA(ValueType value) noexcept { Reg::Write<F_CHENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005c0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
    using F_EPNUM = CortexM3::Field<ValueType, 11, 4>;
    using F_EPDIR = CortexM3::Field<ValueType, 15, 1>;
    using F_LSDEV = CortexM3::Field<ValueType, 17, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_MCNT = CortexM3::Field<ValueType, 20, 2>;
    using F_DAD = CortexM3::Field<ValueType, 22, 7>;
    using F_ODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_CHDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_CHENA = CortexM3::Field<ValueType, 31, 1>;
};

class FS_HCCHAR7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMPSIZ() noexcept -> ValueType { return Reg::Read<F_MPSIZ>(); }
    static void WriteMPSIZ(ValueType value) noexcept { Reg::Write<F_MPSIZ>(value); }
    static auto ReadEPNUM() noexcept -> ValueType { return Reg::Read<F_EPNUM>(); }
    static void WriteEPNUM(ValueType value) noexcept { Reg::Write<F_EPNUM>(value); }
    static auto ReadEPDIR() noexcept -> ValueType { return Reg::Read<F_EPDIR>(); }
    static void WriteEPDIR(ValueType value) noexcept { Reg::Write<F_EPDIR>(value); }
    static auto ReadLSDEV() noexcept -> ValueType { return Reg::Read<F_LSDEV>(); }
    static void WriteLSDEV(ValueType value) noexcept { Reg::Write<F_LSDEV>(value); }
    static auto ReadEPTYP() noexcept -> ValueType { return Reg::Read<F_EPTYP>(); }
    static void WriteEPTYP(ValueType value) noexcept { Reg::Write<F_EPTYP>(value); }
    static auto ReadMCNT() noexcept -> ValueType { return Reg::Read<F_MCNT>(); }
    static void WriteMCNT(ValueType value) noexcept { Reg::Write<F_MCNT>(value); }
    static auto ReadDAD() noexcept -> ValueType { return Reg::Read<F_DAD>(); }
    static void WriteDAD(ValueType value) noexcept { Reg::Write<F_DAD>(value); }
    static auto ReadODDFRM() noexcept -> ValueType { return Reg::Read<F_ODDFRM>(); }
    static void WriteODDFRM(ValueType value) noexcept { Reg::Write<F_ODDFRM>(value); }
    static auto ReadCHDIS() noexcept -> ValueType { return Reg::Read<F_CHDIS>(); }
    static void WriteCHDIS(ValueType value) noexcept { Reg::Write<F_CHDIS>(value); }
    static auto ReadCHENA() noexcept -> ValueType { return Reg::Read<F_CHENA>(); }
    static void WriteCHENA(ValueType value) noexcept { Reg::Write<F_CHENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005e0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MPSIZ = CortexM3::Field<ValueType, 0, 11>;
    using F_EPNUM = CortexM3::Field<ValueType, 11, 4>;
    using F_EPDIR = CortexM3::Field<ValueType, 15, 1>;
    using F_LSDEV = CortexM3::Field<ValueType, 17, 1>;
    using F_EPTYP = CortexM3::Field<ValueType, 18, 2>;
    using F_MCNT = CortexM3::Field<ValueType, 20, 2>;
    using F_DAD = CortexM3::Field<ValueType, 22, 7>;
    using F_ODDFRM = CortexM3::Field<ValueType, 29, 1>;
    using F_CHDIS = CortexM3::Field<ValueType, 30, 1>;
    using F_CHENA = CortexM3::Field<ValueType, 31, 1>;
};

class FS_HCINT0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }
    static auto ReadCHH() noexcept -> ValueType { return Reg::Read<F_CHH>(); }
    static void WriteCHH(ValueType value) noexcept { Reg::Write<F_CHH>(value); }
    static auto ReadSTALL() noexcept -> ValueType { return Reg::Read<F_STALL>(); }
    static void WriteSTALL(ValueType value) noexcept { Reg::Write<F_STALL>(value); }
    static auto ReadNAK() noexcept -> ValueType { return Reg::Read<F_NAK>(); }
    static void WriteNAK(ValueType value) noexcept { Reg::Write<F_NAK>(value); }
    static auto ReadACK() noexcept -> ValueType { return Reg::Read<F_ACK>(); }
    static void WriteACK(ValueType value) noexcept { Reg::Write<F_ACK>(value); }
    static auto ReadTXERR() noexcept -> ValueType { return Reg::Read<F_TXERR>(); }
    static void WriteTXERR(ValueType value) noexcept { Reg::Write<F_TXERR>(value); }
    static auto ReadBBERR() noexcept -> ValueType { return Reg::Read<F_BBERR>(); }
    static void WriteBBERR(ValueType value) noexcept { Reg::Write<F_BBERR>(value); }
    static auto ReadFRMOR() noexcept -> ValueType { return Reg::Read<F_FRMOR>(); }
    static void WriteFRMOR(ValueType value) noexcept { Reg::Write<F_FRMOR>(value); }
    static auto ReadDTERR() noexcept -> ValueType { return Reg::Read<F_DTERR>(); }
    static void WriteDTERR(ValueType value) noexcept { Reg::Write<F_DTERR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000508;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
    using F_CHH = CortexM3::Field<ValueType, 1, 1>;
    using F_STALL = CortexM3::Field<ValueType, 3, 1>;
    using F_NAK = CortexM3::Field<ValueType, 4, 1>;
    using F_ACK = CortexM3::Field<ValueType, 5, 1>;
    using F_TXERR = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERR = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMOR = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERR = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINT1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }
    static auto ReadCHH() noexcept -> ValueType { return Reg::Read<F_CHH>(); }
    static void WriteCHH(ValueType value) noexcept { Reg::Write<F_CHH>(value); }
    static auto ReadSTALL() noexcept -> ValueType { return Reg::Read<F_STALL>(); }
    static void WriteSTALL(ValueType value) noexcept { Reg::Write<F_STALL>(value); }
    static auto ReadNAK() noexcept -> ValueType { return Reg::Read<F_NAK>(); }
    static void WriteNAK(ValueType value) noexcept { Reg::Write<F_NAK>(value); }
    static auto ReadACK() noexcept -> ValueType { return Reg::Read<F_ACK>(); }
    static void WriteACK(ValueType value) noexcept { Reg::Write<F_ACK>(value); }
    static auto ReadTXERR() noexcept -> ValueType { return Reg::Read<F_TXERR>(); }
    static void WriteTXERR(ValueType value) noexcept { Reg::Write<F_TXERR>(value); }
    static auto ReadBBERR() noexcept -> ValueType { return Reg::Read<F_BBERR>(); }
    static void WriteBBERR(ValueType value) noexcept { Reg::Write<F_BBERR>(value); }
    static auto ReadFRMOR() noexcept -> ValueType { return Reg::Read<F_FRMOR>(); }
    static void WriteFRMOR(ValueType value) noexcept { Reg::Write<F_FRMOR>(value); }
    static auto ReadDTERR() noexcept -> ValueType { return Reg::Read<F_DTERR>(); }
    static void WriteDTERR(ValueType value) noexcept { Reg::Write<F_DTERR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000528;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
    using F_CHH = CortexM3::Field<ValueType, 1, 1>;
    using F_STALL = CortexM3::Field<ValueType, 3, 1>;
    using F_NAK = CortexM3::Field<ValueType, 4, 1>;
    using F_ACK = CortexM3::Field<ValueType, 5, 1>;
    using F_TXERR = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERR = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMOR = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERR = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINT2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }
    static auto ReadCHH() noexcept -> ValueType { return Reg::Read<F_CHH>(); }
    static void WriteCHH(ValueType value) noexcept { Reg::Write<F_CHH>(value); }
    static auto ReadSTALL() noexcept -> ValueType { return Reg::Read<F_STALL>(); }
    static void WriteSTALL(ValueType value) noexcept { Reg::Write<F_STALL>(value); }
    static auto ReadNAK() noexcept -> ValueType { return Reg::Read<F_NAK>(); }
    static void WriteNAK(ValueType value) noexcept { Reg::Write<F_NAK>(value); }
    static auto ReadACK() noexcept -> ValueType { return Reg::Read<F_ACK>(); }
    static void WriteACK(ValueType value) noexcept { Reg::Write<F_ACK>(value); }
    static auto ReadTXERR() noexcept -> ValueType { return Reg::Read<F_TXERR>(); }
    static void WriteTXERR(ValueType value) noexcept { Reg::Write<F_TXERR>(value); }
    static auto ReadBBERR() noexcept -> ValueType { return Reg::Read<F_BBERR>(); }
    static void WriteBBERR(ValueType value) noexcept { Reg::Write<F_BBERR>(value); }
    static auto ReadFRMOR() noexcept -> ValueType { return Reg::Read<F_FRMOR>(); }
    static void WriteFRMOR(ValueType value) noexcept { Reg::Write<F_FRMOR>(value); }
    static auto ReadDTERR() noexcept -> ValueType { return Reg::Read<F_DTERR>(); }
    static void WriteDTERR(ValueType value) noexcept { Reg::Write<F_DTERR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000548;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
    using F_CHH = CortexM3::Field<ValueType, 1, 1>;
    using F_STALL = CortexM3::Field<ValueType, 3, 1>;
    using F_NAK = CortexM3::Field<ValueType, 4, 1>;
    using F_ACK = CortexM3::Field<ValueType, 5, 1>;
    using F_TXERR = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERR = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMOR = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERR = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINT3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }
    static auto ReadCHH() noexcept -> ValueType { return Reg::Read<F_CHH>(); }
    static void WriteCHH(ValueType value) noexcept { Reg::Write<F_CHH>(value); }
    static auto ReadSTALL() noexcept -> ValueType { return Reg::Read<F_STALL>(); }
    static void WriteSTALL(ValueType value) noexcept { Reg::Write<F_STALL>(value); }
    static auto ReadNAK() noexcept -> ValueType { return Reg::Read<F_NAK>(); }
    static void WriteNAK(ValueType value) noexcept { Reg::Write<F_NAK>(value); }
    static auto ReadACK() noexcept -> ValueType { return Reg::Read<F_ACK>(); }
    static void WriteACK(ValueType value) noexcept { Reg::Write<F_ACK>(value); }
    static auto ReadTXERR() noexcept -> ValueType { return Reg::Read<F_TXERR>(); }
    static void WriteTXERR(ValueType value) noexcept { Reg::Write<F_TXERR>(value); }
    static auto ReadBBERR() noexcept -> ValueType { return Reg::Read<F_BBERR>(); }
    static void WriteBBERR(ValueType value) noexcept { Reg::Write<F_BBERR>(value); }
    static auto ReadFRMOR() noexcept -> ValueType { return Reg::Read<F_FRMOR>(); }
    static void WriteFRMOR(ValueType value) noexcept { Reg::Write<F_FRMOR>(value); }
    static auto ReadDTERR() noexcept -> ValueType { return Reg::Read<F_DTERR>(); }
    static void WriteDTERR(ValueType value) noexcept { Reg::Write<F_DTERR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000568;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
    using F_CHH = CortexM3::Field<ValueType, 1, 1>;
    using F_STALL = CortexM3::Field<ValueType, 3, 1>;
    using F_NAK = CortexM3::Field<ValueType, 4, 1>;
    using F_ACK = CortexM3::Field<ValueType, 5, 1>;
    using F_TXERR = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERR = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMOR = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERR = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINT4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }
    static auto ReadCHH() noexcept -> ValueType { return Reg::Read<F_CHH>(); }
    static void WriteCHH(ValueType value) noexcept { Reg::Write<F_CHH>(value); }
    static auto ReadSTALL() noexcept -> ValueType { return Reg::Read<F_STALL>(); }
    static void WriteSTALL(ValueType value) noexcept { Reg::Write<F_STALL>(value); }
    static auto ReadNAK() noexcept -> ValueType { return Reg::Read<F_NAK>(); }
    static void WriteNAK(ValueType value) noexcept { Reg::Write<F_NAK>(value); }
    static auto ReadACK() noexcept -> ValueType { return Reg::Read<F_ACK>(); }
    static void WriteACK(ValueType value) noexcept { Reg::Write<F_ACK>(value); }
    static auto ReadTXERR() noexcept -> ValueType { return Reg::Read<F_TXERR>(); }
    static void WriteTXERR(ValueType value) noexcept { Reg::Write<F_TXERR>(value); }
    static auto ReadBBERR() noexcept -> ValueType { return Reg::Read<F_BBERR>(); }
    static void WriteBBERR(ValueType value) noexcept { Reg::Write<F_BBERR>(value); }
    static auto ReadFRMOR() noexcept -> ValueType { return Reg::Read<F_FRMOR>(); }
    static void WriteFRMOR(ValueType value) noexcept { Reg::Write<F_FRMOR>(value); }
    static auto ReadDTERR() noexcept -> ValueType { return Reg::Read<F_DTERR>(); }
    static void WriteDTERR(ValueType value) noexcept { Reg::Write<F_DTERR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000588;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
    using F_CHH = CortexM3::Field<ValueType, 1, 1>;
    using F_STALL = CortexM3::Field<ValueType, 3, 1>;
    using F_NAK = CortexM3::Field<ValueType, 4, 1>;
    using F_ACK = CortexM3::Field<ValueType, 5, 1>;
    using F_TXERR = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERR = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMOR = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERR = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINT5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }
    static auto ReadCHH() noexcept -> ValueType { return Reg::Read<F_CHH>(); }
    static void WriteCHH(ValueType value) noexcept { Reg::Write<F_CHH>(value); }
    static auto ReadSTALL() noexcept -> ValueType { return Reg::Read<F_STALL>(); }
    static void WriteSTALL(ValueType value) noexcept { Reg::Write<F_STALL>(value); }
    static auto ReadNAK() noexcept -> ValueType { return Reg::Read<F_NAK>(); }
    static void WriteNAK(ValueType value) noexcept { Reg::Write<F_NAK>(value); }
    static auto ReadACK() noexcept -> ValueType { return Reg::Read<F_ACK>(); }
    static void WriteACK(ValueType value) noexcept { Reg::Write<F_ACK>(value); }
    static auto ReadTXERR() noexcept -> ValueType { return Reg::Read<F_TXERR>(); }
    static void WriteTXERR(ValueType value) noexcept { Reg::Write<F_TXERR>(value); }
    static auto ReadBBERR() noexcept -> ValueType { return Reg::Read<F_BBERR>(); }
    static void WriteBBERR(ValueType value) noexcept { Reg::Write<F_BBERR>(value); }
    static auto ReadFRMOR() noexcept -> ValueType { return Reg::Read<F_FRMOR>(); }
    static void WriteFRMOR(ValueType value) noexcept { Reg::Write<F_FRMOR>(value); }
    static auto ReadDTERR() noexcept -> ValueType { return Reg::Read<F_DTERR>(); }
    static void WriteDTERR(ValueType value) noexcept { Reg::Write<F_DTERR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005a8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
    using F_CHH = CortexM3::Field<ValueType, 1, 1>;
    using F_STALL = CortexM3::Field<ValueType, 3, 1>;
    using F_NAK = CortexM3::Field<ValueType, 4, 1>;
    using F_ACK = CortexM3::Field<ValueType, 5, 1>;
    using F_TXERR = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERR = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMOR = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERR = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINT6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }
    static auto ReadCHH() noexcept -> ValueType { return Reg::Read<F_CHH>(); }
    static void WriteCHH(ValueType value) noexcept { Reg::Write<F_CHH>(value); }
    static auto ReadSTALL() noexcept -> ValueType { return Reg::Read<F_STALL>(); }
    static void WriteSTALL(ValueType value) noexcept { Reg::Write<F_STALL>(value); }
    static auto ReadNAK() noexcept -> ValueType { return Reg::Read<F_NAK>(); }
    static void WriteNAK(ValueType value) noexcept { Reg::Write<F_NAK>(value); }
    static auto ReadACK() noexcept -> ValueType { return Reg::Read<F_ACK>(); }
    static void WriteACK(ValueType value) noexcept { Reg::Write<F_ACK>(value); }
    static auto ReadTXERR() noexcept -> ValueType { return Reg::Read<F_TXERR>(); }
    static void WriteTXERR(ValueType value) noexcept { Reg::Write<F_TXERR>(value); }
    static auto ReadBBERR() noexcept -> ValueType { return Reg::Read<F_BBERR>(); }
    static void WriteBBERR(ValueType value) noexcept { Reg::Write<F_BBERR>(value); }
    static auto ReadFRMOR() noexcept -> ValueType { return Reg::Read<F_FRMOR>(); }
    static void WriteFRMOR(ValueType value) noexcept { Reg::Write<F_FRMOR>(value); }
    static auto ReadDTERR() noexcept -> ValueType { return Reg::Read<F_DTERR>(); }
    static void WriteDTERR(ValueType value) noexcept { Reg::Write<F_DTERR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005c8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
    using F_CHH = CortexM3::Field<ValueType, 1, 1>;
    using F_STALL = CortexM3::Field<ValueType, 3, 1>;
    using F_NAK = CortexM3::Field<ValueType, 4, 1>;
    using F_ACK = CortexM3::Field<ValueType, 5, 1>;
    using F_TXERR = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERR = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMOR = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERR = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINT7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRC() noexcept -> ValueType { return Reg::Read<F_XFRC>(); }
    static void WriteXFRC(ValueType value) noexcept { Reg::Write<F_XFRC>(value); }
    static auto ReadCHH() noexcept -> ValueType { return Reg::Read<F_CHH>(); }
    static void WriteCHH(ValueType value) noexcept { Reg::Write<F_CHH>(value); }
    static auto ReadSTALL() noexcept -> ValueType { return Reg::Read<F_STALL>(); }
    static void WriteSTALL(ValueType value) noexcept { Reg::Write<F_STALL>(value); }
    static auto ReadNAK() noexcept -> ValueType { return Reg::Read<F_NAK>(); }
    static void WriteNAK(ValueType value) noexcept { Reg::Write<F_NAK>(value); }
    static auto ReadACK() noexcept -> ValueType { return Reg::Read<F_ACK>(); }
    static void WriteACK(ValueType value) noexcept { Reg::Write<F_ACK>(value); }
    static auto ReadTXERR() noexcept -> ValueType { return Reg::Read<F_TXERR>(); }
    static void WriteTXERR(ValueType value) noexcept { Reg::Write<F_TXERR>(value); }
    static auto ReadBBERR() noexcept -> ValueType { return Reg::Read<F_BBERR>(); }
    static void WriteBBERR(ValueType value) noexcept { Reg::Write<F_BBERR>(value); }
    static auto ReadFRMOR() noexcept -> ValueType { return Reg::Read<F_FRMOR>(); }
    static void WriteFRMOR(ValueType value) noexcept { Reg::Write<F_FRMOR>(value); }
    static auto ReadDTERR() noexcept -> ValueType { return Reg::Read<F_DTERR>(); }
    static void WriteDTERR(ValueType value) noexcept { Reg::Write<F_DTERR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005e8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRC = CortexM3::Field<ValueType, 0, 1>;
    using F_CHH = CortexM3::Field<ValueType, 1, 1>;
    using F_STALL = CortexM3::Field<ValueType, 3, 1>;
    using F_NAK = CortexM3::Field<ValueType, 4, 1>;
    using F_ACK = CortexM3::Field<ValueType, 5, 1>;
    using F_TXERR = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERR = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMOR = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERR = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINTMSK0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRCM() noexcept -> ValueType { return Reg::Read<F_XFRCM>(); }
    static void WriteXFRCM(ValueType value) noexcept { Reg::Write<F_XFRCM>(value); }
    static auto ReadCHHM() noexcept -> ValueType { return Reg::Read<F_CHHM>(); }
    static void WriteCHHM(ValueType value) noexcept { Reg::Write<F_CHHM>(value); }
    static auto ReadSTALLM() noexcept -> ValueType { return Reg::Read<F_STALLM>(); }
    static void WriteSTALLM(ValueType value) noexcept { Reg::Write<F_STALLM>(value); }
    static auto ReadNAKM() noexcept -> ValueType { return Reg::Read<F_NAKM>(); }
    static void WriteNAKM(ValueType value) noexcept { Reg::Write<F_NAKM>(value); }
    static auto ReadACKM() noexcept -> ValueType { return Reg::Read<F_ACKM>(); }
    static void WriteACKM(ValueType value) noexcept { Reg::Write<F_ACKM>(value); }
    static auto ReadNYET() noexcept -> ValueType { return Reg::Read<F_NYET>(); }
    static void WriteNYET(ValueType value) noexcept { Reg::Write<F_NYET>(value); }
    static auto ReadTXERRM() noexcept -> ValueType { return Reg::Read<F_TXERRM>(); }
    static void WriteTXERRM(ValueType value) noexcept { Reg::Write<F_TXERRM>(value); }
    static auto ReadBBERRM() noexcept -> ValueType { return Reg::Read<F_BBERRM>(); }
    static void WriteBBERRM(ValueType value) noexcept { Reg::Write<F_BBERRM>(value); }
    static auto ReadFRMORM() noexcept -> ValueType { return Reg::Read<F_FRMORM>(); }
    static void WriteFRMORM(ValueType value) noexcept { Reg::Write<F_FRMORM>(value); }
    static auto ReadDTERRM() noexcept -> ValueType { return Reg::Read<F_DTERRM>(); }
    static void WriteDTERRM(ValueType value) noexcept { Reg::Write<F_DTERRM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x5000050c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRCM = CortexM3::Field<ValueType, 0, 1>;
    using F_CHHM = CortexM3::Field<ValueType, 1, 1>;
    using F_STALLM = CortexM3::Field<ValueType, 3, 1>;
    using F_NAKM = CortexM3::Field<ValueType, 4, 1>;
    using F_ACKM = CortexM3::Field<ValueType, 5, 1>;
    using F_NYET = CortexM3::Field<ValueType, 6, 1>;
    using F_TXERRM = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERRM = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMORM = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERRM = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINTMSK1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRCM() noexcept -> ValueType { return Reg::Read<F_XFRCM>(); }
    static void WriteXFRCM(ValueType value) noexcept { Reg::Write<F_XFRCM>(value); }
    static auto ReadCHHM() noexcept -> ValueType { return Reg::Read<F_CHHM>(); }
    static void WriteCHHM(ValueType value) noexcept { Reg::Write<F_CHHM>(value); }
    static auto ReadSTALLM() noexcept -> ValueType { return Reg::Read<F_STALLM>(); }
    static void WriteSTALLM(ValueType value) noexcept { Reg::Write<F_STALLM>(value); }
    static auto ReadNAKM() noexcept -> ValueType { return Reg::Read<F_NAKM>(); }
    static void WriteNAKM(ValueType value) noexcept { Reg::Write<F_NAKM>(value); }
    static auto ReadACKM() noexcept -> ValueType { return Reg::Read<F_ACKM>(); }
    static void WriteACKM(ValueType value) noexcept { Reg::Write<F_ACKM>(value); }
    static auto ReadNYET() noexcept -> ValueType { return Reg::Read<F_NYET>(); }
    static void WriteNYET(ValueType value) noexcept { Reg::Write<F_NYET>(value); }
    static auto ReadTXERRM() noexcept -> ValueType { return Reg::Read<F_TXERRM>(); }
    static void WriteTXERRM(ValueType value) noexcept { Reg::Write<F_TXERRM>(value); }
    static auto ReadBBERRM() noexcept -> ValueType { return Reg::Read<F_BBERRM>(); }
    static void WriteBBERRM(ValueType value) noexcept { Reg::Write<F_BBERRM>(value); }
    static auto ReadFRMORM() noexcept -> ValueType { return Reg::Read<F_FRMORM>(); }
    static void WriteFRMORM(ValueType value) noexcept { Reg::Write<F_FRMORM>(value); }
    static auto ReadDTERRM() noexcept -> ValueType { return Reg::Read<F_DTERRM>(); }
    static void WriteDTERRM(ValueType value) noexcept { Reg::Write<F_DTERRM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x5000052c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRCM = CortexM3::Field<ValueType, 0, 1>;
    using F_CHHM = CortexM3::Field<ValueType, 1, 1>;
    using F_STALLM = CortexM3::Field<ValueType, 3, 1>;
    using F_NAKM = CortexM3::Field<ValueType, 4, 1>;
    using F_ACKM = CortexM3::Field<ValueType, 5, 1>;
    using F_NYET = CortexM3::Field<ValueType, 6, 1>;
    using F_TXERRM = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERRM = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMORM = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERRM = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINTMSK2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRCM() noexcept -> ValueType { return Reg::Read<F_XFRCM>(); }
    static void WriteXFRCM(ValueType value) noexcept { Reg::Write<F_XFRCM>(value); }
    static auto ReadCHHM() noexcept -> ValueType { return Reg::Read<F_CHHM>(); }
    static void WriteCHHM(ValueType value) noexcept { Reg::Write<F_CHHM>(value); }
    static auto ReadSTALLM() noexcept -> ValueType { return Reg::Read<F_STALLM>(); }
    static void WriteSTALLM(ValueType value) noexcept { Reg::Write<F_STALLM>(value); }
    static auto ReadNAKM() noexcept -> ValueType { return Reg::Read<F_NAKM>(); }
    static void WriteNAKM(ValueType value) noexcept { Reg::Write<F_NAKM>(value); }
    static auto ReadACKM() noexcept -> ValueType { return Reg::Read<F_ACKM>(); }
    static void WriteACKM(ValueType value) noexcept { Reg::Write<F_ACKM>(value); }
    static auto ReadNYET() noexcept -> ValueType { return Reg::Read<F_NYET>(); }
    static void WriteNYET(ValueType value) noexcept { Reg::Write<F_NYET>(value); }
    static auto ReadTXERRM() noexcept -> ValueType { return Reg::Read<F_TXERRM>(); }
    static void WriteTXERRM(ValueType value) noexcept { Reg::Write<F_TXERRM>(value); }
    static auto ReadBBERRM() noexcept -> ValueType { return Reg::Read<F_BBERRM>(); }
    static void WriteBBERRM(ValueType value) noexcept { Reg::Write<F_BBERRM>(value); }
    static auto ReadFRMORM() noexcept -> ValueType { return Reg::Read<F_FRMORM>(); }
    static void WriteFRMORM(ValueType value) noexcept { Reg::Write<F_FRMORM>(value); }
    static auto ReadDTERRM() noexcept -> ValueType { return Reg::Read<F_DTERRM>(); }
    static void WriteDTERRM(ValueType value) noexcept { Reg::Write<F_DTERRM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x5000054c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRCM = CortexM3::Field<ValueType, 0, 1>;
    using F_CHHM = CortexM3::Field<ValueType, 1, 1>;
    using F_STALLM = CortexM3::Field<ValueType, 3, 1>;
    using F_NAKM = CortexM3::Field<ValueType, 4, 1>;
    using F_ACKM = CortexM3::Field<ValueType, 5, 1>;
    using F_NYET = CortexM3::Field<ValueType, 6, 1>;
    using F_TXERRM = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERRM = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMORM = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERRM = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINTMSK3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRCM() noexcept -> ValueType { return Reg::Read<F_XFRCM>(); }
    static void WriteXFRCM(ValueType value) noexcept { Reg::Write<F_XFRCM>(value); }
    static auto ReadCHHM() noexcept -> ValueType { return Reg::Read<F_CHHM>(); }
    static void WriteCHHM(ValueType value) noexcept { Reg::Write<F_CHHM>(value); }
    static auto ReadSTALLM() noexcept -> ValueType { return Reg::Read<F_STALLM>(); }
    static void WriteSTALLM(ValueType value) noexcept { Reg::Write<F_STALLM>(value); }
    static auto ReadNAKM() noexcept -> ValueType { return Reg::Read<F_NAKM>(); }
    static void WriteNAKM(ValueType value) noexcept { Reg::Write<F_NAKM>(value); }
    static auto ReadACKM() noexcept -> ValueType { return Reg::Read<F_ACKM>(); }
    static void WriteACKM(ValueType value) noexcept { Reg::Write<F_ACKM>(value); }
    static auto ReadNYET() noexcept -> ValueType { return Reg::Read<F_NYET>(); }
    static void WriteNYET(ValueType value) noexcept { Reg::Write<F_NYET>(value); }
    static auto ReadTXERRM() noexcept -> ValueType { return Reg::Read<F_TXERRM>(); }
    static void WriteTXERRM(ValueType value) noexcept { Reg::Write<F_TXERRM>(value); }
    static auto ReadBBERRM() noexcept -> ValueType { return Reg::Read<F_BBERRM>(); }
    static void WriteBBERRM(ValueType value) noexcept { Reg::Write<F_BBERRM>(value); }
    static auto ReadFRMORM() noexcept -> ValueType { return Reg::Read<F_FRMORM>(); }
    static void WriteFRMORM(ValueType value) noexcept { Reg::Write<F_FRMORM>(value); }
    static auto ReadDTERRM() noexcept -> ValueType { return Reg::Read<F_DTERRM>(); }
    static void WriteDTERRM(ValueType value) noexcept { Reg::Write<F_DTERRM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x5000056c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRCM = CortexM3::Field<ValueType, 0, 1>;
    using F_CHHM = CortexM3::Field<ValueType, 1, 1>;
    using F_STALLM = CortexM3::Field<ValueType, 3, 1>;
    using F_NAKM = CortexM3::Field<ValueType, 4, 1>;
    using F_ACKM = CortexM3::Field<ValueType, 5, 1>;
    using F_NYET = CortexM3::Field<ValueType, 6, 1>;
    using F_TXERRM = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERRM = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMORM = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERRM = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINTMSK4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRCM() noexcept -> ValueType { return Reg::Read<F_XFRCM>(); }
    static void WriteXFRCM(ValueType value) noexcept { Reg::Write<F_XFRCM>(value); }
    static auto ReadCHHM() noexcept -> ValueType { return Reg::Read<F_CHHM>(); }
    static void WriteCHHM(ValueType value) noexcept { Reg::Write<F_CHHM>(value); }
    static auto ReadSTALLM() noexcept -> ValueType { return Reg::Read<F_STALLM>(); }
    static void WriteSTALLM(ValueType value) noexcept { Reg::Write<F_STALLM>(value); }
    static auto ReadNAKM() noexcept -> ValueType { return Reg::Read<F_NAKM>(); }
    static void WriteNAKM(ValueType value) noexcept { Reg::Write<F_NAKM>(value); }
    static auto ReadACKM() noexcept -> ValueType { return Reg::Read<F_ACKM>(); }
    static void WriteACKM(ValueType value) noexcept { Reg::Write<F_ACKM>(value); }
    static auto ReadNYET() noexcept -> ValueType { return Reg::Read<F_NYET>(); }
    static void WriteNYET(ValueType value) noexcept { Reg::Write<F_NYET>(value); }
    static auto ReadTXERRM() noexcept -> ValueType { return Reg::Read<F_TXERRM>(); }
    static void WriteTXERRM(ValueType value) noexcept { Reg::Write<F_TXERRM>(value); }
    static auto ReadBBERRM() noexcept -> ValueType { return Reg::Read<F_BBERRM>(); }
    static void WriteBBERRM(ValueType value) noexcept { Reg::Write<F_BBERRM>(value); }
    static auto ReadFRMORM() noexcept -> ValueType { return Reg::Read<F_FRMORM>(); }
    static void WriteFRMORM(ValueType value) noexcept { Reg::Write<F_FRMORM>(value); }
    static auto ReadDTERRM() noexcept -> ValueType { return Reg::Read<F_DTERRM>(); }
    static void WriteDTERRM(ValueType value) noexcept { Reg::Write<F_DTERRM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x5000058c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRCM = CortexM3::Field<ValueType, 0, 1>;
    using F_CHHM = CortexM3::Field<ValueType, 1, 1>;
    using F_STALLM = CortexM3::Field<ValueType, 3, 1>;
    using F_NAKM = CortexM3::Field<ValueType, 4, 1>;
    using F_ACKM = CortexM3::Field<ValueType, 5, 1>;
    using F_NYET = CortexM3::Field<ValueType, 6, 1>;
    using F_TXERRM = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERRM = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMORM = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERRM = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINTMSK5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRCM() noexcept -> ValueType { return Reg::Read<F_XFRCM>(); }
    static void WriteXFRCM(ValueType value) noexcept { Reg::Write<F_XFRCM>(value); }
    static auto ReadCHHM() noexcept -> ValueType { return Reg::Read<F_CHHM>(); }
    static void WriteCHHM(ValueType value) noexcept { Reg::Write<F_CHHM>(value); }
    static auto ReadSTALLM() noexcept -> ValueType { return Reg::Read<F_STALLM>(); }
    static void WriteSTALLM(ValueType value) noexcept { Reg::Write<F_STALLM>(value); }
    static auto ReadNAKM() noexcept -> ValueType { return Reg::Read<F_NAKM>(); }
    static void WriteNAKM(ValueType value) noexcept { Reg::Write<F_NAKM>(value); }
    static auto ReadACKM() noexcept -> ValueType { return Reg::Read<F_ACKM>(); }
    static void WriteACKM(ValueType value) noexcept { Reg::Write<F_ACKM>(value); }
    static auto ReadNYET() noexcept -> ValueType { return Reg::Read<F_NYET>(); }
    static void WriteNYET(ValueType value) noexcept { Reg::Write<F_NYET>(value); }
    static auto ReadTXERRM() noexcept -> ValueType { return Reg::Read<F_TXERRM>(); }
    static void WriteTXERRM(ValueType value) noexcept { Reg::Write<F_TXERRM>(value); }
    static auto ReadBBERRM() noexcept -> ValueType { return Reg::Read<F_BBERRM>(); }
    static void WriteBBERRM(ValueType value) noexcept { Reg::Write<F_BBERRM>(value); }
    static auto ReadFRMORM() noexcept -> ValueType { return Reg::Read<F_FRMORM>(); }
    static void WriteFRMORM(ValueType value) noexcept { Reg::Write<F_FRMORM>(value); }
    static auto ReadDTERRM() noexcept -> ValueType { return Reg::Read<F_DTERRM>(); }
    static void WriteDTERRM(ValueType value) noexcept { Reg::Write<F_DTERRM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005ac;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRCM = CortexM3::Field<ValueType, 0, 1>;
    using F_CHHM = CortexM3::Field<ValueType, 1, 1>;
    using F_STALLM = CortexM3::Field<ValueType, 3, 1>;
    using F_NAKM = CortexM3::Field<ValueType, 4, 1>;
    using F_ACKM = CortexM3::Field<ValueType, 5, 1>;
    using F_NYET = CortexM3::Field<ValueType, 6, 1>;
    using F_TXERRM = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERRM = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMORM = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERRM = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINTMSK6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRCM() noexcept -> ValueType { return Reg::Read<F_XFRCM>(); }
    static void WriteXFRCM(ValueType value) noexcept { Reg::Write<F_XFRCM>(value); }
    static auto ReadCHHM() noexcept -> ValueType { return Reg::Read<F_CHHM>(); }
    static void WriteCHHM(ValueType value) noexcept { Reg::Write<F_CHHM>(value); }
    static auto ReadSTALLM() noexcept -> ValueType { return Reg::Read<F_STALLM>(); }
    static void WriteSTALLM(ValueType value) noexcept { Reg::Write<F_STALLM>(value); }
    static auto ReadNAKM() noexcept -> ValueType { return Reg::Read<F_NAKM>(); }
    static void WriteNAKM(ValueType value) noexcept { Reg::Write<F_NAKM>(value); }
    static auto ReadACKM() noexcept -> ValueType { return Reg::Read<F_ACKM>(); }
    static void WriteACKM(ValueType value) noexcept { Reg::Write<F_ACKM>(value); }
    static auto ReadNYET() noexcept -> ValueType { return Reg::Read<F_NYET>(); }
    static void WriteNYET(ValueType value) noexcept { Reg::Write<F_NYET>(value); }
    static auto ReadTXERRM() noexcept -> ValueType { return Reg::Read<F_TXERRM>(); }
    static void WriteTXERRM(ValueType value) noexcept { Reg::Write<F_TXERRM>(value); }
    static auto ReadBBERRM() noexcept -> ValueType { return Reg::Read<F_BBERRM>(); }
    static void WriteBBERRM(ValueType value) noexcept { Reg::Write<F_BBERRM>(value); }
    static auto ReadFRMORM() noexcept -> ValueType { return Reg::Read<F_FRMORM>(); }
    static void WriteFRMORM(ValueType value) noexcept { Reg::Write<F_FRMORM>(value); }
    static auto ReadDTERRM() noexcept -> ValueType { return Reg::Read<F_DTERRM>(); }
    static void WriteDTERRM(ValueType value) noexcept { Reg::Write<F_DTERRM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005cc;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRCM = CortexM3::Field<ValueType, 0, 1>;
    using F_CHHM = CortexM3::Field<ValueType, 1, 1>;
    using F_STALLM = CortexM3::Field<ValueType, 3, 1>;
    using F_NAKM = CortexM3::Field<ValueType, 4, 1>;
    using F_ACKM = CortexM3::Field<ValueType, 5, 1>;
    using F_NYET = CortexM3::Field<ValueType, 6, 1>;
    using F_TXERRM = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERRM = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMORM = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERRM = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCINTMSK7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRCM() noexcept -> ValueType { return Reg::Read<F_XFRCM>(); }
    static void WriteXFRCM(ValueType value) noexcept { Reg::Write<F_XFRCM>(value); }
    static auto ReadCHHM() noexcept -> ValueType { return Reg::Read<F_CHHM>(); }
    static void WriteCHHM(ValueType value) noexcept { Reg::Write<F_CHHM>(value); }
    static auto ReadSTALLM() noexcept -> ValueType { return Reg::Read<F_STALLM>(); }
    static void WriteSTALLM(ValueType value) noexcept { Reg::Write<F_STALLM>(value); }
    static auto ReadNAKM() noexcept -> ValueType { return Reg::Read<F_NAKM>(); }
    static void WriteNAKM(ValueType value) noexcept { Reg::Write<F_NAKM>(value); }
    static auto ReadACKM() noexcept -> ValueType { return Reg::Read<F_ACKM>(); }
    static void WriteACKM(ValueType value) noexcept { Reg::Write<F_ACKM>(value); }
    static auto ReadNYET() noexcept -> ValueType { return Reg::Read<F_NYET>(); }
    static void WriteNYET(ValueType value) noexcept { Reg::Write<F_NYET>(value); }
    static auto ReadTXERRM() noexcept -> ValueType { return Reg::Read<F_TXERRM>(); }
    static void WriteTXERRM(ValueType value) noexcept { Reg::Write<F_TXERRM>(value); }
    static auto ReadBBERRM() noexcept -> ValueType { return Reg::Read<F_BBERRM>(); }
    static void WriteBBERRM(ValueType value) noexcept { Reg::Write<F_BBERRM>(value); }
    static auto ReadFRMORM() noexcept -> ValueType { return Reg::Read<F_FRMORM>(); }
    static void WriteFRMORM(ValueType value) noexcept { Reg::Write<F_FRMORM>(value); }
    static auto ReadDTERRM() noexcept -> ValueType { return Reg::Read<F_DTERRM>(); }
    static void WriteDTERRM(ValueType value) noexcept { Reg::Write<F_DTERRM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005ec;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRCM = CortexM3::Field<ValueType, 0, 1>;
    using F_CHHM = CortexM3::Field<ValueType, 1, 1>;
    using F_STALLM = CortexM3::Field<ValueType, 3, 1>;
    using F_NAKM = CortexM3::Field<ValueType, 4, 1>;
    using F_ACKM = CortexM3::Field<ValueType, 5, 1>;
    using F_NYET = CortexM3::Field<ValueType, 6, 1>;
    using F_TXERRM = CortexM3::Field<ValueType, 7, 1>;
    using F_BBERRM = CortexM3::Field<ValueType, 8, 1>;
    using F_FRMORM = CortexM3::Field<ValueType, 9, 1>;
    using F_DTERRM = CortexM3::Field<ValueType, 10, 1>;
};

class FS_HCTSIZ0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadDPID() noexcept -> ValueType { return Reg::Read<F_DPID>(); }
    static void WriteDPID(ValueType value) noexcept { Reg::Write<F_DPID>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000510;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_DPID = CortexM3::Field<ValueType, 29, 2>;
};

class FS_HCTSIZ1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadDPID() noexcept -> ValueType { return Reg::Read<F_DPID>(); }
    static void WriteDPID(ValueType value) noexcept { Reg::Write<F_DPID>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000530;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_DPID = CortexM3::Field<ValueType, 29, 2>;
};

class FS_HCTSIZ2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadDPID() noexcept -> ValueType { return Reg::Read<F_DPID>(); }
    static void WriteDPID(ValueType value) noexcept { Reg::Write<F_DPID>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000550;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_DPID = CortexM3::Field<ValueType, 29, 2>;
};

class FS_HCTSIZ3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadDPID() noexcept -> ValueType { return Reg::Read<F_DPID>(); }
    static void WriteDPID(ValueType value) noexcept { Reg::Write<F_DPID>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000570;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_DPID = CortexM3::Field<ValueType, 29, 2>;
};

class FS_HCTSIZ4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadDPID() noexcept -> ValueType { return Reg::Read<F_DPID>(); }
    static void WriteDPID(ValueType value) noexcept { Reg::Write<F_DPID>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000590;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_DPID = CortexM3::Field<ValueType, 29, 2>;
};

class FS_HCTSIZ5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadDPID() noexcept -> ValueType { return Reg::Read<F_DPID>(); }
    static void WriteDPID(ValueType value) noexcept { Reg::Write<F_DPID>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005b0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_DPID = CortexM3::Field<ValueType, 29, 2>;
};

class FS_HCTSIZ6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadDPID() noexcept -> ValueType { return Reg::Read<F_DPID>(); }
    static void WriteDPID(ValueType value) noexcept { Reg::Write<F_DPID>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005d0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_DPID = CortexM3::Field<ValueType, 29, 2>;
};

class FS_HCTSIZ7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadXFRSIZ() noexcept -> ValueType { return Reg::Read<F_XFRSIZ>(); }
    static void WriteXFRSIZ(ValueType value) noexcept { Reg::Write<F_XFRSIZ>(value); }
    static auto ReadPKTCNT() noexcept -> ValueType { return Reg::Read<F_PKTCNT>(); }
    static void WritePKTCNT(ValueType value) noexcept { Reg::Write<F_PKTCNT>(value); }
    static auto ReadDPID() noexcept -> ValueType { return Reg::Read<F_DPID>(); }
    static void WriteDPID(ValueType value) noexcept { Reg::Write<F_DPID>(value); }

private:
    static constexpr std::uintptr_t Address = 0x500005f0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_XFRSIZ = CortexM3::Field<ValueType, 0, 19>;
    using F_PKTCNT = CortexM3::Field<ValueType, 19, 10>;
    using F_DPID = CortexM3::Field<ValueType, 29, 2>;
};

} // namespace STM32F103::OTG_FS_HOST
