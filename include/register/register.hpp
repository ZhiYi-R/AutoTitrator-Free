#pragma once

#include "atomic.hpp"
#include "concepts.hpp"
#include "field.hpp"        // IWYU pragma: keep
#include <concepts>
#include <cstdint>
#include <type_traits>      // IWYU pragma: keep

namespace CortexM3 {

/**
 * @brief 内存映射寄存器抽象
 *
 * @tparam T       寄存器值类型（uint8_t / uint16_t / uint32_t）
 * @tparam Address 寄存器绝对地址
 */
template <RegisterValue T, std::uintptr_t Address>
struct Register {
    Register() = delete;
    Register(Register const&) = delete;
    Register& operator=(Register const&) = delete;
    Register(Register&&) = delete;
    Register& operator=(Register&&) = delete;

    using ValueType = T;
    static constexpr std::uintptr_t AddressValue = Address;

    /**
     * @brief 读取寄存器原始值
     */
    static auto Read() noexcept -> T {
        return *reinterpret_cast<volatile T*>(Address);
    }

    /**
     * @brief 整寄存器写入（对齐写天然原子）
     */
    static void Write(T value) noexcept {
        *reinterpret_cast<volatile T*>(Address) = value;
    }

    /**
     * @brief 读取指定字段值
     */
    template <BitField Field>
        requires std::same_as<typename Field::ValueType, ValueType>
    static auto Read() noexcept -> T {
        return (Read() & Field::Mask()) >> Field::PositionValue;
    }

    /**
     * @brief 使用 LDREX/STREX 原子 RMW 写入字段
     */
    template <BitField Field>
        requires std::same_as<typename Field::ValueType, ValueType>
    static void Write(typename Field::ValueType value) noexcept {
        volatile T* reg = reinterpret_cast<volatile T*>(Address);
        T old_value;
        T new_value;
        do {
            old_value = LoadExclusive(reg);
            new_value = (old_value & ~Field::Mask())
                      | ((static_cast<T>(value) << Field::PositionValue) & Field::Mask());
        } while (!StoreExclusive(reg, new_value));
    }

    /**
     * @brief 使用 LDREX/STREX 原子 RMW 置位
     */
    static void Set(T bits) noexcept {
        Modify(bits, T{0});
    }

    /**
     * @brief 使用 LDREX/STREX 原子 RMW 清零
     */
    static void Clear(T bits) noexcept {
        Modify(T{0}, bits);
    }

    /**
     * @brief 使用 LDREX/STREX 原子 RMW 同时置位和清零
     */
    static void Modify(T set_bits, T clear_bits) noexcept {
        volatile T* reg = reinterpret_cast<volatile T*>(Address);
        T old_value;
        T new_value;
        do {
            old_value = LoadExclusive(reg);
            new_value = (old_value & ~clear_bits) | set_bits;
        } while (!StoreExclusive(reg, new_value));
    }
};

} // namespace CortexM3
