from py_scriptutils import configure_asan

import enum
from copy import copy
from pprint import pprint

import pytest
import json
from tempfile import NamedTemporaryFile, TemporaryDirectory, mktemp
import plumbum
import plumbum.commands.base
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
from py_scriptutils.auto_lldb import get_lldb_params

from pydantic import BaseModel
from beartype.typing import List, Optional, Literal, Set, Callable, Any
from hypothesis import strategies as st, settings, given, assume, Verbosity, Phase, note, seed
from hypothesis.stateful import RuleBasedStateMachine, rule, Bundle, precondition, run_state_machine_as_test
from py_scriptutils.script_logging import log
from collections import OrderedDict

from cxx_repository import burndown
from py_scriptutils.os_utils import gettempdir, json_path_serializer


@beartype
def print_df_rich(
    df: pd.DataFrame,
    title: str,
    file: Optional[io.TextIOWrapper] = None,
) -> None:
    console = Console(file=file, force_terminal=False,
                      color_system=None) if file else Console()

    table = Table(
        show_lines=False,
        box=box.ASCII,
        padding=(0, 1),
        show_edge=False,
        title=f"[red]{title}[/red]",
        min_width=len(title),
        title_justify="left",
    )

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
def get_git(dir: Path) -> plumbum.commands.base.BoundEnvCommand:
    assert dir.exists()
    git = plumbum.local["git"].with_cwd(dir)
    return git


@beartype
def git_init_repo(dir: Path) -> None:
    get_git(dir).run(("init",))


@beartype
def git_write_files(dir: Path, files: Dict[str, str]) -> None:
    for path, content in files.items():
        path_path = Path(dir).joinpath(path)
        if not path_path.parent.exists():
            path_path.parent.mkdir(parents=True)

        with open(path_path, "w") as file:
            file.write(content)


@beartype
def git_move_files(dir: Path, source: str, target: str) -> None:
    dir.joinpath(source).rename(dir.joinpath(target))


@beartype
def git_remove_files(dir: Path, file: str) -> None:
    dir.joinpath(file).unlink()


@beartype
def git_add(dir: Path) -> None:
    get_git(dir).run(("add", "."))


@beartype
def git_commit(
    dir: Path,
    message: str,
    date: datetime = datetime.now(),
    author: str = "haxorg-test-author",
    email: str = "haxorg-test-email@email.com",
    allow_fail: bool = False,
) -> None:
    git_add(dir)
    git = get_git(dir)
    git = git.with_env(GIT_AUTHOR_DATE=date.strftime("%Y-%m-%d %H:%M:%S"),
                       GIT_COMMITTER_DATE=date.strftime("%Y-%m-%d %H:%M:%S"))
    code, stdout, stderr = git.run(
        ("commit", f"--author={author} <{email}>", "-m", message), retcode=None)

    if code != 0 and not allow_fail:
        log().warning("Failed to commit")
        log().warning(stdout)
        log().warning(stderr)


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


@beartype
@dataclass
class GitTestRepository:
    start_files: Dict[str, str]
    db: Optional[Path] = None
    dir: Optional[TemporaryDirectory | Path] = None
    init_message: str = "init"
    fixed_dir: Optional[Path] = None
    fixed_db: Optional[Path] = None

    def cmd(self) -> plumbum.commands.base.BoundEnvCommand:
        return get_git(self.git_dir())

    def git_dir(self) -> Path:
        return self.dir if isinstance(self.dir, Path) else Path(
            self.dir.name)  # type: ignore

    def get_engine(self) -> Engine:
        return create_engine("sqlite:///" + str(self.db))

    def __enter__(self) -> "GitTestRepository":
        if self.fixed_dir:
            self.dir = self.fixed_dir
            if self.dir.exists():
                shutil.rmtree(self.dir)

            self.dir.mkdir()

        else:
            self.dir = TemporaryDirectory()
            self.dir.__enter__()

        git_init_repo(self.git_dir())
        git_write_files(self.git_dir(), self.start_files)
        git_commit(self.git_dir(), self.init_message)

        if self.fixed_db:
            self.db = self.fixed_db

        else:
            self.db = Path(mktemp(suffix=".sqlite"))

        return self

    def __exit__(
        self,
        exc_type: Optional[Type[BaseException]],
        exc_value: Optional[BaseException],
        traceback: Optional[TracebackType],
    ) -> Optional[bool]:
        if isinstance(self.dir, TemporaryDirectory):
            self.dir.__exit__(exc_type, exc_value, traceback)

        if exc_type is not None:
            return False

        assert self.db is not None
        db = Path(self.db)
        if db.exists() and not self.fixed_db:
            db.unlink()

        return None


