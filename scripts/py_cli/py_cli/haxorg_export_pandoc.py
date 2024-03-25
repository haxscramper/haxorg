from py_cli.haxorg_cli import *
from beartype.typing import List, Tuple
from py_exporters.export_pandoc import ExporterPandoc
import json


class ExportPandocOptions(BaseModel):
    infile: Path
    outfile: Path
    cachedir: Optional[Path] = None


CAT = "haxorg.export.pandoc"


def export_pandoc_options(f):
    return apply_options(f, options_from_model(ExportPandocOptions))


@click.command("pandoc")
@export_pandoc_options
@click.pass_context
def export_pandoc(ctx: click.Context, config: Optional[str] = None, **kwargs):
    pack_context(ctx, "pandoc", ExportPandocOptions, config=config, kwargs=kwargs)
    run = get_run(ctx)
    with run.event("Run pandoc export", CAT):
        opts: ExportPandocOptions = ctx.obj["pandoc"]
        node = parseCachedFile(opts.infile, opts.cachedir)

        org.exportToTreeFile(node, "/tmp/tree.txt", org.OrgTreeExportOpts(withColor=False))
        
        exp = ExporterPandoc()
        document = exp.evalTop(node).toJson()[0]
        opts.outfile.write_text(json.dumps(document, indent=2))

    run.finalize()
