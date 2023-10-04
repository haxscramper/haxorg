#!/usr/bin/env python

import setup_imports
import sys
import os
import re
from enum import Enum
from beartype import beartype
from beartype.typing import *

import pyhaxorg as org
from py_textlayout import *
from pyhaxorg import OrgContext
from pyhaxorg import OrgSemKind as osk

if not TYPE_CHECKING:
    BlockId = NewType('BlockId', int)


class ExporterBase:

    def __init__(self, derived):
        self.exp = org.ExporterPython()

        direct_mappings = {
            "visitAnyIdAround": self.exp.setVisitAnyIdAround,
            "visitAnyIdIn": self.exp.setVisitAnyIdIn,
            "visitAnyField": self.exp.setVisitAnyField,
            "evalTopCb": self.exp.setEvalTopCb,
            "setPushVisitAnyId": self.exp.setPushVisitAnyId,
            "setPopVisitAnyId": self.exp.setPopVisitAnyId,
            "setVisitAnyHookCb": self.exp.setVisitAnyHookCb,
            "newOrg": self.exp.setNewAnyOrgRes,
            "newLeaf": self.exp.setNewAnyLeafRes,
        }
        for method_name, setter in direct_mappings.items():
            if hasattr(derived, method_name):
                setter(getattr(type(derived), method_name))

        prefix_to_setter_with_kind = [
            (r"visit(.*)", self.exp.setVisitIdInCb),
            (r"eval(.*)", self.exp.setEvalIdIn),
            (r"visit(.*?)Around", self.exp.setVisitIdAround),
            (r"eval(.*?)Around", self.exp.setEvalIdAround),
            (r"visit(.*?)LeafField", self.exp.setVisitLeafField),
            (r"eval(.*?)LeafField", self.exp.setEvalLeafField),
            (r"visit(.*?)OrgField", self.exp.setVisitOrgField),
            (r"eval(.*?)OrgField", self.exp.setEvalOrgField),
            (r"setPushVisitId", self.exp.setPushVisitId),
            (r"setPopVisitIdCb", self.exp.setPopVisitIdCb),
            (r"visit(.*?)Hook", self.exp.setVisitIdHook),
            (r"newOrg(.*)", self.exp.setNewOrgRes),
            (r"newLeaf(.*)", self.exp.setNewLeafRes),
        ]

        # Process methods that match the patterns for OrgSemKind or LeafFieldType
        for method_name in dir(derived):
            if method_name.startswith("__"):
                continue

            for (prefix, setter) in prefix_to_setter_with_kind:
                match = re.match(prefix, method_name)
                if match:
                    kind_str = match.group(1)
                    kind_enum = getattr(org.OrgSemKind, kind_str, None)

                    if not kind_enum:
                        kind_enum = getattr(org.LeafFieldType, kind_str, None)

                    if kind_enum:
                        setter(kind_enum, getattr(type(derived), method_name))
                        break

        # Always execute this at the end
        self.exp.setSelf(self)


class TexCommand(Enum):
    part = 1
    chapter = 2
    section = 3
    subsection = 4
    subsubsection = 5
    paragraph = 6
    subparagrap = 7


