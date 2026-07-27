# AutoTitrator-Free

多模态自动滴定控制器 — STM32F103 固件 + Python 上位机。

| 项目 | 值 |
|------|-----|
| MCU | STM32F103C8T6 (Cortex-M3) |
| 工具链 | GCC ARM (`arm-none-eabi-g++`) |
| 构建系统 | SCons |
| 调试器 | ST-Link V2 (SWD) |
| 语言标准 | C++23, bare-metal, no HAL |
| 上位机 | Python 3.12+, ttkbootstrap + matplotlib |
| 授权 | [PolyForm Shield 1.0.0](LICENSE) |

## 目录结构

```
├── SConstruct            # SCons 构建脚本
├── src/                  # 固件源码 (main.cpp, Interrupts.cpp)
├── Startup/              # 启动代码 + 中断向量 + 链接脚本
├── include/              # 固件头文件 (Platform/HAL/Device/Protocol)
├── TController/          # Python 上位机
│   ├── src/
│   │   ├── main.py       # GUI 入口
│   │   ├── Communication/# 串口通信协议
│   │   ├── DataProcessor/# 终点检测 + 光谱重建
│   │   └── gui/          # ttkbootstrap UI + matplotlib 绘图
│   ├── requirements.txt  # 运行时依赖
│   └── requirements-dev.txt
├── openocd.cfg           # OpenOCD 调试配置
├── .gdbinit              # GDB 初始化脚本
├── LICENSE               # PolyForm Shield 1.0.0
└── README.md
```

## 构建

```sh
# 需要 arm-none-eabi 工具链在 PATH 中
scons

# 指定工具链前缀
scons CROSS=arm-none-eabi-
```

构建产物在 `build/` 目录下：
- `AutoTitrator-Firmware.elf` — ELF 可执行文件（含调试信息）
- `AutoTitrator-Firmware.hex` — Intel HEX
- `AutoTitrator-Firmware.map` — 内存映射
- `AutoTitrator-Firmware.lst` — 反汇编清单

清理：`scons -c`

## 烧录与调试

```sh
# Terminal 1 — 启动 OpenOCD 调试服务
openocd -f openocd.cfg

# Terminal 2 — 连接 GDB
arm-none-eabi-gdb build/AutoTitrator-Firmware.elf -x .gdbinit
```

## 中断使用

所有中断处理函数在 `Startup/Vectors.cpp` 中以 `[[gnu::weak]]` 声明为弱符号，
默认指向 `Default_Handler`（死循环）。用户只需在任意 `.cpp` 中定义同名函数即可覆盖：

```cpp
extern "C" void SysTick_Handler() {
    // 你的 SysTick 处理逻辑
}
```

## 注意事项

- **无 HAL / 无标准库**：所有外设寄存器需手动定义和操作
- **堆内存**：`new` / `delete` 默认触发死循环，如需动态分配请在 `Startup/CXXStubs.cpp` 中实现
- **静态构造**：`.init_array` 在 `main()` 之前由 `Reset_Handler` 调用，支持全局 C++ 对象的构造函数

## 上位机 (TController)

Python 上位机通过串口与 MCU 通信，提供实时光谱/电位曲线、滴定终点检测、泵校准和数据导出。

### 运行

```sh
cd TController
uv sync                      # 安装依赖
uv run python src/main.py    # 启动 GUI
```

### 技术栈

| 组件 | 库 | 授权 |
|------|-----|------|
| UI 框架 | ttkbootstrap | MIT |
| 绘图 | matplotlib (blit 加速) | PSF/BSD |
| 数值计算 | numpy | BSD-3 |
| 串口通信 | pyserial | BSD-3 |
| 数据导出 | openpyxl | MIT |

### 线程模型

- 串口读取：`threading.Thread` + `queue.Queue`（无 Qt 依赖）
- GUI 轮询：`root.after()` 递归调度，80ms 刷新绘图
- 通信事件：`ProtocolHandler.poll()` 排空队列并分发回调

## 授权

本项目采用 [PolyForm Shield 1.0.0](LICENSE) 授权。

- 允许个人学习、研究、内部使用
- 禁止将本软件或其衍生品作为竞争产品提供
- 分发时必须附带本许可证全文或其 URL
