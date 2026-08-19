/**
 * @file    I2C.hpp
 * @brief   I2C1 驱动（中断模式异步传输 + 同步轮询回退）
 */

#pragma once

#include <hal/GPIO.hpp>
#include <platform/NVIC.hpp>
#include <platform/SysTick.hpp>
#include <stm32f103/AFIO.hpp>
#include <stm32f103/I2C1.hpp>
#include <stm32f103/RCC.hpp>
#include <cstddef>
#include <cstdint>

namespace HAL {

/**
 * @brief I2C1 驱动
 *
 * 中断模式异步传输 + 同步轮询回退
 * 100kHz 标准模式, PB8(SCL)/PB9(SDA), AFIO_REMAP
 */
class I2C {
public:
    /**
     * @brief 初始化 I2C1：100kHz, 7-bit 地址模式, PB8/PB9 (REMAP)
     */
    static void initialize() noexcept {
        using namespace STM32F103;

        /** 时钟 */
        RCC::APB1ENR::WriteI2C1EN(1);
        RCC::APB2ENR::WriteIOPBEN(1);
        RCC::APB2ENR::WriteAFIOEN(1);

        /** AFIO REMAP I2C1 → PB8(SCL)/PB9(SDA) */
        AFIO::MAPR::WriteI2C1_REMAP(1);

        /** PB8, PB9 = AF_OD */
        GPIO::configure(GPIO::Port::B, 8, GPIO::Mode::AfOD, GPIO::Pull::None,
                        GPIO::Speed::MHz50);
        GPIO::configure(GPIO::Port::B, 9, GPIO::Mode::AfOD, GPIO::Pull::None,
                        GPIO::Speed::MHz50);

        /** 复位 I2C */
        I2C1::CR1::Write(0);
        I2C1::CR1::WriteSWRST(1);
        I2C1::CR1::WriteSWRST(0);

        /** 配置：APB1=36MHz, FREQ=36 */
        I2C1::CR2::WriteFREQ(36);

        /** 100kHz 标准模式：CCR = 36MHz / (2 × 100kHz) = 180 */
        I2C1::CCR::WriteF_S(0);   /** 标准模式 */
        I2C1::CCR::WriteCCR(180);
        I2C1::TRISE::WriteTRISE(37); /** (1000ns / (1/36MHz)) + 1 = 37 */

        /** 使能外设 */
        I2C1::CR1::WritePE(1);

        /** 使能事件 + 错误中断 */
        I2C1::CR2::WriteITEVTEN(1);
        I2C1::CR2::WriteITBUFEN(1);
        I2C1::CR2::WriteITERREN(1);

        /** NVIC：I2C1_EV + I2C1_ER 优先级 2 */
        Platform::NVIC_::setPriority(Platform::NVIC_::IRQn::I2C1_EV, 2);
        Platform::NVIC_::enableIRQ(Platform::NVIC_::IRQn::I2C1_EV);
        Platform::NVIC_::setPriority(Platform::NVIC_::IRQn::I2C1_ER, 2);
        Platform::NVIC_::enableIRQ(Platform::NVIC_::IRQn::I2C1_ER);

        g_initialized = true;
    }

    /** ====================================================================== */
    /**  同步轮询模式（初始化阶段用）                                           */
    /** ====================================================================== */

    /**
     * @brief 同步写寄存器（阻塞）
     * @param addr7 7 位 I2C 地址
     * @param reg 寄存器地址
     * @param data 待写入数据
     * @param len 数据长度
     * @param timeoutMs 超时（毫秒）
     * @return true=成功, false=超时
     */
    static bool writeRegSync(uint8_t addr7, uint8_t reg, const uint8_t* data,
                             size_t len, uint32_t timeoutMs) noexcept {
        using namespace STM32F103;
        uint32_t t0 = Platform::SysTick_::tickMs();

        /** START */
        I2C1::CR1::WriteACK(1);
        I2C1::CR1::WriteSTART(1);
        if (!waitEvent(I2C1::SR1::ReadSB, t0, timeoutMs)) return false;

        /** 地址 + W */
        I2C1::DR::WriteDR(addr7 << 1);
        if (!waitAddrCleared(t0, timeoutMs)) return false;

        /** 寄存器地址 */
        I2C1::DR::WriteDR(reg);
        if (!waitEvent(I2C1::SR1::ReadTxE, t0, timeoutMs)) return false;

        /** 数据 */
        for (size_t i = 0; i < len; ++i) {
            I2C1::DR::WriteDR(data[i]);
            if (!waitEvent(I2C1::SR1::ReadTxE, t0, timeoutMs)) return false;
        }

        /** 等待 BTF（所有数据发完） */
        if (!waitEvent(I2C1::SR1::ReadBTF, t0, timeoutMs)) return false;

        /** STOP */
        I2C1::CR1::WriteSTOP(1);
        return true;
    }

