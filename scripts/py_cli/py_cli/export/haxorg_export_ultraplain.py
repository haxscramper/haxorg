from py_cli.haxorg_opts import ExportUltraplainOptions
from py_cli.haxorg_cli import get_opts, options_from_model, apply_options, parseFile
import rich_click as click
from beartype.typing import Any, Optional
import glom
from pathlib import Path
from py_scriptutils.script_logging import log


def export_ultraplain_options(f: Any) -> Any:
    return apply_options(f, options_from_model(ExportUltraplainOptions))


@click.command("ultraplain")
@export_ultraplain_options
@click.pass_context
def export_ultraplain(ctx: click.Context, **kwargs: Any) -> None:
    opts = get_opts(ctx, **kwargs)
    assert opts.export
    node = parseFile(opts, glom.glom(opts, "export.ultraplain.infile"))
    from py_exporters.export_ultraplain import ExporterUltraplain
    exp = ExporterUltraplain()
    if opts.export:
        exp.exp.enableFileTrace(opts.export.exportTraceFile, False)

    exp.exp.evalTop(node)
    out_path = Path(glom(opts, "export.ultraplain.outfile"))

    out_path.write_text(exp.result)

    log("haxorg.ultraplain").info(f"Finished DB write to {out_path}")
