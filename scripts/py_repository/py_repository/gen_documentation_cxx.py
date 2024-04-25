from beartype import beartype
import tree_sitter
import py_repository.gen_documentation_utils as docutils
from py_codegen.gen_tu_cpp import QualType, ReferenceKind, QualTypeKind
from beartype.typing import Union, Tuple, Optional, List, Iterable
from pathlib import Path
from tree_sitter import Parser
import dominate.tags as tags
import dominate.util as util
import py_repository.gen_documentation_data as docdata
from pydantic import BaseModel
from enum import Enum
from dataclasses import replace
from pydantic import Field, SerializeAsAny
from py_repository.gen_documentation_utils import fail_node, get_subnode
from beartype.typing import Type, TypeVar, Dict
from py_codegen.refl_read import strip_comment_prefixes
from pygments import lex
from pygments.lexers import CppLexer
import py_haxorg.pyhaxorg_wrap as org
from sqlalchemy.orm import Session
import py_repository.gen_coverage_cxx as cov
from py_scriptutils.script_logging import log

CAT = "docgen"

T = TypeVar("T")


class DocCxxInclude(docdata.DocBase, extra="forbid"):
    Target: str


class DocCxxIdent(docdata.DocBase, extra="forbid"):
    # Unnamed fields and function arguments are allowed in C++
    Name: Optional[str]
    Type: QualType
    Value: Optional[str] = None
    IsTemplateVariadic: bool = False


class DocCxxFunctionKind(str, Enum):
    StandaloneFunction = "StandaloneFunction"
    ImplicitConvertOperator = "ImplicitConvertOperator"
    Constructor = "Constructor"
    ClassMethod = "ClassMethod"


class DocCxxFunction(docdata.DocBase, extra="forbid"):
    # Implicit conversion operator does not have a dedicated name
    Name: Optional[str]
    ReturnTy: Optional[QualType]
    Kind: DocCxxFunctionKind
    Arguments: List[DocCxxIdent] = Field(default_factory=list)
    IsConst: bool = False
    IsStatic: bool = False
    IsVirtual: bool = False


class DocCxxTypedef(docdata.DocBase, extra="forbid"):
    Old: QualType
    New: QualType


class DocCxxEnumField(docdata.DocBase, extra="forbid"):
    Name: str
    Value: Optional[str] = None


class DocCxxEnum(docdata.DocBase, extra="forbid"):
    Name: Optional[QualType]
    Fields: List[DocCxxEnumField] = Field(default_factory=list)


class DocCxxRecord(docdata.DocBase, extra="forbid"):
    Name: Optional[QualType]
    Nested: SerializeAsAny[List["DocCxxEntry"]] = Field(default_factory=list)

    @beartype
    def getNested(self, Target: Type[T]) -> List[T]:
        return list(filter(lambda it: isinstance(it, Target), self.Nested))


class DocCodeRunCall(BaseModel, extra="forbid"):
    Count: int
    CalledBy: str


class DocCodeCxxCoverage(BaseModel, extra="forbid"):
    Call: List[DocCodeRunCall] = Field(default_factory=list)


class DocCodeCxxLine(docdata.DocCodeLine, extra="forbid"):
    Text: str
    Coverage: Optional[DocCodeCxxCoverage] = None


class DocCodeCxxFile(docdata.DocCodeFile, extra="forbid"):
    Content: SerializeAsAny[List["DocCxxEntry"]] = Field(default_factory=list)
    Lines: List[DocCodeCxxLine] = Field(default_factory=list)
    Coverage: Optional[cov.CoverageSegmentTree] = Field(default=None)

    # FIXME temporary workaround until I implement coverage segment tree serde.
    class Config:
        orm_mode = True
        arbitrary_types_allowed = True
        json_encoders = {cov.CoverageSegmentTree: lambda v: "Not serializable"}


class DocCxxConcept(docdata.DocBase, extra="forbid"):
    Name: QualType


