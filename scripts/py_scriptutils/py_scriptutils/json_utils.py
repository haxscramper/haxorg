from dataclasses import dataclass, field
from beartype.typing import Callable, List, Any, Dict, Union
from enum import Enum, auto
import json
from jsonpath_ng import jsonpath, DatumInContext, Index, Fields
import copy
from beartype import beartype

Json = Union[str, int, float, None, Dict, List]

class Op(Enum):
    Replace = auto()
    Remove = auto()
    Add = auto()


@beartype
@dataclass
class DiffItem:
    op: Op
    path: jsonpath.JSONPath
    value: Any = field(default=None)


@beartype
def json_diff(source: Any,
              target: Any,
              path: jsonpath.JSONPath = jsonpath.Root(),
              ignore: Callable[[Any], bool] = lambda x: False) -> List[DiffItem]:
    result = []

    if ignore(target):
        return result
    if source == target:
        return result

    if type(source) != type(target):
        result.append(DiffItem(Op.Replace, path, target))
        return result

    if isinstance(source, list):
        i = 0
        while i < len(source) and i < len(target):
            temp_diff = json_diff(source[i], target[i], path.child(Index(i)), ignore)
            result.extend(temp_diff)
            i += 1

        end_index = len(result)
        while i < len(source):
            result.insert(end_index, DiffItem(Op.Remove, path.child(Index(i))))
            i += 1

        while i < len(target):
            result.append(DiffItem(Op.Add, path.child(Index(i)), target[i]))
            i += 1

    elif isinstance(source, dict):
        for key in source:
            if key in target:
                temp_diff = json_diff(source[key], target[key], path.child(Fields(key)),
                                      ignore)
                result.extend(temp_diff)

            else:
                result.append(DiffItem(Op.Remove, path.child(Fields(key))))

        for key in target:
            if key not in source:
                result.append(DiffItem(Op.Add, path.child(Fields(key)), target[key]))

    else:
        result.append(DiffItem(Op.Replace, path, target))

    return result


@beartype
def get_subset_diff(main_set: Any, expected_subset: Any) -> List[DiffItem]:
    """
    Get list of elements removed from expected subset of changed in expected subset. 
    """

    # If some element from expect *sub*set was added, it is an expected behavior. All other operations
    # are returned. 
    return [it for it in json_diff(source=expected_subset, target=main_set) if it.op != Op.Add]


@beartype
def describe_diff(it: DiffItem, expected: Any, converted: Any) -> str:
    description = "  "
    path = it.path

    if it.op == Op.Remove:
        description += "[red]converted has extra entry[/red]"
    elif it.op == Op.Add:
        description += "[green]export missing entry[/green]"
    elif it.op == Op.Replace:
        description += "[magenta]changed entry[/magenta]"

    description += f" on path '[yellow]{path}[/yellow]' "

    def get_path(value: Any) -> Any:
        value: DatumInContext = [item for item in path.find(value)][0]
        return value.value

    if it.op == Op.Remove:
        description += f"    [red]{json.dumps(get_path(converted), indent=2)}[/red]"

    elif it.op == Op.Add:
        description += f"    {json.dumps(it.value, indent=2)}"

    elif it.op == Op.Replace:
        exp = get_path(expected)
        conv = get_path(converted)
        from_val = json.dumps(exp, indent=2)
        to_val = json.dumps(conv, indent=2)

        if type(exp) != type(conv):
            description += f"type mismatch: {type(exp).__name__} != {type(conv).__name__} "

        if len(from_val) > 40 or len(to_val) > 40:
            description += "\n    from [red]" + from_val + "[/red]\n"
            description += "    to   [green]" + to_val + "[/green]"
        else:
            description += f"    from [red]{from_val}[/red] to [green]{to_val}[/green]"

    return description
