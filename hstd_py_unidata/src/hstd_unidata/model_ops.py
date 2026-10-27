from __future__ import annotations

import enum
import json
import re
from abc import ABC, abstractmethod
from dataclasses import dataclass, field

from beartype import beartype
from beartype.typing import (
    ClassVar,
    Dict,
    FrozenSet,
    List,
    Mapping,
    NoReturn,
    Optional,
    Sequence,
    Tuple,
    Union,
    cast,
)
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    INTEGER_RANGES,
    ExprNode,
    NamedT,
    OpId,
    PrimKind,
    PrimT,
    TypeRef,
    numeric_join,
    type_text,
)
from hstd_py_unidata.model_value import (
    EnumValue,
    ListValue,
    MapValue,
    OptValue,
    PathValue,
    RecordValue,
    ScalarValue,
    TupleValue,
    Value,
    VariantValue,
    concrete_type_text,
    is_numeric_value,
    value_key,
    value_text,
    values_equal,
    walk_values,
)


class TypeClass(enum.StrEnum):
    """Operand requirement used by generated signature facts; one of several listed classes must hold."""

    ANY = "any"
    NUMERIC = "numeric"
    INTEGER = "integer"
    FLOAT = "float"
    STRING = "string"
    BOOL = "bool"
    ORDERED = "ordered"
    LIST = "list"
    MAP = "map"
    OPTIONAL = "optional"


TYPE_CLASS_CONSTRUCTORS: Dict[TypeClass, str] = {
    TypeClass.ANY: "CAny",
    TypeClass.NUMERIC: "CNumeric",
    TypeClass.INTEGER: "CInteger",
    TypeClass.FLOAT: "CFloat",
    TypeClass.STRING: "CString",
    TypeClass.BOOL: "CBool",
    TypeClass.ORDERED: "COrdered",
    TypeClass.LIST: "CList",
    TypeClass.MAP: "CMap",
    TypeClass.OPTIONAL: "COptional",
}

TYPE_CLASS_DESCRIPTIONS: Dict[TypeClass, str] = {
    TypeClass.ANY: "any typed value",
    TypeClass.NUMERIC: "a number (integer or float)",
    TypeClass.INTEGER: "an integer",
    TypeClass.FLOAT: "a float",
    TypeClass.STRING: "a string",
    TypeClass.BOOL: "a bool",
    TypeClass.ORDERED: "a number or a string",
    TypeClass.LIST: "a list or fixed array",
    TypeClass.MAP: "a map",
    TypeClass.OPTIONAL: "an optional",
}


class Capability(enum.StrEnum):
    """Backend capabilities an operator supports, recorded for future lowering targets."""

    VALIDATE = "validate"
    RELATIONAL = "relational"
    GENERATE_GUIDED = "generate_guided"


BOOL_T = PrimT(prim=PrimKind.BOOL)
INT64_T = PrimT(prim=PrimKind.INT64)
STRING_T = PrimT(prim=PrimKind.STRING)
PATH_T = PrimT(prim=PrimKind.PATH)

COMMON_CAPS: FrozenSet[Capability] = frozenset(
    {Capability.VALIDATE, Capability.RELATIONAL}
)
VALIDATE_ONLY: FrozenSet[Capability] = frozenset({Capability.VALIDATE})


@beartype
class EvalError(Exception):
    """Invalid operation during evaluation; it aborts the whole evaluation immediately."""

    def __init__(self, node: ExprNode, message: str, path: Optional[str]) -> None:
        where = f" on value at {path}" if path else ""
        super().__init__(
            f"{node.loc.render()}: evaluation of '{node.op.value}' failed{where}: {message}"
        )
        self.node = node
        self.path = path
        self.message = message


@beartype
@dataclass(frozen=True)
class Env:
    """Evaluation environment: the `This` value and the lexically bound binder values."""

    this: Value
    binders: Mapping[str, Value] = field(default_factory=dict)

    def bind(self, name: str, value: Value) -> Env:
        updated = dict(self.binders)
        updated[name] = value
        return Env(this=self.this, binders=updated)


@beartype
class EvalHost(ABC):
    """Services the evaluator provides to operator implementations."""

    index: ModelIndex

    @abstractmethod
    def eval(self, node: ExprNode, env: Env) -> Value: ...

    @abstractmethod
    def fail(
        self, node: ExprNode, message: str, value: Optional[Value] = None
    ) -> NoReturn: ...

    @abstractmethod
    def matches_type(self, value: Value, t: TypeRef) -> bool: ...


