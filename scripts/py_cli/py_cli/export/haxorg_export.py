from pydantic import BaseModel
import rich_click as click
from py_scriptutils.toml_config_profiler import apply_options, options_from_model, pack_context
from beartype.typing import Optional, Any


class CliExportOptions(BaseModel, extra="forbid"):
    pass


def export_cli_options(f: Any) -> Any:
    return apply_options(f, options_from_model(CliExportOptions))


@click.group()
@click.pass_context
@export_cli_options
def export(ctx: click.Context, **kwargs: Any) -> None:
    """Convert org-mode document to some other markup/document format"""
    pack_context(ctx, "export", CliExportOptions, config=config, kwargs=kwargs)
    pass


from py_cli.export.haxorg_export_tex import export_tex

export.add_command(export_tex)

from py_cli.export.haxorg_export_ultraplain import export_ultraplain

export.add_command(export_ultraplain)

from py_cli.export.haxorg_export_sqlite import export_sqlite

export.add_command(export_sqlite)

from py_cli.export.haxorg_export_html import export_html

export.add_command(export_html)

from py_cli.export.haxorg_export_pandoc import export_pandoc

export.add_command(export_pandoc)

from py_cli.export.haxorg_export_typst import export_typst

export.add_command(export_typst)
