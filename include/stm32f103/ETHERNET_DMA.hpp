#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::ETHERNET_DMA {

class DMABMR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00020101;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSR() noexcept -> ValueType { return Reg::Read<F_SR>(); }
    static void WriteSR(ValueType value) noexcept { Reg::Write<F_SR>(value); }
    static auto ReadDA() noexcept -> ValueType { return Reg::Read<F_DA>(); }
    static void WriteDA(ValueType value) noexcept { Reg::Write<F_DA>(value); }
    static auto ReadDSL() noexcept -> ValueType { return Reg::Read<F_DSL>(); }
    static void WriteDSL(ValueType value) noexcept { Reg::Write<F_DSL>(value); }
    static auto ReadPBL() noexcept -> ValueType { return Reg::Read<F_PBL>(); }
    static void WritePBL(ValueType value) noexcept { Reg::Write<F_PBL>(value); }
    static auto ReadRTPR() noexcept -> ValueType { return Reg::Read<F_RTPR>(); }
    static void WriteRTPR(ValueType value) noexcept { Reg::Write<F_RTPR>(value); }
    static auto ReadFB() noexcept -> ValueType { return Reg::Read<F_FB>(); }
    static void WriteFB(ValueType value) noexcept { Reg::Write<F_FB>(value); }
    static auto ReadRDP() noexcept -> ValueType { return Reg::Read<F_RDP>(); }
    static void WriteRDP(ValueType value) noexcept { Reg::Write<F_RDP>(value); }
    static auto ReadUSP() noexcept -> ValueType { return Reg::Read<F_USP>(); }
    static void WriteUSP(ValueType value) noexcept { Reg::Write<F_USP>(value); }
    static auto ReadFPM() noexcept -> ValueType { return Reg::Read<F_FPM>(); }
    static void WriteFPM(ValueType value) noexcept { Reg::Write<F_FPM>(value); }
    static auto ReadAAB() noexcept -> ValueType { return Reg::Read<F_AAB>(); }
    static void WriteAAB(ValueType value) noexcept { Reg::Write<F_AAB>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40029000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SR = CortexM3::Field<ValueType, 0, 1>;
    using F_DA = CortexM3::Field<ValueType, 1, 1>;
    using F_DSL = CortexM3::Field<ValueType, 2, 5>;
    using F_PBL = CortexM3::Field<ValueType, 8, 6>;
    using F_RTPR = CortexM3::Field<ValueType, 14, 2>;
    using F_FB = CortexM3::Field<ValueType, 16, 1>;
    using F_RDP = CortexM3::Field<ValueType, 17, 6>;
    using F_USP = CortexM3::Field<ValueType, 23, 1>;
    using F_FPM = CortexM3::Field<ValueType, 24, 1>;
    using F_AAB = CortexM3::Field<ValueType, 25, 1>;
};

class DMATPDR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTPD() noexcept -> ValueType { return Reg::Read<F_TPD>(); }
    static void WriteTPD(ValueType value) noexcept { Reg::Write<F_TPD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40029004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TPD = CortexM3::Field<ValueType, 0, 32>;
};

class DMARPDR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRPD() noexcept -> ValueType { return Reg::Read<F_RPD>(); }
    static void WriteRPD(ValueType value) noexcept { Reg::Write<F_RPD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40029008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RPD = CortexM3::Field<ValueType, 0, 32>;
};

class DMARDLAR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSRL() noexcept -> ValueType { return Reg::Read<F_SRL>(); }
    static void WriteSRL(ValueType value) noexcept { Reg::Write<F_SRL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002900c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SRL = CortexM3::Field<ValueType, 0, 32>;
};

class DMATDLAR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSTL() noexcept -> ValueType { return Reg::Read<F_STL>(); }
    static void WriteSTL(ValueType value) noexcept { Reg::Write<F_STL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40029010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STL = CortexM3::Field<ValueType, 0, 32>;
};

