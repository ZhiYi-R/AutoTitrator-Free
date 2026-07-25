#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::RTC {

class CRH {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSECIE() noexcept -> ValueType { return Reg::Read<F_SECIE>(); }
    static void WriteSECIE(ValueType value) noexcept { Reg::Write<F_SECIE>(value); }
    static auto ReadALRIE() noexcept -> ValueType { return Reg::Read<F_ALRIE>(); }
    static void WriteALRIE(ValueType value) noexcept { Reg::Write<F_ALRIE>(value); }
    static auto ReadOWIE() noexcept -> ValueType { return Reg::Read<F_OWIE>(); }
    static void WriteOWIE(ValueType value) noexcept { Reg::Write<F_OWIE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40002800;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SECIE = CortexM3::Field<ValueType, 0, 1>;
    using F_ALRIE = CortexM3::Field<ValueType, 1, 1>;
    using F_OWIE = CortexM3::Field<ValueType, 2, 1>;
};

class CRL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000020;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSECF() noexcept -> ValueType { return Reg::Read<F_SECF>(); }
    static void WriteSECF(ValueType value) noexcept { Reg::Write<F_SECF>(value); }
    static auto ReadALRF() noexcept -> ValueType { return Reg::Read<F_ALRF>(); }
    static void WriteALRF(ValueType value) noexcept { Reg::Write<F_ALRF>(value); }
    static auto ReadOWF() noexcept -> ValueType { return Reg::Read<F_OWF>(); }
    static void WriteOWF(ValueType value) noexcept { Reg::Write<F_OWF>(value); }
    static auto ReadRSF() noexcept -> ValueType { return Reg::Read<F_RSF>(); }
    static void WriteRSF(ValueType value) noexcept { Reg::Write<F_RSF>(value); }
    static auto ReadCNF() noexcept -> ValueType { return Reg::Read<F_CNF>(); }
    static void WriteCNF(ValueType value) noexcept { Reg::Write<F_CNF>(value); }
    static auto ReadRTOFF() noexcept -> ValueType { return Reg::Read<F_RTOFF>(); }

private:
    static constexpr std::uintptr_t Address = 0x40002804;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SECF = CortexM3::Field<ValueType, 0, 1>;
    using F_ALRF = CortexM3::Field<ValueType, 1, 1>;
    using F_OWF = CortexM3::Field<ValueType, 2, 1>;
    using F_RSF = CortexM3::Field<ValueType, 3, 1>;
    using F_CNF = CortexM3::Field<ValueType, 4, 1>;
    using F_RTOFF = CortexM3::Field<ValueType, 5, 1>;
};

class PRLH {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WritePRLH(ValueType value) noexcept { Reg::Write<F_PRLH>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40002808;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRLH = CortexM3::Field<ValueType, 0, 4>;
};

class PRLL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00008000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WritePRLL(ValueType value) noexcept { Reg::Write<F_PRLL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000280c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRLL = CortexM3::Field<ValueType, 0, 16>;
};

class DIVH {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDIVH() noexcept -> ValueType { return Reg::Read<F_DIVH>(); }

private:
    static constexpr std::uintptr_t Address = 0x40002810;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DIVH = CortexM3::Field<ValueType, 0, 4>;
};

class DIVL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00008000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDIVL() noexcept -> ValueType { return Reg::Read<F_DIVL>(); }

private:
    static constexpr std::uintptr_t Address = 0x40002814;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DIVL = CortexM3::Field<ValueType, 0, 16>;
};

class CNTH {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCNTH() noexcept -> ValueType { return Reg::Read<F_CNTH>(); }
    static void WriteCNTH(ValueType value) noexcept { Reg::Write<F_CNTH>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40002818;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CNTH = CortexM3::Field<ValueType, 0, 16>;
};

class CNTL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCNTL() noexcept -> ValueType { return Reg::Read<F_CNTL>(); }
    static void WriteCNTL(ValueType value) noexcept { Reg::Write<F_CNTL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000281c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CNTL = CortexM3::Field<ValueType, 0, 16>;
};

class ALRH {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0000FFFF;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteALRH(ValueType value) noexcept { Reg::Write<F_ALRH>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40002820;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ALRH = CortexM3::Field<ValueType, 0, 16>;
};

class ALRL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0000FFFF;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteALRL(ValueType value) noexcept { Reg::Write<F_ALRL>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40002824;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ALRL = CortexM3::Field<ValueType, 0, 16>;
};

} // namespace STM32F103::RTC
