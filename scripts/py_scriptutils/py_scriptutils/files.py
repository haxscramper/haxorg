import os
from typing import Callable, TypeVar, Union, List
import pickle
from pathlib import Path

T = TypeVar('T')


def IsNewInput(input_path: Union[str, List[str]], output_path: str):
    input_path: List[str] = input_path if isinstance(input_path, list) else [input_path]
    if not os.path.exists(output_path):
        return True

    else:
        in_mtimes = [
            os.path.getmtime(p) if os.path.exists(p) else os.path.getmtime(output_path) +
            1 for p in input_path
        ]
        return os.path.getmtime(output_path) < max(in_mtimes)


def pickle_or_new(input_path: str, output_path: str, builder_cb: Callable[[str], T]) -> T:
    if IsNewInput(input_path, output_path):
        value: T = builder_cb(input_path)
        with open(output_path, "wb") as file:
            pickle.dump(value, file)

        return value

    else:
        with open(output_path, "rb") as file:
            return pickle.load(file)


def file_relpath(base: Path, target: Path) -> str:
    if base.parent == target.parent:
        return "./" + target.name

    else:
        dir_source = os.path.dirname(base.resolve())

        # Compute the relative path
        relative_path = os.path.relpath(target.resolve(), dir_source)

        # Ensure the path starts with "./" if it doesn't go up in the hierarchy
        if not relative_path.startswith(("..", "/")):
            relative_path = f"./{relative_path}"

        return relative_path
