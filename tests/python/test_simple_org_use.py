#!/usr/bin/env python

from dataclasses import field, dataclass
from typing import *
from enum import Enum

import setup_imports

import ctypes

ctypes.CDLL(setup_imports.lib_dir + '/pyhaxorg.so')

import inspect

import pyhaxorg as org
from pyhaxorg import OrgContext
from pyhaxorg import OrgSemKind as osk

# Get all members of the module
all_members = inspect.getmembers(org)

# If you only want to get variable names
exp = [name for name, value in all_members if not inspect.isfunction(value) and not inspect.isclass(value)]
# print(exp)

assert "Block" in exp
# assert "OrgExport" in exp


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
        

wrap = Wrap()
result = wrap.exp.evalTop(ctx.getNode())
assert len(result) == 2
assert result[0] == {"kind": "OrgSemKind.Document"}
assert result[1] == {"kind": "OrgSemKind.DocumentOptions"}
