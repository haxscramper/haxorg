#!/usr/bin/env python

import pandas as pd
from py_cli.haxorg_cli import *
from beartype import beartype
from beartype.typing import List, Any
from collections import defaultdict
from py_haxorg.pyhaxorg_utils import getFlatTags
from py_scriptutils.script_logging import log

CAT = __name__


class NodeCloudOptions(BaseModel):
    infile: List[Path]
    outfile: Path
    cachedir: Optional[Path] = None


def analysis_options(f: Any) -> Any: 
    return apply_options(f, options_from_model(NodeCloudOptions)) 


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@analysis_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs: Any) -> None:
    pack_context(ctx, "root", NodeCloudOptions, config=config, kwargs=kwargs)
    opts: NodeCloudOptions = ctx.obj["root"]
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

    for file in opts.infile:
        node = parseCachedFile(file, opts.cachedir)
        visit(node)

    df = pd.DataFrame(
        [(key[0], key[1], val) for key, val in count.items()],
        columns=["kind", "text", "count"],
    )

    df.to_csv(opts.outfile, index=False)


if __name__ == "__main__":
    cli()
