# AutoTitrator-Free

[中文](README.md) | English

A multimodal automatic titration controller. The STM32F103 bare-metal firmware drives the sample and titrant peristaltic pumps and samples the potential and spectral signals. The Rust/Tauri host application performs online endpoint detection on both signals and provides pump calibration, concentration calculation, and data recording.

## Project overview

| Item | Value |
|------|-------|
| MCU | STM32F103C8T6 (ARM Cortex-M3) |
| Flash | 64 KB @ 0x08000000 |
| RAM | 20 KB @ 0x20000000 |
| Toolchain | GCC ARM (`arm-none-eabi-g++`) |
| Language | C++23, bare-metal, no HAL / no RTOS / no heap |
| Build system | SCons |
| Debugger | ST-Link V2 (SWD) |
| Host | Rust/Tauri 2 + Next.js |
| License | [PolyForm Shield 1.0.0](LICENSE) |

## Documentation

| Document | Audience | Contents |
|----------|----------|----------|
| [Host User Guide](docs/host-user-guide_EN.md) | people running experiments | installation, connection, calibration, titration, export, troubleshooting |
| [Communication Protocol](docs/protocol_EN.md) | people integrating the protocol | frame formats, command table, timing, retries |
| [Firmware Development Guide](docs/firmware-dev-guide_EN.md) | firmware developers | code layout, initialization, register layer, interrupts, protocol extension |
| [Hardware Wiring](docs/hardware-wiring_EN.md) | people assembling prototypes | pin assignments, wiring notes, power supply |
| [Calibration and Data Formats](docs/data-formats_EN.md) | people working with data | calibre.npz structure, sidecar, settings.json |
| [Algorithm Technical Report](docs/algorithm-report_EN.md) | developers interested in the algorithm | multimodal fusion, endpoint detection, parameters, verification |

## Directory layout

```
AutoTitrator-Free
├── SConstruct              # SCons build script
├── Startup/                # startup code, vector table, linker script
│   ├── Vectors.cpp
│   ├── linker.ld
│   └── CXXStubs.cpp
├── src/                    # firmware application source
│   ├── main.cpp            # main loop entry
│   └── Interrupts.cpp      # interrupt handlers
├── include/                # headers
│   ├── register/           # Cortex-M3 register/MMIO abstraction
│   ├── stm32f103/          # 61 peripheral headers generated from SVD
│   ├── platform/           # system clock, SysTick, NVIC helpers
│   ├── hal/                # peripheral HAL drivers
│   ├── device/             # device-level drivers
│   └── protocol/           # communication protocol stack
├── TController/            # Rust/Tauri host
│   ├── crates/controller-core/ # protocol, detection, reconstruction, workflow
│   ├── app/src-tauri/      # Tauri commands and backend state
│   ├── app/ui-next/        # Next.js instrument workbench
│   └── data/               # calibre.npz and runtime state
├── scripts/                # code generation scripts
│   └── generate_stm32f103.py   # generate peripheral headers from CMSIS-SVD
├── requirements-dev.txt    # firmware build and register generation deps
├── openocd.cfg             # OpenOCD debug configuration
├── .gdbinit                # GDB init script
├── README.md
└── LICENSE
```

## Firmware architecture

### 1. Register abstraction layer

Located in `include/register/`, a header-only, pure C++23, zero-overhead MMIO abstraction:

- `CortexM3::Register<T, Address>`: whole-register read/write, field read/write, atomic `Set` / `Clear` / `Modify`.
- `CortexM3::Field<T, Position, Width>`: bitfield type; `Mask()` is computed at compile time.
- `atomic.hpp`: 8/16/32-bit atomic read-modify-write via `LDREX` / `STREX`.

### 2. Peripheral header generation

The 61 peripheral headers under `include/stm32f103/` are generated automatically from CMSIS-SVD by `scripts/generate_stm32f103.py`:

```sh
uv run scripts/generate_stm32f103.py
```

Each register becomes a pure static singleton class. `Read` / `Write` and per-bitfield accessors are generated from the SVD `<access>` attribute, in the namespace `STM32F103::{Peripheral}`.

### 3. HAL layer

| File | Peripheral | Notes |
|------|------------|-------|
| `include/hal/GPIO.hpp` | GPIO | port mode / pull / speed configuration, set / read |
| `include/hal/UART.hpp` | USART1 | RX via DMA1_CH5 circular + IDLE interrupt, TX via TXE interrupt byte by byte |
| `include/hal/I2C.hpp` | I2C1 | 100 kHz, PB8/PB9, synchronous blocking + asynchronous interrupt modes |
| `include/hal/TIM.hpp` | TIM3 / TIM4 | TIM3 as ADC trigger time base, TIM4 dual-channel PWM driving the peristaltic pumps |
| `include/hal/ADC.hpp` | ADC1 | single channel PA0, TIM3_TRGO trigger, EOC interrupt |

