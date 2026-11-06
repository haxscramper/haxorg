from __future__ import annotations

import enum
import json
import re
from dataclasses import dataclass, field
from pathlib import Path

from beartype import beartype
from beartype.typing import cast
from plumbum import local
from pydantic import TypeAdapter
from sqlalchemy import Text
from sqlalchemy.engine import Dialect
from sqlalchemy.types import TypeDecorator

from hstd_py_unidata.model_ir import (
    ArrayT,
    DynT,
    ExternalT,
    ListT,
    MapT,
    NamedT,
    OptT,
    PrimKind,
    PrimT,
    QName,
    TupleT,
    TypeParamT,
    TypeRef,
    UnresolvedT,
    VariantT,
)
from hstd_py_unidata.model_ops import TYPE_CLASS_CONSTRUCTORS, TypeClass

PRIM_CONSTRUCTORS: dict[PrimKind, str] = {
    PrimKind.INT8: "PInt8",
    PrimKind.INT16: "PInt16",
    PrimKind.INT32: "PInt32",
    PrimKind.INT64: "PInt64",
    PrimKind.UINT8: "PUInt8",
    PrimKind.UINT16: "PUInt16",
    PrimKind.UINT32: "PUInt32",
    PrimKind.UINT64: "PUInt64",
    PrimKind.FLOAT32: "PFloat32",
    PrimKind.FLOAT64: "PFloat64",
    PrimKind.STRING: "PString",
    PrimKind.BOOL: "PBool",
    PrimKind.ANY: "PAny",
    PrimKind.NONE: "PNone",
    PrimKind.PATH: "PPath",
}

CONSTRUCTOR_PRIMS = {value: key for key, value in PRIM_CONSTRUCTORS.items()}
CONSTRUCTOR_CLASSES = {value: key for key, value in TYPE_CLASS_CONSTRUCTORS.items()}

type DiagnosticDetail = str | TypeRef | TypeClass | None
type DatabaseValue = TypeRef | QName | PrimKind | TypeClass | str | None


@beartype
@dataclass(frozen=True)
class AdtValue:
    """Named-constructor representation accepted by the serde functors."""

    head: str
    fields: dict[str, AdtValue | str | int] = field(default_factory=dict)


ADT_ADAPTER = TypeAdapter(AdtValue)


class AdtRoot(enum.StrEnum):
    TYPE = "DbType"
    QNAME = "DbQName"
    PRIM = "DbPrim"
    CLASS = "DbClass"
    DIAGNOSTIC_DETAIL = "DbDiagnosticDetail"
    OPTIONAL_TYPE = "DbOptionalType"


@beartype
def adt(head: str, /, **fields: AdtValue | str | int) -> AdtValue:
    return AdtValue(head=head, fields=fields)


@beartype
def nested_value(value: AdtValue, name: str) -> AdtValue:
    result = value.fields[name]
    if not isinstance(result, AdtValue):
        raise TypeError(
            f"Constructor {value.head!r}, field {name!r}: expected a nested "
            f"ADT value, got {result!r}"
        )
    return result


@beartype
def text_value(value: AdtValue, name: str) -> str:
    result = value.fields[name]
    if not isinstance(result, str):
        raise TypeError(
            f"Constructor {value.head!r}, field {name!r}: expected a string, "
            f"got {result!r}"
        )
    return result


@beartype
def number_value(value: AdtValue, name: str) -> int:
    result = value.fields[name]
    if type(result) is not int:
        raise TypeError(
            f"Constructor {value.head!r}, field {name!r}: expected an integer, "
            f"got {result!r}"
        )
    return result


@beartype
def qname_to_adt(value: QName) -> AdtValue:
    scope = (
        adt("NoScope")
        if value.scope is None
        else adt("SomeScope", value=qname_to_adt(value.scope))
    )
    return adt("QNameValue", name=value.name, scope=scope)


@beartype
def qname_from_adt(value: AdtValue) -> QName:
    if value.head != "QNameValue":
        raise ValueError(
            f"Cannot reconstruct QName from constructor {value.head!r}; "
            "expected 'QNameValue'"
        )

    scope = nested_value(value, "scope")
    match scope.head:
        case "NoScope":
            enclosing = None
        case "SomeScope":
            enclosing = qname_from_adt(nested_value(scope, "value"))
        case _:
            raise ValueError(
                f"Cannot reconstruct scope of QName {value!r}: expected "
                f"'NoScope' or 'SomeScope', got {scope.head!r}"
            )

    return QName(name=text_value(value, "name"), scope=enclosing)


