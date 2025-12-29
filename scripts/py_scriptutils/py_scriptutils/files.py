import json
import os
from beartype.typing import (
    Callable,
    TypeVar,
    Union,
    List,
    cast,
    TypeAlias,
    Optional,
    Type,
    Iterable,
    Dict,
    Any,
    Generator,
    Sequence,
)

from functools import wraps
import pickle
from pathlib import Path
from beartype import beartype
from contextlib import contextmanager
import traceback
from types import GeneratorType
from dataclasses import dataclass, field
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from datetime import datetime
import difflib

from py_scriptutils.script_logging import to_debug_json

T = TypeVar("T")

SomePath: TypeAlias = Union[str, Path, GeneratorType, map, Callable]
SomePaths: TypeAlias = Union[SomePath, Sequence[SomePath]]


@beartype
def normalize_paths(input_paths: SomePaths, **kwargs: Any) -> List[Path]:
    result: List[Path] = []

    def add(item: SomePaths) -> None:
        nonlocal result
        match item:
            case str():
                result.append(Path(item))

            case Path():
                result.append(item)

            case GeneratorType():
                for it in item:
                    add(it)

            case Callable():
                for it in item(**kwargs):
                    add(it)

            case List():
                for it in item:
                    add(it)

            case map():
                for it in item:
                    add(it)

            case _:
                raise TypeError(f"Unhandled path normalization {type(item)}")

    add(input_paths)

    return result


@beartype
def max_mtime(input_paths: List[Path]) -> float:
    return max((p.stat().st_mtime for p in input_paths if p.exists()))


@beartype
def min_mtime(input_paths: List[Path]) -> float:
    input_times = [p.stat().st_mtime for p in input_paths if p.exists()]
    if input_times:
        return min(input_times)

    else:
        return 0.0


@beartype
def any_missing(input_paths: List[Path]) -> bool:
    return any((not p.exists() for p in input_paths))


@beartype
def IsNewInput(input_path: SomePaths, output_path: SomePaths, **kwargs: Any) -> bool:
    normalized_input_path = normalize_paths(input_path, **kwargs)
    normalized_output_path = normalize_paths(output_path, **kwargs)
    assert 0 < len(normalized_input_path)
    assert 0 < len(normalized_output_path)
    if any_missing(normalized_output_path):
        return True

    else:
        return min_mtime(normalized_output_path) < max_mtime(normalized_input_path)