### 4. Device drivers and protocol stack

| File | Function |
|------|----------|
| `include/device/PumpMotor.hpp` | two peristaltic pump drivers (TIM4 CH1/CH2), MaxCount / FreeRun modes |
| `include/device/ADCOversample.hpp` | 256-sample ADC accumulation oversampling, right-shift 4 to output 16-bit result |
| `include/device/AS7341.hpp` | AS7341 spectral sensor driver, two-phase SMUX scan state machine |
| `include/device/SerialPort.hpp` | ring-buffer RX + interrupt-driven byte-by-byte TX |
| `include/protocol/CommandDispatcher.hpp` | parses downlink commands, calls device APIs, packs uplink data |
| `include/protocol/FrameCodec.hpp` | CRC-8 (Maxim-Dallas, poly = 0x31) encode/decode |
| `include/protocol/CommandParser.hpp` | downlink frame state-machine parser |

### 5. Interrupt assignment

| Interrupt | Priority | Purpose |
|-----------|----------|---------|
| USART1 | 0 | IDLE reception + TXE transmission |
| DMA1_Channel5 | 0 | USART1 RX DMA half/full |
| TIM4 | 1 | pump pulse counting |
| ADC1_2 | 2 | ADC conversion complete |
| I2C1_EV / I2C1_ER | 2 | AS7341 asynchronous I2C |
| SysTick | 15 | 1 ms tick |

All interrupt handlers are declared as `[[gnu::weak]]` weak symbols in `Startup/Vectors.cpp`, defaulting to `Default_Handler`. Define an `extern "C"` function with the same name in any `.cpp` to override.

### 6. Main loop

`src/main.cpp` initializes the clock, SysTick, LED, UART, pumps, ADC oversampling, and AS7341, then polls the protocol, spectrum, and ADC services in the main loop, starting the next spectral sweep automatically when one finishes.

## Build and flashing

### Firmware build

The `arm-none-eabi` toolchain must be on the PATH:

```sh
scons
# or specify a prefix
scons CROSS=arm-none-eabi-
```

Artifacts land in `build/`:

- `AutoTitrator-Firmware.elf` — executable (with debug info)
- `AutoTitrator-Firmware.hex` — Intel HEX
- `AutoTitrator-Firmware.map` — memory map
- `AutoTitrator-Firmware.lst` — disassembly listing

Clean:

```sh
scons -c
```

### Flashing and debugging

```sh
# Terminal 1 - start OpenOCD
cd D:/Projects/AutoTitrator/Firmware
openocd -f openocd.cfg

# Terminal 2 - connect GDB
arm-none-eabi-gdb build/AutoTitrator-Firmware.elf -x .gdbinit
```

### Register generation tool

The register header generator needs `cmsis-svd`; install the development dependencies with:

```sh
uv pip install -r requirements-dev.txt
uv run scripts/generate_stm32f103.py
```

## Host application (TController)

The Rust/Tauri host communicates with the MCU over a serial port and provides:

- live spectral and potential curves
- online titration endpoint detection
- dual-pump control with progress display
- pump calibration and pH electrode calibration
- state persistence, run history, and reliability diagnostics

### Main modules

| Directory | Function |
|-----------|----------|
| `TController/crates/controller-core/src/protocol/` | serial thread, protocol frame parsing and retries |
| `TController/crates/controller-core/src/processing/` | endpoint detection, spectral reconstruction, pump calibration |
| `TController/crates/controller-core/src/workflow.rs` | titration workflow and pump-control state machine |
| `TController/app/src-tauri/` | backend state snapshot, commands, persistence |
| `TController/app/ui-next/` | Next.js instrument workbench |

### Tech stack

| Component | Technology |
|-----------|------------|
| UI framework | Tauri 2 + Next.js |
| State management | Rust backend snapshot + Zustand view cache |
| Numerics | Rust ndarray / ndarray-npy |
| Serial communication | Rust serialport |

### Running

```sh
cd TController/app/src-tauri
cargo tauri dev       # starts the Next.js dev server automatically
cargo tauri build     # runs the Next.js static export and packages the Tauri app
```

To verify the frontend on its own, run `npm run build` or `npm run lint` under `TController/app/ui-next`. A browser accessing the Next dev server directly uses the explicit mock adapter; the real Tauri environment always uses the Rust backend snapshot as the source of truth.

### App icons

