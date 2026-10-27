from beartype import beartype
from beartype.typing import List, Optional, Tuple
from hstd_py_unidata.model_ir import ExprNode, OpId, PrimKind
from hstd_py_unidata.model_ops import (
    INT64_T,
    Env,
    EvalHost,
    Operator,
    TypeClass,
    make_bool,
    make_int,
    type_arg_text,
)
from hstd_py_unidata.model_value import (
    ListValue,
    MapValue,
    Value,
    concrete_type_text,
    make_map,
    value_key,
    value_text,
)


@beartype
def _find_entry(
    host: EvalHost, mapping: MapValue, key: Value
) -> Optional[Tuple[Value, Value]]:
    kk = value_key(host.index, key)
    for k, v in mapping.entries:
        if value_key(host.index, k) == kk:
            return (k, v)
    return None


@beartype
def _expect_map(host: EvalHost, node: ExprNode, value: Value) -> MapValue:
    if isinstance(value, MapValue):
        return value
    host.fail(
        node,
        f"expected a map operand, got {concrete_type_text(value)} {value_text(value)}",
        value,
    )


class MapSizeOp(Operator):
    op_id = OpId.MAP_SIZE
    roles = ("map",)
    arg_classes = ((TypeClass.MAP,),)
    fixed_result = INT64_T

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Map.size()"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return make_int(
            host,
            node,
            PrimKind.INT64,
            len(_expect_map(host, node, host.eval(node.args[0], env)).entries),
        )


class MapContainsOp(Operator):
    op_id = OpId.MAP_CONTAINS
    roles = ("map", "key")
    arg_classes = ((TypeClass.MAP,), ())
    binary_operands = True

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Map.contains({args[1]})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        mapping = _expect_map(host, node, host.eval(node.args[0], env))
        return make_bool(
            _find_entry(host, mapping, host.eval(node.args[1], env)) is not None
        )


class MapGetOp(Operator):
    op_id = OpId.MAP_GET
    roles = ("map", "key")
    arg_classes = ((TypeClass.MAP,), ())
    binary_operands = True

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Map.get({args[1]})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        mapping = _expect_map(host, node, host.eval(node.args[0], env))
        key = host.eval(node.args[1], env)
        entry = _find_entry(host, mapping, key)
        if entry is None:
            present = ", ".join(value_text(k) for k, _ in mapping.entries[:10])
            host.fail(
                node,
                f"key {value_text(key)} is not present in the map, present keys: {present or '(none)'}",
                mapping,
            )
        return entry[1]


class MapInsertOp(Operator):
    op_id = OpId.MAP_INSERT
    roles = ("map", "key", "value")
    arg_classes = ((TypeClass.MAP,), (), ())
    binary_operands = True

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Map.insert({args[1]}, {args[2]})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        mapping = _expect_map(host, node, host.eval(node.args[0], env))
        key = host.eval(node.args[1], env)
        value = host.eval(node.args[2], env)
        return make_map(host.index, list(mapping.entries) + [(key, value)])


class MapKeysOp(Operator):
    op_id = OpId.MAP_KEYS
    roles = ("map",)
    arg_classes = ((TypeClass.MAP,),)

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Map.keys()"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return ListValue(
            items=tuple(
                k
                for k, _ in _expect_map(host, node, host.eval(node.args[0], env)).entries
            )
        )


class MapValuesOp(Operator):
    op_id = OpId.MAP_VALUES
    roles = ("map",)
    arg_classes = ((TypeClass.MAP,),)

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Map.values()"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return ListValue(
            items=tuple(
                v
                for _, v in _expect_map(host, node, host.eval(node.args[0], env)).entries
            )
        )


class MapEmptyOp(Operator):
    op_id = OpId.MAP_EMPTY

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"op_empty_map({type_arg_text(node)})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return MapValue(entries=())
