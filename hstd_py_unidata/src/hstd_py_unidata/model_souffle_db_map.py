from __future__ import annotations

import enum
import json
import re
from dataclasses import dataclass, field
from pathlib import Path
from types import UnionType

from beartype import beartype
from beartype.typing import (
    Annotated,
    Any,
    Callable,
    Iterable,
    Literal,
    TypeAliasType,
    Union,
    cast,
    get_args,
    get_origin,
)
from plumbum import local
from pydantic import BaseModel, TypeAdapter
from sqlalchemy import Text
from sqlalchemy.engine import Dialect
from sqlalchemy.types import TypeDecorator


@beartype
@dataclass(frozen=True)
class AdtValue:
    """Named-constructor representation accepted by the serde functors."""

    head: str
    fields: dict[str, AdtValue | str | int] = field(default_factory=dict)


type WireValue = AdtValue | str | int

WIRE_ADAPTER = TypeAdapter(AdtValue)


@beartype
@dataclass(frozen=True)
class OptionalShape:
    """Represent an optional value using absent and present constructors."""

    absent: str
    present: str
    value_field: str = "value"


@beartype
@dataclass(frozen=True)
class SequenceShape:
    """Represent a variadic tuple using a recursive constructor list."""

    empty: str
    cons: str
    head_field: str = "head"
    tail_field: str = "tail"


@beartype
@dataclass(frozen=True)
class UnionVariant:
    """Associate a Python type with a union's wrapper constructor."""

    target: Any
    head: str
    value_field: str | None = "value"


@beartype
@dataclass(frozen=True)
class UnionShape:
    """Represent union alternatives using explicit wrapper constructors."""

    variants: tuple[UnionVariant, ...]


@beartype
@dataclass(frozen=True)
class CustomShape:
    """Override both conversion directions for a representation."""

    encode: Callable[[object], WireValue]
    decode: Callable[[WireValue], object]


type ValueShape = OptionalShape | SequenceShape | UnionShape | CustomShape


@beartype
def resolve_annotation(annotation: Any) -> Any:
    while True:
        match annotation:
            case TypeAliasType():
                annotation = annotation.__value__
            case _ if get_origin(annotation) is Annotated:
                annotation = get_args(annotation)[0]
            case _:
                return annotation


@beartype
def expect_adt(value: WireValue, context: str) -> AdtValue:
    if not isinstance(value, AdtValue):
        raise TypeError(
            f"Cannot decode {context}: expected a named ADT constructor, got {value!r}"
        )

    return value


@beartype
def expect_fields(value: AdtValue, expected: Iterable[str]) -> None:
    expected_names = set(expected)
    actual_names = set(value.fields)

    if actual_names != expected_names:
        raise ValueError(
            f"Cannot decode constructor {value.head!r}: "
            f"missing fields {sorted(expected_names - actual_names)!r}; "
            f"unexpected fields {sorted(actual_names - expected_names)!r}; "
            f"expected fields {sorted(expected_names)!r}"
        )


@beartype
@dataclass(frozen=True)
class ModelConstructor:
    """Associate a constructor with a model and explicitly omitted fields."""

    head: str
    model: type[BaseModel]
    omit: frozenset[str] = frozenset()

    def field_names(self) -> tuple[str, ...]:
        names: list[str] = []

        for name, info in self.model.model_fields.items():
            if name in self.omit:
                continue

            annotation = resolve_annotation(info.annotation)
            if (
                get_origin(annotation) is Literal
                and len(get_args(annotation)) == 1
                and not info.is_required()
                and info.default == get_args(annotation)[0]
            ):
                continue

            names.append(name)

        return tuple(names)


