import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.sqlalchemy_utils import IdColumn, ForeignId, IntColumn, StrColumn, DateTimeColumn
from sqlalchemy.orm import declarative_base, sessionmaker
from sqlalchemy import DateTime, Column, Enum, Engine, Boolean
import enum
from py_scriptutils.script_logging import log
from beartype.typing import List, Optional
from beartype import beartype
from py_haxorg.pyhaxorg_utils import evalDateTime
from py_exporters.export_ultraplain import ExporterUltraplain
from datetime import datetime

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


class ValueEditOperation(enum.Enum):
    Added = 1
    Removed = 2
    Changed = 3


class PriorityModified(Base):
    __tablename__ = "PriorityModified"
    id = IdColumn()
    subtree = ForeignId(name="Subtree.id", nullable=False)
    kind = Column(Enum(ValueEditOperation))
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
    kind = Column(Enum(ValueEditOperation))
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
    def aux_subtree_log(node: org.SubtreeLog, subtree_id: int):
        match node.getLogKind():
            case org.SubtreeLogKind.Priority:
                priority: org.SubtreeLogPriority = node.getPriority()
                time = evalDateTime(priority.on.getStatic().time)
                match priority.action:
                    case org.SubtreeLogPriorityAction.Added:
                        session.add(
                            PriorityModified(
                                kind=ValueEditOperation.Added,
                                new_priority=priority.newPriority,
                                timestamp=time,
                                subtree=subtree_id,
                                description=priority.desc and
                                ExporterUltraplain.getStr(priority.desc),
                            ))

                    case org.SubtreeLogPriorityAction.Removed:
                        session.add(
                            PriorityModified(
                                kind=ValueEditOperation.Removed,
                                new_priority=priority.oldPriority,
                                timestamp=time,
                                subtree=subtree_id,
                                description=priority.desc and
                                ExporterUltraplain.getStr(priority.desc),
                            ))

                    case org.SubtreeLogPriorityAction.Changed:
                        session.add(
                            PriorityModified(
                                kind=ValueEditOperation.Changed,
                                new_priority=priority.newPriority,
                                old_priority=priority.oldPriority,
                                timestamp=time,
                                subtree=subtree_id,
                                description=priority.desc and
                                ExporterUltraplain.getStr(priority.desc),
                            ))

            case org.SubtreeLogKind.State:
                state = node.getState()
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
                        timestamp=evalDateTime(state.on.getStatic().time),
                        description=state.desc and ExporterUltraplain.getStr(state.desc),
                    ))

            case org.SubtreeLogKind.Tag:
                tag: org.SubtreeLogTag = node.getTag()
                session.add(
                    TagModified(
                        subtree=subtree_id,
                        added=tag.added,
                        timestamp=evalDateTime(tag.on.getStatic().time),
                        tag=ExporterUltraplain.getStr(tag.tag),
                        description=tag.desc and ExporterUltraplain.getStr(tag.desc),
                    ))

            case org.SubtreeLogKind.Clock:
                clock: org.SubtreeLogClock = node.getClock()
                session.add(
                    ClockModified(
                        subtree=subtree_id,
                        from_=evalDateTime(clock.from_.getStatic().time),
                        to=evalDateTime(clock.to.getStatic().time) if clock.to else None,
                    ))

            case org.SubtreeLogKind.Note:
                note: org.SubtreeLogNote = node.getNote()
                session.add(
                    NoteModified(
                        subtree=subtree_id,
                        plaintext=ExporterUltraplain.getStr(note.desc) if note.desc else "",
                    ))

    @beartype
    def aux(node: org.Org, parent: Optional[int] = None):
        global subtree_count
        match node:
            case org.Subtree():
                def getTime(kind: org.SubtreePeriodKind) -> Optional[datetime]:
                    result: Optional[datetime] = None
                    time: org.SubtreePeriod
                    for time in node.getTimePeriods(
                            org.IntSetOfSubtreePeriodKindIntVec([kind])):


                        # if time.kind == org.SubtreePeriodKind.
                        # log(CAT).info(org.treeRepr(node.title))
                        if time.getTime().getTimeKind() == org.TimeTimeKind.Static:
                            result = evalDateTime(time.getTime().getStatic().time)


                    return result
                
                session.add(
                    Subtree(
                        id=subtree_count,
                        parent=parent,
                        created=getTime(org.SubtreePeriodKind.Created),
                        scheduled=getTime(org.SubtreePeriodKind.Scheduled),
                        level=node.level,
                        plaintext_title=ExporterUltraplain.getStr(node.title),
                        location=get_location(node),
                    ))
                
                subtree_count += 1

                for item in node.logbook:
                    aux_subtree_log(item, id(node))

                for sub in node:
                    aux(sub, parent=id(node))

            case org.Document():
                session.add(Document(id=id(node)))
                for sub in node:
                    aux(sub, parent=id(node))

            case org.List() | org.ListItem():
                for sub in node:
                    aux(sub)

            case org.Paragraph() | org.AnnotatedParagraph():
                subnodes: List[org.Org] = [n for n in node]
                wordcount = 0
                if 0 < len(subnodes):
                    for sub in subnodes:
                        if sub.getKind() == osk.Word:
                            wordcount += 1

                    timestamp: Optional[datetime] = None
                    if isinstance(node, org.AnnotatedParagraph):
                        if node.getAnnotationKind(
                        ) == org.AnnotatedParagraphAnnotationKind.Timestamp:
                            timestamp = evalDateTime(
                                node.getTimestamp().time.getStatic().time)

                    session.add(
                        Block(
                            kind=BlockKind.Paragraph,
                            wordcount=wordcount,
                            timestamp=timestamp,
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


    aux(node)
    session.commit()
