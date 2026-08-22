from __future__ import annotations

import sys
from pathlib import Path

import numpy as np

sys.path.insert(0, str(Path(__file__).parents[1] / "src"))

from DataProcessor.endpoint import EndpointDetector, _ampd_peak_idx
from DataProcessor.online_features import (
    EndpointFusionKF,
    SpectralFeatureTracker,
    cross_entropy,
    cross_entropy_excess,
    js_divergence,
)


def _baseline_frames(tracker: SpectralFeatureTracker) -> None:
    for i in range(1, 9):
        tracker.update(i * 0.05, np.ones(4))


def _tracker_for_events(**overrides: float) -> SpectralFeatureTracker:
    """Tracker tuned so a weak and a strong excursion both confirm."""
    kwargs: dict[str, float] = {
        "js_enter": 0.1,
        "js_exit": 0.03,
        "baseline_enter": 0.001,
        "baseline_frames": 4,
        "baseline_max_volume": 0.4,
        "confirm_frames": 3,
        "min_event_volume": 0.05,
    }
    kwargs.update(overrides)
    return SpectralFeatureTracker(**kwargs)  # type: ignore[arg-type]


def _feed_excursion(
    tracker: SpectralFeatureTracker, volume: float, amplitude: float, recovery: int = 30
) -> tuple[float, dict]:
    """Drive one rise-and-recover excursion; return the new volume and diagnostic."""
    diagnostic: dict = {}
    for _ in range(3):
        volume += 0.05
        diagnostic = tracker.update(volume, np.array([amplitude, 1.0, 1.0, 1.0]))
    for _ in range(recovery):
        volume += 0.05
        diagnostic = tracker.update(volume, np.ones(4))
    return volume, diagnostic


def test_js_is_symmetric_bounded_and_gain_invariant() -> None:
    p = np.array([1.0, 2.0, 4.0, 8.0])
    q = np.array([2.0, 3.0, 5.0, 7.0])
    assert np.isclose(js_divergence(p, q), js_divergence(q, p))
    assert 0.0 <= js_divergence(p, q) <= np.log(2.0)
    assert np.isclose(js_divergence(p, q), js_divergence(17.0 * p, 17.0 * q))


def test_tracker_handles_invalid_and_repeated_volume_without_infinity() -> None:
    tracker = SpectralFeatureTracker()
    first = tracker.update(0.1, np.ones(4))
    repeated = tracker.update(0.1, np.array([2.0, 1.0, 1.0, 1.0]))
    invalid = tracker.update(0.1, np.array([1.0, np.nan, 1.0, 1.0]))
    assert first["valid_frame"] is True
    assert repeated["volume_sync_valid"] is False
    assert repeated["repeated_volume_count"] == 1
    assert np.isfinite(repeated["js_local"])
    assert np.isfinite(repeated["js_speed"])
    assert invalid["valid_frame"] is False
    assert invalid["data_quality"] == "spectrum_nonfinite"


def test_cross_curvature_is_causal() -> None:
    prefix = [
        np.array([1.0, 1.0, 2.0, 1.0, 1.0]),
        np.array([1.0, 2.0, 2.0, 1.0, 1.0]),
        np.array([1.0, 3.0, 2.0, 1.0, 1.0]),
    ]
    future = [
        np.array([1.0, 4.0, 1.0, 2.0, 1.0]),
        np.array([2.0, 1.0, 1.0, 4.0, 1.0]),
    ]
    left = SpectralFeatureTracker(baseline_frames=3, baseline_max_volume=0.2)
    right = SpectralFeatureTracker(baseline_frames=3, baseline_max_volume=0.2)
    left_values = [left.update(i * 0.05, frame) for i, frame in enumerate(prefix, 1)]
    right_values = [right.update(i * 0.05, frame) for i, frame in enumerate(prefix + future, 1)]
    for before, after in zip(left_values, right_values[: len(prefix)]):
        assert np.isclose(before["cross_curvature"], after["cross_curvature"])
        assert np.isclose(before["js_local"], after["js_local"])
        assert before["state"] == after["state"]


def test_peak_requires_recovery_before_confirmation() -> None:
    tracker = SpectralFeatureTracker(
        js_enter=0.2,
        js_exit=0.03,
        baseline_enter=0.001,
        baseline_frames=4,
        baseline_max_volume=0.4,
        confirm_frames=3,
        min_event_volume=0.05,
    )
    _baseline_frames(tracker)
    for volume in (0.45, 0.50, 0.55):
        diagnostic = tracker.update(volume, np.array([100.0, 1.0, 1.0, 1.0]))
        assert diagnostic["state"] == "IN_CHANGE"
    diagnostic = tracker.update(0.60, np.ones(4))
    assert diagnostic["state"] == "IN_CHANGE"
    for volume in tuple(np.arange(0.65, 2.05, 0.05)):
        diagnostic = tracker.update(float(volume), np.ones(4))
    assert diagnostic["state"] == "END_CONFIRMED"
    assert np.isfinite(float(diagnostic["candidate_volume"]))


