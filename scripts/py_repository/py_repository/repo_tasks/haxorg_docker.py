import itertools
from tempfile import TemporaryDirectory
from beartype import beartype
from pathlib import Path
from beartype.typing import List, Literal, Optional
import shutil
import docker
import docker.models.containers
import docker.types
import os

from py_ci.util_scripting import get_docker_cap_flags
from py_repository.repo_tasks.deps_build import build_develop_deps
from py_repository.repo_tasks.examples_build import build_examples, run_js_test_example
from py_repository.repo_tasks.haxorg_build import build_haxorg, install_haxorg_develop
from py_repository.repo_tasks.haxorg_codegen import generate_haxorg_sources, generate_python_protobuf_files
from py_repository.repo_tasks.haxorg_coverage import run_cxx_coverage_merge
from py_repository.repo_tasks.haxorg_docs import build_custom_docs
from py_repository.repo_tasks.haxorg_tests import run_py_tests
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_repository.repo_tasks.command_execution import clone_repo_with_uncommitted_changes, get_cmd_debug_file, run_command
from py_repository.repo_tasks.common import docker_user, ensure_clean_file, get_script_root
from py_repository.repo_tasks.config import HaxorgLogLevel, get_tmpdir
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import merge_dicts
from dataclasses import replace

CAT = __name__


@beartype
def docker_mnt(src: Path, dst: Path) -> List[str]:
    assert src.exists(), f"'{src}'"
    log(CAT).debug(f"Mounting docker '{src}' to '{dst}'")
    return ["--mount", f"type=bind,src={src},dst={dst}"]


@haxorg_task()
def build_docker_develop_image(ctx: TaskContext) -> None:
    run_command(ctx, "docker", ["rm", ctx.config.HAXORG_DOCKER_IMAGE], allow_fail=True)
    run_command(
        ctx,
        "docker",
        [
            "build",
            "-t",
            ctx.config.HAXORG_DOCKER_IMAGE,
            "-f",
            get_script_root(ctx, "scripts/py_repository/Dockerfile"),
            ".",
        ],
        print_output=True,
    )


@beartype
def stop_containers_from_image(image_name: str) -> None:
    client = docker.from_env()
    containers = client.containers.list(filters={"ancestor": image_name})
    for container in containers:
        container.stop()


@beartype
def get_docker_mounts(ctx: TaskContext, items: List[str], build_tmp: Path) -> List[docker.types.Mount]:
    mounts: List[docker.types.Mount] = []

    @beartype
    def docker_path(path: str) -> Path:
        return Path("/haxorg").joinpath(path)

    for it in items:
        mounts.append(
            docker.types.Mount(
                target=str(docker_path(it)),
                source=str(get_script_root(ctx, it)),
                type="bind",
            ))

    mounts.append(
        docker.types.Mount(
            target=str(docker_path("build")),
            source=str(build_tmp),
            type="bind",
        ))

    return mounts


@beartype
def get_container_var(container: docker.models.containers.Container, varname: str) -> str:
    exit_code, output = container.exec_run(
        cmd=["printenv", varname],
        demux=True,
    )
    assert output, f"No output from printenv, the variable {varname} is not defined in container"
    stdout, stderr = output
    value = stdout.decode("utf-8").strip() if stdout else ""
    return value


