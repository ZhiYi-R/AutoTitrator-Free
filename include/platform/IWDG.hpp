/**
 * @file    IWDG.hpp
 * @brief   独立看门狗驱动（LSI ~40kHz，超时 ~5s）
 *
 * IWDG 一旦使能无法关闭；只能周期性喂狗，直到复位。
 * 超时计算：T = (RLR + 1) × prescaler / 40000
 *   prescaler=64（PR=4），RLR=3124 → T = 3125 × 64 / 40000 = 5.0s
 */

#pragma once

#include <stm32f103/IWDG.hpp>
#include <cstdint>

namespace Platform {

/**
 * @brief 独立看门狗驱动
 *
 * LSI ~40kHz，预分频 64，重载 3124 → 超时 ~5s
 * 一旦 initialize() 调用后看门狗永久使能，必须周期性调用 reload()
 */
class IWDG_ {
public:
    /** IWDG 预分频寄存器值（64 分频） */
    static constexpr uint8_t PRESCALER = 4;
    /** 重载值：5s 超时 = 3125 × 64 / 40000 */
    static constexpr uint16_t RELOAD = 3124;

    /** IWDG 启动密钥 */
    static constexpr uint16_t KEY_START = 0xCCCC;
    /** IWDG 喂狗密钥 */
    static constexpr uint16_t KEY_RELOAD = 0xAAAA;
    /** IWDG 寄存器写使能密钥 */
    static constexpr uint16_t KEY_WRITE_ACCESS = 0x5555;

    /** 同步等待上限，防止低速/异常时钟域永久阻塞启动 */
    static constexpr uint32_t SYNC_TIMEOUT = 1000000;

    /** 初始化失败标志，可由调试器或诊断代码读取 */
    inline static volatile bool g_initFailed{false};

    /**
     * @brief 初始化并启动独立看门狗（~5s 超时）
     *
     * 一旦启动后看门狗无法关闭，必须周期性调用 reload() 喂狗。
     * 超时未喂狗将触发系统复位。
     */
    static void initialize() noexcept {
        using namespace STM32F103;

        /** 启动 IWDG 以启动其独立 LSI 时钟域。 */
        IWDG::KR::Write(KEY_START);
        IWDG::KR::Write(KEY_WRITE_ACCESS);

        /** 设置预分频（等待 PVU 清除） */
        IWDG::PR::WritePR(PRESCALER);
        uint32_t timeout = SYNC_TIMEOUT;
        while (IWDG::SR::ReadPVU() != 0 && timeout-- != 0) {
        }
        if (IWDG::SR::ReadPVU() != 0) {
            g_initFailed = true;
            return;
        }

        /** 设置重载值（等待 RVU 清除） */
        IWDG::RLR::WriteRL(RELOAD);
        timeout = SYNC_TIMEOUT;
        while (IWDG::SR::ReadRVU() != 0 && timeout-- != 0) {
        }
        if (IWDG::SR::ReadRVU() != 0) {
            g_initFailed = true;
            return;
        }

        /** 首次喂狗，加载计数器 */
        IWDG::KR::Write(KEY_RELOAD);
    }

    /**
     * @brief 返回初始化是否因时钟域同步失败
     */
    static auto initFailed() noexcept -> bool {
        return g_initFailed;
    }

    /**
     * @brief 喂狗（重载计数器，必须在超时前调用）
     */
    static void reload() noexcept {
        STM32F103::IWDG::KR::Write(KEY_RELOAD);
    }

    IWDG_() = delete;
};

} // namespace Platform
