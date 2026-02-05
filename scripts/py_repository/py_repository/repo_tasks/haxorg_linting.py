import itertools

from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import ensure_existing_dir, get_script_root, get_workflow_out, get_workflow_tmp
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
