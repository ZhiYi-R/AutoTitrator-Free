#pragma once

/**
 * @brief Cortex-M3 寄存器/MMIO 抽象层聚合入口
 *
 * 包含：
 * - concepts.hpp：RegisterValue / BitField concept
 * - field.hpp：Field<T, Position, Width>
 * - register.hpp：Register<T, Address>
 * - atomic.hpp：LDREX/STREX 原语封装
 */

#include "concepts.hpp"     // IWYU pragma: keep
#include "field.hpp"        // IWYU pragma: keep
#include "register.hpp"     // IWYU pragma: keep
