from beartype.typing import List
from py_cli.haxorg_cli import *
from plumbum import local, FG, ProcessExecutionError, colors
import re
import py_haxorg.pyhaxorg_wrap as org
from py_haxorg import pyhaxorg_utils
import itertools


class TypstExportOptions(BaseModel, extra="forbid"):
    infile: Path
    outfile: Path
    do_compile: bool = Field(
        description="Compile the typst document if the export was successful",
        default=True)

    backend: str = Field(
        description="TeX backend to use",
        default="pdflatypst",
    )

    exportTraceFile: Optional[str] = Field(
        description="Write python export trace to this file",
        default=None,
        alias="export_trace_file")


CAT = "haxorg.export.typst"


def export_typst_options(f):
    return apply_options(f, options_from_model(TypstExportOptions))


from py_exporters.export_typst import ExporterTypst, refresh_typst_export_package
from py_textlayout.py_textlayout_wrap import BlockId, TextOptions


@click.command("typst")
@export_typst_options
@click.pass_context
def export_typst(ctx: click.Context, config: Optional[str] = None, **kwargs):
    pack_context(ctx, "typst", TypstExportOptions, config=config, kwargs=kwargs)
    opts: TypstExportOptions = ctx.obj["typst"]
    node = parseFile(ctx.obj["root"], Path(opts.infile))

    typst = ExporterTypst()
    # typst.exp.enableFileTrace("/tmp/trace.txt", False)
    if opts.exportTraceFile:
        log(CAT).debug(f"Enabled export file trace to {opts.exportTraceFile}")
        typst.exp.enableFileTrace(opts.exportTraceFile, True)

    res = typst.exp.evalTop(node)
    with open(opts.outfile, "w") as out:
        if False:
            out.write(typst.t.toTreeRepr(res))

        else:
            out.write(typst.t.toString(res, TextOptions()))

    pyhaxorg_utils.doExportAttachments(
        base=opts.infile,
        destination=opts.outfile.parent,
        attachments=pyhaxorg_utils.getAttachments(node),
    )

    if opts.do_compile:
        refresh_typst_export_package()
        cmd = local["typst"].with_cwd(str(opts.infile.parent))
        pdf = opts.outfile.with_suffix(".pdf")
        cmd.run(["compile", str(opts.outfile), str(pdf)])
        log(CAT).info(f"Export to {pdf}")
