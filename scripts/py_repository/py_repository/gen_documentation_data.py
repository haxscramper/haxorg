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
def getNodePoints(node: tree_sitter.Node) -> Dict[str, Tuple[int, int]]:
    return dict(StartPoint=node.start_point, EndPoint=node.end_point)


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