The PNG and ICO files under `TController/app/src-tauri/icons/` are generated from `icon.svg` in the same directory by `scripts/gen_app_icons.mjs`. The generated files are committed and CI does not regenerate them. To change the icon, edit `icon.svg` and rerun locally:

```sh
cd TController/app/ui-next && npm ci   # the script reuses the frontend's sharp
cd ../../.. && node scripts/gen_app_icons.mjs
```

`bundle.icon` must contain at least one square PNG: the tauri-bundler Linux branch skips non-PNG icons, and the AppImage packager panics if it cannot find a square PNG. macOS needs no separate `.icns`; when the list has no `.icns`, the packager synthesizes the ICNS from the PNGs.

## Continuous integration and releases

`.github/workflows/build.yml` runs on pushes to any branch, on pull requests, and on `RELEASE-*` tags. It builds the firmware and the host in parallel across platforms (`fail-fast: false`; one failing build target does not affect the others).

| Build target | Runner | Artifacts |
|--------------|--------|-----------|
| Firmware cortex-m3 | `ubuntu-24.04` | `.elf` `.hex` (`.map` `.lst` saved as CI artifacts, not in the Release) |
| Host Windows x86_64 | `windows-latest` | `.msi` `-setup.exe` `-portable.zip` |
| Host Windows aarch64 | `windows-11-arm` | `-setup.exe` `-portable.zip` |
| Host Linux x86_64 | `ubuntu-24.04` | `.deb` `.rpm` `.tar.gz` `.AppImage` |
| Host Linux aarch64 | `ubuntu-24.04-arm` | `.deb` `.rpm` `.tar.gz` `.AppImage` |
| Host macOS aarch64 | `macos-15` | `.dmg` `.app.zip` |
| Host macOS x86_64 | `macos-15-intel` | `.dmg` `.app.zip` |

The six host build targets all run on native-architecture runners; there is no cross-compilation, because the Tauri AppImage, MSI, and DMG packagers cannot work cross-architecture.

To release, push a `RELEASE-*` tag. After all builds succeed, the `release` job collects every artifact, generates `SHA256SUMS`, and creates a GitHub Release. If any platform fails, nothing is published, so a Release never covers only some platforms.

Known constraints:

- **Windows aarch64 only produces NSIS.** WiX v3's arm64 support is not validated on Windows on ARM, and Tauri officially guarantees NSIS for ARM64 only.
- **`.tar.gz` is packed by CI itself.** Tauri has no tar.gz target, so CI unpacks the `.deb` file tree and repacks it. The contents match the deb; install with `sudo tar -xzf TController_*.tar.gz -C /` (install dependencies yourself).
- **The Linux glibc floor is 2.39** (Ubuntu 24.04 and newer). 24.04 was chosen over 22.04 because the 22.04 image enters deprecation on 2026-09-17; supporting older distributions means switching back to 22.04 or using container builds.
- **The macOS floor is 10.13 (High Sierra)**, set by `bundle.macOS.minimumSystemVersion` and written to both `LSMinimumSystemVersion` and `MACOSX_DEPLOYMENT_TARGET`. This is the lowest the current toolchain supports: Apple's SDK table lists macOS 10.13-15 for Xcode 16.x (12.0 from Xcode 27 on), and the Tauri packager's default floor is also 10.13. So both macOS build targets stay on `macos-15` (Xcode 16.x), not `macos-latest`.
  Note that Tauri officially documents support for **macOS 10.15 (Catalina) and newer** in its Prerequisites page; 10.13 / 10.14 is allowed by the toolchain but not verified upstream. If it fails to launch on 10.13/10.14, set `minimumSystemVersion` to `"10.15"`; Apple Silicon machines are already 11.0 minimum and are unaffected.
- **macOS artifacts are unsigned and unnotarized.** The repository has no Apple developer certificate; Tauri signs only when `APPLE_CERTIFICATE` is set. First launch requires right-clicking "Open", or running `xattr -dr com.apple.quarantine /Applications/TController.app`. To enable signing, add `APPLE_CERTIFICATE` / `APPLE_CERTIFICATE_PASSWORD` / `APPLE_SIGNING_IDENTITY` secrets to the workflow.

## Notes

- **No HAL / no standard library**: all peripheral registers are accessed through the custom abstraction layer.
- **Heap**: `new` / `delete` trigger an infinite loop by default; implement dynamic allocation in `Startup/CXXStubs.cpp` if needed.
- **Static construction**: `.init_array` runs before `main()` via `Reset_Handler`, so global C++ object constructors work.

## License

This project is licensed under [PolyForm Shield 1.0.0](LICENSE).

- Permitted for personal learning, research, and internal use
- Prohibited from being offered as a competing product, including derivatives
- Redistribution must include the full license text or its URL
