#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::OTG_FS_PWRCLK {

class FS_PCGCCTL {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSTPPCLK() noexcept -> ValueType { return Reg::Read<F_STPPCLK>(); }
    static void WriteSTPPCLK(ValueType value) noexcept { Reg::Write<F_STPPCLK>(value); }
    static auto ReadGATEHCLK() noexcept -> ValueType { return Reg::Read<F_GATEHCLK>(); }
    static void WriteGATEHCLK(ValueType value) noexcept { Reg::Write<F_GATEHCLK>(value); }
    static auto ReadPHYSUSP() noexcept -> ValueType { return Reg::Read<F_PHYSUSP>(); }
    static void WritePHYSUSP(ValueType value) noexcept { Reg::Write<F_PHYSUSP>(value); }

private:
    static constexpr std::uintptr_t Address = 0x50000e00;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_STPPCLK = CortexM3::Field<ValueType, 0, 1>;
    using F_GATEHCLK = CortexM3::Field<ValueType, 1, 1>;
    using F_PHYSUSP = CortexM3::Field<ValueType, 4, 1>;
};

} // namespace STM32F103::OTG_FS_PWRCLK
