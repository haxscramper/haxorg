#!/usr/bin/env python

import setup_imports
import sys
import os
import re
from enum import Enum
from beartype import beartype
from beartype.typing import *

from datetime import date, time, datetime
import py_haxorg.haxorg as org
from py_haxorg.haxorg import OrgSemKind as osk


if not TYPE_CHECKING:
    BlockId = NewType('BlockId', int)

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

def toTree(path: str, node: org.SemId):
    tree = org.OrgExporterTree()
    opts = org.ExporterTreeOpts()
    opts.withColor = False
    tree.toFile(node, path, opts)

def test_tex_exporter():
    tmp = org.OrgContext()
    tmp.parseFile("/home/haxscramper/tmp/doc.org")
    toTree("/tmp/before.txt", tmp.getNode())

    ctx = org.OrgContext()
    cache_file = "/tmp/doc_cache.dat"

    if os.path.exists(cache_file):
        ctx.loadStore(cache_file)
    else:
        ctx.parseFile("/home/haxscramper/tmp/doc.org")
        ctx.writeStore(cache_file)

    toTree("/tmp/after.txt", ctx.getNode())


    tex = ExporterLatex()
    tex.exp.enableFileTrace("/tmp/trace")
    res1: BlockId = tex.exp.evalTop(ctx.getNode())
    with open("/tmp/result.tex", "w") as file:
        file.write(tex.t.toString(res1, TextOptions()))
