import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
import hstd_py_codegen.lang_build.astbuilder_py as pya
import yaml
from beartype import beartype
from hstd_py_codegen.gen_cpp.codegen_write import gen_description_files
from hstd_py_lib.pydantic_utils import to_json_safe
from hstd_py_text_layout.base.wrap import TextLayout
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
def get_codegen_groups(
    builder: cpp.ASTBuilder,
    reflection_path: Path,
    manual_tu_path: Path,
) -> PyhaxorgTypeGroups:
    groups: PyhaxorgTypeGroups = get_pyhaxorg_type_groups(
        ast=builder,
        reflection_path=Path(reflection_path),
        manual_tu_path=manual_tu_path,
    )

    groups_dump_yaml = Path("/tmp/pyhaxorg_groups.yaml")
    with groups_dump_yaml.open("w") as file:
        yaml.safe_dump(to_json_safe(groups.conv_tu), stream=file)
        logger.info(f"Wrote debug for type groups to {groups_dump_yaml}")

    groups_dump_yaml = Path("/tmp/pyhaxorg_manual_groups.yaml")
    with groups_dump_yaml.open("w") as file:
        yaml.safe_dump(to_json_safe(groups.manual_tu), stream=file)
        logger.info(f"Wrote debug for manual type groups to {groups_dump_yaml}")

    return groups


@beartype
def gen_haxorg_cpp_library_source(
    groups: PyhaxorgTypeGroups,
    monorepo_root: Path,
    builder: cpp.ASTBuilder,
) -> GenFiles:
    return gen_haxorg_source(
        ast=builder,
        groups=groups,
        root=monorepo_root / "haxorg_cpp_org_lib",
    )


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
        )
    )

    wrapper_file_groups.append(
        gen_pyhaxorg_napi_wrappers(
            to_wrap=to_wrap,
            type_map=type_map,
            root=monorepo_root / "haxorg_wasm_lib_wrap",
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
def run_codegen_pyhaxorg(
    monorepo_root: Path,
    builder: cpp.ASTBuilder,
    pyast: pya.ASTBuilder,
    reflection_path: Path,
    t: TextLayout,
    manual_tu_path: Path,
) -> None:
    """
    Generate sources for the haxorg library
    :param is_tmp_codegen: If set, put newly genrated sources in the
      temporary directory instead of overwriting existing ones. Useful
      for development.
    :param reflection_path: Input protobuf file with reflection information.
    """

    groups = get_codegen_groups(builder, reflection_path, manual_tu_path=manual_tu_path)

    sources = gen_haxorg_cpp_library_source(groups, monorepo_root, builder)

    gen_description_files(sources, builder, t)

    wrappers = gen_haxorg_cpp_library_wrappers(
        to_wrap=groups.get_entries_for_wrapping(),
        monorepo_root=monorepo_root,
        type_map=groups.type_map,
        builder=builder,
        pyast=pyast,
    )

    for wrap in wrappers:
        gen_description_files(wrap, builder, t)
