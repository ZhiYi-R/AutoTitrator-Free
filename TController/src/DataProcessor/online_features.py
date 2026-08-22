"""Causal online features for multimodal titration endpoint detection.

The classes in this module are deliberately independent of the GUI and
communication layer.  Every update consumes only the current observation and
state retained from previous observations.

Two properties of ``SpectralFeatureTracker`` are worth knowing before reading it:

* The volume-normalised speed is anchored to the last *advancing* frame, not to
  the previous frame.  Production feeds a spectrum per AS7341 frame while volume
  comes from the pump, so several frames can share one volume; feeding those into
  the speed filter would inject zeros and wash out a real excursion.
* ``END_CONFIRMED`` re-arms.  Excursions are accumulated in ``events`` and the
  reported endpoint is the strongest one, replaced only when a later excursion
  beats it by ``supersede_ratio``.  A one-shot latch picked an early transient
  0.97 mL before the true endpoint on real data (Paper/ExpData group B), which the
  Kalman gate could only reject, not repair.
"""

from __future__ import annotations

from collections import deque
from typing import Any

import numpy as np

_EPS = 1e-12

# Measured on Paper/ExpData (2026-08-21): the float64 round-off floor of
# ``js_divergence`` on real 8-channel frames is ~5e-17, while the titration
# plateau sits at ~2e-12 and the endpoint event reaches ~2e-7.  ``js_speed``
# divides by the squared volume step (~2.4e-8 there, i.e. a 4e7 amplification),
# so a JS value at the round-off floor must never be normalised -- otherwise the
# speed signal is amplified arithmetic noise rather than chemistry.
_JS_FLOOR = 1e-14


def _finite_vector(values: np.ndarray) -> tuple[np.ndarray | None, str | None]:
    """Return a non-negative finite vector, or a data-quality reason."""
    arr = np.asarray(values, dtype=np.float64).reshape(-1)
    if arr.size == 0:
        return None, "spectrum_empty"
    if not np.all(np.isfinite(arr)):
        return None, "spectrum_nonfinite"
    arr = np.maximum(arr, 0.0)
    total = float(np.sum(arr))
    if total <= _EPS:
        return None, "spectrum_zero"
    return arr / total, None


def normalize_spectrum(values: np.ndarray, epsilon: float = 1e-9) -> np.ndarray:
    """Normalize a spectrum with additive smoothing and finite-value checks."""
    arr = np.asarray(values, dtype=np.float64).reshape(-1)
    if arr.size == 0 or not np.all(np.isfinite(arr)):
        raise ValueError("spectrum must be a non-empty finite array")
    arr = np.maximum(arr, 0.0) + float(epsilon)
    return arr / float(np.sum(arr))


def js_divergence(p: np.ndarray, q: np.ndarray) -> float:
    """Return the natural-log Jensen-Shannon divergence of two distributions."""
    p_norm = normalize_spectrum(p)
    q_norm = normalize_spectrum(q)
    midpoint = 0.5 * (p_norm + q_norm)
    value = 0.5 * np.sum(p_norm * np.log(p_norm / midpoint))
    value += 0.5 * np.sum(q_norm * np.log(q_norm / midpoint))
    return float(np.clip(value, 0.0, np.log(2.0)))


def cross_entropy(p: np.ndarray, q: np.ndarray) -> float:
    """Return the legacy directional cross-entropy used by older builds."""
    p_norm = normalize_spectrum(p)
    q_norm = normalize_spectrum(q)
    return float(-np.sum(p_norm * np.log(np.maximum(q_norm, 1e-12))))


def cross_entropy_excess(p: np.ndarray, q: np.ndarray) -> float:
    """Return the legacy cross-entropy above its own floor, i.e. ``KL(p||q)``.

    ``cross_entropy(p, p)`` is the entropy of ``p`` (~ln(n)), not zero, so the raw
    value cannot drive a threshold state machine: divided by the squared volume
    step it stays enormous forever and the tracker can never leave ``IN_CHANGE``.
    Measured with ``use_jsd=False`` on a synthetic titration, the speed signal sat
    at 1.4e4 from the first post-baseline frame onwards and no spectral endpoint
    was ever confirmed.  Subtracting the floor leaves the Kullback-Leibler
    divergence, which is zero for identical distributions and therefore
    comparable against an exit threshold.  ``cross_entropy`` itself is unchanged
    because it is re-exported and read by older scripts.
    """
    p_norm = normalize_spectrum(p)
    q_norm = normalize_spectrum(q)
    delta = np.log(np.maximum(p_norm, 1e-12)) - np.log(np.maximum(q_norm, 1e-12))
    return float(max(np.sum(p_norm * delta), 0.0))


