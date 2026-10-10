import json
import shlex
import sys
from dataclasses import dataclass
from pathlib import Path

import pytest
from beartype import beartype
from beartype.typing import Iterator
from hstd_py_lib.debug_utils import bootstrap
from hstd_py_lib.debug_utils.model import (
    FrameInfo,
    Report,
    ReportReason,
    ValueNode,
)
from plumbum import local


@dataclass(frozen=True)
class FixtureBuild:
    binary: Path
    extension_directory: Path
    fixture_directory: Path


@dataclass(frozen=True)
class LldbResult:
    status: int
    stdout: str
    stderr: str
    log_text: str
    reports: list[Report]


@beartype
def quote_path(path: Path) -> str:
    return shlex.quote(str(path.resolve()))


@pytest.fixture(scope="session")
def fixture_build(
    tmp_path_factory: pytest.TempPathFactory,
) -> FixtureBuild:
    source = Path(__file__).parent / "test_lldb_trace"
    build = tmp_path_factory.mktemp("test_lldb_trace")

    local["conan"][
        "install",
        str(source),
        "--output-folder",
        str(build),
        "--build=missing",
        "-s",
        "build_type=Debug",
        "-s",
        "compiler.cppstd=23",
        "-c",
        f"user.haxorg:python_executable={sys.executable}",
    ].run()

    local["cmake"][
        "-S",
        str(source),
        "-B",
        str(build),
        f"-DCMAKE_TOOLCHAIN_FILE={build / 'conan_toolchain.cmake'}",
        "-DCMAKE_BUILD_TYPE=Debug",
    ].run()

    local["cmake"][
        "--build",
        str(build),
        "--parallel",
        "2",
    ].run()

    return FixtureBuild(
        binary=build / "bin" / "hstd_py_lldb_fixture",
        extension_directory=build / "python",
        fixture_directory=source,
    )


@beartype
def run_lldb(
    tmp_path: Path,
    target: list[str],
    *,
    environment: dict[str, str] | None = None,
    before: list[str] | None = None,
    after: list[str] | None = None,
) -> LldbResult:
    log_file = tmp_path / "reports.jsonl"
    settings = {
        "HSTD_PY_LLDB_LOG_FILE": str(log_file),
        "HSTD_PY_LLDB_STRUCTURED_OUTPUT": "true",
    }
    settings.update(environment or {})

    commands = [
        f"command script import {quote_path(Path(bootstrap.__file__))}",
        *(before or []),
        "rich-backtrace-configure",
        *(["run"] if after is None else after),
    ]

    arguments = ["run", "--no-sync", "lldb", "--batch"]

    for command in commands:
        arguments.extend(["-o", command])

    arguments.extend(["--", *target])

    with local.env():
        for name, _ in list(local.env):
            if name.startswith("HSTD_PY_LLDB_"):
                del local.env[name]

        local.env.update(settings)

        status, stdout, stderr = local["uv"][arguments].run(
            retcode=None,
            timeout=90,
        )

    log_text = log_file.read_text() if log_file.exists() else ""

    reports = (
        [Report.from_json(line) for line in log_text.splitlines() if line]
        if settings["HSTD_PY_LLDB_STRUCTURED_OUTPUT"] == "true"
        else []
    )

    return LldbResult(
        status=status,
        stdout=stdout,
        stderr=stderr,
        log_text=log_text,
        reports=reports,
    )


@beartype
def stopped_report(
    fixture_build: FixtureBuild,
    tmp_path: Path,
    *,
    environment: dict[str, str] | None = None,
    before: list[str] | None = None,
) -> LldbResult:
    return run_lldb(
        tmp_path,
        [str(fixture_build.binary)],
        environment=environment,
        before=before,
        after=[
            "breakpoint set -n trace_fixture::inspect",
            "run",
            "rich-backtrace --all",
        ],
    )


@beartype
def find_inspect(report: Report) -> FrameInfo:
    for thread in report.threads:
        for frame in thread.frames:
            if "trace_fixture::inspect" in frame.function_name:
                return frame

    raise AssertionError(
        f"Report does not contain trace_fixture::inspect: {report.to_json()}"
    )


@beartype
def find_argument(frame: FrameInfo, name: str) -> ValueNode:
    for argument in frame.arguments:
        if argument.name == name:
            return argument

    raise AssertionError(
        f"Frame {frame.function_name!r} does not contain "
        f"argument {name!r}; available arguments are "
        f"{[argument.name for argument in frame.arguments]!r}"
    )


