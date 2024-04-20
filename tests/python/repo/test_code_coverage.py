from dataclasses import dataclass, field, replace
from pathlib import Path
from tempfile import TemporaryDirectory

import pandas as pd
import py_repository.gen_coverage_cxx as cov
from beartype import beartype
from beartype.typing import List, Optional, Union
from plumbum import local
from py_scriptutils.pandas_utils import assert_frame, dataframe_to_rich_table
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.rich_utils import render_rich, render_rich_pprint
import py_scriptutils.json_utils as ju
from py_scriptutils.sqlalchemy_utils import (dump_db_all, dump_flat_table, format_db_all,
                                             open_sqlite_session, Session)
from sqlalchemy import select

profdata_merger = get_haxorg_repo_root_path().joinpath(
    "build/utils/profdata_merger/profdata_merger")

tool_dir = get_haxorg_repo_root_path().joinpath("toolchain/llvm/bin")
corpus_base = get_haxorg_repo_root_path().joinpath("tests/python/repo/coverage_corpus")


@beartype
def assert_subtable(
    session: Session,
    subset: ju.Json,
    table: Union[str, ju.Json],
    dict_key: Optional[str] = None,
):
    if isinstance(table, (dict, list)):
        value = table

    else:
        value = dump_flat_table(
            session,
            table_name=table,
            dict_primary_key=dict_key,
        )

    ju.assert_subset(
        value, subset, "Subset:\n{}\nMain:\n{}".format(
            render_rich_pprint(
                subset,
                width=120,
                color=False,
            ),
            render_rich_pprint(
                value,
                width=200,
                color=False,
            ),
        ))


@beartype
@dataclass
class ProfileRunParams():
    dir: Path
    text: str
    run_params: List[str] = field(default_factory=list)
    stdout: Optional[str] = None
    stderr: Optional[str] = None

    def get_code(self) -> Path:
        return self.dir.joinpath("file.cpp")

    def get_binary(self) -> Path:
        return self.dir.joinpath("file.bin")

    def get_profraw(self) -> Path:
        return self.dir.joinpath("file.profraw")

    def get_sqlite(self) -> Path:
        return self.dir.joinpath("file.sqlite")

    def get_summary(self) -> Path:
        return self.dir.joinpath("coverage-summary.json")

    def run_compile(self):
        cmd = local[tool_dir.joinpath("clang++")]
        self.get_code().write_text(self.text)
        cmd.run([
            self.get_code(),
            "-fprofile-instr-generate",
            "-fcoverage-mapping",
            "-o",
            self.get_binary(),
        ])

    def run_binary(self):
        cmd = local[self.get_binary()].with_env(LLVM_PROFILE_FILE=str(self.get_profraw()))
        code, stdout, stderr = cmd.run(self.run_params)
        self.stdout = stdout
        self.stderr = stderr
        assert self.get_profraw().exists()

    def run_profmerge(self):
        self.get_summary().write_text(
            cov.ProfdataFullProfile(runs=[
                cov.ProfdataCookie(
                    test_binary=str(self.get_binary()),
                    test_name="test",
                    test_class="class",
                    test_profile=str(self.get_profraw()),
                    test_params=None,
                )
            ]).model_dump_json(indent=2))

        cmd = local[profdata_merger]
        cmd.run([
            cov.ProfdataParams(
                coverage=str(self.get_summary()),
                coverage_db=str(self.get_sqlite()),
            ).model_dump_json()
        ])

    def run(self):
        self.dir.mkdir(exist_ok=True, parents=True)
        self.run_compile()
        self.run_binary()
        self.run_profmerge()


def test_base_run():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        cmd = ProfileRunParams(dir=dir, text="int main() {}")
        cmd.run()
        assert cmd.get_sqlite().exists()

        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)

        frame = pd.read_sql_query(session.query(cov.CovFunction).statement, session.bind)
        assert_frame(frame, [dict(mangled="main", demangled="main")])


def test_coverage_regions_1():
    with TemporaryDirectory() as tmp:
        dir = Path("/tmp/test_base_run_coverage")
        cmd = ProfileRunParams(
            dir=dir,
            text=corpus_base.joinpath("test_coverage_regions_1.cpp").read_text(),
        )

        cmd.run()

        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)

        functions = dump_flat_table(
            session,
            table_name="CovFunction",
            dict_primary_key="demangled",
        )

        assert_subtable(
            session=session,
            table=functions,
            subset={
                "main":
                    dict(
                        parsed=None,
                        mangled="main",
                    ),
                "function_3(char const*)":
                    dict(parsed=dict(
                        Name=dict(Name="function_3"),
                        Params=[
                            dict(
                                NodeKind="PointerType",
                                Pointee=dict(
                                    Child=dict(Name="char"),
                                    Quals=["QualConst"],
                                ),
                            )
                        ],
                    ))
            },
        )

        print(format_db_all(session))