FORMAT_DIRECTIVE = re.compile(r"%(\.\d+)?([sdfexob%])")

FORMAT_CLASSES: Dict[str, TypeClass] = {
    "s": TypeClass.ANY,
    "d": TypeClass.INTEGER,
    "x": TypeClass.INTEGER,
    "o": TypeClass.INTEGER,
    "b": TypeClass.INTEGER,
    "f": TypeClass.NUMERIC,
    "e": TypeClass.NUMERIC,
}


@beartype
@dataclass(frozen=True)
class FormatSpec:
    """Single CEL-style format directive with its offset in the format string."""

    conv: str
    precision: Optional[int]
    start: int
    end: int


@beartype
def parse_format(fmt: str) -> List[FormatSpec]:
    """Parses CEL-style directives `%s %d %f %e %x %o %b %%` with optional `.precision`."""
    result: List[FormatSpec] = []
    pos = 0
    while True:
        idx = fmt.find("%", pos)
        if idx == -1:
            return result
        match = FORMAT_DIRECTIVE.match(fmt, idx)
        if match is None:
            raise ValueError(
                f"Invalid format directive {fmt[idx : idx + 3]!r} at offset {idx} in format string {fmt!r}; "
                f"supported directives: %s %d %f %e %x %o %b %% with optional precision like %.3f"
            )
        if match.group(2) != "%":
            precision = int(match.group(1)[1:]) if match.group(1) else None
            result.append(
                FormatSpec(
                    conv=match.group(2), precision=precision, start=idx, end=match.end()
                )
            )
        pos = match.end()


@beartype
def apply_format(fmt: str, values: Sequence[Value]) -> str:
    specs = parse_format(fmt)
    parts: List[str] = []
    pos = 0
    for spec, value in zip(specs, values):
        parts.append(fmt[pos : spec.start].replace("%%", "%"))
        number = value.value if isinstance(value, ScalarValue) else None
        match spec.conv:
            case "s":
                parts.append(value_text(value))
            case "d":
                parts.append(str(number))
            case "x":
                parts.append(format(number, "x"))
            case "o":
                parts.append(format(number, "o"))
            case "b":
                parts.append(format(number, "b"))
            case "f":
                parts.append(
                    f"{float(cast(float, number)):.{6 if spec.precision is None else spec.precision}f}"
                )
            case "e":
                parts.append(
                    f"{float(cast(float, number)):.{6 if spec.precision is None else spec.precision}e}"
                )
        pos = spec.end
    parts.append(fmt[pos:].replace("%%", "%"))
    return "".join(parts)


@beartype
def make_bool(value: bool) -> ScalarValue:
    return ScalarValue(prim=PrimKind.BOOL, value=value)


@beartype
def make_int(host: EvalHost, node: ExprNode, prim: PrimKind, value: int) -> ScalarValue:
    lo, hi = INTEGER_RANGES[prim]
    if not (lo <= value <= hi):
        host.fail(
            node,
            f"integer result {value} overflows type '{prim.value}', expected {lo} <= value <= {hi}",
        )
    return ScalarValue(prim=prim, value=value)


@beartype
def expect_bool(host: EvalHost, node: ExprNode, value: Value) -> bool:
    if isinstance(value, ScalarValue) and isinstance(value.value, bool):
        return value.value
    host.fail(
        node,
        f"expected a bool operand, got {concrete_type_text(value)} {value_text(value)}",
        value,
    )


@beartype
def expect_number(host: EvalHost, node: ExprNode, value: Value) -> Union[int, float]:
    if is_numeric_value(value):
        assert isinstance(value, ScalarValue) and isinstance(value.value, (int, float))
        return value.value
    host.fail(
        node,
        f"expected a numeric operand, got {concrete_type_text(value)} {value_text(value)}",
        value,
    )


@beartype
def expect_int(host: EvalHost, node: ExprNode, value: Value) -> int:
    number = expect_number(host, node, value)
    if isinstance(number, float):
        host.fail(node, f"expected an integer operand, got float {number}", value)
    return number


@beartype
def expect_str(host: EvalHost, node: ExprNode, value: Value) -> str:
    if isinstance(value, ScalarValue) and isinstance(value.value, str):
        return value.value
    host.fail(
        node,
        f"expected a string operand, got {concrete_type_text(value)} {value_text(value)}",
        value,
    )


@beartype
def expect_items(host: EvalHost, node: ExprNode, value: Value) -> Tuple[Value, ...]:
    if isinstance(value, ListValue):
        return value.items
    host.fail(
        node,
        f"expected a list operand, got {concrete_type_text(value)} {value_text(value)}",
        value,
    )


