from datetime import datetime
import enum

from beartype import beartype
from beartype.typing import List, Optional, Type
from py_haxorg.exporters.export_ultraplain import ExporterUltraplain
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
    """
    nodoc
    """
    __tablename__ = "Document"
    id = IdColumn()  # nodoc


class Location(Base):
    """
    Source code location information
    """
    __tablename__ = "Location"
    id = IdColumn()  # nodoc
    line = IntColumn()  # nodoc
    column = IntColumn()  # nodoc
    file = ForeignId(name="File.id")  # nodoc


class File(Base):
    """
    Parsed org-mode file
    """
    __tablename__ = "File"
    id = IdColumn()  # nodoc
    path = StrColumn()  # nodoc


class Subtree(Base):
    """
    All subtrees in the document
    """
    __tablename__ = "Subtree"
    id = IdColumn()  # nodoc
    plaintext_title = StrColumn()  # nodoc
    level = IntColumn()  # nodoc
    parent = ForeignId(name="Subtree.id", nullable=True)  # nodoc
    created = DateTimeColumn(nullable=True)  # nodoc
    scheduled = DateTimeColumn(nullable=True)  # nodoc
    deadline = DateTimeColumn(nullable=True)  # nodoc
    closed = DateTimeColumn(nullable=True)  # nodoc
    location = ForeignId(name="Location.id", nullable=True)  # nodoc
    wordcount = IntColumn(nullable=True)  # nodoc


class BlockKind(enum.Enum):
    "Type of the org-mode document block"
    Paragraph = 1  # nodoc
    Src = 2  # nodoc
    Example = 3  # nodoc
    Quote = 4  # nodoc


class Block(Base):
    """
    Structural element in the org-mode document
    """
    __tablename__ = "Block"
    id = IdColumn()  # nodoc
    kind = Column(Enum(BlockKind))  # type: ignore[var-annotated], nodoc
    plaintext = StrColumn(nullable=True)  # nodoc
    timestamp = DateTimeColumn(nullable=True)  # nodoc
    parent = ForeignId(name="Block.id", nullable=True)  # nodoc
    wordcount = IntColumn(nullable=True)  # nodoc
    location = ForeignId(name="Location.id", nullable=True)  # nodoc


class ValueEditOperation(enum.Enum):
    """
    Type of change recorded recorded in the subtree logbook drawer
    """
    Added = 1  # nodoc
    Removed = 2  # nodoc
    Changed = 3  # nodoc


class PriorityModified(Base):
    """
    Subtree priority has been modified
    """
    __tablename__ = "PriorityModified"
    id = IdColumn()  # nodoc
    subtree = ForeignId(name="Subtree.id", nullable=False)  # nodoc
    kind = Column(Enum(ValueEditOperation))  # type: ignore[var-annotated], nodoc
    old_priority = StrColumn(nullable=True)  # nodoc
    new_priority = StrColumn(nullable=True)  # nodoc
    timestamp = DateTimeColumn(nullable=True)  # nodoc
    description = StrColumn(nullable=True)  # nodoc


class StateModified(Base):
    """
    Subtree todo state has been modified
    """
    __tablename__ = "StateModified"
    id = IdColumn()  # nodoc
    subtree = ForeignId(name="Subtree.id", nullable=False)  # nodoc
    old_state = StrColumn(nullable=True)  # nodoc
    new_state = StrColumn(nullable=True)  # nodoc
    kind = Column(Enum(ValueEditOperation))  # type: ignore[var-annotated], nodoc
    timestamp = DateTimeColumn(nullable=True)  # nodoc
    description = StrColumn(nullable=True)  # nodoc


class TagModified(Base):
    """
    Subtree title tag has been modified
    """
    __tablename__ = "TagModified"
    id = IdColumn()  # nodoc
    subtree = ForeignId(name="Subtree.id", nullable=False)  # nodoc
    tag = StrColumn()
    """
    Single hash tag with possible multi-branch nesting.
    """
    timestamp = DateTimeColumn(nullable=True)
    """
    When the subtree tag was added
    """
    added = Column(Boolean)
    """
    Whether the subtree tag was added or removed
    """
    description = StrColumn(nullable=True)
    """
    Optional description with the tag modified logbook entry
    """


class ClockModified(Base):
    """
    Subtree was clocked in or out
    """
    __tablename__ = "ClockModified"
    id = IdColumn()  # nodoc
    subtree = ForeignId(name="Subtree.id")  # nodoc
    from_ = DateTimeColumn()  # nodoc
    to = DateTimeColumn(nullable=True)  # nodoc


class NoteModified(Base):
    """
    Added note to the subtree logbook
    """
    __tablename__ = "NoteModified"
    id = IdColumn()  # nodoc
    subtree = ForeignId(name="Subtree.id")  # nodoc
    plaintext = StrColumn()  # nodoc
    timestamp = DateTimeColumn()  # nodoc


class RefileModified(Base):
    """
    Subtree was refiled
    """
    __tablename__ = "RefileModified"
    id = IdColumn()  # nodoc


CAT = "haxorg.export.sqlite"

subtree_count = 0


@beartype
def registerDocument(node: org.Org, engine: Engine, file: str) -> None:
    """
    Recursively register all subtree and block entries from the org-mode document.
    """
    Base.metadata.bind = engine
    sesion_maker = sessionmaker(bind=engine)
    session = sesion_maker()
    osk = org.OrgSemKind

    file_record = File(path=file)
    session.add(file_record)
    session.commit()

    counter = 0

    def get_location(node: org.Org) -> Optional[int]:
        """
        Insert new location entry to the DB and return ID for the
        location.
        """
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
        """
        Process subtree log entry
        """
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
        """
        Recurisvely add all nodes to the db.
        """
        global subtree_count
        match node:
            case org.Subtree():

                def getNestedWordcount(node: org.Org) -> int:
                    """
                    Get number of world-like nodes (words, raw text, hashtag)
                    for the node, stopping recursion at the node with creation
                    time present.
                    """
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

            case org.Newline() | org.Space() | org.Empty() | org.TextSeparator(
            ) | org.CmdCaption() | org.CmdTblfm() | org.CmdInclude():
                pass

            case org.BlockCode():
                pass

            case org.BlockQuote():
                pass

            case org.BlockExport():
                pass

            case org.BlockExample():
                pass

            case org.Table():
                pass

    aux(node)
    session.commit()
