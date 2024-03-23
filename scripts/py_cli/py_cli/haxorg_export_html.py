from py_cli.haxorg_cli import *
from beartype.typing import List, Tuple
from py_exporters.export_html import ExporterHtml


class ExportHtmlOptions(BaseModel):
    infile: Path
    outfile: Path
    cachedir: Optional[Path] = None


CAT = "haxorg.export.html"


def export_html_options(f):
    return apply_options(f, options_from_model(ExportHtmlOptions))


@click.command("html")
@export_html_options
@click.pass_context
def export_html(ctx: click.Context, config: Optional[str] = None, **kwargs):
    pack_context(ctx, "html", ExportHtmlOptions, config=config, kwargs=kwargs)
    run = get_run(ctx)
    with run.event("Run html export", CAT):
        opts: ExportHtmlOptions = ctx.obj["html"]
        node = parseCachedFile(opts.infile, opts.cachedir)
        exp = ExporterHtml()
        document = exp.evalDocument(node)
        opts.outfile.write_text(str(document))

    run.finalize()
