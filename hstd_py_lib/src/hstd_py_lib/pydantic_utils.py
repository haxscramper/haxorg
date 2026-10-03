from __future__ import annotations

import base64
import importlib
import json
import math
import types
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path
from typing import Annotated, Any, Callable, Optional, TypeVar

import plumbum
from beartype import beartype
from beartype.typing import Literal, Union, get_args, get_origin
from pydantic import AfterValidator, BaseModel, TypeAdapter
from pydantic_core import PydanticSerializationError

from hstd_py_lib.script_logging import ExceptionContextNote

T = TypeVar("T")

# tag used to mark custom-serialized payloads so deserialization can dispatch
_TYPE_TAG = "__type__"
_PYDANTIC_TYPE_TAG = "__pydantic_type__"

# registry: type name -> (dump fn, load fn)


@dataclass(frozen=True)
class _RegisteredType:
    name: str
    json_type: Any
    adapter: TypeAdapter[Any]
    dump: Callable[[Any], Any]
    load: Callable[[Any], Any]


_DUMPERS: dict[type[Any], _RegisteredType] = {}
_LOADERS: dict[str, _RegisteredType] = {}


def register_type(
    tp: type[T],
    name: str,
    json_type: Any,
    dump: Callable[[T], J],
    load: Callable[[J], T],
) -> None:
    entry = _RegisteredType(
        name=name,
        json_type=json_type,
        adapter=TypeAdapter(json_type),
        dump=dump,
        load=load,
    )
    _DUMPERS[tp] = entry
    _LOADERS[name] = entry


register_type(
    Path,
    "Path",
    str,
    dump=lambda it: str(it),
    load=lambda it: Path(it),
)

register_type(
    datetime,
    "datetime",
    str,
    dump=lambda it: it.isoformat(),
    load=lambda it: datetime.fromisoformat(it),
)


@beartype
def _import_pydantic_model(path: str) -> type[BaseModel]:
    module_name, _, qualname = path.partition(":")
    if not module_name or not qualname:
        raise ValueError(f"invalid model path {path!r}")

    module = importlib.import_module(module_name)
    obj: Any = module
    for part in qualname.split("."):
        obj = getattr(obj, part)

    if not isinstance(obj, type) or not issubclass(obj, BaseModel):
        raise ValueError(f"path {path!r} does not resolve to a pydantic model type")

    return obj


@beartype
def _get_importable_model_path(model: BaseModel) -> str | None:
    cls = type(model)
    qualname = cls.__qualname__

    if "<locals>" in qualname:
        return None

    path = f"{cls.__module__}:{qualname}"
    try:
        resolved = _import_pydantic_model(path)
    except Exception:
        return None

    if resolved is cls:
        return path

    return None


@beartype
def _wrap(name: str, payload: Any, wrap_type_mapping: bool) -> dict[str, Any] | Any:
    if wrap_type_mapping:
        return {_TYPE_TAG: name, "data": payload}

    else:
        return payload


@beartype
def to_json_safe(value: Any, wrap_type_mapping: bool = True) -> Any:
    match value:
        case None | bool() | int() | str():
            return value

        case bytes():
            return _wrap(
                "bytes",
                base64.b64encode(value).decode("ascii"),
                wrap_type_mapping=wrap_type_mapping,
            )

        case float():
            if math.isnan(value) or math.isinf(value):
                return None
            return value

        case BaseModel():
            result: dict[str, Any] = {}
            for field_name in type(value).model_fields:
                result[field_name] = to_json_safe(
                    getattr(value, field_name),
                    wrap_type_mapping=wrap_type_mapping,
                )

            model_path = _get_importable_model_path(value)
            if model_path is not None:
                result[_PYDANTIC_TYPE_TAG] = model_path

            return result

        case dict():
            return {
                k: to_json_safe(
                    v,
                    wrap_type_mapping=wrap_type_mapping,
                )
                for k, v in value.items()
            }

        case list() | tuple() | set():
            return [
                to_json_safe(
                    v,
                    wrap_type_mapping=wrap_type_mapping,
                )
                for v in value
            ]

        case _:
            entry = _DUMPERS.get(type(value))
            if entry is None:
                for tp, candidate in _DUMPERS.items():
                    if isinstance(value, tp):
                        entry = candidate
                        break

            if entry is not None:
                payload = entry.adapter.validate_python(entry.dump(value))
                return _wrap(
                    entry.name,
                    to_json_safe(
                        payload,
                        wrap_type_mapping=wrap_type_mapping,
                    ),
                    wrap_type_mapping=wrap_type_mapping,
                )

            raise PydanticSerializationError(
                f"no serializer registered for type {type(value)!r}"
            )


