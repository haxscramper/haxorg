from beartype.typing import List
from py_cli.haxorg_cli import *
from plumbum import local, FG, ProcessExecutionError, colors
import re
import py_haxorg.pyhaxorg_wrap as org
from py_exporters.export_utils.texoutparse import LatexLogParser
import itertools


class TexExportOptions(BaseModel, extra="forbid"):
    infile: Path
    outfile: Path
    do_compile: bool = Field(
        description="Compile the tex document if the export was successful", default=True)

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
    code, stdout, stderr = lualatex.run(("-interaction=nonstopmode", filename),
                                        retcode=None)

    log_file = filename.with_suffix(".log")

    parser = LatexLogParser()
    with log_file.open('r', encoding='utf-8') as f:
        parser.process(f)

    if parser.errors:
        log(CAT).error(f"Error during compilation of {filename}")
        sorted_errors = itertools.groupby(
            iterable=sorted(parser.errors, key=lambda it: it.type_),
            key=lambda it: it.type_,
        )

        for key, group in sorted_errors:
            log(CAT).error(repr([it for it in group][0]))

    else:
        log(CAT).info(f"Compilation of {filename} successful!")


from py_exporters.export_tex import ExporterLatex
from py_textlayout.py_textlayout_wrap import BlockId, TextOptions


class DerivedLatexExporter(ExporterLatex):

    def __init__(self):
        super().__init__(self)
        self.paragraphCount = 0

    def evalParagraph(self, node: org.Paragraph) -> BlockId:
        self.paragraphCount += 1
        return self.t.line([
            self.string("\\orgLocation{{p{}{}}} ".format(
                self.paragraphCount,
                ":" + str(node.loc.line) if node.loc else "",
            )),
            super().evalParagraph(node),
        ])

    def getDocumentStart(self, node: org.Document) -> List[BlockId]:
        return [
            *super().getDocumentStart(node),
            self.string(r"""
\newcommand*\sepline{%
  \begin{center}
    \rule[1ex]{\textwidth}{1pt}
  \end{center}}

\newcommand{\quot}[1]{\textcolor{brown}{#1}}
\newcommand{\orgLocation}[1]{\fbox{\textbf{#1}}}                        
        """)
        ]


@click.command("tex")
@export_tex_options
@click.pass_context
def export_tex(ctx: click.Context, config: Optional[str] = None, **kwargs):
    pack_context(ctx, "tex", TexExportOptions, config=config, kwargs=kwargs)
    opts: TexExportOptions = ctx.obj["tex"]
    node = parseFile(ctx.obj["root"], Path(opts.infile))

    tex = DerivedLatexExporter()
    # tex.exp.enableFileTrace("/tmp/trace.txt", False)
    if opts.exportTraceFile:
        log(CAT).debug(f"Enabled export file trace to {opts.exportTraceFile}")
        tex.exp.enableFileTrace(opts.exportTraceFile, True)

    res = tex.exp.evalTop(node)
    with open(opts.outfile, "w") as out:
        out.write(tex.t.toString(res, TextOptions()))

    if opts.do_compile:
        run_lualatex(opts.outfile)