@beartype
def type_arg_text(node: ExprNode) -> str:
    return type_text(node.type_val) if node.type_val is not None else "?"


@beartype
class Operator(ABC):
    """Authoritative definition of one operator: roles, binders, typing facts, rendering, evaluation."""

    op_id: ClassVar[OpId]
    roles: ClassVar[Tuple[str, ...]] = ()
    rest_role: ClassVar[Optional[str]] = None
    binder_count: ClassVar[int] = 0
    scoped_args: ClassVar[FrozenSet[int]] = frozenset()
    """Argument positions evaluated with the operator binders in scope."""
    binder_insert_at: ClassVar[int] = 1
    arg_classes: ClassVar[Tuple[Tuple[TypeClass, ...], ...]] = ()
    rest_classes: ClassVar[Tuple[TypeClass, ...]] = ()
    fixed_result: ClassVar[Optional[TypeRef]] = None
    """Result type when every argument satisfies its classes, `None` means dedicated typing rules."""
    elem_binder: ClassVar[bool] = False
    """Binder 0 receives the element type of argument 0."""
    binary_operands: ClassVar[bool] = False
    """Arguments 0 and 1 must have compatible types, reported as incompatible operands."""
    capabilities: ClassVar[FrozenSet[Capability]] = COMMON_CAPS

    def arity_ok(self, count: int) -> bool:
        if self.rest_role is None:
            return count == len(self.roles)
        return len(self.roles) <= count

    def arity_text(self) -> str:
        if self.rest_role is None:
            return f"exactly {len(self.roles)} argument(s) ({', '.join(self.roles) or 'none'})"
        return f"at least {len(self.roles)} argument(s) followed by any number of '{self.rest_role}'"

    def role(self, index: int) -> str:
        if index < len(self.roles):
            return self.roles[index]
        return f"{self.rest_role}[{index - len(self.roles)}]"

    def arg_class_facts(self, node: ExprNode) -> List[Tuple[int, TypeClass]]:
        result: List[Tuple[int, TypeClass]] = []
        for idx in range(len(node.args)):
            classes = (
                self.arg_classes[idx]
                if idx < len(self.arg_classes)
                else self.rest_classes
            )
            for cls in classes:
                result.append((idx, cls))
        return result

    def render(self, node: ExprNode, args: List[str]) -> str:
        parts = list(args)
        for offset, name in enumerate(node.binders):
            parts.insert(self.binder_insert_at + offset, json.dumps(name))
        return f"op_{self.op_id.value}({', '.join(parts)})"

    @abstractmethod
    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value: ...


class ThisOp(Operator):
    op_id = OpId.THIS

    def render(self, node: ExprNode, args: List[str]) -> str:
        return "M.This"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return env.this


class VarOp(Operator):
    op_id = OpId.VAR

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"M.Iter({json.dumps(node.str_val)})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        assert node.str_val is not None
        if node.str_val not in env.binders:
            host.fail(
                node,
                f"binder '{node.str_val}' is not bound, bound binders: {', '.join(env.binders) or '(none)'}",
            )
        return env.binders[node.str_val]


class ConstIntOp(Operator):
    op_id = OpId.CONST_INT

    def render(self, node: ExprNode, args: List[str]) -> str:
        return str(node.int_val)

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        assert node.int_val is not None
        return make_int(host, node, PrimKind.INT64, node.int_val)


class ConstFloatOp(Operator):
    op_id = OpId.CONST_FLOAT

    def render(self, node: ExprNode, args: List[str]) -> str:
        return repr(node.float_val)

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return ScalarValue(prim=PrimKind.FLOAT64, value=node.float_val)


class ConstStrOp(Operator):
    op_id = OpId.CONST_STR

    def render(self, node: ExprNode, args: List[str]) -> str:
        return json.dumps(node.str_val)

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return ScalarValue(prim=PrimKind.STRING, value=node.str_val)


class ConstBoolOp(Operator):
    op_id = OpId.CONST_BOOL

    def render(self, node: ExprNode, args: List[str]) -> str:
        return "True" if node.bool_val else "False"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        assert node.bool_val is not None
        return make_bool(node.bool_val)


