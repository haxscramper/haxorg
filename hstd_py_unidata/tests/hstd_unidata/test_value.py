import pytest
from beartype.typing import Dict, List, Optional
from hstd_py_unidata.model_dsl import Int8, __variant__, get_dsl_model
from hstd_py_unidata.model_value import RecordValue, ValueDecodeError, value_size


def make_model():
    M = get_dsl_model("test.value")

    class Base(M.Class):
        name: str = "unnamed"

    class Derived(Base, M.Class):
        extra: Int8

    class Shape(M.Class):
        class Circle(M.Case):
            radius: int

        class Square(M.Case):
            side: int

        __variant__(Circle, Square)

    class Holder(M.Class):
        items: List[Base]
        shape: Shape
        pairs: Dict[int, str]
        note: Optional[str] = None

    return M, Base, Derived, Holder


def test_round_trip_with_polymorphic_slot_variant_and_map() -> None:
    M, Base, Derived, Holder = make_model()
    data = {
        "items": [{"name": "a"}, {"$type": "Derived", "name": "b", "extra": 3}],
        "shape": {"data": {"kind": "Square", "value": {"side": 2}}},
        "pairs": [[1, "one"], [2, "two"]],
        "note": None,
    }
    value = M.decode(Holder, data)
    assert isinstance(value, RecordValue)
    assert M.encode(Holder, value) == data


def test_trivial_and_explicit_defaults() -> None:
    M, Base, Derived, Holder = make_model()
    value = M.decode(Derived, {})
    assert M.encode(Derived, value) == {"name": "unnamed", "extra": 0}
    holder = M.encode(Holder, M.decode(Holder, {}))
    assert holder["shape"] == {"data": {"kind": "Circle", "value": {"radius": 0}}}
    assert holder["note"] is None


def test_decode_errors_name_path_and_expected_values() -> None:
    M, Base, Derived, Holder = make_model()
    with pytest.raises(
        ValueDecodeError,
        match=r"\$\.items\[0\]\.extra: integer 300 is out of range for type 'int8', expected -128 <= value <= 127",
    ):
        M.decode(Holder, {"items": [{"$type": "Derived", "extra": 300}]})
    with pytest.raises(ValueDecodeError, match="available fields: name"):
        M.decode(Base, {"nmae": "x"})
    with pytest.raises(ValueDecodeError, match="expected one of: Base, Derived"):
        M.decode(Base, {"$type": "Holder"})


def test_value_size_orders_by_nodes_then_magnitude() -> None:
    M, Base, Derived, Holder = make_model()
    small = M.decode(Derived, {"extra": 1})
    large = M.decode(Derived, {"extra": 100})
    assert value_size(M.index, small) < value_size(M.index, large)
    assert value_size(M.index, M.decode(Holder, {})) < value_size(
        M.index, M.decode(Holder, {"items": [{}]})
    )
