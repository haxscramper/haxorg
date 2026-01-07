import rich_click as click
from beartype.typing import  Any
from py_cli import haxorg_cli, haxorg_opts


@click.group()
@haxorg_cli.get_wrap_options(haxorg_opts.ExportOptions)
@click.pass_context
def export(ctx: click.Context, **kwargs: Any) -> None:
    """Convert org-mode document to some other markup/document format"""
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
