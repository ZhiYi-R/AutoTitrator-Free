/**
 * @file    UART.hpp
 * @brief   USART1 驱动（RX 用 DMA1_CH5 循环 + IDLE 中断，TX 用 TXE 中断逐字节）
 */

#pragma once

#include <hal/GPIO.hpp>
#include <platform/NVIC.hpp>
#include <platform/SysTick.hpp>
#include <stm32f103/DMA1.hpp>
#include <stm32f103/RCC.hpp>
#include <stm32f103/USART1.hpp>
#include <cstddef>
#include <cstdint>

namespace HAL {

/**
 * @brief USART1 串口驱动
 *
 * RX 用 DMA1_CH5 循环 + IDLE 中断，TX 用 TXE 中断逐字节
 * 115200-8N1, PA9(TX) / PA10(RX)
 */
class UART {
public:
    /** DMA 接收缓冲区大小 */
    static constexpr size_t DMA_BUF_SIZE = 64;

    /**
     * @brief 初始化 USART1 + DMA RX + IDLE 中断
     * @param baudrate 波特率
     */
    static void initialize(uint32_t baudrate) noexcept {
        using namespace STM32F103;

        /** 时钟使能 */
        RCC::APB2ENR::WriteUSART1EN(1);
        RCC::APB2ENR::WriteIOPAEN(1);
        RCC::APB2ENR::WriteAFIOEN(1);
        RCC::AHBENR::WriteDMA1EN(1);

        /** PA9 = TX (AF_PP), PA10 = RX (Input 浮空) */
        GPIO::configure(GPIO::Port::A, 9, GPIO::Mode::AfPP, GPIO::Pull::None,
                        GPIO::Speed::MHz50);
        GPIO::configure(GPIO::Port::A, 10, GPIO::Mode::Input, GPIO::Pull::None);

        /** 波特率：APB2=72MHz, BRR = 72e6 / baudrate */
        uint32_t brr = 72000000u / baudrate;
        USART1::BRR::Write(brr);

        /** CR1: UE + TE + RE + IDLEIE + RXNEIE（RXNEIE 用于错误标志清除） */
        /** 不开 TXEIE（TX 空闲时不发） */
        USART1::CR1::Write(0);
        USART1::CR1::WriteUE(1);
        USART1::CR1::WriteTE(1);
        USART1::CR1::WriteRE(1);
        USART1::CR1::WriteIDLEIE(1);

        /** CR3: DMAR（DMA 接收） */
        USART1::CR3::WriteDMAR(1);

        /** 配置 DMA1_CH5（USART1 RX） */
        DMA1::CCR5::WriteEN(0); /** 先禁用 */
        DMA1::CCR5::WriteDIR(0);          /** 外设→内存 */
        DMA1::CCR5::WriteCIRC(1);         /** 循环模式 */
        DMA1::CCR5::WritePINC(0);         /** 外设地址不增 */
        DMA1::CCR5::WriteMINC(1);         /** 内存地址自增 */
        DMA1::CCR5::WritePSIZE(0);        /** 外设 8 位 */
        DMA1::CCR5::WriteMSIZE(0);        /** 内存 8 位 */
        DMA1::CCR5::WritePL(2);           /** 优先级高 */
        DMA1::CCR5::WriteHTIE(1);         /** 半传输中断 */
        DMA1::CCR5::WriteTCIE(1);         /** 传输完成中断 */
        DMA1::CCR5::WriteTEIE(1);         /** 传输错误中断 */
        DMA1::CNDTR5::WriteNDT(DMA_BUF_SIZE);
        DMA1::CPAR5::WritePA(0x40013804); /** USART1 DR 地址 */
        DMA1::CMAR5::WriteMA(reinterpret_cast<uint32_t>(g_dmaBuf));
        DMA1::IFCR::Write(0x0F0000);      /** 清 CH5 所有标志 */
        DMA1::CCR5::WriteEN(1);           /** 使能 */

        /** NVIC：USART1 + DMA1_CH5，优先级 0（最高） */
        Platform::NVIC_::setPriority(Platform::NVIC_::IRQn::USART1, 0);
        Platform::NVIC_::enableIRQ(Platform::NVIC_::IRQn::USART1);
        Platform::NVIC_::setPriority(Platform::NVIC_::IRQn::DMA1_Channel5, 0);
        Platform::NVIC_::enableIRQ(Platform::NVIC_::IRQn::DMA1_Channel5);

        g_initialized = true;
    }

