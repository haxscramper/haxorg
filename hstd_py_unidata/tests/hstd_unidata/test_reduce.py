import pytest
import test_example_dia as test_example_dia
from beartype.typing import List
from hstd_py_unidata.model_dsl import __check__, get_dsl_model, op_all
from hstd_py_unidata.model_eval import errors_only
from hstd_py_unidata.model_reduce import ReductionInputError
from hstd_py_unidata.model_value import ListValue, RecordValue, ScalarValue, Value


def make_model():
    M = get_dsl_model("test.reduce")

    class Numbers(M.Class):
        values: List[int]

        __check__(
            cond=op_all(M.This["values"], "v", M.Iter("v") < 100), message="below 100"
        )

    return M, Numbers


def has_large(value: Value) -> bool:
    assert isinstance(value, RecordValue)
    items = value.fields["values"]
    assert isinstance(items, ListValue)
    return any(isinstance(i, ScalarValue) and 10 <= i.value for i in items.items)


def test_reduces_to_minimal_valid_value() -> None:
    M, Numbers = make_model()
    value = M.decode(Numbers, {"values": [3, 57, -8, 12, 99]})
    result = M.reduce(Numbers, value, has_large)
    assert M.encode(Numbers, result.value) == {"values": [10]}
    assert result.size_after < result.size_before
    assert not result.exhausted


def test_rejects_invalid_input() -> None:
    M, Numbers = make_model()
    with pytest.raises(ReductionInputError, match="below 100"):
        M.reduce(Numbers, M.decode(Numbers, {"values": [150]}), has_large)


def test_rejects_input_failing_the_predicate() -> None:
    M, Numbers = make_model()
    with pytest.raises(
        ReductionInputError, match="predicate rejects the initial value"
    ):
        M.reduce(Numbers, M.decode(Numbers, {"values": [1]}), has_large)


def test_reduced_diagram_stays_valid() -> None:
    diagram = next(
        d
        for d in map(test_example_dia.generate_diagram, range(100))
        if test_example_dia.has_weighted_edge(d)
    )
    seen: List[Value] = []

    def predicate(value: Value) -> bool:
        seen.append(value)
        return test_example_dia.has_weighted_edge(value)

    result = test_example_dia.M.reduce(test_example_dia.Diagram, diagram, predicate)
    assert test_example_dia.has_weighted_edge(result.value)
    assert all(
        errors_only(test_example_dia.M.validate(test_example_dia.Diagram, v)) == []
        for v in seen
    )
    assert result.size_after < result.size_before
