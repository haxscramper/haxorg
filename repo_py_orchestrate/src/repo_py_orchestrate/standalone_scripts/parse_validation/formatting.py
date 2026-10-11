import json

from beartype import beartype
from beartype.typing import Sequence
from pydantic import JsonValue

from repo_py_orchestrate.standalone_scripts.parse_validation.models import (
    CaseKind,
    Counts,
    Outcome,
    TestCase,
)
from repo_py_orchestrate.standalone_scripts.parse_validation.pytest import (
    format_pytest_diagnostic,
)


@beartype
def count_cases(cases: Sequence[TestCase]) -> Counts:
    outcomes = {outcome: 0 for outcome in Outcome}

    for case in cases:
        outcomes[case.outcome] += 1

    return Counts(total=len(cases), outcomes=outcomes)


@beartype
def format_counts(counts: Counts) -> str:
    parts = [
        f"{outcome.value}={count}" for outcome, count in counts.outcomes.items() if count
    ]

    suffix = f", {', '.join(parts)}" if parts else ""
    return f"total={counts.total}{suffix}"


@beartype
def format_case_name(case: TestCase) -> str:
    if case.kind == CaseKind.COLLECTION:
        return f"[collection] {case.nodeid}"

    return case.nodeid


def format_value(value: JsonValue) -> str:
    if isinstance(value, str):
        return value

    return json.dumps(
        value,
        indent=2,
        ensure_ascii=False,
        sort_keys=True,
    )


def format_diagnostic(value: JsonValue) -> str:
    if isinstance(value, dict) and ("chain" in value or "reprtraceback" in value):
        return format_pytest_diagnostic(value)

    return format_value(value)


def case_extensions(case: TestCase) -> dict[str, JsonValue]:
    result: dict[str, JsonValue] = {}

    if case.metadata:
        result["metadata"] = case.metadata

    phases: list[JsonValue] = []

    for phase in case.phases:
        entry: dict[str, JsonValue] = {
            "phase": phase.phase.value,
        }

        if phase.extensions:
            entry["extensions"] = phase.extensions

        if phase.properties:
            entry["properties"] = [
                prop.model_dump(mode="json") for prop in phase.properties
            ]

        if 1 < len(entry):
            phases.append(entry)

    if phases:
        result["phases"] = phases

    return result


@beartype
def case_output(case: TestCase) -> list[tuple[str, str]]:
    result: list[tuple[str, str]] = []

    # Put every diagnostic before the captured output.
    for phase in case.phases:
        if phase.details is not None:
            content = format_diagnostic(phase.details)

            if content:
                result.append(
                    (
                        f"{phase.phase.value}: {phase.outcome.value}",
                        content,
                    )
                )

    # Pytest reports can repeat earlier phases' captured sections.
    seen_sections: set[tuple[str, str, str, str]] = set()

    for phase in case.phases:
        for section in phase.sections:
            content = format_value(section.content)
            key = (
                section.phase.value,
                section.channel.value,
                section.title,
                content,
            )

            if key in seen_sections:
                continue

            seen_sections.add(key)

            if content:
                result.append(
                    (
                        f"{section.title} "
                        f"[{section.channel.value}, "
                        f"{section.phase.value}]",
                        content,
                    )
                )

    return result
