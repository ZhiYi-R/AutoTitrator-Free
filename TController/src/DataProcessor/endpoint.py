"""Causal online titration endpoint detection.

Potential data is processed with the existing causal EWMA state machine.
Spectra are processed by :mod:`DataProcessor.online_features`, which adds a
bounded Jensen-Shannon signal, causal cross-curvature and a two-state KF for
endpoint/delay fusion.  No feature uses future samples.

Either endpoint can be revised after the fact -- the spectral one when a stronger
excursion supersedes an early transient, the potential one after AMPD refinement
-- so :meth:`EndpointDetector._consume_kf_observations` re-runs the filter from
scratch whenever the observed pair changes.  Gating a corrected value against a
state built from the stale one would reject the correction.
"""

from __future__ import annotations

from typing import Any

import numpy as np

from DataProcessor.online_features import EndpointFusionKF, SpectralFeatureTracker

_SAVGOL_COEFFS_CACHE: dict[tuple[int, int], np.ndarray] = {}


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
    """Savitzky-Golay smoothing (symmetric and intended for offline use)."""
    coeffs = _savgol_coeffs(window, order)
    half = window // 2
    padded = np.pad(signal, half, mode="edge")
    return np.convolve(padded, coeffs[::-1], mode="valid")


class _EWMA:
    """First-order causal exponential moving average."""

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


def _ampd_peak_idx(signal: np.ndarray) -> int | None:
    """Return the most prominent AMPD peak index, or ``None``.

    Reduces each scale row on the fly instead of materialising the dense
    ``L x N`` local-maxima matrix.  The original nested Python loop cost O(N^2)
    interpreted iterations and O(N^2) memory: on a full titration record
    (measured on Paper/ExpData, ~1.4-1.7e4 samples) that was tens of seconds and
    0.4-0.6 GB on the GUI thread.  Results are bit-identical -- the same strict
    comparisons, the same first-minimum ``argmin`` and first-maximum ``argmax``.
    """
    sig = np.asarray(signal, dtype=np.float64)
    N = sig.size
    if N < 12:
        return None
    L = N // 2 - 1
    if L < 2:
        return None

    def _row(k: int) -> np.ndarray:
        centre = sig[k : N - k]
        return (centre > sig[: N - 2 * k]) & (centre > sig[2 * k :])

    # gamma[k-1] counts local maxima at scale k; sigma is the scale where the
    # signal is most consistently peaked.
    gamma = np.fromiter(
        (np.count_nonzero(_row(k)) for k in range(1, L + 1)), dtype=np.int64, count=L
    )
    sigma = int(np.argmin(gamma))

    score = np.zeros(N, dtype=np.int64)
    for k in range(sigma + 1, L + 1):
        score[k : N - k] += _row(k)
    best = int(np.argmax(score))
    return best if score[best] > 0 else None


