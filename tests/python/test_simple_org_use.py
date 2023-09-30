#!/usr/bin/env python

from dataclasses import field, dataclass
from typing import *
from enum import Enum

import setup_imports

import ctypes

ctypes.CDLL(setup_imports.lib_dir + '/pyhaxorg.so')

import inspect

import pyhaxorg
from pyhaxorg import OrgContext

# Get all members of the module
all_members = inspect.getmembers(pyhaxorg)

# If you only want to get variable names
exp = [name for name, value in all_members if not inspect.isfunction(value) and not inspect.isclass(value)]
# print(exp)

assert "Block" in exp
# assert "OrgExport" in exp


ctx = pyhaxorg.OrgContext()
print(pyhaxorg.Document)
ctx.parseString("*Text*")

assert ctx.getNode().getKind() == pyhaxorg.OrgSemKind.Document
assert ctx.getNode()[0].getKind() == pyhaxorg.OrgSemKind.Paragraph
assert ctx.getNode()[0][0].getKind() == pyhaxorg.OrgSemKind.Bold
assert ctx.getNode()[0][0][0].getKind() == pyhaxorg.OrgSemKind.Word
