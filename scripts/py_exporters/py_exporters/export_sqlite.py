import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.sqlalchemy_utils import IdColumn, ForeignId, IntColumn, StrColumn, DateTimeColumn
from sqlalchemy.orm import declarative_base, sessionmaker
from sqlalchemy import DateTime, Column, Enum, Engine
import enum
from py_scriptutils.script_logging import log
from beartype.typing import List
from beartype import beartype
from py_haxorg.pyhaxorg_utils import evalDateTime
from py_exporters.export_ultraplain import ExporterUltraplain

Base = declarative_base()


class Document(Base):
    __tablename__ = "Document"
    id = IdColumn()


class Location(Base):
    __tablename__ = "Location"
    id = IdColumn()
    line = IntColumn()
    column = IntColumn()
    file = ForeignId(name="File.id")


class File(Base):
    __tablename__ = "File"
    id = IdColumn()
    path = StrColumn()


class Subtree(Base):
    __tablename__ = "Subtree"
    id = IdColumn()
    plaintext_title = StrColumn()
    level = IntColumn()
    parent = ForeignId(name="Subtree.id", nullable=True)
    created = DateTimeColumn(nullable=True)
    scheduled = DateTimeColumn(nullable=True)
    deadline = DateTimeColumn(nullable=True)
    closed = DateTimeColumn(nullable=True)
    location = ForeignId(name="Location.id")


class BlockKind(enum.Enum):
    Paragraph = 1
    Src = 2
    Example = 3
    Quote = 4


class Block(Base):
    __tablename__ = "Block"
    id = IdColumn()
    kind = Column(Enum(BlockKind))
    plaintext = StrColumn(nullable=True)
    timestamp = DateTimeColumn(nullable=True)
    parent = ForeignId(name="Block.id", nullable=True)
    wordcount = IntColumn(nullable=True)
    location = ForeignId(name="Location.id")


CAT = "haxorg.export.sqlite"


@beartype
def registerDocument(node: org.Org, engine: Engine, file: str):
    Base.metadata.bind = engine
    sesion_maker = sessionmaker(bind=engine)
    session = sesion_maker()
    osk = org.OrgSemKind

    file_record = File(path=file)
    session.add(file_record)
    session.commit()

    counter = 0

    def get_location(node: org.Org) -> int:
        nonlocal counter
        result = file_record.id * 1E6 + counter
        counter += 1
        session.add(
            Location(
                line=node.loc.line,
                column=node.loc.column,
                file=file_record.id,
                id=result,
            ))
        return result

    @beartype
    def aux(node: org.Org):
        match node.getKind():
            case osk.Subtree:
                session.add(
                    Subtree(
                        level=node.level,
                        plaintext_title=ExporterUltraplain.getStr(node.title),
                        location=get_location(node),
                    ))

                for sub in node:
                    aux(sub)

            case osk.Document | osk.List | osk.ListItem:
                for sub in node:
                    aux(sub)

            case osk.Paragraph:
                subnodes: List[org.Org] = [n for n in node]
                wordcount = 0
                if 0 < len(subnodes):
                    start = 2 if 2 < len(
                        subnodes) and subnodes[0].getKind() == osk.Time else 0

                    for sub in subnodes[start:]:
                        if sub.getKind() == osk.Word:
                            wordcount += 1

                    if subnodes[0].getKind() == osk.Time:
                        session.add(
                            Block(
                                kind=BlockKind.Paragraph,
                                timestamp=evalDateTime(subnodes[0].getStatic().time),
                                wordcount=wordcount,
                                plaintext=ExporterUltraplain.getStr(node),
                                location=get_location(node),
                            ))

                    else:
                        session.add(
                            Block(
                                kind=BlockKind.Paragraph,
                                wordcount=wordcount,
                                plaintext=ExporterUltraplain.getStr(node),
                                location=get_location(node),
                            ))

            case osk.Newline | osk.Space | osk.Empty | osk.TextSeparator | osk.Caption | osk.Tblfm | osk.Include:
                pass

            case osk.Code:
                pass

            case osk.Quote:
                pass

            case osk.Export:
                pass

            case osk.Example:
                pass

            case osk.Table:
                pass

            case _:
                log(CAT).warning(f"Unhandled sql export {node.getKind()} {node.loc.line}")

    aux(node)
    session.commit()
