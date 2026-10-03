import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
import hstd_py_codegen.lang_build.astbuilder_py as pya
import yaml
from hstd_py_codegen.gen_cpp.codegen_write import gen_description_files
from hstd_py_lib.pydantic_utils import to_json_safe
from hstd_py_lib.script_logging import ExceptionContextNote
from hstd_py_text_layout.base.wrap import TextLayout
from repo_py_orchestrate.codegen_config.gen_haxorg.cpp_sources import gen_haxorg_source
from repo_py_orchestrate.src.repo_py_orchestrate.codegen_config.codegen_wrapper_c import (
    gen_haxorg_c_wrappers,
)
from repo_py_orchestrate.src.repo_py_orchestrate.codegen_config.codegen_wrapper_embind import (
    gen_pyhaxorg_napi_wrappers,
)
from repo_py_orchestrate.src.repo_py_orchestrate.codegen_config.codegen_wrapper_nanobind import (
    gen_pyhaxorg_python_wrappers,
)

from repo_py_orchestrate.config import get_tmpdir
from repo_py_orchestrate.src.repo_py_orchestrate.codegen_config.codegen_type_groups import (
    PyhaxorgTypeGroups,
    get_pyhaxorg_type_groups,
)
from repo_py_orchestrate.src.repo_py_orchestrate.codegen_config.org_codegen_data import *


class CodegenOptions(BaseModel):
    reflection_path: str
    codegen_task: Literal["pyhaxorg", "adaptagrams"]
    tmp: bool = False


@beartype
def run_codegen_pyhaxorg(
    monrepo_root: Path,
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
    groups: PyhaxorgTypeGroups = get_pyhaxorg_type_groups(
        ast=builder,
        reflection_path=Path(reflection_path),
        manual_tu_path=manual_tu_path,
    )

    groups_dump_yaml = get_tmpdir().joinpath("pyhaxorg_groups.yaml")
    with groups_dump_yaml.open("w") as file:
        yaml.safe_dump(to_json_safe(groups.conv_tu), stream=file)
        logger.info(f"Wrote debug for type groups to {groups_dump_yaml}")

    groups_dump_yaml = get_tmpdir().joinpath("pyhaxorg_manual_groups.yaml")
    with groups_dump_yaml.open("w") as file:
        yaml.safe_dump(to_json_safe(groups.manual_tu), stream=file)
        logger.info(f"Wrote debug for manual type groups to {groups_dump_yaml}")

    sources = gen_haxorg_source(
        ast=builder,
        groups=groups,
        root=monrepo_root / "haxorg_cpp_org_lib",
    )

    gen_description_files(sources, builder, t)

    _write_files_group(
        gen_haxorg_c_wrappers(
            groups=groups,
            ast=builder,
        ),
        is_tmp_codegen=is_tmp_codegen,
        builder=builder,
        t=t,
    )

    _write_files_group(
        gen_pyhaxorg_napi_wrappers(
            groups=groups,
            ast=builder,
            type_map=groups.type_map,
        ),
        is_tmp_codegen=is_tmp_codegen,
        builder=builder,
        t=t,
    )

    _write_files_group(
        gen_pyhaxorg_python_wrappers(
            groups=groups,
            ast=builder,
            pyast=pyast,
        ),
        is_tmp_codegen=is_tmp_codegen,
        builder=builder,
        t=t,
    )


@beartype
def run_codegen_task(
    reflection_path: Path,
    is_tmp_codegen: bool,
    manual_tu_path: Path,
) -> None:
    t = TextLayout()
    pyast = pya.ASTBuilder(t)
    builder = cpp.ASTBuilder(t)

    with ExceptionContextNote(f"reflection_path:{reflection_path}"):
        run_codegen_pyhaxorg(
            is_tmp_codegen=is_tmp_codegen,
            reflection_path=reflection_path,
            builder=builder,
            pyast=pyast,
            t=t,
            manual_tu_path=manual_tu_path,
        )
