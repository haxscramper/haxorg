#!/usr/bin/env python

import argparse
import re
import shlex
import sys
from pathlib import Path


ANSI_ESCAPE_RE = re.compile(r"\x1b\[[0-?]*[ -/]*[@-~]")
CONAN_CREATE_RE = re.compile(r"(?:^|\s)conan\s+create\s+")
SOURCES_IN_RE = re.compile(r"^\s*Sources in (.+?)\s*$")


def strip_ansi(text: str) -> str:
    return ANSI_ESCAPE_RE.sub("", text)


def find_path_replacements(log: str) -> list[tuple[str, str]]:
    replacements: list[tuple[str, str]] = []
    current_source: str | None = None

    for raw_line in log.splitlines():
        line = strip_ansi(raw_line)

        create_match = CONAN_CREATE_RE.search(line)
        if create_match:
            command = line[create_match.start() :].lstrip()
            arguments = shlex.split(command)

            if len(arguments) < 3:
                raise RuntimeError(f"Malformed conan create command: {line}")

            current_source = arguments[2]
            continue

        sources_match = SOURCES_IN_RE.match(line)
        if sources_match and current_source is not None:
            conan_source = sources_match.group(1)
            replacement = (conan_source, current_source)

            if replacement not in replacements:
                replacements.append(replacement)

            current_source = None

    if not replacements:
        raise RuntimeError(
            "Could not find a matching 'conan create' command and 'Sources in ...' line"
        )

    return replacements


def replace_paths(log: str, replacements: list[tuple[str, str]]) -> str:
    for conan_source, original_source in sorted(
        replacements,
        key=lambda item: len(item[0]),
        reverse=True,
    ):
        log = log.replace(conan_source, original_source)

    return log


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Replace Conan cache source paths with original source paths"
    )
    parser.add_argument("log", type=Path, help="Conan output log")
    arguments = parser.parse_args()
    log = arguments.log.read_text()
    replacements = find_path_replacements(log)
    log = replace_paths(log, replacements)
    arguments.log.write_text(log)


if __name__ == "__main__":
    main()
