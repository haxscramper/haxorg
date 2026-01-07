#!/usr/bin/env python

import pandas as pd
from beartype.typing import Any
from collections import defaultdict
from py_haxorg.pyhaxorg_utils import getFlatTags
from py_scriptutils.toml_config_profiler import apply_options, options_from_model, pack_context
import rich_click as click
import py_haxorg.pyhaxorg_wrap as org
from py_cli.haxorg_opts import GenerateNodeCloudOptions
from py_cli.haxorg_cli import parseCachedFile, get_opts

CAT = __name__


def analysis_options(f: Any) -> Any:
    return apply_options(f, options_from_model(GenerateNodeCloudOptions))


@click.command("node_clouds")
@analysis_options
@click.pass_context
def node_cloud_cli(ctx: click.Context, config: str, **kwargs: Any) -> None:
    opts = get_opts(ctx, config, **kwargs)
    count: defaultdict[tuple[str, str], int] = defaultdict(lambda: 0)

    def visit(node: org.Org) -> None:
        if isinstance(node, org.Word):
            count[("word", node.text)] += 1

        elif isinstance(node, org.HashTag):
            for tag in getFlatTags(node):
                count[("tag", "##".join(tag))] += 1

        else:
            for sub in node:
                visit(sub)

    for file in opts.generate.node_clouds.infile:
        node = parseCachedFile(file, opts.cache)
        visit(node)

    df = pd.DataFrame(
        [(key[0], key[1], val) for key, val in count.items()],
        columns=["kind", "text", "count"],
    )

    df.to_csv(opts.generate.node_clouds.outfile, index=False)


if __name__ == "__main__":
    node_cloud_cli()
