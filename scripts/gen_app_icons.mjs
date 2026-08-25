#!/usr/bin/env node
// 从 icons/icon.svg 生成 Tauri 打包所需的图标集。
//
// 为什么需要这个脚本：tauri-bundler 的 Linux 分支只接受 PNG 图标
// （freedesktop/mod.rs 会跳过非 .png 文件），而 AppImage 打包器在找不到
// 任何正方形 PNG 时会直接 panic。所以 bundle.icon 里必须有 PNG，
// 同时 Windows 的 exe 资源与 msi/nsis 安装器仍需要 .ico。
//
// 依赖 sharp。仓库里没有单独的 node_modules，直接复用前端的：
//   cd TController/app/ui-next && npm ci
//   node scripts/gen_app_icons.mjs
//
// 产物已提交进仓库，CI 不会重新生成——换图标时在本地重跑本脚本并提交。

import { createRequire } from "node:module";
import { fileURLToPath } from "node:url";
import path from "node:path";
import fs from "node:fs/promises";

const require = createRequire(import.meta.url);
const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const iconsDir = path.join(repoRoot, "TController", "app", "src-tauri", "icons");
const source = path.join(iconsDir, "icon.svg");

function loadSharp() {
  const candidates = [
    "sharp",
    path.join(repoRoot, "TController", "app", "ui-next", "node_modules", "sharp"),
  ];
  for (const id of candidates) {
    try {
      return require(id);
    } catch {
      /* 继续尝试下一个 */
    }
  }
  throw new Error(
    "找不到 sharp。请先在 TController/app/ui-next 执行 `npm ci`，或全局安装 sharp。",
  );
}

const sharp = loadSharp();

/** 把 SVG 渲染成指定边长的 PNG buffer。 */
const renderPng = (size) =>
  sharp(source, { density: 384 }).resize(size, size, { fit: "contain" }).png({ compressionLevel: 9 }).toBuffer();

/** 把 SVG 渲染成指定边长的原始 RGBA buffer。 */
const renderRaw = (size) =>
  sharp(source, { density: 384 }).resize(size, size, { fit: "contain" }).raw().ensureAlpha().toBuffer();

/**
 * 构造 ICO 里的一个 BMP/DIB 条目。
 * Windows 只在 32bpp 时用 alpha 通道，但 AND 掩码仍按规范写出，
 * 以兼容按老规则解析 ICO 的 NSIS 与 WiX。
 */
function dibEntry(rgba, size) {
  const header = Buffer.alloc(40);
  header.writeUInt32LE(40, 0); // biSize
  header.writeInt32LE(size, 4); // biWidth
  header.writeInt32LE(size * 2, 8); // biHeight：XOR 位图 + AND 掩码
  header.writeUInt16LE(1, 12); // biPlanes
  header.writeUInt16LE(32, 14); // biBitCount
  header.writeUInt32LE(0, 16); // biCompression = BI_RGB

  const xor = Buffer.alloc(size * size * 4);
  const maskStride = ((size + 31) >> 5) * 4; // 1bpp，行按 4 字节对齐
  const mask = Buffer.alloc(maskStride * size);

  for (let y = 0; y < size; y += 1) {
    const srcRow = y * size * 4;
    const dstRow = (size - 1 - y) * size * 4; // DIB 自下而上存储
    const maskRow = (size - 1 - y) * maskStride;
    for (let x = 0; x < size; x += 1) {
      const s = srcRow + x * 4;
      const d = dstRow + x * 4;
      xor[d] = rgba[s + 2]; // B
      xor[d + 1] = rgba[s + 1]; // G
      xor[d + 2] = rgba[s]; // R
      xor[d + 3] = rgba[s + 3]; // A
      if (rgba[s + 3] < 128) mask[maskRow + (x >> 3)] |= 0x80 >> (x & 7);
    }
  }

  header.writeUInt32LE(xor.length + mask.length, 20); // biSizeImage
  return Buffer.concat([header, xor, mask]);
}

/** 打包多尺寸 ICO：小尺寸用 DIB，256 用 PNG（DIB 会让文件多出 1MB）。 */
function buildIco(entries) {
  const dir = Buffer.alloc(6);
  dir.writeUInt16LE(1, 2); // type = icon
  dir.writeUInt16LE(entries.length, 4);

  let offset = 6 + entries.length * 16;
  const table = [];
  for (const { size, data } of entries) {
    const entry = Buffer.alloc(16);
    entry.writeUInt8(size >= 256 ? 0 : size, 0); // 256 记为 0
    entry.writeUInt8(size >= 256 ? 0 : size, 1);
    entry.writeUInt16LE(1, 4); // planes
    entry.writeUInt16LE(32, 6); // bit count
    entry.writeUInt32LE(data.length, 8);
    entry.writeUInt32LE(offset, 12);
    table.push(entry);
    offset += data.length;
  }

  return Buffer.concat([dir, ...table, ...entries.map((e) => e.data)]);
}

// bundle.icon 里引用的 PNG。文件名里的尺寸必须和真实像素一致：
// tauri-bundler 按解码后的宽高决定 hicolor 目录，只用 @2x 后缀判断高密度。
const pngTargets = [
  ["32x32.png", 32],
  ["128x128.png", 128],
  ["128x128@2x.png", 256],
  ["icon.png", 512],
];

const icoSizes = [16, 24, 32, 48, 64];

await fs.mkdir(iconsDir, { recursive: true });

for (const [name, size] of pngTargets) {
  await fs.writeFile(path.join(iconsDir, name), await renderPng(size));
  console.log(`icons/${name}  ${size}x${size}`);
}

const icoEntries = [];
for (const size of icoSizes) {
  icoEntries.push({ size, data: dibEntry(await renderRaw(size), size) });
}
icoEntries.push({ size: 256, data: await renderPng(256) });

const ico = buildIco(icoEntries);
await fs.writeFile(path.join(iconsDir, "icon.ico"), ico);
console.log(`icons/icon.ico  ${icoSizes.join("/")}/256  ${(ico.length / 1024).toFixed(1)} KiB`);