DocCxxEntry = Union[
    DocCxxRecord,
    DocCxxInclude,
    DocCxxFunction,
    DocCxxIdent,
    DocCxxConcept,
    DocCxxTypedef,
    DocCxxEnum,
    DocCxxEnumField,
    "DocCxxNamespace",
]


class DocCxxNamespace(docdata.DocBase, extra="forbid"):
    Name: Optional[QualType] = None
    Nested: SerializeAsAny[List[DocCxxEntry]] = Field(default_factory=list)


DocCxxRecord.model_rebuild()
DocCxxFunction.model_rebuild()
DocCxxNamespace.model_rebuild()
DocCodeCxxFile.model_rebuild()


@beartype
def parse_cxx(file: Union[Path, str]) -> tree_sitter.Tree:
    parser = Parser()
    parser.set_language(docutils.CPP_LANG)
    if isinstance(file, Path):
        return parser.parse(file.read_bytes())

    else:
        return parser.parse(file.encode())


@beartype
def convert_pointer_wraps(node: tree_sitter.Node, mut_type: QualType):
    match node.type:
        case "pointer_declarator":
            mut_type.ptrCount += 1
            if get_subnode(node, 0).type == "type_qualifier":
                convert_pointer_wraps(get_subnode(node, 1), mut_type)

            else:
                convert_pointer_wraps(get_subnode(node, 0), mut_type)

        case "parameter_declaration" | \
             "optional_parameter_declaration" | \
             "pointer_type_declarator" | \
             "variadic_parameter_declaration":
            decl = get_subnode(node, "declarator")
            if decl:
                convert_pointer_wraps(decl, mut_type)

            for sub in node.named_children:
                if sub.type == "type_qualifier":
                    convert_pointer_wraps(sub, mut_type)

        case "qualified_identifier":
            # ~T::*field~
            convert_pointer_wraps(get_subnode(node, "name"), mut_type)

        case "abstract_reference_declarator":
            mut_type.RefKind = ReferenceKind.LValue

        case "type_qualifier":
            if "const" in node.text.decode():
                mut_type.isConst = True

        case "variadic_declarator":
            mut_type.IsPackExpansion = True
            convert_pointer_wraps(get_subnode(node, 0), mut_type)

        case "reference_declarator":
            if "&&" in node.text.decode():
                mut_type.RefKind = ReferenceKind.RValue

            elif "&" in node.text.decode():
                mut_type.RefKind = ReferenceKind.LValue

            convert_pointer_wraps(get_subnode(node, 0), mut_type)

        case "array_declarator":
            pass

        case "function_declarator" | "identifier" | "type_identifier":
            pass

        case _:
            raise fail_node(node, f"convert pointer wraps {mut_type.format()}")


