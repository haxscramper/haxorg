import pytest
from hstd_py_lib.test_utils import (
    pytest_runtest_makereport as pytest_runtest_makereport,  # noqa
)
from hstd_py_lib.test_utils import (
    stable_test_dir as stable_test_dir,  # noqa
)


@pytest.fixture
def logged_test_dir(stable_test_dir, failed_test_logs):
    failed_test_logs(
        stable_test_dir,
        [
            "stdout.log",
            "stderr.log",
            "reflection_log.log",
        ],
        max_size=128 * 1024,
    )
    return stable_test_dir
