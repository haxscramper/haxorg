from dataclasses import field, dataclass, replace
from beartype.typing import *
from beartype import beartype
import time
from enum import Enum
import os
from contextlib import contextmanager
import json


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

    def __init__(self):
        self.traceEvents: List[TraceEvent] = []
        self.metadata: Dict[str, Any] = {}

    @contextmanager
    def complete_event(self,
                       name: str,
                       category: str = "",
                       args: Optional[Dict[str, Any]] = None):
        pid = os.getpid()
        tid = id(self)
        start_time = int(time.time() * 1e6)  # Convert to microseconds

        yield

        end_time = int(time.time() * 1e6)
        duration = end_time - start_time

        self.traceEvents.append(
            TraceEvent(name=name,
                       cat=category,
                       ph=EventType.COMPLETE,
                       ts=start_time,
                       dur=duration,
                       pid=pid,
                       tid=tid,
                       args=args or {}))

    def set_metadata(self, key: str, value: Any):
        self.metadata[key] = value

    def export_to_json(self, filename: str):
        data = {
            "traceEvents": [event.__dict__ for event in self.traceEvents],
            "otherData": self.metadata
        }
        with open(filename, 'w') as f:
            json.dump(data, f, indent=4)
