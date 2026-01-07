#!/usr/bin/env python

import pandas as pd
from beartype.typing import Any
from collections import defaultdict
from py_haxorg.pyhaxorg_utils import getFlatTags
import rich_click as click
import py_haxorg.pyhaxorg_wrap as org
from py_cli import haxorg_opts, haxorg_cli

CAT = __name__


@click.command("node_clouds")
@haxorg_cli.get_wrap_options(haxorg_opts.GenerateNodeCloudOptions)
@click.pass_context
def node_cloud_cli(ctx: click.Context, **kwargs: Any) -> None:
    opts = haxorg_cli.get_opts(ctx)
    assert opts.generate
    assert opts.generate.node_clouds
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
        node = haxorg_cli.parseCachedFile(file, opts.cache)
        visit(node)

    df = pd.DataFrame(
        [(key[0], key[1], val) for key, val in count.items()],
        columns=["kind", "text", "count"],
    )

    df.to_csv(opts.generate.node_clouds.outfile, index=False)


if __name__ == "__main__":
    node_cloud_cli()
