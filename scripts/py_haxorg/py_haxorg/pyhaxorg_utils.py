from datetime import datetime
from py_haxorg.pyhaxorg_wrap import UserTime, UserTimeBreakdown
import py_haxorg.pyhaxorg_wrap as org
from beartype import beartype
from beartype.typing import List

@beartype
def evalDateTime(time: UserTime) -> datetime:
    brk: org.UserTimeBreakdown = time.getBreakdown()
    kwargs = dict(
        year=brk.year,
        month=brk.month  or 1,
        day=brk.day or 1,
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
    brk: org.UserTimeBreakdown = time.getBreakdown()
    format = "%Y-%m-%d"
    if brk.hour:
        format += " %H"

    if brk.minute:
        format += ":%M"

    if brk.second:
        format += ":%S"

    return evalDateTime(time).strftime(format)

@beartype
def getFlatTags(tag: org.HashTag) -> List[List[str]]:
    def aux(parents: List[str], tag: org.HashTag) -> List[str]:
        result: List[str] = []
        if len(tag.subtags) == 0:
            return [parents + [tag.head]]
        
        else:
            for subtag in tag.subtags:
                for flat in aux(parents + [tag.head], subtag):
                    result.append(flat)
        
        return result
    
    return aux([], tag)
