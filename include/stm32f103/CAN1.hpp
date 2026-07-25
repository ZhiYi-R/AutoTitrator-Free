#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::CAN1 {

class CAN_MCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDBF() noexcept -> ValueType { return Reg::Read<F_DBF>(); }
    static void WriteDBF(ValueType value) noexcept { Reg::Write<F_DBF>(value); }
    static auto ReadRESET() noexcept -> ValueType { return Reg::Read<F_RESET>(); }
    static void WriteRESET(ValueType value) noexcept { Reg::Write<F_RESET>(value); }
    static auto ReadTTCM() noexcept -> ValueType { return Reg::Read<F_TTCM>(); }
    static void WriteTTCM(ValueType value) noexcept { Reg::Write<F_TTCM>(value); }
    static auto ReadABOM() noexcept -> ValueType { return Reg::Read<F_ABOM>(); }
    static void WriteABOM(ValueType value) noexcept { Reg::Write<F_ABOM>(value); }
    static auto ReadAWUM() noexcept -> ValueType { return Reg::Read<F_AWUM>(); }
    static void WriteAWUM(ValueType value) noexcept { Reg::Write<F_AWUM>(value); }
    static auto ReadNART() noexcept -> ValueType { return Reg::Read<F_NART>(); }
    static void WriteNART(ValueType value) noexcept { Reg::Write<F_NART>(value); }
    static auto ReadRFLM() noexcept -> ValueType { return Reg::Read<F_RFLM>(); }
    static void WriteRFLM(ValueType value) noexcept { Reg::Write<F_RFLM>(value); }
    static auto ReadTXFP() noexcept -> ValueType { return Reg::Read<F_TXFP>(); }
    static void WriteTXFP(ValueType value) noexcept { Reg::Write<F_TXFP>(value); }
    static auto ReadSLEEP() noexcept -> ValueType { return Reg::Read<F_SLEEP>(); }
    static void WriteSLEEP(ValueType value) noexcept { Reg::Write<F_SLEEP>(value); }
    static auto ReadINRQ() noexcept -> ValueType { return Reg::Read<F_INRQ>(); }
    static void WriteINRQ(ValueType value) noexcept { Reg::Write<F_INRQ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006400;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DBF = CortexM3::Field<ValueType, 16, 1>;
    using F_RESET = CortexM3::Field<ValueType, 15, 1>;
    using F_TTCM = CortexM3::Field<ValueType, 7, 1>;
    using F_ABOM = CortexM3::Field<ValueType, 6, 1>;
    using F_AWUM = CortexM3::Field<ValueType, 5, 1>;
    using F_NART = CortexM3::Field<ValueType, 4, 1>;
    using F_RFLM = CortexM3::Field<ValueType, 3, 1>;
    using F_TXFP = CortexM3::Field<ValueType, 2, 1>;
    using F_SLEEP = CortexM3::Field<ValueType, 1, 1>;
    using F_INRQ = CortexM3::Field<ValueType, 0, 1>;
};

class CAN_MSR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRX() noexcept -> ValueType { return Reg::Read<F_RX>(); }
    static auto ReadSAMP() noexcept -> ValueType { return Reg::Read<F_SAMP>(); }
    static auto ReadRXM() noexcept -> ValueType { return Reg::Read<F_RXM>(); }
    static auto ReadTXM() noexcept -> ValueType { return Reg::Read<F_TXM>(); }
    static auto ReadSLAKI() noexcept -> ValueType { return Reg::Read<F_SLAKI>(); }
    static void WriteSLAKI(ValueType value) noexcept { Reg::Write<F_SLAKI>(value); }
    static auto ReadWKUI() noexcept -> ValueType { return Reg::Read<F_WKUI>(); }
    static void WriteWKUI(ValueType value) noexcept { Reg::Write<F_WKUI>(value); }
    static auto ReadERRI() noexcept -> ValueType { return Reg::Read<F_ERRI>(); }
    static void WriteERRI(ValueType value) noexcept { Reg::Write<F_ERRI>(value); }
    static auto ReadSLAK() noexcept -> ValueType { return Reg::Read<F_SLAK>(); }
    static auto ReadINAK() noexcept -> ValueType { return Reg::Read<F_INAK>(); }

private:
    static constexpr std::uintptr_t Address = 0x40006404;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RX = CortexM3::Field<ValueType, 11, 1>;
    using F_SAMP = CortexM3::Field<ValueType, 10, 1>;
    using F_RXM = CortexM3::Field<ValueType, 9, 1>;
    using F_TXM = CortexM3::Field<ValueType, 8, 1>;
    using F_SLAKI = CortexM3::Field<ValueType, 4, 1>;
    using F_WKUI = CortexM3::Field<ValueType, 3, 1>;
    using F_ERRI = CortexM3::Field<ValueType, 2, 1>;
    using F_SLAK = CortexM3::Field<ValueType, 1, 1>;
    using F_INAK = CortexM3::Field<ValueType, 0, 1>;
};

