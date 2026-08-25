/**
 * @file    CommandParser.hpp
 * @brief   下行帧状态机解析器
 */

#pragma once

#include <protocol/FrameCodec.hpp>
#include <cstdint>

namespace Protocol {

/**
 * @brief 下行帧状态机解析器
 *
 * 帧结构：BB 55 | cmd(1) | param[N] | CRC8(1)
 * CRC8 = CRC8(cmd + all param bytes), poly=0x31
 *
 * Handler 需提供：
 *   static uint8_t paramLen(uint8_t cmd) noexcept;
 *   static void onCommand(uint8_t cmd, const uint8_t* param, uint8_t len) noexcept;
 *   static void onNak() noexcept;
 *
 * @tparam Handler 命令处理策略类
 */
template <typename Handler>
class CommandParser {
public:
    /**
     * @brief 输入一个字节，推进状态机
     * @param b 输入字节
     */
    static void feed(uint8_t b) noexcept {
        switch (s_state) {
        case State::Idle:
            if (b == FrameCodec::DOWNLINK_PREAMBLE0) {
                s_state = State::GotBB;
            }
            break;

        case State::GotBB:
            if (b == FrameCodec::DOWNLINK_PREAMBLE1) {
                s_state = State::GotCmd;
            } else if (b == FrameCodec::DOWNLINK_PREAMBLE0) {
                s_state = State::GotBB;
            } else {
                s_state = State::Idle;
            }
            break;

        case State::GotCmd:
            if (Handler::paramLen(b) > MAX_PARAM) {
                s_state = State::Idle;
                break;
            }
            s_cmd = b;
            s_idx = 0;
            s_cs = FrameCodec::crc8Update(0, b);
            s_state = (Handler::paramLen(b) == 0) ? State::GotCS : State::GotParam;
            break;

        case State::GotParam:
            s_param[s_idx] = b;
            s_idx = s_idx + 1;
            s_cs = FrameCodec::crc8Update(s_cs, b);
            if (s_idx >= Handler::paramLen(s_cmd)) {
                s_state = State::GotCS;
            }
            break;

        case State::GotCS:
            s_state = State::Idle;
            if (b != s_cs) {
                Handler::onNak();
                break;
            }
            Handler::onCommand(s_cmd, s_param, s_idx);
            break;
        }
    }

    /**
     * @brief 重置状态机到 Idle
     */
    static void reset() noexcept { s_state = State::Idle; }

    CommandParser() = delete;

private:
    /** 参数最大长度 */
    static constexpr uint8_t MAX_PARAM = 5;

    /**
     * @brief 解析状态
     */
    enum class State : uint8_t { Idle, GotBB, GotCmd, GotParam, GotCS };

    inline static State s_state = State::Idle;
    inline static uint8_t s_cmd = 0;
    inline static uint8_t s_param[MAX_PARAM]{};
    inline static uint8_t s_idx = 0;
    inline static uint8_t s_cs = 0;
};

} // namespace Protocol
