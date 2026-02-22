from pathlib import Path
import shutil
from typing import Generator

from beartype import beartype
from beartype.typing import Any, Iterable, List
from py_ci.util_scripting import cmake_opt, get_j_cap
from py_repository.repo_tasks.command_execution import (
    get_uv_develop_env_flags,
    run_cmake_build,
    run_cmake_configure,
    run_command,
)
from py_repository.repo_tasks.common import (
    get_build_root,
    get_component_build_dir,
    get_script_root,
)
from py_repository.repo_tasks.haxorg_base import (
    base_environment,
    generate_develop_deps_install_paths,
    get_cmake_defines,
    get_deps_install_dir,
    symlink_build,
)
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_scriptutils import os_utils
from py_scriptutils.algorithm import cond
from py_scriptutils.files import FileOperation
from py_scriptutils.script_logging import log

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
        *get_cmake_defines(ctx),
        cmake_opt("ORG_DEPS_INSTALL_ROOT", get_deps_install_dir(ctx)),
        *cond(
            ctx.config.python_version,
            [cmake_opt("ORG_DEPS_USE_PYTHON_VERSION", ctx.config.python_version)],
            [],
        ),
    ]

    run_cmake_configure(
        ctx,
        build_dir=get_component_build_dir(ctx, "haxorg"),
        script_root=get_script_root(ctx),
        generator=ctx.config.build_conf.cmake_generator,
        args=pass_flags,
    )


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
        print_output=ctx.config.build_conf.real_time_output_print,
    )

    get_uv_develop_env_flags(ctx)


@haxorg_task()
def build_targets(ctx: TaskContext, targets: List[str]) -> None:
    conf_copy = ctx.config.model_copy(deep=True)
    conf_copy.build_conf.target = targets
    conf_copy.build_conf.force = True
    build_haxorg(ctx=ctx.with_temp_config(conf_copy))


@haxorg_task()
def build_and_setup_text_layout_lib(ctx: TaskContext) -> None:
    "Build the py text layout library and add .so to path"
    import sys
    build_targets(ctx=ctx, targets=["py_textlayout_cpp"])
    ctx.run(symlink_build, ctx=ctx)

    build_path = get_build_root(ctx, "haxorg")
    if str(build_path) not in sys.path:
        text_layout_so = list(build_path.glob("py_textlayout_cpp*.so"))
        assert 0 < len(
            text_layout_so
        ), f"Text layout library was not compiled to dir {build_path}, workflow would not be able to run codegen."
        sys.path.append(str(build_path))


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
            # cmake_opt("ORG_BUILD_WITH_PERFETTO", perfetto),
            # "--component",
            # "haxorg_component"
        ])


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
