/**
 * @file    GPIO.hpp
 * @brief   GPIO 引脚配置（STM32F103 风格：MODE + CNF 4 位/引脚）
 */

#pragma once

#include <stm32f103/AFIO.hpp>
#include <stm32f103/GPIOA.hpp>
#include <stm32f103/GPIOB.hpp>
#include <stm32f103/GPIOC.hpp>
#include <stm32f103/GPIOD.hpp>
#include <stm32f103/RCC.hpp>
#include <cstdint>

namespace HAL {

/**
 * @brief GPIO 引脚配置
 *
 * STM32F103 风格：MODE + CNF 4 位/引脚
 */
class GPIO {
public:
    /**
     * @brief 引脚工作模式
     */
    enum class Mode : uint8_t {
        Input,       /** CNF=01 (浮空), MODE=00 */
        InputPull,   /** CNF=10 (上拉/下拉), MODE=00 */
        InputAnalog, /** CNF=00 (模拟), MODE=00 */
        OutputPP,    /** CNF=00 (推挽), MODE=01/10/11 */
        OutputOD,    /** CNF=01 (开漏), MODE=01/10/11 */
        AfPP,        /** CNF=10 (复用推挽), MODE=01/10/11 */
        AfOD,        /** CNF=11 (复用开漏), MODE=01/10/11 */
    };

    /**
     * @brief 上拉/下拉选择
     */
    enum class Pull : uint8_t { None, Up, Down };

    /**
     * @brief 输出速度
     */
    enum class Speed : uint8_t { MHz10 = 1, MHz2 = 2, MHz50 = 3 };

    /**
     * @brief 端口编号
     */
    enum class Port : uint8_t { A, B, C, D };

    /**
     * @brief 配置指定引脚
     * @param port 端口
     * @param pin 引脚号（0-15）
     * @param mode 工作模式
     * @param pull 上拉/下拉（仅 InputPull 模式有效）
     * @param speed 输出速度（仅输出模式有效）
     */
    static void configure(Port port, uint8_t pin, Mode mode,
                          Pull pull = Pull::None,
                          Speed speed = Speed::MHz50) noexcept {
        enableClock(port);

        uint8_t modeBits = modeSpeedBits(mode, speed);
        uint8_t cnfBits = modeCnfBits(mode, pull);
        uint8_t cfg = (cnfBits << 2) | modeBits;

        if (pin < 8) {
            writeCRL(port, pin, cfg);
        } else {
            writeCRH(port, pin, cfg);
        }

        /** 上拉/下拉需要设置 ODR 对应位 */
        if (mode == Mode::InputPull) {
            setODRBit(port, pin, pull == Pull::Up);
        }
    }

    /**
     * @brief 原子置位/复位（输出高/低电平）
     * @param port 端口
     * @param pin 引脚号
     * @param high true=高电平, false=低电平
     */
    static void set(Port port, uint8_t pin, bool high) noexcept {
        uint32_t mask = 1u << pin;
        uint32_t val = high ? mask : (mask << 16);
        writeBSRR(port, val);
    }

    /**
     * @brief 读取引脚电平
     * @param port 端口
     * @param pin 引脚号
     * @return true=高电平, false=低电平
     */
    static bool read(Port port, uint8_t pin) noexcept {
        return (readIDR(port) >> pin) & 1u;
    }

    GPIO() = delete;

private:
    static void enableClock(Port port) noexcept {
        using namespace STM32F103;
        switch (port) {
        case Port::A: RCC::APB2ENR::WriteIOPAEN(1); break;
        case Port::B: RCC::APB2ENR::WriteIOPBEN(1); break;
        case Port::C: RCC::APB2ENR::WriteIOPCEN(1); break;
        case Port::D: RCC::APB2ENR::WriteIOPDEN(1); break;
        }
    }

    static uint8_t modeSpeedBits(Mode mode, Speed speed) noexcept {
        if (mode == Mode::Input || mode == Mode::InputPull ||
            mode == Mode::InputAnalog) {
            return 0; /** 输入模式 MODE=00 */
        }
        return static_cast<uint8_t>(speed);
    }

