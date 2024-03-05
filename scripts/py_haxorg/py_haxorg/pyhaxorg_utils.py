from datetime import datetime
from py_haxorg.pyhaxorg import UserTime, UserTimeBreakdown
import py_haxorg.pyhaxorg_wrap as org
from beartype import beartype

@beartype
def evalDateTime(time: UserTime) -> datetime:
    brk: org.UserTimeBreakdown = time.getBreakdown()
    kwargs = dict(
        year=brk.year,
        month=brk.month,
        day=brk.day,
    )

    if brk.hour:
        kwargs["hour"] = brk.hour

    if brk.minute:
        kwargs["minute"] = brk.minute

    if brk.second:
        kwargs["second"] = brk.second

    return datetime(**kwargs)

@beartype
def formatDateTime(time: UserTime) -> str:
    return evalDateTime(time).strftime("%Y-%m-%d %H:%M:%S")
