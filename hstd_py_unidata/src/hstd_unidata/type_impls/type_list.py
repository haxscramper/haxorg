from beartype.typing import List

from hstd_unidata.model_ir import ExprNode, OpId, PrimKind
from hstd_unidata.model_ops import (
    INT64_T,
    Env,
    EvalHost,
    Operator,
    TypeClass,
    expect_int,
    expect_items,
    make_bool,
    make_int,
    type_arg_text,
)
from hstd_unidata.model_value import ListValue, Value, values_equal


class ListSizeOp(Operator):
    op_id = OpId.LIST_SIZE
    roles = ("list",)
    arg_classes = ((TypeClass.LIST,),)
    fixed_result = INT64_T

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._List.size()"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return make_int(
            host,
            node,
            PrimKind.INT64,
            len(expect_items(host, node, host.eval(node.args[0], env))),
        )


class ListContainsOp(Operator):
    op_id = OpId.LIST_CONTAINS
    roles = ("list", "item")
    arg_classes = ((TypeClass.LIST,), ())
    binary_operands = True

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._List.contains({args[1]})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        items = expect_items(host, node, host.eval(node.args[0], env))
        needle = host.eval(node.args[1], env)
        return make_bool(any(values_equal(host.index, i, needle) for i in items))


class ListAtOp(Operator):
    op_id = OpId.LIST_AT
    roles = ("list", "index")
    arg_classes = ((TypeClass.LIST,), (TypeClass.INTEGER,))

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._List.at({args[1]})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        items = expect_items(host, node, host.eval(node.args[0], env))
        idx = expect_int(host, node, host.eval(node.args[1], env))
        if not (0 <= idx < len(items)):
            host.fail(
                node,
                f"index {idx} is out of bounds for a list with {len(items)} element(s), expected 0 <= index < {len(items)}",
            )
        return items[idx]


class ListSliceOp(Operator):
    op_id = OpId.LIST_SLICE
    roles = ("list", "start", "end")
    arg_classes = ((TypeClass.LIST,), (TypeClass.INTEGER,), (TypeClass.INTEGER,))

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._List.slice({args[1]}, {args[2]})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        items = expect_items(host, node, host.eval(node.args[0], env))
        start = expect_int(host, node, host.eval(node.args[1], env))
        end = expect_int(host, node, host.eval(node.args[2], env))
        if not (0 <= start <= end <= len(items)):
            host.fail(
                node,
                f"slice [{start}:{end}] is invalid for a list with {len(items)} element(s), expected 0 <= start <= end <= {len(items)}",
            )
        return ListValue(items=items[start:end])


class ListConcatOp(Operator):
    op_id = OpId.LIST_CONCAT
    roles = ("left", "right")
    arg_classes = ((TypeClass.LIST,), (TypeClass.LIST,))
    binary_operands = True

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"op_concat({args[0]}, {args[1]})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        left = expect_items(host, node, host.eval(node.args[0], env))
        right = expect_items(host, node, host.eval(node.args[1], env))
        return ListValue(items=left + right)


class ListEmptyOp(Operator):
    op_id = OpId.LIST_EMPTY

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"op_empty_list({type_arg_text(node)})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return ListValue(items=())
