#!/usr/bin/env python

import rich_click as click
from py_cli.haxorg_cli import (
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

from py_cli.haxorg_export import export
cli.add_command(export)

if __name__ == "__main__":
    cli()
