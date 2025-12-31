from sqlalchemy import Engine
from cxx_repository.orm_model import Base, ViewFullFileSectionLines
from sqlalchemy.orm import sessionmaker
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from py_scriptutils.tracer import TraceCollector
import matplotlib.dates as mdates
from datetime import datetime


def format_epoch_to_date(epoch: float, date_format: str = '%Y-%m-%d') -> str:
    return datetime.utcfromtimestamp(epoch).strftime(date_format)


def run_for(engine: Engine) -> None:
    trace = TraceCollector()

    Base.metadata.bind = engine  # type: ignore[attr-defined]
    sesion_maker = sessionmaker(bind=engine)
    session = sesion_maker()

    # ORM-based SELECT query
    query = session.query(ViewFullFileSectionLines.line_commit_time,
                          ViewFullFileSectionLines.section_commit_time).limit(5000)

    line_time = "line_commit_time"
    sect_time = "section_commit_time"

    # Converting results to a DataFrame
    print(query.statement)
    df = pd.read_sql_query(query.statement,
                           engine,
                           dtype={
                               line_time: "int32",
                               sect_time: "int32"
                           })

    # Close the session
    session.close()

    # Constants for time resolution
    LINE_TIME_RESOLUTION = 10
    SECTION_TIME_RESOLUTION = 40

    # Find min/max
    min_line_time = df[line_time].min()
    max_line_time = df[line_time].max()
    min_section_time = df[sect_time].min()
    max_section_time = df[sect_time].max()

    # Create buckets
    line_time_bins = np.linspace(min_line_time, max_line_time, LINE_TIME_RESOLUTION)
    section_time_bins = np.linspace(min_section_time, max_section_time,
                                    SECTION_TIME_RESOLUTION)

    # Assign to buckets
    df['line_time_bucket'] = pd.cut(
        df[line_time],
        bins=line_time_bins,
        ordered=False,
        labels=[
            f"[{idx}] {format_epoch_to_date(left)} to {format_epoch_to_date(right)}"
            for idx, (left,
                      right) in enumerate(zip(line_time_bins[:-1], line_time_bins[1:]))
        ])
    df['section_time_bucket'] = pd.cut(df[sect_time], bins=section_time_bins)

    # Group and count
    grouped = df.groupby(
        'section_time_bucket')['line_time_bucket'].value_counts().unstack(fill_value=0)

    # Plot
    fig, ax = plt.subplots(figsize=(10, 6))
    grouped.plot(kind='bar', stacked=True, ax=ax)

    # Title and labels
    ax.set_title('Line Time Buckets within Each Section Time Bucket')
    ax.set_xlabel('Section Time Buckets')
    ax.set_ylabel('Count of Line Time Buckets')

    # Format the x-axis as date
    formatter: mdates.DateFormatter = mdates.DateFormatter('%Y-%m-%d') # type: ignore
    ax.xaxis.set_major_formatter(formatter)  # Adjust the format as needed

    # Rotate x-ticks
    plt.xticks(rotation=45, ha='right')  # Rotate and align right

    # Place the legend outside the plot
    ax.legend(loc='upper left', bbox_to_anchor=(1, 1))

    # Adjust layout
    plt.tight_layout()

    plt.savefig("/tmp/aaa.png")
