#!/usr/bin/env python

import lldb # type: ignore
import re
import os
from typing import Any


def simplify_name(name: str) -> str:
    replacements = [
        ("std::__1::__", "std"),
        (r"std::variant<(sem::SemId<sem::\w+>,?\s*)+\s*>", "SemIdVariant"),
        (
            "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>",
            "std::string",
        ),
        ("LexerCommon<OrgTokenKind>", "OrgLexer"),
        ("IntSet<OrgTokenKind>", "OrgTokSet"),
        ("unsigned long", "u32"),
        ("OrgTokenizer::", ""),
        ("OrgParser::", ""),
        ("OrgConverter::", ""),
        ("Token<OrgTokenKind>", "OrgTok"),
        ("IntSet<char>", "CharSet"),
        ("std::function", "Func"),
        ("long", "i32"),
        ("unsigned long long", "u64"),
        ("long long", "i64"),
        ("std::variant", "Variant"),
        ("NodeGroup<OrgNodeKind, OrgTokenKind>", "OrgNodeGroup"),
        ("NodeId<OrgNodeKind, OrgTokenKind, u32, u32>", "OrgNodeId"),
        (r"::'lambda'.*?operator\(\)", "lambda"),
        (r"std::vector<(.*?), std::allocator<\1>>", r"std::vector<\1>"),
        (
            r"std::_Vector_base<(.*?), std::allocator<\1>>",
            r"std::_Vector_base<\1>",
        ),
        (r"\(anonymous namespace\)::", ""),
    ]
    for (_from, _to) in replacements:
        name = re.sub(_from, _to, name)

    return name


def align_on_sides(debugger: lldb.SBDebugger, text1: str, text2: str) -> str:

    def visible_length(s: str) -> int:
        return len(re.sub(r"\x1B\[[0-?]*[ -/]*[@-~]", "", s))

    term_width = debugger.GetTerminalWidth()
    padding_length = (term_width - visible_length(text1) - visible_length(text2))

    if padding_length > 0:
        padding = " " * padding_length
    else:
        padding = ""

    return f"{text1}{padding}{text2}"


def format_frame(frame: Any, unused: Any, **kwargs: Any) -> str:
    def fmt_color(value: int) -> str:
        if "no_color" in kwargs:
            return ""

        else:
            return f"\033[{value}m"



    start = f"{fmt_color(35)}{frame.idx:>2}{fmt_color(0)}: {simplify_name(frame.name)}"
    # 'A read only property that returns the 1 based line number for this
    # line entry, a return value of zero indicates that no line information
    # is available.' -- looks like '4294967295' also indicates something,
    # not sure what exactly though.
    location = ""
    if 0 < frame.line_entry.line < 4294967295:
        loc = frame.line_entry
        text = f"{loc.file.basename}:{loc.line:<4}"
        location = f" {fmt_color(34)}{text}{fmt_color(0)}"

    return align_on_sides(lldb.debugger, start, location)


def should_skip_frame(frame: Any) -> bool:
    return any([
        "___lldb_unnamed_symbol" in frame.name,
        "Catch" in frame.name,
        "__gnu" in frame.name,
        "__libc" in frame.name,
        "___lldb_unnamed" in frame.name,
        (frame.line_entry.file.basename and
         ("std_function" in frame.line_entry.file.basename or
          "invoke.h" in frame.line_entry.file.basename)),
    ])

USE_NATIVE_TRACE = False
DROP_NOISY_FRAMES = False
USE_TRACE_FILE = "/tmp/stacktrace.txt"
USE_STDOUT = False

out_file = None

def skip_backtrace(debugger: Any, command: Any, result: Any, internal_dict: Any) -> None:
    thread = debugger.GetSelectedTarget().GetProcess().GetSelectedThread()
    filtered_frames = []
    columns = int(os.environ.get("LLDB_CUSTOM_TERM_WIDTH", 0))
    if columns != 0:
        debugger.SetTerminalWidth(columns)

    frames = reversed([frame for frame in thread])

    for frame in frames:
        filtered_frames.append(frame)

    filtered_frames = reversed(filtered_frames) # type: ignore

    for index, frame in enumerate(filtered_frames):
        if USE_NATIVE_TRACE:
            if out_file:
                print(frame, file=out_file)
            print(frame)

        else:
            if not DROP_NOISY_FRAMES or not should_skip_frame(frame):
                if out_file:
                    print(format_frame(frame, None, no_color=True), file=out_file)

                print(format_frame(frame, None))




def stop_handler(frame: Any, bp_loc: Any, dict: Any) -> bool:
    global out_file
    if USE_TRACE_FILE:
        out_file = open(USE_TRACE_FILE, "w")

    else:
        out_file = None

    if out_file:
        print("-" * 80, file=out_file)

    print("-" * 80)

    thread = frame.GetThread()
    for i in range(thread.GetNumFrames()):
        skip_backtrace(lldb.debugger, None, None, None)

    if out_file:
        out_file.close()
        out_file = None

    return True


def __lldb_init_module(debugger: Any, internal_dict: Any) -> None:
    debugger.HandleCommand(
        f"command script add -f {__name__}.skip_backtrace skip_backtrace")

    target = debugger.GetSelectedTarget()
    bp = target.BreakpointCreateForException(
        lldb.eLanguageTypeC_plus_plus,
        False,  # don't pause on catch
        True  # do pause on throw
    )
    bp.SetScriptCallbackFunction(f"{__name__}.stop_handler")
    bp.SetAutoContinue(True)
