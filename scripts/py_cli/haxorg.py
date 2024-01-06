#!/usr/bin/env python

import rich_click as click
import click_config_file
import os
from dataclasses import dataclass

from beartype import beartype
from beartype.typing import Optional, List

import py_haxorg.pyhaxorg as org
import py_scriptutils.py_scriptutils.tracer as tracer
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import make_config_provider, run_config_provider, apply_options

CONFIG_FILE_NAME = "pyhaxorg.toml"

arg_infile = click.argument("file", nargs=-1, type=click.Path(exists=True))
arg_outfile = click.option("--out-file",
                           type=click.Path(),
                           help="Single file name for the output file")
arg_outroot = click.option("--out-root",
                           type=click.Path(),
                           help="Root output directory for exporting multiple files")


def make_trace_options(kind: str) -> List[click.option]:
    return (click.option(
        f"--{kind}.traceDir",
        f"{kind}_traceDir",
        type=click.Path(),
        default=None,
        help=f"Output directory for the {kind} trace (if not specified print to stdout)"),
            click.option(f"--{kind}.trace",
                         f"{kind}_trace",
                         type=click.BOOL,
                         default=False,
                         help=f"Whether to trace {kind} execution"))


def common_trace(f):
    return apply_options(f, [
        *make_trace_options("lex"), *make_trace_options("parse"),
        *make_trace_options("sem")
    ])


def export_trace(f):
    return apply_options(f, make_trace_options("export"))


@beartype
@dataclass(frozen=True)
class CliRootOptions:
    lex_traceDir: Optional[str]
    lex_trace: bool
    parse_traceDir: Optional[str]
    parse_trace: bool
    sem_traceDir: Optional[str]
    sem_trace: bool
    config: Optional[str]
    cache: Optional[str]
    trace_path: Optional[str]


def pack_context(ctx: click.Context, name: str, T: type):
    ctx.ensure_object(dict)
    store = {}
    for param, value in ctx.params.items():
        store[param] = value

    ctx.obj[name] = T(**store)


@click.group()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@click.option("--cache",
              type=click.Path(exists=True),
              default=None,
              help="Cache directory path")
@click.option("--trace-path",
              type=click.Path(),
              default=None,
              help="Output path for the execution trace")
@common_trace
@click_config_file.configuration_option(provider=make_config_provider("pyhaxorg.toml"),
                                        cmd_name="haxorg",
                                        config_file_name=CONFIG_FILE_NAME)
@click.pass_context
def cli(
    ctx: click.Context,
    config: str,
    cache: str,
    lex_traceDir: str,
    lex_trace: bool,
    parse_traceDir: str,
    parse_trace: bool,
    sem_traceDir: str,
    sem_trace: bool,
    trace_path: Optional[str],
) -> None:
    """Base command."""
    run_config_provider(config, "haxorg", True)
    pack_context(ctx, "cli", CliRootOptions)
    pass


def parse_input(file: List[str], opts: CliRootOptions) -> org.OrgContext:
    ctx = org.OrgContext()
    path = file[0]  # TODO support multiple files

    if opts.cache:
        if not os.path.exists(opts.cache):
            os.mkdir(opts.cache)

        cache_file = os.path.join(opts.cache, os.path.basename(path) + ".dat")

        if os.path.exists(cache_file) and os.path.getmtime(path) <= os.path.getmtime(
                cache_file):
            log().info(
                f"Found an up-to-date cache file at {cache_file}, using it to parse {path}"
            )
            ctx.loadStore(cache_file)

        else:
            log().info(f"No up-to-date cache file at {cache_file}, parsing new {path}")
            ctx.parseFile(path)
            ctx.writeStore(cache_file)

    else:
        log().info(f"Parsing {path}, no cache dir specified")
        ctx.parseFile(path)

    return ctx


def finalize_trace(tr: tracer.TraceCollector, opts: CliRootOptions):
    if opts.trace_path:
        tr.export_to_json(opts.trace_path)
        log().info(f"Wrote execution trace to {opts.trace_path}")


