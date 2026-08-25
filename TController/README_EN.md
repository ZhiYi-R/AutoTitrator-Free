# TController Host Application

[中文](README.md) | English

The desktop application for AutoTitrator, made of three parts:

- `controller-core`: the Rust backend logic. It handles serial communication, endpoint detection, spectral reconstruction, pump calibration, and the workflow state machine. It has no UI.
- `src-tauri`: the Tauri 2 application shell. It wraps controller-core into a desktop app and exposes commands and a state snapshot to the frontend.
- `ui-next`: the Next.js frontend, the instrument workbench UI.

## Layout

```
TController/
├── Cargo.toml                 # workspace
├── crates/controller-core/    # backend logic (pure logic + serial I/O thread)
│   ├── src/protocol/          # serial protocol, parsing and retries
│   │   ├── crc.rs             #   CRC-8 (poly 0x31)
│   │   ├── frames.rs          #   uplink/downlink frame codec (incl. ADC shift semantics)
│   │   ├── parser.rs          #   AA55 byte-wise state machine
│   │   ├── retry.rs           #   ACK/NAK exponential backoff (single pending slot)
│   │   └── handler.rs         #   serial worker thread + Event channel (poll model)
│   ├── src/processing/        # detection, reconstruction, pump calibration
│   │   ├── ewma.rs savgol.rs ampd.rs
│   │   ├── divergence.rs      #   JS / cross-entropy / KL (incl. rounding lower bound 1e-14)
│   │   ├── tracker.rs         #   SpectralFeatureTracker
│   │   ├── kf.rs              #   EndpointFusionKF
│   │   ├── endpoint.rs        #   EndpointDetector
│   │   ├── reconstructor.rs   #   calibre.npz matrix → 380–1100nm full spectrum
│   │   └── calibration.rs     #   pump linear calibration (slope/intercept)
│   ├── src/workflow.rs        # titration workflow and pump control
│   └── tests/                 # behavior contracts and regression tests
└── app/                       # Tauri 2 application
    ├── src-tauri/             #   backend commands and backend://state snapshots
    └── ui-next/               #   Next.js instrument workbench
```

## Behavior contracts

`tests/endpoint_reliability.rs` keeps the behavior contracts established when the algorithms were ported from Python: JS divergence symmetric and bounded, features use only historical samples (causal), repeated-volume frames hold the speed level, a later event must be 1.5x stronger to supersede an earlier candidate, divergences below the rounding lower bound are not normalized, the KF re-fuses when the endpoint pair changes, and AMPD matches the dense reference implementation point for point. Before changing these behaviors, run the tests; they will tell you exactly where things diverge.

`tests/workflow.rs` fixes a real T=1 deadlock regression: when both modalities confirm but disagree too much (conflict), T=1 must fire as long as potential evidence exists; with only spectral evidence, the pump must not be controlled. See the comments at the top of that file.

AMPD refinement returns `None` when the record is too short (the tail peak has no large-scale coverage); that is expected. The savgol edge padding behaves like the reference algorithm's edge half-window.

## Development environment

You need the Rust toolchain and Node.js. The root `requirements-dev.txt` provides the Python dependencies (installed with `uv`) used by `generate_stm32f103.py`, which generates the firmware peripheral headers; the host application itself does not need them.

```bash
# Install frontend dependencies (first time)
cd app/ui-next
npm install

# Run in development (starts the Next.js dev server)
cd ../src-tauri
cargo tauri dev

# Build a release
cargo tauri build   # runs the Next.js static export automatically
```

## Tests

```bash
cargo test --workspace   # backend logic tests
cargo check --workspace  # compile check

cd app/ui-next
npm run build
npm run lint
```

Tests for `savgol`, `ampd`, `endpoint`, and others freeze the behavior of the Python reference implementation as assertions. When you change a numerical algorithm, look at these tests first. `tests/tmp_diff_python.rs` is a one-off differential test that needs a local, repo-external data file (`tmp_diff/dataA_python.json`) to run; it skips automatically when the file is missing.

## Two data sources: mock and real backend

The frontend runs in one of two modes:

- **Tauri environment**: always uses the Rust backend snapshot as the source of truth. The frontend calls Tauri commands via `invoke`, and the backend pushes a `backend://state` snapshot every 50ms.
- **Browser directly on the Next dev server**: with no Tauri bridge, it automatically uses the built-in simulator in `lib/mock/simulator.ts`, which produces event streams with timers and a titration model. When wiring up the real Tauri backend, only the data source is replaced; the store and UI components stay unchanged.

The switch lives in `isTauriRuntime()` in `lib/backend.ts`. The mock simulator ships a few demo scenarios (normal, noisy, modal conflict, pump failure) that appear only in browser debugging; the packaged Tauri interface does not show the scenario picker.

## Backend state model

controller-core does not hold UI state. It pushes events up through an `Event` channel; the Tauri shell `BackendRuntime` consumes them, maintains a `BackendSnapshot`, and broadcasts it as the `backend://state` event. Snapshot fields are all camelCase and match the type definitions in `lib/backend.ts` one to one.

Key design points:

- The serial worker thread owns the port; the main loop only sends and receives. Command ACK/NAK retries and heartbeats all happen inside the `ProtocolHandler` thread.
- The `WorkflowEngine` is pure logic and does not touch I/O. `on_adc` / `on_spectrum` feed data in; `poll` makes a decision every 500ms and hands pump commands to the transport layer.
- State persistence: `settings.json` (interface preferences, detection parameters, history) and `pump2_calibration.json` (sidecar after applying calibration). Both are ignored by `.gitignore`.
- Diagnostics (reliability, KF snapshot, reason codes) ride along with the snapshot; the "Reliability" group in the frontend displays them directly, with fields matching the `EndpointResult` / `Reliability` structures.

## Data files

- `data/calibre.npz`: spectral reconstruction matrix and pump calibration parameters. Must be kept.
- `data/settings.json`: backend runtime settings and history, generated automatically.
- `data/pump2_calibration.json`: sidecar after applying calibration, generated automatically.

`calibre.npz` is discovered in this order: the `AUTOTITRATOR_CALIBRE` environment variable, the executable's directory, then, in development, `TController/data/calibre.npz` (anchored at compile time). Its structure is described in the "Calibration and Data Formats" document.

## Related documents

- Root README: build, flashing, CI, releases.
- Communication Protocol: frame formats, commands, timing.
- Host User Guide: interface instructions for operators.
- Calibration and Data Formats: structure of calibre.npz and the sidecar.