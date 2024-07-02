from beartype.typing import List, Any, TypeVar, Iterable, Callable, Optional
import itertools
from beartype import beartype
from itertools import dropwhile, takewhile
import more_itertools as mit

T = TypeVar('T')


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


def iterate_object_tree(tree, context: List[Any], pre_visit=None, post_visit=None):
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
    if pre_visit:
        pre_visit(tree)

    context.append(tree)

    if isinstance(tree, (list, tuple)):
        for it in tree:
            iterate_object_tree(
                it,
                context,
                pre_visit=pre_visit,
                post_visit=post_visit,
            )

    elif isinstance(tree, dict):
        for key, value in tree.items():
            iterate_object_tree(
                value,
                context,
                pre_visit=pre_visit,
                post_visit=post_visit,
            )

    # Primitive types cannot be walked over, end iteration
    elif (tree is True or tree is False or tree is None or isinstance(tree, str) or
          isinstance(tree, type) or isinstance(tree, int)):
        pass

    elif isinstance(tree, object):
        # If any object -- walk all slots (attributes)
        if hasattr(tree, "__dict__"):
            for slot, value in vars(tree).items():
                iterate_object_tree(
                    value,
                    context,
                    pre_visit=pre_visit,
                    post_visit=post_visit,
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


@beartype
def trim_left(lst: Iterable[T], predicate: Callable[[T], bool]) -> List[T]:
    return list(dropwhile(predicate, lst))


@beartype
def trim_right(lst: Iterable[T], predicate: Callable[[T], bool]) -> List[T]:
    return list(dropwhile(predicate, lst[::-1]))[::-1]


@beartype
def trim_both(lst: Iterable[T], predicate: Callable[[T], bool]) -> List[T]:
    trimmed_left = list(dropwhile(predicate, lst))
    return list(dropwhile(predicate, trimmed_left[::-1]))[::-1]
