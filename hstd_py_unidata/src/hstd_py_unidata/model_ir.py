from __future__ import annotations

import ast
import enum
import subprocess
from pathlib import Path
from typing import Annotated, Any

from beartype import beartype
from beartype.typing import Dict, List, Literal, Optional, Tuple, Union
from frozendict import deepfreeze, frozendict
from hstd_py_lib.external_packages.rich_utils import IndentedTree
from pydantic import BaseModel, ConfigDict, Field, PlainSerializer, ValidateAs
from rich.text import Text
from rich.tree import Tree

FrozenBackend = Annotated[
    frozendict[str, Any],
    ValidateAs(dict[str, Any], deepfreeze),
    PlainSerializer(dict, return_type=dict[str, Any]),
]


class FrozenModel(BaseModel):
    """Immutable, structurally comparable and hashable IR node."""

    model_config = ConfigDict(frozen=True)


@beartype
class SourceLoc(FrozenModel):
    """Location of a declaration or expression in the user-written model code."""

    file: str
    line: int
    function: str

    def render(self, absolte: bool = False) -> str:
        if absolte:
            return f"{self.file}:{self.line}"

        else:
            return f"{Path(self.file).name}:{self.line}"


@beartype
class QName(FrozenModel):
    """Qualified declaration name, the scope chain mirrors the lexical nesting of classes."""

    name: str
    scope: Optional[QName] = None

    def parts(self) -> Tuple[str, ...]:
        prefix = self.scope.parts() if self.scope else ()
        return prefix + (self.name,)

    def to_id(self) -> str:
        return "::".join(self.parts())

    def nested(self, name: str) -> QName:
        return QName(name=name, scope=self)


class PrimKind(enum.StrEnum):
    """Closed set of built-in primitive types."""

    INT8 = "int8"
    INT16 = "int16"
    INT32 = "int32"
    INT64 = "int64"
    UINT8 = "uint8"
    UINT16 = "uint16"
    UINT32 = "uint32"
    UINT64 = "uint64"
    FLOAT32 = "float32"
    FLOAT64 = "float64"
    STRING = "string"
    BOOL = "bool"
    ANY = "any"
    NONE = "none"
    PATH = "path"


INTEGER_RANGES: Dict[PrimKind, Tuple[int, int]] = {
    PrimKind.INT8: (-(2**7), 2**7 - 1),
    PrimKind.INT16: (-(2**15), 2**15 - 1),
    PrimKind.INT32: (-(2**31), 2**31 - 1),
    PrimKind.INT64: (-(2**63), 2**63 - 1),
    PrimKind.UINT8: (0, 2**8 - 1),
    PrimKind.UINT16: (0, 2**16 - 1),
    PrimKind.UINT32: (0, 2**32 - 1),
    PrimKind.UINT64: (0, 2**64 - 1),
}

FLOAT_PRIMS: Tuple[PrimKind, ...] = (PrimKind.FLOAT32, PrimKind.FLOAT64)


@beartype
def is_integer_prim(prim: PrimKind) -> bool:
    return prim in INTEGER_RANGES


@beartype
def is_numeric_prim(prim: PrimKind) -> bool:
    return prim in INTEGER_RANGES or prim in FLOAT_PRIMS


@beartype
def numeric_join(left: PrimKind, right: PrimKind) -> PrimKind:
    """Result type of arithmetic: any float widens to float64, mixed integer widths widen to int64."""
    if left in FLOAT_PRIMS or right in FLOAT_PRIMS:
        return PrimKind.FLOAT64
    if left == right:
        return left
    return PrimKind.INT64


@beartype
class TypeAnnotation(FrozenModel):
    "Backend-specific annotations for the type usage"

    backend: FrozenBackend = Field(default_factory=frozendict)


class BaseType(FrozenModel):
    annotation: TypeAnnotation = Field(default_factory=lambda: TypeAnnotation())


@beartype
class PrimT(BaseType):
    kind: Literal["prim"] = "prim"  # noqa
    prim: PrimKind


@beartype
class ListT(BaseType):
    kind: Literal["list"] = "list"  # noqa
    elem: TypeRef


@beartype
class ArrayT(BaseType):
    kind: Literal["array"] = "array"  # noqa
    elem: TypeRef
    size: int