@beartype
@docdata.note_used_node
def convert_cxx_type(
    node: tree_sitter.Node,
    name_decl: Optional[tree_sitter.Node] = None,
) -> QualType:

    def aux(node: tree_sitter.Node) -> QualType:
        match node.type:
            case "namespace_identifier" | \
                "type_identifier" | \
                "primitive_type" | \
                "sized_type_specifier" | \
                "placeholder_type_specifier" | \
                "identifier":
                return QualType.ForName(name=node.text.decode())

            case "pointer_declarator":
                result = aux(get_subnode(node, "declarator"))
                return result.model_copy(update=dict(ptrCount=result.ptrCount + 1))

            case "parameter_pack_expansion":
                return aux(
                    node.named_child(0)).model_copy(update=dict(IsPackExpansion=True))

            case "template_type":
                return QualType(
                    name=get_subnode(node, "name").text.decode(),
                    Parameters=[
                        aux(it)
                        for it in get_subnode(node, "arguments").children
                        if it.is_named and it.type != "comment"
                    ],
                )

            case "type_descriptor":
                return aux(get_subnode(node, "type"))

            case "dependent_type" | "dependent_name":
                return aux(node.named_child(0))

            case "number_literal" | "binary_expression" | "decltype" | "sizeof_expression":
                return QualType(Kind=QualTypeKind.TypeExpr, expr=node.text.decode())

            case "template_function":
                result = aux(get_subnode(node, "name"))
                for sub in get_subnode(node, "arguments").named_children:
                    result.Parameters.append(aux(sub))

                return result

            case "nested_namespace_specifier":
                result = aux(node.named_children[-1])
                for item in node.named_children[:1]:
                    result.Spaces.append(aux(item))

                return result

            case "qualified_identifier":
                scopes: List[QualType] = []
                scoped = node
                IsGlobalSpace = False
                while scoped:
                    if scoped.type == "qualified_identifier":
                        if get_subnode(scoped, "scope"):
                            # `::Token<K, V>` is a namespaced identifier but it does not have a scope
                            scopes.append(aux(get_subnode(scoped, "scope")))

                        else:
                            IsGlobalSpace = True

                        scoped = get_subnode(scoped, "name")

                    else:
                        scopes.append(aux(scoped))
                        scoped = None

                scopes = scopes[::-1]

                return scopes[0].model_copy(update=dict(
                    Spaces=scopes[1:],
                    isGlobalNamespace=IsGlobalSpace,
                ))

            case _:
                raise fail_node(node, "convert_cxx_type")

    result = aux(node)
    if name_decl:
        convert_pointer_wraps(node=name_decl, mut_type=result)

    return result


@beartype
def get_name_node(node: tree_sitter.Node) -> Optional[tree_sitter.Node]:
    match node.type:
        case "field_identifier" | \
            "type_identifier" | \
            "null" | \
            "identifier" | \
            "qualified_identifier" | \
            "namespace_identifier" | \
            "identifier" | \
            "operator_name" | \
            "primitive_pype":
            return node

        case "array_declarator" | \
             "function_declarator" | \
             "enumerator" | \
             "template_type" | \
             "preproc_def" | \
             "enum_specifier" | \
             "pointer_declarator" | \
             "preproc_function_def" | \
             "assignment_expression":
            return get_name_node(node.named_child(0))

        case "declaration" | \
             "init_declarator" | \
             "parameter_declaration" | \
            "optional_parameter_declaration" | \
             "variadic_parameter_declaration":
            return get_name_node(get_subnode("declarator"))

        case "abstract_reference_declarator":
            return None

        case _:
            if 0 < node.named_child_count:
                return get_name_node(node.named_child(node.named_child_count - 1))

            else:
                raise fail_node(node, "get_name_node")


@beartype
def convert_cxx_doc(doc: docdata.DocNodeGroup) -> Optional[docdata.DocText]:
    if doc.comments:
        return docdata.DocText(Text="\n".join(
            ["\n".join(strip_comment_prefixes(it.text.decode())) for it in doc.comments]))


