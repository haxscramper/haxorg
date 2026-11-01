from __future__ import annotations

import functools
import re
import sys
import types
from contextvars import ContextVar
from pathlib import Path

from beartype import beartype
from beartype.typing import Any, Callable, Optional, Tuple, TypeVar

from hstd_py_unidata.model_ir import ExprNode, OpId, SourceLoc, TypeRef
from hstd_py_unidata.model_ops_str_format import parse_format
from hstd_py_unidata.model_resolve import AnnotationResolver

IMPLEMENTATION_FILES = frozenset(
    path.resolve() for path in Path(__file__).resolve().parent.rglob("*.py")
)

LIBRARY_PREFIXES = (
    "beartype",
    "pydantic",
    "functools",
    "contextlib",
    "typing",
)

CAPTURED_LOC: ContextVar[Optional[SourceLoc]] = ContextVar("CAPTURED_LOC", default=None)

FrontendFunc = TypeVar("FrontendFunc", bound=Callable[..., Any])

UNRESOLVED_TYPES = AnnotationResolver(None)


@beartype
def is_implementation_frame(frame: types.FrameType) -> bool:
    module = str(frame.f_globals.get("__name__", ""))
    filename = frame.f_code.co_filename
    return (
        filename.startswith("<")
        or module.startswith(LIBRARY_PREFIXES)
        or Path(filename).resolve() in IMPLEMENTATION_FILES
    )


@beartype
def user_frame_loc() -> SourceLoc:
    """Location of the innermost stack frame that belongs to user model code."""
    frame: Optional[types.FrameType] = sys._getframe(1)
    while frame is not None:
        if not is_implementation_frame(frame):
            return SourceLoc(
                file=frame.f_code.co_filename,
                line=frame.f_lineno,
                function=frame.f_code.co_name,
            )
        frame = frame.f_back
    raise RuntimeError(
        "Could not locate user code on the call stack: every frame belongs to the DSL implementation modules "
        f"{sorted(IMPLEMENTATION_FILES)} or to libraries {LIBRARY_PREFIXES}"
    )


def frontend_entry(func: FrontendFunc) -> FrontendFunc:
    """Captures the user source location once, at the outermost public DSL entry point."""

    @functools.wraps(func)
    def wrapper(*args: Any, **kwargs: Any) -> Any:
        if CAPTURED_LOC.get() is not None:
            return func(*args, **kwargs)
        token = CAPTURED_LOC.set(user_frame_loc())
        try:
            return func(*args, **kwargs)
        finally:
            CAPTURED_LOC.reset(token)

    return wrapper  # type: ignore[return-value]


@beartype
def current_loc() -> SourceLoc:
    loc = CAPTURED_LOC.get()
    if loc is None:
        raise RuntimeError(
            "An expression node was constructed outside of a DSL entry point, so its source location is unknown; "
            "decorate the public builder with @frontend_entry"
        )
    return loc


@beartype
def make_node(
    op: OpId,
    args: Tuple[ExprNode, ...] = (),
    binders: Tuple[str, ...] = (),
    str_val: Optional[str] = None,
    int_val: Optional[int] = None,
    float_val: Optional[float] = None,
    bool_val: Optional[bool] = None,
    type_val: Optional[TypeRef] = None,
) -> Expr:
    return Expr(
        ExprNode(
            op=op,
            args=args,
            binders=binders,
            str_val=str_val,
            int_val=int_val,
            float_val=float_val,
            bool_val=bool_val,
            type_val=type_val,
            loc=current_loc(),
        )
    )


@frontend_entry
@beartype
def to_node(value: Any) -> ExprNode:
    """Converts an expression or a Python literal into an expression node."""
    match value:
        case Expr():
            return value.node
        case bool():
            return make_node(OpId.CONST_BOOL, bool_val=value).node
        case int():
            return make_node(OpId.CONST_INT, int_val=value).node
        case float():
            return make_node(OpId.CONST_FLOAT, float_val=value).node
        case str():
            return make_node(OpId.CONST_STR, str_val=value).node
        case _:
            raise TypeError(
                f"Cannot convert {value!r} of type {type(value).__name__} into a DSL expression; expected Expr, bool, int, float or str"
            )