@beartype
def type_to_adt(value: TypeRef) -> AdtValue:
    match value:
        case PrimT():
            return adt("TPrim", prim=adt(PRIM_CONSTRUCTORS[value.prim]))
        case ListT():
            return adt("TList", elem=type_to_adt(value.elem))
        case ArrayT():
            return adt("TArray", elem=type_to_adt(value.elem), size=value.size)
        case MapT():
            return adt(
                "TMap",
                key=type_to_adt(value.key),
                value=type_to_adt(value.value),
            )
        case OptT():
            return adt("TOpt", elem=type_to_adt(value.elem))
        case TupleT():
            elems = adt("TNil")
            for element in reversed(value.elems):
                elems = adt("TCons", head=type_to_adt(element), tail=elems)
            return adt("TTuple", elems=elems)
        case NamedT():
            return adt("TNamed", qname=qname_to_adt(value.qname))
        case ExternalT():
            return adt(
                "TExternal",
                package=value.package,
                qname=qname_to_adt(value.qname),
            )
        case VariantT():
            return adt(
                "TVariant",
                owner=qname_to_adt(value.owner),
                field=value.field,
            )
        case DynT():
            return adt("TDyn", root=type_to_adt(value.root))
        case TypeParamT():
            return adt("TParam", name=value.name)
        case UnresolvedT():
            raise ValueError(
                f"Cannot encode unresolved type {value.text!r}: model types "
                "must be resolved before lowering to Soufflé"
            )
        case _:
            raise TypeError(f"Cannot encode unsupported type reference {value!r}")


@beartype
def type_from_adt(value: AdtValue) -> TypeRef:
    match value.head:
        case "TPrim":
            prim = nested_value(value, "prim")
            return PrimT(prim=CONSTRUCTOR_PRIMS[prim.head])
        case "TList":
            return ListT(elem=type_from_adt(nested_value(value, "elem")))
        case "TArray":
            return ArrayT(
                elem=type_from_adt(nested_value(value, "elem")),
                size=number_value(value, "size"),
            )
        case "TMap":
            return MapT(
                key=type_from_adt(nested_value(value, "key")),
                value=type_from_adt(nested_value(value, "value")),
            )
        case "TOpt":
            return OptT(elem=type_from_adt(nested_value(value, "elem")))
        case "TTuple":
            elements: list[TypeRef] = []
            remaining = nested_value(value, "elems")
            while remaining.head == "TCons":
                elements.append(type_from_adt(nested_value(remaining, "head")))
                remaining = nested_value(remaining, "tail")

            if remaining.head != "TNil":
                raise ValueError(
                    f"Cannot reconstruct tuple {value!r}: its element list "
                    f"terminates with {remaining.head!r}, expected 'TNil'"
                )

            return TupleT(elems=tuple(elements))
        case "TNamed":
            return NamedT(qname=qname_from_adt(nested_value(value, "qname")))
        case "TExternal":
            return ExternalT(
                package=text_value(value, "package"),
                qname=qname_from_adt(nested_value(value, "qname")),
            )
        case "TVariant":
            return VariantT(
                owner=qname_from_adt(nested_value(value, "owner")),
                field=text_value(value, "field"),
            )
        case "TDyn":
            return DynT(root=type_from_adt(nested_value(value, "root")))
        case "TParam":
            return TypeParamT(name=text_value(value, "name"))
        case _:
            raise ValueError(
                f"Cannot reconstruct TypeRef from constructor {value.head!r}: "
                "the constructor is not part of the model Type ADT"
            )


@beartype
def detail_to_adt(value: DiagnosticDetail) -> AdtValue:
    match value:
        case None:
            return adt("NoDetail")
        case TypeClass():
            return adt(
                "ClassDetail",
                value=adt(TYPE_CLASS_CONSTRUCTORS[value]),
            )
        case str():
            return adt("TextDetail", value=value)
        case _:
            return adt("TypeDetail", value=type_to_adt(value))


@beartype
def detail_from_adt(value: AdtValue) -> DiagnosticDetail:
    match value.head:
        case "NoDetail":
            return None
        case "TextDetail":
            return text_value(value, "value")
        case "TypeDetail":
            return type_from_adt(nested_value(value, "value"))
        case "ClassDetail":
            return CONSTRUCTOR_CLASSES[nested_value(value, "value").head]
        case _:
            raise ValueError(
                f"Cannot reconstruct diagnostic detail {value!r}: expected "
                "'NoDetail', 'TextDetail', 'TypeDetail', or 'ClassDetail'"
            )


@beartype
def encode_database_value(value: DatabaseValue, root: AdtRoot) -> AdtValue:
    match root:
        case AdtRoot.TYPE:
            payload = type_to_adt(cast(TypeRef, value))
        case AdtRoot.QNAME:
            payload = qname_to_adt(cast(QName, value))
        case AdtRoot.PRIM:
            payload = adt(PRIM_CONSTRUCTORS[cast(PrimKind, value)])
        case AdtRoot.CLASS:
            payload = adt(TYPE_CLASS_CONSTRUCTORS[cast(TypeClass, value)])
        case AdtRoot.DIAGNOSTIC_DETAIL:
            payload = detail_to_adt(cast(DiagnosticDetail, value))
        case AdtRoot.OPTIONAL_TYPE:
            payload = (
                adt("NoType")
                if value is None
                else adt("SomeType", value=type_to_adt(cast(TypeRef, value)))
            )
        case _:
            raise ValueError(f"Unsupported database ADT root {root!r}")

    return adt(root.value, value=payload)


