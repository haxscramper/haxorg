import hashlib
from collections.abc import Sequence
from pathlib import Path
from typing import Callable

import pytest


def get_test_dir(
    request: pytest.FixtureRequest,
    test_dir_root: Path = Path("/tmp/haxorg/test_out"),
) -> Path:

    # Get test file path relative to tests directory
    test_file_path = Path(request.path)
    tests_root = None

    # Find the 'tests' directory in the path
    for parent in test_file_path.parents:
        if parent.name == "tests":
            tests_root = parent
            break

    if tests_root is None:
        raise ValueError(f"Could not find 'tests' directory in path: {test_file_path}")

    # Get relative path from tests directory, without .py extension
    rel_path = test_file_path.relative_to(tests_root).with_suffix("")

    # Build base directory path
    base_dir = test_dir_root / rel_path

    # Add test function name
    test_name = request.node.name

    # Handle parametrized tests
    if hasattr(request.node, "callspec") and request.node.callspec.params:
        params_items = sorted(request.node.callspec.params.items())
        params_str = "_".join(f"{k}={v}" for k, v in params_items)

        if len(params_str) <= 32:
            # Use parameters as-is if short enough
            final_dir = base_dir / test_name / params_str
        else:
            # Use first 24 chars + hex digest for long parameters
            params_prefix = params_str[:24]
            params_hash = hashlib.md5(params_str.encode()).hexdigest()[:8]
            final_dir = base_dir / test_name / f"{params_prefix}_{params_hash}"
    else:
        final_dir = base_dir / test_name

    return final_dir


@pytest.fixture
def stable_test_dir(request: pytest.FixtureRequest) -> Path:
    import shutil

    final_dir = get_test_dir(request)

    # Clean and create directory
    if final_dir.exists():
        shutil.rmtree(final_dir)

    final_dir.mkdir(parents=True, exist_ok=True)

    return final_dir


@pytest.fixture
def stable_unique_test_name(request: pytest.FixtureRequest) -> str:
    """
    Test fixture to provide stable unique string to each test run.
    """
    final_dir = get_test_dir(request, Path("/"))
    return str(final_dir).replace("/", "_")


@pytest.fixture
def cached_test_dir(request: pytest.FixtureRequest) -> Path:
    import platformdirs

    return get_test_dir(
        request,
        Path(platformdirs.user_cache_dir("haxorg_test")).joinpath("py_test_cache"),
    )


TEST_REPORTS = pytest.StashKey[dict[str, pytest.TestReport]]()


@pytest.fixture
def failed_test_logs(
    request: pytest.FixtureRequest,
) -> Callable[..., None]:
    def configure(
        directory: Path,
        files: Sequence[str | Path],
        *,
        max_size: int = 64 * 1024,
    ) -> None:
        paths = [directory / filename for filename in files]

        def print_on_failure() -> None:
            reports = request.node.stash.get(TEST_REPORTS, {})
            if not any(report.failed for report in reports.values()):
                return

            for path in paths:
                print(f"\n--- {path} ---")

                if not path.is_file():
                    print("File not found")
                elif max_size < path.stat().st_size:
                    print(f"File exceeds {max_size} bytes: {path}")
                else:
                    print(path.read_text(encoding="utf-8"))

        request.addfinalizer(print_on_failure)

    return configure


@pytest.hookimpl(wrapper=True)
def pytest_runtest_makereport(item, call):
    report = yield
    item.stash.setdefault(TEST_REPORTS, {})[report.when] = report
    return report
