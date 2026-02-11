import os
from pathlib import Path

from beartype.typing import List
from py_repository.repo_tasks.command_execution import (
    get_uv_develop_env_flags,
    get_uv_develop_sync_flags,
    run_command,
)
from py_repository.repo_tasks.haxorg_base import symlink_build
from py_repository.repo_tasks.haxorg_build import build_haxorg
from py_repository.repo_tasks.haxorg_codegen import generate_python_protobuf_files
from py_repository.repo_tasks.haxorg_coverage import get_cxx_coverage_dir
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_scriptutils.script_logging import log

CAT = __name__


@haxorg_task(dependencies=[build_haxorg, symlink_build, generate_python_protobuf_files])
def run_py_tests(ctx: TaskContext, arg: List[str] = []) -> None:
    """
    Execute the whole python test suite or run a single test file in non-interactive
    LLDB debugger to work on compiled component issues.
    """

    args = arg
    env = dict()

    if ctx.config.py_test_conf.extra_pytest_args:
        args.extend(ctx.config.py_test_conf.extra_pytest_args)

    # env = get_py_env(ctx)
    if ctx.config.instrument.coverage:
        coverage_dir = get_cxx_coverage_dir(ctx)
        env["HAX_COVERAGE_OUT_DIR"] = str(coverage_dir)

    if not ctx.config.py_test_conf.real_time_output_print:
        env["NO_COLOR"] = "1"
        args.append("--color=no")

    run_command(
        ctx,
        "uv",
        [
            "run",
            "--all-groups",
            *get_uv_develop_sync_flags(ctx),
            *get_uv_develop_env_flags(ctx),
            "python",
            "scripts/py_repository/py_repository/code_analysis/gen_coverage_cxx.py",
        ],
        print_output=ctx.config.py_test_conf.real_time_output_print,
    )

    retcode, stdout, stderr = run_command(
        ctx,
        "uv",
        [
            "run",
            "--all-groups",
            *get_uv_develop_sync_flags(ctx),
            *get_uv_develop_env_flags(ctx),
            "pytest",
            "-vv",
            "-ra",
            "-s",
            "--log-cli-level=DEBUG",
            "--tb=short",
            "--cov=scripts",
            "--cov-report=html",
            "--cov-context=test",
            "--disable-warnings",
            # "--cov-branch",
            *args,
        ],
        allow_fail=True,
        env=env,
        print_output=ctx.config.py_test_conf.real_time_output_print,
    )

    if not ctx.config.py_test_conf.real_time_output_print:
        log(CAT).info("PYTEST SCRIPT EXECUTION")
        log(CAT).info(f"{stdout}")
        log(CAT).info(f"{stderr}")

    if retcode != 0:
        raise RuntimeError("running py tests failed")


@haxorg_task(dependencies=[
    build_haxorg,
    generate_python_protobuf_files,
    symlink_build,
])
def run_py_script(ctx: TaskContext, script: str, arg: List[str] = []) -> None:
    """
    Run script with arguments with all environment variables set.
    Debug task.
    """
    run_command(
        ctx,
        "uv",
        [
            "run",
            *get_uv_develop_sync_flags(ctx),
            *get_uv_develop_env_flags(ctx),
            script,
            *arg,
        ],
    )


@haxorg_task(dependencies=[run_py_tests])
def run_py_tests_ci() -> None:
    """
    CI task that builds base lexer codegen before running the build
    """
    pass