    /**
     * @brief 同步写单字节寄存器
     * @param addr7 7 位 I2C 地址
     * @param reg 寄存器地址
     * @param value 待写入值
     * @param timeoutMs 超时（毫秒）
     * @return true=成功, false=超时
     */
    static bool writeRegSync(uint8_t addr7, uint8_t reg, uint8_t value,
                             uint32_t timeoutMs) noexcept {
        return writeRegSync(addr7, reg, &value, 1, timeoutMs);
    }

    /**
     * @brief 同步读寄存器（阻塞）
     * @param addr7 7 位 I2C 地址
     * @param reg 寄存器地址
     * @param buf 接收缓冲区
     * @param len 读取长度
     * @param timeoutMs 超时（毫秒）
     * @return true=成功, false=超时
     */
    static bool readRegSync(uint8_t addr7, uint8_t reg, uint8_t* buf, size_t len,
                            uint32_t timeoutMs) noexcept {
        using namespace STM32F103;
        if (len == 0) return true;
        uint32_t t0 = Platform::SysTick_::tickMs();

        /** START */
        I2C1::CR1::WriteSTART(1);
        if (!waitEvent(I2C1::SR1::ReadSB, t0, timeoutMs)) return false;

        /** 地址 + W（写寄存器地址阶段） */
        I2C1::DR::WriteDR(addr7 << 1);
        if (!waitAddrCleared(t0, timeoutMs)) return false;

        /** 寄存器地址 */
        I2C1::DR::WriteDR(reg);
        if (!waitEvent(I2C1::SR1::ReadTxE, t0, timeoutMs)) return false;

        /** RESTART */
        I2C1::CR1::WriteSTART(1);
        if (!waitEvent(I2C1::SR1::ReadSB, t0, timeoutMs)) return false;

        /** 地址 + R */
        I2C1::DR::WriteDR((addr7 << 1) | 1);

        /**
         * 单字节读（RM0008 EV6_1）：
         *   在 ADDR 置位后、清除前设 ACK=0（POS=0），
         *   清除 ADDR 后立即设 STOP，再等 RxNE 读数据。
         * 多字节读（N>1）：
         *   清除 ADDR 后保持 ACK=1，倒数第二字节时清 ACK + STOP。
         */
        if (len == 1) {
            if (!waitEvent(I2C1::SR1::ReadADDR, t0, timeoutMs)) return false;
            I2C1::CR1::WriteACK(0);  /** NACK 当前字节（POS=0） */
            (void)I2C1::SR2::Read(); /** 清 ADDR */
            I2C1::CR1::WriteSTOP(1); /** 紧接着产生 STOP */
            if (!waitEvent(I2C1::SR1::ReadRxNE, t0, timeoutMs)) return false;
            buf[0] = static_cast<uint8_t>(I2C1::DR::ReadDR());
        } else {
            if (!waitAddrCleared(t0, timeoutMs)) return false;
            I2C1::CR1::WriteACK(1); /** 多字节：ACK */
            for (size_t i = 0; i < len; ++i) {
                if (!waitEvent(I2C1::SR1::ReadRxNE, t0, timeoutMs)) return false;
                buf[i] = static_cast<uint8_t>(I2C1::DR::ReadDR());
                if (i == len - 2) {
                    /** 倒数第二字节：准备 NACK + STOP */
                    I2C1::CR1::WriteACK(0);
                    I2C1::CR1::WriteSTOP(1);
                }
            }
        }

        /** 恢复 ACK */
        I2C1::CR1::WriteACK(1);
        return true;
    }

