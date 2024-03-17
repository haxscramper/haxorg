#!/usr/bin/env python

from beartype.typing import *
from py_exporters.export_tex import ExporterLatex

import py_haxorg.pyhaxorg_wrap as org
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk
from py_textlayout.py_textlayout_wrap import TextOptions, BlockId
from py_haxorg.utils import toTree
from py_scriptutils.script_logging import log

osk = org.OrgSemKind
CAT = "test_simple_org_use.py"


def test_word() -> None:
    assert org.Document
    node = org.parseString("*Text*")

    assert node.getKind() == org.OrgSemKind.Document
    assert node[0].getKind() == org.OrgSemKind.Paragraph
    assert node[0][0].getKind() == org.OrgSemKind.Bold
    assert node[0][0][0].getKind() == org.OrgSemKind.Word


def test_link_resolution():
    resolve = org.OrgDocumentContext()
    node = org.parseString("""
* Subtree
  :properties:
  :id: id-name
  :end:
""")

    resolve.addNodes(node)
    assert len(resolve.getSubtreeById("id-name")) == 1, org.treeRepr(node)


def test_subnode_visitor():
    node = org.parseString("Word")
    kinds = []
    org.eachSubnodeRec(node, lambda it: kinds.append(it.getKind()))
    assert kinds == [osk.Document, osk.Paragraph, osk.Word], kinds


def test_subnode_selector():
    node = org.parseString("Word")
    selector = org.OrgDocumentSelector()
    selector.searchAnyKind(org.IntSetOfOrgSemKind([osk.Word]))
    matches = selector.getMatches(node)
    assert len(matches) == 1
    assert matches[0].getKind() == osk.Word
    assert matches[0].text == "Word"


def test_procedural_subtree_edits():
    node = org.parseString("""
* Title1
** Subtitle1
Content1
** Subtitle2
Content2
* Title2
""")

    def ensure_content(subtree_path: List[str], content: str):
        def get_selector_at_path(path: List[str]):
            selector = org.OrgDocumentSelector()
            for idx, title in enumerate(path):
                selector.searchSubtreePlaintextTitle(
                    title=title,
                    link=None if idx == len(path) - 1 else selector.linkIndirectSubnode())

            return selector

        matches = get_selector_at_path(subtree_path[::-1]).getMatches(node)
        if not matches:
            parent = get_selector_at_path(subtree_path[:1][::-1]).getMatches(node)
            assert len(parent) == 1
            parent[0].push_back(
                org.Subtree(
                    title=org.Paragraph(subnodes=[org.Word(text=subtree_path[-1])]),
                    subnodes=[org.Paragraph(subnodes=[org.Word(text=content)])]))

    ensure_content(["Title1", "Subtitle2"], "wont_be_added")
    ensure_content(["Title1", "Subtitle2"], "wont_be_added")
    ensure_content(["Title1", "Subtitle2"], "wont_be_added")
    ensure_content(["Title2", "Subtitle3"], "new_content")

    text = org.formatToString(node)
    assert "wont_be_added" not in text
    assert "new_content" in text