@beartype
def print_connection_tables(
        engine: Engine,
        exclude: List[str] = list(),
        file: Optional[io.TextIOWrapper] = None,
) -> None:
    tables = pd.read_sql_query(
        "SELECT name FROM sqlite_master WHERE type='table' OR type='view';", engine)

    print("", file=file)
    for table_name in tables['name'].tolist():
        if table_name not in exclude:
            df = pd.read_sql_table(table_name, engine)
            print_df_rich(df, title=table_name, file=file)


@pytest.mark.test_release
def test_can_run_dir() -> None:
    with GitTestRepository({"a": "fixed_line\ninit_commit_content"},
                           fixed_dir=gettempdir("fixed_git_dir_1"),
                           fixed_db=gettempdir("result.sqlite")) as repo:

        git_write_files(repo.git_dir(), {"a": "fixed_line\nline_1_edit1\nline_2_edit1"})
        git_commit(repo.git_dir(), "second")

        git_write_files(repo.git_dir(), {"a": "fixed_line\nline_1_edit2\nline_2_edit1"})
        git_commit(repo.git_dir(), "third")

        _, stdout, stderr = run_forensics(
            repo.git_dir(),
            {
                "out": {
                    "db_path": str(repo.db),
                    "text_dump": gettempdir("test_run.txt"),
                    # "graphviz": gettempdir("graph.dot"),
                    # "perfetto": gettempdir("code_forensics.pftrace"),
                },
                "log_file": gettempdir("test_can_run_dir.log"),
            })

        assert repo.db
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


@pytest.mark.test_release
def test_file_move() -> None:
    with GitTestRepository({"original_path": "content"}) as repo:
        git_move_files(repo.git_dir(), "original_path", "new_path")
        git_commit(repo.git_dir(), "move1")
        run_forensics(repo.git_dir(), db=str(repo.db))


@pytest.mark.test_release
def test_file_move_and_edit() -> None:
    with GitTestRepository({"original_path": "\n".join(["original"] * 100)}) as repo:
        git_move_files(repo.git_dir(), "original_path", "new_path")
        git_write_files(repo.git_dir(),
                        {"new_path": "\n".join(["original"] * 90 + ["changed"] * 10)})
        git_commit(repo.git_dir(), "move1")
        run_forensics(repo.git_dir(), db=str(repo.db))


@pytest.mark.test_release
def test_file_delete() -> None:
    with GitTestRepository({"base": "content"}) as repo:
        git_remove_files(repo.git_dir(), "base")
        git_commit(repo.git_dir(), "deleted")
        run_forensics(repo.git_dir(), db=str(repo.db))


@pytest.mark.test_release
def test_file_delete_and_recreate() -> None:
    with GitTestRepository({"base": "content"}) as repo:
        git_remove_files(repo.git_dir(), "base")
        git_commit(repo.git_dir(), "deleted-base")
        git_write_files(repo.git_dir(), {"separate": "content"})
        git_commit(repo.git_dir(), "added-separate")
        git_write_files(repo.git_dir(), {"base": "content"})
        git_commit(repo.git_dir(), "added-base-v2")
        run_forensics(repo.git_dir(), db=str(repo.db))


@pytest.mark.test_release
def test_fast_forward_merge() -> None:
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


HAXORG_OUT_DB = gettempdir("test_haxorg_forensics.sqlite")


@pytest.mark.skip()
def test_haxorg_forensics() -> None:
    _, stdout, stderr = run_forensics(
        get_haxorg_repo_root_path(), {
            "out": {
                "db_path": HAXORG_OUT_DB,
                "log_file": gettempdir("test_haxorg_forensics.log"),
                "perfetto": gettempdir("test_haxorg_forensics.pftrace"),
            },
            "config": {
                "max_commit_idx": 250,
            },
        })


