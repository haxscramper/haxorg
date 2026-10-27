from __future__ import annotations

import dataclasses
import json
import math
from dataclasses import dataclass, field

from beartype import beartype
from beartype.typing import Any, Callable, Dict, Iterator, List, Optional, Tuple, Union
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    FLOAT_PRIMS,
    INTEGER_RANGES,
    ArrayT,
    ExternalT,
    FieldSeg,
    IndexSeg,
    ItemPath,
    KeySeg,
    ListT,
    MapT,
    NamedT,
    OptT,
    PathSeg,
    PrimKind,
    PrimT,
    QName,
    TupleT,
    TypeRef,
    VariantT,
    is_numeric_prim,
    type_text,
)


@beartype
@dataclass(frozen=True)
class ScalarValue:
    prim: PrimKind
    value: Union[bool, int, float, str, None]
    path: Optional[ItemPath] = field(default=None, compare=False)


@beartype
@dataclass(frozen=True)
class RecordValue:
    """Record instance, the qname is the concrete type which can derive from the declared slot type."""

    qname: QName
    fields: Dict[str, Value]
    path: Optional[ItemPath] = field(default=None, compare=False)


@beartype
@dataclass(frozen=True)
class ListValue:
    items: Tuple[Value, ...]
    path: Optional[ItemPath] = field(default=None, compare=False)


@beartype
@dataclass(frozen=True)
class MapValue:
    """Map with unique keys under structural equality, entries keep insertion order."""

    entries: Tuple[Tuple[Value, Value], ...]
    path: Optional[ItemPath] = field(default=None, compare=False)


@beartype
@dataclass(frozen=True)
class OptValue:
    value: Optional[Value]
    path: Optional[ItemPath] = field(default=None, compare=False)


@beartype
@dataclass(frozen=True)
class TupleValue:
    items: Tuple[Value, ...]
    path: Optional[ItemPath] = field(default=None, compare=False)


@beartype
@dataclass(frozen=True)
class EnumValue:
    enum: QName
    name: str
    path: Optional[ItemPath] = field(default=None, compare=False)


@beartype
@dataclass(frozen=True)
class VariantValue:
    variant: VariantT
    tag: str
    case: RecordValue
    path: Optional[ItemPath] = field(default=None, compare=False)


@beartype
@dataclass(frozen=True)
class ExternalValue:
    """Opaque payload of an external type in its JSON encoding."""

    type: ExternalT
    payload: Any
    path: Optional[ItemPath] = field(default=None, compare=False)


@beartype
@dataclass(frozen=True)
class AnyValue:
    """Payload of a field declared with the `any` type, stored without interpretation."""

    payload: Any
    path: Optional[ItemPath] = field(default=None, compare=False)


@beartype
@dataclass(frozen=True)
class PathValue:
    """Occurrence path produced by `path_of`, it is not storable in instance data."""

    target: ItemPath
    path: Optional[ItemPath] = field(default=None, compare=False)


type Value = Union[
    ScalarValue,
    RecordValue,
    ListValue,
    MapValue,
    OptValue,
    TupleValue,
    EnumValue,
    VariantValue,
    ExternalValue,
    AnyValue,
    PathValue,
]


@beartype
class ValueDecodeError(Exception):
    """Instance data does not match the declared model type at the given path."""

    def __init__(self, path: ItemPath, message: str) -> None:
        super().__init__(f"{path.render()}: {message}")
        self.path = path
        self.message = message


@beartype
@dataclass(frozen=True)
class Position:
    """Value occurrence inside a tree together with its declared type."""

    path: ItemPath
    type: TypeRef
    value: Value
    rebuild: Callable[[Value], Value]
    """Wraps a replacement for this position into the value stored at the path."""
    is_case_record: bool = False


@beartype
def identity(value: Value) -> Value:
    return value


@beartype
def key_text(value: Value) -> str:
    match value:
        case ScalarValue() if value.prim == PrimKind.STRING:
            return json.dumps(value.value)
        case _:
            return value_text(value)


