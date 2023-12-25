import py_codegen.refl_extract as ex
from tempfile import NamedTemporaryFile, TemporaryDirectory
from pathlib import Path
import json
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import interpolate_dictionary, get_haxorg_repo_root_path


def run_provider(text: str):
    with (
            NamedTemporaryFile(mode="w", suffix=".cpp", delete=True) as file,
            TemporaryDirectory() as dir,
            NamedTemporaryFile(mode="w", suffix=".json", delete=True) as compile_commands,
    ):
        base_dict = dict(
            input=[file.name],
            indexing_tool="{haxorg_root}/build/utils/reflection_tool",
            compilation_database=compile_commands.name,
            toolchain_include="{haxorg_root}/toolchain/llvm/lib/clang/17/include",
            output_directory=dir,
            directory_root=str(Path(file.name).parent))

        conf = ex.TuOptions.model_validate(
            interpolate_dictionary(base_dict,
                                   {"haxorg_root": get_haxorg_repo_root_path()}))
        
        conf.print_reflection_run_fail_to_stdout = True

        compile_commands.write(
            json.dumps([{
                "directory": conf.directory_root,
                "command": f"clang++ {file.name}",
                "file": conf.input[0],
                "output": str(Path(conf.input[0]).with_suffix(".o"))
            }]))

        compile_commands.flush()

        mappings = ex.expand_input(conf)
        commands = ex.read_compile_cmmands(conf)
        wrap = ex.run_collector_for_path(conf, mappings[0], commands)
        assert wrap


def test_provider():
    run_provider("123123")
