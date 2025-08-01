from dataclasses import dataclass, field, replace
from pathlib import Path
from tempfile import TemporaryDirectory

from py_scriptutils.os_utils import gettempdir
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
from py_scriptutils.script_logging import log, to_debug_json, pprint_to_file
from py_scriptutils.rich_utils import render_rich_pprint
from collections import defaultdict
import pytest
from dominate import document
import dominate.tags as tags


def dbg(map) -> str:
    return render_rich_pprint(map, width=200, color=False)


CAT = "test_code_coverage"

profdata_merger = get_haxorg_repo_root_path().joinpath("build/haxorg/profdata_merger")

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
    show_merger_run: Union[bool, Path] = False
    coverage_mapping_dump: Optional[Path] = None
    run_group_batch_size: int = 8

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
            *[self.get_code(it) for it in self.files.keys() if it.endswith(".cpp")],
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

        cmd = local[profdata_merger].with_env(LD_PRELOAD="")
        if self.coverage_mapping_dump:
            self.coverage_mapping_dump.mkdir(exist_ok=True, parents=True)

        self.get_params().write_text(
            cov.ProfdataParams(
                coverage=str(self.get_summary()),
                coverage_db=str(self.get_sqlite()),
                # perf_trace=str(self.get_perf()),
                file_whitelist=self.file_whitelist,
                file_blacklist=self.file_blacklist,
                coverage_mapping_dump=self.coverage_mapping_dump and
                str(self.coverage_mapping_dump),
            ).model_dump_json(indent=2))

        code, stdout, stderr = cmd.run([str(self.get_params())])
        if self.show_merger_run:
            if isinstance(self.show_merger_run, bool):
                outfile = stdout

            else:
                self.show_merger_run.parent.mkdir(parents=True, exist_ok=True)
                outfile = open(self.show_merger_run, "w")

            if stdout:
                print("stdout", file=outfile)
                print(stdout, file=outfile)

            if stderr:
                print("stderr", file=outfile)
                print(stderr, file=outfile)

            if isinstance(self.show_merger_run, Path):
                outfile.close()

    def run(self):
        self.dir.mkdir(exist_ok=True, parents=True)
        self.run_compile()
        self.run_binary()
        self.run_profmerge()


@pytest.mark.test_release
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


@pytest.mark.test_release
def test_coverage_regions_multiple_contexts():
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


@pytest.mark.test_release
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


@pytest.mark.test_release
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


@pytest.mark.test_release
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

        file_table = select(cov.CovFileRegion, cov.CovFile).join(
            cov.CovFile,
            cov.CovFileRegion.File == cov.CovFile.Id,
        )

        df = pd.read_sql(file_table, session.get_bind())
        df["Path"] = df["Path"].map(lambda it: Path(it).name)

        assert len(df) == 2
        assert_frame(df, [
            dict(LineStart=1, LineEnd=1, Path="file1.cpp"),
            dict(LineStart=5, LineEnd=8, Path="main.cpp"),
        ])


@beartype
def cleanup_test_code(code: str) -> str:
    return re.sub(r"\s+", " ", code.replace("\n", " "))


@beartype
def add_cov_segment_text(df: pd.DataFrame, lines: List[str], for_test: bool = True):

    def get_row(row):
        code = cov.extract_text(
            lines,
            start=(row["LineStart"], row["ColumnStart"]),
            end=(row["LineEnd"], row["ColumnEnd"]),
        )
        if for_test:
            return cleanup_test_code(code)

        else:
            return code

    df["Text"] = df.apply(get_row, axis=1)


@pytest.mark.test_release
def test_file_segmentation_1():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        code = corpus_base.joinpath("test_file_segmentation_1.cpp").read_text()
        cmd = ProfileRunParams(dir=dir, main="main.cpp", files={"main.cpp": code})
        cmd.run()

        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)
        main_cov = cov.get_coverage_of(session, cmd.get_code("main.cpp"))
        lines = code.split("\n")

        df = pd.read_sql(main_cov, session.get_bind())
        add_cov_segment_text(df, lines)
        assert_frame(df[df["LineStart"] == 1], [
            dict(Text="{}", ColumnStart=15, ColumnEnd=17),
        ])


