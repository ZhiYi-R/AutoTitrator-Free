/**
 * @file    SerialPort.hpp
 * @brief   串口设备驱动（环形缓冲 RX + TX 管理）
 */

#pragma once

#include <hal/UART.hpp>
#include <cstddef>
#include <cstdint>

namespace Device {

/**
 * @brief 串口设备驱动
 *
 * 环形缓冲 RX + TX 管理
 * RX: HAL::UART DMA 循环 → 环形缓冲 → 用户读取
 * TX: 用户写入 → HAL::UART TXE 中断逐字节发送
 */
class SerialPort {
public:
    /** RX 环形缓冲区大小（必须为 2 的幂） */
    static constexpr size_t RX_BUF_SIZE = 256;
    /** TX 缓冲区大小 */
    static constexpr size_t TX_BUF_SIZE = 32;

    /**
     * @brief 初始化串口
     */
    static void initialize() noexcept {
        HAL::UART::initialize(115200);
        g_lastDmaPos = 0;
    }

    /** RX */

    /**
     * @brief 环形缓冲可读字节数
     * @return 可读字节数
     */
    static size_t available() noexcept {
        return (g_rxHead - g_rxTail) & (RX_BUF_SIZE - 1);
    }

    /**
     * @brief 读一字节（空时自旋等待）
     * @return 读取到的字节
     */
    static uint8_t read() noexcept {
        while (available() == 0) {
            service();
        }
        uint8_t b = g_rxBuf[g_rxTail];
        g_rxTail = (g_rxTail + 1) & (RX_BUF_SIZE - 1);
        return b;
    }

    /**
     * @brief 批量读取（非阻塞）
     * @param buf 接收缓冲区
     * @param len 最大读取长度
     * @return 实际读取数
     */
    static size_t read(uint8_t* buf, size_t len) noexcept {
        size_t cnt = 0;
        service();
        while (cnt < len && available() > 0) {
            buf[cnt] = g_rxBuf[g_rxTail];
            g_rxTail = (g_rxTail + 1) & (RX_BUF_SIZE - 1);
            ++cnt;
        }
        return cnt;
    }

    /**
     * @brief 丢弃所有 RX 数据
     */
    static void flush() noexcept {
        g_rxHead = 0;
        g_rxTail = 0;
        g_lastDmaPos = HAL::UART::dmaWritePos();
    }

    /** TX */

    /**
     * @brief 非阻塞发送（TX 忙时自旋等待）
     * @param data 待发送数据
     * @param len 数据长度
     */
    static void write(const uint8_t* data, size_t len) noexcept {
        if (len == 0) return;
        if (len > TX_BUF_SIZE) len = TX_BUF_SIZE;

        /** 等 TX 空闲 */
        while (!HAL::UART::isTxIdle()) {
            /** 自旋 */
        }
        HAL::UART::setTxData(data, len);
        HAL::UART::startTx();
    }

    /**
     * @brief 发送单字节
     * @param byte 待发送字节
     */
    static void write(uint8_t byte) noexcept {
        write(&byte, 1);
    }

    /**
     * @brief 主循环服务（搬运 DMA 缓冲到环形缓冲）
     */
    static void service() noexcept {
        /** 标志仅用于清除事件状态；写指针本身是数据是否到达的依据。 */
        (void)HAL::UART::consumeRxDmaFlag();
        (void)HAL::UART::consumeRxIdleFlag();
        drainDMA();
    }

    SerialPort() = delete;

private:
    /**
     * @brief 将 DMA 缓冲中的新数据搬运到环形缓冲
     */
    static void drainDMA() noexcept {
        size_t curPos = HAL::UART::dmaWritePos();
        volatile const uint8_t* dmaBuf = HAL::UART::dmaBuffer();
        while (g_lastDmaPos != curPos) {
            uint8_t b = dmaBuf[g_lastDmaPos];
            putRx(b);
            g_lastDmaPos = (g_lastDmaPos + 1) & (HAL::UART::dmaBufferSize() - 1);
        }
    }

    /**
     * @brief 写入 RX 环形缓冲（溢出时丢弃最旧）
     * @param b 待写入字节
     */
    static void putRx(uint8_t b) noexcept {
        g_rxBuf[g_rxHead] = b;
        g_rxHead = (g_rxHead + 1) & (RX_BUF_SIZE - 1);
        if (g_rxHead == g_rxTail) {
            /** 溢出，丢弃最旧 */
            g_rxTail = (g_rxTail + 1) & (RX_BUF_SIZE - 1);
        }
    }

    inline static uint8_t g_rxBuf[RX_BUF_SIZE]{};
    inline static volatile size_t g_rxHead{0};
    inline static volatile size_t g_rxTail{0};
    inline static size_t g_lastDmaPos{0};
};

} // namespace Device
