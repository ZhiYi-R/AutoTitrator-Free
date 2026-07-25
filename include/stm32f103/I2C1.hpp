#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::I2C1 {

class CR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSWRST() noexcept -> ValueType { return Reg::Read<F_SWRST>(); }
    static void WriteSWRST(ValueType value) noexcept { Reg::Write<F_SWRST>(value); }
    static auto ReadALERT() noexcept -> ValueType { return Reg::Read<F_ALERT>(); }
    static void WriteALERT(ValueType value) noexcept { Reg::Write<F_ALERT>(value); }
    static auto ReadPEC() noexcept -> ValueType { return Reg::Read<F_PEC>(); }
    static void WritePEC(ValueType value) noexcept { Reg::Write<F_PEC>(value); }
    static auto ReadPOS() noexcept -> ValueType { return Reg::Read<F_POS>(); }
    static void WritePOS(ValueType value) noexcept { Reg::Write<F_POS>(value); }
    static auto ReadACK() noexcept -> ValueType { return Reg::Read<F_ACK>(); }
    static void WriteACK(ValueType value) noexcept { Reg::Write<F_ACK>(value); }
    static auto ReadSTOP() noexcept -> ValueType { return Reg::Read<F_STOP>(); }
    static void WriteSTOP(ValueType value) noexcept { Reg::Write<F_STOP>(value); }
    static auto ReadSTART() noexcept -> ValueType { return Reg::Read<F_START>(); }
    static void WriteSTART(ValueType value) noexcept { Reg::Write<F_START>(value); }
    static auto ReadNOSTRETCH() noexcept -> ValueType { return Reg::Read<F_NOSTRETCH>(); }
    static void WriteNOSTRETCH(ValueType value) noexcept { Reg::Write<F_NOSTRETCH>(value); }
    static auto ReadENGC() noexcept -> ValueType { return Reg::Read<F_ENGC>(); }
    static void WriteENGC(ValueType value) noexcept { Reg::Write<F_ENGC>(value); }
    static auto ReadENPEC() noexcept -> ValueType { return Reg::Read<F_ENPEC>(); }
    static void WriteENPEC(ValueType value) noexcept { Reg::Write<F_ENPEC>(value); }
    static auto ReadENARP() noexcept -> ValueType { return Reg::Read<F_ENARP>(); }
    static void WriteENARP(ValueType value) noexcept { Reg::Write<F_ENARP>(value); }
    static auto ReadSMBTYPE() noexcept -> ValueType { return Reg::Read<F_SMBTYPE>(); }
    static void WriteSMBTYPE(ValueType value) noexcept { Reg::Write<F_SMBTYPE>(value); }
    static auto ReadSMBUS() noexcept -> ValueType { return Reg::Read<F_SMBUS>(); }
    static void WriteSMBUS(ValueType value) noexcept { Reg::Write<F_SMBUS>(value); }
    static auto ReadPE() noexcept -> ValueType { return Reg::Read<F_PE>(); }
    static void WritePE(ValueType value) noexcept { Reg::Write<F_PE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005400;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SWRST = CortexM3::Field<ValueType, 15, 1>;
    using F_ALERT = CortexM3::Field<ValueType, 13, 1>;
    using F_PEC = CortexM3::Field<ValueType, 12, 1>;
    using F_POS = CortexM3::Field<ValueType, 11, 1>;
    using F_ACK = CortexM3::Field<ValueType, 10, 1>;
    using F_STOP = CortexM3::Field<ValueType, 9, 1>;
    using F_START = CortexM3::Field<ValueType, 8, 1>;
    using F_NOSTRETCH = CortexM3::Field<ValueType, 7, 1>;
    using F_ENGC = CortexM3::Field<ValueType, 6, 1>;
    using F_ENPEC = CortexM3::Field<ValueType, 5, 1>;
    using F_ENARP = CortexM3::Field<ValueType, 4, 1>;
    using F_SMBTYPE = CortexM3::Field<ValueType, 3, 1>;
    using F_SMBUS = CortexM3::Field<ValueType, 1, 1>;
    using F_PE = CortexM3::Field<ValueType, 0, 1>;
};