@pytest.mark.test_release
def test_file_segmentation_2():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        code = corpus_base.joinpath("test_file_segmentation_2.cpp").read_text()
        cmd = ProfileRunParams(dir=dir, main="main.cpp", files={"main.cpp": code})

        cmd.run()
        assert cmd.get_sqlite().exists()
        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)
        # print(format_db_all(session))

        lines = code.split("\n")

        df = pd.read_sql(select(cov.CovFileRegion), session.get_bind())
        add_cov_segment_text(df, lines)

        assert_frame(df, [
            dict(
                LineStart=1,
                LineEnd=1,
                Text="{}",
            ),
            dict(
                LineStart=3,
                LineEnd=5,
                Id=2,
                Text="{ if (true || false) { action(); } }",
            ),
            dict(
                LineStart=4,
                LineEnd=4,
                Text="true",
                ColumnStart=9,
                ColumnEnd=13,
            ),
            dict(
                LineStart=4,
                LineEnd=4,
                Text="true || false",
                ColumnStart=9,
                ColumnEnd=22,
            ),
            dict(
                LineStart=4,
                LineEnd=4,
                Text="false",
                ColumnStart=17,
                ColumnEnd=22,
            ),
            dict(RegionKind="CovRegionKind.GapRegion",),
            dict(
                LineStart=4,
                Text="{ action(); }",
            ),
        ])


@pytest.mark.test_release
@pytest.mark.test_coverage_annotation_file_cxx
def test_coverage_annotation_single_run():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        code = "\n".join([
            "",
            "int main() {",
            "  int a = 1 + 2;",
            "  int b = a + 3;",
            "}",
        ])
        cmd = ProfileRunParams(dir=dir, main="main.cpp", files={"main.cpp": code})
        cmd.run()
        assert cmd.get_sqlite().exists()

        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)
        main_cov = cov.get_coverage_of(session, cmd.get_code("main.cpp"))
        assert main_cov != None
        file = cov.read_code_file(dir, dir.joinpath("main.cpp"))
        flat_segments = cov.get_flat_coverage(session, file.Lines, main_cov)
        # log(CAT).info(flat_segments)
        flat_group = cov.get_coverage_group(flat_segments)

        direct_segmented = cov.org.annotateSequence(
            groups=cov.org.VecOfSequenceSegmentGroupVec([flat_group]),
            first=0,
            last=len(code) - 1,
        )

        # print(format_db_all(session))
        seg: cov.org.SequenceAnnotation
        # for seg in direct_segmented:
        # log(CAT).info(f"{seg.first}, {seg.last}")

        assert len(direct_segmented) == 1

        line_group = cov.get_line_group(file.Lines)

        # print(line_group)

        file_text = "\n".join([it.Text for it in file.Lines])

        line_segmented = cov.org.annotateSequence(
            groups=cov.org.VecOfSequenceSegmentGroupVec([line_group]),
            first=0,
            last=len(code),
        )

        line_annotated_file = cov.get_annotated_files(
            text=file_text,
            annotations=[it for it in line_segmented],
            line_group_kind=line_group.kind,
        )

        ju.assert_subset(
            line_annotated_file.model_dump(),
            dict(Lines=[
                dict(Segments=[dict(Text="\n")]),
                dict(Segments=[dict(Text="int main() {\n")]),
                dict(Segments=[dict(Text="  int a = 1 + 2;\n")]),
                dict(Segments=[dict(Text="  int b = a + 3;\n")]),
                dict(Segments=[dict(Text="}")]),
            ],),
        )

        assert len(line_segmented) == 5

        join_segmented = cov.org.annotateSequence(
            groups=cov.org.VecOfSequenceSegmentGroupVec([line_group, flat_group]),
            first=0,
            last=len(code),
        )

        assert len(join_segmented) == 6

        join_annotated_file = cov.get_annotated_files(
            text=file_text,
            annotations=[it for it in join_segmented],
            line_group_kind=line_group.kind,
        )

        assert len(join_annotated_file.Lines) == 5
        assert len(join_annotated_file.Lines[0].Segments) == 1

        ju.assert_subset(
            join_annotated_file.model_dump(),
            dict(Lines=[
                dict(Segments=[dict(Text="\n")]),
                dict(Segments=[dict(
                    Text="int main() "), dict(Text="{\n")]),
                dict(Segments=[dict(Text="  int a = 1 + 2;\n")]),
                dict(Segments=[dict(Text="  int b = a + 3;\n")]),
                dict(Segments=[dict(Text="}")]),
            ],),
        )

        token_dict = defaultdict(lambda: len(token_dict))

        token_group = cov.get_token_group(
            file_text,
            token_to_int=lambda it: token_dict[it],
        )

        token_segmented = cov.org.annotateSequence(
            groups=cov.org.VecOfSequenceSegmentGroupVec(
                [line_group, flat_group, token_group]),
            first=0,
            last=len(code),
        )

        token_annotated_file = cov.get_annotated_files(
            text=file_text,
            annotations=[it for it in token_segmented],
            line_group_kind=line_group.kind,
            token_group_kind=token_group.kind,
            token_kind_mapping={
                kind: key for key, kind in token_dict.items()
            },
            coverage_group_kind=flat_group.kind,
        )

        ju.assert_subset(
            to_debug_json(token_annotated_file.model_dump()),
            to_debug_json(
                dict(Lines=[
                    dict(Segments=[dict(TokenKind="Token.Text.Whitespace")]),
                    dict(Segments=[
                        dict(Text='int', Annotations={}, TokenKind='Token.Keyword.Type'),
                        dict(Text=' ', Annotations={}, TokenKind='Token.Text.Whitespace'),
                        dict(Text='main', Annotations={},
                             TokenKind='Token.Name.Function'),
                        dict(Text='()', Annotations={}, TokenKind='Token.Punctuation'),
                        dict(Text=' ', Annotations={}, TokenKind='Token.Text.Whitespace'),
                        dict(Text='{',
                             CoverageSegmentIdx=[0],
                             TokenKind='Token.Punctuation'),
                        dict(Text='\n',
                             CoverageSegmentIdx=[0],
                             TokenKind='Token.Text.Whitespace'),
                    ]),
                    dict(),
                    dict(),
                    dict(Segments=[dict(TokenKind="Token.Punctuation")]),
                ])),
        )

        recombine = ""
        for line in token_annotated_file.Lines:
            for segment in line.Segments:
                recombine += segment.Text

        assert recombine == file_text


