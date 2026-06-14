from datetime import datetime, timedelta, timezone

from beartype.typing import Optional
from cxx_repository.orm_model import (
    Base,
    FileSectionLines,
    FileTrack,
    FileTrackSection,
    GitCommit,
    LineData,
    ViewFullFileSectionLines,
)
import matplotlib.dates as mdates
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from py_scriptutils.tracer import TraceCollector
from pydantic import BaseModel
from sqlalchemy import Engine, func, select
from sqlalchemy.engine import Engine
from sqlalchemy.orm import aliased, sessionmaker


class BurndownConfiguration(BaseModel, extra="forbid"):
    min_date: Optional[datetime] = None
    max_date: Optional[datetime] = None
    sample_period: timedelta = timedelta(days=1)
    "How often the repository state is reconstructed (x-axis resolution)."
    band_period: timedelta = timedelta(days=365)
    "How lines are grouped by introduction time into stacked bands."


def _bucket_start(ts: int, period: timedelta) -> int:
    """Floor a posix timestamp to the start of its band bucket."""
    secs = int(period.total_seconds())
    return (ts // secs) * secs


def run_for(
    engine: Engine, config: BurndownConfiguration = BurndownConfiguration()) -> None:
    Base.metadata.bind = engine  # type: ignore[attr-defined]
    session_maker = sessionmaker(bind=engine)
    session = session_maker()

    # Determine the global time range from commit timestamps.
    bounds = session.execute(select(func.min(GitCommit.time),
                                    func.max(GitCommit.time))).one()
    db_min, db_max = bounds
    if db_min is None:
        return

    min_ts = (int(config.min_date.replace(
        tzinfo=timezone.utc).timestamp()) if config.min_date else db_min)
    max_ts = (int(config.max_date.replace(
        tzinfo=timezone.utc).timestamp()) if config.max_date else db_max)

    sample_secs = int(config.sample_period.total_seconds())
    sample_points = list(range(min_ts, max_ts + 1, sample_secs))

    # Subquery: every section with its commit time and track.
    section_time = (select(
        FileTrackSection.id.label("section_id"),
        FileTrackSection.track.label("track"),
        GitCommit.time.label("section_time"),
    ).join(GitCommit, GitCommit.id == FileTrackSection.commit_id).subquery())

    # Per-section line counts grouped by the birth bucket of each line.
    # line birth time comes from the commit that introduced the LineData.
    line_commit = aliased(GitCommit)
    per_section_band = session.execute(
        select(
            section_time.c.section_id,
            section_time.c.track,
            section_time.c.section_time,
            line_commit.time.label("line_time"),
            func.count(FileSectionLines.id).label("n"),
        ).join(FileSectionLines,
               FileSectionLines.section == section_time.c.section_id).join(
                   LineData, LineData.id == FileSectionLines.line_id).join(
                       line_commit, line_commit.id == LineData.commit_id).group_by(
                           section_time.c.section_id,
                           section_time.c.track,
                           section_time.c.section_time,
                           line_commit.time,
                       )).all()

    # Index section data per track, sorted by section time, so that for a
    # given sample date we can pick the latest applicable snapshot per track.
    # track -> sorted list of (section_time, section_id)
    track_sections: dict[int, list[tuple[int, int]]] = {}
    # section_id -> {band_start_ts: line_count}
    section_bands: dict[int, dict[int, int]] = {}

    for row in per_section_band:
        track_sections.setdefault(row.track, [])
        section_bands.setdefault(row.section_id, {})
        band = _bucket_start(row.line_time, config.band_period)
        section_bands[row.section_id][band] = (
            section_bands[row.section_id].get(band, 0) + row.n)

    # Build the (section_time, section_id) lists once, deduplicated and sorted.
    seen: dict[int, set[int]] = {}
    for row in per_section_band:
        seen.setdefault(row.track, set())
        if row.section_id not in seen[row.track]:
            seen[row.track].add(row.section_id)
            track_sections[row.track].append((row.section_time, row.section_id))
    for track in track_sections:
        track_sections[track].sort()

    all_bands = sorted({b for bands in section_bands.values() for b in bands})

    # For each sample date, reconstruct the live line set: for each track take
    # the latest section with section_time <= sample, accumulate its bands.
    matrix = np.zeros((len(all_bands), len(sample_points)), dtype=np.int64)
    band_index = {b: i for i, b in enumerate(all_bands)}

    for col, sample in enumerate(sample_points):
        for track, sections in track_sections.items():
            chosen: Optional[int] = None
            for sec_time, sec_id in sections:
                if sec_time <= sample:
                    chosen = sec_id
                else:
                    break
            if chosen is None:
                continue
            for band, n in section_bands[chosen].items():
                matrix[band_index[band], col] += n

    # Plot stacked area chart.
    x = [datetime.fromtimestamp(s, tz=timezone.utc) for s in sample_points]
    labels = [
        datetime.fromtimestamp(b, tz=timezone.utc).strftime("%Y-%m") for b in all_bands
    ]

    fig, ax = plt.subplots(figsize=(14, 8))
    ax.stackplot(x, matrix, labels=labels)
    ax.set_xlabel("Repository state at date")
    ax.set_ylabel("Surviving lines")
    ax.set_title("Code burndown by introduction period")
    ax.legend(loc="upper left", fontsize="small", ncol=2)
    fig.autofmt_xdate()
    fig.tight_layout()
    plt.show()

    session.close()
