import json

from beartype import beartype
from beartype.typing import Any
from beartype.typing import Optional
from py_cli import haxorg_cli
from py_cli import haxorg_opts
from py_exporters.export_pandoc import ExporterPandoc
import py_haxorg.pyhaxorg_wrap as org
import rich_click as click

CAT = "haxorg.export.pandoc"


@beartype
def export_pandoc(ctx: haxorg_cli.CliRunContext) -> None:
    assert ctx.opts.export
    assert ctx.opts.export.pandoc
    assert ctx.opts.export.pandoc.infile
    assert ctx.opts.export.pandoc.outfile

    with ctx.event("Run pandoc export", CAT):
        node = haxorg_cli.parseCachedFile(ctx, ctx.opts.export.pandoc.infile)

        if ctx.opts.export.pandoc.debug_tree:
            org.exportToTreeFile(node, str(ctx.opts.export.pandoc.debug_tree),
                                 org.OrgTreeExportOpts(withColor=False))

        exp = ExporterPandoc()
        if ctx.opts.export.exportTraceFile:
            exp.enableFileTrace(ctx.opts.export.exportTraceFile)

        document = exp.evalTop(node).toJson()[0]
        ctx.opts.export.pandoc.outfile.write_text(json.dumps(document, indent=2))


@click.command("pandoc")
@haxorg_cli.get_wrap_options(haxorg_opts.ExportPandocOptions)
@click.pass_context
def export_pandoc_cli(ctx: click.Context, **kwargs: Any) -> None:
    export_pandoc(haxorg_cli.get_run(ctx))
