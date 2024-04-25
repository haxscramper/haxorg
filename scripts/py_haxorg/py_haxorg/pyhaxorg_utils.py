from datetime import datetime
from py_haxorg.pyhaxorg_wrap import UserTime, UserTimeBreakdown
import py_haxorg.pyhaxorg_wrap as org
from beartype import beartype
from beartype.typing import List
from py_exporters.export_ultraplain import ExporterUltraplain
from beartype.typing import Dict
from dataclasses import dataclass, field


@beartype
def evalDateTime(time: UserTime) -> datetime:
    brk: org.UserTimeBreakdown = time.getBreakdown()
    kwargs = dict(
        year=brk.year,
        month=brk.month or 1,
        day=brk.day or 1,
    )

    if brk.hour:
        kwargs["hour"] = brk.hour

    if brk.minute:
        kwargs["minute"] = brk.minute

    if brk.second:
        kwargs["second"] = brk.second

    return datetime(**kwargs)


@beartype
def formatDateTime(time: UserTime) -> str:
    brk: org.UserTimeBreakdown = time.getBreakdown()
    format = "%Y-%m-%d"
    if brk.hour:
        format += " %H"

    if brk.minute:
        format += ":%M"

    if brk.second:
        format += ":%S"

    return evalDateTime(time).strftime(format)


@beartype
def getFlatTags(tag: org.HashTag) -> List[List[str]]:

    def aux(parents: List[str], tag: org.HashTag) -> List[str]:
        result: List[str] = []
        if len(tag.subtags) == 0:
            return [parents + [tag.head]]

        else:
            for subtag in tag.subtags:
                for flat in aux(parents + [tag.head], subtag):
                    result.append(flat)

        return result

    return aux([], tag)


@beartype
def formatHashTag(node: org.HashTag) -> str:

    def aux(sub: org.HashTag) -> str:
        if len(sub.subtags) == 0:
            return sub.head

        elif len(sub.subtags) == 1:
            return sub.head + "##" + aux(sub.subtags[0])

        else:
            return sub.head + "##" + "[" + ",".join([aux(it) for it in sub.subtags]) + "]"

    return "#" + aux(node)


@beartype
def formatOrgWithoutTime(node: org.Org) -> str:
    return ("".join([
        ExporterUltraplain.getStr(it) for it in node if it.getKind() not in [
            org.OrgSemKind.Time,
            org.OrgSemKind.TimeRange,
        ]
    ])).strip()


@beartype
@dataclass
class NodeIdProvider():
    nodeIdCounter: Dict[org.Org, int] = field(default_factory=dict)

    def getNodeId(self, value: org.Org) -> str:
        if isinstance(value, org.Subtree) and value.treeId:
            return value.treeId
        
        else:
            if value not in self.nodeIdCounter:
                self.nodeIdCounter[value] = len(self.nodeIdCounter)

            return str(self.nodeIdCounter[value])
