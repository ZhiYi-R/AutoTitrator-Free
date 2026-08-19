/**
 * @file    CommandDispatcher.hpp
 * @brief   命令分发器（解析下行帧 → 调用设备 API → 打包上行帧）
 */

#pragma once

#include <device/ADCOversample.hpp>
#include <device/AS7341.hpp>
#include <device/PumpMotor.hpp>
#include <device/SerialPort.hpp>
#include <platform/NVIC.hpp>
#include <platform/SysTick.hpp>
#include <protocol/CommandParser.hpp>
#include <protocol/FrameCodec.hpp>
#include <cstddef>
#include <cstdint>

namespace Protocol {

/**
 * @brief 命令分发器
 *
 * 解析下行帧 → 调用对应设备 API → 打包上行帧
 *
 * 帧类型（上行 type 字段）：
 *   0x00 ACK        data = [echo_cmd]
 *   0x01 NAK        data = [echo_cmd]
 *   0x10 PumpPos    data = [pump_id(1)] [pos(4)]
 *   0x11 PumpDone   data = [pump_id(1)] [pos(4)]
 *   0x20 ADC        data = [sum(4)] [samples(2)] [shift(1)] [pump2_pos(4)]
 *   0x30 Spectral   data = [F1(2)]...[F8(2)] [Clear(2)] [NIR(2)] [reserved(2)]  (22 bytes)
 *   0x40 Heartbeat  data = [uptime_ms(4)]
 */
class CommandDispatcher {
public:
    /**
     * @brief 初始化（注册到 SerialPort 的 RX 流）
     */
    static void initialize() noexcept {
        Device::SerialPort::initialize();
        g_lastHeartbeat = 0;
        g_heartbeatEnabled = false;
        g_watchdogEnabled = false;
        g_lastHeartbeatRx = 0;
    }

    /**
     * @brief 主循环服务：从 SerialPort 读字节 → 喂入 Parser → 处理事件
     */
    static void service() noexcept {
        /** 喂入 RX 字节 */
        uint8_t buf[16];
        size_t n = Device::SerialPort::read(buf, sizeof(buf));
        for (size_t i = 0; i < n; ++i) {
            CommandParser<DispatcherHandler>::feed(buf[i]);
        }

        /** 看门狗：心跳超时 → 停泵（上位机断线保护） */
        if (g_watchdogEnabled &&
            Platform::SysTick_::elapsed(g_lastHeartbeatRx) >= WATCHDOG_TIMEOUT_MS) {
            g_watchdogEnabled = false;
            g_heartbeatEnabled = false;
            Device::PumpMotor1::stop();
            Device::PumpMotor2::stop();
        }

        /** 处理泵进度上报 */
        if (Device::PumpMotor1::isReportPending()) {
            Device::PumpMotor1::clearReport();
            sendPumpPos(1, Device::PumpMotor1::getPosition());
        }
        if (Device::PumpMotor2::isReportPending()) {
            Device::PumpMotor2::clearReport();
            sendPumpPos(2, Device::PumpMotor2::getPosition());
        }

        /** 处理泵完成 */
        if (Device::PumpMotor1::isDone()) {
            Device::PumpMotor1::clearDone();
            sendPumpDone(1, Device::PumpMotor1::getPosition());
        }
        if (Device::PumpMotor2::isDone()) {
            Device::PumpMotor2::clearDone();
            sendPumpDone(2, Device::PumpMotor2::getPosition());
        }

        /** 处理 ADC 数据就绪 */
        auto r = Device::ADCOversample::readData();
        if (r.samples > 0) {
            sendADC(r, Device::PumpMotor2::getPosition());
        }

        /** 处理光谱数据就绪 */
        if (Device::AS7341::isDataValid()) {
            sendSpectral(Device::AS7341::readData());
        }

        /** 心跳 */
        if (g_heartbeatEnabled) {
            uint32_t now = Platform::SysTick_::tickMs();
            if (Platform::SysTick_::elapsed(g_lastHeartbeat) >= 1000) {
                g_lastHeartbeat = now;
                sendHeartbeat(now);
            }
        }
    }

