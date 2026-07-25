#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::SPI2 {

class CR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadBIDIMODE() noexcept -> ValueType { return Reg::Read<F_BIDIMODE>(); }
    static void WriteBIDIMODE(ValueType value) noexcept { Reg::Write<F_BIDIMODE>(value); }
    static auto ReadBIDIOE() noexcept -> ValueType { return Reg::Read<F_BIDIOE>(); }
    static void WriteBIDIOE(ValueType value) noexcept { Reg::Write<F_BIDIOE>(value); }
    static auto ReadCRCEN() noexcept -> ValueType { return Reg::Read<F_CRCEN>(); }
    static void WriteCRCEN(ValueType value) noexcept { Reg::Write<F_CRCEN>(value); }
    static auto ReadCRCNEXT() noexcept -> ValueType { return Reg::Read<F_CRCNEXT>(); }
    static void WriteCRCNEXT(ValueType value) noexcept { Reg::Write<F_CRCNEXT>(value); }
    static auto ReadDFF() noexcept -> ValueType { return Reg::Read<F_DFF>(); }
    static void WriteDFF(ValueType value) noexcept { Reg::Write<F_DFF>(value); }
    static auto ReadRXONLY() noexcept -> ValueType { return Reg::Read<F_RXONLY>(); }
    static void WriteRXONLY(ValueType value) noexcept { Reg::Write<F_RXONLY>(value); }
    static auto ReadSSM() noexcept -> ValueType { return Reg::Read<F_SSM>(); }
    static void WriteSSM(ValueType value) noexcept { Reg::Write<F_SSM>(value); }
    static auto ReadSSI() noexcept -> ValueType { return Reg::Read<F_SSI>(); }
    static void WriteSSI(ValueType value) noexcept { Reg::Write<F_SSI>(value); }
    static auto ReadLSBFIRST() noexcept -> ValueType { return Reg::Read<F_LSBFIRST>(); }
    static void WriteLSBFIRST(ValueType value) noexcept { Reg::Write<F_LSBFIRST>(value); }
    static auto ReadSPE() noexcept -> ValueType { return Reg::Read<F_SPE>(); }
    static void WriteSPE(ValueType value) noexcept { Reg::Write<F_SPE>(value); }
    static auto ReadBR() noexcept -> ValueType { return Reg::Read<F_BR>(); }
    static void WriteBR(ValueType value) noexcept { Reg::Write<F_BR>(value); }
    static auto ReadMSTR() noexcept -> ValueType { return Reg::Read<F_MSTR>(); }
    static void WriteMSTR(ValueType value) noexcept { Reg::Write<F_MSTR>(value); }
    static auto ReadCPOL() noexcept -> ValueType { return Reg::Read<F_CPOL>(); }
    static void WriteCPOL(ValueType value) noexcept { Reg::Write<F_CPOL>(value); }
    static auto ReadCPHA() noexcept -> ValueType { return Reg::Read<F_CPHA>(); }
    static void WriteCPHA(ValueType value) noexcept { Reg::Write<F_CPHA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40003800;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_BIDIMODE = CortexM3::Field<ValueType, 15, 1>;
    using F_BIDIOE = CortexM3::Field<ValueType, 14, 1>;
    using F_CRCEN = CortexM3::Field<ValueType, 13, 1>;
    using F_CRCNEXT = CortexM3::Field<ValueType, 12, 1>;
    using F_DFF = CortexM3::Field<ValueType, 11, 1>;
    using F_RXONLY = CortexM3::Field<ValueType, 10, 1>;
    using F_SSM = CortexM3::Field<ValueType, 9, 1>;
    using F_SSI = CortexM3::Field<ValueType, 8, 1>;
    using F_LSBFIRST = CortexM3::Field<ValueType, 7, 1>;
    using F_SPE = CortexM3::Field<ValueType, 6, 1>;
    using F_BR = CortexM3::Field<ValueType, 3, 3>;
    using F_MSTR = CortexM3::Field<ValueType, 2, 1>;
    using F_CPOL = CortexM3::Field<ValueType, 1, 1>;
    using F_CPHA = CortexM3::Field<ValueType, 0, 1>;
};

