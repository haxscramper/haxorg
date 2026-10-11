import argparse
import json
from datetime import UTC, datetime
from enum import StrEnum
from pathlib import Path

import dominate
from beartype import beartype
from beartype.typing import Sequence
from dominate import tags
from loguru import logger
from pydantic import BaseModel, ConfigDict, Field, JsonValue, TypeAdapter, ValidationError


class Framework(StrEnum):
    GTEST = "gtest"
    PYTEST = "pytest"


class CaseKind(StrEnum):
    TEST = "test"
    COLLECTION = "collection"


class Phase(StrEnum):
    COLLECTION = "collection"
    SETUP = "setup"
    CALL = "call"
    TEARDOWN = "teardown"


class Outcome(StrEnum):
    PASSED = "passed"
    FAILED = "failed"
    ERROR = "error"
    SKIPPED = "skipped"
    XFAILED = "xfailed"
    XPASSED = "xpassed"
    INCOMPLETE = "incomplete"


class PytestOutcome(StrEnum):
    PASSED = "passed"
    FAILED = "failed"
    SKIPPED = "skipped"


class Channel(StrEnum):
    STDOUT = "stdout"
    STDERR = "stderr"
    LOG = "log"
    CUSTOM = "custom"


class GtestStatus(StrEnum):
    RUN = "RUN"
    NOTRUN = "NOTRUN"


class GtestResult(StrEnum):
    COMPLETED = "COMPLETED"
    SKIPPED = "SKIPPED"
    SUPPRESSED = "SUPPRESSED"


class Section(BaseModel):
    title: str
    channel: Channel
    phase: Phase
    content: JsonValue


class Property(BaseModel):
    name: str
    value: JsonValue


class PhaseReport(BaseModel):
    phase: Phase
    outcome: Outcome
    duration: float = Field(default=0.0, ge=0)
    details: JsonValue = None
    sections: list[Section] = Field(default_factory=list)
    properties: list[Property] = Field(default_factory=list)
    extensions: dict[str, JsonValue] = Field(default_factory=dict)


class TestCase(BaseModel):
    nodeid: str
    kind: CaseKind = CaseKind.TEST
    outcome: Outcome = Outcome.INCOMPLETE
    phases: list[PhaseReport] = Field(default_factory=list)
    metadata: dict[str, JsonValue] = Field(default_factory=dict)

    @property
    @beartype
    def duration(self) -> float:
        return sum(phase.duration for phase in self.phases)


class TestRun(BaseModel):
    source: Path
    framework: Framework
    cases: list[TestCase] = Field(default_factory=list)
    events: list[dict[str, JsonValue]] = Field(default_factory=list)
    metadata: dict[str, JsonValue] = Field(default_factory=dict)
    exit_code: int | None = None


class Counts(BaseModel):
    total: int
    outcomes: dict[Outcome, int]


class Report(BaseModel):
    root: Path
    generated_at: datetime = Field(default_factory=lambda: datetime.now(UTC))
    runs: list[TestRun]
    tests: Counts
    collections: Counts


class PytestRecord(BaseModel):
    model_config = ConfigDict(extra="allow")

    nodeid: str
    outcome: PytestOutcome
    when: Phase | None = None
    duration: float = Field(default=0.0, ge=0)
    longrepr: JsonValue = None
    sections: list[tuple[str, str]] = Field(default_factory=list)
    user_properties: list[tuple[str, JsonValue]] = Field(default_factory=list)
    wasxfail: str | None = None


class PytestFileLocation(BaseModel):
    path: str
    lineno: int
    message: str


class PytestEntryData(BaseModel):
    lines: list[str]
    reprfuncargs: dict[str, list[tuple[str, str]]] | None = None
    reprlocals: dict[str, list[str]] | None = None
    reprfileloc: PytestFileLocation | None = None


class PytestTracebackEntry(BaseModel):
    data: PytestEntryData


