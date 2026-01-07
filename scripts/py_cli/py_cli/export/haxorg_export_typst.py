from beartype.typing import Any, Optional
from py_cli import haxorg_cli, haxorg_opts
import plumbum
import py_haxorg.pyhaxorg_wrap as org
from py_haxorg import pyhaxorg_utils
import rich_click as click
from pathlib import Path
from py_scriptutils.script_logging import log

CAT = "haxorg.export.typst"


def export_typst_options(f: Any) -> Any:
    return haxorg_cli.apply_options(
        f, haxorg_cli.options_from_model(haxorg_opts.TypstExportOptions))


from py_exporters.export_typst import ExporterTypst, refresh_typst_export_package
from py_textlayout.py_textlayout_wrap import BlockId, TextOptions


@click.command("typst")
@export_typst_options
@click.pass_context
def export_typst(ctx: click.Context, **kwargs: Any) -> None:
    opts = haxorg_cli.get_opts(ctx)
    assert opts.export
    assert opts.export.typst
    infile = opts.export.typst.infile
    outfile = opts.export.typst.outfile

    parse_opts = haxorg_cli.getParseOpts(opts, infile)
    node = haxorg_cli.parseFile(ctx.obj["root"], Path(infile), parse_opts=parse_opts)

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
