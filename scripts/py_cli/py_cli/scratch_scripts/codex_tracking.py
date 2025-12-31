#!/usr/bin/env python

import pandas as pd
from py_cli.haxorg_cli import *
from beartype import beartype
from beartype.typing import List, Tuple, Any
from py_haxorg.pyhaxorg_utils import getFlatTags
from py_scriptutils.script_logging import log
import py_haxorg.pyhaxorg_wrap as org
from dataclasses import dataclass, field
from py_scriptutils.pandas_utils import dataframe_to_rich_table
from py_scriptutils.rich_utils import render_rich

CAT = __name__


class CodexTrackingOptions(BaseModel):
    target_file: Path
    codex_files: List[Path]
    outfile: Path
    cachedir: Optional[Path] = None


@beartype
@dataclass
class RadioEntry:
    use_path: List[str] = field(default_factory=list)
    prev_context: List[org.Org] = field(default_factory=list)
    radio_use: List[org.Org] = field(default_factory=list)
    post_context: List[org.Org] = field(default_factory=list)


def analysis_options(f: Any) -> Any:
    return apply_options(f, options_from_model(CodexTrackingOptions)) 


def format_dataframe_for_file(df: pd.DataFrame) -> str:
    result: List[str] = []
    grouped_by_use = df.groupby("use")

    for use, use_group in grouped_by_use:
        result.append(f"use {''.join(use)}:")
        grouped_by_path = use_group.groupby("path")

        for path, path_group in grouped_by_path:
            result.append(f"  path {'/'.join(path)}:")
            for _, row in path_group.iterrows():
                prev = "".join(row["prev"])
                use_field = "".join(row["use"])
                post = "".join(row["post"])
                result.append(f"    .. {prev}>>{use_field}<<{post} ..")

            result.append("")  
    return "\n".join(result).strip()

@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@analysis_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs: Any) -> None:
    pack_context(ctx, "root", CodexTrackingOptions, config=config, kwargs=kwargs)
    opts: CodexTrackingOptions = ctx.obj["root"]
    target_node = parseCachedFile(opts.target_file, opts.cachedir)
    codex_nodes = [parseCachedFile(f, opts.cachedir) for f in opts.codex_files]

    tracking: org.AstTrackingMap = org.getAstTrackingMap(
        org.VecOfSemIdOfOrgVec([target_node] + codex_nodes))

    radio_entries: List[RadioEntry] = list()

    @beartype
    def visit_node(node: org.Org, path: Any) -> Any:
        match node:
            case org.Paragraph():
                groups: List[org.AstTrackingGroup] = org.getSubnodeGroups(node, tracking)

                def clamp(value: int, min: int, max: int) -> int:
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
                        use_path: List[str] = list()
                        for step in path:
                            match step:
                                case org.Subtree():
                                    use_path.append(step.getCleanTitle())

                        radio_entries.append(RadioEntry(
                            use_path=use_path,
                            prev_context=flat_span(i-10, i),
                            post_context=flat_span(i+1, i+11),
                            radio_use=list(radio.nodes),
                        ))


    org.eachSubnodeRecSimplePath(target_node, visit_node)
        
    @beartype
    def format_list(items: List[org.Org]) -> Tuple[str, ...]:
        res = []
        for it in items:
            if isinstance(it, org.Space):
                res.append(it.text)

            else:
                res.append(org.formatToString(it))

        return tuple(res)


    if radio_entries:
        df = pd.DataFrame.from_records([
            dict(
                path=tuple(entry.use_path),
                prev=format_list(entry.prev_context),
                use=format_list(entry.radio_use),
                post=format_list(entry.post_context),
                # use_line=entry.radio_use.lo
            ) for entry in radio_entries
        ])
        
        opts.outfile.write_text(format_dataframe_for_file(df))

    else:
        opts.outfile.write_text("no codex entries detected")


if __name__ == "__main__":
    cli()