class CR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadLAST() noexcept -> ValueType { return Reg::Read<F_LAST>(); }
    static void WriteLAST(ValueType value) noexcept { Reg::Write<F_LAST>(value); }
    static auto ReadDMAEN() noexcept -> ValueType { return Reg::Read<F_DMAEN>(); }
    static void WriteDMAEN(ValueType value) noexcept { Reg::Write<F_DMAEN>(value); }
    static auto ReadITBUFEN() noexcept -> ValueType { return Reg::Read<F_ITBUFEN>(); }
    static void WriteITBUFEN(ValueType value) noexcept { Reg::Write<F_ITBUFEN>(value); }
    static auto ReadITEVTEN() noexcept -> ValueType { return Reg::Read<F_ITEVTEN>(); }
    static void WriteITEVTEN(ValueType value) noexcept { Reg::Write<F_ITEVTEN>(value); }
    static auto ReadITERREN() noexcept -> ValueType { return Reg::Read<F_ITERREN>(); }
    static void WriteITERREN(ValueType value) noexcept { Reg::Write<F_ITERREN>(value); }
    static auto ReadFREQ() noexcept -> ValueType { return Reg::Read<F_FREQ>(); }
    static void WriteFREQ(ValueType value) noexcept { Reg::Write<F_FREQ>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005404;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_LAST = CortexM3::Field<ValueType, 12, 1>;
    using F_DMAEN = CortexM3::Field<ValueType, 11, 1>;
    using F_ITBUFEN = CortexM3::Field<ValueType, 10, 1>;
    using F_ITEVTEN = CortexM3::Field<ValueType, 9, 1>;
    using F_ITERREN = CortexM3::Field<ValueType, 8, 1>;
    using F_FREQ = CortexM3::Field<ValueType, 0, 6>;
};

class OAR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadADDMODE() noexcept -> ValueType { return Reg::Read<F_ADDMODE>(); }
    static void WriteADDMODE(ValueType value) noexcept { Reg::Write<F_ADDMODE>(value); }
    static auto ReadADD10() noexcept -> ValueType { return Reg::Read<F_ADD10>(); }
    static void WriteADD10(ValueType value) noexcept { Reg::Write<F_ADD10>(value); }
    static auto ReadADD7() noexcept -> ValueType { return Reg::Read<F_ADD7>(); }
    static void WriteADD7(ValueType value) noexcept { Reg::Write<F_ADD7>(value); }
    static auto ReadADD0() noexcept -> ValueType { return Reg::Read<F_ADD0>(); }
    static void WriteADD0(ValueType value) noexcept { Reg::Write<F_ADD0>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005408;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ADDMODE = CortexM3::Field<ValueType, 15, 1>;
    using F_ADD10 = CortexM3::Field<ValueType, 8, 2>;
    using F_ADD7 = CortexM3::Field<ValueType, 1, 7>;
    using F_ADD0 = CortexM3::Field<ValueType, 0, 1>;
};

class OAR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadADD2() noexcept -> ValueType { return Reg::Read<F_ADD2>(); }
    static void WriteADD2(ValueType value) noexcept { Reg::Write<F_ADD2>(value); }
    static auto ReadENDUAL() noexcept -> ValueType { return Reg::Read<F_ENDUAL>(); }
    static void WriteENDUAL(ValueType value) noexcept { Reg::Write<F_ENDUAL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000540c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ADD2 = CortexM3::Field<ValueType, 1, 7>;
    using F_ENDUAL = CortexM3::Field<ValueType, 0, 1>;
};

class DR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDR() noexcept -> ValueType { return Reg::Read<F_DR>(); }
    static void WriteDR(ValueType value) noexcept { Reg::Write<F_DR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005410;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DR = CortexM3::Field<ValueType, 0, 8>;
};

class SR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSMBALERT() noexcept -> ValueType { return Reg::Read<F_SMBALERT>(); }
    static void WriteSMBALERT(ValueType value) noexcept { Reg::Write<F_SMBALERT>(value); }
    static auto ReadTIMEOUT() noexcept -> ValueType { return Reg::Read<F_TIMEOUT>(); }
    static void WriteTIMEOUT(ValueType value) noexcept { Reg::Write<F_TIMEOUT>(value); }
    static auto ReadPECERR() noexcept -> ValueType { return Reg::Read<F_PECERR>(); }
    static void WritePECERR(ValueType value) noexcept { Reg::Write<F_PECERR>(value); }
    static auto ReadOVR() noexcept -> ValueType { return Reg::Read<F_OVR>(); }
    static void WriteOVR(ValueType value) noexcept { Reg::Write<F_OVR>(value); }
    static auto ReadAF() noexcept -> ValueType { return Reg::Read<F_AF>(); }
    static void WriteAF(ValueType value) noexcept { Reg::Write<F_AF>(value); }
    static auto ReadARLO() noexcept -> ValueType { return Reg::Read<F_ARLO>(); }
    static void WriteARLO(ValueType value) noexcept { Reg::Write<F_ARLO>(value); }
    static auto ReadBERR() noexcept -> ValueType { return Reg::Read<F_BERR>(); }
    static void WriteBERR(ValueType value) noexcept { Reg::Write<F_BERR>(value); }
    static auto ReadTxE() noexcept -> ValueType { return Reg::Read<F_TxE>(); }
    static auto ReadRxNE() noexcept -> ValueType { return Reg::Read<F_RxNE>(); }
    static auto ReadSTOPF() noexcept -> ValueType { return Reg::Read<F_STOPF>(); }
    static auto ReadADD10() noexcept -> ValueType { return Reg::Read<F_ADD10>(); }
    static auto ReadBTF() noexcept -> ValueType { return Reg::Read<F_BTF>(); }
    static auto ReadADDR() noexcept -> ValueType { return Reg::Read<F_ADDR>(); }
    static auto ReadSB() noexcept -> ValueType { return Reg::Read<F_SB>(); }

