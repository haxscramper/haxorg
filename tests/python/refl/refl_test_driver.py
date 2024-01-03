from py_codegen.refl_read import (
    ConvTu,
    GenTuStruct,
    GenTuEnum,
    GenTuFunction,
    QualType,
)
from beartype.typing import (
    Optional,
    Any,
    TypeVar,
    Callable,
    Type,
    NamedTuple,
    List,
    Dict,
    Union,
)

import enum
from beartype import beartype

import py_codegen.refl_extract as ex
from tempfile import NamedTemporaryFile, TemporaryDirectory
from pathlib import Path
import json

from py_codegen.refl_wrapper_graph import TuWrap
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import interpolate_dictionary, get_haxorg_repo_root_path
from pprint import pprint
import py_codegen.wrapper_gen_nim as gen_nim
from dataclasses import dataclass

STABLE_FILE_NAME = "/tmp/cpp_stable.cpp"


@beartype
class PathComponentKind(enum.Enum):
    DICT_KEY = "dict_key"
    LIST_INDEX = "list_index"


@beartype
@dataclass
class PathComponent(NamedTuple):
    kind: PathComponentKind
    value: str


@beartype
@dataclass
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
def run_provider(text: Union[str, Dict[str, str]],
                 code_dir: Path,
                 print_reflection_run_fail_to_stdout: bool = False) -> List[TuWrap]:
    assert code_dir.exists()
    with (NamedTemporaryFile(mode="w", suffix=".json") as compile_commands):
        if isinstance(text, str):
            text = {"automatic_provider_run_file.hpp": text}

        text = {
            file if Path(file).is_absolute() else str(code_dir.joinpath(file)): value
            for file, value in text.items()
        }

        base_dict = dict(
            input=[str(file) for file in text.keys()],
            indexing_tool="{haxorg_root}/build/utils/reflection_tool",
            compilation_database=compile_commands.name,
            toolchain_include="{haxorg_root}/toolchain/llvm/lib/clang/17/include",
            output_directory=str(code_dir),
            directory_root=str(code_dir),
        )

        conf = ex.TuOptions.model_validate(
            interpolate_dictionary(base_dict,
                                   {"haxorg_root": str(get_haxorg_repo_root_path())}),)

        conf.print_reflection_run_fail_to_stdout = print_reflection_run_fail_to_stdout
        conf.reflection_run_verbose = True

        compile_commands_content = [
            ex.CompileCommand(
                directory=conf.directory_root,
                command=f"clang++ {file}",
                file=file,
                output=str(Path(file).with_suffix(".o")),
            ) for file in text.keys()
        ]

        log.info(compile_commands_content)

        compile_commands.write(
            json.dumps([cmd.model_dump() for cmd in compile_commands_content]))
        compile_commands.flush()

        for file, content in text.items():
            full = Path(code_dir).joinpath(file)
            if full.exists():
                if full.read_text() != content:
                    full.write_text(content)

            else:
                full.write_text(content)

        mappings = ex.expand_input(conf)
        commands = ex.read_compile_cmmands(conf)
        wraps: List[TuWrap] = []
        for mapping in mappings:
            assert any([
                cmd.file == str(mapping.path) for cmd in compile_commands_content
            ]), "Full command list {}, mapping path {}".format(
                [cmd.file for cmd in compile_commands_content],
                mapping.path,
            )

            wrap = ex.run_collector_for_path(conf, mapping, commands)
            wraps.append(wrap)
            assert wrap

        assert wraps
        return wraps


def get_struct(text: str, **kwargs) -> GenTuStruct:
    with TemporaryDirectory() as code_dir:
        tu = run_provider(text, Path(code_dir), **kwargs)[0].tu
        assert len(tu.structs) == 1
        return tu.structs[0]


def get_enum(text: str, **kwargs) -> GenTuEnum:
    with TemporaryDirectory() as code_dir:
        tu = run_provider(text, Path(code_dir), **kwargs)[0].tu
        assert len(tu.enums) == 1
        return tu.enums[0]


def get_function(text: str, **kwargs) -> GenTuFunction:
    with TemporaryDirectory() as code_dir:
        tu = run_provider(text, Path(code_dir), **kwargs)[0].tu
        assert len(tu.functions) == 1
        return tu.functions[0]


def get_nim_code(content: gen_nim.GenTuUnion) -> gen_nim.ConvRes:
    t = gen_nim.nim.TextLayout()
    builder = gen_nim.nim.ASTBuilder(t)
    return gen_nim.conv_res_to_nim(builder, content, gen_nim.NimOptions())
