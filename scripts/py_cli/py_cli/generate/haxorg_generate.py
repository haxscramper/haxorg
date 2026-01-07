import rich_click as click
from beartype.typing import Any, Optional
from py_cli import haxorg_cli, haxorg_opts
from py_scriptutils.script_logging import log

CAT = __name__


def generate_cli_options(f: Any) -> Any:
    return haxorg_cli.apply_options(
        f, haxorg_cli.options_from_model(haxorg_opts.GenerateOptions))


@click.group()
@click.pass_context
@generate_cli_options
def generate(ctx: click.Context, config: Optional[str] = None, **kwargs: Any) -> None:
    """Generate/analyze input org-mode document"""
    log(CAT).info("haxorg generate")


from py_cli.generate import (node_clouds, sort_repository_tags, story_grid,
                             subtree_clocking)

generate.add_command(node_clouds.node_cloud_cli)
generate.add_command(subtree_clocking.subtree_clocking_cli)
generate.add_command(story_grid.story_grid_cli)
generate.add_command(sort_repository_tags.sort_repository_tags_cli)