@beartype
@dataclass(frozen=True, eq=False)
class AdtRegistry:
    """Infer model conversions from constructor registrations and field annotations."""

    models: tuple[ModelConstructor, ...]
    enums: tuple[tuple[enum.Enum, str], ...]
    field_shapes: dict[tuple[type[BaseModel], str], ValueShape] = field(
        default_factory=dict
    )

    models_by_type: dict[type[BaseModel], ModelConstructor] = field(
        init=False,
        repr=False,
        default_factory=dict,
    )
    enum_heads: dict[str, enum.Enum] = field(
        init=False,
        repr=False,
        default_factory=dict,
    )
    enum_values: dict[type[enum.Enum], dict[enum.Enum, str]] = field(
        init=False,
        repr=False,
        default_factory=dict,
    )

    def __post_init__(self) -> None:
        heads: dict[str, str] = {}

        for constructor in self.models:
            if constructor.model in self.models_by_type:
                previous = self.models_by_type[constructor.model]
                raise ValueError(
                    f"Cannot register model {constructor.model.__name__!r} "
                    f"for constructor {constructor.head!r}: it is already "
                    f"registered for {previous.head!r}"
                )

            if constructor.head in heads:
                raise ValueError(
                    f"Cannot register constructor {constructor.head!r} "
                    f"for model {constructor.model.__name__!r}: "
                    f"that constructor already represents {heads[constructor.head]}"
                )

            unknown = constructor.omit - constructor.model.model_fields.keys()
            if unknown:
                raise ValueError(
                    f"Cannot register model {constructor.model.__name__!r}: "
                    f"omitted fields {sorted(unknown)!r} do not exist"
                )

            heads[constructor.head] = constructor.model.__name__
            self.models_by_type[constructor.model] = constructor

        for value, head in self.enums:
            if head in heads:
                raise ValueError(
                    f"Cannot register enum value {value!r} for constructor "
                    f"{head!r}: that constructor already represents {heads[head]}"
                )

            members = self.enum_values.setdefault(type(value), {})
            if value in members:
                raise ValueError(
                    f"Cannot register enum value {value!r} for constructor "
                    f"{head!r}: it is already registered for {members[value]!r}"
                )

            heads[head] = repr(value)
            self.enum_heads[head] = value
            members[value] = head

        for model, name in self.field_shapes:
            if model not in self.models_by_type:
                raise ValueError(
                    f"Cannot configure representation for "
                    f"{model.__name__}.{name}: the model has no ADT constructor"
                )

            constructor = self.models_by_type[model]
            if name not in constructor.field_names():
                raise ValueError(
                    f"Cannot configure representation for "
                    f"{model.__name__}.{name}: the field does not exist "
                    "or is omitted from its ADT constructor"
                )

    def matches(self, annotation: Any, value: object) -> bool:
        target = resolve_annotation(annotation)
        origin = get_origin(target)

        if origin in (Union, UnionType):
            return any(self.matches(item, value) for item in get_args(target))

        match target:
            case _ if target is type(None):
                return value is None
            case _ if target is str:
                return type(value) is str
            case _ if target is int:
                return type(value) is int
            case _ if origin is tuple:
                return isinstance(value, tuple)
            case _ if isinstance(target, type):
                return isinstance(value, target)
            case _:
                return False

    def can_decode(self, annotation: Any, value: WireValue) -> bool:
        target = resolve_annotation(annotation)
        origin = get_origin(target)

        if origin in (Union, UnionType):
            return any(self.can_decode(item, value) for item in get_args(target))

        match value:
            case AdtValue():
                if target in self.models_by_type:
                    return self.models_by_type[target].head == value.head

                member = self.enum_heads.get(value.head)
                return member is not None and type(member) is target

            case str():
                return target is str

            case int():
                return target is int and type(value) is int

            case _:
                return False

    def sequence_element(self, annotation: Any) -> Any:
        target = resolve_annotation(annotation)
        arguments = get_args(target)

        if (
            get_origin(target) is not tuple
            or len(arguments) != 2
            or arguments[1] is not Ellipsis
        ):
            raise TypeError(
                f"Cannot apply a linked sequence representation to "
                f"{annotation!r}: expected tuple[ElementType, ...]"
            )

        return arguments[0]

    def encode(
        self,
        annotation: Any,
        value: object,
        shape: ValueShape | None = None,
    ) -> WireValue:
        match shape:
            case CustomShape():
                return shape.encode(value)

            case OptionalShape():
                if value is None:
                    return AdtValue(shape.absent)

                return AdtValue(
                    shape.present,
                    {shape.value_field: self.encode(annotation, value)},
                )

            case SequenceShape():
                element = self.sequence_element(annotation)
                if not isinstance(value, tuple):
                    raise TypeError(
                        f"Cannot encode {value!r} as {annotation!r}: "
                        "the linked sequence representation requires a tuple"
                    )

                result = AdtValue(shape.empty)
                for item in reversed(value):
                    result = AdtValue(
                        shape.cons,
                        {
                            shape.head_field: self.encode(element, item),
                            shape.tail_field: result,
                        },
                    )

                return result

            case UnionShape():
                variants = [
                    variant
                    for variant in shape.variants
                    if self.matches(variant.target, value)
                ]

                if len(variants) != 1:
                    raise ValueError(
                        f"Cannot encode {value!r} as {annotation!r}: expected "
                        "exactly one matching union constructor, "
                        f"got {[variant.head for variant in variants]!r}"
                    )

                variant = variants[0]
                if variant.value_field is None:
                    return AdtValue(variant.head)

                return AdtValue(
                    variant.head,
                    {
                        variant.value_field: self.encode(
                            variant.target,
                            value,
                        )
                    },
                )

            case None:
                pass

        target = resolve_annotation(annotation)

        if get_origin(target) in (Union, UnionType):
            alternatives = [
                item for item in get_args(target) if self.matches(item, value)
            ]

            if len(alternatives) != 1:
                raise ValueError(
                    f"Cannot encode {value!r} as {annotation!r}: expected "
                    "exactly one matching Python union alternative, "
                    f"got {alternatives!r}"
                )

            return self.encode(alternatives[0], value)

        match value:
            case BaseModel():
                constructor = self.models_by_type.get(type(value))
                if constructor is None:
                    raise ValueError(
                        f"Cannot encode model {type(value).__name__!r} "
                        f"as {annotation!r}: no ADT constructor is registered"
                    )

                fields: dict[str, WireValue] = {}
                for name in constructor.field_names():
                    info = constructor.model.model_fields[name]
                    fields[name] = self.encode(
                        info.annotation,
                        getattr(value, name),
                        self.field_shapes.get((constructor.model, name)),
                    )

                return AdtValue(constructor.head, fields)

            case enum.Enum():
                members = self.enum_values.get(type(value), {})
                if value not in members:
                    raise ValueError(
                        f"Cannot encode enum value {value!r}: no ADT "
                        f"constructor is registered for that member"
                    )

                return AdtValue(members[value])

            case str():
                return value

            case int() if type(value) is int:
                return value

            case _:
                raise TypeError(
                    f"Cannot encode {value!r} as {annotation!r}: no ADT "
                    "constructor or representation is registered"
                )

    def decode(
        self,
        annotation: Any,
        value: WireValue,
        shape: ValueShape | None = None,
    ) -> object:
        match shape:
            case CustomShape():
                return shape.decode(value)

            case OptionalShape():
                wire = expect_adt(value, repr(annotation))

                match wire.head:
                    case head if head == shape.absent:
                        expect_fields(wire, ())
                        return None

                    case head if head == shape.present:
                        expect_fields(wire, (shape.value_field,))
                        return self.decode(
                            annotation,
                            wire.fields[shape.value_field],
                        )

                    case _:
                        raise ValueError(
                            f"Cannot decode constructor {wire.head!r} "
                            f"as {annotation!r}: expected "
                            f"{shape.absent!r} or {shape.present!r}"
                        )

            case SequenceShape():
                element = self.sequence_element(annotation)
                remaining = expect_adt(value, repr(annotation))
                elements: list[object] = []

                while remaining.head == shape.cons:
                    expect_fields(
                        remaining,
                        (shape.head_field, shape.tail_field),
                    )
                    elements.append(
                        self.decode(
                            element,
                            remaining.fields[shape.head_field],
                        )
                    )
                    remaining = expect_adt(
                        remaining.fields[shape.tail_field],
                        f"tail of constructor {shape.cons!r}",
                    )

                if remaining.head != shape.empty:
                    raise ValueError(
                        f"Cannot decode linked sequence as {annotation!r}: "
                        f"its tail uses constructor {remaining.head!r}, "
                        f"expected {shape.cons!r} or {shape.empty!r}"
                    )

                expect_fields(remaining, ())
                return tuple(elements)

            case UnionShape():
                wire = expect_adt(value, repr(annotation))
                variants = [
                    variant for variant in shape.variants if variant.head == wire.head
                ]

                if len(variants) != 1:
                    raise ValueError(
                        f"Cannot decode constructor {wire.head!r} "
                        f"as {annotation!r}: expected exactly one registration "
                        f"among {[item.head for item in shape.variants]!r}, "
                        f"got {len(variants)}"
                    )

                variant = variants[0]
                if variant.value_field is None:
                    expect_fields(wire, ())
                    return TypeAdapter(variant.target).validate_python(None)

                expect_fields(wire, (variant.value_field,))
                return self.decode(
                    variant.target,
                    wire.fields[variant.value_field],
                )

            case None:
                pass

        target = resolve_annotation(annotation)

        if get_origin(target) in (Union, UnionType):
            alternatives = [
                item for item in get_args(target) if self.can_decode(item, value)
            ]

            if len(alternatives) != 1:
                raise ValueError(
                    f"Cannot decode {value!r} as {annotation!r}: expected "
                    "exactly one matching union alternative, "
                    f"got {alternatives!r}"
                )

            return self.decode(alternatives[0], value)

        if target in self.models_by_type:
            constructor = self.models_by_type[target]
            wire = expect_adt(value, constructor.model.__name__)

            if wire.head != constructor.head:
                raise ValueError(
                    f"Cannot decode constructor {wire.head!r} "
                    f"as {constructor.model.__name__}: "
                    f"expected {constructor.head!r}"
                )

            names = constructor.field_names()
            expect_fields(wire, names)

            fields: dict[str, object] = {}
            for name in names:
                info = constructor.model.model_fields[name]
                fields[name] = self.decode(
                    info.annotation,
                    wire.fields[name],
                    self.field_shapes.get((constructor.model, name)),
                )

            return constructor.model.model_validate(fields, by_name=True)

        if isinstance(target, type) and issubclass(target, enum.Enum):
            wire = expect_adt(value, target.__name__)
            expect_fields(wire, ())

            member = self.enum_heads.get(wire.head)
            if member is None or type(member) is not target:
                expected = sorted(self.enum_values.get(target, {}).values())
                raise ValueError(
                    f"Cannot decode constructor {wire.head!r} "
                    f"as enum {target.__name__}: expected one of {expected!r}"
                )

            return member

        match value:
            case str() if target is str:
                return value

            case int() if target is int and type(value) is int:
                return value

            case _:
                raise TypeError(
                    f"Cannot decode {value!r} as {annotation!r}: no matching "
                    "ADT constructor or representation is registered"
                )


