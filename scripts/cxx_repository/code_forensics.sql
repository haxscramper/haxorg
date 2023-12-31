CREATE TABLE
    IF NOT EXISTS FilePath (
        id INTEGER PRIMARY KEY,
        file_path STRING,
        dir INTEGER
    );

CREATE TABLE
    IF NOT EXISTS GitCommit (
        id INTEGER PRIMARY KEY,
        author INTEGER,
        time INTEGER,
        timezone INTEGER,
        hash STRING,
        message STRING
    );

CREATE TABLE
    IF NOT EXISTS FileTrackSection (
        id INTEGER PRIMARY KEY,
        commit_id INTEGER REFERENCES GitCommit (id),
        path_id INTEGER REFERENCES FilePath (id),
        track INTEGER REFERENCES FilePath (id)
    );

CREATE TABLE
    IF NOT EXISTS FileTrack (id INTEGER PRIMARY KEY);

CREATE TABLE
    IF NOT EXISTS Directory (
        id INTEGER PRIMARY KEY,
        parent INTEGER REFERENCES Directory (id),
        name STRING
    );

CREATE TABLE
    IF NOT EXISTS String (id INTEGER PRIMARY KEY, text STRING);

CREATE TABLE
    IF NOT EXISTS Author (id INTEGER PRIMARY KEY, name STRING, email STRING);

CREATE TABLE
    IF NOT EXISTS LineData (
        id INTEGER PRIMARY KEY,
        content INTEGER REFERENCES String (id),
        commit_id INTEGER REFERENCES GitCommit (id)
    );

CREATE TABLE
    IF NOT EXISTS FileSectionLines (
        section INTEGER REFERENCES FileTrackSection (id),
        line_index INTEGER,
        line_id INTEGER REFERENCES LineData (id)
    );

CREATE VIEW
    ViewJoinedFileSectionLines AS
SELECT
    FileSectionLines.section as section_id,
    FileSectionLines.line_index,
    String.text,
    GitCommitForLine.id as line_commit,
    GitCommitForSection.id as section_commit
FROM
    FileSectionLines
    JOIN LineData ON FileSectionLines.line_id = LineData.id
    JOIN String ON LineData.content = String.id
    JOIN GitCommit as GitCommitForLine ON LineData.commit_id = GitCommitForLine.id
    JOIN FileTrackSection ON FileSectionLines.section = FileTrackSection.id
    JOIN GitCommit as GitCommitForSection ON FileTrackSection.commit_id = GitCommitForSection.id
    --
;

CREATE VIEW
    ViewFullFileSectionLines AS
SELECT
    text,
    section_id,
    GitLineCommit.message AS line_commit_message,
    GitLineCommit.time AS line_commit_time,
    GitSectionCommit.message AS section_commit_message,
    GitSectionCommit.time AS section_commit_time
FROM
    ViewJoinedFileSectionLines
    JOIN GitCommit AS GitLineCommit ON ViewJoinedFileSectionLines.line_commit = GitLineCommit.id
    JOIN GitCommit AS GitSectionCommit ON ViewJoinedFileSectionLines.section_commit = GitSectionCommit.id
    --
;