@beartype
def decode_database_value(value: AdtValue, root: AdtRoot) -> DatabaseValue:
    if value.head != root.value:
        raise ValueError(
            f"Cannot decode database ADT {value.head!r} as {root.value!r}: "
            "the stored wrapper does not match the column adapter"
        )

    payload = nested_value(value, "value")
    match root:
        case AdtRoot.TYPE:
            return type_from_adt(payload)
        case AdtRoot.QNAME:
            return qname_from_adt(payload)
        case AdtRoot.PRIM:
            return CONSTRUCTOR_PRIMS[payload.head]
        case AdtRoot.CLASS:
            return CONSTRUCTOR_CLASSES[payload.head]
        case AdtRoot.DIAGNOSTIC_DETAIL:
            return detail_from_adt(payload)
        case AdtRoot.OPTIONAL_TYPE:
            match payload.head:
                case "NoType":
                    return None
                case "SomeType":
                    return type_from_adt(nested_value(payload, "value"))
                case _:
                    raise ValueError(
                        f"Cannot reconstruct optional type {payload!r}: "
                        "expected 'NoType' or 'SomeType'"
                    )
        case _:
            raise ValueError(f"Unsupported database ADT root {root!r}")


@beartype
class AdtSql[T](TypeDecorator[T]):
    """Translate typed Python values to the common DbValue JSON envelope."""

    impl = Text
    cache_ok = True
    should_evaluate_none = True

    def __init__(self, root: AdtRoot) -> None:
        super().__init__()
        self.root = root

    def process_bind_param(self, value: T, dialect: Dialect) -> str:
        wire = encode_database_value(cast(DatabaseValue, value), self.root)
        return ADT_ADAPTER.dump_json(wire).decode("utf-8")

    def process_result_value(self, value: str | None, dialect: Dialect) -> T:
        if value is None:
            raise ValueError(
                f"Cannot decode SQL NULL as {self.root.value}: ADT columns "
                "store explicit constructors rather than SQL NULL"
            )

        wire = ADT_ADAPTER.validate_json(value)
        return cast(T, decode_database_value(wire, self.root))


@beartype
def io_metadata_parameter(ast: str, parameter: str) -> str:
    match = re.search(rf'\b{re.escape(parameter)}="(?=\{{)', ast)
    if match is None:
        raise ValueError(
            f"Soufflé transformed AST contains no {parameter!r} I/O metadata; "
            "the repository entry point must declare SQLite inputs and outputs"
        )

    start = match.end()
    _, end = json.JSONDecoder().raw_decode(ast, start)
    return ast[start:end]


@beartype
def prepare_serde_schema(program: Path, arguments: list[str]) -> str:
    """Derive the functor schema from the repository program using a 32-bit domain."""

    ast = local["souffle"][
        *arguments,
        "--show=transformed-ast",
        str(program),
    ]()

    types = json.loads(io_metadata_parameter(ast, "types"))
    params = json.loads(io_metadata_parameter(ast, "params"))
    names: dict[str, list[str]] = {}

    for declaration in re.finditer(
        r"(?m)^\.type\s+[^\s=]+\s*=\s*([^\n]+)",
        ast,
    ):
        for branch in re.finditer(
            r"([\w?.]+)\s*\{([^{}]*)\}",
            declaration.group(1),
        ):
            attributes: list[str] = []
            for attribute in filter(
                None,
                (item.strip() for item in branch.group(2).split(",")),
            ):
                match = re.fullmatch(
                    r"([\w?]+)\s*:\s*([\w?.]+)",
                    attribute,
                )
                if match is None:
                    raise ValueError(
                        f"Cannot derive serde fields for constructor "
                        f"{branch.group(1)!r}: attribute {attribute!r} is not "
                        "a named field with a named type"
                    )
                attributes.append(match.group(1))
            names[branch.group(1)] = attributes

    for type_name, info in types["ADTs"].items():
        for branch in info["branches"]:
            constructor = branch["name"]
            if constructor not in names:
                raise ValueError(
                    f"Cannot derive serde schema for ADT {type_name!r}: "
                    f"constructor {constructor!r} has no field declaration "
                    "in the transformed AST"
                )

            branch["names"] = names[constructor]
            if len(branch["names"]) != len(branch["types"]):
                raise ValueError(
                    f"Cannot derive serde schema for {constructor!r}: "
                    f"declared fields {branch['names']!r} do not match "
                    f"runtime field types {branch['types']!r}"
                )

    for type_name, info in types["records"].items():
        record_name = type_name.split(":", 1)[1]
        info["names"] = params["records"][record_name]["params"]

    return json.dumps(
        {
            "format": 1,
            "domain_bits": 32,
            "ADTs": types["ADTs"],
            "records": types["records"],
        },
        ensure_ascii=False,
        sort_keys=True,
    )


__all__ = [
    "AdtRoot",
    "AdtSql",
    "DiagnosticDetail",
    "PRIM_CONSTRUCTORS",
    "prepare_serde_schema",
]
