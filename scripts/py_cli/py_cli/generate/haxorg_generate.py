import rich_click as click
from beartype.typing import Any, Optional
from py_cli import haxorg_cli, haxorg_opts
from py_scriptutils.script_logging import log

CAT = __name__


@click.group()
@click.pass_context
@haxorg_cli.get_wrap_options(haxorg_opts.GenerateOptions)
def generate(ctx: click.Context, **kwargs: Any) -> None:
    """Generate/analyze input org-mode document"""


from py_cli.generate import (
    node_clouds,
    sort_repository_tags,
    story_grid,
    subtree_clocking,
    codex_tracking,
)

generate.add_command(node_clouds.node_cloud_cli)
generate.add_command(subtree_clocking.subtree_clocking_cli)
generate.add_command(story_grid.story_grid_cli)
generate.add_command(sort_repository_tags.sort_repository_tags_cli)
generate.add_command(codex_tracking.codex_tracking_cli)
