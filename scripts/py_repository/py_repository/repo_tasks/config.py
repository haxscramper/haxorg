from pydantic import BaseModel, Field
from beartype.typing import List, Optional, Generator, Literal
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


class HaxorgEmscriptenConfig(BaseModel, extra="forbid"):
    build: bool = False
    toolchain: str = "/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake"


class HaxorgBuildConfig(BaseModel, extra="forbid"):
    target: List[str] = Field(default_factory=lambda: list(["all"]))
    force: bool = False
    use_protobuf: bool = True
    use_msgpack: bool = True
    cxx_compiler: str = "clang++"
    c_compiler: str = "clang"


class HaxorgGenerateSourcesConfig(BaseModel, extra="forbid"):
    tmp: bool = False
    standalone: bool = False


class HaxorgCustomDocsConfig(BaseModel, extra="forbid"):
    out_dir: str = get_tmpdir("docs_out")


class HaxorgDevelopCiConfig(BaseModel, extra="forbid"):
    deps: bool = Field(True, description="Build and install third-party dependencies")
    build: bool = Field(True, description="Build all targets in the cmake project")
    test: bool = Field(True, description="Execute testse via pytest")
    docs: bool = Field(True, description="Generate HTML documentation and coverage files")
    coverage: bool = Field(True, description="Build coverage database for the project")
    reflection: bool = Field(True,
                             description="Update source code generation for project")
    linter: bool = Field(True,
                         description="Run linter and formatter for pyton and cxx code")
    install: bool = Field(True, description="Execute cxx code installation")
    example_build: bool = Field(True, description="Build example projects")
    example_run: bool = Field(True, description="Run example projects and tests")
    include_graph: bool = Field(True, description="Generate include graph visualization")

    emscripten_deps: bool = True
    emscripten_build: bool = True
    emscripten_test: bool = True



class HaxorgExampleConfig(BaseModel, extra="forbid"):
    pass


class HaxorgPyTestsConfig(BaseModel, extra="forbid"):
    extra_pytest_args: List[str] = Field(default_factory=list)
    real_time_output_print: bool = Field(
        default=True,
        description=
        "Print the pytest output as it happens intead or capture the stdout/stderr and store it in a file."
    )


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
    update_db: bool = True


class HaxorgCoverageRunPattern(BaseModel, extra="forbid"):
    """
    Group of regular expression patterns to match against the test binary,
    class or name. 
    """
    binary_pattern: Optional[str] = Field(
        default=None,
        description="Pattern matching against the full path of the compiled test binary")
    class_pattern: Optional[str] = Field(
        default=None,
        description="Pattern matching against the cxx/gtest/qtest class name")

    name_pattern: Optional[str] = Field(
        default=None, description="Pattern matching against specific test name")


class HaxorgCoverageConfig(BaseModel, extra="forbid"):
    """

    Whitelist and blacklist patterns to check which coverage
    runsand files should be included in the final coverage database. 
    To be accepted, file/entry must be explicitly allowed by the 
    whitelist first, and then not filtered out by any of the 
    blacklist. 

    The `profdata_merge_*` field pair controls which source files are
    integrated into the coverage database. The `coverage_run_*` field pair
    determines which specific individual runs should be included in the coverage. 

    Filtering is first done on the per-run basis, then the coverage of the 
    specific source files is filtered out by the `reflection_tool`. 
    """

    coverage_run_whitelist: List[HaxorgCoverageRunPattern] = Field(
        default_factory=lambda: [
            HaxorgCoverageRunPattern(
                binary_pattern=".*",
                class_pattern=".*",
                name_pattern=".*",
            )
        ],
        description=
        "List of run patterns to narrow down which coverage runs should be included in the DB."
    )

    coverage_run_blacklist: List[HaxorgCoverageRunPattern] = Field(
        default_factory=list,
        description=
        "Inverse of the `coverage_run_whitelist`, determines which runs should not "
        "be added to the final database.")

    profdata_merge_file_whitelist: List[str] = Field(
        default_factory=lambda: [".*"],
        description="List of regular expressions to filter out which files can be added "
        "to the profile merge database. File must match at least one regex to be accepted."
        "Ideally, the list of the regular expressions can be as inclusive as possible, as "
        "the only consideration when constructing the database is the time it takes to "
        "process all the files.")

    profdata_merge_file_blacklist: List[str] = Field(
        default_factory=lambda: ["base_lexer_gen.cpp", "thirdparty"],
        description="Inverse pair to the `profdata_merge_file_whitelist`. List of regular "
        "expressions to filter out which files are not allowed to be added to the database."
    )

    coverage_html_whitelist: List[str] = Field(
        default_factory=lambda: [".*"],
        description="Which source files should have the HTML coverage documentation.")

    coverage_html_blacklist: List[str] = Field(
        default_factory=lambda: [],
        description="Inverse of the `coverage_html_whitelist` -- which files to exclude "
        "from HTML generation.")


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
    use_dependencies: bool = Field(default=True)
    emscripten: HaxorgEmscriptenConfig = Field(
        default_factory=lambda: HaxorgEmscriptenConfig())
    instrument: HaxorgInstrumentConfig = Field(
        default_factory=lambda: HaxorgInstrumentConfig())
    tasks: HaxorgTasksConfig = Field(default_factory=lambda: HaxorgTasksConfig())
    workflow_log_dir: Path = Field(
        default_factory=lambda: Path("/tmp/haxorg/workflow_log"))

    workflow_out_dir: Path = Field(
        default_factory=lambda: Path("/tmp/haxorg/workflow_out"))

    workflow_tmp_dir: Path = Field(
        default_factory=lambda: Path("/tmp/haxorg/workflow_tmp"))

    use_sarif: bool = Field(default=False)
    force_full_build: bool = Field(
        default=False,
        description="Don't stop the build of the cmake targets on the first error")

    forceall: bool = Field(default=False)
    ci: bool = Field(default=False)
    dryrun: bool = Field(default=False)
    build_base_override: Optional[str] = Field(
        default=None,
        description="Overide the name of the sub-directory in the build/ output")

    separate_debug_symbols: bool = False

    python_version: Optional[str] = None

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
    coverage_conf: HaxorgCoverageConfig = Field(default_factory=HaxorgCoverageConfig)
    generate_sources_conf: HaxorgGenerateSourcesConfig = Field(
        default_factory=HaxorgGenerateSourcesConfig)

    custom_docs_conf: HaxorgCustomDocsConfig = Field(
        default_factory=HaxorgCustomDocsConfig)

    binary_size_conf: HaxorgBinarySizeReportConfig = Field(
        default_factory=HaxorgBinarySizeReportConfig)

    example_conf: HaxorgExampleConfig = Field(default_factory=HaxorgExampleConfig)


# Variable.set("haxorg_config", HaxorgConfig().model_dump(), serialize_json=True)
