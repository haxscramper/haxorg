import enum
from copy import copy
from pprint import pprint

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
from dataclasses import dataclass, field
import pandas as pd
import shutil

from rich.console import Console
from rich.table import Column, Table, Style
from rich import box
from sqlalchemy import create_engine, Engine
import io

from pydantic import BaseModel
from beartype.typing import List, Optional, Literal, Set, Callable
from hypothesis import strategies as st, settings, given, assume, Verbosity, Phase
from hypothesis.stateful import RuleBasedStateMachine, rule, Bundle, precondition, run_state_machine_as_test
from py_scriptutils.script_logging import log
from collections import OrderedDict


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
    get_git(dir).run(("init",))


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
    code, stdout, stderr = git.run(
        ("commit", f"--author={author} <{email}>", "-m", message), retcode=None)
    if code != 0:
        log.warning("Failed to commit")
        log.warning(stdout)
        log.warning(stderr)


@beartype
def run_forensics(dir: Path,
                  params: dict = dict(),
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
                            exclude: List[str] = list(),
                            file: Optional[io.TextIOWrapper] = None):
    tables = pd.read_sql_query(
        "SELECT name FROM sqlite_master WHERE type='table' OR type='view';", engine)

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


@pytest.mark.skip(
    reason="Algorithm does not handle all the edge cases for the larger repo")
def test_haxorg_forensics():
    _, stdout, stderr = run_forensics(
        get_haxorg_repo_root_path(), {
            "out": {
                "db_path": "/tmp/haxorg_repo.sqlite",
            },
            "log_file": "/tmp/haxorg_repo_anal_log.log"
        })


file_names = st.text(
    alphabet=st.characters(
        whitelist_categories=('Lu', 'Ll', 'Nd'),
        whitelist_characters='',
        min_codepoint=48,
        max_codepoint=122,
    ),
    min_size=5,
    max_size=20,
)

line_content = st.text(
    alphabet=st.characters(
        whitelist_categories=('Lu', 'Ll', 'Nd'),
        whitelist_characters='',
        min_codepoint=48,
        max_codepoint=122,
    ),
    min_size=15,
    max_size=20,
)

MAX_FILES = 5


class GitOperationKind(enum.Enum):
    RENAME_FILE = 0
    DELETE_FILE = 1
    MODIFY_FILE = 2
    CREATE_FILE = 3
    REPO_COMMIT = 4


class GitFileEditKind(enum.Enum):
    REMOVE_LINE = 0
    INSERT_LINE = 1
    CHANGE_LINE = 2


@beartype
@dataclass
class GitFileEdit:
    kind: GitFileEditKind
    line_index: int
    line_content: Optional[str] = None


class GitFileEditStrategy:

    def __init__(self, lines: List[str]):
        self.lines = ["" for _ in lines]

    def get_ops(self, draw):
        if not self.lines:
            operation = GitFileEdit(kind=GitFileEditKind.INSERT_LINE,
                                    line_index=0,
                                    line_content=draw(line_content))

        else:
            which_line = draw(st.integers(min_value=0, max_value=len(self.lines) - 1))
            what_to_do = draw(st.sampled_from(list(GitFileEditKind)))

            match what_to_do:
                case GitFileEditKind.INSERT_LINE:
                    operation = GitFileEdit(kind=what_to_do,
                                            line_content=draw(line_content),
                                            line_index=which_line)

                case GitFileEditKind.CHANGE_LINE:
                    operation = GitFileEdit(kind=what_to_do,
                                            line_content=draw(line_content),
                                            line_index=which_line)

                case GitFileEditKind.REMOVE_LINE:
                    operation = GitFileEdit(kind=what_to_do, line_index=which_line)

        edit_file_content_1(operation, self.lines)
        return operation


@beartype
@dataclass
class GitOperation:
    operation: GitOperationKind
    filename: Optional[str] = None
    new_name: Optional[str] = None  # Only used for 'rename' operation
    file_content: Optional[List[str]] = None


@beartype
def edit_file_content_1(edit: GitFileEdit, content: List[str]):
    match edit:
        case GitFileEdit(kind=GitFileEditKind.REMOVE_LINE, line_index=index):
            content.pop(index)

        case GitFileEdit(kind=GitFileEditKind.CHANGE_LINE,
                         line_index=index,
                         line_content=text):
            content[index] = text

        case GitFileEdit(kind=GitFileEditKind.INSERT_LINE,
                         line_index=index,
                         line_content=text):
            content.insert(index, text)


