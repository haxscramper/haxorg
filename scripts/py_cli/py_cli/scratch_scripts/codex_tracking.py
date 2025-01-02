#!/usr/bin/env python

import pandas as pd
from py_cli.haxorg_cli import *
from beartype import beartype
from beartype.typing import List
from py_haxorg.pyhaxorg_utils import getFlatTags
from py_scriptutils.script_logging import log
import py_haxorg.pyhaxorg_wrap as org
from dataclasses import dataclass, field

CAT = __name__


class CodexTrackingOptions(BaseModel):
    target_file: Path
    codex_files: List[Path]
    outfile: Path
    cachedir: Optional[Path] = None


@beartype
@dataclass
class RadioEntry:
    target_path: List[str] = field(default_factory=list)
    prev_context: List[org.Org] = field(default_factory=list)
    radio_use: List[org.Org] = field(default_factory=list)
    post_context: List[org.Org] = field(default_factory=list)


def analysis_options(f):
    return apply_options(f, options_from_model(CodexTrackingOptions))


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@analysis_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", CodexTrackingOptions, config=config, kwargs=kwargs)
    opts: CodexTrackingOptions = ctx.obj["root"]
    target_node = parseCachedFile(opts.target_file, opts.cachedir)
    codex_nodes = [parseCachedFile(f, opts.cachedir) for f in opts.codex_files]

    tracking: org.AstTrackingMap = org.getAstTrackingMap(
        org.VecOfSemIdOfOrgVec([target_node] + codex_nodes))

    radio_entries: List[RadioEntry] = list()

    @beartype
    def visit_node(node: org.Org):
        match node:
            case org.Paragraph():
                groups: List[org.AstTrackingGroup] = org.getSubnodeGroups(node, tracking)

                def clamp(value: int, min: int, max: int) -> max:
                    if value < min:
                        return min

                    elif max < value:
                        return max

                    else:
                        return value

                @beartype
                def flat_span(first: int, last: int) -> List[org.Org]:
                    result: List[org.Org] = []
                    for item in groups[clamp(first, 0, len(groups)):clamp(last, 0, len(groups))]:
                        if item.isRadioTarget():
                            for n in item.getRadioTarget().nodes:
                                result.append(n)

                        else:
                            result.append(item.getSingle().node)

                    return result


                for i in range(0, len(groups)):
                    group: org.AstTrackingGroup = groups[i]
                    if group.isRadioTarget():
                        radio: org.AstTrackingGroupRadioTarget = group.getRadioTarget()
                        target_path: List[str] = list()
                        for step in radio.target.path:
                            match step:
                                case org.Subtree():
                                    target_path.append(step.getCleanTitle())

                        radio_entries.append(RadioEntry(
                            target_path=target_path,
                            prev_context=flat_span(i-10, i),
                            post_context=flat_span(i+1, i+11),
                            radio_use=list(radio.nodes),
                        ))


    org.eachSubnodeRec(target_node, visit_node)
        


if __name__ == "__main__":
    cli()
