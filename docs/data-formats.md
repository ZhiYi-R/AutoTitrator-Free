# 标定与数据格式

[English](data-formats_EN.md) | 中文

本文档说明 `calibre.npz` 和标定 sidecar 的内部结构，供需要读取、生成或迁移这些数据的人参考。实现代码见 `crates/controller-core/src/processing/`。

## 一、calibre.npz

`calibre.npz` 是 NumPy 格式的压缩包，里面同时放光谱重建数据和泵标定数据。上位机启动时按固定顺序找它：环境变量 `AUTOTITRATOR_CALIBRE` → 可执行文件同级目录 → 开发模式 `TController/data/calibre.npz`。找不到时上位机降级运行：光谱不重建、泵用默认参数。

### 光谱重建键

| 键 | 类型 | 说明 |
|----|------|------|
| `spectral_matrix` | (721, 10) float | Golden Device 重建矩阵 |
| `spectral_wavelengths` | (721,) int32 | 波长轴，380–1100nm，1nm 步长 |
| `spectral_offsets` | (10,) float | 每通道暗电流偏移 |
| `spectral_factors` | (10,) float | 每通道增益系数 |

重建公式（`Reconstructor::reconstruct`）：

$$
\text{corrected}[ch] = \text{factors}[ch] \times \max\left(\text{raw}[ch] - \text{offsets}[ch],\, 0\right)
$$

$$
\text{spectrum}[\lambda] = \max\left(\sum_{ch}\, \text{matrix}[\lambda, ch] \times \text{corrected}[ch],\, 0\right)
$$

即先按通道减去偏移、乘增益并截断到非负，再乘矩阵得到 721 点光谱。输入必须是 10 个通道，负数或非有限值会报错。

### 泵标定键

| 键 | 说明 |
|----|------|
| `pump1_slope` / `pump1_intercept` | 泵 1 线性模型 slope（mL/步）与 intercept（mL） |
| `pump2_slope` / `pump2_intercept` | 泵 2 同上 |
| `pump1_pulses` / `pump1_volumes` | 泵 1 标定点（步数 ↔ 实测体积） |
| `pump2_pulses` / `pump2_volumes` | 泵 2 标定点 |
| `pump1_r2` / `pump2_r2` | 拟合 R²，可为标量或单元素数组 |

加载规则：

- slope 必须为正，否则回退默认值。
- intercept 允许为负，但绝对值不能超过 10 mL。
- 缺失或读取失败的键静默回退默认值，不报错。

默认值（`DEFAULT_PUMP_SLOPE = 6.03752e-6`，intercept 0）对应泵步进频率 1000Hz，流速约 6.04e-3 mL/s。

体积与步数互换（`PumpCalibration`）：

$$
\text{volume} = \text{slope} \times \text{steps} + \text{intercept}
$$

$$
\text{steps} = \left\lfloor \frac{\text{volume} - \text{intercept}}{\text{slope}} \right\rfloor \quad (\text{下限 0})
$$

## 二、标定 sidecar

上位机在界面里应用泵标定后，把结果写进与 `settings.json` 同目录的 `pump2_calibration.json`，结构如下：

```json
{
  "points": [
    { "steps": 0,    "vol": 0.0 },
    { "steps": 5000, "vol": 0.031 }
  ],
  "slopeMlPerStep": 6.0997e-6,
  "interceptMl": 0.0,
  "r2": 0.9997
}
```

- `points`：界面里的标定点，`steps` 是累计步数，`vol` 是实测体积（mL）。
- `slopeMlPerStep`：拟合斜率，单位 mL/步。
- `interceptMl`：截距，单位 mL。
- `r2`：拟合优度，可选。

启动时如果这个文件存在且 `slopeMlPerStep > 0`，上位机会用它覆盖 `calibre.npz` 里的泵 2 参数，并把点集和 R² 加载进界面。

## 三、settings.json

`settings.json` 保存界面偏好和运行历史，自动生成：

- `lang`、`theme`、`navCollapsed`：界面偏好。
- `detection`：检测参数（T=1 导数阈值、单步剂量、过量滴定余量、共识容差）。
- `history`：最近 30 次运行记录。
- `port`、`baud`：上次连接的串口与波特率。
- `sampleInput`、`tubingP1`、`tubingP2`：进样体积和管路泵选择。

这个文件可以删除，删了回到默认设置。它被 `.gitignore` 忽略，不会进版本库。

## 四、生成与迁移

需要重新生成 `calibre.npz` 时，用 Python（`numpy` / `scipy`）按上面的键名写入即可。迁移到新机器时，把 `calibre.npz` 放到可执行文件同级目录，或设置 `AUTOTITRATOR_CALIBRE` 指向它。标定数据跟着走：`calibre.npz` 里的泵标定是出厂默认，界面里应用的标定单独放在 `pump2_calibration.json`。