@pytest.mark.skip()
def test_haxorg_repo_burndown() -> None:
    engine = create_engine("sqlite:///" + HAXORG_OUT_DB)
    burndown.run_for(engine)


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


@st.composite
def line_content(draw: st.DrawFn) -> str:
    is_empty = draw(st.booleans())
    if is_empty:
        return ""
    else:
        return draw(
            st.text(
                alphabet=st.characters(
                    whitelist_categories=('Lu', 'Ll', 'Nd'),
                    whitelist_characters='',
                    min_codepoint=48,
                    max_codepoint=122,
                ),
                min_size=15,
                max_size=20,
            ))


MAX_FILES = 5


class GitOperationKind(enum.Enum):
    RENAME_FILE = 0  # Change file name without altering its content
    DELETE_FILE = 1  # Remove file from the index
    MODIFY_FILE = 2  # Change contents of the file
    CREATE_FILE = 3  # Create new file with random starting content
    REPO_COMMIT = 4  # Commit all changes in the repository
    FORK_BRANCH = 5  # Create new random branch off of current one
    JOIN_BRANCH = 6  # Join existing branch to its parent


class GitFileEditKind(enum.Enum):
    REMOVE_LINE = 0  # Delete line at index
    INSERT_LINE = 1  # Add extra line to a file
    CHANGE_LINE = 2  # Replace existing line with new random content
    NEWLINE_END = 3  # Add or remove newline at the end of the file.


@beartype
@dataclass
class GitFileEdit:
    kind: GitFileEditKind
    line_index: int = 0
    line_content: Optional[str] = None


class GitFileEditStrategy:

    def __init__(self, lines: List[str]):
        self.lines = ["" for _ in lines]

    def get_ops(self, draw: st.DrawFn) -> GitFileEdit:
        if not self.lines:
            operation = GitFileEdit(kind=GitFileEditKind.INSERT_LINE,
                                    line_index=0,
                                    line_content=draw(line_content()))

        else:
            which_line = draw(st.integers(min_value=0, max_value=len(self.lines) - 1))
            what_to_do = draw(st.sampled_from(list(GitFileEditKind)))

            match what_to_do:
                case GitFileEditKind.INSERT_LINE:
                    operation = GitFileEdit(kind=what_to_do,
                                            line_content=draw(line_content()),
                                            line_index=which_line)

                case GitFileEditKind.CHANGE_LINE:
                    operation = GitFileEdit(kind=what_to_do,
                                            line_content=draw(line_content()),
                                            line_index=which_line)

                case GitFileEditKind.REMOVE_LINE:
                    operation = GitFileEdit(kind=what_to_do, line_index=which_line)

                case GitFileEditKind.NEWLINE_END:
                    is_empty = draw(st.sampled_from([True, False]))
                    operation = GitFileEdit(
                        kind=what_to_do,
                        line_content="" if is_empty else draw(line_content()))

        edit_file_content_1(operation, self.lines)
        return operation


@beartype
@dataclass
class GitOperation:
    operation: GitOperationKind
    filename: Optional[str] = None
    new_name: Optional[str] = None  # Only used for 'rename' operation
    file_content: Optional[List[str]] = None
    branch_to_checkout: Optional[str] = None
    branch_to_merge: Optional[str] = None


@beartype
def edit_file_content_1(edit: GitFileEdit, content: List[str]) -> None:
    match edit:
        case GitFileEdit(kind=GitFileEditKind.REMOVE_LINE, line_index=index):
            content.pop(index)

        case GitFileEdit(kind=GitFileEditKind.CHANGE_LINE,
                         line_index=index,
                         line_content=text):
            assert text
            content[index] = text

        case GitFileEdit(kind=GitFileEditKind.INSERT_LINE,
                         line_index=index,
                         line_content=text):
            assert text
            content.insert(index, text)

        case GitFileEdit(kind=GitFileEditKind.NEWLINE_END, line_content=text):
            assert text
            content[-1] = text

        case _:
            assert False, f"Unhandled git file edit operation {edit}"


@beartype
def edit_file_content(modifications: List[GitFileEdit], content: List[str]) -> None:
    for edit in modifications:
        edit_file_content_1(edit, content)


