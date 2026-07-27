/**
 * @file    Interrupts.cpp
 * @brief   ISR 桩函数 — 由 Vectors.cpp 中的中断向量表跳转
 *
 * 强定义覆盖 Vectors.cpp 中的 weak 默认处理（Default_Handler）
 */

#include <hal/ADC.hpp>
#include <hal/I2C.hpp>
#include <hal/TIM.hpp>
#include <hal/UART.hpp>
#include <platform/SysTick.hpp>

extern "C" {

/**
 * @brief SysTick 中断（1ms 时基）
 */
void SysTick_Handler() {
    Platform::SysTick_::onTick();
}

/**
 * @brief USART1 中断（IDLE + TXE）
 */
void USART1_IRQHandler() {
    HAL::UART::onInterrupt();
}

/**
 * @brief DMA1 Channel5 中断（USART1 RX half/full/error）
 */
void DMA1_Channel5_IRQHandler() {
    HAL::UART::onRxDMA();
}

/**
 * @brief TIM4 中断（PWM UPDATE，泵脉冲计数）
 */
void TIM4_IRQHandler() {
    HAL::TIM::onUpdate();
}

/**
 * @brief ADC1_2 中断（EOC）
 */
void ADC1_2_IRQHandler() {
    HAL::ADC::onConvCplt();
}

/**
 * @brief I2C1 事件中断
 */
void I2C1_EV_IRQHandler() {
    HAL::I2C::onEvent();
}

/**
 * @brief I2C1 错误中断
 */
void I2C1_ER_IRQHandler() {
    HAL::I2C::onError();
}

} // extern "C"
