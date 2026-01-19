from pathlib import Path
from typing import Generator
from beartype import beartype
from beartype.typing import List, Any, Iterable
import shutil

from py_ci.util_scripting import cmake_opt, get_j_cap
from py_scriptutils import os_utils
from py_scriptutils.algorithm import cond
from py_scriptutils.files import FileOperation
from py_scriptutils.script_logging import log
from py_repository.repo_tasks.haxorg_base import (
    base_environment,
    generate_develop_deps_install_paths,
    get_cmake_defines,
    get_deps_install_dir,
    symlink_build,
)
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_repository.repo_tasks.command_execution import run_cmake_build, run_command
from py_repository.repo_tasks.common import get_component_build_dir, get_script_root, get_build_root

CAT = __name__


@beartype
def get_build_haxorg_stamps(ctx: TaskContext) -> Any:
    return get_cmake_defines(ctx)


@beartype
def get_configure_cmake_haxorg_input(ctx: TaskContext) -> Iterable[Path]:
    return get_script_root(ctx, "src").rglob("*.cmake")


@haxorg_task(
    dependencies=[base_environment, generate_develop_deps_install_paths],
    file_operation=FileOperation.InTmp(
        input=[get_configure_cmake_haxorg_input],
        stamp_name="configure_cmake_haxorg",
        stamp_content=get_build_haxorg_stamps,
    ),
)
def configure_cmake_haxorg(ctx: TaskContext, force: bool = False) -> None:
    """Execute cmake configuration step for haxorg"""
    log(CAT).info("running haxorg cmake configuration")

    pass_flags = [
        "-B",
        get_component_build_dir(ctx, "haxorg"),
        "-S",
        get_script_root(ctx),
        "-G",
        "Ninja",
        *get_cmake_defines(ctx),
        cmake_opt("ORG_CPACK_PACKAGE_VERSION", ctx.config.HAXORG_VERSION),
        cmake_opt("ORG_CPACK_PACKAGE_NAME", ctx.config.HAXORG_NAME),
        cmake_opt("ORG_DEPS_INSTALL_ROOT", get_deps_install_dir(ctx)),
        *cond(
            ctx.config.python_version,
            [cmake_opt("ORG_DEPS_USE_PYTHON_VERSION", ctx.config.python_version)],
            [],
        ),
    ]

    import shlex
    Path("/tmp/cmake_configure_haxorg_flags.txt").write_text(
        shlex.join([str(s) for s in pass_flags[6:]]))
    run_command(ctx, "cmake", pass_flags)


@beartype
def get_build_haxorg_input(ctx: TaskContext) -> Any:
    return get_script_root(ctx).joinpath("src").rglob("*.?pp")


@haxorg_task(
    dependencies=[symlink_build, configure_cmake_haxorg],
    file_operation=FileOperation.InTmp(
        input=[get_build_haxorg_input],
        stamp_name="build_haxorg",
        stamp_content=get_build_haxorg_stamps,
    ),
)
def build_haxorg(ctx: TaskContext) -> None:
    """Compile main set of libraries and binaries for org-mode parser"""
    log(CAT).info(f"Using dependency dir {get_deps_install_dir(ctx)}")
    log(CAT).info(f"Building with\n{' '.join(get_cmake_defines(ctx))}")
    build_dir = get_component_build_dir(ctx, "haxorg")

    targets = cond(0 < len(ctx.config.build_conf.target), ctx.config.build_conf.target,
                   ["all"])

    log(CAT).debug(f"Building targets {targets}")

    run_cmake_build(
        ctx,
        build_dir=build_dir,
        targets=targets,
    )

    if "all" in targets or "pyhaxorg" in targets:
        run_command(ctx, "poetry", ["install", "--no-root", "--only", "haxorg"])


@haxorg_task()
def build_targets(ctx: TaskContext, targets: List[str]) -> None:
    conf_copy = ctx.config.model_copy(deep=True)
    conf_copy.build_conf.target = targets
    conf_copy.build_conf.force = True
    build_haxorg(ctx=ctx.with_temp_config(conf_copy))

@haxorg_task(dependencies=[build_haxorg])
def install_haxorg_develop(ctx: TaskContext, perfetto: bool = False) -> None:
    """Install haxorg targets in the build directory"""
    install_dir = get_build_root(ctx).joinpath("install")
    if install_dir.exists():
        shutil.rmtree(install_dir)

    run_command(
        ctx,
        "cmake",
        [
            "--install",
            get_component_build_dir(ctx, "haxorg"),
            "--prefix",
            install_dir,
            # cmake_opt("ORG_USE_PERFETTO", perfetto),
            # "--component",
            # "haxorg_component"
        ])


@haxorg_task(dependencies=[configure_cmake_haxorg])
def build_release_archive(ctx: TaskContext, force: bool = False) -> None:
    "Generate source archive"

    pack_res = get_script_root(ctx).joinpath("_CPack_Packages")
    log(CAT).info(f"Package tmp directory {pack_res}")
    if pack_res.exists():
        shutil.rmtree(str(pack_res))

    run_command(
        ctx,
        "cpack",
        [
            "--debug",
            # "--verbose",
            "--config",
            str(
                get_component_build_dir(ctx,
                                        "haxorg").joinpath("CPackSourceConfig.cmake")),
        ],
    )

    # else:
    #     log(CAT).debug(op.explain("cpack code"))


@haxorg_task()
def run_cmake_haxorg_clean(ctx: TaskContext) -> None:
    """Clean build directory for the current configuration"""
    build_dir = get_component_build_dir(ctx, "haxorg")
    if build_dir.joinpath("CMakeCache.txt").exists():
        run_command(ctx, "cmake", [
            "--build",
            build_dir,
            "--target",
            "clean",
        ])

    adaptagrams_dir = build_dir.joinpath("libcola")
    import shutil
    if adaptagrams_dir.exists():
        shutil.rmtree(str(adaptagrams_dir))

    os_utils.rmdir_quiet(get_build_root(ctx).joinpath("deps_build"))
    os_utils.rmdir_quiet(get_deps_install_dir(ctx))
