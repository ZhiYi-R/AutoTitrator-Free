/**
 * @file    AS7341.hpp
 * @brief   AS7341 光谱传感器驱动（两 phase SMUX 扫描状态机）
 */

#pragma once

#include <device/AS7341_Reg.hpp>
#include <hal/I2C.hpp>
#include <platform/SysTick.hpp>
#include <cstdint>

namespace Device {

/**
 * @brief AS7341 光谱传感器驱动
 *
 * I2C 地址 0x39，两 phase SMUX 扫描
 * 初始化用同步 I2C，扫描用异步中断模式
 */
class AS7341 {
public:
    using Reg = Device::AS7341_Reg::Reg;
    using AGain = Device::AS7341_Reg::AGain;
    using SpectralData = Device::AS7341_Reg::SpectralData;

    /**
     * @brief 初始化（同步 I2C，带重试）
     */
    static void initialize() noexcept {
        g_ready = false;
        g_error = false;
        HAL::I2C::initialize();
        HAL::I2C::setCompleteCallback(&onI2CComplete);
        HAL::I2C::setErrorCallback(&onI2CError);

        for (int retry = 0; retry < 3; ++retry) {
            /** 写 ENABLE 寄存器，激活传感器 */
            if (!writeRegSync(+Reg::ENABLE, 0x01)) {
                HAL::I2C::recoverBus();
                continue;
            }
            Platform::SysTick_::delayMs(100);

            /** 验证 */
            uint8_t en{};
            if (!readRegSync(+Reg::ENABLE, &en) || !(en & 0x01)) {
                HAL::I2C::recoverBus();
                continue;
            }

            /** 配置寄存器 */
            if (!writeRegSync(0x00, 0x30)) {
                HAL::I2C::recoverBus();
                continue;
            }
            g_ready = true;
            return;
        }
        g_error = true;
    }

    /**
     * @brief 主循环服务（推进异步扫描状态机）
     */
    static void service() noexcept {
        if (g_i2cBusy) {
            if (Platform::SysTick_::elapsed(g_i2cStartedAt) < I2C_TIMEOUT_MS) return;
            if (HAL::I2C::abortAndRecover()) {
                g_i2cBusy = false;
                g_ioDone = false;
                g_error = true;
            }
        }

        /** I2C 出错：复位状态机，让主循环重新启动新一轮测量 */
        if (g_error) {
            g_error = false;
            g_i2cBusy = false;
            g_ioDone = false;
            g_seq = Sequence::Idle;
            return;
        }

        switch (g_seq) {
        case Sequence::SweepF1F4:
            if (!doStartSMUX(Device::AS7341_Reg::SMUX_F1F4)) {
                HAL::I2C::recoverBus();
                g_error = true;
                return;
            }
            g_seq = Sequence::SweepPoll;
            return;

        case Sequence::SweepPoll:
            /** 轮询 STATUS_2.AVALID (bit 6) */
            if (g_ioDone) {
                g_ioDone = false;
                if (g_rxBuf[0] & 0x40) {
                    startReadCH(g_phase2 ? Sequence::SweepReadPhase2
                                         : Sequence::SweepReadPhase1);
                    return;
                }
            }
            /** 异步读 STATUS_2 */
            if (HAL::I2C::readRegIT(+Reg::ADDR, +Reg::STATUS_2, g_rxBuf, 1)) {
                g_i2cBusy = true;
                g_i2cStartedAt = Platform::SysTick_::tickMs();
            }
            return;

        case Sequence::SweepReadPhase1:
            unpackPhase1();
            g_phase2 = true;
            if (!doStartSMUX(Device::AS7341_Reg::SMUX_F5F8)) {
                HAL::I2C::recoverBus();
                g_error = true;
                return;
            }
            g_seq = Sequence::SweepPoll;
            return;

        case Sequence::SweepReadPhase2:
            unpackPhase2();
            g_dataValid = true;
            g_seq = Sequence::SweepDone;
            return;

        case Sequence::SweepDone:
            g_seq = Sequence::Idle;
            return;

        case Sequence::Idle:
            return;
        }
    }

    /** 状态查询 */

    /**
     * @brief 查询是否就绪
     * @return true=就绪
     */
    static bool isReady() noexcept { return g_ready; }

