from pathlib import Path

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from beartype import beartype
from hstd_py_codegen.gen_cpp import codegen_cpp
from hstd_py_codegen.gen_cpp.codegen_algo import (
    collect_type_specializations,
)
from hstd_py_codegen.gen_cpp.codegen_ir import (
    GenTu,
    GenTuInclude,
    GenTuPass,
    GenTuUnion,
    GenTypeMap,
    GenUnit,
)
from hstd_py_codegen.lang_build import astbuilder_py as pya
from hstd_py_codegen.lang_build.astbuilder_nanobind import NbModule
from hstd_py_codegen.lang_build.astbuilder_nanobind_config import (
    NanobindAstbuilderConfig,
)

from repo_py_orchestrate.src.repo_py_orchestrate.codegen_config.codegen_type_groups import (
    verify_type_usage,
)

NB_INCLUDE_LIST = [
    GenTuInclude("nanobind/nanobind.h", True),
    GenTuInclude("nanobind/stl/string.h", True),
    GenTuInclude("nanobind/stl/vector.h", True),
    GenTuInclude("nanobind/stl/map.h", True),
    GenTuInclude("nanobind/stl/array.h", True),
    GenTuInclude("nanobind/stl/filesystem.h", True),
    GenTuInclude("nanobind/stl/function.h", True),
    GenTuInclude("nanobind/stl/map.h", True),
    GenTuInclude("nanobind/stl/optional.h", True),
    GenTuInclude("nanobind/stl/set.h", True),
    GenTuInclude("nanobind/stl/shared_ptr.h", True),
    GenTuInclude("nanobind/stl/string_view.h", True),
    GenTuInclude("nanobind/stl/tuple.h", True),
    GenTuInclude("nanobind/stl/unique_ptr.h", True),
    GenTuInclude("nanobind/stl/unordered_map.h", True),
    GenTuInclude("nanobind/stl/variant.h", True),
    GenTuInclude("nanobind/operators.h", True),
    GenTuInclude("nanobind/make_iterator.h", True),
    GenTuInclude("nanobind/ndarray.h", True),
]


class HaxorgNanobindWrapperConfig(NanobindAstbuilderConfig):
    "Override some nanobind generation options for haxorg-specific types"

    def isRegisteredForBacked(self, Type: codegen_cpp.QualType) -> bool:
        "nodoc"
        match Type.flatQualNameWithParams():
            case ["org", "sem", "SemId", _]:
                return True

            case ["org", "imm", "ImmAdapterTBase", _]:
                return False

            case ["org", "imm", *rest]:
                return True

            case n if n in [
                ["org", "imm", "ImmId", "NodeIdxT"],
                ["org", "bind", "python", "ExporterPython", "PyFunc"],
                ["org", "bind", "python", "ExporterPython", "Res"],
            ]:
                return True

            case _:
                return super().isRegisteredForBacked(Type)


@beartype
def init_pyhaxorg_nanobind_module(
    to_wrap: list[GenTuUnion],
    ast: cpp.ASTBuilder,
    pyast: pya.ASTBuilder,
    type_map: GenTypeMap,
) -> NbModule:
    conf = HaxorgNanobindWrapperConfig(type_map)
    res = NbModule("pyhaxorg", conf)

    for decl in to_wrap:
        if decl.ReflectionParams.isAcceptedBackend("python"):
            res.add_decl(decl, ast=ast)

    specializations = collect_type_specializations(to_wrap, conf)

    verify_type_usage(to_wrap, conf, specializations)

    res.add_type_specializations(ast, specializations=specializations)

    res.Decls.append(ast.Include("pyhaxorg_manual_wrap.hpp"))

    return res


@beartype
def gen_pyhaxorg_cpp_py_wrap_source(
    nb_module: NbModule,
    ast: cpp.ASTBuilder,
    source: Path,
) -> GenUnit:
    return GenUnit(
        header=GenTu(
            source,
            [
                GenTuPass("#undef slots"),
                *NB_INCLUDE_LIST,
                GenTuInclude("haxorg/imm/ImmOrgAdapter.hpp", True),
                GenTuInclude("haxorg/sem/SemOrg.hpp", True),
                GenTuInclude("pyhaxorg_manual_impl.hpp", False),
                GenTuPass(nb_module.build_bind(ast)),
            ],
        )
    )


@beartype
def gen_pyhaxorg_python_type_stub(
    nb_module: NbModule,
    pyast: pya.ASTBuilder,
    file: Path,
) -> GenUnit:
    "Generate haxorg python wrappers"

    return GenUnit(
        header=GenTu(
            file,
            [GenTuPass(nb_module.build_typedef(pyast))],
            clangFormatGuard=False,
        )
    )