@beartype
@dataclass
class FileOperation:
    input: SomePaths
    output: Optional[SomePaths] = None
    stamp_name: Optional[str] = None
    stamp_content: Optional[str | Callable] = None

    def get_stamp_content(self, **kwargs: Any) -> str:
        if self.stamp_content:
            if isinstance(self.stamp_content, str):
                return self.stamp_content

            else:
                return json.dumps(
                    to_debug_json(
                        self.stamp_content(**kwargs),
                        with_stable_formatting=True,
                    ),
                    indent=2,
                    sort_keys=True,
                )

        else:
            return "xx"

    def get_input(self, **kwargs: Any) -> List[Path]:
        return normalize_paths(self.input, **kwargs)

    def get_output(self, **kwargs: Any) -> List[Path]:
        if self.output is None:
            return []
        return normalize_paths(self.output, **kwargs)

    @staticmethod
    def OnlyStamp(name: str, content: str | Callable) -> "FileOperation":
        return FileOperation(
            input=[],
            output=[],
            stamp_name=name,
            stamp_content=content,
        )

    @classmethod
    def InOut(
        self,
        input: SomePaths,
        output: SomePaths,
        stamp_name: Optional[str] = None,
        stamp_content: Optional[str] = None,
    ) -> "FileOperation":
        return FileOperation(
            input=input,
            output=output,
            stamp_name=stamp_name,
            stamp_content=stamp_content,
        )

    @classmethod
    def InTmp(
        self,
        input: SomePaths,
        stamp_name: str,
        stamp_content: Optional[str | Callable] = None,
        output: List[Path] = [],
    ) -> "FileOperation":
        return FileOperation(
            input=input,
            stamp_name=stamp_name,
            output=output,
            stamp_content=stamp_content,
        )

    def get_stamp_path(self, root: Path) -> Optional[Path]:
        if self.stamp_name:
            return root.joinpath(self.stamp_name)

        else:
            return None

    def stamp_content_is_new(self, root: Path, **kwargs: Any) -> bool:
        stamp_path = self.get_stamp_path(root)
        if stamp_path is not None and stamp_path.exists():
            return bool(
                stamp_path.exists() and self.get_stamp_content(**kwargs) and
                stamp_path.read_text() != self.get_stamp_content(**kwargs),)

        else:
            return True

    def get_output_files(self, root: Path, **kwargs: Any) -> List[Path]:
        stamp_path = self.get_stamp_path(root)
        return (self.get_output(**kwargs) or
                []) + ([stamp_path] if stamp_path is not None else [])

    def should_run(self, root: Path, **kwargs: Any) -> bool:
        stamp_path = self.get_stamp_path(root)
        return (self.input and IsNewInput(
            self.input,
            self.get_output_files(root) or
            ([stamp_path] if stamp_path is not None else []), **kwargs)) or bool(
                stamp_path and self.stamp_content_is_new(root, **kwargs))

    def explain(self, name: str, root: Path, **kwargs: Any) -> str:
        if self.should_run(root, **kwargs):
            stamp_path = self.get_stamp_path(root)

            def mtime_str(time: float) -> str:
                return datetime.fromtimestamp(time).strftime("%Y-%m-%d %H:%M:%S")

            why = f"[red]{name}[/red] needs rebuild,"
            if stamp_path is not None and not stamp_path.exists():
                why += " output stamp file is missing "

            if stamp_path is not None and self.stamp_content_is_new(root, **kwargs):
                why += f" stamp content value changed\n"
                for line in difflib.context_diff(
                        stamp_path.read_text().splitlines(),
                        self.get_stamp_content(**kwargs).splitlines(),
                        fromfile="before",
                        tofile="after",
                ):
                    why += f"\n{line}"

            min_time = min_mtime(self.get_output_files(root))
            newer = [
                p for p in self.get_input(**kwargs)
                if p.exists() and min_time < p.stat().st_mtime
            ]

            def format_files(files: Iterable[Path]) -> str:
                return ", ".join(("{} ({})".format(
                    it.name,
                    mtime_str(it.stat().st_mtime) if it.exists() else "<missing>",
                ) for it in files))

            if newer:
                why += " {} files were changed since last creation of {}: {}".format(
                    len(newer),
                    format_files(self.get_output_files(root)),
                    format_files(newer),
                )

            return why

        else:
            result = f"[green]{name}[/green] task is [green]up to date[/green]"

            if not self.stamp_content_is_new(root, **kwargs):
                result += "\nstamp content is not new"

            return result

    @contextmanager
    def scoped_operation(self, root: Path, **kwargs: Any) -> Generator[Any, Any, Any]:
        yield

        stamp = self.get_stamp_path(root)
        if stamp is not None and not stamp.parent.exists():
            stamp.parent.mkdir(parents=True)

        with open(str(stamp), "w") as file:
            file.write(self.get_stamp_content(**kwargs))


def cache_file_processing_result(input_arg_names: List[str]) -> Callable:
    cache: Dict[str, Dict[str, Any]] = {}

    def decorator(func: Callable) -> Callable:

        @wraps(func)
        def wrapper(*args: Any, **kwargs: Any) -> Any:
            cache_key = func.__name__
            mod_times = []
            for arg_name in input_arg_names:
                if arg_name in kwargs:
                    file_path = Path(kwargs[arg_name])
                    mod_times.append((file_path, file_path.stat().st_mtime))
                else:
                    arg_index = func.__code__.co_varnames.index(arg_name)
                    file_path = Path(args[arg_index])
                    mod_times.append((file_path, file_path.stat().st_mtime))

            if cache_key in cache:
                cached_mod_times, cached_result = cache[cache_key]["mod_times"], cache[
                    cache_key]["result"]
                if all(mod_time == cached_mod_times[i][1]
                       for i, (file_path, mod_time) in enumerate(mod_times)):
                    return cached_result

            result = func(*args, **kwargs)
            cache[cache_key] = {"mod_times": mod_times, "result": result}
            return result

        return wrapper

    return decorator


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

        # Ensure the path starts with "./" if it doesn"t go up in the hierarchy
        if not relative_path.startswith(("..", "/")):
            relative_path = f"./{relative_path}"

        return relative_path
