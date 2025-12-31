from dataclasses import dataclass, field
from beartype.typing import Callable, List, Any, Dict, Union, Optional, Tuple
from enum import Enum, auto
import json
from jsonpath_ng import jsonpath, DatumInContext, Index, Fields
import copy
from beartype import beartype

Json = Union[str, int, float, None, Dict, List, Tuple]


class Op(Enum):
    Replace = auto()
    Remove = auto()
    AddField = auto()
    AppendItem = auto()


@beartype
@dataclass
class DiffItem:
    op: Op
    path: jsonpath.JSONPath
    value: Json = field(default=None)


@beartype
def json_diff(
    source: Json,
    target: Json,
    path: jsonpath.JSONPath = jsonpath.Root(),
    ignore: Callable[[Json], bool] = lambda x: False,
) -> List[DiffItem]:
    result: List[DiffItem] = []

    if ignore(target):
        return result
    if source == target:
        return result

    if type(source) != type(target):
        result.append(DiffItem(Op.Replace, path, target))
        return result

    if isinstance(source, (list, tuple)):
        i = 0
        assert isinstance(target, (list, tuple))
        while i < len(source) and i < len(target):
            assert isinstance(i, int), f"{type(i)} {i}"
            temp_diff = json_diff(source[i], target[i], path.child(Index(i)), ignore)
            result.extend(temp_diff)
            i += 1

        end_index = len(result)
        while i < len(source):
            assert isinstance(i, int), f"{type(i)} {i}"
            result.insert(end_index, DiffItem(Op.Remove, path.child(Index(i))))
            i += 1

        while i < len(target):
            assert isinstance(i, int), f"{type(i)} {i}"
            result.append(DiffItem(Op.AppendItem, path.child(Index(i)), target[i]))
            i += 1

        assert i == max(len(target), len(source))

    elif isinstance(source, dict):
        assert isinstance(target, dict)
        for key in source:
            assert isinstance(key, str), f"{type(key)} {key}"
            if key in target:
                temp_diff = json_diff(source[key], target[key], path.child(Fields(key)),
                                      ignore)
                result.extend(temp_diff)

            else:
                result.append(DiffItem(Op.Remove, path.child(Fields(key))))

        for key in target:
            if key not in source:
                assert isinstance(key, str), f"{type(key)} {key}"
                result.append(DiffItem(Op.AddField, path.child(Fields(key)), target[key]))

    else:
        result.append(DiffItem(Op.Replace, path, target))

    return result


@beartype
def get_subset_diff(main_set: Json, expected_subset: Json) -> List[DiffItem]:
    """
    Get list of elements removed from expected subset of changed in expected subset. 
    """

    # If some element from expect *sub*set was added, it is an expected behavior. All other operations
    # are returned.
    return [
        it for it in json_diff(source=expected_subset, target=main_set)
        if it.op != Op.AddField
    ]


@beartype
def describe_diff(
    it: DiffItem,
    source: Json,
    target: Json,
    source_name: str = "source",
    target_name: str = "target",
) -> str:
    description = "  "
    path = it.path

    if it.op == Op.Remove:
        description += f"{source_name} has extra entry"

    elif it.op == Op.AddField:
        description += f"{target_name} missing field"

    elif it.op == Op.AppendItem:
        description += f"{target_name} missing list item"

    elif it.op == Op.Replace:
        description += "changed entry"

    description += f" on path '{path}' "

    def get_path(value: Json) -> Json:
        value_: DatumInContext = [item for item in path.find(value)][0]
        return value_.value

    if it.op == Op.Remove:
        description += f"    {json.dumps(get_path(source), indent=2)}"

    elif it.op == Op.AddField:
        description += f"    {json.dumps(it.value, indent=2)}"

    elif it.op == Op.AppendItem:
        description += f"    {json.dumps(it.value, indent=2)}"

    elif it.op == Op.Replace:
        target_object = get_path(target)
        source_object = get_path(source)
        target_val = json.dumps(target_object)
        if 40 < len(target_val):
            target_val = json.dumps(target_object, indent=2)

        source_val = json.dumps(source_object)
        if 40 < len(source_val):
            source_val = json.dumps(source_object, indent=2)

        if type(target_object) != type(source_object):
            description += f"type mismatch: {type(target_object).__name__} != {type(source_object).__name__} "

        if 40 < len(target_val) or 40 < len(source_val):
            description += "\n"
            description += "    from " + target_val + "\n"
            description += "    to   " + source_val

        else:
            description += f"    from {target_val} ({target_name}) to {source_val} ({source_name})"

    return description


@beartype
def assert_subset(main: Json, subset: Json, message: Optional[str] = None) -> None:
    diff = get_subset_diff(main_set=main, expected_subset=subset)

    compare = "Could not find expected subset of values in the main set\n\n"
    compare += "\n".join([
        "[{}]{}".format(
            idx,
            describe_diff(
                value,
                source=subset,
                target=main,
                source_name="expected subset",
                target_name="given main",
            )) for idx, value in enumerate(diff)
    ])

    if message:
        if "\n" not in compare and "\n" not in message:
            compare += " " + message

        else:
            compare += "\n" + message

    assert len(diff) == 0, compare
