
// @ts-check
/// <reference path="../../src/wrappers/js/haxorg_wasm_types.d.ts" />

function dump_properties(obj) {
  Object.getOwnPropertyNames(obj).forEach(
      prop => { console.log(`${prop}: ${typeof obj[prop]}`, obj[prop]); });
}

const haxorg_wasm = require("./haxorg_wasm/haxorg_wasm");
const fs          = require("fs");
const path        = require("path");
//
/**
 * @typedef {import("../../src/wrappers/js/haxorg_wasm_types.d.ts").haxorg_wasm_module}
 * HaxorgModule
 */

function read_file_content(path) {
  console.log(`Reading ${path}`);
  return fs.readFileSync(path);
}

function is_directory_impl(path) {
  // console.log(`Checking if '${path}' is directory`);
  return fs.lstatSync(path).isDirectory()
}

function is_regular_file(path) {
  // console.log(`Checking if '${path}' is directory`);
  return fs.lstatSync(path).isFile();
}

function is_symlink(path) {
  // console.log(`Checking if '${path}' is symlink`);
  return fs.lstatSync(path).isSymbolicLink();
}

function get_entry_list(input) {
  const files = fs.readdirSync(input);
  return files.map(file => `${input}/${file}`);
}

function resolve_symllink(input) {
  const resolved = fs.realpathSync(input);
  return path.resolve(resolved);
}

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

      const recursive_dir  = path.resolve("../../tests/org/corpus");
      var   directory_opts = new org.OrgDirectoryParseParameters();
      org.setOrgDirectoryIsDirectoryCallback(directory_opts, is_directory_impl);
      org.setOrgDirectoryIsRegularFileCallback(directory_opts, is_regular_file);
      org.setOrgDirectoryIsSymlinkCallback(directory_opts, is_symlink);
      org.setOrgDirectoryFileReaderCallback(directory_opts, read_file_content);
      org.setOrgDirectoryGetDirectoryEntriesCallback(directory_opts,
                                                     get_entry_list);
      org.setOrgDirectoryResolveSymlinkCallback(directory_opts,
                                                resolve_symllink);
      const recursive_node
          = org.parseDirectoryOpts(recursive_dir, directory_opts);
      console.log("Recursive node done");

      var original_context = org.initImmutableAstContext();
      var original_state   = original_context.addRoot(recursive_node.value());
      var graph_state = org.GraphMapGraphState.FromAstContext(original_context);

      const msgpack_context_path = "/tmp/dir1_msgpack.bin";
      const msgpack_graph_path   = "/tmp/dir1_graph_msgpack.bin";
      const msgpack_epoch_path   = "/tmp/dir1_msgpack_epoch.bin";

      {
        console.log("Serialize initial context");
        const binary = org.serializeAstContextToTextUint8(original_context);
        fs.writeFileSync(msgpack_context_path, Buffer.from(binary));
      }

      {
        console.log("Serialize mind map");
        const binary = org.serializeMapGraphToTextUint8(graph_state.getGraph());
        fs.writeFileSync(msgpack_graph_path, Buffer.from(binary));
      }

      {
        console.log("Serialize current epoch");
        const binary
            = org.serializeAstEpochToTextUint8(original_state.getEpoch());
        fs.writeFileSync(msgpack_epoch_path, Buffer.from(binary));
      }

      var deserialized_context = org.initImmutableAstContext();
      var deserialized_version = deserialized_context.getEmptyVersion();
      var deserialized_graph
          = org.GraphMapGraphState.FromAstContext(original_context);

      {
        console.log("Deserialize context");
        const binary = fs.readFileSync(msgpack_context_path);
        org.serializeAstContextFromTextUint8(new Uint8Array(binary),
                                             deserialized_context);
      }

      {
        console.log("Deserialize epoch");
        const binary = fs.readFileSync(msgpack_epoch_path);
        org.serializeAstEpochFromTextUint8(new Uint8Array(binary),
                                           deserialized_version.getEpoch());
      }

      {
        console.log("Deserialize graph");
        const binary = fs.readFileSync(msgpack_graph_path);
        org.serializeMapGraphFromTextUint8(new Uint8Array(binary),
                                           deserialized_graph.getGraph());
      }
    });
