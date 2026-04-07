from dataclasses import fields
import json
from pathlib import Path
import re
import typing

from beartype import beartype
from beartype.typing import Any
import betterproto
from py_codegen import codegen_ir
import py_codegen.proto_lib as pb
from py_scriptutils.script_logging import log
from pydantic import BaseModel

CAT = __name__

# Map of (parent_class, field_name) -> pydantic model class for override
_FIELD_SCHEMA_OVERRIDES: dict[tuple[type[Any], str], type[BaseModel]] = {
    (pb.Record, "reflection_params"): codegen_ir.GenTuReflParams,
    (pb.Function, "reflection_params"): codegen_ir.GenTuReflParams,
    (pb.Enum, "reflection_params"): codegen_ir.GenTuReflParams,
    (pb.RecordField, "reflection_params"): codegen_ir.GenTuReflParams,
    (pb.RecordMethod, "reflection_params"): codegen_ir.GenTuReflParams,
}


def proto_identifier_to_snake(name: str) -> str:
    name = re.sub(r"([A-Z]+)([A-Z][a-z])", r"\1_\2", name)
    name = re.sub(r"([a-z0-9])([A-Z])", r"\1_\2", name)
    return name.lower()


@beartype
def _rewrite_pydantic_refs(obj: Any, ref_map: dict[str, str]) -> None:
    if isinstance(obj, dict):
        if "$ref" in obj and isinstance(obj["$ref"], str):
            ref = obj["$ref"]
            if ref.startswith("#/$defs/"):
                ref_name = ref.split("/")[-1]
                if ref_name in ref_map:
                    obj["$ref"] = f"#/$defs/pydantic_{ref_name}"
        for v in obj.values():
            _rewrite_pydantic_refs(v, ref_map)
    elif isinstance(obj, list):
        for v in obj:
            _rewrite_pydantic_refs(v, ref_map)


@beartype
def betterproto_to_jsonschema(
    msg_class: type[Any],
    defs: dict[str, Any] | None = None,
) -> dict[str, Any]:
    if defs is None:
        defs = {}

    class_name = f"{msg_class.__name__}"

    if issubclass(msg_class, BaseModel):
        class_name = f"pydantic_{class_name}"

    if class_name in defs:
        return {"$ref": f"#/$defs/{class_name}"}

    defs[class_name] = {}
    properties: dict[str, Any] = {}

    if issubclass(msg_class, BaseModel):
        pydantic_schema: dict[str, Any] = msg_class.model_json_schema()
        prefix = f"pydantic_"
        pydantic_defs = pydantic_schema.pop("$defs", {})
        ref_map = {name: f"{prefix}{name}" for name in pydantic_defs}

        for def_name, def_schema in pydantic_defs.items():
            _rewrite_pydantic_refs(def_schema, ref_map)
            defs[ref_map[def_name]] = def_schema

        _rewrite_pydantic_refs(pydantic_schema, ref_map)
        properties = pydantic_schema["properties"]

    else:
        resolved_hints: dict[str, Any] = typing.get_type_hints(msg_class)

        for f in fields(msg_class):
            if f.name.startswith("_"):
                continue

            override_key = (msg_class, f.name)
            if override_key in _FIELD_SCHEMA_OVERRIDES:
                prop = _field_to_schema(_FIELD_SCHEMA_OVERRIDES[override_key], defs)
            else:
                resolved_type = resolved_hints.get(f.name, f.type)
                prop = _field_to_schema(resolved_type, defs)

            if prop is not None:
                properties[proto_identifier_to_snake(f.name)] = prop

    schema: dict[str, Any] = {"type": "object", "properties": properties}
    defs[class_name] = schema
    return {"$ref": f"#/$defs/{class_name}"}


@beartype
def _field_to_schema(tp: Any, defs: dict[str, Any]) -> dict[str, Any]:
    origin = typing.get_origin(tp)
    args = typing.get_args(tp)

    if origin is list:
        inner = args[0] if args else str
        return {"type": "array", "items": _type_to_schema(inner, defs)}

    if origin is typing.Optional or origin is typing.Union:
        non_none = [a for a in args if a is not type(None)]
        if non_none:
            return _type_to_schema(non_none[0], defs)

    return _type_to_schema(tp, defs)


@beartype
def _type_to_schema(tp: Any, defs: dict[str, Any]) -> dict[str, Any]:
    if tp is bool:
        return {"type": "boolean"}
    if tp is int:
        return {"type": "integer"}
    if tp is float:
        return {"type": "number"}
    if tp is str:
        return {"type": "string"}
    if tp is bytes:
        return {"type": "string", "contentEncoding": "base64"}

    if isinstance(tp, type) and issubclass(tp, betterproto.Enum):
        return {"type": "string", "enum": [e.name for e in tp]}

    if isinstance(tp, type) and issubclass(tp, (betterproto.Message, BaseModel)):
        return betterproto_to_jsonschema(tp, defs)

    return {}


@beartype
def _generate_schema(msg_class: type[Any]) -> dict[str, Any]:
    defs: dict[str, Any] = {}
    root = betterproto_to_jsonschema(msg_class, defs)
    return {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        **root,
        "$defs": defs,
    }


@beartype
def write_schema(msg_class: type[Any], output_path: Path) -> None:
    schema = _generate_schema(msg_class)
    output_path.write_text(json.dumps(schema, indent=2))