@beartype
def type_arg(value: Any) -> TypeRef:
    """Type argument of an expression; names in strings are resolved in the scope of the owning record."""
    return UNRESOLVED_TYPES.resolve(value)


@beartype
def check_binder_name(name: str, op: str) -> None:
    if not name.isidentifier():
        raise ValueError(
            f"Binder name {name!r} of {op} must be a valid identifier, like 'item' or 'node'"
        )


@beartype
class StrOps:
    def __init__(self, target: Expr) -> None:
        self.target = target

    @frontend_entry
    def size(self) -> Expr:
        return make_node(OpId.STR_SIZE, (self.target.node,))

    @frontend_entry
    def matches(self, pattern: str) -> Expr:
        try:
            re.compile(pattern)
        except re.error as err:
            raise ValueError(f"Regular expression {pattern!r} is invalid: {err}") from err
        return make_node(OpId.STR_MATCHES, (self.target.node,), str_val=pattern)


@beartype
class ListOps:
    def __init__(self, target: Expr) -> None:
        self.target = target

    @frontend_entry
    def size(self) -> Expr:
        return make_node(OpId.LIST_SIZE, (self.target.node,))

    @frontend_entry
    def contains(self, item: Any) -> Expr:
        return make_node(OpId.LIST_CONTAINS, (self.target.node, to_node(item)))

    @frontend_entry
    def at(self, index: Any) -> Expr:
        return make_node(OpId.LIST_AT, (self.target.node, to_node(index)))

    @frontend_entry
    def slice(self, start: Any, end: Any) -> Expr:
        return make_node(
            OpId.LIST_SLICE, (self.target.node, to_node(start), to_node(end))
        )


@beartype
class MapOps:
    def __init__(self, target: Expr) -> None:
        self.target = target

    @frontend_entry
    def size(self) -> Expr:
        return make_node(OpId.MAP_SIZE, (self.target.node,))

    @frontend_entry
    def contains(self, key: Any) -> Expr:
        return make_node(OpId.MAP_CONTAINS, (self.target.node, to_node(key)))

    @frontend_entry
    def get(self, key: Any) -> Expr:
        return make_node(OpId.MAP_GET, (self.target.node, to_node(key)))

    @frontend_entry
    def insert(self, key: Any, value: Any) -> Expr:
        return make_node(
            OpId.MAP_INSERT, (self.target.node, to_node(key), to_node(value))
        )

    @frontend_entry
    def keys(self) -> Expr:
        return make_node(OpId.MAP_KEYS, (self.target.node,))

    @frontend_entry
    def values(self) -> Expr:
        return make_node(OpId.MAP_VALUES, (self.target.node,))


@beartype
class OptOps:
    def __init__(self, target: Expr) -> None:
        self.target = target

    @frontend_entry
    def has_value(self) -> Expr:
        return make_node(OpId.OPT_HAS_VALUE, (self.target.node,))

    @frontend_entry
    def value(self) -> Expr:
        return make_node(OpId.OPT_VALUE, (self.target.node,))


@beartype
class CaseOps:
    def __init__(self, target: Expr) -> None:
        self.target = target

    @frontend_entry
    def is_case(self, tag: str) -> Expr:
        return make_node(OpId.CASE_IS, (self.target.node,), str_val=tag)

    @frontend_entry
    def which_case(self) -> Expr:
        return make_node(OpId.CASE_WHICH, (self.target.node,))


@beartype
class EnumOps:
    def __init__(self, target: Expr) -> None:
        self.target = target

    @frontend_entry
    def is_val(self, name: str) -> Expr:
        return make_node(OpId.ENUM_IS, (self.target.node,), str_val=name)


@beartype
class NthOps:
    def __init__(self, target: Expr) -> None:
        self.target = target

    @frontend_entry
    def get(self, index: int) -> Expr:
        return make_node(OpId.NTH_GET, (self.target.node,), int_val=index)


