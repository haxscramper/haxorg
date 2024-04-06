#!/usr/bin/env python

from tree_sitter import Language, Parser
import tree_sitter
from py_scriptutils.files import get_haxorg_repo_root_path
from pathlib import Path
from beartype import beartype
from beartype.typing import List, Dict, Optional, Any, Union, Iterator, Iterable, TypeVar, Tuple
from py_scriptutils.script_logging import log
from dataclasses import dataclass, field, replace
from pydantic import BaseModel, Field, SerializeAsAny
from rich.console import Console
from py_scriptutils.rich_utils import render_rich
from py_codegen.refl_read import strip_comment_prefixes
from enum import Enum
import itertools

T = TypeVar("T")


def dropnan(values: Iterable[Optional[T]]) -> Iterable[T]:
    return (it for it in values if it)


CAT = "docgen"

from py_codegen.gen_tu_cpp import (GenTuDoc, GenTuTypedef, GenTuTypeGroup, GenTuNamespace,
                                   GenTuStruct, GenTuEntry, GenTuEnum, GenTuIdent,
                                   QualType, QualTypeKind)

thirdparty = get_haxorg_repo_root_path().joinpath("thirdparty")
build_dir = get_haxorg_repo_root_path().joinpath("build_treesitter")
build_so = build_dir.joinpath("lang.so")

Language.build_library(
    build_so,
    [thirdparty.joinpath("tree-sitter-cpp")],
)

CPP_LANG = Language(build_so, "cpp")


@beartype
def parse_cxx(file: Union[Path, str]) -> tree_sitter.Tree:
    parser = Parser()
    parser.set_language(CPP_LANG)
    if isinstance(file, Path):
        return parser.parse(file.read_bytes())

    else:
        return parser.parse(file.encode())


@beartype
def tree_repr(node: Union[tree_sitter.Tree, tree_sitter.Node]) -> str:

    def aux(node: tree_sitter.Node, indent: int, name: Optional[str] = None) -> str:
        result = "  " * indent
        if name:
            result += f"[green]{name}[/green]: "

        result += f"{node.start_point[0]}:{node.start_point[1]} "

        if node.is_named:
            result += f"[cyan]{node.type}[/cyan]"
            if 0 < len(node.children):
                for idx, subnode in enumerate(node.children):
                    if subnode.is_named:
                        result += "\n"
                        result += aux(subnode, indent + 1, node.field_name_for_child(idx))

            else:
                result += " [yellow]\"" + node.text.decode() + "\"[/yellow]"

        else:
            result += "\"" + node.text.decode() + "\""

        return result

    if isinstance(node, tree_sitter.Node):
        return aux(node, 0)

    else:
        return aux(node.root_node, 0)


@beartype
@dataclass
class DocNodeGroup():
    comments: List[tree_sitter.Node] = field(default_factory=list)
    node: Optional[tree_sitter.Node] = None
    nested: List["DocNodeGroup"] = field(default_factory=list)


class DocCxx(BaseModel, extra="forbid"):
    Text: str = ""


@beartype
def getNodePoints(node: tree_sitter.Node) -> Dict[str, Tuple[int, int]]:
    return dict(StartPoint=node.start_point, EndPoint=node.end_point)


class DocCxxBase(BaseModel, extra="forbid"):
    StartPoint: Tuple[int, int]
    EndPoint: Tuple[int, int]
    Doc: DocCxx = Field(default_factory=lambda: DocCxx())


class DocCxxInclude(DocCxxBase, extra="forbid"):
    Target: str
    Doc: Optional[DocCxx] = None


class DocCxxIdent(DocCxxBase, extra="forbid"):
    # Unnamed fields and function arguments are allowed in C++
    Name: Optional[str]
    Type: QualType
    Value: Optional[str] = None
    Doc: Optional[DocCxx] = None
    IsTemplateVariadic: bool = False


class DocCxxFunctionKind(str, Enum):
    StandaloneFunction = "StandaloneFunction"
    ImplicitConvertOperator = "ImplicitConvertOperator"
    Constructor = "Constructor"
    ClassMethod = "ClassMethod"


