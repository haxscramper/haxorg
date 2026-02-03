import os
from pathlib import Path
import sys
from typing import TYPE_CHECKING

from beartype import beartype

try:
    from py_scriptutils.repo_files import get_haxorg_repo_root_path
    build_dir = get_haxorg_repo_root_path().joinpath("build/haxorg")
    if str(build_dir) not in sys.path:
        sys.path.append(str(build_dir))
except ImportError:
    pass

package_dir = Path(__file__).parent

if str(package_dir) not in sys.path:
    sys.path.append(str(package_dir))

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
