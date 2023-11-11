#!/usr/bin/env python

from beartype import beartype
from beartype.typing import List, Dict, get_args, get_origin, cast, Any
from pydantic import BaseModel, Field
from pprint import pprint
import plumbum
import json
import os
from pathlib import Path

from py_scriptutils.script_logging import log
import py_scriptutils.toml_config_profiler as conf_provider

import rich_click as click

CONFIG_FILE_NAME = "tu_collector.toml"


class TuOptions(BaseModel):
    input: List[str] = Field(description="List of input files, directories or globs")
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


if __name__ == "__main__":
    run()
