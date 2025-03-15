#!/usr/bin/env python

import logging
import os
import subprocess
import shutil
from pathlib import Path
from typing import List, Optional, Union, Dict, Any

logging.basicConfig(level=logging.INFO,
                    format="%(asctime)s - %(filename)s:%(lineno)d - %(levelname)s - %(message)s")
logger = logging.getLogger(__name__)

WORKDIR: Path = Path("/haxorg_wip")
SRC_DIR: Path = Path("/haxorg")


def run_cmd(cmd: List[str], **kwargs: Any) -> subprocess.CompletedProcess:
    """Run a subprocess command with logging."""
    cmd_str = " ".join(str(arg) for arg in cmd)
    logger.info(f"Executing: {cmd_str}")
    return subprocess.run(cmd, check=True, **kwargs)


logger.info(f"Changing directory to {WORKDIR}")
os.chdir(WORKDIR)

logger.info(f"Listing contents of source directory {SRC_DIR}")
run_cmd(["ls", SRC_DIR])

DEPS_BUILD: Path = WORKDIR / "deps_build"
DEPS_SRC: Path = SRC_DIR / "thirdparty"
DEPS_INSTALL: Path = WORKDIR / "deps_install"


def install_dep(build_name: str, deps_name: str, extra_args: str = "") -> None:
    build_dir: Path = DEPS_BUILD / build_name
    src_dir: Path = DEPS_SRC / deps_name
    install_dir: Path = DEPS_INSTALL / build_name

    logger.info(f"Installing dependency: {deps_name} -> {build_name}")

    cmake_args: List[str] = [
        "cmake", "-B",
        str(build_dir), "-S",
        str(src_dir), "-G", "Ninja", f"-DCMAKE_INSTALL_PREFIX={install_dir}",
        "-DCMAKE_BUILD_TYPE=RelWithDebInfo"
    ]

    if extra_args:
        cmake_args.extend(extra_args.split())

    run_cmd(cmake_args)

    run_cmd(["cmake", "--build", str(build_dir), "--target", "install", "--parallel"])

    logger.info(f"Successfully installed dependency: {deps_name}")


logger.info("Starting dependency installation")
install_dep("reflex", "RE-flex", "-DCMAKE_POSITION_INDEPENDENT_CODE=TRUE")
install_dep("lexy", "lexy", "-DLEXY_BUILD_TESTS=OFF -DLEXY_BUILD_EXAMPLES=OFF")
install_dep("abseil", "abseil-cpp",
            "-DABSL_CC_LIB_COPTS=-fPIC -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE")
install_dep(
    "immer", "immer",
    "-Dimmer_BUILD_TESTS=OFF -Dimmer_BUILD_EXAMPLES=OFF -Dimmer_BUILD_DOCS=OFF -Dimmer_BUILD_EXTRAS=OFF"
)
install_dep(
    "lager", "lager",
    "-Dlager_BUILD_EXAMPLES=OFF -Dlager_BUILD_TESTS=OFF -Dlager_BUILD_FAILURE_TESTS=OFF -Dlager_BUILD_DEBUGGER_EXAMPLES=OFF -Dlager_BUILD_DOCS=OFF"
)
install_dep("cpptrace", "cpptrace")
logger.info("All dependencies installed successfully")

CMAKE_CONFIG: str = ("-DORG_DEPS_USE_PROTOBUF=OFF "
                     "-DORG_IS_PUBLISH_BUILD=ON "
                     "-DORG_BUILD_ASSUME_CLANG=ON "
                     "-DCMAKE_CXX_COMPILER=clang++ "
                     "-DCMAKE_C_COMPILER=clang "
                     "-DORG_USE_SANITIZER=OFF "
                     "-DORG_DEPS_USE_ADAPTAGRAMS=OFF "
                     "-DORG_DEPS_USE_PACKAGED_BOOST=OFF "
                     f"-DCMAKE_PREFIX_PATH={DEPS_INSTALL}/reflex/lib/cmake/reflex;"
                     f"{DEPS_INSTALL}/reflex/lib64/cmake/reflex;"
                     f"{DEPS_INSTALL}/lexy/lib/cmake/lexy;"
                     f"{DEPS_INSTALL}/lexy/lib64/cmake/lexy;"
                     f"{DEPS_INSTALL}/abseil/lib64/cmake/absl;"
                     f"{DEPS_INSTALL}/abseil/lib/cmake/absl;"
                     f"{DEPS_INSTALL}/immer/lib/cmake/Immer;"
                     f"{DEPS_INSTALL}/immer/lib64/cmake/Immer;"
                     f"{DEPS_INSTALL}/lager/lib/cmake/Lager;"
                     f"{DEPS_INSTALL}/lager/lib64/cmake/Lager;"
                     f"{DEPS_INSTALL}/cpptrace/lib/cmake/cpptrace;"
                     f"{DEPS_INSTALL}/cpptrace/lib64/cmake/cpptrace;"
                     f"{DEPS_INSTALL}/cpptrace/lib/cmake/libdwarf;"
                     f"{DEPS_INSTALL}/cpptrace/lib64/cmake/libdwarf")

logger.info("Configuring project build")
build_dir: Path = WORKDIR / "build" / "fedora_res"
run_cmd([
    "cmake", "-B",
    str(build_dir), "-S",
    str(SRC_DIR), "-G", "Ninja", "-DORG_CPACK_PACKAGE_VERSION=1.0.0",
    "-DORG_CPACK_PACKAGE_NAME=haxorg"
] + CMAKE_CONFIG.split())

logger.info("Running CPack to create source package")
run_cmd(["cpack", "--debug", "--config", f"{build_dir}/CPackSourceConfig.cmake"])

logger.info("Listing current directory")
run_cmd(["ls"])

target_zip: Path = Path("/tmp/target.zip")
logger.info(f"Copying source package to {target_zip}")
shutil.copy(WORKDIR / "haxorg-1.0.0-Source.zip", target_zip)

UNPACK_DIR: Path = Path("/tmp/target.d/haxorg-1.0.0-Source")
logger.info(f"Creating directory {Path('/tmp/target.d')}")
os.makedirs(Path("/tmp/target.d"), exist_ok=True)

logger.info(f"Unpacking source package to {Path('/tmp/target.d')}")
run_cmd(["unzip", target_zip, "-d", "/tmp/target.d"])

logger.info(f"Listing contents of {UNPACK_DIR}")
run_cmd(["ls", UNPACK_DIR])

logger.info("Configuring build from source package")
unpack_build_dir: Path = UNPACK_DIR / "build"
run_cmd(["cmake", "-B",
         str(unpack_build_dir), "-S",
         str(UNPACK_DIR), "-G", "Ninja"] + CMAKE_CONFIG.split())

logger.info("Building from source package")
run_cmd(["cmake", "--build", str(unpack_build_dir), "--target", "all", "--parallel"])

logger.info("Build process completed successfully")