@haxorg_task(dependencies=[build_docker_develop_image])
def run_docker_develop_test(
        ctx: TaskContext,
        interactive: bool = False,
        build_dir: str = get_tmpdir("docker_develop", "build"),
) -> None:
    """Run docker"""

    HAXORG_BUILD_TMP = Path(build_dir)
    if not HAXORG_BUILD_TMP.exists():
        HAXORG_BUILD_TMP.mkdir(parents=True)

    stop_containers_from_image(ctx.config.HAXORG_DOCKER_IMAGE)

    client = docker.from_env()

    mount_items: List[str] = [
        "src",
        "scripts",
        "tests",
        "benchmark",
        "tasks.py",
        "examples",
        "docs",
        "pyproject.toml",
        "poetry.lock",
        "ignorelist.txt",
        ".git",
        "thirdparty",
        "CMakeLists.txt",
        "toolchain.cmake",
        "HaxorgConfig.cmake.in",
    ]

    mounts = get_docker_mounts(ctx, mount_items, Path(build_dir))

    cpu_count = os.cpu_count() or 6
    nano_cpus = int(cpu_count * 0.9 * 1e9)
    mem_limit = "20g"

    container: docker.models.containers.Container = client.containers.run(
        image=ctx.config.HAXORG_DOCKER_IMAGE,
        command="sleep infinity",
        mounts=mounts,
        detach=True,
        mem_limit=mem_limit,
        nano_cpus=nano_cpus,
        remove=False,
    )

    dctx = replace(ctx, docker_container=container, run_cache=set())
    dctx.config.use_unchanged_tasks = True
    # dctx.config.log_level = HaxorgLogLevel.VERBOSE
    dctx.repo_root = Path("/haxorg")
    dctx.config.workflow_log_dir = Path("/tmp/haxorg/docker_workflow_log_dir")

    TOOL = "/haxorg/toolchain"

    run_command(dctx, "ln", ["-sf", "/docker_toolchain", TOOL])
    run_command(dctx, "ls", ["-al", TOOL])
    container_path = get_container_var(container, "PATH")
    run_command(dctx, "poetry", ["install", "--no-root", "--without", "haxorg"])
    run_command(dctx, "git", ["config", "--global", "--add", "safe.directory", "/haxorg"])
    run_command(dctx, "git", ["config", "--global", "user.email", "you@example.com"])
    run_command(dctx, "git", ["config", "--global", "user.name", "Your Name"])

    dctx.run(run_develop_ci, ctx=dctx)

    # run_command(
    #     ctx,
    #     "docker",
    #     [
    #         "run",
    #         *itertools.chain(*(docker_mnt(
    #             src=get_script_root(it),
    #             dst=docker_path(it),
    #         ) for it in [
    #             "src",
    #             "scripts",
    #             "tests",
    #             "benchmark",
    #             "tasks.py",
    #             "examples",
    #             "docs",
    #             "pyproject.toml",
    #             "poetry.lock",
    #             "ignorelist.txt",
    #             ".git",
    #             "thirdparty",
    #             "CMakeLists.txt",
    #             "toolchain.cmake",
    #             "HaxorgConfig.cmake.in",
    #         ])),
    #         # Scratch directory for simplified local debugging and rebuilds if needed.
    #         *docker_mnt(HAXORG_BUILD_TMP, docker_path("build")),
    #         *(["-it"] if interactive else []),
    #         *get_docker_cap_flags(),
    #         "--rm",
    #         ctx.config.HAXORG_DOCKER_IMAGE,
    #         "./scripts/py_repository/poetry_with_deps.sh",
    #         *(["bash"] if interactive else [
    #             "./scripts/py_repository/py_repository/repo_tasks/workflow.py",
    #             "run",
    #             "--task",
    #             "run_develop_ci",
    #             "--config_override",
    #             "scripts/py_repository/py_repository/repo_tasks/haxorg_conf_develop_docker_ci.json",
    #         ]),
    #     ],
    #     print_output=True,
    # )


