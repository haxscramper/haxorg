#!/usr/bin/env python

from py_cli.haxorg_cli import (
    pack_context,
    BaseModel,
)

from py_scriptutils.toml_config_profiler import (
    make_config_provider,
    run_config_provider,
    apply_options,
    options_from_model,
    merge_cli_model,
)

from py_exporters.export_html import ExporterHtml, add_html, add_new
from py_exporters.export_ultraplain import ExporterUltraplain

import py_haxorg.pyhaxorg_wrap as org
from py_haxorg.pyhaxorg_utils import evalDateTime

from pathlib import Path
from beartype import beartype
from dataclasses import dataclass, field, fields
from beartype.typing import Optional, Tuple, List, Union
import dominate.tags as tags
import dominate
from dominate.util import text
from datetime import datetime, timedelta


class StoryGridOpts(BaseModel, extra="forbid"):
    infile: Path
    outfile: Path


import rich_click as click


def cli_options(f):
    return apply_options(f, options_from_model(StoryGridOpts))


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


def rec_filter_subnodes(node: org.Org, target: List[org.OrgSemKind]) -> List[org.Org]:
    result = []
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
    result = []
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
                        plain = ExporterUltraplain.getStr(prop.getCustomRaw().value)
                        header.shift = plain.split("/")

                    case "story_duration":
                        plain = ExporterUltraplain.getStr(prop.getCustomRaw().value)
                        header.duration = plain

                    case _:
                        assert not prop.getName().startswith("story_"), prop.getName()

            for tag in node.tags:
                header.tags.append(tag)

            def count_words(node: org.Org):
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

            result.append(header)
            for sub in node:
                if isinstance(sub, org.Subtree):
                    result += rec_node(sub)

                elif isinstance(sub, org.List):
                    if sub.isDescriptionList():
                        for item in sub:
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
                                                header.time = evalDateTime(it.getStatic().time)

                                            case org.TimeRange():
                                                header.time = (
                                                    evalDateTime(it.from_.getStatic().time),
                                                    evalDateTime(it.to.getStatic().time),
                                                )

                                    case _:
                                        assert not tag[0].startswith("story_"), tag

                    else:
                        count_words(sub)

                else:
                    count_words(sub)

        case org.Document():
            for sub in node:
                result += rec_node(sub)

    return result


def to_html(node: org.Org | List[org.Org]):
    if isinstance(node, list):
        html = []
        for item in node:
            add_html(html, to_html(item))

        return html

    elif isinstance(node, (str, int)):
        return text(str(node))

    else:
        html = ExporterHtml()
        return html.exp.evalTop(node)


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
    years, diff_seconds = divmod(diff_seconds, seconds_per_year)
    months, diff_seconds = divmod(diff_seconds, seconds_per_month)
    days, diff_seconds = divmod(diff_seconds, seconds_per_day)
    hours, diff_seconds = divmod(diff_seconds, seconds_per_hour)
    minutes, seconds = divmod(diff_seconds, seconds_per_minute)

    # Append non-zero time periods to the duration_parts list
    if years > 0:
        duration_parts.append(f"{int(years)}y")
    if months > 0:
        duration_parts.append(f"{int(months)}m")
    if days > 0:
        duration_parts.append(f"{int(days)}d")
    if hours > 0:
        duration_parts.append(f"{int(hours)}h")
    if minutes > 0:
        duration_parts.append(f"{int(minutes)}min")
    if seconds > 0 or not duration_parts:
        duration_parts.append(f"{int(seconds)}s")

    return duration_parts


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@cli_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", StoryGridOpts, config=config, kwargs=kwargs)
    opts: StoryGridOpts = ctx.obj["root"]
    node = org.parseFile(str(opts.infile.resolve()), org.OrgParseParameters())
    headers = rec_node(node)

    with open("/tmp/res.txt", "w") as file:
        file.write(org.treeRepr(node, colored=False))

    doc = dominate.document()

    table = tags.table(border=1, style='border-collapse: collapse; width: 100%;')
    thead = tags.thead(style='position: sticky; top: 0; background-color: #ddd;')
    header_row = tags.tr()
    skipped = ["level", "pov", "tags"]
    for field in fields(Header([], 0)):
        if field.name in skipped:
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

        def opt(it, **kwargs):
            if it:
                row.add(add_new(tags.td(**kwargs), to_html(it)))

            else:
                row.add(tags.td())

        for field in fields(h):
            if field.name in skipped:
                continue

            elif field.name == "title":
                prefix = f"#{idx} " + "*" * h.level + " "
                opacity = (max_level - h.level) / max_level * 0.75
                row.add(
                    add_new(
                        tags.td(
                            style=f"background-color: rgba(255, 0, 0, {opacity:.2f});"),
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
                    opt(h.words)

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
                        opt(offset)
                        opt("{}".format(start.strftime("[%Y-%m-%d]")))

                    else:
                        opt(offset)
                        opt("{}-{}".format(
                            start.strftime("[%Y-%m-%d]"),
                            end.strftime("[%Y-%m-%d]"),
                        ))

                else:
                    opt("")
                    opt("")

            elif field.name == "shift":
                value = getattr(h, field.name)
                if value:
                    opt("/".join(value))

                else:
                    opt("")

            else:
                opt(getattr(h, field.name))

        table.add(row)

    doc.add(table)

    with open(opts.outfile, "w") as out:
        out.write(str(doc))

    print("parsed node ok")


if __name__ == "__main__":
    cli()
