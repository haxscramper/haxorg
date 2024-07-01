import py_haxorg.pyhaxorg_wrap as org
from py_textlayout.py_textlayout_wrap import TextLayout, BlockId
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk

from beartype.typing import List, Optional, Dict
from enum import Enum
from beartype import beartype

from py_exporters.export_base import ExporterBase
from py_exporters.export_ultraplain import ExporterUltraplain
from py_haxorg.pyhaxorg_utils import formatDateTime, formatHashTag


@beartype
class ExporterTypst(ExporterBase):
    t: TextLayout

    def __init__(self, CRTP_derived=None):
        super().__init__(CRTP_derived or self)
        self.t = TextLayout()

    def newOrg(self, node: org.Org):
        return self.t.text("TODO" + str(node.getKind()))

    def string(self, node: str | BlockId) -> BlockId:
        if isinstance(node, str):
            return self.t.text(node)

        else:
            return node

    def surround(self, text: str, nodes: List[BlockId]) -> BlockId:
        return self.t.line([self.string(text), *nodes, self.string(text)])

    def escape(self, text: str) -> str:
        res = ""
        for ch in text:
            if ch in ["@", "#", "<"]:
                res += "\\" + ch

            else:
                res += ch

        return res

    def call(
            self,
            name: str,
            kwargs: Dict[str, BlockId | str] = dict(),
            body: List[BlockId] = list(),
    ) -> BlockId:
        return self.t.stack([
            self.string(f"#{name}("),
            self.t.stack([
                self.t.line([
                    self.string(key),
                    self.string(": "),
                    self.string(kwargs[key]),
                    self.string(","),
                ]) for key in sorted(kwargs.keys())
            ]),
            self.string(")[") if body else self.string(")"),
        ] + [
            self.t.stack([
                body[idx],
                self.string("]") if idx == len(body) - 1 else self.string("]["),
            ]) for idx in range(len(body))
        ])

    def lineSubnodes(self, node: org.Org) -> BlockId:
        return self.t.line([self.exp.eval(it) for it in node])

    def stackSubnodes(self, node: org.Org) -> BlockId:
        return self.t.stack([self.exp.eval(it) for it in node])

    def evalParagraph(self, node: org.Paragraph) -> BlockId:
        return self.lineSubnodes(node)

    def evalAnnotatedParagraph(self, node: org.AnnotatedParagraph) -> BlockId:
        result = self.lineSubnodes(node)

        return result

    def evalNewline(self, node: org.Newline) -> BlockId:
        return self.string(node.text)

    def evalWord(self, node: org.Word) -> BlockId:
        return self.string(self.escape(node.text))

    def evalBigIdent(self, node: org.BigIdent) -> BlockId:
        return self.string(self.escape(node.text))

    def evalRawText(self, node: org.RawText) -> BlockId:
        return self.string(self.escape(node.text))

    def evalPunctuation(self, node: org.Punctuation) -> BlockId:
        return self.string(self.escape(node.text))

    def evalSpace(self, node: org.Space) -> BlockId:
        return self.string(node.text)

    def evalBold(self, node: org.Bold) -> BlockId:
        return self.surround("*", [self.lineSubnodes(node)])

    def evalMonospace(self, node: org.Monospace) -> BlockId:
        return self.surround("`", [self.lineSubnodes(node)])

    def evalVerbatim(self, node: org.Verbatim) -> BlockId:
        return self.surround("*", [self.lineSubnodes(node)])

    def evalItalic(self, node: org.Italic) -> BlockId:
        return self.surround("_", [self.lineSubnodes(node)])

    def evalAtMention(self, node: org.AtMention) -> BlockId:
        return self.string(self.escape("@" + node.text))

    def evalTextSeparator(self, node: org.TextSeparator) -> BlockId:
        return self.call("line", dict(length="100%"))

    def evalHashTag(self, node: org.HashTag) -> BlockId:
        return self.string(self.escape(formatHashTag(node)))

    def evalQuote(self, node: org.Quote) -> BlockId:
        return self.call("quote", body=[self.stackSubnodes(node)])

    def evalExport(self, node: org.Export) -> BlockId:
        if node.exporter == "typst":
            return self.string(node.content)

        else:
            return self.string("")

    def evalSubtree(self, node: org.Subtree) -> BlockId:
        if node.isComment or node.isArchived:
            return self.string("")

        res = self.t.stack([])

        self.t.add_at(
            res,
            self.t.line([
                self.string("=" * node.level + " "),
                self.exp.eval(node.title),
            ]))

        for it in node:
            self.t.add_at(res, self.exp.eval(it))

        return res

    def evalDocument(self, node: org.Document) -> BlockId:
        res = self.t.stack([])
        for it in node:
            self.t.add_at(res, self.exp.eval(it))

        return res

    def evalMacro(self, node: org.Macro) -> BlockId:
        return self.string("")

    def evalTime(self, node: org.Time) -> BlockId:
        return self.string(formatDateTime(node.getStatic().time))

    def evalTimeRange(self, node: org.TimeRange) -> BlockId:
        return self.t.line(
            [self.exp.eval(node.from_),
             self.string("--"),
             self.exp.eval(node.to)])

    def evalList(self, node: org.List) -> BlockId:
        return self.stackSubnodes(node)

    def evalListItem(self, node: org.ListItem) -> BlockId:
        if node.isDescriptionItem():
            return self.t.line([
                self.string("/ "),
                self.exp.eval(node.header),
                self.string(": "),
                self.stackSubnodes(node),
            ])
            
        else:
            return self.t.line([
                self.string("- "),
                self.stackSubnodes(node),
            ])
