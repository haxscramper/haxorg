import ctypes
import os
import shlex
import subprocess
import time

import pytest

from . import bootstrap
from .config import Settings

_worker_debugger_key = pytest.StashKey[subprocess.Popen]()
_report_offset = 0
_settings_key = pytest.StashKey[Settings]()


def pytest_configure(config: pytest.Config) -> None:
    settings = Settings.from_environment()
    config.stash[_settings_key] = settings

    if settings.enabled and hasattr(config, "workerinput"):
        config.stash[_worker_debugger_key] = attach_worker_debugger(settings)


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


def attach_worker_debugger(settings: Settings) -> subprocess.Popen:
    report_directory = settings.pytest_backtrace_dir
    if report_directory is None:
        raise ValueError(
            "LLDB worker debugging requires HSTD_PY_LLDB_PYTEST_BACKTRACE_DIR"
        )

    pid = os.getpid()
    ready_path = report_directory / f"{pid}.ready"
    debugger_log = report_directory / f"{pid}.lldb.log"

    script = settings.script if settings.script is not None else bootstrap.__file__

    commands = [
        f"process attach --pid {pid}",
        f"command script import {shlex.quote(str(script))}",
        "rich-backtrace-configure",
        (f"script __import__('pathlib').Path({str(ready_path)!r}).touch()"),
        "continue",
    ]

    arguments = ["lldb", "--batch"]
    for command in commands:
        arguments.extend(["-o", command])

    # Gate LLDB startup until this worker grants it ptrace permission.
    # exec preserves the PID to which permission is granted.
    with debugger_log.open("wb") as stream:
        debugger = subprocess.Popen(
            [
                "sh",
                "-c",
                'read -r start && exec "$@"',
                "lldb-worker",
                *arguments,
            ],
            stdin=subprocess.PIPE,
            stdout=stream,
            stderr=subprocess.STDOUT,
        )

    try:
        libc = ctypes.CDLL(None, use_errno=True)
        prctl = libc.prctl
        prctl.argtypes = [
            ctypes.c_int,
            ctypes.c_ulong,
            ctypes.c_ulong,
            ctypes.c_ulong,
            ctypes.c_ulong,
        ]
        prctl.restype = ctypes.c_int

        # Linux PR_SET_PTRACER: permit this debugger to attach under Yama.
        if prctl(0x59616D61, debugger.pid, 0, 0, 0) != 0:
            error_number = ctypes.get_errno()
            raise OSError(error_number, os.strerror(error_number))

        assert debugger.stdin is not None
        debugger.stdin.write(b"start\n")
        debugger.stdin.close()

        deadline = time.monotonic() + 30

        while not ready_path.exists():
            status = debugger.poll()
            if status is not None:
                raise RuntimeError(
                    f"Worker LLDB exited with status {status}:\n"
                    f"{debugger_log.read_text(encoding='utf-8')}"
                )

            if deadline <= time.monotonic():
                raise TimeoutError(
                    f"Worker LLDB did not attach within 30 seconds; see {debugger_log}"
                )

            time.sleep(0.05)

        ready_path.unlink()
        return debugger
    except BaseException:
        if debugger.poll() is None:
            debugger.kill()

        debugger.wait()
        raise
