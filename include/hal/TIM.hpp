/**
 * @file    TIM.hpp
 * @brief   定时器驱动（TIM3 ADC 触发时基 + TIM4 双通道 PWM）
 */

#pragma once

#include <hal/GPIO.hpp>
#include <platform/NVIC.hpp>
#include <stm32f103/RCC.hpp>
#include <stm32f103/TIM3.hpp>
#include <stm32f103/TIM4.hpp>
#include <cstdint>

namespace HAL {

/**
 * @brief 定时器驱动
 *
 * TIM3 — ADC 触发时基（TRGO = Update）
 * TIM4 — 双通道 PWM（CH1=PB6, CH2=PB7）用于蠕动泵脉冲
 */
class TIM {
public:
    /** ====================================================================== */
    /**  TIM3: ADC 触发时基                                                     */
    /** ====================================================================== */

    /**
     * @brief 初始化 TIM3 为指定频率的时基，TRGO=Update
     * @param hz 触发频率（Hz）
     *
     * APB1 定时器时钟 = 72MHz（APB1 prescaler=2 时自动 ×2）
     */
    static void initTIM3(uint32_t hz) noexcept {
        using namespace STM32F103;
        RCC::APB1ENR::WriteTIM3EN(1);

        uint32_t psc = 72 - 1; /** 72MHz / 72 = 1MHz 计数 */
        uint32_t arr = (1000000u / hz) - 1;
        if (arr < 1) arr = 1;

        TIM3::CR1::Write(0);
        TIM3::PSC::Write(psc);
        TIM3::ARR::Write(arr);
        TIM3::CR1::WriteARPE(1); /** ARR 预装载 */
        /** TRGO = Update 事件 (MMS=010) */
        TIM3::CR2::WriteMMS(2);
        /** 产生更新事件加载 PSC/ARR */
        TIM3::EGR::WriteUG(1);
    }

    /**
     * @brief 启动 TIM3
     */
    static void startTIM3() noexcept { STM32F103::TIM3::CR1::WriteCEN(1); }

    /**
     * @brief 停止 TIM3
     */
    static void stopTIM3() noexcept { STM32F103::TIM3::CR1::WriteCEN(0); }

    /** ====================================================================== */
    /**  TIM4: 双通道 PWM（泵脉冲）                                             */
    /** ====================================================================== */

    /**
     * @brief 初始化 TIM4 为指定 PWM 频率，CH1/CH2 配置为 PWM1 50% 占空比
     * @param pwmHz PWM 频率（Hz）
     *
     * 引脚：PB6(CH1), PB7(CH2)
     */
    static void initTIM4(uint32_t pwmHz) noexcept {
        using namespace STM32F103;
        RCC::APB1ENR::WriteTIM4EN(1);
        RCC::APB2ENR::WriteIOPBEN(1);
        RCC::APB2ENR::WriteAFIOEN(1);

        /** PB6, PB7 = AF_PP */
        GPIO::configure(GPIO::Port::B, 6, GPIO::Mode::AfPP, GPIO::Pull::None,
                        GPIO::Speed::MHz50);
        GPIO::configure(GPIO::Port::B, 7, GPIO::Mode::AfPP, GPIO::Pull::None,
                        GPIO::Speed::MHz50);

        uint32_t psc = 72 - 1; /** 1MHz 计数 */
        uint32_t arr = (1000000u / pwmHz) - 1;
        if (arr < 1) arr = 1;

        TIM4::CR1::Write(0);
        TIM4::PSC::Write(psc);
        TIM4::ARR::Write(arr);
        TIM4::CR1::WriteARPE(1); /** ARR 预装载 */

        /** CH1: PWM1, 预装载使能 */
        TIM4::CCMR1_Output::WriteOC1M(6); /** PWM mode 1 (0b110) */
        TIM4::CCMR1_Output::WriteOC1PE(1);
        /** CH2: PWM1, 预装载使能 */
        TIM4::CCMR1_Output::WriteOC2M(6);
        TIM4::CCMR1_Output::WriteOC2PE(1);

        /** 默认 50% 占空比 */
        uint32_t ccr = (arr + 1) / 2;
        TIM4::CCR1::WriteCCR1(ccr);
        TIM4::CCR2::WriteCCR2(ccr);

        /** 使能 CH1/CH2 输出 */
        TIM4::CCER::WriteCC1E(1);
        TIM4::CCER::WriteCC2E(1);

        /** 产生更新事件加载 PSC/ARR/CCR */
        TIM4::EGR::WriteUG(1);

        /** NVIC: TIM4 优先级 1 */
        Platform::NVIC_::setPriority(Platform::NVIC_::IRQn::TIM4, 1);
        Platform::NVIC_::enableIRQ(Platform::NVIC_::IRQn::TIM4);
    }

