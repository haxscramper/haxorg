from pathlib import Path
import os
import shutil

def rmdir_quiet(path: Path): 
    if path.exists():
        shutil.rmtree(path)
