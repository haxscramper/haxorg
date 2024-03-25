#!/usr/bin/env python

import pandas as pd
from py_cli.haxorg_cli import *
from beartype import beartype
from beartype.typing import List
from collections import defaultdict
from py_haxorg.pyhaxorg_utils import getFlatTags
from py_scriptutils.sqlalchemy_utils import (
    IdColumn,
    IntColumn,
    StrColumn,
    MillisecondsUnixTimestamp,
    open_sqlite,
)

from sqlalchemy.orm import declarative_base, sessionmaker, Session
from sqlalchemy import Column, select
from datetime import datetime, timedelta
from py_scriptutils.rich_utils import render_rich_pprint
from pydantic import validator, field_validator
from py_haxorg.pyhaxorg_utils import evalDateTime
import re

CAT = Path(__file__).name


class AlXreaderImportOptions(BaseModel):
    infile: Path = Field(description="Alxreader backup DB")
    target: Path = Field(description="File with bookmark collection")
    cachedir: Optional[Path] = None
    import_offset: Optional[timedelta] = Field(
        default=None,
        description=
        "Apply this time offset on all timestamps imported from the sqlite database")

    @field_validator('import_offset', mode="before")
    def parse_timedelta(cls, v):
        log(CAT).info("Importing the time delta")
        if isinstance(v, timedelta):
            return v
        if isinstance(v, str):
            # Example of a simple parser for strings like "1d 2h 3m 4s"
            # You can adjust the regex and conversion logic as needed
            match = re.match(
                r'((?P<days>\d+)d)?\s*((?P<hours>\d+)h)?\s*((?P<minutes>\d+)m)?\s*((?P<seconds>\d+)s)?',
                v)
            if match:
                parts = {
                    key: int(value) for key, value in match.groupdict(default=0).items()
                }
                return timedelta(**parts)
            # Raise an error if the string format is unrecognized
            raise ValueError("Invalid timedelta string format")
        # Optionally handle other input formats here
        raise TypeError("Invalid type for timedelta")

        return v


def analysis_options(f):
    return apply_options(f, options_from_model(AlXreaderImportOptions))


class BookmarkRecord(BaseModel, extra="forbid"):
    book: str
    text: str
    author: str
    dateadd: datetime
    dateedit: datetime
    start: int
    stop: int
    booksize: int
    bookpos: int
    datelast: datetime
    datefirst: datetime


Base = declarative_base()


class Bookmarks(Base):
    __tablename__ = "bookmarks"
    id = IdColumn()
    idbook = IntColumn()
    dateadd = Column(MillisecondsUnixTimestamp)
    dateedit = Column(MillisecondsUnixTimestamp)
    filename = StrColumn()
    cardpath = StrColumn()
    crc = StrColumn()
    start = IntColumn()
    stop = IntColumn()
    name = StrColumn()
    text = StrColumn()
    lowtext = StrColumn()


class Recent(Base):
    __tablename__ = "recent"
    id = IdColumn()
    filename = StrColumn()
    cardpath = StrColumn()
    booksize = IntColumn()
    bookpos = IntColumn()
    filesize = IntColumn()
    datefirst = Column(MillisecondsUnixTimestamp)
    datelast = Column(MillisecondsUnixTimestamp)
    title = StrColumn()
    author = StrColumn()
    series = StrColumn()
    otherdata = StrColumn()


@beartype
def get_subtree_at_path(node: org.Org, path: List[str]) -> Optional[org.Subtree]:
    selector = org.OrgDocumentSelector()
    for idx, title in enumerate(path):
        selector.searchSubtreePlaintextTitle(
            title=title,
            isTarget=idx == len(path) - 1,
            link=selector.linkIndirectSubnode() if idx < len(path) else None,
        )

    matches = selector.getMatches(node)
    if matches:
        return matches[0]

    else:
        return None


@beartype
def new_subtree(title: str, level: int) -> org.Subtree:
    return org.Subtree(
        title=org.Paragraph(subnodes=[org.RawText(text=title)]),
        level=level,
    )


@beartype
def get_bookmarks(session: Session) -> List[BookmarkRecord]:
    result: List[BookmarkRecord] = []

    expr = select(
        Bookmarks.filename,
        Recent.title.label("book"),
        Recent.author,
        Bookmarks.dateadd,
        Bookmarks.dateedit,
        Bookmarks.text,
        Bookmarks.start,
        Bookmarks.stop,
        Recent.booksize,
        Recent.datefirst,
        Recent.datelast,
        Recent.bookpos,
    ).join(
        Recent,
        Recent.filename == Bookmarks.filename,
    )

    for item in session.execute(expr).mappings():
        result.append(
            BookmarkRecord.model_validate(
                {k: item[k] for k in BookmarkRecord.model_fields}))

    return result


