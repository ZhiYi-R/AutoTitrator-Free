#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace CortexM3::NVIC_STIR {

class STIR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static void WriteINTID(ValueType value) noexcept { Reg::Write<F_INTID>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe000ef00;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_INTID = CortexM3::Field<ValueType, 0, 9>;
};

} // namespace CortexM3::NVIC_STIR
