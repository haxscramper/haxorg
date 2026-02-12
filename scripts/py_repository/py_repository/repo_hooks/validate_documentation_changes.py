#!/usr/bin/env python

import argparse
import ast
from dataclasses import dataclass
import os
from pathlib import Path
import re
import subprocess
import sys
from typing import Iterable, Optional

from tree_sitter import Language, Parser
import tree_sitter_cpp as tscpp

PY_SUFFIXES = {".py"}
CPP_SUFFIXES = {".h", ".hh", ".hpp", ".hxx", ".c", ".cc", ".cpp", ".cxx"}
CAN_SKIP_DOCUMENTATION = {"main"}

HUNK_RE = re.compile(r"^@@ -\d+(?:,\d+)? \+(\d+)(?:,(\d+))? @@")


@dataclass(frozen=True)
class Range:
    "Inclusive range of lines for the documentable entry"
    start: int  # 1-based
    end: int  # 1-based

    def intersects(self, other: "Range") -> bool:
        "Check if two ranges overlap"
        return max(self.start, other.start) <= min(self.end, other.end)


@dataclass(frozen=True)
class Entry:
    """
    Simplified common representation for the documentable cxx entries
    """
    kind: str  # "function" | "class" | "field"
    name: str  # Entry name
    file: str  # Definition file name
    line_range: Range  # Full file range, including the body
    documented: bool  # Has documentation comment or docstring


def staged_changed_line_ranges(path: str) -> list[Range]:
    """
    Returns changed line ranges in the *new/staged* version of the file.
    Uses `-U0` to minimize context.
    """
    cmd = ["git", "diff", "--cached", "-U0", "--", path]
    p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if p.returncode not in (0, 1):
        raise RuntimeError(f"Command failed: {' '.join(cmd)}\n{p.stderr}")

    diff = p.stdout
    ranges: list[Range] = []
    for line in diff.splitlines():
        m = HUNK_RE.match(line)
        if not m:
            continue
        start = int(m.group(1))
        count = int(m.group(2) or "1")
        if count <= 0:
            ranges.append(Range(start, start))
        else:
            ranges.append(Range(start, start + count - 1))
    return ranges


# -----------------------
# Python checks (ast)
# -----------------------
def _py_prev_nonblank_line(lines: list[str], lineno_1based: int) -> Optional[str]:
    "Find previous non-blank line"
    i = lineno_1based - 2  # line above, 0-based
    while i >= 0:
        s = lines[i]
        if s.strip() != "":
            return s
        i -= 1
    return None


def _py_has_preceding_comment(lines: list[str], lineno_1based: int) -> bool:
    "Check if documentable range has comments before it"
    prev = _py_prev_nonblank_line(lines, lineno_1based)
    return bool(prev) and prev.lstrip().startswith("#")


def _py_has_inline_comment(lines: list[str], lineno_1based: int) -> bool:
    """
    Heuristic: treat any '#' on the assignment line as an inline doc comment.
    (Does not try to parse strings; good enough for a pre-commit gate.)
    """
    if lineno_1based <= 0 or lineno_1based > len(lines):
        return False
    line = lines[lineno_1based - 1]
    return "#" in line


def _py_has_following_string_doc(stmt: ast.stmt, next_stmt: Optional[ast.stmt]) -> bool:
    """
    Support the common "attribute docstring" pattern:

        x: int
        "doc for x"

    Requires the doc string literal statement to be the immediate next statement.
    """
    if next_stmt is None:
        return False
    if not isinstance(next_stmt, ast.Expr):
        return False
    val = next_stmt.value
    if not (isinstance(val, ast.Constant) and isinstance(val.value, str)):
        return False

    stmt_end = getattr(stmt, "end_lineno", None) or getattr(stmt, "lineno", None)
    next_line = getattr(next_stmt, "lineno", None)
    if stmt_end is None or next_line is None:
        return False
    return next_line == stmt_end + 1


def _py_is_pydantic_documented(stmt: ast.Assign | ast.AnnAssign) -> bool:
    """Return True if stmt assigns pydantic Field() with non-empty description."""
    value = stmt.value
    if not isinstance(value, ast.Call):
        return False

    func = value.func
    is_field = ((isinstance(func, ast.Name) and func.id == "Field") or
                (isinstance(func, ast.Attribute) and func.attr == "Field"))
    if not is_field:
        return False

    for kw in value.keywords:
        if kw.arg == "description":
            if isinstance(kw.value, ast.Constant):
                val = kw.value.value
                return isinstance(val, str) and bool(val.strip())
    return False


