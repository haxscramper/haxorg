from py_scriptutils.files import get_haxorg_repo_root_path
from beartype.typing import List


def get_lldb_params() -> List[str]:
    lldb_py_script = str(
        get_haxorg_repo_root_path().joinpath("scripts/cxx_repository/lldb_script.py"))
    lldb_cmd_script = str(
        get_haxorg_repo_root_path().joinpath("scripts/cxx_repository/lldb-script.txt"))
    return [
        "--batch",
        "-o",
        f"command script import {lldb_py_script}",
        "-o",
        "run",
        "--source-on-crash",
        lldb_cmd_script,
    ]