class CAN_TSR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadLOW2() noexcept -> ValueType { return Reg::Read<F_LOW2>(); }
    static auto ReadLOW1() noexcept -> ValueType { return Reg::Read<F_LOW1>(); }
    static auto ReadLOW0() noexcept -> ValueType { return Reg::Read<F_LOW0>(); }
    static auto ReadTME2() noexcept -> ValueType { return Reg::Read<F_TME2>(); }
    static auto ReadTME1() noexcept -> ValueType { return Reg::Read<F_TME1>(); }
    static auto ReadTME0() noexcept -> ValueType { return Reg::Read<F_TME0>(); }
    static auto ReadCODE() noexcept -> ValueType { return Reg::Read<F_CODE>(); }
    static auto ReadABRQ2() noexcept -> ValueType { return Reg::Read<F_ABRQ2>(); }
    static void WriteABRQ2(ValueType value) noexcept { Reg::Write<F_ABRQ2>(value); }
    static auto ReadTERR2() noexcept -> ValueType { return Reg::Read<F_TERR2>(); }
    static void WriteTERR2(ValueType value) noexcept { Reg::Write<F_TERR2>(value); }
    static auto ReadALST2() noexcept -> ValueType { return Reg::Read<F_ALST2>(); }
    static void WriteALST2(ValueType value) noexcept { Reg::Write<F_ALST2>(value); }
    static auto ReadTXOK2() noexcept -> ValueType { return Reg::Read<F_TXOK2>(); }
    static void WriteTXOK2(ValueType value) noexcept { Reg::Write<F_TXOK2>(value); }
    static auto ReadRQCP2() noexcept -> ValueType { return Reg::Read<F_RQCP2>(); }
    static void WriteRQCP2(ValueType value) noexcept { Reg::Write<F_RQCP2>(value); }
    static auto ReadABRQ1() noexcept -> ValueType { return Reg::Read<F_ABRQ1>(); }
    static void WriteABRQ1(ValueType value) noexcept { Reg::Write<F_ABRQ1>(value); }
    static auto ReadTERR1() noexcept -> ValueType { return Reg::Read<F_TERR1>(); }
    static void WriteTERR1(ValueType value) noexcept { Reg::Write<F_TERR1>(value); }
    static auto ReadALST1() noexcept -> ValueType { return Reg::Read<F_ALST1>(); }
    static void WriteALST1(ValueType value) noexcept { Reg::Write<F_ALST1>(value); }
    static auto ReadTXOK1() noexcept -> ValueType { return Reg::Read<F_TXOK1>(); }
    static void WriteTXOK1(ValueType value) noexcept { Reg::Write<F_TXOK1>(value); }
    static auto ReadRQCP1() noexcept -> ValueType { return Reg::Read<F_RQCP1>(); }
    static void WriteRQCP1(ValueType value) noexcept { Reg::Write<F_RQCP1>(value); }
    static auto ReadABRQ0() noexcept -> ValueType { return Reg::Read<F_ABRQ0>(); }
    static void WriteABRQ0(ValueType value) noexcept { Reg::Write<F_ABRQ0>(value); }
    static auto ReadTERR0() noexcept -> ValueType { return Reg::Read<F_TERR0>(); }
    static void WriteTERR0(ValueType value) noexcept { Reg::Write<F_TERR0>(value); }
    static auto ReadALST0() noexcept -> ValueType { return Reg::Read<F_ALST0>(); }
    static void WriteALST0(ValueType value) noexcept { Reg::Write<F_ALST0>(value); }
    static auto ReadTXOK0() noexcept -> ValueType { return Reg::Read<F_TXOK0>(); }
    static void WriteTXOK0(ValueType value) noexcept { Reg::Write<F_TXOK0>(value); }
    static auto ReadRQCP0() noexcept -> ValueType { return Reg::Read<F_RQCP0>(); }
    static void WriteRQCP0(ValueType value) noexcept { Reg::Write<F_RQCP0>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006408;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_LOW2 = CortexM3::Field<ValueType, 31, 1>;
    using F_LOW1 = CortexM3::Field<ValueType, 30, 1>;
    using F_LOW0 = CortexM3::Field<ValueType, 29, 1>;
    using F_TME2 = CortexM3::Field<ValueType, 28, 1>;
    using F_TME1 = CortexM3::Field<ValueType, 27, 1>;
    using F_TME0 = CortexM3::Field<ValueType, 26, 1>;
    using F_CODE = CortexM3::Field<ValueType, 24, 2>;
    using F_ABRQ2 = CortexM3::Field<ValueType, 23, 1>;
    using F_TERR2 = CortexM3::Field<ValueType, 19, 1>;
    using F_ALST2 = CortexM3::Field<ValueType, 18, 1>;
    using F_TXOK2 = CortexM3::Field<ValueType, 17, 1>;
    using F_RQCP2 = CortexM3::Field<ValueType, 16, 1>;
    using F_ABRQ1 = CortexM3::Field<ValueType, 15, 1>;
    using F_TERR1 = CortexM3::Field<ValueType, 11, 1>;
    using F_ALST1 = CortexM3::Field<ValueType, 10, 1>;
    using F_TXOK1 = CortexM3::Field<ValueType, 9, 1>;
    using F_RQCP1 = CortexM3::Field<ValueType, 8, 1>;
    using F_ABRQ0 = CortexM3::Field<ValueType, 7, 1>;
    using F_TERR0 = CortexM3::Field<ValueType, 3, 1>;
    using F_ALST0 = CortexM3::Field<ValueType, 2, 1>;
    using F_TXOK0 = CortexM3::Field<ValueType, 1, 1>;
    using F_RQCP0 = CortexM3::Field<ValueType, 0, 1>;
};

class CAN_RF0R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRFOM0() noexcept -> ValueType { return Reg::Read<F_RFOM0>(); }
    static void WriteRFOM0(ValueType value) noexcept { Reg::Write<F_RFOM0>(value); }
    static auto ReadFOVR0() noexcept -> ValueType { return Reg::Read<F_FOVR0>(); }
    static void WriteFOVR0(ValueType value) noexcept { Reg::Write<F_FOVR0>(value); }
    static auto ReadFULL0() noexcept -> ValueType { return Reg::Read<F_FULL0>(); }
    static void WriteFULL0(ValueType value) noexcept { Reg::Write<F_FULL0>(value); }
    static auto ReadFMP0() noexcept -> ValueType { return Reg::Read<F_FMP0>(); }

private:
    static constexpr std::uintptr_t Address = 0x4000640c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RFOM0 = CortexM3::Field<ValueType, 5, 1>;
    using F_FOVR0 = CortexM3::Field<ValueType, 4, 1>;
    using F_FULL0 = CortexM3::Field<ValueType, 3, 1>;
    using F_FMP0 = CortexM3::Field<ValueType, 0, 2>;
};

class CAN_RF1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadRFOM1() noexcept -> ValueType { return Reg::Read<F_RFOM1>(); }
    static void WriteRFOM1(ValueType value) noexcept { Reg::Write<F_RFOM1>(value); }
    static auto ReadFOVR1() noexcept -> ValueType { return Reg::Read<F_FOVR1>(); }
    static void WriteFOVR1(ValueType value) noexcept { Reg::Write<F_FOVR1>(value); }
    static auto ReadFULL1() noexcept -> ValueType { return Reg::Read<F_FULL1>(); }
    static void WriteFULL1(ValueType value) noexcept { Reg::Write<F_FULL1>(value); }
    static auto ReadFMP1() noexcept -> ValueType { return Reg::Read<F_FMP1>(); }

private:
    static constexpr std::uintptr_t Address = 0x40006410;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RFOM1 = CortexM3::Field<ValueType, 5, 1>;
    using F_FOVR1 = CortexM3::Field<ValueType, 4, 1>;
    using F_FULL1 = CortexM3::Field<ValueType, 3, 1>;
    using F_FMP1 = CortexM3::Field<ValueType, 0, 2>;
};

