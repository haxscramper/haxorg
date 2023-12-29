CREATE TABLE IF NOT EXISTS
    FilePath(id INTEGER PRIMARY KEY, file_path STRING, dir INTEGER);

CREATE TABLE IF NOT EXISTS GitCommit(
    id INTEGER PRIMARY KEY,
    author             INTEGER,
    time               INTEGER,
    timezone           INTEGER,
    hash               STRING,
    message            STRING);

CREATE TABLE IF NOT EXISTS FileTrackSection(
    id INTEGER PRIMARY           KEY,
    commit_id INTEGER REFERENCES GitCommit(id),
    path_id INTEGER REFERENCES   FilePath(id),
    track INTEGER REFERENCES     FilePath(id));

CREATE TABLE IF NOT EXISTS
    FileTrack(id INTEGER PRIMARY KEY);

CREATE TABLE IF NOT EXISTS Directory(
    id INTEGER PRIMARY        KEY,
    parent INTEGER REFERENCES Directory(id),
    name                      STRING);

CREATE TABLE IF NOT EXISTS String(id INTEGER PRIMARY KEY, text STRING);

CREATE TABLE IF NOT EXISTS
    Author(id INTEGER PRIMARY KEY, name STRING, email STRING);

CREATE TABLE IF NOT EXISTS LineData(
    id INTEGER PRIMARY           KEY,
    content INTEGER REFERENCES   String(id),
    commit_id INTEGER REFERENCES GitCommit(id));

CREATE TABLE IF NOT EXISTS FileSectionLines(
    section                    INTEGER,
    line_index INTEGER,
    line_id INTEGER REFERENCES LineData(id));
