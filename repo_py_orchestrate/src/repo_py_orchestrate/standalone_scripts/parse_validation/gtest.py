from pathlib import Path

from beartype import beartype
from pydantic import ValidationError

from .models import (
    Framework,
    GtestCase,
    GtestDocument,
    GtestResult,
    GtestStatus,
    Outcome,
    Phase,
    PhaseReport,
    TestCase,
    TestRun,
)


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
                (
                    f"{failure.type}: {failure.failure}"
                    if failure.type
                    else failure.failure
                )
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