    /**
     * @brief 查询是否出错
     * @return true=出错
     */
    static bool isError() noexcept { return g_error; }

    /**
     * @brief 查询是否忙（扫描中）
     * @return true=忙
     */
    static bool isBusy() noexcept { return g_seq != Sequence::Idle; }

    /**
     * @brief 查询数据是否有效
     * @return true=数据有效
     */
    static bool isDataValid() noexcept { return g_dataValid; }

    /** 测量 API */

    /**
     * @brief 启动一轮光谱测量
     */
    static void startMeasurement() noexcept {
        if (!g_ready || isBusy()) return;
        g_dataValid = false;
        g_phase2 = false;
        g_seq = Sequence::SweepF1F4;
    }

    /**
     * @brief 读取光谱数据
     * @return 光谱测量结果
     */
    static SpectralData readData() noexcept {
        SpectralData data = g_data;
        g_dataValid = false;
        return data;
    }

    /** 配置（同步 I2C） */

    /**
     * @brief 设置积分时间
     * @param value ATIME 寄存器值
     */
    static void setATime(uint8_t value) noexcept {
        writeRegSync(+Reg::ATIME, value);
    }

    /**
     * @brief 设置积分步长
     * @param value ASTEP 值（16 位）
     */
    static void setAStep(uint16_t value) noexcept {
        writeRegSync(+Reg::ASTEP_L, value & 0xFF);
        writeRegSync(+Reg::ASTEP_H, (value >> 8) & 0xFF);
    }

    /**
     * @brief 设置 ADC 增益
     * @param gain 增益预设
     */
    static void setAGain(AGain gain) noexcept {
        writeRegSync(+Reg::CFG_1, static_cast<uint8_t>(gain));
    }

    /**
     * @brief 使能/禁用 LED
     * @param on true=使能, false=禁用
     */
    static void enableLED(bool on) noexcept {
        setBankSync(1);
        uint8_t cfg = readRegSyncVal(+Reg::CONFIG);
        if (on) {
            cfg |= 0x08;
        } else {
            cfg &= ~0x08;
            writeRegSync(+Reg::LED, readRegSyncVal(+Reg::LED) & ~0x80);
        }
        writeRegSync(+Reg::CONFIG, cfg);
        setBankSync(0);
    }

    /**
     * @brief 设置 LED 电流
     * @param current 电流值（1-20mA）
     */
    static void setLEDCurrent(uint8_t current) noexcept {
        if (current < 1) current = 1;
        if (current > 20) current = 20;
        setBankSync(1);
        writeRegSync(+Reg::LED, static_cast<uint8_t>(0x80 | (current - 1)));
        setBankSync(0);
    }

    /** I2C ISR 回调 */

    /**
     * @brief I2C 传输完成回调
     */
    static void onI2CComplete() noexcept {
        g_i2cBusy = false;
        g_ioDone = true;
    }

    /**
     * @brief I2C 传输错误回调
     */
    static void onI2CError() noexcept {
        g_i2cBusy = false;
        g_error = true;
    }

    AS7341() = delete;

private:
    /**
     * @brief 扫描状态机阶段
     */
    enum class Sequence : uint8_t {
        Idle,
        SweepF1F4,
        SweepPoll,
        SweepReadPhase1,
        SweepReadPhase2,
        SweepDone,
    };

    /** 同步 I2C 辅助 */

    /**
     * @brief 同步写寄存器
     * @param reg 寄存器地址
     * @param val 待写入值
     * @return true=成功
     */
    static bool writeRegSync(uint8_t reg, uint8_t val) noexcept {
        return HAL::I2C::writeRegSync(+Reg::ADDR, reg, val, 100);
    }

    /**
     * @brief 同步读寄存器
     * @param reg 寄存器地址
     * @param val 读取结果
     * @return true=成功
     */
    static bool readRegSync(uint8_t reg, uint8_t* val) noexcept {
        return HAL::I2C::readRegSync(+Reg::ADDR, reg, val, 1, 100);
    }

    /**
     * @brief 同步读单字节寄存器
     * @param reg 寄存器地址
     * @return 读取到的值
     */
    static uint8_t readRegSyncVal(uint8_t reg) noexcept {
        uint8_t d{};
        readRegSync(reg, &d);
        return d;
    }