@beartype
def edit_file_content(modifications: List[GitFileEdit], content: List[str]):
    for edit in modifications:
        edit_file_content_1(edit, content)


class GitOpStrategy:

    def __init__(self) -> None:
        self.files: OrderedDict[str, List[str]] = OrderedDict()
        self.uncommited_ops_count = 0

    def file_ops(self, draw):
        if 10 < self.uncommited_ops_count:
            self.uncommited_ops_count = 0
            return GitOperation(operation=GitOperationKind.REPO_COMMIT)

        else:
            self.uncommited_ops_count += 1

        allowed_ops: List[GitOperationKind] = []
        if not self.files:
            allowed_ops = [GitOperationKind.CREATE_FILE]

        else:
            if len(self.files) < MAX_FILES:
                allowed_ops.append(GitOperationKind.CREATE_FILE)

            if 4 < len(self.files):
                allowed_ops.append(GitOperationKind.DELETE_FILE)

            allowed_ops += [
                GitOperationKind.MODIFY_FILE,
                GitOperationKind.RENAME_FILE,
            ]

        op = draw(st.sampled_from(allowed_ops))

        match op:
            case GitOperationKind.CREATE_FILE:
                name = draw(file_names.filter(lambda x: x not in self.files))
                self.files[name] = [draw(line_content)]
                return GitOperation(operation=op,
                                    filename=name,
                                    file_content=self.files[name])

            case GitOperationKind.DELETE_FILE:
                name = draw(st.sampled_from(self.files))
                del self.files[name]
                return GitOperation(operation=op, filename=name)

            case GitOperationKind.RENAME_FILE:
                old_name = draw(st.sampled_from(self.files))
                new_name = draw(file_names.filter(lambda x: x not in self.files))
                self.files[new_name] = self.files[old_name]
                del self.files[old_name]
                return GitOperation(operation=op, filename=old_name, new_name=new_name)

            case GitOperationKind.MODIFY_FILE:
                name = draw(st.sampled_from(self.files))
                state = GitFileEditStrategy(self.files[name])

                @st.composite
                def get_operations(draw: st.DrawFn):
                    return state.get_ops(draw)

                modifications = draw(st.lists(get_operations(), min_size=5))
                edit_file_content(modifications, self.files[name])

                return GitOperation(operation=op,
                                    filename=name,
                                    file_content=copy(self.files[name]))

            case _:
                assert False, f"Unexpected git operation {op}"


@st.composite
def multiple_files_strategy(draw):
    state = GitOpStrategy()

    @st.composite
    def sub_strategy(draw: st.DrawFn):
        return state.file_ops(draw)

    return draw(st.lists(sub_strategy(), min_size=10))


def run_repo_operations(repo: GitTestRepository, operations: List[GitOperation]):
    for action in operations:
        match action:
            case GitOperation(operation=GitOperationKind.DELETE_FILE, filename=file):
                git_remove_files(repo.git_dir(), file)

            case GitOperation(operation=GitOperationKind.MODIFY_FILE,
                              filename=file,
                              file_content=file_content):
                repo.git_dir().joinpath(file).write_text("\n".join(file_content))

            case GitOperation(operation=GitOperationKind.CREATE_FILE, filename=file):
                git_write_files(repo.git_dir(), {file: "-----"})

            case GitOperation(operation=GitOperationKind.RENAME_FILE,
                              filename=file,
                              new_name=new_name):
                git_move_files(repo.git_dir(), source=file, target=new_name)

            case GitOperation(operation=GitOperationKind.REPO_COMMIT):
                git_commit(repo.git_dir(), "message")


@given(multiple_files_strategy())
@settings(
    max_examples=20,
    deadline=1000,
    verbosity=Verbosity.quiet,
    # Shrinking phase is very expensive and I don't see it yielding any particularly useful results
    phases=[Phase.explicit, Phase.reuse, Phase.generate])
def test_strategic_repo_edits(operations):
    with GitTestRepository({"init": "init"}) as repo:
        run_repo_operations(repo, operations)
        git_commit(repo.git_dir(), "final commit")
        run_forensics(repo.git_dir(), db=str(repo.db))
        # engine = repo.get_engine()
        # print_connection_tables(engine=engine)
