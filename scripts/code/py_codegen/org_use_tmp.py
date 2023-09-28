#!/usr/bin/env python

from dataclasses import field, dataclass
from typing import *
from enum import Enum

import setup_imports

import ctypes

ctypes.CDLL(setup_imports.lib_dir + '/pyhaxorg.so')

from pyhaxorg import *

ctx = OrgContext()
ctx.run("/tmp/doc.org")
print(ctx.getNode())
print(ctx.getNode().getKind())