def test_kf_gate_and_repeated_observation_are_stable() -> None:
    kf = EndpointFusionKF(potential_std=0.01, spectral_std=0.01, nis_gate=3.84)
    initial = kf.observe("potential", 1.0, token="potential-1")
    accepted = kf.observe("spectral", 1.03, token="spectral-1")
    repeated = kf.observe("spectral", 1.03, token="spectral-1")
    rejected = kf.observe("potential", 2.0, token="potential-2")
    assert initial["accepted"] is True
    assert accepted["accepted"] is True
    assert accepted["consistent"] is True
    assert repeated == accepted
    assert rejected["accepted"] is False
    assert rejected["reason"] == "nis_gate"
    assert np.isfinite(rejected["endpoint_std"])


def test_detector_keeps_legacy_feed_and_result_keys() -> None:
    detector = EndpointDetector(flow_rate=0.0061)
    for index in range(1, 240):
        volume = index * 0.01
        voltage = 1.0 - 0.8 * np.exp(-((volume - 1.0) ** 2) / (2.0 * 0.035**2))
        detector.feed_potential(volume, volume / 0.0061, voltage)
        detector.feed_spectrum(volume, np.array([1.0, 2.0, 3.0, 4.0]))
    result = detector.detect()
    assert detector.potential_state == "END_CONFIRMED"
    assert result is not None
    assert {"volume", "time", "confidence", "method", "potential", "spectral"} <= set(result)
    assert "reliability" in result
    assert result["potential"] is not None


def test_detector_reset_retains_spectrum_configuration() -> None:
    detector = EndpointDetector(
        flow_rate=0.0061,
        wavelengths=np.array([400.0, 500.0, 600.0, 700.0]),
    )
    detector.feed_spectrum(0.1, np.ones(4))
    detector.reset()
    diagnostic = detector.diagnostics()
    assert diagnostic["spectral_features"]["sample_count"] == 0
    detector.feed_spectrum(0.1, np.ones(4))
    assert np.isfinite(detector.diagnostics()["spectral_features"]["cross_curvature"])


def test_repeated_volume_holds_speed_instead_of_injecting_zero() -> None:
    """Production reuses one pump volume for several spectra; speed must not decay.

    The volume-normalised speed is undefined when the step is zero, so those frames
    hold the filter level.  Feeding a zero would drag a live excursion below the
    exit threshold and fake a recovery.
    """
    tracker = SpectralFeatureTracker(baseline_frames=3, baseline_max_volume=0.2)
    for index in range(1, 4):
        tracker.update(index * 0.05, np.ones(4))
    advancing = tracker.update(0.25, np.array([4.0, 1.0, 1.0, 1.0]))
    assert advancing["js_speed_smooth"] > 0.0
    for _ in range(5):
        repeated = tracker.update(0.25, np.array([4.0, 1.0, 1.0, 1.0]))
        assert repeated["volume_sync_valid"] is False
        assert repeated["js_speed_smooth"] == advancing["js_speed_smooth"]
        assert repeated["cross_curvature"] == advancing["cross_curvature"]
    assert repeated["repeated_volume_count"] == 5
    # A later advancing frame resumes normalisation against the last synced frame.
    resumed = tracker.update(0.30, np.array([4.0, 1.0, 1.0, 1.0]))
    assert resumed["volume_sync_valid"] is True


def test_stronger_late_excursion_supersedes_an_early_transient() -> None:
    """Regression for Paper/ExpData group B: the one-shot latch chose a transient."""
    tracker = _tracker_for_events()
    _baseline_frames(tracker)
    volume, weak = _feed_excursion(tracker, 0.40, 3.0)
    assert weak["state"] == "END_CONFIRMED"
    weak_candidate = weak["candidate_volume"]
    volume, strong = _feed_excursion(tracker, volume, 100.0)
    assert strong["state"] == "END_CONFIRMED"
    assert strong["candidate_volume"] != weak_candidate
    assert strong["candidate_volume"] > weak_candidate
    assert strong["event_count"] == 2
    assert strong["superseded_count"] == 1
    assert strong["event_peak_speed"] > weak["event_peak_speed"]
    assert tracker.endpoint_volume == strong["candidate_volume"]
    assert len(tracker.events) == 2


