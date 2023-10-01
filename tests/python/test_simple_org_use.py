#!/usr/bin/env python

from typing import *
import setup_imports
import sys

import pyhaxorg as org
from pyhaxorg import OrgContext
from pyhaxorg import OrgSemKind as osk

ctx = org.OrgContext()
assert org.Document
ctx.parseString("*Text*")

assert ctx.getNode().getKind() == org.OrgSemKind.Document
assert ctx.getNode()[0].getKind() == org.OrgSemKind.Paragraph
assert ctx.getNode()[0][0].getKind() == org.OrgSemKind.Bold
assert ctx.getNode()[0][0][0].getKind() == org.OrgSemKind.Word


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
        self.exp.enablePyStreamTrace(sys.stdout)
        

wrap = Wrap()
result = wrap.exp.evalTop(ctx.getNode())
assert len(result) == 2
assert result[0] == {"kind": "OrgSemKind.Document"}
assert result[1] == {"kind": "OrgSemKind.DocumentOptions"}
