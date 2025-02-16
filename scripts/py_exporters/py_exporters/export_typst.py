import py_haxorg.pyhaxorg_wrap as org
from py_textlayout.py_textlayout_wrap import TextLayout, BlockId
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk

from beartype.typing import List, Optional, Dict
from enum import Enum
from beartype import beartype

from py_exporters.export_base import ExporterBase, with_export_context
from py_exporters.export_ultraplain import ExporterUltraplain
from py_haxorg.pyhaxorg_utils import formatDateTime, formatHashTag, getFlatTags
from py_scriptutils.script_logging import log
import itertools
from py_scriptutils.json_utils import Json
import copy
from py_scriptutils import algorithm
import toml
from py_scriptutils import toml_config_profiler
from py_scriptutils.algorithm import cond, maybe_splice
import py_codegen.astbuilder_typst as typ

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


def refresh_typst_export_package():
    config = typ.get_typst_export_package(typst_toml)
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
    list: str = "orgList"
    listItem: str = "orgListItem"
    paragraph: str = "orgParagraph"
    bigIdent: str = "orgBigIdent"
    placeholder: str = "orgPlaceholder"
    mention: str = "orgMention"
    center: str = "orgCenter"
    quote: str = "orgQuote"
    example: str = "orgExample"
    code: str = "orgCode"
    table: str = "orgTable"
    table_cell: str = "orgTableCell"
    dynamic_block: str = "orgDynamicBlock"


class ExporterTypstConfig(BaseModel):
    tags: ExporterTypstConfigTags = Field(
        default_factory=lambda: ExporterTypstConfigTags())

    with_standard_baze: bool = True