def _needs_runtime_pydantic_resolution(annotation: Any) -> bool:
    if isinstance(annotation, type) and issubclass(annotation, BaseModel):
        return True

    origin = get_origin(annotation)

    if origin is Annotated:
        inner, *metadata = get_args(annotation)

        inner_origin = get_origin(inner)
        if inner_origin in (Union, types.UnionType):
            has_discriminator = any(
                getattr(meta, "discriminator", None) is not None for meta in metadata
            )
            if has_discriminator:
                return False

        return _needs_runtime_pydantic_resolution(inner)

    if origin in (Union, types.UnionType):
        return any(
            _needs_runtime_pydantic_resolution(arg) for arg in get_args(annotation)
        )

    if origin in (list, set, frozenset):
        args = get_args(annotation)
        return bool(args) and _needs_runtime_pydantic_resolution(args[0])

    if origin is tuple:
        args = get_args(annotation)
        if len(args) == 2 and args[1] is Ellipsis:
            return _needs_runtime_pydantic_resolution(args[0])
        return any(_needs_runtime_pydantic_resolution(arg) for arg in args)

    if origin is dict:
        args = get_args(annotation)
        if len(args) == 2:
            _, value_type = args
            return _needs_runtime_pydantic_resolution(value_type)
        return False

    return False


def _restore_json_safe(data: Any, *, resolve_pydantic_models: bool) -> Any:
    if isinstance(data, dict):
        tag = data.get(_TYPE_TAG)
        if tag is not None:
            payload = _restore_json_safe(
                data["data"], resolve_pydantic_models=resolve_pydantic_models
            )
            if tag == "bytes":
                return base64.b64decode(payload)

            entry = _LOADERS.get(tag)
            if entry is None:
                raise ValueError(f"no loader registered for tag {tag!r}")

            typed_payload = entry.adapter.validate_python(payload)
            return entry.load(typed_payload)

        pydantic_type = data.get(_PYDANTIC_TYPE_TAG)
        if isinstance(pydantic_type, str):
            model_payload = {
                k: _restore_json_safe(v, resolve_pydantic_models=resolve_pydantic_models)
                for k, v in data.items()
                if k != _PYDANTIC_TYPE_TAG
            }

            if resolve_pydantic_models:
                model_type = _import_pydantic_model(pydantic_type)
                return model_type.model_validate(model_payload)

            return model_payload

        return {
            k: _restore_json_safe(v, resolve_pydantic_models=resolve_pydantic_models)
            for k, v in data.items()
        }

    if isinstance(data, list):
        return [
            _restore_json_safe(v, resolve_pydantic_models=resolve_pydantic_models)
            for v in data
        ]

    return data


def from_json_safe(data: Any, target_type: type[T]) -> T:
    resolve_pydantic_models = _needs_runtime_pydantic_resolution(target_type)
    restored = _restore_json_safe(data, resolve_pydantic_models=resolve_pydantic_models)
    with ExceptionContextNote(
        lambda: (
            str(type(restored)) + "\n" + format_json_with_fjson(restored, max_width=200)
        )
    ):
        return TypeAdapter(target_type).validate_python(restored)


def model_to_json_data(model: BaseModel) -> Any:
    return to_json_safe(model)


def model_from_json_data(data: Any, model_type: type[T]) -> T:
    return from_json_safe(data, model_type)


