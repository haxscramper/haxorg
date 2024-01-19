#!/usr/bin/env python

import os
from beartype.typing import *

from typing import TYPE_CHECKING
from py_exporters.export_tex import ExporterLatex

import py_haxorg.pyhaxorg as org
from py_haxorg.pyhaxorg import OrgSemKind as osk
from py_textlayout.py_textlayout_wrap import TextOptions
from py_haxorg.utils import toTree
from py_scriptutils.script_logging import log

if TYPE_CHECKING:
    from py_textlayout.py_textlayout_wrap import BlockId
else:
    BlockId = NewType('BlockId', int)


def test_word() -> None:
    ctx = org.OrgContext()
    assert org.Document
    ctx.parseString("*Text*")

    # assert ctx.getNode().getKind() == org.OrgSemKind.Document
    # assert ctx.getNode()[0].getKind() == org.OrgSemKind.Paragraph
    # assert ctx.getNode()[0][0].getKind() == org.OrgSemKind.Bold
    # assert ctx.getNode()[0][0][0].getKind() == org.OrgSemKind.Word