class CAN_IER {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSLKIE() noexcept -> ValueType { return Reg::Read<F_SLKIE>(); }
    static void WriteSLKIE(ValueType value) noexcept { Reg::Write<F_SLKIE>(value); }
    static auto ReadWKUIE() noexcept -> ValueType { return Reg::Read<F_WKUIE>(); }
    static void WriteWKUIE(ValueType value) noexcept { Reg::Write<F_WKUIE>(value); }
    static auto ReadERRIE() noexcept -> ValueType { return Reg::Read<F_ERRIE>(); }
    static void WriteERRIE(ValueType value) noexcept { Reg::Write<F_ERRIE>(value); }
    static auto ReadLECIE() noexcept -> ValueType { return Reg::Read<F_LECIE>(); }
    static void WriteLECIE(ValueType value) noexcept { Reg::Write<F_LECIE>(value); }
    static auto ReadBOFIE() noexcept -> ValueType { return Reg::Read<F_BOFIE>(); }
    static void WriteBOFIE(ValueType value) noexcept { Reg::Write<F_BOFIE>(value); }
    static auto ReadEPVIE() noexcept -> ValueType { return Reg::Read<F_EPVIE>(); }
    static void WriteEPVIE(ValueType value) noexcept { Reg::Write<F_EPVIE>(value); }
    static auto ReadEWGIE() noexcept -> ValueType { return Reg::Read<F_EWGIE>(); }
    static void WriteEWGIE(ValueType value) noexcept { Reg::Write<F_EWGIE>(value); }
    static auto ReadFOVIE1() noexcept -> ValueType { return Reg::Read<F_FOVIE1>(); }
    static void WriteFOVIE1(ValueType value) noexcept { Reg::Write<F_FOVIE1>(value); }
    static auto ReadFFIE1() noexcept -> ValueType { return Reg::Read<F_FFIE1>(); }
    static void WriteFFIE1(ValueType value) noexcept { Reg::Write<F_FFIE1>(value); }
    static auto ReadFMPIE1() noexcept -> ValueType { return Reg::Read<F_FMPIE1>(); }
    static void WriteFMPIE1(ValueType value) noexcept { Reg::Write<F_FMPIE1>(value); }
    static auto ReadFOVIE0() noexcept -> ValueType { return Reg::Read<F_FOVIE0>(); }
    static void WriteFOVIE0(ValueType value) noexcept { Reg::Write<F_FOVIE0>(value); }
    static auto ReadFFIE0() noexcept -> ValueType { return Reg::Read<F_FFIE0>(); }
    static void WriteFFIE0(ValueType value) noexcept { Reg::Write<F_FFIE0>(value); }
    static auto ReadFMPIE0() noexcept -> ValueType { return Reg::Read<F_FMPIE0>(); }
    static void WriteFMPIE0(ValueType value) noexcept { Reg::Write<F_FMPIE0>(value); }
    static auto ReadTMEIE() noexcept -> ValueType { return Reg::Read<F_TMEIE>(); }
    static void WriteTMEIE(ValueType value) noexcept { Reg::Write<F_TMEIE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006414;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SLKIE = CortexM3::Field<ValueType, 17, 1>;
    using F_WKUIE = CortexM3::Field<ValueType, 16, 1>;
    using F_ERRIE = CortexM3::Field<ValueType, 15, 1>;
    using F_LECIE = CortexM3::Field<ValueType, 11, 1>;
    using F_BOFIE = CortexM3::Field<ValueType, 10, 1>;
    using F_EPVIE = CortexM3::Field<ValueType, 9, 1>;
    using F_EWGIE = CortexM3::Field<ValueType, 8, 1>;
    using F_FOVIE1 = CortexM3::Field<ValueType, 6, 1>;
    using F_FFIE1 = CortexM3::Field<ValueType, 5, 1>;
    using F_FMPIE1 = CortexM3::Field<ValueType, 4, 1>;
    using F_FOVIE0 = CortexM3::Field<ValueType, 3, 1>;
    using F_FFIE0 = CortexM3::Field<ValueType, 2, 1>;
    using F_FMPIE0 = CortexM3::Field<ValueType, 1, 1>;
    using F_TMEIE = CortexM3::Field<ValueType, 0, 1>;
};

class CAN_ESR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadREC() noexcept -> ValueType { return Reg::Read<F_REC>(); }
    static auto ReadTEC() noexcept -> ValueType { return Reg::Read<F_TEC>(); }
    static auto ReadLEC() noexcept -> ValueType { return Reg::Read<F_LEC>(); }
    static void WriteLEC(ValueType value) noexcept { Reg::Write<F_LEC>(value); }
    static auto ReadBOFF() noexcept -> ValueType { return Reg::Read<F_BOFF>(); }
    static auto ReadEPVF() noexcept -> ValueType { return Reg::Read<F_EPVF>(); }
    static auto ReadEWGF() noexcept -> ValueType { return Reg::Read<F_EWGF>(); }

private:
    static constexpr std::uintptr_t Address = 0x40006418;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_REC = CortexM3::Field<ValueType, 24, 8>;
    using F_TEC = CortexM3::Field<ValueType, 16, 8>;
    using F_LEC = CortexM3::Field<ValueType, 4, 3>;
    using F_BOFF = CortexM3::Field<ValueType, 2, 1>;
    using F_EPVF = CortexM3::Field<ValueType, 1, 1>;
    using F_EWGF = CortexM3::Field<ValueType, 0, 1>;
};

class CAN_BTR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSILM() noexcept -> ValueType { return Reg::Read<F_SILM>(); }
    static void WriteSILM(ValueType value) noexcept { Reg::Write<F_SILM>(value); }
    static auto ReadLBKM() noexcept -> ValueType { return Reg::Read<F_LBKM>(); }
    static void WriteLBKM(ValueType value) noexcept { Reg::Write<F_LBKM>(value); }
    static auto ReadSJW() noexcept -> ValueType { return Reg::Read<F_SJW>(); }
    static void WriteSJW(ValueType value) noexcept { Reg::Write<F_SJW>(value); }
    static auto ReadTS2() noexcept -> ValueType { return Reg::Read<F_TS2>(); }
    static void WriteTS2(ValueType value) noexcept { Reg::Write<F_TS2>(value); }
    static auto ReadTS1() noexcept -> ValueType { return Reg::Read<F_TS1>(); }
    static void WriteTS1(ValueType value) noexcept { Reg::Write<F_TS1>(value); }
    static auto ReadBRP() noexcept -> ValueType { return Reg::Read<F_BRP>(); }
    static void WriteBRP(ValueType value) noexcept { Reg::Write<F_BRP>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000641c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SILM = CortexM3::Field<ValueType, 31, 1>;
    using F_LBKM = CortexM3::Field<ValueType, 30, 1>;
    using F_SJW = CortexM3::Field<ValueType, 24, 2>;
    using F_TS2 = CortexM3::Field<ValueType, 20, 3>;
    using F_TS1 = CortexM3::Field<ValueType, 16, 4>;
    using F_BRP = CortexM3::Field<ValueType, 0, 10>;
};

class CAN_TI0R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSTID() noexcept -> ValueType { return Reg::Read<F_STID>(); }
    static void WriteSTID(ValueType value) noexcept { Reg::Write<F_STID>(value); }
    static auto ReadEXID() noexcept -> ValueType { return Reg::Read<F_EXID>(); }
    static void WriteEXID(ValueType value) noexcept { Reg::Write<F_EXID>(value); }
    static auto ReadIDE() noexcept -> ValueType { return Reg::Read<F_IDE>(); }
    static void WriteIDE(ValueType value) noexcept { Reg::Write<F_IDE>(value); }
    static auto ReadRTR() noexcept -> ValueType { return Reg::Read<F_RTR>(); }
    static void WriteRTR(ValueType value) noexcept { Reg::Write<F_RTR>(value); }
    static auto ReadTXRQ() noexcept -> ValueType { return Reg::Read<F_TXRQ>(); }
    static void WriteTXRQ(ValueType value) noexcept { Reg::Write<F_TXRQ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006580;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STID = CortexM3::Field<ValueType, 21, 11>;
    using F_EXID = CortexM3::Field<ValueType, 3, 18>;
    using F_IDE = CortexM3::Field<ValueType, 2, 1>;
    using F_RTR = CortexM3::Field<ValueType, 1, 1>;
    using F_TXRQ = CortexM3::Field<ValueType, 0, 1>;
};

class CAN_TDT0R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTIME() noexcept -> ValueType { return Reg::Read<F_TIME>(); }
    static void WriteTIME(ValueType value) noexcept { Reg::Write<F_TIME>(value); }
    static auto ReadTGT() noexcept -> ValueType { return Reg::Read<F_TGT>(); }
    static void WriteTGT(ValueType value) noexcept { Reg::Write<F_TGT>(value); }
    static auto ReadDLC() noexcept -> ValueType { return Reg::Read<F_DLC>(); }
    static void WriteDLC(ValueType value) noexcept { Reg::Write<F_DLC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006584;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TIME = CortexM3::Field<ValueType, 16, 16>;
    using F_TGT = CortexM3::Field<ValueType, 8, 1>;
    using F_DLC = CortexM3::Field<ValueType, 0, 4>;
};

class CAN_TDL0R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDATA3() noexcept -> ValueType { return Reg::Read<F_DATA3>(); }
    static void WriteDATA3(ValueType value) noexcept { Reg::Write<F_DATA3>(value); }
    static auto ReadDATA2() noexcept -> ValueType { return Reg::Read<F_DATA2>(); }
    static void WriteDATA2(ValueType value) noexcept { Reg::Write<F_DATA2>(value); }
    static auto ReadDATA1() noexcept -> ValueType { return Reg::Read<F_DATA1>(); }
    static void WriteDATA1(ValueType value) noexcept { Reg::Write<F_DATA1>(value); }
    static auto ReadDATA0() noexcept -> ValueType { return Reg::Read<F_DATA0>(); }
    static void WriteDATA0(ValueType value) noexcept { Reg::Write<F_DATA0>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006588;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA3 = CortexM3::Field<ValueType, 24, 8>;
    using F_DATA2 = CortexM3::Field<ValueType, 16, 8>;
    using F_DATA1 = CortexM3::Field<ValueType, 8, 8>;
    using F_DATA0 = CortexM3::Field<ValueType, 0, 8>;
};

