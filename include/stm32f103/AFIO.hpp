#pragma once

#include <register/mmio.hpp>
#include <cstdint>

namespace STM32F103::AFIO {

class EVCR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadPIN() noexcept -> ValueType { return Reg::Read<F_PIN>(); }
    static void WritePIN(ValueType value) noexcept { Reg::Write<F_PIN>(value); }
    static auto ReadPORT() noexcept -> ValueType { return Reg::Read<F_PORT>(); }
    static void WritePORT(ValueType value) noexcept { Reg::Write<F_PORT>(value); }
    static auto ReadEVOE() noexcept -> ValueType { return Reg::Read<F_EVOE>(); }
    static void WriteEVOE(ValueType value) noexcept { Reg::Write<F_EVOE>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40010000;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_PIN = CortexM3::Field<ValueType, 0, 4>;
    using F_PORT = CortexM3::Field<ValueType, 4, 3>;
    using F_EVOE = CortexM3::Field<ValueType, 7, 1>;
};

class MAPR {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadSPI1_REMAP() noexcept -> ValueType { return Reg::Read<F_SPI1_REMAP>(); }
    static void WriteSPI1_REMAP(ValueType value) noexcept { Reg::Write<F_SPI1_REMAP>(value); }
    static auto ReadI2C1_REMAP() noexcept -> ValueType { return Reg::Read<F_I2C1_REMAP>(); }
    static void WriteI2C1_REMAP(ValueType value) noexcept { Reg::Write<F_I2C1_REMAP>(value); }
    static auto ReadUSART1_REMAP() noexcept -> ValueType { return Reg::Read<F_USART1_REMAP>(); }
    static void WriteUSART1_REMAP(ValueType value) noexcept { Reg::Write<F_USART1_REMAP>(value); }
    static auto ReadUSART2_REMAP() noexcept -> ValueType { return Reg::Read<F_USART2_REMAP>(); }
    static void WriteUSART2_REMAP(ValueType value) noexcept { Reg::Write<F_USART2_REMAP>(value); }
    static auto ReadUSART3_REMAP() noexcept -> ValueType { return Reg::Read<F_USART3_REMAP>(); }
    static void WriteUSART3_REMAP(ValueType value) noexcept { Reg::Write<F_USART3_REMAP>(value); }
    static auto ReadTIM1_REMAP() noexcept -> ValueType { return Reg::Read<F_TIM1_REMAP>(); }
    static void WriteTIM1_REMAP(ValueType value) noexcept { Reg::Write<F_TIM1_REMAP>(value); }
    static auto ReadTIM2_REMAP() noexcept -> ValueType { return Reg::Read<F_TIM2_REMAP>(); }
    static void WriteTIM2_REMAP(ValueType value) noexcept { Reg::Write<F_TIM2_REMAP>(value); }
    static auto ReadTIM3_REMAP() noexcept -> ValueType { return Reg::Read<F_TIM3_REMAP>(); }
    static void WriteTIM3_REMAP(ValueType value) noexcept { Reg::Write<F_TIM3_REMAP>(value); }
    static auto ReadTIM4_REMAP() noexcept -> ValueType { return Reg::Read<F_TIM4_REMAP>(); }
    static void WriteTIM4_REMAP(ValueType value) noexcept { Reg::Write<F_TIM4_REMAP>(value); }
    static auto ReadCAN_REMAP() noexcept -> ValueType { return Reg::Read<F_CAN_REMAP>(); }
    static void WriteCAN_REMAP(ValueType value) noexcept { Reg::Write<F_CAN_REMAP>(value); }
    static auto ReadPD01_REMAP() noexcept -> ValueType { return Reg::Read<F_PD01_REMAP>(); }
    static void WritePD01_REMAP(ValueType value) noexcept { Reg::Write<F_PD01_REMAP>(value); }
    static auto ReadTIM5CH4_IREMAP() noexcept -> ValueType { return Reg::Read<F_TIM5CH4_IREMAP>(); }
    static void WriteTIM5CH4_IREMAP(ValueType value) noexcept { Reg::Write<F_TIM5CH4_IREMAP>(value); }
    static auto ReadADC1_ETRGINJ_REMAP() noexcept -> ValueType { return Reg::Read<F_ADC1_ETRGINJ_REMAP>(); }
    static void WriteADC1_ETRGINJ_REMAP(ValueType value) noexcept { Reg::Write<F_ADC1_ETRGINJ_REMAP>(value); }
    static auto ReadADC1_ETRGREG_REMAP() noexcept -> ValueType { return Reg::Read<F_ADC1_ETRGREG_REMAP>(); }
    static void WriteADC1_ETRGREG_REMAP(ValueType value) noexcept { Reg::Write<F_ADC1_ETRGREG_REMAP>(value); }
    static auto ReadADC2_ETRGINJ_REMAP() noexcept -> ValueType { return Reg::Read<F_ADC2_ETRGINJ_REMAP>(); }
    static void WriteADC2_ETRGINJ_REMAP(ValueType value) noexcept { Reg::Write<F_ADC2_ETRGINJ_REMAP>(value); }
    static auto ReadADC2_ETRGREG_REMAP() noexcept -> ValueType { return Reg::Read<F_ADC2_ETRGREG_REMAP>(); }
    static void WriteADC2_ETRGREG_REMAP(ValueType value) noexcept { Reg::Write<F_ADC2_ETRGREG_REMAP>(value); }
    static void WriteSWJ_CFG(ValueType value) noexcept { Reg::Write<F_SWJ_CFG>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40010004;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_SPI1_REMAP = CortexM3::Field<ValueType, 0, 1>;
    using F_I2C1_REMAP = CortexM3::Field<ValueType, 1, 1>;
    using F_USART1_REMAP = CortexM3::Field<ValueType, 2, 1>;
    using F_USART2_REMAP = CortexM3::Field<ValueType, 3, 1>;
    using F_USART3_REMAP = CortexM3::Field<ValueType, 4, 2>;
    using F_TIM1_REMAP = CortexM3::Field<ValueType, 6, 2>;
    using F_TIM2_REMAP = CortexM3::Field<ValueType, 8, 2>;
    using F_TIM3_REMAP = CortexM3::Field<ValueType, 10, 2>;
    using F_TIM4_REMAP = CortexM3::Field<ValueType, 12, 1>;
    using F_CAN_REMAP = CortexM3::Field<ValueType, 13, 2>;
    using F_PD01_REMAP = CortexM3::Field<ValueType, 15, 1>;
    using F_TIM5CH4_IREMAP = CortexM3::Field<ValueType, 16, 1>;
    using F_ADC1_ETRGINJ_REMAP = CortexM3::Field<ValueType, 17, 1>;
    using F_ADC1_ETRGREG_REMAP = CortexM3::Field<ValueType, 18, 1>;
    using F_ADC2_ETRGINJ_REMAP = CortexM3::Field<ValueType, 19, 1>;
    using F_ADC2_ETRGREG_REMAP = CortexM3::Field<ValueType, 20, 1>;
    using F_SWJ_CFG = CortexM3::Field<ValueType, 24, 3>;
};

class EXTICR1 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEXTI0() noexcept -> ValueType { return Reg::Read<F_EXTI0>(); }
    static void WriteEXTI0(ValueType value) noexcept { Reg::Write<F_EXTI0>(value); }
    static auto ReadEXTI1() noexcept -> ValueType { return Reg::Read<F_EXTI1>(); }
    static void WriteEXTI1(ValueType value) noexcept { Reg::Write<F_EXTI1>(value); }
    static auto ReadEXTI2() noexcept -> ValueType { return Reg::Read<F_EXTI2>(); }
    static void WriteEXTI2(ValueType value) noexcept { Reg::Write<F_EXTI2>(value); }
    static auto ReadEXTI3() noexcept -> ValueType { return Reg::Read<F_EXTI3>(); }
    static void WriteEXTI3(ValueType value) noexcept { Reg::Write<F_EXTI3>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40010008;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EXTI0 = CortexM3::Field<ValueType, 0, 4>;
    using F_EXTI1 = CortexM3::Field<ValueType, 4, 4>;
    using F_EXTI2 = CortexM3::Field<ValueType, 8, 4>;
    using F_EXTI3 = CortexM3::Field<ValueType, 12, 4>;
};

class EXTICR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEXTI4() noexcept -> ValueType { return Reg::Read<F_EXTI4>(); }
    static void WriteEXTI4(ValueType value) noexcept { Reg::Write<F_EXTI4>(value); }
    static auto ReadEXTI5() noexcept -> ValueType { return Reg::Read<F_EXTI5>(); }
    static void WriteEXTI5(ValueType value) noexcept { Reg::Write<F_EXTI5>(value); }
    static auto ReadEXTI6() noexcept -> ValueType { return Reg::Read<F_EXTI6>(); }
    static void WriteEXTI6(ValueType value) noexcept { Reg::Write<F_EXTI6>(value); }
    static auto ReadEXTI7() noexcept -> ValueType { return Reg::Read<F_EXTI7>(); }
    static void WriteEXTI7(ValueType value) noexcept { Reg::Write<F_EXTI7>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001000c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EXTI4 = CortexM3::Field<ValueType, 0, 4>;
    using F_EXTI5 = CortexM3::Field<ValueType, 4, 4>;
    using F_EXTI6 = CortexM3::Field<ValueType, 8, 4>;
    using F_EXTI7 = CortexM3::Field<ValueType, 12, 4>;
};

class EXTICR3 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEXTI8() noexcept -> ValueType { return Reg::Read<F_EXTI8>(); }
    static void WriteEXTI8(ValueType value) noexcept { Reg::Write<F_EXTI8>(value); }
    static auto ReadEXTI9() noexcept -> ValueType { return Reg::Read<F_EXTI9>(); }
    static void WriteEXTI9(ValueType value) noexcept { Reg::Write<F_EXTI9>(value); }
    static auto ReadEXTI10() noexcept -> ValueType { return Reg::Read<F_EXTI10>(); }
    static void WriteEXTI10(ValueType value) noexcept { Reg::Write<F_EXTI10>(value); }
    static auto ReadEXTI11() noexcept -> ValueType { return Reg::Read<F_EXTI11>(); }
    static void WriteEXTI11(ValueType value) noexcept { Reg::Write<F_EXTI11>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40010010;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EXTI8 = CortexM3::Field<ValueType, 0, 4>;
    using F_EXTI9 = CortexM3::Field<ValueType, 4, 4>;
    using F_EXTI10 = CortexM3::Field<ValueType, 8, 4>;
    using F_EXTI11 = CortexM3::Field<ValueType, 12, 4>;
};

class EXTICR4 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadEXTI12() noexcept -> ValueType { return Reg::Read<F_EXTI12>(); }
    static void WriteEXTI12(ValueType value) noexcept { Reg::Write<F_EXTI12>(value); }
    static auto ReadEXTI13() noexcept -> ValueType { return Reg::Read<F_EXTI13>(); }
    static void WriteEXTI13(ValueType value) noexcept { Reg::Write<F_EXTI13>(value); }
    static auto ReadEXTI14() noexcept -> ValueType { return Reg::Read<F_EXTI14>(); }
    static void WriteEXTI14(ValueType value) noexcept { Reg::Write<F_EXTI14>(value); }
    static auto ReadEXTI15() noexcept -> ValueType { return Reg::Read<F_EXTI15>(); }
    static void WriteEXTI15(ValueType value) noexcept { Reg::Write<F_EXTI15>(value); }

private:
    static constexpr std::uintptr_t Address = 0x40010014;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_EXTI12 = CortexM3::Field<ValueType, 0, 4>;
    using F_EXTI13 = CortexM3::Field<ValueType, 4, 4>;
    using F_EXTI14 = CortexM3::Field<ValueType, 8, 4>;
    using F_EXTI15 = CortexM3::Field<ValueType, 12, 4>;
};

class MAPR2 {
public:
    using ValueType = std::uint32_t;
    static constexpr ValueType ResetValue = 0x00000000;
    
