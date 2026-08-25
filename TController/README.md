# TController — AutoTitrator Rust/Tauri 上位机

Rust `controller-core` 后端 + Tauri 2 应用壳 + Next.js 仪器工作台。后端持有串口、工作流、校准、检测、设置和历史状态，前端通过状态快照和命令接口与其交互。

## 目录

```
TController/
├── Cargo.toml                 # workspace
├── crates/controller-core/    # 后端核心（纯逻辑 + 串口 I/O 线程）
│   ├── src/protocol/          # 串口协议、解析与重试
│   │   ├── crc.rs             #   CRC-8 (poly 0x31)
│   │   ├── frames.rs          #   上/下行帧编解码（含 ADC shift 语义）
│   │   ├── parser.rs          #   AA55 逐字节状态机
│   │   ├── retry.rs           #   ACK/NAK 指数退避重试（单 pending 槽）
│   │   └── handler.rs         #   串口工作线程 + Event 通道（poll 模型）
│   ├── src/processing/        # 检测、重建与泵校准
│   │   ├── ewma.rs savgol.rs ampd.rs
│   │   ├── divergence.rs      #   JS / 交叉熵 / KL（含舍入地板 1e-14）
│   │   ├── tracker.rs         #   SpectralFeatureTracker
│   │   ├── kf.rs              #   EndpointFusionKF
│   │   ├── endpoint.rs        #   EndpointDetector
│   │   ├── reconstructor.rs   #   calibre.npz 矩阵 → 380–1100nm 全光谱
│   │   └── calibration.rs     #   泵线性标定（slope/intercept）
│   ├── src/workflow.rs        # 滴定工作流与泵控逻辑
│   └── tests/                 # 行为契约与回归测试
└── app/                       # Tauri 2 应用
    ├── src-tauri/             #   后端命令与 backend://state 快照
    └── ui-next/               #   Next.js 仪器工作台
```

## 行为契约

`tests/endpoint_reliability.rs` 保留算法移植时建立的行为契约
（JS 对称有界、特征因果性、重复体积 hold、顶替滞回、舍入地板、KF 重置、
AMPD 对照稠密 oracle 等）；`protocol/` 内嵌测试覆盖协议边界；
`tests/workflow.rs` 固化了曾实际发生的 **T=1 死锁回归**
（conflict + 电位证据必须放行 T=1，spectral_only 不得控泵）。

AMPD 精修在短记录（大尺度不覆盖尾部峰）时返回 `None`；savgol edge 填充使用与原始算法一致的边缘半窗口行为。

## 使用

```bash
cd app/src-tauri
cargo tauri dev       # 自动启动 Next.js 开发服务器
cargo tauri build     # 自动执行 Next.js 静态导出并打包 Tauri 应用
```

单独运行后端测试：

```bash
cargo test --workspace
cargo check --workspace
```

单独验证前端：

```bash
cd app/ui-next
npm install
npm run build
npm run lint
```

`calibre.npz` 探测顺序：环境变量 `AUTOTITRATOR_CALIBRE` → exe 同级 →
开发模式 `TController/data/calibre.npz`（由 workspace manifest 路径锚定）。

## 数据文件

- `data/calibre.npz`：光谱重建和泵校准数据，必须保留。
- `data/settings.json`：后端运行时设置和历史记录，由 `.gitignore` 忽略。
- `data/pump2_calibration.json`：应用校准后的 sidecar，由 `.gitignore` 忽略。

## 后续迭代

- [ ] 数据记录与 xlsx 五 sheet 导出（rust_xlsxwriter）
- [ ] 电极元数据（calibre.npz 中的对象数组键，需迁移到 JSON sidecar 或专用格式）
