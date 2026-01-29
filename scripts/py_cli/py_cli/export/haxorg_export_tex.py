import itertools
from pathlib import Path

import plumbum
import py_haxorg.pyhaxorg_wrap as org
import rich_click as click
from beartype import beartype
from beartype.typing import Any, List, Optional
from py_cli import haxorg_cli, haxorg_opts
from py_exporters.export_utils.texoutparse import LatexLogParser
from py_scriptutils.script_logging import log

CAT = "haxorg.export.tex"


def run_lualatex(filename: Path) -> None:
    lualatex = plumbum.local["lualatex"].with_cwd(str(filename.parent))
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

    def __init__(self) -> None:
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


@beartype
def export_tex(ctx: haxorg_cli.CliRunContext) -> None:
    opts = ctx.opts
    assert opts.export
    assert opts.export.tex
    node = haxorg_cli.parseFile(ctx, opts.export.tex.infile)

    tex = DerivedLatexExporter()
    # tex.exp.enableFileTrace("/tmp/trace.txt", False)
    if opts.export.exportTraceFile:
        log(CAT).debug(f"Enabled export file trace to {opts.export.exportTraceFile}")
        tex.exp.enableFileTrace(opts.export.exportTraceFile, True)

    res = tex.exp.evalTop(node)
    opts.export.tex.outfile.write_text(tex.t.toString(res, TextOptions()))

    if opts.export.tex.do_compile:
        run_lualatex(opts.export.tex.outfile)


@click.command("tex")
@haxorg_cli.get_wrap_options(haxorg_opts.TexExportOptions)
@click.pass_context
def export_tex_cli(ctx: click.Context, **kwargs: Any) -> None:
    export_tex(haxorg_cli.get_run(ctx))
