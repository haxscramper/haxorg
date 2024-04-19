from beartype.typing import Optional, Any, List
from pydantic import Field, BaseModel

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