@beartype
@docdata.note_used_node
def convert_cxx_entry(doc: docdata.DocNodeGroup) -> List[DocCxxEntry]:
    node = doc.node
    result = []

    if not node:
        return []

    match node.type:
        case "declaration":
            return []

        case "preproc_ifdef":
            result = []
            for item in docdata.convert_comment_groups(doc.node):
                conv = convert_cxx_entry(item)
                if conv:
                    result += conv

            return result

        case "enumerator":
            name_node = get_subnode(doc.node, "name")
            result = [
                DocCxxEnumField(
                    Name=name_node.text.decode(),
                    Doc=convert_cxx_doc(doc),
                    **docdata.getNodePoints(doc.node, name_node),
                )
            ]

        case "concept_definition":
            name_node = get_subnode(doc.node, "name")
            result = [
                DocCxxConcept(
                    Name=convert_cxx_type(name_node),
                    Doc=convert_cxx_doc(doc),
                    **docdata.getNodePoints(doc.node, name_node),
                )
            ]

        case "enum_specifier":
            name_node = get_subnode(doc.node, "name")
            Enum = DocCxxEnum(
                Name=name_node and convert_cxx_type(name_node),
                Doc=convert_cxx_doc(doc),
                **docdata.getNodePoints(doc.node, name_node),
            )

            if not get_subnode(doc.node, "body"):
                # Tree-sitter grammar does not handle `enum class [[refl]] Kind {}` property at the moment
                return []

            for field in docdata.convert_comment_groups(get_subnode(doc.node, "body")):
                conv = convert_cxx_entry(field)
                if len(conv) == 1:
                    Enum.Fields.append(conv[0])

                else:
                    raise fail_node(field.node, "enum field")

            result = [Enum]

        case "field_declaration":
            record = get_subnode(doc.node, "type")
            if record and record.type in [
                    "struct_specifier",
                    "class_specifier",
                    "enum_specifier",
                    "type_identifier",
            ]:
                return convert_cxx_entry(replace(doc, node=record))

            field_decl = get_subnode(doc.node, ["declarator", "declarator"])
            if not field_decl:
                field_decl = get_subnode(doc.node, "declarator")

            if field_decl:
                Type = get_subnode(doc.node, "type")
                if Type.type in ["union_specifier", "struct_specifier"]:
                    # TODO handle anon type declarations in fields `struct A { int b; } field;`
                    return []

                else:
                    result = [
                        DocCxxIdent(
                            Name=field_decl.text.decode(),
                            Type=convert_cxx_type(Type),
                            Doc=convert_cxx_doc(doc),
                            Value=get_subnode(doc.node, "default_value").text.decode()
                            if get_subnode(doc.node, "default_value") else None,
                            **docdata.getNodePoints(doc.node, field_decl),
                        )
                    ]

            else:
                if get_subnode(doc.node,
                               ["type"]).type in ["union_specifier", "struct_specifier"]:
                    return []  # TODO anon types with no field declaration attached

                else:
                    raise fail_node(doc.node, "field declaration")


        case "parameter_declaration" | \
             "optional_parameter_declaration" | \
             "variadic_parameter_declaration":
            name_node = get_subnode(doc.node, "declarator")
            if name_node:
                name_node = get_name_node(name_node)

            ident = DocCxxIdent(
                Type=convert_cxx_type(get_subnode(doc.node, "type"), doc.node),
                Name=name_node and name_node.text.decode(),
                Doc=convert_cxx_doc(doc),
                **docdata.getNodePoints(doc.node, name_node),
            )

            if node.type == "optional_parameter_declaration":
                ident.Value = get_subnode(doc.node, "default_value").text.decode()

            return [ident]

        case "alias_declaration":
            name_node = get_subnode(doc.node, "type")
            result = [
                DocCxxTypedef(
                    Old=convert_cxx_type(get_subnode(doc.node, "name")),
                    New=convert_cxx_type(name_node),
                    Doc=convert_cxx_doc(doc),
                    **docdata.getNodePoints(doc.node, name_node),
                )
            ]

        case "type_definition":
            name_node = get_subnode(doc.node, "declarator")
            result = [
                DocCxxTypedef(
                    Old=convert_cxx_type(get_subnode(doc.node, "type")),
                    New=convert_cxx_type(name_node),
                    Doc=convert_cxx_doc(doc),
                    **docdata.getNodePoints(doc.node, name_node),
                )
            ]

        case "function_definition":
            decl = get_subnode(node, "declarator")

            if get_subnode(decl, "declarator"):
                if decl.type == "operator_cast":
                    func = DocCxxFunction(
                        Name=None,
                        Kind=DocCxxFunctionKind.ImplicitConvertOperator,
                        ReturnTy=convert_cxx_type(get_subnode(decl, "type")),
                        **docdata.getNodePoints(doc.node, get_subnode(decl, "type")),
                    )

                    decl = get_subnode(decl, "declarator")

                else:
                    if get_subnode(node, "type"):
                        name_node = get_name_node(get_subnode(decl, "declarator"))
                        func = DocCxxFunction(
                            Kind=DocCxxFunctionKind.StandaloneFunction,
                            Name=name_node.text,
                            ReturnTy=convert_cxx_type(get_subnode(node, "type"), decl),
                            Doc=convert_cxx_doc(doc),
                            **docdata.getNodePoints(doc.node, name_node),
                        )

                        while decl.type == "pointer_declarator":
                            decl = get_subnode(decl, "declarator")

                    else:
                        name_node = get_subnode(decl, "declarator")
                        func = DocCxxFunction(
                            Name=name_node.text,
                            ReturnTy=None,
                            Kind=DocCxxFunctionKind.Constructor,
                            Doc=convert_cxx_doc(doc),
                            **docdata.getNodePoints(doc.node, name_node),
                        )

                for param in docdata.convert_comment_groups(
                        get_subnode(decl, "parameters")):
                    func.Arguments += convert_cxx_entry(param)

                result = [func]

        case "class_specifier" | "struct_specifier" | "union_specifier":
            body = get_subnode(node, "body")
            if body:
                name_node = get_subnode(node, "name")
                record = DocCxxRecord(
                    Name=name_node and convert_cxx_type(name_node),
                    Doc=convert_cxx_doc(doc),
                    **docdata.getNodePoints(doc.node, name_node),
                )

                for group in docdata.convert_comment_groups(body):
                    conv = convert_cxx_entry(group)
                    for it in conv:
                        if it:
                            record.Nested.append(it)

                result = [record]

        case "linkage_specification":
            return convert_cxx_entry(replace(doc, node=get_subnode(node, "body")))

        case "template_declaration":
            template_stack: List[tree_sitter.Node] = []
            template = node
            while True:
                template_stack.append(get_subnode(template, "parameters"))
                if template.named_child(1).type == "template_declaration":
                    template = template.named_child(1)

                else:
                    break

            idx = 1

            while template.named_child(idx).type in ["requires_clause", "comment"]:
                idx += 1

            content = template.named_child(idx)

            declared = None
            match content.type:
                case "class_specifier" | "struct_specifier":
                    impl: DocCxxRecord = convert_cxx_entry(replace(doc, node=content))
                    if impl:
                        declared = impl[0]

                case "function_definition":
                    impl: DocCxxFunction = convert_cxx_entry(replace(doc, node=content))
                    if impl:
                        declared = impl[0]

                case "alias_declaration" | "declaration":
                    impl = convert_cxx_entry(replace(doc, node=content))

                    if impl:
                        declared = impl[0]

                case "concept_definition":
                    impl: DocCxxConcept = convert_cxx_entry(replace(doc, node=content))
                    if impl:
                        declared = impl[0]

                case "friend_declaration":
                    return []

                case _:
                    raise fail_node(content,
                                    f"template_declaration content {content.type}")

            if declared:
                result = [declared]

        case "namespace_definition":
            name_node = get_subnode(node, "name")

            if name_node:
                space = DocCxxNamespace(
                    Name=convert_cxx_type(name_node),
                    **docdata.getNodePoints(node, name_node),
                )

            else:
                space = DocCxxNamespace(**docdata.getNodePoints(node, name_node),)

            for it in docdata.convert_comment_groups(get_subnode(node, "body")):
                for entry in convert_cxx_entry(it):
                    if entry:
                        space.Nested.append(entry)

            result = [space]

        case "preproc_function_def":
            return []

        case _:
            if node.type not in [
                    "preproc_include",
                    "preproc_call",
                    "template_instantiation",
                    "preproc_def",
                    "{",
                    ";",
                    "}",
                    "ERROR",
                    "using_declaration",
                    "#ifndef",
                    "identifier",
                    "expression_statement",
                    "#endif",
                    "access_specifier",
                    ":",
                    "namespace_alias_definition",
                    "friend_declaration",
                    ")",
                    "static_assert_declaration",
                    "preproc_else",
                    "preproc_if",
                    "type_identifier",
                    "struct",
                    "base_class_clause",
            ]:
                raise fail_node(node, f"convert cxx entry '{node.type}'")

    return result


