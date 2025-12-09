from beartype.typing import List

from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.haxorg_coverage import get_cxx_coverage_dir
from py_repository.repo_tasks.workflow_utils import TaskContext, haxorg_task
from py_repository.repo_tasks.haxorg_base import symlink_build
from py_repository.repo_tasks.haxorg_build import build_haxorg
from py_repository.repo_tasks.haxorg_codegen import generate_python_protobuf_files


@haxorg_task(dependencies=[build_haxorg, symlink_build, generate_python_protobuf_files])
def run_py_tests(ctx: TaskContext, arg: List[str] = []) -> None:
    """
    Execute the whole python test suite or run a single test file in non-interactive
    LLDB debugger to work on compiled component issues. 
    """

    args = arg
    env = dict()

    # env = get_py_env(ctx)
    if ctx.config.instrument.coverage:
        coverage_dir = get_cxx_coverage_dir()
        env["HAX_COVERAGE_OUT_DIR"] = str(coverage_dir)

    run_command(
        ctx,
        "poetry",
        [
            "run",
            "python",
            "scripts/py_repository/py_repository/coverage_collection/gen_coverage_cxx.py",
        ],
    )

    retcode, _, _ = run_command(
        ctx,
        "poetry",
        [
            "run",
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
        print_output=True,
    )

    if retcode != 0:
        exit(1)


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
        "poetry",
        [
            "run",
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
