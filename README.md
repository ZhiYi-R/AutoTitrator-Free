# AutoTitrator-Free

多模态自动滴定控制器 —— STM32F103 裸机固件 + Rust/Tauri 上位机。

## 项目概览

| 项目 | 值 |
|------|-----|
| MCU | STM32F103C8T6 (ARM Cortex-M3) |
| Flash | 64 KB @ 0x08000000 |
| RAM | 20 KB @ 0x20000000 |
| 工具链 | GCC ARM (`arm-none-eabi-g++`) |
| 语言标准 | C++23，裸机，无 HAL / 无 RTOS / 无堆 |
| 构建系统 | SCons |
| 调试器 | ST-Link V2 (SWD) |
| 上位机 | Rust/Tauri 2 + Next.js |
| 授权 | [PolyForm Shield 1.0.0](LICENSE) |

## 目录结构

```
AutoTitrator-Free
├── SConstruct              # SCons 构建脚本
├── Startup/                # 启动代码、中断向量表、链接脚本
│   ├── Vectors.cpp
│   ├── linker.ld
│   └── CXXStubs.cpp
├── src/                    # 固件应用源码
│   ├── main.cpp            # 主循环入口
│   └── Interrupts.cpp      # 中断处理函数
├── include/                # 头文件
│   ├── register/           # Cortex-M3 寄存器/MMIO 抽象层
│   ├── stm32f103/          # 从 SVD 自动生成的 61 个外设头文件
│   ├── platform/           # 系统时钟、SysTick、NVIC 辅助
│   ├── hal/                # 外设 HAL 驱动
│   ├── device/             # 设备级驱动
│   └── protocol/           # 通信协议栈
├── TController/            # Rust/Tauri 上位机
│   ├── crates/controller-core/ # 协议、检测、重建与工作流
│   ├── app/src-tauri/      # Tauri 命令与后端状态
│   ├── app/ui-next/        # Next.js 仪器工作台
│   └── data/               # calibre.npz 与运行时状态
├── scripts/                # 代码生成脚本
│   └── generate_stm32f103.py   # 从 CMSIS-SVD 生成外设头文件
├── requirements-dev.txt    # 固件构建与寄存器生成依赖
├── openocd.cfg             # OpenOCD 调试配置
├── .gdbinit                # GDB 初始化脚本
├── README.md
└── LICENSE
```

## 固件架构

### 1. 寄存器抽象层

位于 `include/register/`，为 header-only、纯 C++23、零运行时开销的 MMIO 抽象：

- `CortexM3::Register<T, Address>`：整寄存器读写、位域读写、原子 `Set` / `Clear` / `Modify`。
- `CortexM3::Field<T, Position, Width>`：位域类型，`Mask()` 在编译期计算。
- `atomic.hpp`：通过 `LDREX` / `STREX` 实现 8/16/32 位原子 RMW。

### 2. 外设头文件生成

`include/stm32f103/` 下 61 个外设头文件由 `scripts/generate_stm32f103.py` 从 CMSIS-SVD 自动生成：

```sh
uv run scripts/generate_stm32f103.py
```

每个寄存器对应一个纯静态单例类，按 SVD `<access>` 属性生成 `Read` / `Write` 与按位域访问方法，命名空间为 `STM32F103::{Peripheral}`。

### 3. HAL 层

| 文件 | 外设 | 说明 |
|------|------|------|
| `include/hal/GPIO.hpp` | GPIO | 端口模式/上下拉/速度配置、置位/读取 |
| `include/hal/UART.hpp` | USART1 | RX 用 DMA1_CH5 循环 + IDLE 中断，TX 用 TXE 中断逐字节 |
| `include/hal/I2C.hpp` | I2C1 | 100 kHz，PB8/PB9，同步阻塞 + 异步中断双模式 |
| `include/hal/TIM.hpp` | TIM3 / TIM4 | TIM3 作为 ADC 触发时基，TIM4 双通道 PWM 驱动蠕动泵 |
| `include/hal/ADC.hpp` | ADC1 | 单通道 PA0，TIM3_TRGO 触发，EOC 中断 |

### 4. 设备驱动与协议栈

| 文件 | 功能 |
|------|------|
| `include/device/PumpMotor.hpp` | 两个蠕动泵驱动（TIM4 CH1/CH2），支持 MaxCount / FreeRun |
| `include/device/ADCOversample.hpp` | 256 次 ADC 累加过采样，右移 4 位输出 16-bit 结果 |
| `include/device/AS7341.hpp` | AS7341 光谱传感器驱动，两 phase SMUX 扫描状态机 |
| `include/device/SerialPort.hpp` | 环形缓冲 RX + 中断逐字节 TX |
| `include/protocol/CommandDispatcher.hpp` | 解析下行命令、调用设备 API、打包上行数据 |
| `include/protocol/FrameCodec.hpp` | CRC-8（Maxim-Dallas, poly = 0x31）编解码 |
| `include/protocol/CommandParser.hpp` | 下行帧状态机解析器 |

