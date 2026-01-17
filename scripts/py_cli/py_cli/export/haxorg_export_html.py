from py_exporters.export_html import ExporterHtml
from py_cli import haxorg_cli, haxorg_opts
from beartype.typing import Any, Optional
import rich_click as click
from beartype import beartype

CAT = "haxorg.export.html"


@beartype
def export_html(opts: haxorg_opts.RootOptions,
                run: Optional[haxorg_cli.CliRunContext] = None) -> None:
    assert opts.export
    assert opts.export.html
    assert opts.export.html.infile
    assert opts.export.html.outfile

    if not run:
        run = haxorg_cli.get_run(opts) # type: ignore

    with run.event("Run html export", CAT):
        node = haxorg_cli.parseCachedFile(opts, opts.export.html.infile)
        exp = ExporterHtml()
        document = exp.evalDocument(node)
        opts.export.html.outfile.write_text(str(document))

    run.finalize()


@click.command("html")
@haxorg_cli.get_wrap_options(haxorg_opts.ExportHtmlOptions)
@click.pass_context
def export_html_cli(ctx: click.Context, **kwargs: Any) -> None:
    export_html(haxorg_cli.get_opts(ctx))