class ExprAccessors:
    """Typed accessor namespaces that build operations on top of an expression."""

    @property
    def _Str(self) -> StrOps:
        return StrOps(self)  # type: ignore[arg-type]

    @property
    def _List(self) -> ListOps:
        return ListOps(self)  # type: ignore[arg-type]

    @property
    def _Map(self) -> MapOps:
        return MapOps(self)  # type: ignore[arg-type]

    @property
    def _Opt(self) -> OptOps:
        return OptOps(self)  # type: ignore[arg-type]

    @property
    def _Case(self) -> CaseOps:
        return CaseOps(self)  # type: ignore[arg-type]

    @property
    def _Enum(self) -> EnumOps:
        return EnumOps(self)  # type: ignore[arg-type]

    @property
    def _Nth(self) -> NthOps:
        return NthOps(self)  # type: ignore[arg-type]


class Expr(ExprAccessors):
    """Frontend handle of an expression node providing the Python operator syntax."""

    __hash__ = None  # type: ignore[assignment]

    def __init__(self, node: ExprNode) -> None:
        self.node = node

    def __repr__(self) -> str:
        return f"Expr({self.node.op.value} at {self.node.loc.render()})"

    def __bool__(self) -> bool:
        raise TypeError(
            f"DSL expression '{self.node.op.value}' built at {self.node.loc.render()} was used in a Python boolean context "
            "(if, and, or, not, or a chained comparison); use op_and/op_or/op_not or the &, |, ~ operators instead"
        )

    @frontend_entry
    def __eq__(self, other: object) -> Expr:  # type: ignore[override]
        return make_node(OpId.EQ, (self.node, to_node(other)))

    @frontend_entry
    def __ne__(self, other: object) -> Expr:  # type: ignore[override]
        return make_node(OpId.NE, (self.node, to_node(other)))

    @frontend_entry
    def __lt__(self, other: object) -> Expr:
        return make_node(OpId.LT, (self.node, to_node(other)))

    @frontend_entry
    def __le__(self, other: object) -> Expr:
        return make_node(OpId.LE, (self.node, to_node(other)))

    @frontend_entry
    def __gt__(self, other: object) -> Expr:
        return make_node(OpId.LT, (to_node(other), self.node))

    @frontend_entry
    def __ge__(self, other: object) -> Expr:
        return make_node(OpId.LE, (to_node(other), self.node))

    @frontend_entry
    def __add__(self, other: object) -> Expr:
        return make_node(OpId.ADD, (self.node, to_node(other)))

    @frontend_entry
    def __radd__(self, other: object) -> Expr:
        return make_node(OpId.ADD, (to_node(other), self.node))

    @frontend_entry
    def __sub__(self, other: object) -> Expr:
        return make_node(OpId.SUB, (self.node, to_node(other)))

    @frontend_entry
    def __rsub__(self, other: object) -> Expr:
        return make_node(OpId.SUB, (to_node(other), self.node))

    @frontend_entry
    def __mul__(self, other: object) -> Expr:
        return make_node(OpId.MUL, (self.node, to_node(other)))

    @frontend_entry
    def __rmul__(self, other: object) -> Expr:
        return make_node(OpId.MUL, (to_node(other), self.node))

    @frontend_entry
    def __truediv__(self, other: object) -> Expr:
        return make_node(OpId.DIV, (self.node, to_node(other)))

    @frontend_entry
    def __rtruediv__(self, other: object) -> Expr:
        return make_node(OpId.DIV, (to_node(other), self.node))

    @frontend_entry
    def __and__(self, other: object) -> Expr:
        return make_node(OpId.AND, (self.node, to_node(other)))

    @frontend_entry
    def __rand__(self, other: object) -> Expr:
        return make_node(OpId.AND, (to_node(other), self.node))

    @frontend_entry
    def __or__(self, other: object) -> Expr:
        return make_node(OpId.OR, (self.node, to_node(other)))

    @frontend_entry
    def __ror__(self, other: object) -> Expr:
        return make_node(OpId.OR, (to_node(other), self.node))

    @frontend_entry
    def __invert__(self) -> Expr:
        return make_node(OpId.NOT, (self.node,))

    @frontend_entry
    def __getitem__(self, name: str) -> Expr:
        if not isinstance(name, str):
            raise TypeError(
                f"Field access expects a field name string, got {name!r}; use ._List.at(...) or ._Nth.get(...) for positional access"
            )
        return make_node(OpId.GET_FIELD, (self.node,), str_val=name)

    @frontend_entry
    def is_derived_from(self, target: Any) -> Expr:
        return make_node(OpId.IS_DERIVED, (self.node,), type_val=type_arg(target))