### 5. 中断分配

| 中断 | 优先级 | 用途 |
|------|--------|------|
| USART1 | 0 | IDLE 接收 + TXE 发送 |
| DMA1_Channel5 | 0 | USART1 RX DMA half/full |
| TIM4 | 1 | 泵脉冲计数 |
| ADC1_2 | 2 | ADC 转换完成 |
| I2C1_EV / I2C1_ER | 2 | AS7341 异步 I2C |
| SysTick | 15 | 1 ms 时基 |

所有中断处理函数在 `Startup/Vectors.cpp` 中以 `[[gnu::weak]]` 声明为弱符号并默认指向 `Default_Handler`，用户只需在任意 `.cpp` 中定义同名 `extern "C"` 函数即可覆盖。

### 6. 主循环

`src/main.cpp` 初始化时钟、SysTick、LED、串口、泵、ADC 过采样和 AS7341，随后在主循环中轮询协议服务、光谱服务和 ADC 服务，并在光谱测量完成后自动启动下一轮采集。

## 构建与烧录

### 固件构建

需要 `arm-none-eabi` 工具链在 PATH 中：

```sh
scons
# 或指定前缀
scons CROSS=arm-none-eabi-
```

构建产物位于 `build/`：

- `AutoTitrator-Firmware.elf` — 可执行文件（含调试信息）
- `AutoTitrator-Firmware.hex` — Intel HEX
- `AutoTitrator-Firmware.map` — 内存映射
- `AutoTitrator-Firmware.lst` — 反汇编清单

清理：

```sh
scons -c
```

### 烧录与调试

```sh
# Terminal 1 — 启动 OpenOCD
cd D:/Projects/AutoTitrator/Firmware
openocd -f openocd.cfg

# Terminal 2 — 连接 GDB
arm-none-eabi-gdb build/AutoTitrator-Firmware.elf -x .gdbinit
```

### 寄存器生成工具

寄存器头文件生成脚本需要 `cmsis-svd`，开发依赖使用：

```sh
uv pip install -r requirements-dev.txt
uv run scripts/generate_stm32f103.py
```

## 上位机（TController）

Rust/Tauri 上位机通过串口与 MCU 通信，提供：

- 实时光谱曲线与电位曲线
- 在线滴定终点检测
- 双泵控制与进度显示
- 泵校准与 pH 电极校准
- 状态持久化、运行历史和可靠性诊断

### 主要模块

| 目录 | 功能 |
|------|------|
| `TController/crates/controller-core/src/protocol/` | 串口线程、协议帧解析与重试 |
| `TController/crates/controller-core/src/processing/` | 终点检测、光谱重建、泵校准 |
| `TController/crates/controller-core/src/workflow.rs` | 滴定工作流与泵控状态机 |
| `TController/app/src-tauri/` | 后端状态快照、命令和持久化 |
| `TController/app/ui-next/` | Next.js 仪器工作台 |

### 技术栈

| 组件 | 技术 |
|------|------|
| UI 框架 | Tauri 2 + Next.js |
| 状态管理 | Rust backend snapshot + Zustand 视图缓存 |
| 数值计算 | Rust ndarray / ndarray-npy |
| 串口通信 | Rust serialport |

### 运行方式

```sh
cd TController
cargo test --workspace
npm --prefix app/ui-next install
npm --prefix app/ui-next run build
```

开发模式下由 Tauri 加载 `app/ui-next/out`；浏览器直接访问 Next 开发服务器时使用显式 mock adapter，真实 Tauri 环境始终以 Rust backend snapshot 为状态源。

## 注意事项

- **无 HAL / 无标准库**：所有外设寄存器通过自定义抽象层直接访问。
- **堆内存**：`new` / `delete` 默认触发死循环；如需动态分配请在 `Startup/CXXStubs.cpp` 中实现。
- **静态构造**：`.init_array` 在 `main()` 之前由 `Reset_Handler` 调用，支持全局 C++ 对象的构造函数。

## 授权

本项目采用 [PolyForm Shield 1.0.0](LICENSE) 授权。

- 允许个人学习、研究、内部使用
- 禁止将本软件或其衍生品作为竞争产品提供
- 分发时必须附带本许可证全文或其 URL
