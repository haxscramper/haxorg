#!/usr/env/bin python
from beartype.typing import Optional, Any, List, Tuple, Iterable, Dict
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
from py_scriptutils.script_logging import log, to_debug_json
import py_repository.gen_documentation_data as docdata
import dominate.tags as tags
from pygments import lex
from pygments.lexers import CppLexer

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
    OriginalId: int
    First: int
    Last: int

class AnnotationSegment(BaseModel, extra="forbid"):
    Text: str = ""
    Annotations: Dict[int, int] = Field(default_factory=dict)

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
    Segments: List[AnnotationSegment] = Field(default_factory=list)

class AnnotatedFile(BaseModel, extra="forbid"):
    Lines: List[AnnotatedLine] = Field(default_factory= list)

class ProfdataCookie(BaseModel, extra="forbid"):
    test_binary: str
    test_name: str
    test_class: Optional[str] = None
    test_profile: str
    test_params: Any = None


class ProfdataFullProfile(BaseModel, extra="forbid"):
    runs: List[ProfdataCookie] = Field(default_factory=list)


class ProfdataParams(BaseModel, extra="forbid"):
    coverage: str
    coverage_db: str
    perf_trace: Optional[str]
    file_whitelist: List[str]
    file_blacklist: List[str]
    debug_file: Optional[str] = None


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
class CoverageSegmentTree:

    def __init__(self, segments: Iterable[CovSegment]):
        self.root = None
        self.segments = sorted(segments, key=lambda x: (x.LineStart, x.ColStart))
        if self.segments:
            self.root = self.build_tree(0, len(self.segments) - 1)

    @beartype
    class Node:

        def __init__(self, start: int, end: int, segments: Iterable[CovSegment]):
            self.start = start
            self.end = end
            self.segments = segments
            self.left: Optional['CoverageSegmentTree.Node'] = None
            self.right: Optional['CoverageSegmentTree.Node'] = None

    def build_tree(self, start: int, end: int) -> Node:
        if start > end:
            return None
        if start == end:
            return self.Node(start, end, [self.segments[start]])

        mid = (start + end) // 2
        node = self.Node(start, end, self.segments[start:end + 1])
        node.left = self.build_tree(start, mid)
        node.right = self.build_tree(mid + 1, end)
        return node

    def query(self,
              line: int,
              col: int,
              node: Optional[Node] = None) -> Iterable[CovSegment]:
        if node is None:
            node = self.root
        if node is None:
            return []

        # If the point is outside the bounds of the segments in this node
        if node.start > line or node.end < line:
            return []

        # Check for intersection with segments at this node
        result = [seg for seg in node.segments if seg.intersects(line, col)]

        # Recurse on child nodes
        if node.left and line <= (node.left.start + node.left.end) // 2:
            result.extend(self.query(line, col, node.left))
        if node.right and line >= (node.right.start + node.right.end) // 2 + 1:
            result.extend(self.query(line, col, node.right))

        return result


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


class DocCodeRunCall(BaseModel, extra="forbid"):
    Count: int
    CalledBy: str


class DocCodeCxxCoverage(BaseModel, extra="forbid"):
    Call: List[DocCodeRunCall] = Field(default_factory=list)


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
def convert_cxx_tree(
    RootPath: Path,
    AbsPath: Path,
    coverage_session: Optional[Session],
) -> DocCodeCxxFile:
    outfile = read_code_file(RootPath, AbsPath)

    if coverage_session:
        query = get_coverage_of(coverage_session, AbsPath)
        if query is not None:
            log(CAT).info(f"Has coverage for {AbsPath}")
            outfile.Coverage = CoverageSegmentTree(
                it[0]
                for it in coverage_session.execute(query.where(
                    CovSegment.IsLeaf == True)))

    return outfile


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
def get_flat_coverage(session: Session, Lines: List[DocCodeCxxLine],
                      segments: Select[Tuple[CovSegment]]) -> List[GenCovSegmentFlat]:
    result = []

    line_starts: List[int] = []
    current_position = 0
    for line in Lines:
        line_starts.append(current_position)
        current_position += len(line.Text)

    segment: CovSegment
    for (segment,) in session.execute(segments):
        result.append(
            GenCovSegmentFlat(
                OriginalId=segment.Id,
                First=line_starts[segment.LineStart - 1] + segment.ColStart,
                Last=line_starts[segment.LineEnd - 1] + segment.ColEnd,
            ))

    return result


@beartype
def get_line_group(lines: List[DocCodeCxxLine], kind: int = 12) -> org.SequenceSegmentGroup:
    group = org.SequenceSegmentGroup()
    group.kind = kind

    current_position = 0
    for index, line in enumerate(lines):
        group.segments.append(
            org.SequenceSegment(
                kind=index,
                first=current_position,
                last=current_position + len(line.Text),
            ))

        current_position += len(line.Text)

    return group


@beartype
def get_coverage_group(segments: List[GenCovSegmentFlat], kind: int = 13) -> org.SequenceSegmentGroup:
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
def get_annotated_files(text: str, annotations: List[org.SequenceAnnotation], line_group_kind: int = 12,) -> AnnotatedFile:
    current_line = 0
    file = AnnotatedFile()
    file.Lines.append(AnnotatedLine())

    for item in annotations:
        print(item.__dict__)
        log(CAT).info(to_debug_json(item))
        line_idx = None
        annotation: org.SequenceAnnotationTag
        for annotation in item.annotations:
            if annotation.groupKind == line_group_kind:
                line_idx = annotation.segmentKind

        assert line_idx != None

        if line_idx != current_line:
            assert line_idx == len(file.Lines), f"current line:{line_idx} full line count: {len(file.Lines)}"
            file.Lines.append(AnnotatedLine())
            current_line = line_idx

        segment = AnnotationSegment()

        for annotation in item.annotations:
            if annotation.groupKind != line_group_kind:
                segment.Annotations[annotation.groupKind] = annotation.segmentKind

        file.Lines[line_idx].Segments.append(segment)

    return file



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
