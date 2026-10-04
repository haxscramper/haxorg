from pathlib import Path

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
import hstd_py_codegen.lang_build.astbuilder_py as pya
from hstd_py_codegen.gen_cpp.codegen_ir import GenTuStruct, QualType
from hstd_py_codegen.read_cpp.refl_read import ConvTu
from hstd_py_text_layout.base.wrap import TextLayout
from repo_py_orchestrate.codegen_config import org_codegen_data
from repo_py_orchestrate.codegen_config.codegen import gen_code_from_groups
from repo_py_orchestrate.codegen_config.codegen_type_groups import (
    get_pyhaxorg_type_groups,
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