class GetFieldOp(Operator):
    op_id = OpId.GET_FIELD
    roles = ("object",)

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}[{json.dumps(node.str_val)}]"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        target = host.eval(node.args[0], env)
        name = node.str_val
        assert name is not None
        match target:
            case RecordValue() if name in target.fields:
                return target.fields[name]
            case VariantValue() if name in target.case.fields:
                return target.case.fields[name]
            case VariantValue():
                host.fail(
                    node,
                    f"field '{name}' is not present on the active case '{target.tag}' of {type_text(target.variant)}, "
                    f"active case fields: {', '.join(target.case.fields) or '(none)'}",
                    target,
                )
            case RecordValue():
                host.fail(
                    node,
                    f"record '{target.qname.to_id()}' instance has no field '{name}', fields: {', '.join(target.fields)}",
                    target,
                )
            case _:
                host.fail(
                    node,
                    f"field access '{name}' requires a record or variant, got {concrete_type_text(target)}",
                    target,
                )


class CompareOp(Operator):
    roles = ("left", "right")
    binary_operands = True
    symbol: ClassVar[str] = ""

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]} {self.symbol} {args[1]}"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        left = host.eval(node.args[0], env)
        right = host.eval(node.args[1], env)
        return make_bool(self.compare(host, node, left, right))

    @abstractmethod
    def compare(
        self, host: EvalHost, node: ExprNode, left: Value, right: Value
    ) -> bool: ...


class EqOp(CompareOp):
    op_id = OpId.EQ
    symbol = "=="

    def compare(
        self, host: EvalHost, node: ExprNode, left: Value, right: Value
    ) -> bool:
        return values_equal(host.index, left, right)


class NeOp(CompareOp):
    op_id = OpId.NE
    symbol = "!="

    def compare(
        self, host: EvalHost, node: ExprNode, left: Value, right: Value
    ) -> bool:
        return not values_equal(host.index, left, right)


@beartype
def ordered_operands(
    host: EvalHost, node: ExprNode, left: Value, right: Value
) -> Tuple[Union[int, float, str], Union[int, float, str]]:
    if is_numeric_value(left) and is_numeric_value(right):
        return expect_number(host, node, left), expect_number(host, node, right)
    return expect_str(host, node, left), expect_str(host, node, right)


class LtOp(CompareOp):
    op_id = OpId.LT
    symbol = "<"

    def compare(
        self, host: EvalHost, node: ExprNode, left: Value, right: Value
    ) -> bool:
        lv, rv = ordered_operands(host, node, left, right)
        assert isinstance(lv, (int, float))
        assert isinstance(rv, (int, float))
        return lv < rv


class LeOp(CompareOp):
    op_id = OpId.LE
    symbol = "<="

    def compare(
        self, host: EvalHost, node: ExprNode, left: Value, right: Value
    ) -> bool:
        lv, rv = ordered_operands(host, node, left, right)
        assert isinstance(lv, (int, float))
        assert isinstance(rv, (int, float))
        return lv <= rv


class ArithmeticOp(Operator):
    roles = ("left", "right")
    binary_operands = True
    symbol: ClassVar[str] = ""

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"({args[0]} {self.symbol} {args[1]})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        left = host.eval(node.args[0], env)
        right = host.eval(node.args[1], env)
        if (
            self.op_id == OpId.ADD
            and isinstance(left, ScalarValue)
            and isinstance(left.value, str)
        ):
            return ScalarValue(
                prim=PrimKind.STRING, value=left.value + expect_str(host, node, right)
            )
        lv = expect_number(host, node, left)
        rv = expect_number(host, node, right)
        assert isinstance(left, ScalarValue) and isinstance(right, ScalarValue)
        prim = numeric_join(left.prim, right.prim)
        result = self.apply(host, node, lv, rv, prim)
        if prim in INTEGER_RANGES:
            return make_int(host, node, prim, int(result))
        return ScalarValue(prim=prim, value=float(result))

    @abstractmethod
    def apply(
        self,
        host: EvalHost,
        node: ExprNode,
        lv: Union[int, float],
        rv: Union[int, float],
        prim: PrimKind,
    ) -> Union[int, float]: ...


class AddOp(ArithmeticOp):
    op_id = OpId.ADD
    symbol = "+"

    def apply(
        self,
        host: EvalHost,
        node: ExprNode,
        lv: Union[int, float],
        rv: Union[int, float],
        prim: PrimKind,
    ) -> Union[int, float]:
        return lv + rv


class SubOp(ArithmeticOp):
    op_id = OpId.SUB
    symbol = "-"

    def apply(
        self,
        host: EvalHost,
        node: ExprNode,
        lv: Union[int, float],
        rv: Union[int, float],
        prim: PrimKind,
    ) -> Union[int, float]:
        return lv - rv


