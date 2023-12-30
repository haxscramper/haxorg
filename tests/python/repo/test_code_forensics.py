import pytest
import json
from tempfile import NamedTemporaryFile, TemporaryDirectory, mktemp
from plumbum import local
from py_scriptutils.files import get_haxorg_repo_root_path
from beartype import beartype
from beartype.typing import Dict, Optional, Type
from types import TracebackType
from py_scriptutils.toml_config_profiler import merge_dicts
from pathlib import Path
from datetime import datetime
from dataclasses import dataclass
import sqlite3
import pandas as pd
import shutil

from rich.console import Console
from rich.table import Column, Table, Style
from rich import box


@beartype
def print_df_rich(df: pd.DataFrame, title: str):
    console = Console()
    table = Table(show_lines=False,
                  box=box.ASCII,
                  padding=(0, 1),
                  show_edge=False,
                  title=f"[red]{title}[/red]",
                  title_justify="left")

    # Add columns to the table
    for column in df.columns:
        table.add_column(str(column))

    # Add rows to the table, with specific formatting
    for index, row in df.iterrows():
        row_data = []
        for item in row:
            if isinstance(item, (int, float)):
                # Format numbers with cyan color
                row_data.append(f"[cyan]{item}[/cyan]")
            elif isinstance(item, str):
                # Quote strings and highlight in yellow
                row_data.append(f"[yellow]\"{item.strip()}\"[/yellow]")
            else:
                row_data.append(str(item))
        table.add_row(*row_data)

    console.print(table)


@beartype
def get_git(dir: Path):
    assert dir.exists()
    git = local["git"].with_cwd(dir)
    return git


@beartype
def git_init_repo(dir: Path):
    get_git(dir).run(("init"))


@beartype
def git_write_files(dir: Path, files: Dict[str, str]):
    for path, content in files.items():
        path = Path(dir).joinpath(path)
        if not path.parent.exists():
            path.parent.mkdir(parents=True)

        with open(path, "w") as file:
            file.write(content)


@beartype
def git_add(dir: Path):
    get_git(dir).run(("add", "."))


@beartype
def git_commit(dir: Path,
               message: str,
               date: datetime = datetime.now(),
               author: str = "haxorg-test-author",
               email="haxorg-test-email@email.com"):
    git = get_git(dir)
    git = git.with_env(GIT_AUTHOR_DATE=date.strftime("%Y-%m-%d %H:%M:%S"),
                       GIT_COMMITTER_DATE=date.strftime("%Y-%m-%d %H:%M:%S"))
    git.run(("commit", f"--author={author} <{email}>", "-m", message))


@beartype
def run_forensics(dir: Path, params: dict) -> tuple[int, str, str]:
    run = local[str(get_haxorg_repo_root_path().joinpath(
        "build/haxorg/scripts/cxx_repository/code_forensics"))]
    params = merge_dicts([params, {"repo": {"path": str(dir), "branch": "master"}}])

    print(json.dumps(params))
    return run.run((json.dumps(params)))


@beartype
@dataclass
class GitTestRepository:
    startFiles: Dict[str, str]
    db: Optional[str] = ""
    dir: Optional[TemporaryDirectory | Path] = None
    initMessage: str = "init"
    fixedDir: Optional[str] = None

    def git_dir(self) -> Path:
        return self.dir if isinstance(self.dir, Path) else Path(self.dir.name)

    def __enter__(self):
        if self.fixedDir:
            self.dir = Path(self.fixedDir)
            if self.dir.exists():
                shutil.rmtree(self.dir)

            self.dir.mkdir()

        else:
            self.dir = TemporaryDirectory()
            self.dir.__enter__()

        git_init_repo(self.git_dir())
        git_write_files(self.git_dir(), self.startFiles)
        git_add(self.git_dir())
        git_commit(self.git_dir(), self.initMessage)
        self.db = mktemp(suffix=".sqlite")
        return self

    def __exit__(self, exc_type: Optional[Type[BaseException]],
                 exc_value: Optional[BaseException],
                 traceback: Optional[TracebackType]) -> Optional[bool]:
        self.dir.__exit__(exc_type, exc_value, traceback)
        if exc_type is not None:
            return False

        db = Path(self.db)
        if db.exists() and not self.fixedDir:
            db.unlink()


def print_connection_tables(conn: sqlite3.Connection):
    tables = pd.read_sql_query("SELECT name FROM sqlite_master WHERE type='table';", conn)

    print("")
    for table_name in tables['name'].tolist():
        if table_name not in ["FileTrack"]:
            df = pd.read_sql_query(f"SELECT * from {table_name}", conn)
            print_df_rich(df, title=table_name)


def test_can_run_dir():
    with GitTestRepository({"a": "init_commit_content"},
                           fixedDir="/tmp/fixed_git_dir_1") as repo:
        assert not Path(repo.db).exists(), repo.db

        git_write_files(repo.git_dir(), {"a": "line_one_edit\nline_two_edit"})
        git_add(repo.git_dir())
        git_commit(repo.git_dir(), "second")

        _, stdout, stderr = run_forensics(
            repo.git_dir(),
            {"out": {
                "db_path": str(repo.db),
                "text_dump": "/tmp/test_run.txt",
                "graphviz": "/tmp/graph.dot"
            }})
        
        assert Path(repo.db).exists(), repo.db
        conn = sqlite3.connect(repo.db)
        print_connection_tables(conn)
        print(stdout)
        print(stderr)
