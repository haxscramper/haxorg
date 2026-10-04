from pathlib import Path

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
import hstd_py_codegen.lang_build.astbuilder_py as pya
from beartype import beartype
from hstd_py_codegen.gen_cpp.codegen_ir import GenTuStruct, QualType
from hstd_py_codegen.read_cpp.refl_read import ConvTu
from hstd_py_lib.os_utils import latest_file
from hstd_py_text_layout.base.wrap import TextLayout
from repo_py_orchestrate.codegen_config import org_codegen_data
from repo_py_orchestrate.codegen_config.codegen import gen_code_from_groups
from repo_py_orchestrate.codegen_config.codegen_type_groups import (
    get_pyhaxorg_type_groups,
)
from repo_py_orchestrate.codegen_config.extract_refl import (
    extract_reflection,
)


def test_org_codegen_data_run():
    org_codegen_data.get_enums()
    org_codegen_data.get_shared_sem_enums()
    org_codegen_data.get_types()


def test_get_type_groups(stable_test_dir: Path):
    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    groups = get_pyhaxorg_type_groups(
        builder,
        ConvTu(),
        manual_tu=ConvTu(
            structs=[
                GenTuStruct(
                    Name=QualType(Name="UserTime", Spaces=[QualType(Name="hstd")]),
                )
            ]
        ),
    )

    gen_code_from_groups(
        groups=groups,
        monorepo_root=stable_test_dir,
        builder=builder,
        pyast=pya.ASTBuilder(t),
        t=t,
    )


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
    groups = get_pyhaxorg_type_groups(
        ast=builder,
        reflection_uv=reflection_uv,
        manual_tu=ConvTu(),
    )

    gen_code_from_groups(
        groups=groups,
        monorepo_root=stable_test_dir,
        builder=builder,
        pyast=pya.ASTBuilder(t),
        t=t,
    )
