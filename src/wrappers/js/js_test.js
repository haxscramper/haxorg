// Don't do this:
// const wasmBuffer = fs.readFileSync(wasmBinaryPath);
// WebAssembly.instantiate(wasmBuffer, importObject);

const haxorg_wasm = require("../../../build/haxorg_debug_emscripten/haxorg_wasm");

haxorg_wasm().then(org => {
  console.log('WebAssembly loaded!');
  // Access your functions (if bound by Embind):
  console.log(org.parseString("* test"));
});
