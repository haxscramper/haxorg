from pathlib import Path
import os
import shutil
from typing import Optional, Any
import tempfile

def rmdir_quiet(path: Path) -> None: 
    if path.exists():
        shutil.rmtree(path)

def gettempdir(*relative: str) -> Path:
    return Path(tempfile.gettempdir()).joinpath(*relative)

def json_path_serializer(obj: Any) -> str:
    if isinstance(obj, Path):
        return str(obj)
    raise TypeError(f'Object of type {obj.__class__.__name__} is not JSON serializable')