@beartype
class MapT(BaseType):
    kind: Literal["map"] = "map"  # noqa
    key: TypeRef
    value: TypeRef


@beartype
class OptT(BaseType):
    kind: Literal["optional"] = "optional"  # noqa
    elem: TypeRef


@beartype
class TupleT(BaseType):
    kind: Literal["tuple"] = "tuple"  # noqa
    elems: Tuple[TypeRef, ...]


@beartype
class NamedT(BaseType):
    """Reference to a record or enum declared in the model."""

    kind: Literal["named"] = "named"  # noqa
    qname: QName


@beartype
class ExternalT(BaseType):
    """Opaque type provided by another package, the model never inspects its content."""

    kind: Literal["external"] = "external"  # noqa
    package: str
    qname: QName


@beartype
class VariantT(BaseType):
    """Variant created by `__variant__` on the owner record and stored in the named field."""

    kind: Literal["variant"] = "variant"  # noqa
    owner: QName
    field: str


@beartype
class DynT(BaseType):
    """Any value reachable from a value of the root type, produced by recursive traversal."""

    kind: Literal["dyn"] = "dyn"  # noqa
    root: TypeRef


@beartype
class TypeParamT(BaseType):
    kind: Literal["param"] = "param"  # noqa
    name: str


@beartype
class UnresolvedT(BaseType):
    """Annotation text that is resolved against the lexical scope during model finalization."""

    kind: Literal["unresolved"] = "unresolved"  # noqa
    text: str


type TypeRef = Annotated[
    Union[
        PrimT,
        ListT,
        ArrayT,
        MapT,
        OptT,
        TupleT,
        NamedT,
        ExternalT,
        VariantT,
        DynT,
        TypeParamT,
        UnresolvedT,
    ],
    Field(discriminator="kind"),
]


@beartype
def type_text(t: TypeRef) -> str:
    """Human-readable type rendering, identical to the `type_text` relation in Souffle."""
    match t:
        case PrimT():
            return t.prim.value
        case ListT():
            return f"list<{type_text(t.elem)}>"
        case ArrayT():
            return f"array<{type_text(t.elem)}, {t.size}>"
        case MapT():
            return f"map<{type_text(t.key)}, {type_text(t.value)}>"
        case OptT():
            return f"optional<{type_text(t.elem)}>"
        case TupleT():
            return f"tuple<{', '.join(type_text(e) for e in t.elems)}>"
        case NamedT():
            return t.qname.to_id()
        case ExternalT():
            return f"@{t.package}:{t.qname.to_id()}"
        case VariantT():
            return f"variant<{t.owner.to_id()}.{t.field}>"
        case DynT():
            return f"dyn<{type_text(t.root)}>"
        case TypeParamT():
            return t.name
        case UnresolvedT():
            return f"unresolved<{t.text}>"
        case _:
            raise TypeError(f"Unhandled type reference {t!r}")


class OpId(enum.StrEnum):
    """Closed set of core expression operators."""

    THIS = "this"
    # Access to the bound variable, var name is stored in the
    # `str_val` of the expression.
    VAR = "var"
    CONST_INT = "const_int"
    CONST_FLOAT = "const_float"
    CONST_STR = "const_str"
    CONST_BOOL = "const_bool"
    GET_FIELD = "get_field"
    # unary/binary operators for the comparison expressions
    # or logical boolean operations, operand arguments are
    # stored in the `.args`
    EQ = "eq"
    NE = "ne"
    LT = "lt"
    LE = "le"
    ADD = "add"
    SUB = "sub"
    MUL = "mul"
    DIV = "div"
    AND = "and"
    OR = "or"
    NOT = "not"
    COND = "cond"
    LET = "let"
    ALL = "all"
    EXISTS = "exists"
    EXISTS_ONE = "exists_one"
    MAP = "map"
    FILTER = "filter"
    FILTER_MAP = "filter_map"
    TAKE_WHILE = "take_while"
    GROUP_BY = "group_by"
    FOLD = "fold"
    WALK = "walk"
    SUM = "sum"
    MIN = "min"
    MAX = "max"
    STR_SIZE = "str_size"
    STR_MATCHES = "str_matches"
    STR_FORMAT = "str_format"
    LIST_SIZE = "list_size"
    LIST_CONTAINS = "list_contains"
    LIST_AT = "list_at"
    LIST_SLICE = "list_slice"
    LIST_CONCAT = "list_concat"
    LIST_EMPTY = "list_empty"
    MAP_SIZE = "map_size"
    MAP_CONTAINS = "map_contains"
    MAP_GET = "map_get"
    MAP_INSERT = "map_insert"
    MAP_KEYS = "map_keys"
    MAP_VALUES = "map_values"
    MAP_EMPTY = "map_empty"
    OPT_HAS_VALUE = "opt_has_value"
    OPT_VALUE = "opt_value"
    CASE_IS = "case_is"
    CASE_WHICH = "case_which"
    ENUM_IS = "enum_is"
    NTH_GET = "nth_get"
    IS_DERIVED = "is_derived"
    TYPE_COND = "type_cond"
    TYPE_CASE = "type_case"
    PATH_OF = "path_of"
    TYPE_OF = "type_of"


