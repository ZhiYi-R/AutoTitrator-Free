#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::USART3 {

class SR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x000000C0;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCTS() noexcept -> ValueType { return Reg::Read<F_CTS>(); }
    static void WriteCTS(ValueType value) noexcept { Reg::Write<F_CTS>(value); }
    static auto ReadLBD() noexcept -> ValueType { return Reg::Read<F_LBD>(); }
    static void WriteLBD(ValueType value) noexcept { Reg::Write<F_LBD>(value); }
    static auto ReadTXE() noexcept -> ValueType { return Reg::Read<F_TXE>(); }
    static auto ReadTC() noexcept -> ValueType { return Reg::Read<F_TC>(); }
    static void WriteTC(ValueType value) noexcept { Reg::Write<F_TC>(value); }
    static auto ReadRXNE() noexcept -> ValueType { return Reg::Read<F_RXNE>(); }
    static void WriteRXNE(ValueType value) noexcept { Reg::Write<F_RXNE>(value); }
    static auto ReadIDLE() noexcept -> ValueType { return Reg::Read<F_IDLE>(); }
    static auto ReadORE() noexcept -> ValueType { return Reg::Read<F_ORE>(); }
    static auto ReadNE() noexcept -> ValueType { return Reg::Read<F_NE>(); }
    static auto ReadFE() noexcept -> ValueType { return Reg::Read<F_FE>(); }
    static auto ReadPE() noexcept -> ValueType { return Reg::Read<F_PE>(); }

private:
    static constexpr std::uintptr_t Address = 0x40004800;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CTS = CortexM3::Field<ValueType, 9, 1>;
    using F_LBD = CortexM3::Field<ValueType, 8, 1>;
    using F_TXE = CortexM3::Field<ValueType, 7, 1>;
    using F_TC = CortexM3::Field<ValueType, 6, 1>;
    using F_RXNE = CortexM3::Field<ValueType, 5, 1>;
    using F_IDLE = CortexM3::Field<ValueType, 4, 1>;
    using F_ORE = CortexM3::Field<ValueType, 3, 1>;
    using F_NE = CortexM3::Field<ValueType, 2, 1>;
    using F_FE = CortexM3::Field<ValueType, 1, 1>;
    using F_PE = CortexM3::Field<ValueType, 0, 1>;
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
    static constexpr std::uintptr_t Address = 0x40004804;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DR = CortexM3::Field<ValueType, 0, 9>;
};

class BRR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDIV_Mantissa() noexcept -> ValueType { return Reg::Read<F_DIV_Mantissa>(); }
    static void WriteDIV_Mantissa(ValueType value) noexcept { Reg::Write<F_DIV_Mantissa>(value); }
    static auto ReadDIV_Fraction() noexcept -> ValueType { return Reg::Read<F_DIV_Fraction>(); }
    static void WriteDIV_Fraction(ValueType value) noexcept { Reg::Write<F_DIV_Fraction>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40004808;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DIV_Mantissa = CortexM3::Field<ValueType, 4, 12>;
    using F_DIV_Fraction = CortexM3::Field<ValueType, 0, 4>;
};