class DocCxxFunction(DocCxxBase, extra="forbid"):
    # Implicit conversion operator does not have a dedicated name
    Name: Optional[str]
    ReturnTy: Optional[QualType]
    Kind: DocCxxFunctionKind
    Arguments: List[DocCxx] = Field(default_factory=list)
    IsConst: bool = False
    IsStatic: bool = False
    IsVirtual: bool = False
    Doc: Optional[DocCxx] = None


class DocCxxTypedef(DocCxxBase, extra="forbid"):
    Old: QualType
    New: QualType
    Doc: Optional[DocCxx] = None


class DocCxxEnumField(DocCxxBase, extra="forbid"):
    Name: str
    Value: Optional[str] = None
    Doc: Optional[DocCxx] = None


class DocCxxEnum(DocCxxBase, extra="forbid"):
    Name: Optional[QualType]
    Fields: List[DocCxxEnumField] = Field(default_factory=list)
    Doc: Optional[DocCxx] = None


class DocCxxRecord(DocCxxBase, extra="forbid"):
    Name: QualType
    Nested: SerializeAsAny[List["DocCxxEntry"]] = Field(default_factory=list)
    Doc: Optional[DocCxx] = None


class DocCxxConcept(DocCxxBase, extra="forbid"):
    Name: QualType
    Doc: Optional[DocCxx] = None


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


class DocCxxNamespace(BaseModel, extra="forbid"):
    Name: QualType
    Nested: SerializeAsAny[List[DocCxxEntry]] = Field(default_factory=list)



class DocCodeCxxFile(BaseModel, extra="forbid"):
    Content: SerializeAsAny[List[DocCxxEntry]] = Field(default_factory=list)
    Lines: List[str] = Field(default_factory=list)
    RelPath: Path


DocCxxRecord.model_rebuild()
DocCxxFunction.model_rebuild()
DocCxxNamespace.model_rebuild()
DocCodeCxxFile.model_rebuild()

class DocTextFile(BaseModel, extra="forbid"):
    Text: str = ""


class DocDirectory(BaseModel, extra="forbid"):
    CodeFiles: List[DocCodeCxxFile] = Field(default_factory=list)
    TextFiles: List[DocTextFile] = Field(default_factory=list)
    Subdirs: List["DocDirectory"] = Field(default_factory=list)


@beartype
def convert_cxx_type(node: tree_sitter.Node) -> QualType:
    match node.type:
        case "namespace_identifier" | \
            "type_identifier" | \
            "primitive_type" | \
            "sized_type_specifier" | \
            "placeholder_type_specifier" | \
            "identifier":
            return QualType.ForName(name=node.text.decode())

        case "pointer_declarator":
            result = convert_cxx_type(get_subnode(node, "declarator"))
            return result.model_copy(update=dict(ptrCount=result.ptrCount + 1))

        case "parameter_pack_expansion":
            return convert_cxx_type(
                node.named_child(0)).model_copy(update=dict(IsPackExpansion=True))

        case "template_type":
            return QualType(
                name=get_subnode(node, "name").text.decode(),
                Parameters=[
                    convert_cxx_type(it)
                    for it in get_subnode(node, "arguments").children
                    if it.is_named
                ],
            )

        case "type_descriptor":
            return convert_cxx_type(get_subnode(node, "type"))

        case "dependent_type" | "dependent_name":
            return convert_cxx_type(node.named_child(0))

        case "number_literal" | "binary_expression" | "decltype" | "sizeof_expression":
            return QualType(Kind=QualTypeKind.TypeExpr, expr=node.text.decode())

        case "nested_namespace_specifier":
            result = convert_cxx_type(node.named_children[-1])
            for item in node.named_children[:1]:
                result.Spaces.append(convert_cxx_type(item))

            return result

        case "qualified_identifier":
            scopes: List[QualType] = []
            scoped = node
            IsGlobalSpace = False
            while scoped:
                if scoped.type == "qualified_identifier":
                    if get_subnode(scoped, "scope"):
                        # `::Token<K, V>` is a namespaced identifier but it does not have a scope
                        scopes.append(convert_cxx_type(get_subnode(scoped, "scope")))

                    else:
                        IsGlobalSpace = True

                    scoped = get_subnode(scoped, "name")

                else:
                    scopes.append(convert_cxx_type(scoped))
                    scoped = None

            scopes = scopes[::-1]

            return scopes[0].model_copy(update=dict(
                Spaces=scopes[1:],
                isGlobalNamespace=IsGlobalSpace,
            ))

        case _:
            raise fail_node(node, "convert_cxx_type")


