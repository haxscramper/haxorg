#!/usr/bin/env python

import py_exporters.export_sqlite as sql
from py_cli.haxorg_cli import *
from beartype.typing import List, Tuple, Any
from beartype import beartype
from py_scriptutils.files import IsNewInput
from sqlalchemy import create_engine, Engine
from py_scriptutils.script_logging import log
from datetime import datetime, timedelta
import pandas as pd
import matplotlib.pyplot as plt
from sqlalchemy import select, literal, union_all
from sqlalchemy.orm import sessionmaker
import matplotlib.figure as matplotlib_figure
from py_scriptutils.pandas_utils import dataframe_to_rich_table
from py_scriptutils.sqlalchemy_utils import format_rich_query
from py_scriptutils.rich_utils import render_rich
import matplotlib.dates as mdates
import matplotlib.ticker as mticker

CAT = "example.activity_analysis"


class ActivityAnalysisOptions(BaseModel):
    infile: List[Path]
    outdir: Path
    cachedir: Optional[Path] = None
    force_db: bool = False
    db_path: Optional[Path] = Field(
        default=None,
        description="Path to the generated SQLite DB, defaults to outdir/db.sqlite")


def analysis_options(f):
    return apply_options(f, options_from_model(ActivityAnalysisOptions))


@beartype
def plot_timestamped_events_with_pandas(
    engine: Engine,
    min_time: Optional[datetime] = None,
    max_time: Optional[datetime] = None,
    bin_size: int = 5,
    figsize: Tuple[int, int] = (10, 6),
    time_tick_skip: int = 5,
) -> Optional[Tuple[matplotlib_figure.Figure, Any]]:
    session = sessionmaker(bind=engine)()

    # log(CAT).info(
    #     render_rich(
    #         format_rich_query(engine, select(sql.Block.timestamp, literal("Block")))))

    union_query = union_all(
        select(
            sql.PriorityModified.timestamp.label("timestamp"),
            literal("PriorityModified").label("event"),
        ),
        select(sql.StateModified.timestamp, literal("StateModified")),
        select(sql.TagModified.timestamp, literal("TagModified")),
        select(sql.ClockModified.from_.label("timestamp"), literal("ClockModified")),
        select(sql.NoteModified.timestamp, literal("NoteModified")),
        select(sql.Block.timestamp, literal("Block")),
        select(sql.Subtree.created.label("timestamp"), literal("SubtreeCreated")),
        select(sql.Subtree.scheduled, literal("SubtreeScheduled")),
        select(sql.Subtree.deadline, literal("SubtreeDeadline")),
        select(
            sql.Subtree.closed,
            literal("SubtreeClosed"),
        ),
    ).alias("union_query")

    query = select(union_query.c.timestamp,
                   union_query.c.event).where(union_query.c.timestamp.is_not(None))

    df = pd.read_sql(query, engine)

    if min_time is None or max_time is None:
        min_time = df["timestamp"].min() if min_time is None else min_time
        max_time = df["timestamp"].max() if max_time is None else max_time

    min_time = min_time.replace(hour=0, minute=0, second=0, microsecond=0)
    max_time = (max_time + timedelta(days=1)).replace(
        hour=0,
        minute=0,
        second=0,
        microsecond=0,
    )

    bins = pd.date_range(min_time, max_time, freq=f"{bin_size}D")

    df["timestamp"] = pd.to_datetime(df["timestamp"])
    df = df[(min_time <= df["timestamp"]) & (df["timestamp"] <= max_time)]

    df["bin"] = pd.cut(df["timestamp"], bins=bins, right=False)

    grouped = df.groupby(["bin", "event"]).size().unstack(fill_value=0)

    fig, ax = plt.subplots(figsize=figsize)
    grouped.plot.area(stacked=True, ax=ax)

    ax.set_xlabel("Time")
    ax.set_ylabel("Number of Events")
    ax.xaxis_date()
    ax.legend(loc="upper left", bbox_to_anchor=(1, 1))

    grouped.index = pd.to_datetime(grouped.index.map(lambda it: it.left))
    ticklabels = [""] * len(grouped.index)
    ticklabels[::time_tick_skip] = [
        item.strftime("%Y-%m-%d") for item in grouped.index[::time_tick_skip]
    ]

    ax.xaxis.set_major_formatter(mticker.FixedFormatter(ticklabels))
    ax.grid(True)
    ax.grid(color='gray', linestyle='--', linewidth=0.5)

    fig.autofmt_xdate()
    fig.tight_layout()

    session.close()
    return (fig, ax)


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@analysis_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", ActivityAnalysisOptions, config=config, kwargs=kwargs)
    opts: ActivityAnalysisOptions = ctx.obj["root"]
    sql_db = opts.db_path if opts.db_path else opts.outdir.joinpath("db.sqlite")

    if not opts.outdir.exists():
        opts.outdir.mkdir(parents=True)

    if opts.force_db or IsNewInput(input_path=opts.infile, output_path=[sql_db]):
        nodes: List[Tuple[org.Org, str]] = []
        for file in opts.infile:
            log(CAT).info(file)
            nodes.append((parseCachedFile(file, opts.cachedir), file.name))

        if sql_db.exists():
            sql_db.unlink()

        engine: Engine = create_engine("sqlite:///" + str(sql_db))
        sql.Base.metadata.create_all(engine)
        for node, file in nodes:
            sql.registerDocument(node, engine, file)

    else:
        engine: Engine = create_engine("sqlite:///" + str(sql_db))
        log(CAT).info("No DB update needed")

    log(CAT).info("Plotting data")
    plot = plot_timestamped_events_with_pandas(
        engine,
        bin_size=25,
        min_time=datetime(year=2017, month=1, day=1),
        figsize=(20, 12),
        time_tick_skip=1,
    )

    if plot:
        fig, ax = plot
        fig.savefig(opts.outdir.joinpath("event_distribution.png"))
