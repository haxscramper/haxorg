import py_haxorg.pyhaxorg as org
from py_textlayout.py_textlayout_wrap import TextLayout
from py_haxorg.pyhaxorg import OrgSemKind as osk

from beartype.typing import List, Optional
from typing import TYPE_CHECKING, NewType
from enum import Enum
from beartype import beartype
from datetime import datetime

from py_exporters.export_base import ExporterBase
from py_exporters.export_ultraplain import ExporterUltraplain

if TYPE_CHECKING:
    from py_textlayout.py_textlayout_wrap import BlockId
else:
    BlockId = NewType('BlockId', int)


class TexCommand(Enum):
    part = 1
    chapter = 2
    section = 3
    subsection = 4
    subsubsection = 5
    paragraph = 6
    subparagraph = 7


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

    def command(self,
                name: str,
                args: List[str | BlockId] = [],
                opts: List[str | BlockId] = []) -> BlockId:
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

    def evalPlaceholder(self, node: org.SemPlaceholder) -> BlockId:
        return self.command(
            "textsc",
            [self.command("texttt", [self.string(self.string("<" + node.text + ">"))])])

    def evalBigIdent(self, node: org.SemBigIdent) -> BlockId:
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

    def evalNewline(self, node: org.SemNewline) -> BlockId:
        return self.string(node.text)

    def evalCenter(self, node: org.SemCenter) -> BlockId:
        res = self.t.stack([])
        self.t.add_at(res, self.command("begin", [self.string("center")]))
        for item in node:
            self.t.add_at(res, self.exp.eval(item))

        self.t.add_at(res, self.command("end", [self.string("center")]))

        return res

    def evalLink(self, node: org.SemLink) -> BlockId:
        match node.getLinkKind():
            case org.LinkKind.Id:
                target = node.resolve()
                if target:
                    res = self.t.line([
                        self.command("ref", [
                            self.string((self.getRefKind(target) or "") +
                                        target.getReadableId())
                        ])
                    ])

                    if node.description:
                        self.t.add_at(res, self.exp.eval(node.description))

                    return res

                else:
                    return self.string("")

            case org.LinkKind.Raw:
                return self.string(self.escape(node.getRaw().text))

            case _:
                return self.string(f"TODO LINK KIND {node.getLinkKind()}")

    def evalListItem(self, node: org.SemListItem) -> BlockId:
        res = self.t.line([])
        if node.isDescriptionItem():
            self.t.add_at(
                res,
                self.command("item", [self.exp.eval(node.header)] if node.header else []))

        else:
            self.t.add_at(res, self.command("item"))

        self.t.add_at(res, self.string(" "))
        self.t.add_at(res, self.evalStack(node))

        return res

    def evalTextSeparator(self, node: org.SemTextSeparator) -> BlockId:
        return self.command("sepline")

    def evalPunctuation(self, node: org.SemPunctuation) -> BlockId:
        return self.string(self.escape(node.text))

    def evalWord(self, node: org.SemWord) -> BlockId:
        return self.string(self.escape(node.text))

    def evalSpace(self, node: org.SemSpace) -> BlockId:
        return self.string(node.text)

    def evalUnderline(self, node: org.SemUnderline) -> BlockId:
        return self.command("underline", [self.evalLine(node)])

    def evalBold(self, node: org.SemBold) -> BlockId:
        return self.command("bold", [self.evalLine(node)])

    def evalVerbatim(self, node: org.SemVerbatim) -> BlockId:
        return self.command("textsc", [self.evalLine(node)])

    def evalRawText(self, node: org.SemRawText) -> BlockId:
        return self.string(self.escape(node.text))

    def evalEscaped(self, node: org.SemEscaped) -> BlockId:
        return self.string(self.escape(node.text))

    def evalItalic(self, node: org.SemItalic) -> BlockId:
        return self.command("textit", [self.evalLine(node)])

    def evalLine(self, node: org.Org) -> BlockId:
        return self.t.line([self.exp.eval(it) for it in node])

    def evalStack(self, node: org.Org) -> BlockId:
        return self.t.stack([self.exp.eval(it) for it in node])

    def evalParagraph(self, node: org.SemParagraph) -> BlockId:
        return self.evalLine(node)

    def evalExport(self, node: org.SemExport) -> BlockId:
        if node.exporter != "latex" or node.placement:
            return self.string("")

        else:
            return self.string(node.content)

    def evalList(self, node: org.SemList) -> BlockId:
        return self.t.stack([
            self.command("begin", ["itemize"]),
            self.evalStack(node),
            self.command("end", ["itemize"])
        ])

    def getLatexClassOptions(self, node: org.SemDocument) -> List[BlockId]:
        return []

    def evalDocument(self, node: org.SemDocument) -> BlockId:
        res = self.t.stack([])

        self.t.add_at(
            res,
            self.command("documentclass",
                         opts=self.getLatexClassOptions(node),
                         args=[self.getLatexClass(node)]))

        self.t.add_at(res, self.command("usepackage", ["csquotes"]))
        self.t.add_at(res, self.command("usepackage", ["bookmarks"], ["hyperref"]))
        self.t.add_at(res, self.command("usepackage", ["xcolor"]))

        for value in TexCommand:
            cmd = self.t.line([self.string("\\newcommand")])
            arg_count = 1
            self.t.add_at(cmd, self.wrap("\\" + self.getOrgCommand(value), "{", "}"))
            self.t.add_at(cmd, self.wrap(self.string(str(arg_count)), "[", "]"))
            self.t.add_at(cmd, self.wrap(self.command(value.name, ["#1"]), "{", "}"))
            self.t.add_at(res, cmd)

        headerExports: List[org.SemExport] = []

        def visit(_id: org.Org):
            nonlocal headerExports
            if _id._is(osk.Export):
                exp: org.SemExport = _id._as(osk.Export)
                if exp.placement == "header":
                    headerExports.append(exp)

        node.eachSubnodeRec(visit)

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
            self.t.add_at(res, self.exp.eval(it))

        self.t.add_at(res, self.command("end", [self.string("document")]))

        return res

    def getLatexClass(self, node: org.SemDocument) -> str:
        return "book"

    def getOrgCommand(self, cmd: TexCommand) -> str:
        return "orgCmd" + str(cmd.name).capitalize()

    def getSubtreeCommand(self, node: org.SemSubtree) -> Optional[TexCommand]:
        return TexCommand.part
        lclass = self.getLatexClass(node.getDocument())

    def getRefKind(self, node: org.Org) -> Optional[str]:
        match node.getKind():
            case osk.Subtree:
                cmd = self.getSubtreeCommand(node._as(osk.Subtree))
                match cmd:
                    case TexCommand.chapter:
                        return "chap:"
                    case TexCommand.section:
                        return "sec:"
                    case TexCommand.part:
                        return "part:"

    def evalSubtree(self, node: org.SemSubtree) -> BlockId:
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

        if cmd in [TexCommand.part, TexCommand.chapter, TexCommand.section]:
            self.t.add_at(
                res,
                self.command(
                    "label",
                    [self.string(self.getRefKind(node) or "" + "\\the" + cmd.name)]))

        for it in node:
            self.t.add_at(res, self.exp.eval(it))

        return res

    def evalTime(self, node: org.SemTime) -> BlockId:
        time_val: datetime = datetime.fromtimestamp(node.getStatic().time)
        return self.string(time_val.strftime("%Y-%m-%d %H:%M:%S"))

    def evalTimeRange(self, node: org.SemTimeRange) -> BlockId:
        return self.t.line(
            [self.exp.eval(node.from_),
             self.string("--"),
             self.exp.eval(node.to)])
