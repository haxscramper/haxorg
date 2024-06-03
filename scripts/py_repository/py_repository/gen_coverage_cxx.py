#!/usr/env/bin python
from beartype.typing import Optional, Any, List, Tuple, Iterable, Dict, Callable, Iterator, Mapping, Union, Set
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
from dominate import document

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
    # List of coverage segments for the `First, Last` range. The coverage database
    # stores multiple identically-located segments (one for each run), so each run
    # for a given segment is stored as one ID.
    OriginalId: List[int]
    First: int
    Last: int
    Dbg: Any = None


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
    # Mapping from execution segment ID to the coverage context for the execution
    SegmentRunContexts: Dict[int, CovContext] = Field(default_factory=dict, exclude=True)
    SegmentList: List[GenCovSegmentFlat] = Field(default_factory=list)

    class Config:
        orm_mode = True
        arbitrary_types_allowed = True

    def getExecutionContextList(self, segment_idx: int) -> List[CovContext]:
        result = []
        for original in self.SegmentList[segment_idx].OriginalId:
            if original in self.SegmentRunContexts:
                ctx = self.SegmentRunContexts[original]
                assert isinstance(ctx, CovContext), f"{type(ctx)}"
                result.append(ctx)

        return result


@beartype
def open_coverage(path: Path) -> Session:
    return open_sqlite_session(path, CoverageSchema)


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
def extract_text(lines: List[Union[str, DocCodeCxxLine]], start: Tuple[int, int],
                 end: Tuple[int, int]) -> str:
    start_line, start_column = start
    end_line, end_column = end

    def line_at(idx: int, end: Optional[int] = None) -> str:
        if end != None:
            result = []
            for i in range(idx, end):
                result.append(line_at(i))

            return result

        else:
            if isinstance(lines[idx], str):
                return lines[idx]

            else:
                return lines[idx].Text

    if start_line == end_line:
        return line_at(start_line - 1)[start_column - 1:end_column - 1]

    else:
        extracted_lines = [
            line_at(start_line - 1)[start_column - 1:],
            *line_at(start_line, end_line - 1),
            line_at(end_line - 1)[:end_column - 1],
        ]

        return "\n".join(extracted_lines)


def pivot_strings(strings: List[str]) -> List[List[str]]:
    max_len = max(len(s) for s in strings)
    padded_strings = [s.ljust(max_len) for s in strings]
    pivoted = [[padded_strings[row][col]
                for row in range(len(padded_strings))]
               for col in range(max_len)]
    return ["".join(it) for it in pivoted]


@beartype
def format_sequence_segments(
    text: str,
    groups: List[org.SequenceSegmentGroup],
    get_group_name: Callable[[int], Optional[str]],
    get_segment_name: Callable[[int, int], Optional[str]],
) -> str:
    visible_chars = {' ': '␣', '\n': '␤'}
    formatted_text = ''.join(visible_chars.get(c, c) for c in text)

    result: List[List[str]] = []

    result.append([" "] + [str(it) for it in range(len(formatted_text))])
    result.append([" "] + ["" for _ in formatted_text])
    result.append([" "] + [f"'{it}'" for it in formatted_text])

    for group in groups:

        def add_segment_group_lane(
                segments: List[org.SequenceSegment]) -> List[org.SequenceSegment]:
            covered_range: Set[int] = set()
            overlapping: List[org.SequenceSegment] = []

            result.append([" "] + ["" for _ in formatted_text])
            group_lane = [" "] * len(formatted_text)
            segment: org.SequenceSegment
            for segment in segments:
                segment_set = set(range(segment.first, segment.last + 1))
                if 0 < len(covered_range.intersection(segment_set)):
                    overlapping.append(segment)

                else:
                    segment_desc = f"{segment.kind} [{segment.first}..{segment.last}]"
                    name = get_segment_name(group.kind, segment.kind)
                    if name:
                        segment_desc += f" ({name})"

                    assert group_lane[segment.first] == " "
                    if segment.first == segment.last:
                        group_lane[segment.first] = f"⟧{segment_desc}"
                    else:
                        group_lane[segment.first] = f"╗{segment_desc}"
                        if segment.last < len(group_lane):
                            assert group_lane[segment.last] == " "
                            group_lane[segment.last] = "╝"

                        for i in range(segment.first + 1, segment.last):
                            assert group_lane[i] == " "
                            group_lane[i] = "║"

                    covered_range = covered_range.union(segment_set)

            group_desc = str(group.kind)
            name = get_group_name(group.kind)
            if name:
                group_desc += f" ({name})"

            group_lane = [group_desc] + group_lane
            result.append(group_lane)

            return overlapping

        leftover = group.segments
        while 0 < len(leftover):
            leftover = add_segment_group_lane(leftover)

    out_str = []

    for lane in result:
        lane_size = max(len(it) for it in lane)
        for lane_slice in range(0, lane_size):
            out_line = []
            for column in range(len(formatted_text)):
                if lane_slice < len(lane[column]):
                    out_line.append(lane[column][lane_slice])

                else:
                    out_line.append(" ")

            out_str.append("".join(out_line))

    return "\n".join(pivot_strings(out_str))


