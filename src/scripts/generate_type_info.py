#!/usr/bin/env python

import argparse
import clang
import json
import clang.cindex
from typing import List

parser = argparse.ArgumentParser(
    description="Generate structured JSON for types in the input file"
)
parser.add_argument(
    "infile",
    type=str,
    help="Input header/source file to generate info for",
)

parser.add_argument(
    "outfile",
    type=str,
    help="resulting JSON file to write data to",
)

args = parser.parse_args()
print("Reading input from ", args.infile)
print("Writing output to ", args.outfile)


INDENT = 4
K = clang.cindex.CursorKind


def is_std_ns(node):
    return node.kind == K.NAMESPACE and node.spelling == "std"


def clangCursorTreeRepr(
    cursor: clang.cindex.Cursor,
    indent: int = 0,
    saw=set(),
    print_referenced: bool = True,
    print_stdlib: bool = False
) -> str:
    result = ""
    pre = " " * indent
    k = cursor.kind  # type: clang.cindex.CursorKind
    # skip printting UNEXPOSED_*
    if not k.is_unexposed():
        result += f"{pre}{k.name}"
        if cursor.spelling:
            result += f" s: {cursor.spelling}"
            if cursor.type.spelling:
                result += f" t: {cursor.type.spelling}"
            # FIXME: print opcode or literal
    saw.add(cursor.hash)
    if (
        print_referenced
        and cursor.referenced is not None
        and cursor.referenced.hash not in saw
    ):
        result += "\n"
        result += clangCursorTreeRepr(
            cursor.referenced, indent + INDENT, saw
        )

    if print_stdlib:
        for c in cursor.get_children():
            result += "\n"
            result += clangCursorTreeRepr(c, indent + INDENT, saw)

    else:
        skip = len(
            [
                c
                for c in cursor.get_children()
                if indent == 0 and is_std_ns(c)
            ]
        )

        for c in cursor.get_children():
            if not skip:
                result += "\n"
                result += clangCursorTreeRepr(c, indent + INDENT, saw)

            if indent == 0 and is_std_ns(c):
                skip -= 1

        if cursor.hash in saw:
            saw.remove(cursor.hash)

    return result




def find_enums(cursor, basefile) -> List:
    result = []
    if cursor.kind == K.ENUM_DECL and str(cursor.location.file) == basefile:
        print(clangCursorTreeRepr(cursor))
        fields = []
        for field in cursor.get_children():
            fields.append(field.spelling)

        result.append({"kind": "enum", "name": cursor.spelling, "fields": fields})

    for c in cursor.get_children():
        result += find_enums(c, basefile)

    return result


# By default `libclang-14.so` is used, but on arch installation shared
# library has different name. Alternative solution would be to symlink
# correct target library but I prefer to have more localized configuration
# in this case.
clang.cindex.Config.set_library_file("/usr/lib/libclang.so.14.0.6")
index = clang.cindex.Index.create()
tu = index.parse(args.infile)
enums = find_enums(tu.cursor, args.infile)

with open(args.outfile, "w+") as file:
    file.write(json.dumps(enums))