def test_supersede_ratio_suppresses_a_near_tie() -> None:
    """Identical excursions, only the hysteresis differs: the endpoint must not flap."""
    loose = _tracker_for_events(supersede_ratio=1.5)
    tight = _tracker_for_events(supersede_ratio=4.0)
    outcomes = []
    for tracker in (loose, tight):
        _baseline_frames(tracker)
        volume, _ = _feed_excursion(tracker, 0.40, 3.0)
        _, final = _feed_excursion(tracker, volume, 4.0)
        outcomes.append(final)
    assert outcomes[0]["superseded_count"] == 1
    assert outcomes[1]["superseded_count"] == 0
    assert outcomes[1]["candidate_volume"] < outcomes[0]["candidate_volume"]
    # Both saw the same two excursions; only the reported winner differs.
    assert outcomes[0]["event_count"] == outcomes[1]["event_count"] == 2


def test_round_off_scale_divergence_is_not_normalised() -> None:
    """js_speed divides by ~1e-8, so a divergence at the round-off floor must stay 0."""
    tracker = SpectralFeatureTracker()
    tracker.update(0.05, np.ones(4))
    tiny = tracker.update(0.10, np.array([1.0 + 1e-9, 1.0, 1.0, 1.0]))
    assert tiny["volume_sync_valid"] is True
    assert tiny["js_speed"] == 0.0
    real = tracker.update(0.15, np.array([2.0, 1.0, 1.0, 1.0]))
    assert real["js_speed"] > 0.0


def test_kf_reset_lets_a_revised_endpoint_pair_refuse() -> None:
    """A superseded spectral endpoint must be re-fusable, not blocked by dedup."""
    kf = EndpointFusionKF(potential_std=0.01, spectral_std=0.01)
    kf.observe("potential", 2.1475, token=("potential", 2.1475))
    stale = kf.observe("spectral", 1.1805, token=("spectral", 1.1805))
    assert stale["accepted"] is False
    assert stale["reason"] == "nis_gate"
    assert kf.can_fuse is False
    kf.reset()
    kf.observe("potential", 2.1475, token=("potential", 2.1475))
    revised = kf.observe("spectral", 2.1489, token=("spectral", 2.1489))
    assert revised["accepted"] is True
    assert revised["consistent"] is True
    assert kf.can_fuse is True


def test_legacy_cross_entropy_mode_confirms_an_endpoint() -> None:
    """cross_entropy(p, p) is the entropy of p, so the raw value never exits."""
    identical = np.array([1.0, 2.0, 3.0, 4.0])
    assert cross_entropy(identical, identical) > 1.0
    assert cross_entropy_excess(identical, identical) == 0.0
    assert cross_entropy_excess(identical, np.array([4.0, 3.0, 2.0, 1.0])) > 0.0

    candidates = {}
    for use_jsd in (True, False):
        detector = EndpointDetector(flow_rate=0.0061, use_jsd=use_jsd)
        for index in range(1, 300):
            volume = index * 0.01
            voltage = 1.0 - 0.8 * np.exp(-((volume - 1.0) ** 2) / (2.0 * 0.035**2))
            detector.feed_potential(volume, volume / 0.0061, voltage)
            amplitude = 1.0 + 60.0 * np.exp(-((volume - 1.0) ** 2) / (2.0 * 0.03**2))
            detector.feed_spectrum(volume, np.array([amplitude, 1.0, 1.0, 1.0]))
        assert detector.spectral_state == "END_CONFIRMED"
        candidates[use_jsd] = detector.diagnostics()["spectral_features"]["candidate_volume"]
    assert candidates[False] == candidates[True]


def _ampd_reference(signal: np.ndarray) -> int | None:
    """Dense O(N^2) AMPD, kept as the oracle for the reduced implementation."""
    sig = np.asarray(signal, dtype=np.float64)
    N = sig.size
    if N < 12:
        return None
    L = N // 2 - 1
    if L < 2:
        return None
    lms = np.zeros((L, N), dtype=np.int64)
    for k in range(1, L + 1):
        for i in range(k, N - k):
            if sig[i] > sig[i - k] and sig[i] > sig[i + k]:
                lms[k - 1, i] = 1
    sigma = int(np.argmin(lms.sum(axis=1)))
    score = lms[sigma:].sum(axis=0)
    best = int(np.argmax(score))
    return best if score[best] > 0 else None


def test_ampd_reduction_matches_the_dense_reference() -> None:
    rng = np.random.default_rng(20260821)
    cases = [
        np.zeros(40),
        np.ones(40),
        np.arange(40, dtype=np.float64),
        np.arange(40, 0, -1, dtype=np.float64),
        np.array([1.0, 2.0, 1.0]),
        np.linspace(0.0, 1.0, 12),
    ]
    for length in (13, 25, 64, 137):
        cases.append(rng.normal(size=length))
        peak = np.exp(
            -((np.arange(length) - 0.6 * length) ** 2) / (2.0 * (length / 12.0) ** 2)
        )
        cases.append(peak + 0.05 * rng.normal(size=length))
    for case in cases:
        assert _ampd_peak_idx(case) == _ampd_reference(case)
