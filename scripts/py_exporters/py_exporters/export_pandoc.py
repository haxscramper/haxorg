from dataclasses import dataclass
from dataclasses import field
import itertools

from beartype import beartype
from beartype.typing import Any
from beartype.typing import List
from beartype.typing import Optional
from beartype.typing import Set
from py_exporters.export_base import ExporterBase
from py_haxorg.pyhaxorg_utils import formatDateTime
from py_haxorg.pyhaxorg_utils import formatHashTag
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.json_utils import Json

CAT = "export.pandoc"


@beartype
@dataclass
class AttrKv():
    key: str
    value: Json


@beartype
def Attr(identifier: str, classes: List[str] = [], kvpairs: List[AttrKv] = []) -> Json:
    return [identifier, classes, [[it.key, it.value] for it in kvpairs]]


@beartype
@dataclass
class PandocRes():
    unpacked: List[Json] = field(default_factory=list)
    debug: str = ""

    @staticmethod
    def Single(value: Json) -> 'PandocRes':
        return PandocRes(unpacked=[value])

    @staticmethod
    def Multiple(value: List[Json]) -> 'PandocRes':
        return PandocRes(unpacked=value)

    @staticmethod
    def Node(kind: str, content: Json, debug: Optional[str] = None) -> 'PandocRes':
        if debug:
            return PandocRes.Single({"t": kind, "c": content, "debug": debug})

        else:
            return PandocRes.Single({"t": kind, "c": content})

    def toJson(self) -> List[Json]:
        return [it for it in self.unpacked]


osk = org.OrgSemKind
NonTopLevel = set([osk.Newline, osk.Space])


@beartype
class ExporterPandoc(ExporterBase):

    def __init__(self, CRTP_derived: Any = None) -> None:
        super().__init__(CRTP_derived or self)

    def newOrg(self, node: org.Org) -> PandocRes:
        return PandocRes.Node("Str", "TODO " + str(node.getKind()))

    def content(self, node: org.Org, skip: Set[org.OrgSemKind] = set()) -> List[Json]:
        result: List[Json] = []

        for sub in node:
            if sub.getKind() not in skip:
                for item in self.eval(sub).unpacked:
                    result.append(item)

        return result

    def evalParagraph(self, node: org.Paragraph) -> PandocRes:
        return PandocRes.Node("Para", self.content(node))

    def evalBold(self, node: org.Bold) -> PandocRes:
        return PandocRes.Node("Strong", self.content(node))

    def evalItalic(self, node: org.Italic) -> PandocRes:
        return PandocRes.Node("Emph", self.content(node))

    def evalWord(self, node: org.Word) -> PandocRes:
        return PandocRes.Node("Str", node.text, debug=str(node.getKind()))

    def evalSpace(self, node: org.Space) -> PandocRes:
        return PandocRes.Node("Str", node.text)

    def evalTime(self, node: org.Time) -> PandocRes:
        return PandocRes.Node("Str", formatDateTime(node.getStatic().time))

    def evalNewline(self, node: org.Newline) -> PandocRes:
        return PandocRes.Node("Str", node.text)

    def evalBigIdent(self, node: org.BigIdent) -> PandocRes:
        return PandocRes.Node("Str", node.text)

    def evalPunctuation(self, node: org.Punctuation) -> PandocRes:
        return PandocRes.Node("Str", node.text)

    def evalAtMention(self, node: org.AtMention) -> PandocRes:
        return PandocRes.Node("Str", "@" + node.text)

    def evalBlockCode(self, node: org.BlockCode) -> PandocRes:
        return PandocRes()

    def evalBlockExample(self, node: org.BlockExample) -> PandocRes:
        return PandocRes()

    def evalBlockExport(self, node: org.BlockExport) -> PandocRes:
        return PandocRes()

    def evalInlineFootnote(self, node: org.InlineFootnote) -> PandocRes:
        return PandocRes()

    def evalListItem(self, node: org.ListItem) -> PandocRes:
        return PandocRes.Multiple(
            list(
                itertools.chain(*[
                    self.eval(it).unpacked
                    for it in node
                    if it.getKind() not in [osk.Newline]
                ])))

    def evalList(self, node: org.List) -> PandocRes:
        return PandocRes.Node("BulletList", [self.content(node)])

    def evalTextSeparator(self, node: org.TextSeparator) -> PandocRes:
        return PandocRes.Node("HorizontalRule", "")

    def evalTimeRange(self, node: org.TimeRange) -> PandocRes:
        return PandocRes.Node(
            "Str", "{}--{}".format(
                formatDateTime(node.from_.getStatic().time),
                formatDateTime(node.to.getStatic().time),
            ))

    def evalHashTag(self, node: org.HashTag) -> PandocRes:
        return PandocRes.Node("Str", formatHashTag(node))

    def evalMonospace(self, node: org.Monospace) -> PandocRes:
        return PandocRes.Node("Code", [Attr(""), "".join([it.text for it in node])])

    def evalVerbatim(self, node: org.Verbatim) -> PandocRes:
        return PandocRes.Node("Code", [Attr(""), "".join([it.text for it in node])])

    def evalEscaped(self, node: org.Escaped) -> PandocRes:
        return PandocRes.Node("Str", node.text)

    def evalSubtree(self, node: org.Subtree) -> PandocRes:

        attrs: List[AttrKv] = []
        if node.treeId:
            attrs.append(AttrKv("id", node.treeId))

        result = PandocRes.Node("Header", [
            node.level,
            Attr("preface", [], attrs),
            self.content(node.title, NonTopLevel),
        ])

        for sub in node:
            if sub.getKind() not in NonTopLevel:
                result.unpacked += self.eval(sub).unpacked

        return result

    def evalDocument(self, node: org.Org) -> PandocRes:
        return PandocRes.Single({
            "pandoc-api-version": [1, 23, 1],
            "meta": {},
            "blocks": self.content(node, NonTopLevel)
        })