    /**
     * @brief 同步读单字节寄存器
     * @param addr7 7 位 I2C 地址
     * @param reg 寄存器地址
     * @param timeoutMs 超时（毫秒）
     * @return 读取到的值
     */
    static uint8_t readRegSyncVal(uint8_t addr7, uint8_t reg,
                                  uint32_t timeoutMs) noexcept {
        uint8_t v{};
        readRegSync(addr7, reg, &v, 1, timeoutMs);
        return v;
    }

    /** ====================================================================== */
    /**  异步中断模式                                                           */
    /** ====================================================================== */

    /**
     * @brief 异步写寄存器（启动后由 ISR 推进，完成回调 onComplete/onError）
     * @param addr7 7 位 I2C 地址
     * @param reg 寄存器地址
     * @param data 待写入数据
     * @param len 数据长度
     * @return true=已启动, false=忙或超限
     */
    static bool writeRegIT(uint8_t addr7, uint8_t reg, const uint8_t* data,
                           size_t len) noexcept {
        using namespace STM32F103;
        if (g_busy) return false;
        if (len > MAX_BUF) return false;

        g_busy = true;
        g_isRead = false;
        g_addr7 = addr7;
        g_reg = reg;
        g_len = len;
        g_idx = 0;
        g_error = false;
        g_done = false;
        g_phase = Phase::WriteAddrW;

        for (size_t i = 0; i < len; ++i) g_txbuf[i] = data[i];

        /** START */
        I2C1::CR1::WriteACK(1);
        I2C1::CR1::WriteSTART(1);
        return true;
    }

    /**
     * @brief 异步读寄存器（启动后由 ISR 推进，完成回调 onComplete/onError）
     * @param addr7 7 位 I2C 地址
     * @param reg 寄存器地址
     * @param buf 接收缓冲区
     * @param len 读取长度
     * @return true=已启动, false=忙或超限
     */
    static bool readRegIT(uint8_t addr7, uint8_t reg, uint8_t* buf,
                          size_t len) noexcept {
        using namespace STM32F103;
        if (g_busy) return false;
        if (len > MAX_BUF) return false;

        g_busy = true;
        g_isRead = true;
        g_addr7 = addr7;
        g_reg = reg;
        g_len = len;
        g_idx = 0;
        g_error = false;
        g_done = false;
        g_rxbuf = buf;
        g_phase = Phase::WriteAddrW;

        /** START */
        I2C1::CR1::WriteACK(1);
        I2C1::CR1::WriteSTART(1);
        return true;
    }

    /**
     * @brief 查询是否忙
     * @return true=忙
     */
    static bool isBusy() noexcept { return g_busy; }

    /**
     * @brief 查询是否完成
     * @return true=完成
     */
    static bool isDone() noexcept { return g_done; }

    /**
     * @brief 查询是否出错
     * @return true=出错
     */
    static bool isError() noexcept { return g_error; }

    /**
     * @brief 回调函数指针类型
     */
    using Callback = void (*)();

    /**
     * @brief 注册完成回调
     * @param cb 回调函数
     */
    static void setCompleteCallback(Callback cb) noexcept { g_completeCb = cb; }

    /**
     * @brief 注册错误回调
     * @param cb 回调函数
     */
    static void setErrorCallback(Callback cb) noexcept { g_errorCb = cb; }

    /** ====================================================================== */
    /**  ISR 回调                                                               */
    /** ====================================================================== */

