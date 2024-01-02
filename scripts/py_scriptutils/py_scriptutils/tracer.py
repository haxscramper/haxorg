from dataclasses import dataclass
from beartype.typing import Dict, Optional, List, Any, Iterator
from beartype import beartype
import time
from enum import Enum
import os
from contextlib import contextmanager
import json
from pathlib import Path


class EventType(str, Enum):
    COMPLETE = "X"


@beartype
@dataclass
class TraceEvent:
    name: str
    cat: str
    ph: EventType
    ts: int
    dur: int
    pid: int
    tid: int
    args: Dict[str, Any]
    sf: Optional[str] = None
    stack: Optional[List[str]] = None
    esf: Optional[str] = None
    estack: Optional[List[str]] = None


@beartype
class TraceCollector:

    def __init__(self) -> None:
        self.traceEvents: List[TraceEvent] = []
        self.metadata: Dict[str, Any] = {}

    def get_last_event(self) -> Optional[TraceEvent]:
        return self.traceEvents and self.traceEvents[-1]

    @contextmanager
    def complete_event(self,
                       name: str,
                       category: str,
                       args: Optional[Dict[str, Any]] = None) -> Iterator[TraceEvent]:
        pid = os.getpid()
        tid = id(self)
        start_time = int(time.time() * 1e6)  # Convert to microseconds

        new_event = TraceEvent(
            name=name,
            cat=category,
            ph=EventType.COMPLETE,
            ts=start_time,
            dur=0,
            pid=pid,
            tid=tid,
            args=args or {},
        )

        try:
            yield new_event

        finally:
            end_time = int(time.time() * 1e6)
            new_event.dur = end_time - start_time
            self.traceEvents.append(new_event)

    def set_metadata(self, key: str, value: Any):
        self.metadata[key] = value

    def export_to_json(self, filename: Path):
        data = {
            "traceEvents": [event.__dict__ for event in self.traceEvents],
            "otherData": self.metadata
        }
        with open(str(filename), 'w') as f:
            json.dump(data, f, indent=4)


__global_trace_collector: Optional[TraceCollector] = None


def getGlobalTraceCollector():
    global __global_trace_collector
    if not __global_trace_collector:
        __global_trace_collector = TraceCollector()

    return __global_trace_collector


@contextmanager
def GlobCompleteEvent(name: str, category: str, args: Optional[Dict[str, Any]] = None) -> Iterator[TraceEvent]:
    with getGlobalTraceCollector().complete_event(name, category, args) as new_event:
        yield new_event


def GlobExportJson(file: Path):
    return getGlobalTraceCollector().export_to_json(file)