class PytestTraceback(BaseModel):
    reprentries: list[PytestTracebackEntry]
    extraline: str | None = None


class PytestLongRepr(BaseModel):
    reprtraceback: PytestTraceback | None = None
    reprcrash: PytestFileLocation | None = None
    chain: list[tuple[PytestTraceback, PytestFileLocation | None, str | None]] | None = (
        None
    )
    sections: list[tuple[str, str, str]] = Field(default_factory=list)


class GtestFailure(BaseModel):
    model_config = ConfigDict(extra="allow")

    failure: str
    type: str = ""


class GtestCase(BaseModel):
    model_config = ConfigDict(extra="allow")

    name: str
    status: GtestStatus
    result: GtestResult = GtestResult.COMPLETED
    time: str
    failures: list[GtestFailure] = Field(default_factory=list)


class GtestSuite(BaseModel):
    model_config = ConfigDict(extra="allow")

    name: str
    testsuite: list[GtestCase] = Field(default_factory=list)


class GtestDocument(BaseModel):
    model_config = ConfigDict(extra="allow")

    testsuites: list[GtestSuite]


@beartype
def normalize_section(title: str, content: str, phase: Phase) -> Section:
    normalized = title.lower()

    if normalized.startswith("captured stdout"):
        channel = Channel.STDOUT
    elif normalized.startswith("captured stderr"):
        channel = Channel.STDERR
    elif normalized.startswith("captured log"):
        channel = Channel.LOG
    else:
        channel = Channel.CUSTOM

    if channel != Channel.CUSTOM:
        match normalized.rsplit(" ", 1)[-1]:
            case "setup":
                phase = Phase.SETUP
            case "call":
                phase = Phase.CALL
            case "teardown":
                phase = Phase.TEARDOWN

    return Section(
        title=title,
        channel=channel,
        phase=phase,
        content=content,
    )


@beartype
def pytest_outcome(record: PytestRecord, phase: Phase) -> Outcome:
    match record.outcome:
        case PytestOutcome.FAILED:
            if phase != Phase.CALL:
                return Outcome.ERROR
            return Outcome.FAILED

        case PytestOutcome.SKIPPED:
            if record.wasxfail is not None:
                return Outcome.XFAILED
            return Outcome.SKIPPED

        case PytestOutcome.PASSED:
            if record.wasxfail is not None and phase == Phase.CALL:
                return Outcome.XPASSED
            return Outcome.PASSED


@beartype
def overall_outcome(case: TestCase) -> Outcome:
    outcomes = {report.outcome for report in case.phases}

    for outcome in (
        Outcome.ERROR,
        Outcome.FAILED,
        Outcome.XPASSED,
        Outcome.XFAILED,
        Outcome.SKIPPED,
    ):
        if outcome in outcomes:
            return outcome

    expected_phase = Phase.COLLECTION if case.kind == CaseKind.COLLECTION else Phase.CALL

    if any(
        report.phase == expected_phase and report.outcome == Outcome.PASSED
        for report in case.phases
    ):
        return Outcome.PASSED

    return Outcome.INCOMPLETE


