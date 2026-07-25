#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::USB {

class EP0R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEA() noexcept -> ValueType { return Reg::Read<F_EA>(); }
    static void WriteEA(ValueType value) noexcept { Reg::Write<F_EA>(value); }
    static auto ReadSTAT_TX() noexcept -> ValueType { return Reg::Read<F_STAT_TX>(); }
    static void WriteSTAT_TX(ValueType value) noexcept { Reg::Write<F_STAT_TX>(value); }
    static auto ReadDTOG_TX() noexcept -> ValueType { return Reg::Read<F_DTOG_TX>(); }
    static void WriteDTOG_TX(ValueType value) noexcept { Reg::Write<F_DTOG_TX>(value); }
    static auto ReadCTR_TX() noexcept -> ValueType { return Reg::Read<F_CTR_TX>(); }
    static void WriteCTR_TX(ValueType value) noexcept { Reg::Write<F_CTR_TX>(value); }
    static auto ReadEP_KIND() noexcept -> ValueType { return Reg::Read<F_EP_KIND>(); }
    static void WriteEP_KIND(ValueType value) noexcept { Reg::Write<F_EP_KIND>(value); }
    static auto ReadEP_TYPE() noexcept -> ValueType { return Reg::Read<F_EP_TYPE>(); }
    static void WriteEP_TYPE(ValueType value) noexcept { Reg::Write<F_EP_TYPE>(value); }
    static auto ReadSETUP() noexcept -> ValueType { return Reg::Read<F_SETUP>(); }
    static void WriteSETUP(ValueType value) noexcept { Reg::Write<F_SETUP>(value); }
    static auto ReadSTAT_RX() noexcept -> ValueType { return Reg::Read<F_STAT_RX>(); }
    static void WriteSTAT_RX(ValueType value) noexcept { Reg::Write<F_STAT_RX>(value); }
    static auto ReadDTOG_RX() noexcept -> ValueType { return Reg::Read<F_DTOG_RX>(); }
    static void WriteDTOG_RX(ValueType value) noexcept { Reg::Write<F_DTOG_RX>(value); }
    static auto ReadCTR_RX() noexcept -> ValueType { return Reg::Read<F_CTR_RX>(); }
    static void WriteCTR_RX(ValueType value) noexcept { Reg::Write<F_CTR_RX>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c00;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EA = CortexM3::Field<ValueType, 0, 4>;
    using F_STAT_TX = CortexM3::Field<ValueType, 4, 2>;
    using F_DTOG_TX = CortexM3::Field<ValueType, 6, 1>;
    using F_CTR_TX = CortexM3::Field<ValueType, 7, 1>;
    using F_EP_KIND = CortexM3::Field<ValueType, 8, 1>;
    using F_EP_TYPE = CortexM3::Field<ValueType, 9, 2>;
    using F_SETUP = CortexM3::Field<ValueType, 11, 1>;
    using F_STAT_RX = CortexM3::Field<ValueType, 12, 2>;
    using F_DTOG_RX = CortexM3::Field<ValueType, 14, 1>;
    using F_CTR_RX = CortexM3::Field<ValueType, 15, 1>;
};

