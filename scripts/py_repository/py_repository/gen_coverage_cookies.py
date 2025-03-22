from beartype.typing import Optional, Any, List
from pydantic import BaseModel, Field

class ProfdataCookie(BaseModel, extra="forbid"):
    test_binary: str
    test_name: str
    test_class: Optional[str] = None
    test_profile: str
    test_params: Any = None


class ProfdataFullProfile(BaseModel, extra="forbid"):
    runs: List[ProfdataCookie] = Field(default_factory=list)


class ProfdataParams(BaseModel, extra="forbid"):
    coverage: str
    coverage_db: str
    perf_trace: Optional[str] = None
    file_whitelist: List[str] = Field(default_factory=list)
    file_blacklist: List[str] = Field(default_factory=list)
    debug_file: Optional[str] = None
    coverage_mapping_dump: Optional[str] = None
    run_group_batch_size: int = 8
