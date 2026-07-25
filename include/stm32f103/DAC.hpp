#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::DAC {

class CR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEN1() noexcept -> ValueType { return Reg::Read<F_EN1>(); }
    static void WriteEN1(ValueType value) noexcept { Reg::Write<F_EN1>(value); }
    static auto ReadBOFF1() noexcept -> ValueType { return Reg::Read<F_BOFF1>(); }
    static void WriteBOFF1(ValueType value) noexcept { Reg::Write<F_BOFF1>(value); }
    static auto ReadTEN1() noexcept -> ValueType { return Reg::Read<F_TEN1>(); }
    static void WriteTEN1(ValueType value) noexcept { Reg::Write<F_TEN1>(value); }
    static auto ReadTSEL1() noexcept -> ValueType { return Reg::Read<F_TSEL1>(); }
    static void WriteTSEL1(ValueType value) noexcept { Reg::Write<F_TSEL1>(value); }
    static auto ReadWAVE1() noexcept -> ValueType { return Reg::Read<F_WAVE1>(); }
    static void WriteWAVE1(ValueType value) noexcept { Reg::Write<F_WAVE1>(value); }
    static auto ReadMAMP1() noexcept -> ValueType { return Reg::Read<F_MAMP1>(); }
    static void WriteMAMP1(ValueType value) noexcept { Reg::Write<F_MAMP1>(value); }
    static auto ReadDMAEN1() noexcept -> ValueType { return Reg::Read<F_DMAEN1>(); }
    static void WriteDMAEN1(ValueType value) noexcept { Reg::Write<F_DMAEN1>(value); }
    static auto ReadEN2() noexcept -> ValueType { return Reg::Read<F_EN2>(); }
    static void WriteEN2(ValueType value) noexcept { Reg::Write<F_EN2>(value); }
    static auto ReadBOFF2() noexcept -> ValueType { return Reg::Read<F_BOFF2>(); }
    static void WriteBOFF2(ValueType value) noexcept { Reg::Write<F_BOFF2>(value); }
    static auto ReadTEN2() noexcept -> ValueType { return Reg::Read<F_TEN2>(); }
    static void WriteTEN2(ValueType value) noexcept { Reg::Write<F_TEN2>(value); }
    static auto ReadTSEL2() noexcept -> ValueType { return Reg::Read<F_TSEL2>(); }
    static void WriteTSEL2(ValueType value) noexcept { Reg::Write<F_TSEL2>(value); }
    static auto ReadWAVE2() noexcept -> ValueType { return Reg::Read<F_WAVE2>(); }
    static void WriteWAVE2(ValueType value) noexcept { Reg::Write<F_WAVE2>(value); }
    static auto ReadMAMP2() noexcept -> ValueType { return Reg::Read<F_MAMP2>(); }
    static void WriteMAMP2(ValueType value) noexcept { Reg::Write<F_MAMP2>(value); }
    static auto ReadDMAEN2() noexcept -> ValueType { return Reg::Read<F_DMAEN2>(); }
    static void WriteDMAEN2(ValueType value) noexcept { Reg::Write<F_DMAEN2>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007400;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EN1 = CortexM3::Field<ValueType, 0, 1>;
    using F_BOFF1 = CortexM3::Field<ValueType, 1, 1>;
    using F_TEN1 = CortexM3::Field<ValueType, 2, 1>;
    using F_TSEL1 = CortexM3::Field<ValueType, 3, 3>;
    using F_WAVE1 = CortexM3::Field<ValueType, 6, 2>;
    using F_MAMP1 = CortexM3::Field<ValueType, 8, 4>;
    using F_DMAEN1 = CortexM3::Field<ValueType, 12, 1>;
    using F_EN2 = CortexM3::Field<ValueType, 16, 1>;
    using F_BOFF2 = CortexM3::Field<ValueType, 17, 1>;
    using F_TEN2 = CortexM3::Field<ValueType, 18, 1>;
    using F_TSEL2 = CortexM3::Field<ValueType, 19, 3>;
    using F_WAVE2 = CortexM3::Field<ValueType, 22, 2>;
    using F_MAMP2 = CortexM3::Field<ValueType, 24, 4>;
    using F_DMAEN2 = CortexM3::Field<ValueType, 28, 1>;
};

class SWTRIGR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteSWTRIG1(ValueType value) noexcept { Reg::Write<F_SWTRIG1>(value); }
    static void WriteSWTRIG2(ValueType value) noexcept { Reg::Write<F_SWTRIG2>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007404;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SWTRIG1 = CortexM3::Field<ValueType, 0, 1>;
    using F_SWTRIG2 = CortexM3::Field<ValueType, 1, 1>;
};

