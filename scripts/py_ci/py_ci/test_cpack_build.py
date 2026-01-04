#!/usr/bin/env python

import logging
import os
import subprocess
import shutil
from pathlib import Path
from typing import List, Optional, Union, Dict, Any
import py_ci.data_build as data_build
from py_ci.util_scripting import run_cmd, logger, get_j_cap
import argparse

WORKDIR: Path = Path("/haxorg/wip")
SRC_DIR: Path = Path("/haxorg/src")
BUILD_TESTS: bool = True
DEPS_BUILD: Path = WORKDIR / "deps_build"

if os.getenv("HAXORG_THIRD_PARTY_DIR_PATH"):
    DEPS_SRC: Path = Path(os.getenv("HAXORG_THIRD_PARTY_DIR_PATH"))  # type: ignore
else:
    DEPS_SRC: Path = SRC_DIR / "thirdparty"  # type: ignore

DEPS_INSTALL: Path = WORKDIR / "deps_install"
ASSUME_CPACK_PRESENT = False
UNPACK_PARENT = WORKDIR / "target.d"
UNPACK_DIR: Path = UNPACK_PARENT / "haxorg-1.0.0-Source"
BUILD_DIR: Path = UNPACK_DIR / "build"
PY_HAXORG_DIR: Path = SRC_DIR.joinpath("scripts/py_haxorg")


def prepare_env() -> None:
    if not WORKDIR.exists():
        WORKDIR.mkdir(parents=True)

    logger.info(f"Changing directory to {WORKDIR}")
    os.chdir(WORKDIR)

    logger.info(f"Listing contents of source directory {SRC_DIR}")
    run_cmd(["ls", "-al", str(SRC_DIR)])
    run_cmd(["ls", "-al", str(WORKDIR)])


def install_dep(dep: data_build.ExternalDep) -> None:
    build_dir: Path = DEPS_BUILD / dep.build_name
    src_dir: Path = DEPS_SRC / dep.deps_name
    install_dir: Path = DEPS_INSTALL / dep.build_name

    logger.info(f"Installing dependency: {dep}")

    cmake_args: List[str] = [
        "cmake",
        "-B",
        str(build_dir),
        "-S",
        str(src_dir),
        "-G",
        "Ninja",
        f"-DCMAKE_INSTALL_PREFIX={install_dir}",
        "-DCMAKE_BUILD_TYPE=Debug",
    ]

    cmake_args.extend(dep.get_configure_args())

    run_cmd(cmake_args)

    run_cmd([
        "cmake",
        "--build",
        str(build_dir),
        "--target",
        "install",
        "--parallel",
    ])

    logger.info(f"Successfully installed dependency: {dep.build_name}")


def install_all_deps() -> List[str]:

    cmake_config: List[str] = []

    for opt in data_build.get_published_build_opts():
        cmake_config.append(str(opt))

    deps_list: List[data_build.ExternalDep] = []
    dep: data_build.ExternalDep
    for dep in data_build.get_external_deps_list(
            install_dir=DEPS_INSTALL,
            is_emcc=False,
    ):
        if dep.build_name in [
                "lexy", "cctz", "immer", "lager", "cpptrace", "yaml", "msgpack"
        ]:
            deps_list.append(dep)

        elif BUILD_TESTS and dep.build_name in ["googletest", "abseil", "benchmark"]:
            deps_list.append(dep)

    logger.info("Starting dependency installation")
    for dep in deps_list:
        install_dep(dep)

    cmake_paths = data_build.get_deps_install_config(
        deps=deps_list,
        install_dir=DEPS_INSTALL,
        exists_check=lambda path: path.exists(),
    )

    DEPS_INSTALL.mkdir(parents=True, exist_ok=True)
    DEPS_INSTALL.joinpath("paths.cmake").write_text(cmake_paths)

    logger.info("All dependencies installed successfully")
    logger.info(f"Cmake paths:\n{cmake_paths}")

    cmake_config.append(f"-DORG_DEPS_INSTALL_ROOT={DEPS_INSTALL}")

    logger.info("Configuring project build")

    return cmake_config


def update_cpack_archive(cmake_config: List[str]) -> None:
    build_dir: Path = WORKDIR / "build" / "fedora_res"
    run_cmd([
        "cmake",
        "-B",
        str(build_dir),
        "-S",
        str(SRC_DIR),
        "-G",
        "Ninja",
        "-DORG_CPACK_PACKAGE_VERSION=1.0.0",
        "-DORG_CPACK_PACKAGE_NAME=haxorg",
    ] + cmake_config)

    logger.info("Running CPack to create source package")
    run_cmd(["cpack", "--debug", "--config", f"{build_dir}/CPackSourceConfig.cmake"])

    logger.info("Listing current directory")
    run_cmd(["ls"])

    target_zip: Path = WORKDIR / "target.zip"
    logger.info(f"Copying source package to {target_zip}")
    shutil.copy(WORKDIR / "haxorg-1.0.0-Source.zip", target_zip)

    os.makedirs(UNPACK_PARENT, exist_ok=True)

    logger.info(f"Unpacking source package to {UNPACK_PARENT}")
    if UNPACK_DIR.exists():
        shutil.rmtree(UNPACK_DIR)

    run_cmd(["unzip", str(target_zip), "-d", str(UNPACK_PARENT,)])


