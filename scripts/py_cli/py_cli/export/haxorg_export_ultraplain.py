from pathlib import Path

from beartype import beartype
from beartype.typing import Any, Optional
import glom
from py_cli import haxorg_cli, haxorg_opts
from py_scriptutils.script_logging import log
import rich_click as click


@beartype
def export_ultraplain(opts: haxorg_opts.RootOptions) -> None:
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


@click.command("ultraplain")
@haxorg_cli.get_wrap_options(haxorg_opts.ExportUltraplainOptions)
@click.pass_context
def export_ultraplain_cli(ctx: click.Context, **kwargs: Any) -> None:
    export_ultraplain(haxorg_cli.get_opts(ctx))