@beartype
@dataclass(frozen=True)
class CliExportOptions:
    pass


@click.group()
@click.pass_context
def export(ctx):
    """Export command group."""
    pack_context(ctx, "export", CliExportOptions)
    pass


cli.add_command(export)


@click.command("tex")
@arg_infile
@arg_outfile
@arg_outroot
@export_trace
@click.option("--backend", default="pdflatex", help="TeX backend to use.")
@click.pass_context
def export_tex(
    ctx: click.Context,
    file: List[str],
    backend: str,
    out_file: str,
    out_root: str,
    export_trace: bool,
    export_traceDir: str,
):
    """Export"""
    ctx = parse_input(file, ctx.obj["cli"])
    from py_exporters.export_tex import ExporterLatex
    from py_textlayout.py_textlayout import TextOptions

    log().info("Exporting to latex")
    tex = ExporterLatex()
    res = tex.exp.evalTop(ctx.getNode())
    with open(out_file, "w") as out:
        out.write(tex.t.toString(res, TextOptions()))

    log().info(f"Wrote latex export to {out_file}")


export.add_command(export_tex)


@click.command("sem-tree")
@arg_infile
@arg_outfile
@arg_outroot
@export_trace
@click.pass_context
def export_sem_tree(ctx: click.Context, file: List[str], out_file: str, out_root: str,
                    export_trace: bool, export_traceDir: str):
    """Export files as sem tree dump"""
    ctx = parse_input(file, ctx.obj["cli"])
    sem = org.OrgExporterTree()
    opts = org.ExporterTreeOpts()
    opts.withColor = False
    sem.toFile(ctx.getNode(), out_file, opts)
    log().info(f"Wrote sem tree export to {out_file}")


export.add_command(export_sem_tree)


@click.command("json")
@arg_infile
@arg_outfile
@arg_outroot
@export_trace
@click.pass_context
def export_json(ctx: click.Context, file: List[str], out_file: str, out_root: str,
                export_trace: bool, export_traceDir: str):
    """Export files as sem tree dump"""
    ctx = parse_input(file, ctx.obj["cli"])
    sem = org.OrgExporterJson()
    sem.visitNode(ctx.getNode())
    sem.exportToFile(out_file)
    log().info(f"Wrote json export to {out_file}")


export.add_command(export_json)


@click.command("yaml")
@arg_infile
@arg_outfile
@arg_outroot
@export_trace
@click.pass_context
def export_yaml(ctx: click.Context, file: List[str], out_file: str, out_root: str,
                export_trace: bool, export_traceDir: str):
    """Export files as sem tree dump"""
    tra = tracer.TraceCollector()
    with tra.complete_event("parse input"):
        org_ctx = parse_input(file, ctx.obj["cli"])

    sem = org.OrgExporterYaml()
    with tra.complete_event("visit node for yaml export"):
        sem.visitNode(org_ctx.getNode())

    with tra.complete_event("export yaml to file"):
        sem.exportToFile(out_file)

    log().info(f"Wrote yaml export to {out_file}")
    finalize_trace(tra, ctx.obj["cli"])


export.add_command(export_yaml)


@click.command("activity-timeline")
@arg_infile
@arg_outfile
@arg_outroot
@export_trace
@click.pass_context
def export_yaml(ctx: click.Context, file: List[str], out_file: str, out_root: str,
                export_trace: bool, export_traceDir: str):
    """Export files as sem tree dump"""
    tra = tracer.TraceCollector()
    with tra.complete_event("parse input"):
        org_ctx = parse_input(file, ctx.obj["cli"])

    from py_exporters.export_timeline import ExporterTimeline
    exp = ExporterTimeline()
    with tra.complete_event("visit toplevel"):
        exp.evalTop(org_ctx.getNode())

    print(exp.count)

    log().info(f"Wrote yaml export to {out_file}")
    finalize_trace(tra, ctx.obj["cli"])


export.add_command(export_yaml)

if __name__ == "__main__":
    cli()
