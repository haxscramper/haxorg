from dataclasses import replace
from enum import Enum
from pathlib import Path
import itertools
import py_scriptutils.algorithm

import dominate.tags as tags
import dominate.util as util
import py_repository.gen_coverage_python as cov_docpy
import py_repository.gen_documentation_data as docdata
import py_repository.gen_documentation_utils as docutils
import tree_sitter
from sqlalchemy.orm import Session
from beartype import beartype
from beartype.typing import (Dict, Iterable, List, Optional, Tuple, Type, TypeVar, Union)
from py_repository.gen_documentation_utils import (PY_LANG, fail_node, get_subnode,
                                                   tree_repr)
from pydantic import BaseModel, Field, SerializeAsAny
from pygments.lexers import PythonLexer

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
    TestCoverage: Optional[cov_docpy.LineCoverage] = None


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
@docdata.note_used_node
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
@docdata.note_used_node
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
                if sub.node:
                    match sub.node.type:
                        case "pass_statement":
                            pass

                        case "expression_statement":
                            if get_subnode(sub.node, 0).type == "string":
                                docstr = get_subnode(sub.node, [0, 1])
                                if Class.Doc:
                                    Class.Doc.Text += "\n\n" + docstr.text.decode()

                                else:
                                    Class.Doc = docdata.DocText(Text=docstr.text.decode())

                            else:
                                Class.Nested += convert_py_entry(sub)

                        case _:
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
def convert_py_tree(
    tree: tree_sitter.Tree,
    RootPath: Path,
    AbsPath: Path,
    py_coverage_session: Optional[Session],
) -> DocCodePyFile:
    result: List[DocPyEntry] = []

    if py_coverage_session:
        line_coverage = cov_docpy.get_coverage(py_coverage_session, AbsPath)

    else:
        line_coverage = {}

    for toplevel in docdata.convert_comment_groups(tree.root_node):
        entry = convert_py_entry(toplevel)
        if entry:
            result += entry

    return DocCodePyFile(
        Content=result,
        RelPath=AbsPath.relative_to(RootPath),
        Lines=[
            DocCodePyLine(
                Text=line,
                Index=idx,
                TestCoverage=line_coverage.get(idx, None),
            ) for idx, line in enumerate(AbsPath.read_text().splitlines())
        ],
    )


@beartype
def get_docs_fragment(
    entry: Union[DocPyEntry, DocPyType],
    Context: List[DocPyType] = [],
) -> str:
    ctx = "_".join(get_docs_fragment(C) for C in Context)
    if ctx:
        ctx += "_"

    match entry:
        case DocPyType():
            result = entry.Name

            return ctx + result

        case DocPyClass() | DocPyFunction() | DocPyIdent():
            return ctx + entry.Name

        case _:
            raise ValueError(f"{type(entry)}")


@beartype
def is_empty(line: DocCodePyLine) -> bool:
    return not line.Text.strip()

@beartype
def get_html_code_div(code_file: DocCodePyFile) -> tags.div:
    decl_locations: Dict[(int, int), docdata.DocBase] = {}

    def aux_locations(entry: DocPyEntry):
        decl_locations[(entry.NamePoint)] = entry
        match entry:
            case DocPyClass():
                for sub in entry.Nested:
                    aux_locations(sub)

    for entry in code_file.Content:
        aux_locations(entry)

    unique_coverage_context_spans: List[Tuple[range[int], cov_docpy.LineCoverage]] = []
    for key, group in itertools.groupby(
        (pair for pair in enumerate(code_file.Lines) if not is_empty(pair[1])),
            lambda it: it[1].TestCoverage and it[1].TestCoverage.CoveredBy,
    ):
        Lines = [G[0] for G in group]
        assert not Lines or (isinstance(Lines, list) and
                             isinstance(Lines[0], int)), str(Lines)
        if key:
            unique_coverage_context_spans.append((range(min(Lines), max(Lines) + 1), key))

    @beartype
    def get_attr_spans(line: DocCodePyLine) -> List[tags.span]:
        annotations: List[tags.span] = []

        if not code_file.IsTest and not is_empty(line):
            if line.TestCoverage:
                coverage_group = py_scriptutils.algorithm.first_if(
                    items=unique_coverage_context_spans,
                    pred=lambda it: line.Index in it[0],
                )
                if coverage_group:
                    span = tags.span(_class="coverage-span py-coverage")
                    if coverage_group[0][0] == line.Index:
                        span.attributes["class"] += " coverage-span-names"
                        table = tags.table()
                        for test in line.TestCoverage.CoveredBy:
                            table.add(tags.tr(tags.td(util.text(test.test_name))))

                        span.add(table)

                    else:
                        span.add(util.text("…"))
                        span.attributes["class"] += " coverage-span-continuation"

                    annotations.append(span)

        return annotations

    highlight_lexer = PythonLexer()

    @beartype
    def get_line_spans(line: DocCodePyLine) -> List[tags.span]:
        num_span, line_span = docdata.get_code_line_span(
            line=line,
            highilght_lexer=highlight_lexer,
            decl_locations=decl_locations,
            get_docs_fragment=get_docs_fragment,
        )

        if not code_file.IsTest and not is_empty(line):
            if line.TestCoverage:
                line_span.attributes["class"] += " cov-visited"

            else:
                line_span.attributes["class"] += " cov-skipped"

        return [num_span, line_span] + get_attr_spans(line)

    return docdata.get_html_code_div_base(
        Lines=code_file.Lines,
        get_line_spans=get_line_spans,
    )


@beartype
def get_type_span(Type: Optional[DocPyType]) -> tags.span:

    def aux(Type: DocPyType, _class: str) -> tags.span:

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

        head = tags.span(util.text(Type.Name or ""), _class=_class)
        if Type.Parameters:
            head.add(
                util.text("["),
                csv_list((aux(P, "type-param") for P in Type.Parameters),
                         util.text(", ")),
                util.text("]"),
            )

        return head

    if Type:
        return aux(Type, "type-head")

    else:
        return tags.span(util.text("None"), _class="type-head")


@beartype
def gen_ident_spans(ident: DocPyIdent) -> Tuple[util.text, tags.span, tags.span]:
    return (
        util.text(ident.Name + (":" if ident.Type else "") if ident.Name else ""),
        get_type_span(ident.Type) if ident.Type else tags.span(util.text("")),
        tags.span(util.text(" = " + ident.Default)) if ident.Default else tags.span(),
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
            ret = get_type_span(entry.ReturnTy)
            in_class = context and isinstance(context[-1], DocPyClass)

            @beartype
            def ident_row(ident: DocPyIdent) -> Tuple[tags.td, tags.td, tags.td]:
                return tuple(tags.td(arg) for arg in gen_ident_spans(ident))

            link = tags.span(util.text("def"), docdata.get_name_link(entry.Name, entry))
            link.attributes["class"] = "func-backlink"

            for row in docdata.format_argument_rows(
                    ReturnType=ret,
                    Arguments=[
                        ident_row(arg)
                        for arg in entry.Arguments
                        if (not in_class or arg.Name != "self")
                    ],
                    FuncName=link,
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
