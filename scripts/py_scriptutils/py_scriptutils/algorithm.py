from beartype.typing import List, Any, TypeVar, Iterable
import itertools
from beartype import beartype

T = TypeVar('T')


@beartype
def drop_none(items: Iterable[T]) -> Iterable[T]:
    return itertools.filterfalse(lambda it: not it, items)


def iterate_object_tree(tree, callback, context: List[Any]):
    callback(tree)
    context.append(tree)

    if isinstance(tree, list):
        for it in tree:
            iterate_object_tree(it, callback, context)

    elif isinstance(tree, dict):
        for key, value in tree.items():
            iterate_object_tree(value, callback, context)

    # Primitive types cannot be walked over, end iteration
    elif (tree is True or tree is False or tree is None or isinstance(tree, str) or
          isinstance(tree, type) or isinstance(tree, int)):
        pass

    elif isinstance(tree, object):
        # If any object -- walk all slots (attributes)
        for slot, value in vars(tree).items():
            iterate_object_tree(value, callback, context)

    # Walk over every item in list
    # Otherwise, print the value -- if something is missing it will be added later
    else:
        print(f"? {tree}")

    context.pop()
