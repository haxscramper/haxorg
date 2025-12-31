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
    trace_dir: Optional[str] = Field(
        description="Write processing logs to the directory",
        default=None,
    )

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


def export_typst_options(f: Any) -> Any:
    return apply_options(f, options_from_model(TypstExportOptions))


from py_exporters.export_typst import ExporterTypst, refresh_typst_export_package
from py_textlayout.py_textlayout_wrap import BlockId, TextOptions


@click.command("typst")
@export_typst_options
@click.pass_context
def export_typst(ctx: click.Context, config: Optional[str] = None, **kwargs: Any) -> None:
    pack_context(ctx, "typst", TypstExportOptions, config=config, kwargs=kwargs)
    opts: TypstExportOptions = ctx.obj["typst"]
    parse_opts = org.OrgParseParameters()
    if opts.trace_dir:
        dir = Path(opts.trace_dir)
        parse_opts.parseTracePath = str(dir.joinpath("parse_trace.log"))
        parse_opts.semTracePath = str(dir.joinpath("sem_trace.log"))
        parse_opts.baseTokenTracePath = str(dir.joinpath("base_token.log"))
        parse_opts.tokenTracePath = str(dir.joinpath("token_trace.log"))
    node = parseFile(ctx.obj["root"], Path(opts.infile), parse_opts=parse_opts)

    if opts.trace_dir:
        Path(opts.trace_dir).joinpath("node.yaml").write_text(
            org.exportToYamlString(node, org.OrgYamlExportOpts()))

    typst = ExporterTypst()
    # typst.exp.enableFileTrace("/tmp/trace.txt", False)
    if opts.exportTraceFile:
        log(CAT).debug(f"Enabled export file trace to {opts.exportTraceFile}")
        typst.exp.enableFileTrace(opts.exportTraceFile, True)

    res = typst.exp.evalTop(node)
    opts.outfile.parent.mkdir(exist_ok=True, parents=True)
    with open(opts.outfile, "w") as out:
        if False:
            out.write(typst.t.toTreeRepr(res))

        else:
            out.write(typst.t.toString(res))

    pyhaxorg_utils.doExportAttachments(
        base=opts.infile,
        destination=opts.outfile.parent,
        attachments=pyhaxorg_utils.getAttachments(node),
        backends=["typst"],
    )

    if opts.do_compile:
        refresh_typst_export_package()
        cmd = local["typst"].with_cwd(str(opts.infile.parent))
        pdf = opts.outfile.with_suffix(".pdf")
        cmd.run(["compile", str(opts.outfile), str(pdf)])
        log(CAT).info(f"Export to {pdf}")
