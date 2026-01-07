from py_cli import haxorg_cli, haxorg_opts
from beartype.typing import Any, Optional
from py_exporters.export_pandoc import ExporterPandoc
import json
import rich_click as click
import py_haxorg.pyhaxorg_wrap as org

CAT = "haxorg.export.pandoc"


@click.command("pandoc")
@haxorg_cli.get_wrap_options(haxorg_opts.ExportPandocOptions)
@click.pass_context
def export_pandoc(ctx: click.Context, **kwargs: Any) -> None:
    opts = haxorg_cli.get_opts(ctx)
    assert opts.export
    assert opts.export.pandoc
    assert opts.export.pandoc.infile
    assert opts.export.pandoc.outfile

    run = haxorg_cli.get_run(ctx)
    with run.event("Run pandoc export", CAT):
        node = haxorg_cli.parseCachedFile(opts.export.pandoc.infile, opts.cache)

        if opts.export.pandoc.debug_tree:
            org.exportToTreeFile(node, str(opts.export.pandoc.debug_tree),
                                 org.OrgTreeExportOpts(withColor=False))

        exp = ExporterPandoc()
        if opts.export.exportTraceFile:
            exp.enableFileTrace(opts.export.exportTraceFile)

        document = exp.evalTop(node).toJson()[0]
        opts.export.pandoc.outfile.write_text(json.dumps(document, indent=2))

    run.finalize()
