/**
 * @file    Vectors.cpp
 * @brief   Interrupt vector table and startup code for STM32F103C8T6
 *
 * The Cortex-M3 reads SP from the first word of the vector table and
 * PC (Reset_Handler) from the second word at power-on reset.
 * The vector table is placed in the .isr_vector section so the linker
 * positions it at the beginning of FLASH (0x08000000).
 */

#include <cstdint>

// =========================================================================
//  Forward declarations
// =========================================================================

extern "C" int main();

// =========================================================================
//  Linker-defined symbols
// =========================================================================

extern "C" {
    extern std::uint32_t _estack;   // top of stack
    extern std::uint32_t _sidata;   // start of .data LMA  (FLASH)
    extern std::uint32_t _sdata;    // start of .data VMA  (RAM)
    extern std::uint32_t _edata;    // end   of .data      (RAM)
    extern std::uint32_t _sbss;     // start of .bss       (RAM)
    extern std::uint32_t _ebss;     // end   of .bss       (RAM)
}

// =========================================================================
//  C++ init / fini array markers
// =========================================================================

extern "C" {
    using ctor_t = void (*)();

    extern ctor_t __preinit_array_start[];
    extern ctor_t __preinit_array_end[];
    extern ctor_t __init_array_start[];
    extern ctor_t __init_array_end[];
}

// =========================================================================
//  Exception / interrupt handlers
// =========================================================================