@beartype
def walk_values(node: ValueNode) -> Iterator[ValueNode]:
    yield node

    for nested in node.nested:
        yield from walk_values(nested)


def test_import_does_not_create_or_launch_target(
    tmp_path: Path,
) -> None:
    script = quote_path(Path(bootstrap.__file__))

    status, stdout, stderr = local["uv"][
        "run",
        "--no-sync",
        "lldb",
        "--batch",
        "-o",
        f"command script import {script}",
        "-o",
        "script assert lldb.debugger.GetNumTargets() == 0",
        "-o",
        "help rich-backtrace",
        "-o",
        "help rich-backtrace-configure",
    ].run(retcode=None, timeout=30)

    assert status == 0, stdout + stderr


def test_default_configuration_inside_lldb(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    checks = (
        "from hstd_py_lib.debug_utils.config import Settings; "
        "settings = Settings.from_environment(); "
        "assert settings.fatal_signals == "
        "['SIGSEGV', 'SIGABRT', 'SIGBUS', 'SIGFPE', "
        "'SIGILL', 'SIGSYS']; "
        "assert settings.frame_blacklist == []; "
        "assert settings.breakpoint_functions == []"
    )

    result = stopped_report(
        fixture_build,
        tmp_path,
        before=[f"script {checks}"],
    )

    assert result.status == 0, result.stdout + result.stderr
    assert len(result.reports) == 1


def test_native_argument_extraction(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    result = stopped_report(fixture_build, tmp_path)

    assert result.status == 0, result.stdout + result.stderr
    assert len(result.reports) == 1

    report = result.reports[0]
    assert report.reason == ReportReason.MANUAL
    assert 0 < report.pid

    frame = find_inspect(report)
    assert frame.file_path is not None
    assert frame.line is not None
    assert 0 < frame.line

    count = find_argument(frame, "count")
    assert count.value == "7"
    assert count.error is None

    point = find_argument(frame, "point")
    assert "trace_fixture::Point" in point.type_name

    coordinates = {node.name: node.value for node in point.nested}
    assert coordinates["x"] == "17"
    assert coordinates["y"] == "29"

    envelope = find_argument(frame, "envelope")
    assert any(node.value == "8" for node in walk_values(envelope))

    pointer = find_argument(frame, "pointer")
    assert pointer.value is not None
    assert pointer.error is None


def test_frame_blacklist_preserves_original_indices(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    result = stopped_report(
        fixture_build,
        tmp_path,
        environment={
            "HSTD_PY_LLDB_FRAME_BLACKLIST": json.dumps(["trace_fixture::hidden_frame"]),
        },
    )

    assert result.status == 0, result.stdout + result.stderr

    frames = result.reports[0].threads[0].frames
    assert frames[0].index == 0
    assert all(
        "trace_fixture::hidden_frame" not in frame.function_name for frame in frames
    )
    assert any(2 <= frame.index for frame in frames)


def test_frame_range(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    result = stopped_report(
        fixture_build,
        tmp_path,
        environment={
            "HSTD_PY_LLDB_FRAME_START": "1",
            "HSTD_PY_LLDB_FRAME_END": "2",
        },
    )

    assert result.status == 0, result.stdout + result.stderr
    assert [frame.index for frame in result.reports[0].threads[0].frames] == [1]


def test_depth_limit(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    result = stopped_report(
        fixture_build,
        tmp_path,
        environment={"HSTD_PY_LLDB_MAX_DEPTH": "0"},
    )

    assert result.status == 0, result.stdout + result.stderr

    point = find_argument(
        find_inspect(result.reports[0]),
        "point",
    )
    assert point.nested == []
    assert point.truncated


def test_nested_limit(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    result = stopped_report(
        fixture_build,
        tmp_path,
        environment={"HSTD_PY_LLDB_MAX_NESTED": "1"},
    )

    assert result.status == 0, result.stdout + result.stderr

    point = find_argument(
        find_inspect(result.reports[0]),
        "point",
    )
    assert len(point.nested) == 1
    assert point.truncated


def test_custom_extractor(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    adapter = fixture_build.fixture_directory / "lldb_fixture_adapter.py"

    result = stopped_report(
        fixture_build,
        tmp_path,
        before=[f"command script import {quote_path(adapter)}"],
    )

    assert result.status == 0, result.stdout + result.stderr

    point = find_argument(
        find_inspect(result.reports[0]),
        "point",
    )
    assert point.summary == "point(17, 29)"
    assert len(point.nested) == 2


def test_named_breakpoint_auto_continues(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    result = run_lldb(
        tmp_path,
        [str(fixture_build.binary)],
        environment={
            "HSTD_PY_LLDB_BREAKPOINT_FUNCTIONS": json.dumps(["trace_fixture::inspect"]),
        },
    )

    assert result.status == 0, result.stdout + result.stderr
    assert len(result.reports) == 1
    assert result.reports[0].reason == ReportReason.BREAKPOINT
    assert "exited with status = 0" in result.stdout


def test_named_breakpoint_can_remain_stopped(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    result = run_lldb(
        tmp_path,
        [str(fixture_build.binary)],
        environment={
            "HSTD_PY_LLDB_BREAKPOINT_FUNCTIONS": json.dumps(["trace_fixture::inspect"]),
            "HSTD_PY_LLDB_AUTO_CONTINUE": "false",
        },
        after=["run", "rich-backtrace"],
    )

    assert result.status == 0, result.stdout + result.stderr
    assert [report.reason for report in result.reports] == [
        ReportReason.BREAKPOINT,
        ReportReason.MANUAL,
    ]


def test_human_output_to_file(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    result = stopped_report(
        fixture_build,
        tmp_path,
        environment={
            "HSTD_PY_LLDB_STRUCTURED_OUTPUT": "false",
        },
    )

    assert result.status == 0, result.stdout + result.stderr
    assert "=== manual traceback ===" in result.log_text
    assert "trace_fixture::inspect" in result.log_text
    assert "count: int = 7" in result.log_text
    assert "=== manual traceback ===" not in result.stdout
    assert "=== manual traceback ===" not in result.stderr


def test_structured_round_trip(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    result = stopped_report(fixture_build, tmp_path)

    assert result.status == 0, result.stdout + result.stderr

    report = result.reports[0]
    assert Report.from_json(report.to_json()) == report
    assert len(result.log_text.splitlines()) == 1


@pytest.mark.parametrize(
    ("variable", "value", "expected"),
    [
        (
            "HSTD_PY_LLDB_FRAME_END",
            "not-an-integer",
            "HSTD_PY_LLDB_FRAME_END",
        ),
        (
            "HSTD_PY_LLDB_AUTO_CONTINUE",
            "1",
            "Expected 'true' or 'false'",
        ),
        (
            "HSTD_PY_LLDB_FRAME_BLACKLIST",
            "[",
            "HSTD_PY_LLDB_FRAME_BLACKLIST",
        ),
        (
            "HSTD_PY_LLDB_FRAME_BLACKLIST",
            '["["]',
            "Invalid HSTD_PY_LLDB_FRAME_BLACKLIST",
        ),
        (
            "HSTD_PY_LLDB_BREAKPOINT_FUNCTIONS",
            '["valid", 42]',
            "index 1",
        ),
        (
            "HSTD_PY_LLDB_MAX_DEPTH",
            "-1",
            "max_depth must be nonnegative",
        ),
    ],
)
def test_invalid_configuration_fails_in_lldb(
    fixture_build: FixtureBuild,
    tmp_path: Path,
    variable: str,
    value: str,
    expected: str,
) -> None:
    result = run_lldb(
        tmp_path,
        [str(fixture_build.binary)],
        environment={variable: value},
    )

    assert result.status != 0
    assert expected in result.stdout + result.stderr
    assert result.reports == []


@pytest.mark.parametrize("mode", ["abort", "repeat"])
def test_fatal_signal_is_reported_once_and_delivered(
    fixture_build: FixtureBuild,
    tmp_path: Path,
    mode: str,
) -> None:
    result = run_lldb(
        tmp_path,
        [str(fixture_build.binary), mode],
    )

    assert result.status == 0, result.stdout + result.stderr
    assert len(result.reports) == 1

    report = result.reports[0]
    assert report.reason == ReportReason.SIGNAL
    assert report.threads[0].signal_name == "SIGABRT"
    assert "exited" in result.stdout


def test_signal_list_replacement(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    checks = (
        "from hstd_py_lib.debug_utils.config import Settings; "
        "assert Settings.from_environment().fatal_signals "
        "== ['SIGABRT']"
    )

    result = run_lldb(
        tmp_path,
        [str(fixture_build.binary), "abort"],
        environment={
            "HSTD_PY_LLDB_FATAL_SIGNALS": '["SIGABRT"]',
        },
        before=[f"script {checks}"],
    )

    assert result.status == 0, result.stdout + result.stderr
    assert len(result.reports) == 1


def test_empty_signal_list_disables_signal_reporting(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    checks = (
        "from hstd_py_lib.debug_utils.config import Settings; "
        "assert Settings.from_environment().fatal_signals == []"
    )

    result = stopped_report(
        fixture_build,
        tmp_path,
        environment={
            "HSTD_PY_LLDB_FATAL_SIGNALS": "[]",
        },
        before=[f"script {checks}"],
    )

    assert result.status == 0, result.stdout + result.stderr
    assert [report.reason for report in result.reports] == [ReportReason.MANUAL]


def test_python_nanobind_argument_extraction(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    runner = fixture_build.fixture_directory / "python_runner.py"

    result = run_lldb(
        tmp_path,
        [
            sys.executable,
            str(runner),
            str(fixture_build.extension_directory),
            "run",
        ],
        environment={
            "HSTD_PY_LLDB_BREAKPOINT_FUNCTIONS": json.dumps(["trace_fixture::inspect"]),
        },
    )

    assert result.status == 0, result.stdout + result.stderr
    assert len(result.reports) == 1

    frame = find_inspect(result.reports[0])
    assert find_argument(frame, "count").value == "7"
    assert any(
        "trace_fixture::hidden_frame" in frame.function_name
        for frame in result.reports[0].threads[0].frames
    )
    assert "exited with status = 0" in result.stdout


def test_python_nanobind_fatal_signal_preserves_faulthandler(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    runner = fixture_build.fixture_directory / "python_runner.py"

    result = run_lldb(
        tmp_path,
        [
            sys.executable,
            str(runner),
            str(fixture_build.extension_directory),
            "abort",
        ],
    )

    assert result.status == 0, result.stdout + result.stderr
    assert len(result.reports) == 1
    assert result.reports[0].reason == ReportReason.SIGNAL
    assert result.reports[0].threads[0].signal_name == "SIGABRT"
    assert "Fatal Python error" in result.stdout + result.stderr


def test_pytest_plugin_captures_backtraces_per_test(
    fixture_build: FixtureBuild,
    tmp_path: Path,
) -> None:
    report_directory = tmp_path / "pytest-backtraces"
    report_directory.mkdir()

    fixture = fixture_build.fixture_directory / "pytest_capture_fixture.py"

    result = run_lldb(
        tmp_path,
        [
            sys.executable,
            "-m",
            "pytest",
            "-p",
            "hstd_py_lib.debug_utils.pytest_plugin",
            "--noconftest",
            "--color=no",
            "--tb=short",
            "-o",
            "addopts=",
            "-q",
            str(fixture),
        ],
        environment={
            "PYTHONPATH": str(fixture_build.extension_directory),
            "HSTD_PY_LLDB_BREAKPOINT_FUNCTIONS": json.dumps(["trace_fixture::inspect"]),
            "HSTD_PY_LLDB_PYTEST_BACKTRACE_DIR": str(report_directory),
            "HSTD_PY_LLDB_STRUCTURED_OUTPUT": "false",
        },
    )

    output = result.stdout + result.stderr

    # LLDB's batch status does not represent pytest's exit status.
    assert result.status == 0, output
    assert "1 failed, 1 passed" in output
    assert "test_failing_breakpoint" in output

    report_files = list(report_directory.glob("*.log"))
    assert len(report_files) == 1, output

    backtraces = report_files[0].read_text(encoding="utf-8")
    marker = "=== breakpoint traceback ==="

    # Both tests triggered a breakpoint, routed to the inferior's PID file.
    assert backtraces.count(marker) == 2
    assert f"pid={report_files[0].stem}" in backtraces
    assert backtraces.count("count: int = 7") == 2

    # Only the failing test's captured section should be displayed.
    # This also verifies that the plugin consumes the passing test's logs
    # rather than carrying them into the following test.
    assert output.count("Captured LLDB backtrace call") == 1, output
    assert output.count(marker) == 1, output
    assert output.count("count: int = 7") == 1, output

    # Nothing was printed immediately or sent to the normal LLDB log file.
    before_failures, separator, _ = output.partition(
        "=================================== FAILURES"
    )
    assert separator, output
    assert marker not in before_failures
    assert result.log_text == ""
