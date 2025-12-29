from beartype.typing import List, Any, TypeVar, Iterable, Callable, Optional
import itertools
from beartype import beartype
from itertools import dropwhile, takewhile
import more_itertools as mit
from collections import defaultdict
import re

T = TypeVar('T')


def cond(expr: Any, ifTrue: Any = None, ifFalse: Any = None) -> Any:
    """
    Alternative for inline if expression for simpler syntax and better formatting. Also supports 
    multiple conditions, similar to the `cond` and `pcond` macro from lisp. Note: will evaluate
    all arguments irrespective of the truth value, so use it only in case where compute cost is
    small and there are no side effects. 

    If the `expr` is not a list or a tuple other type -- based on the value of `expr`, return the `ifTrue` or `ifFalse. 

    ```
    value = cond(expr, "true", "false")
    ```

    If the `expr` is a list is a list or a tuple return the first item where the expression is true. If no elements
    have true values, will return `None`. To get a default branch, use `True` as an expression. 

    ```
    value = cond([
        (expr1, value1),
        (expr2, value2),
        (True, default)
    ])
    ```

    """
    if isinstance(expr, (list, tuple)):
        for key, value in expr:
            if key:
                return value

    else:
        if expr:
            return ifTrue

        else:
            return ifFalse


def maybe_splice(expr: Any, item: T) -> List[T]:
    """
    Return `[item]` if the expression evaluates to true, otherwise return an empty list. 
    
    Use this for splicing optional values into the list `[it1, *maybe_splice(cond, it2)]` --
    depending on the `cond` value, the resulting list might have one or two elements. 
    """
    if expr:
        return [item]

    else:
        return []


def remove_ansi(text: str) -> str:
    ansi_escape = re.compile(r'\x1B[@-_][0-?]*[ -/]*[@-~]')
    return ansi_escape.sub("", text)


@beartype
def drop_none(items: Iterable[T]) -> Iterable[T]:
    return itertools.filterfalse(lambda it: not it, items)


@beartype
def first_index_if(items: Iterable[T], pred: Callable[[T], bool]) -> int:
    for idx, value in enumerate(items):
        if pred(value):
            return idx

    return -1


@beartype
def first_if(items: Iterable[T], pred: Callable[[T], bool]) -> Optional[T]:
    for value in items:
        if pred(value):
            return value
    return None


def iterate_object_tree(
    tree: Any,
    context: List[Any],
    pre_visit: Optional[Callable[[Any], None]] = None,
    post_visit: Optional[Callable[[Any], None]] = None,
    item_visit_format: Optional[Callable[[Any, List[Any]], str]] = None,
) -> None:
    """
    Recursively iterate the data tree, irrespective of the types -- treat the whole object
    as an untyped dict/etc. 

    :param context: Starting list of the scopes to be used in the iteration. The value is 
      going to be mutated during the iterationg -- using .append() and .pop()

    :param pre_visit: Callback invoked before appending the new tree to the stack, use 
      for pre-order DFS traversal of the data. One-argument function.

    :param post_visit: Callback for post-order DFS traversal.

    To use iteration context in the callback functions, define the mutable variable and 
    read it in the callbacks.
    """

    recursion_guard: set[int] = set()

    def aux(tree: Any, context: List[Any], depth: int) -> None:
        if pre_visit:
            pre_visit(tree)

        if item_visit_format:
            prefix = "  " * (depth if depth < 30 else 30)
            value_format = ""
            match tree:
                case bool() | int() | float() | str() | None:
                    value_format = str(tree)

            value_format = value_format.replace("\n", "\\n")

            print(f"{prefix} {type(tree)} {item_visit_format(tree, context)} {value_format}")

        if id(tree) in recursion_guard:
            return

        else:
            recursion_guard.add(id(tree))

        context.append(tree)

        if isinstance(tree, (list, tuple, set)):
            for it in tree:
                aux(
                    it,
                    context,
                    depth + 1,
                )

        elif isinstance(tree, dict):
            for key, value in tree.items():
                if item_visit_format:
                    print(f"{prefix}   {key}:")
                aux(
                    value,
                    context,
                    depth + 2,
                )

        # Primitive types cannot be walked over, end iteration
        elif (tree is True or tree is False or tree is None or isinstance(tree, str) or
              isinstance(tree, type) or isinstance(tree, int)):
            pass

        elif isinstance(tree, object):
            # If any object -- walk all slots (attributes)
            if hasattr(tree, "__dict__"):
                for slot, value in vars(tree).items():
                    if item_visit_format:
                        print(f"{prefix}   {slot}=")
                    aux(
                        value,
                        context,
                        depth + 2,
                    )

            else:
                print(f"??? {type(tree)}")

        # Walk over every item in list
        # Otherwise, print the value -- if something is missing it will be added later
        else:
            print(f"? {tree}")

        context.pop()
        if post_visit:
            post_visit(tree)

    aux(tree, context, 0)


@beartype
def trim_left(lst: Iterable[T], predicate: Callable[[T], bool]) -> List[T]:
    return list(dropwhile(predicate, lst))


@beartype
def trim_right(lst: Iterable[T], predicate: Callable[[T], bool]) -> List[T]:
    lst_list = list(lst)
    return list(dropwhile(predicate, lst_list[::-1]))[::-1]


@beartype
def trim_both(lst: Iterable[T], predicate: Callable[[T], bool]) -> List[T]:
    trimmed_left = list(dropwhile(predicate, lst))
    return list(dropwhile(predicate, trimmed_left[::-1]))[::-1]


@beartype
def validate_unique(items: Iterable[T], key: Callable[[T], Any] = lambda x: x) -> None:
    seen = defaultdict(list)
    for item in items:
        seen[key(item)].append(item)

    duplicates = {k: v for k, v in seen.items() if len(v) > 1}
    if duplicates:
        raise ValueError(f"Found duplicate items: {duplicates}")


@beartype
def partition_list(items: List[T], predicate: Callable[[T], bool]) -> List[List[T]]:
    """
    Split input list on items matching predicate, final result will not contain matched items
    """
    result: List[List[T]] = []
    current_partition: List[T] = []

    for item in items:
        if predicate(item):
            if current_partition:
                result.append(current_partition)
                current_partition = []
        else:
            current_partition.append(item)

    if current_partition:
        result.append(current_partition)

    return result
