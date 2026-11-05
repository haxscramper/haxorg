import argparse
from pathlib import Path

from beartype import beartype
from loguru import logger

from repo_py_orchestrate.standalone_scripts.parse_validation.format_html import (
    render_html,
)
from repo_py_orchestrate.standalone_scripts.parse_validation.format_text import (
    render_text,
)
from repo_py_orchestrate.standalone_scripts.parse_validation.formatting import count_cases
from repo_py_orchestrate.standalone_scripts.parse_validation.gtest import read_gtest
from repo_py_orchestrate.standalone_scripts.parse_validation.models import (
    CaseKind,
    Report,
)
from repo_py_orchestrate.standalone_scripts.parse_validation.pytest import read_pytest


@beartype
def aggregate(root: Path) -> Report:
    if not root.is_dir():
        raise NotADirectoryError(
            f"Test results directory does not exist or is not a directory: {root}"
        )

    patterns = (
        "**/gtest_results/*.json",
        "**/conan_pytest.jsonl",
        "**/package_tests.jsonl",
    )

    sources = sorted(
        {path for pattern in patterns for path in root.glob(pattern) if path.is_file()}
    )

    if not sources:
        raise FileNotFoundError(
            f"No test reports found under {root}; "
            f"searched patterns: {', '.join(patterns)}"
        )

    runs = [
        read_gtest(path) if path.suffix == ".json" else read_pytest(path)
        for path in sources
    ]
    cases = [case for run in runs for case in run.cases]

    return Report(
        root=root,
        runs=runs,
        tests=count_cases([case for case in cases if case.kind == CaseKind.TEST]),
        collections=count_cases(
            [case for case in cases if case.kind == CaseKind.COLLECTION]
        ),
    )


@beartype
def main() -> None:
    parser = argparse.ArgumentParser(
        description="Aggregate Google Test and pytest-reportlog results."
    )
    parser.add_argument("root", type=Path)
    parser.add_argument("--output", type=Path)
    arguments = parser.parse_args()

    root = arguments.root.resolve()
    output = (
        arguments.output.resolve()
        if arguments.output is not None
        else root / "aggregated-report"
    )

    report = aggregate(root)
    output.mkdir(parents=True, exist_ok=True)

    text_path = output / "report.txt"
    html_path = output / "report.html"

    text_path.write_text(
        render_text(report),
        encoding="utf-8",
    )
    html_path.write_text(
        render_html(report),
        encoding="utf-8",
    )

    logger.info(f"Wrote text report to {text_path}")
    logger.info(f"Wrote HTML report to {html_path}")


if __name__ == "__main__":
    main()
