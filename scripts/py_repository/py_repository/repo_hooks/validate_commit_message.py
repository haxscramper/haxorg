#!/usr/bin/env python
"""
commit-msg hook: validate commit message format.

Rules:
- Subject must start with an allowed prefix (optionally with "(scope)") and ":".
  Example:  py(parser): fix tokenization
            cxx: speed up lexer
- Subject length <= 50 chars
- Commit must have a body (non-empty text after a blank line)
- Body lines length <= 75 chars
  - EXCEPTION: lines inside Markdown triple-backtick code fences (``` ... ```)
    are ignored and may be any length.

If subject formatting is wrong, prints allowed prefixes with descriptions.
"""

from __future__ import annotations

import logging
from pathlib import Path
import re
import sys

logging.basicConfig(
    level=logging.DEBUG,
    format="%(levelname)s %(filename)s:%(lineno)d: %(message)s",
)

log = logging.getLogger(__name__)

PREFIXES: dict[str, str] = {
    "build": "Build system changes (CMake, tasks, dependencies)",
    "ci": "Continuous integration, Docker, packaging",
    "cli": "Command-line interface and entry points",
    "codegen": "Code generation (reflection, bindings)",
    "cov": "Coverage collection and reporting",
    "cxx": "C++ core, parser, lexer, stdlib",
    "debug": "Debugging, logging, tracing (absl logging; tracing flags in CMake)",
    "doc": "Documentation generation or updates",
    "editor": "Editor integrations or editor-specific features",
    "ex": "Examples",
    "export": "Export pipelines (HTML, Tex, Pandoc, etc.)",
    "gen": "General generation tasks (e.g., sources)",
    "gui": "GUI components (Qt/imgui examples)",
    "hstd": "hstd library (C++ utilities)",
    "js": "JavaScript bindings",
    "lex": "Lexer implementation",
    "mmap": "Mind map/org graph handling",
    "org": "Org-mode parser/AST core",
    "parse": "Parsing pipeline (lexer → parser → sem)",
    "py": "Python bindings, scripts, tests",
    "refactor": "Refactoring commits",
    "refl": "Reflection system (code generation)",
    "repo": "Repository-level configuration, workflow script",
    "report": "Reporting outputs (coverage, docs)",
    "sem": "Semantic analysis phase",
    "test": "Test suites, corpus, CI tests",
}

_ALLOWED_PREFIXES_CASEFOLD = {k.casefold(): k for k in PREFIXES.keys()}

SUBJECT_MAX = 50
BODY_LINE_MAX = 75

SUBJECT_RE = re.compile(
    r"""^
        (?P<prefix>[A-Za-z][A-Za-z0-9_-]*)
        (?:\([^)]+\))?
        :
        \s+
        \S.*$
    """,
    re.VERBOSE,
)


def save_failed_message(msg_path: Path) -> Path:
    bak = msg_path.with_name(msg_path.name + ".failed")
    bak.write_text(msg_path.read_text(encoding="utf-8", errors="replace"),
                   encoding="utf-8")
    log.warning(f"saved your commit message to: {bak}")
    return bak


def strip_comments(lines: list[str]) -> list[str]:
    return [ln.rstrip("\n") for ln in lines if not ln.lstrip().startswith("#")]


def print_prefix_table() -> None:
    log.info("")
    log.info("Allowed prefixes:")
    width = max(len(k) for k in PREFIXES)
    for k in sorted(PREFIXES.keys(), key=lambda s: (s.casefold(), s)):
        log.info(f"  {k.ljust(width)}  {PREFIXES[k]}")


def is_fence_line(line: str) -> bool:
    # Markdown triple-backtick fence, optionally indented and with a language tag.
    return line.lstrip().startswith("```")


def main() -> int:
    if len(sys.argv) != 2:
        log.error("usage: commit-msg <path-to-commit-message-file>")
        return 2

    msg_path = Path(sys.argv[1])
    raw_lines = msg_path.read_text(encoding="utf-8", errors="replace").splitlines(True)
    lines = strip_comments(raw_lines)

    subject_idx = None
    for i, ln in enumerate(lines):
        if ln.strip():
            subject_idx = i
            break

    if subject_idx is None:
        log.error("error: empty commit message")
        return 1

    subject = lines[subject_idx]

    if subject.startswith("Merge "):
        return 0

    if len(subject) > SUBJECT_MAX:
        log.error(f"error: subject line too long ({len(subject)} > {SUBJECT_MAX})")
        log.error(f"subject: {subject}")
        save_failed_message(msg_path)
        return 1

    m = SUBJECT_RE.match(subject)
    if not m:
        log.error("error: subject must match: <prefix>(<scope>): <summary>")
        log.error("example: py(parser): fix tokenization")
        log.error(f"subject: {subject}")
        print_prefix_table()
        save_failed_message(msg_path)
        return 1

    prefix = m.group("prefix").casefold()
    if prefix not in _ALLOWED_PREFIXES_CASEFOLD:
        log.error(f"error: invalid prefix '{m.group('prefix')}'")
        log.error("expected one of the allowed prefixes below.")
        print_prefix_table()
        save_failed_message(msg_path)
        return 1

    # Body requirement: must have blank line after subject, then non-empty body text.
    rest = lines[subject_idx + 1:]

    try:
        blank_pos = next(i for i, ln in enumerate(rest) if ln.strip() == "")
    except StopIteration:
        log.error("error: commit must have a body separated by a blank line")
        log.error("hint: add an empty line after the subject, then body text")
        save_failed_message(msg_path)
        return 1

    body_lines = rest[blank_pos + 1:]
    if not any(ln.strip() for ln in body_lines):
        log.error("error: commit must have a non-empty body")
        save_failed_message(msg_path)
        return 1

    # Enforce body line length, except inside ``` fences.
    in_fence = False
    for idx, ln in enumerate(body_lines, start=1):
        if is_fence_line(ln):
            in_fence = not in_fence
            continue

        if in_fence:
            continue

        if not ln.strip():
            continue

        if len(ln) > BODY_LINE_MAX:
            log.error(f"error: body line {idx} too long ({len(ln)} > {BODY_LINE_MAX})")
            log.error(f"line: {ln}")
            save_failed_message(msg_path)
            return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
