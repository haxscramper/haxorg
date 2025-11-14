from pydantic import BaseModel, Field
from beartype.typing import List, Optional
from airflow.models import Variable

CAT = __name__


class HaxorgInstrumentConfig(BaseModel, extra="forbid"):
    coverage: bool = Field(default=False)
    xray: bool = Field(default=False)
    asan: bool = Field(default=False)
    perfetto: bool = Field(default=False)


class HaxorgUseConfig(BaseModel, extra="forbid"):
    qt: bool = Field(default=False)


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
    use: HaxorgUseConfig = Field(default_factory=lambda: HaxorgUseConfig())
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

    # Major version of the LLVM toolchain used for the project. This is not a configuration
    # value, only as constant to avoid typing the same thing all over.
    LLVM_MAJOR: str = "18"
    LLVM_VERSION: str = "18.1.4"
    CAT: str = "tasks"
    HAXORG_VERSION: str = "1.0.0"
    HAXORG_NAME: str = "haxorg"
    in_ci: bool = False
    HAXORG_DOCKER_IMAGE: str = "docker-haxorg"



def get_config() -> HaxorgConfig:
    raw_config = Variable.get("haxorg_config", deserialize_json=True)
    return HaxorgConfig(**raw_config)


Variable.set("haxorg_config", HaxorgConfig().model_dump(), serialize_json=True)
