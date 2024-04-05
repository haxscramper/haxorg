#!/usr/bin/env python

from tree_sitter import Language, Parser
import tree_sitter
from py_scriptutils.files import get_haxorg_repo_root_path
from pathlib import Path
from beartype import beartype
from beartype.typing import List, Dict, Optional, Any, Union, Iterator, Iterable, TypeVar
from py_scriptutils.script_logging import log
from dataclasses import dataclass, field, replace
from pydantic import BaseModel, Field
from rich.console import Console
from py_scriptutils.rich_utils import render_rich

T = TypeVar("T")


def dropnan(values: Iterable[Optional[T]]) -> Iterable[T]:
    return (it for it in values if it)


CAT = "docgen"

from py_codegen.gen_tu_cpp import (
    GenTuDoc,
    GenTuTypedef,
    GenTuTypeGroup,
    GenTuNamespace,
    GenTuStruct,
    GenTuEntry,
    GenTuEnum,
    GenTuIdent,
    QualType,
)

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


class DocCxxInclude(BaseModel, extra="forbid"):
    Target: str


class DocCxx(BaseModel, extra="forbid"):
    Text: str = ""


class DocCxxIdent(BaseModel, extra="forbid"):
    Name: str
    Type: QualType
    Value: Optional[str] = None
    Doc: Optional[DocCxx] = None


class DocCxxFunction(BaseModel, extra="forbid"):
    Name: str
    ReturnTy: QualType
    Arguments: List[DocCxx] = Field(default_factory=list)
    IsConst: bool = False
    IsStatic: bool = False
    IsVirtual: bool = False


class DocCxxTypedef(BaseModel, extra="forbid"):
    Old: QualType
    New: QualType


class DocCxxEnumField(BaseModel, extra="forbid"):
    Name: str
    Value: Optional[str] = None


class DocCxxEnum(BaseModel, extra="forbid"):
    Name: QualType
    Fields: List[DocCxxEnumField] = Field(default_factory=list)


class DocCxxRecord(BaseModel, extra="forbid"):
    Name: QualType
    Nested: List["DocCxxEntry"] = Field(default_factory=list)


class DocCxxConcept(BaseModel, extra="forbid"):
    Name: QualType


DocCxxEntry = Union[
    DocCxxRecord,
    DocCxxInclude,
    DocCxxFunction,
    DocCxxIdent,
    DocCxxTypedef,
    DocCxxEnum,
    DocCxxEnumField,
    "DocCxxNamespace",
]


class DocCxxNamespace(BaseModel, extra="forbid"):
    name: QualType
    nested: List[DocCxxEntry] = Field(default_factory=list)


class DocCxxFile(BaseModel, extra="forbid"):
    Content: List[DocCxxEntry] = Field(default_factory=list)


@beartype
def convert_cxx_type(node: tree_sitter.Node) -> QualType:
    match node.type:
        case "namespace_identifier":
            return QualType.ForName(name=node.text.decode())

        case "template_type":
            return QualType(
                name=get_subnode(node, "name").text.decode(),
                Parameters=[
                    convert_cxx_type(it)
                    for it in get_subnode(node, "arguments").children
                    if it.is_named
                ],
            )

        case "type_descriptor" | "type_identifier" | "primitive_type":
            return QualType(name=node.text.decode())

        case "qualified_identifier":
            return QualType(
                name=get_subnode(node, "name").text.decode(),
                Spaces=[convert_cxx_type(get_subnode(node, "scope"))],
            )

        case _:
            raise fail_node(node, "convert_cxx_type")


