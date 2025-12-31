from py_scriptutils.sqlalchemy_utils import (
    ForeignId,
    IdColumn,
    IntColumn,
    StrColumn,
    BoolColumn,
    open_sqlite_session,
)
from sqlalchemy import Column, LargeBinary
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import Session
from pathlib import Path
from beartype import beartype
from pydantic import BaseModel, Field
from beartype.typing import List, Dict, Optional, Type, Any
from py_scriptutils.script_logging import log
import coverage.numbits
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from sqlalchemy.ext.declarative import DeclarativeMeta
    BaseType: Type[DeclarativeMeta]
else:
    BaseType = declarative_base()

CAT = "docgen"

Base: Type[Any] = declarative_base()


class CoverageSchema(Base):
    __tablename__ = "coverage_schema"
    id = IdColumn()
    version = IntColumn()


class Meta(Base):
    __tablename__ = "meta"
    id = IdColumn()
    key = StrColumn()
    value = StrColumn()
    has_arcs = BoolColumn()
    sys_arv = StrColumn()
    version = StrColumn()
    when = StrColumn()


class File(Base):
    __tablename__ = "file"
    id = IdColumn()
    path = StrColumn()


class Context(Base):
    __tablename__ = "context"
    id = IdColumn()
    context = StrColumn()


class LineBits(Base):
    __tablename__ = "line_bits"
    rowid = IdColumn()
    file_id = ForeignId("file.id")
    context_id = ForeignId("context.id")
    numbits = Column(LargeBinary)


class Arc(Base):
    __tablename__ = "arc"
    rowid = IdColumn()
    file_id = ForeignId("file.id")
    context_id = ForeignId("context.id")
    fromno = IntColumn()
    tono = IntColumn()


class Tracer(Base):
    __tablename__ = "tracer"
    id = IdColumn()
    file_id = ForeignId("file.id")
    tracer = StrColumn()


class TestName(BaseModel, extra="forbid"):
    rel_path: str
    test_name: str
    subname: str
    class_name: Optional[str] = None


@beartype
def parse_test_name(text: str) -> Optional[TestName]:
    if "::" in text and "|" in text:
        match text.split("::"):
            case [path, subname]:
                func_name, step = subname.split("|")
                if func_name.startswith("test_"):
                    func_name = func_name[5:]

                return TestName(rel_path=path, test_name=func_name, subname=step)

            case [path, Class, subname]:
                func_name, step = subname.split("|")
                if func_name.startswith("test_"):
                    func_name = func_name[5:]

                return TestName(
                    rel_path=path,
                    test_name=func_name,
                    subname=step,
                    class_name=Class,
                )
            
            case _:
                raise ValueError(text)
    return None


class LineCoverage(BaseModel, extra="forbid"):
    CoveredBy: List[TestName] = Field(default_factory=list)


def as_dict(row: Any) -> Dict[str, Any]:
    if row:
        return {column.name: getattr(row, column.name) for column in row.__table__.columns}
    return {}


@beartype
def get_coverage(session: Session, path: Path) -> Dict[int, LineCoverage]:
    file_rows = session.query(File).where(File.path == str(path)).all()
    if file_rows:
        file_id = file_rows[0].id
        result: Dict[int, LineCoverage] = {}
        row: LineBits
        context: Context
        for row, context in session.query(
                LineBits, Context).where(LineBits.file_id == file_id).join(
                    Context,
                    LineBits.context_id == Context.id,
                ).all():
            test_name = parse_test_name(context.context)
            if test_name and test_name.subname == "run":
                numbits_bytes = row.numbits if isinstance(row.numbits, bytes) else bytes(row.numbits)
                line_numbers = coverage.numbits.numbits_to_nums(numbits_bytes)
                for line in line_numbers:
                    result.setdefault(line - 1,
                                      LineCoverage()).CoveredBy.append(test_name)

        return result

    else:
        return {}


@beartype
def open_coverage(path: Path) -> Session:
    return open_sqlite_session(path, Base)