@beartype
def read_pytest(path: Path) -> TestRun:
    run = TestRun(source=path, framework=Framework.PYTEST)
    indexed: dict[tuple[CaseKind, str], TestCase] = {}
    adapter = TypeAdapter(dict[str, JsonValue])

    with path.open(encoding="utf-8") as stream:
        for line_number, line in enumerate(stream, start=1):
            if not line.strip():
                continue

            try:
                payload = adapter.validate_json(line)
                report_type = payload.get("$report_type")

                match report_type:
                    case "TestReport" | "CollectReport":
                        record = PytestRecord.model_validate(payload)

                        if report_type == "CollectReport":
                            kind = CaseKind.COLLECTION
                            phase = Phase.COLLECTION
                        else:
                            kind = CaseKind.TEST
                            if record.when not in (
                                Phase.SETUP,
                                Phase.CALL,
                                Phase.TEARDOWN,
                            ):
                                raise ValueError(
                                    f"TestReport for {record.nodeid!r} has "
                                    f"invalid phase {record.when!r}"
                                )
                            phase = record.when

                        key = (kind, record.nodeid)
                        if key not in indexed:
                            case = TestCase(nodeid=record.nodeid, kind=kind)
                            indexed[key] = case
                            run.cases.append(case)

                        extensions = adapter.validate_python(record.model_extra or {})
                        extensions.pop("$report_type", None)

                        if record.wasxfail is not None:
                            extensions["wasxfail"] = record.wasxfail

                        indexed[key].phases.append(
                            PhaseReport(
                                phase=phase,
                                outcome=pytest_outcome(record, phase),
                                duration=record.duration,
                                details=record.longrepr,
                                sections=[
                                    normalize_section(title, content, phase)
                                    for title, content in record.sections
                                ],
                                properties=[
                                    Property(name=name, value=value)
                                    for name, value in record.user_properties
                                ],
                                extensions=extensions,
                            )
                        )

                    case "SessionFinish":
                        run.events.append(payload)
                        exit_code = payload.get("exitstatus")
                        if exit_code is not None:
                            run.exit_code = TypeAdapter(int).validate_python(exit_code)

                    case _:
                        run.events.append(payload)

            except (ValidationError, ValueError) as error:
                raise ValueError(
                    f"Invalid pytest report record at {path}:{line_number}: {error}"
                ) from error

    for case in run.cases:
        case.outcome = overall_outcome(case)

    return run


@beartype
def gtest_outcome(case: GtestCase) -> Outcome:
    if case.failures:
        return Outcome.FAILED

    if case.status == GtestStatus.NOTRUN or case.result in (
        GtestResult.SKIPPED,
        GtestResult.SUPPRESSED,
    ):
        return Outcome.SKIPPED

    return Outcome.PASSED


@beartype
def read_gtest(path: Path) -> TestRun:
    try:
        document = GtestDocument.model_validate_json(path.read_text(encoding="utf-8"))
    except ValidationError as error:
        raise ValueError(f"Invalid Google Test report at {path}: {error}") from error

    run = TestRun(
        source=path,
        framework=Framework.GTEST,
        metadata=document.model_dump(
            mode="json",
            exclude={"testsuites"},
        ),
    )

    for suite in document.testsuites:
        suite_metadata = suite.model_dump(
            mode="json",
            exclude={"testsuite"},
        )

        for record in suite.testsuite:
            if not record.time.endswith("s"):
                raise ValueError(
                    f"Invalid duration {record.time!r} for "
                    f"{suite.name}.{record.name} in {path}; "
                    f"expected seconds followed by 's'"
                )

            outcome = gtest_outcome(record)
            details = "\n\n".join(
                f"{failure.type}: {failure.failure}" if failure.type else failure.failure
                for failure in record.failures
            )

            run.cases.append(
                TestCase(
                    nodeid=f"{suite.name}.{record.name}",
                    outcome=outcome,
                    metadata={"suite": suite_metadata},
                    phases=[
                        PhaseReport(
                            phase=Phase.CALL,
                            outcome=outcome,
                            duration=float(record.time.removesuffix("s")),
                            details=details or None,
                            extensions=record.model_dump(
                                mode="json",
                                exclude={"time"},
                            ),
                        )
                    ],
                )
            )

    return run


@beartype
def count_cases(cases: Sequence[TestCase]) -> Counts:
    outcomes = {outcome: 0 for outcome in Outcome}
    for case in cases:
        outcomes[case.outcome] += 1
    return Counts(total=len(cases), outcomes=outcomes)


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


def format_value(value: JsonValue) -> str:
    if isinstance(value, str):
        return value

    else:
        return json.dumps(value, indent=2, ensure_ascii=False, sort_keys=True)


