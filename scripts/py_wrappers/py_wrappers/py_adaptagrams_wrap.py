import copy
from numbers import Number
import os
import sys
from typing import TYPE_CHECKING

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Tuple
from dominate import tags
from py_scriptutils.repo_files import get_haxorg_repo_root_path
import py_scriptutils.svg_utils as svg

build_dir = get_haxorg_repo_root_path().joinpath("build/haxorg")
if str(build_dir) not in sys.path:
    sys.path.append(str(build_dir))

from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from py_wrappers.py_adaptagrams import *  # type: ignore
else:
    from py_adaptagrams import *


@beartype
class GraphLayout():

    def __init__(self) -> None:
        self.ir = GraphLayoutIR()

    def newAlignSpec(self,
                     node: int,
                     fixPos: Optional[float] = None,
                     offset: float = 0.0) -> GraphNodeConstraintAlignSpec:
        return GraphNodeConstraintAlignSpec(
            node=node,
            fixPos=fixPos,
            offset=float(offset),
        )

    def newAlign(
        self,
        specs: List[GraphNodeConstraintAlignSpec | int],
        dimension: GraphDimension,
    ) -> GraphNodeConstraintAlign:
        aligns: List[GraphNodeConstraintAlignSpec] = []
        for spec in specs:
            match spec:
                case GraphNodeConstraintAlignSpec():
                    aligns.append(spec)

                case int():
                    aligns.append(self.newAlignSpec(spec))

                case _:
                    raise TypeError(type(spec))

        return GraphNodeConstraintAlign(nodes=aligns, dimension=dimension)

    def newAlignX(
            self,
            specs: List[GraphNodeConstraintAlignSpec | int]) -> GraphNodeConstraintAlign:
        return self.newAlign(specs=specs, dimension=GraphDimension.XDIM)

    def newAlignY(
            self,
            specs: List[GraphNodeConstraintAlignSpec | int]) -> GraphNodeConstraintAlign:
        return self.newAlign(specs=specs, dimension=GraphDimension.YDIM)

    def alignDimN(self, specs: List[GraphNodeConstraintAlignSpec],
                  dimension: GraphDimension) -> None:
        self.ir.nodeConstraints.append(
            GraphNodeConstraint.InitAlignStatic(self.newAlign(specs, dimension)))

    def alignXDimN(self, specs: List[GraphNodeConstraintAlignSpec]) -> None:
        self.alignDimN(specs, GraphDimension.XDIM)

    def alignYDimN(self, specs: List[GraphNodeConstraintAlignSpec]) -> None:
        self.alignDimN(specs, GraphDimension.YDIM)

    def alignDim2(self, source: int, target: int, dimension: GraphDimension) -> None:
        self.ir.nodeConstraints.append(
            GraphNodeConstraint.InitAlignStatic(
                GraphNodeConstraintAlign(
                    nodes=[
                        GraphNodeConstraintAlignSpec(node=source),
                        GraphNodeConstraintAlignSpec(node=target),
                    ],
                    dimension=dimension,
                )))

    def alignXDim2(self, source: int, target: int) -> None:
        self.alignDim2(source, target, dimension=GraphDimension.XDIM)

    def alignYDim2(self, source: int, target: int) -> None:
        self.alignDim2(source, target, dimension=GraphDimension.YDIM)

    def edgePorts(self, source: int, target: int, sourcePort: GraphEdgeConstraintPort,
                  targetPort: GraphEdgeConstraintPort) -> None:
        self.ir.edgeConstraints[GraphEdge(
            source=source,
            target=target,
        )] = GraphEdgeConstraint(
            sourcePort=sourcePort,
            targetPort=targetPort,
        )

    def separate2(self,
                  left: GraphNodeConstraintAlign,
                  right: GraphNodeConstraintAlign,
                  dimension: GraphDimension,
                  distance: float = 1.0) -> None:
        self.ir.nodeConstraints.append(
            GraphNodeConstraint.InitSeparateStatic(
                GraphNodeConstraintSeparate(
                    left=left,
                    right=right,
                    separationDistance=float(distance),
                    dimension=dimension,
                )))

    def separateXDim2(self,
                      left: GraphNodeConstraintAlign,
                      right: GraphNodeConstraintAlign,
                      distance: float = 1.0) -> None:
        self.separate2(left=left,
                       right=right,
                       dimension=GraphDimension.XDIM,
                       distance=float(distance))

    def separateYDim2(self,
                      left: GraphNodeConstraintAlign,
                      right: GraphNodeConstraintAlign,
                      distance: float = 1.0) -> None:
        self.separate2(left=left,
                       right=right,
                       dimension=GraphDimension.YDIM,
                       distance=float(distance))

    def separateN(
        self,
        lines: List[GraphNodeConstraintAlign],
        dimension: GraphDimension,
        distance: float = 1.0,
        alignPairs: Optional[List[Tuple[int, int]]] = None,
        isExactSeparation: bool = False,
    ) -> GraphNodeConstraintMultiSeparate:
        pairs = [(i, i + 1)
                 for i in range(0,
                                len(lines) - 1)] if alignPairs is None else alignPairs
        constraint = GraphNodeConstraintMultiSeparate(
            lines=lines,
            separationDistance=float(distance),
            dimension=dimension,
            alignPairs=pairs,
            isExactSeparation=isExactSeparation,
        )

        self.ir.nodeConstraints.append(
            GraphNodeConstraint.InitMultiSeparateStatic(constraint))
        return constraint

    def pageBoundary(
        self,
        rects: List[int],
        boundary: GraphRect,
        weight: float = 100.0,
    ) -> GraphNodeConstraintPageBoundary:
        constraint = GraphNodeConstraintPageBoundary(
            rect=boundary,
            nodes=rects,
            weight=100,
        )

        self.ir.nodeConstraints.append(
            GraphNodeConstraint.InitPageBoundaryStatic(constraint))
        return constraint

    def separateXDimN(
        self,
        lines: List[GraphNodeConstraintAlign],
        distance: float = 1.0,
        alignPairs: Optional[List[Tuple[int, int]]] = None,
        isExactSeparation: bool = False,
    ) -> GraphNodeConstraintMultiSeparate:
        return self.separateN(
            lines=lines,
            dimension=GraphDimension.XDIM,
            distance=float(distance),
            alignPairs=alignPairs,
            isExactSeparation=isExactSeparation,
        )

    def separateYDimN(
        self,
        lines: List[GraphNodeConstraintAlign],
        distance: float = 1.0,
        alignPairs: Optional[List[Tuple[int, int]]] = None,
        isExactSeparation: bool = False,
    ) -> GraphNodeConstraintMultiSeparate:
        return self.separateN(
            lines=lines,
            dimension=GraphDimension.YDIM,
            distance=float(distance),
            alignPairs=alignPairs,
            isExactSeparation=isExactSeparation,
        )

    def edge(self, source: int, target: int) -> None:
        self.ir.edges.append(GraphEdge(source=source, target=target))

    def rect(self, width: int, height: int) -> int:
        res_idx = len(self.ir.rectangles)
        self.ir.rectangles.append(GraphSize(w=width, h=height))
        return res_idx


