#!/usr/bin/env python

from tree_sitter import Language, Parser
import tree_sitter
from py_scriptutils.files import get_haxorg_repo_root_path
from pathlib import Path
from beartype import beartype
from beartype.typing import List, Dict, Optional, Any, Union, Iterator, Iterable, TypeVar
from py_scriptutils.script_logging import log
from dataclasses import dataclass, field
from pydantic import BaseModel, Field

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
def parse_cxx(file: Path) -> tree_sitter.Tree:
    parser = Parser()
    parser.set_language(CPP_LANG)
    return parser.parse(file.read_bytes())


@beartype
def tree_repr(node: Union[tree_sitter.Tree, tree_sitter.Node]) -> str:

    def aux(node: tree_sitter.Node, indent: int, name: Optional[str] = None) -> str:
        result = "  " * indent
        if name:
            result += name
            result += ": "

        if node.is_named:
            result += node.type
            if 0 < len(node.children):
                for idx, subnode in enumerate(node.children):
                    if subnode.is_named:
                        result += "\n"
                        result += aux(subnode, indent + 1, node.field_name_for_child(idx))

            else:
                result += " \"" + node.text.decode() + "\""

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


class DocCxxFunction(BaseModel, extra="forbid"):
    Name: str 


class DocCxx(BaseModel, extra="forbid"):
    Text: str = ""


class DocCxxField(BaseModel, extra="forbid"):
    Name: str
    Type: QualType
    Doc: DocCxx = Field(default_factory=lambda: DocCxx())


class DocCxxMethod(BaseModel, extra="forbid"):
    Name: str


class DocCxxRecord(BaseModel, extra="forbid"):
    Name: QualType
    Fields: List[DocCxxField] = Field(default_factory=list)
    Methods: List[DocCxxMethod] = Field(default_factory=list)


DocCxxEntry = Union[DocCxxRecord, DocCxxInclude, DocCxxFunction, DocCxxField, "DocCxxNamespace"]


class DocCxxNamespace(BaseModel, extra="forbid"):
    name: QualType
    nested: List[DocCxxEntry] = Field(default_factory=list)


class DocCxxFile(BaseModel, extra="forbid"):
    content: List[DocCxxEntry] = Field(default_factory=list)


@beartype
def convert_cxx_type(node: tree_sitter.Node) -> QualType:
    match node.type:
        case "namespace_identifier":
            return QualType.ForName(name=node.text.decode())

        case "template_type":
            return QualType(
                name=node.child_by_field_name("name").text.decode(),
                Parameters=[
                    convert_cxx_type(it)
                    for it in node.child_by_field_name("arguments").children
                    if it.is_named
                ],
            )
        
        case "type_descriptor" | "type_identifier":
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
def get_subnode(node: tree_sitter.Node, name: Union[str, List[str]]) -> tree_sitter.Node:
    match name:
        case str():
            return node.child_by_field_name(name)
        
        case list():
            for part in name:
                node = get_subnode(node, part)

            return node
        

@beartype
def fail_node(node: tree_sitter.Node, name: str) -> ValueError:
    return ValueError(f"Unhandled type tree structure in {name}\n\n{tree_repr(node)}")

@beartype
def convert_cxx_entry(doc: DocNodeGroup) -> Optional[DocCxxEntry]:
    node = doc.node
    result = None

    if not node:
        return None

    match node.type:
        case "field_declaration":
            result = DocCxxField(
                Name=get_subnode(doc.node, ["declarator", "declarator"]).text.decode(),
                Type=convert_cxx_type(get_subnode(doc.node, "type"))
            )

        case "function_definition":
            decl = node.child_by_field_name("declarator")

            if decl.child_by_field_name("declarator"):
                func = DocCxxFunction(name=decl.child_by_field_name("declarator").text,)
                result = func

        case "class_specifier" | "struct_specifier":
            body = node.child_by_field_name("body")
            if body:
                result = DocCxxRecord(
                    Name=convert_cxx_type(node.child_by_field_name("name")))

                for group in convert_cxx_groups(body):
                    conv = convert_cxx_entry(group)
                    match conv:
                        case DocCxxField():
                            result.Fields.append(conv)

                        case None:
                            pass

                        case _:
                            raise fail_node(body, "record declaration body element")

            else:
                return None

        case "template_declaration":
            content = node.named_child(1)
            match content.type:
                case "class_specifier" | "struct_specifier":
                    impl: DocCxxRecord = convert_cxx_entry(DocNodeGroup(node=content))
                    if not impl:
                        return None

                    result = impl

                case _:
                    raise fail_node(content, "template_declaration content")

        case "namespace_definition":
            result = DocCxxNamespace(
                name=convert_cxx_type(node.child_by_field_name("name")),
                nested=([
                    *dropnan(
                        convert_cxx_entry(it)
                        for it in convert_cxx_groups(node.child_by_field_name("body")))
                ]),
            )

        case "preproc_include" | "preproc_call" | "template_instantiation" | "preproc_def" | "{" | ";" | "}" | "ERROR":
            return None

    if not result:
        Path("/tmp/debug.txt").write_text(node.text.decode() + "\n\n\n" + tree_repr(node))
        raise RuntimeError()

    return result


@beartype
def convert_cxx_tree(tree: tree_sitter.Tree) -> List[DocCxxEntry]:
    result: List[DocCxxEntry] = []
    for toplevel in convert_cxx_groups(tree.root_node):
        entry = convert_cxx_entry(toplevel)
        if entry:
            result.append(entry)

    return result


for glob in {"*.hpp"}:
    for file in sorted(get_haxorg_repo_root_path().joinpath("src").rglob(glob)):
        if file.name == "base_lexer_gen.cpp":
            continue

        log(CAT).info(file)
        converted = convert_cxx_tree(parse_cxx(file))

print("done")
