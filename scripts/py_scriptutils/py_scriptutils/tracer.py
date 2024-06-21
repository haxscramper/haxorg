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
    METADATA = "M"


@beartype
@dataclass
class TraceEvent:
    name: str
    ph: EventType
    pid: int
    tid: int
    args: Dict[str, Any]
    dur: Optional[int] = None
    cat: Optional[str] = None
    ts: Optional[int] = None
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

    def add_instant_event(self, event: TraceEvent) -> TraceEvent:
        with self.lock:
            self.traceEvents.append(event)

        return event

    def add_metadata_event(self, name: str, args: dict) -> TraceEvent:
        return self.add_instant_event(
            TraceEvent(
                name=name,
                pid=os.getpid(),
                tid=threading.get_ident(),
                ph=EventType.METADATA,
                args=args,
                dur=0,
                ts=self.get_time(),
                cat="metadata",
            ))

    def add_process_name_event(self, name: str) -> TraceEvent:
        return self.add_metadata_event("process_name", dict(name=name))

    def add_thread_name_event(self, name: str) -> TraceEvent:
        return self.add_metadata_event("thread_name", dict(name=name))

    def add_process_index_event(self, index: int) -> TraceEvent:
        return self.add_metadata_event("process_sort_index", dict(sort_index=index))

    def add_thread_index_event(self, index: int) -> TraceEvent:
        return self.add_metadata_event("thread_sort_index", dict(sort_index=index))

    def get_time(self) -> int:
        return int(time.time() * 1e6)

    def push_complete_event(self,
                            name: str,
                            category: str,
                            args: Optional[Dict[str, Any]] = None) -> TraceEvent:
        pid = os.getpid()
        tid = threading.get_ident()

        new_event = TraceEvent(
            name=name,
            cat=category,
            ph=EventType.COMPLETE,
            ts=self.get_time(),
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
def GlobNameThisProcess(name: str):
    getGlobalTraceCollector().add_process_name_event(name)


@beartype
def GlobNameThisThread(name: str):
    getGlobalTraceCollector().add_thread_name_event(name)


@beartype
def GlobIndexThisProcess(index: int):
    getGlobalTraceCollector().add_process_index_event(index)


@beartype
def GlobIndexThisThread(index: int):
    getGlobalTraceCollector().add_thread_index_event(index)


@beartype
def GlobExportJson(file: Path):
    return getGlobalTraceCollector().export_to_json(file)
