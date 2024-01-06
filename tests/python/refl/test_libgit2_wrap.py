from tempfile import TemporaryDirectory

from py_codegen.tu_collector import run_wrap_for_config, TuOptions
from py_scriptutils.toml_config_profiler import interpolate_dictionary
from py_scriptutils.files import get_haxorg_repo_root_path

def test_libgit2_conv():
    with TemporaryDirectory() as dir:
        root = get_haxorg_repo_root_path()
        start = dict(
            input=["{config_dir}/include"],
            indexing_tool="{tool_dir}/build/utils_debug/reflection_tool",
            compilation_database="{config_dir}/compile_commands.json",
            toolchain_include="{tool_dir}/toolchain/llvm/lib/clang/17/include",
            output_directory=dir,
        )

        conf = TuOptions(
            **interpolate_dictionary(
                start,
                dict(
                    config_dir=str(root.joinpath("thirdparty/libgit2")),
                    tool_dir=str(root),
                )))

    run_wrap_for_config(conf)