@frontend_entry
@beartype
def this_expr() -> Expr:
    return make_node(OpId.THIS)


@frontend_entry
@beartype
def var_expr(name: str) -> Expr:
    check_binder_name(name, "M.Iter")
    return make_node(OpId.VAR, str_val=name)


@frontend_entry
@beartype
def op_and(*args: Any) -> Expr:
    if len(args) == 0:
        raise ValueError("op_and requires at least one operand")
    return make_node(OpId.AND, tuple(to_node(a) for a in args))


@frontend_entry
@beartype
def op_or(*args: Any) -> Expr:
    if len(args) == 0:
        raise ValueError("op_or requires at least one operand")
    return make_node(OpId.OR, tuple(to_node(a) for a in args))


@frontend_entry
@beartype
def op_not(arg: Any) -> Expr:
    return make_node(OpId.NOT, (to_node(arg),))


@frontend_entry
@beartype
def op_cond(*branches: Tuple[Any, Any], default: Any) -> Expr:
    """Lisp-style conditional: the value of the first branch whose condition holds, otherwise the default."""
    result = to_node(default)
    for cond, value in reversed(branches):
        result = make_node(OpId.COND, (to_node(cond), to_node(value), result)).node
    return Expr(result)


@frontend_entry
@beartype
def op_let(name: str, value: Any, body: Any) -> Expr:
    """
    Introduce a new bound variable `name` into the scope, assigning the expression
    `value` to it. The expression itself evaluates to the result of the `body` block.
    """
    check_binder_name(name, "op_let")
    return make_node(OpId.LET, (to_node(value), to_node(body)), binders=(name,))


@beartype
def collection_op(op: OpId, collection: Any, name: str, body: Any) -> Expr:
    check_binder_name(name, f"op_{op.value}")
    return make_node(op, (to_node(collection), to_node(body)), binders=(name,))


@frontend_entry
@beartype
def op_all(collection: Any, name: str, body: Any) -> Expr:
    """
    Check if all elements in the provided collection match the predicate
    Second argument describes the new binding variable for each individual
    item in the collection to iterate.
    """
    return collection_op(OpId.ALL, collection, name, body)


@frontend_entry
@beartype
def op_exists(collection: Any, name: str, body: Any) -> Expr:
    "Check if any element in the collection matches the predicate"
    return collection_op(OpId.EXISTS, collection, name, body)


@frontend_entry
@beartype
def op_exists_one(collection: Any, name: str, body: Any) -> Expr:
    "Check if exactly one element in the collection matches the predicate"
    return collection_op(OpId.EXISTS_ONE, collection, name, body)


@frontend_entry
@beartype
def op_map(collection: Any, name: str, body: Any) -> Expr:
    "Convert every element in the input collection to the new list of items."
    return collection_op(OpId.MAP, collection, name, body)


@frontend_entry
@beartype
def op_filter(collection: Any, name: str, body: Any) -> Expr:
    "Return items matching the predicate in collection"
    return collection_op(OpId.FILTER, collection, name, body)


@frontend_entry
@beartype
def op_filter_map(collection: Any, name: str, body: Any) -> Expr:
    """Keeps the present values of an optional-producing body, like `filter_map` in Rust."""
    return collection_op(OpId.FILTER_MAP, collection, name, body)


@frontend_entry
@beartype
def op_take_while(collection: Any, name: str, body: Any) -> Expr:
    return collection_op(OpId.TAKE_WHILE, collection, name, body)


@frontend_entry
@beartype
def op_group_by(collection: Any, name: str, key: Any) -> Expr:
    """Map from each distinct key to the list of elements producing it, in first-occurrence order."""
    return collection_op(OpId.GROUP_BY, collection, name, key)


@frontend_entry
@beartype
def op_fold(collection: Any, init: Any, acc: str, item: str, body: Any) -> Expr:
    check_binder_name(acc, "op_fold")
    check_binder_name(item, "op_fold")
    return make_node(
        OpId.FOLD,
        (to_node(collection), to_node(init), to_node(body)),
        binders=(acc, item),
    )


