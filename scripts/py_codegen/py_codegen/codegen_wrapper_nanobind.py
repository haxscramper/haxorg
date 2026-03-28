from beartype import beartype
import py_codegen.astbuilder_cpp as cpp
from pathlib import Path
from py_codegen.astbuilder_nanobind import NbModule
from py_codegen.astbuilder_nanobind_config import NanobindAstbuilderConfig
from py_codegen.codegen_algo import collect_type_specializations
from py_codegen.codegen_ir import GenTu, GenTuInclude, GenFiles, GenTuPass, GenUnit, get_type_map
from py_codegen import codegen_cpp, refl_read
from py_codegen import astbuilder_py as pya
from py_codegen.codegen_type_groups import PyhaxorgTypeGroups, verify_type_usage
from py_scriptutils.script_logging import ExceptionContextNote, log

CAT = __name__

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


@beartype
def gen_adaptagrams_wrappers(
    ast: cpp.ASTBuilder,
    pyast: pya.ASTBuilder,
    reflection_path: Path,
) -> GenFiles:
    "Generate wrappers for adaptagrams library"
    tu: refl_read.ConvTu = refl_read.conv_proto_file(reflection_path)

    reflection_debug = Path("/tmp/haxorg/adaptagrams_reflection.json")
    reflection_debug.write_text(refl_read.open_proto_file(reflection_path).to_json(2))
    log(CAT).debug(f"Debug reflection data to '{reflection_debug}'")

    with ExceptionContextNote(f"reflection_debug:{reflection_debug}"):
        type_map = get_type_map(tu.enums + tu.structs + tu.typedefs)  # type: ignore
        conf = NanobindAstbuilderConfig(type_map)
        res = NbModule("py_adaptagrams", conf)
        res.add_all(tu.get_all(), ast=ast)
        specializations = collect_type_specializations(tu.get_all(), conf)
        res.add_type_specializations(
            ast=ast,
            specializations=specializations,
        )

        return GenFiles([
            GenUnit(header=GenTu(
                "{root}/scripts/py_wrappers/py_wrappers/py_adaptagrams.pyi",
                [GenTuPass(res.build_typedef(pyast))],
                clangFormatGuard=False,
            )),
            GenUnit(header=GenTu(
                "{root}/src/py_libs/py_adaptagrams/adaptagrams_py_wrap.cpp",
                [
                    GenTuPass("#undef slots"),
                    GenTuInclude("adaptagrams/adaptagrams_ir.hpp", True),
                    GenTuInclude("py_libs/nanobind_utils.hpp", True),
                    *NB_INCLUDE_LIST,
                    GenTuPass(res.build_bind(ast)),
                ],
            )),
        ])


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
def gen_pyhaxorg_python_wrappers(
    groups: PyhaxorgTypeGroups,
    ast: cpp.ASTBuilder,
    pyast: pya.ASTBuilder,
) -> GenFiles:
    "Generate haxorg python wrappers"
    conf = HaxorgNanobindWrapperConfig(groups.type_map)
    res = NbModule("pyhaxorg", conf)

    for decl in groups.get_entries_for_wrapping():
        if decl.ReflectionParams.isAcceptedBackend("python"):
            res.add_decl(decl, ast=ast)

    specializations = collect_type_specializations(
        groups.get_entries_for_wrapping(),
        conf,
    )

    verify_type_usage(groups.get_entries_for_wrapping(), conf, specializations)

    res.add_type_specializations(ast, specializations=specializations)

    res.Decls.append(ast.Include("pyhaxorg_manual_wrap.hpp"))

    return GenFiles([
        GenUnit(header=GenTu(
            "{root}/scripts/py_haxorg/py_haxorg/pyhaxorg.pyi",
            [GenTuPass(res.build_typedef(pyast))],
            clangFormatGuard=False,
        )),
        GenUnit(header=GenTu(
            "{root}/src/py_libs/pyhaxorg/pyhaxorg.cpp",
            [
                GenTuPass("#undef slots"),
                *NB_INCLUDE_LIST,
                GenTuInclude("haxorg/imm/ImmOrgAdapter.hpp", True),
                GenTuInclude("haxorg/sem/SemOrg.hpp", True),
                GenTuInclude("pyhaxorg_manual_impl.hpp", False),
                GenTuPass(res.build_bind(ast)),
            ],
        )),
    ])