    /**
     * @brief 切换寄存器 Bank
     * @param bank Bank 编号（0 或 1）
     */
    static bool setBankSync(uint8_t bank) noexcept {
        uint8_t d{};
        if (!readRegSync(+Reg::CFG_0, &d)) return false;
        d = (bank == 1) ? (d | (1 << 4)) : (d & ~(1 << 4));
        return writeRegSync(+Reg::CFG_0, d);
    }

    /** SMUX 配置 + 启动测量（同步） */

    /**
     * @brief 写入 SMUX 配置并启动测量
     * @param smux SMUX 配置表（20 字节）
     */
    static bool doStartSMUX(const uint8_t* smux) noexcept {
        g_ioDone = false;
        if (!writeRegSync(+Reg::CFG_0, 0)) return false;

        uint8_t enable{};
        if (!readRegSync(+Reg::ENABLE, &enable) ||
            !writeRegSync(+Reg::ENABLE, enable & ~(1 << 1)) ||
            !writeRegSync(0xAF, 0x10)) {
            return false;
        }
        for (uint8_t i = 0; i < 20; ++i) {
            if (!writeRegSync(i, smux[i])) return false;
        }
        if (!readRegSync(+Reg::ENABLE, &enable) ||
            !writeRegSync(+Reg::ENABLE, enable | (1 << 4)) ||
            !setBankSync(1)) {
            return false;
        }

        uint8_t config{};
        if (!readRegSync(+Reg::CONFIG, &config) ||
            !writeRegSync(+Reg::CONFIG, config & ~3) ||
            !setBankSync(0) ||
            !readRegSync(+Reg::ENABLE, &enable) ||
            !writeRegSync(+Reg::ENABLE, enable | (1 << 1))) {
            return false;
        }
        return true;
    }

    /** 异步读通道数据 */

    /**
     * @brief 启动异步读取 12 字节通道数据
     * @param next 读取完成后的下一状态
     */
    static void startReadCH(Sequence next) noexcept {
        if (HAL::I2C::readRegIT(+Reg::ADDR, +Reg::CH0_DATA_L, g_rxBuf, 12)) {
            g_i2cBusy = true;
            g_i2cStartedAt = Platform::SysTick_::tickMs();
            g_seq = next;
        }
    }

    /** 数据解包 */

    /**
     * @brief 从接收缓冲解包 16 位值
     * @param i 缓冲区偏移
     * @return 16 位值（小端）
     */
    static uint16_t unpack(unsigned i) noexcept {
        return static_cast<uint16_t>(g_rxBuf[i]) |
               static_cast<uint16_t>(static_cast<uint16_t>(g_rxBuf[i + 1]) << 8);
    }

    /**
     * @brief 解包 Phase 1 数据（F1-F4 + Clear + NIR）
     */
    static void unpackPhase1() noexcept {
        g_data.nm415 = unpack(0);
        g_data.nm445 = unpack(2);
        g_data.nm480 = unpack(4);
        g_data.nm515 = unpack(6);
        g_clear1 = unpack(8);
        g_nir1 = unpack(10);
    }

    /**
     * @brief 解包 Phase 2 数据（F5-F8 + Clear + NIR），Clear 和 NIR 取两次平均
     */
    static void unpackPhase2() noexcept {
        g_data.nm555 = unpack(0);
        g_data.nm590 = unpack(2);
        g_data.nm630 = unpack(4);
        g_data.nm680 = unpack(6);
        uint16_t clear2 = unpack(8);
        uint16_t nir2 = unpack(10);
        g_data.Clear = (g_clear1 + clear2) / 2;
        g_data.nm910 = (g_nir1 + nir2) / 2;
    }

    /** 状态 */

    inline static Sequence g_seq = Sequence::Idle;
    inline static volatile bool g_ready{false};
    inline static volatile bool g_error{false};
    inline static volatile bool g_dataValid{false};
    inline static volatile bool g_ioDone{false};
    inline static volatile bool g_phase2{false};
    inline static SpectralData g_data{};
    inline static uint16_t g_clear1{0};
    inline static uint16_t g_nir1{0};
    inline static volatile bool g_i2cBusy{false};
    inline static volatile uint32_t g_i2cStartedAt{0};
    inline static volatile uint8_t g_rxBuf[12]{};

    static constexpr uint32_t I2C_TIMEOUT_MS = 100;
};

} // namespace Device