class CAN_TDH0R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDATA7() noexcept -> ValueType { return Reg::Read<F_DATA7>(); }
    static void WriteDATA7(ValueType value) noexcept { Reg::Write<F_DATA7>(value); }
    static auto ReadDATA6() noexcept -> ValueType { return Reg::Read<F_DATA6>(); }
    static void WriteDATA6(ValueType value) noexcept { Reg::Write<F_DATA6>(value); }
    static auto ReadDATA5() noexcept -> ValueType { return Reg::Read<F_DATA5>(); }
    static void WriteDATA5(ValueType value) noexcept { Reg::Write<F_DATA5>(value); }
    static auto ReadDATA4() noexcept -> ValueType { return Reg::Read<F_DATA4>(); }
    static void WriteDATA4(ValueType value) noexcept { Reg::Write<F_DATA4>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000658c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA7 = CortexM3::Field<ValueType, 24, 8>;
    using F_DATA6 = CortexM3::Field<ValueType, 16, 8>;
    using F_DATA5 = CortexM3::Field<ValueType, 8, 8>;
    using F_DATA4 = CortexM3::Field<ValueType, 0, 8>;
};

class CAN_TI1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSTID() noexcept -> ValueType { return Reg::Read<F_STID>(); }
    static void WriteSTID(ValueType value) noexcept { Reg::Write<F_STID>(value); }
    static auto ReadEXID() noexcept -> ValueType { return Reg::Read<F_EXID>(); }
    static void WriteEXID(ValueType value) noexcept { Reg::Write<F_EXID>(value); }
    static auto ReadIDE() noexcept -> ValueType { return Reg::Read<F_IDE>(); }
    static void WriteIDE(ValueType value) noexcept { Reg::Write<F_IDE>(value); }
    static auto ReadRTR() noexcept -> ValueType { return Reg::Read<F_RTR>(); }
    static void WriteRTR(ValueType value) noexcept { Reg::Write<F_RTR>(value); }
    static auto ReadTXRQ() noexcept -> ValueType { return Reg::Read<F_TXRQ>(); }
    static void WriteTXRQ(ValueType value) noexcept { Reg::Write<F_TXRQ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006590;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STID = CortexM3::Field<ValueType, 21, 11>;
    using F_EXID = CortexM3::Field<ValueType, 3, 18>;
    using F_IDE = CortexM3::Field<ValueType, 2, 1>;
    using F_RTR = CortexM3::Field<ValueType, 1, 1>;
    using F_TXRQ = CortexM3::Field<ValueType, 0, 1>;
};

class CAN_TDT1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTIME() noexcept -> ValueType { return Reg::Read<F_TIME>(); }
    static void WriteTIME(ValueType value) noexcept { Reg::Write<F_TIME>(value); }
    static auto ReadTGT() noexcept -> ValueType { return Reg::Read<F_TGT>(); }
    static void WriteTGT(ValueType value) noexcept { Reg::Write<F_TGT>(value); }
    static auto ReadDLC() noexcept -> ValueType { return Reg::Read<F_DLC>(); }
    static void WriteDLC(ValueType value) noexcept { Reg::Write<F_DLC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006594;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TIME = CortexM3::Field<ValueType, 16, 16>;
    using F_TGT = CortexM3::Field<ValueType, 8, 1>;
    using F_DLC = CortexM3::Field<ValueType, 0, 4>;
};

class CAN_TDL1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDATA3() noexcept -> ValueType { return Reg::Read<F_DATA3>(); }
    static void WriteDATA3(ValueType value) noexcept { Reg::Write<F_DATA3>(value); }
    static auto ReadDATA2() noexcept -> ValueType { return Reg::Read<F_DATA2>(); }
    static void WriteDATA2(ValueType value) noexcept { Reg::Write<F_DATA2>(value); }
    static auto ReadDATA1() noexcept -> ValueType { return Reg::Read<F_DATA1>(); }
    static void WriteDATA1(ValueType value) noexcept { Reg::Write<F_DATA1>(value); }
    static auto ReadDATA0() noexcept -> ValueType { return Reg::Read<F_DATA0>(); }
    static void WriteDATA0(ValueType value) noexcept { Reg::Write<F_DATA0>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006598;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA3 = CortexM3::Field<ValueType, 24, 8>;
    using F_DATA2 = CortexM3::Field<ValueType, 16, 8>;
    using F_DATA1 = CortexM3::Field<ValueType, 8, 8>;
    using F_DATA0 = CortexM3::Field<ValueType, 0, 8>;
};

class CAN_TDH1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDATA7() noexcept -> ValueType { return Reg::Read<F_DATA7>(); }
    static void WriteDATA7(ValueType value) noexcept { Reg::Write<F_DATA7>(value); }
    static auto ReadDATA6() noexcept -> ValueType { return Reg::Read<F_DATA6>(); }
    static void WriteDATA6(ValueType value) noexcept { Reg::Write<F_DATA6>(value); }
    static auto ReadDATA5() noexcept -> ValueType { return Reg::Read<F_DATA5>(); }
    static void WriteDATA5(ValueType value) noexcept { Reg::Write<F_DATA5>(value); }
    static auto ReadDATA4() noexcept -> ValueType { return Reg::Read<F_DATA4>(); }
    static void WriteDATA4(ValueType value) noexcept { Reg::Write<F_DATA4>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000659c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA7 = CortexM3::Field<ValueType, 24, 8>;
    using F_DATA6 = CortexM3::Field<ValueType, 16, 8>;
    using F_DATA5 = CortexM3::Field<ValueType, 8, 8>;
    using F_DATA4 = CortexM3::Field<ValueType, 0, 8>;
};

class CAN_TI2R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSTID() noexcept -> ValueType { return Reg::Read<F_STID>(); }
    static void WriteSTID(ValueType value) noexcept { Reg::Write<F_STID>(value); }
    static auto ReadEXID() noexcept -> ValueType { return Reg::Read<F_EXID>(); }
    static void WriteEXID(ValueType value) noexcept { Reg::Write<F_EXID>(value); }
    static auto ReadIDE() noexcept -> ValueType { return Reg::Read<F_IDE>(); }
    static void WriteIDE(ValueType value) noexcept { Reg::Write<F_IDE>(value); }
    static auto ReadRTR() noexcept -> ValueType { return Reg::Read<F_RTR>(); }
    static void WriteRTR(ValueType value) noexcept { Reg::Write<F_RTR>(value); }
    static auto ReadTXRQ() noexcept -> ValueType { return Reg::Read<F_TXRQ>(); }
    static void WriteTXRQ(ValueType value) noexcept { Reg::Write<F_TXRQ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x400065a0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STID = CortexM3::Field<ValueType, 21, 11>;
    using F_EXID = CortexM3::Field<ValueType, 3, 18>;
    using F_IDE = CortexM3::Field<ValueType, 2, 1>;
    using F_RTR = CortexM3::Field<ValueType, 1, 1>;
    using F_TXRQ = CortexM3::Field<ValueType, 0, 1>;
};

class CAN_TDT2R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTIME() noexcept -> ValueType { return Reg::Read<F_TIME>(); }
    static void WriteTIME(ValueType value) noexcept { Reg::Write<F_TIME>(value); }
    static auto ReadTGT() noexcept -> ValueType { return Reg::Read<F_TGT>(); }
    static void WriteTGT(ValueType value) noexcept { Reg::Write<F_TGT>(value); }
    static auto ReadDLC() noexcept -> ValueType { return Reg::Read<F_DLC>(); }
    static void WriteDLC(ValueType value) noexcept { Reg::Write<F_DLC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x400065a4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TIME = CortexM3::Field<ValueType, 16, 16>;
    using F_TGT = CortexM3::Field<ValueType, 8, 1>;
    using F_DLC = CortexM3::Field<ValueType, 0, 4>;
};