@beartype
def toSvg(
    res: GraphLayoutIRResult,
    draw_geometric_positions: bool = True,
    rect_debug_map: Dict[int, Dict[str, Any]] = dict(),
    edge_debug_map: Dict[Tuple[int, int], Dict[str, Any]] = dict(),
    draw_positions_inside: bool = True,
    grid_vertical_step: Optional[int] = 50,
    grid_horizontal_step: Optional[int] = 50,
    ir: Optional[GraphLayoutIR] = None,
) -> svg.svg:
    r = 10
    viewbox_width = res.bbox.width + r * 2
    viewbox_height = res.bbox.height + r * 2
    result = svg.svg(
        width=viewbox_width,
        height=viewbox_height,
        viewBox="0 0 {:.3f} {:.3f}".format(
            viewbox_width,
            viewbox_height,
        ),
    )

    grid_style = dict(
        stroke="black",
        stroke_width="0.25",
        stroke_dasharray="5, 10",
    )

    if grid_horizontal_step != None:
        for i in range(0, int(viewbox_width), grid_horizontal_step):
            result.add(svg.svg_line(
                x1=i,
                x2=i,
                y1=0,
                y2=viewbox_height,
                **grid_style,
            ))

    if grid_vertical_step != None:
        for i in range(0, int(viewbox_height), grid_vertical_step):
            result.add(svg.svg_line(
                x1=0,
                x2=viewbox_width,
                y1=i,
                y2=i,
                **grid_style,
            ))

    for rect_idx, rect in enumerate(res.fixed):
        rect_x = rect.left + r
        rect_y = rect.top + r
        if draw_geometric_positions:
            stext = svg.svg_text(f"", font_size="8px")
            stext.add(
                svg.svg_tspan(f"x:{rect.left:.0f} y:{rect.top:.0f}", dy="1.2em", x="0"))
            stext.add(
                svg.svg_tspan(f"w:{rect.width:.0f} h:{rect.height:.0f}",
                              dy="1.2em",
                              x="0"))
            stext.add(svg.svg_tspan(f"idx:{rect_idx}", dy="1.2em", x="0"))

            if rect_idx in rect_debug_map:
                for key, value in rect_debug_map[rect_idx].items():
                    stext.add(svg.svg_tspan(f"{key}:{value}", dy="1.2em", x="0"))

            if draw_positions_inside:
                sg = svg.svg_g(transform=f"translate({rect_x + 2:.0f}, {rect_y +2:.0f})")

            else:
                sg = svg.svg_g(transform=f"translate({rect_x - 50:.0f}, {rect_y:.0f})")

            sg.add(stext)
            result.add(sg)

        result.add(
            svg.svg_circle(
                x=str(round(rect_x, ndigits=3)),
                y=str(round(rect_y, ndigits=3)),
                r=3,
                fill="red",
            ))

        result.add(
            svg.svg_rect(
                x=str(round(rect_x, ndigits=3)),
                y=str(round(rect_y, ndigits=3)),
                width=round(rect.width, ndigits=3),
                height=round(rect.height, ndigits=3),
                fill="none",
                stroke="black",
                stroke_width=1,
                rect_idx=str(rect_idx),
            ))

    for line_idx, line in enumerate(res.lines.values()):
        cmd = svg.svg_path_cmd()
        for it in line.paths:
            cmd.move_to(it.points[0].x + r, it.points[0].y + r)
            for point in it.points[1:]:
                cmd.line_to(point.x + r, point.y + r)

            # cmd.close_path()
            # cmd.move_to(it.points[-1].x + x_offset, it.points[-1].y)

        result.add(
            svg.svg_path(
                d=cmd,
                stroke="black",
                fill="none",
                line_idx=str(line_idx),
                stroke_linecap="butt",
                stroke_width="1",
                fill_rule="nonzero",
                stroke_linejoin="miter",
                stroke_opacity="1",
                stroke_miterlimit="10",
            ))

    if ir:
        for c in ir.nodeConstraints:
            match c.getKind():
                case GraphNodeConstraintKind.PageBoundary:
                    b = c.getPageBoundary()
                    result.add(
                        svg.svg_rect(
                            x=str(round(b.rect.left + r, ndigits=3)),
                            y=str(round(b.rect.top + r, ndigits=3)),
                            width=str(round(b.rect.width, ndigits=3)),
                            height=str(round(b.rect.height, ndigits=3)),
                            fill="none",
                            stroke="blue",
                        ))

                case _:
                    pass

    return result