@beartype
def convert_cxx_groups(node: tree_sitter.Node) -> List[DocNodeGroup]:
    idx = 0
    nodes = node.children
    converted: List[DocNodeGroup] = []

    def aux() -> Optional[DocNodeGroup]:
        nonlocal idx
        value = nodes[idx]
        result = DocNodeGroup()
        while idx < len(nodes) and nodes[idx].type == "comment":
            result.comments.append(nodes[idx])
            idx += 1

        while idx < len(nodes) and not nodes[idx].is_named:
            idx += 1

        if idx < len(nodes):
            result.node = nodes[idx]
            idx += 1

        if result.node or result.comments:
            return result

    while idx < len(nodes):
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
            result = [DocCxxEnumField(Name=get_subnode(doc.node, "name").text.decode())]

        case "concept_definition":
            result = [DocCxxConcept(Name=convert_cxx_type(get_subnode(doc.node, "name")))]

        case "enum_specifier":
            Enum = DocCxxEnum(Name=convert_cxx_type(get_subnode(doc.node, "name")))
            for field in convert_cxx_groups(get_subnode(doc.node, "body")):
                Enum.Fields.append(convert_cxx_entry(field)[0])

            result = [Enum]

        case "field_declaration":
            record = get_subnode(doc.node, "type")
            if record and record.type in ["struct_specifier"]:
                return convert_cxx_entry(replace(doc, node=record))

            field_decl = get_subnode(doc.node, ["declarator", "declarator"])
            if not field_decl:
                field_decl = get_subnode(doc.node, "declarator")

            if field_decl:
                result = [
                    DocCxxIdent(Name=field_decl.text.decode(),
                                Type=convert_cxx_type(get_subnode(doc.node, "type")))
                ]

            else:
                raise fail_node(doc.node, "field declaration")

        case "optional_parameter_declaration":
            return [
                DocCxxIdent(
                    Type=convert_cxx_type(get_subnode(doc.node, "type")),
                    Name=get_subnode(doc.node, "declarator").text.decode(),
                    Value=get_subnode(doc.node, "default_value").text.decode(),
                )
            ]

        case "alias_declaration":
            result = [
                DocCxxTypedef(
                    Old=convert_cxx_type(get_subnode(doc.node, "name")),
                    New=convert_cxx_type(get_subnode(doc.node, "type")),
                )
            ]

        case "function_definition":
            decl = get_subnode(node, "declarator")

            if get_subnode(decl, "declarator"):
                func = DocCxxFunction(
                    Name=get_subnode(decl, "declarator").text,
                    ReturnTy=convert_cxx_type(get_subnode(node, "type")),
                )

                for param in get_subnode(decl, "parameters").children:
                    if param.is_named:
                        func.Arguments += convert_cxx_entry(DocNodeGroup(node=param))

                result = [func]

        case "class_specifier" | "struct_specifier":
            body = get_subnode(node, "body")
            if body:
                record = DocCxxRecord(Name=convert_cxx_type(get_subnode(node, "name")))

                for group in convert_cxx_groups(body):
                    conv = convert_cxx_entry(group)
                    for it in conv:
                        if it:
                            record.Nested.append(it)

                result = [record]

        case "template_declaration":
            content = node.named_child(1)
            declared = None
            match content.type:
                case "class_specifier" | "struct_specifier":
                    impl: DocCxxRecord = convert_cxx_entry(DocNodeGroup(node=content))
                    if impl:
                        declared = impl[0]

                case "function_definition":
                    impl: DocCxxFunction = convert_cxx_entry(DocNodeGroup(node=content))
                    if impl:
                        declared = impl[0]

                case "alias_declaration" | "declaration":
                    impl = convert_cxx_entry(replace(doc, node=content))

                    if impl:
                        declared = impl[0]

                case _:
                    raise fail_node(content, "template_declaration content")

            if declared:
                result = [declared]

        case "namespace_definition":
            result = [
                DocCxxNamespace(
                    name=convert_cxx_type(get_subnode(node, "name")),
                    nested=([
                        *dropnan(
                            convert_cxx_entry(it)
                            for it in convert_cxx_groups(get_subnode(node, "body")))
                    ]),
                )
            ]

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
            ]:
                raise fail_node(node, "convert cxx entry")

    return result


@beartype
def convert_cxx_tree(tree: tree_sitter.Tree) -> DocCxxFile:
    result: List[DocCxxEntry] = []
    for toplevel in convert_cxx_groups(tree.root_node):
        entry = convert_cxx_entry(toplevel)
        if entry:
            result += entry

    return DocCxxFile(Content=result)


if __name__ == "__main__":
    for glob in {"*.hpp"}:
        for file in sorted(get_haxorg_repo_root_path().joinpath("src").rglob(glob)):
            if file.name == "base_lexer_gen.cpp":
                continue

            log(CAT).info(file)
            converted = convert_cxx_tree(parse_cxx(file))

    print("done")
