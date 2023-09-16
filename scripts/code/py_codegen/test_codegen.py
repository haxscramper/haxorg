#!/usr/bin/env python

from dataclasses import field, dataclass
from typing import *
from enum import Enum

import setup_imports

# Now you should be able to import your C++ library
from py_textlayout import TextLayout, TextOptions, BlockId
from astbuilder_cpp import *
from gen_tu_cpp import *


ast = ASTBuilder()
build = ast.Doc(DocParams(brief="Text"))
print("Q")
print(ast.b.toTreeRepr(build))
print("A")
print(ast.b.toString(build, TextOptions()))
print("B")
print("Done")