class _ScalarEWMA:
    __slots__ = ("alpha", "value")

    def __init__(self, alpha: float) -> None:
        self.alpha = float(np.clip(alpha, 0.0, 1.0))
        self.value: float | None = None

    def __call__(self, value: float) -> float:
        value = float(value)
        if self.value is None:
            self.value = value
        else:
            self.value = self.alpha * value + (1.0 - self.alpha) * self.value
        return self.value

    def hold(self) -> float:
        """Return the current level without folding in a new sample."""
        return 0.0 if self.value is None else float(self.value)

    def reset(self) -> None:
        self.value = None


class SpectralFeatureTracker:
    """Causal JS, baseline distance and cross-curvature tracker.

    ``update`` accepts arbitrary-length spectra.  Spectral frames may reuse the
    most recent ADC volume, so the volume-normalised speed is anchored to the
    last frame that actually advanced the burette: JS is accumulated across the
    stale frames and divided by the real volume step, and the speed filter is
    held (not fed a zero) while the volume stands still.

    Confirmation is not one-shot.  Each completed excursion is recorded as an
    event and the reported endpoint is the strongest one seen so far, so a weak
    early transient cannot permanently mask the real endpoint.
    """

    IDLE = "IDLE"
    IN_CHANGE = "IN_CHANGE"
    END_CONFIRMED = "END_CONFIRMED"

    def __init__(
        self,
        *,
        alpha: float = 0.20,
        js_enter: float = 0.05,
        js_exit: float = 0.008,
        baseline_enter: float = 3e-7,
        baseline_frames: int = 12,
        baseline_max_volume: float = 0.30,
        confirm_frames: int = 4,
        min_event_volume: float = 0.08,
        epsilon_volume: float = 1e-8,
        lookback_frames: int = 8,
        supersede_ratio: float = 1.5,
        js_floor: float = _JS_FLOOR,
        wavelengths: np.ndarray | None = None,
        use_jsd: bool = True,
    ) -> None:
        self.alpha = float(alpha)
        self.js_enter = float(js_enter)
        self.js_exit = float(js_exit)
        self.baseline_enter = float(baseline_enter)
        self.baseline_frames = max(3, int(baseline_frames))
        self.baseline_max_volume = float(baseline_max_volume)
        self.confirm_frames = max(1, int(confirm_frames))
        self.min_event_volume = float(min_event_volume)
        self.epsilon_volume = max(float(epsilon_volume), 1e-12)
        self.lookback_frames = max(1, int(lookback_frames))
        self.supersede_ratio = max(float(supersede_ratio), 1.0)
        self.js_floor = max(float(js_floor), 0.0)
        self.use_jsd = bool(use_jsd)
        self._configured_wavelengths = (
            None if wavelengths is None else np.asarray(wavelengths, dtype=np.float64).copy()
        )
        self._reset_state()

    def _reset_state(self) -> None:
        self._smoothed: np.ndarray | None = None
        self._previous_volume: float | None = None
        # Anchor frame for volume-normalised features: the last frame whose
        # volume actually advanced.
        self._sync_spectrum: np.ndarray | None = None
        self._sync_volume: float | None = None
        self._baseline_sum: np.ndarray | None = None
        self._baseline_count = 0
        self._baseline: np.ndarray | None = None
        self._frame_count = 0
        self._valid_frame_count = 0
        self._invalid_frame_count = 0
        self._nonmonotonic_count = 0
        self._repeated_volume_count = 0
        self._last_volume_sync_valid = False
        self._state = self.IDLE
        self._candidate_volume: float | None = None
        self._entry_volume: float | None = None
        self._peak_value = 0.0
        self._peak_js = 0.0
        self._recovery_frames = 0
        self._recent: deque[tuple[float, float]] = deque(maxlen=self.lookback_frames)
        self._events: list[dict[str, float]] = []
        self._best_event: dict[str, float] | None = None
        self._supersede_count = 0
        self._last: dict[str, Any] = self._empty_diagnostic()
        self._js_smooth = _ScalarEWMA(self.alpha)
        self._speed_smooth = _ScalarEWMA(self.alpha)
        self._curvature_smooth = _ScalarEWMA(self.alpha)
        self._configured_axis = self._configured_wavelengths

    def reset(self) -> None:
        """Clear history while retaining feature configuration and wavelength axis."""
        self._reset_state()

    def set_wavelengths(self, wavelengths: np.ndarray | None) -> None:
        """Set the wavelength/channel axis used by cross-curvature."""
        if wavelengths is None:
            self._configured_wavelengths = None
            self._configured_axis = None
            return
        axis = np.asarray(wavelengths, dtype=np.float64).reshape(-1)
        if axis.size < 2 or not np.all(np.isfinite(axis)):
            raise ValueError("wavelength axis must contain at least two finite values")
        if np.any(np.diff(axis) <= 0):
            raise ValueError("wavelength axis must be strictly increasing")
        self._configured_wavelengths = axis.copy()
        self._configured_axis = axis.copy()

    @staticmethod
    def _empty_diagnostic() -> dict[str, Any]:
        return {
            "sample_count": 0,
            "valid_frame": False,
            "data_quality": "no_spectrum",
            "volume": None,
            "delta_volume": 0.0,
            "volume_sync_valid": False,
            "js_local": 0.0,
            "js_local_smooth": 0.0,
            "js_speed": 0.0,
            "js_speed_smooth": 0.0,
            "js_base": 0.0,
            "cross_curvature": 0.0,
            "curvature_peak_channel": None,
            "state": SpectralFeatureTracker.IDLE,
            "candidate_volume": None,
            "max_js": 0.0,
            "event_maturity": 0.0,
            "recovery_frames": 0,
            "baseline_ready": False,
            "repeated_volume_count": 0,
            "nonmonotonic_count": 0,
            "event_count": 0,
            "superseded_count": 0,
            "event_peak_speed": 0.0,
        }

    def _axis_for(self, size: int) -> np.ndarray:
        if self._configured_axis is not None and self._configured_axis.size == size:
            return self._configured_axis
        return np.arange(size, dtype=np.float64)

    def _lookback_peak(self, volume: float, speed: float) -> tuple[float, float]:
        """Return the strongest (speed, volume) over the recent causal window.

        The speed filter lags the underlying excursion, so the frame that first
        crosses ``js_enter`` can already be on the declining flank of a short
        transient.  Seeding the peak from the retained window keeps the
        candidate on the actual maximum instead of the crossing point.
        """
        peak_speed, peak_volume = speed, volume
        for past_volume, past_speed in self._recent:
            if past_speed > peak_speed:
                peak_speed, peak_volume = past_speed, past_volume
        return peak_speed, peak_volume

    def _commit_event(self) -> None:
        """Record the finished excursion and keep the strongest one."""
        if self._candidate_volume is None:
            return
        event = {
            "candidate_volume": float(self._candidate_volume),
            "entry_volume": float(self._entry_volume or self._candidate_volume),
            "peak_speed": float(self._peak_value),
            "peak_js": float(self._peak_js),
        }
        self._events.append(event)
        if self._best_event is None:
            self._best_event = event
        elif event["peak_speed"] > self._best_event["peak_speed"] * self.supersede_ratio:
            # Hysteresis: a later excursion only takes over when it is clearly
            # stronger, so near-ties do not make the reported endpoint flap.
            self._best_event = event
            self._supersede_count += 1

    def update(self, volume: float, spectrum: np.ndarray, t: float | None = None) -> dict[str, Any]:
        """Consume one spectrum and return a JSON-friendly causal diagnostic."""
        del t  # The feature is volume-causal; time is retained by the detector.
        self._frame_count += 1
        volume = float(volume)
        normalized, reason = _finite_vector(np.asarray(spectrum))
        if normalized is None:
            self._invalid_frame_count += 1
            self._last = dict(self._last)
            self._last.update(
                {
                    "sample_count": self._frame_count,
                    "valid_frame": False,
                    "data_quality": reason,
                    "volume": volume,
                    "baseline_ready": self._baseline is not None,
                    "repeated_volume_count": self._repeated_volume_count,
                    "nonmonotonic_count": self._nonmonotonic_count,
                }
            )
            return dict(self._last)

        self._valid_frame_count += 1
        smoothed = normalized if self._smoothed is None else (
            self.alpha * normalized + (1.0 - self.alpha) * self._smoothed
        )
        smoothed = smoothed / max(float(np.sum(smoothed)), _EPS)

        if self._previous_volume is None:
            delta_volume = 0.0
            sync_valid = False
        else:
            delta_volume = volume - self._previous_volume
            if delta_volume > self.epsilon_volume:
                sync_valid = True
            elif abs(delta_volume) <= self.epsilon_volume:
                sync_valid = False
                self._repeated_volume_count += 1
            else:
                sync_valid = False
                self._nonmonotonic_count += 1
        self._last_volume_sync_valid = sync_valid

        # Frame-to-frame JS stays a pure diagnostic; it is not volume-normalised
        # and so is meaningless as an event driver when frames repeat a volume.
        local = 0.0
        if self._smoothed is not None:
            local = (
                js_divergence(smoothed, self._smoothed)
                if self.use_jsd
                else cross_entropy_excess(smoothed, self._smoothed)
            )
        local_smooth = self._js_smooth(local)

        # Volume-normalised speed is anchored to the last advancing frame.  JS
        # between nearby distributions is second order, so dividing by the
        # squared step yields a step-size invariant Fisher-Rao speed squared.
        speed = self._speed_smooth.hold()
        speed_raw = 0.0
        curvature = 0.0
        peak_channel: int | None = None
        anchor_delta = (
            0.0 if self._sync_volume is None else volume - self._sync_volume
        )
        if self._sync_spectrum is not None and anchor_delta > self.epsilon_volume:
            anchor_js = (
                js_divergence(smoothed, self._sync_spectrum)
                if self.use_jsd
                else cross_entropy_excess(smoothed, self._sync_spectrum)
            )
            if anchor_js > self.js_floor:
                speed_raw = anchor_js / (anchor_delta * anchor_delta)
            shape_gradient = (
                np.log(np.maximum(smoothed, 1e-12))
                - np.log(np.maximum(self._sync_spectrum, 1e-12))
            ) / anchor_delta
            axis = self._axis_for(smoothed.size)
            if axis.size == shape_gradient.size and shape_gradient.size >= 3:
                wavelength_gradient = np.gradient(shape_gradient, axis)
                curvature = float(np.sqrt(np.mean(wavelength_gradient**2)))
                peak_channel = int(np.argmax(np.abs(wavelength_gradient)))
            speed = self._speed_smooth(speed_raw)
            self._curvature_smooth(curvature)
            self._sync_spectrum = smoothed.copy()
            self._sync_volume = volume
        elif self._sync_spectrum is None:
            self._sync_spectrum = smoothed.copy()
            self._sync_volume = volume
        speed_smooth = speed
        curvature_smooth = self._curvature_smooth.hold()

        if self._baseline is None and volume <= self.baseline_max_volume:
            if self._baseline_sum is None:
                self._baseline_sum = np.zeros_like(smoothed)
            self._baseline_sum += smoothed
            self._baseline_count += 1
            if self._baseline_count >= self.baseline_frames:
                self._baseline = self._baseline_sum / float(self._baseline_count)
                self._baseline /= max(float(np.sum(self._baseline)), _EPS)

        base_js = 0.0 if self._baseline is None else js_divergence(smoothed, self._baseline)

        if self._baseline is not None:
            # END_CONFIRMED re-arms: a later, clearly stronger excursion must be
            # able to take over the reported endpoint.
            if self._state in (self.IDLE, self.END_CONFIRMED):
                if speed_smooth >= self.js_enter and base_js >= self.baseline_enter:
                    peak_speed, peak_volume = self._lookback_peak(volume, speed_smooth)
                    self._state = self.IN_CHANGE
                    self._entry_volume = volume
                    self._candidate_volume = peak_volume
                    self._peak_value = peak_speed
                    self._peak_js = local
                    self._recovery_frames = 0
            elif self._state == self.IN_CHANGE:
                if speed_smooth > self._peak_value:
                    self._peak_value = speed_smooth
                    self._peak_js = local
                    self._candidate_volume = volume
                    self._recovery_frames = 0
                elif speed_smooth <= self.js_exit:
                    self._recovery_frames += 1
                    if (
                        self._entry_volume is not None
                        and volume - self._entry_volume >= self.min_event_volume
                        and self._recovery_frames >= self.confirm_frames
                    ):
                        self._state = self.END_CONFIRMED
                        self._commit_event()
                else:
                    self._recovery_frames = 0

        maturity = 0.0
        if self._state == self.IN_CHANGE:
            maturity = min(0.99, self._recovery_frames / float(self.confirm_frames))
        elif self._state == self.END_CONFIRMED:
            maturity = 1.0

        best = self._best_event
        self._smoothed = smoothed.copy()
        self._previous_volume = volume
        self._recent.append((volume, speed_smooth))
        self._last = {
            "sample_count": self._frame_count,
            "valid_frame": True,
            "data_quality": "ok",
            "volume": volume,
            "delta_volume": float(delta_volume),
            "volume_sync_valid": bool(sync_valid),
            "js_local": float(local),
            "js_local_smooth": float(local_smooth),
            "js_speed": float(speed_raw),
            "js_speed_smooth": float(speed_smooth),
            "js_base": float(base_js),
            "cross_curvature": float(curvature_smooth),
            "curvature_peak_channel": peak_channel,
            "state": self._state,
            "candidate_volume": None if best is None else best["candidate_volume"],
            "max_js": float(self._peak_js if best is None else best["peak_js"]),
            "event_maturity": float(maturity),
            "recovery_frames": self._recovery_frames,
            "baseline_ready": self._baseline is not None,
            "repeated_volume_count": self._repeated_volume_count,
            "nonmonotonic_count": self._nonmonotonic_count,
            "event_count": len(self._events),
            "superseded_count": self._supersede_count,
            "event_peak_speed": float(0.0 if best is None else best["peak_speed"]),
        }
        return dict(self._last)

    @property
    def last(self) -> dict[str, Any]:
        return dict(self._last)

    @property
    def valid_frame_count(self) -> int:
        """Number of frames that passed the finite/non-zero spectrum checks."""
        return self._valid_frame_count

    @property
    def events(self) -> list[dict[str, float]]:
        """All confirmed excursions, in the order they completed."""
        return [dict(event) for event in self._events]

    @property
    def endpoint_volume(self) -> float | None:
        """Candidate volume of the strongest confirmed excursion so far."""
        if self._best_event is None:
            return None
        return float(self._best_event["candidate_volume"])


