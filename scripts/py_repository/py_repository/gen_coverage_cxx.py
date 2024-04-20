#!/usr/env/bin python
from beartype.typing import Optional, Any, List
from pydantic import Field, BaseModel

from sqlalchemy import create_engine, Column
from sqlalchemy import Enum as SqlEnum
from sqlalchemy.schema import CreateTable
from sqlalchemy.orm import declarative_base
from py_scriptutils.sqlalchemy_utils import IdColumn, ForeignId, IntColumn, StrColumn, BoolColumn
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from sqlalchemy.types import JSON
import enum

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


class CovSegment(CoverageSchema):
    __tablename__ = "CovSegment"
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
    ]:
        full_code.append(str(CreateTable(table.__table__).compile(db_engine)) + ";")

    get_haxorg_repo_root_path().joinpath(
        "scripts/cxx_codegen/profdata_merger/profdata_merger.sql").write_text(
            "\n".join(full_code))
