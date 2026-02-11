import itertools
import json
from pathlib import Path
import shutil
from tempfile import TemporaryDirectory

from beartype import beartype
from beartype.typing import Any, List, Optional
import plumbum
from py_ci.data_build import (
    CmakeFlagConfig,
    CmakeOptConfig,
    ExternalDep,
    get_external_deps_list,
)
from py_ci.util_scripting import cmake_opt, get_j_cap
from py_repository.repo_tasks.command_execution import (
    get_cmd_debug_file,
    run_cmake_build,
    run_cmake_configure,
    run_command,
)
from py_repository.repo_tasks.common import (
    check_path_exists,
    ensure_existing_dir,
    get_build_root,
    get_log_dir,
    get_script_root,
)
from py_repository.repo_tasks.config import HaxorgConfig
from py_repository.repo_tasks.haxorg_base import (
    generate_develop_deps_install_paths,
    get_deps_build_dir,
    get_deps_install_dir,
    get_toolchain_path,
)
from py_repository.repo_tasks.haxorg_build import build_release_archive
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_scriptutils.algorithm import cond, maybe_splice
from py_scriptutils.files import FileOperation
from py_scriptutils.script_logging import log, to_debug_json

CAT = __name__


@haxorg_task()
def validate_dependencies_install(ctx: TaskContext) -> None:
    install_dir = get_deps_install_dir(ctx).joinpath("paths.cmake")
    assert check_path_exists(ctx,
                             install_dir), f"No dependency paths found at '{install_dir}'"


@beartype
def get_develop_deps_stamp(ctx: TaskContext) -> Any:
    return get_external_deps_list(
        get_deps_install_dir(ctx),
        is_emcc=ctx.config.emscripten.build,
    )


@haxorg_task(file_operation=FileOperation.OnlyStamp(
    "build_develop_deps",
    get_develop_deps_stamp,
))
def build_develop_deps(ctx: TaskContext) -> None:
    "Install dependencies for cmake project development"
    conf = ctx.config
    build_dir = get_deps_build_dir(ctx)
    ensure_existing_dir(ctx, build_dir)
    install_dir = get_deps_install_dir(ctx)
    ensure_existing_dir(ctx, install_dir)
    deps_dir = get_script_root(ctx).joinpath("thirdparty")

    debug_conf = dict(
        append_stderr_debug=True,
        append_stdout_debug=True,
    )

    @beartype
    def dep(item: ExternalDep) -> None:
        if 0 < len(
                conf.build_develop_deps_conf.build_whitelist
        ) and item.build_name not in conf.build_develop_deps_conf.build_whitelist:
            return

        configure_args = list(
            itertools.chain(*[
                it.get_cli()
                for it in item.configure_args
                if isinstance(it, CmakeOptConfig) or not it.isBuild
            ]))

        log(CAT).info(f"Running build name='{item.build_name}' deps='{item.deps_name}'")
        if conf.build_develop_deps_conf.configure:
            run_cmake_configure(
                ctx,
                build_dir=build_dir.joinpath(item.build_name),
                script_root=deps_dir.joinpath(item.deps_name),
                generator=ctx.config.build_conf.cmake_generator,
                args=[
                    cmake_opt("CMAKE_INSTALL_PREFIX",
                              install_dir.joinpath(item.build_name)),
                    cmake_opt("CMAKE_BUILD_TYPE", "RelWithDebInfo"),
                    cmake_opt("CMAKE_CXX_COMPILER", conf.build_conf.cxx_compiler),
                    cmake_opt("CMAKE_C_COMPILER", conf.build_conf.c_compiler),
                    *configure_args,
                    *maybe_splice(conf.build_develop_deps_conf.force, "--fresh"),
                ],
                **debug_conf,  # type: ignore
            )

        build_args = list(
            itertools.chain(*[
                it.get_cli()
                for it in item.configure_args
                if isinstance(it, CmakeFlagConfig) and it.isBuild
            ]))

        run_cmake_build(
            ctx,
            build_dir=build_dir.joinpath(item.build_name),
            targets=["install"],
            build_tool_args=build_args,
            **debug_conf,  # type: ignore
        )

    if conf.in_ci:
        run_command(ctx, "git", [
            "config",
            "--global",
            "--add",
            "safe.directory",
            deps_dir.joinpath("range-v3"),
        ])

    for item in get_external_deps_list(
            install_dir,
            is_emcc=ctx.config.emscripten.build,
    ):
        dep(item)

    log(CAT).info(f"Finished develop dependencies installation, {debug_conf}")
    generate_develop_deps_install_paths(ctx=ctx)
    log(CAT).info(f"Installed into {install_dir}")


@haxorg_task(dependencies=[build_release_archive])
def build_release_deps(
    ctx: TaskContext,
    testdir: Optional[str] = None,
    deps_install_dir: Optional[str] = None,
) -> None:
    "Test cpack-provided build"

    package_archive = get_script_root(ctx).joinpath(
        f"{ctx.config.HAXORG_NAME}-{ctx.config.HAXORG_VERSION}-Source.zip")

    with TemporaryDirectory() as tmpdir:
        if testdir:
            build_dir = Path(testdir)

        else:
            build_dir = Path(tmpdir)

        if build_dir.exists():
            shutil.rmtree(build_dir)

        build_dir.mkdir(parents=True, exist_ok=True)
        package_copy = build_dir.joinpath("target.zip")

        shutil.copy(package_archive, package_copy)
        unzip = plumbum.local["unzip"]
        unzip.run([
            str(package_copy),
            "-d",
            str(build_dir),
        ])

        log(CAT).info(f"Unzipped package to {build_dir}")
        src_root = build_dir.joinpath(
            f"{ctx.config.HAXORG_NAME}-{ctx.config.HAXORG_VERSION}-Source")
        src_build = build_dir.joinpath("build")

        install_dir = get_build_root(ctx).joinpath("deps_install")

        run_cmake_configure(
            ctx,
            build_dir=src_build,
            script_root=src_root,
            generator=ctx.config.build_conf.cmake_generator,
            args=[
                *cond(
                    deps_install_dir,
                    [cmake_opt("ORG_DEPS_INSTALL_ROOT", deps_install_dir)],
                    [],
                ),
                cmake_opt("ORG_DEPS_USE_PROTOBUF", False),
                cmake_opt("ORG_BUILD_IS_DEVELOP", False),
                cmake_opt("ORG_BUILD_TESTS", True),
                cmake_opt("ORG_BUILD_ASSUME_CLANG", False),
                cmake_opt("CMAKE_CXX_COMPILER", "clang++"),
                cmake_opt("CMAKE_C_COMPILER", "clang"),
                cmake_opt("ORG_DEPS_USE_ADAPTAGRAMS", False),
                cmake_opt("ORG_DEPS_USE_PACKAGED_BOOST", False),
                cmake_opt("CMAKE_PREFIX_PATH", [
                    install_dir.joinpath("lexy/lib/cmake/lexy"),
                    install_dir.joinpath("abseil/lib/cmake/absl"),
                    install_dir.joinpath("abseil/lib64/cmake/absl"),
                ]),
            ],
        )

        log(CAT).info("Completed cpack build configuration")

        run_cmake_build(
            ctx,
            build_dir=src_build,
            targets=["all"],
            stderr_debug=get_log_dir(ctx).joinpath("cpack_build_stderr.log"),
            stdout_debug=get_log_dir(ctx).joinpath("cpack_build_stdout.log"),
        )
