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
    perf_trace: Optional[str]
    file_whitelist: List[str]
    file_blacklist: List[str]
    debug_file: Optional[str] = None
    coverage_mapping_dump: Optional[str] = None
