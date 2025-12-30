from py_scriptutils import configure_asan
import logging
from tempfile import TemporaryDirectory

import os
from beartype.typing import TYPE_CHECKING
if os.getenv("HAXORG_REDUCED_RELEASE_TEST") and not TYPE_CHECKING:
    from py_scriptutils.test_utils import HasAnyAttr 
    tu_collector = HasAnyAttr()
else: 
    import py_codegen.tu_collector as tu_collector

if os.getenv("HAXORG_REDUCED_RELEASE_TEST") and not TYPE_CHECKING:
    from py_scriptutils.test_utils import HasAnyAttr 
    refl_test_driver = HasAnyAttr()
else: 
    import refl_test_driver

from py_scriptutils.toml_config_profiler import interpolate_dictionary
from py_scriptutils.files import get_haxorg_repo_root_path
from pathlib import Path
from py_scriptutils.tracer import TraceCollector
from py_scriptutils.script_logging import log
import pytest
from tempfile import gettempdir

log("refl.nim").setLevel(logging.DEBUG)


@pytest.mark.skip()
def test_libgit2_conv() -> None:
    with TemporaryDirectory() as dir:
        code_dir = Path(dir)
        code_dir = Path(gettempdir()) / "libgit_wrap_test_dir"
        root = get_haxorg_repo_root_path()
        start = dict(
            input=["{config_dir}/include"],
            indexing_tool="{tool_dir}/build/haxorg/scripts/cxx_codegen/reflection_tool",
            build_root="{config_dir}/build",
            source_root="{config_dir}",
            header_root="{config_dir}/include",
            toolchain_include="{tool_dir}/toolchain/llvm/lib/clang/18/include",
            output_directory=str(code_dir),
            execution_trace=str(code_dir.joinpath("run_trace.json")),
            cmake_configure_options=["-DBULD_TEST=OFF"],
            nim=dict(
                universal_imports="libgit2_config.nim",
                function_renames=[
                    dict(original="git_odb_write_pack", renamed="git_odb_write_pack_fn")
                ],
            ),
        )

        dep = get_haxorg_repo_root_path().joinpath("thirdparty/libgit2")
        comp = "compile_commands.json"
        if dep.joinpath(comp).exists():
            dep.joinpath(comp).unlink()

        if dep.joinpath("build").joinpath(comp).exists():
            dep.joinpath("build").joinpath(comp).unlink()

        conf = tu_collector.TuOptions(**interpolate_dictionary(
            start,
            dict(
                config_dir=str(root.joinpath("thirdparty/libgit2")),
                tool_dir=str(root),
            )))

    trace = TraceCollector()
    tu_collector.run_wrap_for_config(conf, trace)
    trace.export_to_json(code_dir.joinpath("trace.json"))

    relative = [
        str(file.relative_to(code_dir))
        for file in code_dir.joinpath("git2").glob("*.nim")
    ]

    importall = "\n".join(f"import \"{it}\"" for it in relative)
    assert "git2/commit.nim" in relative
    assert "git2/refspec.nim" in relative
    assert "git2/revert.nim" in relative

    refl_test_driver.compile_nim_code(code_dir, {"main.nim": importall})
