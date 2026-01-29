#!/usr/bin/env python

from datetime import datetime, timedelta

import matplotlib.figure as matplotlib_figure
import matplotlib.pyplot as plt
import pandas as pd
import py_exporters.export_sqlite as sql
from beartype import beartype
from beartype.typing import Any, List, Tuple
from py_cli import haxorg_cli, haxorg_opts
from py_cli.haxorg_cli import *
from py_scriptutils.files import IsNewInput
from py_scriptutils.script_logging import log
from sqlalchemy import Engine, create_engine, literal, select, union_all
from sqlalchemy.orm import sessionmaker
import glom

CAT = "example.activity_analysis"


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

    union_query = union_all(
        select(
            sql.PriorityModified.timestamp.label("timestamp"),
            literal("PriorityModified").label("event"),
            literal(1).label("count"),
        ),
        select(
            sql.StateModified.timestamp,
            literal("StateModified"),
            literal(1).label("count"),
        ),
        select(
            sql.TagModified.timestamp,
            literal("TagModified"),
            literal(1).label("count"),
        ),
        select(
            sql.ClockModified.from_.label("timestamp"),
            literal("ClockModified"),
            literal(1).label("count"),
        ),
        select(
            sql.NoteModified.timestamp,
            literal("NoteModified"),
            literal(1).label("count"),
        ),
        select(
            sql.Block.timestamp,
            literal("Block"),
            literal(1).label("count"),
        ),
        select(
            sql.Subtree.created.label("timestamp"),
            literal("SubtreeCreated"),
            literal(1).label("count"),
        ),
        select(
            sql.Subtree.scheduled,
            literal("SubtreeScheduled"),
            literal(1).label("count"),
        ),
        select(
            sql.Subtree.deadline,
            literal("SubtreeDeadline"),
            literal(1).label("count"),
        ),
        select(
            sql.Subtree.closed,
            literal("SubtreeClosed"),
            literal(1).label("count"),
        ),
        select(
            sql.Subtree.created.label("timestamp"),
            literal("SubtreeWordcount"),
            sql.Subtree.wordcount.label("count"),
        ),
        select(
            sql.Block.timestamp,
            literal("BlockWordcount"),
            sql.Block.wordcount.label("count"),
        ),
    ).alias("union_query")

    query = select(
        union_query.c.timestamp,
        union_query.c.event,
        union_query.c.count,
    ).where(union_query.c.timestamp.is_not(None))

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

    grouped = df.groupby(["bin", "event"])["count"].sum().unstack(fill_value=0)
    grouped.index = pd.to_datetime(grouped.index.map(lambda it: it.left))

    if grouped.empty:
        return None

    # log(CAT).info("\n" + render_rich(dataframe_to_rich_table(grouped.head(20))))
    n_plots = len(grouped.columns)
    fig, axes = plt.subplots(n_plots, 1, sharex=True, figsize=(10, 2 * n_plots))

    if n_plots == 1:
        axes = [axes]

    for ax, column in zip(axes, grouped.columns):
        ax.fill_between(grouped.index, grouped[column], alpha=0.5)
        ax.plot(grouped.index, grouped[column], label=column)
        ax.margins(y=0.1)  # Add some margin to the y-axis for aesthetics
        ax.set_ylabel(column)
        ax.legend(loc="upper left")

    ticklabels = [item.strftime("%Y-%m-%d") for item in grouped.index]
    axes[0].set_xticklabels(ticklabels[::time_tick_skip])
    axes[0].set_xticks(grouped.index[::time_tick_skip])

    for ax in axes:
        ax.xaxis.grid(True)
        ax.yaxis.grid(False)
        ax.grid(color='gray', linestyle='--', linewidth=0.5)

    fig.autofmt_xdate(rotation=45)
    fig.tight_layout()

    session.close()
    return (fig, axes)


@beartype
def activity_analysis(ctx: haxorg_cli.CliRunContext) -> None:
    opts = ctx.opts
    assert opts.generate
    assert opts.generate.activity_analysis
    outdir: Path = glom.glom(opts, "generate.activity_analysis.outdir")
    infile: List[Path] = glom.glom(opts, "generate.activity_analysis.infile")
    sql_db = Path(
        glom.glom(opts,
                  "generate.activity_analysis.db_path",
                  default=outdir.joinpath("db.sqlite")))

    if not outdir.exists():
        outdir.mkdir(parents=True)

    if opts.generate.activity_analysis.force_db or IsNewInput(input_path=infile,
                                                              output_path=[sql_db]):
        nodes: List[Tuple[org.Org, str]] = []
        for file in infile:
            log(CAT).info(file)
            nodes.append((parseCachedFile(ctx, file), file.name))

        if sql_db.exists():
            sql_db.unlink()

        log(CAT).info("Registering DB")
        engine: Engine = create_engine("sqlite:///" + str(sql_db))
        sql.Base.metadata.create_all(engine)
        for node, file_name in nodes:
            sql.registerDocument(node, engine, file_name)

    else:
        engine: Engine = create_engine("sqlite:///" + str(sql_db))  # type: ignore
        log(CAT).info("No DB update needed")

    # log(CAT).info("Plotting data")
    # plot = plot_timestamped_events_with_pandas(
    #     engine,
    #     bin_size=30,
    #     # min_time=datetime(year=2017, month=1, day=1),
    #     figsize=(20, 12),
    #     time_tick_skip=5,
    # )

    # if plot:
    #     fig, ax = plot
    #     fig.savefig(opts.outdir.joinpath("event_distribution.png"))


@click.command("activity_analysis")
@haxorg_cli.get_wrap_options(haxorg_opts.GenerateActivityAnalysisOptions)
@click.pass_context
def activity_analysis_cli(ctx: click.Context, **kwargs: Any) -> None:
    activity_analysis(haxorg_cli.get_run(ctx))
