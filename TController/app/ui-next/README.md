# ui-next 仪器工作台

[English](README_EN.md) | 中文

AutoTitrator 上位机的前端部分，基于 Next.js。它展示滴定工作台、标定、维护、数据记录和设置五个页面，数据来源有两种：

- Tauri 环境：订阅后端 `backend://state` 快照，通过 `invoke` 调用 Tauri 命令。
- 浏览器直接访问：自动使用 `lib/mock/simulator.ts` 的模拟器，内置几种演示场景，方便不开硬件调试界面。

切换逻辑在 `lib/backend.ts`。正式打包进 Tauri 时始终走真实后端，mock 只在浏览器开发模式出现。

## 开发

```bash
npm install
npm run dev        # 开发服务器（浏览器模式，自动启用 mock）
npm run build      # 静态导出，供 Tauri 打包
npm run lint
```

## 目录

```
lib/
├── backend.ts        # Tauri/mock 双数据源桥接
├── store.ts          # Zustand 全局状态
├── i18n.ts           # 中英文案
├── types.ts          # 前后端事件协议类型
├── chart-utils.ts    # Canvas 图表公共工具
├── tone.ts           # 语义色调映射
└── mock/
    ├── simulator.ts  # 内置模拟器
    └── calibre.ts    # 泵标定镜像
```

## 约定

- 界面文案全部走 `i18n.ts`，不要在组件里写死中文或英文。
- 状态字段名与后端快照的 camelCase 字段一一对应，改协议先改 `types.ts`。
- 页面布局见 `design.md`，改版式前先读它。