def format_diagnostic(value: JsonValue) -> str:
    if not isinstance(value, dict):
        return format_value(value)

    if "chain" not in value and "reprtraceback" not in value:
        return format_value(value)

    representation = PytestLongRepr.model_validate(value)
    parts: list[str] = []

    chain = representation.chain
    if chain is None:
        chain = []
        if representation.reprtraceback is not None:
            chain.append(
                (
                    representation.reprtraceback,
                    representation.reprcrash,
                    None,
                )
            )

    for traceback, crash, description in chain:
        for entry in traceback.reprentries:
            data = entry.data

            if data.reprfuncargs:
                arguments = data.reprfuncargs.get("args", [])
                if arguments:
                    parts.append(
                        ", ".join(f"{name} = {argument}" for name, argument in arguments)
                    )

            parts.append("\n".join(data.lines))

            if data.reprlocals:
                parts.append("\n".join(data.reprlocals.get("lines", [])))

            if data.reprfileloc is not None:
                location = data.reprfileloc
                parts.append(f"{location.path}:{location.lineno}: {location.message}")

        if traceback.extraline:
            parts.append(traceback.extraline)

        if crash is not None:
            parts.append(f"{crash.path}:{crash.lineno}: {crash.message}")

        if description:
            parts.append(description)

    for title, content, separator in representation.sections:
        parts.append(f"{separator * 8} {title} {separator * 8}\n{content}")

    return "\n\n".join(part for part in parts if part)


@beartype
def format_counts(counts: Counts) -> str:
    parts = [
        f"{outcome.value}={count}" for outcome, count in counts.outcomes.items() if count
    ]
    return f"total={counts.total}" + (f", {', '.join(parts)}" if parts else "")


@beartype
def render_text(report: Report) -> str:
    lines = [
        "Aggregated test report",
        f"Generated: {report.generated_at.isoformat()}",
        f"Root: {report.root}",
        f"Tests: {format_counts(report.tests)}",
        f"Collections: {format_counts(report.collections)}",
    ]

    for run in report.runs:
        lines.extend(
            [
                "",
                f"Source: {run.source.relative_to(report.root)}",
                f"Framework: {run.framework.value}",
            ]
        )

        if run.exit_code is not None:
            lines.append(f"Session exit code: {run.exit_code}")

        if run.metadata:
            lines.extend(["Run metadata:", format_value(run.metadata)])

        for case in run.cases:
            lines.extend(
                [
                    "",
                    (
                        f"[{case.outcome.value}] "
                        f"{case.kind.value}: {case.nodeid} "
                        f"({case.duration:.6f}s)"
                    ),
                ]
            )

            if case.metadata:
                lines.extend(["Case metadata:", format_value(case.metadata)])

            for phase in case.phases:
                lines.append(
                    f"  {phase.phase.value}: {phase.outcome.value} "
                    f"({phase.duration:.6f}s)"
                )

                if phase.details is not None:
                    lines.extend(["  Details:", format_diagnostic(phase.details)])

                for section in phase.sections:
                    lines.extend(
                        [
                            (
                                f"  Section: {section.title} "
                                f"[{section.channel.value}, "
                                f"{section.phase.value}]"
                            ),
                            format_value(section.content),
                        ]
                    )

                for prop in phase.properties:
                    lines.extend(
                        [
                            f"  Property: {prop.name}",
                            format_value(prop.value),
                        ]
                    )

                if phase.extensions:
                    lines.extend(
                        [
                            "  Report extensions:",
                            format_value(phase.extensions),
                        ]
                    )

        if run.events:
            lines.extend(["", "Session events:", format_value(run.events)])

    return "\n".join(lines) + "\n"


def html_payload(title: str, value: JsonValue) -> None:
    with tags.details():
        tags.summary(title)
        tags.pre(format_value(value))


