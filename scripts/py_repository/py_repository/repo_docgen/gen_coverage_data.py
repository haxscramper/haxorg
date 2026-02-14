from pathlib import Path

from beartype import beartype
from beartype.typing import List, Optional, Tuple, TypeVar, Union
from pydantic import BaseModel, Field

CAT = "docgen"


class DocText(BaseModel, extra="forbid"):
    "Documentation text"
    Text: str = Field(default="", description="Full text of the documentation")


class DocBase(BaseModel, extra="forbid"):
    "Base class for documentable entry"
    StartPoint: Tuple[int, int] = Field(
        description="line:column starting point of the documentable entry range")
    EndPoint: Tuple[int, int] = Field(
        description="line:column ending point of the documentable entry range")
    NamePoint: Optional[Tuple[int, int]] = Field(
        description="line:column placement for the name of the documentable entry")
    Doc: Optional[DocText] = Field(default=None,
                                   description="Documentation text for the entry")


class DocCodeFile(BaseModel, extra="forbid"):
    "Source file"
    RelPath: Path = Field(description="File path relative to the traversal root")
    IsTest: bool = Field(
        default=False, description="Whether the source code file is a part of test suite")


class DocTextFile(BaseModel, extra="forbid"):
    "Documentation file"
    RelPath: Path = Field(default="",
                          description="File path relative to the traversal root")
    Text: str = Field(default="", description="Full text of the documentation file")


class DocDirectory(BaseModel, extra="forbid"):
    "Project directory and its contents"
    RelPath: Path = Field(description="Directory path relative to the traversal root")
    CodeFiles: List[DocCodeFile] = Field(default_factory=list,
                                         description="Source code files in the directory")
    TextFiles: List[DocTextFile] = Field(
        default_factory=list, description="Documentation files in the directory")
    Subdirs: List["DocDirectory"] = Field(default_factory=list,
                                          description="Nested directories")


class DocCodeLine(BaseModel, extra="forbid"):
    "Single line of the source code"
    Index: int
    "Zero-based index for the code line"
    Text: str
    "Full source code of the line"


T_CodeLine = TypeVar("T_CodeLine", bound=DocCodeLine)


@beartype
def get_html_path(entry: Union[DocDirectory, DocCodeFile, DocTextFile],
                  html_out_path: Path) -> Path:
    """
    Get path for the final HTML document for the code entry
    """
    match entry:
        case DocDirectory():
            return html_out_path.joinpath(entry.RelPath)

        case DocCodeFile():
            return html_out_path.joinpath(entry.RelPath).with_stem(
                entry.RelPath.stem +
                entry.RelPath.suffix.replace(".", "_")).with_suffix(".html")

        case DocTextFile():
            return html_out_path.joinpath(entry.RelPath).with_suffix(".html")
