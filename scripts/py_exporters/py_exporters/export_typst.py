import py_haxorg.pyhaxorg_wrap as org
from py_textlayout.py_textlayout_wrap import TextLayout, BlockId
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk

from beartype.typing import List, Optional, Dict
from enum import Enum
from beartype import beartype

from py_exporters.export_base import ExporterBase
from py_exporters.export_ultraplain import ExporterUltraplain
from py_haxorg.pyhaxorg_utils import formatDateTime, formatHashTag
from py_scriptutils.script_logging import log

CAT = "typst"

from pydantic import BaseModel, Field
from py_scriptutils.repo_files import get_haxorg_repo_root_path
import toml
from pathlib import Path
import shutil

this_dir = get_haxorg_repo_root_path().joinpath("scripts/py_exporters/py_exporters")
typst_toml = this_dir.joinpath("export_typst_base.toml")
typst_typ = this_dir.joinpath("export_typst_base.typ")

assert typst_toml.exists(), typst_toml
assert typst_typ.exists(), typst_typ


class TypstPackageFields(BaseModel):
    name: str
    version: str
    entrypoint: str
    authors: List[str]
    license: str
    description: str


class TypstPackageModel(BaseModel):
    package: TypstPackageFields


def get_typst_export_package() -> TypstPackageModel:
    return TypstPackageModel.model_validate(toml.loads(typst_toml.read_text()))


def refresh_typst_export_package():
    config = get_typst_export_package()
    out_path = Path("~/.local/share/typst/packages/{namespace}/{name}/{version}".format(
        version=config.package.version,
        name=config.package.name,
        namespace="local",
    )).expanduser()

    out_path.mkdir(parents=True, exist_ok=True)

    shutil.copy(typst_typ, out_path.joinpath(typst_typ.name))
    shutil.copy(typst_toml, out_path.joinpath("typst.toml"))
    log(CAT).info(f"Refresh package to {out_path}")


class ExporterTypstConfigTags(BaseModel):
    subtree: str = "orgSubtree"


class ExporterTypstConfig(BaseModel):
    tags: ExporterTypstConfigTags = Field(
        default_factory=lambda: ExporterTypstConfigTags())

    with_standard_baze: bool = True