# @beartype
class ExporterTypst(ExporterBase):
    t: typ.ASTBuilder
    c: ExporterTypstConfig

    def applyExportConfig(self, config: org.BlockExport):
        new_config = toml.loads(config.content)
        old_config = self.c.model_dump()
        mix_config = toml_config_profiler.merge_dicts([old_config, new_config])
        self.c = ExporterTypstConfig.model_validate(mix_config)

    def __init__(self, CRTP_derived=None):
        super().__init__(CRTP_derived or self)
        self.t = typ.ASTBuilder()
        self.c = ExporterTypstConfig()

    def newOrg(self, node: org.Org):
        return self.t.string("TODO" + str(node.getKind()))

    def expr(self, value, isLine: bool = False) -> BlockId:
        match value:
            case org.Org():
                return self.t.content(self.exp.eval(value))

            case _:
                return self.t.expr(value=value, isLine=isLine)

    def wrapStmt(self, node: org.Stmt, result: BlockId) -> BlockId:
        args = node.getAttrs("export")
        if args and 0 < len(args) and args[0].getBool() == False:
            return self.t.string("")

        else:
            return result

    def trimSub(self, node: org.Org | List[org.Org]) -> List[org.Org]:
        return algorithm.trim_both(node,
                                   lambda it: it.getKind() in [osk.Newline, osk.Space])

    def lineSubnodes(self, node: org.Org | List[org.Org]) -> BlockId:
        return self.t.line([self.exp.eval(it) for it in node])

    def stackSubnodes(self, node: org.Org | List[org.Org]) -> BlockId:
        return self.t.stack([self.exp.eval(it) for it in node])

    def evalParagraph(self, node: org.Paragraph) -> BlockId:
        if (node.isFootnoteDefinition() or node.hasTimestamp() or
                self.isDefaultAdmonition(node)) and 0 < len(node.getBody()):
            result = self.lineSubnodes(self.trimSub(node.getBody()))
            args = dict()
            if node.isFootnoteDefinition():
                args["kind"] = "footnote"
                args["footnote"] = node.getFootnoteName()

            elif node.hasAdmonition():
                args["kind"] = "admonition"
                args["admonition"] = node.getAdmonitions()[0]

            else:
                args["kind"] = "timestamp"
                args["timestamp"] = formatDateTime(node.getTimestamps()[0])

            result = self.t.call(self.c.tags.paragraph,
                                 args=args,
                                 body=[result],
                                 isLine=True)
            return result

        elif len(node.subnodes) == 1 and isinstance(
                node[0], org.Link) and node[0].target.isAttachment():
            return self.t.string("")

        elif len(node.subnodes) == 0:
            return self.t.string("")

        else:
            return self.t.call(
                self.c.tags.paragraph,
                body=[self.lineSubnodes(self.trimSub(node))],
                isLine=True,
            )

    def evalBlockDynamicFallback(self, node: org.BlockDynamicFallback) -> BlockId:
        return self.t.call(
            self.c.tags.dynamic_block,
            args=dict(
                body=[typ.RawBlock(self.t.content(self.eval(it))) for it in node],
                name=node.name,
                org_attrs=self.getNodeAttrs(node),
            ),
        )

    def evalBlockCenter(self, node: org.BlockCenter) -> BlockId:
        return self.t.call(self.c.tags.center, body=[self.stackSubnodes(node)])

    def evalNewline(self, node: org.Newline) -> BlockId:
        return self.t.string(node.text)

    def evalWord(self, node: org.Word) -> BlockId:
        return self.t.string(self.t.escape(node.text))

    def evalBigIdent(self, node: org.BigIdent) -> BlockId:
        return self.t.call(
            self.c.tags.bigIdent,
            args=dict(text=node.text),
            isLine=True,
        )

    def evalRawText(self, node: org.RawText) -> BlockId:
        return self.t.string(self.t.escape(node.text))

    def evalPunctuation(self, node: org.Punctuation) -> BlockId:
        return self.t.string(self.t.escape(node.text))

    def evalSpace(self, node: org.Space) -> BlockId:
        return self.t.string(node.text)

    def evalPlaceholder(self, node: org.Placeholder) -> BlockId:
        return self.t.call(
            self.c.tags.placeholder,
            args=dict(text=node.text),
            isLine=True,
        )

    def evalBold(self, node: org.Bold) -> BlockId:
        return self.t.surround("*", [self.lineSubnodes(node)])

    def evalMonospace(self, node: org.Monospace) -> BlockId:
        return self.t.surround("`", [self.lineSubnodes(node)])

    def evalVerbatim(self, node: org.Verbatim) -> BlockId:
        return self.t.surround("*", [self.lineSubnodes(node)])

    def evalItalic(self, node: org.Italic) -> BlockId:
        return self.t.surround("_", [self.lineSubnodes(node)])

    def evalAtMention(self, node: org.AtMention) -> BlockId:
        return self.t.call(
            self.c.tags.mention,
            args=dict(text=node.text),
            isLine=True,
        )

    def evalTextSeparator(self, node: org.TextSeparator) -> BlockId:
        return self.t.call("line", dict(length=typ.RawStr("100%")))

    def evalHashTag(self, node: org.HashTag) -> BlockId:
        return self.t.string(self.t.escape(formatHashTag(node)))

    def evalBlockQuote(self, node: org.BlockQuote) -> BlockId:
        return self.t.call(self.c.tags.quote, body=[self.stackSubnodes(node)])

    def evalBlockCode(self, node: org.BlockCode) -> BlockId:
        text = ""
        line: org.BlockCodeLine
        for idx, line in enumerate(node.lines):
            item: org.BlockCodeLinePart
            if idx != 0:
                text += "\\n"

            for item in line.parts:
                match item.getKind():
                    case org.BlockCodeLinePartKind.Raw:
                        text += item.getRaw().code

        return self.t.call(
            self.c.tags.code,
            args=dict(lang=node.lang, text=text),
        )

    def evalBlockExample(self, node: org.BlockExample) -> BlockId:
        return self.t.call(self.c.tags.example, body=[self.stackSubnodes(node)])

    def evalBlockExport(self, node: org.BlockExport) -> BlockId:
        if node.exporter == "typst":
            edit_config = node.getAttrs("edit-config")
            if edit_config and 0 < len(edit_config):
                match edit_config[0].getString():
                    case "pre-visit":
                        return self.t.string("")

                    case "in-visit":
                        self.applyExportConfig(node)
                        return self.t.string("")

                    case _:
                        raise ValueError(
                            f"edit-config parameter at {node.loc} has unexpected value '{edit_config[0].getString()}'"
                        )

            else:
                return self.t.string(node.content)

        else:
            return self.t.string("")

    @with_export_context
    def evalSubtree(self, node: org.Subtree) -> BlockId:
        if node.isComment or node.isArchived:
            return self.t.string("")

        res = self.t.stack([])

        tags = []
        for tag in node.tags:
            for it in getFlatTags(tag):
                tags.append("##".join(it))

        self.t.add_at(
            res,
            self.t.line([
                self.t.call(
                    self.c.tags.subtree,
                    dict(level=self.getRealSubtreeLevel(node), tags=tags),
                    self.exp.eval(node.title),
                ),
            ]))

        for it in node:
            self.t.add_at(res, self.exp.eval(it))

        return res

    @with_export_context
    def evalDocument(self, node: org.Document) -> BlockId:
        res = self.t.stack([])
        self.printTrace(
            f"Eval document, context: {[n.getKind() for n in self.context]}, is in include {self.isInInclude()}"
        )
        if not self.isInInclude():
            module = typ.get_typst_export_package(typst_toml)

            if self.c.with_standard_baze:
                self.t.add_at(
                    res,
                    self.t.string("#import \"@local/{name}:{version}\": *".format(
                        name=module.package.name,
                        version=module.package.version,
                    )),
                )

            for it in node:
                if isinstance(it, org.BlockExport):
                    edit_config = it.getAttrs("edit-config")
                    if edit_config and 0 < len(edit_config):
                        if edit_config[0].getString() == "pre-visit":
                            self.applyExportConfig(it)

        for it in node:
            self.t.add_at(res, self.exp.eval(it))

        return res

    def evalMacro(self, node: org.Macro) -> BlockId:
        return self.t.string("")

    def evalTime(self, node: org.Time) -> BlockId:
        return self.t.string(formatDateTime(node.getStatic().time))

    def evalLink(self, node: org.Link) -> BlockId:
        self.printTrace(f">>>>??? {node.target.getKind()}")
        match node.target.getKind():
            case org.LinkTargetKind.Attachment:
                return self.t.string("")

            case org.LinkTargetKind.Raw:
                return self.t.call(
                    "link",
                    positional=[node.target.getRaw().text],
                    body=[self.exp.eval(node.description)] if node.description else [],
                    isLine=True,
                )

            case _:
                return self.t.string(f"TODO {node.target.getKind()}")

    @with_export_context
    def evalCmdInclude(self, node: org.CmdInclude) -> BlockId:
        match node.getIncludeKind():
            case org.CmdIncludeKind.OrgDocument:
                return self.eval(node.subnodes[0])

            case _:
                return self.t.string(f"TODO {node.getIncludeKind()}")

    def evalTimeRange(self, node: org.TimeRange) -> BlockId:
        return self.t.line([
            self.exp.eval(node.from_),
            self.t.string("--"),
            self.exp.eval(node.to),
        ])

    def getNodeAttrs(self, node: org.Org) -> Dict[str, List[any]]:
        res: Dict[str, List] = dict()
        arg: org.AttrValue
        for arg in node.getAttrs():
            name = org.org_ident_normalize(arg.name)
            if name not in res:
                res[name] = []

            res[name].append(arg.getString())

        if isinstance(node, org.Stmt):
            caption = node.getCaption()
            if 0 < len(caption):
                res["caption"] = [
                    typ.RawBlock(self.t.content(self.eval(it))) for it in caption
                ]

        return res

    def evalList(self, node: org.List) -> BlockId:
        desc_status = [it.isDescriptionItem() for it in node.subnodes]
        if any(desc_status) and not all(desc_status):
            raise ValueError(
                "Typst export does not support mixed description list items, list starting at {} "
                "has a mix of description and non-description items. First non-description item is at {}. List parsed as {}"
                .format(
                    node.loc,
                    list(filter(lambda it: not it.isDescriptionItem(),
                                node.subnodes))[0].loc,
                    org.treeRepr(node, maxDepth=1),
                ))

        if node.isDescriptionList() and node.getListFormattingMode(
        ) == org.ListFormattingMode.Table1D2Col:
            items = []
            item: org.ListItem
            for item in node:
                items.append(
                    typ.RawBlock(
                        self.t.call(self.c.tags.table_cell,
                                    isFirst=False,
                                    args=dict(column=0),
                                    body=self.eval(item.header))))
                items.append(
                    typ.RawBlock(
                        self.t.call(self.c.tags.table_cell,
                                    isFirst=False,
                                    args=dict(column=1),
                                    body=self.t.stack([self.eval(it) for it in item]))))

            return self.t.call(
                self.c.tags.table,
                args=dict(
                    items=items,
                    kwargs=dict(columns=2),
                    org_attrs=self.getNodeAttrs(node),
                ),
            )

        else:
            return self.wrapStmt(
                node,
                self.t.call(
                    self.c.tags.list,
                    args=dict(
                        isDescription=node.isDescriptionList(),
                        items=typ.RawBlock(
                            self.expr([typ.RawBlock(self.exp.eval(it)) for it in node])),
                    )))

    def evalListItem(self, node: org.ListItem) -> BlockId:
        args = dict(
            content=typ.RawBlock(self.t.content(self.stackSubnodes(self.trimSub(node)))))

        if node.isDescriptionItem():
            args["header"] = typ.RawBlock(self.t.content(self.exp.eval(node.header)))
            args["isDescription"] = True

        else:
            args["isDescription"] = False

        return self.t.call(self.c.tags.listItem, args=args, isContent=True)
