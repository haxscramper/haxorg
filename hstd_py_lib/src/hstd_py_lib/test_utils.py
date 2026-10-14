import hashlib
import re
from collections.abc import Sequence
from pathlib import Path
from typing import Callable

import pytest


def get_test_dir(
    request: pytest.FixtureRequest,
    test_dir_root: Path = Path("/tmp/haxorg_tests"),
) -> Path:
    test_file_path = Path(request.path)
    tests_root = next(
        (parent for parent in test_file_path.parents if parent.name == "tests"),
        None,
    )

    if tests_root is None:
        raise ValueError(f"Could not find 'tests' directory in path: {test_file_path}")

    rel_path = test_file_path.relative_to(tests_root).with_suffix("")
    test_name = getattr(request.node, "originalname", None) or request.node.name
    base_dir = test_dir_root / rel_path / test_name

    callspec = getattr(request.node, "callspec", None)
    if callspec is None or not callspec.params:
        return base_dir

    params_str = "_".join(
        f"{key}={value}" for key, value in sorted(callspec.params.items())
    )
    sanitized_params = re.sub(r"[^a-zA-Z0-9_]", "_", params_str)

    if sanitized_params != params_str or 32 < len(sanitized_params):
        params_hash = hashlib.sha256(params_str.encode()).hexdigest()[:8]
        sanitized_params = f"{sanitized_params[:24]}_{params_hash}"

    return base_dir / sanitized_params


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