@beartype
def convert_cxx_groups(node: tree_sitter.Node) -> List[DocNodeGroup]:
    idx = 0
    nodes = node.children
    converted: List[DocNodeGroup] = []

    def next():
        nonlocal idx
        # log(CAT).info(f"{idx}, {nodes[idx]}")
        idx += 1

    def has_next():
        return idx < len(nodes)

    def aux() -> Optional[DocNodeGroup]:
        nonlocal idx
        result = DocNodeGroup()

        def get():
            return nodes[idx]

        def at_skip() -> bool:
            return not get().is_named and get().type != "comment"

        def at_comment() -> bool:
            return get().type == "comment"

        while has_next() and at_skip():
            next()

        while has_next() and at_comment():
            result.comments.append(get())
            next()

        if has_next():
            result.node = get()
            next()

        while has_next() and at_skip():
            next()

        while has_next() and at_comment():
            if get().text.decode().startswith("///<"):
                result.comments.append(get())
                next()

            else:
                break

        if result.node or result.comments:
            return result

    while has_next():
        group = aux()
        if group:
            converted.append(group)

    return converted


@beartype
def get_subnode(node: tree_sitter.Node,
                name: Union[str, List[str]]) -> Optional[tree_sitter.Node]:
    match name:
        case str():
            return node.child_by_field_name(name)

        case list():
            for part in name:
                if node:
                    node = get_subnode(node, part)

            return node


@beartype
def fail_node(node: tree_sitter.Node, name: str) -> ValueError:
    result = ValueError(
        f"Unhandled type tree structure in {name}\n\n{render_rich(tree_repr(node), color=False)}"
    )

    setattr(result, "__rich_msg__", tree_repr(node))

    return result


@beartype
def convert_cxx_doc(doc: DocNodeGroup) -> Optional[DocCxx]:
    if doc.comments:
        return DocCxx(Text="\n".join(
            ["\n".join(strip_comment_prefixes(it.text.decode())) for it in doc.comments]))


