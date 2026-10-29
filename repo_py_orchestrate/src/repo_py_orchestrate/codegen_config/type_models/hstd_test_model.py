import enum

from beartype import beartype
from beartype.typing import Optional
from hstd_py_unidata.model_dsl import __check__, get_dsl_model
from hstd_py_unidata.model_expr import (
    Expr,
    op_all,
    op_and,
    op_concat,
    op_cond,
    op_empty_list,
    op_empty_map,
    op_exists,
    op_exists_one,
    op_filter,
    op_filter_map,
    op_fold,
    op_format,
    op_group_by,
    op_let,
    op_map,
    op_max,
    op_min,
    op_or,
    op_path_of,
    op_sum,
    op_take_while,
    op_typeof,
    op_walk,
    type_case,
    type_cond,
)

M = get_dsl_model("hstd.unidata_dsl.test")


class TrivialText(M.Class):
    text: str = M.Field(
        check=0 < M.This._Str.size(),
        message="text must not be empty",
    )


class Status(M.Enum):
    Ready: int = 0
    Other: int = 1


class CheckKind(M.Enum):
    Eq: int = enum.auto()
    Ne: int = enum.auto()
    Lt: int = enum.auto()
    Le: int = enum.auto()
    Add: int = enum.auto()
    Sub: int = enum.auto()
    Mul: int = enum.auto()
    Div: int = enum.auto()
    ConstFloat: int = enum.auto()
    ConstBool: int = enum.auto()
    And: int = enum.auto()
    Or: int = enum.auto()
    Not: int = enum.auto()
    Cond: int = enum.auto()
    CondLazy: int = enum.auto()
    Let: int = enum.auto()
    All: int = enum.auto()
    Exists: int = enum.auto()
    ExistsOne: int = enum.auto()
    Map: int = enum.auto()
    Filter: int = enum.auto()
    FilterMap: int = enum.auto()
    TakeWhile: int = enum.auto()
    GroupBy: int = enum.auto()
    Fold: int = enum.auto()
    Walk: int = enum.auto()
    Sum: int = enum.auto()
    Min: int = enum.auto()
    Max: int = enum.auto()
    StrSize: int = enum.auto()
    StrMatches: int = enum.auto()
    StrFormat: int = enum.auto()
    ListSize: int = enum.auto()
    ListContains: int = enum.auto()
    ListAt: int = enum.auto()
    ListSlice: int = enum.auto()
    ListSliceBounds: int = enum.auto()
    ListConcat: int = enum.auto()
    ListEmpty: int = enum.auto()
    MapSize: int = enum.auto()
    MapContains: int = enum.auto()
    MapGet: int = enum.auto()
    MapInsert: int = enum.auto()
    MapReplace: int = enum.auto()
    MapKeys: int = enum.auto()
    MapValues: int = enum.auto()
    MapEmpty: int = enum.auto()
    OptHasValue: int = enum.auto()
    OptValue: int = enum.auto()
    CaseIs: int = enum.auto()
    CaseWhich: int = enum.auto()
    CaseField: int = enum.auto()
    EnumIs: int = enum.auto()
    NthGet: int = enum.auto()
    IsDerived: int = enum.auto()
    TypeCond: int = enum.auto()
    TypeCondOptional: int = enum.auto()
    TypeOf: int = enum.auto()
    PathOf: int = enum.auto()
    EmptyCollections: int = enum.auto()


class Base(M.Class):
    id: int

    __check__(
        id="base-positive-id",
        cond=0 < M.This["id"],
        message="base id must be positive",
    )


class Derived(Base):
    weight: int

    __check__(
        id="derived-positive-weight",
        cond=0 < M.This["weight"],
        message="derived weight must be positive",
    )


class Choice(M.Class):
    class First(M.Case):
        value: int

    class Second(M.Case):
        label: str

    __variant__(First, Second, field="data", kind="Kind")


@beartype
def selected(kind: str, condition: Expr) -> Expr:
    return op_or(
        ~M.This["operation"]._Enum.is_val(kind),
        condition,
    )


