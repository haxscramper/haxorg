import os

from ex_py_standalone import value, verify


def test_value() -> None:
    expected = int(os.environ["EX_EXPECTED_VERSION"])
    assert value() == expected
    verify(expected)
