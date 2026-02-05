from datetime import datetime
import enum

from beartype import beartype
from beartype.typing import List, Optional, Type
from py_exporters.export_ultraplain import ExporterUltraplain
from py_haxorg.pyhaxorg_utils import (
    evalDateTime,
    formatHashTag,
    getCreationTime,
    getSubtreeTime,
)
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.script_logging import log
from py_scriptutils.sqlalchemy_utils import (
    DateTimeColumn,
    ForeignId,
    IdColumn,
    IntColumn,
    StrColumn,
)
from sqlalchemy import Boolean, Column, Engine, Enum
from sqlalchemy.orm import declarative_base, sessionmaker

Base: Type = declarative_base()


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
    location = ForeignId(name="Location.id", nullable=True)
    wordcount = IntColumn(nullable=True)


class BlockKind(enum.Enum):
    Paragraph = 1
    Src = 2
    Example = 3
    Quote = 4


class Block(Base):
    __tablename__ = "Block"
    id = IdColumn()
    kind = Column(Enum(BlockKind))  # type: ignore[var-annotated]
    plaintext = StrColumn(nullable=True)
    timestamp = DateTimeColumn(nullable=True)
    parent = ForeignId(name="Block.id", nullable=True)
    wordcount = IntColumn(nullable=True)
    location = ForeignId(name="Location.id", nullable=True)


class ValueEditOperation(enum.Enum):
    Added = 1
    Removed = 2
    Changed = 3


class PriorityModified(Base):
    __tablename__ = "PriorityModified"
    id = IdColumn()
    subtree = ForeignId(name="Subtree.id", nullable=False)
    kind = Column(Enum(ValueEditOperation))  # type: ignore[var-annotated]
    old_priority = StrColumn(nullable=True)
    new_priority = StrColumn(nullable=True)
    timestamp = DateTimeColumn(nullable=True)
    description = StrColumn(nullable=True)


class StateModified(Base):
    __tablename__ = "StateModified"
    id = IdColumn()
    subtree = ForeignId(name="Subtree.id", nullable=False)
    old_state = StrColumn(nullable=True)
    new_state = StrColumn(nullable=True)
    kind = Column(Enum(ValueEditOperation))  # type: ignore[var-annotated]
    timestamp = DateTimeColumn(nullable=True)
    description = StrColumn(nullable=True)


class TagModified(Base):
    __tablename__ = "TagModified"
    id = IdColumn()
    subtree = ForeignId(name="Subtree.id", nullable=False)
    tag = StrColumn()
    timestamp = DateTimeColumn(nullable=True)
    added = Column(Boolean)
    description = StrColumn(nullable=True)


class ClockModified(Base):
    __tablename__ = "ClockModified"
    id = IdColumn()
    subtree = ForeignId(name="Subtree.id")
    from_ = DateTimeColumn()
    to = DateTimeColumn(nullable=True)


class NoteModified(Base):
    __tablename__ = "NoteModified"
    id = IdColumn()
    subtree = ForeignId(name="Subtree.id")
    plaintext = StrColumn()
    timestamp = DateTimeColumn()


class RefileModified(Base):
    __tablename__ = "RefileModified"
    id = IdColumn()


CAT = "haxorg.export.sqlite"

subtree_count = 0


