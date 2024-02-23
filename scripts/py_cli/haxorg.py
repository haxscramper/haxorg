#!/usr/bin/env python

import rich_click as click
import click_config_file
import os
from dataclasses import dataclass

from beartype import beartype
from beartype.typing import Optional, List, Tuple
from py_scriptutils import tracer

from py_scriptutils.script_logging import log
from pathlib import Path
from haxorg_cli import (
    BaseModel,
    apply_options,
    options_from_model,
    pack_context,
    base_cli_options,
    CliRootOptions,
    CliRunContext,
)


@click.group()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@base_cli_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    """Base command."""
    pack_context(ctx, "root", CliRootOptions, config=config, kwargs=kwargs)
    opts = ctx.obj["root"]
    ctx.ensure_object(dict)
    ctx.obj["run"] = CliRunContext(opts)
    pass

from haxorg_export import export
cli.add_command(export)

if __name__ == "__main__":
    cli()
