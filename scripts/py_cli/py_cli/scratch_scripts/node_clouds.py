#!/usr/bin/env python

import pandas as pd
from py_cli.haxorg_cli import *
from beartype import beartype
from beartype.typing import List
from collections import defaultdict
from py_haxorg.pyhaxorg_utils import getFlatTags

CAT = __name__


class NodeCloudOptions(BaseModel):
    infile: List[Path]
    outfile: Path
    cachedir: Optional[Path] = None


def analysis_options(f):
    return apply_options(f, options_from_model(NodeCloudOptions))


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@analysis_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", NodeCloudOptions, config=config, kwargs=kwargs)
    opts: NodeCloudOptions = ctx.obj["root"]
    count: defaultdict[str, int] = defaultdict(lambda: 0)

    def visit(node: org.Org):
        if isinstance(node, org.Word):
            count[("word", node.text)] += 1

        elif isinstance(node, org.HashTag):
            for tag in getFlatTags(node):
                count[("tag", "##".join(tag))] += 1

    org_ctx = org.OrgContext()
    for file in opts.infile:
        node = parseCachedFile(file, opts.cachedir)
        org_ctx.eachSubnodeRec(node, visit)

    df = pd.DataFrame(
        [(key[0], key[1], val) for key, val in count.items()],
        columns=["kind", "text", "count"],
    )

    df.to_csv(opts.outfile, index=False)


if __name__ == "__main__":
    cli()
