import py_haxorg.pyhaxorg_wrap as org
import json
from py_exporters.export_base import ExporterBase
from beartype import beartype
from dataclasses import dataclass, field
from beartype.typing import Union, List, Dict, Set, Tuple
from py_scriptutils.script_logging import log
from py_haxorg.pyhaxorg_utils import formatDateTime

CAT = "export.pandoc"

Json = Union[str, int, float, None, Dict, List]
AttrKv = List[Tuple[str, Json]]


@beartype
def Attr(identifier: str, classes: List[str] = [], kvpairs: List[AttrKv] = []) -> Json:
    return [identifier, classes, *[[key, value] for key, value in kvpairs]]


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
    def Node(kind: str, content: Json) -> 'PandocRes':
        return PandocRes.Single({"k": kind, "c": content})

    def toJson(self) -> List[Json]:
        return [it for it in self.unpacked]


osk = org.OrgSemKind


@beartype
class ExporterPandoc(ExporterBase):

    def __init__(self, CRTP_derived=None):
        super().__init__(CRTP_derived or self)

    def newOrg(self, node: org.Org) -> PandocRes:
        return PandocRes.Single("TODO " + str(node.getKind()))

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
        return PandocRes.Node("Str", node.text)
    
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

    def evalSubtree(self, node: org.Subtree) -> PandocRes:

        attrs: AttrKv = []
        if node.treeId:
            attrs.append(("id", node.treeId))

        result = PandocRes.Node("Header", [
            node.level,
            Attr("preface", [], attrs),
            self.content(node.title),
        ])

        for sub in node:
            result.unpacked += self.eval(sub).unpacked

        return result

    def evalDocument(self, node: org.Org) -> PandocRes:
        return PandocRes.Single({
            "pandoc-api-version": [1, 22, 2, 1],
            "meta": {},
            "blocks": self.content(node, set([
                osk.Newline,
                osk.Space,
            ]))
        })
