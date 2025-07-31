from pathlib import Path
import os
import shutil
from typing import Optional
import tempfile

def rmdir_quiet(path: Path): 
    if path.exists():
        shutil.rmtree(path)

def gettempdir(*relative) -> Path:
    return Path(tempfile.gettempdir()).joinpath(*relative)

def json_path_serializer(obj):
    if isinstance(obj, Path):
        return str(obj)
    raise TypeError(f'Object of type {obj.__class__.__name__} is not JSON serializable')