class EndpointDetector:
    """Causal endpoint detector for potential and full-field spectral data."""

    # Potential channel parameters.
    POT_V_ALPHA = 0.15
    POT_D_ALPHA = 0.05
    POT_OBSERVE_VOL = 0.1
    POT_ENTER_SIGMA = 2.5
    POT_EXIT_SIGMA = 2.5
    POT_MIN_ENTER = 0.005
    POT_MIN_EXIT = 0.001
    POT_CONFIRM_VOL = 0.15

    # Legacy spectral names remain public for old validation/configuration code.
    # SPEC_ENTER/SPEC_EXIT are the cross-entropy-era thresholds and are only used
    # when use_jsd=False; that path is kept for compatibility and is not tuned.
    SPEC_CE_ALPHA = 0.20
    SPEC_ENTER = 1e-3
    SPEC_EXIT = 1e-4
    SPEC_CONFIRM_FRAMES = 10

    # Thresholds on the volume-normalised JS speed, i.e. nats/mL^2 -- not the
    # bounded JS value itself.  JS between adjacent frames is second order in the
    # volume step, so dividing by that step squared makes the speed independent
    # of the sampling density; the numbers below are therefore not comparable to
    # the ln(2) bound on plain JS.
    SPEC_JS_ENTER = 0.05
    SPEC_JS_EXIT = 0.008
    SPEC_BASELINE_ENTER = 3e-7
    SPEC_BASELINE_FRAMES = 12
    SPEC_BASELINE_MAX_VOL = 0.30
    SPEC_MIN_EVENT_VOL = 0.08
    # A later excursion must be this much stronger to take over the endpoint.
    SPEC_SUPERSEDE_RATIO = 1.5

    # AMPD refinement rejects a peak beyond this fraction of the record: the
    # largest AMPD scale only evaluates the middle of the window, so a peak in
    # the tail is supported by few scales.  0.75 silently rejected valid late
    # endpoints (a manual stop shortly after the equivalence point puts it near
    # 0.8 of the record), so the guard sits just inside the unsupported tail.
    AMPD_MAX_POSITION = 0.9

    def __init__(
        self,
        flow_rate: float | None = None,
        *,
        use_jsd: bool = True,
        enable_curvature: bool = True,
        enable_kf: bool = True,
        wavelengths: np.ndarray | None = None,
    ) -> None:
        if flow_rate is None:
            from DataProcessor.calibration import FLOW_RATE

            self._flow_rate = FLOW_RATE
        else:
            self._flow_rate = float(flow_rate)
        self._use_jsd = bool(use_jsd)
        self._enable_curvature = bool(enable_curvature)
        self._enable_kf = bool(enable_kf)
        self._spectrum_axis = None if wavelengths is None else np.asarray(wavelengths, dtype=np.float64).copy()
        self._reset_state()

    def _reset_state(self) -> None:
        # Potential state and causal derivative history.
        self._pot_v_smooth = _EWMA(self.POT_V_ALPHA)
        self._pot_d_smooth = _EWMA(self.POT_D_ALPHA)
        self._pot_prev_v: float | None = None
        self._pot_prev_t: float | None = None
        self._pot_state = "IDLE"
        self._pot_ep_vol: float | None = None
        self._pot_ep_t: float | None = None
        self._pot_min_d = 0.0
        self._pot_cand_vol: float | None = None
        self._pot_entry_vol: float | None = None
        self._pot_done = False
        self._pot_d_vals: list[float] = []
        self._pot_obs_done = False
        self._pot_enter_th = -1e9
        self._pot_exit_th = -1e9
        self._pot_raw_buf: list[float] = []
        self._pot_vol_buf: list[float] = []
        self._pot_sample_count = 0
        self._pot_last_d = 0.0

        # Spectral state is delegated to the causal feature tracker.
        self._spectral = SpectralFeatureTracker(
            alpha=self.SPEC_CE_ALPHA,
            js_enter=self.SPEC_JS_ENTER if self._use_jsd else self.SPEC_ENTER,
            js_exit=self.SPEC_JS_EXIT if self._use_jsd else self.SPEC_EXIT,
            baseline_enter=self.SPEC_BASELINE_ENTER,
            baseline_frames=self.SPEC_BASELINE_FRAMES,
            baseline_max_volume=self.SPEC_BASELINE_MAX_VOL,
            confirm_frames=self.SPEC_CONFIRM_FRAMES,
            min_event_volume=self.SPEC_MIN_EVENT_VOL,
            supersede_ratio=self.SPEC_SUPERSEDE_RATIO,
            wavelengths=self._spectrum_axis,
            use_jsd=self._use_jsd,
        )
        self._spec_state = "IDLE"
        self._spec_ep_vol: float | None = None
        self._spec_ep_t: float | None = None
        self._spec_max_js = 0.0
        self._spec_last_diag: dict[str, Any] = self._spectral.last
        self._spec_done = False

        self._kf = EndpointFusionKF() if self._enable_kf else None
        # Endpoint pair the KF has already been run on, so a superseded value can
        # be detected and re-fused instead of gated against a stale state.
        self._kf_consumed: tuple[float | None, float | None] | None = None
        self._last_pot_result: dict[str, Any] | None = None
        self._last_spec_result: dict[str, Any] | None = None
        self._last_reliability = self._build_reliability(None, None)

    # ================================================================
    # Data input
    # ================================================================

    def feed_potential(self, vol: float, t: float, v: float) -> None:
        """Feed one potential point: volume in mL, time in seconds, voltage."""
        vol = float(vol)
        t = float(t)
        v_sm = self._pot_v_smooth(float(v))

        if self._pot_prev_t is not None and self._pot_prev_v is not None:
            dt = t - self._pot_prev_t
            dv = v_sm - self._pot_prev_v
            d_raw = dv / dt if dt > 0 else 0.0
        else:
            d_raw = 0.0

        d_sm = self._pot_d_smooth(d_raw)
        self._pot_prev_v = v_sm
        self._pot_prev_t = t
        self._pot_last_d = d_sm
        self._pot_sample_count += 1
        self._pot_raw_buf.append(float(d_raw))
        self._pot_vol_buf.append(vol)

        if not self._pot_obs_done:
            self._pot_d_vals.append(d_sm)
            if vol >= self.POT_OBSERVE_VOL:
                arr = np.asarray(self._pot_d_vals, dtype=np.float64)
                if len(arr) < 3:
                    return
                d_mean = float(np.mean(arr))
                d_std = max(float(np.std(arr, ddof=1)), abs(d_mean) * 0.01, 1e-6)
                self._pot_enter_th = d_mean - max(
                    self.POT_MIN_ENTER, self.POT_ENTER_SIGMA * d_std
                )
                self._pot_exit_th = d_mean - max(
                    self.POT_MIN_EXIT, self.POT_EXIT_SIGMA * d_std
                )
                self._pot_obs_done = True
                self._pot_d_vals = []
            return

        if not self._pot_done:
            if self._pot_state == "IDLE" and d_sm < self._pot_enter_th:
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
                    and self._pot_cand_vol is not None
                    and vol - self._pot_entry_vol > self.POT_CONFIRM_VOL
                ):
                    self._pot_ep_vol = self._pot_cand_vol
                    self._pot_ep_t = self._pot_cand_vol / self._flow_rate
                    self._pot_state = "END_CONFIRMED"
                    self._pot_done = True

    def feed_spectrum(
        self,
        vol: float,
        spectrum: np.ndarray,
        t: float | None = None,
    ) -> None:
        """Feed one raw-channel or reconstructed full-spectrum frame."""
        diag = self._spectral.update(float(vol), np.asarray(spectrum), t=t)
        self._spec_last_diag = diag
        self._spec_state = str(diag["state"])
        self._spec_max_js = max(self._spec_max_js, float(diag.get("max_js", 0.0)))
        candidate = self._spectral.endpoint_volume
        # The tracker reports the strongest excursion so far, so the candidate can
        # move when a later, clearly stronger event supersedes an early transient.
        if candidate is not None and candidate != self._spec_ep_vol:
            self._spec_ep_vol = float(candidate)
            self._spec_ep_t = self._spec_ep_vol / self._flow_rate
            self._spec_done = True

    def set_spectrum_axis(self, wavelengths: np.ndarray | None) -> None:
        """Configure the wavelength axis used by causal cross-curvature."""
        if wavelengths is None:
            self._spectrum_axis = None
        else:
            self._spectrum_axis = np.asarray(wavelengths, dtype=np.float64).copy()
        self._spectral.set_wavelengths(self._spectrum_axis)

    # ================================================================
    # Results and reliability
    # ================================================================

    def _build_pot_result(self) -> dict[str, Any] | None:
        if self._pot_ep_vol is None:
            return None
        result: dict[str, Any] = {
            "volume": self._pot_ep_vol,
            "time": self._pot_ep_t or (self._pot_ep_vol / self._flow_rate),
            "min_dvdt": round(self._pot_min_d, 2),
            "state": self._pot_state,
        }
        if self._kf is not None:
            kf = self._kf.snapshot()
            for field in ("endpoint_std", "nis", "innovation"):
                kf_value = kf.get(field)
                if kf_value is not None:
                    result[field] = kf_value
        return result

    def _build_spec_result(self) -> dict[str, Any] | None:
        if self._spec_ep_vol is None:
            return None
        diag = self._spec_last_diag
        # max_ce is retained as a schema alias for old exports/consumers.
        return {
            "volume": self._spec_ep_vol,
            "time": self._spec_ep_t or (self._spec_ep_vol / self._flow_rate),
            "max_ce": round(self._spec_max_js, 8),
            "max_js": round(self._spec_max_js, 8),
            "js_local": round(float(diag.get("js_local", 0.0)), 8),
            "js_speed": round(float(diag.get("js_speed", 0.0)), 8),
            "js_base": round(float(diag.get("js_base", 0.0)), 8),
            "cross_curvature": round(float(diag.get("cross_curvature", 0.0)), 8)
            if self._enable_curvature
            else None,
            "event_maturity": float(diag.get("event_maturity", 0.0)),
            "recovery_frames": int(diag.get("recovery_frames", 0)),
            "event_count": int(diag.get("event_count", 0)),
            "superseded_count": int(diag.get("superseded_count", 0)),
            "event_peak_speed": round(float(diag.get("event_peak_speed", 0.0)), 8),
            "state": self._spec_state,
        }

    def _build_reliability(
        self,
        pot: dict[str, Any] | None,
        spec: dict[str, Any] | None,
    ) -> dict[str, Any]:
        pot_confirmed = pot is not None
        spec_confirmed = spec is not None
        diagnostic = self._spec_last_diag
        kf = self._kf.snapshot() if self._kf is not None else {}
        if pot_confirmed and spec_confirmed:
            status = "CONFIRMED" if self._kf is not None and self._kf.can_fuse else "CONFLICT"
        elif pot_confirmed or spec_confirmed:
            status = "CONFIRMED" if (pot_confirmed and not self._enable_kf) else "CANDIDATE"
        elif self._pot_state == "TRACKING" or self._spec_state == "IN_CHANGE":
            status = "CONFIRMING"
        elif self._pot_sample_count == 0 and diagnostic.get("sample_count", 0) == 0:
            status = "UNOBSERVABLE"
        else:
            status = "EARLY_WARNING"

        reasons: list[str] = []
        if diagnostic.get("data_quality") not in {"ok", "no_spectrum"}:
            reasons.append(str(diagnostic["data_quality"]))
        if diagnostic.get("repeated_volume_count", 0):
            reasons.append("repeated_spectral_volume")
        if diagnostic.get("nonmonotonic_count", 0):
            reasons.append("nonmonotonic_volume")
        if self._kf is not None and pot_confirmed and spec_confirmed and not self._kf.can_fuse:
            reasons.append("kf_innovation_gate")
        if diagnostic.get("superseded_count", 0):
            reasons.append("spectral_endpoint_superseded")
        if not diagnostic.get("baseline_ready", False):
            reasons.append("baseline_pending")

        if pot_confirmed and spec_confirmed:
            agreement = abs(float(pot["volume"]) - float(spec["volume"]))
        else:
            agreement = None
        return {
            "status": status,
            "data_quality": {
                "potential_samples": self._pot_sample_count,
                "spectral_samples": int(diagnostic.get("sample_count", 0)),
                "valid_spectral_frames": self._spectral.valid_frame_count,
                "baseline_ready": bool(diagnostic.get("baseline_ready", False)),
                "repeated_spectral_volume": int(diagnostic.get("repeated_volume_count", 0)),
                "nonmonotonic_volume": int(diagnostic.get("nonmonotonic_count", 0)),
                "last_frame": diagnostic.get("data_quality", "no_spectrum"),
            },
            "potential_evidence": pot is not None,
            "spectral_evidence": spec is not None,
            "modal_consistency": {
                "agreement_mL": agreement,
                "kf_consistent": bool(self._kf.can_fuse) if self._kf is not None else None,
            },
            "event_maturity": float(diagnostic.get("event_maturity", 0.0)),
            "spectral_events": int(diagnostic.get("event_count", 0)),
            "spectral_superseded": int(diagnostic.get("superseded_count", 0)),
            "endpoint_std": kf.get("endpoint_std"),
            "spectral_delay": kf.get("spectral_delay"),
            "nis": kf.get("nis"),
            "innovation": kf.get("innovation"),
            "reason_codes": reasons,
        }

    def diagnostics(self) -> dict[str, Any]:
        """Return current causal feature and reliability diagnostics."""
        pot = self._build_pot_result()
        spec = self._build_spec_result()
        self._last_reliability = self._build_reliability(pot, spec)
        return {
            "potential_state": self._pot_state,
            "spectral_state": self._spec_state,
            "potential": pot,
            "spectral": spec,
            "spectral_features": dict(self._spec_last_diag),
            "kf": self._kf.snapshot() if self._kf is not None else None,
            "reliability": self._last_reliability,
        }

    def _consume_kf_observations(
        self, pot: dict[str, Any] | None, spec: dict[str, Any] | None
    ) -> None:
        if self._kf is None:
            return
        pot_vol = None if pot is None else float(pot["volume"])
        spec_vol = None if spec is None else float(spec["volume"])
        pair = (pot_vol, spec_vol)
        if pair == self._kf_consumed:
            return
        # Either endpoint can be revised after the KF has already consumed it: the
        # spectral candidate when a stronger excursion supersedes an early
        # transient, the potential one after AMPD refinement.  Gating the revised
        # value against a state built from the stale one would reject the
        # correction, so the filter is re-run from scratch on the current pair.
        self._kf.reset()
        if pot_vol is not None:
            self._kf.observe("potential", pot_vol, token=("potential", pot_vol))
        if spec_vol is not None:
            self._kf.observe("spectral", spec_vol, token=("spectral", spec_vol))
        self._kf_consumed = pair

    def detect(self) -> dict[str, Any] | None:
        """Return a backward-compatible endpoint result with diagnostics."""
        pot = self._build_pot_result()
        spec = self._build_spec_result()
        if pot is None and spec is None:
            self._last_reliability = self._build_reliability(None, None)
            return None

        self._consume_kf_observations(pot, spec)
        # Rebuild child results after the first observation so exported NIS/std
        # fields describe the observation that was just consumed.
        pot = self._build_pot_result()
        spec = self._build_spec_result()
        reliability = self._build_reliability(pot, spec)
        self._last_reliability = reliability
        result: dict[str, Any]

        if pot is not None and spec is not None:
            kf = self._kf.snapshot() if self._kf is not None else None
            if self._kf is not None and self._kf.can_fuse and kf is not None:
                volume = float(kf["endpoint_volume"])
                result = {
                    "volume": round(volume, 3),
                    "time": round(volume / self._flow_rate, 3),
                    "confidence": "high",
                    "method": "consensus",
                    "potential": pot,
                    "spectral": spec,
                    "reliability": reliability,
                }
            elif self._kf is None and abs(pot["volume"] - spec["volume"]) < 0.3:
                volume = (pot["volume"] + spec["volume"]) / 2.0
                result = {
                    "volume": round(volume, 3),
                    "time": round((pot["time"] + spec["time"]) / 2.0, 3),
                    "confidence": "high",
                    "method": "consensus",
                    "potential": pot,
                    "spectral": spec,
                    "reliability": reliability,
                }
            else:
                result = {
                    "volume": round(float(pot["volume"]), 3),
                    "time": round(float(pot["time"]), 3),
                    "confidence": "low",
                    "method": "conflict",
                    "potential": pot,
                    "spectral": spec,
                    "warning": f"电位{pot['volume']:.3f}mL vs 光谱{spec['volume']:.3f}mL "
                    "未通过创新一致性门控",
                    "reliability": reliability,
                }
            return result

        if pot is not None:
            return {
                "volume": round(float(pot["volume"]), 3),
                "time": round(float(pot["time"]), 3),
                "confidence": "medium",
                "method": "potential_only",
                "potential": pot,
                "spectral": None,
                "reliability": reliability,
            }
        assert spec is not None
        return {
            "volume": round(float(spec["volume"]), 3),
            "time": round(float(spec["time"]), 3),
            "confidence": "medium",
            "method": "spectral_only",
            "potential": None,
            "spectral": spec,
            "reliability": reliability,
        }

    def refine_with_ampd(self) -> float | None:
        """Use offline AMPD refinement after enough historical samples exist."""
        if len(self._pot_raw_buf) < 20:
            return None
        arr = np.asarray(self._pot_raw_buf, dtype=np.float64)
        idx = _ampd_peak_idx(-arr)
        if idx is None or idx >= len(self._pot_vol_buf) * self.AMPD_MAX_POSITION:
            return None
        refined_vol = self._pot_vol_buf[idx]
        self._pot_ep_vol = refined_vol
        self._pot_ep_t = refined_vol / self._flow_rate
        return refined_vol

    # ================================================================
    # Lifecycle and compatibility properties
    # ================================================================

    def reset(self) -> None:
        """Clear all filters and state for a new titration."""
        self._reset_state()

    @property
    def potential_state(self) -> str:
        return self._pot_state

    @property
    def spectral_state(self) -> str:
        return self._spec_state

    @property
    def endpoint_volume(self) -> float | None:
        if self._kf is not None and self._kf.can_fuse:
            return float(self._kf.x[0])
        return self._pot_ep_vol or self._spec_ep_vol


__all__ = ["EndpointDetector", "savgol_filter"]