def build_cpack_archive(cmake_config: List[str], unpack_build_dir: Path) -> None:
    logger.info(f"Listing contents of {UNPACK_DIR}")
    run_cmd(["ls", str(UNPACK_DIR)])

    logger.info("Configuring build from source package")
    run_cmd([
        "cmake",
        "-B",
        str(unpack_build_dir),
        "-S",
        str(UNPACK_DIR),
        "-G",
        "Ninja",
    ] + cmake_config)

    logger.info("Building from source package")

    run_cmd([
        "cmake",
        "--build",
        str(unpack_build_dir),
        "--target",
        "all",
        *get_j_cap(),
    ])

    logger.info("Build process completed successfully")


def test_cpack_archive(
    unpack_build_dir: Path,
    test_cxx: bool,
    test_python: bool,
    python_version: str = "python3",
) -> None:
    if test_python:
        os.chdir(SRC_DIR)
        env = os.environ.copy()
        cache_dir = os.path.join(WORKDIR, ".poetry_cache")
        os.makedirs(cache_dir, exist_ok=True)
        assert BUILD_DIR.joinpath("pyhaxorg.so").exists()
        env.update({
            "POETRY_CACHE_DIR":
                cache_dir,
            "POETRY_VIRTUALENVS_PATH":
                os.path.join(WORKDIR, ".poetry_venvs"),
            "POETRY_CONFIG_DIR":
                os.path.join(WORKDIR, ".poetry_config"),
            "POETRY_DATA_DIR":
                os.path.join(WORKDIR, ".poetry_data"),
            "POETRY_REPOSITORIES_CACHE_DIR":
                os.path.join(cache_dir, "repositories"),
            "POETRY_HTTP_CACHE_DIR":
                os.path.join(cache_dir, "http"),
            "POETRY_VIRTUALENVS_IN_PROJECT":
                "true",
            "HAXORG_PYHAXORG_SO_PATH":
                str(BUILD_DIR.joinpath("pyhaxorg.so")),
            "HAXORG_PYTEXTLAYOUT_SO_PATH":
                str(BUILD_DIR.joinpath("py_textlayout_cpp.so")),
            "HAXORG_REPO_HAXORG_ROOT_BUILD_PATH":
                str(BUILD_DIR),
        })

        run_cmd(
            [
                "poetry",
                "--version",
            ],
            env=env,
        )

        run_cmd(
            [
                "poetry",
                "env",
                "use",
                python_version,
            ],
            env=env,
        )

        run_cmd(
            [
                "poetry",
                "install",
                "--no-root",
                "--no-interaction",
                "--no-ansi",
                "--without",
                "haxorg",
            ],
            env=env,
            check=False,
        )

        def find_whl() -> List[Path]:
            result = []
            for wheel_file in PY_HAXORG_DIR.joinpath("dist").glob("*.whl"):
                result.append(wheel_file)

            return result

        if PY_HAXORG_DIR.joinpath("build").exists():
            shutil.rmtree(PY_HAXORG_DIR.joinpath("build"))

        if PY_HAXORG_DIR.joinpath("dist").exists():
            shutil.rmtree(PY_HAXORG_DIR.joinpath("dist"))

        assert SRC_DIR.joinpath("scripts/py_haxorg").exists()

        run_cmd(
            [
                "poetry",
                "run",
                "python",
                "-m",
                "build",
                "--wheel",
                "--outdir",
                str(PY_HAXORG_DIR.joinpath("dist")),
                str(SRC_DIR.joinpath("scripts/py_haxorg")),
            ],
            env=env,
            cwd=str(SRC_DIR),
        )

        run_cmd(["ls", "-alR", "build"], cwd=str(PY_HAXORG_DIR))
        run_cmd(["ls", "-alR", "dist"], cwd=str(PY_HAXORG_DIR))

        assert len(find_whl()) == 1, str(find_whl())

        new_whl = find_whl()[0]
        assert new_whl is not None

        run_cmd(
            [
                "poetry",
                "remove",
                "py_haxorg",
            ],
            env=env,
        )

        run_cmd(
            [
                "poetry",
                "add",
                str(new_whl),
            ],
            env=env,
        )

        run_cmd(
            [
                "poetry",
                "run",
                "pytest",
                "-vv",
                "-ra",
                "-s",
                "--tb=short",
                "--disable-warnings",
                "-m",
                "not test_release",
            ],
            env=env,
        )

    elif test_cxx:
        run_cmd([unpack_build_dir.joinpath("tests_hstd")])
        run_cmd([unpack_build_dir.joinpath("tests_org")])


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Script with boolean flags and choice arguments")

    # Boolean flags
    parser.add_argument(
        "--deps",
        default=True,
        action="store_true",
        help="Dependencies flag",
    )

    parser.add_argument(
        "--no-deps",
        dest="deps",
        action="store_false",
        help="Disable deps",
    )

    parser.add_argument(
        "--build",
        default=True,
        action="store_true",
        help="Build flag",
    )

    parser.add_argument(
        "--no-build",
        dest="build",
        action="store_false",
        help="Disable build",
    )

    parser.add_argument(
        "--python-bin",
        dest="python_bin",
        default="python3",
        help="Which python to use",
    )

    # Choice argument
    parser.add_argument(
        "--test",
        choices=["none", "cxx", "python"],
        default="none",
        help="Test type: none, cxx, or python",
    )

    args = parser.parse_args()

    prepare_env()

    if args.deps:
        cmake_config = install_all_deps()

    unpack_build_dir: Path = UNPACK_DIR / "build"

    if args.build:
        if not ASSUME_CPACK_PRESENT:
            update_cpack_archive(cmake_config=cmake_config)

        build_cpack_archive(
            cmake_config=cmake_config,
            unpack_build_dir=unpack_build_dir,
        )

    test_cpack_archive(
        unpack_build_dir=unpack_build_dir,
        test_cxx="cxx" == args.test,
        test_python="python" == args.test,
    )


if __name__ == "__main__":
    main()
