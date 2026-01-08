#!/usr/bin/env python

import pandas as pd
from py_cli import haxorg_cli, haxorg_opts
from beartype import beartype
from beartype.typing import List, Tuple, Any
import py_haxorg.pyhaxorg_wrap as org
from dataclasses import dataclass, field
from py_scriptutils.script_logging import log
import rich_click as click

CAT = __name__


@beartype
@dataclass
class RadioEntry:
    use_path: List[str] = field(default_factory=list)
    prev_context: List[org.Org] = field(default_factory=list)
    radio_use: List[org.Org] = field(default_factory=list)
    post_context: List[org.Org] = field(default_factory=list)


def _format_dataframe_for_file(df: pd.DataFrame) -> str:
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


@beartype
def _format_list(items: List[org.Org]) -> Tuple[str, ...]:
    res = []
    for it in items:
        if isinstance(it, org.Space):
            res.append(it.text)

        else:
            res.append(org.formatToString(it))

    return tuple(res)


def codex_tracking(opts: haxorg_opts.RootOptions) -> None:
    assert opts.generate
    assert opts.generate.codex_tracking
    target_node = haxorg_cli.parseCachedFile(opts.generate.codex_tracking.target_file,
                                             opts.cache)
    codex_nodes = [
        haxorg_cli.parseCachedFile(f, opts.cache)
        for f in opts.generate.codex_tracking.codex_files
    ]

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
                    for item in groups[clamp(first, 0, len(groups)
                                            ):clamp(last, 0, len(groups))]:
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

                        radio_entries.append(
                            RadioEntry(
                                use_path=use_path,
                                prev_context=flat_span(i - 10, i),
                                post_context=flat_span(i + 1, i + 11),
                                radio_use=list(radio.nodes),
                            ))

    org.eachSubnodeRecSimplePath(target_node, visit_node)

    if radio_entries:
        df = pd.DataFrame.from_records([
            dict(
                path=tuple(entry.use_path),
                prev=_format_list(entry.prev_context),
                use=_format_list(entry.radio_use),
                post=_format_list(entry.post_context),
                # use_line=entry.radio_use.lo
            ) for entry in radio_entries
        ])

        opts.generate.codex_tracking.outfile.write_text(_format_dataframe_for_file(df))

    else:
        opts.generate.codex_tracking.outfile.write_text("no codex entries detected")


@click.command("codex_tracking")
@haxorg_cli.get_wrap_options(haxorg_opts.CodexTrackingOptions)
@click.pass_context
def codex_tracking_cli(ctx: click.Context, **kwargs: Any) -> None:
    codex_tracking(haxorg_cli.get_opts(ctx))
