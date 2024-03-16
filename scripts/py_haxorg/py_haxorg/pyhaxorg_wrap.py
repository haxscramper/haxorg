from py_scriptutils.repo_files import get_haxorg_repo_root_path
import sys 
from typing import TYPE_CHECKING

build_dir = get_haxorg_repo_root_path().joinpath("build/haxorg")   
if str(build_dir) not in sys.path:
    sys.path.append(str(build_dir))

from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from py_haxorg.pyhaxorg import *
else:
    from pyhaxorg import *

SemSet = set[OrgSemKind]

def treeRepr(node: Org, colored: bool = True) -> str:
    return exportToTreeString(node, OrgTreeExportOpts(withColor=colored))
