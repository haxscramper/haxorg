import re
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable

import lldb

from hstd_py_lib.debug_utils.config import Settings
from hstd_py_lib.debug_utils.model import (
    FrameInfo,
    Report,
    ReportReason,
    ThreadInfo,
    ValueNode,
)


@dataclass(frozen=True)
class ExtractorRegistration:
    pattern: re.Pattern[str]
    extract: Callable[
        [lldb.SBValue, "ExtractionContext", int],
        ValueNode,
    ]


@dataclass
class ExtractorRegistry:
    registrations: list[ExtractorRegistration] = field(default_factory=list)

    def register(
        self,
        pattern: str,
        extract: Callable[
            [lldb.SBValue, "ExtractionContext", int],
            ValueNode,
        ],
    ) -> None:
        self.registrations.append(
            ExtractorRegistration(
                pattern=re.compile(pattern),
                extract=extract,
            )
        )


@dataclass
class ExtractionContext:
    settings: Settings
    registry: ExtractorRegistry
    blacklist: list[re.Pattern[str]] = field(init=False)

    def __post_init__(self) -> None:
        self.blacklist = [
            re.compile(pattern) for pattern in self.settings.frame_blacklist
        ]

    def extract(
        self,
        value: lldb.SBValue,
        depth: int = 0,
    ) -> ValueNode:
        if not value.IsValid():
            return ValueNode(
                name="<invalid>",
                type_name="",
                error="LLDB returned an invalid SBValue",
            )

        type_name = value.GetTypeName() or ""

        for registration in self.registry.registrations:
            if registration.pattern.search(type_name):
                return registration.extract(value, self, depth)

        return self.extract_default(value, depth)

    def extract_default(
        self,
        value: lldb.SBValue,
        depth: int = 0,
    ) -> ValueNode:
        if not value.IsValid():
            return ValueNode(
                name="<invalid>",
                type_name="",
                error="LLDB returned an invalid SBValue",
            )

        source = value.GetDynamicValue(lldb.eDynamicDontRunTarget)
        if not source.IsValid():
            source = value

        source.SetPreferSyntheticValue(True)

        node = ValueNode(
            name=value.GetName() or "",
            type_name=value.GetTypeName() or "",
            value=source.GetValue(),
            summary=source.GetSummary(),
        )

        error = source.GetError()
        if error.Fail():
            node.error = (
                error.GetCString()
                or f"LLDB could not read {node.name!r} of type {node.type_name!r}"
            )
            return node

        if source.GetType().IsPointerType() and source.GetValueAsUnsigned() == 0:
            return node

        if self.settings.max_depth <= depth:
            node.truncated = source.MightHaveChildren()
            return node

        limit = self.settings.max_nested
        count = source.GetNumChildren(limit + 1)
        node.truncated = limit < count

        for index in range(min(count, limit)):
            nested = source.GetChildAtIndex(index)
            node.nested.append(self.extract(nested, depth + 1))

        return node

    def extract_frame(
        self,
        frame: lldb.SBFrame,
        index: int,
    ) -> FrameInfo | None:
        function_name = (
            frame.GetDisplayFunctionName()
            or frame.GetFunctionName()
            or frame.GetSymbol().GetName()
            or "<unknown>"
        )

        if any(pattern.search(function_name) for pattern in self.blacklist):
            return None

        file_path: str | None = None
        line: int | None = None
        entry = frame.GetLineEntry()

        if entry.IsValid():
            specification = entry.GetFileSpec()
            filename = specification.GetFilename()

            if filename:
                file_path = str(Path(specification.GetDirectory() or "") / filename)
                line = entry.GetLine()

        arguments = frame.GetVariables(
            True,
            False,
            False,
            True,
        )

        return FrameInfo(
            index=index,
            function_name=function_name,
            file_path=file_path,
            line=line,
            arguments=[
                self.extract(arguments.GetValueAtIndex(position))
                for position in range(arguments.GetSize())
            ],
        )

    def extract_thread(
        self,
        thread: lldb.SBThread,
    ) -> ThreadInfo:
        reason = thread.GetStopReason()
        signal_name: str | None = None
        signal_number: int | None = None

        if reason == lldb.eStopReasonSignal:
            signal_number = thread.GetStopReasonDataAtIndex(0)
            signal_name = (
                thread.GetProcess().GetUnixSignals().GetSignalAsCString(signal_number)
            )

        description = thread.GetStopDescription(1024)
        info = ThreadInfo(
            tid=thread.GetThreadID(),
            stop_reason=description or str(reason),
            signal_name=signal_name,
            signal_number=signal_number,
        )

        end = min(
            self.settings.frame_end,
            thread.GetNumFrames(),
        )

        for index in range(self.settings.frame_start, end):
            frame = self.extract_frame(
                thread.GetFrameAtIndex(index),
                index,
            )
            if frame is not None:
                info.frames.append(frame)

        return info

    def extract_report(
        self,
        process: lldb.SBProcess,
        threads: list[lldb.SBThread],
        reason: ReportReason,
    ) -> Report:
        return Report(
            pid=process.GetProcessID(),
            reason=reason,
            threads=[self.extract_thread(thread) for thread in threads],
        )
