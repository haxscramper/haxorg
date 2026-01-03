import io
import json
import os.path
import time
from copy import deepcopy
from dataclasses import dataclass, field
from hashlib import md5
from pathlib import Path
from pprint import pformat, pprint
from typing import TYPE_CHECKING
import sys
from plumbum import local

import py_scriptutils.toml_config_profiler as conf_provider
from beartype import beartype
from beartype.typing import (
    Any,
    Dict,
    List,
    NewType,
    Optional,
    Set,
    Tuple,
    TypeAlias,
    Union,
    cast,
    Literal,
)
from plumbum import local
from py_scriptutils.files import IsNewInput
from py_scriptutils.script_logging import log
from pydantic import BaseModel, Field

import py_codegen.wrapper_gen_nim as gen_nim
from py_codegen.gen_tu_cpp import QualType
from py_codegen.refl_read import ConvTu, conv_proto_file, open_proto_file
from py_codegen.refl_wrapper_graph import GenGraph, TuWrap

if TYPE_CHECKING:
    from py_textlayout.py_textlayout_wrap import BlockId
else:
    BlockId = NewType('BlockId', int)


class TuOptions(BaseModel):
    input: List[str] = Field(description="List of input files, directories or globs",)
    indexing_tool: str = Field(description="Path to the TU index generator tool",)

    compilation_database: Optional[str] = Field(
        description="Explicit path to the compilation database to use for analysis",
        default=None,
    )

    build_root: Optional[str] = Field(
        description="Path to the wrapped project build directory. For cmake projects"
        "compile commands will be contructed automatically there if compilation "
        "database json was not specified explicitly.",
        default=None,
    )

    source_root: Optional[str] = Field(
        description="Main project root where cmake is located", default=None)

    header_root: str = Field(description="Path to the header file directory wrapped",)

    binary_tmp: str = Field(
        description="Path to store temporary binary artifacts",
        default="/tmp/tu_collector",
    )

    cmake_configure_options: List[str] = Field(
        description="Parameters for cmake run when creating compilation database",
        default_factory=list)

    toolchain_include: Optional[str] = Field(
        description="Path to the toolchain that was used to compile indexing tool",
        default=None,
    )

    reflect_cache: str = Field(
        description="Store last reflection convert timestamps",
        default="/tmp/tu_collector/runs.json",
    )

    cache_collector_runs: bool = Field(
        default=True,
        description="Cache collector binary runs for files",
    )

    path_suffixes: List[str] = Field(
        description="List of file suffixes used for dir list filtering",
        default=[".hpp", ".cpp", ".h", ".c", ".cxx"],
        alias="path-suffixes",
    )

    execution_trace: Optional[str] = Field(
        description="Output path for the execution trace json",
        default=None,
    )

    output_directory: str = Field(description="Directory to write output wrapped files",)

    convert_failure_log_dir: str = Field(
        default="/tmp/tu_collector/converter_fails",
        description=
        "Directory to dump debug information about failed translation unit converter runs"
    )

    nim: Optional[gen_nim.NimOptions] = None
    print_reflection_run_fail_to_stdout: bool = Field(
        description="If reflection tool run fails, write the error report to stdout",
        default=False)

    reflection_run_verbose: bool = Field(default=False)
    reflection_run_serialize: bool = Field(
        default=False,
        description="Serialize result of the reflection collector run into a JSON file",
    )
    reflection_run_path: Optional[str] = Field(
        default=None,
        description=
        "Absolute path to the reflection run serialization output. If not specified but the "
        "reflection serialization itself is requested, script will will write JSON file "
        "in the same output directory as the rest of the conversion.")


@beartype
@dataclass
class PathMapping:
    path: Path
    root: Path


@beartype
def expand_input(conf: TuOptions) -> List[PathMapping]:
    """
    Generate list of file mappings based on input configuration options -- individual
    files, globs or recursive directories. 
    """
    directory_root = Path(conf.header_root) and Path(conf.header_root)
    result: List[PathMapping] = []
    for item in conf.input:
        path = Path(item)
        if path.is_file():
            result.append(PathMapping(path, directory_root))

        elif path.is_dir():
            for sub in path.rglob("*"):
                if sub.suffix in conf.path_suffixes:
                    result.append(PathMapping(sub, directory_root or path))

        else:
            if "*" not in item and "?" not in item:
                log().warning(f"{item} is not a file or directory, treating as glob")

            for sub in Path().glob(item):
                result.append(PathMapping(sub, directory_root))

    return result