@frontend_entry
@beartype
def op_walk(root: Any) -> Expr:
    """
    Recursive descent over every value contained in the root, including the root itself.

    Return the evaluation result as a flat list of all values in the model, the consumer
    is expected to use `type_cond` to evaluate the outputs.
    """
    return make_node(OpId.WALK, (to_node(root),))


@frontend_entry
@beartype
def op_all_rec(root: Any, name: str, body: Any) -> Expr:
    """
    Recursively iterate over all the items in the model structure and return expression
    eval from the result.
    """
    return collection_op(OpId.ALL, op_walk(root), name, body)


@frontend_entry
@beartype
def op_concat(first: Any, *rest: Any) -> Expr:
    "Concatenate one or more list collections"
    result = to_node(first)
    for item in rest:
        result = make_node(OpId.LIST_CONCAT, (result, to_node(item))).node
    return Expr(result)


@frontend_entry
@beartype
def op_sum(collection: Any) -> Expr:
    "Add all collection elements together"
    return make_node(OpId.SUM, (to_node(collection),))


@frontend_entry
@beartype
def op_min(collection: Any) -> Expr:
    return make_node(OpId.MIN, (to_node(collection),))


@frontend_entry
@beartype
def op_max(collection: Any) -> Expr:
    return make_node(OpId.MAX, (to_node(collection),))


@frontend_entry
@beartype
def op_empty_list(elem_type: Any) -> Expr:
    "Create empty list value"
    return make_node(OpId.LIST_EMPTY, type_val=UNRESOLVED_TYPES.resolve(list[elem_type]))


@frontend_entry
@beartype
def op_empty_map(key_type: Any, value_type: Any) -> Expr:
    "Create empty map value"
    return make_node(
        OpId.MAP_EMPTY, type_val=UNRESOLVED_TYPES.resolve(dict[key_type, value_type])
    )


@frontend_entry
@beartype
def op_format(fmt: str, *args: Any) -> Expr:
    """F-string formatting"""
    specs = parse_format(fmt).get_specs()
    if len(specs) != len(args):
        raise ValueError(
            f"Format string {fmt!r} has {len(specs)} directive(s) ({', '.join(str(s) for s in specs) or 'none'}) but {len(args)} argument(s) were given"
        )
    return make_node(OpId.STR_FORMAT, tuple(to_node(a) for a in args), str_val=fmt)


@frontend_entry
@beartype
def op_path_of(value: Any) -> Expr:
    """
    Return the path of the provided expression in the root object.
    """
    return make_node(OpId.PATH_OF, (to_node(value),))


@frontend_entry
@beartype
def op_typeof(value: Any) -> Expr:
    """Name of the concrete runtime type of the value, the most derived record type for records."""
    return make_node(OpId.TYPE_OF, (to_node(value),))


@frontend_entry
@beartype
def type_case(match_type: Any, name: str, body: Any) -> Expr:
    """
    Branch of `type_cond`, the binder receives the subject narrowed to the matched type.

    The first argument provided is a type expression that is going to be matched
    against the input, then the new bound variable and then the expression to evaluate
    in case the binding is successful.
    """
    check_binder_name(name, "type_case")
    return make_node(
        OpId.TYPE_CASE, (to_node(body),), binders=(name,), type_val=type_arg(match_type)
    )


@frontend_entry
@beartype
def type_cond(subject: Any, *cases: Expr, unhandled_ignore: bool = False) -> Expr:
    """
    `cond`, but for the type matching. Evaluate multiple `type_case` branches and evaluate
    the final result.

    First matching branch wins; with `unhandled_ignore` the result is optional and unmatched values give none.
    """
    if len(cases) == 0:
        raise ValueError("type_cond requires at least one type_case(...) branch")
    for case in cases:
        if case.node.op != OpId.TYPE_CASE:
            raise TypeError(
                f"type_cond branches must be type_case(...) expressions, got '{case.node.op.value}' built at {case.node.loc.render()}"
            )
    return make_node(
        OpId.TYPE_COND,
        (to_node(subject),) + tuple(c.node for c in cases),
        bool_val=unhandled_ignore,
    )
