import itertools

from py_ci.util_scripting import get_threading_count
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import (
    ensure_existing_dir,
    get_script_root,
    get_workflow_out,
    get_workflow_tmp,
)
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_scriptutils.script_logging import log

CAT = __name__


@haxorg_task()
def run_mypy(ctx: TaskContext) -> None:
    script_files = list(
        itertools.chain(
            get_script_root(ctx, "scripts").rglob("*.py"),
            get_script_root(ctx, "tests/python").rglob("*.py"),
        ))

    script_files = [f for f in script_files if (".venv" not in str(f))]
    all_outputs = []

    cache_dir = get_workflow_tmp(ctx, "mypy_cache")
    ensure_existing_dir(ctx, cache_dir)

    had_fails = False
    for py_file in script_files:
        code, stdout, stderr = run_command(
            ctx,
            "uv",
            [
                "run",
                "mypy",
                str(py_file),
                "--show-error-codes",
                "--show-error-context",
                "--follow-imports=silent",
                "--cache-dir",
                str(cache_dir),
                "--config-file",
                get_script_root(ctx, "pyproject.toml"),
            ],
            allow_fail=True,
            capture=True,
        )

        if code != 0:
            had_fails = True

        file_output = f"File: {py_file}\n"
        file_output += f"Exit Code: {code}\n"
        if stdout:
            file_output += f"STDOUT:\n{stdout}\n"
        if stderr:
            file_output += f"STDERR:\n{stderr}\n"
        file_output += "-" * 80 + "\n"

        if code != 0:
            all_outputs.append(file_output)

    report_content = "MyPy Analysis Report\n"
    report_content += "=" * 80 + "\n"
    report_content += "".join(all_outputs)

    report_file = get_workflow_out(ctx, "mypy.txt")
    report_file.write_text(report_content, encoding="utf-8")
    if had_fails:
        log(CAT).warning(f"Wrote full report to {report_file}")

    # assert not had_fails


@haxorg_task()
def run_codechecker(ctx: TaskContext):
    "run codechecker on the whole cxx code"
    tool_dir = get_script_root(ctx).joinpath(
        "scripts/py_repository/py_repository/code_analysis/codechecker_environment")

    compile_commands = get_script_root(ctx, "build/haxorg/compile_commands.json")
    analysis_artifact_outdir = get_script_root(ctx, "build/codechecker_result")
    analysis_artifact_render = get_script_root(ctx, "build/codechecker_render")
    analysis_artifact_structured = get_script_root(ctx, "build/codechecker_structured")
    ensure_existing_dir(ctx, analysis_artifact_outdir)

    run_cmd = [
        "--project",
        str(tool_dir),
        "run",
        "CodeChecker",
    ]

    jobs_cmd = [
        "--jobs",
        str(int(get_threading_count() * 0.5)),
    ]

    skip_cmd = [
        "--skip",
        str(tool_dir.joinpath("skip.txt")),
    ]

    # run_command(
    #     ctx,
    #     "uv",
    #     [
    #         *run_cmd,
    #         "analyze",
    #         compile_commands,
    #         "--ctu-collect",
    #         *skip_cmd,
    #         "--output",
    #         analysis_artifact_outdir,
    #         *jobs_cmd,
    #     ],
    #     print_output=True,
    # )

    # run_command(
    #     ctx,
    #     "uv",
    #     [
    #         *run_cmd,
    #         "analyze",
    #         compile_commands,
    #         "--ctu-analyze",
    #         *skip_cmd,
    #         "--output",
    #         analysis_artifact_outdir,
    #         *jobs_cmd,
    #     ],
    #     print_output=True,
    #     allow_fail=True,
    # )

    # run_command(
    #     ctx,
    #     "uv",
    #     [
    #         *run_cmd,
    #         "parse",
    #         analysis_artifact_outdir,
    #         "--export",
    #         "html",
    #         "--output",
    #         str(analysis_artifact_render),
    #     ],
    #     print_output=True,
    #     allow_fail=True,
    # )

    code, stdout, stderr = run_command(
        ctx,
        "uv",
        [
            *run_cmd,
            "parse",
            analysis_artifact_outdir,
            "--print-steps",
        ],
        capture=True,
        allow_fail=True,
    )

    ensure_existing_dir(ctx, analysis_artifact_structured)
    analysis_artifact_structured.joinpath("reports.txt").write_text(stdout)

    # run_command(
    #     ctx,
    #     "uv",
    #     [
    #         *run_cmd,
    #         "store",
    #         analysis_artifact_outdir,
    #         "--name",
    #         "haxorg",
    #         "--url",
    #         "localhost:8001/Default",
    #     ],
    #     print_output=True,
    #     allow_fail=True,
    # )
