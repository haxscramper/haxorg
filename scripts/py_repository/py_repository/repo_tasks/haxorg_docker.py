from dataclasses import replace
import itertools
import os
from pathlib import Path
import shutil
from tempfile import TemporaryDirectory

from beartype import beartype
from beartype.typing import Any, List, Literal, Optional, Tuple
import docker
import docker.errors
import docker.models.containers
import docker.types
from py_ci.util_scripting import get_docker_cap_flags
from py_repository.repo_tasks.command_execution import (
    clone_repo_with_uncommitted_changes,
    get_cmd_debug_file,
    get_python_binary,
    get_uv_develop_sync_flags,
    run_command,
)
from py_repository.repo_tasks.common import (
    docker_user,
    ensure_clean_file,
    ensure_existing_dir,
    get_build_root,
    get_script_root,
)
from py_repository.repo_tasks.config import get_tmpdir, HaxorgLogLevel
from py_repository.repo_tasks.deps_build import build_develop_deps
from py_repository.repo_tasks.docker_fuse import (
    cleanup_overlay_mount_points,
    create_overlay_mount_points,
)
from py_repository.repo_tasks.examples_build import (
    build_examples,
    run_examples,
    run_js_test_example,
)
from py_repository.repo_tasks.haxorg_build import build_haxorg, install_haxorg_develop
from py_repository.repo_tasks.haxorg_codegen import (
    generate_binary_size_report,
    generate_haxorg_sources,
    generate_include_graph,
    generate_python_protobuf_files,
)
from py_repository.repo_tasks.haxorg_coverage import run_cxx_coverage_merge
from py_repository.repo_tasks.haxorg_docs import build_custom_docs
from py_repository.repo_tasks.haxorg_tests import run_py_tests
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import merge_dicts

CAT = __name__


@beartype
def docker_mnt(src: Path, dst: Path) -> List[str]:
    assert src.exists(), f"'{src}'"
    log(CAT).debug(f"Mounting docker '{src}' to '{dst}'")
    return ["--mount", f"type=bind,src={src},dst={dst}"]


def create_bind_mounts(ctx: TaskContext,
                       mappings: List[Tuple[str, Path]],
                       container_prefix: str = "/haxorg") -> List[docker.types.Mount]:
    """Create bind mounts from (container_relative_path, host_path) pairs."""
    return [
        docker.types.Mount(
            target=f"{container_prefix}/{name}" if name else container_prefix,
            source=str(host_path.resolve()),
            type="bind",
            read_only=False) for name, host_path in mappings
    ]


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
def get_docker_mount(ctx: TaskContext, docker_name: str,
                     local_path: Path) -> docker.types.Mount:

    @beartype
    def docker_path(path: str) -> Path:
        name_path = Path(path)
        if name_path.is_absolute():
            return name_path

        else:
            return Path("/haxorg").joinpath(path)

    return docker.types.Mount(
        target=str(docker_path(docker_name)),
        source=str(local_path),
        type="bind",
    )


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
        build_dir: Path = get_tmpdir("docker_develop", "build"),
        uv_cache: Path = get_tmpdir("docker_develop", "uv_venv"),
        uv_venv: Path = get_tmpdir("docker_develop", "uv_venv"),
) -> None:
    """Run docker"""

    ensure_existing_dir(ctx, build_dir)
    ensure_existing_dir(ctx, uv_cache)
    ensure_existing_dir(ctx, uv_venv)

    stop_containers_from_image(ctx.config.HAXORG_DOCKER_IMAGE)

    client = docker.from_env()

    mounts: List[docker.types.Mount] = list()
    script_root = Path(get_script_root(ctx))
    mounts = create_bind_mounts(ctx, [(name, script_root / name) for name in [
        "src",
        "scripts",
        "tests",
        "benchmark",
        "tasks.py",
        "examples",
        "docs",
        "pyproject.toml",
        "uv.lock",
        "ignorelist.txt",
        ".git",
        "thirdparty",
        "CMakeLists.txt",
        "toolchain.cmake",
        "HaxorgConfig.cmake.in",
    ]] + [
        ("build", build_dir),
        ("uv_cache", uv_cache),
        ("uv_venv", uv_venv),
    ])

    cpu_count = os.cpu_count() or 6
    nano_cpus = int(cpu_count * 0.9 * 1e9)
    mem_limit = "20g"

    mounts = create_overlay_mount_points(
        ctx,
        mounts=mounts,
        cow_root=get_tmpdir("docker_develop_cow"),
    )

    container: docker.models.containers.Container = client.containers.run(
        image=ctx.config.HAXORG_DOCKER_IMAGE,
        command="sleep infinity",
        mounts=mounts,
        mem_limit=mem_limit,
        nano_cpus=nano_cpus,
        remove=False,
        detach=True,
    )

    dctx = replace(ctx, docker_container=container, run_cache=set())
    dctx.config.log_level = HaxorgLogLevel.VERBOSE
    dctx.config.use_unchanged_tasks = True
    dctx.repo_root = Path("/haxorg")
    dctx.config.workflow_log_dir = Path("/tmp/haxorg/docker_workflow_log_dir")
    dctx.config.emscripten.toolchain = "/opt/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"

    container_path = get_container_var(container, "PATH")
    run_command(dctx, "uv", ["sync", "--all-groups", *get_uv_develop_sync_flags(dctx)])
    run_command(dctx, "git", ["config", "--global", "--add", "safe.directory", "*"])
    run_command(dctx, "git", ["config", "--global", "user.email", "you@example.com"])
    run_command(dctx, "git", ["config", "--global", "user.name", "Your Name"])

    dctx.run(run_develop_ci, ctx=dctx)


