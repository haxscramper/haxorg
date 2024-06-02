#!/usr/env/bin python
from beartype.typing import Optional, Any, List, Tuple, Iterable, Dict, Callable, Iterator, Mapping
from pydantic import Field, BaseModel

from sqlalchemy import create_engine, Column, select, Select
from sqlalchemy import Enum as SqlEnum
from sqlalchemy.schema import CreateTable
from sqlalchemy.orm import declarative_base, Session
from py_scriptutils.sqlalchemy_utils import IdColumn, ForeignId, IntColumn, StrColumn, BoolColumn
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from sqlalchemy.types import JSON
import enum
from beartype import beartype
from pathlib import Path
from py_scriptutils.sqlalchemy_utils import open_sqlite_session
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.script_logging import log, to_debug_json, pprint_to_file
from py_scriptutils.rich_utils import render_rich_pprint
import py_repository.gen_documentation_data as docdata
import dominate.tags as tags
from pygments import lex
from pygments.lexers import CppLexer
from pygments.token import Token, _TokenType, Whitespace
from py_repository.gen_coverage_cookies import *
from collections import defaultdict
from dataclasses import dataclass

CAT = "coverage"

CoverageSchema = declarative_base()


class CovFunction(CoverageSchema):
    __tablename__ = "CovFunction"
    Id = IdColumn()
    Mangled = StrColumn()
    Demangled = StrColumn()
    Parsed = Column(JSON)


class CovContext(CoverageSchema):
    __tablename__ = "CovContext"
    Id = IdColumn()
    Name = StrColumn()
    Parent = StrColumn(nullable=True)
    Profile = StrColumn()
    Params = Column(JSON)
    Binary = StrColumn()


class CovFile(CoverageSchema):
    __tablename__ = "CovFile"
    Id = IdColumn()
    Path = StrColumn()


class CovRegionKind(enum.Enum):
    CodeRegion = 0
    ExpansionRegion = 1
    SkippedRegion = 2
    GapRegion = 3
    BranchRegion = 4


class CovFunctionRegion(CoverageSchema):
    __tablename__ = "CovFunctionRegion"
    Id = IdColumn()
    Function = ForeignId(CovFunction.Id)
    Context = ForeignId(CovContext.Id)
    IsBranch = BoolColumn()
    ExecutionCount = IntColumn()
    FalseExecutionCount = IntColumn()
    Folded = BoolColumn()

    # Counter mapping region fields
    FileId = ForeignId(CovFile.Id)
    ExpandedFileId = ForeignId(CovFile.Id)
    LineStart = IntColumn()
    ColumnStart = IntColumn()
    LineEnd = IntColumn()
    ColumnEnd = IntColumn()
    RegionKind = Column(SqlEnum(CovRegionKind))


class CovFileBranch(CoverageSchema):
    __tablename__ = "CovFileBranch"
    Id = IdColumn()
    Context = ForeignId(CovContext.Id)
    ExecutionCount = IntColumn()
    FalseExecutionCount = IntColumn()
    Folded = BoolColumn()

    # Counter mapping region fields
    LineStart = IntColumn()
    ColumnStart = IntColumn()
    LineEnd = IntColumn()
    ColumnEnd = IntColumn()
    RegionKind = Column(SqlEnum(CovRegionKind))


class CovSegmentFlat(CoverageSchema):
    __tablename__ = "CovSegmentFlat"
    Id = IdColumn()
    Line = IntColumn()
    Col = IntColumn()
    Count = IntColumn()
    HasCount = BoolColumn()
    IsRegionEntry = BoolColumn()
    IsGapRegion = BoolColumn()
    File = ForeignId(CovFile.Id)
    Context = ForeignId(CovContext.Id)
    SegmentIndex = IntColumn()


class CovSegment(CoverageSchema):
    __tablename__ = "CovSegment"
    Id = IdColumn()
    LineStart = IntColumn()
    ColStart = IntColumn()
    LineEnd = IntColumn()
    ColEnd = IntColumn()
    StartCount = IntColumn()
    EndCount = IntColumn()
    HasCount = BoolColumn()
    File = ForeignId(CovFile.Id)
    Context = ForeignId(CovContext.Id)
    SegmentIndex = IntColumn()
    NestedIn = ForeignId("CovSegment.Id", nullable=True)
    IsLeaf = BoolColumn()
    IsBranch = BoolColumn()

    def intersects(self, line: int, col: int) -> bool:
        return (self.LineStart <= line <= self.LineEnd) and (self.ColStart <= col <=
                                                             self.ColEnd)


class CovInstantiationGroup(CoverageSchema):
    __tablename__ = "CovInstantiationGroup"
    Id = IdColumn()
    Line = IntColumn()
    Col = IntColumn()


class CovExpansionRegion(CoverageSchema):
    __tablename__ = "CovExpansionRegion"
    Id = IdColumn()
    FileId = ForeignId(CovFile.Id)
    Region = ForeignId(CovFunctionRegion.Id)
    Function = ForeignId(CovFunction.Id)