@haxorg_task(dependencies=[])
def run_docker_release_test(
    ctx: TaskContext,
    build_dir: str = get_tmpdir("docker_release", "build"),
    clone_dir: str = get_tmpdir("docker_release", "clone"),
    clone_code: Literal["none", "comitted", "all"] = "all",
    deps: bool = True,
    test: str = "python",
    build: bool = True,
    interactive: bool = False,
) -> None:
    CPACK_TEST_IMAGE = "docker-haxorg-cpack"
    dep_debug_stdout = get_cmd_debug_file("stdout")
    dep_debug_stderr = get_cmd_debug_file("stderr")

    ensure_clean_file(ctx, dep_debug_stderr)
    ensure_clean_file(ctx, dep_debug_stdout)

    debug_conf = dict(
        append_stderr_debug=True,
        append_stdout_debug=True,
        stdout_debug=dep_debug_stdout,
        stderr_debug=dep_debug_stderr,
    )

    @beartype
    def docker_path(path: str) -> Path:
        return Path("/haxorg/src").joinpath(path)

    run_command(
        ctx,
        "docker",
        ["rm", CPACK_TEST_IMAGE],
        allow_fail=True,
        **debug_conf,  # type: ignore
    )

    run_command(
        ctx,
        "docker",
        [
            "build",
            "-t",
            CPACK_TEST_IMAGE,
            "-f",
            get_script_root(ctx, "scripts/py_repository/cpack_build_in_fedora.dockerfile"),
            ".",
        ],
        **debug_conf,  # type: ignore
    )

    @beartype
    def run_docker(clone_dir: Path, build_dir: Path) -> None:
        source_prefix: Optional[Path] = None
        if clone_code == "all":
            if clone_dir.exists():
                shutil.rmtree(clone_dir)
            clone_repo_with_uncommitted_changes(
                ctx,
                src_repo=get_script_root(ctx),
                dst_repo=clone_dir,
            )

            source_prefix = clone_dir

        elif clone_code == "comitted":
            if clone_dir.exists():
                shutil.rmtree(clone_dir)
            run_command(
                ctx,
                "git",
                ["clone", get_script_root(ctx), clone_dir],
                **debug_conf,  # type: ignore
            )
            source_prefix = clone_dir

        else:
            source_prefix = clone_dir

        @beartype
        def pass_mnt(path: Optional[str] = None) -> Path:
            if path is None:
                if source_prefix:
                    return source_prefix

                else:
                    return get_script_root(ctx)

            else:
                if source_prefix:
                    assert source_prefix.is_absolute(), source_prefix
                    return source_prefix.joinpath(path)

                else:
                    return get_script_root(ctx, path)

        run_command(
            ctx,
            "docker",
            [
                "run",
                *docker_mnt(
                    src=get_script_root(ctx, "thirdparty"),
                    dst=docker_path("thirdparty"),
                ),
                *(["-it"] if interactive else []),
                *get_docker_cap_flags(),
                "--rm",
                *docker_user(),
                *docker_mnt(pass_mnt(), Path("/haxorg/src")),
                *docker_mnt(build_dir, Path("/haxorg/wip")),
                "-e",
                "PYTHONPATH=/haxorg/src/scripts/py_ci",
                "-e",
                f"HAXORG_THIRD_PARTY_DIR_PATH={docker_path('thirdparty')}",
                CPACK_TEST_IMAGE,
                *(["bash"] if interactive else [
                    # "ls",
                    # "-a",
                    # "/haxorg_wip",
                    "python",
                    "-m",
                    "py_ci.test_cpack_build",
                    invoke_opt("build", build),
                    invoke_opt("deps", deps),
                    f"--test={test}",
                ])
            ],
            **debug_conf,
        )

    def run_with_build_dir(build_dir: Path) -> None:
        if clone_dir:
            log(CAT).info(f"Specified clone directory, using it for docker")
            run_docker(clone_dir=Path(clone_dir), build_dir=build_dir)

        else:
            with TemporaryDirectory() as dir:
                log(CAT).info(
                    f"No docker clone directory specified, using temporary {dir}")
                run_docker(clone_dir=Path(dir), build_dir=build_dir)

    if build_dir:
        if not Path(build_dir).exists():
            Path(build_dir).mkdir(parents=True)

        run_with_build_dir(build_dir=Path(build_dir))

    else:
        with TemporaryDirectory() as dir:
            run_with_build_dir(build_dir=Path(dir))


@haxorg_task()
@beartype
def run_develop_ci(ctx: TaskContext) -> None:
    "Execute all CI tasks"
    conf = ctx.config

    log(CAT).info("Running binary task set")
    if conf.develop_ci_conf.deps:
        ctx.run(build_develop_deps, ctx=ctx)

    if conf.develop_ci_conf.install:
        ctx.run(install_haxorg_develop, ctx=ctx)

    if conf.develop_ci_conf.build:
        ctx.run(build_haxorg, ctx=ctx)

    if conf.develop_ci_conf.reflection:
        ctx.run(generate_haxorg_sources, ctx=ctx)

    if conf.develop_ci_conf.test:
        ctx.run(generate_python_protobuf_files, ctx=ctx)
        ctx.run(run_py_tests, ctx=ctx)

    if conf.develop_ci_conf.example:
        ctx.run(build_examples, ctx=ctx)

    if conf.develop_ci_conf.coverage and conf.instrument.coverage:
        ctx.run(run_cxx_coverage_merge, ctx=ctx)

    if conf.develop_ci_conf.docs:
        ctx.run(build_custom_docs, ctx=ctx)

    log(CAT).info("Running EMCC task set")
    emcc_conf = conf.model_copy()
    emcc_conf.emscripten.build = True
    emcc_conf.instrument.coverage = False
    emcc_conf.use.qt = False
    emcc_context = ctx.with_temp_config(emcc_conf)

    if conf.develop_ci_conf.emscripten_deps:
        emcc_context.run(build_develop_deps, ctx=emcc_context)

    if conf.develop_ci_conf.emscripten_build:
        emcc_context.run(build_haxorg, ctx=emcc_context)

    if conf.develop_ci_conf.emscripten_test:
        emcc_context.run(run_js_test_example, ctx=emcc_context)