    static uint8_t modeCnfBits(Mode mode, Pull /*pull*/) noexcept {
        switch (mode) {
        case Mode::Input:       return 1; /** 浮空输入 */
        case Mode::InputPull:   return 2; /** 上拉/下拉输入 */
        case Mode::InputAnalog: return 0; /** 模拟输入 */
        case Mode::OutputPP:    return 0; /** 通用推挽输出 */
        case Mode::OutputOD:    return 1; /** 通用开漏输出 */
        case Mode::AfPP:        return 2; /** 复用推挽输出 */
        case Mode::AfOD:        return 3; /** 复用开漏输出 */
        }
        return 0;
    }

    /** CRL/CRH 按引脚号计算偏移并 RMW */

    static void writeCRL(Port port, uint8_t pin, uint8_t cfg) noexcept {
        uint32_t shift = pin * 4;
        uint32_t mask = 0xFu << shift;
        uint32_t val = static_cast<uint32_t>(cfg) << shift;
        switch (port) {
        case Port::A: STM32F103::GPIOA::CRL::Write((STM32F103::GPIOA::CRL::Read() & ~mask) | val); break;
        case Port::B: STM32F103::GPIOB::CRL::Write((STM32F103::GPIOB::CRL::Read() & ~mask) | val); break;
        case Port::C: STM32F103::GPIOC::CRL::Write((STM32F103::GPIOC::CRL::Read() & ~mask) | val); break;
        case Port::D: STM32F103::GPIOD::CRL::Write((STM32F103::GPIOD::CRL::Read() & ~mask) | val); break;
        }
    }

    static void writeCRH(Port port, uint8_t pin, uint8_t cfg) noexcept {
        uint32_t shift = (pin - 8) * 4;
        uint32_t mask = 0xFu << shift;
        uint32_t val = static_cast<uint32_t>(cfg) << shift;
        switch (port) {
        case Port::A: STM32F103::GPIOA::CRH::Write((STM32F103::GPIOA::CRH::Read() & ~mask) | val); break;
        case Port::B: STM32F103::GPIOB::CRH::Write((STM32F103::GPIOB::CRH::Read() & ~mask) | val); break;
        case Port::C: STM32F103::GPIOC::CRH::Write((STM32F103::GPIOC::CRH::Read() & ~mask) | val); break;
        case Port::D: STM32F103::GPIOD::CRH::Write((STM32F103::GPIOD::CRH::Read() & ~mask) | val); break;
        }
    }

    static void setODRBit(Port port, uint8_t pin, bool high) noexcept {
        uint32_t mask = 1u << pin;
        switch (port) {
        case Port::A: {
            auto v = STM32F103::GPIOA::ODR::Read();
            STM32F103::GPIOA::ODR::Write(high ? (v | mask) : (v & ~mask));
            break;
        }
        case Port::B: {
            auto v = STM32F103::GPIOB::ODR::Read();
            STM32F103::GPIOB::ODR::Write(high ? (v | mask) : (v & ~mask));
            break;
        }
        case Port::C: {
            auto v = STM32F103::GPIOC::ODR::Read();
            STM32F103::GPIOC::ODR::Write(high ? (v | mask) : (v & ~mask));
            break;
        }
        case Port::D: {
            auto v = STM32F103::GPIOD::ODR::Read();
            STM32F103::GPIOD::ODR::Write(high ? (v | mask) : (v & ~mask));
            break;
        }
        }
    }

    static void writeBSRR(Port port, uint32_t val) noexcept {
        switch (port) {
        case Port::A: STM32F103::GPIOA::BSRR::Write(val); break;
        case Port::B: STM32F103::GPIOB::BSRR::Write(val); break;
        case Port::C: STM32F103::GPIOC::BSRR::Write(val); break;
        case Port::D: STM32F103::GPIOD::BSRR::Write(val); break;
        }
    }

    static uint32_t readIDR(Port port) noexcept {
        switch (port) {
        case Port::A: return STM32F103::GPIOA::IDR::Read();
        case Port::B: return STM32F103::GPIOB::IDR::Read();
        case Port::C: return STM32F103::GPIOC::IDR::Read();
        case Port::D: return STM32F103::GPIOD::IDR::Read();
        }
        return 0;
    }
};

} // namespace HAL
