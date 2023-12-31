import pytest
import json
from tempfile import NamedTemporaryFile, TemporaryDirectory, mktemp
from plumbum import local
from py_scriptutils.files import get_haxorg_repo_root_path
from beartype import beartype
from beartype.typing import Dict, Optional, Type, List
from types import TracebackType
from py_scriptutils.toml_config_profiler import merge_dicts
from pathlib import Path
from datetime import datetime
from dataclasses import dataclass
import sqlite3
import pandas as pd
import shutil
from pprint import pprint

from rich.console import Console
from rich.table import Column, Table, Style
from rich import box
from sqlalchemy import create_engine, Engine
import io


@beartype
def print_df_rich(df: pd.DataFrame, title: str, file: Optional[io.TextIOWrapper] = None):
    console = Console(file=file, force_terminal=False,
                      color_system=None) if file else Console()

    table = Table(show_lines=False,
                  box=box.ASCII,
                  padding=(0, 1),
                  show_edge=False,
                  title=f"[red]{title}[/red]",
                  min_width=len(title),
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
def git_move_files(dir: Path, source: str, target: str):
    dir.joinpath(source).rename(dir.joinpath(target))


@beartype
def git_remove_files(dir: Path, file: str):
    dir.joinpath(file).unlink()

@beartype
def git_add(dir: Path):
    get_git(dir).run(("add", "."))


@beartype
def git_commit(dir: Path,
               message: str,
               date: datetime = datetime.now(),
               author: str = "haxorg-test-author",
               email="haxorg-test-email@email.com"):
    git_add(dir)
    git = get_git(dir)
    git = git.with_env(GIT_AUTHOR_DATE=date.strftime("%Y-%m-%d %H:%M:%S"),
                       GIT_COMMITTER_DATE=date.strftime("%Y-%m-%d %H:%M:%S"))
    git.run(("commit", f"--author={author} <{email}>", "-m", message))


@beartype
def run_forensics(dir: Path,
                  params: dict = {},
                  db: Optional[str] = None) -> tuple[int, str, str]:
    run = local[str(get_haxorg_repo_root_path().joinpath(
        "build/haxorg/scripts/cxx_repository/code_forensics"))]
    params = merge_dicts([{
        "out": {
            "db_path": db
        }
    }, params, {
        "repo": {
            "path": str(dir),
            "branch": "master"
        }
    }])

    return run.run((json.dumps(params)))


@beartype
@dataclass
class GitTestRepository:
    startFiles: Dict[str, str]
    db: Optional[str] = ""
    dir: Optional[TemporaryDirectory | Path] = None
    initMessage: str = "init"
    fixedDir: Optional[str] = None
    fixedDb: Optional[str] = None

    def git_dir(self) -> Path:
        return self.dir if isinstance(self.dir, Path) else Path(self.dir.name)
    
    def get_engine(self) -> Engine:
        return create_engine("sqlite:///" + self.db)

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
        git_commit(self.git_dir(), self.initMessage)

        if self.fixedDb:
            self.db = self.fixedDb

        else:
            self.db = mktemp(suffix=".sqlite")

        return self

    def __exit__(self, exc_type: Optional[Type[BaseException]],
                 exc_value: Optional[BaseException],
                 traceback: Optional[TracebackType]) -> Optional[bool]:
        self.dir.__exit__(exc_type, exc_value, traceback)
        if exc_type is not None:
            return False

        db = Path(self.db)
        if db.exists() and not self.fixedDb:
            db.unlink()


@beartype
def print_connection_tables(engine: Engine,
                            exclude: List[str] = [],
                            file: Optional[io.TextIOWrapper] = None):
    tables = pd.read_sql_query("SELECT name FROM sqlite_master WHERE type='table' OR type='view';",
                               engine)

    print("", file=file)
    for table_name in tables['name'].tolist():
        if table_name not in exclude:
            df = pd.read_sql_table(table_name, engine)
            print_df_rich(df, title=table_name, file=file)


def test_can_run_dir():
    with GitTestRepository({"a": "fixed_line\ninit_commit_content"},
                           fixedDir="/tmp/fixed_git_dir_1",
                           fixedDb="/tmp/result.sqlite") as repo:

        git_write_files(repo.git_dir(), {"a": "fixed_line\nline_1_edit1\nline_2_edit1"})
        git_commit(repo.git_dir(), "second")

        git_write_files(repo.git_dir(), {"a": "fixed_line\nline_1_edit2\nline_2_edit1"})
        git_commit(repo.git_dir(), "third")

        _, stdout, stderr = run_forensics(
            repo.git_dir(), {
                "out": {
                    "db_path": str(repo.db),
                    "text_dump": "/tmp/test_run.txt",
                    "graphviz": "/tmp/graph.dot",
                    "perfetto": "/tmp/code_forensics.pftrace"
                }
            })

        assert Path(repo.db).exists(), repo.db
        engine = repo.get_engine()
        df_string = pd.read_sql_table("String", engine)["text"].to_list()
        assert "init_commit_content" in df_string
        assert "line_1_edit1" in df_string
        assert "line_1_edit2" in df_string
        assert "line_2_edit1" in df_string
        assert "line_2_edit1" in df_string
        assert df_string.count("fixed_line") == 1

        df_commits = [
            c.strip()
            for c in pd.read_sql_table("GitCommit", engine)["message"].to_list()
        ]

        assert "second" in df_commits
        assert "init" in df_commits

        df_section_lines = pd.read_sql_table("ViewFullFileSectionLines", engine)
        section_versions = df_section_lines.groupby(["section_id"])
        assert len(section_versions) == 3
        commit1, commit2, commit3 = [group for _, group in section_versions]
        assert commit1["text"].to_list() == ["fixed_line", "init_commit_content"]
        assert commit2["text"].to_list() == ["fixed_line", "line_1_edit1", "line_2_edit1"]
        assert commit3["text"].to_list() == ["fixed_line", "line_1_edit2", "line_2_edit1"]

        def trimall(values: List[str]) -> List[str]:
            return [s.strip() for s in values]

        assert trimall(commit1["line_commit_message"].to_list()) == ["init", "init"]
        assert trimall(
            commit2["line_commit_message"].to_list()) == ["init", "second", "second"]
        assert trimall(
            commit3["line_commit_message"].to_list()) == ["init", "third", "second"]

        assert trimall(commit1["section_commit_message"].to_list()) == ["init", "init"]
        assert trimall(commit2["section_commit_message"].to_list()) == [
            "second", "second", "second"
        ]
        assert trimall(
            commit3["section_commit_message"].to_list()) == ["third", "third", "third"]


def test_file_move():
    with GitTestRepository({"original_path": "content"}) as repo:
        git_move_files(repo.git_dir(), "original_path", "new_path")
        git_commit(repo.git_dir(), "move1")
        run_forensics(repo.git_dir(), db=str(repo.db))


def test_file_move_and_edit():
    with GitTestRepository({"original_path": "\n".join(["original"] * 100)}) as repo:
        git_move_files(repo.git_dir(), "original_path", "new_path")
        git_write_files(repo.git_dir(),
                        {"new_path": "\n".join(["original"] * 90 + ["changed"] * 10)})
        git_commit(repo.git_dir(), "move1")
        run_forensics(repo.git_dir(), db=str(repo.db))


def test_file_delete():
    with GitTestRepository({"base": "content"}) as repo:
        git_remove_files(repo.git_dir(), "base")
        git_commit(repo.git_dir(), "deleted")
        run_forensics(repo.git_dir(), db=str(repo.db))

def test_file_delete_and_recreate():
    with GitTestRepository({"base": "content"}) as repo:
        git_remove_files(repo.git_dir(), "base")
        git_commit(repo.git_dir(), "deleted-base")
        git_write_files(repo.git_dir(), {"separate": "content"})
        git_commit(repo.git_dir(), "added-separate")
        git_write_files(repo.git_dir(), {"base": "content"})
        git_commit(repo.git_dir(), "added-base-v2")
        run_forensics(repo.git_dir(), db=str(repo.db))

def test_fast_forward_merge():
    with GitTestRepository({"base": "content"}) as repo:
        git_write_files(repo.git_dir(), {"file-1": "content-1"})
        git_commit(repo.git_dir(), "on-master")
        get_git(repo.git_dir()).run(("checkout", "-b", "from-master"))
        git_write_files(repo.git_dir(), {"file-2": "content-2"})
        git_commit(repo.git_dir(), "on-branch-1")
        git_write_files(repo.git_dir(), {"file-3": "content-3"})
        git_commit(repo.git_dir(), "on-branch-2")
        get_git(repo.git_dir()).run(("checkout", "master"))
        get_git(repo.git_dir()).run(("merge", "from-master"))
        run_forensics(repo.git_dir(), db=str(repo.db))


@pytest.mark.xfail(
    reason="Algorithm does not handle all the edge cases for the larger repo")
def test_haxorg_forensics():
    _, stdout, stderr = run_forensics(
        get_haxorg_repo_root_path(), {
            "out": {
                "db_path": "/tmp/haxorg_repo.sqlite",
            },
            "log_file": "/tmp/haxorg_repo_anal_log.log"
        })