@beartype
class ExporterLatex(ExporterBase):
    t: TextLayout

    def __init__(self):
        super().__init__(self)
        self.t = TextLayout()

    def newOrg(self, node: org.SemId):
        return self.t.text("TODO" + str(node.getKind()))

    def string(self, node: str | BlockId) -> BlockId:
        if isinstance(node, str):
            return self.t.text(node)

        else:
            return node

    def wrap(self, node: str | BlockId, opens: str, closes: str) -> BlockId:
        return self.t.line(
            [self.string(opens),
             self.string(node),
             self.string(closes)])

    def command(self,
                name: str,
                args: List[str | BlockId] = [],
                opts: List[str | BlockId] = []) -> BlockId:
        return self.t.line([
            self.t.text("\\" + name),
            *[self.wrap(it, "[", "]") for it in opts],
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
        return self.command("textsc", [
            self.command("texttt",
                         [self.string(self.string("<" + node.text + ">"))])
        ])

    def evalBigIdent(self, node: org.SemBigIdent) -> BlockId:
        specialColor = ""
        match node.text:
            case "TODO":
                specialColor = "green"
            case "WIP":
                specialColor = "brown"

        if specialColor:
            return self.command("fbox", [
                self.command("colorbox", [
                    self.string(specialColor),
                    self.string(self.escape(node.text))
                ])
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

    def evalListItem(self, node: org.SemListItem) -> BlockId:
        res = self.t.line([])
        if node.isDescriptionItem():
            self.t.add_at(res, self.command("item", [self.exp.eval(node.header)] if node.header else []))

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
        return self.string(node.text)

    def evalSpace(self, node: org.SemSpace) -> BlockId:
        return self.string(node.text)

    def evalUnderline(self, node: org.SemUnderline) -> BlockId:
        return self.command("underline", [self.evalLine(node)])

    def evalBold(self, node: org.SemBold) -> BlockId:
        return self.command("bold", [self.evalLine(node)])

    def evalLine(self, node: org.SemId) -> BlockId:
        return self.t.line([self.exp.eval(it) for it in node])

    def evalStack(self, node: org.SemId) -> BlockId:
        return self.t.stack([self.exp.eval(it) for it in node])

    def evalParagraph(self, node: org.SemParagraph) -> BlockId:
        return self.evalLine(node)


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

        self.t.add_at(res, self.command("documentclass", opts=self.getLatexClassOptions(node), args=[self.getLatexClass(node)]))

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

    def getRefKind(self, node: org.SemId) -> Optional[str]:
        match node.getKind():
            case osk.Subtree:
                cmd = self.getSubtreeCommand(node)
                match cmd:
                    case TexCommand.chapter: return "chap:"
                    case TexCommand.section: return "sec:"
                    case TexCommand.part: return "part:"


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
                            self.string(str(item.getKind()))
                        ]))

        cmd = self.getSubtreeCommand(node)
        self.t.add_at(
            res, self.command(self.getOrgCommand(cmd) if cmd else "texbf", [title_text]))

        if cmd in [TexCommand.part, TexCommand.chapter, TexCommand.section]:
            self.t.add_at(res, self.command("label", [
                self.string(self.getRefKind(node) or "" + "\\the" + cmd.name)
            ]))

        for it in node:
            self.t.add_at(res, self.exp.eval(it))

        return res

    def evalTimeRange(self, node: org.SemTimeRange) -> BlockId:
        # FIXME `from` field is missing
        return self.t.line([self.string("--"), self.exp.eval(node.to)])


def test_word():
    ctx = org.OrgContext()
    assert org.Document
    ctx.parseString("*Text*")

    assert ctx.getNode().getKind() == org.OrgSemKind.Document
    assert ctx.getNode()[0].getKind() == org.OrgSemKind.Paragraph
    assert ctx.getNode()[0][0].getKind() == org.OrgSemKind.Bold
    assert ctx.getNode()[0][0][0].getKind() == org.OrgSemKind.Word


def test_serialization_expose():
    ctx = org.OrgContext()
    ctx.parseString("Text")
    ctx.writeStore("/tmp/cachedStore.dat")

    new = org.OrgContext()
    new.loadStore("/tmp/cachedStore.dat")
    assert new.getNode().getKind() == osk.Document

    assert ctx.getNode().getKind() == org.OrgSemKind.Document
    assert ctx.getNode()[0].getKind() == org.OrgSemKind.Paragraph
    assert ctx.getNode()[0][0].getKind() == org.OrgSemKind.Word

def test_tex_exporter():
    return 

    ctx = org.OrgContext()
    with open(os.path.join(setup_imports.root_dir, "tests/corpus/org/all.org"),
              "r") as f:
        ctx.parseString(f.read())

    tex = ExporterLatex()
    tex.exp.enableFileTrace("/tmp/trace")
    res1: BlockId = tex.exp.evalTop(ctx.getNode())
    print(tex.t.toString(res1, TextOptions()))


# if True:

#     @export_class_methods
#     class Decorated:
#         def __init__(self):
#             self.initExporter()

#         def visitParagraphHook(self, res: Any, node: org.SemParagraph):
#             print("VISITING PARAGRAPH", res, node)

#         def visitDocumentHook(self, res: Any, node: org.SemDocument):
#             print("[0]", self)
#             print("[1]", res)
#             print("[2]", node)
#             print("VISITING DOCUMENT")

#     deco = Decorated()
#     res1 = deco.exp.evalTop(ctx.getNode())

# if True:

#     class Wrap:

#         def newRes(self, node: org.SemId):
#             return [{"kind": str(node.getKind())}]

#         def visit(self, res, node: org.SemId):
#             res.append({"kind": str(node.getKind())})

#         def __init__(self) -> None:
#             self.exp = org.ExporterPython()
#             self.res = ""
#             self.exp.setSelf(self)
#             self.exp.setNewOrgRes(osk.Document, Wrap.newRes)
#             self.exp.setVisitAnyIdAround(Wrap.visit)
#             # self.exp.enablePyStreamTrace(sys.stdout)

#     wrap = Wrap()
#     result = wrap.exp.evalTop(ctx.getNode())
#     assert len(result) == 2
#     assert result[0] == {"kind": "OrgSemKind.Document"}
#     assert result[1] == {"kind": "OrgSemKind.DocumentOptions"}
