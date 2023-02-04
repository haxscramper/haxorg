#!/usr/bin/env python

import argparse
import json
from textwrap import indent

parser = argparse.ArgumentParser(description="Generate type boilerplate for mapped types")
parser.add_argument(
    "infile",
    type=str,
    help="Input json file"
)

parser.add_argument(
    "out_header",
    type=str,
    help="Header file to write mappings to"
)

parser.add_argument(
    "out_source",
    type=str,
    help="Source file to write mappings to"
)

args = parser.parse_args()

content = json.loads(open(args.infile).read())

header_out = []
source_out = []

for entry in content:
    if entry["kind"] == "enum":
        source_out.append("#ifdef IN_NAMESPACE")
        name = entry["name"]
        fields = entry["fields"]
        header_out.append(f"""
const char* to_string({name} in);
{name} {name}_from_string(const char*, int on_error = -1);
        """)

        if True:
            cases = []
            for f in fields:
                cases.append(f"if (strcmp(in, \"{f}\") == 0) {{ return {name}::{f}; }}")
            cases.append(f"return ({name})on_error;")

            cases = indent("\n".join(cases), " " * 4)
            source_out.append(f"""
{name} {name}_from_string(const char* in, int on_error) {{
{cases}
}}
            """)


        if True:
            cases = []
            for f in fields:
                cases.append(f"case {name}::{f}: return \"{f}\";")
            cases.append("default: return nullptr;")
            cases = indent("\n".join(cases), " " * 8)

            source_out.append(f"""
const char* to_string({name} in) {{
    switch(in) {{
{cases}
    }}
}}
            """)

        source_out.append("#endif")
        source_out.append(f"""
#ifndef IN_NAMESPACE
template <>
{name} low() {{
    return {name}::{fields[0]};
}}

template <{name}>
{name} high() {{
    return {name}::{fields[-1]};
}}
#endif
""")



import os

for f in [args.out_source, args.out_header]:
    parent_dir = os.path.dirname(f)

    if not os.path.exists(parent_dir):
        os.makedirs(parent_dir)

with open(args.out_source, "w+") as file:
    file.write("\n".join(source_out))

with open(args.out_header, "w+") as file:
    file.write("#include <string.h>\n")
    file.write("\n".join(header_out))

print("done generating source mappings")
