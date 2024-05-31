from dataclasses import replace
from enum import Enum
from pathlib import Path
import itertools
import py_scriptutils.algorithm

import dominate.tags as tags
import dominate.util as util
import py_repository.gen_coverage_python as cov_docpy
import py_repository.gen_documentation_data as docdata
import py_repository.gen_documentation_utils as docutils
from sqlalchemy.orm import Session
from beartype import beartype
from beartype.typing import (Dict, Iterable, List, Optional, Tuple, Type, TypeVar, Union)
from pydantic import BaseModel, Field, SerializeAsAny
from pygments.lexers import PythonLexer

T = TypeVar("T")

CAT = "docgen"

from py_scriptutils.script_logging import log


class DocCodePyLine(docdata.DocCodeLine, extra="forbid"):
    TestCoverage: Optional[cov_docpy.LineCoverage] = None




class DocCodePyFile(docdata.DocCodeFile, extra="forbid"):
    Lines: List[DocCodePyLine] = Field(default_factory=list)



@beartype
def convert_py_tree(
    RootPath: Path,
    AbsPath: Path,
    py_coverage_session: Optional[Session],
) -> DocCodePyFile:
    if py_coverage_session:
        line_coverage = cov_docpy.get_coverage(py_coverage_session, AbsPath)

    else:
        line_coverage = {}

    return DocCodePyFile(
        RelPath=AbsPath.relative_to(RootPath),
        Lines=[
            DocCodePyLine(
                Text=line,
                Index=idx,
                TestCoverage=line_coverage.get(idx, None),
            ) for idx, line in enumerate(AbsPath.read_text().splitlines())
        ],
    )



@beartype
def is_empty(line: DocCodePyLine) -> bool:
    return not line.Text.strip()

@beartype
def get_html_code_div(code_file: DocCodePyFile) -> tags.div:
    unique_coverage_context_spans: List[Tuple[range[int], cov_docpy.LineCoverage]] = []
    for key, group in itertools.groupby(
        (pair for pair in enumerate(code_file.Lines) if not is_empty(pair[1])),
            lambda it: it[1].TestCoverage and it[1].TestCoverage.CoveredBy,
    ):
        Lines = [G[0] for G in group]
        assert not Lines or (isinstance(Lines, list) and
                             isinstance(Lines[0], int)), str(Lines)
        if key:
            unique_coverage_context_spans.append((range(min(Lines), max(Lines) + 1), key))

    @beartype
    def get_attr_spans(line: DocCodePyLine) -> List[tags.span]:
        annotations: List[tags.span] = []

        if not code_file.IsTest and not is_empty(line):
            if line.TestCoverage:
                coverage_group = py_scriptutils.algorithm.first_if(
                    items=unique_coverage_context_spans,
                    pred=lambda it: line.Index in it[0],
                )
                if coverage_group:
                    span = tags.span(_class="coverage-span py-coverage")
                    if coverage_group[0][0] == line.Index:
                        span.attributes["class"] += " coverage-span-names"
                        table = tags.table()
                        for test in line.TestCoverage.CoveredBy:
                            table.add(tags.tr(tags.td(util.text(test.test_name))))

                        span.add(table)

                    else:
                        span.add(util.text("…"))
                        span.attributes["class"] += " coverage-span-continuation"

                    annotations.append(span)

        return annotations

    highlight_lexer = PythonLexer()

    @beartype
    def get_line_spans(line: DocCodePyLine) -> List[tags.span]:
        num_span, line_span = docdata.get_code_line_span(
            line=line,
            highilght_lexer=highlight_lexer,
        )

        if not code_file.IsTest and not is_empty(line):
            if line.TestCoverage:
                line_span.attributes["class"] += " cov-visited"

            else:
                line_span.attributes["class"] += " cov-skipped"

        return [num_span, line_span] + get_attr_spans(line)

    return docdata.get_html_code_div_base(
        Lines=code_file.Lines,
        get_line_spans=get_line_spans,
    )

