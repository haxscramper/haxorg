from pathlib import Path

import plumbum
import py_haxorg.pyhaxorg_wrap as org
import rich_click as click
from beartype.typing import Any
from py_cli import haxorg_cli, haxorg_opts
from py_exporters.export_typst import (ExporterTypst, refresh_typst_export_package)
from py_haxorg import pyhaxorg_utils
from py_scriptutils.script_logging import log
from beartype import beartype

CAT = "haxorg.export.typst"


@beartype
def export_typst(opts: haxorg_opts.RootOptions) -> None:
    assert opts.export
    assert opts.export.typst
    infile = opts.export.typst.infile
    outfile = opts.export.typst.outfile

    parse_opts = haxorg_cli.getParseOpts(opts, infile)
    node = haxorg_cli.parseFile(opts, Path(infile), parse_opts=parse_opts)

    typst = ExporterTypst()
    if opts.export.exportTraceFile:
        typst.enableFileTrace(str(opts.export.exportTraceFile))

    res = typst.exp.evalTop(node)
    outfile.parent.mkdir(exist_ok=True, parents=True)
    outfile.write_text(typst.t.toString(res))

    pyhaxorg_utils.doExportAttachments(
        base=infile,
        destination=outfile,
        attachments=pyhaxorg_utils.getAttachments(node),
        backends=["typst"],
    )

    if opts.export.typst.do_compile:
        refresh_typst_export_package()
        cmd = plumbum.local["typst"].with_cwd(str(infile.parent))
        pdf = outfile.with_suffix(".pdf")
        cmd.run(["compile", str(outfile), str(pdf)])
        log(CAT).info(f"Export to {pdf}")


@click.command("typst")
@haxorg_cli.get_wrap_options(haxorg_opts.TypstExportOptions)
@click.pass_context
def export_typst_cli(ctx: click.Context, **kwargs: Any) -> None:
    export_typst(haxorg_cli.get_opts(ctx))
