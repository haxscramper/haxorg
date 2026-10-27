from pathlib import Path

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from beartype import beartype
from deepdiff import DeepDiff
from hstd_py_codegen.gen_cpp.codegen_write import gen_description_files
from hstd_py_codegen.read_cpp.refl_read import ConvTu
from hstd_py_lib.os_utils import ensure_clean_dir, latest_file
from hstd_py_lib.pydantic_utils import format_json_with_fjson
from hstd_py_lib.script_logging import to_debug_json
from hstd_py_text_layout.base.wrap import TextLayout
from loguru import logger
from repo_py_orchestrate.codegen_config import org_codegen_data
from repo_py_orchestrate.codegen_config.codegen import (
    gen_haxorg_base_sources,
    gen_haxorg_base_sources1,
    run_codegen_pyhaxorg_wrappers,
)
from repo_py_orchestrate.codegen_config.codegen_type_groups import (
    get_pyhaxorg_type_groups,
)
from repo_py_orchestrate.codegen_config.extract_refl import (
    extract_reflection,
)
from repo_py_orchestrate.codegen_config.type_models.model_to_gentu import (
    get_pyhaxorg_type_groups_via_dsl,
)


def test_org_dsl_codegen_conversion(stable_test_dir: Path):
    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    v2_model = get_pyhaxorg_type_groups_via_dsl(builder)
    v1_model = get_pyhaxorg_type_groups(ast=builder)

    v1_json = to_debug_json(v1_model)
    v2_json = to_debug_json(v2_model)
    diff = DeepDiff(v1_json, v2_json, verbose_level=1)

    stable_test_dir.joinpath("v1_model.json").write_text(format_json_with_fjson(v1_json))
    stable_test_dir.joinpath("v2_model.json").write_text(format_json_with_fjson(v2_json))

    stable_test_dir.joinpath("result.json").write_text(
        format_json_with_fjson(diff.to_dict()),
    )

    for v, value in [("v1", v1_model), ("v2", v2_model)]:
        logger.info(f"Generating sources {v}")
        res_dir = stable_test_dir.joinpath(f"files_{v}")
        ensure_clean_dir(res_dir)
        _, sources = gen_haxorg_base_sources1(
            res_dir,
            builder=builder,
            groups=value,
            t=t,
            context_tu=org_codegen_data.COMMON_CONTEXT_TU,
        )
        gen_description_files(sources, builder, t)


def test_org_codegen_data_run():
    org_codegen_data.get_enums()
    org_codegen_data.get_shared_sem_enums()
    org_codegen_data.get_sem_node_definitions()


def test_gen_base_code(stable_test_dir: Path):
    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    _, sources = gen_haxorg_base_sources(
        stable_test_dir,
        t=t,
        context_tu=org_codegen_data.COMMON_CONTEXT_TU,
    )
    gen_description_files(sources, builder, t)


@beartype
def test_get_type_groups_with_reflection(stable_test_dir: Path) -> None:
    root = Path(__file__).resolve().parents[2]
    reflection_uv = extract_reflection(
        compilation_database=latest_file(
            [
                root
                / "build/conan_build/haxorg_cpp_py_wrap/build/Release/compile_commands.json",
                root
                / "build/conan_build/haxorg_cpp_py_wrap/build/Debug/compile_commands.json",
            ]
        ),
        target_file=root
        / "haxorg_cpp_py_wrap/src/haxorg_cpp_py_wrap/pyhaxorg_manual_impl.cpp",
        output_directory=stable_test_dir / "reflection",
    )

    assert reflection_uv.get_all(), (
        "No annotated declarations were extracted from "
        "haxorg_cpp_py_wrap/src/haxorg_cpp_py_wrap/pyhaxorg_manual_refl.cpp"
    )

    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    base_types, _ = gen_haxorg_base_sources(stable_test_dir, t=t)

    wrappers = run_codegen_pyhaxorg_wrappers(
        base_types,
        stable_test_dir,
        reflection_tu=reflection_uv,
        manual_tu=ConvTu(),
        t=t,
    )

    for wrap in wrappers:
        gen_description_files(wrap, builder, t)
