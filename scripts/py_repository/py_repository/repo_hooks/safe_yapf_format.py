#!/usr/bin/env python
from __future__ import annotations

import io
import re
import subprocess
import sys
import tokenize
from dataclasses import dataclass
from pathlib import Path
import base64
import ast

_PLACEHOLDER_PREFIX = "__safe_yapf_type_alias__"


@dataclass(frozen=True)
class _LineRange:
    start_line: int  # 1-based, inclusive
    end_line: int  # 1-based, inclusive


def _find_type_alias_statement_ranges(src: str) -> list[_LineRange]:
    paren_level = 0
    at_logical_line_start = True
    type_stmt_start_line: int | None = None
    ranges: list[_LineRange] = []

    tokens = tokenize.generate_tokens(io.StringIO(src).readline)
    for tok in tokens:
        ttype = tok.type
        tstring = tok.string

        if ttype == tokenize.OP:
            if tstring in "([{":
                paren_level += 1
            elif tstring in ")]}":
                paren_level -= 1
            elif tstring == ";" and paren_level == 0:
                if type_stmt_start_line is not None:
                    ranges.append(_LineRange(type_stmt_start_line, tok.start[0]))
                    type_stmt_start_line = None
                at_logical_line_start = True
                continue

        if ttype == tokenize.NL:
            continue

        if ttype == tokenize.NEWLINE and paren_level == 0:
            if type_stmt_start_line is not None:
                ranges.append(_LineRange(type_stmt_start_line, tok.start[0]))
                type_stmt_start_line = None
            at_logical_line_start = True
            continue

        if ttype in (tokenize.INDENT, tokenize.DEDENT):
            at_logical_line_start = True
            continue

        if at_logical_line_start and paren_level == 0 and ttype == tokenize.NAME and tstring == "type":
            type_stmt_start_line = tok.start[0]
            at_logical_line_start = False
            continue

        at_logical_line_start = False

    return ranges


_ws_re = re.compile(r"^(\s*)(.*)$")
_restore_re = re.compile(r"^(\s*)#\s*" + re.escape(_PLACEHOLDER_PREFIX) +
                         r"(?:\s(.*)|\s*)$")


def _dedent_by_prefix(block: str, prefix: str) -> str:
    out: list[str] = []
    for line in block.splitlines(keepends=True):
        if line.startswith(prefix):
            out.append(line[len(prefix):])
        else:
            out.append(line)
    return "".join(out)


def _indent_block(block: str, indent: str) -> str:
    out: list[str] = []
    for line in block.splitlines(keepends=True):
        if line in ("\n", "\r\n"):
            out.append(line)
        else:
            out.append(indent + line)
    return "".join(out)


def _rewrite_type_aliases_to_placeholders(src: str) -> tuple[str, bool]:
    ranges = _find_type_alias_statement_ranges(src)
    if not ranges:
        return src, False

    lines = src.splitlines(keepends=True)

    # Apply from bottom to top so line indices remain valid while editing
    for idx, r in reversed(list(enumerate(ranges))):
        original_block = "".join(lines[r.start_line - 1:r.end_line])

        first_line = lines[r.start_line - 1]
        indent = first_line[:len(first_line) - len(first_line.lstrip())]

        payload_block = _dedent_by_prefix(original_block, indent)
        payload_b64 = base64.b64encode(payload_block.encode("utf-8")).decode("ascii")

        placeholder_line = f"{indent}{_PLACEHOLDER_PREFIX}{idx} = {payload_b64!r}\n"
        lines[r.start_line - 1:r.end_line] = [placeholder_line]

    return "".join(lines), True


def _restore_type_aliases_from_placeholders(src: str) -> str:
    tree = ast.parse(src)
    lines = src.splitlines(keepends=True)

    replacements: list[tuple[int, int, str]] = []
    for node in ast.walk(tree):
        if not isinstance(node, ast.Assign):
            continue
        if len(node.targets) != 1 or not isinstance(node.targets[0], ast.Name):
            continue

        name = node.targets[0].id
        if not name.startswith(_PLACEHOLDER_PREFIX):
            continue

        if not (hasattr(node, "end_lineno") and node.end_lineno is not None):
            raise RuntimeError("AST nodes missing end position information")

        if not isinstance(node.value, ast.Constant) or not isinstance(
                node.value.value, str):
            raise RuntimeError(f"Unexpected placeholder value form for {name}")

        start_line = node.lineno
        end_line = node.end_lineno

        line0 = lines[start_line - 1]
        indent = line0[:node.col_offset]

        payload_b64 = node.value.value
        payload_block = base64.b64decode(payload_b64.encode("ascii")).decode("utf-8")
        restored_block = _indent_block(payload_block, indent)

        replacements.append((start_line, end_line, restored_block))

    # Replace bottom-up so earlier indices are unaffected
    replacements.sort(key=lambda x: x[0], reverse=True)
    for start_line, end_line, restored_block in replacements:
        lines[start_line - 1:end_line] = restored_block.splitlines(keepends=True)

    return "".join(lines)


def main(argv: list[str]) -> int:
    files = [Path(a) for a in argv[1:]]
    if not files:
        return 0

    for path in files:
        original_src = path.read_text(encoding="utf-8")
        rewritten_src, changed = _rewrite_type_aliases_to_placeholders(original_src)

        try:
            if changed:
                path.write_text(rewritten_src, encoding="utf-8")

            print(f"safe_yapf_format: formatting {path}", file=sys.stderr, flush=True)
            subprocess.run(["yapf", "-i", str(path)], check=True)

            if changed:
                formatted = path.read_text(encoding="utf-8")
                restored = _restore_type_aliases_from_placeholders(formatted)
                path.write_text(restored, encoding="utf-8")

        except Exception:
            if changed:
                path.write_text(original_src, encoding="utf-8")
            raise

    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
