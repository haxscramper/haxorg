from datetime import UTC, datetime
from enum import StrEnum
from pathlib import Path

from beartype import beartype
from pydantic import BaseModel, ConfigDict, Field, JsonValue


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


class Channel(StrEnum):
    STDOUT = "stdout"
    STDERR = "stderr"
    LOG = "log"
    CUSTOM = "custom"


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
    duration: float = Field(default=0.0, ge=0, allow_inf_nan=False)
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
        return sum((phase.duration for phase in self.phases), 0.0)


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


class PytestOutcome(StrEnum):
    PASSED = "passed"
    FAILED = "failed"
    SKIPPED = "skipped"


class PytestRecord(BaseModel):
    model_config = ConfigDict(extra="allow")

    nodeid: str
    outcome: PytestOutcome
    when: Phase | None = None
    duration: float = Field(default=0.0, ge=0, allow_inf_nan=False)
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


class GtestStatus(StrEnum):
    RUN = "RUN"
    NOTRUN = "NOTRUN"


class GtestResult(StrEnum):
    COMPLETED = "COMPLETED"
    SKIPPED = "SKIPPED"
    SUPPRESSED = "SUPPRESSED"


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
