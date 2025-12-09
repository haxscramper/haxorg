
import json
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import get_build_root, get_lldb_py_import, get_lldb_source_on_crash, get_script_root
from py_repository.repo_tasks.haxorg_build import build_haxorg
from py_repository.repo_tasks.workflow_utils import TaskContext, haxorg_task


@haxorg_task(dependencies=[build_haxorg])
def haxorg_code_forensics(ctx: TaskContext, debug: bool = False) -> None:
    "Generate code forensics dump for the repository"
    tool = get_build_root("haxorg/code_forensics")
    config = {
        "repo": {
            "path": str(get_script_root()),
            "branch": "master"
        },
        "out": {
            "text_dump": "/tmp/code_forenics.txt"
        },
    }
    if debug:
        run_command(ctx, "lldb", [
            str(tool),
            "--batch",
            *get_lldb_py_import(),
            "-o",
            "run",
            *get_lldb_source_on_crash(),
            json.dumps(config),
        ])
    else:
        run_command(ctx, tool, [json.dumps(config)])