@beartype
def derived_ids(root: Expr) -> Expr:
    return op_filter_map(
        op_walk(root),
        "walk_value",
        type_cond(
            M.Iter("walk_value"),
            type_case(
                M._T["Derived"],
                "derived",
                M.Iter("derived")["id"],
            ),
            unhandled_ignore=True,
        ),
    )


class OperationChecks(M.Class):
    operation: CheckKind
    number: int
    real: float
    flag: bool
    text: str
    numbers: list[int]
    optionals: list[Optional[int]]
    mapping: dict[str, int]
    optional: Optional[int]
    coords: tuple[int, str]
    status: Status
    base: Base
    derived: Derived
    choice: Choice

    for check_name, condition in (
        ("Eq", M.This["number"] == 6),
        ("Ne", M.This["number"] != 8),
        ("Lt", M.This["number"] < 7),
        ("Le", M.This["number"] <= 6),
        ("Add", M.This["number"] + 3 == 9),
        ("Sub", M.This["number"] - 3 == 3),
        ("Mul", M.This["number"] * 3 == 18),
        ("Div", M.This["number"] / 3 == 2),
        (
            "ConstFloat",
            op_and(
                M.This["real"] == 2.5,
                M.This["real"] / 2.0 == 1.25,
                M.This["real"] * 2.0 == 5.0,
                M.This["real"] - 0.5 == 2.0,
                M.This["real"] + 0.5 == 3.0,
            ),
        ),
        ("ConstBool", M.This["flag"] == True),
        (
            "And",
            op_and(
                M.This["flag"],
                M.This["number"] == 6,
                M.This["mapping"]._Map.get("a") == 1,
            ),
        ),
        (
            "Or",
            op_or(
                False,
                M.This["number"] == 6,
                M.This["mapping"]._Map.get("a") == 99,
            ),
        ),
        ("Not", ~(M.This["number"] != 6)),
        (
            "Cond",
            op_cond(
                (M.This["number"] == 6, M.This["text"]),
                default=op_format("other-%d", M.This["number"]),
            )
            == "six",
        ),
        (
            "CondLazy",
            op_cond(
                (M.This["flag"], M.This["mapping"]._Map.get("a")),
                default=M.This["mapping"]._Map.get("absent"),
            )
            == 1,
        ),
        # TODO: Fixme: the error and semantics are unclear here, fails
        # with binder shadowing error.
        # (
        #     "Let",
        #     op_let(
        #         "bound",
        #         M.This["number"],
        #         op_let(
        #             "bound",
        #             M.Iter("bound") + 1,
        #             M.Iter("bound"),
        #         ),
        #     )
        #     == 7,
        # ),
        (
            "All",
            op_all(
                M.This["numbers"],
                "number",
                M.Iter("number") < 4,
            ),
        ),
        (
            "Exists",
            op_exists(
                M.This["numbers"],
                "number",
                M.Iter("number") == 3,
            ),
        ),
        (
            "ExistsOne",
            op_exists_one(
                M.This["numbers"],
                "number",
                M.Iter("number") == 3,
            ),
        ),
        (
            "Map",
            op_map(
                M.This["numbers"],
                "number",
                M.Iter("number") * 2,
            )._List.at(2)
            == 6,
        ),
        (
            "Filter",
            op_filter(
                M.This["numbers"],
                "number",
                1 < M.Iter("number"),
            )._List.size()
            == 2,
        ),
        (
            "FilterMap",
            op_let(
                "present",
                op_filter_map(
                    M.This["optionals"],
                    "optional",
                    M.Iter("optional"),
                ),
                op_and(
                    M.Iter("present")._List.size() == 2,
                    M.Iter("present")._List.at(0) == 1,
                    M.Iter("present")._List.at(1) == 3,
                ),
            ),
        ),
        (
            "TakeWhile",
            op_take_while(
                M.This["numbers"],
                "number",
                M.Iter("number") < 3,
            )._List.size()
            == 2,
        ),
        (
            "GroupBy",
            op_let(
                "groups",
                op_group_by(
                    M.This["numbers"],
                    "number",
                    M.Iter("number") < 3,
                ),
                op_and(
                    M.Iter("groups")._Map.size() == 2,
                    M.Iter("groups")._Map.values()._List.at(0)._List.at(0)
                    == M.This["numbers"]._List.at(0),
                ),
            ),
        ),
        (
            "Fold",
            op_fold(
                M.This["numbers"],
                0,
                "acc",
                "number",
                M.Iter("acc") + M.Iter("number"),
            )
            == 6,
        ),
        (
            "Walk",
            op_let(
                "ids",
                derived_ids(M.This["derived"]),
                op_and(
                    M.Iter("ids")._List.size() == 1,
                    M.Iter("ids")._List.at(0) == 6,
                ),
            ),
        ),
        ("Sum", op_sum(M.This["numbers"]) == 6),
        ("Min", op_min(M.This["numbers"]) == 1),
        ("Max", op_max(M.This["numbers"]) == 3),
        ("StrSize", M.This["text"]._Str.size() == 3),
        ("StrMatches", M.This["text"]._Str.matches("^s[a-z]{2}$")),
        (
            "StrFormat",
            op_format("%s:%d", M.This["text"], M.This["number"]) == "six:6",
        ),
        ("ListSize", M.This["numbers"]._List.size() == 3),
        ("ListContains", M.This["numbers"]._List.contains(3)),
        ("ListAt", M.This["numbers"]._List.at(2) == 3),
        (
            "ListSlice",
            op_let(
                "slice",
                M.This["numbers"]._List.slice(1, 3),
                op_and(
                    M.Iter("slice")._List.size() == 2,
                    M.Iter("slice")._List.at(0) == 2,
                    M.Iter("slice")._List.at(1) == 3,
                ),
            ),
        ),
        (
            "ListSliceBounds",
            op_let(
                "slice",
                M.This["numbers"]._List.slice(-2, 100),
                op_and(
                    M.Iter("slice")._List.size() == 2,
                    M.Iter("slice")._List.at(0) == 2,
                    M.Iter("slice")._List.at(1) == 3,
                ),
            ),
        ),
        (
            "ListConcat",
            op_let(
                "joined",
                op_concat(M.This["numbers"], M.This["numbers"]),
                op_and(
                    M.Iter("joined")._List.size() == 6,
                    M.Iter("joined")._List.at(3) == M.This["numbers"]._List.at(0),
                ),
            ),
        ),
        ("ListEmpty", op_empty_list(int)._List.size() == 0),
        ("MapSize", M.This["mapping"]._Map.size() == 2),
        ("MapContains", M.This["mapping"]._Map.contains("a")),
        ("MapGet", M.This["mapping"]._Map.get("a") == 1),
        (
            "MapInsert",
            op_let(
                "updated",
                M.This["mapping"]._Map.insert("c", 3),
                op_and(
                    M.Iter("updated")._Map.size() == 3,
                    M.Iter("updated")._Map.get("c") == 3,
                    ~M.This["mapping"]._Map.contains("c"),
                ),
            ),
        ),
        (
            "MapReplace",
            op_let(
                "updated",
                M.This["mapping"]._Map.insert("a", 9),
                op_and(
                    M.Iter("updated")._Map.size() == M.This["mapping"]._Map.size(),
                    M.Iter("updated")._Map.get("a") == 9,
                    M.This["mapping"]._Map.get("a") == 1,
                ),
            ),
        ),
        (
            "MapKeys",
            op_let(
                "keys",
                M.This["mapping"]._Map.keys(),
                op_and(
                    M.Iter("keys")._List.size() == 2,
                    M.Iter("keys")._List.contains("a"),
                    M.Iter("keys")._List.contains("b"),
                ),
            ),
        ),
        (
            "MapValues",
            op_let(
                "values",
                M.This["mapping"]._Map.values(),
                op_and(
                    M.Iter("values")._List.size() == 2,
                    M.Iter("values")._List.contains(1),
                    M.Iter("values")._List.contains(2),
                ),
            ),
        ),
        ("MapEmpty", op_empty_map(str, int)._Map.size() == 0),
        ("OptHasValue", M.This["optional"]._Opt.has_value()),
        (
            "OptValue",
            op_and(
                M.This["optional"]._Opt.has_value(),
                M.This["optional"]._Opt.value() == 3,
            ),
        ),
        # FIXME: `.data` can be considered an internal implementation detail here
        # not really clear whether it should be exposed (for multi-variant objects
        # that effectively act as a `Variant*Variant` tuple)
        # or it should instead be hidden. Right now using `["choice"]` with
        # `.is_case` directly fails with typing error because the
        # OperationChecks.choice has a type of `Choice`
        ("CaseIs", M.This["choice"]["data"]._Case.is_case("First")),
        (
            "CaseWhich",
            M.This["choice"]["data"]._Case.which_case()._Enum.is_val("First"),
        ),
        (
            "CaseField",
            op_cond(
                (
                    M.This["choice"]["data"]._Case.is_case("First"),
                    M.This["choice"]["data"]["value"],
                ),
                default=-1,
            )
            == 6,
        ),
        ("EnumIs", M.This["status"]._Enum.is_val("Ready")),
        (
            "NthGet",
            op_and(
                M.This["coords"]._Nth.get(0) == 6,
                M.This["coords"]._Nth.get(1) == "six",
            ),
        ),
        (
            "IsDerived",
            op_and(
                M.This["derived"].is_derived_from(M._T["Base"]),
                ~M.This["base"].is_derived_from(M._T["Derived"]),
            ),
        ),
        (
            "TypeCond",
            type_cond(
                op_walk(M.This["derived"])._List.at(0),
                type_case(
                    M._T["Base"],
                    "record",
                    M.Iter("record")["id"],
                ),
                type_case(
                    M._T["Derived"],
                    "record",
                    -1,
                ),
            )
            == 6,
        ),
        (
            "TypeCondOptional",
            op_and(
                ~type_cond(
                    op_walk(M.This["base"])._List.at(0),
                    type_case(
                        M._T["Derived"],
                        "record",
                        M.Iter("record")["id"],
                    ),
                    unhandled_ignore=True,
                )._Opt.has_value(),
                type_cond(
                    op_walk(M.This["derived"])._List.at(0),
                    type_case(
                        M._T["Derived"],
                        "record",
                        M.Iter("record")["id"],
                    ),
                    unhandled_ignore=True,
                )._Opt.value()
                == 6,
            ),
        ),
        (
            "TypeOf",
            type_cond(
                op_walk(M.This["derived"])._List.at(0),
                type_case(
                    M._T["Base"],
                    "record",
                    op_typeof(M.Iter("record")),
                ),
            )
            == "Derived",
        ),
        (
            "PathOf",
            op_and(
                op_format("%s", op_path_of(M.This["number"])) == "/number",
                op_map(
                    M.This["numbers"],
                    "number",
                    op_format("%s", op_path_of(M.Iter("number"))),
                )._List.at(0)
                == "/numbers/0",
                type_cond(
                    op_walk(M.This["derived"])._List.at(0),
                    type_case(
                        M._T["Base"],
                        "record",
                        op_format("%s", op_path_of(M.Iter("record"))),
                    ),
                )
                == "/derived",
            ),
        ),
        (
            "EmptyCollections",
            op_and(
                op_all(
                    op_empty_list(int),
                    "number",
                    0 < M.Iter("number"),
                ),
                ~op_exists(
                    op_empty_list(int),
                    "number",
                    0 < M.Iter("number"),
                ),
                ~op_exists_one(
                    op_empty_list(int),
                    "number",
                    0 < M.Iter("number"),
                ),
                op_sum(op_empty_list(int)) == 0,
                op_map(
                    op_empty_list(int),
                    "unused",
                    M.This["mapping"]._Map.get("absent"),
                )._List.size()
                == 0,
                op_filter(
                    op_empty_list(int),
                    "unused",
                    M.This["optional"]._Opt.value() == 0,
                )._List.size()
                == 0,
                op_filter_map(
                    op_empty_list(int),
                    "unused",
                    M.This["optional"],
                )._List.size()
                == 0,
                op_take_while(
                    op_empty_list(int),
                    "unused",
                    M.This["optional"]._Opt.value() == 0,
                )._List.size()
                == 0,
                op_group_by(
                    op_empty_list(int),
                    "unused",
                    M.This["mapping"]._Map.get("absent"),
                )._Map.size()
                == 0,
                op_fold(
                    op_empty_list(int),
                    9,
                    "acc",
                    "unused",
                    M.This["mapping"]._Map.get("absent"),
                )
                == 9,
                op_concat(
                    op_empty_list(int),
                    op_empty_list(int),
                )._List.size()
                == 0,
                op_cond(
                    (True, 42),
                    default=op_min(op_empty_list(int)),
                )
                == 42,
                op_cond(
                    (True, 42),
                    default=op_max(op_empty_list(int)),
                )
                == 42,
            ),
        ),
    ):
        __check__(
            id=f"poc.{check_name}",
            cond=selected(check_name, condition),
            message=f"poc.{check_name}",
        )

    del check_name, condition


