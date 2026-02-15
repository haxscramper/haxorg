from enum import Enum

from beartype.typing import Any, List, Optional
from py_haxorg.exporters.export_base import ExporterBase
from py_haxorg.exporters.export_ultraplain import ExporterUltraplain
from py_haxorg.layout.wrap import BlockId, TextLayout
from py_haxorg.pyhaxorg_utils import formatDateTime
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk
import py_haxorg.pyhaxorg_wrap as org


class TexCommand(Enum):
    """
    Collection of the latex commands used in the generated tex sources
    """
    part = 1  # nodoc
    chapter = 2  # nodoc
    section = 3  # nodoc
    subsection = 4  # nodoc
    subsubsection = 5  # nodoc
    paragraph = 6  # nodoc
    subparagraph = 7  # nodoc
    textbf = 8  # nodoc


# @beartype
class ExporterLatex(ExporterBase):
    """
    Export org-mode document to latex
    """
    t: TextLayout  # nodoc

    def __init__(self, CRTP_derived: Any = None) -> None:
        super().__init__(CRTP_derived or self)
        self.t = TextLayout()

    def newOrg(self, node: org.Org) -> Any:
        return self.t.text("TODO" + str(node.getKind()))

    def string(self, node: str | BlockId) -> BlockId:
        """
        Normalize input node by converting it into a block id.
        """
        if isinstance(node, str):
            return self.t.text(node)

        else:
            return node

    def wrap(self, node: str | BlockId, opens: str, closes: str) -> BlockId:
        """
        Wrap input node/content into a line delimited by the open/close braces.
        """
        return self.t.line([self.string(opens), self.string(node), self.string(closes)])

    def command(
        self,
        name: str,
        args: List[str | BlockId] = [],
        opts: List[str | BlockId] = [],
    ) -> BlockId:
        """
        Generate line block with the latex command call.
        """
        return self.t.line([
            self.t.text("\\" + name), *[self.wrap(it, "[", "]") for it in opts],
            *[self.wrap(it, "{", "}") for it in args]
        ])

    def escape(self, value: str) -> str:
        """
        Escape input string for latex writing.
        """
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

    def evalBlockCenter(self, node: org.BlockCenter) -> BlockId:
        res = self.t.stack([])
        self.t.add_at(res, self.command("begin", [self.string("center")]))
        for item in node:
            self.t.add_at(res, self.exp.eval(item))

        self.t.add_at(res, self.command("end", [self.string("center")]))

        return res

    def evalLink(self, node: org.Link) -> BlockId:
        match node.target.getKind():
            case org.LinkTargetKind.Raw:
                return self.string(self.escape(node.target.getRaw().text))

            case org.LinkTargetKind.Person:
                return self.eval(node.description) if node.description else self.string(
                    node.target.getPerson().name)

            case org.LinkTargetKind.Id:
                return self.eval(node.description) if node.description else self.string(
                    node.target.getId().text)

            case _:
                return self.string(f"TODO LINK KIND {node.target.getKind()}")

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
        """
        Horizontally concat eval results for input subnodes
        """
        return self.t.line([self.exp.eval(it) for it in node])

    def stackSubnodes(self, node: org.Org) -> BlockId:
        """
        Vertically stack eval results for input subnodes.
        """
        return self.t.stack([self.exp.eval(it) for it in node])

    def evalParagraph(self, node: org.Paragraph) -> BlockId:
        return self.lineSubnodes(node)

    def evalBlockExport(self, node: org.BlockExport) -> BlockId:
        if node.exporter != "latex" or node.getPlacement():
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
        """
        Get extra configuration options for the latex export.
        """
        property: org.NamedProperty = node.getProperty("ExportLatexClassOptions")
        if property:
            values: str = property.getExportLatexClassOptions().options[0]
            return [self.string(values.strip("[]"))]

        else:
            return []

    def getLatexClass(self, node: org.Document) -> str:
        """
        Get name of the latex class for the final document.
        """
        property: org.NamedProperty = node.getProperty("ExportLatexClass")
        if property:
            return property.getExportLatexClass().latexClass

        else:
            return "book"

    def getDocumentStart(self, node: org.Document) -> List[BlockId]:
        """
        Generate a preabmle for the latex document.
        """
        res: List[BlockId] = []

        res.append(
            self.command("documentclass",
                         opts=self.getLatexClassOptions(node),
                         args=[self.getLatexClass(node)]))

        res.append(self.command("usepackage", ["csquotes"]))
        res.append(self.command("usepackage", opts=["bookmarks"], args=["hyperref"]))
        res.append(self.command("usepackage", ["xcolor"]))

        for value in TexCommand:
            cmd = self.t.line([self.string("\\newcommand")])
            arg_count = 1
            self.t.add_at(cmd, self.wrap("\\" + self.getOrgCommand(value), "{", "}"))
            self.t.add_at(cmd, self.wrap(self.string(str(arg_count)), "[", "]"))
            self.t.add_at(cmd, self.wrap(self.command(value.name, ["#1"]), "{", "}"))
            res.append(cmd)

        for it in node:
            if isinstance(it, org.BlockExport) and it.getPlacement() == "header":
                res.append(self.string(it.content))

        return res

    def evalDocument(self, node: org.Document) -> BlockId:
        self.document = node

        res = self.t.stack([])
        for item in self.getDocumentStart(node):
            self.t.add_at(res, item)

        self.t.add_at(res, self.command("begin", [self.string("document")]))

        for it in node:
            if isinstance(it, org.BlockExport) and it.getPlacement() == "header":
                continue

            self.t.add_if_not_empty(res, self.exp.eval(it))

        self.t.add_at(res, self.command("end", [self.string("document")]))

        return res

    def getOrgCommand(self, cmd: TexCommand) -> str:
        """
        Get latex command to be used for the final export document
        """
        return "orgCmd" + str(cmd.name).capitalize()

    def getSubtreeCommand(self, node: org.Subtree) -> Optional[TexCommand]:
        """
        Get subtree command based on the level and the document latex class.
        """
        lclass = self.getLatexClass(self.document)
        if lclass == "book":
            match node.level:
                case 1:
                    return TexCommand.part
                case 2:
                    return TexCommand.chapter
                case 3:
                    return TexCommand.section
                case 4:
                    return TexCommand.subsection
                case 5:
                    return TexCommand.subsubsection
                case 6:
                    return TexCommand.paragraph
                case 7:
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
        """
        Which latex reference kind should be used to refer to the node.
        """
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

        return None

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

        if cmd in [TexCommand.part, TexCommand.chapter, TexCommand.section]:
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