@beartype
def registerDocument(node: org.Org, engine: Engine, file: str) -> None:
    Base.metadata.bind = engine
    sesion_maker = sessionmaker(bind=engine)
    session = sesion_maker()
    osk = org.OrgSemKind

    file_record = File(path=file)
    session.add(file_record)
    session.commit()

    counter = 0

    def get_location(node: org.Org) -> Optional[int]:
        if not node.loc:
            return None

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
    def aux_subtree_log(node: org.SubtreeLog, subtree_id: int) -> None:
        match node.head.getLogKind():
            case org.SubtreeLogHeadKind.Priority:
                priority: org.SubtreeLogHeadPriority = node.head.getPriority()
                time = evalDateTime(priority.on)
                match priority.action:
                    case org.SubtreeLogHeadPriorityAction.Added:
                        session.add(
                            PriorityModified(
                                kind=ValueEditOperation.Added,
                                new_priority=priority.newPriority,
                                timestamp=time,
                                subtree=subtree_id,
                                description=node.desc and
                                ExporterUltraplain.getStr(node.desc),
                            ))

                    case org.SubtreeLogHeadPriorityAction.Removed:
                        session.add(
                            PriorityModified(
                                kind=ValueEditOperation.Removed,
                                new_priority=priority.oldPriority,
                                timestamp=time,
                                subtree=subtree_id,
                                description=node.desc and
                                ExporterUltraplain.getStr(node.desc),
                            ))

                    case org.SubtreeLogHeadPriorityAction.Changed:
                        session.add(
                            PriorityModified(
                                kind=ValueEditOperation.Changed,
                                new_priority=priority.newPriority,
                                old_priority=priority.oldPriority,
                                timestamp=time,
                                subtree=subtree_id,
                                description=node.desc and
                                ExporterUltraplain.getStr(node.desc),
                            ))

            case org.SubtreeLogHeadKind.State:
                state = node.head.getState()
                change = None
                match (bool(state.from_), bool(state.to)):
                    case (True, True):
                        change = ValueEditOperation.Changed

                    case (False, True):
                        change = ValueEditOperation.Added

                    case (True, False):
                        change = ValueEditOperation.Removed

                session.add(
                    StateModified(
                        subtree=subtree_id,
                        old_state=state.from_,
                        new_state=state.to,
                        kind=change,
                        timestamp=evalDateTime(state.on),
                        description=node.desc and ExporterUltraplain.getStr(node.desc),
                    ))

            case org.SubtreeLogHeadKind.Tag:
                tag: org.SubtreeLogHeadTag = node.head.getTag()
                session.add(
                    TagModified(
                        subtree=subtree_id,
                        added=tag.added,
                        timestamp=evalDateTime(tag.on),
                        tag=formatHashTag(tag.tag),
                        description=node.desc and ExporterUltraplain.getStr(node.desc),
                    ))

            case org.SubtreeLogHeadKind.Clock:
                clock: org.SubtreeLogHeadClock = node.head.getClock()
                session.add(
                    ClockModified(
                        subtree=subtree_id,
                        from_=evalDateTime(clock.from_),
                        to=evalDateTime(clock.to) if clock.to else None,
                    ))

            case org.SubtreeLogHeadKind.Note:
                note: org.SubtreeLogHeadNote = node.head.getNote()
                session.add(
                    NoteModified(
                        subtree=subtree_id,
                        plaintext=ExporterUltraplain.getStr(node.desc)
                        if node.desc else "",
                    ))

    @beartype
    def aux(node: org.Org, parent: Optional[int] = None) -> None:
        global subtree_count
        match node:
            case org.Subtree():

                def getNestedWordcount(node: org.Org) -> int:
                    if not node or getCreationTime(node) is not None:
                        return 0

                    else:
                        result = 0
                        match node:
                            case org.Word() | org.BigIdent() | org.RawText(
                            ) | org.HashTag() | org.AtMention():
                                result += 1

                            case _:
                                for sub in node:
                                    result += getNestedWordcount(sub)

                        return result

                count = 0
                for sub in node:
                    count += getNestedWordcount(sub)

                # log(CAT).info("{} {} {}:{}".format(
                #     ExporterUltraplain.getStr(node.title),
                #     count,
                #     node.loc.line if node.loc else -1,
                #     node.loc.column if node.loc else -1,
                # ))

                session.add(
                    Subtree(
                        id=subtree_count,
                        parent=parent,
                        created=getCreationTime(node),
                        scheduled=getSubtreeTime(node, org.SubtreePeriodKind.Scheduled),
                        level=node.level,
                        plaintext_title=node.getCleanTitle().strip(),
                        location=get_location(node),
                        wordcount=count,
                    ))

                subtree_count += 1

                for item in node.logbook:
                    aux_subtree_log(item, id(node))

                for sub in node:
                    aux(sub, parent=id(node))

            case org.File():
                for sub in node:
                    aux(sub, parent=id(node))

            case org.Document():
                session.add(Document(id=id(node)))
                for sub in node:
                    aux(sub, parent=id(node))

            case org.List() | org.ListItem():
                for sub in node:
                    aux(sub)

            case org.Paragraph():
                subnodes: List[org.Org] = [n for n in node]
                wordcount = 0
                if 0 < len(subnodes):
                    for sub in subnodes:
                        if sub.getKind() == osk.Word:
                            wordcount += 1

                    session.add(
                        Block(
                            kind=BlockKind.Paragraph,
                            wordcount=wordcount,
                            timestamp=getCreationTime(node),
                            plaintext=ExporterUltraplain.getStr(node).strip(),
                            location=get_location(node),
                        ))

            case osk.Newline | osk.Space | osk.Empty | osk.TextSeparator | osk.CmdCaption | osk.CmdTblfm | osk.CmdInclude:
                pass

            case osk.BlockCode:
                pass

            case osk.BlockQuote:
                pass

            case osk.BlockExport:
                pass

            case osk.BlockExample:
                pass

            case osk.Table:
                pass

    aux(node)
    session.commit()
