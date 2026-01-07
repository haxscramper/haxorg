from py_exporters.export_html import ExporterHtml
from py_cli import haxorg_cli, haxorg_opts
from beartype.typing import Any, Optional
import rich_click as click

CAT = "haxorg.export.html"


@click.command("html")
@haxorg_cli.get_wrap_options(haxorg_opts.ExportHtmlOptions)
@click.pass_context
def export_html(ctx: click.Context, **kwargs: Any) -> None:
    opts = haxorg_cli.get_opts(ctx)
    run = haxorg_cli.get_run(ctx)
    assert opts.export
    assert opts.export.html
    assert opts.export.html.infile
    assert opts.export.html.outfile

    with run.event("Run html export", CAT):
        node = haxorg_cli.parseCachedFile(opts.export.html.infile, opts.cache)
        exp = ExporterHtml()
        document = exp.evalDocument(node)
        opts.export.html.outfile.write_text(str(document))

    run.finalize()
