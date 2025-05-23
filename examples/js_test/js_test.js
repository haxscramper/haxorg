
// @ts-check
/// <reference path="../../src/wrappers/js/haxorg_wasm_types.d.ts" />

function dump_properties(obj) {
  Object.getOwnPropertyNames(obj).forEach(
      prop => { console.log(`${prop}: ${typeof obj[prop]}`, obj[prop]); });
}

const haxorg_wasm = require("../../build/haxorg_debug_emscripten/haxorg_wasm");
const fs          = require("fs");

//
/**
 * @typedef {import("../../src/wrappers/js/haxorg_wasm_types.d.ts").haxorg_wasm_module}
 * HaxorgModule
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
      console.log("?");
      const doc = org.cast_to_Document(node);
      console.log("???");
      console.log(doc.title.has_value());
      console.log(typeof doc.title.value());
      // dump_properties(doc.title.value());

      console.log(org.format_OrgSemKind(doc.title.value().getKind()));

      const recursive_dir  = "/home/haxscramper/tmp/org_test_dir";
      var   directory_opts = new org.OrgDirectoryParseParameters();
      const recursive_node
          = org.parseDirectoryOpts(recursive_dir, directory_opts);
      console.log("Recursive node done");
    });
