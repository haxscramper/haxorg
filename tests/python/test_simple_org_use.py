#!/usr/bin/env python

from typing import *
import setup_imports
import sys
import re

import pyhaxorg as org
from py_textlayout import *
from pyhaxorg import OrgContext
from pyhaxorg import OrgSemKind as osk

ctx = org.OrgContext()
assert org.Document
ctx.parseString("*Text*")

assert ctx.getNode().getKind() == org.OrgSemKind.Document
assert ctx.getNode()[0].getKind() == org.OrgSemKind.Paragraph
assert ctx.getNode()[0][0].getKind() == org.OrgSemKind.Bold
assert ctx.getNode()[0][0][0].getKind() == org.OrgSemKind.Word


def export_class_methods(cls):
    """
    A decorator that takes a class and binds its methods to the nested ExporterPython.
    """

    class Wrapped(cls):

        def initExporter(self, *args, **kwargs):
            self.exp = org.ExporterPython()  

            # Direct method to function mappings without kind
            direct_mappings = {
                "visitAnyIdAround": self.exp.setVisitAnyIdAround,
                "visitAnyIdIn": self.exp.setVisitAnyIdIn,
                "visitAnyField": self.exp.setVisitAnyField,
                "evalTopCb": self.exp.setEvalTopCb,
                "setPushVisitAnyId": self.exp.setPushVisitAnyId,
                "setPopVisitAnyId": self.exp.setPopVisitAnyId,
                "setVisitAnyHookCb": self.exp.setVisitAnyHookCb,
                # Add others if needed
            }
            for method_name, setter in direct_mappings.items():
                if hasattr(self, method_name):
                    setter(getattr(self, method_name))

            # Methods with OrgSemKind or LeafFieldType
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
                (r"setNewOrgRes", self.exp.setNewOrgRes),
                (r"setNewLeafRes", self.exp.setNewLeafRes),
            ]

            # Process methods that match the patterns for OrgSemKind or LeafFieldType
            for method_name in dir(self):
                for (prefix, setter) in prefix_to_setter_with_kind:
                    match = re.match(prefix, method_name)
                    if match:
                        kind_str = match.group(1)
                        kind_enum = getattr(org.OrgSemKind, kind_str, None)

                        if not kind_enum:
                            kind_enum = getattr(org.LeafFieldType, kind_str,
                                                None)

                        if kind_enum:
                            setter(kind_enum, getattr(type(self), method_name))
                            break

            # Always execute this at the end
            self.exp.setSelf(self)

    return Wrapped

if True:
    @export_class_methods
    class ExporterLatex:
        def __init__(self):
            self.initExporter()
            self.t = TextLayout()

        # def evalSpace(self, node: org.SemSpace) -> BlockId:
            # return self.t.text(node)

    tex = ExporterLatex()



if True:

    @export_class_methods
    class Decorated:
        def __init__(self):
            self.initExporter()

        def visitParagraphHook(self, res: Any, node: org.SemParagraph):
            print("VISITING PARAGRAPH", res, node)

        def visitDocumentHook(self, res: Any, node: org.SemDocument):
            print("[0]", self)
            print("[1]", res)
            print("[2]", node)
            print("VISITING DOCUMENT")

    deco = Decorated()
    deco.exp.enableFileTrace("/tmp/trace")
    res1 = deco.exp.evalTop(ctx.getNode())

if True:

    class Wrap:

        def newRes(self, node: org.SemId):
            return [{"kind": str(node.getKind())}]

        def visit(self, res, node: org.SemId):
            res.append({"kind": str(node.getKind())})

        def __init__(self) -> None:
            self.exp = org.ExporterPython()
            self.res = ""
            self.exp.setSelf(self)
            self.exp.setNewOrgRes(osk.Document, Wrap.newRes)
            self.exp.setVisitAnyIdAround(Wrap.visit)
            # self.exp.enablePyStreamTrace(sys.stdout)

    wrap = Wrap()
    result = wrap.exp.evalTop(ctx.getNode())
    assert len(result) == 2
    assert result[0] == {"kind": "OrgSemKind.Document"}
    assert result[1] == {"kind": "OrgSemKind.DocumentOptions"}
