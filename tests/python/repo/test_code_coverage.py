from dataclasses import dataclass, field, replace
from pathlib import Path
from tempfile import TemporaryDirectory

import re
import pandas as pd
import py_repository.gen_coverage_cxx as cov
from beartype import beartype
from beartype.typing import List, Optional, Union, Dict, Tuple
from plumbum import local
import rich.box
from py_scriptutils.pandas_utils import assert_frame, dataframe_to_rich_table
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.rich_utils import render_rich, render_rich_pprint
import py_scriptutils.json_utils as ju
from py_scriptutils.sqlalchemy_utils import (dump_db_all, dump_flat_table, format_db_all,
                                             format_rich_query, open_sqlite_session,
                                             Session)
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
    main: str
    files: Dict[str, str]
    run_contexts: Dict[str, List[str]] = field(default_factory=lambda: {"main": []})
    run_results: Dict[str, Tuple[int, str, str]] = field(default_factory=dict)
    file_whitelist: List[str] = field(default_factory=lambda: [".*"])
    file_blacklist: List[str] = field(default_factory=lambda: [])

    def get_code(self, name: str) -> Path:
        return self.dir.joinpath(name)

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

    def get_params(self) -> Path:
        return self.dir.joinpath("test-params.json")

    def run_compile(self):
        cmd = local[tool_dir.joinpath("clang++")]
        for name, text in self.files.items():
            self.get_code(name).write_text(text)

        cmd.run([
            *[self.get_code(it) for it in self.files.keys()],
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
        self.get_params().write_text(
            cov.ProfdataParams(
                coverage=str(self.get_summary()),
                coverage_db=str(self.get_sqlite()),
                perf_trace=str(self.get_perf()),
                file_whitelist=self.file_whitelist,
                file_blacklist=self.file_blacklist,
            ).model_dump_json(indent=2))

        cmd.run([str(self.get_params())])

    def run(self):
        self.dir.mkdir(exist_ok=True, parents=True)
        self.run_compile()
        self.run_binary()
        self.run_profmerge()


def test_base_run():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        cmd = ProfileRunParams(
            dir=dir,
            main="main.cpp",
            files={"main.cpp": """
int main() {
  int a = 1 + 2;
  int b = a + 3;
}
"""})
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
            main="main.cpp",
            files={
                "main.cpp":
                    corpus_base.joinpath("test_coverage_regions_1.cpp").read_text()
            },
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
            main="main.cpp",
            files={
                "main.cpp":
                    corpus_base.joinpath("test_instantiation_regions.cpp").read_text()
            })
        cmd.run()
        assert cmd.get_sqlite().exists()
        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)


def test_region_types():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        cmd = ProfileRunParams(
            dir=dir,
            main="main.cpp",
            files={
                "main.cpp": corpus_base.joinpath("test_macro_expansions.cpp").read_text()
            })

        cmd.run()
        assert cmd.get_sqlite().exists()
        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)


def test_file_coverage_filter():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        cmd = ProfileRunParams(
            dir=dir,
            main="main.cpp",
            file_whitelist=["main.cpp", "file1.cpp"],
            files={
                "file1.cpp":
                    "void file_1_function() {}",
                "file2.cpp":
                    "void file_2_function() {}",
                "main.cpp":
                    """
void file_1_function();
void file_2_function();

int main() {
  file_1_function();
  file_2_function();
}
"""
            },
        )

        cmd.run()
        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)

        file_table = select(cov.CovSegment, cov.CovFile).join(
            cov.CovFile,
            cov.CovSegment.File == cov.CovFile.Id,
        )

        df = pd.read_sql(file_table, session.get_bind())
        df["Path"] = df["Path"].map(lambda it: Path(it).name)

        assert len(df) == 2
        assert_frame(df, [
            dict(StartLine=1, EndLine=1, Path="file1.cpp"),
            dict(StartLine=5, EndLine=8, Path="main.cpp"),
        ])


@beartype
def cleanup_test_code(code: str) -> str:
    return re.sub(r"\s+", " ", code.replace("\n", " "))


def test_file_segmentation():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        dir = Path("/tmp/test_base_run_coverage")
        code = corpus_base.joinpath("test_file_segmentation_2.cpp").read_text()
        cmd = ProfileRunParams(dir=dir, main="main.cpp", files={"main.cpp": code})

        cmd.run()
        assert cmd.get_sqlite().exists()
        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)
        # print(format_db_all(session))

        lines = code.split("\n")

        df = pd.read_sql(select(cov.CovSegment), session.get_bind())
        df["Text"] = df.apply(
            lambda row: cleanup_test_code(
                cov.extract_text(
                    lines,
                    start=(row["StartLine"], row["StartCol"]),
                    end=(row["EndLine"], row["EndCol"]),
                )),
            axis=1,
        )

        table = dataframe_to_rich_table(df)
        table.show_lines = True
        Path("/tmp/regions.txt").write_text(render_rich(table, color=False))

        segment_df = pd.read_sql(select(cov.CovSegmentFlat), session.get_bind())
        segment_df["Text"] = segment_df["Line"].map(lambda it: lines[it - 1])
        table = dataframe_to_rich_table(segment_df)
        table.show_lines = True
        Path("/tmp/segments.txt").write_text(render_rich(table, color=False))

        assert_frame(df, [
            dict(
                StartLine=1,
                EndLine=1,
                SegmentIndex=0,
                Text="{}",
            ),
            dict(
                StartLine=3,
                EndLine=5,
                SegmentIndex=1,
                Id=2,
                Text="{ if (true || false) { action(); } }",
            ),
            dict(
                StartLine=4,
                EndLine=4,
                SegmentIndex=2,
                Text="true",
                StartCol=9,
                EndCol=13,
                NestedIn=2,
            ),
            dict(
                StartLine=4,
                EndLine=4,
                SegmentIndex=3,
                Text="false",
                StartCol=17,
                EndCol=22,
                NestedIn=2,
            ),
            dict(
                StartLine=4,
                SegmentIndex=4,
                Text="{ action(); }",
                NestedIn=2,
            ),
        ])