class FieldChecks(M.Class):
    padding: int
    text: str = M.Field(
        check=0 < M.This._Str.size(),
        message=op_format("text length is %d", M.This._Str.size()),
    )
    numbers: list[int] = M.Field(
        check=op_all(M.This, "number", 0 < M.Iter("number")),
        message=op_format("values=%s", M.This),
    )


class MessageChecks(M.Class):
    number: int
    real: float
    flag: bool
    text: str
    numbers: list[int]
    details: dict[str, int]

    __check__(
        id="format-message",
        cond=M.This["number"] == 6,
        message=op_format(
            "n=%d real=%f sci=%e hex=%x oct=%o flag=%b text=%s list=%s lookup=%d %%",
            M.This["number"],
            M.This["real"],
            M.This["real"],
            M.This["number"],
            M.This["number"],
            M.This["flag"],
            M.This["text"],
            M.This["numbers"],
            M.This["details"]._Map.get("detail"),
        ),
    )


class Node(M.Class):
    id: str


class Edge(M.Class):
    source: str
    target: str


@beartype
def elements_of(root: Expr, type_name: str, binder: str) -> Expr:
    return op_filter_map(
        op_walk(root),
        f"{binder}_any",
        type_cond(
            M.Iter(f"{binder}_any"),
            type_case(M._T[type_name], binder, M.Iter(binder)),
            unhandled_ignore=True,
        ),
    )


