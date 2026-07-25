#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::DBG {

class IDCODE {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static auto ReadDEV_ID() noexcept -> ValueType { return Reg::Read<F_DEV_ID>(); }
    static auto ReadREV_ID() noexcept -> ValueType { return Reg::Read<F_REV_ID>(); }

private:
    static constexpr std::uintptr_t Address = 0xe0042000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DEV_ID = CortexM3::Field<ValueType, 0, 12>;
    using F_REV_ID = CortexM3::Field<ValueType, 16, 16>;
};

class CR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadDBG_SLEEP() noexcept -> ValueType { return Reg::Read<F_DBG_SLEEP>(); }
    static void WriteDBG_SLEEP(ValueType value) noexcept { Reg::Write<F_DBG_SLEEP>(value); }
    static auto ReadDBG_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_STOP>(); }
    static void WriteDBG_STOP(ValueType value) noexcept { Reg::Write<F_DBG_STOP>(value); }
    static auto ReadDBG_STANDBY() noexcept -> ValueType { return Reg::Read<F_DBG_STANDBY>(); }
    static void WriteDBG_STANDBY(ValueType value) noexcept { Reg::Write<F_DBG_STANDBY>(value); }
    static auto ReadTRACE_IOEN() noexcept -> ValueType { return Reg::Read<F_TRACE_IOEN>(); }
    static void WriteTRACE_IOEN(ValueType value) noexcept { Reg::Write<F_TRACE_IOEN>(value); }
    static auto ReadTRACE_MODE() noexcept -> ValueType { return Reg::Read<F_TRACE_MODE>(); }
    static void WriteTRACE_MODE(ValueType value) noexcept { Reg::Write<F_TRACE_MODE>(value); }
    static auto ReadDBG_IWDG_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_IWDG_STOP>(); }
    static void WriteDBG_IWDG_STOP(ValueType value) noexcept { Reg::Write<F_DBG_IWDG_STOP>(value); }
    static auto ReadDBG_WWDG_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_WWDG_STOP>(); }
    static void WriteDBG_WWDG_STOP(ValueType value) noexcept { Reg::Write<F_DBG_WWDG_STOP>(value); }
    static auto ReadDBG_TIM1_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_TIM1_STOP>(); }
    static void WriteDBG_TIM1_STOP(ValueType value) noexcept { Reg::Write<F_DBG_TIM1_STOP>(value); }
    static auto ReadDBG_TIM2_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_TIM2_STOP>(); }
    static void WriteDBG_TIM2_STOP(ValueType value) noexcept { Reg::Write<F_DBG_TIM2_STOP>(value); }
    static auto ReadDBG_TIM3_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_TIM3_STOP>(); }
    static void WriteDBG_TIM3_STOP(ValueType value) noexcept { Reg::Write<F_DBG_TIM3_STOP>(value); }
    static auto ReadDBG_TIM4_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_TIM4_STOP>(); }
    static void WriteDBG_TIM4_STOP(ValueType value) noexcept { Reg::Write<F_DBG_TIM4_STOP>(value); }
    static auto ReadDBG_CAN1_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_CAN1_STOP>(); }
    static void WriteDBG_CAN1_STOP(ValueType value) noexcept { Reg::Write<F_DBG_CAN1_STOP>(value); }
    static auto ReadDBG_I2C1_SMBUS_TIMEOUT() noexcept -> ValueType { return Reg::Read<F_DBG_I2C1_SMBUS_TIMEOUT>(); }
    static void WriteDBG_I2C1_SMBUS_TIMEOUT(ValueType value) noexcept { Reg::Write<F_DBG_I2C1_SMBUS_TIMEOUT>(value); }
    static auto ReadDBG_I2C2_SMBUS_TIMEOUT() noexcept -> ValueType { return Reg::Read<F_DBG_I2C2_SMBUS_TIMEOUT>(); }
    static void WriteDBG_I2C2_SMBUS_TIMEOUT(ValueType value) noexcept { Reg::Write<F_DBG_I2C2_SMBUS_TIMEOUT>(value); }
    static auto ReadDBG_TIM8_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_TIM8_STOP>(); }
    static void WriteDBG_TIM8_STOP(ValueType value) noexcept { Reg::Write<F_DBG_TIM8_STOP>(value); }
    static auto ReadDBG_TIM5_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_TIM5_STOP>(); }
    static void WriteDBG_TIM5_STOP(ValueType value) noexcept { Reg::Write<F_DBG_TIM5_STOP>(value); }
    static auto ReadDBG_TIM6_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_TIM6_STOP>(); }
    static void WriteDBG_TIM6_STOP(ValueType value) noexcept { Reg::Write<F_DBG_TIM6_STOP>(value); }
    static auto ReadDBG_TIM7_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_TIM7_STOP>(); }
    static void WriteDBG_TIM7_STOP(ValueType value) noexcept { Reg::Write<F_DBG_TIM7_STOP>(value); }
    static auto ReadDBG_CAN2_STOP() noexcept -> ValueType { return Reg::Read<F_DBG_CAN2_STOP>(); }
    static void WriteDBG_CAN2_STOP(ValueType value) noexcept { Reg::Write<F_DBG_CAN2_STOP>(value); }

private:
    static constexpr std::uintptr_t Address = 0xe0042004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_DBG_SLEEP = CortexM3::Field<ValueType, 0, 1>;
    using F_DBG_STOP = CortexM3::Field<ValueType, 1, 1>;
    using F_DBG_STANDBY = CortexM3::Field<ValueType, 2, 1>;
    using F_TRACE_IOEN = CortexM3::Field<ValueType, 5, 1>;
    using F_TRACE_MODE = CortexM3::Field<ValueType, 6, 2>;
    using F_DBG_IWDG_STOP = CortexM3::Field<ValueType, 8, 1>;
    using F_DBG_WWDG_STOP = CortexM3::Field<ValueType, 9, 1>;
    using F_DBG_TIM1_STOP = CortexM3::Field<ValueType, 10, 1>;
    using F_DBG_TIM2_STOP = CortexM3::Field<ValueType, 11, 1>;
    using F_DBG_TIM3_STOP = CortexM3::Field<ValueType, 12, 1>;
    using F_DBG_TIM4_STOP = CortexM3::Field<ValueType, 13, 1>;
    using F_DBG_CAN1_STOP = CortexM3::Field<ValueType, 14, 1>;
    using F_DBG_I2C1_SMBUS_TIMEOUT = CortexM3::Field<ValueType, 15, 1>;
    using F_DBG_I2C2_SMBUS_TIMEOUT = CortexM3::Field<ValueType, 16, 1>;
    using F_DBG_TIM8_STOP = CortexM3::Field<ValueType, 17, 1>;
    using F_DBG_TIM5_STOP = CortexM3::Field<ValueType, 18, 1>;
    using F_DBG_TIM6_STOP = CortexM3::Field<ValueType, 19, 1>;
    using F_DBG_TIM7_STOP = CortexM3::Field<ValueType, 20, 1>;
    using F_DBG_CAN2_STOP = CortexM3::Field<ValueType, 21, 1>;
};

} // namespace STM32F103::DBG
