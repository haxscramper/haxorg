#!/usr/bin/env python

from tree_sitter import Language, Parser
import tree_sitter
from py_scriptutils.files import get_haxorg_repo_root_path
from pathlib import Path
from beartype import beartype
from beartype.typing import List, Dict, Optional, Any, Union, Iterator, Iterable, TypeVar, Tuple, Type
from py_scriptutils.script_logging import log
from dataclasses import dataclass, field, replace
from pydantic import BaseModel, Field, SerializeAsAny
from rich.console import Console
from py_scriptutils.rich_utils import render_rich
from py_codegen.refl_read import strip_comment_prefixes
from enum import Enum
import itertools
import dominate.tags as tags
from dominate import document
import dominate.util as util
from py_scriptutils.toml_config_profiler import options_from_model, BaseModel, apply_options, get_cli_model
import rich_click as click
import py_repository.run_coverage as coverage
import more_itertools
import concurrent.futures
from pygments import lex
from pygments.lexers import CppLexer
from pygments.token import Token, _TokenType
import py_haxorg.pyhaxorg_wrap as org
from py_exporters.export_html import ExporterHtml

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
    QualTypeKind,
    ReferenceKind,
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
    NamePoint: Optional[Tuple[int, int]]
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

    @beartype
    def getNested(self, Target: Type[T]) -> List[T]:
        return list(filter(lambda it: isinstance(it, Target), self.Nested))


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


class DocCxxNamespace(DocCxxBase, extra="forbid"):
    Name: QualType
    Nested: SerializeAsAny[List[DocCxxEntry]] = Field(default_factory=list)


class DocCodeRunCall(BaseModel, extra="forbid"):
    Count: int
    CalledBy: str


class DocCodeCxxCoverage(BaseModel, extra="forbid"):
    Call: List[DocCodeRunCall] = Field(default_factory=list)


class DocCodeCxxLine(BaseModel, extra="forbid"):
    Text: str
    Coverage: Optional[DocCodeCxxCoverage] = None


class DocCodeCxxFile(BaseModel, extra="forbid"):
    Content: SerializeAsAny[List[DocCxxEntry]] = Field(default_factory=list)
    Lines: List[DocCodeCxxLine] = Field(default_factory=list)
    RelPath: Path


class DocTextFile(BaseModel, extra="forbid"):
    RelPath: Path
    Text: str = ""


class DocDirectory(BaseModel, extra="forbid"):
    RelPath: Path
    CodeFiles: List[DocCodeCxxFile] = Field(default_factory=list)
    TextFiles: List[DocTextFile] = Field(default_factory=list)
    Subdirs: List["DocDirectory"] = Field(default_factory=list)


