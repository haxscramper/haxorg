#!/usr/bin/env python

import rich_click as click
from beartype.typing import Any, Optional
from py_cli.haxorg_cli import (
    pack_context,
    base_cli_options,
    CliRootOptions,
    CliRunContext,
)


@click.group()
@base_cli_options
@click.pass_context
def cli(ctx: click.Context, config: Optional[str], **kwargs: Any) -> None:
    """Base command."""
    pack_context(ctx, "root", CliRootOptions, config=config, kwargs=kwargs)
    opts = ctx.obj["root"]
    ctx.ensure_object(dict)
    ctx.obj["run"] = CliRunContext(opts)
    pass


from py_cli.haxorg_export import export
from py_cli.haxorg_generate import generate

cli.add_command(export)
cli.add_command(generate)

if __name__ == "__main__":
    cli()
