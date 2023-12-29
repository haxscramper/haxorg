import pytest
import json
from tempfile import NamedTemporaryFile, TemporaryDirectory, mktemp
from plumbum import local
from py_scriptutils.files import get_haxorg_repo_root_path
from beartype import beartype
from beartype.typing import Dict
from py_scriptutils.toml_config_profiler import merge_dicts
from pathlib import Path

@beartype
def get_git(dir: str):
    assert Path(dir).exists()
    git = local["git"].with_cwd(dir)
    return git 

@beartype
def git_init_repo(dir: str):
    get_git(dir).run(("init"))


@beartype
def git_write_files(dir: str, files: Dict[str, str]):
    for path, content in files.items():
        path = Path(dir).joinpath(path)
        if not path.parent.exists():
            path.parent.mkdir(parents=True)

        with open(path, "w") as file:
            file.write(content)


@beartype
def git_add(dir: str):
    get_git(dir).run(("add", "."))

@beartype
def git_commit(dir: str, message: str):
    get_git(dir).run(("commit", "-m", message))   

@beartype
def run_forensics(dir: str, params: dict):
    run = local[str(get_haxorg_repo_root_path().joinpath("build/haxorg/scripts/cxx_repository/code_forensics"))]
    params = merge_dicts([params, {
        "repo": {
            "path": dir,
            "branch": "master"
        }
    }])

    run.run((json.dumps(params)))



def test_can_run_dir():
    with TemporaryDirectory() as dir:
        git_init_repo(dir)
        git_write_files(dir, {"a": "b"})
        git_add(dir)
        git_commit(dir, "init")
        db = mktemp(suffix=".sqlite")
        assert not Path(db).exists(), db
        run_forensics(dir, {
            "out": {
                "db_path": db
            }        
        })

        assert Path(db).exists(), db
