from beartype.typing import List, Optional, Union, Dict
from pathlib import Path
from beartype import beartype
import tree_sitter
from py_repository.gen_documentation_utils import fail_node, tree_repr, PY_LANG, get_subnode
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


class DocCodePyLine(docdata.DocCodeLine, extra="forbid"):
    pass


class DocPyType(BaseModel, extra="forbid"):
    Name: str
    Parameters: List["DocPyType"] = Field(default_factory=list)


class DocPyIdent(docdata.DocBase, extra="forbid"):
    Name: str
    Type: DocPyType
    Default: Optional[str] = None


class DocPyDecorator(docdata.DocBase, extra="forbid"):
    Name: str


class DocPyFunction(docdata.DocBase, extra="forbid"):
    Name: str
    ReturnTy: Optional[DocPyType] = None
    Arguments: List[DocPyIdent] = Field(default_factory=list)
    Decorators: List[DocPyDecorator] = Field(default_factory=list)


class DocPyClass(docdata.DocBase, extra="forbid"):
    Name: str
    Nested: List["DocPyEntry"]


DocPyEntry = Union[DocPyClass, DocPyFunction]

DocPyClass.model_rebuild()
DocPyFunction.model_rebuild()


class DocCodePyFile(docdata.DocCodeFile, extra="forbid"):
    Content: SerializeAsAny[List["DocPyEntry"]] = Field(default_factory=list)
    Lines: List[DocCodePyLine] = Field(default_factory=list)


@beartype
def get_name_node(node: tree_sitter.Node) -> Optional[tree_sitter.Node]:
    match node.type:
        case "identifier":
            return node

        case _:
            raise fail_node(node, "get_name_node")


@beartype
def convert_py_type(node: tree_sitter.Node) -> DocPyType:
    match node.type:
        case "identifier":
            return DocPyType(Name=node.text.decode())

        case "type":
            return convert_py_type(get_subnode(node, 0))

        case _:
            raise fail_node(node, "convert_py_type")


@beartype
def convert_py_entry(doc: docdata.DocNodeGroup) -> List[DocPyEntry]:
    node = doc.node

    if not node:
        return []

    match node.type:
        case "function_definition":
            name = get_name_node(get_subnode(node, "name"))
            func = DocPyFunction(
                ReturnTy=convert_py_type(get_subnode(node, "return_type")),
                Name=name.text.decode(),
                **docdata.getNodePoints(node, name),
            )

            for arg in get_subnode(node, "parameters").children:
                func.Arguments.append(convert_py_entry(arg))

            return [func]

        case _:
            raise fail_node(node, "convert_py_entry")

    return []


@beartype
def convert_py_tree(tree: tree_sitter.Tree, RootPath: Path,
                    AbsPath: Path) -> DocCodePyFile:
    result: List[DocPyEntry] = []

    for toplevel in docdata.convert_comment_groups(tree.root_node):
        entry = convert_py_entry(toplevel)
        if entry:
            result += entry

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
