import json
from dataclasses import asdict, dataclass, field
from enum import StrEnum
from typing import Any


class ReportReason(StrEnum):
    MANUAL = "manual"
    BREAKPOINT = "breakpoint"
    SIGNAL = "signal"


@dataclass
class ValueNode:
    name: str
    type_name: str
    value: str | None = None
    summary: str | None = None
    error: str | None = None
    truncated: bool = False
    nested: list["ValueNode"] = field(default_factory=list)


@dataclass
class FrameInfo:
    index: int
    function_name: str
    file_path: str | None
    line: int | None
    arguments: list[ValueNode] = field(default_factory=list)


@dataclass
class ThreadInfo:
    tid: int
    stop_reason: str
    signal_name: str | None
    signal_number: int | None
    frames: list[FrameInfo] = field(default_factory=list)


@dataclass
class Report:
    pid: int
    reason: ReportReason
    threads: list[ThreadInfo] = field(default_factory=list)

    def to_json(self) -> str:
        return json.dumps(
            asdict(self),
            ensure_ascii=False,
            separators=(",", ":"),
        )

    @classmethod
    def from_json(cls, text: str) -> "Report":
        data = json.loads(text)
        data["reason"] = ReportReason(data["reason"])

        threads: list[ThreadInfo] = []
        for thread_data in data.pop("threads"):
            frames: list[FrameInfo] = []

            for frame_data in thread_data.pop("frames"):
                arguments = [
                    value_from_data(argument) for argument in frame_data.pop("arguments")
                ]
                frames.append(FrameInfo(**frame_data, arguments=arguments))

            threads.append(ThreadInfo(**thread_data, frames=frames))

        return cls(**data, threads=threads)


def value_from_data(data: dict[str, Any]) -> ValueNode:
    nested = [value_from_data(item) for item in data.pop("nested")]
    return ValueNode(**data, nested=nested)
