import os
from pathlib import Path


def get_haxorg_repo_root_path() -> Path:
    result = Path(__file__).parent.parent.parent.parent
    assert result.exists(), result
    assert result.is_dir(), result
    assert result.joinpath("tasks.py").exists(), result
    return result


def get_haxorg_build_path() -> Path:
    build_root = "HAXORG_REPO_HAXORG_ROOT_BUILD_PATH"
    root_val = os.getenv(build_root)
    if root_val:
        return Path(root_val)

    else:
        return get_haxorg_repo_root_path().joinpath("build")


def get_maybe_repo_rel_path(path: Path) -> Path:
    if path.is_relative_to(path):
        return path.relative_to(get_haxorg_repo_root_path())

    else:
        return path
