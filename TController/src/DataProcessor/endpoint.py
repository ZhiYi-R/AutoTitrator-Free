"""
滴定终点在线检测（因果 EWMA + 状态机）。

电位通道: EWMA(α=0.15) 平滑电位 → 逐点 dV/dt → EWMA(α=0.05) 平滑导数
          → 状态机 IDLE→TRACKING→END_CONFIRMED（体积门控确认）
光谱通道: 逐帧交叉熵 → EWMA(α=0.20) 平滑 → 状态机
共识:     V_pot 与 V_spec 差异在阈值内则输出均值 + 高置信度

全部处理均为因果（仅使用历史数据），适用在线流式场景。
"""

from __future__ import annotations

import numpy as np

# ======================================================================
#  工具函数（保留兼容性）
# ======================================================================

_SAVGOL_COEFFS_CACHE: dict[tuple, np.ndarray] = {}


def _savgol_coeffs(window: int, order: int) -> np.ndarray:
    if window % 2 == 0:
        raise ValueError(f"window 必须为奇数，得到 {window}")
    key = (window, order)
    if key not in _SAVGOL_COEFFS_CACHE:
        half = window // 2
        x = np.arange(-half, half + 1, dtype=np.float64)
        A = np.vander(x, order + 1, increasing=True)
        ATA = A.T @ A
        coeffs = np.linalg.solve(ATA, A.T)
        _SAVGOL_COEFFS_CACHE[key] = coeffs[0].copy()
    return _SAVGOL_COEFFS_CACHE[key]


def savgol_filter(signal: np.ndarray, window: int = 5, order: int = 2) -> np.ndarray:
    """Savitzky–Golay 平滑（中心对称，离线用）。"""
    coeffs = _savgol_coeffs(window, order)
    half = window // 2
    padded = np.pad(signal, half, mode="edge")
    return np.convolve(padded, coeffs[::-1], mode="valid")


# ======================================================================
#  因果指数移动平均
# ======================================================================


class _EWMA:
    """一阶指数移动平均（因果，O(1) 每步）。"""

    __slots__ = ("_a", "_v")

    def __init__(self, alpha: float) -> None:
        self._a = alpha
        self._v: float | None = None

    def __call__(self, x: float) -> float:
        if self._v is None:
            self._v = float(x)
        else:
            self._v = self._a * float(x) + (1.0 - self._a) * self._v
        return self._v

    @property
    def value(self) -> float | None:
        return self._v

    def reset(self) -> None:
        self._v = None


# ======================================================================
#  Automatic Multi-scale Peak Detection (Scholkmann 2012)
#  对取反后的信号找峰 → 原信号的谷底
# ======================================================================


def _ampd_peak_idx(signal: np.ndarray) -> int | None:
    """返回 AMPD 定位的最显著峰值索引（无峰时返回 None）。"""
    N = len(signal)
    if N < 12:
        return None
    L = N // 2 - 1
    if L < 2:
        return None

    # LMS 矩阵: LMS[k, i] = 1 若 X[i] 在尺度 k 上是局部极大值
    LMS = np.zeros((L, N), dtype=np.int32)
    for k in range(1, L + 1):
        for i in range(k, N - k):
            if signal[i] > signal[i - k] and signal[i] > signal[i + k]:
                LMS[k - 1, i] = 1

    # 最优尺度 = 局部极大值最少的行（噪声抑制最充分）
    gamma = LMS.sum(axis=1)
    sigma = int(np.argmin(gamma))

    # 从最优尺度起累计，得分最高的列为峰位
    score = LMS[sigma:, :].sum(axis=0)
    best = int(np.argmax(score))
    return best if score[best] > 0 else None


# ======================================================================
#  EndpointDetector 主类（在线流式版）
# ======================================================================