@beartype
def _run_docker_release_test_impl(
    ctx: TaskContext,
    clone_dir_path: Path,
    build_dir_path: Path,
    clone_code: str,
) -> None:
    """
    Implementation of the docker release test runner
    """

    source_prefix: Optional[Path] = None
    if clone_code == "all":
        if clone_dir_path.exists():
            shutil.rmtree(clone_dir_path)
        clone_repo_with_uncommitted_changes(
            ctx,
            src_repo=get_script_root(ctx),
            dst_repo=clone_dir_path,
        )
        source_prefix = clone_dir_path

    elif clone_code == "comitted":
        if clone_dir_path.exists():
            shutil.rmtree(clone_dir_path)
        client_low = docker.APIClient()
        import subprocess
        subprocess.run(
            ["git", "clone",
             str(get_script_root(ctx)),
             str(clone_dir_path)],
            check=True,
        )
        source_prefix = clone_dir_path

    else:
        source_prefix = clone_dir_path

    assert source_prefix
    assert source_prefix.exists()

    environment = {
        "PYTHONPATH": "/haxorg/src/scripts/py_ci",
    }

    cap_add = ["SYS_PTRACE"]
    client = docker.from_env()

    mounts = create_bind_mounts(
        ctx,
        [
            ("thirdparty", Path(get_script_root(ctx, "thirdparty"))),
            ("src", source_prefix),
            ("wip", build_dir_path),
        ],
        container_prefix="/haxorg",
    )

    cow_root = get_tmpdir("docker_release_cow")
    mounts = create_overlay_mount_points(ctx, mounts=mounts, cow_root=cow_root)

    container: docker.models.containers.Container = client.containers.run(
        ctx.config.HAXORG_DOCKER_RELEASE_IMAGE,
        command="sleep infinity",
        mounts=mounts,
        environment=environment,
        cap_add=cap_add,
        remove=True,
        detach=True,
    )

    dctx = replace(ctx, docker_container=container, run_cache=set())
    dctx.config.log_level = HaxorgLogLevel.VERBOSE
    dctx.config.use_unchanged_tasks = True
    dctx.repo_root = Path("/haxorg")
    dctx.config.workflow_log_dir = Path("/tmp/haxorg/docker_workflow_log_dir")

    python_binary = get_python_binary(dctx)
    log(CAT).info(f"Using python binary {python_binary}")

    run_command(dctx, "git", [
        "config",
        "--global",
        "safe.directory",
        "*",
    ])

    try:
        pass

    finally:
        cleanup_overlay_mount_points(ctx, cow_root=cow_root)


