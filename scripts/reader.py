#!/usr/bin/env python

from rich.logging import RichHandler
import logging
from enum import Enum
from datetime import datetime
from pprint import pprint
from dataclasses import dataclass, field
from dataclasses_json import dataclass_json, config, Undefined
import json
from typing import *


logging.basicConfig(
    level="NOTSET",
    format="%(message)s",
    datefmt="[%X]",
    handlers=[
        RichHandler(
            markup=True,
            enable_link_path=False,
            show_time=False,
        )
    ],
)

for name in logging.root.manager.loggerDict:
    logger = logging.getLogger(name)
    logger.setLevel(logging.WARNING)

    log = logging.getLogger("rich")
    log.setLevel(logging.DEBUG)

    log = logging.getLogger("rich")
    log.setLevel(logging.DEBUG)

log = logging.getLogger("main")


def jnode(dct):
    if "kind" in dct:
        if dct["kind"] == "List":
            dct["kind"] = "OList"

        kind = dct["kind"]
        if kind in globals():
            return globals().get(kind).from_dict(dct)
        else:
            log.error(dct)
            raise Exception()
    else:
        raise ValueError("Invalid value for 'kind' field")


def jnode_list(lst: List) -> List['Org']:
    result: List['Org'] = []
    for item in lst:
        result.append(jnode(item))

    return result


class OrgKind(Enum):
    StmtList = "StmtList"
    Row = "Row"
    Table = "Table"
    HashTag = "HashTag"
    Completion = "Completion"
    Paragraph = "Paragraph"
    BigIdent = "BigIdent"
    Link = "Link"
    Bold = "Bold"
    Italic = "Italic"
    Strike = "Strike"
    Monospace = "Monospace"
    Verbatim = "Verbatim"
    RawText = "RawText"
    OList = "OList"
    ListItem = "ListItem"
    Center = "Center"
    Par = "Par"
    Quote = "Quote"
    Example = "Example"
    Code = "Code"
    Time = "Time"
    SubtreeLog = "SubtreeLog"
    TimeRange = "TimeRange"
    Subtree = "Subtree"
    Newline = "Newline"
    Space = "Space"
    Word = "Word"
    Punctuation = "Punctuation"
    MarkQuote = "MarkQuote"
    Caption = "Caption"
    CommandGroup = "CommandGroup"
    Placeholder = "Placeholder"
    InlineMath = "InlineMath"


@dataclass_json
@dataclass
class Org:

    kind: OrgKind = OrgKind.Space
    subnodes: List["Org"] = field(metadata=config(
        decoder=jnode_list), default_factory=list)
    parent: Optional['Org'] = None

    def __getitem__(self, index: int) -> 'Org':
        return self.subnodes[index]


@dataclass_json
@dataclass
class StmtList(Org):
    pass


@dataclass_json
@dataclass
class Paragraph(Org):
    pass


@dataclass_json
@dataclass
class Leaf(Org):
    text: str = ""


@dataclass_json
@dataclass
class Link(Org):
    pass


@dataclass_json
@dataclass
class OList(Org):
    pass


@dataclass_json
@dataclass
class Par(Org):
    pass


@dataclass_json
@dataclass
class ListItem(Org):
    pass


@dataclass_json
@dataclass
class MarkQuote(Org):
    pass


@dataclass_json
@dataclass
class Verbatim(Org):
    pass


@dataclass_json
@dataclass
class Italic(Org):
    pass


@dataclass_json
@dataclass
class Bold(Org):
    pass


@dataclass_json
@dataclass
class Caption(Org):
    text: Paragraph = Paragraph()


@dataclass_json
@dataclass
class Quote(Org):
    text: Paragraph = Paragraph()


@dataclass_json
@dataclass
class InlineMath(Org):
    pass


@dataclass_json
@dataclass
class Word(Leaf):
    pass


@dataclass_json
@dataclass
class Placeholder(Leaf):
    pass


@dataclass_json
@dataclass
class RawText(Leaf):
    pass


@dataclass_json
@dataclass
class Space(Leaf):
    pass


@dataclass_json
@dataclass
class Newline(Leaf):
    pass


@dataclass_json
@dataclass
class BigIdent(Leaf):
    pass


@dataclass_json
@dataclass
class Punctuation(Leaf):
    pass


class ExportOption:
    backend: str
    args: Any


@dataclass_json
@dataclass
class Property:
    export_option: Optional[ExportOption] = None


@dataclass_json
@dataclass
class Drawer:
    props: List[Property] = field(default_factory=list)
    log: dict = field(default_factory=dict)


@dataclass_json
@dataclass
class SubtreeLog(Org):
    props: List[Property] = field(default_factory=list)
    log: dict = field(default_factory=dict)


class RepeatMode(Enum):
    None_ = "None"
    Exact = "Exact"
    FirstMatch = "FirstMatch"
    SameDay = "SameDay"


class RepeatPeriod(Enum):
    Year = "Year"
    Month = "Month"
    Week = "Week"
    Day = "Day"
    Hour = "Hour"
    Minute = "Minute"


@dataclass_json
@dataclass
class Repeat:
    mode: str
    period: str
    count: int


@dataclass_json
@dataclass
class StaticTime:
    time: datetime = field(
        metadata=config(
            encoder=datetime.isoformat,
            decoder=datetime.fromisoformat
        )
    )

    repeat: Optional[Repeat] = None


@dataclass_json
@dataclass
class DynamicTime:
    expr: str


@dataclass_json
@dataclass
class Time(Org):
    isActive: bool = False
    isStatic: bool = False

    repeat: Optional[Repeat] = None
    static: Optional[StaticTime] = None
    dynamic: Optional[DynamicTime] = None


@dataclass_json
@dataclass
class TimeRange(Org):
    tfrom: Optional[Time] = field(
        default_factory=lambda: None,
        metadata=config(field_name="from"))

    tto: Optional[Time] = field(
        default_factory=lambda: None,
        metadata=config(field_name="to"))


@dataclass_json
@dataclass
class Subtree(Org):
    level: int = 0
    todo: Optional[str] = None
    tags: List[str] = field(default_factory=list)
    logbook: List[SubtreeLog] = field(default_factory=list)
    description: Optional[str] = None
    completion: Optional[Any] = None
    title: Optional[Paragraph] = field(
        metadata=config(decoder=jnode), default=Paragraph())
    drawer: Drawer = Drawer()



sem: Org = None
# Usage example
with open("/tmp/parse_corpus.json", "r") as file:
    j = json.load(file)
    sem = jnode(j)

with open("/tmp/parsed", "w+t") as file:
    pprint(sem, file, width=150)

log.info("Done")

