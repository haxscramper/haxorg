#!/usr/bin/env python

import lldb

def simplify_name(name: str) -> str:
    replacements = [
        ("std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>", "std::string")
    ]
    for (_from, _to) in replacements:
        name = name.replace(_from, _to)

    return name


def format_frame(frame, unused):
    result = f"\033[35m{frame.idx:>2}\033[0m: {simplify_name(frame.name)}"
    # 'A read only property that returns the 1 based line number for this
    # line entry, a return value of zero indicates that no line information
    # is available.' -- looks like '4294967295' also indicates something,
    # not sure what exactly though.
    if 0 < frame.line_entry.line < 4294967295:
        loc = frame.line_entry
        result += f" at \033[34m{loc.file.basename}:{loc.line}\033[0m"

    return result + "\n"

def __lldb_init_module(debugger, internal_dict):
    print("Install")
