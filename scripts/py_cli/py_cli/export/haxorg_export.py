import rich_click as click
from beartype.typing import Any
from py_cli import haxorg_cli, haxorg_opts


@click.group()
@haxorg_cli.get_wrap_options(haxorg_opts.ExportOptions)
@click.pass_context
def export(ctx: click.Context, **kwargs: Any) -> None:
    """Convert org-mode document to some other markup/document format"""
    pass


from py_cli.export.haxorg_export_tex import export_tex_cli
from py_cli.export.haxorg_export_ultraplain import export_ultraplain_cli
from py_cli.export.haxorg_export_sqlite import export_sqlite_cli
from py_cli.export.haxorg_export_html import export_html_cli
from py_cli.export.haxorg_export_pandoc import export_pandoc_cli
from py_cli.export.haxorg_export_typst import export_typst_cli

export.add_command(export_tex_cli)
export.add_command(export_ultraplain_cli)
export.add_command(export_sqlite_cli)
export.add_command(export_html_cli)
export.add_command(export_pandoc_cli)
export.add_command(export_typst_cli)
