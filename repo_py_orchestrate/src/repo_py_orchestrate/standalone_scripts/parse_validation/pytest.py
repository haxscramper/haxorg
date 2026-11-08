from pathlib import Path

from beartype import beartype
from pydantic import JsonValue, TypeAdapter, ValidationError

from .models import (
    CaseKind,
    Channel,
    Framework,
    Outcome,
    Phase,
    PhaseReport,
    Property,
    PytestLongRepr,
    PytestOutcome,
    PytestRecord,
    Section,
    TestCase,
    TestRun,
)


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

    raise ValueError(f"Unsupported pytest outcome: {record.outcome!r}")


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
    exit_code_adapter = TypeAdapter(int)

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
                            case = TestCase(
                                nodeid=record.nodeid,
                                kind=kind,
                            )
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
                            run.exit_code = exit_code_adapter.validate_python(exit_code)

                    case _:
                        run.events.append(payload)

            except (ValidationError, ValueError) as error:
                raise ValueError(
                    f"Invalid pytest report record at {path}:{line_number}: {error}"
                ) from error

    for case in run.cases:
        case.outcome = overall_outcome(case)

    return run


def format_pytest_diagnostic(value: dict[str, JsonValue]) -> str:
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