@pytest.mark.test_release
@pytest.mark.test_coverage_annotation_file_cxx
def test_coverage_annotation_multiple_run_single_segment():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        code = "\n".join([
            "",
            "int main() {",
            "  int a = 1 + 2;",
            "  int b = a + 3;",
            "}",
        ])

        cmd = ProfileRunParams(
            dir=dir,
            main="main.cpp",
            files={"main.cpp": code},
            run_contexts={
                "function_3": [],
                "function_1": ["2"],
                "function_2": ["3", "3"],
            },
        )

        cmd.run()

        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)

        file = cov.get_annotated_files_for_session(
            session=session,
            root_path=dir,
            abs_path=dir.joinpath("main.cpp"),
        )

        recombine = ""
        for line in file.Lines:
            for segment in line.Segments:
                recombine += segment.Text

        assert recombine == code


css_path = get_haxorg_repo_root_path().joinpath(
    "scripts/py_repository/py_repository/gen_documentation.css")

js_path = get_haxorg_repo_root_path().joinpath(
    "scripts/py_repository/py_repository/gen_documentation.js")


@pytest.mark.test_release
@pytest.mark.test_coverage_annotation_file_cxx
def test_coverage_annotation_multiple_run_multiple_segment():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        code = corpus_base.joinpath("test_coverage_regions_2.cpp").read_text()

        cmd = ProfileRunParams(
            dir=dir,
            main="main.cpp",
            files={"main.cpp": code},
            run_contexts={
                "function_3": [],
                # "function_1": ["2"],
                # "function_2": ["3", "3"],
            },
        )

        cmd.show_merger_run = gettempdir() / "show_merger_run.txt"

        cmd.run()

        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)

        db_debug_path = Path(
            gettempdir()) / "test_coverage_annotation_multiple_run_multiple_segment.txt"
        db_debug_path.write_text(format_db_all(session, style=False))

        file = cov.get_annotated_files_for_session(
            session=session,
            root_path=dir,
            abs_path=dir.joinpath("main.cpp"),
            debug_format_segments=gettempdir() / "annotated_segments.txt",
        )

        pprint_to_file(file, gettempdir() / "annotated.py", width=200)

        ranges = list()
        position = 0
        for line_idx, line_text in enumerate(code.splitlines()):
            line_info = dict(
                line_idx=line_idx,
                line_text=line_text,
                pos_first=position,
                columns=[],
                line_len=len(line_text),
            )

            for col_idx, col_text in enumerate(line_text):
                col_info = dict(col_idx=col_idx, col_text=col_text, position=position)
                position += 1
                line_info["columns"].append(col_info)

            line_info["pos_last"] = position
            position += 1

            ranges.append(line_info)

        pprint_to_file(ranges, gettempdir() / "char_ranges.py")

        recombine = ""
        for line in file.Lines:
            for segment in line.Segments:
                recombine += segment.Text

        assert recombine == code

        debug_path = Path(
            gettempdir()) / "test_coverage_annotation_multiple_run_multiple_segment.html"

        debug_path.write_text(
            cov.get_file_annotation_document(
                session=session,
                root_path=dir,
                abs_path=dir.joinpath("main.cpp"),
            ).render())

        session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)
        main_cov = cov.get_coverage_of(session, cmd.get_code("main.cpp"))
        lines = code.split("\n")

        df = pd.read_sql(main_cov, session.get_bind())
        add_cov_segment_text(df, lines, for_test=False)

        debug_path = gettempdir() / "coverage_segments.txt"
        debug_path.write_text(
            render_rich(
                dataframe_to_rich_table(
                    df,
                    show_lines=True,
                ),
                color=False,
            ))


