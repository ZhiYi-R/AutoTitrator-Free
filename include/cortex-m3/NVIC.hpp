#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace CortexM3::NVIC {

class NVIC_ISER0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETENA() noexcept -> ValueType { return Reg::Read<F_SETENA>(); }
    static void WriteSETENA(ValueType value) noexcept { Reg::Write<F_SETENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e100;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISER1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETENA() noexcept -> ValueType { return Reg::Read<F_SETENA>(); }
    static void WriteSETENA(ValueType value) noexcept { Reg::Write<F_SETENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e104;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISER2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETENA() noexcept -> ValueType { return Reg::Read<F_SETENA>(); }
    static void WriteSETENA(ValueType value) noexcept { Reg::Write<F_SETENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e108;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISER3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETENA() noexcept -> ValueType { return Reg::Read<F_SETENA>(); }
    static void WriteSETENA(ValueType value) noexcept { Reg::Write<F_SETENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e10c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISER4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETENA() noexcept -> ValueType { return Reg::Read<F_SETENA>(); }
    static void WriteSETENA(ValueType value) noexcept { Reg::Write<F_SETENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e110;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISER5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETENA() noexcept -> ValueType { return Reg::Read<F_SETENA>(); }
    static void WriteSETENA(ValueType value) noexcept { Reg::Write<F_SETENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e114;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISER6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETENA() noexcept -> ValueType { return Reg::Read<F_SETENA>(); }
    static void WriteSETENA(ValueType value) noexcept { Reg::Write<F_SETENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e118;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISER7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETENA() noexcept -> ValueType { return Reg::Read<F_SETENA>(); }
    static void WriteSETENA(ValueType value) noexcept { Reg::Write<F_SETENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e11c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICER0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRENA() noexcept -> ValueType { return Reg::Read<F_CLRENA>(); }
    static void WriteCLRENA(ValueType value) noexcept { Reg::Write<F_CLRENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e180;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICER1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRENA() noexcept -> ValueType { return Reg::Read<F_CLRENA>(); }
    static void WriteCLRENA(ValueType value) noexcept { Reg::Write<F_CLRENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e184;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICER2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRENA() noexcept -> ValueType { return Reg::Read<F_CLRENA>(); }
    static void WriteCLRENA(ValueType value) noexcept { Reg::Write<F_CLRENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e188;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICER3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRENA() noexcept -> ValueType { return Reg::Read<F_CLRENA>(); }
    static void WriteCLRENA(ValueType value) noexcept { Reg::Write<F_CLRENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e18c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICER4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRENA() noexcept -> ValueType { return Reg::Read<F_CLRENA>(); }
    static void WriteCLRENA(ValueType value) noexcept { Reg::Write<F_CLRENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e190;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICER5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRENA() noexcept -> ValueType { return Reg::Read<F_CLRENA>(); }
    static void WriteCLRENA(ValueType value) noexcept { Reg::Write<F_CLRENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e194;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICER6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRENA() noexcept -> ValueType { return Reg::Read<F_CLRENA>(); }
    static void WriteCLRENA(ValueType value) noexcept { Reg::Write<F_CLRENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e198;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICER7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRENA() noexcept -> ValueType { return Reg::Read<F_CLRENA>(); }
    static void WriteCLRENA(ValueType value) noexcept { Reg::Write<F_CLRENA>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e19c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRENA = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISPR0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETPEND() noexcept -> ValueType { return Reg::Read<F_SETPEND>(); }
    static void WriteSETPEND(ValueType value) noexcept { Reg::Write<F_SETPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e200;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISPR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETPEND() noexcept -> ValueType { return Reg::Read<F_SETPEND>(); }
    static void WriteSETPEND(ValueType value) noexcept { Reg::Write<F_SETPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e204;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISPR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETPEND() noexcept -> ValueType { return Reg::Read<F_SETPEND>(); }
    static void WriteSETPEND(ValueType value) noexcept { Reg::Write<F_SETPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e208;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISPR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETPEND() noexcept -> ValueType { return Reg::Read<F_SETPEND>(); }
    static void WriteSETPEND(ValueType value) noexcept { Reg::Write<F_SETPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e20c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISPR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETPEND() noexcept -> ValueType { return Reg::Read<F_SETPEND>(); }
    static void WriteSETPEND(ValueType value) noexcept { Reg::Write<F_SETPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e210;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISPR5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETPEND() noexcept -> ValueType { return Reg::Read<F_SETPEND>(); }
    static void WriteSETPEND(ValueType value) noexcept { Reg::Write<F_SETPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e214;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISPR6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETPEND() noexcept -> ValueType { return Reg::Read<F_SETPEND>(); }
    static void WriteSETPEND(ValueType value) noexcept { Reg::Write<F_SETPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e218;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ISPR7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSETPEND() noexcept -> ValueType { return Reg::Read<F_SETPEND>(); }
    static void WriteSETPEND(ValueType value) noexcept { Reg::Write<F_SETPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e21c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SETPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICPR0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRPEND() noexcept -> ValueType { return Reg::Read<F_CLRPEND>(); }
    static void WriteCLRPEND(ValueType value) noexcept { Reg::Write<F_CLRPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e280;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICPR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRPEND() noexcept -> ValueType { return Reg::Read<F_CLRPEND>(); }
    static void WriteCLRPEND(ValueType value) noexcept { Reg::Write<F_CLRPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e284;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICPR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRPEND() noexcept -> ValueType { return Reg::Read<F_CLRPEND>(); }
    static void WriteCLRPEND(ValueType value) noexcept { Reg::Write<F_CLRPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e288;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICPR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRPEND() noexcept -> ValueType { return Reg::Read<F_CLRPEND>(); }
    static void WriteCLRPEND(ValueType value) noexcept { Reg::Write<F_CLRPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e28c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICPR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRPEND() noexcept -> ValueType { return Reg::Read<F_CLRPEND>(); }
    static void WriteCLRPEND(ValueType value) noexcept { Reg::Write<F_CLRPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e290;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICPR5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRPEND() noexcept -> ValueType { return Reg::Read<F_CLRPEND>(); }
    static void WriteCLRPEND(ValueType value) noexcept { Reg::Write<F_CLRPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e294;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICPR6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRPEND() noexcept -> ValueType { return Reg::Read<F_CLRPEND>(); }
    static void WriteCLRPEND(ValueType value) noexcept { Reg::Write<F_CLRPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e298;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_ICPR7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadCLRPEND() noexcept -> ValueType { return Reg::Read<F_CLRPEND>(); }
    static void WriteCLRPEND(ValueType value) noexcept { Reg::Write<F_CLRPEND>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e29c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_CLRPEND = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_IABR0 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACTIVE() noexcept -> ValueType { return Reg::Read<F_ACTIVE>(); }
    static void WriteACTIVE(ValueType value) noexcept { Reg::Write<F_ACTIVE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e300;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACTIVE = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_IABR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACTIVE() noexcept -> ValueType { return Reg::Read<F_ACTIVE>(); }
    static void WriteACTIVE(ValueType value) noexcept { Reg::Write<F_ACTIVE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e304;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACTIVE = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_IABR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACTIVE() noexcept -> ValueType { return Reg::Read<F_ACTIVE>(); }
    static void WriteACTIVE(ValueType value) noexcept { Reg::Write<F_ACTIVE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e308;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACTIVE = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_IABR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACTIVE() noexcept -> ValueType { return Reg::Read<F_ACTIVE>(); }
    static void WriteACTIVE(ValueType value) noexcept { Reg::Write<F_ACTIVE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e30c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACTIVE = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_IABR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACTIVE() noexcept -> ValueType { return Reg::Read<F_ACTIVE>(); }
    static void WriteACTIVE(ValueType value) noexcept { Reg::Write<F_ACTIVE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e310;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACTIVE = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_IABR5 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACTIVE() noexcept -> ValueType { return Reg::Read<F_ACTIVE>(); }
    static void WriteACTIVE(ValueType value) noexcept { Reg::Write<F_ACTIVE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e314;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACTIVE = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_IABR6 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACTIVE() noexcept -> ValueType { return Reg::Read<F_ACTIVE>(); }
    static void WriteACTIVE(ValueType value) noexcept { Reg::Write<F_ACTIVE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e318;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACTIVE = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_IABR7 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadACTIVE() noexcept -> ValueType { return Reg::Read<F_ACTIVE>(); }
    static void WriteACTIVE(ValueType value) noexcept { Reg::Write<F_ACTIVE>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e31c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_ACTIVE = CortexM3::Field<ValueType, 0, 32>;
};

class NVIC_IPR0 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e400;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR1 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e404;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR2 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e408;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR3 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e40c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR4 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e410;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR5 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e414;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR6 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e418;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR7 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e41c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR8 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e420;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR9 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e424;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR10 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e428;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR11 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e42c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR12 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e430;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR13 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e434;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR14 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e438;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR15 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e43c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR16 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e440;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR17 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e444;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR18 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e448;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR19 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e44c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR20 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e450;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR21 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e454;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR22 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e458;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR23 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e45c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR24 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e460;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR25 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e464;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR26 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e468;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR27 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e46c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR28 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e470;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR29 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e474;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR30 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e478;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR31 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e47c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR32 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e480;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR33 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e484;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR34 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e488;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR35 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e48c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR36 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e490;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR37 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e494;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR38 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e498;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR39 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e49c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR40 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4a0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR41 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4a4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR42 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4a8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR43 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4ac;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR44 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4b0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR45 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4b4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR46 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4b8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR47 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4bc;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR48 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4c0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR49 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4c4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR50 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4c8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR51 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4cc;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR52 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4d0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR53 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4d4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR54 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4d8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR55 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4dc;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR56 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4e0;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR57 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4e4;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR58 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4e8;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

class NVIC_IPR59 {
public:
    using ValueType = std::uint32_t;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPRI_N3() noexcept -> ValueType { return Reg::Read<F_PRI_N3>(); }
    static void WritePRI_N3(ValueType value) noexcept { Reg::Write<F_PRI_N3>(value); }
    static auto ReadPRI_N2() noexcept -> ValueType { return Reg::Read<F_PRI_N2>(); }
    static void WritePRI_N2(ValueType value) noexcept { Reg::Write<F_PRI_N2>(value); }
    static auto ReadPRI_N1() noexcept -> ValueType { return Reg::Read<F_PRI_N1>(); }
    static void WritePRI_N1(ValueType value) noexcept { Reg::Write<F_PRI_N1>(value); }
    static auto ReadPRI_N0() noexcept -> ValueType { return Reg::Read<F_PRI_N0>(); }
    static void WritePRI_N0(ValueType value) noexcept { Reg::Write<F_PRI_N0>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000e4ec;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PRI_N3 = CortexM3::Field<ValueType, 24, 8>;
    using F_PRI_N2 = CortexM3::Field<ValueType, 16, 8>;
    using F_PRI_N1 = CortexM3::Field<ValueType, 8, 8>;
    using F_PRI_N0 = CortexM3::Field<ValueType, 0, 8>;
};

} // namespace CortexM3::NVIC
