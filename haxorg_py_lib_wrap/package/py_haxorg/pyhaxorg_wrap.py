from typing import TYPE_CHECKING

from beartype import beartype

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
