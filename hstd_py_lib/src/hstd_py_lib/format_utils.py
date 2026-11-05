from datetime import timedelta

from beartype import beartype


@beartype
def format_readable_duration(duration: timedelta | None) -> str:
    if duration is None:
        return ""

    remaining: int = max(0, duration // timedelta(milliseconds=1))
    units: list[tuple[int, str]] = [
        (30 * 24 * 60 * 60 * 1000, "mo"),
        (24 * 60 * 60 * 1000, "d"),
        (60 * 60 * 1000, "h"),
        (60 * 1000, "m"),
    ]
    parts: list[str] = []

    for size, suffix in units:
        value, remaining = divmod(remaining, size)
        if value:
            parts.append(f"{value}{suffix}")
        if len(parts) == 2:
            return " ".join(parts)

    seconds, milliseconds = divmod(remaining, 1000)

    if parts:
        if seconds:
            parts.append(f"{seconds}s")
        elif milliseconds:
            parts.append(f"{milliseconds}ms")
    elif seconds == 0:
        parts.append(f"{milliseconds}ms")
    elif seconds < 10:
        parts.append(f"{seconds}.{milliseconds:03d}s")
    else:
        parts.append(f"{seconds}.{milliseconds // 100}s")

    return " ".join(parts)