@beartype
def value_text(value: Value) -> str:
    """Text rendering used by `%s` formatting and diagnostics."""
    match value:
        case ScalarValue():
            match value.value:
                case bool():
                    return "true" if value.value else "false"
                case None:
                    return "null"
                case _:
                    return str(value.value)
        case EnumValue():
            return value.name
        case ListValue() | TupleValue():
            return "[" + ", ".join(key_text(i) for i in value.items) + "]"
        case MapValue():
            return (
                "{"
                + ", ".join(f"{key_text(k)}: {key_text(v)}" for k, v in value.entries)
                + "}"
            )
        case OptValue():
            return "null" if value.value is None else value_text(value.value)
        case RecordValue():
            inner = ", ".join(f"{n}: {key_text(v)}" for n, v in value.fields.items())
            return f"{value.qname.to_id()}{{{inner}}}"
        case VariantValue():
            return f"{value.tag}({value_text(value.case)})"
        case ExternalValue():
            return json.dumps(value.payload, sort_keys=True, default=str)
        case AnyValue():
            return json.dumps(value.payload, sort_keys=True, default=str)
        case PathValue():
            return value.target.render()
        case _:
            raise TypeError(f"Unhandled value {value!r}")


@beartype
def concrete_type_text(value: Value) -> str:
    """Runtime type name used by `type_of`; containers report only their kind."""
    match value:
        case ScalarValue():
            return value.prim.value
        case RecordValue():
            return value.qname.to_id()
        case EnumValue():
            return value.enum.to_id()
        case ListValue():
            return "list"
        case MapValue():
            return "map"
        case OptValue():
            return "optional"
        case TupleValue():
            return "tuple"
        case VariantValue():
            return type_text(value.variant)
        case ExternalValue():
            return type_text(value.type)
        case AnyValue():
            return "any"
        case PathValue():
            return "path"
        case _:
            raise TypeError(f"Unhandled value {value!r}")


@beartype
def value_key(index: ModelIndex, value: Value) -> Any:
    """Hashable structural identity; records use their custom equality fields when declared."""
    match value:
        case ScalarValue():
            match value.value:
                case bool():
                    return ("bool", value.value)
                case int() | float():
                    return ("num", value.value)
                case str():
                    return ("str", value.value)
                case None:
                    return ("none",)
        case EnumValue():
            return ("enum", value.enum.to_id(), value.name)
        case RecordValue():
            names = index.key_fields(value.qname) or tuple(sorted(value.fields))
            return (
                "rec",
                value.qname.to_id(),
                tuple((n, value_key(index, value.fields[n])) for n in names),
            )
        case ListValue():
            return ("list", tuple(value_key(index, i) for i in value.items))
        case TupleValue():
            return ("tuple", tuple(value_key(index, i) for i in value.items))
        case MapValue():
            return (
                "map",
                frozenset(
                    (value_key(index, k), value_key(index, v)) for k, v in value.entries
                ),
            )
        case OptValue():
            return (
                "opt",
                None if value.value is None else value_key(index, value.value),
            )
        case VariantValue():
            return ("variant", value.tag, value_key(index, value.case))
        case ExternalValue():
            return (
                "ext",
                type_text(value.type),
                json.dumps(value.payload, sort_keys=True, default=str),
            )
        case AnyValue():
            return ("any", json.dumps(value.payload, sort_keys=True, default=str))
        case PathValue():
            return ("path", value.target.render())
    raise TypeError(f"Unhandled value {value!r}")


@beartype
def is_numeric_value(value: Value) -> bool:
    return isinstance(value, ScalarValue) and is_numeric_prim(value.prim)


@beartype
def values_equal(index: ModelIndex, left: Value, right: Value) -> bool:
    """Numeric values compare by value across widths, everything else structurally."""
    if is_numeric_value(left) and is_numeric_value(right):
        return left.value == right.value

    else:
        return value_key(index, left) == value_key(index, right)


@beartype
def make_map(index: ModelIndex, entries: List[Tuple[Value, Value]]) -> MapValue:
    """Builds a map where a later entry with an equal key overwrites the earlier one."""
    positions: Dict[Any, int] = {}
    result: List[Tuple[Value, Value]] = []
    for k, v in entries:
        kk = value_key(index, k)
        if kk in positions:
            result[positions[kk]] = (result[positions[kk]][0], v)
        else:
            positions[kk] = len(result)
            result.append((k, v))
    return MapValue(entries=tuple(result))


