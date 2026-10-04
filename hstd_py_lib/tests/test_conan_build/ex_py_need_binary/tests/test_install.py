import os

from ex_py_need_binary import verify


def test_installed_artifacts() -> None:
    verify(int(os.environ["EX_EXPECTED_VERSION"]))
