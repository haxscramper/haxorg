#!/usr/bin/env python

from beartype.typing import *
from py_exporters.export_tex import ExporterLatex

import py_haxorg.pyhaxorg_wrap as org
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk
from py_textlayout.py_textlayout_wrap import TextOptions, BlockId
from py_haxorg.utils import toTree
from py_scriptutils.script_logging import log

osk = org.OrgSemKind

def test_word() -> None:
    ctx = org.OrgContext()
    assert org.Document
    node = ctx.parseString("*Text*")

    assert node.getKind() == org.OrgSemKind.Document
    assert node[0].getKind() == org.OrgSemKind.Paragraph
    assert node[0][0].getKind() == org.OrgSemKind.Bold
    assert node[0][0][0].getKind() == org.OrgSemKind.Word


def test_link_resolution():
    ctx = org.OrgContext()
    resolve = org.OrgDocumentContext()
    node = ctx.parseString("""
* Subtree
  :properties:
  :id: id-name
  :end:
""")
    
    resolve.addNodes(node)
    assert len(resolve.getSubtreeById("id-name")) == 1, org.treeRepr(node)
 

def test_subnode_visitor():
    ctx = org.OrgContext()
    node = ctx.parseString("Word")
    kinds = []
    ctx.eachSubnodeRec(node, lambda it: kinds.append(it.getKind()))
    assert kinds == [osk.Document, osk.Paragraph, osk.Word], kinds
