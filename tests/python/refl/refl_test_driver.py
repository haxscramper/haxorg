from py_codegen.refl_read import ConvTu, GenTuStruct, GenTuEnum, GenTuFunction, QualType
from beartype.typing import Optional, Any, TypeVar, Callable, Type, NamedTuple, List
import enum
from beartype import beartype

import py_codegen.refl_extract as ex
from tempfile import NamedTemporaryFile, TemporaryDirectory
from pathlib import Path
import json
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import interpolate_dictionary, get_haxorg_repo_root_path
from pprint import pprint
import py_codegen.wrapper_gen_nim as gen_nim

STABLE_FILE_NAME = "/tmp/cpp_stable.cpp"


@beartype
class PathComponentKind(enum.Enum):
    DICT_KEY = "dict_key"
    LIST_INDEX = "list_index"


@beartype
class PathComponent(NamedTuple):
    kind: PathComponentKind
    value: str


@beartype
class PathFail(NamedTuple):
    path: List[PathComponent]
    message: str
    given_node: Any
    expected_node: Any


@beartype
def is_dict_subset(expected: dict,
                   given: dict,
                   path: List[PathComponent] = []) -> List[PathFail]:

    failures = []
    if isinstance(expected, dict) and isinstance(given, dict):
        missing_keys = set(expected.keys()).difference(set(given.keys()))
        if 0 < len(missing_keys):
            return [
                PathFail(path, f"Expected had keys not present in given {missing_keys}")
            ]

        else:
            for key in expected.keys():
                failures += is_dict_subset(
                    expected=expected[key],
                    given=given[key],
                    path=path + [PathComponent(PathComponentKind.DICT_KEY, key)])

    elif isinstance(expected, list) and isinstance(given, list):
        if len(expected) != len(given):
            return [
                PathFail(
                    path,
                    f"List len mismatch {len(expected)} for expected, {len(given)} for given"
                )
            ]

        else:
            fails = []
            for index, (expected_item, given_item) in enumerate(zip(expected, given)):
                fails += is_dict_subset(
                    expected_item, given_item,
                    path + [PathComponent(PathComponentKind.LIST_INDEX, str(index))])

    elif isinstance(expected, set) and isinstance(given, set):
        if not set(expected).issubset(set(given)):
            failures.append(PathFail(path, "Subset mismatch in set", given, expected))

    elif expected != given:
        failures.append(PathFail(path, "Value mismatch", given, expected))

    return failures


@beartype
def run_provider(text: str,
                 stable_cpp_file: Optional[str] = None,
                 print_reflection_run_fail_to_stdout: bool = False) -> ConvTu:
    with (
            # TODO Delete only when test run is ok
            open(stable_cpp_file, "w")
            if stable_cpp_file else NamedTemporaryFile(mode="w", suffix=".cpp") as file,
            NamedTemporaryFile(mode="w", suffix=".json") as compile_commands,
    ):
        tmp_parent = str(Path(file.name).parent)
        base_dict = dict(
            input=[file.name],
            indexing_tool="{haxorg_root}/build/utils/reflection_tool",
            compilation_database=compile_commands.name,
            toolchain_include="{haxorg_root}/toolchain/llvm/lib/clang/17/include",
            output_directory=tmp_parent,
            directory_root=tmp_parent)

        conf = ex.TuOptions.model_validate(
            interpolate_dictionary(base_dict,
                                   {"haxorg_root": get_haxorg_repo_root_path()}))

        conf.print_reflection_run_fail_to_stdout = print_reflection_run_fail_to_stdout
        conf.reflection_run_verbose = True

        compile_commands.write(
            json.dumps([{
                "directory": conf.directory_root,
                "command": f"clang++ {file.name}",
                "file": conf.input[0],
                "output": str(Path(conf.input[0]).with_suffix(".o"))
            }]))

        compile_commands.flush()

        file.write(text)
        file.flush()

        mappings = ex.expand_input(conf)
        commands = ex.read_compile_cmmands(conf)
        wrap = ex.run_collector_for_path(conf, mappings[0], commands)
        assert wrap
        return wrap.tu


def get_struct(text: str, **kwargs) -> GenTuStruct:
    tu = run_provider(text, **kwargs)
    assert len(tu.structs) == 1
    return tu.structs[0]


def get_enum(text: str, **kwargs) -> GenTuEnum:
    tu = run_provider(text, **kwargs)
    assert len(tu.enums) == 1
    return tu.enums[0]


def get_function(text: str, **kwargs) -> GenTuFunction:
    tu = run_provider(text, **kwargs)
    assert len(tu.functions) == 1
    return tu.functions[0]


def get_nim_code(content: gen_nim.GenTuUnion) -> gen_nim.ConvRes:
    t = gen_nim.nim.TextLayout()
    builder = gen_nim.nim.ASTBuilder(t)
    return gen_nim.conv_res_to_nim(builder, content, gen_nim.NimOptions())