@beartype
def node_ids(root: Expr) -> Expr:
    return op_map(
        elements_of(root, "Node", "node"),
        "node",
        M.Iter("node")["id"],
    )


@beartype
def endpoints_known(ids: Expr, edge: Expr) -> Expr:
    return op_and(
        ids._List.contains(edge["source"]),
        ids._List.contains(edge["target"]),
    )


@beartype
def grouped_nodes(root: Expr) -> Expr:
    return op_group_by(
        elements_of(root, "Node", "node"),
        "node",
        M.Iter("node")["id"],
    )._Map.values()


@beartype
def duplicate_groups(root: Expr) -> Expr:
    return op_filter(
        grouped_nodes(root),
        "group",
        1 < M.Iter("group")._List.size(),
    )


class Graph(M.Class):
    nodes: list[Node]
    edges: list[Edge]

    __check__(
        id="graph-unique-node-ids",
        cond=op_all(
            grouped_nodes(M.This),
            "group",
            M.Iter("group")._List.size() <= 1,
        ),
        message=op_format(
            "duplicate node ids at %s",
            op_map(
                duplicate_groups(M.This),
                "group",
                op_map(
                    M.Iter("group"),
                    "node",
                    op_path_of(M.Iter("node")),
                ),
            ),
        ),
    )

    __check__(
        id="graph-no-dangling-edges",
        cond=op_let(
            "ids",
            node_ids(M.This),
            op_all(
                M.This["edges"],
                "edge",
                endpoints_known(M.Iter("ids"), M.Iter("edge")),
            ),
        ),
        message=op_let(
            "ids",
            node_ids(M.This),
            op_format(
                "dangling edges at %s",
                op_map(
                    op_filter(
                        M.This["edges"],
                        "edge",
                        ~endpoints_known(M.Iter("ids"), M.Iter("edge")),
                    ),
                    "edge",
                    op_path_of(M.Iter("edge")),
                ),
            ),
        ),
    )
