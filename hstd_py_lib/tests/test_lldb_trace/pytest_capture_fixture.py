import hstd_py_lldb_fixture_extension as extension


def test_passing_breakpoint() -> None:
    assert extension.run() == 112


def test_failing_breakpoint() -> None:
    result = extension.run()
    assert result == 0