@beartype
@dataclass(frozen=True, eq=False)
class AdtCodec[T]:
    """Combine a Python type adapter with its ADT representation and envelope."""

    registry: AdtRegistry
    target: Any
    wrapper: str
    shape: ValueShape | None = None
    adapter: TypeAdapter[T] = field(init=False, repr=False)

    def __post_init__(self) -> None:
        object.__setattr__(
            self,
            "adapter",
            TypeAdapter[T](self.target),
        )

    def to_adt(self, value: T) -> AdtValue:
        validated = self.adapter.validate_python(value)
        return AdtValue(
            self.wrapper,
            {
                "value": self.registry.encode(
                    self.target,
                    validated,
                    self.shape,
                )
            },
        )

    def from_adt(self, value: AdtValue) -> T:
        if value.head != self.wrapper:
            raise ValueError(
                f"Cannot decode database constructor {value.head!r} "
                f"as {self.target!r}: expected wrapper {self.wrapper!r}"
            )

        expect_fields(value, ("value",))
        decoded = self.registry.decode(
            self.target,
            value.fields["value"],
            self.shape,
        )
        return self.adapter.validate_python(decoded)

    def dump_json(self, value: T) -> str:
        return WIRE_ADAPTER.dump_json(self.to_adt(value)).decode("utf-8")

    def validate_json(self, value: str) -> T:
        return self.from_adt(WIRE_ADAPTER.validate_json(value))


@beartype
class AdtSql[T](TypeDecorator[T]):
    """Store values using a column-specific ADT codec."""

    impl = Text
    cache_ok = True
    should_evaluate_none = True

    def __init__(self, codec: AdtCodec[T]) -> None:
        super().__init__()
        self.codec = codec

    def process_bind_param(self, value: T | None, dialect: Dialect) -> str:
        return self.codec.dump_json(cast(T, value))

    def process_result_value(self, value: str | None, dialect: Dialect) -> T:
        if value is None:
            raise ValueError(
                f"Cannot decode SQL NULL as {self.codec.target!r}: "
                f"wrapper {self.codec.wrapper!r} stores explicit ADT "
                "constructors rather than SQL NULL"
            )

        return self.codec.validate_json(value)


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