class EP1R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEA() noexcept -> ValueType { return Reg::Read<F_EA>(); }
    static void WriteEA(ValueType value) noexcept { Reg::Write<F_EA>(value); }
    static auto ReadSTAT_TX() noexcept -> ValueType { return Reg::Read<F_STAT_TX>(); }
    static void WriteSTAT_TX(ValueType value) noexcept { Reg::Write<F_STAT_TX>(value); }
    static auto ReadDTOG_TX() noexcept -> ValueType { return Reg::Read<F_DTOG_TX>(); }
    static void WriteDTOG_TX(ValueType value) noexcept { Reg::Write<F_DTOG_TX>(value); }
    static auto ReadCTR_TX() noexcept -> ValueType { return Reg::Read<F_CTR_TX>(); }
    static void WriteCTR_TX(ValueType value) noexcept { Reg::Write<F_CTR_TX>(value); }
    static auto ReadEP_KIND() noexcept -> ValueType { return Reg::Read<F_EP_KIND>(); }
    static void WriteEP_KIND(ValueType value) noexcept { Reg::Write<F_EP_KIND>(value); }
    static auto ReadEP_TYPE() noexcept -> ValueType { return Reg::Read<F_EP_TYPE>(); }
    static void WriteEP_TYPE(ValueType value) noexcept { Reg::Write<F_EP_TYPE>(value); }
    static auto ReadSETUP() noexcept -> ValueType { return Reg::Read<F_SETUP>(); }
    static void WriteSETUP(ValueType value) noexcept { Reg::Write<F_SETUP>(value); }
    static auto ReadSTAT_RX() noexcept -> ValueType { return Reg::Read<F_STAT_RX>(); }
    static void WriteSTAT_RX(ValueType value) noexcept { Reg::Write<F_STAT_RX>(value); }
    static auto ReadDTOG_RX() noexcept -> ValueType { return Reg::Read<F_DTOG_RX>(); }
    static void WriteDTOG_RX(ValueType value) noexcept { Reg::Write<F_DTOG_RX>(value); }
    static auto ReadCTR_RX() noexcept -> ValueType { return Reg::Read<F_CTR_RX>(); }
    static void WriteCTR_RX(ValueType value) noexcept { Reg::Write<F_CTR_RX>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c04;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EA = CortexM3::Field<ValueType, 0, 4>;
    using F_STAT_TX = CortexM3::Field<ValueType, 4, 2>;
    using F_DTOG_TX = CortexM3::Field<ValueType, 6, 1>;
    using F_CTR_TX = CortexM3::Field<ValueType, 7, 1>;
    using F_EP_KIND = CortexM3::Field<ValueType, 8, 1>;
    using F_EP_TYPE = CortexM3::Field<ValueType, 9, 2>;
    using F_SETUP = CortexM3::Field<ValueType, 11, 1>;
    using F_STAT_RX = CortexM3::Field<ValueType, 12, 2>;
    using F_DTOG_RX = CortexM3::Field<ValueType, 14, 1>;
    using F_CTR_RX = CortexM3::Field<ValueType, 15, 1>;
};

class EP2R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEA() noexcept -> ValueType { return Reg::Read<F_EA>(); }
    static void WriteEA(ValueType value) noexcept { Reg::Write<F_EA>(value); }
    static auto ReadSTAT_TX() noexcept -> ValueType { return Reg::Read<F_STAT_TX>(); }
    static void WriteSTAT_TX(ValueType value) noexcept { Reg::Write<F_STAT_TX>(value); }
    static auto ReadDTOG_TX() noexcept -> ValueType { return Reg::Read<F_DTOG_TX>(); }
    static void WriteDTOG_TX(ValueType value) noexcept { Reg::Write<F_DTOG_TX>(value); }
    static auto ReadCTR_TX() noexcept -> ValueType { return Reg::Read<F_CTR_TX>(); }
    static void WriteCTR_TX(ValueType value) noexcept { Reg::Write<F_CTR_TX>(value); }
    static auto ReadEP_KIND() noexcept -> ValueType { return Reg::Read<F_EP_KIND>(); }
    static void WriteEP_KIND(ValueType value) noexcept { Reg::Write<F_EP_KIND>(value); }
    static auto ReadEP_TYPE() noexcept -> ValueType { return Reg::Read<F_EP_TYPE>(); }
    static void WriteEP_TYPE(ValueType value) noexcept { Reg::Write<F_EP_TYPE>(value); }
    static auto ReadSETUP() noexcept -> ValueType { return Reg::Read<F_SETUP>(); }
    static void WriteSETUP(ValueType value) noexcept { Reg::Write<F_SETUP>(value); }
    static auto ReadSTAT_RX() noexcept -> ValueType { return Reg::Read<F_STAT_RX>(); }
    static void WriteSTAT_RX(ValueType value) noexcept { Reg::Write<F_STAT_RX>(value); }
    static auto ReadDTOG_RX() noexcept -> ValueType { return Reg::Read<F_DTOG_RX>(); }
    static void WriteDTOG_RX(ValueType value) noexcept { Reg::Write<F_DTOG_RX>(value); }
    static auto ReadCTR_RX() noexcept -> ValueType { return Reg::Read<F_CTR_RX>(); }
    static void WriteCTR_RX(ValueType value) noexcept { Reg::Write<F_CTR_RX>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c08;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EA = CortexM3::Field<ValueType, 0, 4>;
    using F_STAT_TX = CortexM3::Field<ValueType, 4, 2>;
    using F_DTOG_TX = CortexM3::Field<ValueType, 6, 1>;
    using F_CTR_TX = CortexM3::Field<ValueType, 7, 1>;
    using F_EP_KIND = CortexM3::Field<ValueType, 8, 1>;
    using F_EP_TYPE = CortexM3::Field<ValueType, 9, 2>;
    using F_SETUP = CortexM3::Field<ValueType, 11, 1>;
    using F_STAT_RX = CortexM3::Field<ValueType, 12, 2>;
    using F_DTOG_RX = CortexM3::Field<ValueType, 14, 1>;
    using F_CTR_RX = CortexM3::Field<ValueType, 15, 1>;
};