class EndpointFusionKF:
    """Two-state linear KF for potential endpoint and spectral volume delay."""

    # The innovation of each observation is scalar, so the chi-square gate has
    # one degree of freedom: 6.635 is the 99th percentile of chi2(1).  The
    # previous 9.21 is the chi2(2) percentile and was a degrees-of-freedom
    # mismatch, giving an effective significance of 0.24% instead of 1%.
    DEFAULT_NIS_GATE = 6.635

    def __init__(
        self,
        *,
        potential_std: float = 0.012,
        spectral_std: float = 0.025,
        delay_std: float = 0.08,
        process_std: float = 0.004,
        delay_prior: float = 0.02,
        nis_gate: float = DEFAULT_NIS_GATE,
    ) -> None:
        self.potential_var = max(float(potential_std) ** 2, 1e-8)
        self.spectral_var = max(float(spectral_std) ** 2, 1e-8)
        self.delay_var = max(float(delay_std) ** 2, 1e-8)
        self.process_var = max(float(process_std) ** 2, 1e-10)
        self.delay_prior = float(delay_prior)
        self.nis_gate = max(float(nis_gate), 1.0)
        self.reset()

    def reset(self) -> None:
        self.x = np.zeros(2, dtype=np.float64)
        self.P = np.eye(2, dtype=np.float64) * 1e6
        self.initialized = False
        self.observed: set[str] = set()
        self._observed_tokens: set[object] = set()
        self.last: dict[str, Any] = {
            "initialized": False,
            "endpoint_volume": None,
            "spectral_delay": None,
            "endpoint_std": None,
            "innovation": None,
            "innovation_covariance": None,
            "nis": None,
            "accepted": False,
            "kind": None,
            "consistent": False,
            "reason": "no_observation",
        }

    def _prediction(self) -> tuple[np.ndarray, np.ndarray]:
        if not self.initialized:
            return self.x.copy(), self.P.copy()
        return self.x.copy(), self.P + np.eye(2) * self.process_var

    def observe(self, kind: str, volume: float, token: object | None = None) -> dict[str, Any]:
        """Consume one endpoint observation, idempotently when token repeats."""
        if kind not in {"potential", "spectral"}:
            raise ValueError("kind must be 'potential' or 'spectral'")
        if token is None:
            token = (kind, round(float(volume), 9))
        if token in self._observed_tokens:
            return dict(self.last)
        z = float(volume)
        if not np.isfinite(z):
            self.last = dict(self.last)
            self.last.update({"kind": kind, "accepted": False, "reason": "nonfinite_observation"})
            return dict(self.last)

        if not self.initialized:
            if kind == "potential":
                self.x[:] = (z, 0.0)
                self.P[:] = np.diag([self.potential_var, self.delay_var])
            else:
                self.x[:] = (z - self.delay_prior, self.delay_prior)
                self.P[:] = np.diag([self.spectral_var + self.delay_var, self.delay_var])
            self.initialized = True
            self.observed.add(kind)
            self._observed_tokens.add(token)
            self.last = self._snapshot(
                kind=kind,
                innovation=0.0,
                innovation_covariance=self.P[0, 0],
                nis=0.0,
                accepted=True,
                reason="initialized",
            )
            return dict(self.last)

        x_prior, p_prior = self._prediction()
        if kind == "potential":
            h = np.array([1.0, 0.0])
            r = self.potential_var
        else:
            h = np.array([1.0, 1.0])
            r = self.spectral_var
        innovation = z - float(h @ x_prior)
        innovation_covariance = float(h @ p_prior @ h + r)
        innovation_covariance = max(innovation_covariance, 1e-10)
        nis = float(innovation * innovation / innovation_covariance)
        accepted = bool(nis <= self.nis_gate)
        if accepted:
            gain = (p_prior @ h) / innovation_covariance
            self.x = x_prior + gain * innovation
            self.P = (np.eye(2) - np.outer(gain, h)) @ p_prior
            self.P = 0.5 * (self.P + self.P.T)
            self.observed.add(kind)
            self._observed_tokens.add(token)
        else:
            self.x = x_prior
            self.P = p_prior
        self.last = self._snapshot(
            kind=kind,
            innovation=innovation,
            innovation_covariance=innovation_covariance,
            nis=nis,
            accepted=accepted,
            reason="accepted" if accepted else "nis_gate",
        )
        return dict(self.last)

    def _snapshot(
        self,
        *,
        kind: str,
        innovation: float,
        innovation_covariance: float,
        nis: float,
        accepted: bool,
        reason: str,
    ) -> dict[str, Any]:
        endpoint_std = float(np.sqrt(max(self.P[0, 0], 0.0)))
        return {
            "initialized": bool(self.initialized),
            "endpoint_volume": float(self.x[0]),
            "spectral_delay": float(self.x[1]),
            "endpoint_std": endpoint_std,
            "innovation": float(innovation),
            "innovation_covariance": float(innovation_covariance),
            "nis": float(nis),
            "accepted": bool(accepted),
            "kind": kind,
            "consistent": bool(self.observed == {"potential", "spectral"}),
            "reason": reason,
        }

    def snapshot(self) -> dict[str, Any]:
        return dict(self.last)

    @property
    def can_fuse(self) -> bool:
        return self.observed == {"potential", "spectral"} and self.last.get("accepted", False)


__all__ = [
    "EndpointFusionKF",
    "SpectralFeatureTracker",
    "cross_entropy",
    "js_divergence",
    "normalize_spectrum",
]
