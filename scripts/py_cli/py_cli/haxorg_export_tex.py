from py_cli.haxorg_cli import *
from plumbum import local, FG, ProcessExecutionError, colors
import re

class TexExportOptions(BaseModel, extra="forbid"):
    infile: Path
    outfile: Path
    do_compile: bool = Field(
        description="Compile the tex document if the export was successful",
        default=True
    )

    backend: str = Field(
        description="TeX backend to use",
        default="pdflatex",
    )

    exportTraceFile: Optional[str] = Field(
        description="Write python export trace to this file",
        default=None,
        alias="export_trace_file")

CAT = "haxorg.export.tex"

def export_tex_options(f):
    return apply_options(f, options_from_model(TexExportOptions))


def run_lualatex(filename: Path):
    lualatex = local["lualatex"].with_cwd(str(filename.parent))
    code, stdout, stderr = lualatex.run(("-interaction=nonstopmode", filename), retcode=None)

    log_file = filename.with_suffix(".log")

    with log_file.open('r', encoding='utf-8') as f:
        log_content = f.read()

    error_patterns = [
        r"^!(.*?)\nerror\)",  # TeX errors
        r"^Emergency stop",    # Emergency stop
        r"^No pages?.*?output",  # No output produced
    ]
    has_errors = any(re.search(pattern, log_content, re.MULTILINE | re.DOTALL) for pattern in error_patterns)

    if has_errors:
        log(CAT).error(f"Error during compilation of {filename}:\n{log_content}")
    else:
        log(CAT).info(f"Compilation of {filename} successful!")


@click.command("tex")
@export_tex_options
@click.pass_context
def export_tex(ctx: click.Context, config: Optional[str] = None, **kwargs):
    pack_context(ctx, "tex", TexExportOptions, config=config, kwargs=kwargs)
    opts: TexExportOptions = ctx.obj["tex"]
    node = parseFile(ctx.obj["root"], opts.infile)
    from py_exporters.export_tex import ExporterLatex
    from py_textlayout.py_textlayout_wrap import TextOptions

    log(CAT).info("Exporting to latex")
    tex = ExporterLatex()
    if opts.exportTraceFile:
        log(CAT).debug(f"Enabled export file trace to {opts.exportTraceFile}")
        tex.exp.enableFileTrace(opts.exportTraceFile, True)

    res = tex.exp.evalTop(node)
    with open(opts.outfile, "w") as out:
        out.write(tex.t.toString(res, TextOptions()))

    log(CAT).info(f"Wrote latex export to {opts.outfile}")
    if opts.do_compile:
        run_lualatex(opts.outfile)