class EP3R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEA() noexcept -> ValueType { return Reg::Read<F_EA>(); }
    static void WriteEA(ValueType value) noexcept { Reg::Write<F_EA>(value); }
    static auto ReadSTAT_TX() noexcept -> ValueType { return Reg::Read<F_STAT_TX>(); }
    static void WriteSTAT_TX(ValueType value) noexcept { Reg::Write<F_STAT_TX>(value); }
    static auto ReadDTOG_TX() noexcept -> ValueType { return Reg::Read<F_DTOG_TX>(); }
    static void WriteDTOG_TX(ValueType value) noexcept { Reg::Write<F_DTOG_TX>(value); }
    static auto ReadCTR_TX() noexcept -> ValueType { return Reg::Read<F_CTR_TX>(); }
    static void WriteCTR_TX(ValueType value) noexcept { Reg::Write<F_CTR_TX>(value); }
    static auto ReadEP_KIND() noexcept -> ValueType { return Reg::Read<F_EP_KIND>(); }
    static void WriteEP_KIND(ValueType value) noexcept { Reg::Write<F_EP_KIND>(value); }
    static auto ReadEP_TYPE() noexcept -> ValueType { return Reg::Read<F_EP_TYPE>(); }
    static void WriteEP_TYPE(ValueType value) noexcept { Reg::Write<F_EP_TYPE>(value); }
    static auto ReadSETUP() noexcept -> ValueType { return Reg::Read<F_SETUP>(); }
    static void WriteSETUP(ValueType value) noexcept { Reg::Write<F_SETUP>(value); }
    static auto ReadSTAT_RX() noexcept -> ValueType { return Reg::Read<F_STAT_RX>(); }
    static void WriteSTAT_RX(ValueType value) noexcept { Reg::Write<F_STAT_RX>(value); }
    static auto ReadDTOG_RX() noexcept -> ValueType { return Reg::Read<F_DTOG_RX>(); }
    static void WriteDTOG_RX(ValueType value) noexcept { Reg::Write<F_DTOG_RX>(value); }
    static auto ReadCTR_RX() noexcept -> ValueType { return Reg::Read<F_CTR_RX>(); }
    static void WriteCTR_RX(ValueType value) noexcept { Reg::Write<F_CTR_RX>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c0c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EA = CortexM3::Field<ValueType, 0, 4>;
    using F_STAT_TX = CortexM3::Field<ValueType, 4, 2>;
    using F_DTOG_TX = CortexM3::Field<ValueType, 6, 1>;
    using F_CTR_TX = CortexM3::Field<ValueType, 7, 1>;
    using F_EP_KIND = CortexM3::Field<ValueType, 8, 1>;
    using F_EP_TYPE = CortexM3::Field<ValueType, 9, 2>;
    using F_SETUP = CortexM3::Field<ValueType, 11, 1>;
    using F_STAT_RX = CortexM3::Field<ValueType, 12, 2>;
    using F_DTOG_RX = CortexM3::Field<ValueType, 14, 1>;
    using F_CTR_RX = CortexM3::Field<ValueType, 15, 1>;
};