@beartype
def default_value(
    index: ModelIndex, t: TypeRef, stack: Tuple[QName, ...] = ()
) -> Value:
    """Trivial default: zero, empty string, false, empty collection, no value, first enum value or case."""
    match t:
        case PrimT():
            match t.prim:
                case p if p in INTEGER_RANGES:
                    return ScalarValue(prim=p, value=0)
                case p if p in FLOAT_PRIMS:
                    return ScalarValue(prim=p, value=0.0)
                case PrimKind.STRING:
                    return ScalarValue(prim=t.prim, value="")
                case PrimKind.BOOL:
                    return ScalarValue(prim=t.prim, value=False)
                case PrimKind.NONE:
                    return ScalarValue(prim=t.prim, value=None)
                case PrimKind.ANY:
                    return AnyValue(payload=None)
                case _:
                    raise TypeError(
                        f"Type '{t.prim.value}' has no default value because it cannot be stored in instance data"
                    )
        case ListT():
            return ListValue(items=())
        case ArrayT():
            return ListValue(
                items=tuple(default_value(index, t.elem, stack) for _ in range(t.size))
            )
        case MapT():
            return MapValue(entries=())
        case OptT():
            return OptValue(value=None)
        case TupleT():
            return TupleValue(
                items=tuple(default_value(index, e, stack) for e in t.elems)
            )
        case NamedT() if index.is_enum(t.qname):
            values = index.enum_values(t.qname)
            if len(values) == 0:
                raise TypeError(
                    f"Enum '{t.qname.to_id()}' has no values, so it has no default value"
                )
            return EnumValue(enum=t.qname, name=values[0].name)
        case NamedT():
            return record_default(index, t.qname, stack)
        case VariantT():
            first = index.variant(t).cases[0]
            return VariantValue(
                variant=t, tag=first.tag, case=record_default(index, first.case, stack)
            )
        case ExternalT():
            return ExternalValue(type=t, payload=None)
        case _:
            raise TypeError(
                f"Type '{type_text(t)}' cannot hold instance data, so it has no default value"
            )


@beartype
def record_default(
    index: ModelIndex, qname: QName, stack: Tuple[QName, ...] = ()
) -> RecordValue:
    if qname in stack:
        chain = " -> ".join(q.to_id() for q in stack + (qname,))
        raise TypeError(
            f"Record '{qname.to_id()}' has no finite default value because it contains itself through non-collection fields: {chain}"
        )
    fields: Dict[str, Value] = {}
    for f in index.effective_fields(qname):
        if f.default is not None:
            fields[f.name] = decode_json(
                index, f.type, f.default.value, ItemPath().field(f.name)
            )
        else:
            fields[f.name] = default_value(index, f.type, stack + (qname,))
    return RecordValue(qname=qname, fields=fields)


@beartype
def decode_prim(prim: PrimKind, data: Any, path: ItemPath) -> Value:
    match prim:
        case p if p in INTEGER_RANGES:
            if isinstance(data, bool) or not isinstance(data, int):
                raise ValueDecodeError(
                    path,
                    f"expected an integer for type '{p.value}', got {type(data).__name__} {data!r}",
                )
            lo, hi = INTEGER_RANGES[p]
            if not (lo <= data <= hi):
                raise ValueDecodeError(
                    path,
                    f"integer {data} is out of range for type '{p.value}', expected {lo} <= value <= {hi}",
                )
            return ScalarValue(prim=p, value=data)
        case p if p in FLOAT_PRIMS:
            if isinstance(data, bool) or not isinstance(data, (int, float)):
                raise ValueDecodeError(
                    path,
                    f"expected a number for type '{p.value}', got {type(data).__name__} {data!r}",
                )
            return ScalarValue(prim=p, value=float(data))
        case PrimKind.STRING:
            if not isinstance(data, str):
                raise ValueDecodeError(
                    path, f"expected a string, got {type(data).__name__} {data!r}"
                )
            return ScalarValue(prim=prim, value=data)
        case PrimKind.BOOL:
            if not isinstance(data, bool):
                raise ValueDecodeError(
                    path, f"expected a boolean, got {type(data).__name__} {data!r}"
                )
            return ScalarValue(prim=prim, value=data)
        case PrimKind.NONE:
            if data is not None:
                raise ValueDecodeError(
                    path, f"expected null for type 'none', got {data!r}"
                )
            return ScalarValue(prim=prim, value=None)
        case PrimKind.ANY:
            return AnyValue(payload=data)
        case _:
            raise ValueDecodeError(
                path, f"type '{prim.value}' cannot be stored in instance data"
            )