class DMASR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTS() noexcept -> ValueType { return Reg::Read<F_TS>(); }
    static void WriteTS(ValueType value) noexcept { Reg::Write<F_TS>(value); }
    static auto ReadTPSS() noexcept -> ValueType { return Reg::Read<F_TPSS>(); }
    static void WriteTPSS(ValueType value) noexcept { Reg::Write<F_TPSS>(value); }
    static auto ReadTBUS() noexcept -> ValueType { return Reg::Read<F_TBUS>(); }
    static void WriteTBUS(ValueType value) noexcept { Reg::Write<F_TBUS>(value); }
    static auto ReadTJTS() noexcept -> ValueType { return Reg::Read<F_TJTS>(); }
    static void WriteTJTS(ValueType value) noexcept { Reg::Write<F_TJTS>(value); }
    static auto ReadROS() noexcept -> ValueType { return Reg::Read<F_ROS>(); }
    static void WriteROS(ValueType value) noexcept { Reg::Write<F_ROS>(value); }
    static auto ReadTUS() noexcept -> ValueType { return Reg::Read<F_TUS>(); }
    static void WriteTUS(ValueType value) noexcept { Reg::Write<F_TUS>(value); }
    static auto ReadRS() noexcept -> ValueType { return Reg::Read<F_RS>(); }
    static void WriteRS(ValueType value) noexcept { Reg::Write<F_RS>(value); }
    static auto ReadRBUS() noexcept -> ValueType { return Reg::Read<F_RBUS>(); }
    static void WriteRBUS(ValueType value) noexcept { Reg::Write<F_RBUS>(value); }
    static auto ReadRPSS() noexcept -> ValueType { return Reg::Read<F_RPSS>(); }
    static void WriteRPSS(ValueType value) noexcept { Reg::Write<F_RPSS>(value); }
    static auto ReadPWTS() noexcept -> ValueType { return Reg::Read<F_PWTS>(); }
    static void WritePWTS(ValueType value) noexcept { Reg::Write<F_PWTS>(value); }
    static auto ReadETS() noexcept -> ValueType { return Reg::Read<F_ETS>(); }
    static void WriteETS(ValueType value) noexcept { Reg::Write<F_ETS>(value); }
    static auto ReadFBES() noexcept -> ValueType { return Reg::Read<F_FBES>(); }
    static void WriteFBES(ValueType value) noexcept { Reg::Write<F_FBES>(value); }
    static auto ReadERS() noexcept -> ValueType { return Reg::Read<F_ERS>(); }
    static void WriteERS(ValueType value) noexcept { Reg::Write<F_ERS>(value); }
    static auto ReadAIS() noexcept -> ValueType { return Reg::Read<F_AIS>(); }
    static void WriteAIS(ValueType value) noexcept { Reg::Write<F_AIS>(value); }
    static auto ReadNIS() noexcept -> ValueType { return Reg::Read<F_NIS>(); }
    static void WriteNIS(ValueType value) noexcept { Reg::Write<F_NIS>(value); }
    static auto ReadRPS() noexcept -> ValueType { return Reg::Read<F_RPS>(); }
    static auto ReadTPS() noexcept -> ValueType { return Reg::Read<F_TPS>(); }
    static auto ReadEBS() noexcept -> ValueType { return Reg::Read<F_EBS>(); }
    static auto ReadMMCS() noexcept -> ValueType { return Reg::Read<F_MMCS>(); }
    static auto ReadPMTS() noexcept -> ValueType { return Reg::Read<F_PMTS>(); }
    static auto ReadTSTS() noexcept -> ValueType { return Reg::Read<F_TSTS>(); }

private:
    static constexpr std::uintptr_t Address = 0x40029014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TS = CortexM3::Field<ValueType, 0, 1>;
    using F_TPSS = CortexM3::Field<ValueType, 1, 1>;
    using F_TBUS = CortexM3::Field<ValueType, 2, 1>;
    using F_TJTS = CortexM3::Field<ValueType, 3, 1>;
    using F_ROS = CortexM3::Field<ValueType, 4, 1>;
    using F_TUS = CortexM3::Field<ValueType, 5, 1>;
    using F_RS = CortexM3::Field<ValueType, 6, 1>;
    using F_RBUS = CortexM3::Field<ValueType, 7, 1>;
    using F_RPSS = CortexM3::Field<ValueType, 8, 1>;
    using F_PWTS = CortexM3::Field<ValueType, 9, 1>;
    using F_ETS = CortexM3::Field<ValueType, 10, 1>;
    using F_FBES = CortexM3::Field<ValueType, 13, 1>;
    using F_ERS = CortexM3::Field<ValueType, 14, 1>;
    using F_AIS = CortexM3::Field<ValueType, 15, 1>;
    using F_NIS = CortexM3::Field<ValueType, 16, 1>;
    using F_RPS = CortexM3::Field<ValueType, 17, 3>;
    using F_TPS = CortexM3::Field<ValueType, 20, 3>;
    using F_EBS = CortexM3::Field<ValueType, 23, 3>;
    using F_MMCS = CortexM3::Field<ValueType, 27, 1>;
    using F_PMTS = CortexM3::Field<ValueType, 28, 1>;
    using F_TSTS = CortexM3::Field<ValueType, 29, 1>;
};

