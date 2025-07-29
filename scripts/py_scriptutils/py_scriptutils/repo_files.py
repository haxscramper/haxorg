from pathlib import Path
import yaml
from pydantic import BaseModel, Field
from beartype.typing import List, Optional
import os


class HaxorgInstrumentConfig(BaseModel, extra="forbid"):
    coverage: bool = Field(default=False)
    xray: bool = Field(default=False)
    asan: bool = Field(default=False)
    perfetto: bool = Field(default=False)


class HaxorgTasksConfig(BaseModel, extra="forbid"):
    skip_python_refl: bool = Field(default=False)

    # invoke config fields
    search_root: Optional[str] = None
    dedupe: bool = True
    collection_name: Optional[str] = None
    ignore_unknown_help: bool = False
    executor_class: Optional[str] = None
    auto_dash_names: bool = True


class HaxorgCoverageCookiePattern(BaseModel, extra="forbid"):
    binary_pattern: Optional[str] = None
    class_pattern: Optional[str] = None
    name_pattern: Optional[str] = None


class HaxorgCoverageAggregateFilter(BaseModel, extra="forbid"):
    whitelist_patterns: List[HaxorgCoverageCookiePattern] = []
    blacklist_patterns: List[HaxorgCoverageCookiePattern] = []


class HaxorgEmscriptenConfig(BaseModel, extra="forbid"):
    build: bool = False
    toolchain: str = "/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake"


class HaxorgConfig(BaseModel, extra="forbid"):
    quiet: bool = Field(default=False)
    debug: bool = Field(default=False)
    emscripten: HaxorgEmscriptenConfig = Field(
        default_factory=lambda: HaxorgEmscriptenConfig())
    instrument: HaxorgInstrumentConfig = Field(
        default_factory=lambda: HaxorgInstrumentConfig())
    tasks: HaxorgTasksConfig = Field(default_factory=lambda: HaxorgTasksConfig())
    force_task: List[str] = Field(
        default_factory=list,
        description="Always execute task",
    )

    forceall: bool = Field(default=False)
    ci: bool = Field(default=False)
    dryrun: bool = Field(default=False)

    python_version: Optional[str] = None
    aggregate_filters: Optional[HaxorgCoverageAggregateFilter] = None
    profdata_file_whitelist: List[str] = Field(default_factory=lambda: [".*"])
    profdata_file_blacklist: List[str] = Field(
        default_factory=lambda: ["base_lexer_gen.cpp", "thirdparty"])

    # field for unparsing invoke config
    sudo: dict = Field(default_factory=dict)
    runners: dict = Field(default_factory=dict)
    timeouts: dict = Field(default_factory=dict)
    run: dict = Field(default_factory=dict)


def get_haxorg_repo_root_path() -> Path:
    result = Path(__file__).parent.parent.parent.parent
    assert result.exists(), result
    assert result.is_dir(), result
    assert result.joinpath("tasks.py").exists(), result
    return result

def get_haxorg_build_path() -> Path:
    build_root = "HAXORG_REPO_HAXORG_ROOT_BUILD_PATH"
    if os.getenv(build_root): 
        return Path(os.getenv(build_root))

    else:
        return get_haxorg_repo_root_path().joinpath("build")


def get_maybe_repo_rel_path(path: Path) -> Path:
    if path.is_relative_to(path):
        return path.relative_to(get_haxorg_repo_root_path())

    else:
        return path
