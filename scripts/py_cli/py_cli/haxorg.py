#!/usr/bin/env python

import rich_click as click
from beartype import beartype
from beartype.typing import Any, Optional
from py_cli import haxorg_cli, haxorg_opts
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import DefaultWrapperValue

CAT = __name__


@beartype
def base_cli_options(f: Any) -> Any:
    return haxorg_cli.apply_options(
        f, haxorg_cli.options_from_model(haxorg_opts.RootOptions))


@click.group()
@base_cli_options
@click.pass_context
def haxorg_main_cli(ctx: click.Context, **kwargs: Any) -> None:
    """Base command."""
    log(CAT).info("haxorg")
    opts = haxorg_cli.get_opts(ctx)
    ctx.ensure_object(dict)
    ctx.obj["run"] = haxorg_cli.CliRunContext(opts)
    pass


from py_cli.export.haxorg_export import export
from py_cli.generate.haxorg_generate import generate

haxorg_main_cli.add_command(export)
haxorg_main_cli.add_command(generate)

if __name__ == "__main__":
    haxorg_main_cli()
