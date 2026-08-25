# Hardware Wiring

[中文](hardware-wiring.md) | English

This document describes the pin assignments of the titrator main unit, for people assembling a prototype or debugging wiring. The firmware hard-codes these assignments; if you change the circuit, update the firmware first.

## 1. Pin assignments

| Peripheral | Pin | Direction | Notes |
|------------|-----|-----------|-------|
| USART1 | PA9 (TX) / PA10 (RX) | output / input | Host serial port, 115200-8N1 |
| I2C1 | PB8 (SCL) / PB9 (SDA) | open-drain | AS7341 spectral sensor, 100kHz, requires AFIO remap |
| ADC1 | PA0 | input | Potential measurement, triggered by TIM3 |
| TIM3 | — | — | ADC trigger time base, 1kHz |
| TIM4 | PB6 (CH1) / PB7 (CH2) | output | Dual-pump PWM, 1kHz, 50% duty |
| DMA1_CH5 | — | — | USART1 receive DMA |
| GPIO | PC13 | output | LED status indicator |

## 2. Wiring notes

### Serial port (USART1)

PA9 goes to the RX of a USB-serial adapter, PA10 to its TX, and the grounds are shared. This port talks to the host application at a fixed 115200 baud. Note that these pins use the alternate-function mode; do not mix them with the I2C or PWM pins.

### Spectral sensor (I2C1 → AS7341)

Connect PB8 (SCL) and PB9 (SDA) to the matching AS7341 pins, and pull both up to 3.3V (open-drain mode). I2C1 needs the AFIO remap, which the firmware already does in `AFIO::MAPR::WriteI2C1_REMAP(1)`. The AS7341 address is 0x39 (7-bit).

### Potential measurement (ADC1 → PA0)

Connect the electrode to PA0 and wire the reference and ground properly. The potential is analog and sampled by TIM3 at 1kHz. Keep the signal traces away from the pump PWM lines to reduce interference.

### Peristaltic pumps (TIM4 → PB6/PB7)

PB6 (CH1) drives pump 1 (sample pump); PB7 (CH2) drives pump 2 (titrant pump). The PWM runs at 1kHz with a 50% duty cycle. The firmware controls start and stop; no external enable pin is needed. Make sure the pump driver board shares a ground.

### LED (PC13)

The on-board LED lights after startup and indicates the system is running.

## 3. Power supply

- The MCU and sensors use 3.3V.
- The peristaltic pump motors need a separate supply (usually 12V) through a driver board.
- The pump and sensor grounds must share the MCU ground, or the PWM signals will be corrupted.

## 4. Notes on rewiring

The pin assignments are scattered across several headers:

| Function | Location |
|----------|----------|
| Serial pins | `GPIO::configure` in `include/hal/UART.hpp` |
| I2C pins | `GPIO::configure` in `include/hal/I2C.hpp` |
| ADC pin | `include/hal/ADC.hpp` |
| Pump PWM | `initTIM4` in `include/hal/TIM.hpp` |
| LED | `src/main.cpp` |

Change them one at a time and run `scons` to verify. The I2C remap, ADC trigger source, and TIM4 channels depend on each other; do not change only one of them.