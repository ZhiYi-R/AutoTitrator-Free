/**
 * @file    CXXStubs.cpp
 * @brief   Minimal C++ runtime support stubs for bare-metal (no libstdc++)
 *
 * Provides the symbols the compiler expects when using C++ features
 * with -nostdlib.  Users may override any of these in their own code.
 */

#include <cstddef>
#include <cstdint>

extern "C" {

// ---------------------------------------------------------------------------
// __cxa_pure_virtual  —  called when a pure virtual function is invoked
// ---------------------------------------------------------------------------
void __cxa_pure_virtual() {
    while (true) {
    }
}

// ---------------------------------------------------------------------------
// __cxa_atexit  —  register at-exit handler (no-op on bare-metal)
// ---------------------------------------------------------------------------
int __cxa_atexit(void (*)(void*), void*, void*) {
    return 0;
}

// ---------------------------------------------------------------------------
// Guard variable support for function-local static variables
// (single-threaded bare-metal with interrupts: save/restore PRIMASK)
// ---------------------------------------------------------------------------

static uint32_t disableIrqSave() noexcept {
    uint32_t primask;
    __asm volatile("mrs %0, primask\n\tcpsid i"
                   : "=r"(primask)
                   :
                   : "memory");
    return primask;
}

static void restoreIrq(uint32_t primask) noexcept {
    __asm volatile("msr primask, %0" : : "r"(primask) : "memory");
}

/** 保存最近一次 __cxa_guard_acquire 的 PRIMASK，供 release/abort 恢复。
 *  单线程裸机中同一时刻只有一个静态对象在构造（因已关中断），全局变量足够。 */
static uint32_t g_guardPrimask{0};

int __cxa_guard_acquire(std::int64_t* g) {
    auto* p = reinterpret_cast<std::uint8_t*>(g);
    g_guardPrimask = disableIrqSave();
    if (*p == 0) {
        *p = 1;  // 构造中
        return 1;
    }
    restoreIrq(g_guardPrimask);
    return 0;
}

void __cxa_guard_release(std::int64_t* g) {
    auto* p = reinterpret_cast<std::uint8_t*>(g);
    *p = 1;  // 已构造完成
    restoreIrq(g_guardPrimask);
}

void __cxa_guard_abort(std::int64_t* g) {
    auto* p = reinterpret_cast<std::uint8_t*>(g);
    *p = 0;  // 重置
    restoreIrq(g_guardPrimask);
}

}  // extern "C"

// ---------------------------------------------------------------------------
// Dynamic memory operators  —  trap if called (no heap by default)
// users should override these if dynamic allocation is needed.
// NOTE: C++23 requires operator new to never return nullptr unless
//       'noexcept' or '-fcheck-new' is used. We use '-fcheck-new'
//       in SConstruct to suppress this warning.
// ---------------------------------------------------------------------------

void* operator new(std::size_t size) {
    (void)size;
    while (true) {
    }
    return nullptr;  // NOLINT(clang-diagnostic-new-returns-null) 裸机无堆，operator new 不可达，仅满足链接
}

void* operator new[](std::size_t size) {
    return operator new(size);
}

void operator delete(void* ptr) noexcept {
    (void)ptr;
}

void operator delete[](void* ptr) noexcept {
    (void)ptr;
}

void operator delete(void* ptr, std::size_t) noexcept {
    (void)ptr;
}

void operator delete[](void* ptr, std::size_t) noexcept {
    (void)ptr;
}
