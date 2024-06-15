from dataclasses import dataclass
from beartype.typing import Dict, Optional, List, Any, Iterator
from beartype import beartype
import time
from enum import Enum
import os
from contextlib import contextmanager
import json
from pathlib import Path
import threading

import inspect


class EventType(str, Enum):
    COMPLETE = "X"


@beartype
@dataclass
class TraceEvent:
    name: str  # The name of the event, as displayed in Trace Viewer
    cat: str  # The event categories. This is a comma separated list of categories for the event. The categories can be used to hide events in the Trace Viewer UI.
    ph: EventType
    ts: int  # The tracing clock timestamp of the event. The timestamps are provided at microsecond granularity.
    dur: int
    pid: int  # The process ID for the process that output this event.
    tid: int  # The thread ID for the thread that output this event.
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
        self.eventStacks: Dict[int, List[TraceEvent]] = {}
        self.lock = threading.Lock()

    def get_last_event(self) -> Optional[TraceEvent]:
        return self.traceEvents and self.traceEvents[-1]

    def addEvents(self, events: List[TraceEvent]):
        with self.lock:
            self.traceEvents += events

    def push_complete_event(self,
                            name: str,
                            category: str,
                            args: Optional[Dict[str, Any]] = None) -> TraceEvent:
        pid = os.getpid()
        tid = threading.get_ident()
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

        with self.lock:
            if tid not in self.eventStacks:
                self.eventStacks[tid] = []
            self.eventStacks[tid].append(new_event)

        return new_event

    def pop_complete_event(self) -> TraceEvent:
        tid = threading.get_ident()

        with self.lock:
            new_event = self.eventStacks[tid].pop()
            end_time = int(time.time() * 1e6)
            new_event.dur = end_time - new_event.ts
            self.traceEvents.append(new_event)

        return new_event

    @contextmanager
    def complete_event(
        self,
        name: str,
        category: str,
        args: Optional[Dict[str, Any]] = None,
        file: Optional[str] = None,
        line: Optional[int] = None,
        function: Optional[str] = None,
    ) -> Iterator[TraceEvent]:

        if file or line or function:
            args = args or dict()
            args["call_file"] = file
            args["call_line"] = line
            args["call_function"] = function

        new_event = self.push_complete_event(name, category, args)
        try:
            yield new_event

        finally:
            self.pop_complete_event()

    def set_metadata(self, key: str, value: Any):
        self.metadata[key] = value

    def export_to_json(self, filename: Path):
        data = {
            "traceEvents": [event.__dict__ for event in self.traceEvents],
            "otherData": self.metadata
        }

        if not filename.parent.exists():
            filename.parent.mkdir(parents=True)

        with open(str(filename), 'w+') as f:
            json.dump(data, f, indent=4)


__global_trace_collector: Optional[TraceCollector] = None


@beartype
def getGlobalTraceCollector() -> TraceCollector:
    global __global_trace_collector
    if not __global_trace_collector:
        __global_trace_collector = TraceCollector()

    return __global_trace_collector


@contextmanager
def GlobCompleteEvent(
    name: str,
    category: str,
    args: Optional[Dict[str, Any]] = None,
    file: Optional[str] = None,
    line: Optional[int] = None,
    function: Optional[str] = None,
) -> Iterator[TraceEvent]:
    frame = inspect.currentframe().f_back.f_back
    info = inspect.getframeinfo(frame)

    with getGlobalTraceCollector().complete_event(
            name,
            category,
            args,
            file=file or info.filename,
            line=line or info.lineno,
            function=function or info.function,
    ) as new_event:
        yield new_event


def GlobGetEvents() -> List[TraceEvent]:
    return getGlobalTraceCollector().traceEvents


@beartype
def GlobAddEvents(events: List[TraceEvent]):
    getGlobalTraceCollector().addEvents(events)

@beartype
def GlobRestart():
    getGlobalTraceCollector().traceEvents = []


@beartype
def GlobExportJson(file: Path):
    return getGlobalTraceCollector().export_to_json(file)
