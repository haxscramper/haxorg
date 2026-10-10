import os

import pytest

from .config import Settings

_report_offset = 0
_settings_key = pytest.StashKey[Settings]()


def pytest_configure(config: pytest.Config) -> None:
    config.stash[_settings_key] = Settings.from_environment()


@pytest.hookimpl(hookwrapper=True, tryfirst=True)
def pytest_runtest_makereport(item, call):
    global _report_offset

    outcome = yield
    report = outcome.get_result()

    settings = item.config.stash[_settings_key]
    report_directory = settings.pytest_backtrace_dir
    if report_directory is None:
        return

    report_path = report_directory / f"{os.getpid()}.log"
    if not report_path.exists():
        return

    with report_path.open(encoding="utf-8") as stream:
        stream.seek(_report_offset)
        backtrace = stream.read()
        _report_offset = stream.tell()

    if backtrace:
        report.sections.append((f"Captured LLDB backtrace {report.when}", backtrace))
