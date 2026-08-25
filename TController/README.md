# TController 上位机

[English](README_EN.md) | 中文

AutoTitrator 的桌面端，由三部分组成：

- `controller-core`：Rust 后端逻辑，负责串口通信、终点检测、光谱重建、泵标定和工作流状态机，不含界面。
- `src-tauri`：Tauri 2 应用壳，把 controller-core 包装成桌面应用，向前端提供命令接口和状态快照。
- `ui-next`：Next.js 前端，仪器工作台界面。

## 目录

```
TController/
├── Cargo.toml                 # workspace
├── crates/controller-core/    # 后端逻辑（纯逻辑 + 串口 I/O 线程）
│   ├── src/protocol/          # 串口协议、解析与重试
│   │   ├── crc.rs             #   CRC-8 (poly 0x31)
│   │   ├── frames.rs          #   上/下行帧编解码（含 ADC shift 语义）
│   │   ├── parser.rs          #   AA55 逐字节状态机
│   │   ├── retry.rs           #   ACK/NAK 指数退避重试（单 pending 槽）
│   │   └── handler.rs         #   串口工作线程 + Event 通道（poll 模型）
│   ├── src/processing/        # 检测、重建与泵校准
│   │   ├── ewma.rs savgol.rs ampd.rs
│   │   ├── divergence.rs      #   JS / 交叉熵 / KL（含舍入下界 1e-14）
│   │   ├── tracker.rs         #   SpectralFeatureTracker
│   │   ├── kf.rs              #   EndpointFusionKF
│   │   ├── endpoint.rs        #   EndpointDetector
│   │   ├── reconstructor.rs   #   calibre.npz 矩阵 → 380–1100nm 全光谱
│   │   └── calibration.rs     #   泵线性标定（slope/intercept）
│   ├── src/workflow.rs        # 滴定工作流与泵控逻辑
│   └── tests/                 # 行为约定与回归测试
└── app/                       # Tauri 2 应用
    ├── src-tauri/             #   后端命令与 backend://state 快照
    └── ui-next/               #   Next.js 仪器工作台
```

## 行为约定

`tests/endpoint_reliability.rs` 保留了算法从 Python 移植时定下的行为约定：JS 散度对称有界、特征只用历史样本（因果）、重复体积帧保持速度电平、后发事件要强 1.5 倍才能顶替旧候选、舍入下界以下的散度不归一化、端点对变化时 KF 重新融合、AMPD 与稠密参照实现逐点一致。改动这些行为前先跑测试，改完测试会明确告诉你有哪里不一致。

`tests/workflow.rs` 固化了一次实际发生过的 T=1 死锁回归：当双模态都确认但差距过大（conflict）时，只要电位证据在就必须放行 T=1；只有光谱、没有电位证据时不能控泵。场景见该文件顶部注释。

AMPD 精修在记录太短（尾部峰没有大尺度覆盖）时返回 `None`，这是预期行为；savgol 边缘填充与参照算法的边缘半窗口行为一致。

## 开发环境

需要 Rust 工具链和 Node.js。根目录的 `requirements-dev.txt` 提供 Python 依赖（`uv` 安装），`generate_stm32f103.py` 生成固件外设头文件，上位机本身不需要它。

```bash
# 安装前端依赖（首次）
cd app/ui-next
npm install

# 启动开发（自动拉起 Next.js 开发服务器）
cd ../src-tauri
cargo tauri dev

# 打包发布
cargo tauri build   # 自动执行 Next.js 静态导出
```

## 测试

```bash
cargo test --workspace   # 后端逻辑测试
cargo check --workspace  # 编译检查

cd app/ui-next
npm run build
npm run lint
```

`savgol`、`ampd`、`endpoint` 等测试把 Python 参照实现的行为固化成断言，改数值算法时优先看这些测试是否还能过。`tests/tmp_diff_python.rs` 是一次性差分测试，需要先跑 `tmp_diff/dump_python.py` 生成对照数据，缺文件时自动跳过。

## 双数据源：mock 与真实后端

前端有两种运行方式：

- **Tauri 环境**：始终以 Rust backend snapshot 为状态源。前端通过 `invoke` 调用 Tauri 命令，后端每 50ms 推一次 `backend://state` 快照。
- **浏览器直接访问 Next 开发服务器**：没有 Tauri 桥，自动使用 `lib/mock/simulator.ts` 的内置模拟器，用定时器和滴定模型产生事件流。接 Tauri 后端时只需替换数据源，store 与界面组件不用改。

切换判断在 `lib/backend.ts` 的 `isTauriRuntime()`。mock 模拟器里带有几种演示场景（正常、弱信号、模态冲突、泵故障），只在浏览器调试时出现，打包进 Tauri 的正式界面不会显示场景选择。

## 后端状态模型

controller-core 不持有界面状态，通过 `Event` 通道向上抛事件，Tauri 壳 `BackendRuntime` 消费事件，维护一份 `BackendSnapshot`，以 `backend://state` 事件广播。快照字段全部 camelCase，与前端 `lib/backend.ts` 的类型定义一一对应。

关键设计：

- 串口工作线程独占端口，主循环只管收发，命令的 ACK/NAK 重试、心跳都在 `ProtocolHandler` 线程里完成。
- 工作流引擎 `WorkflowEngine` 是纯逻辑，不碰 I/O。`on_adc` / `on_spectrum` 喂数据，`poll` 每 500ms 做一次决策，产出泵指令交给传输层执行。
- 状态持久化：`settings.json`（界面偏好、检测参数、历史）、`pump2_calibration.json`（应用标定后的 sidecar）。两个文件都由 `.gitignore` 忽略。
- 诊断信息（可靠性、KF 快照、reason codes）随快照推送，前端「可靠性」分组直接展示，字段与 `EndpointResult` / `Reliability` 结构对应。

## 数据文件

- `data/calibre.npz`：光谱重建矩阵和泵标定参数，必须保留。
- `data/settings.json`：后端运行时设置和历史记录，自动生成。
- `data/pump2_calibration.json`：应用标定后的 sidecar，自动生成。

`calibre.npz` 的探测顺序：环境变量 `AUTOTITRATOR_CALIBRE` → 可执行文件同级目录 → 开发模式 `TController/data/calibre.npz`（编译期锚定）。结构见「标定与数据格式」文档。

## 相关文档

- 根 README：构建、烧录、CI、发布。
- 通信协议：帧格式、命令、时序。
- 上位机使用手册：面向操作者的界面说明。
- 标定与数据格式：calibre.npz 与 sidecar 的结构。