def python_entries(path: str, src: str) -> list[Entry]:
    "Recursively collect all documentable entries from python file"
    try:
        tree = ast.parse(src, filename=path, type_comments=True)
    except SyntaxError:
        return [Entry("file", "<parse error>", path, Range(1, 10**9), documented=False)]

    lines = src.splitlines()
    entries: list[Entry] = []

    def qualname(prefix: list[str], name: str) -> str:
        "Merge fully qualified python name"
        return ".".join(prefix + [name]) if prefix else name

    def emit(kind: str, name: str, node: ast.AST, documented: bool) -> None:
        "Store documentable entry information if it has associated line range"
        lineno = getattr(node, "lineno", None)
        end_lineno = getattr(node, "end_lineno", None)

        if lineno is None:
            return

        if end_lineno is None:
            end_lineno = lineno

        entries.append(
            Entry(kind=kind,
                  name=name,
                  file=path,
                  line_range=Range(lineno, end_lineno),
                  documented=documented))

    def visit(node: ast.AST, prefix: list[str]) -> None:
        "Recusirvely traverse the AST"
        # Handle node itself
        if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef)):
            doc = ast.get_docstring(node, clean=False)
            if node.name not in CAN_SKIP_DOCUMENTATION:
                emit("function",
                     qualname(prefix, node.name),
                     node,
                     documented=(doc is not None))

        elif isinstance(node, ast.ClassDef):
            doc = ast.get_docstring(node, clean=False)
            cls_name = qualname(prefix, node.name)
            emit("class", cls_name, node, documented=(doc is not None))

            # Class fields: Assign / AnnAssign directly in class body
            body = list(node.body)
            for i, stmt in enumerate(body):
                next_stmt = body[i + 1] if i + 1 < len(body) else None

                if isinstance(stmt, ast.Assign):
                    # support: a = 1; a = b = 1  (simple Name targets only)
                    field_names = [t.id for t in stmt.targets if isinstance(t, ast.Name)]
                    if not field_names:
                        continue

                    documented = (
                        _py_is_pydantic_documented(stmt) or
                        _py_has_inline_comment(lines,
                                               getattr(stmt, "lineno", 0) or 0) or
                        _py_has_preceding_comment(lines,
                                                  getattr(stmt, "lineno", 0) or 0) or
                        _py_has_following_string_doc(stmt, next_stmt))
                    for fn in field_names:
                        emit("field", f"{cls_name}.{fn}", stmt, documented=documented)

                elif isinstance(stmt, ast.AnnAssign):
                    # support: x: int = 1  /  x: int
                    t = stmt.target
                    if not isinstance(t, ast.Name):
                        continue
                    documented = (
                        _py_is_pydantic_documented(stmt) or
                        _py_has_inline_comment(lines,
                                               getattr(stmt, "lineno", 0) or 0) or
                        _py_has_preceding_comment(lines,
                                                  getattr(stmt, "lineno", 0) or 0) or
                        _py_has_following_string_doc(stmt, next_stmt))
                    emit("field", f"{cls_name}.{t.id}", stmt, documented=documented)

            # Recurse into nested content with updated prefix
            for child in ast.iter_child_nodes(node):
                visit(child, prefix + [node.name])
            return  # already recursed; don't fall through

        # Default recursion
        for child in ast.iter_child_nodes(node):
            visit(child, prefix)

    visit(tree, [])
    return entries


# -----------------------
# C++ checks (tree-sitter)
# -----------------------
def _configure_cpp_parser() -> Parser:
    "nodoc"
    return Parser(Language(tscpp.language()))


def _walk_ts(node) -> Iterable:
    "Recursively perform DFS walk of all the nodes and named subnodes."
    stack = [node]
    while stack:
        n = stack.pop()
        yield n
        stack.extend(reversed(getattr(n, "children", [])))


def _node_text(src_bytes: bytes, node) -> str:
    "Get full text representation of the documentable cxx entry"
    return src_bytes[node.start_byte:node.end_byte].decode("utf-8", errors="replace")


def _find_first_identifier(node, src_bytes: bytes) -> Optional[str]:
    "Attempt to find name of the documentable cxx entry"
    for n in _walk_ts(node):
        if n.type in ("identifier", "field_identifier", "type_identifier",
                      "namespace_identifier"):
            return _node_text(src_bytes, n)
    return None


def _has_leading_comment(lines: list[str], start_line_1based: int) -> bool:
    """
    Requires a comment block immediately above the declaration (no blank line).
    Accepts //... and /* ... */.
    """
    i = start_line_1based - 2  # line above start, 0-based index
    if i < 0:
        return False

    if lines[i].strip() == "":
        return False

    s = lines[i].lstrip()
    if s.startswith("//"):
        return True

    if "*/" in s:
        while i >= 0 and lines[i].strip() != "":
            if "/*" in lines[i]:
                return True
            i -= 1
        return False

    return False


