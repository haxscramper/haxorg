from pathlib import Path

from ex_py_need_binary import verify as verify_binary
from ex_py_need_nanobind import verify as verify_nanobind
from ex_py_standalone import verify as verify_standalone


def verify(expected_version: int) -> dict:
    report = {
        "version": expected_version,
        "packages": {
            __name__: str(Path(__file__).resolve()),
        },
    }

    for dependency in (
        verify_standalone,
        verify_binary,
        verify_nanobind,
    ):
        dependency_report = dependency(expected_version)
        assert dependency_report["version"] == expected_version

        report["packages"].update(dependency_report["packages"])

        for key, value in dependency_report.items():
            if key not in ("version", "packages"):
                assert key not in report
                report[key] = value

    return report