@beartype
def decode_json(
    index: ModelIndex, t: TypeRef, data: Any, path: ItemPath = ItemPath()
) -> Value:
    """Decodes JSON-compatible data; polymorphic record slots use the `$type` key."""
    match t:
        case PrimT():
            return decode_prim(t.prim, data, path)
        case ListT() | ArrayT():
            if not isinstance(data, list):
                raise ValueDecodeError(
                    path,
                    f"expected a list for type '{type_text(t)}', got {type(data).__name__}",
                )
            if isinstance(t, ArrayT) and len(data) != t.size:
                raise ValueDecodeError(
                    path,
                    f"fixed array '{type_text(t)}' requires exactly {t.size} elements, got {len(data)}",
                )
            return ListValue(
                items=tuple(
                    decode_json(index, t.elem, d, path.index(i))
                    for i, d in enumerate(data)
                )
            )
        case MapT():
            return decode_map(index, t, data, path)
        case OptT():
            if data is None:
                return OptValue(value=None)
            return OptValue(value=decode_json(index, t.elem, data, path))
        case TupleT():
            if not isinstance(data, list) or len(data) != len(t.elems):
                raise ValueDecodeError(
                    path,
                    f"expected a list with {len(t.elems)} elements for '{type_text(t)}', got {data!r}",
                )
            return TupleValue(
                items=tuple(
                    decode_json(index, e, d, path.index(i))
                    for i, (e, d) in enumerate(zip(t.elems, data))
                )
            )
        case NamedT() if index.is_enum(t.qname):
            return decode_enum(index, t.qname, data, path)
        case NamedT():
            return decode_record(index, t.qname, data, path)
        case VariantT():
            return decode_variant(index, t, data, path)
        case ExternalT():
            return ExternalValue(type=t, payload=data)
        case _:
            raise ValueDecodeError(
                path, f"type '{type_text(t)}' cannot hold instance data"
            )


@beartype
def decode_map(index: ModelIndex, t: MapT, data: Any, path: ItemPath) -> MapValue:
    pairs: List[Tuple[Any, Any]]
    if t.key == PrimT(prim=PrimKind.STRING) and isinstance(data, dict):
        pairs = list(data.items())
    elif isinstance(data, list) and all(
        isinstance(p, list) and len(p) == 2 for p in data
    ):
        pairs = [(p[0], p[1]) for p in data]
    else:
        raise ValueDecodeError(
            path,
            f"expected a JSON object (string keys) or a list of [key, value] pairs for '{type_text(t)}', got {type(data).__name__}",
        )
    seen: Dict[Any, Any] = {}
    entries: List[Tuple[Value, Value]] = []
    for i, (kd, vd) in enumerate(pairs):
        key = decode_json(index, t.key, kd, path.key(json.dumps(kd, default=str), i))
        kk = value_key(index, key)
        if kk in seen:
            raise ValueDecodeError(
                path,
                f"duplicate map key {json.dumps(kd, default=str)}, first given as {json.dumps(seen[kk], default=str)}",
            )
        seen[kk] = kd
        entries.append(
            (key, decode_json(index, t.value, vd, path.key(key_text(key), i)))
        )
    return MapValue(entries=tuple(entries))


