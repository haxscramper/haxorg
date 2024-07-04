import py_haxorg.pyhaxorg_wrap as org
from py_textlayout.py_textlayout_wrap import TextLayout, BlockId
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk

from beartype.typing import List, Optional, Dict
from enum import Enum
from beartype import beartype

from py_exporters.export_base import ExporterBase
from py_exporters.export_ultraplain import ExporterUltraplain
from py_haxorg.pyhaxorg_utils import formatDateTime, formatHashTag, getFlatTags
from py_scriptutils.script_logging import log
import itertools
from py_scriptutils.json_utils import Json
import copy
from py_scriptutils import algorithm
import toml
from py_scriptutils import toml_config_profiler

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


def cond(expr, ifTrue=None, ifFalse=None):
    """
    Alternative for inline if expression for simpler syntax and better formatting. Also supports 
    multiple conditions, similar to the `cond` and `pcond` macro from lisp. Note: will evaluate
    all arguments irrespective of the truth value, so use it only in case where compute cost is
    small and there are no side effects. 

    If the `expr` is not a list or a tuple other type -- based on the value of `expr`, return the `ifTrue` or `ifFalse. 

    ```
    value = cond(expr, "true", "false")
    ```

    If the `expr` is a list is a list or a tuple return the first item where the expression is true. If no elements
    have true values, will return `None`. To get a default branch, use `True` as an expression. 

    ```
    value = cond([
        (expr1, value1),
        (expr2, value2),
        (True, default)
    ])
    ```

    """
    if isinstance(expr, (list, tuple)):
        for key, value in expr:
            if key:
                return value

    else:
        if expr:
            return ifTrue

        else:
            return ifFalse


def maybe_splice(expr, item):
    """
    Return `[item]` if the expression evaluates to true, otherwise return an empty list. 
    
    Use this for splicing optional values into the list `[it1, *maybe_splice(cond, it2)]` --
    depending on the `cond` value, the resulting list might have one or two elements. 
    """
    if expr:
        return [item]

    else:
        return []


@beartype
class RawStr():

    def __init__(self, value: str) -> None:
        self.value = value


@beartype
class RawBlock():

    def __init__(self, value: BlockId) -> None:
        self.value = value


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


class ExporterTypstConfig(BaseModel):
    tags: ExporterTypstConfigTags = Field(
        default_factory=lambda: ExporterTypstConfigTags())

    with_standard_baze: bool = True


