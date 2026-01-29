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

osk: Type = org.OrgSemKind
CAT = "test_simple_org_use.py"


def test_word() -> None:
    parse = org.ParseContext()
    assert org.Document is not None
    node = parse.parseString("*Text*", "<test_word>")

    assert node.getKind() == org.OrgSemKind.Document
    assert node[0].getKind() == org.OrgSemKind.Paragraph
    assert node[0][0].getKind() == org.OrgSemKind.Bold
    assert node[0][0][0].getKind() == org.OrgSemKind.Word


def test_attached_property_list() -> None:
    parse = org.ParseContext()
    node = parse.parseString(
        """#+attr_list: :export nil
- =some_property= :: Value
    """, "<test>")

    l: org.List = node[0]
    assert l.getKind() == org.OrgSemKind.List
    exp: org.AttrList = l.getAttrs("export")
    assert exp
    exp0 = exp[0]
    assert exp0
    assert exp0.getString() == "nil"
    assert exp0.getBool() == False


def test_attached_property_link() -> None:
    parse = org.ParseContext()
    node = parse.parseString(
        """#+attr_link: :attach-method copy :attach-on-export t
[[attachment:image 1.jpg]]
    """, "<test>")

    p: org.Paragraph = node[0]
    assert p.getKind() == org.OrgSemKind.Paragraph
    l: org.Link = p[0]
    assert l.getKind() == org.OrgSemKind.Link
    # log(CAT).info(org.treeRepr(l))
    onExport: org.AttrList = l.getAttrs("attach-on-export")
    assert onExport
    onExport0 = onExport[0]
    assert onExport0
    assert onExport0.getString() == "t"
    assert onExport0.getBool() == True


def test_subnode_visitor() -> None:
    parse = org.ParseContext()
    node = parse.parseString("Word", "<test>")
    kinds = []
    org.eachSubnodeRec(node, lambda it: kinds.append(it.getKind()))
    assert kinds == [osk.Document, osk.Paragraph, osk.Word, osk.DocumentOptions], kinds


class CorpusDebug(BaseModel):
    doParse: bool = True
    doLex: bool = True
    doLexBase: bool = True


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


def test_unexpected_field_passed() -> None:
    try:
        tree = org.Subtree(askldfjaslkdfjaksdjfaksdjfaksdjf="12222")
        assert False, "No error triggered with unknown field"

    except RuntimeError as err:
        pass


def test_sem_parser_expected() -> None:
    corpus_root = get_haxorg_repo_root_path().joinpath("tests/org/corpus")
    corpus_files = corpus_root.rglob("*.yaml")
    corpus_data = [(CorpusFile.model_validate(load_yaml(file)), file) for file in corpus_files]

    table = tags.table(**borders)
    row = tags.tr()
    row.add(tags.th("Source", _class="source-column"))
    row.add(tags.th("Yaml tree", _class="yaml-column"))
    row.add(tags.th("sem tree", _class="sem-column"))

    table.add(row)
    parse = org.ParseContext()

    for file, path in corpus_data:
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

            if entry.debug.doLexBase and entry.debug.doLex and entry.debug.doParse:
                node = parse.parseString(text, f"<{path.stem}-{entry.name}>")
                yaml_pre = tags.pre()
                try:
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

                except Exception as e:
                    yaml_pre.add_raw_string(str(e))

                row.add(tags.td(yaml_pre, _class="yaml-cell"))

                tree = tags.pre()
                try:
                    conv = Ansi2HTMLConverter()
                    tree.add_raw_string(
                        conv.convert(org.treeRepr(node, colored=True), full=False))

                except Exception as e:
                    tree.add_raw_string(str(e))

                row.add(tags.td(tree, _class="sem-cell"))

            else:
                row.add(tags.td(util.text("Parse disabled"), _class="yaml-column"))
                row.add(tags.td(util.text("Parse disabled"), _class="sem-column"))

            table.add(row)

    doc = dominate.document(title="test_sem_parser_expected")
    doc.head.add(
        tags.link(rel="stylesheet",
                  href=get_haxorg_repo_root_path().joinpath(
                      "tests/python/test_sem_parser_expected.css")))
    doc.add(table)

    Path("/tmp/test_sem_parser_expected.html").write_text(str(doc))


def test_segment_tree() -> None:
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


def test_doc1() -> None:
    parse = org.ParseContext()
    file = Path("~/tmp/doc1.org").expanduser()
    if not file.exists():
        return

    node = parse.parseFile(str(file))
    text = org.treeRepr(node, colored=False)
    Path("/tmp/test_doc1.txt").write_text(text)


if __name__ == "__main__":
    test_doc1()
