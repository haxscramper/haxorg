from pathlib import Path

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from beartype import beartype
from hstd_py_codegen.gen_cpp.codegen_write import gen_description_files
from hstd_py_codegen.read_cpp.refl_read import ConvTu
from hstd_py_lib.os_utils import latest_file
from hstd_py_text_layout.base.wrap import TextLayout
from repo_py_orchestrate.codegen_config import org_codegen_data
from repo_py_orchestrate.codegen_config.codegen import (
    gen_haxorg_base_sources,
    run_codegen_pyhaxorg_wrappers,
)
from repo_py_orchestrate.codegen_config.extract_refl import (
    extract_reflection,
)


def test_org_codegen_data_run():
    org_codegen_data.get_enums()
    org_codegen_data.get_shared_sem_enums()
    org_codegen_data.get_sem_node_definitions()


def test_gen_base_code(stable_test_dir: Path):
    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    _, sources = gen_haxorg_base_sources(stable_test_dir, t=t)
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
