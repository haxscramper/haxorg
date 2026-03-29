from beartype.typing import Any
import json
from pathlib import Path
from py_scriptutils.script_logging import log
from py_codegen import codegen_ir
import typing
from pydantic import BaseModel
import py_codegen.proto_lib.reflection_defs as pb
from dataclasses import fields
import betterproto

# Map of (parent_class, field_name) -> pydantic model class for override
_FIELD_SCHEMA_OVERRIDES: dict[tuple[type, str], type[BaseModel]] = {
    (pb.Record, "reflection_params"): codegen_ir.GenTuReflParams,
    (pb.Function, "reflection_params"): codegen_ir.GenTuReflParams,
    (pb.Enum, "reflection_params"): codegen_ir.GenTuReflParams,
    (pb.RecordField, "reflection_params"): codegen_ir.GenTuReflParams,
}


def betterproto_to_jsonschema(msg_class, defs=None):
    if defs is None:
        defs = {}

    class_name = msg_class.__name__
    if class_name in defs:
        return {"$ref": f"#/$defs/{class_name}"}

    defs[class_name] = {}
    properties = {}

    resolved_hints = typing.get_type_hints(msg_class)

    for f in fields(msg_class):
        if f.name.startswith("_"):
            continue

        override_key = (msg_class, f.name)
        if override_key in _FIELD_SCHEMA_OVERRIDES:
            prop = _pydantic_override_schema(_FIELD_SCHEMA_OVERRIDES[override_key], defs)
        else:
            resolved_type = resolved_hints.get(f.name, f.type)
            prop = _field_to_schema(resolved_type, defs)

        if prop is not None:
            properties[f.name] = prop

    schema = {"type": "object", "properties": properties}
    defs[class_name] = schema
    return {"$ref": f"#/$defs/{class_name}"}


def _rewrite_pydantic_refs(obj):
    if isinstance(obj, dict):
        if "$ref" in obj and obj["$ref"].startswith("#/$defs/"):
            ref_name = obj["$ref"].split("/")[-1]
            obj["$ref"] = f"#/$defs/{ref_name}"
        for v in obj.values():
            _rewrite_pydantic_refs(v)
    elif isinstance(obj, list):
        for v in obj:
            _rewrite_pydantic_refs(v)


def _pydantic_override_schema(pydantic_cls, defs):
    pydantic_schema = pydantic_cls.model_json_schema()
    if "$defs" in pydantic_schema:
        for def_name, def_schema in pydantic_schema.pop("$defs").items():
            defs[f"{def_name}"] = def_schema
    _rewrite_pydantic_refs(pydantic_schema)
    return pydantic_schema


def _field_to_schema(tp, defs):
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


def _type_to_schema(tp, defs):
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

    try:
        if isinstance(tp, type) and issubclass(tp, betterproto.Enum):
            return {"type": "string", "enum": [e.name for e in tp]}
    except TypeError:
        pass

    try:
        if isinstance(tp, type) and issubclass(tp, betterproto.Message):
            return betterproto_to_jsonschema(tp, defs)
    except TypeError:
        pass

    return {}


def _generate_schema(msg_class) -> dict:
    defs = {}
    root = betterproto_to_jsonschema(msg_class, defs)
    return {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        **root,
        "$defs": defs,
    }


def write_schema(msg_class, output_path: Path):
    schema = _generate_schema(msg_class)
    output_path.write_text(json.dumps(schema, indent=2))
