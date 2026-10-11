from datetime import timedelta
from pathlib import Path

import dominate
from beartype import beartype
from dominate import tags
from dominate.dom_tag import dom_tag
from dominate.util import raw
from hstd_py_lib.format_utils import format_readable_duration
from pydantic import JsonValue

from repo_py_orchestrate.standalone_scripts.parse_validation.formatting import (
    case_extensions,
    case_output,
    format_case_name,
    format_counts,
    format_value,
)
from repo_py_orchestrate.standalone_scripts.parse_validation.models import (
    Outcome,
    Report,
    TestCase,
    TestRun,
)


class template(dom_tag):
    """HTML template element."""


def html_payload(title: str, value: JsonValue) -> None:
    tags.h3(title)
    tags.pre(format_value(value))


@beartype
def html_action(label: str, template_id: str, case_name: str) -> None:
    with tags.td(cls="action-cell"):  # type: ignore
        tags.button(
            label,
            type="button",
            cls="action",
            data_template=template_id,
            aria_pressed="false",
            aria_controls="detail-content",
            aria_label=f"Show {label.lower()} for {case_name}",
        )


@beartype
def html_detail_templates(
    index: int,
    run: TestRun,
    case: TestCase,
    source: str,
) -> None:
    name = format_case_name(case)

    with template(id=f"extensions-{index}"):
        tags.h2(f"Extensions — {name}")
        tags.p(
            f"{run.framework.value} · {source}",
            cls="muted",
        )

        extensions = case_extensions(case)

        if extensions:
            html_payload("Test extensions", extensions)

        if run.metadata:
            html_payload("Run metadata", run.metadata)

        if run.exit_code is not None:
            tags.p(f"Session exit code: {run.exit_code}")

        if run.events:
            html_payload("Session events", run.events)

        if not extensions and not run.metadata and not run.events:
            tags.p("No extension information.")

    with template(id=f"output-{index}"):
        tags.h2(f"Output — {name}")
        tags.p(
            f"{run.framework.value} · {source}",
            cls="muted",
        )

        output = case_output(case)

        if output:
            for title, content in output:
                tags.h3(title)
                tags.pre(content)
        else:
            tags.p("No error or captured output.")


@beartype
def render_html(report: Report) -> str:
    document = dominate.document(title="Aggregated test report")

    rows = [
        (
            run,
            case,
            str(run.source.relative_to(report.root)),
        )
        for run in report.runs
        for case in run.cases
    ]

    outcome_order = {
        Outcome.ERROR: 0,
        Outcome.FAILED: 1,
        Outcome.XPASSED: 2,
        Outcome.SKIPPED: 3,
        Outcome.XFAILED: 4,
        Outcome.PASSED: 5,
        Outcome.INCOMPLETE: 6,
    }

    rows: list[tuple[TestRun, TestCase, str]] = sorted(
        rows, key=lambda it: outcome_order[it[1].outcome]
    )

    with document.head:
        tags.meta(charset="utf-8")
        tags.meta(
            name="viewport",
            content="width=device-width, initial-scale=1",
        )
        tags.style(raw(Path(__file__).with_suffix(".css").read_text()))

    with document:
        tags.h1("Aggregated test report")
        tags.p(f"Tests: {format_counts(report.tests)}")
        tags.p(f"Collections: {format_counts(report.collections)}")
        tags.p(
            f"Generated: {report.generated_at.isoformat()} · Root: {report.root}",
            cls="muted",
        )

        with tags.div(cls="layout"):  # type: ignore
            with tags.div(cls="table-panel"):  # type: ignore
                with tags.table(id="results"):  # type: ignore
                    with tags.colgroup():  # type: ignore
                        tags.col(cls="state-column")
                        tags.col(cls="origin-column")
                        tags.col(cls="name-column")
                        tags.col(cls="time-column")
                        tags.col()
                        tags.col()

                    with tags.thead():  # type: ignore
                        with tags.tr():  # type: ignore
                            tags.th("State", scope="col")
                            tags.th("Origin", scope="col")
                            tags.th("Test name", scope="col")
                            tags.th("Time", scope="col")
                            tags.th("Extensions", scope="col")
                            tags.th("Output", scope="col")

                    with tags.tbody():  # type: ignore
                        for index, (run, case, source) in enumerate(rows):
                            name = format_case_name(case)

                            with tags.tr():  # type: ignore
                                tags.td(
                                    case.outcome.value,
                                    cls=f"state {case.outcome.value}",
                                )
                                tags.td(run.framework.value)
                                tags.td(
                                    name,
                                    cls="test-name",
                                    title=source,
                                )
                                tags.td(
                                    format_readable_duration(
                                        timedelta(seconds=case.duration)
                                    ),
                                    cls="time",
                                )

                                html_action(
                                    "Extensions",
                                    f"extensions-{index}",
                                    name,
                                )
                                html_action(
                                    "Output",
                                    f"output-{index}",
                                    name,
                                )

                if not rows:
                    tags.p("No test or collection cases.")

            with tags.aside(  # type: ignore
                cls="details-panel",
                aria_label="Selected test details",
            ):
                with tags.div(  # type: ignore
                    id="detail-content",
                    aria_live="polite",
                    aria_atomic="true",
                ):
                    tags.h2("Test details")
                    tags.p("Click Extensions or Output to inspect a test.")

        for index, (run, case, source) in enumerate(rows):
            html_detail_templates(index, run, case, source)

        tags.script(raw(Path(__file__).with_suffix(".js").read_text()))

    return document.render()
