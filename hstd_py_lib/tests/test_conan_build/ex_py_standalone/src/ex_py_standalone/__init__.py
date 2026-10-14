from pathlib import Path

from .value import VALUE


def value() -> int:
    return VALUE


def verify(expected_version: int) -> dict:
    assert value() == expected_version

    return {
        "version": expected_version,
        "packages": {
            __name__: str(Path(__file__).resolve()),
        },
    }
