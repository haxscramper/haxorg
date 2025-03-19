from pathlib import Path
import yaml
from pydantic import BaseModel, Field
from beartype.typing import List, Optional
import os


class HaxorgInstrumentConfig(BaseModel, extra="forbid"):
    coverage: bool = Field(default=False)
    xray: bool = Field(default=False)
    asan: bool = Field(default=False)


class HaxorgTasksConfig(BaseModel, extra="forbid"):
    skip_python_refl: bool = Field(default=False)


class HaxorgCoverageCookiePattern(BaseModel, extra="forbid"):
    binary_pattern: Optional[str] = None
    class_pattern: Optional[str] = None
    name_pattern: Optional[str] = None


class HaxorgCoverageAggregateFilter(BaseModel, extra="forbid"):
    whitelist_patterns: List[HaxorgCoverageCookiePattern] = []
    blacklist_patterns: List[HaxorgCoverageCookiePattern] = []


class HaxorgConfig(BaseModel, extra="forbid"):
    quiet: bool = Field(default=False)
    debug: bool = Field(default=False)
    instrument: HaxorgInstrumentConfig = Field(
        default_factory=lambda: HaxorgInstrumentConfig())
    tasks: HaxorgTasksConfig = Field(default_factory=lambda: HaxorgTasksConfig())
    force_task: List[str] = Field(
        default_factory=list,
        description="Always execute task",
    )

    python_version: Optional[str] = None
    aggregate_filters: Optional[HaxorgCoverageAggregateFilter] = None
    profdata_file_whitelist: List[str] = Field(default_factory=lambda: [".*"])
    profdata_file_blacklist: List[str] = Field(default_factory=lambda: ["base_lexer_gen.cpp", "thirdparty"])


def get_haxorg_repo_root_path() -> Path:
    result = Path(__file__).parent.parent.parent.parent
    assert result.exists(), result
    assert result.is_dir(), result
    assert result.joinpath("tasks.py").exists(), result
    return result


def get_haxorg_repo_root_config_path() -> Path:
    return get_haxorg_repo_root_path().joinpath("invoke.yaml")


def get_haxorg_repo_root_config() -> HaxorgConfig:
    file = get_haxorg_repo_root_config_path()

    with open(file, 'r') as f:
        data = yaml.load(f, Loader=yaml.SafeLoader)

    return HaxorgConfig(**data)


def get_maybe_repo_rel_path(path: Path) -> Path:
    if path.is_relative_to(path):
        return path.relative_to(get_haxorg_repo_root_path())

    else:
        return path
