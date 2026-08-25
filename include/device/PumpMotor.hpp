/**
 * @file    PumpMotor.hpp
 * @brief   蠕动泵驱动（模板化，按 TIM4 通道区分）
 */

#pragma once

#include <hal/TIM.hpp>
#include <cstdint>

namespace Device {

/**
 * @brief 泵运行模式
 */
enum class PumpMode : uint8_t {
    MaxCount, /** 达到脉冲上限后自动停止 */
    FreeRun,  /** 不显式调用 stop() 不停止 */
};

/**
 * @brief 蠕动泵驱动
 *
 * 模板化，按 TIM4 通道区分
 * PWM 脉冲由 TIM4 硬件生成，UPDATE 中断计数
 *
 * @tparam Channel  TIM4 通道号（1 或 2）
 * @tparam ReportEvery  每 N 脉冲标记一次进度上报
 */
template <uint32_t Channel, uint16_t ReportEvery = 1000>
class PumpMotor {
    static_assert(Channel == 1 || Channel == 2, "Channel 必须是 1 或 2");

public:
    /**
     * @brief 初始化（配置 TIM4 PWM，但不启动脉冲）
     * @param hz PWM 频率（Hz）
     */
    static void initialize(uint16_t hz = 1000) noexcept {
        HAL::TIM::initTIM4(hz);
        HAL::TIM::setUpdateCallback(Channel - 1, &onTick);
        g_initialized = true;
    }

    /**
     * @brief 启动泵
     * @param mode 运行模式
     * @param maxCount 最大脉冲数（仅 MaxCount 模式有效）
     */
    static void start(PumpMode mode, uint32_t maxCount = 0) noexcept {
        if (g_running) stop();
        uint32_t primask = disableIrqSave();
        g_mode = mode;
        g_maxCount = maxCount;
        g_count = 0;
        g_done = false;
        g_reportPending = false;
        g_running = true;

        HAL::TIM::startPWM(Channel);
        HAL::TIM::enableTIM4();
        HAL::TIM::enableUpdateIRQ();
        restoreIrq(primask);
    }

    /**
     * @brief 停止泵
     */
    static void stop() noexcept {
        uint32_t primask = disableIrqSave();
        if (!g_running) {
            restoreIrq(primask);
            return;
        }
        g_running = false;
        HAL::TIM::stopPWM(Channel);
        /** UPDATE 中断和主计数器由两个通道共享，仅在全部停止后关闭。 */
        if constexpr (Channel == 1) {
            if (!PumpMotor<2>::isRunning()) {
                HAL::TIM::disableUpdateIRQ();
                HAL::TIM::disableTIM4();
            }
        } else {
            if (!PumpMotor<1>::isRunning()) {
                HAL::TIM::disableUpdateIRQ();
                HAL::TIM::disableTIM4();
            }
        }
        restoreIrq(primask);
    }

    /**
     * @brief 查询泵是否运行中
     * @return true=运行中
     */
    static bool isRunning() noexcept { return g_running; }

    /**
     * @brief 查询泵是否完成（MaxCount 模式达到上限）
     * @return true=完成
     */
    static bool isDone() noexcept { return g_done; }

    /**
     * @brief 清除完成标志
     */
    static void clearDone() noexcept { g_done = false; }

    /**
     * @brief 查询是否有进度上报待发送
     * @return true=有进度待上报
     */
    static bool isReportPending() noexcept { return g_reportPending; }

    /**
     * @brief 清除进度上报标志
     */
    static void clearReport() noexcept { g_reportPending = false; }

    /**
     * @brief 获取当前脉冲计数
     * @return 脉冲计数
     */
    static uint32_t getPosition() noexcept { return g_count; }

    /**
     * @brief 重置脉冲计数
     */
    static void resetPosition() noexcept { g_count = 0; }

    /**
     * @brief TIM4 UPDATE 中断回调（由 HAL::TIM::onUpdate → setUpdateCallback 调用）
     */
    static void onTick() noexcept {
        if (!g_running) return;
        uint32_t c = g_count;
        g_count = c + 1;
        if ((c % ReportEvery) == 0) {
            g_reportPending = true;
        }
        if (g_mode == PumpMode::MaxCount && g_count >= g_maxCount) {
            g_done = true;
            stop();
        }
    }

    PumpMotor() = delete;

private:
    static uint32_t disableIrqSave() noexcept {
        uint32_t primask;
        __asm volatile("mrs %0, primask\n\tcpsid i"
                       : "=r"(primask)
                       :
                       : "memory");
        return primask;
    }

    static void restoreIrq(uint32_t primask) noexcept {
        __asm volatile("msr primask, %0" : : "r"(primask) : "memory");
    }

    inline static volatile bool g_running{false};
    inline static volatile bool g_done{false};
    inline static volatile bool g_reportPending{false};
    inline static volatile bool g_initialized{false};
    inline static volatile PumpMode g_mode{PumpMode::FreeRun};
    inline static volatile uint32_t g_maxCount{0};
    inline static volatile uint32_t g_count{0};
};

/** 泵 1（TIM4 CH1, PB6） */
using PumpMotor1 = PumpMotor<1>;
/** 泵 2（TIM4 CH2, PB7） */
using PumpMotor2 = PumpMotor<2>;

} // namespace Device
