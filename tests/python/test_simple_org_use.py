#!/usr/bin/env python

import os
from beartype.typing import *

from typing import TYPE_CHECKING
from py_exporters.export_tex import ExporterLatex
import py_haxorg.pyhaxorg as org
from py_haxorg.pyhaxorg import OrgSemKind as osk
from py_textlayout.py_textlayout import TextOptions
from py_haxorg.utils import toTree


if TYPE_CHECKING:
    from py_textlayout.py_textlayout import BlockId
else:
    BlockId = NewType('BlockId', int)

def test_word() -> None:
    ctx = org.OrgContext()
    assert org.Document
    ctx.parseString("*Text*")

    assert ctx.getNode().getKind() == org.OrgSemKind.Document
    assert ctx.getNode()[0].getKind() == org.OrgSemKind.Paragraph
    assert ctx.getNode()[0][0].getKind() == org.OrgSemKind.Bold
    assert ctx.getNode()[0][0][0].getKind() == org.OrgSemKind.Word


def test_serialization_expose() -> None:
    ctx = org.OrgContext()
    ctx.parseString("Text")
    ctx.writeStore("/tmp/cachedStore.dat")

    new = org.OrgContext()
    new.loadStore("/tmp/cachedStore.dat")
    assert new.getNode().getKind() == osk.Document

    assert ctx.getNode().getKind() == org.OrgSemKind.Document
    assert ctx.getNode()[0].getKind() == org.OrgSemKind.Paragraph
    assert ctx.getNode()[0][0].getKind() == org.OrgSemKind.Word

def test_tex_exporter() -> None:
    tmp = org.OrgContext()
    tmp.parseFile("/home/haxscramper/tmp/doc.org")
    toTree("/tmp/before.txt", tmp.getNode())

    ctx = org.OrgContext()
    cache_file = "/tmp/doc_cache.dat"

    if os.path.exists(cache_file):
        ctx.loadStore(cache_file)
    else:
        ctx.parseFile("/home/haxscramper/tmp/doc2.org")
        ctx.writeStore(cache_file)

    toTree("/tmp/after.txt", ctx.getNode())


    tex = ExporterLatex()
    tex.exp.enableFileTrace("/tmp/trace")
    res1: BlockId = tex.exp.evalTop(ctx.getNode())
    with open("/tmp/result.tex", "w") as file:
        file.write(tex.t.toString(res1, TextOptions()))
