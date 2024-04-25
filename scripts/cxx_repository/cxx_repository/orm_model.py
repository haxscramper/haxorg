from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.orm import declarative_base
from py_scriptutils.sqlalchemy_utils import IdColumn, ForeignId, IntColumn, StrColumn

Base = declarative_base()





# Table Definitions
class FilePath(Base):
    __tablename__ = "FilePath"
    id = IdColumn()
    file_path = StrColumn()


class GitCommit(Base):
    __tablename__ = "GitCommit"
    id = IdColumn()
    author = ForeignId("Author.id")
    time = IntColumn()
    timezone = IntColumn()
    hash = StrColumn()
    message = StrColumn()


class GitCommitActions(Base):
    __tablename__ = "GitCommitActions"
    id = IdColumn()
    commit_id = ForeignId("GitCommit.id", nullable=False)
    kind = IntColumn()
    track = ForeignId("FileTrack.id")
    old_path = ForeignId("FilePath.id")
    new_path = ForeignId("FilePath.id")
    file = ForeignId("FilePath.id")
    added = IntColumn()
    removed = IntColumn()


class FileTrackSection(Base):
    __tablename__ = "FileTrackSection"
    id = IdColumn()
    commit_id = ForeignId("GitCommit.id")
    path_id = ForeignId("FilePath.id")
    track = ForeignId("FilePath.id")


class FileTrack(Base):
    __tablename__ = "FileTrack"
    id = IdColumn()


class Directory(Base):
    __tablename__ = "Directory"
    id = IdColumn()
    parent = ForeignId("Directory.id")
    name = StrColumn()


class GitString(Base):
    __tablename__ = "String"
    id = IdColumn()
    text = StrColumn()


class Author(Base):
    __tablename__ = "Author"
    id = IdColumn()
    name = StrColumn()
    email = StrColumn()


class LineData(Base):
    __tablename__ = "LineData"
    id = IdColumn()
    content = ForeignId("String.id")
    commit_id = ForeignId("GitCommit.id")


class FileSectionLines(Base):
    __tablename__ = "FileSectionLines"
    id = IdColumn()
    section = ForeignId("FileTrackSection.id", nullable=False)
    line_index = IntColumn()
    line_id = ForeignId("LineData.id")


# ORM Model for ViewJoinedFileSectionLines
class ViewJoinedFileSectionLines(Base):
    __tablename__ = "ViewJoinedFileSectionLines"
    id = IdColumn()
    section_id = IntColumn()  # Assuming this can uniquely identify rows
    line_index = IntColumn()
    text = StrColumn()
    line_commit = IntColumn()
    section_commit = IntColumn()


# ORM Model for ViewFullFileSectionLines
class ViewFullFileSectionLines(Base):
    __tablename__ = "ViewFullFileSectionLines"
    text = StrColumn()
    id = IdColumn()
    section_id = IntColumn()  # Assuming this can uniquely identify rows
    line_commit_message = StrColumn()
    line_commit_time = IntColumn()
    section_commit_message = StrColumn()
    section_commit_time = IntColumn()
