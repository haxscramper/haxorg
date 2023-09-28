#!/usr/bin/env python

from dataclasses import field, dataclass
from typing import *
from enum import Enum

import setup_imports

import ctypes

ctypes.CDLL(setup_imports.lib_dir + '/pyhaxorg.so')

import inspect

import pyhaxorg

# Get all members of the module
all_members = inspect.getmembers(pyhaxorg)

# If you only want to get variable names
exp = [name for name, value in all_members if not inspect.isfunction(value) and not inspect.isclass(value)]

assert "Block" in exp
assert "OrgExport" in exp

# print(exp)

# ctx = pyhaxorg.OrgContext()
# ctx.run("/tmp/doc.org")
# print(ctx.getNode())
# print(ctx.getNode().getKind())

