//! TController Tauri 应用入口：命令层只负责边界，设备状态由 backend runtime 持有。

#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

mod backend;

use std::sync::{Arc, Mutex};

use backend::{
    apply_calibration, backend_info as info, connect as connect_runtime,
    disconnect as disconnect_runtime, emit_snapshot, set_detection as set_detection_runtime,
    set_ui_settings as set_ui_settings_runtime, set_watchdog as set_watchdog_runtime,
    ApplyCalibrationRequest, BackendInfo, BackendRuntime, BackendSnapshot, DetectionPatch,
    SharedBackend, UiSettingsPatch,
};
use tauri::{AppHandle, Manager, State};

#[tauri::command]
fn backend_info() -> BackendInfo {
    info()
}

#[tauri::command]
fn backend_state(state: State<'_, SharedBackend>) -> Result<BackendSnapshot, String> {
    state
        .lock()
        .map(|runtime| runtime.snapshot())
        .map_err(|_| "backend state poisoned".into())
}

#[tauri::command]
fn list_ports() -> Vec<controller_core::protocol::PortInfo> {
    controller_core::protocol::list_ports()
}

#[tauri::command]
fn connect(
    app: AppHandle,
    state: State<'_, SharedBackend>,
    port: String,
    baud: u32,
) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        connect_runtime(&mut runtime, port, baud);
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn disconnect(app: AppHandle, state: State<'_, SharedBackend>) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        disconnect_runtime(&mut runtime);
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn set_sample_input(
    app: AppHandle,
    state: State<'_, SharedBackend>,
    value: f64,
) -> Result<(), String> {
    if !value.is_finite() || value <= 0.0 {
        return Err("样品体积必须为正数".into());
    }
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.set_sample_input(value);
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn set_tubing_pumps(
    app: AppHandle,
    state: State<'_, SharedBackend>,
    p1: bool,
    p2: bool,
) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.set_tubing_pumps(p1, p2)?;
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn start_titration(app: AppHandle, state: State<'_, SharedBackend>) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.start()?;
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn manual_stop(app: AppHandle, state: State<'_, SharedBackend>) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.manual_stop();
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn abort(app: AppHandle, state: State<'_, SharedBackend>) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.abort();
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn reset(app: AppHandle, state: State<'_, SharedBackend>) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.reset();
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn start_tubing(app: AppHandle, state: State<'_, SharedBackend>, op: String) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.start_tubing(&op)?;
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn stop_tubing(app: AppHandle, state: State<'_, SharedBackend>) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.stop_tubing();
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn free_run(app: AppHandle, state: State<'_, SharedBackend>, pump: u8) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.free_run(pump)?;
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn free_stop(app: AppHandle, state: State<'_, SharedBackend>, pump: u8) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.free_stop(pump)?;
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn jog(
    app: AppHandle,
    state: State<'_, SharedBackend>,
    pump: u8,
    steps: u32,
) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        runtime.jog(pump, steps)?;
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn set_watchdog(
    app: AppHandle,
    state: State<'_, SharedBackend>,
    enabled: bool,
) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        set_watchdog_runtime(&mut runtime, enabled);
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn set_detection(
    app: AppHandle,
    state: State<'_, SharedBackend>,
    patch: DetectionPatch,
) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        set_detection_runtime(&mut runtime, patch);
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn set_ui_settings(
    app: AppHandle,
    state: State<'_, SharedBackend>,
    patch: UiSettingsPatch,
) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        set_ui_settings_runtime(&mut runtime, patch);
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

#[tauri::command]
fn apply_pump_calibration(
    app: AppHandle,
    state: State<'_, SharedBackend>,
    request: ApplyCalibrationRequest,
) -> Result<(), String> {
    {
        let mut runtime = state.lock().map_err(|_| "backend state poisoned")?;
        apply_calibration(&mut runtime, request)?;
    }
    emit_snapshot(&app, state.inner());
    Ok(())
}

fn main() {
    let runtime = Arc::new(Mutex::new(BackendRuntime::new()));
    tauri::Builder::default()
        .manage(runtime)
        .setup(|app| {
            let state = app.state::<SharedBackend>();
            backend::run_event_loop(app.handle().clone(), Arc::clone(state.inner()));
            Ok(())
        })
        .invoke_handler(tauri::generate_handler![
            backend_info,
            backend_state,
            list_ports,
            connect,
            disconnect,
            set_sample_input,
            set_tubing_pumps,
            start_titration,
            manual_stop,
            abort,
            reset,
            start_tubing,
            stop_tubing,
            free_run,
            free_stop,
            jog,
            set_watchdog,
            set_detection,
            set_ui_settings,
            apply_pump_calibration,
        ])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
