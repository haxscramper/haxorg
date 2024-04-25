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

from pathlib import Path
import rich_click as click

import py_haxorg.pyhaxorg_wrap as org
from py_haxorg.pyhaxorg_utils import evalDateTime, formatOrgWithoutTime
from py_scriptutils.script_logging import log
from beartype import beartype
from beartype.typing import List, Optional, Literal, Tuple, Dict
from py_scriptutils.datetime_utils import format_iso8601, format_iso8601_date
from datetime import datetime
from dataclasses import field, dataclass
import json

CAT = "gantt_timeline"


@beartype
@dataclass
class WeekdayClose():
    pass


@beartype
@dataclass
class RangeClose():
    start: datetime
    end: datetime


@beartype
@dataclass
class Event():
    start: datetime
    end: datetime
    name: str
    completion: Optional[int] = None
    nested: List['Event'] = field(default_factory=list)

    hasHours: bool = True
    hasMinutes: bool = True
    hasSeconds: bool = True

    def getConvexTime(self) -> Tuple[datetime, datetime]:
        pass

    def getMinMax(self) -> Tuple[datetime, datetime]:
        pass

    def toJson(self) -> Dict:
        return {
            "start": format_iso8601(self.start),
            "stop": format_iso8601(self.end),
            "name": self.name,
            "start_date_only": format_iso8601_date(self.start),
            "stop_date_only": format_iso8601_date(self.end),
            "completion": self.completion,
            "nested": [it.toJson() for it in self.nested],
        }


@beartype
@dataclass
class Gantt():
    title: Optional[str] = None
    dateFormat: Optional[str] = None
    today: Optional[datetime] = None
    printScale: Optional[Literal["daily", "weekly", "monthly", "yearly"]] = None
    projectStart: Optional[datetime] = None
    projectEnd: Optional[datetime] = None
    legend: Optional[str] = None

    barstyle: Optional[str] = None
    calendar: Optional[str] = None
    weekEnds: Optional[str] = None
    holidays: Optional[str] = None

    events: List[Event] = field(default_factory=list)
    timeSpan: Optional[Tuple[datetime, datetime]] = None

    def toJson(self) -> Dict:
        res = {"events": [e.toJson() for e in self.events]}

        return res


def getGantt(doc: org.Document) -> Gantt:
    res = Gantt()

    @beartype
    @dataclass
    class Ctx():
        event: Optional[Event] = None
        filled: bool = False

    stack: List[Ctx] = []

    def aux(node: org.Org):
        match node:
            case org.Subtree():
                start: Optional[datetime] = None
                end: Optional[datetime] = None

                period: org.SubtreePeriod
                for period in node.getTimePeriods(
                        org.IntSetOfSubtreePeriodKind([org.SubtreePeriodKind.Titled])):
                    if period.to:
                        start = evalDateTime(period.from_.getStatic().time)
                        end = evalDateTime(period.to.getStatic().time)

                    else:
                        start = evalDateTime(period.from_.getStatic().time)
                        end = start

                if start and end:
                    stack.append(
                        Ctx(
                            event=Event(
                                name=formatOrgWithoutTime(node.title),
                                start=start,
                                end=end,
                            ),
                            filled=True,
                        ))

                else:
                    stack.append(Ctx())

                for sub in node:
                    aux(sub)

                last = stack.pop()
                if 0 == len(stack):
                    if last.filled:
                        res.events.append(last.event)

                else:
                    if last.filled:
                        backset = 1
                        _len = len(stack)
                        while backset < _len and not stack[_len - backset].filled:
                            backset += 1

                        if backset < _len:
                            stack[_len - backset].event.nested.append(last.event)

                        else:
                            assert isinstance(last.event, Event), type(last.event)
                            res.events.append(last.event)

            case _:
                for sub in node:
                    aux(sub)

    aux(doc)

    return res


class GanttOpts(BaseModel, extra="forbid"):
    infile: Path
    outfile: Path


def cli_options(f):
    return apply_options(f, options_from_model(GanttOpts))


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@cli_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", GanttOpts, config=config, kwargs=kwargs)
    opts: GanttOpts = ctx.obj["root"]
    log(CAT).info("starting")
    node = org.parseFile(str(opts.infile.resolve()), org.OrgParseParameters())

    gantt = getGantt(node)
    opts.outfile.write_text(json.dumps(gantt.toJson(), indent=2))

    log(CAT).info("ok")


if __name__ == "__main__":
    cli()
