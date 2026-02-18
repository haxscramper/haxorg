import itertools

from beartype import beartype
from beartype.typing import Any
from py_ci.data_build import (
    CmakeFlagConfig,
    CmakeOptConfig,
    ExternalDep,
    get_external_deps_list,
)
from py_ci.util_scripting import cmake_opt
from py_repository.repo_tasks.command_execution import (
    get_cmd_debug_file,
    run_cmake_build,
    run_cmake_configure,
    run_command,
)
from py_repository.repo_tasks.common import (
    check_path_exists,
    ensure_existing_dir,
    get_script_root,
)
from py_repository.repo_tasks.haxorg_base import (
    generate_develop_deps_install_paths,
    get_deps_build_dir,
    get_deps_install_dir,
)
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_scriptutils.algorithm import maybe_splice
from py_scriptutils.files import FileOperation
from py_scriptutils.script_logging import log

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