class EndpointDetector:
    """滴定终点在线检测（因果滤波 + 状态机）。

    用法::

        det = EndpointDetector(flow_rate=0.0061)
        det.feed_potential(t, v)
        det.feed_spectrum(t, spectrum)
        result = det.detect()
    """

    # 电位通道参数（自适应阈值）
    POT_V_ALPHA = 0.15
    POT_D_ALPHA = 0.05
    POT_OBSERVE_VOL = 0.1  # mL: 观察窗口，用于学习噪声基底
    POT_ENTER_SIGMA = 6.0  # dv/dt 低于噪声均值 6σ 时进入 TRACKING
    POT_EXIT_SIGMA = 2.5  # dv/dt 恢复至 2.5σ 以内时确认终点
    POT_MIN_ENTER = 0.005  # V/s: ENTER 阈值安全下限
    POT_MIN_EXIT = 0.001  # V/s: EXIT 阈值安全下限
    POT_CONFIRM_VOL = 0.15

    # 光谱通道参数
    SPEC_CE_ALPHA = 0.20
    SPEC_ENTER = 1e-3
    SPEC_EXIT = 1e-4
    SPEC_CONFIRM_FRAMES = 10

    def __init__(self, flow_rate: float | None = None) -> None:
        if flow_rate is None:
            from DataProcessor.calibration import FLOW_RATE

            self._flow_rate = FLOW_RATE
        else:
            self._flow_rate = flow_rate

        self._reset_state()

    def _reset_state(self) -> None:
        # 电位
        self._pot_v_smooth = _EWMA(self.POT_V_ALPHA)
        self._pot_d_smooth = _EWMA(self.POT_D_ALPHA)
        self._pot_prev_v: float | None = None
        self._pot_prev_t: float | None = None
        self._pot_state: str = "IDLE"
        self._pot_ep_vol: float | None = None
        self._pot_ep_t: float | None = None
        self._pot_min_d: float = 0.0
        self._pot_cand_vol: float | None = None
        self._pot_entry_vol: float | None = None
        self._pot_done: bool = False
        # 噪声观察（自适应阈值）
        self._pot_d_vals: list[float] = []
        self._pot_obs_vol: float = 0.0
        self._pot_obs_done: bool = False
        self._pot_enter_th: float = -1e9
        self._pot_exit_th: float = -1e9
        # dv/dt 全历史（用于 AMPD 精确定位）
        self._pot_raw_buf: list[float] = []
        self._pot_vol_buf: list[float] = []

        # 光谱
        self._spec_ce_smooth = _EWMA(self.SPEC_CE_ALPHA)
        self._spec_prev: np.ndarray | None = None
        self._spec_state: str = "IDLE"
        self._spec_ep_vol: float | None = None
        self._spec_ep_t: float | None = None
        self._spec_max_ce: float = 0.0
        self._spec_cand_vol: float | None = None
        self._spec_rest_cnt: int = 0
        self._spec_done: bool = False

        self._last_pot_result: dict | None = None
        self._last_spec_result: dict | None = None

    # ================================================================
    #  数据馈入
    # ================================================================

    def feed_potential(self, vol: float, t: float, v: float) -> None:
        """馈入电位数据点 (vol: mL, t: 秒, v: 伏特)。"""
        v_sm = self._pot_v_smooth(v)

        if self._pot_prev_t is not None and self._pot_prev_v is not None:
            dt = t - self._pot_prev_t
            dv = v_sm - self._pot_prev_v
            d_raw = dv / dt if dt > 0 else 0.0
        else:
            d_raw = 0.0

        d_sm = self._pot_d_smooth(d_raw)
        self._pot_prev_v = v_sm
        self._pot_prev_t = t

        # 缓存原始 dv/dt（用于 AMPD 精确定位）
        self._pot_raw_buf.append(d_raw)
        self._pot_vol_buf.append(vol)

        # --- 噪声观察阶段：学习 dv/dt 基线，计算自适应阈值 ---
        if not self._pot_obs_done:
            self._pot_d_vals.append(d_sm)
            if vol >= self.POT_OBSERVE_VOL:
                arr = np.array(self._pot_d_vals)
                if len(arr) < 3:
                    # 数据点过少，无法可靠估计标准差
                    self._pot_obs_done = False
                    return
                d_mean = float(np.mean(arr))
                d_std = float(np.std(arr, ddof=1))  # 使用样本标准差（Bessel 校正）
                
                # 防止标准差过小导致阈值过于敏感
                # 使用相对噪声下限：至少为均值的 1% 或绝对下限 1e-6
                d_std = max(d_std, abs(d_mean) * 0.01, 1e-6)
                
                enter = d_mean - max(self.POT_MIN_ENTER, self.POT_ENTER_SIGMA * d_std)
                exit_ = d_mean - max(self.POT_MIN_EXIT, self.POT_EXIT_SIGMA * d_std)
                self._pot_enter_th = enter
                self._pot_exit_th = exit_
                self._pot_obs_done = True
                self._pot_d_vals = []  # 释放
            return  # 观察期间不进入检测

        # --- 终点检测（使用自适应阈值） ---
        if not self._pot_done:
            if self._pot_state == "IDLE":
                if d_sm < self._pot_enter_th:
                    self._pot_state = "TRACKING"
                    self._pot_min_d = d_sm
                    self._pot_cand_vol = vol
                    self._pot_entry_vol = vol
            elif self._pot_state == "TRACKING":
                if d_sm < self._pot_min_d:
                    self._pot_min_d = d_sm
                    self._pot_cand_vol = vol
                if (
                    d_sm > self._pot_exit_th
                    and self._pot_entry_vol is not None
                    and (vol - self._pot_entry_vol) > self.POT_CONFIRM_VOL
                ):
                    assert self._pot_cand_vol is not None
                    self._pot_ep_vol = self._pot_cand_vol
                    self._pot_ep_t = self._pot_cand_vol / self._flow_rate
                    self._pot_state = "END_CONFIRMED"
                    self._pot_done = True

    def feed_spectrum(self, vol: float, spectrum: np.ndarray) -> None:
        """馈入光谱数据 (vol: mL, spectrum: 10 通道或全光谱数组)。"""
        ce_raw = 0.0

        if self._spec_prev is not None:
            p = np.maximum(spectrum.astype(np.float64), 0.0)
            q = np.maximum(self._spec_prev.astype(np.float64), 0.0)
            p /= p.sum() + 1e-12
            q /= q.sum() + 1e-12
            ce_raw = -float(np.sum(p * np.log(np.maximum(q, 1e-12))))
        self._spec_prev = spectrum.copy()

        ce_sm = self._spec_ce_smooth(ce_raw)

        if not self._spec_done:
            if self._spec_state == "IDLE":
                if ce_sm > self.SPEC_ENTER:
                    self._spec_state = "IN_CHANGE"
                    self._spec_max_ce = ce_sm
                    self._spec_cand_vol = vol
            elif self._spec_state == "IN_CHANGE":
                if ce_sm > self._spec_max_ce:
                    self._spec_max_ce = ce_sm
                    self._spec_cand_vol = vol
                if ce_sm < self.SPEC_EXIT:
                    self._spec_rest_cnt += 1
                    if self._spec_rest_cnt >= self.SPEC_CONFIRM_FRAMES:
                        assert self._spec_cand_vol is not None
                        self._spec_ep_vol = self._spec_cand_vol
                        self._spec_ep_t = self._spec_cand_vol / self._flow_rate
                        self._spec_state = "END_CONFIRMED"
                        self._spec_done = True
                else:
                    self._spec_rest_cnt = 0

    # ================================================================
    #  检测
    # ================================================================

    def detect(self) -> dict | None:
        """返回当前终点检测结果。

        返回值结构::

            {
                "volume": 1.091,
                "time": 178.9,
                "confidence": "high" / "medium" / "low",
                "method": "consensus" / "potential_only" / "spectral_only" / "conflict",
                "potential": {...} | None,
                "spectral": {...} | None,
            }
        """
        pot = self._build_pot_result()
        spec = self._build_spec_result()

        if pot is not None and spec is not None:
            diff = abs(pot["volume"] - spec["volume"])
            if diff < 0.3:
                v = (pot["volume"] + spec["volume"]) / 2.0
                return {
                    "volume": round(v, 3),
                    "time": round((pot["time"] + spec["time"]) / 2.0, 3),
                    "confidence": "high",
                    "method": "consensus",
                    "potential": pot,
                    "spectral": spec,
                }
            return {
                "volume": round(pot["volume"], 3),
                "time": round(pot["time"], 3),
                "confidence": "low",
                "method": "conflict",
                "potential": pot,
                "spectral": spec,
                "warning": f"电位{pot['volume']:.3f}mL vs "
                f"光谱{spec['volume']:.3f}mL 差异过大",
            }

        if pot is not None:
            return {
                "volume": round(pot["volume"], 3),
                "time": round(pot["time"], 3),
                "confidence": "medium",
                "method": "potential_only",
                "potential": pot,
                "spectral": None,
            }
        if spec is not None:
            return {
                "volume": round(spec["volume"], 3),
                "time": round(spec["time"], 3),
                "confidence": "medium",
                "method": "spectral_only",
                "potential": None,
                "spectral": spec,
            }
        return None

    def refine_with_ampd(self) -> float | None:
        """用 AMPD 对 dv/dt 历史数据精确定位终点。

        对 dv/dt 信号取反后找最显著峰，峰位对应的体积即为终点。
        在 AMPD 定位后增加合理性校验：若结果过于接近缓冲区末端
        （导数尚未充分恢复），判定为无效，保留原有 T=1 值。
        返回 refined volume (mL)，若无法定位或结果不可信则返回 None。
        """
        if len(self._pot_raw_buf) < 20:
            return None
        arr = np.array(self._pot_raw_buf, dtype=np.float64)
        # 取反使谷底变高峰
        neg = -arr
        idx = _ampd_peak_idx(neg)
        if idx is None:
            return None
        # 合理性校验：AMPD 结果不应位于缓冲区最后 25% 位置
        # （说明导数还在下降或刚过拐点，未充分恢复）
        if idx >= len(self._pot_vol_buf) * 0.75:
            return None
        refined_vol = self._pot_vol_buf[idx]
        # 更新 _pot_ep_vol
        self._pot_ep_vol = refined_vol
        self._pot_ep_t = refined_vol / self._flow_rate
        return refined_vol

    def _build_pot_result(self) -> dict | None:
        if self._pot_ep_vol is None:
            return None
        return {
            "volume": self._pot_ep_vol,
            "time": self._pot_ep_t or (self._pot_ep_vol / self._flow_rate),
            "min_dvdt": round(self._pot_min_d, 2),
            "state": self._pot_state,
        }

    def _build_spec_result(self) -> dict | None:
        if self._spec_ep_vol is None:
            return None
        return {
            "volume": self._spec_ep_vol,
            "time": self._spec_ep_t or (self._spec_ep_vol / self._flow_rate),
            "max_ce": round(self._spec_max_ce, 8),
            "state": self._spec_state,
        }

    # ================================================================
    #  生命周期
    # ================================================================

    def reset(self) -> None:
        """清空所有滤波器与状态机，准备新一轮滴定。"""
        self._reset_state()

    @property
    def potential_state(self) -> str:
        return self._pot_state

    @property
    def spectral_state(self) -> str:
        return self._spec_state

    @property
    def endpoint_volume(self) -> float | None:
        return self._pot_ep_vol or self._spec_ep_vol


__all__ = ["EndpointDetector", "savgol_filter"]