class EP4R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEA() noexcept -> ValueType { return Reg::Read<F_EA>(); }
    static void WriteEA(ValueType value) noexcept { Reg::Write<F_EA>(value); }
    static auto ReadSTAT_TX() noexcept -> ValueType { return Reg::Read<F_STAT_TX>(); }
    static void WriteSTAT_TX(ValueType value) noexcept { Reg::Write<F_STAT_TX>(value); }
    static auto ReadDTOG_TX() noexcept -> ValueType { return Reg::Read<F_DTOG_TX>(); }
    static void WriteDTOG_TX(ValueType value) noexcept { Reg::Write<F_DTOG_TX>(value); }
    static auto ReadCTR_TX() noexcept -> ValueType { return Reg::Read<F_CTR_TX>(); }
    static void WriteCTR_TX(ValueType value) noexcept { Reg::Write<F_CTR_TX>(value); }
    static auto ReadEP_KIND() noexcept -> ValueType { return Reg::Read<F_EP_KIND>(); }
    static void WriteEP_KIND(ValueType value) noexcept { Reg::Write<F_EP_KIND>(value); }
    static auto ReadEP_TYPE() noexcept -> ValueType { return Reg::Read<F_EP_TYPE>(); }
    static void WriteEP_TYPE(ValueType value) noexcept { Reg::Write<F_EP_TYPE>(value); }
    static auto ReadSETUP() noexcept -> ValueType { return Reg::Read<F_SETUP>(); }
    static void WriteSETUP(ValueType value) noexcept { Reg::Write<F_SETUP>(value); }
    static auto ReadSTAT_RX() noexcept -> ValueType { return Reg::Read<F_STAT_RX>(); }
    static void WriteSTAT_RX(ValueType value) noexcept { Reg::Write<F_STAT_RX>(value); }
    static auto ReadDTOG_RX() noexcept -> ValueType { return Reg::Read<F_DTOG_RX>(); }
    static void WriteDTOG_RX(ValueType value) noexcept { Reg::Write<F_DTOG_RX>(value); }
    static auto ReadCTR_RX() noexcept -> ValueType { return Reg::Read<F_CTR_RX>(); }
    static void WriteCTR_RX(ValueType value) noexcept { Reg::Write<F_CTR_RX>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c10;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EA = CortexM3::Field<ValueType, 0, 4>;
    using F_STAT_TX = CortexM3::Field<ValueType, 4, 2>;
    using F_DTOG_TX = CortexM3::Field<ValueType, 6, 1>;
    using F_CTR_TX = CortexM3::Field<ValueType, 7, 1>;
    using F_EP_KIND = CortexM3::Field<ValueType, 8, 1>;
    using F_EP_TYPE = CortexM3::Field<ValueType, 9, 2>;
    using F_SETUP = CortexM3::Field<ValueType, 11, 1>;
    using F_STAT_RX = CortexM3::Field<ValueType, 12, 2>;
    using F_DTOG_RX = CortexM3::Field<ValueType, 14, 1>;
    using F_CTR_RX = CortexM3::Field<ValueType, 15, 1>;
};

