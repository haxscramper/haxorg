from pydantic import BaseModel, Field
from beartype import beartype
import tree_sitter
from beartype.typing import Tuple, Dict, Optional

class DocText(BaseModel, extra="forbid"):
    Text: str = ""

class DocBase(BaseModel, extra="forbid"):
    StartPoint: Tuple[int, int]
    EndPoint: Tuple[int, int]
    NamePoint: Optional[Tuple[int, int]]
    Doc: Optional[DocText] = None


@beartype
def getNodePoints(node: tree_sitter.Node) -> Dict[str, Tuple[int, int]]:
    return dict(StartPoint=node.start_point, EndPoint=node.end_point)