@beartype
class ExprNode(FrozenModel):
    """Expression tree node, binder names are lexically scoped and resolved per occurrence."""

    op: OpId
    args: Tuple[ExprNode, ...] = ()
    binders: Tuple[str, ...] = ()
    "Binder variables added in the expression, e.g. `op_map(?, <binder-name>)`"
    str_val: Optional[str] = None
    int_val: Optional[int] = None
    float_val: Optional[float] = None
    bool_val: Optional[bool] = None
    type_val: Optional[TypeRef] = None
    "Instance of the type value, e.g. for `type_case` node"
    typed_as: Optional[TypeRef] = None
    "Inferred type of this expression occurrence."
    expr_id: Optional[int] = None
    "Expression ID used in the type checking"
    loc: SourceLoc


class Severity(enum.StrEnum):
    ERROR = "error"
    WARNING = "warning"


class CheckContext(enum.StrEnum):
    """Whether `This` refers to the whole record or to a single field value."""

    RECORD = "record"
    FIELD = "field"


class RecordKind(enum.StrEnum):
    CLASS = "class"
    CASE = "case"
    ENUM = "enum"


@beartype
class ExplicitDefault(FrozenModel):
    """User-provided default in the JSON value encoding; absence means the trivial default."""

    value: Any


@beartype
class FieldDef(FrozenModel):
    name: str
    type: TypeRef
    doc: str = ""
    default: Optional[ExplicitDefault] = None
    loc: SourceLoc
    checks: List[CheckDef] = Field(default_factory=list)


@beartype
class EnumValueDef(FrozenModel):
    name: str
    value: int
    doc: str = ""
    loc: SourceLoc


@beartype
class VariantCaseDef(FrozenModel):
    """Stable case tag, equal to the short name of the case record."""

    tag: str
    case: QName


@beartype
class VariantDef(FrozenModel):
    """Variant data field with the generated kind enum listing the case tags."""

    field: str
    kind_enum: QName
    cases: Tuple[VariantCaseDef, ...]
    loc: SourceLoc


@beartype
class MethodArgDef(FrozenModel):
    name: str
    type: TypeRef
    default: Optional[ExplicitDefault] = None
    is_vararg: bool = False
    is_kwarg: bool = False


@beartype
class MethodDef(FrozenModel):
    """Model-understood method signature; backend data is opaque and never checked."""

    name: str
    args: Tuple[MethodArgDef, ...] = ()
    return_type: TypeRef
    type_params: Tuple[str, ...] = ()
    is_static: bool = False
    is_constructor: bool = False
    backend: Dict[str, Any] = Field(default_factory=dict)
    doc: str = ""
    loc: SourceLoc


@beartype
class CheckDef(FrozenModel):
    """Validation check with a boolean condition and a string message evaluated only on failure."""

    id: str
    "Globally unique ID for the check"
    level: Severity = Severity.ERROR
    context: CheckContext = CheckContext.RECORD
    field: Optional[str] = None
    cond: ExprNode
    "Bool-valued expressiont to validate if the check holds or not"
    message: ExprNode
    "String-valued expression that will be used to generate an error message"
    loc: SourceLoc
    "Location where the check was originally defined in the DSL code"