@beartype
def read_code_file(RootPath: Path, AbsPath: Path) -> DocCodeCxxFile:
    return DocCodeCxxFile(
        RelPath=AbsPath.relative_to(RootPath),
        Lines=[
            DocCodeCxxLine(Text=line, Index=idx)
            for idx, line in enumerate(AbsPath.read_text().splitlines())
        ],
    )


def esc(s):
    return s.replace("\n", "␤")


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
        current_position += len(line.Text) + 1

    SegmentRuns: Dict[Tuple[int, int], List[Tuple[int,
                                                  str]]] = defaultdict(lambda: list())

    # FlatLines = "\n".join(it.Text for it in Lines)

    segment: CovSegment
    for (segment,) in session.execute(segments):
        if segment.IsLeaf:
            First = line_starts[segment.LineStart - 1] + segment.ColStart - 1
            Last = line_starts[segment.LineEnd - 1] + segment.ColEnd - 1

            if False:
                DbgLines = "[{}:{} {}:{}]".format(
                    segment.LineStart,
                    segment.ColStart,
                    segment.LineEnd,
                    segment.ColEnd,
                )

                DbgRange = "[{}..{}]".format(
                    First,
                    Last,
                )

                DbgText = '{}'.format(
                    extract_text(
                        Lines,
                        start=(segment.LineStart, segment.ColStart),
                        end=(segment.LineEnd, segment.ColEnd),
                    ))

                DbgFlatText = FlatLines[First:Last + 1]

                print(f"{DbgLines} {DbgRange} -> '{esc(DbgText)}' / '{esc(DbgFlatText)}'")

            SegmentRuns[(First, Last)].append((segment.Id, None))
        # print(f"{First} {Last} {segment.Id}")

    # print(render_rich_pprint(to_debug_json(SegmentRuns)))

    it: Tuple[Tuple[int, int], List[Tuple[int, str]]]
    for it in sorted(SegmentRuns.items(), key=lambda it: it[0][0]):
        result.append(
            GenCovSegmentFlat(
                OriginalId=[s[0] for s in it[1]],
                First=it[0][0],
                Last=it[0][1],
                Dbg=[s[1] for s in it[1]],
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
    debug_format_segments: Optional[Path] = None,
    use_highlight: bool = True,
) -> AnnotatedFile:
    file = read_code_file(root_path, abs_path)
    file_cov = get_coverage_of(session, abs_path)
    run_contexts: Dict[int, CovContext] = dict()

    if file_cov != None:
        coverage_segments = get_flat_coverage(session, file.Lines, file_cov)
        log(CAT).info(f"{len(coverage_segments)} segments")
        # pprint_to_file(coverage_segments, "/tmp/coverage_segments.py")
        coverage_group = get_coverage_group(coverage_segments)

        for seg in coverage_segments:
            for seg_id in seg.OriginalId:
                original_seg = session.execute(
                    select(CovSegment).where(CovSegment.Id == seg_id)).fetchall()
                assert len(original_seg) == 1
                assert len(original_seg[0]) == 1
                original_seg: CovSegment = original_seg[0][0]
                assert isinstance(original_seg, CovSegment)
                context = session.execute(
                    select(CovContext).where(
                        CovContext.Id == original_seg.Context)).fetchall()
                assert isinstance(context[0][0], CovContext)
                run_contexts[seg_id] = context[0][0]

    else:
        coverage_group = None
        coverage_segments = None



    line_group = get_line_group(file.Lines)
    file_full_content = abs_path.read_text()
    if use_highlight:
        token_dict = defaultdict(lambda: len(token_dict))
        token_group = get_token_group(file_full_content,
                                  token_to_int=lambda it: token_dict[it])

    else:
        token_dict = dict()
        token_group = None

    groups = [line_group]

    if token_group:
        groups.append(token_group)

    if coverage_group:
        groups.append(coverage_group)

    token_names = {kind: key for key, kind in token_dict.items()}

    def get_group_name(it: int) -> Optional[str]:
        if it == line_group.kind:
            return "line"

        elif token_group and it == token_group.kind:
            return "tok"

        elif coverage_group and it == coverage_group.kind:
            return "cov"

    def get_segment_name(group: int, segment: int) -> Optional[str]:
        if token_group and group == token_group.kind:
            return token_names[segment]

        elif coverage_group and group == coverage_group.kind:
            return str(coverage_segments[segment].Dbg)

    if debug_format_segments:
        debug_format_segments.write_text(
            format_sequence_segments(
                file_full_content,
                groups,
                get_group_name=get_group_name,
                get_segment_name=get_segment_name,
            ))

    token_segmented = org.annotateSequence(
        groups=org.VecOfSequenceSegmentGroupVec(groups),
        first=0,
        last=len(file_full_content),
    )

    token_annotated_file = get_annotated_files(
        text=file_full_content,
        annotations=[it for it in token_segmented],
        line_group_kind=line_group.kind,
        token_group_kind=token_group and token_group.kind,
        token_kind_mapping=token_names,
        coverage_group_kind=coverage_group and coverage_group.kind,
    )

    token_annotated_file.SegmentRunContexts = run_contexts
    if coverage_segments:
        token_annotated_file.SegmentList = coverage_segments

    return token_annotated_file


@beartype
def get_file_annotation_html(file: AnnotatedFile) -> tags.div:
    div = tags.div()
    coverage_indices: Set[int] = set()

    for line in file.Lines:
        hline = tags.div(_class="code-line")
        tokens = tags.span(_class="code-line-text")

        for segment in line.Segments:
            if segment.Text == "\n":
                continue

            hspan = tags.span(
                segment.Text,
                _class=docdata.abbreviate_token_name(segment.TokenKind),
            )

            if segment.CoverageSegmentIdx:
                executions = file.getExecutionContextList(segment.CoverageSegmentIdx)
                if executions:
                    coverage_indices.add(segment.CoverageSegmentIdx)
                    hspan["class"] += " segment-cov-executed"

                else:
                    hspan["class"] += " segment-cov-skipped"

                hspan["data-cov-idx"] = str(segment.CoverageSegmentIdx)

                for run in executions:
                    hspan["covered"] = "run"

            tokens.add(hspan)

        hline.add(tokens)

        div.add(hline)

    assert len(div) == len(file.Lines)

    result = tags.div(_class="page-tab-content", id="page-code")
    coverage_data_div = tags.div(_class="coverage-data", style="display:none;")
    for idx in coverage_indices:
        context_div = tags.div(_class="cov-context", id=f"cov-context-{idx}")
        executions = file.getExecutionContextList(idx)

        for run in executions:
            context_div.add(
                tags.div(
                    f"Name: {run.Name}, Profile: {run.Profile}, Params: {run.Params}"))

        coverage_data_div.add(context_div)

    result.add(coverage_data_div)
    assert len(div) == len(file.Lines)
    result.add(div)

    return result

css_path = get_haxorg_repo_root_path().joinpath(
    "scripts/py_repository/py_repository/gen_documentation.css")

js_path = get_haxorg_repo_root_path().joinpath(
    "scripts/py_repository/py_repository/gen_documentation.js")


@beartype
def get_file_annotation_document(session: Session, root_path: Path, abs_path: Path) -> document:
    file = get_annotated_files_for_session(
        session=session,
        root_path=root_path,
        abs_path=abs_path,
    )

    html = get_file_annotation_html(file)
    doc = document()
    doc.head.add(tags.link(rel="stylesheet", href=css_path))
    doc.head.add(tags.script(src=str(js_path)))
    doc.add(html)

    return doc


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
