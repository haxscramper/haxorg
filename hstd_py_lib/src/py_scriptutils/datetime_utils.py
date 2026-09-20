from datetime import datetime

from beartype import beartype


@beartype
def format_iso8601(time: datetime) -> str:
    return time.strftime("%Y-%m-%dT%H:%M:%S")


@beartype
def format_iso8601_date(time: datetime) -> str:
    return time.strftime("%Y-%m-%d")