class MulOp(ArithmeticOp):
    op_id = OpId.MUL
    symbol = "*"

    def apply(
        self,
        host: EvalHost,
        node: ExprNode,
        lv: Union[int, float],
        rv: Union[int, float],
        prim: PrimKind,
    ) -> Union[int, float]:
        return lv * rv


class DivOp(ArithmeticOp):
    op_id = OpId.DIV
    symbol = "/"

    def apply(
        self,
        host: EvalHost,
        node: ExprNode,
        lv: Union[int, float],
        rv: Union[int, float],
        prim: PrimKind,
    ) -> Union[int, float]:
        if rv == 0:
            host.fail(node, f"division by zero: {lv} / {rv}")
        if prim in INTEGER_RANGES:
            quotient = abs(int(lv)) // abs(int(rv))
            return quotient if (lv < 0) == (rv < 0) else -quotient
        return lv / rv


class AndOp(Operator):
    op_id = OpId.AND
    rest_role = "operand"
    rest_classes = (TypeClass.BOOL,)
    fixed_result = BOOL_T

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        for arg in node.args:
            if not expect_bool(host, arg, host.eval(arg, env)):
                return make_bool(False)
        return make_bool(True)


class OrOp(Operator):
    op_id = OpId.OR
    rest_role = "operand"
    rest_classes = (TypeClass.BOOL,)
    fixed_result = BOOL_T

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        for arg in node.args:
            if expect_bool(host, arg, host.eval(arg, env)):
                return make_bool(True)
        return make_bool(False)


class NotOp(Operator):
    op_id = OpId.NOT
    roles = ("operand",)
    arg_classes = ((TypeClass.BOOL,),)
    fixed_result = BOOL_T

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return make_bool(not expect_bool(host, node, host.eval(node.args[0], env)))


class CondOp(Operator):
    op_id = OpId.COND
    roles = ("condition", "then", "else")
    arg_classes = ((TypeClass.BOOL,), (), ())

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"op_cond(({args[0]}, {args[1]}), default={args[2]})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        if expect_bool(host, node, host.eval(node.args[0], env)):
            return host.eval(node.args[1], env)
        return host.eval(node.args[2], env)


class LetOp(Operator):
    op_id = OpId.LET
    roles = ("value", "body")
    binder_count = 1
    scoped_args = frozenset({1})
    binder_insert_at = 0

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        value = host.eval(node.args[0], env)
        return host.eval(node.args[1], env.bind(node.binders[0], value))


class CollectionOp(Operator):
    roles = ("collection", "body")
    binder_count = 1
    scoped_args = frozenset({1})
    elem_binder = True

    def body_values(
        self, host: EvalHost, node: ExprNode, env: Env
    ) -> List[Tuple[Value, Value]]:
        items = expect_items(host, node, host.eval(node.args[0], env))
        return [
            (item, host.eval(node.args[1], env.bind(node.binders[0], item)))
            for item in items
        ]


class AllOp(CollectionOp):
    op_id = OpId.ALL
    arg_classes = ((TypeClass.LIST,), (TypeClass.BOOL,))

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        for item in expect_items(host, node, host.eval(node.args[0], env)):
            if not expect_bool(
                host, node, host.eval(node.args[1], env.bind(node.binders[0], item))
            ):
                return make_bool(False)
        return make_bool(True)


class ExistsOp(CollectionOp):
    op_id = OpId.EXISTS
    arg_classes = ((TypeClass.LIST,), (TypeClass.BOOL,))

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        for item in expect_items(host, node, host.eval(node.args[0], env)):
            if expect_bool(
                host, node, host.eval(node.args[1], env.bind(node.binders[0], item))
            ):
                return make_bool(True)
        return make_bool(False)


class ExistsOneOp(CollectionOp):
    op_id = OpId.EXISTS_ONE
    arg_classes = ((TypeClass.LIST,), (TypeClass.BOOL,))

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        count = sum(
            1
            for _, r in self.body_values(host, node, env)
            if expect_bool(host, node, r)
        )
        return make_bool(count == 1)


class MapOp(CollectionOp):
    op_id = OpId.MAP
    arg_classes = ((TypeClass.LIST,), ())

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return ListValue(items=tuple(r for _, r in self.body_values(host, node, env)))


class FilterOp(CollectionOp):
    op_id = OpId.FILTER
    arg_classes = ((TypeClass.LIST,), (TypeClass.BOOL,))

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return ListValue(
            items=tuple(
                i
                for i, r in self.body_values(host, node, env)
                if expect_bool(host, node, r)
            )
        )


