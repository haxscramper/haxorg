#!/usr/bin/env python

import lldb
import re
import os


def simplify_name(name: str) -> str:
    replacements = [
        ("std::__1::__", "std"),
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


def format_frame(frame, unused):
    start = f"\033[35m{frame.idx:>2}\033[0m: {simplify_name(frame.name)}"
    # 'A read only property that returns the 1 based line number for this
    # line entry, a return value of zero indicates that no line information
    # is available.' -- looks like '4294967295' also indicates something,
    # not sure what exactly though.
    location = ""
    if 0 < frame.line_entry.line < 4294967295:
        loc = frame.line_entry
        text = f"{loc.file.basename}:{loc.line:<4}"

        location = f"\033[34m{text}\033[0m"

    return align_on_sides(lldb.debugger, start, location)


def should_skip_frame(frame):
    return ("Catch" in frame.name or "__gnu" in frame.name or "__libc" in frame.name or
            "___lldb_unnamed" in frame.name or
            (frame.line_entry.file.basename and
             ("std_function" in frame.line_entry.file.basename or
              "invoke.h" in frame.line_entry.file.basename)))


def skip_backtrace(debugger, command, result, internal_dict):
    thread = debugger.GetSelectedTarget().GetProcess().GetSelectedThread()
    filtered_frames = []
    columns = int(os.environ.get("LLDB_CUSTOM_TERM_WIDTH", 0))
    if columns != 0:
        debugger.SetTerminalWidth(columns)

    frames = reversed([frame for frame in thread])

    for frame in frames:
        filtered_frames.append(frame)

    filtered_frames = reversed(filtered_frames)

    for index, frame in enumerate(filtered_frames):
        print("{frame}".format(frame=frame))


def __lldb_init_module(debugger, internal_dict):
    debugger.HandleCommand(
        "command script add -f {module}.skip_backtrace skip_backtrace".format(
            module=__name__))
    print("Install")
