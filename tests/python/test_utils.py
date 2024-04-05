import py_scriptutils.json_utils as ju
from jsonpath_ng import Root, Fields, Index
from beartype.typing import Any, List

def get_diff(source: Any, target: Any) -> List[ju.DiffItem]:
    res = ju.json_diff(source=source, target=target)

    for it in res:
        ju.describe_diff(it, expected=target, converted=source)

    return res

def test_no_difference():
    res = get_diff([], [])
    assert len(res) == 0, res

def test_one_extra_element():
    res = get_diff([], [1])
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Add
    assert res[0].value == 1

def test_one_removed_element():
    res = get_diff([1], [])
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Remove
    assert res[0].path == Root().child(Index(0))

def test_type_mismatch():
    res = get_diff({}, [])
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Replace
    assert res[0].path == Root()

def test_nested_structure_addition():
    res = get_diff({"a": {"b": 1}}, {"a": {"b": 1, "c": 2}})
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Add
    assert res[0].path == Root().child(Fields("a")).child(Fields("c"))
    assert res[0].value == 2

def test_nested_structure_removal():
    res = get_diff({"a": {"b": 1, "c": 2}}, {"a": {"b": 1}})
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Remove
    assert res[0].path == Root().child(Fields("a")).child(Fields("c"))

def test_simple_value_change():
    res = get_diff({"a": 1}, {"a": 2})
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Replace
    assert res[0].path == Root().child(Fields("a"))
    assert res[0].value == 2

def test_array_element_change():
    res = get_diff([1, 2, 3], [1, 4, 3])
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Replace
    assert res[0].path == Root().child(Index(1))
    assert res[0].value == 4

def test_addition_and_removal():
    res = get_diff([1, 2], [2, 3])
    assert len(res) == 2, res
    ops = set([item.op for item in res])
    assert ju.Op.Replace in ops, res
    assert ju.Op.Add not in ops, res
    assert ju.Op.Remove not in ops, res

def test_expected_subset_no_difference():
    res = ju.get_subset_diff([1], [])
    assert len(res) == 0, res

def test_expected_subset_missing_item():
    res = ju.get_subset_diff([1, 2], [1, 2, 3])
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Remove
