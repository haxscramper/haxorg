#!/usr/bin/env python

import rich_click as click
import click_config_file
import os
from dataclasses import dataclass

from beartype import beartype
from beartype.typing import Optional, List

import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils import tracer
from pydantic import BaseModel, Field, Extra
from py_scriptutils.script_logging import log
from py_scriptutils.files import FileOperation
from pathlib import Path
from py_scriptutils.toml_config_profiler import (
    make_config_provider,
    run_config_provider,
    apply_options,
    options_from_model,
    merge_cli_model,
)

CONFIG_FILE_NAME = "pyhaxorg.toml"


class CliRootOptions(BaseModel, extra="forbid"):
    lex_traceDir: Optional[str] = None
    lex_trace: bool = False
    parse_traceDir: Optional[str] = None
    parse_trace: bool = False
    sem_traceDir: Optional[str] = None
    sem_trace: bool = False
    config: Optional[str] = None
    cache: Optional[str] = Field(
        description="Optional directory to cache file parsing to speed up large corpus processing",
        default=None,
    )

    trace_path: Optional[str] = None

@beartype
def parseFile(root: CliRootOptions, file: Path) -> org.Org:
    cache_file = None if not root.cache else Path(root.cache).joinpath(file.name)
    ctx = org.OrgContext()
    if cache_file:
        with FileOperation.InOut([file], [cache_file]) as op:
            if op.should_run():
                log("haxorg.cache").info(f"{file} cached in {cache_file}")
                node = ctx.parseFile(str(file.resolve()))
                if not cache_file.parent.exists():
                    cache_file.parent.mkdir()

                ctx.saveProtobuf(node, str(cache_file))

            else:
                log("haxorg.cache").info(f"{file} read from cache {cache_file}")
                node = ctx.parseProtobuf(str(cache_file))

            return node

    else:
        return ctx.parseFile(str(file.resolve()))



def pack_context(ctx: click.Context, name: str, T: type, kwargs: dict, config: Optional[str]):
    """
    Convert the provided CLI parameters into the object of type `T` for
    more typesafe usage
    """
    config_base = run_config_provider(
        ([str(Path(config).resolve())] if config else []), True) if config else {}
    conf = merge_cli_model(ctx, config_base, kwargs, T)
    ctx.ensure_object(dict)
    ctx.obj[name] = conf


def base_cli_options(f):
    return apply_options(f, options_from_model(CliRootOptions))


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


class TexExportOptions(BaseModel, extra="forbid"):
    infile: Path
    outfile: Path
    backend: str = Field(
        description="TeX backend to use",
        default="pdflatex",
    )

    exportTraceFile: Optional[str] = Field(
        description="Write python export trace to this file",
        default=None,
        alias="export_trace_file"
    )


def export_tex_options(f):
    return apply_options(f, options_from_model(TexExportOptions))


@click.command("tex")
@export_tex_options
@click.pass_context
def export_tex(ctx: click.Context, config: Optional[str] = None, **kwargs):
    pack_context(ctx, "tex", TexExportOptions, config=config, kwargs=kwargs)
    opts: TexExportOptions = ctx.obj["tex"]
    node = parseFile(ctx.obj["root"], opts.infile)
    from py_exporters.export_tex import ExporterLatex
    from py_textlayout.py_textlayout_wrap import TextOptions

    tree = org.OrgExporterTree()
    tree_opts = org.ExporterTreeOpts()
    tree_opts.withColor = False
    tree.toFile(node, "/tmp/tex_tree.txt", tree_opts)

    log().info("Exporting to latex")
    tex = ExporterLatex()
    if opts.exportTraceFile:
        log("haxorg.cli").debug(f"Enabled export file trace to {opts.exportTraceFile}")
        tex.exp.enableFileTrace(opts.exportTraceFile, True)

    res = tex.exp.evalTop(node)
    with open(opts.outfile, "w") as out:
        out.write(tex.t.toString(res, TextOptions()))

    log("haxorg.cli").info(f"Wrote latex export to {opts.outfile}")


export.add_command(export_tex)

if __name__ == "__main__":
    cli()