@beartype
def try_parse_json(value: Any):
    match value:
        case bytes():
            try:
                value = value.decode("utf-8")
            except UnicodeDecodeError:
                return value

        case str():
            try:
                # to recursively unpack JSON dumps that contain
                # json strings as field values.
                return try_parse_json(json.loads(value))
            except json.JSONDecodeError:
                return value

        case dict():
            return {k: try_parse_json(v) for k, v in value.items()}

        case list():
            return [try_parse_json(v) for v in value]

        case _:
            return value


def first_by_field_value(obj: list[T], field: str, value: Any) -> Optional[T]:
    return glom.glom(
        obj,
        glom.Iter().first(
            lambda it: getattr(it, field) == value,  # type: ignore
            default=None,
        ),
    )


def _abs(p: Path) -> Path:
    return p.expanduser().resolve()


def _existing_file(p: Path) -> Path:
    p = _abs(p)
    if not p.is_file():
        raise ValueError(f"File does not exist: {p}")
    return p


def _existing_dir(p: Path) -> Path:
    p = _abs(p)
    if not p.is_dir():
        raise ValueError(f"Directory does not exist: {p}")
    return p


def _output_file(p: Path) -> Path:
    p = _abs(p)
    p.parent.mkdir(parents=True, exist_ok=True)
    return p


def _output_dir(p: Path) -> Path:
    p = _abs(p)
    p.mkdir(parents=True, exist_ok=True)
    return p


def _existing_path(p: Path) -> Path:
    p = _abs(p)
    if not p.exists():
        raise ValueError(f"Path does not exist: {p}")
    return p


ExistingPath = Annotated[Path, AfterValidator(_existing_path)]
ExistingFile = Annotated[Path, AfterValidator(_existing_file)]
ExistingDir = Annotated[Path, AfterValidator(_existing_dir)]
OutputFile = Annotated[Path, AfterValidator(_output_file)]
OutputDir = Annotated[Path, AfterValidator(_output_dir)]


@beartype
def format_json_with_fjson(
    value: Any,
    compact: bool = False,
    max_width: int | None = None,
    indent: int | None = None,
    tabs: bool = False,
    eol: Literal["lf", "crlf"] | None = None,  # type: ignore
    comments: Literal["error", "remove", "preserve"] | None = None,  # type: ignore
    trailing_commas: bool = False,
    preserve_blanks: bool = False,
    number_align: Literal["left", "right", "decimal", "normalize"]  # type: ignore
    | None = None,
    max_inline_complexity: int | None = None,
    max_table_complexity: int | None = None,
    simple_bracket_padding: bool = False,
    no_nested_bracket_padding: bool = False,
) -> str:
    args: list[str] = ["fjson"]

    if compact:
        args.append("--compact")
    if max_width is not None:
        args.extend(["--max-width", str(max_width)])
    if indent is not None:
        args.extend(["--indent", str(indent)])
    if tabs:
        args.append("--tabs")
    if eol is not None:
        args.extend(["--eol", eol])
    if comments is not None:
        args.extend(["--comments", comments])
    if trailing_commas:
        args.append("--trailing-commas")
    if preserve_blanks:
        args.append("--preserve-blanks")
    if number_align is not None:
        args.extend(["--number-align", number_align])
    if max_inline_complexity is not None:
        args.extend(["--max-inline-complexity", str(max_inline_complexity)])
    if max_table_complexity is not None:
        args.extend(["--max-table-complexity", str(max_table_complexity)])
    if simple_bracket_padding:
        args.append("--simple-bracket-padding")
    if no_nested_bracket_padding:
        args.append("--no-nested-bracket-padding")

    command = plumbum.local[args[0]]
    for arg in args[1:]:
        command = command[arg]

    payload = json.dumps(value, default=str)

    try:
        _, stdout, _ = (command << payload).run(retcode=0)
    except plumbum.ProcessExecutionError as error:
        raise RuntimeError(
            f"fjson failed with exit code {error.retcode}: {error.stderr.strip()}"
        ) from error

    return stdout
