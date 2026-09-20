#!/usr/bin/env python

import sys

import rich_click as click
from beartype.typing import Any
from py_scriptutils.script_logging import custom_traceback_handler

from py_cli import haxorg_cli, haxorg_opts
from py_cli.export.haxorg_export import export
from py_cli.generate.haxorg_generate import generate

CAT = __name__


@click.group()
@haxorg_cli.get_wrap_options(haxorg_opts.RootOptions)
@click.pass_context
def haxorg_main_cli(ctx: click.Context, **kwargs: Any) -> None:
    sys.excepthook = custom_traceback_handler
    """Base command."""
    opts = haxorg_cli.get_opts(ctx)
    ctx.ensure_object(dict)
    ctx.obj["run"] = haxorg_cli.CliRunContext(opts)
    pass


haxorg_main_cli.add_command(export)
haxorg_main_cli.add_command(generate)

if __name__ == "__main__":
    haxorg_main_cli()