    /** RX DMA 缓冲访问（供 SerialPort drain） */

    /**
     * @brief 获取 DMA 接收缓冲区指针
     * @return DMA 缓冲区首地址
     */
    static volatile uint8_t* dmaBuffer() noexcept { return g_dmaBuf; }

    /**
     * @brief 获取 DMA 接收缓冲区大小
     * @return 缓冲区大小（字节）
     */
    static constexpr size_t dmaBufferSize() noexcept { return DMA_BUF_SIZE; }

    /**
     * @brief 获取 DMA 当前写入位置（0..DMA_BUF_SIZE-1）
     * @return 当前写入位置
     */
    static size_t dmaWritePos() noexcept {
        return DMA_BUF_SIZE - STM32F103::DMA1::CNDTR5::ReadNDT();
    }

    /** TX（中断逐字节） */

    /**
     * @brief 启动 TX：写入首字节并使能 TXE 中断
     */
    static void startTx() noexcept {
        if (g_txLen > 0) {
            STM32F103::USART1::DR::WriteDR(g_txBuf[g_txIdx]);
            g_txIdx = g_txIdx + 1;
            STM32F103::USART1::CR1::WriteTXEIE(1);
        }
    }

    /**
     * @brief 填入 TX 数据（覆盖式，调用前需确保 isTxIdle）
     * @param data 待发送数据
     * @param len 数据长度
     */
    static void setTxData(const uint8_t* data, size_t len) noexcept {
        if (len > TX_BUF_SIZE) len = TX_BUF_SIZE;
        for (size_t i = 0; i < len; ++i) g_txBuf[i] = data[i];
        g_txLen = len;
        g_txIdx = 0;
    }

    /**
     * @brief 查询 TX 是否空闲
     * @return true=空闲
     */
    static bool isTxIdle() noexcept { return g_txLen == 0; }

    /** ISR 回调 */

    /**
     * @brief DMA1_CH5 中断回调（half/full/error）
     */
    static void onRxDMA() noexcept {
        /** 清 CH5 标志 */
        STM32F103::DMA1::IFCR::Write(0x0F0000);
        g_rxDmaFlag = true; /** 通知 SerialPort drain */
    }

    /**
     * @brief USART1 中断回调（IDLE + TXE）
     */
    static void onInterrupt() noexcept {
        using namespace STM32F103;

        /** IDLE 中断：读 SR 再读 DR 清除 */
        if (USART1::SR::ReadIDLE() != 0) {
            (void)USART1::SR::Read();
            (void)USART1::DR::Read();
            g_rxIdleFlag = true;
        }

        /** TXE 中断：发送下一字节 */
        if (USART1::SR::ReadTXE() != 0 && USART1::CR1::ReadTXEIE() != 0) {
            if (g_txIdx < g_txLen) {
                USART1::DR::WriteDR(g_txBuf[g_txIdx]);
                g_txIdx = g_txIdx + 1;
            } else {
                /** 发送完成，关闭 TXE 中断 */
                USART1::CR1::WriteTXEIE(0);
                g_txLen = 0;
                g_txIdx = 0;
                g_txIdle = true;
            }
        }
    }

    /**
     * @brief 消费 RX DMA 标志（读取并清除）
     * @return true=有新 DMA 事件
     */
    static bool consumeRxDmaFlag() noexcept {
        bool f = g_rxDmaFlag;
        g_rxDmaFlag = false;
        return f;
    }

    /**
     * @brief 消费 RX IDLE 标志（读取并清除）
     * @return true=有新 IDLE 事件
     */
    static bool consumeRxIdleFlag() noexcept {
        bool f = g_rxIdleFlag;
        g_rxIdleFlag = false;
        return f;
    }

    UART() = delete;

private:
    static constexpr size_t TX_BUF_SIZE = 32;

    inline static volatile uint8_t g_dmaBuf[DMA_BUF_SIZE]{};
    inline static volatile uint8_t g_txBuf[TX_BUF_SIZE]{};
    inline static volatile size_t g_txLen{0};
    inline static volatile size_t g_txIdx{0};
    inline static volatile bool g_txIdle{true};
    inline static volatile bool g_rxDmaFlag{false};
    inline static volatile bool g_rxIdleFlag{false};
    inline static bool g_initialized{false};
};

} // namespace HAL
