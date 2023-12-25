import io
import json
import time
from copy import deepcopy
from dataclasses import dataclass, field
from hashlib import md5
from pathlib import Path
from pprint import pformat, pprint
from typing import TYPE_CHECKING
import sys

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
    from py_textlayout.py_textlayout import BlockId
else:
    BlockId = NewType('BlockId', int)


class TuOptions(BaseModel):
    input: List[str] = Field(description="List of input files, directories or globs")
    indexing_tool: str = Field(description="Path to the TU index generator tool")
    compilation_database: str = Field(description="Path to the compilation database")
    binary_tmp: str = Field(description="Path to store temporary binary artifacts",
                            default="/tmp/tu_collector")
    toolchain_include: str = Field(
        description="Path to the toolchain that was used to compile indexing tool")
    reflect_cache: str = Field(description="Store last reflection convert timestamps",
                               default="/tmp/tu_collector/runs.json")
    directory_root: Optional[str] = Field(
        description="Root of the source header directory", default=None)
    path_suffixes: List[str] = Field(
        description="List of file suffixes used for dir list filtering",
        default=[".hpp", ".cpp", ".h", ".c", ".cxx"],
        alias="path-suffixes")

    execution_trace: str = Field(description="Output path for the execution trace json",
                                 default="/tmp/tu_collector_trace.json")

    output_directory: str = Field(description="Directory to write output wrapped files")

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
    directory_root = conf.directory_root and Path(conf.directory_root)
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
                log.warning(f"{item} is not a file or directory, treating as glob")

            for sub in Path().glob(item):
                result.append(PathMapping(sub, directory_root))

    return result


@beartype
@dataclass
class CollectorRunResult:
    conv_tu: Optional[ConvTu]
    pb_path: Optional[Path]
    success: bool
    res_stdout: str
    res_stderr: str
    flags: List[str] = field(default_factory=list)


@beartype
def run_collector(conf: TuOptions, input: Path,
                  output: Path) -> Optional[CollectorRunResult]:
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

    flags = [
        f"-p={conf.compilation_database}",
        f"--compilation-database={conf.compilation_database}",
        f"--out={str(tmp_output)}",
        f"--toolchain-include={conf.toolchain_include}",
        f"--target-files={target_files}",
        str(input),
    ]

    if conf.reflection_run_verbose:
        flags.append("--verbose")

    if IsNewInput([str(input), conf.indexing_tool], tmp_output):
        with open(str(target_files), "w") as file:
            file.write(json.dumps([str(input)], indent=2))

        log.info(f"Running collector on {input}")

        res_code, res_stdout, res_stderr = cast(Tuple[int, str, str],
                                                tool.run(flags, retcode=None))

    else:
        log.info(f"Using cache for {input}")
        res_code = 0
        res_stdout = ""
        res_stderr = ""

    if res_code != 0:
        log.warning(f"Failed to run collector for {input}")
        return CollectorRunResult(
            None,
            None,
            success=False,
            res_stdout=res_stdout,
            res_stderr=res_stderr,
            flags=flags,
        )

    else:
        tu = conv_proto_file(str(tmp_output))
        refl[str(input)] = time.time()
        with open(conf.reflect_cache, "w") as file:
            file.write(json.dumps(refl, indent=2))

        return CollectorRunResult(
            tu,
            tmp_output,
            success=True,
            res_stdout=res_stdout,
            res_stderr=res_stderr,
            flags=flags,
        )


class CompileCommand(BaseModel):
    directory: str
    command: str
    file: str
    output: Optional[str] = None


@beartype
def read_compile_cmmands(conf: TuOptions):
    assert Path(conf.compilation_database).exists(), conf.compilation_database
    return [
        CompileCommand.model_validate(d)
        for d in json.load(open(conf.compilation_database))
    ]


@beartype
def write_run_result_information(conf: TuOptions, tu: CollectorRunResult, path: Path,
                                 commands: List[CompileCommand]):
    debug_dir = Path(conf.convert_failure_log_dir)
    # if debug_dir.exists():
    #     shutil.rmtree(str(debug_dir))

    debug_dir.mkdir(parents=True, exist_ok=True)
    sanitized = "".join([c if c.isalnum() else "_" for c in str(path)])

    if not tu.success:
        if not conf.print_reflection_run_fail_to_stdout:
            log.warning(
                f"Failed to run conversion for [green]{path}[/green], wrote to {debug_dir}/{sanitized}"
            )

    def write_reflection_fail(file: io.TextIOWrapper):
        def sep(name: str):
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
        file.write(" ^\n    ".join([conf.indexing_tool] + tu.flags))

    if conf.print_reflection_run_fail_to_stdout:
        buffer = io.StringIO()
        write_reflection_fail(buffer)
        log.error(buffer.getvalue())

    else:
        with open(debug_dir.joinpath(sanitized), "w") as file:
            write_reflection_fail(file)




@beartype
def run_collector_for_path(conf: TuOptions, mapping: PathMapping,
                           commands: List[CompileCommand]) -> Optional[TuWrap]:
    path = mapping.path
    tu: CollectorRunResult = run_collector(conf, path, path.with_suffix(".py"))
    if tu.success:
        relative = Path(conf.output_directory).joinpath(path.relative_to(mapping.root))

        if not relative.parent.exists():
            relative.parent.mkdir(parents=True)

        with open(str(relative.with_suffix(".json")), "w") as file:
            file.write(open_proto_file(str(tu.pb_path)).to_json(2))

        write_run_result_information(conf, tu, path, commands)

        return TuWrap(name=path.stem,
                      tu=tu.conv_tu,
                      original=path,
                      mapping=relative.with_suffix(".nim"))

    else:
        write_run_result_information(conf, tu, path, commands)