class CR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadUE() noexcept -> ValueType { return Reg::Read<F_UE>(); }
    static void WriteUE(ValueType value) noexcept { Reg::Write<F_UE>(value); }
    static auto ReadM() noexcept -> ValueType { return Reg::Read<F_M>(); }
    static void WriteM(ValueType value) noexcept { Reg::Write<F_M>(value); }
    static auto ReadWAKE() noexcept -> ValueType { return Reg::Read<F_WAKE>(); }
    static void WriteWAKE(ValueType value) noexcept { Reg::Write<F_WAKE>(value); }
    static auto ReadPCE() noexcept -> ValueType { return Reg::Read<F_PCE>(); }
    static void WritePCE(ValueType value) noexcept { Reg::Write<F_PCE>(value); }
    static auto ReadPS() noexcept -> ValueType { return Reg::Read<F_PS>(); }
    static void WritePS(ValueType value) noexcept { Reg::Write<F_PS>(value); }
    static auto ReadPEIE() noexcept -> ValueType { return Reg::Read<F_PEIE>(); }
    static void WritePEIE(ValueType value) noexcept { Reg::Write<F_PEIE>(value); }
    static auto ReadTXEIE() noexcept -> ValueType { return Reg::Read<F_TXEIE>(); }
    static void WriteTXEIE(ValueType value) noexcept { Reg::Write<F_TXEIE>(value); }
    static auto ReadTCIE() noexcept -> ValueType { return Reg::Read<F_TCIE>(); }
    static void WriteTCIE(ValueType value) noexcept { Reg::Write<F_TCIE>(value); }
    static auto ReadRXNEIE() noexcept -> ValueType { return Reg::Read<F_RXNEIE>(); }
    static void WriteRXNEIE(ValueType value) noexcept { Reg::Write<F_RXNEIE>(value); }
    static auto ReadIDLEIE() noexcept -> ValueType { return Reg::Read<F_IDLEIE>(); }
    static void WriteIDLEIE(ValueType value) noexcept { Reg::Write<F_IDLEIE>(value); }
    static auto ReadTE() noexcept -> ValueType { return Reg::Read<F_TE>(); }
    static void WriteTE(ValueType value) noexcept { Reg::Write<F_TE>(value); }
    static auto ReadRE() noexcept -> ValueType { return Reg::Read<F_RE>(); }
    static void WriteRE(ValueType value) noexcept { Reg::Write<F_RE>(value); }
    static auto ReadRWU() noexcept -> ValueType { return Reg::Read<F_RWU>(); }
    static void WriteRWU(ValueType value) noexcept { Reg::Write<F_RWU>(value); }
    static auto ReadSBK() noexcept -> ValueType { return Reg::Read<F_SBK>(); }
    static void WriteSBK(ValueType value) noexcept { Reg::Write<F_SBK>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000480c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_UE = CortexM3::Field<ValueType, 13, 1>;
    using F_M = CortexM3::Field<ValueType, 12, 1>;
    using F_WAKE = CortexM3::Field<ValueType, 11, 1>;
    using F_PCE = CortexM3::Field<ValueType, 10, 1>;
    using F_PS = CortexM3::Field<ValueType, 9, 1>;
    using F_PEIE = CortexM3::Field<ValueType, 8, 1>;
    using F_TXEIE = CortexM3::Field<ValueType, 7, 1>;
    using F_TCIE = CortexM3::Field<ValueType, 6, 1>;
    using F_RXNEIE = CortexM3::Field<ValueType, 5, 1>;
    using F_IDLEIE = CortexM3::Field<ValueType, 4, 1>;
    using F_TE = CortexM3::Field<ValueType, 3, 1>;
    using F_RE = CortexM3::Field<ValueType, 2, 1>;
    using F_RWU = CortexM3::Field<ValueType, 1, 1>;
    using F_SBK = CortexM3::Field<ValueType, 0, 1>;
};

class CR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadLINEN() noexcept -> ValueType { return Reg::Read<F_LINEN>(); }
    static void WriteLINEN(ValueType value) noexcept { Reg::Write<F_LINEN>(value); }
    static auto ReadSTOP() noexcept -> ValueType { return Reg::Read<F_STOP>(); }
    static void WriteSTOP(ValueType value) noexcept { Reg::Write<F_STOP>(value); }
    static auto ReadCLKEN() noexcept -> ValueType { return Reg::Read<F_CLKEN>(); }
    static void WriteCLKEN(ValueType value) noexcept { Reg::Write<F_CLKEN>(value); }
    static auto ReadCPOL() noexcept -> ValueType { return Reg::Read<F_CPOL>(); }
    static void WriteCPOL(ValueType value) noexcept { Reg::Write<F_CPOL>(value); }
    static auto ReadCPHA() noexcept -> ValueType { return Reg::Read<F_CPHA>(); }
    static void WriteCPHA(ValueType value) noexcept { Reg::Write<F_CPHA>(value); }
    static auto ReadLBCL() noexcept -> ValueType { return Reg::Read<F_LBCL>(); }
    static void WriteLBCL(ValueType value) noexcept { Reg::Write<F_LBCL>(value); }
    static auto ReadLBDIE() noexcept -> ValueType { return Reg::Read<F_LBDIE>(); }
    static void WriteLBDIE(ValueType value) noexcept { Reg::Write<F_LBDIE>(value); }
    static auto ReadLBDL() noexcept -> ValueType { return Reg::Read<F_LBDL>(); }
    static void WriteLBDL(ValueType value) noexcept { Reg::Write<F_LBDL>(value); }
    static auto ReadADD() noexcept -> ValueType { return Reg::Read<F_ADD>(); }
    static void WriteADD(ValueType value) noexcept { Reg::Write<F_ADD>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40004810;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_LINEN = CortexM3::Field<ValueType, 14, 1>;
    using F_STOP = CortexM3::Field<ValueType, 12, 2>;
    using F_CLKEN = CortexM3::Field<ValueType, 11, 1>;
    using F_CPOL = CortexM3::Field<ValueType, 10, 1>;
    using F_CPHA = CortexM3::Field<ValueType, 9, 1>;
    using F_LBCL = CortexM3::Field<ValueType, 8, 1>;
    using F_LBDIE = CortexM3::Field<ValueType, 6, 1>;
    using F_LBDL = CortexM3::Field<ValueType, 5, 1>;
    using F_ADD = CortexM3::Field<ValueType, 0, 4>;
};

