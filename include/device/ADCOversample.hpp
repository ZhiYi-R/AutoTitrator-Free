/**
 * @file    ADCOversample.hpp
 * @brief   ADC 软件过采样驱动（256 次累加 → 16-bit 结果）
 */

#pragma once

#include <hal/ADC.hpp>
#include <hal/TIM.hpp>
#include <cstdint>

namespace Device {

/**
 * @brief ADC 软件过采样驱动
 *
 * 256 次采样累加 → sum >> 4 得到 16-bit 结果（等效提升 2 位分辨率）
 * 由 TIM3 定时触发 ADC，EOC 中断累加
 */
class ADCOversample {
public:
    /** 过采样次数 */
    static constexpr uint16_t OVERSAMPLE = 256;
    /** 右移位数：log2(256) - 4 = 4，压回 16-bit */
    static constexpr uint8_t SHIFT = 4;

    /**
     * @brief 过采样结果
     */
    struct Result {
        uint32_t sum;     /** 256 次采样累加和 */
        uint16_t samples; /** 实际采样次数 */
        uint8_t shift;    /** 右移位数 */
    };

    /**
     * @brief 初始化：配置 ADC + 启动 TIM3 触发
     */
    static void initialize() noexcept {
        HAL::ADC::initialize();
        HAL::ADC::setConvCallback(&onConvCplt);
        HAL::TIM::initTIM3(1000); /** 1kHz 触发 */
        HAL::TIM::startTIM3();
        g_ready = true;
        startMeasurement();
    }

    /**
     * @brief 主循环服务（空操作，中断驱动）
     */
    static void service() noexcept {}

    /**
     * @brief 查询是否就绪
     * @return true=就绪
     */
    static bool isReady() noexcept { return g_ready; }

    /**
     * @brief 查询数据是否就绪
     * @return true=数据就绪
     */
    static bool isDataReady() noexcept { return g_dataReady; }

    /**
     * @brief 启动一轮过采样
     */
    static void startMeasurement() noexcept {
        g_dataReady = false;
        g_acc = 0;
        g_count = 0;
    }

    /**
     * @brief 读取结果并自动续采
     * @return 过采样结果
     */
    static Result readData() noexcept {
        Result r{g_acc, OVERSAMPLE, SHIFT};
        startMeasurement();
        return r;
    }

    /**
     * @brief 归一化结果（sum >> shift → 16-bit）
     * @return 16-bit 归一化结果
     */
    static uint16_t readNormalized() noexcept {
        return static_cast<uint16_t>(g_acc >> SHIFT);
    }

    /**
     * @brief ADC EOC 中断回调
     * @param value ADC 转换结果
     */
    static void onConvCplt(uint16_t value) noexcept {
        if (!g_ready) return;
        if (g_dataReady) return;  /** 已就绪：停止累加，等主循环读取后续采 */
        g_acc = g_acc + value;
        g_count = g_count + 1;
        if (g_count >= OVERSAMPLE) {
            g_dataReady = true;
        }
    }

    ADCOversample() = delete;

private:
    inline static volatile bool g_ready{false};
    inline static volatile bool g_dataReady{false};
    inline static volatile uint32_t g_acc{0};
    inline static volatile uint16_t g_count{0};
};

} // namespace Device
