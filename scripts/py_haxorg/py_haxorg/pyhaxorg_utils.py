from dataclasses import dataclass
from dataclasses import field
from datetime import datetime
import itertools
import os
from pathlib import Path
import shutil

from beartype import beartype
from beartype.typing import Dict
from beartype.typing import List
from beartype.typing import Optional
from beartype.typing import Set
from beartype.typing import Union
from py_exporters.export_ultraplain import ExporterUltraplain
from py_haxorg.pyhaxorg_wrap import UserTime
from py_haxorg.pyhaxorg_wrap import UserTimeBreakdown
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.script_logging import ExceptionContextNote
from py_scriptutils.script_logging import log

CAT = "org"

TODO_ITEMS = set([
    "TODO",
    "DONE",
    "COMPLETED",
    "NEXT",
    "WIP",
    "TRIAGED",
    "FAILED",
    "PARTIALLY",
    "CANCELLED",
    "PAUSED",
    "REVIEW",
])

ADMONITION_ITEMS = set([
    "QUESTION",
    "NOTE",
    "IDEA",
    "WARNING",
    "ERROR",
    "BUG",
    "FIXME",
    "XXX",
    "XXXX",
    "XXXXX",
    "IMPLEMENT",
    "TEMP",
    "HACK",
])

SEMANTIC_BIG_IDENT_ITEMS = TODO_ITEMS.union(ADMONITION_ITEMS)


@beartype
def evalDateTime(time: UserTime) -> datetime:
    brk: org.UserTimeBreakdown = time.getBreakdown()
    kwargs: Dict[str, int] = dict(
        year=brk.year or 1970,
        month=brk.month or 1,
        day=brk.day or 1,
    )

    if brk.hour:
        kwargs["hour"] = brk.hour

    if brk.minute:
        kwargs["minute"] = brk.minute

    if brk.second:
        kwargs["second"] = brk.second

    return datetime(**kwargs)  # type: ignore


@beartype
def normalize(it: str) -> str:
    result = ""
    for ch in it:
        if ch not in ["_", "-"]:
            result += ch.lower()

    return result


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
def getFlatTags(tag: Union[org.HashTag, org.HashTagText]) -> List[List[str]]:

    def aux(parents: List[str], tag: org.HashTagText) -> List[List[str]]:
        result: List[List[str]] = []
        if len(tag.subtags) == 0:
            return [parents + [tag.head]]

        else:
            for subtag in tag.subtags:
                for flat in aux(parents + [tag.head], subtag):
                    result.append(flat)

        return result

    if isinstance(tag, org.HashTag):
        return aux([], tag.text)

    else:
        return aux([], tag)


@beartype
def formatHashTag(node: Union[org.HashTag, org.HashTagText]) -> str:

    def aux(sub: org.HashTagText) -> str:
        if len(sub.subtags) == 0:
            return sub.head

        elif len(sub.subtags) == 1:
            return sub.head + "##" + aux(sub.subtags[0])

        else:
            return sub.head + "##" + "[" + ",".join([aux(it) for it in sub.subtags]) + "]"

    if isinstance(node, org.HashTag):
        return "#" + aux(node.text)

    else:
        return "#" + aux(node)


@beartype
def formatOrgWithoutPrefix(node: org.Org | List[org.Org],
                           skip: Set[org.OrgSemKind]) -> str:
    items = []

    def add(it: org.Org) -> None:
        items.append(ExporterUltraplain.getStr(it))

    in_skip = True
    for item in node:  # type: ignore
        if in_skip and item.getKind() in skip:
            continue

        in_skip = False
        add(item)

    return "".join(items).strip()


@beartype
def formatOrgWithoutTime(node: org.Org | List[org.Org]) -> str:
    return formatOrgWithoutPrefix(
        node,
        set([
            org.OrgSemKind.Time,
            org.OrgSemKind.TimeRange,
        ]),
    )


@beartype
def getTitleBody(node: org.Subtree,
                 todo_items: Set[str] = SEMANTIC_BIG_IDENT_ITEMS) -> List[org.Org]:
    title = [sub for sub in node.title]  # type: ignore
    while title and isinstance(title[0], (org.Time, org.TimeRange, org.Space)) or (
            isinstance(title[0], org.BigIdent) and title[0].text in todo_items):
        title.pop(0)

    while title and isinstance(title[-1], org.Space):
        title.pop()

    return title


@beartype
def getSubtreeTime(node: org.Subtree, kind: org.SubtreePeriodKind) -> Optional[datetime]:
    result: Optional[datetime] = None
    time: org.SubtreePeriod
    for time in node.getTimePeriods(org.IntSetOfSubtreePeriodKind([  # type: ignore
            kind
    ])):
        result = evalDateTime(time.from_)

    return result


@beartype
def getCreationTime(node: org.Org) -> Optional[datetime]:
    match node:
        case org.Subtree():
            return getSubtreeTime(node, org.SubtreePeriodKind.Created) or getSubtreeTime(
                node, org.SubtreePeriodKind.Titled)

        case org.Paragraph() if node.hasTimestamp():
            return evalDateTime(node.getTimestamps()[0])

        case _:
            return None


@beartype
def getAttachments(node: org.Org) -> List[org.Link]:
    result = []

    def visit(it: org.Org) -> None:
        if isinstance(it, org.Link) and it.target.isAttachment():
            result.append(it)

    org.eachSubnodeRec(node, visit)

    return result


@beartype
def doExportAttachments(
    base: Path,
    destination: Path,
    attachments: List[org.Link],
    backends: List[str],
) -> None:
    assert base.exists() and base.is_file(), base
    assert destination.exists() and destination.is_dir(), destination
    for item in attachments:
        path = item.target.getAttachment().file
        do_attach = item.getAttrs("attach-on-export")
        if do_attach and 0 < len(do_attach) and (do_attach[0].getString() == "t" or
                                                 normalize(do_attach[0].getString())
                                                 in [normalize(it) for it in backends]):

            method = item.getAttrs("attach-method")
            op = method[0].getString()
            with ExceptionContextNote(
                    "Attachment operation {}, for base path '{}', destination '{}', relative '{}'"
                    .format(
                        op,
                        base.parent,
                        destination,
                        path,
                    )):
                match op:
                    case "copy" | "symlink":
                        src = base.parent.joinpath(path)
                        if src.exists():
                            dst = destination.joinpath(path)
                            if src != dst:
                                if op == "copy":
                                    shutil.copy(src=src, dst=dst)
                                    log(CAT).info(f"Copied {path}")

                                elif op == "symlink":
                                    if dst.exists() or dst.is_symlink():
                                        os.unlink(dst)

                                    assert not dst.exists()
                                    assert src.exists()

                                    dst.symlink_to(src)
                                    log(CAT).info(f"Symlinked {path}")

                    case _:
                        assert False


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
