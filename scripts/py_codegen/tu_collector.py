#!/usr/bin/env python

import json
import time
from copy import deepcopy
from dataclasses import dataclass, field
from hashlib import md5
from pathlib import Path
from pprint import pformat, pprint
from typing import TYPE_CHECKING

import py_scriptutils.toml_config_profiler as conf_provider
import rich_click as click
from beartype import beartype
from beartype.typing import (Any, Dict, List, NewType, Optional, Set, Tuple, TypeAlias,
                             Union, cast)
from plumbum import local
from py_scriptutils.files import IsNewInput
from py_scriptutils.script_logging import log
from py_scriptutils.tracer import GlobCompleteEvent, GlobExportJson
from pydantic import BaseModel, Field

import wrapper_gen_nim as gen_nim
from gen_tu_cpp import QualType
from refl_read import ConvTu, conv_proto_file, open_proto_file
from wrapper_graph import GenGraph, TuWrap

CONFIG_FILE_NAME = "tu_collector.toml"

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
    directory_root: Optional[str] = Field(description="Root of the source header directory", 
        default=None)
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


@beartype
@dataclass
class PathMapping:
    path: Path
    root: Path


@beartype
def expand_input(input: List[str], path_suffixes: List[str],
                 directory_root: Optional[Path]) -> List[PathMapping]:
    result: List[PathMapping] = []
    for item in input:
        path = Path(item)
        if path.is_file():
            result.append(PathMapping(path, directory_root))

        elif path.is_dir():
            for sub in path.rglob("*"):
                if sub.suffix in path_suffixes:
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


def model_options(f):
    return conf_provider.apply_options(f, conf_provider.options_from_model(TuOptions))


class CompileCommand(BaseModel):
    directory: str
    command: str
    file: str
    output: Optional[str] = None


@beartype
def write_run_result_information(conf: TuOptions, tu: CollectorRunResult, path: Path,
                                 commands: List[CompileCommand]):
    debug_dir = Path(conf.convert_failure_log_dir)
    # if debug_dir.exists():
    #     shutil.rmtree(str(debug_dir))

    debug_dir.mkdir(parents=True, exist_ok=True)
    sanitized = "".join([c if c.isalnum() else "_" for c in str(path)])

    if not tu.success:
        log.warning(
            f"Failed to run conversion for [green]{path}[/green], wrote to {debug_dir}/{sanitized}"
        )

    with open(debug_dir.joinpath(sanitized), "w") as file:

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


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@model_options
@click.pass_context
def run(ctx: click.Context, config: str, **kwargs):
    config_base = conf_provider.run_config_provider(
        ([config] if config else
         conf_provider.find_default_search_locations(CONFIG_FILE_NAME)), True)
    conf: TuOptions = cast(
        TuOptions, conf_provider.merge_cli_model(ctx, config_base, kwargs, TuOptions))

    paths: List[PathMapping] = expand_input(conf.input, conf.path_suffixes,
                                            conf.directory_root and Path(conf.directory_root))  # [:10]
    wraps: List[TuWrap] = []

    with GlobCompleteEvent("Load compilation database", "config"):
        commands: List[CompileCommand] = [
            CompileCommand.model_validate(d)
            for d in json.load(open(conf.compilation_database))
        ]

    out_map: Dict[Path, Path] = {}

    with GlobCompleteEvent("Run reflection collector", "read"):
        mapping: PathMapping
        for mapping in paths:
            if any([cmd.file == str(mapping.path) for cmd in commands]):
                with GlobCompleteEvent("Run collector", "read",
                                       {"path": str(mapping.path)}):
                    wrap = run_collector_for_path(conf, mapping, commands)
                    if wrap:
                        wraps.append(wrap)
                        out_map[wrap.original] = wrap.mapping

            else:
                log.warning(f"No compile commands for {mapping.path}")

    with GlobCompleteEvent("Merge graph information", "build"):
        graph: GenGraph = GenGraph()
        for wrap in wraps:
            graph.add_unit(wrap)

        log.info("Finished conversion")

    with GlobCompleteEvent("Build graph edges", "build"):
        graph.connect_usages()

    with GlobCompleteEvent("Group connected files", "build"):
        graph.group_connected_files()

    with GlobCompleteEvent("Generate graphviz image", "write"):
        graph.to_graphviz("/tmp/output.dot", drop_zero_degree=True)
        graph.to_csv("/tmp/nodes.csv", "/tmp/edges.csv")

    graph.graph.write_graphml("/tmp/output.graphml")

    def get_out_path(path: Path):
        return out_map[path]

    with GlobCompleteEvent("Write wrapper output", "write"):
        for sub in graph.subgraphs:
            with GlobCompleteEvent("Single file wrap", "write",
                                   {"original": str(sub.original)}):
                code: Optional[str] = gen_nim.to_nim(graph=graph,
                                                     sub=sub,
                                                     conf=conf.nim,
                                                     get_out_path=get_out_path,
                                                     output_directory=Path(
                                                         conf.output_directory))

                if code:
                    result = get_out_path(sub.original)
                    with open(str(result), "w") as file:
                        file.write(code)

                else:
                    log.warning(f"No declarations found for {sub.original}")

    with GlobCompleteEvent("Write translation unit information", "write"):
        for sub in graph.subgraphs:
            with GlobCompleteEvent("Write subgraph information", "write",
                                   {"original": str(sub.original)}):
                with GlobCompleteEvent("Collect declaration info", "write"):
                    info = graph.to_decl_info(sub)

                result = get_out_path(sub.original)
                result = result.with_stem(result.stem + "-tu").with_suffix(".json")

                with GlobCompleteEvent("Write JSON information for file", "write"):
                    with open(str(result), "w") as file:
                        file.write(json.dumps(info.model_dump(), indent=2))

    GlobExportJson(conf.execution_trace)
    log.info("Done all")


if __name__ == "__main__":
    run()