@beartype
class EnumDef(FrozenModel):
    qname: QName
    kind: Literal[RecordKind.ENUM] = RecordKind.ENUM
    doc: str = ""
    enum_values: Tuple[EnumValueDef, ...] = ()
    backend: Dict[str, Any] = Field(default_factory=dict)
    loc: SourceLoc


@beartype
class RecordDef(FrozenModel):
    kind: Literal[RecordKind.CLASS, RecordKind.CASE]
    qname: QName
    doc: str = ""
    bases: Tuple[QName, ...] = ()
    fields: Tuple[FieldDef, ...] = ()
    nested: Tuple[QName, ...] = ()
    variants: Tuple[VariantDef, ...] = ()
    methods: Tuple[MethodDef, ...] = ()
    checks: Tuple[CheckDef, ...] = ()
    backend: Dict[str, Any] = Field(default_factory=dict)
    hash_fields: Optional[Tuple[str, ...]] = None
    eq_fields: Optional[Tuple[str, ...]] = None
    loc: SourceLoc


class ModelDef(FrozenModel):
    """Finalized, backend-independent model with every name and type resolved."""

    package: str
    records: Tuple[RecordDef, ...]
    enums: Tuple[EnumDef, ...] = ()


@beartype
class FieldSeg(FrozenModel):
    kind: Literal["field"] = "field"  # noqa
    name: str


@beartype
class IndexSeg(FrozenModel):
    kind: Literal["index"] = "index"  # noqa
    index: int


@beartype
class KeySeg(FrozenModel):
    """Map entry segment, the entry position identifies the entry and the key text is for display."""

    kind: Literal["key"] = "key"  # noqa
    key: str
    entry: int


type PathSeg = Annotated[Union[FieldSeg, IndexSeg, KeySeg], Field(discriminator="kind")]


@beartype
class ItemPath(FrozenModel):
    """Occurrence path of a value inside a tree-shaped instance, used for diagnostics context."""

    segments: Tuple[PathSeg, ...] = ()

    def field(self, name: str) -> ItemPath:
        return ItemPath(segments=self.segments + (FieldSeg(name=name),))

    def index(self, index: int) -> ItemPath:
        return ItemPath(segments=self.segments + (IndexSeg(index=index),))

    def key(self, key: str, entry: int) -> ItemPath:
        return ItemPath(segments=self.segments + (KeySeg(key=key, entry=entry),))

    def is_prefix_of(self, other: ItemPath) -> bool:
        return other.segments[: len(self.segments)] == self.segments

    def render(self) -> str:
        parts = ["$"]
        for seg in self.segments:
            match seg:
                case FieldSeg():
                    parts.append(f".{seg.name}")
                case IndexSeg():
                    parts.append(f"[{seg.index}]")
                case KeySeg():
                    parts.append(f"[{seg.key}]")
        return "".join(parts)


for model_cls in (
    QName,
    ListT,
    ArrayT,
    MapT,
    OptT,
    TupleT,
    DynT,
    ExprNode,
    FieldDef,
    MethodArgDef,
    MethodDef,
    CheckDef,
    RecordDef,
    ModelDef,
    ItemPath,
):
    model_cls.model_rebuild()


@beartype
def expr_tree_repr(expr: ExprNode) -> IndentedTree:
    @beartype
    def label(node: ExprNode) -> Text:
        parts = []

        if node.expr_id is not None:
            parts.append(f"{node.op}:{node.expr_id!r}")

        else:
            parts.append(f"{node.op}")

        if node.typed_as is not None:
            parts.append(f"typed_as={type_text(node.typed_as)!r}")

        if node.type_val is not None:
            parts.append(f"type_val={type_text(node.type_val)!r}")

        for name, value in (
            ("str_val", node.str_val),
            ("int_val", node.int_val),
            ("float_val", node.float_val),
            ("bool_val", node.bool_val),
        ):
            if value is not None:
                parts.append(f"{name}={value!r}")

        if node.binders:
            parts.append(f"binders={node.binders!r}")

        return Text(" ".join(parts))

    @beartype
    def populate(node: ExprNode, tree: Tree) -> None:
        for nested in node.args:
            populate(nested, tree.add(label(nested)))

    tree = IndentedTree(label(expr))
    populate(expr, tree)
    return tree