    static auto Read() noexcept -> ValueType { return Reg::Read(); }
    static void Write(ValueType value) noexcept { Reg::Write(value); }
    static auto ReadTIM9_REMAP() noexcept -> ValueType { return Reg::Read<F_TIM9_REMAP>(); }
    static void WriteTIM9_REMAP(ValueType value) noexcept { Reg::Write<F_TIM9_REMAP>(value); }
    static auto ReadTIM10_REMAP() noexcept -> ValueType { return Reg::Read<F_TIM10_REMAP>(); }
    static void WriteTIM10_REMAP(ValueType value) noexcept { Reg::Write<F_TIM10_REMAP>(value); }
    static auto ReadTIM11_REMAP() noexcept -> ValueType { return Reg::Read<F_TIM11_REMAP>(); }
    static void WriteTIM11_REMAP(ValueType value) noexcept { Reg::Write<F_TIM11_REMAP>(value); }
    static auto ReadTIM13_REMAP() noexcept -> ValueType { return Reg::Read<F_TIM13_REMAP>(); }
    static void WriteTIM13_REMAP(ValueType value) noexcept { Reg::Write<F_TIM13_REMAP>(value); }
    static auto ReadTIM14_REMAP() noexcept -> ValueType { return Reg::Read<F_TIM14_REMAP>(); }
    static void WriteTIM14_REMAP(ValueType value) noexcept { Reg::Write<F_TIM14_REMAP>(value); }
    static auto ReadFSMC_NADV() noexcept -> ValueType { return Reg::Read<F_FSMC_NADV>(); }
    static void WriteFSMC_NADV(ValueType value) noexcept { Reg::Write<F_FSMC_NADV>(value); }

private:
    static constexpr std::uintptr_t Address = 0x4001001c;
    using Reg = CortexM3::Register<ValueType, Address>;
    using F_TIM9_REMAP = CortexM3::Field<ValueType, 5, 1>;
    using F_TIM10_REMAP = CortexM3::Field<ValueType, 6, 1>;
    using F_TIM11_REMAP = CortexM3::Field<ValueType, 7, 1>;
    using F_TIM13_REMAP = CortexM3::Field<ValueType, 8, 1>;
    using F_TIM14_REMAP = CortexM3::Field<ValueType, 9, 1>;
    using F_FSMC_NADV = CortexM3::Field<ValueType, 10, 1>;
};

} // namespace STM32F103::AFIO
