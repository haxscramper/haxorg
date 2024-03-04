#!/usr/bin/env python 

from py_cli.haxorg_cli import (
    pack_context, 
    BaseModel,
)

from py_scriptutils.toml_config_profiler import (
    make_config_provider,
    run_config_provider,
    apply_options,
    options_from_model,
    merge_cli_model,
)

from py_exporters.export_html import ExporterHtml

import py_haxorg.pyhaxorg_wrap as org

from pathlib import Path

class StoryGridOpts(BaseModel, extra="forbid"):
    infile: Path
    outfile: Path

import rich_click as click

def cli_options(f):
    return apply_options(f, options_from_model(StoryGridOpts))

@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@cli_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", StoryGridOpts, config=config, kwargs=kwargs)
    opts: StoryGridOpts = ctx.obj["root"]
    ctx = org.OrgContext()
    node = ctx.parseFile(str(opts.infile.resolve()))

if __name__ == "__main__":
    cli()