@beartype
def convert_cxx_tree(
    tree: tree_sitter.Tree,
    RootPath: Path,
    AbsPath: Path,
    coverage_session: Optional[Session],
) -> DocCodeCxxFile:
    result: List[DocCxxEntry] = []
    for toplevel in docdata.convert_comment_groups(tree.root_node):
        entry = convert_cxx_entry(toplevel)
        if entry:
            result += entry

    outfile = DocCodeCxxFile(
        Content=result,
        RelPath=AbsPath.relative_to(RootPath),
        Lines=[
            DocCodeCxxLine(Text=line, Index=idx)
            for idx, line in enumerate(AbsPath.read_text().splitlines())
        ],
    )

    if coverage_session:
        query = cov.get_coverage_of(coverage_session, AbsPath)
        if query is not None:
            log(CAT).info(f"Has coverage for {AbsPath}")
            outfile.Coverage = cov.CoverageSegmentTree(
                it[0]
                for it in coverage_session.execute(query.where(
                    cov.CovSegment.IsLeaf == True)))
            

    return outfile


@beartype
def get_docs_fragment(
    entry: Union[DocCxxEntry, QualType],
    Context: List[QualType] = [],
) -> str:
    ctx = "_".join(get_docs_fragment(C) for C in Context)
    if ctx:
        ctx += "_"

    match entry:
        case QualType():
            result = "_".join(["ns_" + get_docs_fragment(s) for s in entry.Spaces])
            result += "t_" + entry.name
            return ctx + result

        case DocCxxRecord():
            return ctx + get_docs_fragment(entry.Name)

        case DocCxxEnum():
            return ctx + get_docs_fragment(entry.Name)

        case DocCxxFunction():
            return ctx + (entry.Name or "None")

        case DocCxxTypedef():
            return ctx + get_docs_fragment(entry.New)

        case DocCxxIdent():
            return ctx + entry.Name

        case DocCxxConcept():
            return ctx + get_docs_fragment(entry.Name)

        case DocCxxNamespace():
            return ctx + get_docs_fragment(entry.Name)

        case _:
            raise ValueError(f"TODO {type(entry)}")