    CommandDispatcher() = delete;

private:
    /**
     * @brief CommandParser 的 Handler 实现
     */
    struct DispatcherHandler {
        static uint8_t paramLen(uint8_t cmd) noexcept {
            return FrameCodec::downlinkParamLen(cmd);
        }

        static void onCommand(uint8_t cmd, const uint8_t* param,
                              uint8_t len) noexcept {
            switch (cmd) {
            case 0x01: { /** MaxCount: pump_id(1) + count(4) */
                if (len < 5) { sendNak(cmd); break; }
                uint8_t id = param[0];
                uint32_t cnt = readU32(param + 1);
                if (id == 1) Device::PumpMotor1::start(Device::PumpMode::MaxCount, cnt);
                else if (id == 2) Device::PumpMotor2::start(Device::PumpMode::MaxCount, cnt);
                else { sendNak(cmd); break; }
                sendAck(cmd);
                break;
            }
            case 0x02: { /** FreeRun: pump_id(1) */
                if (len < 1) { sendNak(cmd); break; }
                uint8_t id = param[0];
                if (id == 1) Device::PumpMotor1::start(Device::PumpMode::FreeRun);
                else if (id == 2) Device::PumpMotor2::start(Device::PumpMode::FreeRun);
                else { sendNak(cmd); break; }
                sendAck(cmd);
                break;
            }
            case 0x03: /** FreeStop: 正常停止，pump_id(1), 0xFF=全部 */
            case 0x04: { /** AbortAll: 紧急停止，功能等价于 0x03 但语义不同，pump_id(1), 0xFF=全部 */
                if (len < 1) { sendNak(cmd); break; }
                uint8_t id = param[0];
                if (id == 0xFF) {
                    Device::PumpMotor1::stop();
                    Device::PumpMotor2::stop();
                } else if (id == 1) {
                    Device::PumpMotor1::stop();
                } else if (id == 2) {
                    Device::PumpMotor2::stop();
                } else {
                    sendNak(cmd); break;
                }
                sendAck(cmd);
                break;
            }
            case 0x05: { /** Heartbeat: 0x01=使能看门狗+心跳上报，0x00=关闭 */
                if (len < 1) { sendNak(cmd); break; }
                bool en = (param[0] != 0);
                g_heartbeatEnabled = en;
                g_watchdogEnabled = en;
                g_lastHeartbeatRx = Platform::SysTick_::tickMs();
                sendAck(cmd);
                break;
            }
            case 0x06: { /** Reset */
                sendAck(cmd);
                /** 等发送完成再复位 */
                Platform::SysTick_::delayMs(10);
                Platform::NVIC_::systemReset();
                break;
            }
            default:
                sendNak(cmd);
                break;
            }
        }

        static void onNak() noexcept {
            /** CRC 错误，不发响应（避免噪声触发回包） */
        }
    };

    /** 上行帧打包发送 */

    /**
     * @brief 发送 ACK 帧
     * @param cmd 回显命令字
     */
    static void sendAck(uint8_t cmd) noexcept {
        uint8_t out[5];
        size_t outLen;
        FrameCodec::packUplink(0x00, &cmd, 1, out, &outLen);
        Device::SerialPort::write(out, outLen);
    }

    /**
     * @brief 发送 NAK 帧
     * @param cmd 回显命令字
     */
    static void sendNak(uint8_t cmd) noexcept {
        uint8_t out[5];
        size_t outLen;
        FrameCodec::packUplink(0x01, &cmd, 1, out, &outLen);
        Device::SerialPort::write(out, outLen);
    }

    /**
     * @brief 发送泵位置帧
     * @param id 泵编号
     * @param pos 脉冲位置
     */
    static void sendPumpPos(uint8_t id, uint32_t pos) noexcept {
        uint8_t data[5];
        data[0] = id;
        writeU32(data + 1, pos);
        uint8_t out[9];
        size_t outLen;
        FrameCodec::packUplink(0x10, data, 5, out, &outLen);
        Device::SerialPort::write(out, outLen);
    }

