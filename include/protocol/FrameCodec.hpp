/**
 * @file    FrameCodec.hpp
 * @brief   帧编解码器（CRC-8 + 上行帧打包 + 下行参数长度查表）
 */

#pragma once

#include <cstddef>
#include <cstdint>

namespace Protocol {

/**
 * @brief 帧编解码器
 *
 * CRC-8 (Maxim-Dallas, poly = 0x31, init = 0x00)
 */
class FrameCodec {
public:
    /**
     * @brief 增量 CRC8 更新
     * @param crc 当前 CRC 值
     * @param data 输入字节
     * @return 更新后的 CRC 值
     */
    static uint8_t crc8Update(uint8_t crc, uint8_t data) noexcept {
        crc ^= data;
        for (uint8_t i = 0; i < 8; ++i) {
            crc = (crc & 0x80) ? static_cast<uint8_t>((crc << 1) ^ 0x31)
                               : static_cast<uint8_t>(crc << 1);
        }
        return crc;
    }

    /**
     * @brief 计算整段数据的 CRC8
     * @param data 数据指针
     * @param len 数据长度
     * @return CRC8 值
     */
    static uint8_t crc8(const uint8_t* data, size_t len) noexcept {
        uint8_t crc = 0;
        for (size_t i = 0; i < len; ++i) {
            crc = crc8Update(crc, data[i]);
        }
        return crc;
    }

    /** 上行帧前导字 */
    static constexpr uint8_t UPLINK_PREAMBLE0 = 0xAA;
    static constexpr uint8_t UPLINK_PREAMBLE1 = 0x55;

    /** 下行帧前导字 */
    static constexpr uint8_t DOWNLINK_PREAMBLE0 = 0xBB;
    static constexpr uint8_t DOWNLINK_PREAMBLE1 = 0x55;

    /**
     * @brief 打包上行帧：AA 55 | type | data[0..len-1] | CRC8
     * @param type 帧类型
     * @param data 数据指针
     * @param len 数据长度
     * @param out 输出缓冲区
     * @param outLen 输出长度（4 + len：前导2 + type1 + data + crc1）
     */
    static void packUplink(uint8_t type, const uint8_t* data, size_t len,
                           uint8_t* out, size_t* outLen) noexcept {
        uint8_t* p = out;
        *p++ = UPLINK_PREAMBLE0;
        *p++ = UPLINK_PREAMBLE1;
        *p++ = type;
        uint8_t cs = crc8Update(0, type);
        for (size_t i = 0; i < len; ++i) {
            *p++ = data[i];
            cs = crc8Update(cs, data[i]);
        }
        *p++ = cs;
        *outLen = static_cast<size_t>(p - out);
    }

    /**
     * @brief 下行命令参数长度查表
     * @param cmd 命令字
     * @return 参数长度（字节）
     */
    static uint8_t downlinkParamLen(uint8_t cmd) noexcept {
        switch (cmd) {
        case 0x01: return 5; /** MaxCount: pump_id(1) + count(4) */
        case 0x02: return 1; /** FreeRun: pump_id(1) */
        case 0x03: return 1; /** FreeStop: pump_id(1) */
        case 0x04: return 1; /** AbortAll: pump_id(1), 0xFF=全部 */
        case 0x05: return 1; /** Heartbeat: 0x01=enable */
        case 0x06: return 0; /** Reset */
        default:   return 0;
        }
    }

    FrameCodec() = delete;
};

} // namespace Protocol
