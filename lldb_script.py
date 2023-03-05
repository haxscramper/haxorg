#!/usr/bin/env python

import lldb
import re


def simplify_name(name: str) -> str:
    replacements = [
        (
            "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>",
            "std::string",
        ),
        ("LexerCommon<OrgTokenKind>", "OrgLexer"),
        ("IntSet<OrgTokenKind>", "OrgTokSet"),
        ("unsigned long", "u32"),
        ("long", "i32"),
        ("unsigned long long", "u64"),
        ("long long", "i64"),
        (r"std::vector<(.*?), std::allocator<\1>>", r"std::vector<\1>"),
        (
            r"std::_Vector_base<(.*?), std::allocator<\1>>",
            r"std::_Vector_base<\1>",
        ),
    ]
    for (_from, _to) in replacements:
        name = re.sub(_from, _to, name)

    return name


def format_frame(frame, unused):
    if (
        "Catch" in frame.name
        or "__gnu" in frame.name
        or "__libc" in frame.name
        or (
            frame.line_entry.file.basename
            and (
                "std_function" in frame.line_entry.file.basename
                or "invoke.h" in frame.line_entry.file.basename
            )
        )
    ):
        return ""

    result = f"\033[35m{frame.idx:>2}\033[0m: {simplify_name(frame.name)}"
    # 'A read only property that returns the 1 based line number for this
    # line entry, a return value of zero indicates that no line information
    # is available.' -- looks like '4294967295' also indicates something,
    # not sure what exactly though.
    if 0 < frame.line_entry.line < 4294967295:
        loc = frame.line_entry
        result += f" at \033[34m{loc.file.basename}:{loc.line}\033[0m"

    # if "Catch" not in frame.name:
    #     for arg in frame.args:
    #         result += f"\n       = {arg.name:<16} = {arg.summary}"

    return result + "\n"


def __lldb_init_module(debugger, internal_dict):
    print("Install")
