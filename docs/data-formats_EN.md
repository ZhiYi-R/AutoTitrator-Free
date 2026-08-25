# Calibration and Data Formats

[中文](data-formats.md) | English

This document describes the internal structure of `calibre.npz` and the calibration sidecar, for people who need to read, generate, or migrate these data files. The implementation lives in `crates/controller-core/src/processing/`.

## 1. calibre.npz

`calibre.npz` is a NumPy-format archive that holds both the spectral reconstruction data and the pump calibration data. At startup the host looks for it in a fixed order: the `AUTOTITRATOR_CALIBRE` environment variable, then the executable's directory, then, in development, `TController/data/calibre.npz` (anchored at compile time). If it is not found, the host degrades: the spectrum is not reconstructed and the pumps use default parameters.

### Spectral reconstruction keys

| Key | Type | Notes |
|-----|------|-------|
| `spectral_matrix` | (721, 10) float | Golden Device reconstruction matrix |
| `spectral_wavelengths` | (721,) int32 | Wavelength axis, 380–1100nm, 1nm steps |
| `spectral_offsets` | (10,) float | Per-channel dark offset |
| `spectral_factors` | (10,) float | Per-channel gain factor |

Reconstruction (`Reconstructor::reconstruct`):

$$
\text{corrected}[ch] = \text{factors}[ch] \times \max\left(\text{raw}[ch] - \text{offsets}[ch],\, 0\right)
$$

$$
\text{spectrum}[\lambda] = \max\left(\sum_{ch}\, \text{matrix}[\lambda, ch] \times \text{corrected}[ch],\, 0\right)
$$

That is, per channel, subtract the offset, multiply by the factor, clamp to non-negative, then multiply by the matrix to get the 721-point spectrum. The input must have exactly 10 channels; negative or non-finite values raise an error.

### Pump calibration keys

| Key | Notes |
|-----|-------|
| `pump1_slope` / `pump1_intercept` | Pump 1 linear model slope (mL/step) and intercept (mL) |
| `pump2_slope` / `pump2_intercept` | Pump 2, same |
| `pump1_pulses` / `pump1_volumes` | Pump 1 calibration points (steps ↔ measured volume) |
| `pump2_pulses` / `pump2_volumes` | Pump 2 calibration points |
| `pump1_r2` / `pump2_r2` | Fit R², either a scalar or a single-element array |

Loading rules:

- The slope must be positive, otherwise the default is used.
- The intercept may be negative, but its absolute value must not exceed 10 mL.
- Missing or unreadable keys silently fall back to defaults; no error is reported.

Defaults (`DEFAULT_PUMP_SLOPE = 6.03752e-6`, intercept 0) correspond to a pump step rate of 1000Hz, a flow rate of about 6.04e-3 mL/s.

Volume and steps convert as follows (`PumpCalibration`):

$$
\text{volume} = \text{slope} \times \text{steps} + \text{intercept}
$$

$$
\text{steps} = \left\lfloor \frac{\text{volume} - \text{intercept}}{\text{slope}} \right\rfloor \quad (\text{lower bound 0})
$$

## 2. Calibration sidecar

After the user applies a pump calibration in the interface, the host writes the result to `pump2_calibration.json` next to `settings.json`:

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

- `points`: the calibration points from the interface; `steps` is the accumulated step count, `vol` the measured volume (mL).
- `slopeMlPerStep`: fitted slope, in mL/step.
- `interceptMl`: intercept, in mL.
- `r2`: goodness of fit, optional.

At startup, if this file exists and `slopeMlPerStep > 0`, the host uses it to override the pump 2 parameters from `calibre.npz` and loads the points and R² into the interface.

## 3. settings.json

`settings.json` stores interface preferences and run history, created automatically:

- `lang`, `theme`, `navCollapsed`: interface preferences.
- `detection`: detection parameters (T=1 derivative threshold, dose per step, over-titration margin, consensus tolerance).
- `history`: the most recent 30 runs.
- `port`, `baud`: the serial port and baud rate from the last connection.
- `sampleInput`, `tubingP1`, `tubingP2`: sample volume and tubing pump selection.

This file can be deleted to reset to defaults. It is ignored by `.gitignore` and does not enter the repository.

## 4. Generation and migration

To regenerate `calibre.npz`, write the keys above with Python (`numpy` / `scipy`). To migrate to a new machine, put `calibre.npz` next to the executable, or point `AUTOTITRATOR_CALIBRE` at it. Calibration data follows along: the pump calibration inside `calibre.npz` is the factory default, while a calibration applied in the interface lives separately in `pump2_calibration.json`.