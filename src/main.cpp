/**
 * @file    main.cpp
 * @brief   应用入口 — STM32F103C8T6 裸机 C++23
 */

#include <device/ADCOversample.hpp>
#include <device/AS7341.hpp>
#include <device/PumpMotor.hpp>
#include <hal/GPIO.hpp>
#include <platform/IWDG.hpp>
#include <platform/NVIC.hpp>
#include <platform/SysTick.hpp>
#include <platform/SystemClock.hpp>
#include <protocol/CommandDispatcher.hpp>

extern "C" int main() {  // NOLINT(clang-diagnostic-main) 裸机 main 由 Reset_Handler bl 调用，必须无 name mangling
    /** 1. 平台初始化 */
    Platform::SystemClock::initialize();
    Platform::SysTick_::initialize();
    Platform::NVIC_::setPriorityGrouping(0);

    /** 2. LED 指示灯（PC13） */
    HAL::GPIO::configure(HAL::GPIO::Port::C, 13, HAL::GPIO::Mode::OutputPP);
    HAL::GPIO::set(HAL::GPIO::Port::C, 13, true);

    /** 3. 设备初始化 */
    Protocol::CommandDispatcher::initialize(); /** 内部调 SerialPort::initialize */
    Device::PumpMotor1::initialize(1000);
    Device::PumpMotor2::initialize(1000);
    Device::ADCOversample::initialize();
    Device::AS7341::initialize();

    /** 4. 启动首轮光谱测量 */
    Device::AS7341::startMeasurement();

    /** 5. 启动独立看门狗（~5s 超时，必须在主循环中周期性喂狗） */
    Platform::IWDG_::initialize();

    /** 6. 主循环 */
    while (true) {
        Protocol::CommandDispatcher::service();
        Device::AS7341::service();
        Device::ADCOversample::service();

        /** 光谱测量完成后自动续采 */
        if (!Device::AS7341::isBusy() && !Device::AS7341::isDataValid()) {
            Device::AS7341::startMeasurement();
        }

        /** 喂狗：主循环每轮刷新看门狗计数器 */
        Platform::IWDG_::reload();
    }
}