class DMAOMR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSR() noexcept -> ValueType { return Reg::Read<F_SR>(); }
    static void WriteSR(ValueType value) noexcept { Reg::Write<F_SR>(value); }
    static auto ReadOSF() noexcept -> ValueType { return Reg::Read<F_OSF>(); }
    static void WriteOSF(ValueType value) noexcept { Reg::Write<F_OSF>(value); }
    static auto ReadRTC() noexcept -> ValueType { return Reg::Read<F_RTC>(); }
    static void WriteRTC(ValueType value) noexcept { Reg::Write<F_RTC>(value); }
    static auto ReadFUGF() noexcept -> ValueType { return Reg::Read<F_FUGF>(); }
    static void WriteFUGF(ValueType value) noexcept { Reg::Write<F_FUGF>(value); }
    static auto ReadFEF() noexcept -> ValueType { return Reg::Read<F_FEF>(); }
    static void WriteFEF(ValueType value) noexcept { Reg::Write<F_FEF>(value); }
    static auto ReadST() noexcept -> ValueType { return Reg::Read<F_ST>(); }
    static void WriteST(ValueType value) noexcept { Reg::Write<F_ST>(value); }
    static auto ReadTTC() noexcept -> ValueType { return Reg::Read<F_TTC>(); }
    static void WriteTTC(ValueType value) noexcept { Reg::Write<F_TTC>(value); }
    static auto ReadFTF() noexcept -> ValueType { return Reg::Read<F_FTF>(); }
    static void WriteFTF(ValueType value) noexcept { Reg::Write<F_FTF>(value); }
    static auto ReadTSF() noexcept -> ValueType { return Reg::Read<F_TSF>(); }
    static void WriteTSF(ValueType value) noexcept { Reg::Write<F_TSF>(value); }
    static auto ReadDFRF() noexcept -> ValueType { return Reg::Read<F_DFRF>(); }
    static void WriteDFRF(ValueType value) noexcept { Reg::Write<F_DFRF>(value); }
    static auto ReadRSF() noexcept -> ValueType { return Reg::Read<F_RSF>(); }
    static void WriteRSF(ValueType value) noexcept { Reg::Write<F_RSF>(value); }
    static auto ReadDTCEFD() noexcept -> ValueType { return Reg::Read<F_DTCEFD>(); }
    static void WriteDTCEFD(ValueType value) noexcept { Reg::Write<F_DTCEFD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40029018;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SR = CortexM3::Field<ValueType, 1, 1>;
    using F_OSF = CortexM3::Field<ValueType, 2, 1>;
    using F_RTC = CortexM3::Field<ValueType, 3, 2>;
    using F_FUGF = CortexM3::Field<ValueType, 6, 1>;
    using F_FEF = CortexM3::Field<ValueType, 7, 1>;
    using F_ST = CortexM3::Field<ValueType, 13, 1>;
    using F_TTC = CortexM3::Field<ValueType, 14, 3>;
    using F_FTF = CortexM3::Field<ValueType, 20, 1>;
    using F_TSF = CortexM3::Field<ValueType, 21, 1>;
    using F_DFRF = CortexM3::Field<ValueType, 24, 1>;
    using F_RSF = CortexM3::Field<ValueType, 25, 1>;
    using F_DTCEFD = CortexM3::Field<ValueType, 26, 1>;
};