class FilterMapOp(CollectionOp):
    op_id = OpId.FILTER_MAP
    arg_classes = ((TypeClass.LIST,), (TypeClass.OPTIONAL,))

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        result: List[Value] = []
        for _, r in self.body_values(host, node, env):
            if not isinstance(r, OptValue):
                host.fail(
                    node,
                    f"filter_map body must produce an optional, got {concrete_type_text(r)}",
                    r,
                )
            if r.value is not None:
                result.append(r.value)
        return ListValue(items=tuple(result))


class TakeWhileOp(CollectionOp):
    op_id = OpId.TAKE_WHILE
    arg_classes = ((TypeClass.LIST,), (TypeClass.BOOL,))
    capabilities = VALIDATE_ONLY

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        result: List[Value] = []
        for item in expect_items(host, node, host.eval(node.args[0], env)):
            if not expect_bool(
                host, node, host.eval(node.args[1], env.bind(node.binders[0], item))
            ):
                break
            result.append(item)
        return ListValue(items=tuple(result))


class GroupByOp(CollectionOp):
    op_id = OpId.GROUP_BY
    roles = ("collection", "key")
    arg_classes = ((TypeClass.LIST,), (TypeClass.ANY,))

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        order: List[object] = []
        keys: Dict[object, Value] = {}
        groups: Dict[object, List[Value]] = {}
        for item, key in self.body_values(host, node, env):
            kk = value_key(host.index, key)
            if kk not in groups:
                order.append(kk)
                keys[kk] = key
                groups[kk] = []
            groups[kk].append(item)
        return MapValue(
            entries=tuple((keys[k], ListValue(items=tuple(groups[k]))) for k in order)
        )


class FoldOp(Operator):
    op_id = OpId.FOLD
    roles = ("collection", "init", "body")
    binder_count = 2
    scoped_args = frozenset({2})
    binder_insert_at = 2
    arg_classes = ((TypeClass.LIST,), (), ())
    capabilities = VALIDATE_ONLY

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        acc = host.eval(node.args[1], env)
        for item in expect_items(host, node, host.eval(node.args[0], env)):
            acc = host.eval(
                node.args[2], env.bind(node.binders[0], acc).bind(node.binders[1], item)
            )
        return acc


class WalkOp(Operator):
    op_id = OpId.WALK
    roles = ("root",)
    arg_classes = ((TypeClass.ANY,),)

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return ListValue(items=tuple(walk_values(host.eval(node.args[0], env))))


class SumOp(Operator):
    op_id = OpId.SUM
    roles = ("collection",)
    arg_classes = ((TypeClass.LIST,),)

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        numbers = [
            expect_number(host, node, i)
            for i in expect_items(host, node, host.eval(node.args[0], env))
        ]
        if any(isinstance(n, float) for n in numbers):
            return ScalarValue(prim=PrimKind.FLOAT64, value=float(sum(numbers)))
        return make_int(host, node, PrimKind.INT64, int(sum(numbers)))


class ExtremumOp(Operator):
    roles = ("collection",)
    arg_classes = ((TypeClass.LIST,),)
    pick_max: ClassVar[bool] = False

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        items = expect_items(host, node, host.eval(node.args[0], env))
        if len(items) == 0:
            host.fail(node, f"{self.op_id.value} of an empty list is undefined")
        best = items[0]
        for item in items[1:]:
            lv, rv = ordered_operands(host, node, best, item)
            assert isinstance(lv, (int, float))
            assert isinstance(rv, (int, float))
            if (lv < rv) if self.pick_max else (rv < lv):
                best = item
        return best


class MinOp(ExtremumOp):
    op_id = OpId.MIN


class MaxOp(ExtremumOp):
    op_id = OpId.MAX
    pick_max = True


class StrSizeOp(Operator):
    op_id = OpId.STR_SIZE
    roles = ("string",)
    arg_classes = ((TypeClass.STRING,),)
    fixed_result = INT64_T

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Str.size()"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return make_int(
            host,
            node,
            PrimKind.INT64,
            len(expect_str(host, node, host.eval(node.args[0], env))),
        )


class StrMatchesOp(Operator):
    op_id = OpId.STR_MATCHES
    roles = ("string",)
    arg_classes = ((TypeClass.STRING,),)
    fixed_result = BOOL_T
    capabilities = VALIDATE_ONLY

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Str.matches({json.dumps(node.str_val)})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        assert node.str_val is not None
        return make_bool(
            re.search(
                node.str_val, expect_str(host, node, host.eval(node.args[0], env))
            )
            is not None
        )


