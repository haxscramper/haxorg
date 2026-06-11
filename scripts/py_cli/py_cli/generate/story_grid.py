#!/usr/bin/env python

import dataclasses
from dataclasses import dataclass, field, fields
from datetime import datetime, timedelta
import itertools
from numbers import Number
from pathlib import Path
import statistics

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Tuple, Union
import dominate
import dominate.tags as tags
from dominate.util import text
from py_cli import haxorg_cli, haxorg_opts
import py_haxorg.astbuilder.astbuilder_typst as typ
from py_haxorg.exporters.export_html import add_html, add_new, ExporterHtml
from py_haxorg.exporters.export_ultraplain import ExporterUltraplain
from py_haxorg.pyhaxorg_utils import evalDateTime
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.algorithm import maybe_splice
from py_scriptutils.script_logging import log, pprint_to_file, to_debug_json
import rich_click as click

CAT = "story-grid"


@beartype
@dataclass
class Header():
    title: List[org.Org]
    level: int
    words: Optional[int] = None
    duration: Optional[str] = None
    pov: Optional[List[org.Org]] = None
    location: Optional[List[org.Org]] = None
    value: Optional[List[org.Org]] = None
    note: Optional[List[org.Org]] = None
    event: Optional[List[org.Org]] = None
    turning_point: Optional[List[org.Org]] = None
    shift: Optional[Tuple[str, str]] = None
    tags: List[org.HashTag] = field(default_factory=list)
    time: Optional[Union[datetime, Tuple[datetime, datetime]]] = None
    nested: List["Header"] = field(default_factory=list)


@beartype
def rec_filter_subnodes(node: org.Org, target: List[org.OrgSemKind]) -> List[org.Org]:
    result: List[org.Org] = []
    if node is None:
        return result

    if node.getKind() in target:
        result.append(node)

    for sub in node:
        result += rec_filter_subnodes(sub, target)

    return result


osk = org.OrgSemKind


@beartype
def rec_node(node: org.Org) -> List[Header]:
    result: List[Header] = []
    match node:
        case org.Subtree():
            if node.isComment or node.isArchived:
                return result

            title = [sub for sub in node.title]
            time = None
            if title and isinstance(title[0], (org.Time, org.TimeRange)):
                time = title.pop(0)
                if isinstance(title[0], org.Space):
                    title.pop(0)

            header = Header(title=title, level=node.level)

            if isinstance(time, org.Time):
                header.time = evalDateTime(time.getStatic().time)

            elif isinstance(time, org.TimeRange):
                header.time = (
                    evalDateTime(time.from_.getStatic().time),
                    evalDateTime(time.to.getStatic().time),
                )

            for prop in node.properties:
                match prop.getName():
                    case "story_polarity_shift":
                        plain = str(prop.getCustomRaw().value).strip()
                        header.shift = plain.split("/")  # type: ignore

                    case "story_duration":
                        plain = str(prop.getCustomRaw().value).strip()
                        header.duration = plain

                    case _:
                        assert not prop.getName().startswith("story_"), prop.getName()

            for tag in node.tags:
                header.tags.append(tag)

            def count_words(node: org.Org) -> None:
                count = 0

                if node.getKind() in [osk.Word, osk.RawText]:
                    count += 1

                for sub in node:
                    count_words(sub)

                if count != 0:
                    if header.words:
                        header.words += count

                    else:
                        header.words = count

            for sub in node:
                if isinstance(sub, (org.Subtree, org.Document, org.CmdInclude, org.File)):
                    header.nested += rec_node(sub)

                elif isinstance(sub, org.List):
                    if sub.isDescriptionList():
                        for item in sub:
                            # item: org.ListItem
                            tag = [
                                w.text
                                for w in rec_filter_subnodes(item.header, [
                                    org.OrgSemKind.Word,
                                    org.OrgSemKind.RawText,
                                ])
                            ]

                            if len(tag) == 1:
                                match tag[0]:
                                    case "story_event":
                                        header.event = list(item.subnodes)

                                    case "story_turning_point":
                                        header.turning_point = list(item.subnodes)

                                    case "story_location":
                                        header.location = list(item.subnodes)

                                    case "story_pov":
                                        header.pov = list(item.subnodes)

                                    case "story_note":
                                        header.note = list(item.subnodes)

                                    case "story_value":
                                        header.value = list(item.subnodes)

                                    case "story_time":
                                        it = item.subnodes[0][0]
                                        match it:
                                            case org.Time():
                                                header.time = evalDateTime(
                                                    it.getStatic().time)

                                            case org.TimeRange():
                                                header.time = (
                                                    evalDateTime(
                                                        it.from_.getStatic().time),
                                                    evalDateTime(it.to.getStatic().time),
                                                )

                                    case _:
                                        assert not tag[0].startswith("story_"), tag

                    else:
                        count_words(sub)

                else:
                    count_words(sub)

            result.append(header)

        case org.Document() | org.CmdInclude() | org.File():
            for sub in node:
                result += rec_node(sub)

    return result


@beartype
def to_html(node: org.Org | List[org.Org] | str | int) -> Any:
    if isinstance(node, list):
        html: List[tags.html_tag] = []
        for item in node:
            add_html(html, to_html(item))

        return html

    elif isinstance(node, (str, int)):
        return text(str(node))

    else:
        html_exp = ExporterHtml()
        return html_exp.exp.evalTop(node)


