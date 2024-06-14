#!/usr/env/bin python
from beartype.typing import Optional, Any, List, Tuple, Iterable, Dict, Callable, Iterator, Mapping, Union, Set
from pydantic import Field, BaseModel

from sqlalchemy import create_engine, Column, select, Select
from sqlalchemy.schema import CreateTable
from sqlalchemy.orm import declarative_base, Session
from py_scriptutils.sqlalchemy_utils import IdColumn, ForeignId, IntColumn, StrColumn, BoolColumn
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from sqlalchemy.types import JSON
import enum
from beartype import beartype
from pathlib import Path
from py_scriptutils.sqlalchemy_utils import open_sqlite_session, NumericEnum
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
from dataclasses import dataclass, field
from dominate import document
import functools
from py_scriptutils.tracer import GlobCompleteEvent
import more_itertools
import itertools
import json

CAT = "coverage"

CoverageSchema = declarative_base()


class CovFunction(CoverageSchema):
    __tablename__ = "CovFunction"
    Id = IdColumn()
    Mangled = StrColumn()
    Demangled = StrColumn()
    Parsed = Column(JSON)


class CovContextKind(enum.Enum):
    GTest = "GTest"
    OrgCorpus = "OrgCorpus"


class CovContext(CoverageSchema):
    __tablename__ = "CovContext"
    Id = IdColumn()
    Name = StrColumn()
    Parent = StrColumn(nullable=True)
    Profile = StrColumn()
    Params = Column(JSON)
    Binary = StrColumn()

    def getKind(self) -> CovContextKind:
        if self.Params and "kind" in self.Params:
            return CovContextKind(self.Params["kind"])

        else:
            return CovContextKind.GTest

    @beartype
    def getContextRunLine(self) -> Optional[int]:
        if self.Params and "loc" in self.Params:
            return int(self.Params["loc"]["line"])

    @beartype
    def getContextRunCol(self) -> Optional[int]:
        if self.Params and "loc" in self.Params:
            return int(self.Params["loc"]["col"])

    @beartype
    def getContextRunFile(self) -> Optional[str]:
        if self.Params and "loc" in self.Params:
            return self.Params["loc"]["path"]

    @beartype
    def getContextRunArgs(self) -> Optional[List[Any]]:
        if self.Params and "args" in self.Params:
            return [it for it in self.Params["args"]]


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
    MCDCDecisionRegion = 5
    MCDCBranchRegion = 6


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
    RegionKind = Column(NumericEnum(CovRegionKind))


class CovFileRegion(CoverageSchema):
    __tablename__ = "CovFileRegion"
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
    RegionKind = Column(NumericEnum(CovRegionKind))
    File = ForeignId(CovFile.Id)
    Function = ForeignId(CovFunction.Id, nullable=True)

    def startLoc(self) -> Tuple[int, int]:
        return (self.LineStart, self.ColumnStart)

    def endLoc(self) -> Tuple[int, int]:
        return (self.LineEnd, self.ColumnEnd)


class CovInstantiationGroup(CoverageSchema):
    __tablename__ = "CovInstantiationGroup"
    Id = IdColumn()
    Line = IntColumn()
    Col = IntColumn()


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
    CoverageSegmentIdx: List[int] = Field(default_factory=list)

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


@beartype
@dataclass
class GenCovSegmentContext():
    # Coverage context entry can be associated with multiple segments in the database.
    # This class bundles together information to identify the context *when* the segment
    # might've been executed together with the segment itself to check *if* it has
    # actually been executed (execution count)
    Context: CovContext
    Segment: CovFileRegion


@beartype
@dataclass
class CovSegmentInstantiation():
    Segment: CovFileRegion
    Function: Optional[CovFunction] = None


@beartype
@dataclass
class CovSegmentFunctionGroup():
    # Parent coverage context for all individual file region executions
    Context: CovContext

    # Coverage context and a corresponding coverage function
    FunctionSegments: List[CovSegmentInstantiation] = field(default_factory=list)


