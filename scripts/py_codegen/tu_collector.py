#!/usr/bin/env python

from beartype import beartype
from beartype.typing import List, cast, Any, Tuple
from pydantic import BaseModel, Field
from pprint import pprint
from plumbum import local
from hashlib import md5
import json
import os
from pathlib import Path

from py_scriptutils.script_logging import log
import py_scriptutils.toml_config_profiler as conf_provider
from refl_read import conv_proto_file

import rich_click as click

CONFIG_FILE_NAME = "tu_collector.toml"


class TuOptions(BaseModel):
    input: List[str] = Field(description="List of input files, directories or globs")
    indexing_tool: str = Field(description="Path to the TU index generator tool")
    compilation_database: str = Field(description="Path to the compilation database")
    binary_tmp: str = Field(description="Path to store temporary binary artifacts",
                            default="/tmp/tu_collector")
    toolchain_include: str = Field(
        description="Path to the toolchain that was used to compile indexing tool")
    path_suffixes: List[str] = Field(
        description="List of file suffixes used for dir list filtering",
        default=[".hpp", ".cpp", ".h", ".c", ".cxx"],
        alias="path-suffixes")


@beartype
def expand_input(input: List[str], path_suffixes: List[str]) -> List[Path]:
    result: List[str] = []
    for item in input:
        path = Path(item)
        if path.is_file():
            result.append(item)

        elif path.is_dir():
            for sub in path.rglob("*"):
                if sub.suffix in path_suffixes:
                    result.append(sub)

        else:
            for sub in Path().glob(item):
                result.append(sub)

    return result


@beartype
def run_collector(conf: TuOptions, input: Path, output: Path):
    assert input.exists()
    if not output.parent.exists():
        output.parent.mkdir(parents=True)

    tmp = Path(conf.binary_tmp)
    if not tmp.exists():
        tmp.mkdir(parents=True)

    tool = local[conf.indexing_tool]

    tmp_output = tmp.joinpath(md5(str(output).encode("utf-8")).hexdigest() + ".pb")
    target_files = tmp_output.with_suffix(".json")
    with open(str(target_files), "w") as file:
        file.write(json.dumps([str(input)], indent=2))

    res_code, res_stdout, res_stderr = cast(
        Tuple[int, str, str],
        tool.run((
            f"-p={conf.compilation_database}",
            f"--compilation-database={conf.compilation_database}",
            f"--out={str(tmp_output)}",
            f"--toolchain-include={conf.toolchain_include}",
            f"--target-files={target_files}",
            str(input),
        ),
                 retcode=None))

    if res_code != 0:
        if res_stdout:
            log.error(res_stdout)

        if res_stderr:
            log.error(res_stderr)

    else:
        tu = conv_proto_file(str(tmp_output))
        with open(output, "w") as file:
            pprint(tu, width=200, stream=file)

        log.info(f"Converted TU file to {output}")


def model_options(f):
    return conf_provider.apply_options(f, conf_provider.options_from_model(TuOptions))


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
    conf: TuOptions = cast(TuOptions,
                           conf_provider.merge_cli_model(ctx, config_base, TuOptions))

    paths: List[Path] = expand_input(conf.input, conf.path_suffixes)
    for path in paths[:2]:
        run_collector(conf, path, path.with_suffix(".py"))


if __name__ == "__main__":
    run()