@beartype
def add_tree_text(tree: Tree, text: str) -> Tree:
    return tree.add(Text(text))


@beartype
def add_tree_doc(tree: Tree, doc: str) -> None:
    if doc:
        add_tree_text(tree, f"doc={doc!r}")


@beartype
def add_check_tree(tree: Tree, check: CheckDef) -> None:
    parts = [
        f"check {check.id!r}",
        f"level={check.level}",
        f"context={check.context}",
    ]
    if check.field is not None:
        parts.append(f"field={check.field!r}")

    branch = add_tree_text(tree, " ".join(parts))
    add_tree_text(branch, "cond").add(expr_tree_repr(check.cond))
    add_tree_text(branch, "message").add(expr_tree_repr(check.message))


@beartype
def enum_tree_repr(value: EnumDef) -> IndentedTree:
    tree = IndentedTree(Text(f"{value.kind} {value.qname}"))
    add_tree_doc(tree, value.doc)

    for item in value.enum_values:
        branch = add_tree_text(
            tree,
            f"value {item.name} = {item.value}",
        )
        add_tree_doc(branch, item.doc)

    if value.backend:
        add_tree_text(tree, f"backend={value.backend!r}")

    return tree


@beartype
def record_tree_repr(value: RecordDef) -> IndentedTree:
    tree = IndentedTree(Text(f"{value.kind} {value.qname}"))
    add_tree_doc(tree, value.doc)

    for base in value.bases:
        add_tree_text(tree, f"base {base}")

    for nested in value.nested:
        add_tree_text(tree, f"nested {nested}")

    if value.hash_fields is not None:
        add_tree_text(tree, f"hash_fields={value.hash_fields!r}")

    if value.eq_fields is not None:
        add_tree_text(tree, f"eq_fields={value.eq_fields!r}")

    for field in value.fields:
        parts = [
            f"field {field.name}",
            f"type={type_text(field.type)!r}",
        ]
        if field.default is not None:
            parts.append(f"default={field.default.value!r}")

        branch = add_tree_text(tree, " ".join(parts))
        add_tree_doc(branch, field.doc)

        for check in field.checks:
            add_check_tree(branch, check)

    for variant in value.variants:
        branch = add_tree_text(
            tree,
            f"variant {variant.field} kind_enum={variant.kind_enum}",
        )
        for case in variant.cases:
            add_tree_text(branch, f"case {case.tag!r} record={case.case}")

    for method in value.methods:
        parts = [
            f"method {method.name}",
            f"return_type={type_text(method.return_type)!r}",
        ]
        if method.type_params:
            parts.append(f"type_params={method.type_params!r}")
        if method.is_static:
            parts.append("static")
        if method.is_constructor:
            parts.append("constructor")

        branch = add_tree_text(tree, " ".join(parts))
        add_tree_doc(branch, method.doc)

        for arg in method.args:
            arg_parts = [
                f"arg {arg.name}",
                f"type={type_text(arg.type)!r}",
            ]
            if arg.default is not None:
                arg_parts.append(f"default={arg.default.value!r}")
            if arg.is_vararg:
                arg_parts.append("vararg")
            if arg.is_kwarg:
                arg_parts.append("kwarg")
            add_tree_text(branch, " ".join(arg_parts))

        if method.backend:
            add_tree_text(branch, f"backend={method.backend!r}")

    for check in value.checks:
        add_check_tree(tree, check)

    if value.backend:
        add_tree_text(tree, f"backend={value.backend!r}")

    return tree


@beartype
def model_tree_repr(value: ModelDef) -> IndentedTree:
    tree = IndentedTree(Text(f"model {value.package!r}"))

    for enum_def in value.enums:
        tree.add(enum_tree_repr(enum_def))

    for record in value.records:
        tree.add(record_tree_repr(record))

    return tree


