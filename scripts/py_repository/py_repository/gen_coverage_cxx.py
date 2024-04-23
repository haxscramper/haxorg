#!/usr/env/bin python
from beartype.typing import Optional, Any, List, Tuple, Iterable
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
    debug_file: Optional[str]


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
def get_coverage_of(session: Session, path: Path) -> Select[Tuple[CovSegment]]:
    target_id = session.execute(
        select(CovFile).where(CovFile.Path == str(path))).fetchall()

    if len(target_id) != 1:
        raise ValueError(
            f"{len(target_id)} files matched for given path '{path}', expected exactly one match"
        )

    return select(CovSegment).where(CovSegment.File == target_id[0][0].Id)


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
