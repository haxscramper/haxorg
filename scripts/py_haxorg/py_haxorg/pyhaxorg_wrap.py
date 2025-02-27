from py_scriptutils.repo_files import get_haxorg_repo_root_path
import sys
from typing import TYPE_CHECKING
import os
from beartype import beartype

build_dir = get_haxorg_repo_root_path().joinpath("build/haxorg")
if str(build_dir) not in sys.path:
    sys.path.append(str(build_dir))

from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from py_haxorg.pyhaxorg import *
else:
    print(os.getenv("LD_PRELOAD"))
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
    return exportToTreeString(node, OrgTreeExportOpts(withColor=colored,
                                                      maxDepth=maxDepth))
