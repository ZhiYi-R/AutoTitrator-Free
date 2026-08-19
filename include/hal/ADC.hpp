/**
 * @file    ADC.hpp
 * @brief   ADC1 驱动（TIM3_TRGO 触发，单通道 CH0 / PA0，EOC 中断）
 */

#pragma once

#include <hal/GPIO.hpp>
#include <platform/NVIC.hpp>
#include <platform/SysTick.hpp>
#include <stm32f103/ADC1.hpp>
#include <stm32f103/RCC.hpp>
#include <cstdint>

namespace HAL {

/**
 * @brief ADC1 驱动
 *
 * TIM3_TRGO 触发，单通道 CH0 (PA0)，EOC 中断
 */
class ADC {
public:
    /**
     * @brief 初始化 ADC1：PA0 模拟输入，TIM3_TRGO 触发，右对齐，1.5 cycle 采样
     */
    static void initialize() noexcept {
        using namespace STM32F103;

        /** 时钟 + GPIO */
        RCC::APB2ENR::WriteADC1EN(1);
        RCC::APB2ENR::WriteIOPAEN(1);
        GPIO::configure(GPIO::Port::A, 0, GPIO::Mode::InputAnalog);

        /** ADC 上电 */
        ADC1::CR2::WriteADON(1);
        Platform::SysTick_::delayMs(1); /** ADC 上电稳定 */

        /** 校准 */
        ADC1::CR2::WriteRSTCAL(1);
        while (ADC1::CR2::ReadRSTCAL() != 0) {}
        ADC1::CR2::WriteCAL(1);
        while (ADC1::CR2::ReadCAL() != 0) {}

        /** 配置：单通道、右对齐、单次转换、TIM3_TRGO 触发 */
        ADC1::CR1::WriteSCAN(0);       /** 非扫描模式 */
        ADC1::CR2::WriteCONT(0);       /** 单次转换 */
        ADC1::CR2::WriteALIGN(0);      /** 右对齐 */
        ADC1::CR2::WriteEXTTRIG(1);    /** 外部触发使能 */
        ADC1::CR2::WriteEXTSEL(4);     /** TIM3_TRGO (0b100)；000=TIM1_CC1 */

        /** 通道 0 采样时间 1.5 cycle (SMPR2.SMP0 = 0b000) */
        ADC1::SMPR2::Write(0); /** 全部 1.5 cycle */

        /** 规则组：1 个转换，SQ1 = channel 0 */
        ADC1::SQR1::WriteL(0);         /** L = 0 → 1 个转换 */
        ADC1::SQR3::WriteSQ1(0);       /** SQ1 = channel 0 */

        /** EOC 中断使能 */
        ADC1::CR1::WriteEOCIE(1);

        /** NVIC：ADC1_2 优先级 2 */
        Platform::NVIC_::setPriority(Platform::NVIC_::IRQn::ADC1_2, 2);
        Platform::NVIC_::enableIRQ(Platform::NVIC_::IRQn::ADC1_2);

        g_initialized = true;
    }

    /**
     * @brief 启动一次转换（等待 TIM3 触发）
     *
     * TIM3_TRGO 会自动触发；也可 SWSTART 软件触发
     * 这里依赖 TIM3 TRGO，无需额外操作
     */
    static void startConversion() noexcept {
    }

    /**
     * @brief 读取数据寄存器
     * @return ADC 转换结果（12 位右对齐）
     */
    static uint16_t readDR() noexcept {
        return static_cast<uint16_t>(STM32F103::ADC1::DR::ReadDATA());
    }

    /**
     * @brief EOC 中断回调（由 ADC1_2_IRQHandler 调用）
     */
    static void onConvCplt() noexcept {
        if (STM32F103::ADC1::SR::ReadEOC() != 0) {
            uint16_t v = readDR();
            if (g_convCallback != nullptr) {
                g_convCallback(v);
            }
        }
    }

    /**
     * @brief 转换完成回调函数指针类型
     * @param value ADC 转换结果
     */
    using ConvCallback = void (*)(uint16_t);

    /**
     * @brief 注册转换完成回调
     * @param cb 回调函数
     */
    static void setConvCallback(ConvCallback cb) noexcept {
        g_convCallback = cb;
    }

    ADC() = delete;

private:
    inline static ConvCallback g_convCallback{nullptr};
    inline static bool g_initialized{false};
};

} // namespace HAL
