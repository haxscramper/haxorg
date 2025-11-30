import itertools
from beartype import beartype
from beartype.typing import List, Optional

from py_ci.data_build import CmakeFlagConfig, CmakeOptConfig, ExternalDep, get_external_deps_list
from py_ci.util_scripting import cmake_opt, get_j_cap
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_repository.repo_tasks.command_execution import get_cmd_debug_file, run_command
from py_repository.repo_tasks.common import ensure_existing_dir, get_script_root
from py_repository.repo_tasks.config import get_config
from py_repository.repo_tasks.haxorg_base import generate_develop_deps_install_paths, get_deps_build_dir, get_deps_install_dir, get_toolchain_path
from py_repository.repo_tasks.haxorg_build import build_release_archive
from py_scriptutils.algorithm import maybe_splice
from py_scriptutils.script_logging import log

CAT = __name__


@haxorg_task()
def validate_dependencies_install(ctx: TaskContext):
    install_dir = get_deps_install_dir().joinpath("paths.cmake")
    assert install_dir.exists(), f"No dependency paths found at '{install_dir}'"


@haxorg_task()
def build_develop_deps(ctx: TaskContext):
    "Install dependencies for cmake project development"
    conf = get_config()
    build_dir = get_deps_build_dir()
    ensure_existing_dir(build_dir)
    install_dir = get_deps_install_dir()
    ensure_existing_dir(install_dir)
    deps_dir = get_script_root().joinpath("thirdparty")

    dep_debug_stdout = get_cmd_debug_file("stdout")
    dep_debug_stderr = get_cmd_debug_file("stderr")

    debug_conf = dict(
        append_stderr_debug=True,
        append_stdout_debug=True,
        stdout_debug=dep_debug_stdout,
        stderr_debug=dep_debug_stderr,
    )

    @beartype
    def dep(item: ExternalDep):
        if 0 < len(conf.build_develop_deps_conf.build_whitelist) and item.build_name not in conf.build_develop_deps_conf.build_whitelist:
            return

        configure_args = list(
            itertools.chain(*[
                it.get_cli()
                for it in item.configure_args
                if isinstance(it, CmakeOptConfig) or not it.isBuild
            ]))

        log(CAT).info(f"Running build name='{item.build_name}' deps='{item.deps_name}'")
        if conf.build_develop_deps_conf.configure:
            run_command(
                "cmake",
                [
                    "-B",
                    build_dir.joinpath(item.build_name),
                    "-S",
                    deps_dir.joinpath(item.deps_name),
                    "-G",
                    "Ninja",
                    cmake_opt("CMAKE_INSTALL_PREFIX", install_dir.joinpath(
                        item.build_name)),
                    cmake_opt("CMAKE_BUILD_TYPE", "RelWithDebInfo"),
                    *([cmake_opt("CMAKE_TOOLCHAIN_FILE", get_toolchain_path())]
                      if item.is_bundled_toolchain else []),
                    *configure_args,
                    *maybe_splice(conf.build_develop_deps_conf.force, "--fresh"),
                ],
                **debug_conf,
            )

        build_args = list(
            itertools.chain(*[
                it.get_cli()
                for it in item.configure_args
                if isinstance(it, CmakeFlagConfig) and it.isBuild
            ]))

        run_command(
            "cmake",
            [
                "--build",
                build_dir.joinpath(item.build_name),
                "--target",
                "install",
                *get_j_cap(),
                *(["--", *build_args] if 0 < len(build_args) else []),
            ],
            **debug_conf,
        )

    if conf.in_ci:
        run_command("git", [
            "config",
            "--global",
            "--add",
            "safe.directory",
            deps_dir.joinpath("range-v3"),
        ])

    for item in get_external_deps_list(
            install_dir,
            is_emcc=get_config().emscripten.build,
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
):
    "Test cpack-provided build"

    package_archive = get_script_root().joinpath(
        f"{HAXORG_NAME}-{HAXORG_VERSION}-Source.zip")

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
        unzip = local["unzip"]
        unzip.run([
            str(package_copy),
            "-d",
            str(build_dir),
        ])

        log(CAT).info(f"Unzipped package to {build_dir}")
        src_root = build_dir.joinpath(f"{HAXORG_NAME}-{HAXORG_VERSION}-Source")
        src_build = build_dir.joinpath("build")

        install_dir = get_build_root().joinpath("deps_install")

        run_command(ctx, "cmake", [
            "-B",
            str(src_build),
            "-S",
            str(src_root),
            "-G",
            "Ninja",
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
        ])

        log(CAT).info("Completed cpack build configuration")

        run_command(
            ctx,
            "cmake",
            [
                "--build",
                str(src_build),
                "--target",
                "all",
                *get_j_cap(),
            ],
            stderr_debug=get_log_dir().joinpath("cpack_build_stderr.log"),
            stdout_debug=get_log_dir().joinpath("cpack_build_stdout.log"),
        )
