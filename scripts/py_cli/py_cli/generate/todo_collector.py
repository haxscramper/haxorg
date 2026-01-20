import itertools
import json
from dataclasses import dataclass, field
from datetime import datetime
from pathlib import Path

import py_haxorg.pyhaxorg_utils as org_utils
import py_haxorg.pyhaxorg_wrap as org
import rich_click as click
from beartype import beartype
from beartype.typing import Any, List, Optional, Dict, Literal
from py_cli import haxorg_cli, haxorg_opts
from py_scriptutils.script_logging import log
import pandas as pd

CAT = __name__


@beartype
@dataclass
class Entry():
    title: List[org.Org]
    todo: str
    type: Literal["subtree", "list_item"]
    nested: List["Entry"] = field(default_factory=list)
    created: Optional[datetime] = None


@beartype
def rec_node(node: org.Org, opts: haxorg_opts.RootOptions) -> List[Entry]:
    result: List[Entry] = list()

    def aux_nested(node: org.Org) -> List[Entry]:
        return list(itertools.chain(*[rec_node(sub, opts) for sub in node]))

    match node:
        case org.Subtree():
            if node.todo is not None:
                result.append(
                    Entry(
                        title=org_utils.getTitleBody(node),
                        nested=aux_nested(node),
                        created=org_utils.getCreationTime(node),
                        todo=node.todo,
                        type="subtree",
                    ))

            else:
                result.extend(aux_nested(node))

        case org.ListItem():
            if node.size() == 0:
                return result

            head = node[0]
            if not isinstance(head, org.Paragraph):
                result.extend(aux_nested(node))
                return result

            ad = head.getAdmonitions()
            if not ad or ad[0] not in opts.todo_ident_names:
                result.extend(aux_nested(node))
                return result

            entry = Entry(
                title=list(head),
                created=org_utils.getCreationTime(head),
                todo=ad[0],
                type="list_item",
            )

            for idx, sub in enumerate(node):
                if 0 < idx:
                    entry.nested.extend(rec_node(sub, opts))

            result.append(entry)

        case _:
            result.extend(aux_nested(node))

    return result


class TodoCollectorResult():
    nested_report: Path
    chronological_report: Path
    json_dump: Path


@beartype
def _generate_report(ctx: haxorg_cli.CliRunContext, entries: List[Entry],
                     result: TodoCollectorResult) -> None:

    assert ctx.opts.generate
    assert ctx.opts.generate.todo_collector

    items: List[Dict[str, Any]] = list(dict())

    title_skip = set([
        org.OrgSemKind.Time,
        org.OrgSemKind.TimeRange,
        org.OrgSemKind.Space,
        org.OrgSemKind.BigIdent,
    ])

    def _aux_nested(entry: Entry, path: List[int]) -> None:
        items.append(
            dict(
                todo=entry.todo,
                title=org_utils.formatOrgWithoutPrefix(entry.title, title_skip),
                path=path,
                created=entry.created if entry.created else datetime.fromtimestamp(0),
                depth=len(path),
                type=entry.type,
            ))

        for index, sub in enumerate(entry.nested):
            _aux_nested(sub, path + [index])

    for index, entry in enumerate(entries):
        _aux_nested(entry, [index])

    df = pd.DataFrame(items)

    out_d = ctx.opts.generate.todo_collector.outdir
    out_d.mkdir(parents=True, exist_ok=True)

    result.nested_report = out_d.joinpath("nested.txt")
    result.chronological_report = out_d.joinpath("chronological.txt")

    result.json_dump = out_d.joinpath("entries.json")
    grouped = df.groupby("todo").apply(lambda x: x.to_dict("records")).to_dict()

    def json_serializer(obj: Any) -> Any:
        if isinstance(obj, datetime):
            return obj.isoformat()
        raise TypeError(f"Object of type {type(obj)} is not JSON serializable")

    result.json_dump.write_text(json.dumps(grouped, indent=2, default=json_serializer))


@beartype
def todo_collector(ctx: haxorg_cli.CliRunContext) -> TodoCollectorResult:
    result = TodoCollectorResult()

    assert ctx.opts.generate
    assert ctx.opts.generate.todo_collector

    nodes = haxorg_cli.parsePathList(ctx, ctx.opts.generate.todo_collector.infile)
    entires = list(itertools.chain(*[rec_node(node, ctx.opts) for node in nodes]))

    _generate_report(ctx, entires, result)

    return result


@click.command("todo_collector")
@haxorg_cli.get_wrap_options(haxorg_opts.GenerateNodeCloudOptions)
@click.pass_context
def todo_collector_cli(ctx: click.Context, **kwargs: Any) -> None:
    log(CAT).info("Starting todo collector command")
    result = todo_collector(haxorg_cli.get_run(ctx))
    log(CAT).info(f"Wrote JSON to {result.json_dump}")
