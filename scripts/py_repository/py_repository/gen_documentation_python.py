from beartype.typing import List, Optional, Union, Dict
from pathlib import Path
from beartype import beartype
import tree_sitter
from py_repository.gen_documentation_utils import fail_node, tree_repr, DocNodeGroup, PY_LANG
import py_repository.gen_documentation_data as docdata
from pydantic import SerializeAsAny, BaseModel, Field
import dominate.tags as tags
import dominate.util as util
from pygments.lexers import PythonLexer

@beartype
def parse_py(file: Union[Path, str]) -> tree_sitter.Tree:
    parser = tree_sitter.Parser()
    parser.set_language(PY_LANG)
    if isinstance(file, Path):
        return parser.parse(file.read_bytes())

    else:
        return parser.parse(file.encode())


class DocPyClass(docdata.DocBase, extra="forbid"):
    pass

class DocCodePyLine(docdata.DocCodeLine, extra="forbid"):
    pass

DocPyEntry = Union[DocPyClass]

class DocCodePyFile(docdata.DocCodeFile, extra="forbid"):
    Content: SerializeAsAny[List["DocPyEntry"]] = Field(default_factory=list)
    Lines: List[DocCodePyLine] = Field(default_factory=list)

@beartype
def convert_py_tree(tree: tree_sitter.Tree, RootPath: Path, AbsPath: Path) -> DocCodePyFile:
    result: List[DocPyEntry] = []

    return DocCodePyFile(
        Content=result,
        RelPath=AbsPath.relative_to(RootPath),
        Lines=[DocCodePyLine(Text=line) for line in AbsPath.read_text().splitlines()],
    )

@beartype
def get_docs_fragment(entry: DocPyEntry) -> str:
    return "?"

@beartype
def get_html_code_div(code_file: DocCodePyFile) -> tags.div:
    decl_locations: Dict[(int, int), docdata.DocBase] = {}
    def get_attr_spans(line: DocCodePyLine) -> List[tags.span]:
        return []
    
    return docdata.get_html_code_div_base(
        Lines=code_file.Lines,
        decl_locations=decl_locations,
        highilght_lexer=PythonLexer(),
        get_attr_spans=get_attr_spans,
        get_docs_fragment=get_docs_fragment,
    )


@beartype
def get_html_docs_div(code_file: DocCodePyFile) -> tags.div:
    div = tags.div(_class="page-tab-content", id="page-docs")

    return div
