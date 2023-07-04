#!/usr/bin/env python

from rich.logging import RichHandler
import logging
from enum import Enum
from datetime import datetime
from pprint import pprint
from dataclasses import dataclass, field
from dataclasses_json import dataclass_json, config, Undefined
import json
from typing import *
from pathlib import Path


logging.basicConfig(
    level="NOTSET",
    format="%(message)s",
    datefmt="[%X]",
    handlers=[
        RichHandler(
            markup=True,
            enable_link_path=False,
            show_time=False,
        )
    ],
)


@dataclass_json
@dataclass
class TraceArgs:
    detail: str = ""


@dataclass_json
@dataclass
class TraceEvent:
    pid: int = 0
    tid: int = 0
    ph: str = ""
    ts: int = 0
    dur: int = 0
    name: str = ""
    args: TraceArgs = field(default_factory=TraceArgs)


@dataclass_json
@dataclass
class TraceFile:
    traceEvents: List[TraceEvent] = field(default_factory=list)
    beginningOfTime: int = 0


@dataclass
class TraceEventNode:
    event: TraceEvent
    children: List["TraceEventNode"]

    def to_dict(self) -> Dict[str, Any]:
        return {
            "event": self.event.to_dict(),
            "children": [child.to_dict() for child in self.children],
        }


def build_flamegraph(trace_events: List[TraceEvent]) -> Optional[TraceEventNode]:
    if not trace_events:
        return None

    with open("/tmp/res.json", "w") as out_file:
        for event in trace_events:
            out_file.write(json.dumps(TraceEvent.to_dict(event)) + "\n")

    # Sort events by start time
    trace_events.sort(key=lambda e: e.ts)

    # Initialize call stack with the first event
    root = TraceEventNode(event=trace_events[0], children=[])
    call_stack = [root]

    with open("/tmp/flame_trace", "w") as file:
        # Process the rest of the events
        for event in trace_events[1:]:
            e = call_stack[-1].event
            print(
                f"{'  ' * len(call_stack)} {e.name} from {e.ts / 1000000:6.3}s for {e.dur / 1000000:6.3}s on {e.args.detail}",
                file=file,
            )
            # Pop completed events from the call stack
            while (call_stack[-1].event.ts + call_stack[-1].event.dur) < event.ts:
                call_stack.pop()
                if not call_stack:
                    break

            # If the call stack is empty, this event starts a new tree
            if not call_stack:
                root = TraceEventNode(event=event, children=[])
                call_stack.append(root)
            else:
                # Otherwise, this event is a child of the current event at the top of the call stack
                node = TraceEventNode(event=event, children=[])
                call_stack[-1].children.append(node)
                call_stack.append(node)

        return root


if __name__ == "__main__":
    for path in Path(
        "/mnt/workspace/repos/build-haxorg-Clang-RelWithDebInfo/CMakeFiles/haxorg.dir/src/parse/"
    ).rglob("OrgParser.cpp.json"):
        with open(path) as file:
            print(path)
            j = json.load(file)
            converted: TraceFile = TraceFile.from_dict(j)

            flame = build_flamegraph(
                [
                    e
                    for e in converted.traceEvents
                    if e.tid == converted.traceEvents[0].tid
                ]
            )
            flame_path = path.with_suffix(".flame.json")

            # Write flamegraph to JSON file
            with open(flame_path, "w") as flame_file:
                json.dump(flame.to_dict(), flame_file)

    print("Done")
