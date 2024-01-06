import logging
from tempfile import TemporaryDirectory

from py_codegen.tu_collector import run_wrap_for_config, TuOptions
from py_scriptutils.toml_config_profiler import interpolate_dictionary
from py_scriptutils.files import get_haxorg_repo_root_path
from pathlib import Path
from py_scriptutils.tracer import TraceCollector
from refl_test_driver import compile_nim_code
from py_scriptutils.script_logging import log

log("refl.nim").setLevel(logging.DEBUG)


def test_libgit2_conv():
    with TemporaryDirectory() as dir:
        code_dir = Path(dir)
        code_dir = Path("/tmp/libgit_wrap_test_dir")
        root = get_haxorg_repo_root_path()
        start = dict(
            input=["{config_dir}/include"],
            indexing_tool="{tool_dir}/build/utils_debug/reflection_tool",
            compilation_database="{config_dir}/compile_commands.json",
            toolchain_include="{tool_dir}/toolchain/llvm/lib/clang/17/include",
            output_directory=str(code_dir),
            execution_trace=str(code_dir.joinpath("run_trace.json")),
            nim=dict(
                universal_imports="libgit2_config.nim",
                function_renames=[
                    dict(original="git_odb_write_pack", renamed="git_odb_write_pack_fn")
                ],
            ),
            directory_root="{config_dir}/include",
        )

        conf = TuOptions(**interpolate_dictionary(
            start,
            dict(
                config_dir=str(root.joinpath("thirdparty/libgit2")),
                tool_dir=str(root),
            )))

    trace = TraceCollector()
    run_wrap_for_config(conf, trace)
    trace.export_to_json(code_dir.joinpath("trace.json"))

    importall = "\n".join(f"import \"{file.relative_to(code_dir)}\""
                          for file in code_dir.joinpath("git2").glob("*.nim"))

    compile_nim_code(code_dir, {"main.nim": importall})
