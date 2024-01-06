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
    Tuple,
)

import enum
from beartype import beartype

import py_codegen.refl_extract as ex
from tempfile import NamedTemporaryFile, TemporaryDirectory
from pathlib import Path
import json
from plumbum import local

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
@dataclass
class ReflProviderRunResult:
    wraps: List[TuWrap]
    code_dir: Path


@beartype
def run_provider(
    text: Union[str, Dict[str, str]],
    code_dir: Path,
    print_reflection_run_fail_to_stdout: bool = False,
) -> ReflProviderRunResult:
    if not code_dir.exists():
        code_dir.mkdir(parents=True)

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
            header_root=str(code_dir),
        )

        conf = ex.TuOptions.model_validate(
            interpolate_dictionary(base_dict,
                                   {"haxorg_root": str(get_haxorg_repo_root_path())}),)

        conf.cache_collector_runs = False
        conf.print_reflection_run_fail_to_stdout = print_reflection_run_fail_to_stdout
        conf.reflection_run_verbose = True

        compile_commands_content = [
            ex.CompileCommand(
                directory=conf.header_root,
                command=f"clang++ {file}",
                file=file,
                output=str(Path(file).with_suffix(".o")),
            ) for file in text.keys()
        ]

        log().info(compile_commands_content)

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
        return ReflProviderRunResult(wraps=wraps, code_dir=code_dir)


def get_struct(text: str, **kwargs) -> GenTuStruct:
    with TemporaryDirectory() as code_dir:
        tu = run_provider(text, Path(code_dir), **kwargs).wraps[0].tu
        assert len(tu.structs) == 1
        return tu.structs[0]


@beartype
def get_enum(text: str, **kwargs) -> GenTuEnum:
    with TemporaryDirectory() as code_dir:
        tu = run_provider(text, Path(code_dir), **kwargs).wraps[0].tu
        assert len(tu.enums) == 1
        return tu.enums[0]


@beartype
def get_function(text: str, **kwargs) -> GenTuFunction:
    with TemporaryDirectory() as code_dir:
        tu = run_provider(text, Path(code_dir), **kwargs).wraps[0].tu
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
    graph: gen_nim.GenGraph() = gen_nim.GenGraph()
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
def compile_nim_path(file: Path, binary: Path):
    cmd = local["nim"]
    cmd.run(["cpp", f"-o={binary}", str(file)])


@beartype
def compile_nim_code(code_dir: Path, files: Dict[str, str]):
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
