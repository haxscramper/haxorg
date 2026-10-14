import json
import os
import re
from dataclasses import dataclass, field, fields
from pathlib import Path
from typing import Callable, Mapping


def parse_boolean(value: str) -> bool:
    match value:
        case "true" | "1":
            return True
        case "false" | "0":
            return False
        case _:
            raise ValueError(
                f"Unexpected bool value, expected true/false/1/0 received {value!r}"
            )


def parse_strings(value: str) -> list[str]:
    parsed = json.loads(value)

    if not isinstance(parsed, list):
        raise TypeError(f"Expected a JSON array of strings, received {parsed!r}")

    for index, item in enumerate(parsed):
        if not isinstance(item, str):
            raise TypeError(f"Expected a string at index {index}, received {item!r}")

    return parsed


def parse_path(value: str) -> Path:
    if not value:
        raise ValueError("Expected a nonempty filesystem path")

    return Path(value)


@dataclass(frozen=True)
class Settings:
    enabled: bool = field(default=False, metadata={"parse": parse_boolean})
    formatter_max_string: int = field(default=1024, metadata={"parse": int})
    formatter_timeout_us: int = field(default=1_000_000, metadata={"parse": int})
    python_repr: bool = field(default=True, metadata={"parse": parse_boolean})
    script: Path | None = field(default=None, metadata={"parse": parse_path})
    frame_start: int = field(default=0, metadata={"parse": int})
    frame_end: int = field(default=40, metadata={"parse": int})
    max_depth: int = field(default=4, metadata={"parse": int})
    max_nested: int = field(default=64, metadata={"parse": int})
    binary_file_full_path: bool = field(default=False, metadata={"parse": parse_boolean})
    frame_blacklist: list[str] = field(
        default_factory=list, metadata={"parse": parse_strings}
    )
    breakpoint_functions: list[str] = field(
        default_factory=list, metadata={"parse": parse_strings}
    )
    fatal_signals: list[str] = field(
        default_factory=lambda: [
            "SIGSEGV",
            "SIGABRT",
            "SIGBUS",
            "SIGFPE",
            "SIGILL",
            "SIGSYS",
        ],
        metadata={"parse": parse_strings},
    )
    auto_continue: bool = field(default=True, metadata={"parse": parse_boolean})
    log_file: Path | None = field(default=None, metadata={"parse": parse_path})
    structured_output: bool = field(default=False, metadata={"parse": parse_boolean})
    pytest_backtrace_dir: Path | None = field(
        default=None,
        metadata={"parse": parse_path},
    )

    def __post_init__(self) -> None:
        for name in (
            "frame_start",
            "frame_end",
            "max_depth",
            "max_nested",
        ):
            value = getattr(self, name)
            if value < 0:
                raise ValueError(f"{name} must be nonnegative, received {value}")

        if self.frame_end < self.frame_start:
            raise ValueError(
                f"frame_end={self.frame_end} precedes frame_start={self.frame_start}"
            )

        for pattern in self.frame_blacklist:
            try:
                re.compile(pattern)
            except re.error as error:
                raise ValueError(
                    f"Invalid HSTD_PY_LLDB_FRAME_BLACKLIST "
                    f"expression {pattern!r}: {error}"
                ) from error

    @classmethod
    def from_environment(
        cls,
        environment: Mapping[str, str] | None = None,
    ) -> "Settings":
        source = os.environ if environment is None else environment
        values: dict[str, object] = {}

        for entry in fields(cls):
            variable = f"HSTD_PY_LLDB_{entry.name.upper()}"

            if variable not in source:
                continue

            parser: Callable[[str], object] = entry.metadata["parse"]

            try:
                values[entry.name] = parser(source[variable])
            except (ValueError, TypeError) as error:
                raise ValueError(
                    f"Invalid {variable}={source[variable]!r}: {error}"
                ) from error

        return cls(**values)  # type: ignore