    /**
     * @brief 启动 PWM 通道
     * @param channel 通道号（1 或 2）
     */
    static void startPWM(uint32_t channel) noexcept {
        if (channel == 1) STM32F103::TIM4::CCER::WriteCC1E(1);
        if (channel == 2) STM32F103::TIM4::CCER::WriteCC2E(1);
    }

    /**
     * @brief 停止 PWM 通道
     * @param channel 通道号（1 或 2）
     */
    static void stopPWM(uint32_t channel) noexcept {
        if (channel == 1) STM32F103::TIM4::CCER::WriteCC1E(0);
        if (channel == 2) STM32F103::TIM4::CCER::WriteCC2E(0);
    }

    /**
     * @brief 使能 TIM4 主计数器
     */
    static void enableTIM4() noexcept { STM32F103::TIM4::CR1::WriteCEN(1); }

    /**
     * @brief 禁用 TIM4 主计数器
     */
    static void disableTIM4() noexcept { STM32F103::TIM4::CR1::WriteCEN(0); }

    /**
     * @brief 使能 TIM4 UPDATE 中断
     */
    static void enableUpdateIRQ() noexcept {
        STM32F103::TIM4::SR::WriteUIF(0); /** 清标志 */
        STM32F103::TIM4::DIER::WriteUIE(1);
    }

    /**
     * @brief 禁用 TIM4 UPDATE 中断
     */
    static void disableUpdateIRQ() noexcept { STM32F103::TIM4::DIER::WriteUIE(0); }

    /**
     * @brief 清 TIM4 UPDATE 标志
     */
    static void clearUpdateFlag() noexcept { STM32F103::TIM4::SR::WriteUIF(0); }

    /**
     * @brief 设置 TIM4 频率（运行时修改，修改后产生 UG 事件加载）
     * @param hz PWM 频率（Hz）
     */
    static void setTIM4Freq(uint32_t hz) noexcept {
        if (hz < 1) hz = 1;
        if (hz > 500000) hz = 500000;
        uint32_t arr = (1000000u / hz) - 1;
        if (arr < 1) arr = 1;
        STM32F103::TIM4::ARR::Write(arr);
        uint32_t ccr = (arr + 1) / 2;
        STM32F103::TIM4::CCR1::WriteCCR1(ccr);
        STM32F103::TIM4::CCR2::WriteCCR2(ccr);
        STM32F103::TIM4::EGR::WriteUG(1);
    }

    /**
     * @brief TIM4 UPDATE 中断回调（由 TIM4_IRQHandler 调用）
     *
     * 调用用户注册的 onUpdate 回调
     */
    static void onUpdate() noexcept {
        if (STM32F103::TIM4::SR::ReadUIF() != 0) {
            STM32F103::TIM4::SR::WriteUIF(0);
            if (g_updateCallback != nullptr) {
                g_updateCallback();
            }
        }
    }

    /**
     * @brief UPDATE 回调函数指针类型
     */
    using UpdateCallback = void (*)();

    /**
     * @brief 注册 UPDATE 回调
     * @param cb 回调函数
     */
    static void setUpdateCallback(UpdateCallback cb) noexcept {
        g_updateCallback = cb;
    }

    TIM() = delete;

private:
    inline static UpdateCallback g_updateCallback{nullptr};
};

} // namespace HAL
