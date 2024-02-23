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
    pass


def finalize_trace(tr: tracer.TraceCollector, opts: CliRootOptions):
    if opts.trace_path:
        tr.export_to_json(Path(opts.trace_path))
        log().info(f"Wrote execution trace to {opts.trace_path}")


class CliExportOptions(BaseModel, extra="forbid"):
    pass


def export_cli_options(f):
    return apply_options(f, options_from_model(CliExportOptions))


@click.group()
@click.pass_context
@export_cli_options
def export(ctx: click.Context, config: Optional[str] = None, **kwargs):
    """Export command group."""
    pack_context(ctx, "export", CliExportOptions, config=config, kwargs=kwargs)
    pass


cli.add_command(export)


from haxorg_export_tex import export_tex
export.add_command(export_tex)

from haxorg_export_ultraplain import export_ultraplain
export.add_command(export_ultraplain)

from haxorg_export_sqlite import export_sqlite
export.add_command(export_sqlite)

if __name__ == "__main__":
    cli()
