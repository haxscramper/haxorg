import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
import hstd_py_codegen.lang_build.astbuilder_py as pya
import yaml
from beartype import beartype
from hstd_py_codegen.gen_cpp.codegen_type_order import topological_sort_entries
from hstd_py_codegen.read_cpp import refl_read
from hstd_py_lib.script_logging import to_debug_json
from hstd_py_text_layout.base.wrap import TextLayout
from loguru import logger
from repo_py_orchestrate.codegen_config.codegen_type_groups import (
    PyhaxorgTypeGroups,
    get_pyhaxorg_type_groups,
)
from repo_py_orchestrate.codegen_config.gen_haxorg.cpp_sources import gen_haxorg_source
from repo_py_orchestrate.codegen_config.gen_wrappers.c_wrap import (
    gen_haxorg_c_wrappers,
)
from repo_py_orchestrate.codegen_config.gen_wrappers.py_wrap import (
    gen_pyhaxorg_cpp_py_wrap_source,
    gen_pyhaxorg_python_type_stub,
    init_pyhaxorg_nanobind_module,
)
from repo_py_orchestrate.codegen_config.gen_wrappers.wasm_wrap import (
    gen_pyhaxorg_napi_wrappers,
)
from repo_py_orchestrate.codegen_config.org_codegen_data import *


class CodegenOptions(BaseModel):
    reflection_path: str
    codegen_task: Literal["pyhaxorg", "adaptagrams"]
    tmp: bool = False


@beartype
def gen_haxorg_cpp_library_wrappers(
    to_wrap: list[GenTuUnion],
    monorepo_root: Path,
    builder: cpp.ASTBuilder,
    pyast: pya.ASTBuilder,
    type_map: GenTypeMap,
) -> list[GenFiles]:

    wrapper_file_groups: list[GenFiles] = list()

    wrapper_file_groups.append(
        gen_haxorg_c_wrappers(
            to_wrap=to_wrap,
            type_map=type_map,
            root=monorepo_root / "haxorg_cpp_c_wrap",
            ast=builder,
        )
    )

    wrapper_file_groups.append(
        gen_pyhaxorg_napi_wrappers(
            to_wrap=to_wrap,
            type_map=type_map,
            root=monorepo_root / "haxorg_wasm_lib_wrap",
            ast=builder,
        )
    )

    nb_module = init_pyhaxorg_nanobind_module(to_wrap, builder, pyast, type_map)
    wrapper_file_groups.append(
        GenFiles(
            [
                gen_pyhaxorg_python_type_stub(
                    nb_module,
                    pyast,
                    monorepo_root / "haxorg_py_lib/src/haxorg_py_lib/pyhaxorg.pyi",
                ),
                gen_pyhaxorg_cpp_py_wrap_source(
                    nb_module,
                    builder,
                    monorepo_root
                    / "haxorg_cpp_py_wrap/src/haxorg_cpp_py_wrap/pyhaxorg.cpp",
                ),
            ]
        )
    )

    return wrapper_file_groups


@beartype
def gen_haxorg_base_sources(
    monorepo_root: Path,
    t: TextLayout,
    context_tu: refl_read.ConvTu = refl_read.ConvTu(),
    with_context: bool = True,
) -> tuple[list[GenTuUnion], GenFiles]:
    builder = cpp.ASTBuilder(t)
    groups: PyhaxorgTypeGroups = get_pyhaxorg_type_groups(ast=builder)
    groups.context_tu = context_tu
    type_map = GenTypeMap.FromTypes(groups.get_all())

    sources = gen_haxorg_source(
        ast=builder,
        groups=groups,
        root=monorepo_root / "haxorg_cpp_org_lib",
        type_map=type_map,
    )

    return groups.get_all(with_context=with_context), sources


@beartype
def run_codegen_pyhaxorg_wrappers(
    preset_type: Sequence[GenTuUnion],
    monorepo_root: Path,
    reflection_tu: refl_read.ConvTu,
    manual_tu: refl_read.ConvTu,
    t: TextLayout,
) -> list[GenFiles]:

    builder = cpp.ASTBuilder(t)
    pyast = pya.ASTBuilder(t)

    groups_dump_yaml = Path("/tmp/pyhaxorg_groups.yaml")
    with groups_dump_yaml.open("w") as file:
        yaml.safe_dump(to_debug_json(reflection_tu), stream=file)
        logger.info(f"Wrote debug for type groups to {groups_dump_yaml}")

    groups_dump_yaml = Path("/tmp/pyhaxorg_manual_groups.yaml")
    with groups_dump_yaml.open("w") as file:
        yaml.safe_dump(to_debug_json(manual_tu), stream=file)
        logger.info(f"Wrote debug for manual type groups to {groups_dump_yaml}")

    to_wrap = topological_sort_entries(
        list(
            itertools.chain(
                preset_type,
                reflection_tu.enums,
                reflection_tu.structs,
                reflection_tu.typedefs,
                manual_tu.enums,
                manual_tu.structs,
                manual_tu.typedefs,
                reflection_tu.functions,
                manual_tu.functions,
            )
        )
    )

    type_map = GenTypeMap.FromTypes(to_wrap)

    return gen_haxorg_cpp_library_wrappers(
        to_wrap=to_wrap,
        monorepo_root=monorepo_root,
        type_map=type_map,
        builder=builder,
        pyast=pyast,
    )