    /**
     * @brief I2C1 事件中断（I2C1_EV_IRQHandler）
     */
    static void onEvent() noexcept {
        using namespace STM32F103;
        if (!g_busy) return;

        uint32_t sr1 = I2C1::SR1::Read();
        (void)I2C1::SR2::Read(); /** 读 SR2 清 ADDR/STOPF */

        /** SB (Start Bit) */
        if (sr1 & 0x0001) {
            switch (g_phase) {
            case Phase::WriteAddrW:
                I2C1::DR::WriteDR(g_addr7 << 1);
                g_phase = Phase::WriteReg;
                break;
            case Phase::RestartAddrR:
                I2C1::DR::WriteDR((g_addr7 << 1) | 1);
                g_phase = Phase::ReadData;
                /**
                 * ACK 配置：
                 *   单字节读：ACK=0，STOP/POS 在 ADDR 事件中处理（见上方 ADDR 分支）
                 *   多字节读：ACK=1，倒数第二字节时清 ACK + STOP（见下方 RxNE 分支）
                 */
                if (g_len == 1) {
                    I2C1::CR1::WriteACK(0);
                } else {
                    I2C1::CR1::WriteACK(1);
                }
                break;
            default:
                break;
            }
            return;
        }

        /** ADDR */
        if (sr1 & 0x0002) {
            /**
             * 单字节读（RM0008 EV6_1）：ADDR 置位时清 ACK，
             * 读 SR2 清 ADDR 后立即设 STOP。
             * POS=0（仅 2 字节读才用 POS）。
             */
            if (g_isRead && g_len == 1) {
                I2C1::CR1::WriteACK(0);
                (void)I2C1::SR2::Read(); /** 清 ADDR */
                I2C1::CR1::WriteSTOP(1);
                return;
            }
            /** 读 SR2 已清 ADDR */
            return;
        }

        /** TxE (Transmit buffer Empty) */
        if (sr1 & 0x0080) {
            switch (g_phase) {
            case Phase::WriteReg:
                I2C1::DR::WriteDR(g_reg);
                if (g_isRead) {
                    g_phase = Phase::Restart;
                } else {
                    g_phase = Phase::WriteData;
                }
                break;
            case Phase::Restart:
                I2C1::CR1::WriteSTART(1); /** RESTART */
                g_phase = Phase::RestartAddrR;
                break;
            case Phase::WriteData:
                if (g_idx < g_len) {
                    I2C1::DR::WriteDR(g_txbuf[g_idx]);
                    g_idx = g_idx + 1;
                } else {
                    /** 等待 BTF */
                }
                break;
            default:
                break;
            }
            return;
        }

        /** BTF (Byte Transfer Finished) */
        if (sr1 & 0x0004) {
            if (!g_isRead && g_idx >= g_len) {
                /** 写完成 */
                I2C1::CR1::WriteSTOP(1);
                finishComplete();
            }
            return;
        }

        /** RxNE (Receive buffer Not Empty) */
        if (sr1 & 0x0040) {
            if (g_isRead && g_phase == Phase::ReadData) {
                if (g_rxbuf != nullptr && g_idx < g_len) {
                    g_rxbuf[g_idx] = static_cast<uint8_t>(I2C1::DR::ReadDR());
                    g_idx = g_idx + 1;
                    /**
                     * 多字节读（N>1）：倒数第二字节时 NACK + STOP。
                     * 单字节读（N=1）：STOP 已在 ADDR 事件中发送，此处无需再设。
                     */
                    if (g_len > 1 && g_idx == g_len - 1) {
                        I2C1::CR1::WriteACK(0);
                        I2C1::CR1::WriteSTOP(1);
                    }
                }
                if (g_idx >= g_len) {
                    /** 读完成 */
                    I2C1::CR1::WriteACK(1);
                    finishComplete();
                }
            }
            return;
        }
    }

    /**
     * @brief I2C1 错误中断（I2C1_ER_IRQHandler）
     */
    static void onError() noexcept {
        using namespace STM32F103;
        /** 清所有错误标志 */
        I2C1::SR1::WriteBERR(0);
        I2C1::SR1::WriteARLO(0);
        I2C1::SR1::WriteAF(0);
        I2C1::SR1::WriteOVR(0);
        I2C1::CR1::WriteSTOP(1);
        g_error = true;
        g_busy = false;
        if (g_errorCb != nullptr) g_errorCb();
    }