def run_common(
        cmd: ProfileRunParams,
        dir: Path,
        path_pprint: Optional[Path] = Path("annotated.py"),
        path_genhtml: Optional[Path] = Path(""),
        path_dbdump: Optional[Path] = Path("dbdump.txt"),
        path_format_segments: Optional[Path] = Path("annotated_segments.txt"),
        path_merger_run: Optional[Path] = Path("show_merger_run.txt"),
        path_coverage_mapping_dump: Optional[Path] = Path("mapping_dump"),
        filename: Path = Path("main.cpp"),
):

    def pass_path(path: Path) -> Path:
        if path.is_absolute():
            return path

        else:
            return dir.joinpath(path)

    if path_merger_run:
        cmd.show_merger_run = pass_path(path_merger_run)

    if path_coverage_mapping_dump:
        cmd.coverage_mapping_dump = pass_path(path_coverage_mapping_dump)

    cmd.run()
    assert cmd.get_sqlite().exists(), cmd.get_sqlite()
    session = open_sqlite_session(cmd.get_sqlite(), cov.CoverageSchema)

    if path_dbdump:
        pass_path(path_dbdump).write_text(format_db_all(session, style=False))

    file = cov.get_annotated_files_for_session(
        session=session,
        root_path=dir,
        abs_path=dir.joinpath(filename),
        debug_format_segments=pass_path(path_format_segments),
    )

    if path_pprint:
        pprint_to_file(file, pass_path(path_pprint), width=200)

    log(CAT).info(pass_path(path_genhtml))
    if path_genhtml:
        html_out_dir = pass_path(path_genhtml)
        for code_in in cmd.files.keys():
            html_out = html_out_dir.joinpath(code_in)
            pass_path(html_out).write_text(
                cov.get_file_annotation_document(
                    session=session,
                    root_path=dir,
                    abs_path=dir.joinpath(code_in),
                ).render())

            pass_path(path_genhtml).with_suffix(".json").write_text(
                file.model_dump_json(indent=2))
            pass_path(path_genhtml).with_suffix(".txt").write_text(file.get_debug())


@pytest.mark.test_release
@pytest.mark.test_coverage_annotation_file_cxx
def test_template_coverage_annotations():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        code = corpus_base.joinpath("test_template_coverage1.hpp").read_text()

        cmd = ProfileRunParams(
            dir=dir,
            main="main.cpp",
            files={"main.cpp": code},
            run_contexts={f"branch_{it}": ["arg"] * it for it in [1, 2, 9]},
        )

        run_common(cmd, dir)


@pytest.mark.test_release
@pytest.mark.test_coverage_annotation_file_cxx
def test_macro_coverage1():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        code = corpus_base.joinpath("test_macro_coverage.hpp").read_text()

        cmd = ProfileRunParams(
            dir=dir,
            main="main.cpp",
            files={"main.cpp": code},
            run_contexts={"macro": []},
        )

        run_common(cmd, dir)


@pytest.mark.test_release
@pytest.mark.test_coverage_annotation_file_cxx
def test_exporter_tcc_coverage():
    with TemporaryDirectory() as tmp:
        dir = Path(tmp)
        cmd = ProfileRunParams(dir=dir,
                               main="main.cpp",
                               files={
                                   "exporter.hpp":
                                       """
#pragma once
template <typename T>
struct Exporter {
    void impl_1();
    void impl_2();
};             
                """,
                                   "exporter.tcc":
                                       """
#include "exporter.hpp"

template <typename T>
void Exporter<T>::impl_1() {}

template <typename T>
void Exporter<T>::impl_2() {}

                """,
                                   "exporter.cpp":
                                       """
#include "exporter.hpp"                
#include "exporter.tcc"

template class Exporter<int>;
                """,
                                   "main.cpp":
                                       """
#include "exporter.hpp"

int main() {
    Exporter<int> exp;

    exp.impl_1();
    exp.impl_2();
}
                """,
                               },
                               run_contexts={"1": []})

    run_common(cmd, dir)