@beartype
def decode_enum(
    index: ModelIndex, qname: QName, data: Any, path: ItemPath
) -> EnumValue:
    values = index.enum_values(qname)
    for ev in values:
        if (isinstance(data, str) and data == ev.name) or (
            isinstance(data, int) and not isinstance(data, bool) and data == ev.value
        ):
            return EnumValue(enum=qname, name=ev.name)
    expected = ", ".join(f"{ev.name}={ev.value}" for ev in values)
    raise ValueDecodeError(
        path,
        f"{data!r} is not a value of enum '{qname.to_id()}', expected one of: {expected}",
    )


@beartype
def decode_record(
    index: ModelIndex, declared: QName, data: Any, path: ItemPath
) -> RecordValue:
    if not isinstance(data, dict):
        raise ValueDecodeError(
            path,
            f"expected a JSON object for record '{declared.to_id()}', got {type(data).__name__}",
        )
    concrete = declared
    if "$type" in data:
        type_name = data["$type"]
        allowed = [q.to_id() for q in index.descendants(declared)]
        if type_name not in allowed:
            raise ValueDecodeError(
                path,
                f"'$type' {type_name!r} is not allowed in a slot of type '{declared.to_id()}', expected one of: {', '.join(allowed)}",
            )
        concrete = index.by_id[type_name]
    fields = index.effective_fields(concrete)
    names = {f.name for f in fields}
    unknown = [k for k in data if k != "$type" and k not in names]
    if unknown:
        raise ValueDecodeError(
            path,
            f"record '{concrete.to_id()}' has no field(s) {', '.join(map(repr, unknown))}, available fields: {', '.join(f.name for f in fields)}",
        )
    defaults = record_default(index, concrete)
    values: Dict[str, Value] = {}
    for f in fields:
        if f.name in data:
            values[f.name] = decode_json(
                index, f.type, data[f.name], path.field(f.name)
            )
        else:
            values[f.name] = defaults.fields[f.name]
    return RecordValue(qname=concrete, fields=values)


@beartype
def decode_variant(
    index: ModelIndex, t: VariantT, data: Any, path: ItemPath
) -> VariantValue:
    vdef = index.variant(t)
    tags = ", ".join(c.tag for c in vdef.cases)
    if not isinstance(data, dict) or "kind" not in data:
        raise ValueDecodeError(
            path,
            f'expected an object {{"kind": <tag>, "value": {{...}}}} for \'{type_text(t)}\' with tag one of: {tags}',
        )
    extra = [k for k in data if k not in ("kind", "value")]
    if extra:
        raise ValueDecodeError(
            path,
            f"variant object accepts only 'kind' and 'value' keys, got extra {', '.join(map(repr, extra))}",
        )
    for c in vdef.cases:
        if c.tag == data["kind"]:
            case = decode_record(index, c.case, data.get("value", {}), path)
            return VariantValue(variant=t, tag=c.tag, case=case)
    raise ValueDecodeError(
        path,
        f"{data['kind']!r} is not a case of '{type_text(t)}', expected one of: {tags}",
    )


@beartype
def encode_json(index: ModelIndex, t: TypeRef, value: Value) -> Any:
    """Inverse of `decode_json`, a `$type` key is written only when the concrete type differs from the slot."""
    match value:
        case ScalarValue():
            return value.value
        case AnyValue() | ExternalValue():
            return value.payload
        case EnumValue():
            return value.name
        case PathValue():
            return value.target.render()
        case ListValue():
            match t:
                case ListT() | ArrayT():
                    return [encode_json(index, t.elem, i) for i in value.items]
        case TupleValue():
            match t:
                case TupleT():
                    return [
                        encode_json(index, e, i) for e, i in zip(t.elems, value.items)
                    ]
        case MapValue():
            match t:
                case MapT() if t.key == PrimT(prim=PrimKind.STRING):
                    return {
                        k.value: encode_json(index, t.value, v)
                        for k, v in value.entries
                        if isinstance(k, ScalarValue)
                    }
                case MapT():
                    return [
                        [encode_json(index, t.key, k), encode_json(index, t.value, v)]
                        for k, v in value.entries
                    ]
        case OptValue():
            match t:
                case OptT():
                    return (
                        None
                        if value.value is None
                        else encode_json(index, t.elem, value.value)
                    )
        case RecordValue():
            result: Dict[str, Any] = {}
            if not (isinstance(t, NamedT) and t.qname == value.qname):
                result["$type"] = value.qname.to_id()
            for f in index.effective_fields(value.qname):
                result[f.name] = encode_json(index, f.type, value.fields[f.name])
            return result
        case VariantValue():
            case_value = encode_json(
                index,
                NamedT(qname=index.variant_case(value.variant, value.tag).case),
                value.case,
            )
            return {"kind": value.tag, "value": case_value}
    raise TypeError(
        f"Value {value_text(value)} does not match declared type '{type_text(t)}'"
    )


