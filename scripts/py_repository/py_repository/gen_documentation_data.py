from pydantic import BaseModel, Field
from beartype import beartype
from beartype.typing import Tuple, Dict, Optional, List, Union, Callable, Any
from pathlib import Path
import dominate.tags as tags
import dominate.util as util
from pygments import lex
from pygments.token import Token, _TokenType
from py_repository.gen_documentation_utils import abbreviate_token_name
from dataclasses import dataclass, field
import py_haxorg.pyhaxorg_wrap as org
from py_exporters.export_html import ExporterHtml
import itertools
from py_scriptutils.script_logging import log
from functools import wraps
from py_scriptutils.rich_utils import render_rich

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
def get_code_line_span(
    line: DocCodeLine,
    highilght_lexer,
) -> Tuple[tags.span, tags.span]:
    tokens = tags.span(_class="code-line-text")
    column = 0

    for token_type, token_text in lex(line.Text, highilght_lexer):
        span = tags.span(token_text.strip("\n"), _class=abbreviate_token_name(token_type))
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
