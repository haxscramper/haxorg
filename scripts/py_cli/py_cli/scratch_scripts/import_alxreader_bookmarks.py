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

CAT = Path(__file__).name


class AlXreaderImportOptions(BaseModel):
    infile: Path = Field(description="Alxreader backup DB")
    target: Path = Field(description="File with bookmark collection")
    cachedir: Optional[Path] = None
    import_offset: Optional[timedelta] = Field(
        default=None,
        description=
        "Apply this time offset on all timestamps imported from the sqlite database")


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
    match_order = path[::-1]
    selector = org.OrgDocumentSelector()
    for idx, title in enumerate(match_order):
        selector.searchSubtreePlaintextTitle(
            title=title,
            link=None if idx == len(match_order) - 1 else selector.linkIndirectSubnode(),
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
    return time.strftime('%Y-%m-%d %H:%M:%S')


@beartype
def get_book_tree_name(rec: BookmarkRecord) -> str:
    return "\"{}\" by \"{}\"".format(
        rec.book.replace("\"", ""),
        rec.author,
    )


@beartype
def get_bookmark_tree_name(rec: BookmarkRecord) -> str:
    return "[{}] {:06.3f}/{:06.3f}".format(
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

    if get_bookmark_entry():
        return

    book_entry = get_subtree_at_path(tree, [
        get_book_tree_name(mark),
    ])

    if not book_entry:
        tree.subnodes.append(new_subtree(
            title=get_book_tree_name(mark),
            level=1,
        ))

    book_entry = get_subtree_at_path(tree, [
        get_book_tree_name(mark),
    ])

    assert book_entry

    book_entry.subnodes.append(new_subtree(
        title=get_bookmark_tree_name(mark),
        level=2,
    ))

    bookmark_entry = get_bookmark_entry()
    bookmark_entry.setPropertyStrValue(kind="bookmark_start", value=str(mark.start))
    bookmark_entry.setPropertyStrValue(kind="bookmark_stop", value=str(mark.stop))
    bookmark_entry.setPropertyStrValue(kind="bookmark_booksize", value=str(mark.booksize))


    bookmark_entry.setPropertyStrValue(kind="bookmark_date",
                                       value=f"[{format_time(mark.dateadd)}]")

    book_entry.subnodes.append(org.Newline(text="\n\n"))
    book_entry.subnodes.append(org.Quote(subnodes=[org.RawText(text=mark.text)]))
    book_entry.subnodes.append(org.Newline(text="\n\n"))

    assert book_entry


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
        bookmarks = [
            it.model_copy(update=dict(
                dateadd=it.dateadd + opts.import_offset,
                dateedit=opts.import_offset,
            )) for it in get_bookmarks(session)
        ]

    else:
        bookmarks = get_bookmarks(session)

    impl(opts, bookmarks)


if __name__ == "__main__":
    cli()