@beartype
def type_ast_repr(t: TypeRef) -> ast.expr:
    def generic(name: str, *params: ast.expr) -> ast.Subscript:
        return ast.Subscript(
            value=ast.Name(id=name, ctx=ast.Load()),
            slice=(
                params[0]
                if len(params) == 1
                else ast.Tuple(elts=list(params), ctx=ast.Load())
            ),
            ctx=ast.Load(),
        )

    def qname_to_ast(qname: QName) -> ast.expr:
        if qname.scope is None:
            return ast.Name(id=qname.name, ctx=ast.Load())

        return ast.Attribute(
            value=qname_to_ast(qname.scope),
            attr=qname.name,
            ctx=ast.Load(),
        )

    match t:
        case PrimT():
            return ast.parse(t.prim.value, mode="eval").body
        case ListT():
            return generic("list", type_ast_repr(t.elem))
        case ArrayT():
            return generic("array", type_ast_repr(t.elem), ast.Constant(value=t.size))
        case MapT():
            return generic("map", type_ast_repr(t.key), type_ast_repr(t.value))
        case OptT():
            return generic("optional", type_ast_repr(t.elem))
        case TupleT():
            return generic("tuple", *(type_ast_repr(elem) for elem in t.elems))
        case NamedT():
            return qname_to_ast(t.qname)
        case ExternalT():
            return generic(
                "ExternalT",
                ast.Constant(value=t.package),
                qname_to_ast(t.qname),
            )
        case VariantT():
            return generic(
                "variant",
                ast.Attribute(
                    value=qname_to_ast(t.owner),
                    attr=t.field,
                    ctx=ast.Load(),
                ),
            )
        case DynT():
            return generic("dyn", type_ast_repr(t.root))
        case TypeParamT():
            return ast.Name(id=t.name, ctx=ast.Load())
        case UnresolvedT():
            return generic("unresolved", ast.Constant(value=t.text))
        case _:
            raise TypeError(f"Unhandled type reference {t!r}")


@beartype
def expr_call_repr(expr: ExprNode, width: int = 90) -> str:
    def build(node: ExprNode) -> ast.expr:
        op = str(node.op)

        binary_ops = {
            "add": ast.Add,
            "sub": ast.Sub,
            "mul": ast.Mult,
            "div": ast.Div,
        }
        comparison_ops = {
            "eq": ast.Eq,
            "ne": ast.NotEq,
            "lt": ast.Lt,
            "le": ast.LtE,
        }
        boolean_ops = {
            "and": ast.And,
            "or": ast.Or,
        }

        if op == "not":
            (operand,) = node.args
            return ast.UnaryOp(op=ast.Not(), operand=build(operand))

        if op in binary_ops:
            left, right = node.args
            return ast.BinOp(
                left=build(left),
                op=binary_ops[op](),
                right=build(right),
            )

        if op in comparison_ops:
            left, right = node.args
            return ast.Compare(
                left=build(left),
                ops=[comparison_ops[op]()],
                comparators=[build(right)],
            )

        if op in boolean_ops:
            left, right = node.args
            return ast.BoolOp(
                op=boolean_ops[op](),
                values=[build(left), build(right)],
            )

        operation: ast.expr = ast.Name(id=op, ctx=ast.Load())

        if node.typed_as is not None:
            operation = ast.Subscript(
                value=operation,
                slice=type_ast_repr(node.typed_as),
                ctx=ast.Load(),
            )

        args: list[ast.expr] = []
        if node.binders:
            args.append(
                ast.Tuple(
                    elts=[ast.Constant(value=name) for name in node.binders],
                    ctx=ast.Load(),
                )
            )

        args.extend(build(child) for child in node.args)

        keywords: list[ast.keyword] = []
        if node.type_val is not None:
            keywords.append(
                ast.keyword(arg="type_val", value=type_ast_repr(node.type_val))
            )

        for name, value in (
            ("str_val", node.str_val),
            ("int_val", node.int_val),
            ("float_val", node.float_val),
            ("bool_val", node.bool_val),
        ):
            if value is not None:
                keywords.append(ast.keyword(arg=name, value=ast.Constant(value=value)))

        return ast.Call(func=operation, args=args, keywords=keywords)

    source = ast.unparse(build(expr)) + "\n"
    result = subprocess.run(
        [
            "ruff",
            "format",
            "--line-length",
            str(width),
            "--stdin-filename",
            "expression.py",
            "-",
        ],
        input=source,
        text=True,
        stdout=subprocess.PIPE,
        check=True,
    )
    return result.stdout.rstrip("\n")
