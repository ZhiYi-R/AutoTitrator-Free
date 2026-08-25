import type { NextConfig } from "next";

const nextConfig: NextConfig = {
  /* Tauri frontendDist 指向静态导出产物 */
  output: "export",
  images: { unoptimized: true },
};

export default nextConfig;
