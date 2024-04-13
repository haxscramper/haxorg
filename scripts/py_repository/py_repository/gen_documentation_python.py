from beartype.typing import List, Optional, Union, Dict, Tuple, Type, TypeVar, Iterable
from pathlib import Path
from beartype import beartype
import tree_sitter
from py_repository.gen_documentation_utils import fail_node, tree_repr, PY_LANG, get_subnode, note_used_node
import py_repository.gen_documentation_utils as docutils
import py_repository.gen_documentation_data as docdata
from pydantic import SerializeAsAny, BaseModel, Field
import dominate.tags as tags
import dominate.util as util
from pygments.lexers import PythonLexer
from dataclasses import replace
from enum import Enum

T = TypeVar("T")

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


class DocPyTypeKind(str, Enum):
    Regular = "Regular"
    TypeList = "TypeList"  ## ~Callable[[T1, T2, T3], Res]~
    TypeUnion = "TypeUnion"  ## ~A | B~
    TypeTuple = "TypeTuple"


class DocPyType(BaseModel, extra="forbid"):
    Name: Optional[str] = None
    Spaces: List[str] = Field(default_factory=list)
    Parameters: List["DocPyType"] = Field(default_factory=list)
    Kind: DocPyTypeKind = DocPyTypeKind.Regular


class DocPyIdentKind(str, Enum):
    Regular = "Regular"
    DictSplice = "DictSplice"
    ListSplice = "ListSplice"


class DocPyIdent(docdata.DocBase, extra="forbid"):
    Name: str
    Type: Optional[DocPyType]
    Default: Optional[str] = None
    Kind: DocPyIdentKind = DocPyIdentKind.Regular


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

    @beartype
    def getNested(self, Target: Type[T]) -> List[T]:
        return list(filter(lambda it: isinstance(it, Target), self.Nested))


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

        case "list_splat_pattern":
            return get_subnode(node, 0)

        case _:
            raise fail_node(node, "get_name_node")


@beartype
@note_used_node
def convert_py_type(node: tree_sitter.Node) -> DocPyType:
    match node.type:
        case "identifier" | "none":
            return DocPyType(Name=node.text.decode())

        case "list":
            head = DocPyType(Kind=DocPyTypeKind.TypeList)
            for arg in node.named_children:
                head.Parameters.append(convert_py_type(arg))
            return head

        case "tuple":
            result = DocPyType(Kind=DocPyTypeKind.TypeTuple)
            for param in node.named_children:
                result.Parameters.append(convert_py_type(param))

            return result

        case "binary_operator":
            return DocPyType(
                Kind=DocPyTypeKind.TypeUnion,
                Parameters=[
                    convert_py_type(get_subnode(node, "left")),
                    convert_py_type(get_subnode(node, "right")),
                ],
            )

        case "union_type":
            result = DocPyType(Kind=DocPyTypeKind.TypeUnion)
            for param in node.named_children:
                result.Parameters.append(convert_py_type(param))

            return result

        case "string":
            return DocPyType(Name=get_subnode(node, 1).text.decode())

        case "type":
            return convert_py_type(get_subnode(node, 0))

        case "attribute":
            Spaces, Node = split_attribute(node)
            head = convert_py_type(Node)
            for space in Spaces:
                head.Spaces.append(space.text.decode())

            return head

        case "subscript":
            head = convert_py_type(get_subnode(node, "value"))
            for param in get_subnode(node, "subscript").named_children:
                head.Parameters.append(convert_py_type(param))

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
def split_attribute(
        node: tree_sitter.Node) -> Tuple[List[tree_sitter.Node], tree_sitter.Node]:
    Spaces = []
    Spaces.append(get_subnode(node, "object"))
    return (Spaces, get_subnode(node, "attribute"))


