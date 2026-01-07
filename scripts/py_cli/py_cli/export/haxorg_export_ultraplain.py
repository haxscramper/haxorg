from py_cli import haxorg_cli, haxorg_opts
import rich_click as click
from beartype.typing import Any, Optional
import glom
from pathlib import Path
from py_scriptutils.script_logging import log


@click.command("ultraplain")
@haxorg_cli.get_wrap_options(haxorg_opts.ExportUltraplainOptions)
@click.pass_context
def export_ultraplain(ctx: click.Context, **kwargs: Any) -> None:
    opts = haxorg_cli.get_opts(ctx)
    assert opts.export
    node = haxorg_cli.parseFile(opts, glom.glom(opts, "export.ultraplain.infile"))
    from py_exporters.export_ultraplain import ExporterUltraplain
    exp = ExporterUltraplain()
    if opts.export:
        exp.exp.enableFileTrace(opts.export.exportTraceFile, False)

    exp.exp.evalTop(node)
    out_path = Path(glom(opts, "export.ultraplain.outfile"))

    out_path.write_text(exp.result)

    log("haxorg.ultraplain").info(f"Finished DB write to {out_path}")
