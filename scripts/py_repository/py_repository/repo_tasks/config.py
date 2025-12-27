from pydantic import BaseModel, Field
from beartype.typing import List, Optional, Generator
from contextlib import contextmanager
import tempfile
from pathlib import Path
from beartype import beartype

CAT = __name__


@beartype
def get_tmpdir(*name: str) -> str:
    return str(Path(tempfile.gettempdir()).joinpath("haxorg").joinpath(*name))


class HaxorgInstrumentConfig(BaseModel, extra="forbid"):
    coverage: bool = Field(default=False)
    xray: bool = Field(default=False)
    asan: bool = Field(default=False)
    perfetto: bool = Field(default=False)


class HaxorgUseConfig(BaseModel, extra="forbid"):
    qt: bool = Field(default=True)


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


class HaxorgBuildConfig(BaseModel, extra="forbid"):
    target: List[str] = Field(default_factory=lambda: list(["all"]))
    force: bool = False


class HaxorgGenerateSourcesConfig(BaseModel, extra="forbid"):
    tmp: bool = False
    standalone: bool = False


class HaxorgCustomDocsConfig(BaseModel, extra="forbid"):
    coverage_file_whitelist: List[str] = [".*"]
    coverage_file_blacklist: List[str] = []
    out_dir: str = get_tmpdir("docs_out")


class HaxorgDevelopCiConfig(BaseModel, extra="forbid"):
    deps: bool = True
    build: bool = True
    test: bool = True
    docs: bool = True
    coverage: bool = True
    reflection: bool = True
    install: bool = True
    example: bool = True

    emscripten_deps: bool = True
    emscripten_build: bool = True
    emscripten_test: bool = True


class HaxorgPyTestsConfig(BaseModel, extra="forbid"):
    extra_pytest_args: List[str] = Field(default_factory=list)


class HaxorgBuildDevelopDepsConfig(BaseModel, extra="forbid"):
    rebuild: bool = False
    force: bool = False
    build_whitelist: List[str] = []
    configure: bool = True


class HaxorgBinarySizeReportConfig(BaseModel, extra="forbid"):
    min_symbol_index: Optional[int] = None
    max_symbol_index: Optional[int] = None
    binary_path: Optional[str] = None
    output_db: Optional[str] = None
    perf_out: Optional[str] = None
    report_path: Optional[str] = None


import enum


class HaxorgLogLevel(str, enum.Enum):
    NORMAL = "NORMAL"
    QUIET = "QUIET"
    VERBOSE = "VERBOSE"


class HaxorgConfig(BaseModel, extra="forbid"):
    log_level: HaxorgLogLevel = Field(default=HaxorgLogLevel.NORMAL)
    debug: bool = Field(default=False)

    use: HaxorgUseConfig = Field(default_factory=lambda: HaxorgUseConfig())
    use_unchanged_tasks: bool = Field(default=False)
    emscripten: HaxorgEmscriptenConfig = Field(
        default_factory=lambda: HaxorgEmscriptenConfig())
    instrument: HaxorgInstrumentConfig = Field(
        default_factory=lambda: HaxorgInstrumentConfig())
    tasks: HaxorgTasksConfig = Field(default_factory=lambda: HaxorgTasksConfig())
    workflow_log_dir: Path = Field(
        default_factory=lambda: Path("/tmp/haxorg/workflow_log"))

    use_sarif: bool = Field(default=False)
    force_full_build: bool = Field(
        default=False,
        description="Don't stop the build of the cmake targets on the first error")

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
    CPACK_TEST_IMAGE: str = "docker-haxorg-cpack"
    develop_ci_conf: HaxorgDevelopCiConfig = Field(default_factory=HaxorgDevelopCiConfig)
    py_test_conf: HaxorgPyTestsConfig = Field(default_factory=HaxorgPyTestsConfig)
    build_develop_deps_conf: HaxorgBuildDevelopDepsConfig = Field(
        default_factory=HaxorgBuildDevelopDepsConfig)
    build_conf: HaxorgBuildConfig = Field(default_factory=HaxorgBuildConfig)
    generate_sources_conf: HaxorgGenerateSourcesConfig = Field(
        default_factory=HaxorgGenerateSourcesConfig)

    custom_docs_conf: HaxorgCustomDocsConfig = Field(
        default_factory=HaxorgCustomDocsConfig)

    binary_size_conf: HaxorgBinarySizeReportConfig = Field(
        default_factory=HaxorgBinarySizeReportConfig)


# Variable.set("haxorg_config", HaxorgConfig().model_dump(), serialize_json=True)
