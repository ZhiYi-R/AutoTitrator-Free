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
// (single-threaded bare-metal: no lock needed)
// ---------------------------------------------------------------------------
int __cxa_guard_acquire(std::int64_t* g) {
    return !(*g);  // return 1 if not yet initialised
}

void __cxa_guard_release(std::int64_t* g) {
    *g = 1;
}

void __cxa_guard_abort(std::int64_t* g) {
    (void)g;
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
