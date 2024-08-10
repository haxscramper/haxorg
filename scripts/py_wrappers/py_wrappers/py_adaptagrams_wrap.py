from py_scriptutils.repo_files import get_haxorg_repo_root_path
import sys
from typing import TYPE_CHECKING
import os
from beartype import beartype
from beartype.typing import Optional, List

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

    def alignSpec(self,
                  node: int,
                  fixPos: Optional[float] = None,
                  offset: float = 0.0) -> GraphConstraintAlignSpec:
        return GraphConstraintAlignSpec(node=node, fixPos=fixPos, offset=offset)

    def alignDimN(self, specs: List[GraphConstraintAlignSpec], dimension: GraphDimension):
        self.ir.constraints.append(
            GraphConstraint.InitAlignStatic(
                GraphConstraintAlign(
                    nodes=specs,
                    dimension=dimension,
                )))

    def alignXDimN(self, specs: List[GraphConstraintAlignSpec]):
        self.alignDimN(specs, GraphDimension.XDIM)

    def alignYDimN(self, specs: List[GraphConstraintAlignSpec]):
        self.alignDimN(specs, GraphDimension.YDIM)

    def alignDim2(self, source: int, target: int, dimension: GraphDimension):
        self.ir.constraints.append(
            GraphConstraint.InitAlignStatic(
                GraphConstraintAlign(
                    nodes=[
                        GraphConstraintAlignSpec(node=source),
                        GraphConstraintAlignSpec(node=target),
                    ],
                    dimension=dimension,
                )))

    def alignXDim2(self, source: int, target: int):
        self.alignDim2(source, target, dimension=GraphDimension.XDIM)

    def alignYDim2(self, source: int, target: int):
        self.alignDim2(source, target, dimension=GraphDimension.YDIM)

    def edge(self, source: int, target: int):
        self.ir.edges.append(GraphEdge(source=source, target=target))

    def rect(self, width: int, height: int):
        self.ir.rectangles.append(GraphSize(w=width, h=height))