## @file   build.py
## @brief  Custom build script for copying shared library files

import os
import shutil
from pathlib import Path


def build_shared_library_conf(
    setup_kwargs,
    name: str,
    soname: str,
    envname: str,
    package_so_file: Path,
    rel_path: Path,
):
    package_so_file.parent.mkdir(parents=True, exist_ok=True)

    # Source location of the shared library
    if os.getenv(envname):
        so_file = Path(os.getenv(envname)).resolve().absolute()
        print(f"Using shared library from environment variable {envname}: {so_file}")
    else:
        so_file = rel_path
        print(f"Using default shared library path: {so_file}")

    if so_file.exists():
        print(f"Copying {so_file} to {package_so_file}")
        shutil.copy2(so_file, package_so_file)  # copy2 preserves metadata

        # Verify the copy was successful
        if package_so_file.exists():
            print(f"Successfully copied shared library to {package_so_file}")
            # Update package_data to ensure it's included
            if 'package_data' in setup_kwargs:
                if name not in setup_kwargs['package_data']:
                    setup_kwargs['package_data'][name] = []
                if '*.so' not in setup_kwargs['package_data'][name]:
                    setup_kwargs['package_data'][name].append('*.so')
        else:
            raise RuntimeError(f"Failed to copy shared library to {package_so_file}")
    else:
        raise FileNotFoundError(
            f"Could not find {soname} at {so_file} to include in the package")


def build_shared_library(setup_kwargs):
    """Copy or build the shared library during package installation"""
    base_dir = Path(__file__).parent
    # Target location in the package
    build_shared_library_conf(
        setup_kwargs=setup_kwargs,
        name="py_haxorg",
        soname="pyhaxorg.so",
        envname="HAXORG_PYHAXORG_SO_PATH",
        package_so_file=base_dir / "py_haxorg" / "pyhaxorg.so",
        rel_path=(base_dir / "../../build/haxorg/pyhaxorg.so").resolve().absolute(),
    )

    build_shared_library_conf(
        setup_kwargs=setup_kwargs,
        name="py_textlayout_cpp",
        soname="py_textlayout_cpp.so",
        envname="HAXORG_PYTEXTLAYOUT_SO_PATH",
        package_so_file=base_dir / "py_haxorg" / "py_textlayout_cpp.so",
        rel_path=(base_dir / "../../build/hstd/py_textlayout_cpp.so").resolve().absolute(),
    )


def build(setup_kwargs):
    """Main build function called by setup.py"""
    try:
        print("Building shared library component...")
        build_shared_library(setup_kwargs)
        print("Shared library build completed successfully")
    except Exception as e:
        print(f"Error: Failed to build/copy shared library: {e}")
        # For shared libraries, we typically want to fail the build
        raise
