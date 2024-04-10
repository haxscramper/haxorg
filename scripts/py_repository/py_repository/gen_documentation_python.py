from beartype.typing import List, Optional, Union
from pathlib import Path
from beartype import beartype
import tree_sitter
from py_repository.gen_documentation_utils import fail_node, tree_repr, DocNodeGroup, PY_LANG
from py_repository.gen_documentation_data import DocBase, DocText
from pydantic import SerializeAsAny, BaseModel, Field

@beartype
def parse_py(file: Union[Path, str]) -> tree_sitter.Tree:
    parser = tree_sitter.Parser()
    parser.set_language(PY_LANG)
    if isinstance(file, Path):
        return parser.parse(file.read_bytes())

    else:
        return parser.parse(file.encode())


class DocPyClass(DocBase, extra="forbid"):
    pass

class DocCodePyLine(BaseModel, extra="forbid"):
    Text: str

DocPyEntry = Union[DocPyClass]

class DocCodePyFile(BaseModel, extra="forbid"):
    Content: SerializeAsAny[List["DocPyEntry"]] = Field(default_factory=list)
    Lines: List[DocCodePyLine] = Field(default_factory=list)
    RelPath: Path

@beartype
def convert_py_tree(tree: tree_sitter.Tree, RootPath: Path, AbsPath: Path) -> DocCodePyFile:
    result: List[DocPyEntry] = []

    return DocCodePyFile(
        Content=result,
        RelPath=AbsPath.relative_to(RootPath),
        Lines=[DocCodePyLine(Text=line) for line in AbsPath.read_text().splitlines()],
    )
