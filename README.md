# AutoTitrator-Firmware

| 项目 | 值 |
|------|-----|
| MCU | STM32F103C8T6 (Cortex-M3) |
| 工具链 | GCC ARM (`arm-none-eabi-g++`) |
| 构建系统 | SCons |
| 调试器 | ST-Link V2 (SWD) |
| 语言标准 | C++23, bare-metal, no HAL |

## 目录结构

```
├── SConstruct            # SCons 构建脚本
├── src/
│   └── main.cpp          # 应用入口
├── Startup/
│   ├── Vectors.cpp       # 中断向量表 + 启动代码 (Reset_Handler)
│   ├── CXXStubs.cpp      # C++ 裸机运行时桩 (new/delete/guard/atexit)
│   └── linker.ld         # 链接脚本 (64KB Flash / 20KB RAM)
├── include/              # 公共头文件
├── openocd.cfg           # OpenOCD 调试配置
├── .gdbinit              # GDB 初始化脚本
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