@beartype
def aux_qualifiers(t: QualType) -> Optional[tags.span]:
    text = ""

    if t.isConst:
        text += "const"

    text += "*" * t.ptrCount

    match t.RefKind:
        case ReferenceKind.RValue:
            text += "&&"

        case ReferenceKind.LValue:
            text += "&"

    if text:
        return tags.span(util.text(text), _class="type-qual")


@beartype
def get_type_span(Type: QualType) -> tags.span:

    def csv_list(items: Iterable[tags.html_tag],
                 split: tags.html_tag) -> List[tags.html_tag]:
        result = []
        first = False
        for Parameter in items:
            if not first:
                result.append(split)

            first = False
            result.append(Parameter)

        return result

    qual = aux_qualifiers(Type)
    match Type:
        case QualType(Kind=QualTypeKind.RegularType):
            head = tags.span(util.text(Type.name), _class="type-head")
            if qual:
                head.add(qual)

            if Type.Parameters:
                head.add(
                    util.text("<"),
                    csv_list((get_type_span(P) for P in Type.Parameters),
                             util.text(", ")),
                    util.text(">"),
                )

            return head

        case QualType(Kind=QualTypeKind.TypeExpr):
            return tags.span(util.text(Type.expr))

        case _:
            raise ValueError(str(Type.Kind))


@beartype
def gen_ident_spans(ident: DocCxxIdent) -> Tuple[tags.span, util.text, tags.span]:
    return (
        get_type_span(ident.Type),
        util.text(ident.Name if ident.Name else ""),
        tags.span(util.text(ident.Value)) if ident.Value else tags.span(),
    )


