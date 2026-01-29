#!/usr/bin/env python

from collections import defaultdict

import pandas as pd
import py_haxorg.pyhaxorg_wrap as org
import rich_click as click
from beartype import beartype
from beartype.typing import Any, Optional
from py_cli import haxorg_cli, haxorg_opts
from py_haxorg.pyhaxorg_utils import getFlatTags

CAT = __name__


@beartype
def node_clouds(ctx: haxorg_cli.CliRunContext) -> None:
    assert ctx.opts.generate
    assert ctx.opts.generate.node_clouds
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

    for file in ctx.opts.generate.node_clouds.infile:
        node = haxorg_cli.parseCachedFile(ctx, file)
        visit(node)

    df = pd.DataFrame(
        [(key[0], key[1], val) for key, val in count.items()],
        columns=["kind", "text", "count"],
    )

    df.to_csv(ctx.opts.generate.node_clouds.outfile, index=False)


@click.command("node_clouds")
@haxorg_cli.get_wrap_options(haxorg_opts.GenerateNodeCloudOptions)
@click.pass_context
def node_cloud_cli(ctx: click.Context, **kwargs: Any) -> None:
    node_clouds(haxorg_cli.get_run(ctx))