    /**
     * @brief 总线恢复（9 个 SCL 脉冲解锁被拉低的 SDA）
     *
     * 注意：I2C1 REMAP 后 SCL=PB8, SDA=PB9
     */
    static void recoverBus() noexcept {
        using namespace STM32F103;
        /** 复位 I2C 外设 */
        I2C1::CR1::Write(0);
        I2C1::CR1::WriteSWRST(1);
        I2C1::CR1::WriteSWRST(0);

        /** PB8/PB9 切为 GPIO 输出开漏 */
        GPIO::configure(GPIO::Port::B, 8, GPIO::Mode::OutputOD, GPIO::Pull::None,
                        GPIO::Speed::MHz50);
        GPIO::configure(GPIO::Port::B, 9, GPIO::Mode::OutputOD, GPIO::Pull::None,
                        GPIO::Speed::MHz50);

        /** 拉高 SCL + SDA */
        GPIO::set(GPIO::Port::B, 8, true);
        GPIO::set(GPIO::Port::B, 9, true);
        Platform::SysTick_::delayMs(1);

        /** 9 个 SCL 脉冲 */
        for (int i = 0; i < 9; ++i) {
            GPIO::set(GPIO::Port::B, 8, false);
            Platform::SysTick_::delayMs(1);
            GPIO::set(GPIO::Port::B, 8, true);
            Platform::SysTick_::delayMs(1);
        }

        /** 切回 AF_OD */
        GPIO::configure(GPIO::Port::B, 8, GPIO::Mode::AfOD, GPIO::Pull::None,
                        GPIO::Speed::MHz50);
        GPIO::configure(GPIO::Port::B, 9, GPIO::Mode::AfOD, GPIO::Pull::None,
                        GPIO::Speed::MHz50);

        /** 重新初始化 I2C */
        I2C1::CR2::WriteFREQ(36);
        I2C1::CCR::WriteF_S(0);
        I2C1::CCR::WriteCCR(180);
        I2C1::TRISE::WriteTRISE(37);
        I2C1::CR1::WritePE(1);
        /** 恢复事件 + 缓冲 + 错误中断使能（与 initialize() 一致） */
        I2C1::CR2::WriteITEVTEN(1);
        I2C1::CR2::WriteITBUFEN(1);
        I2C1::CR2::WriteITERREN(1);
        Platform::SysTick_::delayMs(5);
    }

    I2C() = delete;

private:
    /** 异步传输缓冲区最大长度 */
    static constexpr size_t MAX_BUF = 20;

    /**
     * @brief 异步传输状态机阶段
     */
    enum class Phase : uint8_t {
        Idle,
        WriteAddrW,
        WriteReg,
        Restart,
        RestartAddrR,
        WriteData,
        ReadData,
    };

    /**
     * @brief 标记异步传输完成
     */
    static void finishComplete() noexcept {
        g_busy = false;
        g_done = true;
        g_phase = Phase::Idle;
        if (g_completeCb != nullptr) g_completeCb();
    }

    /** 同步等待辅助 */

    /**
     * @brief SR 寄存器检查函数指针类型
     */
    using SrCheck = uint32_t (*)() noexcept;

    /**
     * @brief 同步等待指定 SR 事件
     * @param check SR 检查函数
     * @param t0 起始时间戳
     * @param timeoutMs 超时（毫秒）
     * @return true=事件发生, false=超时
     */
    static bool waitEvent(SrCheck check, uint32_t t0,
                          uint32_t timeoutMs) noexcept {
        while (Platform::SysTick_::elapsed(t0) < timeoutMs) {
            if (check() != 0) return true;
        }
        return false;
    }

    /**
     * @brief 同步等待 ADDR 标志清除
     * @param t0 起始时间戳
     * @param timeoutMs 超时（毫秒）
     * @return true=成功, false=超时
     */
    static bool waitAddrCleared(uint32_t t0, uint32_t timeoutMs) noexcept {
        using namespace STM32F103;
        if (!waitEvent(I2C1::SR1::ReadADDR, t0, timeoutMs)) return false;
        (void)I2C1::SR2::Read(); /** 读 SR2 清 ADDR */
        return true;
    }

    /** 异步状态 */

    inline static volatile bool g_busy{false};
    inline static volatile bool g_done{false};
    inline static volatile bool g_error{false};
    inline static volatile bool g_isRead{false};
    inline static volatile Phase g_phase{Phase::Idle};
    inline static volatile uint8_t g_addr7{0};
    inline static volatile uint8_t g_reg{0};
    inline static volatile size_t g_len{0};
    inline static volatile size_t g_idx{0};
    inline static uint8_t g_txbuf[MAX_BUF]{};
    inline static uint8_t* g_rxbuf{nullptr};
    inline static bool g_initialized{false};
    inline static Callback g_completeCb{nullptr};
    inline static Callback g_errorCb{nullptr};
};

} // namespace HAL