@beartype
def format_time_difference(delta: timedelta) -> List[str]:
    # Define a year and a month in seconds for approximate calculation
    # Assuming an average month length of 30.44 days and a year of 365.25 days
    seconds_per_year = 365.25 * 24 * 60 * 60
    seconds_per_month = 30.44 * 24 * 60 * 60
    seconds_per_day = 24 * 60 * 60
    seconds_per_hour = 60 * 60
    seconds_per_minute = 60

    duration_parts = []
    # Calculate total difference in seconds
    diff_seconds = int(delta.total_seconds())

    # Calculate years, months, days, hours, minutes, and seconds
    years, diff_seconds = divmod(diff_seconds, int(seconds_per_year))
    months, diff_seconds = divmod(diff_seconds, int(seconds_per_month))
    days, diff_seconds = divmod(diff_seconds, seconds_per_day)
    hours, diff_seconds = divmod(diff_seconds, seconds_per_hour)
    minutes, seconds = divmod(diff_seconds, seconds_per_minute)

    # Append non-zero time periods to the duration_parts list
    if 0 < years:
        duration_parts.append(f"{int(years)}y")
    if 0 < months:
        duration_parts.append(f"{int(months)}m")
    if 0 < days:
        duration_parts.append(f"{int(days)}d")
    if 0 < hours:
        duration_parts.append(f"{int(hours)}h")
    if 0 < minutes:
        duration_parts.append(f"{int(minutes)}min")
    if 0 < seconds or not duration_parts:
        duration_parts.append(f"{int(seconds)}s")

    return duration_parts


SKIP_FIELDS = ["level", "pov", "tags", "nested"]


@beartype
def get_html_story_grid(nested_headers: List[Header]) -> dominate.document:
    headers: List[Header] = []

    @beartype
    def aux(h: Header) -> None:
        headers.append(h)
        for sub in h.nested:
            aux(sub)

    for h in nested_headers:
        aux(h)

    assert all(isinstance(h, Header) for h in headers)

    doc = dominate.document(title="story_grid")

    table = tags.table(border=1, style="border-collapse: collapse; width: 100%;")
    thead = tags.thead(style="position: sticky; top: 0; background-color: #ddd;")
    header_row = tags.tr()

    for field in fields(Header([], 0)):
        if field.name in SKIP_FIELDS:
            continue

        elif field.name == "time":
            header_row.add(tags.th("delta"))

        header_row.add(tags.th(field.name))

    thead.add(header_row)
    table.add(thead)

    max_level = max(h.level for h in headers) * 1.0
    max_words = max((h.words or 0) for h in headers)

    for idx, h in enumerate(headers):
        row = tags.tr()

        def prev_time() -> Optional[Union[datetime, Tuple[datetime, datetime]]]:
            offset = 1
            while 0 <= (idx - offset):
                prev_h = headers[idx - offset]
                if isinstance(prev_h.time, (datetime, tuple)):
                    return prev_h.time

                else:
                    offset += 1

            return None

        def opt(it: Any, **kwargs: Any) -> None:
            if it:
                row.add(add_new(tags.td(**kwargs), to_html(it)))

            else:
                row.add(tags.td(**kwargs))

        for field in fields(h):
            opacity = (max_level - h.level) / max_level * 0.75
            header_style = f"background-color: rgba(255, 0, 0, {opacity:.2f});"
            cell_args: Dict[str, Any] = dict()

            if field.name in SKIP_FIELDS:
                continue

            elif field.name == "title":
                prefix = f"#{idx} " + "*" * h.level + " "
                row.add(
                    add_new(
                        tags.td(style=header_style),
                        [to_html(prefix), to_html(h.title)],
                    ))

            elif field.name == "words":
                if h.words:
                    opacity = h.words / (max_words * 1.0)
                    row.add(
                        add_new(
                            tags.td(
                                style=f"background-color: rgba(0, 255, 0, {opacity:.2f});"
                            ), to_html(h.words)))

                else:
                    opt(h.words, **cell_args)

            elif field.name == "time":
                if h.time:
                    prev = prev_time()
                    offset = ""
                    start, end = (h.time,
                                  None) if isinstance(h.time, datetime) else h.time
                    if prev:
                        prev_start, prev_end = (prev, None) if isinstance(
                            prev, datetime) else prev
                        offset += "{}".format(" ".join(
                            format_time_difference(start - prev_start)[:2]))

                    if isinstance(h.time, datetime):
                        opt(offset, **cell_args)
                        opt("{}".format(start.strftime("[%Y-%m-%d]")), **cell_args)

                    else:
                        assert end
                        opt(offset, **cell_args)
                        opt(
                            "{}-{}".format(
                                start.strftime("[%Y-%m-%d]"),
                                end.strftime("[%Y-%m-%d]"),
                            ),
                            **cell_args,
                        )

                else:
                    opt("", **cell_args)
                    opt("", **cell_args)

            elif field.name == "shift":
                value = getattr(h, field.name)
                if value:
                    opt("/".join(value), **cell_args)

                else:
                    opt("", **cell_args)

            else:
                opt(getattr(h, field.name), **cell_args)

        table.add(row)

    doc.add(table)

    return doc


@beartype
def story_grid(ctx: haxorg_cli.CliRunContext) -> None:
    assert ctx.opts.generate
    assert ctx.opts.generate.story_grid
    node = haxorg_cli.parseFile(ctx, Path(ctx.opts.generate.story_grid.infile))
    headers = rec_node(node)

    doc = get_html_story_grid(headers)
    Path(ctx.opts.generate.story_grid.outfile).write_text(str(doc))


@click.command("story_grid")
@haxorg_cli.get_wrap_options(haxorg_opts.StoryGridOpts)
@click.pass_context
def story_grid_cli(ctx: click.Context, **kwargs: Any) -> None:
    story_grid(haxorg_cli.get_run(ctx))