@beartype
class ExporterTypst(ExporterBase):
    t: TextLayout
    c: ExporterTypstConfig

    def __init__(self, CRTP_derived=None):
        super().__init__(CRTP_derived or self)
        self.t = TextLayout()
        self.c = ExporterTypstConfig()

    def newOrg(self, node: org.Org):
        return self.t.text("TODO" + str(node.getKind()))

    def string(self, node: str | BlockId) -> BlockId:
        if isinstance(node, str):
            return self.t.text(node)

        else:
            return node

    def surround(self, text: str, nodes: List[BlockId]) -> BlockId:
        return self.t.line([self.string(text), *nodes, self.string(text)])

    def content(self, content: BlockId) -> BlockId:
        return self.t.line([self.string("["), content, self.string("]")])

    def escape(self, text: str) -> str:
        res = ""
        for ch in text:
            if ch in ["@", "#", "<"]:
                res += "\\" + ch

            else:
                res += ch

        return res

    @beartype
    def call(
            self,
            name: str,
            kwargs: Dict[str, BlockId | str] = dict(),
            body: List[BlockId] | BlockId = list(),
    ) -> BlockId:
        b = body if isinstance(body, list) else [body]
        return self.t.stack([
            self.string(f"#{name}("),
            self.t.indent(
                2,
                self.t.stack([
                    self.t.line([
                        self.string(key),
                        self.string(": "),
                        self.string(kwargs[key]),
                        self.string(","),
                    ]) for key in sorted(kwargs.keys())
                ]),
            ),
            self.string(")[") if b else self.string(")"),
        ] + [
            self.t.stack([
                b[idx],
                self.string("]") if idx == len(b) - 1 else self.string("]["),
            ]) for idx in range(len(b))
        ])

    def wrapStmt(self, node: org.Stmt, result: BlockId) -> BlockId:
        args = node.getArguments("export")
        if args and 0 < len(args.args) and args.args[0].getBool() == False:
            return self.string("")

        else:
            return result

    def lineSubnodes(self, node: org.Org) -> BlockId:
        return self.t.line([self.exp.eval(it) for it in node])

    def stackSubnodes(self, node: org.Org) -> BlockId:
        return self.t.stack([self.exp.eval(it) for it in node])

    def evalParagraph(self, node: org.Paragraph) -> BlockId:
        return self.lineSubnodes(node)

    def evalAnnotatedParagraph(self, node: org.AnnotatedParagraph) -> BlockId:
        result = self.lineSubnodes(node)

        return result

    def evalNewline(self, node: org.Newline) -> BlockId:
        return self.string(node.text)

    def evalWord(self, node: org.Word) -> BlockId:
        return self.string(self.escape(node.text))

    def evalBigIdent(self, node: org.BigIdent) -> BlockId:
        return self.string(self.escape(node.text))

    def evalRawText(self, node: org.RawText) -> BlockId:
        return self.string(self.escape(node.text))

    def evalPunctuation(self, node: org.Punctuation) -> BlockId:
        return self.string(self.escape(node.text))

    def evalSpace(self, node: org.Space) -> BlockId:
        return self.string(node.text)

    def evalPlaceholder(self, node: org.Placeholder) -> BlockId:
        return self.surround("*", [self.string(self.escape(node.text))])

    def evalBold(self, node: org.Bold) -> BlockId:
        return self.surround("*", [self.lineSubnodes(node)])

    def evalMonospace(self, node: org.Monospace) -> BlockId:
        return self.surround("`", [self.lineSubnodes(node)])

    def evalVerbatim(self, node: org.Verbatim) -> BlockId:
        return self.surround("*", [self.lineSubnodes(node)])

    def evalItalic(self, node: org.Italic) -> BlockId:
        return self.surround("_", [self.lineSubnodes(node)])

    def evalAtMention(self, node: org.AtMention) -> BlockId:
        return self.string(self.escape("@" + node.text))

    def evalTextSeparator(self, node: org.TextSeparator) -> BlockId:
        return self.call("line", dict(length="100%"))

    def evalHashTag(self, node: org.HashTag) -> BlockId:
        return self.string(self.escape(formatHashTag(node)))

    def evalQuote(self, node: org.Quote) -> BlockId:
        return self.call("quote", body=[self.stackSubnodes(node)])

    def evalExport(self, node: org.Export) -> BlockId:
        if node.exporter == "typst":
            return self.string(node.content)

        else:
            return self.string("")

    def evalSubtree(self, node: org.Subtree) -> BlockId:
        if node.isComment or node.isArchived:
            return self.string("")

        res = self.t.stack([])

        self.t.add_at(
            res,
            self.t.line([
                self.call(
                    self.c.tags.subtree,
                    dict(level=str(node.level)),
                    self.exp.eval(node.title),
                ),
            ]))

        for it in node:
            self.t.add_at(res, self.exp.eval(it))

        return res

    def evalDocument(self, node: org.Document) -> BlockId:
        module = get_typst_export_package()
        res = self.t.stack([])

        if self.c.with_standard_baze:
            self.t.add_at(
                res,
                self.string("#import \"@local/{name}:{version}\": *".format(
                    name=module.package.name,
                    version=module.package.version,
                )),
            )

        for it in node:
            self.t.add_at(res, self.exp.eval(it))

        return res

    def evalMacro(self, node: org.Macro) -> BlockId:
        return self.string("")

    def evalTime(self, node: org.Time) -> BlockId:
        return self.string(formatDateTime(node.getStatic().time))

    def evalTimeRange(self, node: org.TimeRange) -> BlockId:
        return self.t.line(
            [self.exp.eval(node.from_),
             self.string("--"),
             self.exp.eval(node.to)])

    def evalList(self, node: org.List) -> BlockId:
        return self.wrapStmt(node, self.stackSubnodes(node))

    def evalListItem(self, node: org.ListItem) -> BlockId:
        if node.isDescriptionItem():
            return self.t.line([
                self.string("/ "),
                self.exp.eval(node.header),
                self.string(": "),
                self.stackSubnodes(node),
            ])

        else:
            return self.t.line([
                self.string("- "),
                self.stackSubnodes(node),
            ])