class CAN_TDL2R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDATA3() noexcept -> ValueType { return Reg::Read<F_DATA3>(); }
    static void WriteDATA3(ValueType value) noexcept { Reg::Write<F_DATA3>(value); }
    static auto ReadDATA2() noexcept -> ValueType { return Reg::Read<F_DATA2>(); }
    static void WriteDATA2(ValueType value) noexcept { Reg::Write<F_DATA2>(value); }
    static auto ReadDATA1() noexcept -> ValueType { return Reg::Read<F_DATA1>(); }
    static void WriteDATA1(ValueType value) noexcept { Reg::Write<F_DATA1>(value); }
    static auto ReadDATA0() noexcept -> ValueType { return Reg::Read<F_DATA0>(); }
    static void WriteDATA0(ValueType value) noexcept { Reg::Write<F_DATA0>(value); }

private:
    static constexpr std::uintptr_t Address = 0x400065a8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA3 = CortexM3::Field<ValueType, 24, 8>;
    using F_DATA2 = CortexM3::Field<ValueType, 16, 8>;
    using F_DATA1 = CortexM3::Field<ValueType, 8, 8>;
    using F_DATA0 = CortexM3::Field<ValueType, 0, 8>;
};

class CAN_TDH2R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDATA7() noexcept -> ValueType { return Reg::Read<F_DATA7>(); }
    static void WriteDATA7(ValueType value) noexcept { Reg::Write<F_DATA7>(value); }
    static auto ReadDATA6() noexcept -> ValueType { return Reg::Read<F_DATA6>(); }
    static void WriteDATA6(ValueType value) noexcept { Reg::Write<F_DATA6>(value); }
    static auto ReadDATA5() noexcept -> ValueType { return Reg::Read<F_DATA5>(); }
    static void WriteDATA5(ValueType value) noexcept { Reg::Write<F_DATA5>(value); }
    static auto ReadDATA4() noexcept -> ValueType { return Reg::Read<F_DATA4>(); }
    static void WriteDATA4(ValueType value) noexcept { Reg::Write<F_DATA4>(value); }

private:
    static constexpr std::uintptr_t Address = 0x400065ac;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA7 = CortexM3::Field<ValueType, 24, 8>;
    using F_DATA6 = CortexM3::Field<ValueType, 16, 8>;
    using F_DATA5 = CortexM3::Field<ValueType, 8, 8>;
    using F_DATA4 = CortexM3::Field<ValueType, 0, 8>;
};

class CAN_RI0R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadSTID() noexcept -> ValueType { return Reg::Read<F_STID>(); }
    static auto ReadEXID() noexcept -> ValueType { return Reg::Read<F_EXID>(); }
    static auto ReadIDE() noexcept -> ValueType { return Reg::Read<F_IDE>(); }
    static auto ReadRTR() noexcept -> ValueType { return Reg::Read<F_RTR>(); }

private:
    static constexpr std::uintptr_t Address = 0x400065b0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STID = CortexM3::Field<ValueType, 21, 11>;
    using F_EXID = CortexM3::Field<ValueType, 3, 18>;
    using F_IDE = CortexM3::Field<ValueType, 2, 1>;
    using F_RTR = CortexM3::Field<ValueType, 1, 1>;
};

class CAN_RDT0R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadTIME() noexcept -> ValueType { return Reg::Read<F_TIME>(); }
    static auto ReadFMI() noexcept -> ValueType { return Reg::Read<F_FMI>(); }
    static auto ReadDLC() noexcept -> ValueType { return Reg::Read<F_DLC>(); }

private:
    static constexpr std::uintptr_t Address = 0x400065b4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TIME = CortexM3::Field<ValueType, 16, 16>;
    using F_FMI = CortexM3::Field<ValueType, 8, 8>;
    using F_DLC = CortexM3::Field<ValueType, 0, 4>;
};

class CAN_RDL0R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDATA3() noexcept -> ValueType { return Reg::Read<F_DATA3>(); }
    static auto ReadDATA2() noexcept -> ValueType { return Reg::Read<F_DATA2>(); }
    static auto ReadDATA1() noexcept -> ValueType { return Reg::Read<F_DATA1>(); }
    static auto ReadDATA0() noexcept -> ValueType { return Reg::Read<F_DATA0>(); }

private:
    static constexpr std::uintptr_t Address = 0x400065b8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA3 = CortexM3::Field<ValueType, 24, 8>;
    using F_DATA2 = CortexM3::Field<ValueType, 16, 8>;
    using F_DATA1 = CortexM3::Field<ValueType, 8, 8>;
    using F_DATA0 = CortexM3::Field<ValueType, 0, 8>;
};

class CAN_RDH0R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDATA7() noexcept -> ValueType { return Reg::Read<F_DATA7>(); }
    static auto ReadDATA6() noexcept -> ValueType { return Reg::Read<F_DATA6>(); }
    static auto ReadDATA5() noexcept -> ValueType { return Reg::Read<F_DATA5>(); }
    static auto ReadDATA4() noexcept -> ValueType { return Reg::Read<F_DATA4>(); }

private:
    static constexpr std::uintptr_t Address = 0x400065bc;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA7 = CortexM3::Field<ValueType, 24, 8>;
    using F_DATA6 = CortexM3::Field<ValueType, 16, 8>;
    using F_DATA5 = CortexM3::Field<ValueType, 8, 8>;
    using F_DATA4 = CortexM3::Field<ValueType, 0, 8>;
};

class CAN_RI1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadSTID() noexcept -> ValueType { return Reg::Read<F_STID>(); }
    static auto ReadEXID() noexcept -> ValueType { return Reg::Read<F_EXID>(); }
    static auto ReadIDE() noexcept -> ValueType { return Reg::Read<F_IDE>(); }
    static auto ReadRTR() noexcept -> ValueType { return Reg::Read<F_RTR>(); }

private:
    static constexpr std::uintptr_t Address = 0x400065c0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STID = CortexM3::Field<ValueType, 21, 11>;
    using F_EXID = CortexM3::Field<ValueType, 3, 18>;
    using F_IDE = CortexM3::Field<ValueType, 2, 1>;
    using F_RTR = CortexM3::Field<ValueType, 1, 1>;
};

class CAN_RDT1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadTIME() noexcept -> ValueType { return Reg::Read<F_TIME>(); }
    static auto ReadFMI() noexcept -> ValueType { return Reg::Read<F_FMI>(); }
    static auto ReadDLC() noexcept -> ValueType { return Reg::Read<F_DLC>(); }

private:
    static constexpr std::uintptr_t Address = 0x400065c4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TIME = CortexM3::Field<ValueType, 16, 16>;
    using F_FMI = CortexM3::Field<ValueType, 8, 8>;
    using F_DLC = CortexM3::Field<ValueType, 0, 4>;
};

class CAN_RDL1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDATA3() noexcept -> ValueType { return Reg::Read<F_DATA3>(); }
    static auto ReadDATA2() noexcept -> ValueType { return Reg::Read<F_DATA2>(); }
    static auto ReadDATA1() noexcept -> ValueType { return Reg::Read<F_DATA1>(); }
    static auto ReadDATA0() noexcept -> ValueType { return Reg::Read<F_DATA0>(); }

private:
    static constexpr std::uintptr_t Address = 0x400065c8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA3 = CortexM3::Field<ValueType, 24, 8>;
    using F_DATA2 = CortexM3::Field<ValueType, 16, 8>;
    using F_DATA1 = CortexM3::Field<ValueType, 8, 8>;
    using F_DATA0 = CortexM3::Field<ValueType, 0, 8>;
};