class CR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTXEIE() noexcept -> ValueType { return Reg::Read<F_TXEIE>(); }
    static void WriteTXEIE(ValueType value) noexcept { Reg::Write<F_TXEIE>(value); }
    static auto ReadRXNEIE() noexcept -> ValueType { return Reg::Read<F_RXNEIE>(); }
    static void WriteRXNEIE(ValueType value) noexcept { Reg::Write<F_RXNEIE>(value); }
    static auto ReadERRIE() noexcept -> ValueType { return Reg::Read<F_ERRIE>(); }
    static void WriteERRIE(ValueType value) noexcept { Reg::Write<F_ERRIE>(value); }
    static auto ReadSSOE() noexcept -> ValueType { return Reg::Read<F_SSOE>(); }
    static void WriteSSOE(ValueType value) noexcept { Reg::Write<F_SSOE>(value); }
    static auto ReadTXDMAEN() noexcept -> ValueType { return Reg::Read<F_TXDMAEN>(); }
    static void WriteTXDMAEN(ValueType value) noexcept { Reg::Write<F_TXDMAEN>(value); }
    static auto ReadRXDMAEN() noexcept -> ValueType { return Reg::Read<F_RXDMAEN>(); }
    static void WriteRXDMAEN(ValueType value) noexcept { Reg::Write<F_RXDMAEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40003804;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TXEIE = CortexM3::Field<ValueType, 7, 1>;
    using F_RXNEIE = CortexM3::Field<ValueType, 6, 1>;
    using F_ERRIE = CortexM3::Field<ValueType, 5, 1>;
    using F_SSOE = CortexM3::Field<ValueType, 2, 1>;
    using F_TXDMAEN = CortexM3::Field<ValueType, 1, 1>;
    using F_RXDMAEN = CortexM3::Field<ValueType, 0, 1>;
};

class SR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000002;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadBSY() noexcept -> ValueType { return Reg::Read<F_BSY>(); }
    static auto ReadOVR() noexcept -> ValueType { return Reg::Read<F_OVR>(); }
    static auto ReadMODF() noexcept -> ValueType { return Reg::Read<F_MODF>(); }
    static auto ReadCRCERR() noexcept -> ValueType { return Reg::Read<F_CRCERR>(); }
    static void WriteCRCERR(ValueType value) noexcept { Reg::Write<F_CRCERR>(value); }
    static auto ReadUDR() noexcept -> ValueType { return Reg::Read<F_UDR>(); }
    static auto ReadCHSIDE() noexcept -> ValueType { return Reg::Read<F_CHSIDE>(); }
    static auto ReadTXE() noexcept -> ValueType { return Reg::Read<F_TXE>(); }
    static auto ReadRXNE() noexcept -> ValueType { return Reg::Read<F_RXNE>(); }

private:
    static constexpr std::uintptr_t Address = 0x40003808;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_BSY = CortexM3::Field<ValueType, 7, 1>;
    using F_OVR = CortexM3::Field<ValueType, 6, 1>;
    using F_MODF = CortexM3::Field<ValueType, 5, 1>;
    using F_CRCERR = CortexM3::Field<ValueType, 4, 1>;
    using F_UDR = CortexM3::Field<ValueType, 3, 1>;
    using F_CHSIDE = CortexM3::Field<ValueType, 2, 1>;
    using F_TXE = CortexM3::Field<ValueType, 1, 1>;
    using F_RXNE = CortexM3::Field<ValueType, 0, 1>;
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
    static constexpr std::uintptr_t Address = 0x4000380c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DR = CortexM3::Field<ValueType, 0, 16>;
};

class CRCPR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000007;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCRCPOLY() noexcept -> ValueType { return Reg::Read<F_CRCPOLY>(); }
    static void WriteCRCPOLY(ValueType value) noexcept { Reg::Write<F_CRCPOLY>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40003810;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CRCPOLY = CortexM3::Field<ValueType, 0, 16>;
};

class RXCRCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadRxCRC() noexcept -> ValueType { return Reg::Read<F_RxCRC>(); }

private:
    static constexpr std::uintptr_t Address = 0x40003814;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_RxCRC = CortexM3::Field<ValueType, 0, 16>;
};

class TXCRCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadTxCRC() noexcept -> ValueType { return Reg::Read<F_TxCRC>(); }

private:
    static constexpr std::uintptr_t Address = 0x40003818;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TxCRC = CortexM3::Field<ValueType, 0, 16>;
};

class I2SCFGR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadI2SMOD() noexcept -> ValueType { return Reg::Read<F_I2SMOD>(); }
    static void WriteI2SMOD(ValueType value) noexcept { Reg::Write<F_I2SMOD>(value); }
    static auto ReadI2SE() noexcept -> ValueType { return Reg::Read<F_I2SE>(); }
    static void WriteI2SE(ValueType value) noexcept { Reg::Write<F_I2SE>(value); }
    static auto ReadI2SCFG() noexcept -> ValueType { return Reg::Read<F_I2SCFG>(); }
    static void WriteI2SCFG(ValueType value) noexcept { Reg::Write<F_I2SCFG>(value); }
    static auto ReadPCMSYNC() noexcept -> ValueType { return Reg::Read<F_PCMSYNC>(); }
    static void WritePCMSYNC(ValueType value) noexcept { Reg::Write<F_PCMSYNC>(value); }
    static auto ReadI2SSTD() noexcept -> ValueType { return Reg::Read<F_I2SSTD>(); }
    static void WriteI2SSTD(ValueType value) noexcept { Reg::Write<F_I2SSTD>(value); }
    static auto ReadCKPOL() noexcept -> ValueType { return Reg::Read<F_CKPOL>(); }
    static void WriteCKPOL(ValueType value) noexcept { Reg::Write<F_CKPOL>(value); }
    static auto ReadDATLEN() noexcept -> ValueType { return Reg::Read<F_DATLEN>(); }
    static void WriteDATLEN(ValueType value) noexcept { Reg::Write<F_DATLEN>(value); }
    static auto ReadCHLEN() noexcept -> ValueType { return Reg::Read<F_CHLEN>(); }
    static void WriteCHLEN(ValueType value) noexcept { Reg::Write<F_CHLEN>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000381c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_I2SMOD = CortexM3::Field<ValueType, 11, 1>;
    using F_I2SE = CortexM3::Field<ValueType, 10, 1>;
    using F_I2SCFG = CortexM3::Field<ValueType, 8, 2>;
    using F_PCMSYNC = CortexM3::Field<ValueType, 7, 1>;
    using F_I2SSTD = CortexM3::Field<ValueType, 4, 2>;
    using F_CKPOL = CortexM3::Field<ValueType, 3, 1>;
    using F_DATLEN = CortexM3::Field<ValueType, 1, 2>;
    using F_CHLEN = CortexM3::Field<ValueType, 0, 1>;
};

class I2SPR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0000000A;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadMCKOE() noexcept -> ValueType { return Reg::Read<F_MCKOE>(); }
    static void WriteMCKOE(ValueType value) noexcept { Reg::Write<F_MCKOE>(value); }
    static auto ReadODD() noexcept -> ValueType { return Reg::Read<F_ODD>(); }
    static void WriteODD(ValueType value) noexcept { Reg::Write<F_ODD>(value); }
    static auto ReadI2SDIV() noexcept -> ValueType { return Reg::Read<F_I2SDIV>(); }
    static void WriteI2SDIV(ValueType value) noexcept { Reg::Write<F_I2SDIV>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40003820;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_MCKOE = CortexM3::Field<ValueType, 9, 1>;
    using F_ODD = CortexM3::Field<ValueType, 8, 1>;
    using F_I2SDIV = CortexM3::Field<ValueType, 0, 8>;
};

} // namespace STM32F103::SPI2