def cpp_entries(path: str, src: str, parser: Parser) -> list[Entry]:
    "Collect documentable cxx entries, recursively for the whole file at once."
    src_bytes = src.encode("utf-8", errors="replace")
    tree = parser.parse(src_bytes)
    root = tree.root_node
    lines = src.splitlines()

    entries: list[Entry] = []

    def doc_anchor_node(n):
        "Find which node should be used as a reference point for documentation"
        p = getattr(n, "parent", None)
        if p is not None and p.type == "template_declaration":
            return p
        return n

    for n in _walk_ts(root):
        if n.type == "function_definition":
            decl = n.child_by_field_name("declarator")
            name = _find_first_identifier(decl, src_bytes) if decl else None
            name = name or "<anonymous>"
            dn = doc_anchor_node(n)
            start_line = dn.start_point[0] + 1
            end_line = dn.end_point[0] + 1
            documented = _has_leading_comment(lines, start_line)
            entries.append(
                Entry("function", name, path, Range(start_line, end_line), documented))

        elif n.type in ("declaration", "field_declaration"):
            decl = n.child_by_field_name("declarator")
            if decl is None:
                continue
            is_func_decl = any(x.type == "function_declarator" for x in _walk_ts(decl))
            if not is_func_decl:
                continue
            name = _find_first_identifier(decl, src_bytes) or "<anonymous>"
            dn = doc_anchor_node(n)
            start_line = dn.start_point[0] + 1
            end_line = dn.end_point[0] + 1
            documented = _has_leading_comment(lines, start_line)
            entries.append(
                Entry("function", name, path, Range(start_line, end_line), documented))

        elif n.type in ("class_specifier", "struct_specifier", "union_specifier"):
            name_node = n.child_by_field_name("name")
            name = _node_text(src_bytes, name_node) if name_node else "<anonymous>"
            dn = doc_anchor_node(n)
            start_line = dn.start_point[0] + 1
            end_line = dn.end_point[0] + 1
            documented = _has_leading_comment(lines, start_line)
            kind = "class" if n.type == "class_specifier" else (
                "struct" if n.type == "struct_specifier" else "union")
            entries.append(
                Entry(kind, name, path, Range(start_line, end_line), documented))

        elif n.type in ("enum_specifier", "enum_class_specifier"):
            name_node = n.child_by_field_name("name")
            name = _node_text(src_bytes, name_node) if name_node else "<anonymous>"
            dn = doc_anchor_node(n)
            start_line = dn.start_point[0] + 1
            end_line = dn.end_point[0] + 1
            documented = _has_leading_comment(lines, start_line)
            entries.append(
                Entry("enum", name, path, Range(start_line, end_line), documented))

    return entries


def relevant_file(path: str) -> bool:
    "Filter out files for validation"
    _, ext = os.path.splitext(path)
    return ext in PY_SUFFIXES or ext in CPP_SUFFIXES


def should_check_entry(entry: Entry, whole_file: bool,
                       change_ranges: list[Range]) -> bool:
    "Check if documentable entry intersects with the changed range"
    if whole_file:
        return True
    return any(entry.line_range.intersects(r) for r in change_ranges)


def parse_args(argv: list[str]) -> argparse.Namespace:
    "nodoc"
    ap = argparse.ArgumentParser(
        description=
        "Fail if new/changed (or all, in --whole-file mode) functions/classes are undocumented."
    )
    ap.add_argument(
        "--whole-file",
        action="store_true",
        help=
        "Ignore staged diff and validate the entire file for missing documentation/comments.",
    )
    ap.add_argument("files", nargs="*")
    return ap.parse_args(argv[1:])


def main(argv: list[str]) -> int:
    ns = parse_args(argv)
    files = [p for p in ns.files if relevant_file(p) and os.path.exists(p)]
    if not files:
        return 0

    cpp_parser = _configure_cpp_parser()
    problems: list[str] = []

    for path in files:
        src = Path(path).read_text()
        _, ext = os.path.splitext(path)

        if ext in PY_SUFFIXES:
            entries = python_entries(path, src)
        else:
            entries = cpp_entries(path, src, cpp_parser)

        change_ranges: list[Range] = []
        if not ns.whole_file:
            change_ranges = staged_changed_line_ranges(path)
            if not change_ranges:
                continue  # nothing staged changed => no checks in diff mode

        for e in entries:
            if e.documented:
                continue
            if should_check_entry(e, ns.whole_file, change_ranges):
                scope = "in file" if ns.whole_file else "changed in staged diff"
                problems.append(f"{e.file}:{e.line_range.start}-{e.line_range.end}: "
                                f"Undocumented {e.kind} '{e.name}' {scope}")

    if problems:
        sys.stderr.write(
            "ERROR: Functions/classes/fields/structs/unions/enums must be documented.\n"
            "Add a Python docstring (or field comment/doc literal) or a C++ comment block immediately above the declaration.\n\n"
        )

        sys.stderr.write("\n".join(problems) + "\n")
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