@dataclass
class GitOpStrategy:
    files: OrderedDict[str, List[str]] = field(default_factory=lambda: OrderedDict())
    uncommited_ops_count: int = 0
    branch_stack: List[str] = field(default_factory=list)
    used_branches: Set[str] = field(default_factory=set)

    def file_ops(self, draw: st.DrawFn) -> GitOperation:
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

        if 0 < len(self.branch_stack):
            allowed_ops += [GitOperationKind.JOIN_BRANCH]

        allowed_ops += [GitOperationKind.FORK_BRANCH]
        op = draw(st.sampled_from(allowed_ops))

        match op:
            case GitOperationKind.CREATE_FILE:
                name = draw(file_names.filter(lambda x: x not in self.files))
                self.files[name] = draw(st.lists(line_content(), min_size=2, max_size=5))
                return GitOperation(operation=op,
                                    filename=name,
                                    file_content=self.files[name])

            case GitOperationKind.DELETE_FILE:
                name = draw(st.sampled_from(self.files)) # type: ignore
                del self.files[name]
                return GitOperation(operation=op, filename=name)

            case GitOperationKind.RENAME_FILE:
                old_name = draw(st.sampled_from(self.files)) # type: ignore
                new_name = draw(file_names.filter(lambda x: x not in self.files))
                self.files[new_name] = self.files[old_name]
                del self.files[old_name]
                return GitOperation(operation=op, filename=old_name, new_name=new_name)

            case GitOperationKind.FORK_BRANCH:
                new_branch = draw(
                    file_names.filter(lambda x: x not in self.used_branches))
                self.used_branches.add(new_branch)
                self.branch_stack.append(new_branch)
                return GitOperation(operation=op, branch_to_checkout=new_branch)

            case GitOperationKind.JOIN_BRANCH:
                to_checkout = self.branch_stack[-2] if 1 < len(
                    self.branch_stack) else "master"
                return GitOperation(operation=op,
                                    branch_to_merge=self.branch_stack.pop(),
                                    branch_to_checkout=to_checkout)

            case GitOperationKind.MODIFY_FILE:
                name = draw(st.sampled_from(self.files)) # type: ignore
                state = GitFileEditStrategy(self.files[name])

                @st.composite
                def get_operations(draw: st.DrawFn) -> GitFileEdit: 
                    return state.get_ops(draw)

                modifications = draw(st.lists(get_operations(), min_size=5))
                edit_file_content(modifications, self.files[name])

                return GitOperation(operation=op,
                                    filename=name,
                                    file_content=copy(self.files[name]))

            case _:
                assert False, f"Unexpected git operation {op}"


@st.composite
def multiple_files_strategy(draw: st.DrawFn) -> List[Any]:
    state = GitOpStrategy()

    @st.composite
    def sub_strategy(draw: st.DrawFn) -> GitOperation:
        return state.file_ops(draw)

    return draw(st.lists(sub_strategy(), min_size=10, max_size=90))


@beartype
def run_repo_operations(repo: GitTestRepository, operations: List[GitOperation]) -> None:
    BRANCH_CANARY_FILE = "branch-canary"
    for idx, action in enumerate(operations):
        match action:
            case GitOperation(
                operation=GitOperationKind.DELETE_FILE,
                filename=file,
            ):
                assert file
                git_remove_files(repo.git_dir(), file)

            case GitOperation(
                operation=GitOperationKind.MODIFY_FILE,
                filename=file,
                file_content=file_content,
            ):
                assert file
                assert file_content
                repo.git_dir().joinpath(file).write_text("\n".join(file_content))

            case GitOperation(operation=GitOperationKind.CREATE_FILE,
                              filename=file,
                              file_content=content):
                assert file
                assert content
                git_write_files(repo.git_dir(), {file: "\n".join(content)})

            case GitOperation(
                operation=GitOperationKind.RENAME_FILE,
                filename=file,
                new_name=new_name,
            ):
                assert file
                assert new_name
                git_move_files(repo.git_dir(), source=file, target=new_name)

            case GitOperation(operation=GitOperationKind.REPO_COMMIT,):
                git_commit(repo.git_dir(), "message", allow_fail=True)

            case GitOperation(
                operation=GitOperationKind.FORK_BRANCH,
                branch_to_checkout=branch,
            ):
                repo.cmd().run(("checkout", "-b", branch))
                git_write_files(repo.git_dir(), {BRANCH_CANARY_FILE: str(idx)})
                git_commit(repo.git_dir(), f"auto-after-fork-{idx}", allow_fail=True)

            case GitOperation(
                operation=GitOperationKind.JOIN_BRANCH,
                branch_to_merge=merge,
                branch_to_checkout=checkout,
            ):
                git_commit(repo.git_dir(), f"auto-pre-join-{idx}", allow_fail=True)
                repo.cmd().run(("checkout", checkout))
                repo.cmd().run(("merge", "--no-ff", merge))

            case _:
                assert False, f"Unhandled git repo operation {action}"