    /**
     * @brief 发送泵完成帧
     * @param id 泵编号
     * @param pos 完成时的脉冲计数
     */
    static void sendPumpDone(uint8_t id, uint32_t pos) noexcept {
        uint8_t data[5];
        data[0] = id;
        writeU32(data + 1, pos);
        uint8_t out[9];
        size_t outLen;
        FrameCodec::packUplink(0x11, data, 5, out, &outLen);
        Device::SerialPort::write(out, outLen);
    }

    /**
     * @brief 发送 ADC 数据帧
     * @param r 过采样结果
     * @param pump2Pos 采样时刻泵 2 脉冲计数（供上位机体积同步）
     */
    static void sendADC(const Device::ADCOversample::Result& r,
                        uint32_t pump2Pos) noexcept {
        uint8_t data[11];
        writeU32(data, r.sum);
        writeU16(data + 4, r.samples);
        data[6] = r.shift;
        writeU32(data + 7, pump2Pos);
        uint8_t out[15];
        size_t outLen;
        FrameCodec::packUplink(0x20, data, 11, out, &outLen);
        Device::SerialPort::write(out, outLen);
    }

    /**
     * @brief 发送光谱数据帧
     * @param s 光谱测量结果
     */
    static void sendSpectral(const Device::AS7341::SpectralData& s) noexcept {
        uint8_t data[22];
        writeU16(data + 0, s.nm415);
        writeU16(data + 2, s.nm445);
        writeU16(data + 4, s.nm480);
        writeU16(data + 6, s.nm515);
        writeU16(data + 8, s.nm555);
        writeU16(data + 10, s.nm590);
        writeU16(data + 12, s.nm630);
        writeU16(data + 14, s.nm680);
        writeU16(data + 16, s.Clear);
        writeU16(data + 18, s.nm910);
        /** 占位 2 字节（保留） */
        data[20] = 0;
        data[21] = 0;
        uint8_t out[26];
        size_t outLen;
        FrameCodec::packUplink(0x30, data, 22, out, &outLen);
        Device::SerialPort::write(out, outLen);
    }

    /**
     * @brief 发送心跳帧
     * @param uptimeMs 运行时间（毫秒）
     */
    static void sendHeartbeat(uint32_t uptimeMs) noexcept {
        uint8_t data[4];
        writeU32(data, uptimeMs);
        uint8_t out[8];
        size_t outLen;
        FrameCodec::packUplink(0x40, data, 4, out, &outLen);
        Device::SerialPort::write(out, outLen);
    }

    /** 字节序辅助（小端） */

    /**
     * @brief 从字节流读取 32 位小端无符号整数
     * @param p 字节流指针
     * @return 32 位值
     */
    static uint32_t readU32(const uint8_t* p) noexcept {
        return static_cast<uint32_t>(p[0]) |
               (static_cast<uint32_t>(p[1]) << 8) |
               (static_cast<uint32_t>(p[2]) << 16) |
               (static_cast<uint32_t>(p[3]) << 24);
    }

    /**
     * @brief 向字节流写入 32 位小端无符号整数
     * @param p 字节流指针
     * @param v 待写入值
     */
    static void writeU32(uint8_t* p, uint32_t v) noexcept {
        p[0] = static_cast<uint8_t>(v);
        p[1] = static_cast<uint8_t>(v >> 8);
        p[2] = static_cast<uint8_t>(v >> 16);
        p[3] = static_cast<uint8_t>(v >> 24);
    }

    /**
     * @brief 向字节流写入 16 位小端无符号整数
     * @param p 字节流指针
     * @param v 待写入值
     */
    static void writeU16(uint8_t* p, uint16_t v) noexcept {
        p[0] = static_cast<uint8_t>(v);
        p[1] = static_cast<uint8_t>(v >> 8);
    }

    inline static volatile bool g_heartbeatEnabled{false};
    inline static volatile uint32_t g_lastHeartbeat{0};
    inline static volatile bool g_watchdogEnabled{false};
    inline static volatile uint32_t g_lastHeartbeatRx{0};

    /** 看门狗超时：上位机心跳间隔 1s，5s 未收到判定断线 */
    static constexpr uint32_t WATCHDOG_TIMEOUT_MS = 5000;
};

} // namespace Protocol
