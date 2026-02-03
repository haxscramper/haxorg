from dataclasses import dataclass
import enum
import json
from pathlib import Path

from beartype import beartype
from beartype.typing import Any
from beartype.typing import Dict
from beartype.typing import List
from beartype.typing import Optional
from beartype.typing import Tuple
from beartype.typing import Union
from plumbum import CommandNotFound
from plumbum import local
import py_codegen.refl_extract as ex
from py_codegen.refl_read import ConvTu
from py_codegen.refl_read import GenTuEnum
from py_codegen.refl_read import GenTuFunction
from py_codegen.refl_read import GenTuStruct
from py_codegen.refl_read import GenTuUnion
from py_codegen.refl_read import QualType
from py_codegen.refl_wrapper_graph import TuWrap
import py_codegen.wrapper_gen_nim as gen_nim
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import get_haxorg_repo_root_path


@beartype
class PathComponentKind(enum.Enum):
    DICT_KEY = "dict_key"
    LIST_INDEX = "list_index"


@beartype
@dataclass
class PathComponent():
    kind: PathComponentKind
    value: str


@beartype
@dataclass
class PathFail():
    path: List[PathComponent]
    message: str
    given_node: Optional[Any] = None
    expected_node: Optional[Any] = None


@beartype
def is_dict_subset(expected: dict,
                   given: dict,
                   path: List[PathComponent] = []) -> List[PathFail]:

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
                    path=path + [PathComponent(PathComponentKind.DICT_KEY, key)])

    elif isinstance(expected, list) and isinstance(given, list):
        if len(expected) != len(given):
            return [
                PathFail(
                    path=path,
                    message=
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
            failures.append(
                PathFail(
                    path=path,
                    message="Subset mismatch in set",
                    given_node=given,
                    expected_node=expected,
                ))

    elif expected != given:
        failures.append(
            PathFail(
                path=path,
                message="Value mismatch",
                given_node=given,
                expected_node=expected,
            ))

    return failures


@beartype
@dataclass
class ReflProviderRunResult:
    wraps: List[TuWrap]
    code_dir: Path


@beartype
def run_provider(
    text: Union[str, Dict[str, str]],
    code_dir: Path,
    output_dir: Path,
    only_annotated: bool = False,
    print_reflection_run_fail_to_stdout: bool = False,
) -> ReflProviderRunResult:
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
        directory_root=str(code_dir),
        header_root=str(code_dir),
        binary_collection_file=str(output_dir.joinpath("reflection.pb")),
        only_annotated=only_annotated,
    )

    conf.cache_collector_runs = False
    conf.print_reflection_run_fail_to_stdout = print_reflection_run_fail_to_stdout
    conf.reflection_run_verbose = True
    conf.reflection_run_serialize = True

    compile_commands_content = [
        ex.CompileCommand(
            directory=conf.header_root,
            command=f"clang++ {file}",
            file=file,
            output=str(Path(file).with_suffix(".o")),
        ) for file in text.keys()
    ]

    log().info(compile_commands_content)

    compile_commands.write_text(
        json.dumps([cmd.model_dump() for cmd in compile_commands_content]))

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
        assert any([cmd.file == str(mapping.path) for cmd in compile_commands_content
                   ]), "Full command list {}, mapping path {}".format(
                       [cmd.file for cmd in compile_commands_content],
                       mapping.path,
                   )

        wrap = ex.run_collector_for_path(conf, mapping, commands)
        wraps.append(wrap)
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
    tu = run_provider(
        text,
        code_dir_override or Path(code_dir),
        output_dir=stable_test_dir,
        **kwargs,
    ).wraps[0].tu
    assert len(tu.structs) == 1
    return tu.structs[0]


@beartype
def get_entires(text: str, stable_test_dir: Path, **kwargs: Any) -> List[GenTuUnion]:
    code_dir = stable_test_dir
    tu = run_provider(
        text,
        Path(code_dir),
        output_dir=stable_test_dir,
        **kwargs,
    ).wraps[0].tu
    return tu.enums + tu.structs + tu.functions + tu.typedefs


@beartype
def get_enum(text: str, stable_test_dir: Path, **kwargs: Any) -> GenTuEnum:
    code_dir = stable_test_dir
    tu = run_provider(
        text,
        Path(code_dir),
        output_dir=stable_test_dir,
        **kwargs,
    ).wraps[0].tu
    assert len(tu.enums) == 1
    return tu.enums[0]


@beartype
def get_function(text: str, stable_test_dir: Path, **kwargs: Any) -> GenTuFunction:
    code_dir = stable_test_dir
    tu = run_provider(
        text,
        Path(code_dir),
        output_dir=stable_test_dir,
        **kwargs,
    ).wraps[0].tu

    assert len(tu.functions) == 1
    return tu.functions[0]


@beartype
def get_nim_code(content: gen_nim.GenTuUnion) -> gen_nim.ConvRes:
    t = gen_nim.nim.TextLayout()
    builder = gen_nim.nim.ASTBuilder(t)
    return gen_nim.conv_res_to_nim(builder, content, gen_nim.NimOptions())


@beartype
def format_nim_code(refl: ReflProviderRunResult,
                    is_cpp_wrap: bool = True,
                    with_header_imports: bool = True) -> Dict[str, gen_nim.GenNimResult]:
    graph: gen_nim.GenGraph = gen_nim.GenGraph()
    for wrap in refl.wraps:
        graph.add_unit(wrap)

    graph.connect_usages()
    graph.group_connected_files()

    def get_out_path(path: Path) -> Path:
        return path.with_suffix(".nim")

    mapped: Dict[str, gen_nim.GenNimResult] = {}
    for sub in graph.subgraphs:
        code = gen_nim.to_nim(
            graph=graph,
            sub=sub,
            conf=gen_nim.NimOptions(
                with_header_imports=with_header_imports,
                is_cpp_wrap=is_cpp_wrap,
            ),
            output_directory=refl.code_dir,
            get_out_path=get_out_path,
        )

        assert code
        mapped[str(get_out_path(sub.original).relative_to(refl.code_dir))] = code

    return mapped


@beartype
def has_nim_installed() -> bool:
    try:
        local["nim"]
        return True

    except CommandNotFound:
        return False


@beartype
def compile_nim_path(file: Path, binary: Path) -> None:
    cmd = local["nim"]
    cmd.run(["cpp", f"-o={binary}", str(file)])


@beartype
def compile_nim_code(code_dir: Path, files: Dict[str, str]) -> None:
    for file, content in files.items():
        code_dir.joinpath(file).write_text(content)

    for file in files.keys():
        compile_nim_path(code_dir.joinpath(file),
                         code_dir.joinpath(file).with_suffix(".bin"))


@beartype
def verify_nim_code(code_dir: Path, formatted: Dict[str, gen_nim.GenNimResult],
                    test_text: str) -> Tuple[int, str, str]:
    compile_nim_code(code_dir=code_dir,
                     files={
                         file: res.content for file, res in formatted.items()
                     })

    compile_nim_code(code_dir, files={"main.nim": test_text})

    binary = local[str(code_dir.joinpath("main.bin"))]
    retcode, stdout, stderr = binary.run()
    return (retcode, stdout, stderr)