class CovFunctionInstantiation(CoverageSchema):
    __tablename__ = "CovFunctionInstantiation"
    Id = IdColumn()
    Instantiation = ForeignId(CovInstantiationGroup.Id)
    Function = ForeignId(CovFunction.Id)


class GenCovSegmentFlat(BaseModel, extra="forbid"):
    OriginalId: List[int]
    First: int
    Last: int


class AnnotationSegment(BaseModel, extra="forbid"):
    Text: str = ""
    Annotations: Dict[int, int] = Field(default_factory=dict)
    TokenKind: str = ""
    CoverageSegmentIdx: Optional[int] = None

    def isAnnotated(self) -> bool:
        return 0 < len(self.Annotations)

    def isGrouped(self, kind: int) -> bool:
        "Is the segment annotated with a specific group kind?"
        return kind in self.Annotations

    def getAnnotation(self, kind: int) -> Optional[int]:
        "Get segment annotation for a specified group"
        if self.isGrouped(kind):
            return self.Annotations[kind]


class AnnotatedLine(BaseModel, extra="forbid"):
    Index: int
    Segments: List[AnnotationSegment] = Field(default_factory=list)


class AnnotatedFile(BaseModel, extra="forbid"):
    Lines: List[AnnotatedLine] = Field(default_factory=list)


@beartype
def open_coverage(path: Path) -> Session:
    return open_sqlite_session(path, CoverageSchema)


@beartype
def extract_text(lines: List[str], start: Tuple[int, int], end: Tuple[int, int]) -> str:
    start_line, start_column = start
    end_line, end_column = end

    if start_line == end_line:
        return lines[start_line - 1][start_column - 1:end_column - 1]

    else:
        extracted_lines = [
            lines[start_line - 1][start_column - 1:]
        ] + lines[start_line:end_line - 1] + [lines[end_line - 1][:end_column - 1]]
        return "\n".join(extracted_lines)


@beartype
def get_coverage_of(session: Session, path: Path) -> Optional[Select[Tuple[CovSegment]]]:
    target_id = session.execute(
        select(CovFile).where(CovFile.Path == str(path))).fetchall()

    match len(target_id):
        case 0:
            return None

        case 1:
            return select(CovSegment).where(CovSegment.File == target_id[0][0].Id)

        case _:
            raise ValueError(
                f"{len(target_id)} files matched for given path '{path}', expected exactly 0-1 matches"
            )


class DocCodeCxxLine(docdata.DocCodeLine, extra="forbid"):
    pass


class DocCodeCxxFile(docdata.DocCodeFile, extra="forbid"):
    Lines: List[DocCodeCxxLine] = Field(default_factory=list)


@beartype
def read_code_file(RootPath: Path, AbsPath: Path) -> DocCodeCxxFile:
    return DocCodeCxxFile(
        RelPath=AbsPath.relative_to(RootPath),
        Lines=[
            DocCodeCxxLine(Text=line, Index=idx)
            for idx, line in enumerate(AbsPath.read_text().splitlines())
        ],
    )


@beartype
def get_html_code_div(code_file: DocCodeCxxFile) -> tags.div:
    highlight_lexer = CppLexer()

    def get_line_spans(line: DocCodeCxxLine) -> List[tags.span]:
        return list(
            docdata.get_code_line_span(
                line=line,
                highilght_lexer=highlight_lexer,
            ))

    return docdata.get_html_code_div_base(
        Lines=code_file.Lines,
        get_line_spans=get_line_spans,
    )


@beartype
def get_flat_coverage(
    session: Session,
    Lines: List[DocCodeCxxLine],
    segments: Select[Tuple[CovSegment]],
) -> List[GenCovSegmentFlat]:
    result = []

    line_starts: List[int] = []
    current_position = 0
    for line in Lines:
        line_starts.append(current_position)
        current_position += len(line.Text)

    SegmentRuns: Dict[Tuple[int, int], List[int]] = defaultdict(lambda: list())

    segment: CovSegment
    for (segment,) in session.execute(segments):
        First = line_starts[segment.LineStart - 1] + segment.ColStart
        Last = line_starts[segment.LineEnd - 1] + segment.ColEnd

        SegmentRuns[(First, Last)].append(segment.Id)
        # print(f"{First} {Last} {segment.Id}")

    # print(render_rich_pprint(to_debug_json(SegmentRuns)))

    it: Tuple[Tuple[int, int], List[int]]
    for it in sorted(SegmentRuns.items(), key=lambda it: it[0][0]):
        result.append(GenCovSegmentFlat(
            OriginalId=it[1],
            First=it[0][0],
            Last=it[0][1],
        ))

    return result


@beartype
def get_line_group(lines: List[DocCodeCxxLine],
                   kind: int = 12) -> org.SequenceSegmentGroup:
    group = org.SequenceSegmentGroup()
    group.kind = kind

    current_position = 0
    for index, line in enumerate(lines):
        is_last = index == len(lines) - 1
        line_end = current_position + len(line.Text)

        seg = org.SequenceSegment(
            kind=index,
            first=current_position,
            last=line_end,
        )

        group.segments.append(seg)
        current_position = line_end + 1

    return group


