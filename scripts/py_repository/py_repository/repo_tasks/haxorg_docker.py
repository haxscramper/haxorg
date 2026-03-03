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
from py_ci.util_scripting import get_docker_cap_flags, get_threading_count
from py_repository.repo_tasks.command_execution import (
    clone_repo_with_uncommitted_changes,
    get_cmd_debug_file,
    get_python_binary,
    get_uv_develop_sync_flags,
    run_command,
)
from py_repository.repo_tasks.common import (
    ctx_read_text,
    ctx_write_text,
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
                       mappings: List[Tuple[str, Path] | str],
                       container_prefix: str = "/haxorg") -> List[docker.types.Mount]:
    """Create bind mounts from (container_relative_path, host_path) pairs."""

    def get_mappings():
        "nodoc"
        for m in mappings:
            if len(m) == 2:
                assert m[1].exists(), str(m)
                yield m
            else:
                assert Path(m).exists(), str(m)
                yield m, Path(m)

    return [
        docker.types.Mount(
            target=f"{container_prefix}/{name}" if name else container_prefix,
            source=str(host_path.resolve()),
            type="bind",
            read_only=False) for name, host_path in get_mappings()
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
