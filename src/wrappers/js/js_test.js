const addon = require('../../../build/haxorg_debug_qt/nodehaxorg.node');
const params = new addon.OrgParseParametersJs();
// console.log("Parsing file");
const node = addon.parseFile("/home/haxscramper/workspace/haxorg/tests/org/corpus/org/all.org", params);
// console.log("??");
console.log(node.getKind().toString())
console.log(node.at(0).getKind().toString())
console.log(node.size())
