// esbuild.config.ts
import * as esbuild from "esbuild";

await esbuild.build({
  entryPoints : [ "main.ts", "renderer/index.ts" ],
  bundle : true,
  outdir : "dist",
  platform : "node",
  target : "node16",
  format : "cjs",
  external : [ "electron",  "../../../build/haxorg_debug_qt/nodehaxorg.node" ],
  sourcemap : true,
});

await esbuild.build({
  entryPoints : [ "app/main.tsx" ],
  bundle : true,
  outdir : "dist/app",
  platform : "browser",
  format : "esm",
  loader : {
    ".tsx" : "tsx",
    ".ts" : "ts",
    ".js" : "js",
  },
  jsx : "automatic",
  sourcemap : true,
  inject: ["./app/preload-stub.ts"],
});
