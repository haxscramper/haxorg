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
)
import pickle
from pathlib import Path
from beartype import beartype
from contextlib import contextmanager
import traceback
from types import GeneratorType
from dataclasses import dataclass, field
from py_scriptutils.repo_files import get_haxorg_repo_root_path

T = TypeVar('T')

SomePath: TypeAlias = Union[str, Path, GeneratorType]
SomePaths: TypeAlias = Union[SomePath, List[SomePath]]





@beartype
def normalize_paths(input_paths: SomePaths) -> List[Path]:
    result: List[Path] = []

    def add(item: SomePaths):
        nonlocal result
        match item:
            case str():
                result.append(Path(item))

            case Path():
                result.append(item)

            case GeneratorType():
                for it in item:
                    add(it)

            case List():
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
    input_paths = [p.stat().st_mtime for p in input_paths if p.exists()]
    if input_paths:
        return min(input_paths)

    else:
        return 0.0


@beartype
def any_missing(input_paths: List[Path]) -> bool:
    return any((not p.exists() for p in input_paths))


@beartype
def IsNewInput(input_path: SomePaths, output_path: SomePaths) -> bool:
    input_path = normalize_paths(input_path)
    output_path = normalize_paths(output_path)
    if any_missing(output_path):
        return True

    else:
        return min_mtime(output_path) < max_mtime(input_path)


@beartype
@dataclass
class FileOperation:
    input: List[Path]
    output: Optional[List[Path]] = None
    stamp_path: Optional[Path] = None
    stamp_content: Optional[str] = None

    @classmethod
    def InOut(
        self,
        input: SomePaths,
        output: SomePaths,
        stamp_path: Optional[Path] = None,
        stamp_content: Optional[str] = None,
    ) -> 'FileOperation':
        return FileOperation(
            normalize_paths(input),
            output=normalize_paths(output),
            stamp_path=stamp_path,
            stamp_content=stamp_content,
        )

    @classmethod
    def InTmp(self,
              input: SomePaths,
              stamp_path: Path,
              stamp_content: Optional[str] = None,
              output: List[Path] = []) -> 'FileOperation':
        return FileOperation(normalize_paths(input),
                             stamp_path=stamp_path,
                             output=output,
                             stamp_content=stamp_content)

    def stamp_content_is_new(self) -> bool:
        return bool(self.stamp_path.exists() and self.stamp_content and
                    self.stamp_path.read_text() != self.stamp_content)

    def get_output_files(self) -> List[Path]:
        return (self.output or []) + ([self.stamp_path] if self.stamp_path else [])

    def should_run(self) -> bool:
        return IsNewInput(self.input, self.get_output_files()) or bool(
            self.stamp_path and self.stamp_content_is_new())

    def explain(self, name: str) -> str:
        if self.should_run():
            why = f"[red]{name}[/red] needs rebuild,"
            if self.stamp_path and not self.stamp_path.exists():
                why += " output stamp file is missing "

            if self.stamp_path and self.stamp_content_is_new():
                why += (
                    f" stamp content value changed, was [red]{self.stamp_path.read_text()}[/red], "
                    + f"now [green]{self.stamp_content}[/green]")

            min_time = min_mtime(self.get_output_files())
            newer = [p for p in self.input if p.exists() and min_time < p.stat().st_mtime]
            if newer:
                why += f" {len(newer)} files were changed since last creation: " + ", ".join(
                    (it.name for it in newer))

            return why

        else:
            return f"[green]{name}[/green] task is [green]up to date[/green]"

    def __enter__(self):
        return self

    def __exit__(self, exc_type: Optional[Type[BaseException]],
                 exc_value: Optional[BaseException], traceback) -> Optional[bool]:
        if exc_type is None and exc_value is None and self.stamp_path is not None:
            if not self.stamp_path.parent.exists():
                self.stamp_path.parent.mkdir(parents=True)

            with open(str(self.stamp_path), "w") as file:
                if self.stamp_content:
                    file.write(self.stamp_content)

                else:
                    file.write("xx")


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