@beartype
def format_time(time: datetime) -> str:
    return "[" + time.strftime('%Y-%m-%d %H:%M:%S') + "]"


@beartype
def get_book_tree_name(rec: BookmarkRecord) -> str:
    return "\"{}\" by \"{}\"".format(
        rec.book.replace("\"", ""),
        rec.author,
    )


@beartype
def get_bookmark_tree_name(rec: BookmarkRecord) -> str:
    return "{} {:06.3f}/{:06.3f}".format(
        format_time(rec.dateadd),
        rec.start * 1.0 / rec.booksize * 100,
        rec.stop * 1.0 / rec.booksize * 100,
    )


@beartype
def insert_new_bookmark(tree: org.Org, mark: BookmarkRecord):

    def get_bookmark_entry() -> Optional[org.Subtree]:
        return get_subtree_at_path(tree, [
            get_book_tree_name(mark),
            get_bookmark_tree_name(mark),
        ])

    def get_book_entry() -> Optional[org.Subtree]:
        return get_subtree_at_path(tree, [
            get_book_tree_name(mark),
        ])

    book = get_book_entry()

    name = f"[red]\"{mark.book}\"[/red] by [yellow]\"{mark.author}\"[/yellow]"

    if not book:
        log(CAT).info(f"Add book for {name}")
        tree.subnodes.append(new_subtree(
            title=get_book_tree_name(mark),
            level=1,
        ))

    book = get_book_entry()
    assert book

    book.setPropertyStrValue(kind="book_last_read", value=format_time(mark.datelast))
    book.setPropertyStrValue(kind="book_first_read", value=format_time(mark.datefirst))

    item: org.SubtreeLog
    found_last_log = False
    for item in book.logbook:
        if item.getLogKind() == org.SubtreeLogKind.Note and item.getNote().on:
            note_date = evalDateTime(item.getNote().on.getStatic().time)
            second_precision = mark.datelast.replace(microsecond=0)
            if note_date == second_precision:
                found_last_log = True

    if not found_last_log:
        log(CAT).info(f"New read timestamp {name}")
        book.logbook.append(
            org.SubtreeLog(log=org.SubtreeLogNote(
                on=org.newSemTimeStatic(
                    org.UserTimeBreakdown(
                        year=mark.datelast.year,
                        month=mark.datelast.month,
                        day=mark.datelast.day,
                        hour=mark.datelast.hour,
                        minute=mark.datelast.minute,
                        second=mark.datelast.second,
                    ),
                    isActive=False,
                ),
                desc=org.StmtList(subnodes=[
                    org.RawText(text=f"Reading progress {mark.bookpos}/{mark.booksize}")
                ]),
            )))

    bookmark = get_bookmark_entry()

    if not bookmark:
        book.subnodes.append(new_subtree(
            title=get_bookmark_tree_name(mark),
            level=2,
        ))

        bookmark = get_bookmark_entry()
        assert bookmark

        log(CAT).info(f"Add bookmark for {name}")

        bookmark_entry = get_bookmark_entry()
        bookmark_entry.setPropertyStrValue(kind="bookmark_start", value=str(mark.start))
        bookmark_entry.setPropertyStrValue(kind="bookmark_stop", value=str(mark.stop))
        bookmark_entry.setPropertyStrValue(kind="bookmark_booksize",
                                           value=str(mark.booksize))

        bookmark_entry.setPropertyStrValue(kind="bookmark_date",
                                           value=format_time(mark.dateadd))

        bookmark.subnodes.append(org.Newline(text="\n\n"))
        bookmark.subnodes.append(
            org.Quote(subnodes=[org.RawText(text=mark.text.replace("\x0D", " "))]))
        bookmark.subnodes.append(org.Newline(text="\n\n"))


def impl(opts: AlXreaderImportOptions, bookmarks: List[BookmarkRecord]):
    if not opts.target.exists():
        opts.target.write_text("")

    node = parseCachedFile(opts.target, opts.cachedir)

    for it in bookmarks:
        insert_new_bookmark(node, it)

    opts.target.write_text(org.formatToString(node))


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@analysis_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", AlXreaderImportOptions, config=config, kwargs=kwargs)
    opts: AlXreaderImportOptions = ctx.obj["root"]

    engine = open_sqlite(opts.infile)
    session = sessionmaker()(bind=engine)
    if opts.import_offset:
        log(CAT).info(f"Import time offset {opts.import_offset}")
        bookmarks = [
            it.model_copy(update=dict(
                dateadd=it.dateadd + opts.import_offset,
                dateedit=opts.import_offset,
            )) for it in get_bookmarks(session)
        ]

    else:
        bookmarks = get_bookmarks(session)

    impl(opts, bookmarks)
    log(CAT).info("Import done")


if __name__ == "__main__":
    cli()
