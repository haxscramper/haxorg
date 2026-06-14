import json
from pathlib import Path

from beartype import beartype
from beartype.typing import Optional
import plumbum
import plumbum.commands.base
from py_scriptutils.auto_lldb import get_lldb_params
from py_scriptutils.files import get_haxorg_repo_root_path
from py_scriptutils.os_utils import json_path_serializer
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import merge_dicts
from pydantic import BaseModel, Field


@beartype
def run_forensics(
    dir: Path,
    params: dict = dict(),
    db: Optional[str] = None,
    with_debugger: bool = False,
    verbose_consistency_checks: bool = False,
) -> tuple[int, str, str]:
    tool_path = str(get_haxorg_repo_root_path().joinpath("build/haxorg/code_forensics"))

    params = merge_dicts([{
        "out": {
            "db_path": db,
        },
        "config": {
            "verbose_consistency_checks": verbose_consistency_checks,
        },
    }, params, {
        "repo": {
            "path": str(dir),
            "branch": "master"
        }
    }])

    if with_debugger:
        run_parameters = [tool_path, *get_lldb_params(), "--", json.dumps(params)]
        code, stdout, stderr = plumbum.local["lldb"].with_env(LD_PRELOAD="").run(
            tuple(run_parameters))
        print(run_parameters)
        if code != 0:
            log().warning(f"{tool_path} run failed")
            log().warning(stdout)
            log().warning(stderr)

        return code, stdout, stderr

    else:
        return plumbum.local[tool_path].with_env(LD_PRELOAD="").run(
            (json.dumps(params, default=json_path_serializer)))
