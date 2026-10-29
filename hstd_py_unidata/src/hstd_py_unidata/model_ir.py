from __future__ import annotations

import enum
from typing import Annotated, Any

from beartype import beartype
from beartype.typing import Dict, List, Literal, Optional, Tuple, Union
from frozendict import deepfreeze, frozendict
from pydantic import BaseModel, ConfigDict, Field, PlainSerializer, ValidateAs

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

    def render(self) -> str:
        return f"{self.file}:{self.line}"


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
    """Human-readable type rendering, identical to the `type_text` relation in Soufflé."""
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
    VAR = "var"
    CONST_INT = "const_int"
    CONST_FLOAT = "const_float"
    CONST_STR = "const_str"
    CONST_BOOL = "const_bool"
    GET_FIELD = "get_field"
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
    str_val: Optional[str] = None
    int_val: Optional[int] = None
    float_val: Optional[float] = None
    bool_val: Optional[bool] = None
    type_val: Optional[TypeRef] = None
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
    level: Severity = Severity.ERROR
    context: CheckContext = CheckContext.RECORD
    field: Optional[str] = None
    cond: ExprNode
    message: ExprNode
    loc: SourceLoc


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