@beartype
def get_compile_commands(conf: TuOptions) -> Path:
    lg = log("refl.cli.read")
    if conf.compilation_database:
        lg.info(f"Using provided compilation database file {conf.compilation_database}")
        assert Path(conf.compilation_database).exists(), conf.compilation_database
        database = Path(conf.compilation_database)

    else:
        assert conf.build_root
        assert conf.source_root
        comp = "compile_commands.json"

        build = Path(conf.build_root)
        source = Path(conf.source_root)

        if not build.joinpath(comp).exists():
            lg.info(f"'{build.joinpath(comp)}' does not exist, using cmake to generate")
            cmake = local["cmake"]
            cmake.run([
                *conf.cmake_configure_options,
                "-B",
                str(conf.build_root),
                "-S",
                str(conf.source_root),
                "-DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE",
            ])

        if not source.joinpath(comp).exists():
            lg.info(f"'{source.joinpath(comp)}' does not exist, using compdb to generate")
            compdb = local["poetry"]
            _, stdout, _ = compdb.run(
                ["run", "compdb", "-p",
                 str(conf.build_root), "list"])

            source.joinpath(comp).write_text(stdout)

        database = source.joinpath(comp)

    assert database.exists()
    return database


@beartype
@dataclass
class CollectorRunResult:
    conv_tu: Optional[ConvTu]
    pb_path: Optional[Path]
    success: bool
    res_stdout: str
    res_stderr: str
    flags: dict = field(default_factory=dict)


@beartype
def run_collector(
    conf: TuOptions,
    input: Path,
    output: Path,
) -> Optional[CollectorRunResult]:
    # Execute reflection data collector binary, producing a new converted translation
    # unit or an empty result of conversion has failed.
    assert input.exists()
    if not output.parent.exists():
        output.parent.mkdir(parents=True)

    tmp = Path(conf.binary_tmp)
    if not tmp.exists():
        tmp.mkdir(parents=True)

    refl = {}
    if Path(conf.reflect_cache).exists():
        with open(conf.reflect_cache, "r") as file:
            refl = json.load(file)

    if (str(input) in refl) and (max(input.stat().st_mtime,
                                     Path(conf.indexing_tool).stat().st_mtime)
                                 < refl[str(input)]) and (output.exists()):
        # return
        pass

    assert Path(conf.indexing_tool).exists(
    ), f"Indexing tool binary is missing, '{conf.indexing_tool}' does not exist"

    tool = local[conf.indexing_tool]

    # Create a temporary list of files content will be added to the dumped translation
    # unit.
    tmp_output = tmp.joinpath(md5(str(output).encode("utf-8")).hexdigest() + ".pb")
    target_files = tmp_output.with_suffix(".json")

    database = get_compile_commands(conf)

    opts: Dict[str, Any] = dict(
        reflection=dict(compilation_database=str(database),),
        output=str(tmp_output),
        input=[str(input)],
        mode="AllTargetedFiles",
    )

    if conf.toolchain_include:
        opts["reflection"]["toolchain_include"] = str(conf.toolchain_include)

    if conf.reflection_run_verbose:
        opts["verbose"] = True

    if not conf.cache_collector_runs or IsNewInput([str(input), conf.indexing_tool],
                                                   tmp_output):
        log("refl.cli.read").info(f"Running collector on {input}")

        res_code, res_stdout, res_stderr = cast(
            Tuple[int, str, str], tool.run([json.dumps(opts)], retcode=None))

    else:
        log("refl.cli.read").info(f"Using cache for {input}")
        res_code = 0
        res_stdout = ""
        res_stderr = ""

    if res_code != 0:
        log("refl.cli.read").warning(f"Failed to run collector for {input}")
        return CollectorRunResult(
            None,
            None,
            success=False,
            res_stdout=res_stdout,
            res_stderr=res_stderr,
            flags=opts,
        )

    else:
        tu = conv_proto_file(tmp_output, original=input)
        refl[str(input)] = time.time()
        with open(conf.reflect_cache, "w") as file:
            file.write(json.dumps(refl, indent=2))

        return CollectorRunResult(
            tu,
            tmp_output,
            success=True,
            res_stdout=res_stdout,
            res_stderr=res_stderr,
            flags=opts,
        )


