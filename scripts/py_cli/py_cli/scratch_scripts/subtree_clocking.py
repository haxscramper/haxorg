#!/usr/bin/env python

import pandas as pd
from py_cli.haxorg_cli import *
from beartype import beartype
from beartype.typing import List, Tuple
from py_scriptutils.script_logging import log
from datetime import datetime, timedelta
from py_exporters.export_ultraplain import ExporterUltraplain
import itertools
import functools
import statistics
from py_haxorg.pyhaxorg_utils import evalDateTime, getFlatTags

CAT = __name__


class SubtreeInfo(BaseModel):
    clock_count: int
    total_clock: Optional[timedelta] = Field(
        default=None, description="Total number the task has been clocked")

    average_clock_restart: Optional[timedelta] = Field(
        default=None,
        description="Average time between the start of each subsequent clock record")

    first_clock_start: Optional[datetime] = Field(
        default=None, description="Start time of the first clock in logbook")

    last_clock_end: Optional[datetime] = Field(
        default=None, description="End time of the last completed clock in logbook")

    title: str = Field(description="Plaintext title of the subtree")

    tags: List[str] = Field(default_factory=list,
                            description="List of tags associated with subtree")


class ClockTimeAnalysisOptions(BaseModel):
    infile: List[Path]
    outfile: Path
    cachedir: Optional[Path] = None


def analysis_options(f):
    return apply_options(f, options_from_model(ClockTimeAnalysisOptions))


@beartype
def getSubtreeInfo(node: org.Org) -> List[SubtreeInfo]:
    result = []

    if isinstance(node, org.Subtree):
        clocks: List[Tuple[datetime, datetime]] = []
        time: org.SubtreePeriod
        for time in node.getTimePeriods(
                org.IntSetOfSubtreePeriodKind([org.SubtreePeriodKind.Clocked])):
            if time.to and time.from_:
                clocks.append((
                    evalDateTime(time.from_.getStatic().time),
                    evalDateTime(time.to.getStatic().time),
                ))

        # log(CAT).info(org.treeRepr(node))

        info = SubtreeInfo(
            title=ExporterUltraplain.getStr(node.title),
            clock_count=len(clocks),
            tags=itertools.chain(
                *[["##".join(tag) for tag in getFlatTags(it)] for it in node.tags]),
        )

        if clocks:
            info.first_clock_start = clocks[0][0]
            info.last_clock_end = clocks[-1][1]

            if 1 < len(clocks):
                info.average_clock_restart = timedelta(seconds=statistics.mean(
                    map(
                        lambda it: (it[1] - it[0]).total_seconds(),
                        itertools.pairwise(map(
                            lambda it: it[0],
                            clocks,
                        )),
                    )))

            info.total_clock = functools.reduce(
                lambda delta, clock: delta + clock[1] - clock[0],
                clocks,
                timedelta(),
            )

        result.append(info)

    for sub in node:
        result += getSubtreeInfo(sub)

    return result


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@analysis_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", ClockTimeAnalysisOptions, config=config, kwargs=kwargs)
    opts: ClockTimeAnalysisOptions = ctx.obj["root"]
    subtrees: List[SubtreeInfo] = []
    for file in opts.infile:
        log(CAT).info(file)
        subtrees += getSubtreeInfo(parseCachedFile(file, opts.cachedir))

    df = pd.DataFrame([model.model_dump() for model in subtrees])
    df['tags'] = df['tags'].apply(lambda x: ','.join(x))

    def to_seconds(it: Optional[timedelta | datetime]):
        if not it or pd.isna(it):
            return None

        elif isinstance(it, timedelta):
            return it.total_seconds()

        else:
            return it.timestamp()

    df["total_clock"] = df["total_clock"].apply(to_seconds)
    df["average_clock_restart"] = df["average_clock_restart"].apply(to_seconds)
    df["first_clock_start"] = df["first_clock_start"].apply(to_seconds)
    df["last_clock_end"] = df["last_clock_end"].apply(to_seconds)

    df.to_csv(opts.outfile)


if __name__ == "__main__":
    cli()