@beartype
def run_repo_operations_test(
        operations: List[GitOperation],
        with_debugger: bool = False,
        fixed_dir: Optional[Path] = None,
        params: Dict[str, Any] = dict(),
) -> None:
    with GitTestRepository({"init": "init"}, fixed_dir=fixed_dir) as repo:
        run_repo_operations(repo, operations)
        git_commit(repo.git_dir(), "final commit", allow_fail=True)

        run_forensics(
            repo.git_dir(),
            db=str(repo.db),
            with_debugger=with_debugger,
            params=params,
        )
        # engine = repo.get_engine()
        # print_connection_tables(engine=engine)


@pytest.mark.test_release
def test_repo_operations_example_1() -> None:
    # yapf:disable
    run_repo_operations_test([
        GitOperation(operation=GitOperationKind.CREATE_FILE, filename='00000', file_content=['000000000000000']),
        GitOperation(operation=GitOperationKind.RENAME_FILE, filename='00000', new_name='00002'),
        GitOperation(operation=GitOperationKind.CREATE_FILE, filename='00001', file_content=['000000000000000']),
        GitOperation(operation=GitOperationKind.RENAME_FILE, filename='00002', new_name='00000'),
        GitOperation(operation=GitOperationKind.FORK_BRANCH, branch_to_checkout='00002'),
        GitOperation(operation=GitOperationKind.FORK_BRANCH, branch_to_checkout='00000'),
        GitOperation(operation=GitOperationKind.JOIN_BRANCH, branch_to_checkout='00002', branch_to_merge='00000'),
        GitOperation(operation=GitOperationKind.FORK_BRANCH, branch_to_checkout='00001'),
        GitOperation(operation=GitOperationKind.JOIN_BRANCH, branch_to_checkout='00002', branch_to_merge='00001'),
        GitOperation(operation=GitOperationKind.JOIN_BRANCH, branch_to_checkout='master', branch_to_merge='00002')
    ], fixed_dir=gettempdir("test_repo_operations_example_1"))
    # yapf:enable


@pytest.mark.test_release
def test_repo_operations_example_2() -> None:
    # yapf:disable
    run_repo_operations_test(
        [
            GitOperation(operation=GitOperationKind.FORK_BRANCH, branch_to_checkout='JbWE5TXWZHKK'),
            GitOperation(operation=GitOperationKind.JOIN_BRANCH, branch_to_checkout='master', branch_to_merge='JbWE5TXWZHKK'),
            GitOperation(operation=GitOperationKind.CREATE_FILE, filename='nlAjw', file_content=['55HPsjzi5joBchT', 'n3BtxWyZQHjgrB08Hy5u']),
            GitOperation(operation=GitOperationKind.FORK_BRANCH, branch_to_checkout='C5RGCKw'),
            GitOperation(operation=GitOperationKind.MODIFY_FILE, filename='nlAjw', file_content=['BebTFIjVzClRpeo']),
            GitOperation(operation=GitOperationKind.JOIN_BRANCH, branch_to_checkout='master', branch_to_merge='C5RGCKw'),
            GitOperation(operation=GitOperationKind.RENAME_FILE, filename='nlAjw', new_name='TkxO1B'),
            GitOperation(operation=GitOperationKind.MODIFY_FILE, filename='TkxO1B', file_content=['IKg0kaEBYCeraVBI', '4aZcYZyYGFziOsh', 'FmzjICazxQMfRcVU', 'BAaKDLvCFmqvzbXyMa']),
            GitOperation(operation=GitOperationKind.CREATE_FILE, filename='DRgnfGjgVGQX6v', file_content=['xQaxNCazTBYU65o9YL2P']),
            GitOperation(operation=GitOperationKind.RENAME_FILE, filename='DRgnfGjgVGQX6v', new_name='vP9woVMYqc6SeQnNTEQn'),
            GitOperation(operation=GitOperationKind.FORK_BRANCH, branch_to_checkout='8RG9Q'),
            GitOperation(operation=GitOperationKind.REPO_COMMIT),
            GitOperation(operation=GitOperationKind.MODIFY_FILE, filename='TkxO1B', file_content=['AHxNeMGfKpdlJkOR7', 'og8YCVAtJ2FLJk7sMH', 'n3BtxWyZQHjgrB08Hy5u', '4aZcYZyYGFziOsh']),
            GitOperation(operation=GitOperationKind.MODIFY_FILE, filename='TkxO1B', file_content=['55HPsjzi5joBchT', 'n3BtxWyZQHjgrB08Hy5u']),
            GitOperation(operation=GitOperationKind.CREATE_FILE, filename='WDmICkCg', file_content=['3bhx2yd4D22nkmQd']),
            GitOperation(operation=GitOperationKind.JOIN_BRANCH, branch_to_checkout='master', branch_to_merge='8RG9Q'),
            GitOperation(operation=GitOperationKind.CREATE_FILE, filename='IPwllW', file_content=['GHte9uhs1xNPohXX'])
        ])
    # yapf:enable


