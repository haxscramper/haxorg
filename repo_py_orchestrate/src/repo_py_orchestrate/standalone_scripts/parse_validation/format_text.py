from beartype import beartype

from .formatting import (
    case_extensions,
    case_output,
    format_case_name,
    format_counts,
    format_duration,
    format_value,
)
from .models import Report


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
        source = run.source.relative_to(report.root)

        lines.extend(
            [
                "",
                f"{source} ({run.framework.value})",
            ]
        )

        if run.exit_code is not None:
            lines.append(f"Exit code: {run.exit_code}")

        for case in run.cases:
            lines.extend(
                [
                    "",
                    (
                        f"[{case.outcome.value}] "
                        f"{format_case_name(case)} "
                        f"— {format_duration(case.duration)}"
                    ),
                ]
            )

            for title, content in case_output(case):
                lines.extend(
                    [
                        f"{title}:",
                        content,
                    ]
                )

            extensions = case_extensions(case)

            if extensions:
                lines.extend(
                    [
                        "Extensions:",
                        format_value(extensions),
                    ]
                )

        if run.metadata:
            lines.extend(
                [
                    "",
                    "Run metadata:",
                    format_value(run.metadata),
                ]
            )

        if run.events:
            lines.extend(
                [
                    "",
                    "Session events:",
                    format_value(run.events),
                ]
            )

    return "\n".join(lines) + "\n"
