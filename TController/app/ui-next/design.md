# Design — AutoTitrator Console

A locked design system for this instrument console. Later page work
reads this file before changing chrome. Do not regenerate per page.

## Genre
modern-minimal, instrument register (not SaaS marketing)

## Macrostructure family
- App pages: Workbench — always-visible run chrome, live plots, readout rail
- Marketing / content: none

## Inferred brief
- Audience: lab operator at the bench
- Use: connect, start a run, watch the endpoint
- Tone: utilitarian / technical

## Theme
Existing grayscale instrument palette. Colour is reserved for status.

- `--background`  oklch(0.11 0 0) dark / oklch(0.985 0 0) light
- `--card`        oklch(0.155 0 0) dark / oklch(1 0 0) light
- `--foreground`  oklch(0.97 0 0) dark / oklch(0.145 0 0) light
- `--border`      hairline, low-chroma
- `--status-ok` / `--status-warn` / `--status-danger` only for state
- `--curve-potential` high-contrast solid
- `--curve-derivative` mid-ink, dashed

## Typography
- Display / body: Geist Sans (already loaded)
- Readouts: Geist Mono + tabular nums
- No italic headings
- Instrument labels: 11px, wide tracking, nowrap

## Spacing
4-point scale via Tailwind. Console chrome stays compact:
title 32px + tool strip 36px, status bar 32px, page gap 12px.
Tool strip is left-aligned segmented clusters (link, sample, run);
E-STOP is isolated on the right.

## Motion
- Duration ≤ 150ms, transform/opacity only
- Reduced-motion: opacity only
- No celebratory toasts for routine connect/start

## CTA voice
- Primary: filled ink, start / connect — never transparent; readable before hover
- Cautionary: warn outline + label, reset (clears the run)
- Destructive physical: filled danger, E-STOP
- Secondary: hairline, stop / abort

## What pages MUST share
- Wordmark + flask mark
- Grayscale paper, status-only colour
- Geist + mono readouts
- Run controls in the top bar, live values in the status bar
- Tight-radius panels (`--radius` 6px), not SaaS pills

## What pages MAY differ on
- Interior card arrangement
- Empty-state copy for that page's job
