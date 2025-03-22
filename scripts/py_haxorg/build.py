## @file   build.py
## @brief  Setuptools script for installable python package

# py_haxorg/build.py
import os
import shutil
from pathlib import Path


def build_shared_library(setup_kwargs):
    """Copy or build the shared library during package installation"""
    package_dir = Path(__file__).parent / "build/lib/py_haxorg/pyhaxorg.so"

    so_file = Path("../../build/haxorg/pyhaxorg.so").resolve().absolute()

    if so_file.exists():
        print(f"Copied {so_file} to {package_dir}")
        shutil.copy(so_file, package_dir)
        return

    else:
        raise FileNotFoundError(f"Could not find pyhaxorg.so at {so_file} to include in the package")


# This function will be called by Poetry during the build process
def build(setup_kwargs):
    try:
        build_shared_library(setup_kwargs)
    except Exception as e:
        print(f"Warning: Failed to build/copy shared library: {e}")