class CAN_RDH1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDATA7() noexcept -> ValueType { return Reg::Read<F_DATA7>(); }
    static auto ReadDATA6() noexcept -> ValueType { return Reg::Read<F_DATA6>(); }
    static auto ReadDATA5() noexcept -> ValueType { return Reg::Read<F_DATA5>(); }
    static auto ReadDATA4() noexcept -> ValueType { return Reg::Read<F_DATA4>(); }

private:
    static constexpr std::uintptr_t Address = 0x400065cc;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DATA7 = CortexM3::Field<ValueType, 24, 8>;
    using F_DATA6 = CortexM3::Field<ValueType, 16, 8>;
    using F_DATA5 = CortexM3::Field<ValueType, 8, 8>;
    using F_DATA4 = CortexM3::Field<ValueType, 0, 8>;
};

class CAN_FMR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFINIT() noexcept -> ValueType { return Reg::Read<F_FINIT>(); }
    static void WriteFINIT(ValueType value) noexcept { Reg::Write<F_FINIT>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006600;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FINIT = CortexM3::Field<ValueType, 0, 1>;
};

class CAN_FM1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFBM0() noexcept -> ValueType { return Reg::Read<F_FBM0>(); }
    static void WriteFBM0(ValueType value) noexcept { Reg::Write<F_FBM0>(value); }
    static auto ReadFBM1() noexcept -> ValueType { return Reg::Read<F_FBM1>(); }
    static void WriteFBM1(ValueType value) noexcept { Reg::Write<F_FBM1>(value); }
    static auto ReadFBM2() noexcept -> ValueType { return Reg::Read<F_FBM2>(); }
    static void WriteFBM2(ValueType value) noexcept { Reg::Write<F_FBM2>(value); }
    static auto ReadFBM3() noexcept -> ValueType { return Reg::Read<F_FBM3>(); }
    static void WriteFBM3(ValueType value) noexcept { Reg::Write<F_FBM3>(value); }
    static auto ReadFBM4() noexcept -> ValueType { return Reg::Read<F_FBM4>(); }
    static void WriteFBM4(ValueType value) noexcept { Reg::Write<F_FBM4>(value); }
    static auto ReadFBM5() noexcept -> ValueType { return Reg::Read<F_FBM5>(); }
    static void WriteFBM5(ValueType value) noexcept { Reg::Write<F_FBM5>(value); }
    static auto ReadFBM6() noexcept -> ValueType { return Reg::Read<F_FBM6>(); }
    static void WriteFBM6(ValueType value) noexcept { Reg::Write<F_FBM6>(value); }
    static auto ReadFBM7() noexcept -> ValueType { return Reg::Read<F_FBM7>(); }
    static void WriteFBM7(ValueType value) noexcept { Reg::Write<F_FBM7>(value); }
    static auto ReadFBM8() noexcept -> ValueType { return Reg::Read<F_FBM8>(); }
    static void WriteFBM8(ValueType value) noexcept { Reg::Write<F_FBM8>(value); }
    static auto ReadFBM9() noexcept -> ValueType { return Reg::Read<F_FBM9>(); }
    static void WriteFBM9(ValueType value) noexcept { Reg::Write<F_FBM9>(value); }
    static auto ReadFBM10() noexcept -> ValueType { return Reg::Read<F_FBM10>(); }
    static void WriteFBM10(ValueType value) noexcept { Reg::Write<F_FBM10>(value); }
    static auto ReadFBM11() noexcept -> ValueType { return Reg::Read<F_FBM11>(); }
    static void WriteFBM11(ValueType value) noexcept { Reg::Write<F_FBM11>(value); }
    static auto ReadFBM12() noexcept -> ValueType { return Reg::Read<F_FBM12>(); }
    static void WriteFBM12(ValueType value) noexcept { Reg::Write<F_FBM12>(value); }
    static auto ReadFBM13() noexcept -> ValueType { return Reg::Read<F_FBM13>(); }
    static void WriteFBM13(ValueType value) noexcept { Reg::Write<F_FBM13>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006604;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FBM0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FBM1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FBM2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FBM3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FBM4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FBM5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FBM6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FBM7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FBM8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FBM9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FBM10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FBM11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FBM12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FBM13 = CortexM3::Field<ValueType, 13, 1>;
};

class CAN_FS1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFSC0() noexcept -> ValueType { return Reg::Read<F_FSC0>(); }
    static void WriteFSC0(ValueType value) noexcept { Reg::Write<F_FSC0>(value); }
    static auto ReadFSC1() noexcept -> ValueType { return Reg::Read<F_FSC1>(); }
    static void WriteFSC1(ValueType value) noexcept { Reg::Write<F_FSC1>(value); }
    static auto ReadFSC2() noexcept -> ValueType { return Reg::Read<F_FSC2>(); }
    static void WriteFSC2(ValueType value) noexcept { Reg::Write<F_FSC2>(value); }
    static auto ReadFSC3() noexcept -> ValueType { return Reg::Read<F_FSC3>(); }
    static void WriteFSC3(ValueType value) noexcept { Reg::Write<F_FSC3>(value); }
    static auto ReadFSC4() noexcept -> ValueType { return Reg::Read<F_FSC4>(); }
    static void WriteFSC4(ValueType value) noexcept { Reg::Write<F_FSC4>(value); }
    static auto ReadFSC5() noexcept -> ValueType { return Reg::Read<F_FSC5>(); }
    static void WriteFSC5(ValueType value) noexcept { Reg::Write<F_FSC5>(value); }
    static auto ReadFSC6() noexcept -> ValueType { return Reg::Read<F_FSC6>(); }
    static void WriteFSC6(ValueType value) noexcept { Reg::Write<F_FSC6>(value); }
    static auto ReadFSC7() noexcept -> ValueType { return Reg::Read<F_FSC7>(); }
    static void WriteFSC7(ValueType value) noexcept { Reg::Write<F_FSC7>(value); }
    static auto ReadFSC8() noexcept -> ValueType { return Reg::Read<F_FSC8>(); }
    static void WriteFSC8(ValueType value) noexcept { Reg::Write<F_FSC8>(value); }
    static auto ReadFSC9() noexcept -> ValueType { return Reg::Read<F_FSC9>(); }
    static void WriteFSC9(ValueType value) noexcept { Reg::Write<F_FSC9>(value); }
    static auto ReadFSC10() noexcept -> ValueType { return Reg::Read<F_FSC10>(); }
    static void WriteFSC10(ValueType value) noexcept { Reg::Write<F_FSC10>(value); }
    static auto ReadFSC11() noexcept -> ValueType { return Reg::Read<F_FSC11>(); }
    static void WriteFSC11(ValueType value) noexcept { Reg::Write<F_FSC11>(value); }
    static auto ReadFSC12() noexcept -> ValueType { return Reg::Read<F_FSC12>(); }
    static void WriteFSC12(ValueType value) noexcept { Reg::Write<F_FSC12>(value); }
    static auto ReadFSC13() noexcept -> ValueType { return Reg::Read<F_FSC13>(); }
    static void WriteFSC13(ValueType value) noexcept { Reg::Write<F_FSC13>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000660c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FSC0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FSC1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FSC2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FSC3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FSC4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FSC5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FSC6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FSC7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FSC8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FSC9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FSC10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FSC11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FSC12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FSC13 = CortexM3::Field<ValueType, 13, 1>;
};

