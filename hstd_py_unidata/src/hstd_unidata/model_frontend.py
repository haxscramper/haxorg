from __future__ import annotations

import enum
from dataclasses import dataclass, field

from beartype import beartype
from beartype.typing import Any, Callable, Dict, List, Optional, Tuple
from pydantic import BaseModel

from hstd_unidata.model_ir import (
    EnumValueDef,
    ExprNode,
    ExternalT,
    QName,
    RecordKind,
    Severity,
    SourceLoc,
)


class DslAttr(enum.StrEnum):
    """Attributes the declaration metaclass stores on user classes."""

    QNAME = "__dsl_qname__"
    MODEL = "__dsl_model__"
    KIND = "__dsl_kind__"
    ROOT = "__dsl_root__"
    BUILD = "__dsl_build__"


class Missing(enum.Enum):
    """Marker for a field declared without any explicit default."""

    NO_DEFAULT = "no_default"


NO_DEFAULT = Missing.NO_DEFAULT


class Int8:
    pass


class Int16:
    pass


class Int32:
    pass


class Int64:
    pass


class UInt8:
    pass


class UInt16:
    pass


class UInt32:
    pass


class UInt64:
    pass


class Float32:
    pass


class Float64:
    pass


@beartype
@dataclass(frozen=True)
class FixedArrayMeta:
    elem_type: Any
    size: int


@beartype
class FixedArrayFactory:
    """Annotation factory used as `FixedArray[Elem, Size]`."""

    def __getitem__(self, params: Tuple[Any, int]) -> FixedArrayMeta:
        elem_type, size = params
        return FixedArrayMeta(elem_type=elem_type, size=size)


FixedArray = FixedArrayFactory()


@beartype
class EnFieldAnnotation(BaseModel):
    """Documentation attached to an enum value through `Annotated`."""

    doc: str = ""

    def __hash__(self) -> int:
        return hash((self.doc,))


@beartype
class ExternalTypeLookup:
    """Produces references to types of an external package, used as `Model._T["a.b.Name"]`."""

    def __init__(self, package: str) -> None:
        self.package = package

    def __getitem__(self, type_path: str) -> ExternalT:
        qname: Optional[QName] = None
        for part in type_path.split("."):
            qname = QName(name=part, scope=qname)
        assert qname is not None
        return ExternalT(package=self.package, qname=qname)


@beartype
@dataclass
class MethodWrapper:
    """Method declaration with backend-specific data that the model never interprets."""

    func: Callable[..., Any]
    backend: Dict[str, Any]
    loc: SourceLoc


@beartype
@dataclass
class RawField:
    name: str
    annotation: Any
    doc: str
    default: Any
    check: Optional[ExprNode]
    message: Optional[str]
    loc: SourceLoc


@beartype
@dataclass
class RawVariant:
    cases: Tuple[Any, ...]
    field: str
    kind: str
    loc: SourceLoc


@beartype
@dataclass
class RawCheck:
    id: str
    cond: ExprNode
    message: ExprNode
    level: Severity
    loc: SourceLoc


@beartype
@dataclass
class RawMethod:
    name: str
    func: Callable[..., Any]
    backend: Dict[str, Any]
    is_static: bool
    loc: SourceLoc


@beartype
@dataclass
class RawRecord:
    """Class declaration captured by the metaclass before any name or type resolution."""

    kind: RecordKind
    qname: QName
    bases: Tuple[QName, ...]
    doc: str
    loc: SourceLoc
    module_globals: Dict[str, Any]
    fields: List[RawField] = field(default_factory=list)
    enum_values: List[EnumValueDef] = field(default_factory=list)
    variants: List[RawVariant] = field(default_factory=list)
    checks: List[RawCheck] = field(default_factory=list)
    methods: List[RawMethod] = field(default_factory=list)
    hash_func: Optional[Callable[..., Any]] = None
    eq_func: Optional[Callable[..., Any]] = None
    backend: Dict[str, Any] = field(default_factory=dict)
