/**
 * @file    SysTick.hpp
 * @brief   1ms 时基（SysTick，AHB 72MHz / 72000 = 1kHz）
 */

#pragma once

#include <cortex-m3/Control.hpp>
#include <cortex-m3/SysTick.hpp>
#include <cstdint>

namespace Platform {

/**
 * @brief 1ms 时基驱动
 *
 * SysTick 定时器，AHB 72MHz / 72000 = 1kHz
 * 优先级最低（15），可被任何中断抢占
 */
class SysTick_ {
public:
    /**
     * @brief 初始化 SysTick 定时器
     */
    static void initialize() noexcept {
        /** AHB 72MHz → RELOAD = 72000 - 1 → 1ms 中断 */
        CortexM3::SysTick::STRVR::WriteRELOAD(72000 - 1);
        CortexM3::SysTick::STCVR::WriteCURRENT(0);
        /** 系统异常优先级 15（最低），避免抢占 I2C/TIM4 关键时序 */
        CortexM3::Control::SHPR3::WritePRI_15(0xF0);
        /** CLKSOURCE=1 (AHB), TICKINT=1 (中断), ENABLE=1 */
        CortexM3::SysTick::STCSR::Write(0x00000007);
    }

    /**
     * @brief 获取毫秒计数（原子读，32 位回绕周期 49.7 天）
     * @return 当前毫秒计数值
     */
    static uint32_t tickMs() noexcept { return g_tickCount; }

    /**
     * @brief 计算从 since 到现在经过的毫秒数（无符号减法处理回绕）
     * @param since 起始时间戳
     * @return 经过的毫秒数
     */
    static uint32_t elapsed(uint32_t since) noexcept {
        return g_tickCount - since;
    }

    /**
     * @brief 阻塞延时（忙等，允许中断打断）
     * @param ms 延时毫秒数
     */
    static void delayMs(uint32_t ms) noexcept {
        uint32_t start = g_tickCount;
        while (elapsed(start) < ms) {
            /** 忙等 */
        }
    }

    /**
     * @brief SysTick 中断回调（由 SysTick_Handler 调用）
     */
    static void onTick() noexcept { g_tickCount = g_tickCount + 1; }

    SysTick_() = delete;

private:
    inline static volatile uint32_t g_tickCount{0};
};

} // namespace Platform
