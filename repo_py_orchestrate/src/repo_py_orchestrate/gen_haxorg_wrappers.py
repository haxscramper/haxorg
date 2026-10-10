import sys
from pathlib import Path

import click
import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from hstd_py_codegen.gen_cpp.codegen_write import gen_description_files
from hstd_py_codegen.read_cpp.refl_read import conv_proto_file
from hstd_py_lib.os_utils import latest_file
from hstd_py_lib.script_logging import get_custom_traceback_handler
from hstd_py_text_layout.base.wrap import TextLayout

from repo_py_orchestrate.codegen_config.codegen import (
    gen_haxorg_base_sources,
    run_codegen_pyhaxorg_wrappers,
)
from repo_py_orchestrate.codegen_config.extract_refl import extract_reflection


@click.command()
@click.argument("source_dir", type=Path)
@click.argument("out_dir", type=Path)
def main(source_dir: Path, out_dir: Path):
    reflection_uv = extract_reflection(
        compilation_database=latest_file(
            [
                source_dir
                / "build/conan_build/haxorg_cpp_py_wrap/build/Release/compile_commands.json",
                source_dir
                / "build/conan_build/haxorg_cpp_py_wrap/build/Debug/compile_commands.json",
            ]
        ),
        target_file=source_dir
        / "haxorg_cpp_py_wrap/src/haxorg_cpp_py_wrap/pyhaxorg_manual_impl.cpp",
        output_directory=out_dir,
    )

    assert reflection_uv.get_all(), (
        "No annotated declarations were extracted from "
        "haxorg_cpp_py_wrap/src/haxorg_cpp_py_wrap/pyhaxorg_manual_refl.cpp"
    )

    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    base_types, _ = gen_haxorg_base_sources(
        source_dir,
        t=t,
        context_tu=reflection_uv,
    )
    manual_tu = conv_proto_file(
        source_dir
        / "repo_py_orchestrate/src/repo_py_orchestrate/codegen_config/codegen_extra_types.json"
    )

    wrappers = run_codegen_pyhaxorg_wrappers(
        base_types,
        out_dir,
        reflection_tu=reflection_uv,
        manual_tu=manual_tu,
        t=t,
    )

    for wrap in wrappers:
        gen_description_files(wrap, builder, t)


if __name__ == "__main__":
    sys.excepthook = get_custom_traceback_handler(
        show_args=False,
    )
    main()