extern "C" {

void Reset_Handler(void);
void Default_Handler(void);

// ---- System exceptions (Cortex-M3) --------------------------------------

[[gnu::weak]] void NMI_Handler(void)               { Default_Handler(); }
[[gnu::weak]] void HardFault_Handler(void)         { Default_Handler(); }
[[gnu::weak]] void MemManage_Handler(void)         { Default_Handler(); }
[[gnu::weak]] void BusFault_Handler(void)          { Default_Handler(); }
[[gnu::weak]] void UsageFault_Handler(void)        { Default_Handler(); }
[[gnu::weak]] void SVC_Handler(void)               { Default_Handler(); }
[[gnu::weak]] void DebugMon_Handler(void)          { Default_Handler(); }
[[gnu::weak]] void PendSV_Handler(void)            { Default_Handler(); }
[[gnu::weak]] void SysTick_Handler(void)           { Default_Handler(); }

// ---- Peripheral IRQs (STM32F103x8 medium-density, 43 total) -------------

[[gnu::weak]] void WWDG_IRQHandler(void)               { Default_Handler(); }
[[gnu::weak]] void PVD_IRQHandler(void)                { Default_Handler(); }
[[gnu::weak]] void TAMPER_IRQHandler(void)             { Default_Handler(); }
[[gnu::weak]] void RTC_IRQHandler(void)                { Default_Handler(); }
[[gnu::weak]] void FLASH_IRQHandler(void)              { Default_Handler(); }
[[gnu::weak]] void RCC_IRQHandler(void)                { Default_Handler(); }
[[gnu::weak]] void EXTI0_IRQHandler(void)              { Default_Handler(); }
[[gnu::weak]] void EXTI1_IRQHandler(void)              { Default_Handler(); }
[[gnu::weak]] void EXTI2_IRQHandler(void)              { Default_Handler(); }
[[gnu::weak]] void EXTI3_IRQHandler(void)              { Default_Handler(); }
[[gnu::weak]] void EXTI4_IRQHandler(void)              { Default_Handler(); }
[[gnu::weak]] void DMA1_Channel1_IRQHandler(void)      { Default_Handler(); }
[[gnu::weak]] void DMA1_Channel2_IRQHandler(void)      { Default_Handler(); }
[[gnu::weak]] void DMA1_Channel3_IRQHandler(void)      { Default_Handler(); }
[[gnu::weak]] void DMA1_Channel4_IRQHandler(void)      { Default_Handler(); }
[[gnu::weak]] void DMA1_Channel5_IRQHandler(void)      { Default_Handler(); }
[[gnu::weak]] void DMA1_Channel6_IRQHandler(void)      { Default_Handler(); }
[[gnu::weak]] void DMA1_Channel7_IRQHandler(void)      { Default_Handler(); }
[[gnu::weak]] void ADC1_2_IRQHandler(void)             { Default_Handler(); }
[[gnu::weak]] void USB_HP_CAN1_TX_IRQHandler(void)     { Default_Handler(); }
[[gnu::weak]] void USB_LP_CAN1_RX0_IRQHandler(void)    { Default_Handler(); }
[[gnu::weak]] void CAN1_RX1_IRQHandler(void)           { Default_Handler(); }
[[gnu::weak]] void CAN1_SCE_IRQHandler(void)           { Default_Handler(); }
[[gnu::weak]] void EXTI9_5_IRQHandler(void)            { Default_Handler(); }
[[gnu::weak]] void TIM1_BRK_IRQHandler(void)           { Default_Handler(); }
[[gnu::weak]] void TIM1_UP_IRQHandler(void)            { Default_Handler(); }
[[gnu::weak]] void TIM1_TRG_COM_IRQHandler(void)       { Default_Handler(); }
[[gnu::weak]] void TIM1_CC_IRQHandler(void)            { Default_Handler(); }
[[gnu::weak]] void TIM2_IRQHandler(void)               { Default_Handler(); }
[[gnu::weak]] void TIM3_IRQHandler(void)               { Default_Handler(); }
[[gnu::weak]] void TIM4_IRQHandler(void)               { Default_Handler(); }
[[gnu::weak]] void I2C1_EV_IRQHandler(void)            { Default_Handler(); }
[[gnu::weak]] void I2C1_ER_IRQHandler(void)            { Default_Handler(); }
[[gnu::weak]] void I2C2_EV_IRQHandler(void)            { Default_Handler(); }
[[gnu::weak]] void I2C2_ER_IRQHandler(void)            { Default_Handler(); }
[[gnu::weak]] void SPI1_IRQHandler(void)               { Default_Handler(); }
[[gnu::weak]] void SPI2_IRQHandler(void)               { Default_Handler(); }
[[gnu::weak]] void USART1_IRQHandler(void)             { Default_Handler(); }
[[gnu::weak]] void USART2_IRQHandler(void)             { Default_Handler(); }
[[gnu::weak]] void USART3_IRQHandler(void)             { Default_Handler(); }
[[gnu::weak]] void EXTI15_10_IRQHandler(void)          { Default_Handler(); }
[[gnu::weak]] void RTCAlarm_IRQHandler(void)           { Default_Handler(); }
[[gnu::weak]] void USBWakeUp_IRQHandler(void)          { Default_Handler(); }

// =========================================================================
//  Vector table  (placed at 0x08000000 by linker script)
// =========================================================================

[[gnu::section(".isr_vector"), gnu::used]]
void (* const g_pfnVectors[])(void) = {
    // ----- SP / system exceptions (16 entries) -----
    (void (*)())(&_estack),          // [ 0] Initial SP  (not a handler)
    Reset_Handler,                   // [ 1] Reset
    NMI_Handler,                     // [ 2] NMI
    HardFault_Handler,               // [ 3] HardFault
    MemManage_Handler,               // [ 4] MPU fault
    BusFault_Handler,                // [ 5] Bus fault
    UsageFault_Handler,              // [ 6] Usage fault
    nullptr,                         // [ 7] Reserved
    nullptr,                         // [ 8] Reserved
    nullptr,                         // [ 9] Reserved
    nullptr,                         // [10] Reserved
    SVC_Handler,                     // [11] SVCall
    DebugMon_Handler,                // [12] Debug monitor
    nullptr,                         // [13] Reserved
    PendSV_Handler,                  // [14] PendSV
    SysTick_Handler,                 // [15] SysTick

    // ----- Peripheral IRQs (43 entries for STM32F103x8) -----
    WWDG_IRQHandler,                 // [16]
    PVD_IRQHandler,                  // [17]
    TAMPER_IRQHandler,               // [18]
    RTC_IRQHandler,                  // [19]
    FLASH_IRQHandler,                // [20]
    RCC_IRQHandler,                  // [21]
    EXTI0_IRQHandler,                // [22]
    EXTI1_IRQHandler,                // [23]
    EXTI2_IRQHandler,                // [24]
    EXTI3_IRQHandler,                // [25]
    EXTI4_IRQHandler,                // [26]
    DMA1_Channel1_IRQHandler,        // [27]
    DMA1_Channel2_IRQHandler,        // [28]
    DMA1_Channel3_IRQHandler,        // [29]
    DMA1_Channel4_IRQHandler,        // [30]
    DMA1_Channel5_IRQHandler,        // [31]
    DMA1_Channel6_IRQHandler,        // [32]
    DMA1_Channel7_IRQHandler,        // [33]
    ADC1_2_IRQHandler,               // [34]
    USB_HP_CAN1_TX_IRQHandler,       // [35]
    USB_LP_CAN1_RX0_IRQHandler,      // [36]
    CAN1_RX1_IRQHandler,             // [37]
    CAN1_SCE_IRQHandler,             // [38]
    EXTI9_5_IRQHandler,              // [39]
    TIM1_BRK_IRQHandler,             // [40]
    TIM1_UP_IRQHandler,              // [41]
    TIM1_TRG_COM_IRQHandler,         // [42]
    TIM1_CC_IRQHandler,              // [43]
    TIM2_IRQHandler,                 // [44]
    TIM3_IRQHandler,                 // [45]
    TIM4_IRQHandler,                 // [46]
    I2C1_EV_IRQHandler,              // [47]
    I2C1_ER_IRQHandler,              // [48]
    I2C2_EV_IRQHandler,              // [49]
    I2C2_ER_IRQHandler,              // [50]
    SPI1_IRQHandler,                 // [51]
    SPI2_IRQHandler,                 // [52]
    USART1_IRQHandler,               // [53]
    USART2_IRQHandler,               // [54]
    USART3_IRQHandler,               // [55]
    EXTI15_10_IRQHandler,            // [56]
    RTCAlarm_IRQHandler,             // [57]
    USBWakeUp_IRQHandler,            // [58]
};

// =========================================================================
//  Reset_Handler  —  C/C++ runtime initialisation, then jump to main()
// =========================================================================

void Reset_Handler(void) {
    // 1. Copy .data section from FLASH (LMA) to RAM (VMA)
    auto *src = &_sidata;
    auto *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    // 2. Zero-fill .bss section
    for (dst = &_sbss; dst < &_ebss; ++dst) {
        *dst = 0;
    }

    // 3. Call C++ static constructors
    for (auto fn = __preinit_array_start; fn < __preinit_array_end; ++fn) {
        (*fn)();
    }
    for (auto fn = __init_array_start; fn < __init_array_end; ++fn) {
        (*fn)();
    }

    // 4. Jump to application
    main();

    // Should never return on bare-metal; trap if it does
    while (true) {
    }
}

// =========================================================================
//  Default_Handler  —  catch-all for unhandled interrupts
// =========================================================================

void Default_Handler(void) {
    while (true) {
    }
}

}  // extern "C"
