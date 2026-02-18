import enum

from beartype.typing import Any, List, Optional
from pydantic import BaseModel, Field


class ProfdataCookie(BaseModel, extra="forbid"):
    test_binary: str
    test_name: str
    test_class: Optional[str] = None
    test_profile: str
    test_params: Any = None


class ProfdataFullProfile(BaseModel, extra="forbid"):
    runs: List[ProfdataCookie] = Field(default_factory=list)


class Mode(str, enum.Enum):
    RunProfileMerge = "RunProfileMerge"
    BuildProfileMerge = "BuildProfileMerge"
    AllTargetedFiles = "AllTargetedFiles"
    AllMainSymbolsInCompilationDb = "AllMainSymbolsInCompilationDb"
    AllAnotatedSymbols = "AllAnotatedSymbols"
    BinarySymbols = "BinarySymbols"


class ProfdataConfig(BaseModel, extra="forbid"):
    build_profile_dir: str = ""
    file_whitelist: List[str] = Field(default_factory=lambda: [".*"])
    file_blacklist: List[str] = Field(default_factory=list)
    debug_file: Optional[str] = None
    coverage_mapping_dump: Optional[str] = None
    run_group_batch_size: int = 8


class ReflectionConfig(BaseModel, extra="forbid"):
    compilation_database: str = ""
    toolchain_include: Optional[str] = None
    clang_resource_dir: Optional[str] = None
    no_std_include: bool = False


class ReflectionCLI(BaseModel, extra="forbid"):
    output: str
    mode: Mode
    profdata: ProfdataConfig = Field(default_factory=lambda: ProfdataConfig())
    reflection: ReflectionConfig = Field(default_factory=lambda: ReflectionConfig())
    perf_path: Optional[str] = None
    log_path: Optional[str] = None
    verbose_log: bool = False
    input: List[str] = Field(default_factory=list)