@beartype
@note_used_node
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

        case "list_splat_pattern":
            Name = get_subnode(node, 0)
            return [
                DocPyIdent(
                    Name=Name.text.decode(),
                    Type=None,
                    Kind=DocPyIdentKind.ListSplice,
                    **docdata.getNodePoints(node, Name),
                )
            ]

        case "expression_statement":
            asgn = get_subnode(node, 0)
            if asgn and asgn.type == "assignment":
                left = get_subnode(asgn, "left")
                t = get_subnode(asgn, "type")
                right = get_subnode(asgn, "right")
                if left and t:
                    return [
                        DocPyIdent(
                            Name=left.text.decode(),
                            Type=convert_py_type(t),
                            Default=right and right.text.decode(),
                            **docdata.getNodePoints(node, left),
                        )
                    ]

                else:
                    return []

            else:
                return []

        case "dictionary_splat_pattern":
            Name = get_subnode(node, 0)
            return [
                DocPyIdent(
                    Name=Name.text.decode(),
                    Type=None,
                    Kind=DocPyIdentKind.DictSplice,
                    **docdata.getNodePoints(node, Name),
                )
            ]

        case "class_definition":
            Name = get_name_node(get_subnode(node, "name"))
            Class = DocPyClass(
                Name=Name.text.decode(),
                **docdata.getNodePoints(node, Name),
            )

            if get_subnode(node, "superclasses"):
                for base in get_subnode(node, "superclasses").named_children:
                    if base.type in ["keyword_argument"]:
                        pass

                    else:
                        Class.Bases.append(convert_py_type(base))

            for sub in docdata.convert_comment_groups(get_subnode(node, "body")):
                if sub.node and sub.node.type not in ["pass_statement"]:
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
                    "if_statement",
                    "for_statement",
                    "with_statement",
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
def get_type_span(Type: DocPyType) -> tags.span:

    def csv_list(items: Iterable[tags.html_tag],
                 split: tags.html_tag) -> List[tags.html_tag]:
        result = []
        first = True
        for Parameter in items:
            if not first:
                result.append(split)

            first = False
            result.append(Parameter)

        return result

    head = tags.span(util.text(Type.Name or ""), _class="type-head")
    if Type.Parameters:
        head.add(
            util.text("["),
            csv_list((get_type_span(P) for P in Type.Parameters), util.text(", ")),
            util.text("]"),
        )

    return head


@beartype
def gen_ident_spans(ident: DocPyIdent) -> Tuple[util.text, tags.span, tags.span]:
    return (
        util.text(ident.Name + ":" if ident.Name else ""),
        get_type_span(ident.Type) if ident.Type else tags.span(util.text("")),
        tags.span(util.text(ident.Default)) if ident.Default else tags.span(),
    )


@beartype
def get_entry_div(entry: DocPyEntry, context: List[Union[DocPyClass]]) -> tags.div:
    docs = docdata.get_doc_block(entry)
    res = tags.div(_class=f"docs-entry-{type(entry).__name__}")
    if docs:
        res.attributes["class"] += " entry-documented"

    else:
        res.attributes["class"] += " entry-undocumented"

    match entry:
        case DocPyClass():
            link = docdata.get_name_link(entry.Name, entry)
            link = tags.span(util.text("Class "), link, _class="class-name")
            res.add(link)

            if docs:
                res.add(docs)

            if entry.getNested(DocPyIdent):
                nested = tags.div(_class="nested-record")
                nested.add(tags.p(util.text(f"Fields")))
                field_table = tags.table(_class="record-fields")
                for item in entry.getNested(DocPyIdent):
                    row = tags.tr()
                    Type, Name, Default = gen_ident_spans(item)
                    row.add(tags.td(Type))
                    row.add(tags.td(Name))
                    row.add(tags.td(Default))

                    docs = docdata.get_entry_docs(item)
                    if docs:
                        row.add(tags.td(docs, _class="entry-documented"))

                    else:
                        row.add(tags.td(_class="entry-undocumented"))

                    field_table.add(row)

                nested.add(field_table)

                res.add(nested)

            if entry.getNested(DocPyFunction):
                nested = tags.div(_class="nested-record")
                nested.add(tags.p(util.text(f"Methods")))
                for item in entry.getNested(DocPyFunction):
                    nested.add(get_entry_div(item, context + [entry]))

                res.add(nested)

        case DocPyFunction():
            func = tags.div()
            sign = tags.table(_class="func-signature")
            ret = get_type_span(entry.ReturnTy) if entry.ReturnTy else util.text("")

            def ident_row(ident: DocPyIdent) -> List[tags.td]:
                return [tags.td(arg) for arg in gen_ident_spans(ident)]

            for row in docdata.format_argument_rows(
                    ReturnType=ret,
                    Arguments=[ident_row(arg) for arg in entry.Arguments],
                    FuncName=docdata.get_name_link(entry.Name, entry),
            ):
                sign.add(row)

            func.add(sign)

            res.add(func)

    return res


@beartype
def get_html_docs_div(code_file: DocCodePyFile) -> tags.div:
    div = tags.div(_class="page-tab-content", id="page-docs")

    for item in code_file.Content:
        div.add(get_entry_div(item, []))

    return div
