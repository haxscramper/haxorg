from beartype import beartype
from beartype.typing import Any, Optional
from py_cli import haxorg_cli, haxorg_opts
from py_haxorg.exporters.export_html import ExporterHtml
import rich_click as click

CAT = "haxorg.export.html"


@beartype
def export_html(ctx: haxorg_cli.CliRunContext) -> None:
    assert ctx.opts.export
    assert ctx.opts.export.html
    assert ctx.opts.export.html.infile
    assert ctx.opts.export.html.outfile

    with ctx.event("Run html export", CAT):
        node = haxorg_cli.parseCachedFile(ctx, ctx.opts.export.html.infile)
        exp = ExporterHtml()
        document = exp.evalDocument(node)
        ctx.opts.export.html.outfile.write_text(str(document))


@click.command("html")
@haxorg_cli.get_wrap_options(haxorg_opts.ExportHtmlOptions)
@click.pass_context
def export_html_cli(ctx: click.Context, **kwargs: Any) -> None:
    export_html(haxorg_cli.get_run(ctx))