@haxorg_task(dependencies=[])
def run_docker_release_test(
    ctx: TaskContext,
    build_dir: Path = get_tmpdir("docker_release", "build"),
    clone_dir: Path = get_tmpdir("docker_release", "clone"),
    clone_code: Literal["none", "comitted", "all"] = "all",
) -> None:
    """
    Run the release test set in the docker container.
    """

    dep_debug_stdout = get_cmd_debug_file("stdout")
    dep_debug_stderr = get_cmd_debug_file("stderr")

    ensure_clean_file(ctx, dep_debug_stderr)
    ensure_clean_file(ctx, dep_debug_stdout)

    client = docker.from_env()

    @beartype
    def write_logs(container: docker.models.containers.Container) -> None:
        logs = container.logs(stdout=True, stderr=False)
        with open(dep_debug_stdout, "ab") as f:
            f.write(logs)
        logs = container.logs(stdout=False, stderr=True)
        with open(dep_debug_stderr, "ab") as f:
            f.write(logs)

    try:
        old_container = client.containers.get(ctx.config.HAXORG_DOCKER_RELEASE_IMAGE)
        old_container.remove(force=True)
    except docker.errors.NotFound:
        pass

    dockerfile_path = Path(
        get_script_root(ctx, "scripts/py_repository/fedora_release.dockerfile"))
    build_context_path = Path(get_script_root(ctx))

    def print_build_logs(build_logs: List[Any]) -> None:
        for log_entry in build_logs:
            if hasattr(log_entry, 'get'):
                if 'stream' in log_entry:
                    print(log_entry['stream'].strip())
            else:
                print(log_entry.strip())

    try:
        image, build_logs = client.images.build(
            path=str(build_context_path),
            dockerfile=str(dockerfile_path),
            tag=ctx.config.HAXORG_DOCKER_RELEASE_IMAGE,
            rm=True  # Remove intermediate containers
        )

        print_build_logs(build_logs)

    except docker.errors.BuildError as e:
        print("Build failed with error:")
        print_build_logs(e.build_log)
        raise

    @beartype
    def run_with_build_dir(build_dir_path: Path) -> None:
        "nodoc"
        if clone_dir:
            log(CAT).info("Specified clone directory, using it for docker")
            _run_docker_release_test_impl(
                ctx,
                clone_dir_path=Path(clone_dir),
                build_dir_path=build_dir_path,
                clone_code=clone_code,
            )
        else:
            with TemporaryDirectory() as dir:
                log(CAT).info(
                    f"No docker clone directory specified, using temporary {dir}")
                _run_docker_release_test_impl(
                    ctx,
                    clone_dir_path=Path(dir),
                    build_dir_path=build_dir_path,
                    clone_code=clone_code,
                )

    if build_dir:
        build_dir_path = Path(build_dir)
        if not build_dir_path.exists():
            build_dir_path.mkdir(parents=True)
        run_with_build_dir(build_dir_path=build_dir_path)
    else:
        with TemporaryDirectory() as dir:
            run_with_build_dir(build_dir_path=Path(dir))


@haxorg_task()
@beartype
def run_develop_ci(ctx: TaskContext) -> None:
    "Execute all CI tasks"
    conf = ctx.config

    if conf.develop_ci_conf.coverage:
        for file in get_build_root(ctx).rglob("*.gcda"):
            file.unlink()

    log(CAT).info("Running binary task set")
    if conf.develop_ci_conf.deps:
        ctx.run(build_develop_deps, ctx=ctx)

    if conf.develop_ci_conf.install:
        ctx.run(install_haxorg_develop, ctx=ctx)

    if conf.develop_ci_conf.build:
        ctx.run(build_haxorg, ctx=ctx)

    if conf.develop_ci_conf.example_build:
        ctx.run(build_examples, ctx=ctx)

    if conf.develop_ci_conf.reflection:
        ctx.run(generate_haxorg_sources, ctx=ctx)

    if conf.develop_ci_conf.test:
        ctx.run(generate_python_protobuf_files, ctx=ctx)
        ctx.run(run_py_tests, ctx=ctx)

    if conf.develop_ci_conf.example_run:
        ctx.run(run_examples, ctx=ctx)

    if conf.develop_ci_conf.coverage:
        assert conf.instrument.coverage, "Coverage was enabled in the workflow develop CI configuration, but not in the build"
        ctx.run(run_cxx_coverage_merge, ctx=ctx)

    if conf.develop_ci_conf.docs:
        ctx.run(build_custom_docs, ctx=ctx)

    if conf.develop_ci_conf.include_graph:
        ctx.run(generate_include_graph, ctx=ctx)

    if conf.develop_ci_conf.symbol_size:
        ctx.run(generate_binary_size_report, ctx=ctx)

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
