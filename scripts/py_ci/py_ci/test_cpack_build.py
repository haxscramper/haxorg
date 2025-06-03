#!/usr/bin/env python

import logging
import os
import subprocess
import shutil
from pathlib import Path
from typing import List, Optional, Union, Dict, Any
import py_ci.data_build as data_build
from py_ci.util_scripting import run_cmd, logger, get_j_cap

WORKDIR: Path = Path("/haxorg_wip")
SRC_DIR: Path = Path("/haxorg")
BUILD_TESTS: bool = True
DEPS_BUILD: Path = WORKDIR / "deps_build"
DEPS_SRC: Path = SRC_DIR / "thirdparty"
DEPS_INSTALL: Path = WORKDIR / "deps_install"
ASSUME_CPACK_PRESENT = False
UNPACK_PARENT = WORKDIR / "target.d"
UNPACK_DIR: Path = UNPACK_PARENT / "haxorg-1.0.0-Source"


def prepare_env():
    if not WORKDIR.exists():
        WORKDIR.mkdir(parents=True)

    logger.info(f"Changing directory to {WORKDIR}")
    os.chdir(WORKDIR)

    logger.info(f"Listing contents of source directory {SRC_DIR}")
    run_cmd(["ls", SRC_DIR])


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
        if dep.build_name in ["lexy", "cctz", "immer", "lager", "cpptrace", "yaml", "msgpack"]:
            deps_list.append(dep)

        elif BUILD_TESTS and dep.build_name in ["googletest", "abseil"]:
            deps_list.append(dep)

    logger.info("Starting dependency installation")
    for dep in deps_list:
        install_dep(dep)

    cmake_paths = data_build.get_deps_install_config(
        deps=deps_list,
        install_dir=DEPS_INSTALL,
    )

    DEPS_INSTALL.mkdir(parents=True, exist_ok=True)
    DEPS_INSTALL.joinpath("paths.cmake").write_text(cmake_paths)

    logger.info("All dependencies installed successfully")
    logger.info(f"Cmake paths:\n{cmake_paths}")

    cmake_config.append(f"-DORG_DEPS_INSTALL_ROOT={DEPS_INSTALL}")

    logger.info("Configuring project build")

    return cmake_config


def update_cpack_archive(cmake_config: List[str]):
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

    run_cmd(["unzip", target_zip, "-d", str(UNPACK_PARENT,)])


def build_cpack_archive(cmake_config: List[str]):
    logger.info(f"Listing contents of {UNPACK_DIR}")
    run_cmd(["ls", UNPACK_DIR])

    logger.info("Configuring build from source package")
    unpack_build_dir: Path = UNPACK_DIR / "build"
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
    run_cmd([
        unpack_build_dir.joinpath("tests_hstd"),
    ])

    run_cmd([
        unpack_build_dir.joinpath("tests_org"),
    ])


def main():
    prepare_env()
    cmake_config = install_all_deps()
    if not ASSUME_CPACK_PRESENT:
        update_cpack_archive(cmake_config=cmake_config)

    build_cpack_archive(cmake_config=cmake_config)


if __name__ == "__main__":
    main()
