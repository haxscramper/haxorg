import py_haxorg.pyhaxorg_wrap as org
from py_textlayout.py_textlayout_wrap import TextLayout, BlockId
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk

from beartype.typing import List, Optional
from typing import TYPE_CHECKING, NewType
from enum import Enum
from beartype import beartype
from datetime import datetime

from py_exporters.export_base import ExporterBase
from py_exporters.export_ultraplain import ExporterUltraplain
from py_scriptutils.script_logging import to_debug_json
from py_haxorg.pyhaxorg_utils import formatDateTime

class TexCommand(Enum):
    part = 1
    chapter = 2
    section = 3
    subsection = 4
    subsubsection = 5
    paragraph = 6
    subparagraph = 7
    textbf = 8


@beartype
class ExporterLatex(ExporterBase):
    t: TextLayout

    def __init__(self):
        super().__init__(self)
        self.t = TextLayout()

    def newOrg(self, node: org.Org):
        return self.t.text("TODO" + str(node.getKind()))

    def string(self, node: str | BlockId) -> BlockId:
        if isinstance(node, str):
            return self.t.text(node)

        else:
            return node

    def wrap(self, node: str | BlockId, opens: str, closes: str) -> BlockId:
        return self.t.line([self.string(opens), self.string(node), self.string(closes)])

    def command(
        self,
        name: str,
        args: List[str | BlockId] = [],
        opts: List[str | BlockId] = [],
    ) -> BlockId:
        return self.t.line([
            self.t.text("\\" + name), *[self.wrap(it, "[", "]") for it in opts],
            *[self.wrap(it, "{", "}") for it in args]
        ])

    def escape(self, value: str) -> str:
        res = ""
        for ch in value:
            if ch in {"&", "_", "}", "{", "#", "%"}:
                res += "\\" + ch
            else:
                res += ch

        return res

    def evalPlaceholder(self, node: org.Placeholder) -> BlockId:
        return self.command(
            "textsc",
            [self.command("texttt", [self.string(self.string("<" + node.text + ">"))])])

    def evalBigIdent(self, node: org.BigIdent) -> BlockId:
        specialColor = ""
        match node.text:
            case "TODO":
                specialColor = "green"
            case "WIP":
                specialColor = "brown"

        if specialColor:
            return self.command("fbox", [
                self.command(
                    "colorbox",
                    [self.string(specialColor),
                     self.string(self.escape(node.text))])
            ])

        else:
            return self.string(node.text)

    def evalNewline(self, node: org.Newline) -> BlockId:
        return self.string(node.text)

    def evalCenter(self, node: org.Center) -> BlockId:
        res = self.t.stack([])
        self.t.add_at(res, self.command("begin", [self.string("center")]))
        for item in node:
            self.t.add_at(res, self.exp.eval(item))

        self.t.add_at(res, self.command("end", [self.string("center")]))

        return res

    def evalLink(self, node: org.Link) -> BlockId:
        match node.getLinkKind():
        # case org.LinkKind.Id:
        #     return
        # target = node.resolve()
        # if target:
        #     res = self.t.line([
        #         self.command("ref", [
        #             self.string((self.getRefKind(target) or "") +
        #                         target.getReadableId())
        #         ])
        #     ])
        #
        #     if node.description:
        #         self.t.add_at(res, self.exp.eval(node.description))
        #
        #     return res
        #
        # else:
        #     return self.string("")2

            case org.LinkKind.Raw:
                return self.string(self.escape(node.getRaw().text))

            case _:
                return self.string(f"TODO LINK KIND {node.getLinkKind()}")

    def evalListItem(self, node: org.ListItem) -> BlockId:
        res = self.t.line([])
        self.t.add_at(res, self.command("item"))

        if node.isDescriptionItem():
            self.t.add_at(res, self.string(" "))
            self.t.add_at(res, self.command("textbf", [self.exp.eval(node.header)]))

        self.t.add_at(res, self.string(" "))
        self.t.add_at(res, self.stackSubnodes(node))

        return res

    def evalTextSeparator(self, node: org.TextSeparator) -> BlockId:
        return self.command("sepline")

    def evalPunctuation(self, node: org.Punctuation) -> BlockId:
        return self.string(self.escape(node.text))

    def evalWord(self, node: org.Word) -> BlockId:
        return self.string(self.escape(node.text))

    def evalSpace(self, node: org.Space) -> BlockId:
        return self.string(node.text)

    def evalUnderline(self, node: org.Underline) -> BlockId:
        return self.command("underline", [self.lineSubnodes(node)])

    def evalBold(self, node: org.Bold) -> BlockId:
        return self.command("textbf", [self.lineSubnodes(node)])

    def evalVerbatim(self, node: org.Verbatim) -> BlockId:
        return self.command("textsc", [self.lineSubnodes(node)])

    def evalRawText(self, node: org.RawText) -> BlockId:
        return self.string(self.escape(node.text))

    def evalEscaped(self, node: org.Escaped) -> BlockId:
        return self.string(self.escape(node.text))

    def evalItalic(self, node: org.Italic) -> BlockId:
        return self.command("textit", [self.lineSubnodes(node)])

    def lineSubnodes(self, node: org.Org) -> BlockId:
        return self.t.line([self.exp.eval(it) for it in node])

    def stackSubnodes(self, node: org.Org) -> BlockId:
        return self.t.stack([self.exp.eval(it) for it in node])

    def evalParagraph(self, node: org.Paragraph) -> BlockId:
        return self.lineSubnodes(node)

    def evalExport(self, node: org.Export) -> BlockId:
        if node.exporter != "latex" or node.placement:
            return self.string("")

        else:
            return self.string(node.content)

    def evalList(self, node: org.List) -> BlockId:
        return self.t.stack([
            self.command("begin", ["itemize"]),
            self.stackSubnodes(node),
            self.command("end", ["itemize"])
        ])

    def getLatexClassOptions(self, node: org.Document) -> List[BlockId]:
        property: org.SubtreeProperty = node.getProperty("ExportLatexClassOptions")
        if property:
            values: str = property.getExportLatexClassOptions().options[0]
            return [self.string(values.strip("[]"))]

        else:
            return []

    def getLatexClass(self, node: org.Document) -> str:
        property: org.SubtreeProperty = node.getProperty("ExportLatexClass")
        if property:
            return property.getExportLatexClass().latexClass

        else:
            return "book"

    def evalDocument(self, node: org.Document) -> BlockId:
        self.document = node
        res = self.t.stack([])

        self.t.add_at(
            res,
            self.command("documentclass",
                         opts=self.getLatexClassOptions(node),
                         args=[self.getLatexClass(node)]))

        self.t.add_at(res, self.command("usepackage", ["csquotes"]))
        self.t.add_at(res,
                      self.command("usepackage", opts=["bookmarks"], args=["hyperref"]))
        self.t.add_at(res, self.command("usepackage", ["xcolor"]))

        for value in TexCommand:
            cmd = self.t.line([self.string("\\newcommand")])
            arg_count = 1
            self.t.add_at(cmd, self.wrap("\\" + self.getOrgCommand(value), "{", "}"))
            self.t.add_at(cmd, self.wrap(self.string(str(arg_count)), "[", "]"))
            self.t.add_at(cmd, self.wrap(self.command(value.name, ["#1"]), "{", "}"))
            self.t.add_at(res, cmd)

        headerExports: List[org.Export] = []

        def visit(_id: org.Org):
            nonlocal headerExports
            if _id._is(osk.Export):
                exp: org.Export = _id._as(osk.Export)
                if exp.placement == "header":
                    headerExports.append(exp)

        for exp in headerExports:
            self.t.add_at(res, self.string(exp.content))

        self.t.add_at(
            res,
            self.string("""
\\newcommand*\\sepline{%
  \\begin{center}
    \\rule[1ex]{\\textwidth}{1pt}
  \\end{center}}

  \\newcommand{\\quot}[1]{\\textcolor{brown}{#1}}
        """))

        for it in node:
            if isinstance(it, org.Export) and it.placement == "header":
                self.t.add_at(res, self.string(it.content))

        self.t.add_at(res, self.command("begin", [self.string("document")]))

        for it in node:
            if isinstance(it, org.Export) and it.placement == "header":
                continue

            self.t.add_at(res, self.exp.eval(it))

        self.t.add_at(res, self.command("end", [self.string("document")]))

        return res

    def getOrgCommand(self, cmd: TexCommand) -> str:
        return "orgCmd" + str(cmd.name).capitalize()

    def getSubtreeCommand(self, node: org.Subtree) -> Optional[TexCommand]:
        lclass = self.getLatexClass(self.document)
        if lclass == "book":
            match node.level:
                case 1:
                    return TexCommand.chapter
                case 2:
                    return TexCommand.section
                case 3:
                    return TexCommand.subsection
                case 4:
                    return TexCommand.subsubsection
                case 5:
                    return TexCommand.paragraph
                case 6:
                    return TexCommand.subparagraph
                case _:
                    return TexCommand.textbf

        else:
            match node.level:
                case 1:
                    return TexCommand.section
                case 2:
                    return TexCommand.subsection
                case 3:
                    return TexCommand.subsubsection
                case 4:
                    return TexCommand.paragraph
                case 5:
                    return TexCommand.subparagraph
                case _:
                    return TexCommand.textbf

    def getRefKind(self, node: org.Org) -> Optional[str]:
        match node.getKind():
            case osk.Subtree:
                cmd = self.getSubtreeCommand(node)
                match cmd:
                    case TexCommand.chapter:
                        return "chap:"
                    case TexCommand.section:
                        return "sec:"
                    case TexCommand.part:
                        return "part:"

    def evalSubtree(self, node: org.Subtree) -> BlockId:
        res = self.t.stack([])
        title_text = self.t.line([])
        for item in node.title:
            match item.getKind():
                case osk.Space:
                    self.t.add_at(title_text, self.exp.eval(item))
                case _:
                    self.t.add_at(
                        title_text,
                        self.command("texorpdfstring", [
                            self.exp.eval(item),
                            self.string(self.escape(ExporterUltraplain.getStr(item)))
                        ]))

        cmd = self.getSubtreeCommand(node)
        self.t.add_at(
            res, self.command(self.getOrgCommand(cmd) if cmd else "texbf", [title_text]))

        if False and cmd in [TexCommand.part, TexCommand.chapter, TexCommand.section]:
            self.t.add_at(
                res,
                self.command(
                    "label",
                    [self.string(self.getRefKind(node) or "" + "\\the" + cmd.name)]))

        for it in node:
            self.t.add_at(res, self.exp.eval(it))

        return res

    def evalTime(self, node: org.Time) -> BlockId:
        return self.string(formatDateTime(node.getStatic().time))

    def evalTimeRange(self, node: org.TimeRange) -> BlockId:
        return self.t.line(
            [self.exp.eval(node.from_),
             self.string("--"),
             self.exp.eval(node.to)])
