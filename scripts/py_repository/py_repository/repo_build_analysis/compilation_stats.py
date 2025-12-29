#!/usr/bin/env python

## @file   compilation_stats.py
## @brief  Aggregate build time statistics from the `-ftime-trace` JSON 

from rich.logging import RichHandler
import logging
from enum import Enum
from datetime import datetime
from pprint import pprint
from dataclasses import dataclass, field
try:
    from dataclasses_json import dataclass_json, config, Undefined  # type: ignore[import-not-found]
except ImportError:
    # Fallback if dataclasses_json is not available
    def dataclass_json(cls):  # type: ignore
        return cls
import json
from beartype.typing import *
from pathlib import Path
import pandas as pd



logging.basicConfig(
    level="NOTSET",
    format="%(message)s",
    datefmt="[%X]",
    handlers=[RichHandler(
        markup=True,
        enable_link_path=False,
        show_time=False,
    )],
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


@dataclass
class TraceEventNode:
    event: TraceEvent
    children: List["TraceEventNode"]

    def to_dict(self) -> Dict[str, Any]:
        return {
            "event": self.event.to_dict(),
            "children": [child.to_dict() for child in self.children],
        }


@dataclass_json
@dataclass
class TraceFile:
    traceEvents: List[TraceEvent] = field(default_factory=list)
    tree: Optional[TraceEventNode] = None
    path: str = ""
    beginningOfTime: int = 0


def build_flamegraph(trace_events: List[TraceEvent]) -> Optional[TraceEventNode]:
    if not trace_events:
        return None

    # with open("/tmp/res.json", "w") as out_file:
    #     for event in trace_events:
    #         out_file.write(json.dumps(TraceEvent.to_dict(event)) + "\n")

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
    path_files: List[Path] = []
    max_len = 1200
    for path in Path(
            "/mnt/workspace/repos/build-haxorg-Clang_16-RelWithDebInfo/CMakeFiles/"
    ).rglob("*.cpp.json"):
        path_files.append(path)

    all_files: List[TraceFile] = []

    for i in range(0, min(max_len, len(path_files))):
        path = path_files[i]
        print(f"{i}/{len(path_files)} {path}")
        with open(path) as file:
            j = json.load(file)
            converted: TraceFile = TraceFile.from_dict(j)
            converted.path = str(path)

            converted.tree = build_flamegraph([
                e for e in converted.traceEvents if e.tid == converted.traceEvents[0].tid
            ])

            all_files.append(converted)

            continue

            flame_path = path.with_suffix(".flame.json")

            # Write flamegraph to JSON file
            with open(flame_path, "w") as flame_file:
                json.dump(flame.to_dict(), flame_file)

    for f in sorted(all_files, key=lambda f: -f.tree.event.dur):
            print("{:10.5f}s {}".format(f.tree.event.dur / 1e6, f.path))

    def flatten_tracefiles(tracefiles: List[TraceFile]) -> List[Dict[str, Any]]:
        # Flatten the list of TraceFile objects
        flattened: List[Dict[str, Any]] = []
        for tracefile in tracefiles:
            for event in tracefile.traceEvents:
                flattened.append({
                    "name": event.name,
                    "detail": event.args.detail,
                    "duration": event.dur,
                })
        return flattened

    # Flatten your tracefiles
    flattened = flatten_tracefiles(all_files)

    # Convert to DataFrame
    df = pd.DataFrame(flattened)

    # This will set max rows and columns displayed to be unlimited.
    pd.set_option("display.max_rows", None)
    pd.set_option("display.max_columns", None)
    pd.set_option("display.max_colwidth", 20)

    # This is our custom aggregation function
    def custom_agg(group: pd.DataFrame) -> pd.Series:
        data = {
            "count": group["duration"].count(),
            "total_time": group["duration"].sum(),
        }
        return pd.Series(data, index=["count", "total_time"])

    # Calculate total duration for each group
    group_total_durations = df.groupby("name")["duration"].sum()

    # Sort group names by total duration in descending order
    sorted_group_names = group_total_durations.sort_values(ascending=False).index

    # Write the DataFrame to a file.
    with open("/tmp/sorted.txt", "w") as f:
        for i in range(0, len(sorted_group_names)):
            name = sorted_group_names[i]
            print(f"{i}/{len(sorted_group_names)} {name}")
            name_group = df[df["name"] == name]
            detail_group = name_group.groupby("detail").apply(custom_agg)
            sorted_group = detail_group.sort_values("total_time", ascending=False)

            f.write(
                f"Name: {name} total {sorted_group['total_time'].sum() / 1E6:10.5f}\n")
            for detail, row in sorted_group.iterrows():
                f.write("  {:<10} {:10.5f} {:<20}\n".format(row["count"],
                                                            row["total_time"] / 1e6,
                                                            detail))

            f.write("\n\n")

    print("Done")
