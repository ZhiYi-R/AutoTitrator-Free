#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::WWDG {

class CR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0000007F;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadT() noexcept -> ValueType { return Reg::Read<F_T>(); }
    static void WriteT(ValueType value) noexcept { Reg::Write<F_T>(value); }
    static auto ReadWDGA() noexcept -> ValueType { return Reg::Read<F_WDGA>(); }
    static void WriteWDGA(ValueType value) noexcept { Reg::Write<F_WDGA>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40002c00;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_T = CortexM3::Field<ValueType, 0, 7>;
    using F_WDGA = CortexM3::Field<ValueType, 7, 1>;
};

class CFR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x0000007F;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadW() noexcept -> ValueType { return Reg::Read<F_W>(); }
    static void WriteW(ValueType value) noexcept { Reg::Write<F_W>(value); }
    static auto ReadWDGTB() noexcept -> ValueType { return Reg::Read<F_WDGTB>(); }
    static void WriteWDGTB(ValueType value) noexcept { Reg::Write<F_WDGTB>(value); }
    static auto ReadEWI() noexcept -> ValueType { return Reg::Read<F_EWI>(); }
    static void WriteEWI(ValueType value) noexcept { Reg::Write<F_EWI>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40002c04;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_W = CortexM3::Field<ValueType, 0, 7>;
    using F_WDGTB = CortexM3::Field<ValueType, 7, 2>;
    using F_EWI = CortexM3::Field<ValueType, 9, 1>;
};

class SR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEWI() noexcept -> ValueType { return Reg::Read<F_EWI>(); }
    static void WriteEWI(ValueType value) noexcept { Reg::Write<F_EWI>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40002c08;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EWI = CortexM3::Field<ValueType, 0, 1>;
};

} // namespace STM32F103::WWDG
