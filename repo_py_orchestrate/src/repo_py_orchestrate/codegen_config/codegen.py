import os

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
import hstd_py_codegen.lang_build.astbuilder_py as pya
import yaml
from hstd_py_codegen.gen_cpp import codegen_cpp
from hstd_py_lib.script_logging import ExceptionContextNote
from hstd_py_lib.toml_config_profiler import (
    apply_options,
    options_from_model,
)
from hstd_py_text_layout.base.wrap import TextLayout, TextOptions
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


@beartype
def gen_unit(
    define: GenTu,
    builder: cpp.ASTBuilder,
    t: TextLayout,
    tmp: bool,
    isHeader: bool,
    isSplitHeaderSource: bool,
):
    """
    Generate code for source/header of the translation unit component
    """
    out_root = Path("/tmp") if tmp else get_haxorg_repo_root_path()

    path = define.path.format(base=out_root.joinpath("src/haxorg"), root=out_root)

    with ExceptionContextNote(f"Path: {define.path}"):
        result = builder.TranslationUnit(
            [
                codegen_cpp.GenConverter(
                    builder, isHeader=isHeader, isSplitHeaderSource=isSplitHeaderSource
                ).convertTu(define)
            ]
        )

    directory = os.path.dirname(path)
    if not os.path.exists(directory):
        os.makedirs(directory)
        logger.info(f"Created dir for {path}")

    opts = TextOptions()
    opts.rightMargin = 160
    newCode = t.toString(result, opts)

    if os.path.exists(path):
        with open(path, "r") as f:
            oldCode = f.read()

        if oldCode != newCode:
            with open(path, "w") as out:
                out.write(newCode)
            logger.info(f"[red]Updated code[/red] in {define.path}")
        else:
            logger.info(f"[green]No changes[/green] on {define.path}")
    else:
        with open(path, "w") as out:
            out.write(newCode)
        logger.info(f"[red]Wrote[/red] to {define.path}")


def gen_description_files(
    description: GenFiles,
    builder: cpp.ASTBuilder,
    t: TextLayout,
    tmp: bool,
) -> None:
    "Generate all translation unit files"
    for tu in description.files:
        if tu.source:
            gen_unit(
                tu.source,
                builder,
                t,
                tmp,
                isHeader=False,
                isSplitHeaderSource=bool(tu.source and tu.header),
            )

        gen_unit(
            tu.header,
            builder,
            t,
            tmp,
            isHeader=True,
            isSplitHeaderSource=bool(tu.source and tu.header),
        )


class CodegenOptions(BaseModel):
    reflection_path: str
    codegen_task: Literal["pyhaxorg", "adaptagrams"]
    tmp: bool = False


def codegen_options(f: Any) -> Any:
    return apply_options(f, options_from_model(CodegenOptions))


def _write_files_group(
    impl: GenFiles,
    builder: cpp.ASTBuilder,
    is_tmp_codegen: bool,
    t: TextLayout,
) -> None:
    gen_description_files(
        description=impl,
        builder=builder,
        t=t,
        tmp=is_tmp_codegen,
    )


@beartype
def run_codegen_pyhaxorg(
    is_tmp_codegen: bool,
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

    _write_files_group(
        gen_pyhaxorg_source(
            ast=builder,
            groups=groups,
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
