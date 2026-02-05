from beartype.typing import Any, Optional
from py_cli import haxorg_cli, haxorg_opts
from py_scriptutils.script_logging import log
import rich_click as click

CAT = __name__


@click.group()
@click.pass_context
@haxorg_cli.get_wrap_options(haxorg_opts.GenerateOptions)
def generate(ctx: click.Context, **kwargs: Any) -> None:
    """Generate/analyze input org-mode document"""


from py_cli.generate import codex_tracking, node_clouds, sort_repository_tags, story_grid, subtree_clocking, todo_collector
from py_cli.generate.mind_map import gen_mind_map

generate.add_command(node_clouds.node_cloud_cli)
generate.add_command(subtree_clocking.subtree_clocking_cli)
generate.add_command(story_grid.story_grid_cli)
generate.add_command(sort_repository_tags.sort_repository_tags_cli)
generate.add_command(codex_tracking.codex_tracking_cli)
generate.add_command(gen_mind_map.gen_mind_map_cli)
generate.add_command(todo_collector.todo_collector_cli)