class EP5R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEA() noexcept -> ValueType { return Reg::Read<F_EA>(); }
    static void WriteEA(ValueType value) noexcept { Reg::Write<F_EA>(value); }
    static auto ReadSTAT_TX() noexcept -> ValueType { return Reg::Read<F_STAT_TX>(); }
    static void WriteSTAT_TX(ValueType value) noexcept { Reg::Write<F_STAT_TX>(value); }
    static auto ReadDTOG_TX() noexcept -> ValueType { return Reg::Read<F_DTOG_TX>(); }
    static void WriteDTOG_TX(ValueType value) noexcept { Reg::Write<F_DTOG_TX>(value); }
    static auto ReadCTR_TX() noexcept -> ValueType { return Reg::Read<F_CTR_TX>(); }
    static void WriteCTR_TX(ValueType value) noexcept { Reg::Write<F_CTR_TX>(value); }
    static auto ReadEP_KIND() noexcept -> ValueType { return Reg::Read<F_EP_KIND>(); }
    static void WriteEP_KIND(ValueType value) noexcept { Reg::Write<F_EP_KIND>(value); }
    static auto ReadEP_TYPE() noexcept -> ValueType { return Reg::Read<F_EP_TYPE>(); }
    static void WriteEP_TYPE(ValueType value) noexcept { Reg::Write<F_EP_TYPE>(value); }
    static auto ReadSETUP() noexcept -> ValueType { return Reg::Read<F_SETUP>(); }
    static void WriteSETUP(ValueType value) noexcept { Reg::Write<F_SETUP>(value); }
    static auto ReadSTAT_RX() noexcept -> ValueType { return Reg::Read<F_STAT_RX>(); }
    static void WriteSTAT_RX(ValueType value) noexcept { Reg::Write<F_STAT_RX>(value); }
    static auto ReadDTOG_RX() noexcept -> ValueType { return Reg::Read<F_DTOG_RX>(); }
    static void WriteDTOG_RX(ValueType value) noexcept { Reg::Write<F_DTOG_RX>(value); }
    static auto ReadCTR_RX() noexcept -> ValueType { return Reg::Read<F_CTR_RX>(); }
    static void WriteCTR_RX(ValueType value) noexcept { Reg::Write<F_CTR_RX>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c14;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EA = CortexM3::Field<ValueType, 0, 4>;
    using F_STAT_TX = CortexM3::Field<ValueType, 4, 2>;
    using F_DTOG_TX = CortexM3::Field<ValueType, 6, 1>;
    using F_CTR_TX = CortexM3::Field<ValueType, 7, 1>;
    using F_EP_KIND = CortexM3::Field<ValueType, 8, 1>;
    using F_EP_TYPE = CortexM3::Field<ValueType, 9, 2>;
    using F_SETUP = CortexM3::Field<ValueType, 11, 1>;
    using F_STAT_RX = CortexM3::Field<ValueType, 12, 2>;
    using F_DTOG_RX = CortexM3::Field<ValueType, 14, 1>;
    using F_CTR_RX = CortexM3::Field<ValueType, 15, 1>;
};

class EP6R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEA() noexcept -> ValueType { return Reg::Read<F_EA>(); }
    static void WriteEA(ValueType value) noexcept { Reg::Write<F_EA>(value); }
    static auto ReadSTAT_TX() noexcept -> ValueType { return Reg::Read<F_STAT_TX>(); }
    static void WriteSTAT_TX(ValueType value) noexcept { Reg::Write<F_STAT_TX>(value); }
    static auto ReadDTOG_TX() noexcept -> ValueType { return Reg::Read<F_DTOG_TX>(); }
    static void WriteDTOG_TX(ValueType value) noexcept { Reg::Write<F_DTOG_TX>(value); }
    static auto ReadCTR_TX() noexcept -> ValueType { return Reg::Read<F_CTR_TX>(); }
    static void WriteCTR_TX(ValueType value) noexcept { Reg::Write<F_CTR_TX>(value); }
    static auto ReadEP_KIND() noexcept -> ValueType { return Reg::Read<F_EP_KIND>(); }
    static void WriteEP_KIND(ValueType value) noexcept { Reg::Write<F_EP_KIND>(value); }
    static auto ReadEP_TYPE() noexcept -> ValueType { return Reg::Read<F_EP_TYPE>(); }
    static void WriteEP_TYPE(ValueType value) noexcept { Reg::Write<F_EP_TYPE>(value); }
    static auto ReadSETUP() noexcept -> ValueType { return Reg::Read<F_SETUP>(); }
    static void WriteSETUP(ValueType value) noexcept { Reg::Write<F_SETUP>(value); }
    static auto ReadSTAT_RX() noexcept -> ValueType { return Reg::Read<F_STAT_RX>(); }
    static void WriteSTAT_RX(ValueType value) noexcept { Reg::Write<F_STAT_RX>(value); }
    static auto ReadDTOG_RX() noexcept -> ValueType { return Reg::Read<F_DTOG_RX>(); }
    static void WriteDTOG_RX(ValueType value) noexcept { Reg::Write<F_DTOG_RX>(value); }
    static auto ReadCTR_RX() noexcept -> ValueType { return Reg::Read<F_CTR_RX>(); }
    static void WriteCTR_RX(ValueType value) noexcept { Reg::Write<F_CTR_RX>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c18;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EA = CortexM3::Field<ValueType, 0, 4>;
    using F_STAT_TX = CortexM3::Field<ValueType, 4, 2>;
    using F_DTOG_TX = CortexM3::Field<ValueType, 6, 1>;
    using F_CTR_TX = CortexM3::Field<ValueType, 7, 1>;
    using F_EP_KIND = CortexM3::Field<ValueType, 8, 1>;
    using F_EP_TYPE = CortexM3::Field<ValueType, 9, 2>;
    using F_SETUP = CortexM3::Field<ValueType, 11, 1>;
    using F_STAT_RX = CortexM3::Field<ValueType, 12, 2>;
    using F_DTOG_RX = CortexM3::Field<ValueType, 14, 1>;
    using F_CTR_RX = CortexM3::Field<ValueType, 15, 1>;
};