@beartype
@dataclass
class CovSegmentContextGroup():
    # Segment executions grouped by the coverage context. All coverage contexts related to a specific region in the code file
    Grouped: List[CovSegmentFunctionGroup] = field(default_factory=list)


class CovContextModel(BaseModel, extra="forbid"):
    Name: str = Field(description="Direct name of the execution context")
    Parent: Optional[str] = Field(description="Parent name for the execution context",
                                  default=None)
    RunLine: Optional[int] = Field(
        description="Where the test is executed. Set for tests that are generated "
        "from external configuration files, mainly the org parse corpus",
        default=None,
    )
    RunCol: Optional[int] = Field(
        description="Where test is executed, see run line",
        default=None,
    )
    RunFile: Optional[int] = Field(
        description="Where test is executed, see run line",
        default=None,
    )

    RunArgs: Optional[List[Any]] = Field(
        description="Optional list of the execution arguments. `None` and `[]` have"
        "a different meanings. Not all tests properly communicate the list of arguments, "
        "ones that do not have a `None`.",
        default=None,
    )


class CovSegmentModel(BaseModel, extra="forbid"):
    Function: Optional[int] = Field(
        description="ID of the function which contains this segment. "
        "Mainly for differentiating template function instantiations. Value for a function is stored in the "
        "coverage segment context group model",
        default=None,
    )
    ExecutionCount: int = Field(
        description="Number of execution times for this segment under a parent context "
        "(full number of execution counts over all segments can be computed by "
        "summing up all the coverage context groups)")


class CovSegmentFunctionModel(BaseModel, extra="forbid"):
    Mangled: str = Field(description="Full mangled name of the function")
    Demangled: str = Field(
        description=
        "Full demangled name of the function, if demangle failed, then is set to the same value as mangled"
    )
    SimplifiedDemangled: str = Field(
        description="Simplified representation of the demangled function name")


class CovSegmentFunctionGroupModel(BaseModel, extra="forbid"):
    """
    Grouping of segments under a coverage context. Each function group model stores information 
    """
    Context: CovContextModel
    FunctionSegments: List[CovSegmentModel] = Field(
        default_factory=list,
        description="Full list of segment instantiations for a given point. "
        "If a segment is located inside of a template function, it will have a separate count "
        "for each individual instantiation",
    )


class CovSegmentContextGroupModel(BaseModel, extra="forbid"):
    """
    Full data on execution of a specific segment in the code. Information on execution is grouped by coverage contexts 
    and then by a function. The data model here is poised to answer a question, "for a given segment, who ran it?"
    and give the answer in form of "here are the contexts (tests) that run this piece of code, and here is a more 
    detailed breakdown on which specific instantiations of a function were in this run". 
    """
    Grouped: List[CovSegmentFunctionGroupModel]


class CovFileContextModel(BaseModel, extra="forbid"):
    """
    Full information on executing each individual segment in an annotated file
    """
    SegmentContexts: Dict[int, CovSegmentContextGroupModel] = Field(
        description="Segment ID to a coverage information for this segment",
        default_factory=dict,
    )
    Functions: Dict[int, CovSegmentFunctionModel] = Field(
        default_factory=dict, description="Function ID to the function description data")