class CompileCommand(BaseModel):
    directory: str
    command: str
    file: str
    output: Optional[str] = None


@beartype
def read_compile_cmmands(conf: TuOptions) -> List[CompileCommand]:
    database = get_compile_commands(conf)
    return [CompileCommand.model_validate(d) for d in json.loads(database.read_text())]


@beartype
def write_run_result_information(
    conf: TuOptions,
    tu: CollectorRunResult,
    path: Path,
    commands: List[CompileCommand],
) -> None:
    debug_dir = Path(conf.convert_failure_log_dir)
    # if debug_dir.exists():
    #     shutil.rmtree(str(debug_dir))

    debug_dir.mkdir(parents=True, exist_ok=True)
    sanitized = "".join([c if c.isalnum() else "_" for c in str(path)])

    if not tu.success or conf.reflection_run_verbose:
        if not conf.print_reflection_run_fail_to_stdout:
            log().warning(
                f"{'Executed' if tu.success else 'Failed to run'} conversion for [green]{path}[/green], wrote to {debug_dir}/{sanitized}"
            )

    def write_reflection_stats(file: io.TextIOWrapper) -> None:

        def sep(name: str) -> None:
            file.write("\n\n" + name + "-" * 120 + "\n\n")

        sep("Failure stdout:")
        file.write(tu.res_stdout)

        sep("Failure stderr:")
        file.write(tu.res_stderr)

        for cmd in commands:
            if cmd.file == str(path):
                sep("Compile commands:")
                file.write(json.dumps(cmd.model_dump(), indent=2))

                sep("Binary command:")
                file.write(" ^\n    ".join(cmd.command.split()))

        sep("Flags:")
        file.write(" ^\n    ".join([
            conf.indexing_tool,
            "'" + json.dumps(tu.flags) + "'",
        ]))

        sep("Serialized data:")
        if tu.pb_path and tu.pb_path.exists():
            file.write(open_proto_file(tu.pb_path).to_json(2))

    if conf.print_reflection_run_fail_to_stdout:
        buffer = io.StringIO()
        write_reflection_stats(buffer)  # type: ignore
        log().error(buffer.getvalue())

    else:
        with open(debug_dir.joinpath(sanitized), "w") as file:
            write_reflection_stats(file)


@beartype
def remove_dbgOrigin(json_str: str) -> str:

    def remove_field(obj: Any) -> Any:
        if isinstance(obj, dict):
            obj.pop("dbgOrigin", None)
            for key, value in list(obj.items()):
                obj[key] = remove_field(value)
        elif isinstance(obj, list):
            obj = [remove_field(item) for item in obj]
        return obj

    data = json.loads(json_str)
    cleaned_data = remove_field(data)
    return json.dumps(cleaned_data, indent=2, sort_keys=True)


@beartype
def run_collector_for_path(
    conf: TuOptions,
    mapping: PathMapping,
    commands: List[CompileCommand],
) -> Optional[TuWrap]:
    path = mapping.path
    tu: CollectorRunResult = run_collector(conf, path, path.with_suffix(".py"))
    if tu.success:
        relative = Path(conf.output_directory).joinpath(path.relative_to(mapping.root))

        if not relative.parent.exists():
            relative.parent.mkdir(parents=True)

        serialize_path = relative.with_suffix(".json")
        if conf.reflection_run_serialize:
            out_path = conf.reflection_run_path or str(serialize_path)
            with open(out_path, "w") as file:
                file.write(remove_dbgOrigin(open_proto_file(tu.pb_path).to_json()))
                log().info(f"Wrote dump to {serialize_path}")

        write_run_result_information(conf, tu, path, commands)

        return TuWrap(name=path.stem,
                      tu=tu.conv_tu,
                      original=path,
                      mapping=relative.with_suffix(".nim"))

    else:
        write_run_result_information(conf, tu, path, commands)
        return None