class CAN_FFA1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFFA0() noexcept -> ValueType { return Reg::Read<F_FFA0>(); }
    static void WriteFFA0(ValueType value) noexcept { Reg::Write<F_FFA0>(value); }
    static auto ReadFFA1() noexcept -> ValueType { return Reg::Read<F_FFA1>(); }
    static void WriteFFA1(ValueType value) noexcept { Reg::Write<F_FFA1>(value); }
    static auto ReadFFA2() noexcept -> ValueType { return Reg::Read<F_FFA2>(); }
    static void WriteFFA2(ValueType value) noexcept { Reg::Write<F_FFA2>(value); }
    static auto ReadFFA3() noexcept -> ValueType { return Reg::Read<F_FFA3>(); }
    static void WriteFFA3(ValueType value) noexcept { Reg::Write<F_FFA3>(value); }
    static auto ReadFFA4() noexcept -> ValueType { return Reg::Read<F_FFA4>(); }
    static void WriteFFA4(ValueType value) noexcept { Reg::Write<F_FFA4>(value); }
    static auto ReadFFA5() noexcept -> ValueType { return Reg::Read<F_FFA5>(); }
    static void WriteFFA5(ValueType value) noexcept { Reg::Write<F_FFA5>(value); }
    static auto ReadFFA6() noexcept -> ValueType { return Reg::Read<F_FFA6>(); }
    static void WriteFFA6(ValueType value) noexcept { Reg::Write<F_FFA6>(value); }
    static auto ReadFFA7() noexcept -> ValueType { return Reg::Read<F_FFA7>(); }
    static void WriteFFA7(ValueType value) noexcept { Reg::Write<F_FFA7>(value); }
    static auto ReadFFA8() noexcept -> ValueType { return Reg::Read<F_FFA8>(); }
    static void WriteFFA8(ValueType value) noexcept { Reg::Write<F_FFA8>(value); }
    static auto ReadFFA9() noexcept -> ValueType { return Reg::Read<F_FFA9>(); }
    static void WriteFFA9(ValueType value) noexcept { Reg::Write<F_FFA9>(value); }
    static auto ReadFFA10() noexcept -> ValueType { return Reg::Read<F_FFA10>(); }
    static void WriteFFA10(ValueType value) noexcept { Reg::Write<F_FFA10>(value); }
    static auto ReadFFA11() noexcept -> ValueType { return Reg::Read<F_FFA11>(); }
    static void WriteFFA11(ValueType value) noexcept { Reg::Write<F_FFA11>(value); }
    static auto ReadFFA12() noexcept -> ValueType { return Reg::Read<F_FFA12>(); }
    static void WriteFFA12(ValueType value) noexcept { Reg::Write<F_FFA12>(value); }
    static auto ReadFFA13() noexcept -> ValueType { return Reg::Read<F_FFA13>(); }
    static void WriteFFA13(ValueType value) noexcept { Reg::Write<F_FFA13>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006614;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FFA0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FFA1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FFA2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FFA3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FFA4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FFA5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FFA6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FFA7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FFA8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FFA9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FFA10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FFA11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FFA12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FFA13 = CortexM3::Field<ValueType, 13, 1>;
};

class CAN_FA1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFACT0() noexcept -> ValueType { return Reg::Read<F_FACT0>(); }
    static void WriteFACT0(ValueType value) noexcept { Reg::Write<F_FACT0>(value); }
    static auto ReadFACT1() noexcept -> ValueType { return Reg::Read<F_FACT1>(); }
    static void WriteFACT1(ValueType value) noexcept { Reg::Write<F_FACT1>(value); }
    static auto ReadFACT2() noexcept -> ValueType { return Reg::Read<F_FACT2>(); }
    static void WriteFACT2(ValueType value) noexcept { Reg::Write<F_FACT2>(value); }
    static auto ReadFACT3() noexcept -> ValueType { return Reg::Read<F_FACT3>(); }
    static void WriteFACT3(ValueType value) noexcept { Reg::Write<F_FACT3>(value); }
    static auto ReadFACT4() noexcept -> ValueType { return Reg::Read<F_FACT4>(); }
    static void WriteFACT4(ValueType value) noexcept { Reg::Write<F_FACT4>(value); }
    static auto ReadFACT5() noexcept -> ValueType { return Reg::Read<F_FACT5>(); }
    static void WriteFACT5(ValueType value) noexcept { Reg::Write<F_FACT5>(value); }
    static auto ReadFACT6() noexcept -> ValueType { return Reg::Read<F_FACT6>(); }
    static void WriteFACT6(ValueType value) noexcept { Reg::Write<F_FACT6>(value); }
    static auto ReadFACT7() noexcept -> ValueType { return Reg::Read<F_FACT7>(); }
    static void WriteFACT7(ValueType value) noexcept { Reg::Write<F_FACT7>(value); }
    static auto ReadFACT8() noexcept -> ValueType { return Reg::Read<F_FACT8>(); }
    static void WriteFACT8(ValueType value) noexcept { Reg::Write<F_FACT8>(value); }
    static auto ReadFACT9() noexcept -> ValueType { return Reg::Read<F_FACT9>(); }
    static void WriteFACT9(ValueType value) noexcept { Reg::Write<F_FACT9>(value); }
    static auto ReadFACT10() noexcept -> ValueType { return Reg::Read<F_FACT10>(); }
    static void WriteFACT10(ValueType value) noexcept { Reg::Write<F_FACT10>(value); }
    static auto ReadFACT11() noexcept -> ValueType { return Reg::Read<F_FACT11>(); }
    static void WriteFACT11(ValueType value) noexcept { Reg::Write<F_FACT11>(value); }
    static auto ReadFACT12() noexcept -> ValueType { return Reg::Read<F_FACT12>(); }
    static void WriteFACT12(ValueType value) noexcept { Reg::Write<F_FACT12>(value); }
    static auto ReadFACT13() noexcept -> ValueType { return Reg::Read<F_FACT13>(); }
    static void WriteFACT13(ValueType value) noexcept { Reg::Write<F_FACT13>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000661c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FACT0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FACT1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FACT2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FACT3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FACT4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FACT5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FACT6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FACT7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FACT8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FACT9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FACT10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FACT11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FACT12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FACT13 = CortexM3::Field<ValueType, 13, 1>;
};

class F0R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006640;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F0R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006644;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F1R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006648;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F1R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000664c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F2R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006650;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F2R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006654;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F3R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006658;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F3R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000665c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F4R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006660;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F4R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006664;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F5R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006668;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F5R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000666c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F6R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006670;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F6R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006674;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F7R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006678;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F7R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000667c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F8R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006680;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F8R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006684;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F9R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006688;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F9R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000668c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F10R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006690;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F10R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006694;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F11R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40006698;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F11R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000669c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F12R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x400066a0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F12R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x400066a4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F13R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x400066a8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

