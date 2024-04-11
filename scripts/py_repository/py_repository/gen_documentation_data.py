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


class DocText(BaseModel, extra="forbid"):
    Text: str = ""


class DocBase(BaseModel, extra="forbid"):
    StartPoint: Tuple[int, int]
    EndPoint: Tuple[int, int]
    NamePoint: Optional[Tuple[int, int]]
    Doc: Optional[DocText] = None


class DocCodeFile(BaseModel, extra="forbid"):
    RelPath: Path


class DocTextFile(BaseModel, extra="forbid"):
    RelPath: Path
    Text: str = ""


class DocDirectory(BaseModel, extra="forbid"):
    RelPath: Path
    CodeFiles: List[DocCodeFile] = Field(default_factory=list)
    TextFiles: List[DocTextFile] = Field(default_factory=list)
    Subdirs: List["DocDirectory"] = Field(default_factory=list)


class DocCodeLine(BaseModel, extra="forbid"):
    Text: str


@beartype
def get_html_path(entry: Union[DocDirectory, DocCodeFile, DocTextFile],
                  html_out_path: Path) -> Path:
    match entry:
        case DocDirectory():
            return html_out_path.joinpath(entry.RelPath)

        case DocCodeFile():
            return html_out_path.joinpath(entry.RelPath).with_suffix(".html")


@beartype
def getNodePoints(node: tree_sitter.Node,
                  name_node: Optional[tree_sitter.Node]) -> Dict[str, Tuple[int, int]]:
    return dict(
        StartPoint=node.start_point,
        EndPoint=node.end_point,
        NamePoint=name_node and name_node.start_point,
    )


@beartype
def get_html_code_div_base(
    Lines: List[DocCodeLine],
    highilght_lexer,
    decl_locations: Dict[(int, int), DocBase],
    get_docs_fragment: Callable[[DocBase | Any], str],
    get_attr_spans: Callable[[DocCodeLine], List[tags.span]],
) -> tags.div:
    div = tags.div(_class="page-tab-content", id="page-code")

    decl_locations: Dict[(int, int), DocBase] = {}

    for idx, line in enumerate(Lines):
        hline = tags.p(_class="code-line")
        hline.add(tags.span(str(idx), _class="code-line-number", id=f"line-{idx}"))

        tokens = tags.span(_class="code-line-text", style="width:600px;")
        column = 0

        for token_type, token_text in lex(line.Text, highilght_lexer):
            maybe_entry = decl_locations.get((idx, column), None)
            if maybe_entry:
                token_html = tags.a(
                    href=f"#{get_docs_fragment(maybe_entry)}",
                    onclick="openPage('page-docs')",
                )

                token_html.add(token_text.strip("\n"))

                tokens.add(
                    tags.span(token_html,
                              _class=abbreviate_token_name(token_type) +
                              " code-backlink"))

            else:
                tokens.add(
                    tags.span(token_text.strip("\n"),
                              _class=abbreviate_token_name(token_type)))

            column += len(token_text)

        hline.add(tokens)

        for span in get_attr_spans(line):
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