@beartype
def value_size(index: ModelIndex, value: Value) -> Tuple[int, int]:
    """Reduction order: node count first, then total scalar magnitude, string length and ordinals."""
    nodes = 0
    magnitude = 0
    pending: List[Value] = [value]
    while pending:
        cur = pending.pop()
        nodes += 1
        match cur:
            case ScalarValue():
                match cur.value:
                    case bool():
                        magnitude += int(cur.value)
                    case int():
                        magnitude += abs(cur.value)
                    case float():
                        magnitude += (
                            math.ceil(abs(cur.value))
                            if math.isfinite(cur.value)
                            else 2**64
                        )
                    case str():
                        magnitude += len(cur.value)
                    case None:
                        pass
            case EnumValue():
                names = [ev.name for ev in index.enum_values(cur.enum)]
                magnitude += names.index(cur.name)
            case RecordValue():
                pending.extend(cur.fields.values())
            case ListValue() | TupleValue():
                pending.extend(cur.items)
            case MapValue():
                for k, v in cur.entries:
                    pending.extend([k, v])
            case OptValue():
                if cur.value is not None:
                    pending.append(cur.value)
            case VariantValue():
                tags = [c.tag for c in index.variant(cur.variant).cases]
                magnitude += tags.index(cur.tag)
                pending.append(cur.case)
            case ExternalValue() | AnyValue():
                magnitude += (
                    0
                    if cur.payload is None
                    else len(json.dumps(cur.payload, default=str))
                )
            case PathValue():
                pass
    return (nodes, magnitude)


@beartype
def positions(
    index: ModelIndex, t: TypeRef, value: Value, path: ItemPath = ItemPath()
) -> Iterator[Position]:
    """Pre-order occurrences of the tree; optional and variant wrappers do not add path segments."""
    yield from positions_rec(index, t, value, path, identity, False)


@beartype
def positions_rec(
    index: ModelIndex,
    t: TypeRef,
    value: Value,
    path: ItemPath,
    rebuild: Callable[[Value], Value],
    is_case_record: bool,
) -> Iterator[Position]:
    yield Position(
        path=path, type=t, value=value, rebuild=rebuild, is_case_record=is_case_record
    )
    match value, t:
        case RecordValue(), _:
            for f in index.effective_fields(value.qname):
                if f.name not in value.fields:
                    raise ValueDecodeError(
                        path,
                        f"record '{value.qname.to_id()}' instance is missing field '{f.name}'",
                    )
                yield from positions_rec(
                    index,
                    f.type,
                    value.fields[f.name],
                    path.field(f.name),
                    identity,
                    False,
                )
        case ListValue(), ListT() | ArrayT():
            for i, item in enumerate(value.items):
                yield from positions_rec(
                    index, t.elem, item, path.index(i), identity, False
                )
        case TupleValue(), TupleT():
            for i, (e, item) in enumerate(zip(t.elems, value.items)):
                yield from positions_rec(index, e, item, path.index(i), identity, False)
        case MapValue(), MapT():
            for i, (k, v) in enumerate(value.entries):
                yield from positions_rec(
                    index, t.value, v, path.key(key_text(k), i), identity, False
                )
        case OptValue(), OptT() if value.value is not None:
            yield from positions_rec(
                index,
                t.elem,
                value.value,
                path,
                lambda v: rebuild(OptValue(value=v)),
                False,
            )
        case VariantValue(), VariantT():
            variant_value = value
            yield from positions_rec(
                index,
                NamedT(qname=index.variant_case(t, value.tag).case),
                value.case,
                path,
                lambda v: rebuild(dataclasses.replace(variant_value, case=v)),
                True,
            )
        case _:
            pass