class CR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCTSIE() noexcept -> ValueType { return Reg::Read<F_CTSIE>(); }
    static void WriteCTSIE(ValueType value) noexcept { Reg::Write<F_CTSIE>(value); }
    static auto ReadCTSE() noexcept -> ValueType { return Reg::Read<F_CTSE>(); }
    static void WriteCTSE(ValueType value) noexcept { Reg::Write<F_CTSE>(value); }
    static auto ReadRTSE() noexcept -> ValueType { return Reg::Read<F_RTSE>(); }
    static void WriteRTSE(ValueType value) noexcept { Reg::Write<F_RTSE>(value); }
    static auto ReadDMAT() noexcept -> ValueType { return Reg::Read<F_DMAT>(); }
    static void WriteDMAT(ValueType value) noexcept { Reg::Write<F_DMAT>(value); }
    static auto ReadDMAR() noexcept -> ValueType { return Reg::Read<F_DMAR>(); }
    static void WriteDMAR(ValueType value) noexcept { Reg::Write<F_DMAR>(value); }
    static auto ReadSCEN() noexcept -> ValueType { return Reg::Read<F_SCEN>(); }
    static void WriteSCEN(ValueType value) noexcept { Reg::Write<F_SCEN>(value); }
    static auto ReadNACK() noexcept -> ValueType { return Reg::Read<F_NACK>(); }
    static void WriteNACK(ValueType value) noexcept { Reg::Write<F_NACK>(value); }
    static auto ReadHDSEL() noexcept -> ValueType { return Reg::Read<F_HDSEL>(); }
    static void WriteHDSEL(ValueType value) noexcept { Reg::Write<F_HDSEL>(value); }
    static auto ReadIRLP() noexcept -> ValueType { return Reg::Read<F_IRLP>(); }
    static void WriteIRLP(ValueType value) noexcept { Reg::Write<F_IRLP>(value); }
    static auto ReadIREN() noexcept -> ValueType { return Reg::Read<F_IREN>(); }
    static void WriteIREN(ValueType value) noexcept { Reg::Write<F_IREN>(value); }
    static auto ReadEIE() noexcept -> ValueType { return Reg::Read<F_EIE>(); }
    static void WriteEIE(ValueType value) noexcept { Reg::Write<F_EIE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40004814;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CTSIE = CortexM3::Field<ValueType, 10, 1>;
    using F_CTSE = CortexM3::Field<ValueType, 9, 1>;
    using F_RTSE = CortexM3::Field<ValueType, 8, 1>;
    using F_DMAT = CortexM3::Field<ValueType, 7, 1>;
    using F_DMAR = CortexM3::Field<ValueType, 6, 1>;
    using F_SCEN = CortexM3::Field<ValueType, 5, 1>;
    using F_NACK = CortexM3::Field<ValueType, 4, 1>;
    using F_HDSEL = CortexM3::Field<ValueType, 3, 1>;
    using F_IRLP = CortexM3::Field<ValueType, 2, 1>;
    using F_IREN = CortexM3::Field<ValueType, 1, 1>;
    using F_EIE = CortexM3::Field<ValueType, 0, 1>;
};

class GTPR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadGT() noexcept -> ValueType { return Reg::Read<F_GT>(); }
    static void WriteGT(ValueType value) noexcept { Reg::Write<F_GT>(value); }
    static auto ReadPSC() noexcept -> ValueType { return Reg::Read<F_PSC>(); }
    static void WritePSC(ValueType value) noexcept { Reg::Write<F_PSC>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40004818;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_GT = CortexM3::Field<ValueType, 8, 8>;
    using F_PSC = CortexM3::Field<ValueType, 0, 8>;
};

} // namespace STM32F103::USART3
