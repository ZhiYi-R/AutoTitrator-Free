#pragma once

#include <concepts>

namespace CortexM3 {

/**
 * @brief 使用 ARMv7-M LDREX/STREX 指令实现独占加载
 *
 * 根据模板参数宽度在编译期选择 LDREX / LDREXH / LDREXB。
 */
template <std::unsigned_integral T>
inline T LoadExclusive(volatile T* ptr) noexcept {
    T result;
    if constexpr (sizeof(T) == 1) {
        asm volatile("ldrexb %0, [%1]" : "=r"(result) : "r"(ptr) : "memory");
    } else if constexpr (sizeof(T) == 2) {
        asm volatile("ldrexh %0, [%1]" : "=r"(result) : "r"(ptr) : "memory");
    } else {
        asm volatile("ldrex %0, [%1]" : "=r"(result) : "r"(ptr) : "memory");
    }
    return result;
}

/**
 * @brief 使用 ARMv7-M STREX/STREXH/STREXB 指令实现独占存储
 *
 * @return true  存储成功
 * @return false 存储失败（需重试）
 */
template <std::unsigned_integral T>
inline bool StoreExclusive(volatile T* ptr, T value) noexcept {
    T result;
    if constexpr (sizeof(T) == 1) {
        asm volatile("strexb %0, %2, [%1]" : "=&r"(result) : "r"(ptr), "r"(value) : "memory");
    } else if constexpr (sizeof(T) == 2) {
        asm volatile("strexh %0, %2, [%1]" : "=&r"(result) : "r"(ptr), "r"(value) : "memory");
    } else {
        asm volatile("strex %0, %2, [%1]" : "=&r"(result) : "r"(ptr), "r"(value) : "memory");
    }
    return result == 0;
}

} // namespace CortexM3