class EP7R {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEA() noexcept -> ValueType { return Reg::Read<F_EA>(); }
    static void WriteEA(ValueType value) noexcept { Reg::Write<F_EA>(value); }
    static auto ReadSTAT_TX() noexcept -> ValueType { return Reg::Read<F_STAT_TX>(); }
    static void WriteSTAT_TX(ValueType value) noexcept { Reg::Write<F_STAT_TX>(value); }
    static auto ReadDTOG_TX() noexcept -> ValueType { return Reg::Read<F_DTOG_TX>(); }
    static void WriteDTOG_TX(ValueType value) noexcept { Reg::Write<F_DTOG_TX>(value); }
    static auto ReadCTR_TX() noexcept -> ValueType { return Reg::Read<F_CTR_TX>(); }
    static void WriteCTR_TX(ValueType value) noexcept { Reg::Write<F_CTR_TX>(value); }
    static auto ReadEP_KIND() noexcept -> ValueType { return Reg::Read<F_EP_KIND>(); }
    static void WriteEP_KIND(ValueType value) noexcept { Reg::Write<F_EP_KIND>(value); }
    static auto ReadEP_TYPE() noexcept -> ValueType { return Reg::Read<F_EP_TYPE>(); }
    static void WriteEP_TYPE(ValueType value) noexcept { Reg::Write<F_EP_TYPE>(value); }
    static auto ReadSETUP() noexcept -> ValueType { return Reg::Read<F_SETUP>(); }
    static void WriteSETUP(ValueType value) noexcept { Reg::Write<F_SETUP>(value); }
    static auto ReadSTAT_RX() noexcept -> ValueType { return Reg::Read<F_STAT_RX>(); }
    static void WriteSTAT_RX(ValueType value) noexcept { Reg::Write<F_STAT_RX>(value); }
    static auto ReadDTOG_RX() noexcept -> ValueType { return Reg::Read<F_DTOG_RX>(); }
    static void WriteDTOG_RX(ValueType value) noexcept { Reg::Write<F_DTOG_RX>(value); }
    static auto ReadCTR_RX() noexcept -> ValueType { return Reg::Read<F_CTR_RX>(); }
    static void WriteCTR_RX(ValueType value) noexcept { Reg::Write<F_CTR_RX>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c1c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EA = CortexM3::Field<ValueType, 0, 4>;
    using F_STAT_TX = CortexM3::Field<ValueType, 4, 2>;
    using F_DTOG_TX = CortexM3::Field<ValueType, 6, 1>;
    using F_CTR_TX = CortexM3::Field<ValueType, 7, 1>;
    using F_EP_KIND = CortexM3::Field<ValueType, 8, 1>;
    using F_EP_TYPE = CortexM3::Field<ValueType, 9, 2>;
    using F_SETUP = CortexM3::Field<ValueType, 11, 1>;
    using F_STAT_RX = CortexM3::Field<ValueType, 12, 2>;
    using F_DTOG_RX = CortexM3::Field<ValueType, 14, 1>;
    using F_CTR_RX = CortexM3::Field<ValueType, 15, 1>;
};

class CNTR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000003;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadFRES() noexcept -> ValueType { return Reg::Read<F_FRES>(); }
    static void WriteFRES(ValueType value) noexcept { Reg::Write<F_FRES>(value); }
    static auto ReadPDWN() noexcept -> ValueType { return Reg::Read<F_PDWN>(); }
    static void WritePDWN(ValueType value) noexcept { Reg::Write<F_PDWN>(value); }
    static auto ReadLPMODE() noexcept -> ValueType { return Reg::Read<F_LPMODE>(); }
    static void WriteLPMODE(ValueType value) noexcept { Reg::Write<F_LPMODE>(value); }
    static auto ReadFSUSP() noexcept -> ValueType { return Reg::Read<F_FSUSP>(); }
    static void WriteFSUSP(ValueType value) noexcept { Reg::Write<F_FSUSP>(value); }
    static auto ReadRESUME() noexcept -> ValueType { return Reg::Read<F_RESUME>(); }
    static void WriteRESUME(ValueType value) noexcept { Reg::Write<F_RESUME>(value); }
    static auto ReadESOFM() noexcept -> ValueType { return Reg::Read<F_ESOFM>(); }
    static void WriteESOFM(ValueType value) noexcept { Reg::Write<F_ESOFM>(value); }
    static auto ReadSOFM() noexcept -> ValueType { return Reg::Read<F_SOFM>(); }
    static void WriteSOFM(ValueType value) noexcept { Reg::Write<F_SOFM>(value); }
    static auto ReadRESETM() noexcept -> ValueType { return Reg::Read<F_RESETM>(); }
    static void WriteRESETM(ValueType value) noexcept { Reg::Write<F_RESETM>(value); }
    static auto ReadSUSPM() noexcept -> ValueType { return Reg::Read<F_SUSPM>(); }
    static void WriteSUSPM(ValueType value) noexcept { Reg::Write<F_SUSPM>(value); }
    static auto ReadWKUPM() noexcept -> ValueType { return Reg::Read<F_WKUPM>(); }
    static void WriteWKUPM(ValueType value) noexcept { Reg::Write<F_WKUPM>(value); }
    static auto ReadERRM() noexcept -> ValueType { return Reg::Read<F_ERRM>(); }
    static void WriteERRM(ValueType value) noexcept { Reg::Write<F_ERRM>(value); }
    static auto ReadPMAOVRM() noexcept -> ValueType { return Reg::Read<F_PMAOVRM>(); }
    static void WritePMAOVRM(ValueType value) noexcept { Reg::Write<F_PMAOVRM>(value); }
    static auto ReadCTRM() noexcept -> ValueType { return Reg::Read<F_CTRM>(); }
    static void WriteCTRM(ValueType value) noexcept { Reg::Write<F_CTRM>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c40;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FRES = CortexM3::Field<ValueType, 0, 1>;
    using F_PDWN = CortexM3::Field<ValueType, 1, 1>;
    using F_LPMODE = CortexM3::Field<ValueType, 2, 1>;
    using F_FSUSP = CortexM3::Field<ValueType, 3, 1>;
    using F_RESUME = CortexM3::Field<ValueType, 4, 1>;
    using F_ESOFM = CortexM3::Field<ValueType, 8, 1>;
    using F_SOFM = CortexM3::Field<ValueType, 9, 1>;
    using F_RESETM = CortexM3::Field<ValueType, 10, 1>;
    using F_SUSPM = CortexM3::Field<ValueType, 11, 1>;
    using F_WKUPM = CortexM3::Field<ValueType, 12, 1>;
    using F_ERRM = CortexM3::Field<ValueType, 13, 1>;
    using F_PMAOVRM = CortexM3::Field<ValueType, 14, 1>;
    using F_CTRM = CortexM3::Field<ValueType, 15, 1>;
};

class ISTR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEP_ID() noexcept -> ValueType { return Reg::Read<F_EP_ID>(); }
    static void WriteEP_ID(ValueType value) noexcept { Reg::Write<F_EP_ID>(value); }
    static auto ReadDIR() noexcept -> ValueType { return Reg::Read<F_DIR>(); }
    static void WriteDIR(ValueType value) noexcept { Reg::Write<F_DIR>(value); }
    static auto ReadESOF() noexcept -> ValueType { return Reg::Read<F_ESOF>(); }
    static void WriteESOF(ValueType value) noexcept { Reg::Write<F_ESOF>(value); }
    static auto ReadSOF() noexcept -> ValueType { return Reg::Read<F_SOF>(); }
    static void WriteSOF(ValueType value) noexcept { Reg::Write<F_SOF>(value); }
    static auto ReadRESET() noexcept -> ValueType { return Reg::Read<F_RESET>(); }
    static void WriteRESET(ValueType value) noexcept { Reg::Write<F_RESET>(value); }
    static auto ReadSUSP() noexcept -> ValueType { return Reg::Read<F_SUSP>(); }
    static void WriteSUSP(ValueType value) noexcept { Reg::Write<F_SUSP>(value); }
    static auto ReadWKUP() noexcept -> ValueType { return Reg::Read<F_WKUP>(); }
    static void WriteWKUP(ValueType value) noexcept { Reg::Write<F_WKUP>(value); }
    static auto ReadERR() noexcept -> ValueType { return Reg::Read<F_ERR>(); }
    static void WriteERR(ValueType value) noexcept { Reg::Write<F_ERR>(value); }
    static auto ReadPMAOVR() noexcept -> ValueType { return Reg::Read<F_PMAOVR>(); }
    static void WritePMAOVR(ValueType value) noexcept { Reg::Write<F_PMAOVR>(value); }
    static auto ReadCTR() noexcept -> ValueType { return Reg::Read<F_CTR>(); }
    static void WriteCTR(ValueType value) noexcept { Reg::Write<F_CTR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c44;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EP_ID = CortexM3::Field<ValueType, 0, 4>;
    using F_DIR = CortexM3::Field<ValueType, 4, 1>;
    using F_ESOF = CortexM3::Field<ValueType, 8, 1>;
    using F_SOF = CortexM3::Field<ValueType, 9, 1>;
    using F_RESET = CortexM3::Field<ValueType, 10, 1>;
    using F_SUSP = CortexM3::Field<ValueType, 11, 1>;
    using F_WKUP = CortexM3::Field<ValueType, 12, 1>;
    using F_ERR = CortexM3::Field<ValueType, 13, 1>;
    using F_PMAOVR = CortexM3::Field<ValueType, 14, 1>;
    using F_CTR = CortexM3::Field<ValueType, 15, 1>;
};

class FNR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadFN() noexcept -> ValueType { return Reg::Read<F_FN>(); }
    static auto ReadLSOF() noexcept -> ValueType { return Reg::Read<F_LSOF>(); }
    static auto ReadLCK() noexcept -> ValueType { return Reg::Read<F_LCK>(); }
    static auto ReadRXDM() noexcept -> ValueType { return Reg::Read<F_RXDM>(); }
    static auto ReadRXDP() noexcept -> ValueType { return Reg::Read<F_RXDP>(); }

private:
    static constexpr std::uintptr_t Address = 0x40005c48;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_FN = CortexM3::Field<ValueType, 0, 11>;
    using F_LSOF = CortexM3::Field<ValueType, 11, 2>;
    using F_LCK = CortexM3::Field<ValueType, 13, 1>;
    using F_RXDM = CortexM3::Field<ValueType, 14, 1>;
    using F_RXDP = CortexM3::Field<ValueType, 15, 1>;
};

class DADDR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadADD() noexcept -> ValueType { return Reg::Read<F_ADD>(); }
    static void WriteADD(ValueType value) noexcept { Reg::Write<F_ADD>(value); }
    static auto ReadEF() noexcept -> ValueType { return Reg::Read<F_EF>(); }
    static void WriteEF(ValueType value) noexcept { Reg::Write<F_EF>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c4c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ADD = CortexM3::Field<ValueType, 0, 7>;
    using F_EF = CortexM3::Field<ValueType, 7, 1>;
};

class BTABLE {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadBTABLE() noexcept -> ValueType { return Reg::Read<F_BTABLE>(); }
    static void WriteBTABLE(ValueType value) noexcept { Reg::Write<F_BTABLE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40005c50;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_BTABLE = CortexM3::Field<ValueType, 3, 13>;
};

} // namespace STM32F103::USB