@beartype
def convert_cxx_entry(doc: DocNodeGroup) -> List[DocCxxEntry]:
    node = doc.node
    result = []

    if not node:
        return []

    match node.type:
        case "declaration":
            return []

        case "preproc_ifdef":
            result = []
            for item in convert_cxx_groups(doc.node):
                conv = convert_cxx_entry(item)
                if conv:
                    result += conv

            return result

        case "enumerator":
            result = [
                DocCxxEnumField(
                    Name=get_subnode(doc.node, "name").text.decode(),
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )
            ]

        case "concept_definition":
            result = [
                DocCxxConcept(
                    Name=convert_cxx_type(get_subnode(doc.node, "name")),
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )
            ]

        case "enum_specifier":
            Enum = DocCxxEnum(
                Name=get_subnode(doc.node, "name") and
                convert_cxx_type(get_subnode(doc.node, "name")),
                Doc=convert_cxx_doc(doc),
                **getNodePoints(doc.node),
            )

            if not get_subnode(doc.node, "body"):
                # Tree-sitter grammar does not handle `enum class [[refl]] Kind {}` property at the moment
                return []

            for field in convert_cxx_groups(get_subnode(doc.node, "body")):
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
                result = [
                    DocCxxIdent(
                        Name=field_decl.text.decode(),
                        Type=convert_cxx_type(get_subnode(doc.node, "type")),
                        Doc=convert_cxx_doc(doc),
                        Value=get_subnode(doc.node, "default_value").text.decode()
                        if get_subnode(doc.node, "default_value") else None,
                        **getNodePoints(doc.node),
                    )
                ]

            else:
                raise fail_node(doc.node, "field declaration")

        case "optional_parameter_declaration":
            return [
                DocCxxIdent(
                    Type=convert_cxx_type(get_subnode(doc.node, "type")),
                    Name=get_subnode(doc.node, "declarator").text.decode(),
                    Value=get_subnode(doc.node, "default_value").text.decode(),
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )
            ]

        case "parameter_declaration":
            return [
                DocCxxIdent(
                    Type=convert_cxx_type(get_subnode(doc.node, "type")),
                    Name=get_subnode(doc.node, "declarator") and
                    get_subnode(doc.node, "declarator").text.decode(),
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )
            ]

        case "variadic_parameter_declaration":
            return [
                DocCxxIdent(
                    Type=convert_cxx_type(get_subnode(doc.node, "type")),
                    Name=get_subnode(doc.node, "declarator") and
                    get_subnode(doc.node, "declarator").text.decode(),
                    Doc=convert_cxx_doc(doc),
                    IsTemplateVariadic=True,
                    **getNodePoints(doc.node),
                )
            ]

        case "alias_declaration":
            result = [
                DocCxxTypedef(
                    Old=convert_cxx_type(get_subnode(doc.node, "name")),
                    New=convert_cxx_type(get_subnode(doc.node, "type")),
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )
            ]

        case "type_definition":
            result = [
                DocCxxTypedef(
                    Old=convert_cxx_type(get_subnode(doc.node, "type")),
                    New=convert_cxx_type(get_subnode(doc.node, "declarator")),
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
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
                        **getNodePoints(doc.node),
                    )

                    decl = get_subnode(decl, "declarator")

                else:
                    if get_subnode(node, "type"):
                        func = DocCxxFunction(
                            Kind=DocCxxFunctionKind.StandaloneFunction,
                            Name=get_subnode(decl, "declarator").text,
                            ReturnTy=convert_cxx_type(get_subnode(node, "type")),
                            Doc=convert_cxx_doc(doc),
                            **getNodePoints(doc.node),
                        )

                        while decl.type == "pointer_declarator":
                            func.ReturnTy.ptrCount += 1
                            decl = get_subnode(decl, "declarator")

                    else:
                        func = DocCxxFunction(
                            Name=get_subnode(decl, "declarator").text,
                            ReturnTy=None,
                            Kind=DocCxxFunctionKind.Constructor,
                            Doc=convert_cxx_doc(doc),
                            **getNodePoints(doc.node),
                        )

                for param in convert_cxx_groups(get_subnode(decl, "parameters")):
                    func.Arguments += convert_cxx_entry(param)

                result = [func]

        case "class_specifier" | "struct_specifier":
            body = get_subnode(node, "body")
            if body:
                record = DocCxxRecord(
                    Name=convert_cxx_type(get_subnode(node, "name")),
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )

                for group in convert_cxx_groups(body):
                    conv = convert_cxx_entry(group)
                    for it in conv:
                        if it:
                            record.Nested.append(it)

                result = [record]

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
            space = DocCxxNamespace(Name=convert_cxx_type(get_subnode(node, "name")))

            for it in convert_cxx_groups(get_subnode(node, "body")):
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
def convert_cxx_tree(tree: tree_sitter.Tree, RootPath: Path,
                     AbsPath: Path) -> DocCodeCxxFile:
    result: List[DocCxxEntry] = []
    for toplevel in convert_cxx_groups(tree.root_node):
        entry = convert_cxx_entry(toplevel)
        if entry:
            result += entry

    return DocCodeCxxFile(
        Content=result,
        RelPath=AbsPath.relative_to(RootPath),
        Lines=AbsPath.read_text().splitlines(),
    )


if __name__ == "__main__":
    root = get_haxorg_repo_root_path().joinpath("src")

    @beartype
    def aux_dir(dir: Path) -> DocDirectory:
        result = DocDirectory()
        for file in sorted(dir.glob("*")):
            log(CAT).info(file)
            if file.name == "base_lexer_gen.cpp":
                continue

            match file.suffix:
                case ".hpp":
                    result.CodeFiles.append(
                        convert_cxx_tree(
                            parse_cxx(file),
                            RootPath=root,
                            AbsPath=file.absolute(),
                        ))

                case "*.org":
                    result.TextFiles.append(DocTextFile(Text=file.read_text()))

                case _ if file.is_dir():
                    result.Subdirs.append(aux_dir(file))

        return result

    result = aux_dir(root)
    Path("/tmp/result.json").write_text(result.model_dump_json(indent=2))

    print("done")
