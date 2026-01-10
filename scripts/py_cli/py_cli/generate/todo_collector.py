from dataclasses import dataclass, field
from pathlib import Path

import py_haxorg.pyhaxorg_wrap as org
import py_haxorg.pyhaxorg_utils as org_utils
import rich_click as click
from beartype import beartype
from beartype.typing import Any, Optional, List, Tuple
from py_cli import haxorg_cli, haxorg_opts
from py_scriptutils.script_logging import log
from datetime import datetime
import itertools

CAT = __name__


@beartype
@dataclass
class Entry():
    title: List[org.Org]
    todo: str
    nested: List["Entry"] = field(default_factory=list)
    created: Optional[datetime] = None


@beartype
def rec_node(node: org.Org) -> List[Entry]:
    result: List[Entry] = list()

    def aux_nested(node: org.Org) -> List[Entry]:
        return list(itertools.chain(*[rec_node(sub) for sub in node]))

    log(CAT).info(f"{node.getKind()} {node}")

    match node:
        case org.Subtree():
            if node.todo is not None:
                result.append(
                    Entry(
                        title=org_utils.getTitleBody(node),
                        nested=aux_nested(node),
                        created=org_utils.getCreationTime(node),
                        todo=node.todo,
                    ))

            else:
                result.extend(aux_nested(node))

        case org.Paragraph():
            ad = node.getAdmonitions()
            if ad:
                result.append(
                    Entry(
                        title=list(node.getBody()),
                        created=org_utils.getCreationTime(node),
                        todo=ad[0],
                    ))

        case org.List():
            log(CAT).info("Found list")

        case _:
            result.extend(aux_nested(node))

    return result


class TodoCollectorResult():
    nested_report: Path
    chronological_report: Path


@beartype
def _generate_report(opts: haxorg_opts.RootOptions, entries: List[Entry],
                     result: TodoCollectorResult) -> None:

    assert opts.generate
    assert opts.generate.todo_collector

    items: List[Tuple[int, Entry]] = list()

    def _aux_nested(entry: Entry, depth: int) -> None:
        items.append((depth, entry))
        for sub in entry.nested:
            _aux_nested(sub, depth + 1)

    for entry in entries:
        _aux_nested(entry, 0)

    result.nested_report = opts.generate.todo_collector.outfile.joinpath("nested.txt")
    result.chronological_report = opts.generate.todo_collector.outfile.joinpath(
        "chronological.txt")

    opts.generate.todo_collector.outfile.mkdir(parents=True, exist_ok=True)

    result.nested_report.write_text("\n".join([
        f"{'  ' * depth} {entry.todo} {org_utils.formatOrgWithoutTime(entry.title)}"
        for depth, entry in items
    ]))

    result.chronological_report.write_text("\n".join([
        f"{entry.todo} {org_utils.formatOrgWithoutTime(entry.title)}"
        for depth, entry in sorted(items, key=lambda it: it[1].created)
    ]))


@beartype
def todo_collector(opts: haxorg_opts.RootOptions,
                   run: Optional[haxorg_cli.CliRunContext] = None) -> TodoCollectorResult:
    if not run:
        run = haxorg_cli.get_run(opts)  # type: ignore

    result = TodoCollectorResult()

    assert opts.generate
    assert opts.generate.todo_collector

    nodes = haxorg_cli.parsePathList(opts, opts.generate.todo_collector.infile)
    entires = list(itertools.chain(*[rec_node(node) for node in nodes]))

    _generate_report(opts, entires, result)

    return result


@click.command("todo_collector")
@haxorg_cli.get_wrap_options(haxorg_opts.GenerateNodeCloudOptions)
@click.pass_context
def node_cloud_cli(ctx: click.Context, **kwargs: Any) -> None:
    todo_collector(haxorg_cli.get_opts(ctx))