private:
    static constexpr std::uintptr_t Address = 0x40005414;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SMBALERT = CortexM3::Field<ValueType, 15, 1>;
    using F_TIMEOUT = CortexM3::Field<ValueType, 14, 1>;
    using F_PECERR = CortexM3::Field<ValueType, 12, 1>;
    using F_OVR = CortexM3::Field<ValueType, 11, 1>;
    using F_AF = CortexM3::Field<ValueType, 10, 1>;
    using F_ARLO = CortexM3::Field<ValueType, 9, 1>;
    using F_BERR = CortexM3::Field<ValueType, 8, 1>;
    using F_TxE = CortexM3::Field<ValueType, 7, 1>;
    using F_RxNE = CortexM3::Field<ValueType, 6, 1>;
    using F_STOPF = CortexM3::Field<ValueType, 4, 1>;
    using F_ADD10 = CortexM3::Field<ValueType, 3, 1>;
    using F_BTF = CortexM3::Field<ValueType, 2, 1>;
    using F_ADDR = CortexM3::Field<ValueType, 1, 1>;
    using F_SB = CortexM3::Field<ValueType, 0, 1>;
};

class SR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadPEC() noexcept -> ValueType { return Reg::Read<F_PEC>(); }
    static auto ReadDUALF() noexcept -> ValueType { return Reg::Read<F_DUALF>(); }
    static auto ReadSMBHOST() noexcept -> ValueType { return Reg::Read<F_SMBHOST>(); }
    static auto ReadSMBDEFAULT() noexcept -> ValueType { return Reg::Read<F_SMBDEFAULT>(); }
    static auto ReadGENCALL() noexcept -> ValueType { return Reg::Read<F_GENCALL>(); }
    static auto ReadTRA() noexcept -> ValueType { return Reg::Read<F_TRA>(); }
    static auto ReadBUSY() noexcept -> ValueType { return Reg::Read<F_BUSY>(); }
    static auto ReadMSL() noexcept -> ValueType { return Reg::Read<F_MSL>(); }

private:
    static constexpr std::uintptr_t Address = 0x40005418;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PEC = CortexM3::Field<ValueType, 8, 8>;
    using F_DUALF = CortexM3::Field<ValueType, 7, 1>;
    using F_SMBHOST = CortexM3::Field<ValueType, 6, 1>;
    using F_SMBDEFAULT = CortexM3::Field<ValueType, 5, 1>;
    using F_GENCALL = CortexM3::Field<ValueType, 4, 1>;
    using F_TRA = CortexM3::Field<ValueType, 2, 1>;
    using F_BUSY = CortexM3::Field<ValueType, 1, 1>;
    using F_MSL = CortexM3::Field<ValueType, 0, 1>;
};

class CCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadF_S() noexcept -> ValueType { return Reg::Read<F_F_S>(); }
    static void WriteF_S(ValueType value) noexcept { Reg::Write<F_F_S>(value); }
    static auto ReadDUTY() noexcept -> ValueType { return Reg::Read<F_DUTY>(); }
    static void WriteDUTY(ValueType value) noexcept { Reg::Write<F_DUTY>(value); }
    static auto ReadCCR() noexcept -> ValueType { return Reg::Read<F_CCR>(); }
    static void WriteCCR(ValueType value) noexcept { Reg::Write<F_CCR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000541c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_F_S = CortexM3::Field<ValueType, 15, 1>;
    using F_DUTY = CortexM3::Field<ValueType, 14, 1>;
    using F_CCR = CortexM3::Field<ValueType, 0, 12>;
};

class TRISE {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000002;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTRISE() noexcept -> ValueType { return Reg::Read<F_TRISE>(); }
    static void WriteTRISE(ValueType value) noexcept { Reg::Write<F_TRISE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005420;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TRISE = CortexM3::Field<ValueType, 0, 6>;
};

} // namespace STM32F103::I2C1
