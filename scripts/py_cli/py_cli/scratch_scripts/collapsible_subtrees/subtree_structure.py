from pathlib import Path
import rich_click as click

from py_cli.haxorg_cli import (
    apply_options,
    options_from_model,
    BaseModel,
    pack_context,
    Field,
)

from beartype.typing import List, Union
from beartype import beartype

import py_haxorg.pyhaxorg_wrap as org
from py_haxorg.pyhaxorg_utils import formatOrgWithoutTime
from py_scriptutils.script_logging import log


CAT = "subtree_structure"


class SubtreeStructure(BaseModel):
    name: str
    subtrees: List["SubtreeStructure"] = Field(default_factory=list)

@beartype
def getStructure(node: Union[org.Document, org.Subtree]) -> SubtreeStructure:
    result = SubtreeStructure(
        name=formatOrgWithoutTime(node.title) if isinstance(node, org.Subtree) else "<document>"
    )

    for item in node:
        if isinstance(item, org.Subtree):
            result.subtrees.append(getStructure(item))

    return result

class SubtreeStructureOpts(BaseModel, extra="forbid"):
    infile: Path
    outfile: Path

def cli_options(f):
    return apply_options(f, options_from_model(SubtreeStructureOpts))

@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@cli_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", SubtreeStructureOpts, config=config, kwargs=kwargs)
    opts: SubtreeStructureOpts = ctx.obj["root"]
    node = org.parseFile(str(opts.infile.resolve()), org.OrgParseParameters())

if __name__ == "__main__":
    cli()