@beartype
def replace_at(root: Value, path: ItemPath, new: Value) -> Value:
    """Immutable update of the outermost value stored at the path."""
    return replace_rec(root, path.segments, new, path)


@beartype
def replace_rec(
    cur: Value, segs: Tuple[PathSeg, ...], new: Value, full: ItemPath
) -> Value:
    if len(segs) == 0:
        return new
    seg = segs[0]
    match cur, seg:
        case OptValue(), _ if cur.value is not None:
            return OptValue(value=replace_rec(cur.value, segs, new, full))
        case VariantValue(), FieldSeg():
            case = replace_rec(cur.case, segs, new, full)
            assert isinstance(case, RecordValue)
            return dataclasses.replace(cur, case=case)
        case RecordValue(), FieldSeg() if seg.name in cur.fields:
            fields = dict(cur.fields)
            fields[seg.name] = replace_rec(cur.fields[seg.name], segs[1:], new, full)
            return dataclasses.replace(cur, fields=fields)
        case ListValue(), IndexSeg() if seg.index < len(cur.items):
            items = list(cur.items)
            items[seg.index] = replace_rec(items[seg.index], segs[1:], new, full)
            return dataclasses.replace(cur, items=tuple(items))
        case TupleValue(), IndexSeg() if seg.index < len(cur.items):
            items = list(cur.items)
            items[seg.index] = replace_rec(items[seg.index], segs[1:], new, full)
            return dataclasses.replace(cur, items=tuple(items))
        case MapValue(), KeySeg() if seg.entry < len(cur.entries):
            entries = list(cur.entries)
            k, v = entries[seg.entry]
            entries[seg.entry] = (k, replace_rec(v, segs[1:], new, full))
            return dataclasses.replace(cur, entries=tuple(entries))
    raise ValueError(
        f"Path {full.render()} does not exist in the value: segment {seg!r} cannot be applied to {concrete_type_text(cur)} value {value_text(cur)[:200]}"
    )


@beartype
def locate(value: Value, path: ItemPath = ItemPath()) -> Value:
    """Copy of the tree where every value carries its occurrence path."""
    match value:
        case RecordValue():
            return RecordValue(
                qname=value.qname,
                fields={n: locate(v, path.field(n)) for n, v in value.fields.items()},
                path=path,
            )
        case ListValue():
            return ListValue(
                items=tuple(
                    locate(v, path.index(i)) for i, v in enumerate(value.items)
                ),
                path=path,
            )
        case TupleValue():
            return TupleValue(
                items=tuple(
                    locate(v, path.index(i)) for i, v in enumerate(value.items)
                ),
                path=path,
            )
        case MapValue():
            return MapValue(
                entries=tuple(
                    (
                        locate(k, path.key(key_text(k), i)),
                        locate(v, path.key(key_text(k), i)),
                    )
                    for i, (k, v) in enumerate(value.entries)
                ),
                path=path,
            )
        case OptValue():
            return OptValue(
                value=None if value.value is None else locate(value.value, path),
                path=path,
            )
        case VariantValue():
            case = locate(value.case, path)
            assert isinstance(case, RecordValue)
            return VariantValue(
                variant=value.variant, tag=value.tag, case=case, path=path
            )
        case _:
            return dataclasses.replace(value, path=path)


@beartype
def walk_values(value: Value) -> List[Value]:
    """Recursive descent in pre-order; containers, optionals and variants are transparent."""
    result: List[Value] = []
    pending: List[Value] = [value]
    while pending:
        cur = pending.pop()
        match cur:
            case RecordValue():
                result.append(cur)
                pending.extend(reversed(list(cur.fields.values())))
            case ListValue() | TupleValue():
                pending.extend(reversed(cur.items))
            case MapValue():
                for k, v in reversed(cur.entries):
                    pending.extend([v, k])
            case OptValue():
                if cur.value is not None:
                    pending.append(cur.value)
            case VariantValue():
                pending.append(cur.case)
            case _:
                result.append(cur)
    return result