@beartype
def html_case(case: TestCase) -> None:
    expanded = case.outcome in (
        Outcome.FAILED,
        Outcome.ERROR,
        Outcome.XPASSED,
        Outcome.INCOMPLETE,
    )

    attributes = {"cls": f"case {case.outcome.value}"}
    if expanded:
        attributes["open"] = "open"

    with tags.details(**attributes):
        tags.summary(
            f"[{case.outcome.value}] "
            f"{case.kind.value}: {case.nodeid} "
            f"({case.duration:.6f}s)"
        )

        if case.metadata:
            html_payload("Case metadata", case.metadata)

        for phase in case.phases:
            with tags.div(cls="phase"):
                tags.h4(
                    f"{phase.phase.value}: {phase.outcome.value} ({phase.duration:.6f}s)"
                )

                if phase.details is not None:
                    tags.pre(format_diagnostic(phase.details), cls="diagnostic")

                for section in phase.sections:
                    with tags.details():
                        tags.summary(
                            f"{section.title} "
                            f"[{section.channel.value}, "
                            f"{section.phase.value}]"
                        )
                        tags.pre(format_value(section.content))

                for prop in phase.properties:
                    html_payload(f"Property: {prop.name}", prop.value)

                if phase.extensions:
                    html_payload("Report extensions", phase.extensions)


@beartype
def render_html(report: Report) -> str:
    document = dominate.document(title="Aggregated test report")

    with document.head:
        tags.meta(charset="utf-8")
        tags.meta(
            name="viewport",
            content="width=device-width, initial-scale=1",
        )
        tags.style(
            """
            :root { color-scheme: light dark; }
            body {
                font-family: system-ui, sans-serif;
                max-width: 1100px;
                margin: 2rem auto;
                padding: 0 1rem;
            }
            table { border-collapse: collapse; margin: 1rem 0; }
            th, td {
                border: 1px solid GrayText;
                padding: .4rem .7rem;
                text-align: left;
            }
            details { margin: .6rem 0; }
            summary { cursor: pointer; overflow-wrap: anywhere; }
            .case { border-left: 4px solid GrayText; padding-left: .8rem; }
            .failed, .error { border-left-color: Crimson; }
            .xpassed, .incomplete { border-left-color: DarkOrange; }
            .passed { border-left-color: SeaGreen; }
            .phase { margin-left: 1rem; }
            pre {
                white-space: pre;
                overflow: auto;
                max-height: 40rem;
                overflow-wrap: normal;
                tab-size: 4;
                font-family: monospace;
                font-size: .875rem;
                line-height: 1.45;
            }
            """
        )

    with document:
        tags.h1("Aggregated test report")
        tags.p(f"Generated: {report.generated_at.isoformat()}")
        tags.p(f"Root: {report.root}")

        with tags.table():
            with tags.thead():
                with tags.tr():
                    tags.th("Kind")
                    tags.th("Total")
                    for outcome in Outcome:
                        tags.th(outcome.value)

            with tags.tbody():
                for label, counts in (
                    ("Tests", report.tests),
                    ("Collections", report.collections),
                ):
                    with tags.tr():
                        tags.td(label)
                        tags.td(str(counts.total))
                        for outcome in Outcome:
                            tags.td(str(counts.outcomes[outcome]))

        for run in report.runs:
            with tags.section():
                tags.h2(str(run.source.relative_to(report.root)))
                tags.p(f"Framework: {run.framework.value}")

                if run.exit_code is not None:
                    tags.p(f"Session exit code: {run.exit_code}")

                if run.metadata:
                    html_payload("Run metadata", run.metadata)

                for case in run.cases:
                    html_case(case)

                if run.events:
                    html_payload("Session events", run.events)

    return document.render()


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

    text_path.write_text(render_text(report), encoding="utf-8")
    html_path.write_text(render_html(report), encoding="utf-8")

    logger.info(f"Wrote text report to {text_path}")
    logger.info(f"Wrote HTML report to {html_path}")


if __name__ == "__main__":
    main()