class DHR12R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDACC1DHR() noexcept -> ValueType { return Reg::Read<F_DACC1DHR>(); }
    static void WriteDACC1DHR(ValueType value) noexcept { Reg::Write<F_DACC1DHR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007408;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC1DHR = CortexM3::Field<ValueType, 0, 12>;
};

class DHR12L1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDACC1DHR() noexcept -> ValueType { return Reg::Read<F_DACC1DHR>(); }
    static void WriteDACC1DHR(ValueType value) noexcept { Reg::Write<F_DACC1DHR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000740c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC1DHR = CortexM3::Field<ValueType, 4, 12>;
};

class DHR8R1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDACC1DHR() noexcept -> ValueType { return Reg::Read<F_DACC1DHR>(); }
    static void WriteDACC1DHR(ValueType value) noexcept { Reg::Write<F_DACC1DHR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007410;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC1DHR = CortexM3::Field<ValueType, 0, 8>;
};

class DHR12R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDACC2DHR() noexcept -> ValueType { return Reg::Read<F_DACC2DHR>(); }
    static void WriteDACC2DHR(ValueType value) noexcept { Reg::Write<F_DACC2DHR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007414;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC2DHR = CortexM3::Field<ValueType, 0, 12>;
};

class DHR12L2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDACC2DHR() noexcept -> ValueType { return Reg::Read<F_DACC2DHR>(); }
    static void WriteDACC2DHR(ValueType value) noexcept { Reg::Write<F_DACC2DHR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007418;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC2DHR = CortexM3::Field<ValueType, 4, 12>;
};

class DHR8R2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDACC2DHR() noexcept -> ValueType { return Reg::Read<F_DACC2DHR>(); }
    static void WriteDACC2DHR(ValueType value) noexcept { Reg::Write<F_DACC2DHR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4000741c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC2DHR = CortexM3::Field<ValueType, 0, 8>;
};

class DHR12RD {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDACC1DHR() noexcept -> ValueType { return Reg::Read<F_DACC1DHR>(); }
    static void WriteDACC1DHR(ValueType value) noexcept { Reg::Write<F_DACC1DHR>(value); }
    static auto ReadDACC2DHR() noexcept -> ValueType { return Reg::Read<F_DACC2DHR>(); }
    static void WriteDACC2DHR(ValueType value) noexcept { Reg::Write<F_DACC2DHR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007420;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC1DHR = CortexM3::Field<ValueType, 0, 12>;
    using F_DACC2DHR = CortexM3::Field<ValueType, 16, 12>;
};

class DHR12LD {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDACC1DHR() noexcept -> ValueType { return Reg::Read<F_DACC1DHR>(); }
    static void WriteDACC1DHR(ValueType value) noexcept { Reg::Write<F_DACC1DHR>(value); }
    static auto ReadDACC2DHR() noexcept -> ValueType { return Reg::Read<F_DACC2DHR>(); }
    static void WriteDACC2DHR(ValueType value) noexcept { Reg::Write<F_DACC2DHR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007424;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC1DHR = CortexM3::Field<ValueType, 4, 12>;
    using F_DACC2DHR = CortexM3::Field<ValueType, 20, 12>;
};

class DHR8RD {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDACC1DHR() noexcept -> ValueType { return Reg::Read<F_DACC1DHR>(); }
    static void WriteDACC1DHR(ValueType value) noexcept { Reg::Write<F_DACC1DHR>(value); }
    static auto ReadDACC2DHR() noexcept -> ValueType { return Reg::Read<F_DACC2DHR>(); }
    static void WriteDACC2DHR(ValueType value) noexcept { Reg::Write<F_DACC2DHR>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40007428;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC1DHR = CortexM3::Field<ValueType, 0, 8>;
    using F_DACC2DHR = CortexM3::Field<ValueType, 8, 8>;
};

class DOR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDACC1DOR() noexcept -> ValueType { return Reg::Read<F_DACC1DOR>(); }

private:
    static constexpr std::uintptr_t Address = 0x4000742c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC1DOR = CortexM3::Field<ValueType, 0, 12>;
};

class DOR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDACC2DOR() noexcept -> ValueType { return Reg::Read<F_DACC2DOR>(); }

private:
    static constexpr std::uintptr_t Address = 0x40007430;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DACC2DOR = CortexM3::Field<ValueType, 0, 12>;
};

} // namespace STM32F103::DAC