class F13R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFB0() noexcept -> ValueType { return Reg::Read<F_FB0>(); }
    static void WriteFB0(ValueType value) noexcept { Reg::Write<F_FB0>(value); }
    static auto ReadFB1() noexcept -> ValueType { return Reg::Read<F_FB1>(); }
    static void WriteFB1(ValueType value) noexcept { Reg::Write<F_FB1>(value); }
    static auto ReadFB2() noexcept -> ValueType { return Reg::Read<F_FB2>(); }
    static void WriteFB2(ValueType value) noexcept { Reg::Write<F_FB2>(value); }
    static auto ReadFB3() noexcept -> ValueType { return Reg::Read<F_FB3>(); }
    static void WriteFB3(ValueType value) noexcept { Reg::Write<F_FB3>(value); }
    static auto ReadFB4() noexcept -> ValueType { return Reg::Read<F_FB4>(); }
    static void WriteFB4(ValueType value) noexcept { Reg::Write<F_FB4>(value); }
    static auto ReadFB5() noexcept -> ValueType { return Reg::Read<F_FB5>(); }
    static void WriteFB5(ValueType value) noexcept { Reg::Write<F_FB5>(value); }
    static auto ReadFB6() noexcept -> ValueType { return Reg::Read<F_FB6>(); }
    static void WriteFB6(ValueType value) noexcept { Reg::Write<F_FB6>(value); }
    static auto ReadFB7() noexcept -> ValueType { return Reg::Read<F_FB7>(); }
    static void WriteFB7(ValueType value) noexcept { Reg::Write<F_FB7>(value); }
    static auto ReadFB8() noexcept -> ValueType { return Reg::Read<F_FB8>(); }
    static void WriteFB8(ValueType value) noexcept { Reg::Write<F_FB8>(value); }
    static auto ReadFB9() noexcept -> ValueType { return Reg::Read<F_FB9>(); }
    static void WriteFB9(ValueType value) noexcept { Reg::Write<F_FB9>(value); }
    static auto ReadFB10() noexcept -> ValueType { return Reg::Read<F_FB10>(); }
    static void WriteFB10(ValueType value) noexcept { Reg::Write<F_FB10>(value); }
    static auto ReadFB11() noexcept -> ValueType { return Reg::Read<F_FB11>(); }
    static void WriteFB11(ValueType value) noexcept { Reg::Write<F_FB11>(value); }
    static auto ReadFB12() noexcept -> ValueType { return Reg::Read<F_FB12>(); }
    static void WriteFB12(ValueType value) noexcept { Reg::Write<F_FB12>(value); }
    static auto ReadFB13() noexcept -> ValueType { return Reg::Read<F_FB13>(); }
    static void WriteFB13(ValueType value) noexcept { Reg::Write<F_FB13>(value); }
    static auto ReadFB14() noexcept -> ValueType { return Reg::Read<F_FB14>(); }
    static void WriteFB14(ValueType value) noexcept { Reg::Write<F_FB14>(value); }
    static auto ReadFB15() noexcept -> ValueType { return Reg::Read<F_FB15>(); }
    static void WriteFB15(ValueType value) noexcept { Reg::Write<F_FB15>(value); }
    static auto ReadFB16() noexcept -> ValueType { return Reg::Read<F_FB16>(); }
    static void WriteFB16(ValueType value) noexcept { Reg::Write<F_FB16>(value); }
    static auto ReadFB17() noexcept -> ValueType { return Reg::Read<F_FB17>(); }
    static void WriteFB17(ValueType value) noexcept { Reg::Write<F_FB17>(value); }
    static auto ReadFB18() noexcept -> ValueType { return Reg::Read<F_FB18>(); }
    static void WriteFB18(ValueType value) noexcept { Reg::Write<F_FB18>(value); }
    static auto ReadFB19() noexcept -> ValueType { return Reg::Read<F_FB19>(); }
    static void WriteFB19(ValueType value) noexcept { Reg::Write<F_FB19>(value); }
    static auto ReadFB20() noexcept -> ValueType { return Reg::Read<F_FB20>(); }
    static void WriteFB20(ValueType value) noexcept { Reg::Write<F_FB20>(value); }
    static auto ReadFB21() noexcept -> ValueType { return Reg::Read<F_FB21>(); }
    static void WriteFB21(ValueType value) noexcept { Reg::Write<F_FB21>(value); }
    static auto ReadFB22() noexcept -> ValueType { return Reg::Read<F_FB22>(); }
    static void WriteFB22(ValueType value) noexcept { Reg::Write<F_FB22>(value); }
    static auto ReadFB23() noexcept -> ValueType { return Reg::Read<F_FB23>(); }
    static void WriteFB23(ValueType value) noexcept { Reg::Write<F_FB23>(value); }
    static auto ReadFB24() noexcept -> ValueType { return Reg::Read<F_FB24>(); }
    static void WriteFB24(ValueType value) noexcept { Reg::Write<F_FB24>(value); }
    static auto ReadFB25() noexcept -> ValueType { return Reg::Read<F_FB25>(); }
    static void WriteFB25(ValueType value) noexcept { Reg::Write<F_FB25>(value); }
    static auto ReadFB26() noexcept -> ValueType { return Reg::Read<F_FB26>(); }
    static void WriteFB26(ValueType value) noexcept { Reg::Write<F_FB26>(value); }
    static auto ReadFB27() noexcept -> ValueType { return Reg::Read<F_FB27>(); }
    static void WriteFB27(ValueType value) noexcept { Reg::Write<F_FB27>(value); }
    static auto ReadFB28() noexcept -> ValueType { return Reg::Read<F_FB28>(); }
    static void WriteFB28(ValueType value) noexcept { Reg::Write<F_FB28>(value); }
    static auto ReadFB29() noexcept -> ValueType { return Reg::Read<F_FB29>(); }
    static void WriteFB29(ValueType value) noexcept { Reg::Write<F_FB29>(value); }
    static auto ReadFB30() noexcept -> ValueType { return Reg::Read<F_FB30>(); }
    static void WriteFB30(ValueType value) noexcept { Reg::Write<F_FB30>(value); }
    static auto ReadFB31() noexcept -> ValueType { return Reg::Read<F_FB31>(); }
    static void WriteFB31(ValueType value) noexcept { Reg::Write<F_FB31>(value); }

private:
    static constexpr std::uintptr_t Address = 0x400066ac;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FB0 = CortexM3::Field<ValueType, 0, 1>;
    using F_FB1 = CortexM3::Field<ValueType, 1, 1>;
    using F_FB2 = CortexM3::Field<ValueType, 2, 1>;
    using F_FB3 = CortexM3::Field<ValueType, 3, 1>;
    using F_FB4 = CortexM3::Field<ValueType, 4, 1>;
    using F_FB5 = CortexM3::Field<ValueType, 5, 1>;
    using F_FB6 = CortexM3::Field<ValueType, 6, 1>;
    using F_FB7 = CortexM3::Field<ValueType, 7, 1>;
    using F_FB8 = CortexM3::Field<ValueType, 8, 1>;
    using F_FB9 = CortexM3::Field<ValueType, 9, 1>;
    using F_FB10 = CortexM3::Field<ValueType, 10, 1>;
    using F_FB11 = CortexM3::Field<ValueType, 11, 1>;
    using F_FB12 = CortexM3::Field<ValueType, 12, 1>;
    using F_FB13 = CortexM3::Field<ValueType, 13, 1>;
    using F_FB14 = CortexM3::Field<ValueType, 14, 1>;
    using F_FB15 = CortexM3::Field<ValueType, 15, 1>;
    using F_FB16 = CortexM3::Field<ValueType, 16, 1>;
    using F_FB17 = CortexM3::Field<ValueType, 17, 1>;
    using F_FB18 = CortexM3::Field<ValueType, 18, 1>;
    using F_FB19 = CortexM3::Field<ValueType, 19, 1>;
    using F_FB20 = CortexM3::Field<ValueType, 20, 1>;
    using F_FB21 = CortexM3::Field<ValueType, 21, 1>;
    using F_FB22 = CortexM3::Field<ValueType, 22, 1>;
    using F_FB23 = CortexM3::Field<ValueType, 23, 1>;
    using F_FB24 = CortexM3::Field<ValueType, 24, 1>;
    using F_FB25 = CortexM3::Field<ValueType, 25, 1>;
    using F_FB26 = CortexM3::Field<ValueType, 26, 1>;
    using F_FB27 = CortexM3::Field<ValueType, 27, 1>;
    using F_FB28 = CortexM3::Field<ValueType, 28, 1>;
    using F_FB29 = CortexM3::Field<ValueType, 29, 1>;
    using F_FB30 = CortexM3::Field<ValueType, 30, 1>;
    using F_FB31 = CortexM3::Field<ValueType, 31, 1>;
};

} // namespace STM32F103::CAN1
