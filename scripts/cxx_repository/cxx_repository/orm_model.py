from typing import Type, TYPE_CHECKING

from py_scriptutils.sqlalchemy_utils import ForeignId, IdColumn, IntColumn, StrColumn
from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.orm import declarative_base

if TYPE_CHECKING:
    from sqlalchemy.orm.decl_api import DeclarativeMeta
    Base = DeclarativeMeta
else:
    Base = declarative_base()


class FilePath(Base):
    """
    An interned table of file paths. Each unique path string appears only once.
    """
    __tablename__ = "FilePath"
    id = IdColumn()
    file_path = ForeignId("String.id")


class GitCommit(Base):
    """
    One row per git commit discovered during repository traversal.
    """
    __tablename__ = "GitCommit"
    id = IdColumn()
    author = ForeignId("Author.id")
    "Author for the commit"
    time = IntColumn()
    "Posix timestamp for the commit"
    timezone = IntColumn()
    "Timezone offset; minutes from UTC"
    hash = StrColumn()
    "Full git SHA for the commit"
    message = StrColumn()
    "Full text of the git commit message"


class GitCommitActions(Base):
    "One row per file-level action within a commit (a commit touching N files produces N rows)."
    __tablename__ = "GitCommitActions"
    id = IdColumn()
    commit_id = ForeignId("GitCommit.id", nullable=False)
    kind = IntColumn()
    "Integer enum: 0=Modify, 1=Delete, 2=Rename, 3=Add (from `ir::Commit::ActionKind`)"
    track = ForeignId("FileTrack.id")
    "the logical file identity, which file did this commit interact with"
    old_path = ForeignId("FilePath.id")
    "path before a rename; NULL for non-renames"
    new_path = ForeignId("FilePath.id")
    "path after a rename; NULL for non-renames"
    file = ForeignId("FilePath.id")
    "path for non-rename actions; NULL for renames"
    added = IntColumn()
    "Number of lines added in this action; only set when kind=Modify"
    removed = IntColumn()
    "Number of lines removed in this action; only set when kind=Modify"


class FileTrackSection(Base):
    """
    A snapshot of a tracked file's content as it existed at a specific commit. A single FileTrack has one FileTrackSection per commit that touched it.
    """
    __tablename__ = "FileTrackSection"
    id = IdColumn()
    commit_id = ForeignId("GitCommit.id")
    "the commit in which this snapshot was recorded"
    path_id = ForeignId("FilePath.id")
    "the file's path at the time of this snapshot"
    track = ForeignId("FilePath.id")
    "the logical file this snapshot belongs to"


class FileTrack(Base):
    """
    A logical identity for a file across its entire history, surviving renames. Contains only an id; all historical snapshots are in FileTrackSection.
    """
    __tablename__ = "FileTrack"
    id = IdColumn()


class Directory(Base):
    __tablename__ = "Directory"
    id = IdColumn()
    parent = ForeignId("Directory.id")
    name = StrColumn()


class GitString(Base):
    """
    A global interned string pool shared by file paths, line content, and other text values.
    """
    __tablename__ = "String"
    id = IdColumn()
    text = StrColumn()


class Author(Base):
    """
    Interned, deduplicated author identities extracted from git commit signatures.
    """
    __tablename__ = "Author"
    id = IdColumn()
    name = StrColumn()
    "Author display name (from git_signature::name)"
    email = StrColumn()
    "Author email (from git_signature::email)"


class LineData(Base):
    """
    An interned, deduplicated record of a unique (content, commit) pair. The same line text appearing in two different commits produces two LineData rows.
    """
    __tablename__ = "LineData"
    id = IdColumn()
    content = ForeignId("String.id")
    "the text of the line"
    commit_id = ForeignId("GitCommit.id")
    "the commit that first introduced this line"


class FileSectionLines(Base):
    __tablename__ = "FileSectionLines"
    id = IdColumn()
    section = ForeignId("FileTrackSection.id", nullable=False)
    line_index = IntColumn()
    line_id = ForeignId("LineData.id")


# ORM Model for ViewJoinedFileSectionLines
class ViewJoinedFileSectionLines(Base):
    """
    A convenience view that resolves the FileSectionLines join table into readable columns, joining through LineData and String to get the text, and joining FileTrackSection to get both the line's originating commit and the section's commit.
    """
    __tablename__ = "ViewJoinedFileSectionLines"
    id = IdColumn()
    section_id = IntColumn()  # Assuming this can uniquely identify rows
    "The FileTrackSection.id this line belongs to"
    line_index = IntColumn()
    "0-based position of the line within the section"
    text = StrColumn()
    "Resolved text content of the line (from String.text)"
    line_commit = IntColumn()
    "GitCommit.id of the commit that introduced this line"
    section_commit = IntColumn()
    "GitCommit.id of the commit that created this section snapshot"


# ORM Model for ViewFullFileSectionLines
class ViewFullFileSectionLines(Base):
    """
    Extends ViewJoinedFileSectionLines by resolving the two commit IDs into their human-readable messages and timestamps.
    """
    __tablename__ = "ViewFullFileSectionLines"
    text = StrColumn()
    id = IdColumn()
    section_id = IntColumn()  # Assuming this can uniquely identify rows
    line_commit_message = StrColumn()
    "Commit message of the commit that introduced this line"
    line_commit_time = IntColumn()
    "POSIX timestamp of the commit that introduced this line"
    section_commit_message = StrColumn()
    "Commit message of the commit that created this section snapshot"
    section_commit_time = IntColumn()
    "POSIX timestamp of the commit that created this section snapshot"
