import enum
import json
from dataclasses import dataclass
from pathlib import Path

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Union
from hstd_py_lib.script_logging import pprint_to_file

import hstd_py_codegen.read_cpp.refl_extract as ex
from hstd_py_codegen.read_cpp.refl_wrapper_graph import (
    TuWrap,
)


@beartype
class PathComponentKind(enum.Enum):
    DICT_KEY = "dict_key"
    LIST_INDEX = "list_index"


@beartype
@dataclass
class PathComponent:
    kind: PathComponentKind
    value: str


@beartype
@dataclass
class PathFail:
    path: List[PathComponent]
    message: str
    given_node: Optional[Any] = None
    expected_node: Optional[Any] = None


@beartype
def is_dict_subset(
    expected: dict, given: dict, path: List[PathComponent] = []
) -> List[PathFail]:

    failures = []
    if isinstance(expected, dict) and isinstance(given, dict):
        missing_keys = set(expected.keys()).difference(set(given.keys()))
        if 0 < len(missing_keys):
            return [
                PathFail(
                    path=path,
                    message=f"Expected had keys not present in given {missing_keys}",
                )
            ]

        else:
            for key in expected.keys():
                failures += is_dict_subset(
                    expected=expected[key],
                    given=given[key],
                    path=path + [PathComponent(PathComponentKind.DICT_KEY, key)],
                )

    elif isinstance(expected, list) and isinstance(given, list):
        if len(expected) != len(given):
            return [
                PathFail(
                    path=path,
                    message=f"List len mismatch {len(expected)} for expected, {len(given)} for given",
                )
            ]

        else:
            fails = []
            for index, (expected_item, given_item) in enumerate(zip(expected, given)):
                fails += is_dict_subset(
                    expected_item,
                    given_item,
                    path + [PathComponent(PathComponentKind.LIST_INDEX, str(index))],
                )

    elif isinstance(expected, set) and isinstance(given, set):
        if not set(expected).issubset(set(given)):
            failures.append(
                PathFail(
                    path=path,
                    message="Subset mismatch in set",
                    given_node=given,
                    expected_node=expected,
                )
            )

    elif expected != given:
        failures.append(
            PathFail(
                path=path,
                message="Value mismatch",
                given_node=given,
                expected_node=expected,
            )
        )

    return failures


@beartype
@dataclass
class ReflProviderRunResult:
    wraps: List[TuWrap]
    code_dir: Path


@beartype
def run_reflection_tool_provider(
    text: Union[str, Dict[str, str]],
    code_dir: Path,
    output_dir: Path,
    only_annotated: bool = False,
    reflection_run_verbose: bool = False,
    print_reflection_run_fail_to_stdout: bool = False,
) -> ReflProviderRunResult:
    """
    Run reflection data provider
    """
    if not code_dir.exists():
        code_dir.mkdir(parents=True)

    compile_commands = output_dir.joinpath("compile_commands.json")

    assert len(str(output_dir)) != 0

    if isinstance(text, str):
        text = {"automatic_provider_run_file.hpp": text}

    text = {
        file if Path(file).is_absolute() else str(code_dir.joinpath(file)): value
        for file, value in text.items()
    }

    conf = ex.TuOptions(
        input=[str(file) for file in text.keys()],
        compilation_database=str(compile_commands),
        output_directory=str(output_dir),
        header_root=str(code_dir),
        binary_collection_file=str(output_dir.joinpath("reflection.pb")),
        only_annotated=only_annotated,
        convert_failure_log_dir=str(output_dir),
        build_root=str(output_dir),
    )

    conf.cache_collector_runs = False
    conf.print_reflection_run_fail_to_stdout = print_reflection_run_fail_to_stdout
    conf.reflection_run_verbose = reflection_run_verbose
    conf.reflection_run_serialize = True

    compile_commands_content = [
        ex.CompileCommand(
            directory=conf.header_root,
            command=f"clang++ -std=c++23 {file}",
            file=file,
            output=str(Path(file).with_suffix(".o")),
        )
        for file in text.keys()
    ]

    # log().info(compile_commands_content)

    compile_commands.write_text(
        json.dumps([cmd.model_dump() for cmd in compile_commands_content])
    )

    for file, content in text.items():
        full = Path(code_dir).joinpath(file)
        full.parent.mkdir(exist_ok=True, parents=True)
        if full.exists():
            if full.read_text() != content:
                full.write_text(content)

        else:
            full.write_text(content)

    mappings = ex.expand_input(conf)
    commands = ex.read_compile_commands(Path(conf.build_root))
    wraps: List[TuWrap] = []
    for mapping in mappings:
        assert any([cmd.file == str(mapping.path) for cmd in compile_commands_content]), (
            "Full command list {}, mapping path {}".format(
                [cmd.file for cmd in compile_commands_content],
                mapping.path,
            )
        )

        wrap = ex.run_reflection_tool_for_path(
            conf,
            mapping,
            commands,
        )
        assert wrap
        wraps.append(wrap)
        pprint_to_file(wrap, output_dir.joinpath(wrap.name).with_suffix(".py"))
        assert wrap

    assert wraps
    return ReflProviderRunResult(wraps=wraps, code_dir=code_dir)
