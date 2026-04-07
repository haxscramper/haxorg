from beartype import beartype
from py_codegen import astbuilder_cpp as cpp, astbuilder_embind as napi
from py_codegen.astbuilder_embind_config import EmbindAstbuilderConfig
from py_codegen.codegen_algo import collect_type_specializations
from py_codegen.codegen_ir import GenFiles, GenTu, GenTuPass, GenTypeMap, GenUnit
from py_codegen.codegen_type_groups import PyhaxorgTypeGroups


@beartype
def gen_pyhaxorg_napi_wrappers(
    groups: PyhaxorgTypeGroups,
    ast: cpp.ASTBuilder,
    type_map: GenTypeMap,
) -> GenFiles:
    "Generate embind wrappers"

    cpp_builder = cpp.ASTBuilder(ast.b)

    conf = EmbindAstbuilderConfig(type_map)
    res = napi.WasmModule("haxorg_wasm", conf)

    res.add_specializations(
        b=ast,
        specializations=collect_type_specializations(groups.get_entries_for_wrapping(),
                                                     conf),
    )

    for decl in groups.get_entries_for_wrapping():
        if conf.isAcceptedByBackend(decl):
            res.add_decl(decl)

    res.Header.append(napi.WasmBindPass(ast.Include("node_utils.hpp")))
    res.Header.append(napi.WasmBindPass(ast.Include("node_org_include.hpp")))
    res.Header.append(napi.WasmBindPass(ast.Include("haxorg_wasm_manual.hpp")))
    res.Header.append(napi.WasmBindPass(ast.string("using namespace org::bind::js;")))

    res.add_decl(napi.WasmBindPass(ast.string("haxorg_wasm_manual_register();")))

    return GenFiles([
        GenUnit(header=GenTu("{root}/src/wrappers/js/haxorg_wasm.cpp", [
            GenTuPass(res.build_bind(ast=ast, b=cpp_builder)),
        ])),
        GenUnit(header=GenTu("{root}/src/wrappers/js/haxorg_wasm_types.d.ts", [
            GenTuPass(res.build_typedef(ast=ast)),
        ])),
    ])
