import importlib.util
import os
from pathlib import Path
import sys
from typing import TYPE_CHECKING

from beartype import beartype

s = importlib.util.find_spec("pyhaxorg")
print(f"SPEC: {s.origin if s else None}")

LD_LIBRARY_PATH = os.getenv("LD_LIBRARY_PATH")
print(f"LD_LIBRARY_PATH={LD_LIBRARY_PATH}")

for p in sys.path:
    print(f"PATH: {p}")

from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from py_haxorg.pyhaxorg import *
else:
    from pyhaxorg import *

SemSet = set[OrgSemKind]


@beartype
def org_ident_normalize(input_str: str) -> str:
    result = ""
    for c in input_str:
        if c not in {"_", "-"}:
            if c.islower() or c.isdigit():
                result += c
            elif c.isupper():
                result += c.lower()

    return result


@beartype
def treeRepr(node: Org, colored: bool = True, maxDepth: int = 50) -> str:
    return exportToTreeString(  # type: ignore
        node,
        OrgTreeExportOpts(  # type: ignore
            withColor=colored,
            maxDepth=maxDepth,
        ),
    )
