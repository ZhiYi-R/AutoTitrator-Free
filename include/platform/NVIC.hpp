/**
 * @file    NVIC.hpp
 * @brief   NVIC 辅助：优先级分组、使能/禁用 IRQ、设置优先级、系统复位
 */

#pragma once

#include <cortex-m3/Control.hpp>
#include <cortex-m3/NVIC.hpp>
#include <cstdint>

namespace Platform {

/**
 * @brief NVIC 辅助工具
 *
 * 提供优先级分组、使能/禁用 IRQ、设置优先级、系统复位等功能
 */
class NVIC_ {
public:
    /**
     * @brief IRQ 编号（STM32F103 medium-density，外设 IRQ 从 0 开始）
     */
    enum class IRQn : uint8_t {
        WWDG = 0,
        PVD = 1,
        TAMPER = 2,
        RTC = 3,
        FLASH = 4,
        RCC = 5,
        EXTI0 = 6,
        EXTI1 = 7,
        EXTI2 = 8,
        EXTI3 = 9,
        EXTI4 = 10,
        DMA1_Channel1 = 11,
        DMA1_Channel2 = 12,
        DMA1_Channel3 = 13,
        DMA1_Channel4 = 14,
        DMA1_Channel5 = 15,
        DMA1_Channel6 = 16,
        DMA1_Channel7 = 17,
        ADC1_2 = 18,
        USB_HP_CAN1_TX = 19,
        USB_LP_CAN1_RX0 = 20,
        CAN1_RX1 = 21,
        CAN1_SCE = 22,
        EXTI9_5 = 23,
        TIM1_BRK = 24,
        TIM1_UP = 25,
        TIM1_TRG_COM = 26,
        TIM1_CC = 27,
        TIM2 = 28,
        TIM3 = 29,
        TIM4 = 30,
        I2C1_EV = 31,
        I2C1_ER = 32,
        I2C2_EV = 33,
        I2C2_ER = 34,
        SPI1 = 35,
        SPI2 = 36,
        USART1 = 37,
        USART2 = 38,
        USART3 = 39,
        EXTI15_10 = 40,
        RTCAlarm = 41,
        USBWakeUp = 42,
    };

    /**
     * @brief 设置优先级分组（AIRCR.PRIGROUP）
     * @param group 分组编号，group=0 → 4 位抢占 / 0 位子优先级（16 级抢占）
     */
    static void setPriorityGrouping(uint32_t group) noexcept {
        /** AIRCR 写入需要 VECTKEY = 0x5FA */
        auto v = CortexM3::Control::AIRCR::Read();
        v &= ~(0x7u << 8);          /** 清 PRIGROUP */
        v |= (group & 0x7) << 8;    /** 设 PRIGROUP */
        v |= (0x5FAu << 16);        /** VECTKEY */
        CortexM3::Control::AIRCR::Write(v);
    }

    /**
     * @brief 使能指定 IRQ
     * @param irqn IRQ 编号
     */
    static void enableIRQ(IRQn irqn) noexcept {
        uint8_t n = static_cast<uint8_t>(irqn);
        if (n < 32) {
            CortexM3::NVIC::NVIC_ISER0::WriteSETENA(1u << n);
        } else {
            CortexM3::NVIC::NVIC_ISER1::WriteSETENA(1u << (n - 32));
        }
    }

    /**
     * @brief 禁用指定 IRQ
     * @param irqn IRQ 编号
     */
    static void disableIRQ(IRQn irqn) noexcept {
        uint8_t n = static_cast<uint8_t>(irqn);
        if (n < 32) {
            CortexM3::NVIC::NVIC_ICER0::WriteCLRENA(1u << n);
        } else {
            CortexM3::NVIC::NVIC_ICER1::WriteCLRENA(1u << (n - 32));
        }
    }

    /**
     * @brief 设置 IRQ 优先级（0=最高, 15=最低，PRIGROUP=0 时纯抢占）
     * @param irqn IRQ 编号
     * @param priority 优先级（0-15），STM32F103 只用高 4 位，左移 4 位写入 IPR
     */
    static void setPriority(IRQn irqn, uint8_t priority) noexcept {
        uint8_t n = static_cast<uint8_t>(irqn);
        uint8_t regIdx = n / 4;
        uint8_t byteIdx = n % 4;
        uint8_t shifted = (priority & 0x0F) << 4;

        /** IPR 寄存器每个 32 位存 4 个 IRQ，按字节位置写入 */
        /** 使用 RMW 方式只改目标字节 */
        using namespace CortexM3::NVIC;
        uint32_t mask = 0xFFu << (byteIdx * 8);
        uint32_t val = static_cast<uint32_t>(shifted) << (byteIdx * 8);

        /** 选择对应 IPR 寄存器（regIdx 0-14 覆盖 60 个 IRQ） */
        switch (regIdx) {
        case 0: NVIC_IPR0::Write((NVIC_IPR0::Read() & ~mask) | val); break;
        case 1: NVIC_IPR1::Write((NVIC_IPR1::Read() & ~mask) | val); break;
        case 2: NVIC_IPR2::Write((NVIC_IPR2::Read() & ~mask) | val); break;
        case 3: NVIC_IPR3::Write((NVIC_IPR3::Read() & ~mask) | val); break;
        case 4: NVIC_IPR4::Write((NVIC_IPR4::Read() & ~mask) | val); break;
        case 5: NVIC_IPR5::Write((NVIC_IPR5::Read() & ~mask) | val); break;
        case 6: NVIC_IPR6::Write((NVIC_IPR6::Read() & ~mask) | val); break;
        case 7: NVIC_IPR7::Write((NVIC_IPR7::Read() & ~mask) | val); break;
        case 8: NVIC_IPR8::Write((NVIC_IPR8::Read() & ~mask) | val); break;
        case 9: NVIC_IPR9::Write((NVIC_IPR9::Read() & ~mask) | val); break;
        case 10: NVIC_IPR10::Write((NVIC_IPR10::Read() & ~mask) | val); break;
        case 11: NVIC_IPR11::Write((NVIC_IPR11::Read() & ~mask) | val); break;
        case 12: NVIC_IPR12::Write((NVIC_IPR12::Read() & ~mask) | val); break;
        case 13: NVIC_IPR13::Write((NVIC_IPR13::Read() & ~mask) | val); break;
        case 14: NVIC_IPR14::Write((NVIC_IPR14::Read() & ~mask) | val); break;
        default: break;
        }
    }

    /**
     * @brief 触发系统复位（AIRCR.SYSRESETREQ）
     */
    static void systemReset() noexcept {
        auto v = CortexM3::Control::AIRCR::Read();
        v |= (0x5FAu << 16);    /** VECTKEY */
        v |= (1u << 2);         /** SYSRESETREQ */
        CortexM3::Control::AIRCR::Write(v);
        while (true) {
            /** 等待复位 */
        }
    }

    NVIC_() = delete;
};

} // namespace Platform
