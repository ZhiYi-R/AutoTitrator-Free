# ui-next Instrument Workbench

[中文](README.md) | English

The frontend of the AutoTitrator host application, built with Next.js. It shows five pages: titration workbench, calibration, maintenance, records, and settings. Data comes from one of two sources:

- Tauri environment: subscribes to the backend `backend://state` snapshot and calls Tauri commands via `invoke`.
- Browser directly: automatically uses the simulator in `lib/mock/simulator.ts`, which ships a few demo scenarios for developing the UI without hardware.

The switch lives in `lib/backend.ts`. The packaged Tauri app always uses the real backend; mock appears only in browser development mode.

## Development

```bash
npm install
npm run dev        # dev server (browser mode, mock enabled automatically)
npm run build      # static export, used by the Tauri build
npm run lint
```

## Layout

```
lib/
├── backend.ts        # Tauri/mock dual data-source bridge
├── store.ts          # Zustand global state
├── i18n.ts           # Chinese/English strings
├── types.ts          # frontend-backend event protocol types
├── chart-utils.ts    # shared Canvas chart utilities
├── tone.ts           # semantic tone mapping
└── mock/
    ├── simulator.ts  # built-in simulator
    └── calibre.ts    # pump calibration mirror
```

## Conventions

- All UI strings go through `i18n.ts`; do not hard-code Chinese or English in components.
- State field names map one to one to the camelCase fields of the backend snapshot. Change `types.ts` first when the protocol changes.
- Page layout is documented in `design.md`; read it before changing the layout.