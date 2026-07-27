#pragma once

#include <concepts>
#include <cstdint>

namespace CortexM3 {

/**
 * @brief 约束可作为寄存器值类型的无符号整数
 */
template <typename T>
concept RegisterValue = std::unsigned_integral<T>;

/**
 * @brief 约束一个类型是否为合法的位域描述类
 *
 * 要求：
 * - 存在 ValueType 且为无符号整数
 * - PositionValue / FieldWidth 可转换为 std::uint8_t
 * - Mask() 返回 ValueType，且为 consteval
 * - 位域不越界
 */
template <typename T>
concept BitField = requires {
    typename T::ValueType;
    requires RegisterValue<typename T::ValueType>;
    { T::PositionValue } -> std::convertible_to<std::uint8_t>;
    { T::FieldWidth }    -> std::convertible_to<std::uint8_t>;
    { T::Mask() }        -> std::same_as<typename T::ValueType>;
} && (T::PositionValue + T::FieldWidth <= sizeof(typename T::ValueType) * 8);

} // namespace CortexM3
