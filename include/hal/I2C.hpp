/**
 * @file    I2C.hpp
 * @brief   I2C1 驱动（中断模式异步传输 + 同步轮询回退）
 */

#pragma once

#include <hal/GPIO.hpp>
#include <platform/IWDG.hpp>
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

        /** 异步传输开始时再使能中断；同步轮询期间必须保持关闭。 */
        I2C1::CR2::WriteITEVTEN(0);
        I2C1::CR2::WriteITBUFEN(0);
        I2C1::CR2::WriteITERREN(0);

        /** NVIC：AN2824 要求 I2C 事件不可被应用中断抢占 */
        Platform::NVIC_::setPriority(Platform::NVIC_::IRQn::I2C1_EV, 0);
        Platform::NVIC_::enableIRQ(Platform::NVIC_::IRQn::I2C1_EV);
        Platform::NVIC_::setPriority(Platform::NVIC_::IRQn::I2C1_ER, 0);
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
        if (g_busy || (len > 0 && data == nullptr)) return false;
        uint32_t t0 = Platform::SysTick_::tickMs();
        if (!waitBusIdle(t0, timeoutMs)) return false;

        /** START */
        I2C1::CR1::WritePOS(0);
        I2C1::CR1::WriteACK(1);
        I2C1::CR1::WriteSTART(1);
        if (!waitEvent(I2C1::SR1::ReadSB, t0, timeoutMs)) return false;

        /** 地址 + W */
        I2C1::DR::Write(addr7 << 1);
        if (!waitAddrCleared(t0, timeoutMs)) return false;

        /** 寄存器地址 */
        I2C1::DR::Write(reg);
        if (!waitEvent(I2C1::SR1::ReadTxE, t0, timeoutMs)) return false;

        /** 数据 */
        for (size_t i = 0; i < len; ++i) {
            I2C1::DR::Write(data[i]);
            if (!waitEvent(I2C1::SR1::ReadTxE, t0, timeoutMs)) return false;
        }

        /** 等待 BTF（所有数据发完） */
        if (!waitEvent(I2C1::SR1::ReadBTF, t0, timeoutMs)) return false;

        /** STOP */
        I2C1::CR1::WriteSTOP(1);
        return waitStopCleared(t0, timeoutMs);
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
        if (g_busy || (len > 0 && buf == nullptr)) return false;
        if (len == 0) return true;
        uint32_t t0 = Platform::SysTick_::tickMs();
        if (!waitBusIdle(t0, timeoutMs)) return false;

        /** START */
        I2C1::CR1::WritePOS(0);
        I2C1::CR1::WriteACK(1);
        I2C1::CR1::WriteSTART(1);
        if (!waitEvent(I2C1::SR1::ReadSB, t0, timeoutMs)) return false;

        /** 地址 + W（写寄存器地址阶段） */
        I2C1::DR::Write(addr7 << 1);
        if (!waitAddrCleared(t0, timeoutMs)) return false;

        /** 寄存器地址 */
        I2C1::DR::Write(reg);
        if (!waitEvent(I2C1::SR1::ReadBTF, t0, timeoutMs)) return false;

        /** RESTART */
        I2C1::CR1::WriteSTART(1);
        if (!waitEvent(I2C1::SR1::ReadSB, t0, timeoutMs)) return false;

        /** 地址 + R */
        I2C1::DR::Write((addr7 << 1) | 1);

        /**
         * 单字节读（RM0008 EV6_1）：
         *   在 ADDR 置位后、清除前设 ACK=0（POS=0），
         *   清除 ADDR 后立即设 STOP，再等 RxNE 读数据。
         * 两字节读（RM0008 N=2）：
         *   必须先置 POS=1，ACK=1；清 ADDR 后清 ACK，
         *   等待 BTF 后置 STOP，连读两字节。
         * 多字节读（N>2）：
         *   清除 ADDR 后保持 ACK=1，倒数第二字节时清 ACK + STOP。
         */
        if (len == 1) {
            if (!waitEvent(I2C1::SR1::ReadADDR, t0, timeoutMs)) return false;
            I2C1::CR1::WriteACK(0);  /** NACK 当前字节（POS=0） */
            uint32_t primask = disableIrqSave();
            (void)I2C1::SR2::Read(); /** 清 ADDR */
            I2C1::CR1::WriteSTOP(1); /** EV6_3 必须在当前字节结束前完成 */
            restoreIrq(primask);
            if (!waitEvent(I2C1::SR1::ReadRxNE, t0, timeoutMs)) return false;
            buf[0] = static_cast<uint8_t>(I2C1::DR::ReadDR());
        } else if (len == 2) {
            I2C1::CR1::WritePOS(1);
            I2C1::CR1::WriteACK(1);
            if (!waitEvent(I2C1::SR1::ReadADDR, t0, timeoutMs)) return false;
            uint32_t primask = disableIrqSave();
            (void)I2C1::SR2::Read(); /** 清 ADDR */
            I2C1::CR1::WriteACK(0);   /** NACK 第 2 字节 */
            restoreIrq(primask);
            if (!waitEvent(I2C1::SR1::ReadBTF, t0, timeoutMs)) return false;
            primask = disableIrqSave();
            I2C1::CR1::WriteSTOP(1);  /** 产生 STOP */
            buf[0] = static_cast<uint8_t>(I2C1::DR::ReadDR());
            restoreIrq(primask);
            buf[1] = static_cast<uint8_t>(I2C1::DR::ReadDR());
        } else {
            I2C1::CR1::WriteACK(1); /** 多字节：ACK 必须在首字节接收前置位 */
            if (!waitAddrCleared(t0, timeoutMs)) return false;

            size_t idx = 0;
            size_t remaining = len;
            while (remaining > 3) {
                if (!waitEvent(I2C1::SR1::ReadBTF, t0, timeoutMs)) return false;
                buf[idx++] = static_cast<uint8_t>(I2C1::DR::ReadDR());
                --remaining;
            }

            /** AN2824 method 2：BTF 拉低 SCL 后完成最后三字节的前两次读取。 */
            if (!waitEvent(I2C1::SR1::ReadBTF, t0, timeoutMs)) return false;
            I2C1::CR1::WriteACK(0);
            uint32_t primask = disableIrqSave();
            buf[idx++] = static_cast<uint8_t>(I2C1::DR::ReadDR());
            I2C1::CR1::WriteSTOP(1);
            buf[idx++] = static_cast<uint8_t>(I2C1::DR::ReadDR());
            restoreIrq(primask);
            if (!waitEvent(I2C1::SR1::ReadRxNE, t0, timeoutMs)) return false;
            buf[idx] = static_cast<uint8_t>(I2C1::DR::ReadDR());
        }

        if (!waitStopCleared(t0, timeoutMs)) return false;
        I2C1::CR1::WritePOS(0);
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
        if (g_busy || I2C1::SR2::ReadBUSY() != 0 || I2C1::CR1::ReadSTOP() != 0) {
            return false;
        }
        if (len == 0 || len > MAX_BUF || data == nullptr) return false;

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
        I2C1::CR1::WritePOS(0);
        I2C1::CR1::WriteACK(1);
        enableInterrupts();
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
    static bool readRegIT(uint8_t addr7, uint8_t reg, volatile uint8_t* buf,
                          size_t len) noexcept {
        using namespace STM32F103;
        if (g_busy || I2C1::SR2::ReadBUSY() != 0 || I2C1::CR1::ReadSTOP() != 0) {
            return false;
        }
        if (len == 0 || len > MAX_BUF || buf == nullptr) return false;

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
        I2C1::CR1::WritePOS(0);
        I2C1::CR1::WriteACK(1);
        enableInterrupts();
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
     * @brief 取消卡住的异步传输并恢复总线
     */
    static bool abortAndRecover() noexcept {
        uint32_t primask = disableIrqSave();
        if (!g_busy) {
            restoreIrq(primask);
            return false;
        }
        disableInterrupts();
        g_busy = false;
        g_done = false;
        g_error = true;
        g_phase = Phase::Idle;
        restoreIrq(primask);
        recoverBus();
        return true;
    }

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

        /** SB (Start Bit) */
        if (sr1 & 0x0001) {
            switch (g_phase) {
            case Phase::WriteAddrW:
                I2C1::DR::Write(g_addr7 << 1);
                g_phase = Phase::WriteReg;
                break;
            case Phase::RestartAddrR:
                I2C1::DR::Write((g_addr7 << 1) | 1);
                g_phase = Phase::ReadData;
                /**
                 * ACK/POS 配置：
                 *   单字节读：ACK=0，STOP 在 ADDR 事件中处理
                 *   两字节读：POS=1, ACK=1，清 ADDR 后再清 ACK，由 BTF 读双字节
                 *   多字节读（N>2）：ACK=1，倒数第二字节时清 ACK + STOP
                 */
                if (g_len == 1) {
                    I2C1::CR1::WriteACK(0);
                } else if (g_len == 2) {
                    I2C1::CR1::WritePOS(1);
                    I2C1::CR1::WriteACK(1);
                } else {
                    I2C1::CR1::WriteACK(1);
                }
                I2C1::CR2::WriteITBUFEN((g_len == 2 || g_len == 3) ? 0 : 1);
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
             * 两字节读：POS=1, ACK=1 已在 SB 中置位；清 ACK 后等待 BTF。
             */
            if (g_isRead && g_phase == Phase::ReadData && g_len == 1) {
                uint32_t primask = disableIrqSave();
                (void)I2C1::SR2::Read(); /** 清 ADDR */
                I2C1::CR1::WriteSTOP(1);
                restoreIrq(primask);
                return;
            }
            if (g_isRead && g_phase == Phase::ReadData && g_len == 2) {
                uint32_t primask = disableIrqSave();
                (void)I2C1::SR2::Read(); /** 清 ADDR */
                I2C1::CR1::WriteACK(0);   /** NACK 第 2 字节 */
                restoreIrq(primask);
                return;
            }
            (void)I2C1::SR2::Read(); /** 清写地址阶段或 N>2 读阶段的 ADDR */
            return;
        }

        /** BTF (Byte Transfer Finished) */
        if (sr1 & 0x0004) {
            if (!g_isRead && g_idx >= g_len) {
                /** 写完成 */
                I2C1::CR1::WriteSTOP(1);
                finishComplete();
                return;
            }
            if (g_isRead && g_phase == Phase::Restart) {
                I2C1::CR1::WriteSTART(1); /** 等寄存器地址 BTF 后产生 RESTART */
                g_phase = Phase::RestartAddrR;
                return;
            }
            if (g_isRead && g_len == 2 && g_phase == Phase::ReadData &&
                g_rxbuf != nullptr) {
                /** 两字节读：读双字节并结束 */
                uint32_t primask = disableIrqSave();
                I2C1::CR1::WriteSTOP(1);
                g_rxbuf[0] = static_cast<uint8_t>(I2C1::DR::ReadDR());
                restoreIrq(primask);
                g_rxbuf[1] = static_cast<uint8_t>(I2C1::DR::ReadDR());
                g_idx = 2;
                finishComplete();
                return;
            }
            if (g_isRead && g_len > 2 && g_phase == Phase::ReadData &&
                g_rxbuf != nullptr) {
                size_t remaining = g_len - g_idx;
                if (remaining > 3) {
                    g_rxbuf[g_idx] = static_cast<uint8_t>(I2C1::DR::ReadDR());
                    g_idx = g_idx + 1;
                    if (g_len - g_idx == 3) I2C1::CR2::WriteITBUFEN(0);
                    return;
                }
                if (remaining == 3) {
                    I2C1::CR1::WriteACK(0);
                    uint32_t primask = disableIrqSave();
                    g_rxbuf[g_idx] = static_cast<uint8_t>(I2C1::DR::ReadDR());
                    g_idx = g_idx + 1;
                    I2C1::CR1::WriteSTOP(1);
                    g_rxbuf[g_idx] = static_cast<uint8_t>(I2C1::DR::ReadDR());
                    g_idx = g_idx + 1;
                    restoreIrq(primask);
                    I2C1::CR2::WriteITBUFEN(1);
                    return;
                }
            }
        }

        /** TxE (Transmit buffer Empty) */
        if ((sr1 & 0x0080) &&
            (g_phase == Phase::WriteReg || g_phase == Phase::WriteData)) {
            switch (g_phase) {
            case Phase::WriteReg:
                I2C1::DR::Write(g_reg);
                if (g_isRead) {
                    g_phase = Phase::Restart;
                    I2C1::CR2::WriteITBUFEN(0);
                } else {
                    g_phase = Phase::WriteData;
                    if (g_len == 0) I2C1::CR2::WriteITBUFEN(0);
                }
                break;
            case Phase::WriteData:
                if (g_idx < g_len) {
                    I2C1::DR::Write(g_txbuf[g_idx]);
                    g_idx = g_idx + 1;
                    if (g_idx >= g_len) I2C1::CR2::WriteITBUFEN(0);
                } else {
                    /** 等待 BTF */
                }
                break;
            default:
                break;
            }
            return;
        }

        /** RxNE (Receive buffer Not Empty) */
        if (sr1 & 0x0040) {
            if (g_isRead && g_phase == Phase::ReadData) {
                /** 两字节读由 BTF 事件统一读取，避免提前读走 DataN-1 */
                if (g_len == 2) return;

                size_t remaining = g_len - g_idx;
                /** N>2 在剩余三字节时等待 BTF，由上方 method 2 收尾。 */
                if (g_len > 2 && remaining == 3) return;

                if (g_rxbuf != nullptr && remaining > 0) {
                    g_rxbuf[g_idx] = static_cast<uint8_t>(I2C1::DR::ReadDR());
                    g_idx = g_idx + 1;
                    if (g_len > 2 && g_len - g_idx == 3) {
                        I2C1::CR2::WriteITBUFEN(0);
                    }
                }
                if (g_idx >= g_len) {
                    /** 读完成 */
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
        g_done = false;
        g_phase = Phase::Idle;
        disableInterrupts();
        if (g_errorCb != nullptr) g_errorCb();
    }

    /**
     * @brief 总线恢复（9 个 SCL 脉冲解锁被拉低的 SDA）
     *
     * 注意：I2C1 REMAP 后 SCL=PB8, SDA=PB9
     * 总延时约 23ms，恢复前后喂狗防止 IWDG 超时
     */
    static void recoverBus() noexcept {
        using namespace STM32F103;
        
        /** 恢复前喂狗（23ms 阻塞期间可能导致看门狗超时） */
        Platform::IWDG_::reload();
        
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
        /** 同步恢复后保持中断关闭，下一次异步传输再使能。 */
        disableInterrupts();
        Platform::SysTick_::delayMs(5);
        
        /** 恢复后再次喂狗 */
        Platform::IWDG_::reload();
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
        disableInterrupts();
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

    static bool waitBusIdle(uint32_t t0, uint32_t timeoutMs) noexcept {
        while (Platform::SysTick_::elapsed(t0) < timeoutMs) {
            if (STM32F103::I2C1::SR2::ReadBUSY() == 0 &&
                STM32F103::I2C1::CR1::ReadSTOP() == 0) {
                return true;
            }
        }
        return false;
    }

    static bool waitStopCleared(uint32_t t0, uint32_t timeoutMs) noexcept {
        while (Platform::SysTick_::elapsed(t0) < timeoutMs) {
            if (STM32F103::I2C1::CR1::ReadSTOP() == 0) return true;
        }
        return false;
    }

    static void enableInterrupts() noexcept {
        STM32F103::I2C1::CR2::WriteITERREN(1);
        STM32F103::I2C1::CR2::WriteITBUFEN(1);
        STM32F103::I2C1::CR2::WriteITEVTEN(1);
    }

    static void disableInterrupts() noexcept {
        STM32F103::I2C1::CR2::WriteITEVTEN(0);
        STM32F103::I2C1::CR2::WriteITBUFEN(0);
        STM32F103::I2C1::CR2::WriteITERREN(0);
    }

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
    inline static volatile uint8_t g_txbuf[MAX_BUF]{};
    inline static volatile uint8_t* g_rxbuf{nullptr};
    inline static bool g_initialized{false};
    inline static Callback g_completeCb{nullptr};
    inline static Callback g_errorCb{nullptr};
};

} // namespace HAL
