import enum
import json
from dataclasses import dataclass
from pathlib import Path

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Union
from hstd_py_lib.script_logging import pprint_to_file

import hstd_py_codegen as pb
import hstd_py_codegen.read_cpp.refl_extract as ex
from hstd_py_codegen.gen_cpp.codegen_ir import (
    GenTuEnum,
    GenTuFunction,
    GenTuStruct,
    GenTuUnion,
)
from hstd_py_codegen.read_cpp.refl_read import QualType
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
    reflection_tool_profraw_path: Optional[Path] = None,
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
        indexing_tool=f"{get_haxorg_repo_root_path()}/build/haxorg/reflection_tool",
        compilation_database=str(compile_commands),
        output_directory=str(output_dir),
        header_root=str(code_dir),
        binary_collection_file=str(output_dir.joinpath("reflection.pb")),
        only_annotated=only_annotated,
        convert_failure_log_dir=str(output_dir),
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
    commands = ex.read_compile_cmmands(conf)
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
            reflection_tool_profraw_path=reflection_tool_profraw_path,
        )
        assert wrap
        wraps.append(wrap)
        pprint_to_file(wrap, output_dir.joinpath(wrap.name).with_suffix(".py"))
        assert wrap

    assert wraps
    return ReflProviderRunResult(wraps=wraps, code_dir=code_dir)


def get_struct(
    text: str,
    stable_test_dir: Path,
    code_dir_override: Optional[Path] = None,
    **kwargs: Any,
) -> GenTuStruct:
    code_dir = stable_test_dir
    tu = (
        run_reflection_tool_provider(
            text,
            code_dir_override or Path(code_dir),
            output_dir=stable_test_dir,
            **kwargs,
        )
        .wraps[0]
        .tu
    )
    assert len(tu.structs) == 1
    return tu.structs[0]


def get_include_tree(
    text: Union[str, Dict[str, str]],
    stable_test_dir: Path,
    main_file_suffix: str,
    code_dir_override: Optional[Path] = None,
    **kwargs: Any,
) -> pb.IncludeVisit:
    code_dir = stable_test_dir
    tus = run_reflection_tool_provider(
        text,
        code_dir_override or Path(code_dir),
        output_dir=stable_test_dir,
        **kwargs,
    ).wraps
    tu = next(
        it
        for it in tus
        if it.tu.main_file_include_tree.absolute_path.endswith(main_file_suffix)
    )

    assert tu.tu.main_file_include_tree
    return tu.tu.main_file_include_tree


@beartype
def get_entires(text: str, stable_test_dir: Path, **kwargs: Any) -> List[GenTuUnion]:
    code_dir = stable_test_dir
    tu = (
        run_reflection_tool_provider(
            text,
            Path(code_dir),
            output_dir=stable_test_dir,
            **kwargs,
        )
        .wraps[0]
        .tu
    )
    return tu.enums + tu.structs + tu.functions + tu.typedefs


@beartype
def get_enum(text: str, stable_test_dir: Path, **kwargs: Any) -> GenTuEnum:
    code_dir = stable_test_dir
    tu = (
        run_reflection_tool_provider(
            text,
            Path(code_dir),
            output_dir=stable_test_dir,
            **kwargs,
        )
        .wraps[0]
        .tu
    )
    assert len(tu.enums) == 1
    return tu.enums[0]


@beartype
def get_function(text: str, stable_test_dir: Path, **kwargs: Any) -> GenTuFunction:
    code_dir = stable_test_dir
    tu = (
        run_reflection_tool_provider(
            text,
            Path(code_dir),
            output_dir=stable_test_dir,
            **kwargs,
        )
        .wraps[0]
        .tu
    )

    assert len(tu.functions) == 1
    return tu.functions[0]


@beartype
def get_type(
    *,
    preamble: List[str],
    stable_test_dir: Path,
    typ: str = "",
    struct_header: str = "struct [[refl]] test",
    field_decl: Optional[str] = None,
    **kwargs: Any,
) -> QualType:
    """
    Parse the `typ` parameter to qualified type and return result.

    :param preamble: List of extra definitions to insert before the type parsing
    :param typ: text of the type to parse
    :param stable_test_dir: Temporary directory to put the text for parsing
    :param struct_header: Temporary structure wrapping around type usage
    :param field_decl: Override standard field declaration block
    """
    assert not (typ and field_decl), "Declare either typ or field_decl, but not both"

    if field_decl:
        type_use = field_decl

    else:
        type_use = f"[[refl]] {typ} field;"

    struct = get_struct(
        "\n".join(preamble)
        + f"""
{struct_header} {{
    {type_use}
}};
""",
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        **kwargs,
    )

    assert len(struct.Fields) == 1
    return struct.Fields[0].Type
