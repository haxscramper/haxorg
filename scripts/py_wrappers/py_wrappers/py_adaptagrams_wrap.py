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
    from py_wrappers.py_adaptagrams import *
else:
    print(os.getenv("LD_PRELOAD"))
    from py_adaptagrams import *


@beartype
class GraphLayout():

    def __init__(self) -> None:
        self.ir = GraphLayoutIR()

    def alignDim(self, source: int, target: int, dimension: GraphDimension):
        self.ir.constraints.append(
            GraphConstraint.InitAlignStatic(
                GraphConstraintAlign(
                    nodes=[
                        GraphConstraintAlignSpec(node=source),
                        GraphConstraintAlignSpec(node=target),
                    ],
                    dimension=dimension,
                )))

    def alignXDim(self, source: int, target: int):
        self.alignDim(source, target, dimension=GraphDimension.XDIM)

    def alignYDim(self, source: int, target: int):
        self.alignDim(source, target, dimension=GraphDimension.YDIM)

    def edge(self, source: int, target: int):
        self.ir.edges.append(GraphEdge(source=source, target=target))

    def rect(self, width: int, height: int):
        self.ir.rectangles.append(GraphSize(w=width, h=height))