class AnnotatedFile(BaseModel, extra="forbid"):
    Lines: List[AnnotatedLine] = Field(default_factory=list)
    # Mapping from execution segment ID to the coverage context for the execution
    SegmentRunContexts: Dict[int, GenCovSegmentContext] = Field(
        default_factory=dict,
        exclude=True,
    )

    SegmentFunctions: Dict[int, CovFunction] = Field(
        default_factory=dict,
        exclude=True,
    )

    SegmentList: List[GenCovSegmentFlat] = Field(default_factory=list)

    class Config:
        orm_mode = True
        arbitrary_types_allowed = True

    @beartype
    def get_debug(self) -> str:
        result = ""
        for func in self.SegmentFunctions.values():
            result += "\n{}\n{}\n{}\n{}".format(
                func.Mangled,
                func.Demangled,
                get_simple_function_name(func),
                json.dumps(func.Parsed, indent=2),
            )

        return result

    @beartype
    def getSortedSegmentIndices(self, segment_idx: List[int]) -> List[int]:
        """
        Sort list of segment indices based on their nesting levels.
        Outermost elements are placed first, innermost are placed latest.
        """

        @beartype
        def get1(original_idx: int) -> Optional[GenCovSegmentContext]:
            return self.SegmentRunContexts.get(original_idx, None)

        @beartype
        def cmpSegment(lhs_idx: int, rhs_idx: int) -> bool:
            # Taking first original ID index because all runs for a given segment will have the same size.
            lhs = get1(self.SegmentList[lhs_idx].OriginalId[0])
            rhs = get1(self.SegmentList[rhs_idx].OriginalId[0])

            if lhs == None:
                return True

            elif rhs == None:
                return False

            elif lhs.Segment.startLoc() != rhs.Segment.startLoc():
                return lhs.Segment.startLoc() < rhs.Segment.startLoc()

            elif lhs.Segment.endLoc() != rhs.Segment.endLoc():
                return rhs.Segment.endLoc() < lhs.Segment.endLoc()

            else:
                return True

        return sorted(segment_idx, key=functools.cmp_to_key(cmpSegment))

    @beartype
    def getExecutionsForSegment(self, segment_idx: int) -> CovSegmentContextGroup:
        contexts: List[GenCovSegmentContext] = []

        for original in self.SegmentList[segment_idx].OriginalId:
            if original in self.SegmentRunContexts:
                ctx = self.SegmentRunContexts[original]
                assert isinstance(ctx, GenCovSegmentContext), f"{type(ctx)}"
                contexts.append(ctx)

        @beartype
        def key_func(ctx: GenCovSegmentContext) -> int:
            return ctx.Context.Id

        result = CovSegmentContextGroup(Grouped=[])
        for key, context_group in itertools.groupby(
                sorted(contexts, key=key_func),
                key=key_func,
        ):
            context_group = list(context_group)
            group = CovSegmentFunctionGroup(
                Context=context_group[0].Context,
                FunctionSegments=[
                    CovSegmentInstantiation(
                        Segment=seg.Segment,
                        Function=self.SegmentFunctions[seg.Segment.Function]
                        if seg.Segment.Function else None) for seg in context_group
                ],
            )

            result.Grouped.append(group)

        return result

    @beartype
    def getExecutionsModelForSegment(self,
                                     segment_idx: int) -> CovSegmentContextGroupModel:
        group = self.getExecutionsForSegment(segment_idx=segment_idx)

        @beartype
        def conv_segment(seg: CovSegmentInstantiation) -> CovSegmentModel:
            return CovSegmentModel(
                ExecutionCount=seg.Segment.ExecutionCount,
                Function=seg.Function.Id if seg.Function else None,
            )

        @beartype
        def conv_context(context: CovContext) -> CovContextModel:
            return CovContextModel(
                Name=context.Name,
                Parent=context.Parent,
                RunLine=context.getContextRunLine(),
                RunCol=context.getContextRunCol(),
                RunFile=context.getContextRunFile(),
                RunArgs=context.getContextRunArgs(),
            )

        @beartype
        def conv_group(group: CovSegmentFunctionGroup) -> CovSegmentFunctionGroupModel:
            return CovSegmentFunctionGroupModel(
                Context=conv_context(group.Context),
                FunctionSegments=[conv_segment(it) for it in group.FunctionSegments],
            )

        return CovSegmentContextGroupModel(
            Grouped=[conv_group(it) for it in group.Grouped],)

    @beartype
    def getExecutionsModelForAllSegments(self,
                                         segments: Iterable[int]) -> CovFileContextModel:
        result = CovFileContextModel()

        @beartype
        def conv_function(group: CovFunction) -> CovSegmentFunctionModel:
            return CovSegmentFunctionModel(
                Mangled=group.Mangled,
                Demangled=group.Demangled,
                SimplifiedDemangled=get_simple_function_name(group),
            )

        for idx in sorted(segments):
            contexts = self.getExecutionsModelForSegment(idx)
            result.SegmentContexts[idx] = contexts

            for it in contexts.Grouped:
                for segment in it.FunctionSegments:
                    if segment.Function and segment.Function not in result:
                        result.Functions[segment.Function] = conv_function(
                            self.SegmentFunctions[segment.Function])

        return result


