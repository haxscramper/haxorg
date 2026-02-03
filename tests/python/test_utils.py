from beartype.typing import Any
from beartype.typing import List
from jsonpath_ng import Fields
from jsonpath_ng import Index
from jsonpath_ng import Root
import py_scriptutils.json_utils as ju


def get_diff(source: Any, target: Any) -> List[ju.DiffItem]:
    res = ju.json_diff(source=source, target=target)

    for it in res:
        ju.describe_diff(it, target=target, source=source)

    return res


def test_no_difference() -> None:
    res = get_diff([], [])
    assert len(res) == 0, res


def test_one_extra_element() -> None:
    res = get_diff([], [1])
    assert len(res) == 1, res
    assert res[0].op == ju.Op.AppendItem
    assert res[0].value == 1


def test_one_removed_element() -> None:
    res = get_diff([1], [])
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Remove
    assert res[0].path == Root().child(Index(0))


def test_type_mismatch() -> None:
    res = get_diff({}, [])
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Replace
    assert res[0].path == Root()


def test_nested_structure_addition() -> None:
    res = get_diff({"a": {"b": 1}}, {"a": {"b": 1, "c": 2}})
    assert len(res) == 1, res
    assert res[0].op == ju.Op.AddField
    assert res[0].path == Root().child(Fields("a")).child(Fields("c"))
    assert res[0].value == 2


def test_nested_structure_removal() -> None:
    res = get_diff({"a": {"b": 1, "c": 2}}, {"a": {"b": 1}})
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Remove
    assert res[0].path == Root().child(Fields("a")).child(Fields("c"))


def test_simple_value_change() -> None:
    res = get_diff({"a": 1}, {"a": 2})
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Replace
    assert res[0].path == Root().child(Fields("a"))
    assert res[0].value == 2


def test_array_element_change() -> None:
    res = get_diff([1, 2, 3], [1, 4, 3])
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Replace
    assert res[0].path == Root().child(Index(1))
    assert res[0].value == 4


def test_addition_and_removal() -> None:
    res = get_diff([1, 2], [2, 3])
    assert len(res) == 2, res
    ops = set([item.op for item in res])
    assert ju.Op.Replace in ops, res
    assert ju.Op.AppendItem not in ops, res
    assert ju.Op.Remove not in ops, res


def test_expected_subset_list_removed() -> None:
    res = ju.get_subset_diff([1], [])
    assert len(res) == 1, res


def test_expected_subset_missing_item() -> None:
    res = ju.get_subset_diff([1, 2], [1, 2, 3])
    assert len(res) == 1, res
    assert res[0].op == ju.Op.Remove


def test_subset_assert() -> None:
    ju.assert_subset([3], [3])
    ju.assert_subset([{"a": "b", "c": "d"}], [{"a": "b"}])
