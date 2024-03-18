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
from datetime import datetime
from py_scriptutils.rich_utils import render_rich_pprint

CAT = Path(__file__).name


class AlXreaderImportOptions(BaseModel):
    infile: Path = Field(description="Alxreader backup DB")

    target: Path = Field(description="File with bookmark collection")

    cachedir: Optional[Path] = None


def analysis_options(f):
    return apply_options(f, options_from_model(AlXreaderImportOptions))


class BookmarkRecord(BaseModel, extra="forbid"):
    book: str
    text: str
    dateadd: datetime
    dateedit: datetime


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
def get_bookmarks(session: Session) -> List[BookmarkRecord]:
    result: List[BookmarkRecord] = []

    expr = select(
        Bookmarks.filename,
        Recent.title.label("book"),
        Bookmarks.dateadd,
        Bookmarks.dateedit,
        Bookmarks.text,
    ).join(
        Recent,
        Recent.filename == Bookmarks.filename,
    )

    for item in session.execute(expr).mappings():
        result.append(
            BookmarkRecord.model_validate(
                {k: item[k] for k in BookmarkRecord.model_fields}))

    return result


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

    # node = parseCachedFile(opts., opts.cachedir)
    engine = open_sqlite(opts.infile)
    session = sessionmaker()(bind=engine)
    bookmarks = get_bookmarks(session)

    for it in bookmarks[:5]:
        log(CAT).info("\n" + render_rich_pprint(
            it,
            max_string=80,
        ))


if __name__ == "__main__":
    cli()