class DMAIER {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTIE() noexcept -> ValueType { return Reg::Read<F_TIE>(); }
    static void WriteTIE(ValueType value) noexcept { Reg::Write<F_TIE>(value); }
    static auto ReadTPSIE() noexcept -> ValueType { return Reg::Read<F_TPSIE>(); }
    static void WriteTPSIE(ValueType value) noexcept { Reg::Write<F_TPSIE>(value); }
    static auto ReadTBUIE() noexcept -> ValueType { return Reg::Read<F_TBUIE>(); }
    static void WriteTBUIE(ValueType value) noexcept { Reg::Write<F_TBUIE>(value); }
    static auto ReadTJTIE() noexcept -> ValueType { return Reg::Read<F_TJTIE>(); }
    static void WriteTJTIE(ValueType value) noexcept { Reg::Write<F_TJTIE>(value); }
    static auto ReadROIE() noexcept -> ValueType { return Reg::Read<F_ROIE>(); }
    static void WriteROIE(ValueType value) noexcept { Reg::Write<F_ROIE>(value); }
    static auto ReadTUIE() noexcept -> ValueType { return Reg::Read<F_TUIE>(); }
    static void WriteTUIE(ValueType value) noexcept { Reg::Write<F_TUIE>(value); }
    static auto ReadRIE() noexcept -> ValueType { return Reg::Read<F_RIE>(); }
    static void WriteRIE(ValueType value) noexcept { Reg::Write<F_RIE>(value); }
    static auto ReadRBUIE() noexcept -> ValueType { return Reg::Read<F_RBUIE>(); }
    static void WriteRBUIE(ValueType value) noexcept { Reg::Write<F_RBUIE>(value); }
    static auto ReadRPSIE() noexcept -> ValueType { return Reg::Read<F_RPSIE>(); }
    static void WriteRPSIE(ValueType value) noexcept { Reg::Write<F_RPSIE>(value); }
    static auto ReadRWTIE() noexcept -> ValueType { return Reg::Read<F_RWTIE>(); }
    static void WriteRWTIE(ValueType value) noexcept { Reg::Write<F_RWTIE>(value); }
    static auto ReadETIE() noexcept -> ValueType { return Reg::Read<F_ETIE>(); }
    static void WriteETIE(ValueType value) noexcept { Reg::Write<F_ETIE>(value); }
    static auto ReadFBEIE() noexcept -> ValueType { return Reg::Read<F_FBEIE>(); }
    static void WriteFBEIE(ValueType value) noexcept { Reg::Write<F_FBEIE>(value); }
    static auto ReadERIE() noexcept -> ValueType { return Reg::Read<F_ERIE>(); }
    static void WriteERIE(ValueType value) noexcept { Reg::Write<F_ERIE>(value); }
    static auto ReadAISE() noexcept -> ValueType { return Reg::Read<F_AISE>(); }
    static void WriteAISE(ValueType value) noexcept { Reg::Write<F_AISE>(value); }
    static auto ReadNISE() noexcept -> ValueType { return Reg::Read<F_NISE>(); }
    static void WriteNISE(ValueType value) noexcept { Reg::Write<F_NISE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4002901c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TIE = CortexM3::Field<ValueType, 0, 1>;
    using F_TPSIE = CortexM3::Field<ValueType, 1, 1>;
    using F_TBUIE = CortexM3::Field<ValueType, 2, 1>;
    using F_TJTIE = CortexM3::Field<ValueType, 3, 1>;
    using F_ROIE = CortexM3::Field<ValueType, 4, 1>;
    using F_TUIE = CortexM3::Field<ValueType, 5, 1>;
    using F_RIE = CortexM3::Field<ValueType, 6, 1>;
    using F_RBUIE = CortexM3::Field<ValueType, 7, 1>;
    using F_RPSIE = CortexM3::Field<ValueType, 8, 1>;
    using F_RWTIE = CortexM3::Field<ValueType, 9, 1>;
    using F_ETIE = CortexM3::Field<ValueType, 10, 1>;
    using F_FBEIE = CortexM3::Field<ValueType, 13, 1>;
    using F_ERIE = CortexM3::Field<ValueType, 14, 1>;
    using F_AISE = CortexM3::Field<ValueType, 15, 1>;
    using F_NISE = CortexM3::Field<ValueType, 16, 1>;
};

class DMAMFBOCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadMFC() noexcept -> ValueType { return Reg::Read<F_MFC>(); }
    static auto ReadOMFC() noexcept -> ValueType { return Reg::Read<F_OMFC>(); }
    static auto ReadMFA() noexcept -> ValueType { return Reg::Read<F_MFA>(); }
    static auto ReadOFOC() noexcept -> ValueType { return Reg::Read<F_OFOC>(); }

private:
    static constexpr std::uintptr_t Address = 0x40029020;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MFC = CortexM3::Field<ValueType, 0, 16>;
    using F_OMFC = CortexM3::Field<ValueType, 16, 1>;
    using F_MFA = CortexM3::Field<ValueType, 17, 11>;
    using F_OFOC = CortexM3::Field<ValueType, 28, 1>;
};

class DMACHTDR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadHTDAP() noexcept -> ValueType { return Reg::Read<F_HTDAP>(); }

private:
    static constexpr std::uintptr_t Address = 0x40029048;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_HTDAP = CortexM3::Field<ValueType, 0, 32>;
};

class DMACHRDR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadHRDAP() noexcept -> ValueType { return Reg::Read<F_HRDAP>(); }

private:
    static constexpr std::uintptr_t Address = 0x4002904c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_HRDAP = CortexM3::Field<ValueType, 0, 32>;
};

class DMACHTBAR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadHTBAP() noexcept -> ValueType { return Reg::Read<F_HTBAP>(); }

private:
    static constexpr std::uintptr_t Address = 0x40029050;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_HTBAP = CortexM3::Field<ValueType, 0, 32>;
};

class DMACHRBAR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadHRBAP() noexcept -> ValueType { return Reg::Read<F_HRBAP>(); }

private:
    static constexpr std::uintptr_t Address = 0x40029054;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_HRBAP = CortexM3::Field<ValueType, 0, 32>;
};

} // namespace STM32F103::ETHERNET_DMA