@beartype
def get_entry_div(
        entry: DocCxxEntry, context: List[Union[
            DocCxxNamespace,
            DocCxxEnum,
            DocCxxRecord,
        ]]) -> tags.div:
    res = tags.div(_class=f"docs-entry-{type(entry).__name__}")
    docs = docdata.get_doc_block(entry)
    if docs:
        res.attributes["class"] += " entry-documented"

    else:
        res.attributes["class"] += " entry-undocumented"

    match entry:
        case DocCxxRecord():
            if entry.Name:
                link = docdata.get_name_link(entry.Name.name, entry)
            else:
                link = util.text("<anon>")

            link = tags.span(util.text("Record "), link, _class="class-name")
            res.add(link)

            if docs:
                res.add(docs)

            if entry.getNested(DocCxxIdent):
                nested = tags.div(_class="nested-record")
                nested.add(tags.p(util.text(f"Fields")))
                field_table = tags.table(_class="record-fields")
                for item in entry.getNested(DocCxxIdent):
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

            if entry.getNested(DocCxxEnum):
                nested = tags.div(_class="nested-record")
                nested.add(tags.p(util.text(f"Nested enums")))
                for item in entry.getNested(DocCxxEnum):
                    nested.add(get_entry_div(item, context + [entry]))

                res.add(nested)

            if entry.getNested(DocCxxFunction):
                nested = tags.div(_class="nested-record")
                nested.add(tags.p(util.text(f"Methods")))
                for item in entry.getNested(DocCxxFunction):
                    nested.add(get_entry_div(item, context + [entry]))

                res.add(nested)

            if entry.getNested(DocCxxRecord):
                nested = tags.div(_class="nested-record")
                nested.add(tags.p(util.text(f"Nested records")))
                for item in entry.getNested(DocCxxRecord):
                    nested.add(get_entry_div(item, context + [entry]))

                res.add(nested)

        case DocCxxIdent():
            res.add(util.text("non-record ident"))

        case DocCxxFunction():
            if context and isinstance(context[-1], DocCxxFunction):
                meth = tags.div()

                if docs:
                    meth.add(docs)

                res.add(meth)

            else:
                func = tags.div()
                sign = tags.table(_class="func-signature")
                ret = get_type_span(entry.ReturnTy) if entry.ReturnTy else util.text("")

                @beartype
                def ident_row(ident: DocCxxIdent) -> Tuple[tags.td, tags.td, tags.td]:
                    return tuple(tags.td(arg) for arg in gen_ident_spans(ident))

                for row in docdata.format_argument_rows(
                        ReturnType=ret,
                        Arguments=[ident_row(arg) for arg in entry.Arguments],
                        FuncName=docdata.get_name_link(entry.Name, entry),
                ):
                    sign.add(row)

                func.add(sign)

                if docs:
                    func.add(docs)

                res.add(func)

        case _:
            res.add(util.text(str(type(entry))))

    return res


@beartype
def get_html_docs_div(code_file: DocCodeCxxFile) -> tags.div:
    div = tags.div(_class="page-tab-content", id="page-docs")

    for item in code_file.Content:
        div.add(get_entry_div(item, []))

    return div


@beartype
def get_html_code_div(code_file: DocCodeCxxFile) -> tags.div:
    decl_locations: Dict[(int, int), docdata.DocBase] = {}

    def aux_locations(entry: DocCxxEntry):
        decl_locations[(entry.NamePoint)] = entry
        match entry:
            case DocCxxRecord():
                for sub in entry.Nested:
                    aux_locations(sub)

    for entry in code_file.Content:
        aux_locations(entry)

    def get_attr_spans(line: DocCodeCxxLine) -> List[tags.span]:
        return []

    highlight_lexer = CppLexer()

    def get_line_spans(line: DocCodeCxxLine) -> List[tags.span]:
        return list(
            docdata.get_code_line_span(
                line=line,
                highilght_lexer=highlight_lexer,
                decl_locations=decl_locations,
                get_docs_fragment=get_docs_fragment,
            ))

    return docdata.get_html_code_div_base(
        Lines=code_file.Lines,
        get_line_spans=get_line_spans,
    )