@beartype
def get_coverage_group(
    segments: List[GenCovSegmentFlat],
    kind: int = 13,
) -> org.SequenceSegmentGroup:
    group = org.SequenceSegmentGroup()
    group.kind = kind

    for idx, segment in enumerate(segments):
        group.segments.append(
            org.SequenceSegment(
                kind=idx,
                first=segment.First,
                last=segment.Last,
            ))

    return group


@beartype
def get_token_group(
    text: str,
    token_to_int: Callable[[_TokenType], int],
    kind: int = 14,
) -> org.SequenceSegmentGroup:
    group = org.SequenceSegmentGroup()
    group.kind = kind
    position = 0

    def esc(s):
        return s.replace("\n", "␤")

    for idx, (token_type, token_text) in enumerate(
            lex(
                text,
                CppLexer(
                    stripnl=False,  # Don't drop newlines in the input
                    ensurenl=False,  # Don't introduce arbitrary trailing whitespaces
                ))):
        kind = token_to_int(token_type)

        assert type(kind) is int, f"{token_type} -> {kind}, {type(kind)}"
        last = position + len(token_text) - 1
        desc = f"[{idx:<2}] {kind:<3} {str(token_type):<40} '{esc(token_text)}' [{position}:{last}] -> '{esc(text[position:last+1])}'"

        assert token_text == text[position:last + 1], desc

        group.segments.append(org.SequenceSegment(kind=kind, first=position, last=last))

        position = last + 1

    return group


@beartype
def get_annotated_files(
    text: str,
    annotations: List[org.SequenceAnnotation],
    line_group_kind: int,
    token_group_kind: Optional[int] = None,
    token_kind_mapping: Mapping[int, _TokenType] = dict(),
    coverage_group_kind: Optional[int] = None,
) -> AnnotatedFile:
    current_line = 0
    file = AnnotatedFile()
    file.Lines.append(AnnotatedLine(Index=0))
    last_segment_finish = None

    for item in annotations:
        if last_segment_finish and item.first != last_segment_finish + 1:
            file.Lines[line_idx].Segments.append(
                AnnotationSegment(Text=text[last_segment_finish + 1:item.first]))

        line_idx = None
        annotation: org.SequenceAnnotationTag
        for annotation in item.annotations:
            if annotation.groupKind == line_group_kind:
                line_idx = annotation.segmentKind

        assert line_idx != None

        if line_idx != current_line:
            assert line_idx == len(
                file.Lines), f"current line:{line_idx} full line count: {len(file.Lines)}"
            file.Lines.append(AnnotatedLine(Index=line_idx))
            current_line = line_idx

        segment = AnnotationSegment(Text=text[item.first:item.last + 1])

        for annotation in item.annotations:
            if annotation.groupKind == line_group_kind:
                pass

            elif annotation.groupKind == token_group_kind:
                segment.TokenKind = str(token_kind_mapping[annotation.segmentKind])

            elif annotation.groupKind == coverage_group_kind:
                segment.CoverageSegmentIdx = annotation.segmentKind

            else:
                segment.Annotations[annotation.groupKind] = annotation.segmentKind

        file.Lines[line_idx].Segments.append(segment)

        last_segment_finish = item.last

    return file


@beartype
def get_annotated_files_for_session(
    session: Session,
    root_path: Path,
    abs_path: Path,
) -> AnnotatedFile:
    file_cov = get_coverage_of(session, abs_path)
    file = read_code_file(root_path, abs_path)
    coverage_segments = get_flat_coverage(session, file.Lines, file_cov)
    pprint_to_file(coverage_segments, "/tmp/coverage_segments.py")
    coverage_group = get_coverage_group(coverage_segments)
    line_group = get_line_group(file.Lines)
    file_full_content = abs_path.read_text()
    token_dict = defaultdict(lambda: len(token_dict))
    token_group = get_token_group(file_full_content,
                                  token_to_int=lambda it: token_dict[it])

    token_segmented = org.annotateSequence(
        groups=org.VecOfSequenceSegmentGroupVec([line_group, coverage_group,
                                                 token_group]),
        first=0,
        last=len(file_full_content),
    )

    token_annotated_file = get_annotated_files(
        text=file_full_content,
        annotations=[it for it in token_segmented],
        line_group_kind=line_group.kind,
        token_group_kind=token_group.kind,
        token_kind_mapping={
            kind: key for key, kind in token_dict.items()
        },
        coverage_group_kind=coverage_group.kind,
    )

    return token_annotated_file


if __name__ == "__main__":
    sql_url = "sqlite:///:memory:"
    db_engine = create_engine(sql_url)

    full_code = []

    for table in [
            CovFunction,
            CovContext,
            CovFunctionRegion,
            CovFileBranch,
            CovFile,
            CovInstantiationGroup,
            CovFunctionInstantiation,
            CovSegment,
            CovExpansionRegion,
            CovSegmentFlat,
    ]:
        full_code.append(str(CreateTable(table.__table__).compile(db_engine)) + ";")

    get_haxorg_repo_root_path().joinpath(
        "scripts/cxx_codegen/profdata_merger/profdata_merger.sql").write_text(
            "\n".join(full_code))
