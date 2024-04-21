from dataclasses import dataclass, field, replace
from pathlib import Path
from tempfile import TemporaryDirectory

import pandas as pd
import py_repository.gen_coverage_cxx as cov
from beartype import beartype
from beartype.typing import List, Optional, Union, Dict, Tuple
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
    run_contexts: Dict[str, List[str]] = field(default_factory=lambda: {"main": []})
    run_results: Dict[str, Tuple[int, str, str]] = field(default_factory=dict)

    def get_code(self) -> Path:
        return self.dir.joinpath("file.cpp")

    def get_binary(self) -> Path:
        return self.dir.joinpath("file.bin")

    def get_profraw(self, context: str) -> Path:
        return self.dir.joinpath(context + ".profraw")

    def get_sqlite(self) -> Path:
        return self.dir.joinpath("file.sqlite")

    def get_summary(self) -> Path:
        return self.dir.joinpath("coverage-summary.json")

    def get_perf(self) -> Path:
        return self.dir.joinpath("profdata_merger.perfetto")

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
        for context, run_params in self.run_contexts.items():
            cmd = local[self.get_binary()].with_env(
                LLVM_PROFILE_FILE=str(self.get_profraw(context)))
            self.run_results[context] = cmd.run(run_params)
            assert self.get_profraw(context).exists()

    def run_profmerge(self):
        self.get_summary().write_text(
            cov.ProfdataFullProfile(runs=[
                cov.ProfdataCookie(
                    test_binary=str(self.get_binary()),
                    test_name=context,
                    test_class="class",
                    test_profile=str(self.get_profraw(context)),
                    test_params=run_params,
                ) for context, run_params in self.run_contexts.items()
            ]).model_dump_json(indent=2))

        cmd = local[profdata_merger]
        cmd.run([
            cov.ProfdataParams(
                coverage=str(self.get_summary()),
                coverage_db=str(self.get_sqlite()),
                perf_trace=str(self.get_perf()),
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
        cmd = ProfileRunParams(dir=dir,
                               text="""
int main() {
  int a = 1 + 2;
  int b = a + 3;
}
""")
        cmd.run()
        assert cmd.get_sqlite().exists()

        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)

        frame = pd.read_sql_query(session.query(cov.CovFunction).statement, session.bind)
        assert_frame(frame, [dict(Mangled="main", Demangled="main")])


def test_coverage_regions_1():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        cmd = ProfileRunParams(
            dir=dir,
            text=corpus_base.joinpath("test_coverage_regions_1.cpp").read_text(),
            run_contexts={
                "function_3": [],
                "function_1": ["2"],
                "function_2": ["3", "3"],
            })

        cmd.run()

        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)

        functions = dump_flat_table(
            session,
            table_name="CovFunction",
            dict_primary_key="Demangled",
        )

        assert_subtable(
            session=session,
            table=functions,
            subset={
                "main":
                    dict(
                        Parsed=None,
                        Mangled="main",
                    ),
                "function_1()":
                    dict(),
                "function_2()":
                    dict(),
                "function_3(char const*)":
                    dict(Parsed=dict(
                        Name=dict(Name="function_3"),
                        Params=[
                            dict(Name="char"),
                        ],
                    )),
                "function_3(char const*)":
                    dict(Parsed=dict(
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


def test_region_types():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        cmd = ProfileRunParams(
            dir=dir,
            text=corpus_base.joinpath("test_instantiation_regions.cpp").read_text())
        cmd.run()
        assert cmd.get_sqlite().exists()
        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)


def test_region_types():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        dir = Path("/tmp/test_base_run_coverage")
        cmd = ProfileRunParams(
            dir=dir,
            text=corpus_base.joinpath("test_macro_expansions.cpp").read_text())
        cmd.run()
        assert cmd.get_sqlite().exists()
        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)
        print(format_db_all(session))
