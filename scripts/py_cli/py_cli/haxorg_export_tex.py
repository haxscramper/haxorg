from haxorg_cli import *

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
        alias="export_trace_file")


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
