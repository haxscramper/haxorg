import os
import shutil
import tempfile
from pathlib import Path
from typing import Any

from beartype import beartype


def rmdir_quiet(path: Path) -> None:
    if path.exists():
        shutil.rmtree(path)


def gettempdir(*relative: str) -> Path:
    return Path(tempfile.gettempdir()).joinpath(*relative)


def json_path_serializer(obj: Any) -> str:
    if isinstance(obj, Path):
        return str(obj)
    raise TypeError(f"Object of type {obj.__class__.__name__} is not JSON serializable")


def which_all(name: str) -> list[Path]:
    "Find all paths for the command by name"
    return [
        path.resolve()
        for directory in os.get_exec_path()
        if (path := Path(directory) / name).is_file() and os.access(path, os.X_OK)
    ]


@beartype
def ensure_clean_dir(dir: Path) -> Path:
    if dir.exists():
        shutil.rmtree(str(dir))
    dir.mkdir(parents=True, exist_ok=True)
    return dir


@beartype
def ensure_existing_dir(dir: Path) -> Path:
    dir.mkdir(parents=True, exist_ok=True)
    return dir


@beartype
def ensure_clean_file(file: Path) -> Path:
    ensure_existing_dir(file.parent)
    file.write_text("")
    return file
