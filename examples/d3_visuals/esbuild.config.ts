// esbuild.config.ts
import * as esbuild from 'esbuild';

await esbuild.build({
  entryPoints: ['main.ts', 'renderer/index.ts'],
  bundle: true,
  outdir: 'dist',
  platform: 'node',
  target: 'node16',
  format: 'cjs',
  external: ['electron']
});
