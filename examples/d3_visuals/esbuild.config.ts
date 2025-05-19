// esbuild.config.ts
import * as esbuild from "esbuild";
import * as fs from "node:fs";
import * as path from "node:path";

await esbuild.build({
  entryPoints : [ "src/preload.ts" ],
  bundle : true,
  outfile : "dist/preload.js",
  platform : "node",
  target : "es2020",
  format : "cjs",
  external : [ "electron" ],
  define : {"process.env.NODE_ENV" : "\"production\""},
});

await esbuild.build({
  entryPoints : [ "src/main/main.ts", "src/main/index.ts" ],
  bundle : true,
  outdir : "dist/main",
  platform : "node",
  target : "node16",
  format : "cjs",
  external : [ "electron" ],
  sourcemap : true,
});

await esbuild.build({
  entryPoints : [ "src/renderer/app.tsx" ],
  bundle : true,
  outdir : "dist/renderer",
  platform : "browser",
  format : "esm",
  loader : {
    ".tsx" : "tsx",
    ".ts" : "ts",
    ".js" : "js",
  },
  jsx : "automatic",
  sourcemap : true,
});

fs.copyFileSync("src/renderer/index.html", "dist/renderer/index.html");
fs.copyFileSync("src/renderer/index.css", "dist/renderer/index.css");