@beartype
def open_coverage(path: Path) -> Session:
    return open_sqlite_session(path, CoverageSchema)


@beartype
def get_coverage_of(session: Session,
                    path: Path) -> Optional[Select[Tuple[CovFileRegion]]]:
    target_id = session.execute(
        select(CovFile).where(CovFile.Path == str(path))).fetchall()

    match len(target_id):
        case 0:
            return None

        case 1:
            return select(CovFileRegion).where(CovFileRegion.File == target_id[0][0].Id)

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
    segments: Select[Tuple[CovFileRegion]],
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

    segment: CovFileRegion
    for (segment,) in session.execute(segments):
        First = line_starts[segment.LineStart - 1] + segment.ColumnStart - 1
        Last = line_starts[segment.LineEnd - 1] + segment.ColumnEnd - 1

        if False:
            DbgLines = "[{}:{} {}:{}]".format(
                segment.LineStart,
                segment.ColumnStart,
                segment.LineEnd,
                segment.ColumnEnd,
            )

            DbgRange = "[{}..{}]".format(
                First,
                Last,
            )

            DbgText = '{}'.format(
                extract_text(
                    Lines,
                    start=(segment.LineStart, segment.ColumnStart),
                    end=(segment.LineEnd, segment.ColumnEnd),
                ))

            DbgFlatText = FlatLines[First:Last + 1]

            print(f"{DbgLines} {DbgRange} -> '{esc(DbgText)}' / '{esc(DbgFlatText)}'")

        SegmentRuns[(First, Last)].append((segment.Id, None))
        # print(f"{First} {Last} {segment.Id}")

    # print(render_rich_pprint(to_debug_json(SegmentRuns)))

    it: Tuple[Tuple[int, int], List[Tuple[int, str]]]
    for it in sorted(SegmentRuns.items(), key=lambda it: it[0][0]):
        DbgAnnotations = [s[1] for s in it[1] if s[1]]
        result.append(
            GenCovSegmentFlat(
                OriginalId=[s[0] for s in it[1]],
                First=it[0][0],
                Last=it[0][1],
                Dbg=DbgAnnotations if 0 < len(DbgAnnotations) else None,
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

        line_idx: int = None
        annotation: org.SequenceAnnotationTag
        for annotation in item.annotations:
            if annotation.groupKind == line_group_kind:
                # Line annotation segments don't overlap by construction
                assert len(annotation.segmentKinds) == 1
                line_idx = annotation.segmentKinds[0]

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
                segment.TokenKind = str(token_kind_mapping[annotation.segmentKinds[0]])

            elif annotation.groupKind == coverage_group_kind:
                segment.CoverageSegmentIdx = list(annotation.segmentKinds)

            else:
                segment.Annotations[annotation.groupKind] = annotation.segmentKinds

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
    with GlobCompleteEvent("Read file", "cov"):
        file = read_code_file(root_path, abs_path)

    with GlobCompleteEvent("Get coverage for file", "cov"):
        file_cov = get_coverage_of(session, abs_path)

    run_contexts: Dict[int, CovContext] = dict()
    run_functions: Dict[int, CovFunction] = dict()

    if file_cov != None:
        with GlobCompleteEvent("Get flat coverage", "cov"):
            coverage_segments = get_flat_coverage(session, file.Lines, file_cov)

        # pprint_to_file(coverage_segments, "/tmp/coverage_segments.py")
        with GlobCompleteEvent("Get coverage group", "cov"):
            coverage_group = get_coverage_group(coverage_segments)

        with GlobCompleteEvent("Find original segments", "cov"):
            this_file_segments = set()
            for seg in coverage_segments:
                for seg_id in seg.OriginalId:
                    this_file_segments.add(seg_id)

            for segments in more_itertools.chunked(this_file_segments, 256):
                for (original_seg, context) in session.execute(
                        select(CovFileRegion,
                               CovContext).where(CovFileRegion.Id.in_(segments)).join(
                                   CovContext,
                                   CovFileRegion.Context == CovContext.Id,
                               )):

                    assert isinstance(context, CovContext)
                    assert isinstance(original_seg, CovFileRegion)
                    run_contexts[original_seg.Id] = GenCovSegmentContext(
                        Context=context,
                        Segment=original_seg,
                    )

                    if original_seg.Function is not None and original_seg.Function not in run_functions:
                        executed_in = session.execute(
                            select(CovFunction).where(
                                CovFunction.Id == original_seg.Function)).fetchall()[0][0]
                        assert isinstance(executed_in,
                                          CovFunction), f"{type(executed_in)}"
                        run_functions[original_seg.Function] = executed_in

    else:
        coverage_group = None
        coverage_segments = None

    with GlobCompleteEvent("Get line group", "cov"):
        line_group = get_line_group(file.Lines)

    file_full_content = abs_path.read_text()

    if use_highlight:
        with GlobCompleteEvent("Get token group", "cov"):
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
            if coverage_segments[segment].Dbg:
                return str(coverage_segments[segment].Dbg)

    if debug_format_segments:
        debug_format_segments.write_text(
            format_sequence_segments(
                file_full_content,
                groups,
                get_group_name=get_group_name,
                get_segment_name=get_segment_name,
            ))

    with GlobCompleteEvent("Annotate sequence", "cov"):
        token_segmented = org.annotateSequence(
            groups=org.VecOfSequenceSegmentGroupVec(groups),
            first=0,
            last=len(file_full_content),
        )

    with GlobCompleteEvent("Get annotated file", "cov"):
        token_annotated_file = get_annotated_files(
            text=file_full_content,
            annotations=[it for it in token_segmented],
            line_group_kind=line_group.kind,
            token_group_kind=token_group and token_group.kind,
            token_kind_mapping=token_names,
            coverage_group_kind=coverage_group and coverage_group.kind,
        )

    token_annotated_file.SegmentRunContexts = run_contexts
    token_annotated_file.SegmentFunctions = run_functions
    if coverage_segments:
        token_annotated_file.SegmentList = coverage_segments

    return token_annotated_file


@beartype
def try_get(j: dict, path: List[str]) -> Optional[Any]:
    result = j
    for step in path:
        if isinstance(result, dict) and step in result:
            result = result[step]

        else:
            return None

    return result


@beartype
def get_simple_function_name(func: CovFunction) -> str:

    def aux(j: dict) -> Optional[str]:
        match j["NodeKind"]:
            case "NestedName":
                Qual = aux(j["Qual"])
                Name = aux(j["Name"])

                if Qual and Name:
                    return f"{Qual}::{Name}"

                else:
                    return Name

            case "NameType":
                if j["Name"] in ["__cxx11"]:
                    return None

                else:
                    return j["Name"]

            case "FunctionEncoding":
                return aux(j["Name"])

            case "NameWithTemplateArgs":
                if try_get(j, ["Name", "Name", "Name"]) == "basic_string":
                    return "std::string"

                else:
                    return "{}<{}>".format(aux(j["Name"]), aux(j["TemplateArgs"]))

            case "TemplateArgs":
                args = []
                for arg in j["Params"]:
                    res = aux(arg)
                    if res:
                        args.append(res)

                return ", ".join(args)

            case _:
                return j["NodeKind"]

    if func.Parsed is None:
        return func.Demangled

    else:
        return aux(func.Parsed)


@beartype
@dataclass
class FileAnnotationData():
    body: tags.div
    coverage_indices: Set[int]


@beartype
def get_file_annotation_html(file: AnnotatedFile) -> FileAnnotationData:
    div = tags.div()
    coverage_indices: Set[int] = set()

    for line in file.Lines:
        hline = tags.div(_class="code-line")
        tokens = tags.span(_class="code-line-text")

        hline.add(
            tags.span(str(line.Index), _class="code-line-number",
                      id=f"line-{line.Index}"),)

        for segment in line.Segments:
            if segment.Text == "\n":
                continue

            hspan = tags.span(
                segment.Text,
                _class=docdata.abbreviate_token_name(segment.TokenKind),
            )

            if 0 < len(segment.CoverageSegmentIdx):
                # Pick index of the closest segment
                closest_segment: int = file.getSortedSegmentIndices(
                    segment.CoverageSegmentIdx)[-1]
                executions = file.getExecutionsForSegment(closest_segment)
                triggered_executions = [
                    it for it in executions.Grouped
                    if any(0 < gr.Segment.ExecutionCount for gr in it.FunctionSegments)
                ]

                kind = file.SegmentRunContexts[
                    file.SegmentList[closest_segment].OriginalId[0]].Segment.RegionKind

                if kind in [CovRegionKind.CodeRegion, CovRegionKind.ExpansionRegion]:
                    if 0 < len(triggered_executions):
                        coverage_indices.add(closest_segment)
                        hspan["class"] += " segment-cov-executed"

                    else:
                        hspan["class"] += " segment-cov-skipped"

                hspan["onclick"] = f"show_coverage_segment_idx({closest_segment})"

            tokens.add(hspan)

        hline.add(tokens)

        div.add(hline)

    assert len(div) == len(file.Lines)

    result = tags.div(_class="page-tab-content", id="page-code")

    assert len(div) == len(file.Lines)
    result.add(div)

    return FileAnnotationData(
        body=result,
        coverage_indices=coverage_indices,
    )


css_path = get_haxorg_repo_root_path().joinpath(
    "scripts/py_repository/py_repository/gen_documentation.css")

js_path = get_haxorg_repo_root_path().joinpath(
    "scripts/py_repository/py_repository/gen_documentation.js")


@beartype
def get_file_annotation_document(session: Session, root_path: Path,
                                 abs_path: Path) -> document:
    file = get_annotated_files_for_session(
        session=session,
        root_path=root_path,
        abs_path=abs_path,
    )

    html = get_file_annotation_html(file)
    doc = document()
    doc.head.add(tags.link(rel="stylesheet", href=css_path))
    doc.head.add(tags.script(src=str(js_path)))
    json_dump = tags.script(
        type="application/json",
        id="segment-coverage",
    )

    json_dump.add_raw_string(
        file.getExecutionsModelForAllSegments(
            html.coverage_indices).model_dump_json(indent=2))
    doc.head.add(json_dump)

    doc.add(html.body)

    return doc


if __name__ == "__main__":
    sql_url = "sqlite:///:memory:"
    db_engine = create_engine(sql_url)

    full_code = []

    for table in [
            CovFunction,
            CovContext,
            CovFunctionRegion,
            CovFile,
            CovInstantiationGroup,
            CovFunctionInstantiation,
            CovFileRegion,
    ]:
        full_code.append(str(CreateTable(table.__table__).compile(db_engine)) + ";")

    get_haxorg_repo_root_path().joinpath(
        "scripts/cxx_codegen/profdata_merger/profdata_merger.sql").write_text(
            "\n".join(full_code))
