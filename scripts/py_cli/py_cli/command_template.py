import py_haxorg.pyhaxorg_wrap as org
import rich_click as click
from beartype import beartype
from beartype.typing import Any, Optional
from py_cli import haxorg_cli, haxorg_opts
from py_scriptutils.script_logging import log

CAT = __name__


@beartype
def node_clouds(ctx: haxorg_cli.CliRunContext) -> None:
    pass


@click.command("node_clouds")
@haxorg_cli.get_wrap_options(haxorg_opts.GenerateNodeCloudOptions)
@click.pass_context
def node_cloud_cli(ctx: click.Context, **kwargs: Any) -> None:
    node_clouds(haxorg_cli.get_run(ctx))