@pytest.mark.test_release
def test_repo_operations_example_3() -> None:
    run_repo_operations_test([
        GitOperation(GitOperationKind.CREATE_FILE,
                     filename="manual_wrap.hpp",
                     file_content=[
                         "#ifndef PY_HAXORG_COMPILING",
                         *(["SAME"] * 20),
                         "",
                         "",
                     ]),
        GitOperation(operation=GitOperationKind.REPO_COMMIT),
        GitOperation(GitOperationKind.CREATE_FILE,
                     filename="manual_wrap.hpp",
                     file_content=[
                         "#ifndef PY_HAXORG_COMPILING",
                         *(["SAME"] * 20),
                         "",
                     ]),
        GitOperation(operation=GitOperationKind.REPO_COMMIT),
    ],
                             fixed_dir=gettempdir("test_repo_operations_example_3"))


@pytest.mark.test_release
def test_repo_operations_example_4() -> None:
    file_1 = "manual_impl.cpp"
    file_2 = "manual_wrap.hpp"
    content_1 = [
        "#ifndef PY_HAXORG_COMPILING",
        *(["SAME"] * 20),
        "",
        "",
    ]

    content_2 = [
        "#ifndef PY_HAXORG_COMPILING",
        *(["WHATVRASDSA"] * 20),
        "",
    ]

    run_repo_operations_test(
        [
            GitOperation(
                GitOperationKind.CREATE_FILE, filename=file_1, file_content=content_1),
            GitOperation(operation=GitOperationKind.REPO_COMMIT),
            GitOperation(
                operation=GitOperationKind.RENAME_FILE, filename=file_1, new_name=file_2),
            GitOperation(operation=GitOperationKind.REPO_COMMIT),
            GitOperation(
                GitOperationKind.CREATE_FILE, filename=file_1, file_content=content_2),
            GitOperation(operation=GitOperationKind.REPO_COMMIT),
            GitOperation(operation=GitOperationKind.MODIFY_FILE,
                         filename=file_2,
                         file_content=content_1[:-3] + ["LINE1", "LINE2", "LINE3"])
        ],
        params={
            "config": {
                "verbose_consistency_checks": True
            },
            "out": {
                "log_file": gettempdir("test_repo_operations_example_4.log")
            }
        },
        fixed_dir=gettempdir("test_repo_operations_example_4"))


@pytest.mark.test_release
@given(multiple_files_strategy())
@settings(
    max_examples=20,
    deadline=2000,
    verbosity=Verbosity.normal,
    # Shrinking phase is very expensive and I don't see it yielding any particularly useful results
    phases=[Phase.explicit, Phase.reuse, Phase.generate])
def test_strategic_repo_edits(operations: List[GitOperation]) -> None:
    run_repo_operations_test(operations)