DocCxxRecord.model_rebuild()
DocCxxFunction.model_rebuild()
DocCxxNamespace.model_rebuild()
DocCodeCxxFile.model_rebuild()


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
            name_node = get_subnode(doc.node, "name")
            result = [
                DocCxxEnumField(
                    Name=name_node.text.decode(),
                    NamePoint=name_node.start_point,
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )
            ]

        case "concept_definition":
            name_node = get_subnode(doc.node, "name")
            result = [
                DocCxxConcept(
                    Name=convert_cxx_type(name_node),
                    NamePoint=name_node.start_point,
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )
            ]

        case "enum_specifier":
            name_node = get_subnode(doc.node, "name")
            Enum = DocCxxEnum(
                Name=name_node and convert_cxx_type(name_node),
                NamePoint=name_node and name_node.start_point,
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
                        NamePoint=field_decl.start_point,
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
            name_node = get_subnode(doc.node, "declarator")
            return [
                DocCxxIdent(
                    Type=convert_cxx_type(get_subnode(doc.node, "type")),
                    Name=name_node.text.decode(),
                    NamePoint=name_node.start_point,
                    Value=get_subnode(doc.node, "default_value").text.decode(),
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )
            ]

        case "parameter_declaration":
            name_node = get_subnode(doc.node, "declarator")
            return [
                DocCxxIdent(
                    Type=convert_cxx_type(get_subnode(doc.node, "type")),
                    NamePoint=name_node and name_node.start_point,
                    Name=name_node and name_node.text.decode(),
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )
            ]

        case "variadic_parameter_declaration":
            name_node = get_subnode(doc.node, "declarator")
            return [
                DocCxxIdent(
                    Type=convert_cxx_type(get_subnode(doc.node, "type")),
                    Name=name_node and name_node.text.decode(),
                    NamePoint=name_node and name_node.start_point,
                    Doc=convert_cxx_doc(doc),
                    IsTemplateVariadic=True,
                    **getNodePoints(doc.node),
                )
            ]

        case "alias_declaration":
            name_node = get_subnode(doc.node, "type")
            result = [
                DocCxxTypedef(
                    Old=convert_cxx_type(get_subnode(doc.node, "name")),
                    New=convert_cxx_type(name_node),
                    NamePoint=name_node.start_point,
                    Doc=convert_cxx_doc(doc),
                    **getNodePoints(doc.node),
                )
            ]

        case "type_definition":
            name_node = get_subnode(doc.node, "declarator")
            result = [
                DocCxxTypedef(
                    Old=convert_cxx_type(get_subnode(doc.node, "type")),
                    New=convert_cxx_type(name_node),
                    NamePoint=name_node.start_point,
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
                        NamePoint=get_subnode(decl, "type").start_point,
                        ReturnTy=convert_cxx_type(get_subnode(decl, "type")),
                        **getNodePoints(doc.node),
                    )

                    decl = get_subnode(decl, "declarator")

                else:
                    if get_subnode(node, "type"):
                        name_node = get_subnode(decl, "declarator")
                        func = DocCxxFunction(
                            Kind=DocCxxFunctionKind.StandaloneFunction,
                            NamePoint=name_node.start_point,
                            Name=name_node.text,
                            ReturnTy=convert_cxx_type(get_subnode(node, "type")),
                            Doc=convert_cxx_doc(doc),
                            **getNodePoints(doc.node),
                        )

                        while decl.type == "pointer_declarator":
                            func.ReturnTy.ptrCount += 1
                            decl = get_subnode(decl, "declarator")

                    else:
                        name_node = get_subnode(decl, "declarator")
                        func = DocCxxFunction(
                            Name=name_node.text,
                            NamePoint=name_node.start_point,
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
                name_node = get_subnode(node, "name")
                record = DocCxxRecord(
                    NamePoint=name_node.start_point,
                    Name=convert_cxx_type(name_node),
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
            name_node = get_subnode(node, "name")
            space = DocCxxNamespace(
                NamePoint=name_node.start_point,
                Name=convert_cxx_type(name_node),
                **getNodePoints(node),
            )

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
        Lines=[DocCodeCxxLine(Text=line) for line in AbsPath.read_text().splitlines()],
    )


def lerp_html_color(
    value: float,
    start: Tuple[float, float, float],
    end: Tuple[float, float, float],
) -> str:

    interpolated = tuple(
        int(255 * (r * (1 - value) + g * value))
        for r, g in zip([float(n) for n in start], [float(n) for n in end]))

    return f"#{interpolated[0]:02x}{interpolated[1]:02x}{interpolated[2]:02x}"


@beartype
def get_html_path(entry: Union[DocDirectory, DocCodeCxxFile, DocTextFile],
                  html_out_path: Path) -> Path:
    match entry:
        case DocDirectory():
            return html_out_path.joinpath(entry.RelPath)

        case DocCodeCxxFile() | DocTextFile():
            return html_out_path.joinpath(entry.RelPath).with_suffix(".html")


@beartype
def generate_tree_sidebar(directory: DocDirectory, html_out_path: Path) -> tags.ul:
    directory_list = tags.ul(cls="sidebar-directory")
    for subdir in directory.Subdirs:
        subdir_list = generate_tree_sidebar(subdir, html_out_path)
        directory_list.add(
            tags.li(
                tags.a(subdir.RelPath.name,
                       href=get_html_path(subdir, html_out_path=html_out_path)),
                subdir_list))

    for code_file in directory.CodeFiles:
        total_entries: int = 0
        documented_entries: int = 0

        def aux_docs(entry: DocCxxEntry):
            nonlocal total_entries
            nonlocal documented_entries

            total_entries += 1
            if entry.Doc and entry.Doc.Text:
                documented_entries += 1

            match entry:
                case DocCxxRecord():
                    for sub in entry.Nested:
                        aux_docs(sub)

                case DocCxxFunction():
                    for arg in entry.Arguments:
                        aux_docs(arg)

                case DocCxxEnum():
                    for field in entry.Fields:
                        aux_docs(field)

        for entry in code_file.Content:
            aux_docs(entry)

        item = tags.li(_class="sidebar-code")
        link = tags.a(href=get_html_path(code_file, html_out_path=html_out_path))
        link.add(util.text(code_file.RelPath.name))
        link.add(util.text(" "))
        doc_coverage = tags.b(style="color:{}".format(
            lerp_html_color(
                float(documented_entries) / float(total_entries),
                (1, 0, 0),
                (0, 1, 0),
            ) if total_entries != 0 else "yellow"))

        doc_coverage.add(util.text(f"{documented_entries}/{total_entries}"))
        link.add(doc_coverage)

        item.add(link)
        directory_list.add(item)

    for text_file in directory.TextFiles:
        directory_list.add(
            tags.li(
                tags.a("Text File",
                       href=get_html_path(text_file, html_out_path=html_out_path)),
                _class="sidebar-text",
            ))

    return directory_list


@beartype
def abbreviate_token_name(token: _TokenType) -> str:
    # Remove the base "Token" from the token type
    token_path = str(token).split('.')[1:]

    # Take the first letter of each part of the token type
    abbreviation = ''.join(part[0] for part in token_path).lower()

    return abbreviation


@beartype
def get_html_code_div(code_file: DocCodeCxxFile) -> tags.div:
    highilght_lexer = CppLexer()
    div = tags.div(_class="page-tab-content", id="page-code")

    decl_locations: Dict[(int, int), DocCxxEntry] = {}

    def aux_locations(entry: DocCxxEntry):
        decl_locations[(entry.NamePoint)] = entry
        match entry:
            case DocCxxRecord():
                for sub in entry.Nested:
                    aux_locations(sub)

    for entry in code_file.Content:
        aux_locations(entry)

    for idx, line in enumerate(code_file.Lines):
        hline = tags.p(_class="code-line")
        hline.add(tags.span(str(idx), _class="code-line-number", id=f"line-{idx}"))

        tokens = tags.span(_class="code-line-text", style="width:600px;")
        column = 0

        for token_type, token_text in lex(line.Text, highilght_lexer):
            maybe_entry = decl_locations.get((idx, column), None)
            if maybe_entry:
                token_html = tags.a(
                    href=f"#{get_docs_fragment(entry)}",
                    onclick="openPage('page-docs')",
                )

                token_html.add(token_text.strip("\n"))

                tokens.add(
                    tags.span(token_html,
                              _class=abbreviate_token_name(token_type) +
                              " code-backlink"))

            else:
                tokens.add(
                    tags.span(token_text.strip("\n"),
                              _class=abbreviate_token_name(token_type)))

            column += len(token_text)

        hline.add(tokens)

        if line.Coverage:
            cov = tags.span(_class="code-line-coverage", style="width:50px;")
            cov.add(util.text(str(sum([cover.Count for cover in line.Coverage.Call]))))
            hline.add(cov)

        div.add(hline)

    return div


@beartype
def get_entry_docs(entry: DocCxxEntry) -> List[Union[tags.html_tag, util.text]]:
    if entry.Doc and entry.Doc.Text:
        parsed = org.parseString(entry.Doc.Text)
        exp = ExporterHtml(get_break_tag=lambda _: util.text(" "))
        return list(itertools.chain(*[exp.exp.evalTop(it) for it in parsed]))

    else:
        return []


@beartype
def get_docs_fragment(entry: Union[DocCxxEntry, QualType]) -> str:
    match entry:
        case QualType():
            result = "_".join(["ns_" + get_docs_fragment(s) for s in entry.Spaces])
            result += "t_" + entry.name
            return result

        case DocCxxRecord():
            return get_docs_fragment(entry.Name)

        case DocCxxEnum():
            return get_docs_fragment(entry.Name)

        case DocCxxFunction():
            return entry.Name

        case DocCxxTypedef():
            return get_docs_fragment(entry.New)

        case DocCxxConcept():
            return get_docs_fragment(entry.Name)

        case DocCxxNamespace():
            return get_docs_fragment(entry.Name)

        case _:
            raise ValueError(f"TODO {type(entry)}")


@beartype
def get_name_link(entry: DocCxxEntry) -> tags.html_tag:
    match entry:
        case DocCxxRecord():
            name = entry.Name.name

        case _:
            name = entry.Name

    if not name:
        name = "<no-name>"

    link = tags.a(onclick=f"openPage('page-code')", href=f"#line-{entry.StartPoint[0]}")

    link.add(util.text(name))
    return link


@beartype
def get_html_docs_div(code_file: DocCodeCxxFile) -> tags.div:
    div = tags.div(_class="page-tab-content", id="page-docs")

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
            return tags.span(util.text(text))

    @beartype
    def aux_type(Type: QualType) -> tags.span:

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

        match Type:
            case QualType(Kind=QualTypeKind.RegularType):
                head = tags.span(util.text(Type.name), _class="docs-type-head")
                if Type.Parameters:
                    head.add(
                        util.text("<"),
                        csv_list((aux_type(P) for P in Type.Parameters), util.text(", ")),
                        util.text(">"),
                    )

                return head

            case QualType(Kind=QualTypeKind.TypeExpr):
                return tags.span(util.text(Type.expr))

            case _:
                raise ValueError(str(Type.Kind))

    @beartype
    def aux_ident(ident: DocCxxIdent) -> Tuple[tags.span, util.text, tags.span]:
        return (
            aux_type(ident.Type),
            util.text(ident.Name if ident.Name else ""),
            tags.span(util.text(ident.Value)) if ident.Value else tags.span(),
        )

    @beartype
    def get_doc_block(entry: DocCxxEntry) -> Optional[tags.div]:
        docs = get_entry_docs(entry)
        if docs:
            it = tags.div(_style="docs-entry-text")
            for item in docs:
                it.add(item)

            return it

    @beartype
    def aux_entry(
            entry: DocCxxEntry, context: List[Union[
                DocCxxNamespace,
                DocCxxEnum,
                DocCxxRecord,
            ]]) -> tags.div:
        res = tags.div(_class=f"docs-entry-{type(entry).__name__}")

        match entry:
            case DocCxxRecord():
                decl = tags.b(get_name_link(entry))
                res.add(decl)

                if entry.getNested(DocCxxIdent):
                    nested = tags.div(_class="docs-nested-record")
                    nested.add(tags.p(util.text(f"Fields")))
                    field_table = tags.table(_class="docs-record-fields")
                    for item in entry.getNested(DocCxxIdent):
                        row = tags.tr()
                        Type, Name, Default = aux_ident(item)
                        row.add(tags.td(Type))
                        row.add(tags.td(Name))
                        row.add(tags.td(Default))

                        docs = get_entry_docs(item)
                        if docs:
                            row.add(tags.td(docs))

                        else:
                            row.add(tags.td())

                        field_table.add(row)

                    nested.add(field_table)

                    res.add(nested)

                if entry.getNested(DocCxxEnum):
                    nested = tags.div(_class="docs-nested-record")
                    nested.add(tags.p(util.text(f"Nested enums")))
                    for item in entry.getNested(DocCxxEnum):
                        nested.add(aux_entry(item, context + [entry]))

                    res.add(nested)

                if entry.getNested(DocCxxFunction):
                    nested = tags.div(_class="docs-nested-record")
                    nested.add(tags.p(util.text(f"Methods")))
                    for item in entry.getNested(DocCxxFunction):
                        nested.add(aux_entry(item, context + [entry]))

                    res.add(nested)

                if entry.getNested(DocCxxRecord):
                    nested = tags.div(_class="docs-nested-record")
                    nested.add(tags.p(util.text(f"Nested records")))
                    for item in entry.getNested(DocCxxRecord):
                        nested.add(aux_entry(item, context + [entry]))

                    res.add(nested)

            case DocCxxIdent():
                if context and isinstance(context[-1], DocCxxRecord):
                    ident = tags.p()
                    ident.add(util.text(entry.Name))
                    ident.add(util.text(entry.Type.format()))
                    res.add(ident)

                else:
                    res.add(util.text("non-record ident"))

            case DocCxxFunction():
                if context and isinstance(context[-1], DocCxxFunction):
                    meth = tags.div()

                    res.add(meth)

                else:
                    func = tags.div()
                    sign = tags.table(_class="docs-func-signature")
                    ret = aux_type(entry.ReturnTy) if entry.ReturnTy else util.text("")

                    def ident_row(ident: DocCxxIdent) -> List[tags.td]:
                        return [tags.td(arg) for arg in aux_ident(ident)]

                    match entry.Arguments:
                        case []:
                            sign.add(
                                tags.tr(
                                    tags.td(ret),
                                    tags.td(get_name_link(entry)),
                                    tags.td(util.text("()")),
                                ))

                        case [one_arg]:
                            sign.add(
                                tags.tr(*[
                                    tags.td(ret),
                                    tags.td(get_name_link(entry)),
                                    tags.td(util.text("(")),
                                    *ident_row(one_arg),
                                    tags.td(util.text(")")),
                                ]))

                        case [first_arg, *middle_args, last_arg]:
                            sign.add(
                                tags.tr(
                                    tags.td(ret),
                                    tags.td(get_name_link(entry)),
                                    tags.td(util.text("(")),
                                    *ident_row(first_arg),
                                ),
                                *[
                                    tags.tr(
                                        tags.td(),
                                        tags.td(),
                                        tags.td(),
                                        *ident_row(it),
                                    ) for it in middle_args
                                ],
                                tags.tr(
                                    tags.td(),
                                    tags.td(),
                                    tags.td(),
                                    *ident_row(last_arg),
                                    tags.td(")"),
                                ),
                            )

                    func.add(sign)
                    res.add(func)

            case _:
                res.add(util.text(str(type(entry))))

        docs = get_doc_block(entry)
        if docs:
            res.add(docs)

        return res

    for item in code_file.Content:
        div.add(aux_entry(item, []))

    return div


@beartype
def get_html_page_tabs() -> tags.div:
    div = tags.div(_class="page-tab-row")
    for idx, name in enumerate([
            "docs",
            "code",
    ]):
        button_opts = dict(
            _class="page-tab-link",
            onclick=f"openPage('page-{name}')",
        )

        if idx == 0:
            button = tags.button(**button_opts, id="page-tab-link-default")

        else:
            button = tags.button(**button_opts)

        button.add(util.text(name))
        div.add(button)

    return div


@beartype
def generate_html_for_directory(directory: "DocDirectory", html_out_path: Path) -> None:
    sidebar = generate_tree_sidebar(directory, html_out_path=html_out_path)
    sidebar = tags.div(sidebar, _class="sidebar-directory-root")
    css_path = get_haxorg_repo_root_path().joinpath(
        "scripts/py_repository/py_repository/gen_documentation.css")

    js_path = get_haxorg_repo_root_path().joinpath(
        "scripts/py_repository/py_repository/gen_documentation.js")

    def aux(directory: DocDirectory, html_out_path: Path) -> None:
        for subdir in directory.Subdirs:
            aux(subdir, html_out_path)

        for code_file in directory.CodeFiles:
            path = get_html_path(code_file, html_out_path=html_out_path)
            doc = document(title=str(code_file.RelPath))
            doc.head.add(tags.link(rel="stylesheet", href=css_path))
            doc.head.add(tags.script(src=str(js_path)))

            container = tags.div(_class="container")
            container.add(tags.div(sidebar, _class="sidebar"))
            main = tags.div(_class="main")
            main.add(get_html_page_tabs())
            main.add(get_html_code_div(code_file))
            main.add(get_html_docs_div(code_file))
            container.add(main)
            doc.add(container)

            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(doc.render())

        for text_file in directory.TextFiles:
            path = get_html_path(text_file, html_out_path=html_out_path)
            doc = document(title=str(text_file.RelPath))
            doc.head.add(tags.link(rel="stylesheet", href=css_path))
            doc.add(tags.div(sidebar, _class="sidebar"))
            main = tags.div(_class="main")
            main.add(tags.pre(text_file.Text))

            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(doc.render())

    aux(directory, html_out_path)


class DocGenerationOptions(BaseModel, extra="forbid"):
    html_out_path: Path = Field(description="Root directory to output generated HTML to")
    json_out_path: Optional[Path] = Field(
        description="Path to write JSON data for the documentation model",
        default=None,
    )
    src_path: Path = Field(description="Root directory for input source code")
    tests_path: Optional[Path] = Field(
        description="Root directory for the tests",
        default=None,
    )


def cli_options(f):
    return apply_options(f, options_from_model(DocGenerationOptions))


@beartype
def get_coverage_data_single(
        file) -> Tuple[coverage.ProfdataCookie, coverage.TestRunCoverage]:
    cookie = coverage.ProfdataCookie.model_validate_json(file.read_text())
    model = coverage.get_profile_model(cookie)
    return (cookie, model)


@beartype
def get_full_coverage_data_all(
        files: Iterable[Path],
        max_workers=5) -> List[Tuple[
            coverage.ProfdataCookie,
            coverage.TestRunCoverage,
        ]]:

    results = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=max_workers) as executor:
        future_to_file = {
            executor.submit(get_coverage_data_single, file): file for file in files
        }

        for future in concurrent.futures.as_completed(future_to_file):
            result = future.result()
            results.append(result)

    return results


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@cli_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    conf = get_cli_model(ctx, DocGenerationOptions, kwargs=kwargs, config=config)

    rel_path_to_code_file: Dict[Path, DocCodeCxxFile] = {}

    @beartype
    def aux_dir(dir: Path) -> DocDirectory:
        result = DocDirectory(RelPath=dir.relative_to(conf.src_path))
        for file in sorted(dir.glob("*")):
            if file.name == "base_lexer_gen.cpp":
                continue

            match file.suffix:
                case ".hpp":
                    code_file = convert_cxx_tree(
                        parse_cxx(file),
                        RootPath=conf.src_path,
                        AbsPath=file.absolute(),
                    )

                    rel_path_to_code_file[code_file.RelPath] = code_file
                    result.CodeFiles.append(code_file)

                case "*.org":
                    result.TextFiles.append(DocTextFile(Text=file.read_text()))

                case _ if file.is_dir():
                    result.Subdirs.append(aux_dir(file))

        return result

    result = aux_dir(conf.src_path)

    if False:
        coverage_meta = get_full_coverage_data_all([
            file for file in coverage.get_profile_root().glob("*" +
                                                              coverage.COOKIE_SUFFIX)
            if "AllNodeCoverage" not in str(file)
        ])

        for cookie, model in coverage_meta:
            for entry in model.coverage.data:
                for file in entry.files:
                    try:
                        rel_covered = Path(file.filename).relative_to(conf.src_path)
                    except ValueError:
                        continue

                    doc_file = rel_path_to_code_file.get(rel_covered, None)
                    if doc_file:
                        for segment in file.segments:
                            segment_line_idx = segment.line - 1

                            if not doc_file.Lines[segment_line_idx].Coverage:
                                doc_file.Lines[
                                    segment_line_idx].Coverage = DocCodeCxxCoverage()

                            doc_file.Lines[segment_line_idx].Coverage.Call.append(
                                DocCodeRunCall(
                                    Count=segment.count,
                                    CalledBy=cookie.test_name,
                                ))

    if conf.json_out_path:
        conf.json_out_path.write_text(result.model_dump_json(indent=2))

    generate_html_for_directory(result, html_out_path=conf.html_out_path)


if __name__ == "__main__":
    cli()
