#!/usr/bin/env python

from beartype.typing import *
from py_exporters.export_tex import ExporterLatex

import py_haxorg.pyhaxorg_wrap as org
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk
from py_textlayout.py_textlayout_wrap import TextOptions, BlockId
from py_scriptutils.script_logging import log
from py_scriptutils.files import get_haxorg_repo_root_path
import yaml
from pathlib import Path
from pydantic import BaseModel, Field
from dominate import tags, util
import dominate
from beartype import beartype
from beartype.typing import Any, List
from py_scriptutils.rich_utils import render_debug
from ansi2html import Ansi2HTMLConverter

import pygments
from pygments import highlight
from pygments.lexers import YamlLexer
from pygments.formatters import HtmlFormatter

osk = org.OrgSemKind
CAT = "test_simple_org_use.py"


def test_word() -> None:
    assert org.Document
    node = org.parseString("*Text*")

    assert node.getKind() == org.OrgSemKind.Document
    assert node[0].getKind() == org.OrgSemKind.Paragraph
    assert node[0][0].getKind() == org.OrgSemKind.Bold
    assert node[0][0][0].getKind() == org.OrgSemKind.Word


def test_attached_property_list():
    node = org.parseString("""#+attr_list: :export nil
- =some_property= :: Value
    """)

    l: org.List = node[0]
    assert l.getKind() == org.OrgSemKind.List
    exp: org.CmdArgumentList = l.getArguments("export")
    assert exp
    exp0 = exp.args[0]
    assert exp0
    assert exp0.getString() == "nil"
    assert exp0.getBool() == False


def test_attached_property_link():
    node = org.parseString("""#+attr_link: :attach-method copy :attach-on-export t
[[attachment:image 1.jpg]]
    """)

    p: org.Paragraph = node[0]
    assert p.getKind() == org.OrgSemKind.Paragraph
    l: org.Link = p[0]
    assert l.getKind() == org.OrgSemKind.Link
    # log(CAT).info(org.treeRepr(l))
    onExport: org.CmdArgumentList = l.getArguments("attach-on-export")
    assert onExport
    onExport0 = onExport.args[0]
    assert onExport0
    assert onExport0.getString() == "t"
    assert onExport0.getBool() == True


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
    assert kinds == [osk.Document, osk.Paragraph, osk.Word, osk.DocumentOptions], kinds


def test_subnode_selector():
    node = org.parseString("Word")
    selector = org.OrgDocumentSelector()
    selector.searchAnyKind(
        org.IntSetOfOrgSemKind([osk.Word]),
        isTarget=True,
    )
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
                    isTarget=idx == len(path) - 1,
                    link=selector.linkIndirectSubnode() if idx < len(path) else None,
                )

            return selector

        matches = get_selector_at_path(subtree_path).getMatches(node)
        if not matches:
            parent = get_selector_at_path(subtree_path[:1]).getMatches(node)
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


class CorpusDebug(BaseModel):
    doParse: bool = True
    doLex: bool = True


class CorpusEntry(BaseModel, extra="forbid"):
    name: str
    source: Optional[str] = None
    file: Optional[str] = None
    debug: CorpusDebug = Field(default_factory=lambda: CorpusDebug())
    base_tokens: Optional[List[Any]] = None
    tokens: Optional[List[Any]] = None
    sem: Optional[Dict] = None
    conf: Optional[Dict] = None
    subnodes: Optional[List[Any]] = None
    tags: List[str] = Field(default_factory=list)


class CorpusFile(BaseModel, extra="forbid"):
    items: List[CorpusEntry]


@beartype
def load_yaml(path: Path) -> Any:
    with open(path, "r") as file:
        return yaml.load(file, Loader=yaml.SafeLoader)


@beartype
def as_multiline(txt: str) -> List[util.text]:
    result = []
    for idx, part in enumerate(txt.split("\n")):
        if idx != 0:
            tags.br()

        result.append(util.text(part))

    return result


borders = dict(border=1, style='border-collapse: collapse; width: 100%;')


def test_unexpected_field_passed():
    try:
        tree = org.Subtree(askldfjaslkdfjaksdjfaksdjfaksdjf="12222")
        assert False, "No error triggered with unknown field"

    except RuntimeError as err:
        pass


def test_sem_parser_expected():
    corpus_root = get_haxorg_repo_root_path().joinpath("tests/org/corpus")
    corpus_files = corpus_root.rglob("*.yaml")
    corpus_data = [CorpusFile.model_validate(load_yaml(file)) for file in corpus_files]

    table = tags.table(**borders)
    row = tags.tr()
    row.add(tags.th("Source", _class="source-column"))
    row.add(tags.th("Yaml tree", _class="yaml-column"))
    row.add(tags.th("sem tree", _class="sem-column"))

    table.add(row)

    for file in corpus_data:
        for entry in file.items:
            head_row = tags.tr()
            head_row.add(
                tags.td(tags.b(util.text(entry.name)), style="text-align:center;"))

            row = tags.tr()
            if entry.source:
                text = entry.source

            else:
                text = corpus_root.joinpath(entry.file).read_text()

            row.add(tags.td(tags.pre(text), _class="source-cell"))

            if entry.debug.doLex and entry.debug.doParse:
                node = org.parseString(text)
                yaml_pre = tags.pre()
                yaml_text = org.exportToYamlString(
                    node,
                    org.OrgYamlExportOpts(
                        skipNullFields=True,
                        skipFalseFields=True,
                        skipZeroFields=True,
                        skipLocation=True,
                        skipId=True,
                    ))

                formatter = HtmlFormatter()
                yaml_pre.add_raw_string(highlight(yaml_text, YamlLexer(), formatter))
                row.add(tags.td(yaml_pre, _class="yaml-cell"))

                tree = tags.pre()
                conv = Ansi2HTMLConverter()
                tree.add_raw_string(
                    conv.convert(org.treeRepr(node, colored=True), full=False))
                row.add(tags.td(tree, _class="sem-cell"))

            else:
                row.add(tags.td(util.text("Parse disabled"), _class="yaml-column"))
                row.add(tags.td(util.text("Parse disabled"), _class="sem-column"))

            table.add(row)

    doc = dominate.document()
    doc.head.add(
        tags.link(rel="stylesheet",
                  href=get_haxorg_repo_root_path().joinpath(
                      "tests/python/test_sem_parser_expected.css")))
    doc.add(table)

    Path("/tmp/test_sem_parser_expected.html").write_text(str(doc))


def test_segment_tree():
    segments = [
        org.SequenceSegmentGroup(
            kind=1,
            segments=org.VecOfSequenceSegmentVec(
                [org.SequenceSegment(kind=2, first=0, last=2)]),
        )
    ]

    annotations: List[org.SequenceAnnotation] = org.annotateSequence(
        org.VecOfSequenceSegmentGroupVec(segments), 0, 2)

    assert len(annotations) == 1
    assert annotations[0].first == 0
    assert annotations[0].last == 2
    assert len(annotations[0].annotations) == 1
    assert annotations[0].isAnnotatedWith(1, 2)


def test_corspus_sem_render():
    pass
