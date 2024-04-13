from beartype.typing import List, Optional, Union, Dict, Tuple
from pathlib import Path
from beartype import beartype
import tree_sitter
from py_repository.gen_documentation_utils import fail_node, tree_repr, PY_LANG, get_subnode
import py_repository.gen_documentation_data as docdata
from pydantic import SerializeAsAny, BaseModel, Field
import dominate.tags as tags
import dominate.util as util
from pygments.lexers import PythonLexer
from dataclasses import replace


CAT = "docgen"

from py_scriptutils.script_logging import log


@beartype
def parse_py(file: Union[Path, str]) -> tree_sitter.Tree:
    parser = tree_sitter.Parser()
    parser.set_language(PY_LANG)
    if isinstance(file, Path):
        tree = parser.parse(file.read_bytes())

    else:
        tree = parser.parse(file.encode())

    return tree


class DocCodePyLine(docdata.DocCodeLine, extra="forbid"):
    pass


class DocPyType(BaseModel, extra="forbid"):
    Name: str
    Spaces: List[str] = Field(default_factory=list)
    Parameters: List["DocPyType"] = Field(default_factory=list)


class DocPyIdent(docdata.DocBase, extra="forbid"):
    Name: str
    Type: Optional[DocPyType]
    Default: Optional[str] = None
    IsKwargsSplice: bool = False


class DocPyDecorator(docdata.DocBase, extra="forbid"):
    Name: str
    Spaces: List[str] = Field(default_factory=list)
    Arguments: List[str] = Field(default_factory=list)


class DocPyFunction(docdata.DocBase, extra="forbid"):
    Name: str
    ReturnTy: Optional[DocPyType] = None
    Arguments: List[DocPyIdent] = Field(default_factory=list)
    Decorators: List[DocPyDecorator] = Field(default_factory=list)


class DocPyClass(docdata.DocBase, extra="forbid"):
    Name: str
    Bases: List[DocPyType] = Field(default_factory=list)
    Nested: List["DocPyEntry"] = Field(default_factory=list)
    Decorators: List[DocPyDecorator] = Field(default_factory=list)


DocPyEntry = Union[DocPyClass, DocPyFunction, DocPyIdent]

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
def convert_py_type(node: Optional[tree_sitter.Node]) -> Optional[DocPyType]:
    if not node:
        return None

    match node.type:
        case "none":
            return None

        case "identifier":
            return DocPyType(Name=node.text.decode())

        case "type":
            return convert_py_type(get_subnode(node, 0))

        case "attribute":
            Spaces, Node = split_attribute(node)
            head = convert_py_type(Node)
            for space in Spaces:
                head.Spaces.append(space.text.decode())

            return head

        case "generic_type":
            head = convert_py_type(get_subnode(node, 0))
            for param in get_subnode(node, 1).named_children:
                head.Parameters.append(convert_py_type(param))

            return head

        case _:
            raise fail_node(node, "convert_py_type")


@beartype
def convert_decorator(node: tree_sitter.Node) -> DocPyDecorator:
    Spaces: List[str] = []
    Name: tree_sitter.Node = None
    if get_subnode(node, 0).type == "identifier":
        Name = get_subnode(node, 0)

    elif get_subnode(node, 0).type == "call":
        call = get_subnode(node, 0)
        func = get_subnode(call, "function")
        if func.type == "attribute":
            node_spaces, node_name = split_attribute(func)
            Spaces = [S.text.decode() for S in node_spaces]
            Name = node_name

        else:
            Name = call

    elif get_subnode(node, 0).type == "attribute":
        node_spaces, node_name = split_attribute(get_subnode(node, 0))
        Spaces = [S.text.decode() for S in node_spaces]
        Name = node_name

    else:
        raise fail_node(node, "decorator")

    result = DocPyDecorator(
        Spaces=Spaces,
        Name=Name.text.decode(),
        **docdata.getNodePoints(node, Name),
    )

    if get_subnode(node, 0).type == "call":
        for entry in get_subnode(node, [0, "arguments"]).named_children:
            result.Arguments.append(entry.text.decode())

    return result

@beartype
def split_attribute(node: tree_sitter.Node) -> Tuple[List[tree_sitter.Node], tree_sitter.Node]:
    Spaces = []
    Spaces.append(get_subnode(node, "object"))
    return (Spaces, get_subnode(node, "attribute"))

@beartype
def convert_py_entry(doc: docdata.DocNodeGroup) -> List[DocPyEntry]:
    node = doc.node

    if not node:
        return []

    match node.type:
        case "function_definition":
            name = get_name_node(get_subnode(node, "name"))
            return_ty = get_subnode(node, "return_type")
            func = DocPyFunction(
                ReturnTy=return_ty and convert_py_type(return_ty),
                Name=name.text.decode(),
                **docdata.getNodePoints(node, name),
            )

            for arg in docdata.convert_comment_groups(get_subnode(node, "parameters")):
                func.Arguments += convert_py_entry(arg)

            return [func]

        case "decorated_definition":
            entry = convert_py_entry(replace(doc, node=get_subnode(node, "definition")))
            for subnode in node.named_children:
                if subnode.type == "decorator":
                    entry[0].Decorators.append(convert_decorator(subnode))

            return entry

        case "typed_parameter":
            name = get_name_node(get_subnode(node, 0))
            arg = DocPyIdent(
                Name=name.text.decode(),
                Type=convert_py_type(get_subnode(node, "type")),
                **docdata.getNodePoints(node, name),
            )

            return [arg]

        case "identifier":
            return [
                DocPyIdent(
                    Name=node.text.decode(),
                    Type=None,
                    **docdata.getNodePoints(node, node),
                )
            ]

        case "dictionary_splat_pattern":
            Name = get_subnode(node, 0)
            return [
                DocPyIdent(
                    Name=Name.text.decode(),
                    Type=None,
                    **docdata.getNodePoints(node, Name),
                )
            ]

        case "class_definition":
            Name = get_name_node(get_subnode(node, "name"))
            Class = DocPyClass(
                Name=Name.text.decode(),
                **docdata.getNodePoints(node, Name),
            )

            for base in get_subnode(node, "superclasses").named_children:
                Class.Bases.append(convert_py_type(base))

            for sub in docdata.convert_comment_groups(get_subnode(node, "body")):
                Class.Nested += convert_py_entry(sub)

            return [Class]

        case "typed_default_parameter" | "default_parameter":
            name = get_name_node(get_subnode(node, "name"))
            Type = get_subnode(node, "type")
            arg = DocPyIdent(
                Name=name.text.decode(),
                Type=Type and convert_py_type(Type),
                Default=get_subnode(node, "value").text.decode(),
                **docdata.getNodePoints(node, name),
            )

            return [arg]

        case _:
            if node.type in [
                    "import_from_statement",
                    "import_statement",
                    "expression_statement",
                    "if_statement",
            ]:
                return []

            else:
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
