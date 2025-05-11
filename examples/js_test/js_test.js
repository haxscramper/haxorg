
// @ts-check
/// <reference path="../../src/wrappers/js/haxorg_wasm_types.d.ts" />

function dump_properties(obj) {
  Object.getOwnPropertyNames(obj).forEach(
      prop => { console.log(`${prop}: ${typeof obj[prop]}`, obj[prop]); });
}

const haxorg_wasm = require("../../build/haxorg_debug_emscripten/haxorg_wasm");

// Or alternatively, if you're using JSDoc:
/**
 * @typedef {import("../../src/wrappers/js/haxorg_wasm_types.d.ts").haxorg_wasm_module} HaxorgModule
 */


haxorg_wasm().then(
    /** @param {HaxorgModule} org */ org => {
      console.log("WebAssembly loaded!");
      // Access your functions (if bound by Embind):
      const node = org.parseString("#+title: title\n* test");
      console.log(node);
      console.log(node.getKind() == org.OrgSemKind.Document);
      const node2 = node.at(0);
      console.log(org.format_OrgSemKind(node.getKind()));
      const doc = org.cast_to_Document(node);
      console.log(doc.title.has_value());
      console.log(typeof doc.title.value());
      // dump_properties(doc.title.value());
      
      console.log(org.format_OrgSemKind(doc.title.value().getKind()));
    });
