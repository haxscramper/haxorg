import shutil

import pytest
from beartype.typing import List
from hstd_py_unidata.model_diagnostics import DiagCode, DslTypeError
from hstd_py_unidata.model_dsl import (
    Int8,
    __check__,
    __variant__,
    get_dsl_model,
    op_filter_map,
    op_map,
    op_walk,
    type_case,
    type_cond,
)

pytestmark = pytest.mark.skipif(
    shutil.which("souffle") is None, reason="souffle is not installed"
)


def test_valid_model_passes() -> None:
    M = get_dsl_model("test.tc.valid")

    class Item(M.Class):
        name: str
        size: Int8

        __check__(
            cond=0.5 < M.This["size"],
            message="numeric widening allows float and int8 operands",
        )

    class Box(M.Class):
        items: List[Item]

        __check__(
            cond=op_map(M.This["items"], "item", M.Iter("item")["name"])._List.contains(
                "lid"
            ),
            message="needs a lid",
        )

    M.type_check()


def test_unknown_field_lists_available_fields() -> None:
    M = get_dsl_model("test.tc.field")

    class Item(M.Class):
        name: str
        size: int

        __check__(cond=M.This["sise"] < 3, message="typo")

    diags = M.type_check_diagnostics()
    assert [d.code for d in diags] == [DiagCode.UNKNOWN_FIELD]
    assert "available fields: name, size" in diags[0].message
    assert "lt" in diags[0].notes[0]


def test_types_are_per_occurrence() -> None:
    M = get_dsl_model("test.tc.occurrence")
    shared = M.This["items"]._List.size() <= 3

    class Listy(M.Class):
        items: List[int]

        __check__(cond=shared, message="too many")

    class Stringy(M.Class):
        items: str

        __check__(cond=shared, message="too many")

    diags = M.type_check_diagnostics()
    assert len(diags) == 1
    assert diags[0].code == DiagCode.ARG_CLASS
    assert diags[0].record.name == "Stringy"
    assert "must be a list" in diags[0].message


def test_map_preserves_result_type() -> None:
    M = get_dsl_model("test.tc.map")

    class Item(M.Class):
        name: str

    class Box(M.Class):
        items: List[Item]

        __check__(
            cond=op_map(M.This["items"], "item", M.Iter("item")["name"]),
            message="not a bool",
        )

    with pytest.raises(DslTypeError) as err:
        M.type_check()
    assert err.value.diagnostics[0].code == DiagCode.ROOT_TYPE
    assert "has type 'list<string>'" in err.value.diagnostics[0].message


def test_invalid_case_tag_lists_tags() -> None:
    M = get_dsl_model("test.tc.case")

    class Shape(M.Class):
        class Circle(M.Case):
            radius: int

        class Square(M.Case):
            side: int

        __variant__(Circle, Square)
        __check__(cond=M.This["data"]._Case.is_case("Triangle"), message="no triangles")

    diags = M.type_check_diagnostics()
    assert [d.code for d in diags] == [DiagCode.INVALID_CASE_TAG]
    assert "expected one of: Circle, Square" in diags[0].message


def test_unreachable_type_case() -> None:
    M = get_dsl_model("test.tc.reach")

    class Leaf(M.Class):
        value: int

    class Other(M.Class):
        value: int

    class Tree(M.Class):
        leaves: List[Leaf]

        __check__(
            cond=op_filter_map(
                op_walk(M.This),
                "any",
                type_cond(
                    M.Iter("any"),
                    type_case(Other, "other", M.Iter("other")["value"] < 3),
                    unhandled_ignore=True,
                ),
            )._List.size()
            == 0,
            message="no others",
        )

    diags = M.type_check_diagnostics()
    assert [d.code for d in diags] == [DiagCode.UNREACHABLE_TYPE_CASE]
    assert "Leaf" in diags[0].message
