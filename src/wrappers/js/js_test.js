const module = require(
    "/home/haxscramper/workspace/haxorg/build/haxorg_debug_emscripten/haxorg_wasm.js");

module.onRuntimeInitialized = () => {
  try {
    const sum = module.globalAdd(2, 3);
    console.log("Result:", sum);
  } catch (e) {
    console.error("Error:", e);
  }
};
