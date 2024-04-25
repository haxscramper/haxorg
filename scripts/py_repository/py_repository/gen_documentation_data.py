from pydantic import BaseModel, Field
from beartype import beartype
import tree_sitter
from beartype.typing import Tuple, Dict, Optional, List, Union, Callable, Any
from pathlib import Path
import dominate.tags as tags
import dominate.util as util
from pygments import lex
from pygments.token import Token, _TokenType
from py_repository.gen_documentation_utils import abbreviate_token_name
import tree_sitter
from dataclasses import dataclass, field
import py_haxorg.pyhaxorg_wrap as org
from py_exporters.export_html import ExporterHtml
import itertools
from py_scriptutils.script_logging import log
from functools import wraps
from py_scriptutils.rich_utils import render_rich
from py_repository.gen_documentation_utils import tree_repr

CAT = "docgen"


class DocText(BaseModel, extra="forbid"):
    Text: str = ""


class DocBase(BaseModel, extra="forbid"):
    StartPoint: Tuple[int, int]
    EndPoint: Tuple[int, int]
    NamePoint: Optional[Tuple[int, int]]
    Doc: Optional[DocText] = None


class DocCodeFile(BaseModel, extra="forbid"):
    RelPath: Path
    IsTest: bool = False


class DocTextFile(BaseModel, extra="forbid"):
    RelPath: Path
    Text: str = ""


class DocDirectory(BaseModel, extra="forbid"):
    RelPath: Path
    CodeFiles: List[DocCodeFile] = Field(default_factory=list)
    TextFiles: List[DocTextFile] = Field(default_factory=list)
    Subdirs: List["DocDirectory"] = Field(default_factory=list)


class DocCodeLine(BaseModel, extra="forbid"):
    Index: int
    Text: str


@beartype
def get_html_path(entry: Union[DocDirectory, DocCodeFile, DocTextFile],
                  html_out_path: Path) -> Path:
    match entry:
        case DocDirectory():
            return html_out_path.joinpath(entry.RelPath)

        case DocCodeFile():
            return html_out_path.joinpath(entry.RelPath).with_stem(
                entry.RelPath.stem +
                entry.RelPath.suffix.replace(".", "_")).with_suffix(".html")


@beartype
def getNodePoints(node: tree_sitter.Node,
                  name_node: Optional[tree_sitter.Node]) -> Dict[str, Tuple[int, int]]:
    return dict(
        StartPoint=node.start_point,
        EndPoint=node.end_point,
        NamePoint=name_node and name_node.start_point,
    )


@beartype
def get_code_line_span(
    line: DocCodeLine,
    highilght_lexer,
    decl_locations: Dict[(int, int), DocBase],
    get_docs_fragment: Callable[[DocBase | Any, List[Any]], tags.a],
) -> Tuple[tags.span, tags.span]:
    tokens = tags.span(_class="code-line-text")
    column = 0

    for token_type, token_text in lex(line.Text, highilght_lexer):
        maybe_entry = decl_locations.get((line.Index, column), None)
        if maybe_entry:
            token_html = tags.a(
                href=f"#{get_docs_fragment(maybe_entry)}",
                onclick="openPage('page-docs')",
            )

            token_html.add(token_text.strip("\n"))

            span = tags.span(token_html,
                          _class=abbreviate_token_name(token_type) + " code-backlink")
            

        else:
            span = tags.span(token_text.strip("\n"),
                          _class=abbreviate_token_name(token_type))
            
        tokens.add(span)

        column += len(token_text)

    return (
        tags.span(str(line.Index), _class="code-line-number", id=f"line-{line.Index}"),
        tokens,
    )


@beartype
def get_html_code_div_base(
    Lines: List[DocCodeLine],
    get_line_spans: Callable[[DocCodeLine], List[tags.span]],
) -> tags.div:
    div = tags.div(_class="page-tab-content", id="page-code")

    for line in Lines:
        hline = tags.div(_class="code-line")
        for span in get_line_spans(line):
            hline.add(span)

        div.add(hline)

    return div


