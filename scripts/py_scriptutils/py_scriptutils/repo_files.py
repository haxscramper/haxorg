from pathlib import Path

def get_haxorg_repo_root_path() -> Path:
    result = Path(__file__).parent.parent.parent.parent
    assert result.exists(), result
    assert result.is_dir(), result
    assert result.joinpath("tasks.py").exists(), result
    return result