@beartype
class ExporterTypst(ExporterBase):
    t: TextLayout
    c: ExporterTypstConfig

    def applyExportConfig(self, config: org.Export):
        new_config = toml.loads(config.content)
        old_config = self.c.model_dump()
        mix_config = toml_config_profiler.merge_dicts([old_config, new_config])
        self.c = ExporterTypstConfig.model_validate(mix_config)

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

    def expr(self, value) -> BlockId:
        match value:
            case bool():
                return self.string("true" if value else "false")

            case int() | float():
                return self.string(str(value))

            case RawStr():
                return self.string(value.value)

            case RawBlock():
                return self.string(value.value)

            case str():
                return self.t.wrap_quote(value)

            case list():
                if all(isinstance(it, (int, str, float)) for it in value):
                    return self.t.pars(self.t.csv([self.expr(it) for it in value]))

                else:
                    return self.t.stack([
                        self.string("("),
                        self.t.csv(
                            [self.expr(it) for it in value],
                            isLine=False,
                            isTrailing=True,
                        ),
                        self.string(")")
                    ])

            case None:
                return self.string("null")

            case org.Org():
                return self.content(self.exp.eval(value))

            case dict():
                return self.t.pars(
                    self.t.csv([
                        self.t.line(
                            [self.string(key),
                             self.string(": "),
                             self.expr(value[key])]) for key in sorted(value.keys())
                    ]))

            case _:
                raise ValueError(
                    f"Unexpected type for `expr()` conversion: {type(value)}")

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
        args: Dict[str, BlockId | str] = dict(),
        body: List[BlockId] | BlockId = list(),
        positional: List[BlockId] | BlockId = list(),
        isContent: bool = False,
        isLine: bool = False,
    ) -> BlockId:
        b = body if isinstance(body, list) else [body]
        arglist = []

        if isinstance(positional, list):
            for it in positional:
                arglist.append(self.t.line([it, self.string(cond(isLine, ", ", ","))]))

        else:
            arglist.append(positional)

        for key in sorted(args.keys()):
            arglist.append(
                self.t.line([
                    self.string(key),
                    self.string(": "),
                    self.expr(args[key]),
                    self.string(cond(isLine, ", ", ",")),
                ]))

        result = cond(isLine, self.t.line, self.t.stack)([
            self.string(
                cond([
                    (arglist, f"#{name}("),
                    (b and not isLine, f"#{name}["),
                    (True, f"#{name}"),
                ])),
            *maybe_splice(
                arglist,
                self.t.line(arglist) if isLine else self.t.indent(
                    2,
                    self.t.stack(arglist),
                )),
            *maybe_splice(
                arglist,
                self.string(
                    cond([
                        (b and arglist and not isLine, ")["),
                        (arglist, ")"),
                        (True, ""),
                    ]))),
        ] + [
            cond(isLine, self.t.line, self.t.stack)([
                *maybe_splice(isLine, self.string("[")),
                self.t.indent(cond(isLine, 0, 2), b[idx]),
                self.string("]") if idx == len(b) - 1 else self.string("]["),
            ]) for idx in range(len(b))
        ])

        if isContent:
            return self.content(result)

        else:
            return result

    def wrapStmt(self, node: org.Stmt, result: BlockId) -> BlockId:
        args = node.getArguments("export")
        if args and 0 < len(args.args) and args.args[0].getBool() == False:
            return self.string("")

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
        if len(node.subnodes) == 1 and isinstance(
                node[0], org.Link) and node[0].getLinkKind() in [org.LinkKind.Attachment]:
            return self.string("")

        elif len(node.subnodes) == 0:
            return self.string("")

        else:
            return self.call(
                self.c.tags.paragraph,
                body=[self.lineSubnodes(self.trimSub(node))],
                isLine=True,
            )

    def evalAnnotatedParagraph(self, node: org.AnnotatedParagraph) -> BlockId:
        result = self.lineSubnodes(self.trimSub(node))
        args = dict()
        match node.getAnnotationKind():
            case org.AnnotatedParagraphAnnotationKind.Footnote:
                args["kind"] = "footnote"
                args["footnote"] = node.getFootnote().name

            case org.AnnotatedParagraphAnnotationKind.Admonition:
                args["kind"] = "admonition"
                args["admonition"] = node.getAdmonition().name.text

            case org.AnnotatedParagraphAnnotationKind.Timestamp:
                args["kind"] = "timestamp"
                args["timestamp"] = formatDateTime(
                    node.getTimestamp().time.getStatic().time)

        result = self.call(self.c.tags.paragraph, args=args, body=[result], isLine=True)
        return result

    def evalCenter(self, node: org.Center) -> BlockId:
        return self.call(self.c.tags.center, body=[self.stackSubnodes(node)])

    def evalNewline(self, node: org.Newline) -> BlockId:
        return self.string(node.text)

    def evalWord(self, node: org.Word) -> BlockId:
        return self.string(self.escape(node.text))

    def evalBigIdent(self, node: org.BigIdent) -> BlockId:
        return self.call(
            self.c.tags.bigIdent,
            args=dict(text=node.text),
            isLine=True,
        )

    def evalRawText(self, node: org.RawText) -> BlockId:
        return self.string(self.escape(node.text))

    def evalPunctuation(self, node: org.Punctuation) -> BlockId:
        return self.string(self.escape(node.text))

    def evalSpace(self, node: org.Space) -> BlockId:
        return self.string(node.text)

    def evalPlaceholder(self, node: org.Placeholder) -> BlockId:
        return self.call(
            self.c.tags.placeholder,
            args=dict(text=node.text),
            isLine=True,
        )

    def evalBold(self, node: org.Bold) -> BlockId:
        return self.surround("*", [self.lineSubnodes(node)])

    def evalMonospace(self, node: org.Monospace) -> BlockId:
        return self.surround("`", [self.lineSubnodes(node)])

    def evalVerbatim(self, node: org.Verbatim) -> BlockId:
        return self.surround("*", [self.lineSubnodes(node)])

    def evalItalic(self, node: org.Italic) -> BlockId:
        return self.surround("_", [self.lineSubnodes(node)])

    def evalAtMention(self, node: org.AtMention) -> BlockId:
        return self.call(
            self.c.tags.mention,
            args=dict(text=node.text),
            isLine=True,
        )

    def evalTextSeparator(self, node: org.TextSeparator) -> BlockId:
        return self.call("line", dict(length=RawStr("100%")))

    def evalHashTag(self, node: org.HashTag) -> BlockId:
        return self.string(self.escape(formatHashTag(node)))

    def evalQuote(self, node: org.Quote) -> BlockId:
        return self.call(self.c.tags.quote, body=[self.stackSubnodes(node)])

    def evalCode(self, node: org.Code) -> BlockId:
        text = ""
        line: org.CodeLine
        for idx, line in enumerate(node.lines):
            item: org.CodeLinePart
            if idx != 0:
                text += "\\n"

            for item in line.parts:
                match item.getKind():
                    case org.CodeLinePartKind.Raw:
                        text += item.getRaw().code

        return self.call(
            self.c.tags.code,
            args=dict(lang=node.lang, text=text),
        )

    def evalExample(self, node: org.Example) -> BlockId:
        return self.call(self.c.tags.example, body=[self.stackSubnodes(node)])

    def evalExport(self, node: org.Export) -> BlockId:
        if node.exporter == "typst":
            edit_config = node.getArguments("edit-config")
            if edit_config and 0 < len(edit_config.args):
                match edit_config.args[0].getString():
                    case "pre-visit":
                        return self.string("")

                    case "in-visit":
                        self.applyExportConfig(node)
                        return self.string("")

            else:
                return self.string(node.content)

        else:
            return self.string("")

    def evalSubtree(self, node: org.Subtree) -> BlockId:
        if node.isComment or node.isArchived:
            return self.string("")

        res = self.t.stack([])

        tags = []
        for tag in node.tags:
            for it in getFlatTags(tag):
                tags.append("##".join(it))

        self.t.add_at(
            res,
            self.t.line([
                self.call(
                    self.c.tags.subtree,
                    dict(
                        level=node.level,
                        tags=RawBlock(
                            self.t.pars(
                                self.t.csv([self.t.wrap_quote(tag) for tag in tags]))),
                    ),
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
            if isinstance(it, org.Export):
                log(CAT).info(org.treeRepr(it))
                edit_config = it.getArguments("edit-config")
                if edit_config and 0 < len(edit_config.args):
                    if edit_config.args[0].getString() == "pre-visit":
                        self.applyExportConfig(it)

        for it in node:
            self.t.add_at(res, self.exp.eval(it))

        return res

    def evalMacro(self, node: org.Macro) -> BlockId:
        return self.string("")

    def evalTime(self, node: org.Time) -> BlockId:
        return self.string(formatDateTime(node.getStatic().time))

    def evalLink(self, node: org.Link) -> BlockId:
        match node.getLinkKind():
            case org.LinkKind.Attachment:
                return self.string("")

            case org.LinkKind.Raw:
                return self.call(
                    "link",
                    positional=[self.string(node.getRaw().text)],
                    body=[self.exp.eval(node.description)] if node.description else [],
                )

    def evalTimeRange(self, node: org.TimeRange) -> BlockId:
        return self.t.line([
            self.exp.eval(node.from_),
            self.string("--"),
            self.exp.eval(node.to),
        ])

    def evalList(self, node: org.List) -> BlockId:
        return self.wrapStmt(
            node,
            self.call(self.c.tags.list,
                      args=dict(
                          isDescription=node.isDescriptionList(),
                          items=RawBlock(
                              self.expr([RawBlock(self.exp.eval(it)) for it in node])),
                      )))

    def evalListItem(self, node: org.ListItem) -> BlockId:
        args = dict(
            content=RawBlock(self.content(self.stackSubnodes(self.trimSub(node)))))

        if node.isDescriptionItem():
            args["header"] = RawBlock(self.content(self.exp.eval(node.header)))
            args["isDescription"] = True

        else:
            args["isDescription"] = False

        return self.call(self.c.tags.listItem, args=args, isContent=True)
