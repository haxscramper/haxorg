from pathlib import Path

from beartype import beartype
from hstd_py_codegen.gen_cpp.codegen_algo import (
    collect_type_specializations,
)
from hstd_py_codegen.gen_cpp.codegen_ir import (
    GenFiles,
    GenTu,
    GenTuPass,
    GenTuUnion,
    GenTypeMap,
    GenUnit,
)
from hstd_py_codegen.lang_build import astbuilder_cpp as cpp
from hstd_py_codegen.lang_build import astbuilder_embind as napi
from hstd_py_codegen.lang_build.astbuilder_embind_config import (
    EmbindAstbuilderConfig,
)


@beartype
def gen_pyhaxorg_napi_wrappers(
    to_wrap: list[GenTuUnion],
    ast: cpp.ASTBuilder,
    type_map: GenTypeMap,
    root: Path,
) -> GenFiles:
    "Generate embind wrappers"

    cpp_builder = cpp.ASTBuilder(ast.b)

    conf = EmbindAstbuilderConfig(type_map)
    res = napi.WasmModule("haxorg_wasm", conf)

    res.add_specializations(
        b=ast,
        specializations=collect_type_specializations(to_wrap, conf),
    )

    for decl in to_wrap:
        if conf.isAcceptedByBackend(decl):
            res.add_decl(decl)

    res.Header.append(napi.WasmBindPass(ast.Include("node_utils.hpp")))
    res.Header.append(napi.WasmBindPass(ast.Include("node_org_include.hpp")))
    res.Header.append(napi.WasmBindPass(ast.Include("haxorg_wasm_manual.hpp")))
    res.Header.append(napi.WasmBindPass(ast.string("using namespace org::bind::js;")))

    res.add_decl(napi.WasmBindPass(ast.string("haxorg_wasm_manual_register();")))

    return GenFiles(
        [
            GenUnit(
                header=GenTu(
                    root / "src/wrappers/js/haxorg_wasm.cpp",
                    [
                        GenTuPass(res.build_bind(ast=ast, b=cpp_builder)),
                    ],
                )
            ),
            GenUnit(
                header=GenTu(
                    root / "src/wrappers/js/haxorg_wasm_types.d.ts",
                    [
                        GenTuPass(res.build_typedef(ast=ast)),
                    ],
                )
            ),
        ]
    )
