#!/usr/bin/env python

from pathlib import Path
import sys

from tree_sitter import Language, Parser
import tree_sitter_cpp as tscpp

CPP_LANGUAGE = Language(tscpp.language())

DEBUG_FUNCTIONS = {"_dbg", "HSLOG_DEBUG"}


def find_debug_calls(source_code: bytes, filename: str) -> list[tuple[int, int, str]]:
    """Find all debug function calls in source code."""
    parser = Parser(CPP_LANGUAGE)
    tree = parser.parse(source_code)

    findings = []
    lines = source_code.split(b'\n')

    def visit(node):
        # Match call_expression nodes
        if node.type == "call_expression":
            # First child is the function being called
            func_node = node.child_by_field_name("function")
            if func_node:
                func_name = source_code[func_node.start_byte:func_node.end_byte].decode()
                if func_name in DEBUG_FUNCTIONS:
                    end_line_idx = node.end_point[0]
                    line_content = lines[end_line_idx] if end_line_idx < len(
                        lines) else b''
                    if b'// hook-ignore' not in line_content:
                        findings.append((
                            node.start_point[0] + 1,  # line (1-indexed)
                            node.start_point[1] + 1,  # column (1-indexed)
                            func_name))

        for child in node.children:
            visit(child)

    visit(tree.root_node)
    return findings


def main() -> int:
    exit_code = 0

    for filepath in sys.argv[1:]:
        path = Path(filepath)
        if path.suffix not in {".cpp", ".cc", ".cxx", ".hpp", ".h", ".hxx"}:
            continue

        source = path.read_bytes()
        findings = find_debug_calls(source, filepath)

        for line, col, func_name in findings:
            print(f"{filepath}:{line}:{col}: found debug call '{func_name}'")
            exit_code = 1

    return exit_code


if __name__ == "__main__":
    sys.exit(main())
