#pragma once

#include "concepts.hpp"
#include <cstdint>

namespace CortexM3 {

/**
 * @brief 寄存器位域描述类（纯数据类，无操作）
 *
 * @tparam T     寄存器值类型
 * @tparam Position  字段起始位
 * @tparam Width     字段宽度（bit）
 */
template <RegisterValue T, std::uint8_t Position, std::uint8_t Width>
struct Field {
    Field() = delete;
    Field(Field const&) = delete;
    Field& operator=(Field const&) = delete;
    Field(Field&&) = delete;
    Field& operator=(Field&&) = delete;

    using ValueType = T;
    static constexpr std::uint8_t PositionValue = Position;
    static constexpr std::uint8_t FieldWidth    = Width;

    /**
     * @brief 计算字段掩码，consteval 强制编译期求值
     */
    static consteval T Mask() noexcept {
        if constexpr (Width >= sizeof(T) * 8) {
            return ~T{0};
        } else {
            return ((T{1} << Width) - 1) << Position;
        }
    }
};

} // namespace CortexM3
