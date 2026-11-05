import pytest
from beartype.typing import Dict, List, Optional
from hstd_py_unidata.model_dsl import (
    __check__,
    get_dsl_model,
    op_all,
    op_filter,
    op_format,
    op_group_by,
    op_map,
    op_not,
    op_or,
    op_path_of,
)
from hstd_py_unidata.model_ops import EvalError


def test_short_circuit_guards_empty_optional() -> None:
    M = get_dsl_model("test.eval.guard")

    class Column(M.Class):
        width: Optional[int] = None

        __check__(
            cond=op_or(
                op_not(M.This["width"]._Opt.has_value()),
                0 < M.This["width"]._Opt.value(),
            ),
            message="positive width",
        )

    assert M.validate(Column, M.decode(Column, {})) == []
    failures = M.validate(Column, M.decode(Column, {"width": -1}))
    assert [f.message for f in failures] == ["positive width"]


def test_invalid_operation_terminates_with_location() -> None:
    M = get_dsl_model("test.eval.crash")

    class Column(M.Class):
        width: Optional[int] = None

        __check__(cond=0 < M.This["width"]._Opt.value(), message="positive width")

    with pytest.raises(EvalError, match=r"opt_value.*\$\.width"):
        M.validate(Column, M.decode(Column, {}))


def test_division_by_zero_is_an_evaluation_error() -> None:
    M = get_dsl_model("test.eval.div")

    class Ratio(M.Class):
        num: int
        den: int

        __check__(cond=M.This["num"] / M.This["den"] < 10, message="ratio")

    with pytest.raises(EvalError, match="division by zero"):
        M.validate(Ratio, M.decode(Ratio, {"num": 1, "den": 0}))


def test_message_formats_paths_of_duplicates() -> None:
    M = get_dsl_model("test.eval.group")

    class Item(M.Class):
        id: str

    class Bag(M.Class):
        items: List[Item]

        __check__(
            id="unique",
            cond=op_all(
                op_group_by(M.This["items"], "item", M.Iter("item")["id"])._Map.values(),
                "group",
                M.Iter("group")._List.size() <= 1,
            ),
            message=op_format(
                "duplicate ids at {}",
                op_map(
                    op_filter(
                        op_group_by(
                            M.This["items"], "item", M.Iter("item")["id"]
                        )._Map.values(),
                        "dup",
                        1 < M.Iter("dup")._List.size(),
                    ),
                    "dup_group",
                    op_map(
                        M.Iter("dup_group"), "dup_item", op_path_of(M.Iter("dup_item"))
                    ),
                ),
            ),
        )

    value = M.decode(Bag, {"items": [{"id": "a"}, {"id": "b"}, {"id": "a"}]})
    failures = M.validate(Bag, value)
    # The formatting uses `""` to wrap the messages because the format
    # operation received the nested list of strings. If quote is not necessary,
    # the formatting should assemble the string as required by interpolating
    # individual list elements.
    assert [f.message for f in failures] == [
        'duplicate ids at [["$.items[0]", "$.items[2]"]]'
    ]


def test_map_insert_overwrites_structurally_equal_key() -> None:
    M = get_dsl_model("test.eval.map")

    class Counts(M.Class):
        counts: Dict[str, int]

        __check__(
            cond=M.This["counts"]._Map.insert("a", 5)._Map.size() == 1,
            message="insert overwrites",
        )

    assert M.validate(Counts, M.decode(Counts, {"counts": {"a": 1}})) == []