class StrFormatOp(Operator):
    op_id = OpId.STR_FORMAT
    rest_role = "value"
    fixed_result = STRING_T
    capabilities = VALIDATE_ONLY

    def arg_class_facts(self, node: ExprNode) -> List[Tuple[int, TypeClass]]:
        assert node.str_val is not None
        return [
            (i, FORMAT_CLASSES[spec.conv])
            for i, spec in enumerate(parse_format(node.str_val))
        ]

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"op_format({', '.join([json.dumps(node.str_val)] + args)})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        assert node.str_val is not None
        values = [host.eval(a, env) for a in node.args]
        for spec, value, arg in zip(parse_format(node.str_val), values, node.args):
            if spec.conv != "s" and not is_numeric_value(value):
                host.fail(
                    arg,
                    f"format directive %{spec.conv} requires a number, got {concrete_type_text(value)}",
                    value,
                )
        return ScalarValue(
            prim=PrimKind.STRING, value=apply_format(node.str_val, values)
        )


class OptHasValueOp(Operator):
    op_id = OpId.OPT_HAS_VALUE
    roles = ("optional",)
    arg_classes = ((TypeClass.OPTIONAL,),)
    fixed_result = BOOL_T

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Opt.has_value()"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        value = host.eval(node.args[0], env)
        if not isinstance(value, OptValue):
            host.fail(
                node, f"expected an optional, got {concrete_type_text(value)}", value
            )
        return make_bool(value.value is not None)


class OptValueOp(Operator):
    op_id = OpId.OPT_VALUE
    roles = ("optional",)
    arg_classes = ((TypeClass.OPTIONAL,),)

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Opt.value()"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        value = host.eval(node.args[0], env)
        if not isinstance(value, OptValue):
            host.fail(
                node, f"expected an optional, got {concrete_type_text(value)}", value
            )
        if value.value is None:
            host.fail(
                node,
                "optional has no value; guard the access with `_Opt.has_value()` in a short-circuiting op_and/op_or/op_cond",
                value,
            )
        return value.value


class CaseIsOp(Operator):
    op_id = OpId.CASE_IS
    roles = ("variant",)

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Case.is_case({json.dumps(node.str_val)})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        value = host.eval(node.args[0], env)
        if not isinstance(value, VariantValue):
            host.fail(
                node, f"expected a variant, got {concrete_type_text(value)}", value
            )
        return make_bool(value.tag == node.str_val)


class CaseWhichOp(Operator):
    op_id = OpId.CASE_WHICH
    roles = ("variant",)

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Case.which_case()"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        value = host.eval(node.args[0], env)
        if not isinstance(value, VariantValue):
            host.fail(
                node, f"expected a variant, got {concrete_type_text(value)}", value
            )
        return EnumValue(
            enum=host.index.variant(value.variant).kind_enum, name=value.tag
        )


class EnumIsOp(Operator):
    op_id = OpId.ENUM_IS
    roles = ("enum",)

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Enum.is_val({json.dumps(node.str_val)})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        value = host.eval(node.args[0], env)
        if not isinstance(value, EnumValue):
            host.fail(
                node, f"expected an enum value, got {concrete_type_text(value)}", value
            )
        return make_bool(value.name == node.str_val)


class NthGetOp(Operator):
    op_id = OpId.NTH_GET
    roles = ("tuple",)

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}._Nth.get({node.int_val})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        value = host.eval(node.args[0], env)
        assert node.int_val is not None
        if not isinstance(value, TupleValue) or not (
            0 <= node.int_val < len(value.items)
        ):
            host.fail(
                node,
                f"tuple index {node.int_val} is invalid for {concrete_type_text(value)} {value_text(value)}",
                value,
            )
        return value.items[node.int_val]


class IsDerivedOp(Operator):
    op_id = OpId.IS_DERIVED
    roles = ("object",)

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"{args[0]}.is_derived_from({type_arg_text(node)})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        value = host.eval(node.args[0], env)
        if not isinstance(value, RecordValue) or not isinstance(node.type_val, NamedT):
            host.fail(
                node,
                f"derivation test requires a record value, got {concrete_type_text(value)}",
                value,
            )
        return make_bool(host.index.derived_from(value.qname, node.type_val.qname))