@beartype
@dataclass
class DocNodeGroup():
    comments: List[tree_sitter.Node] = field(default_factory=list)
    node: Optional[tree_sitter.Node] = None
    nested: List["DocNodeGroup"] = field(default_factory=list)


@beartype
def convert_comment_groups(node: tree_sitter.Node) -> List[DocNodeGroup]:
    idx = 0
    nodes = node.children
    converted: List[DocNodeGroup] = []

    def next():
        nonlocal idx
        idx += 1

    def has_next():
        return idx < len(nodes)

    def aux() -> Optional[DocNodeGroup]:
        nonlocal idx
        result = DocNodeGroup()

        def get():
            return nodes[idx]

        def at_skip() -> bool:
            return not get().is_named and get().type != "comment"

        def at_comment() -> bool:
            return get().type == "comment"

        while has_next() and at_skip():
            next()

        while has_next() and at_comment():
            result.comments.append(get())
            next()

        if has_next():
            result.node = get()
            next()

        while has_next() and at_skip():
            next()

        while has_next() and at_comment():
            if get().text.decode().startswith("///<"):
                result.comments.append(get())
                next()

            else:
                break

        if result.node or result.comments:
            return result

    while has_next():
        group = aux()
        if group:
            converted.append(group)

    return converted


def note_used_node(func):

    @wraps(func)
    def impl(*args, **kwargs):
        try:
            return func(*args, **kwargs)

        except Exception as e:
            for value in args:
                if isinstance(value, (tree_sitter.Node, DocNodeGroup)):
                    if isinstance(value, DocNodeGroup):
                        value = value.node

                    if not hasattr(e, "__notes__") or not any(
                        ["TS Tree:" in note for note in e.__notes__]):
                        e.add_note(
                            f"TS Tree: {render_rich(tree_repr(value), color=False)}")

            raise e from None

    return impl


@beartype
def get_entry_docs(entry: DocBase) -> List[Union[tags.html_tag, util.text]]:
    if entry.Doc and entry.Doc.Text:
        parsed = org.parseString(entry.Doc.Text)
        exp = ExporterHtml(get_break_tag=lambda _: util.text(" "))
        return list(itertools.chain(*[exp.exp.evalTop(it) for it in parsed]))

    else:
        return []


@beartype
def get_doc_block(entry: DocBase) -> Optional[tags.div]:
    docs = get_entry_docs(entry)
    if docs:
        it = tags.div(_class="doc-text")
        for item in docs:
            it.add(item)

        return it


@beartype
def format_argument_rows(
    FuncName: tags.html_tag,
    ReturnType: tags.html_tag | util.text,
    Arguments: List[Tuple[tags.td, tags.td, tags.td]],
) -> List[tags.tr]:
    match Arguments:
        case []:
            return [
                tags.tr(
                    tags.td(FuncName),
                    tags.td(util.text("() ->")),
                    tags.td(ReturnType),
                )
            ]

        case [one_arg]:
            return [
                tags.tr(*[
                    tags.td(FuncName),
                    tags.td(util.text("(")),
                    *one_arg,
                    tags.td(util.text(") ->")),
                    tags.td(ReturnType),
                ])
            ]

        case [first_arg, *middle_args, last_arg]:
            return [
                tags.tr(
                    tags.td(FuncName),
                    tags.td(util.text("(")),
                    *first_arg,
                ),
                *[tags.tr(
                    tags.td(),
                    tags.td(),
                    *it,
                ) for it in middle_args],
                tags.tr(
                    tags.td(),
                    tags.td(),
                    *last_arg,
                    tags.td(") ->"),
                    tags.td(ReturnType),
                ),
            ]


@beartype
def get_name_link(name: Optional[str], entry: DocBase) -> tags.html_tag:
    if not name:
        name = "<no-name>"

    link = tags.a(onclick=f"openPage('page-code')", href=f"#line-{entry.StartPoint[0]}")

    link.add(util.text(name))
    return link