class TypeCondOp(Operator):
    op_id = OpId.TYPE_COND
    roles = ("subject",)
    rest_role = "case"

    def render(self, node: ExprNode, args: List[str]) -> str:
        suffix = ", unhandled_ignore=True" if node.bool_val else ""
        return f"type_cond({', '.join(args)}{suffix})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        subject = host.eval(node.args[0], env)
        for case in node.args[1:]:
            assert case.type_val is not None
            if host.matches_type(subject, case.type_val):
                result = host.eval(case.args[0], env.bind(case.binders[0], subject))
                return OptValue(value=result) if node.bool_val else result
        if node.bool_val:
            return OptValue(value=None)
        handled = ", ".join(type_arg_text(c) for c in node.args[1:])
        host.fail(
            node,
            f"no type_case matched a value of type {concrete_type_text(subject)}, handled types: {handled}",
            subject,
        )


class TypeCaseOp(Operator):
    op_id = OpId.TYPE_CASE
    roles = ("body",)
    binder_count = 1
    scoped_args = frozenset({0})

    def render(self, node: ExprNode, args: List[str]) -> str:
        return f"type_case({type_arg_text(node)}, {json.dumps(node.binders[0])}, {args[0]})"

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        host.fail(node, "type_case can only be evaluated as an argument of type_cond")


class PathOfOp(Operator):
    op_id = OpId.PATH_OF
    roles = ("value",)
    arg_classes = ((TypeClass.ANY,),)
    fixed_result = PATH_T
    capabilities = VALIDATE_ONLY

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        value = host.eval(node.args[0], env)
        if value.path is None:
            host.fail(
                node,
                f"value {value_text(value)[:100]} was computed by the expression and has no occurrence path in the instance",
            )
        return PathValue(target=value.path)


class TypeOfOp(Operator):
    op_id = OpId.TYPE_OF
    roles = ("value",)
    arg_classes = ((TypeClass.ANY,),)
    fixed_result = STRING_T

    def evaluate(self, host: EvalHost, node: ExprNode, env: Env) -> Value:
        return ScalarValue(
            prim=PrimKind.STRING, value=concrete_type_text(host.eval(node.args[0], env))
        )


@beartype
def default_operators() -> List[Operator]:
    """Core operator set; pass a modified list to `get_dsl_model` to customize the language."""
    from hstd_py_unidata.type_impls import type_list, type_map

    return [
        ThisOp(),
        VarOp(),
        ConstIntOp(),
        ConstFloatOp(),
        ConstStrOp(),
        ConstBoolOp(),
        GetFieldOp(),
        EqOp(),
        NeOp(),
        LtOp(),
        LeOp(),
        AddOp(),
        SubOp(),
        MulOp(),
        DivOp(),
        AndOp(),
        OrOp(),
        NotOp(),
        CondOp(),
        LetOp(),
        AllOp(),
        ExistsOp(),
        ExistsOneOp(),
        MapOp(),
        FilterOp(),
        FilterMapOp(),
        TakeWhileOp(),
        GroupByOp(),
        FoldOp(),
        WalkOp(),
        SumOp(),
        MinOp(),
        MaxOp(),
        StrSizeOp(),
        StrMatchesOp(),
        StrFormatOp(),
        type_list.ListSizeOp(),
        type_list.ListContainsOp(),
        type_list.ListAtOp(),
        type_list.ListSliceOp(),
        type_list.ListConcatOp(),
        type_list.ListEmptyOp(),
        type_map.MapSizeOp(),
        type_map.MapContainsOp(),
        type_map.MapGetOp(),
        type_map.MapInsertOp(),
        type_map.MapKeysOp(),
        type_map.MapValuesOp(),
        type_map.MapEmptyOp(),
        OptHasValueOp(),
        OptValueOp(),
        CaseIsOp(),
        CaseWhichOp(),
        EnumIsOp(),
        NthGetOp(),
        IsDerivedOp(),
        TypeCondOp(),
        TypeCaseOp(),
        PathOfOp(),
        TypeOfOp(),
    ]


@beartype
def operator_table(operators: Sequence[Operator]) -> Dict[OpId, Operator]:
    table: Dict[OpId, Operator] = {}
    for op in operators:
        if op.op_id in table:
            raise ValueError(
                f"Operator '{op.op_id.value}' is registered twice: {type(table[op.op_id]).__name__} and {type(op).__name__}"
            )
        table[op.op_id] = op
    return table


@beartype
def render_expr(table: Dict[OpId, Operator], node: ExprNode) -> str:
    return table[node.op].render(node, [render_expr(table, a) for a in node.args])
