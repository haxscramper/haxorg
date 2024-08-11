from py_scriptutils.repo_files import get_haxorg_repo_root_path
import sys
from typing import TYPE_CHECKING
import os
from beartype import beartype
from beartype.typing import Optional, List
from dominate import tags
from numbers import Number
import copy

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


class svg(tags.html_tag):

    def __init__(self, width: int, height: int, *args, **kwargs):
        super().__init__(*args, width=width, height=height, **kwargs)


class svg_circle(tags.html_tag):
    tagname = "circle"


class svg_rect(tags.html_tag):
    tagname = "rect"

    def __init__(self, x: int, y: int, width: int, height: int, *args, **kwargs):
        super().__init__(*args, x=x, y=y, width=width, height=height, **kwargs)


class svg_text(tags.html_tag):
    tagname = "text"


@beartype
class SvgPathBuilder:

    def __init__(self):
        self.commands = []

    def move_to(self, x: Number, y: Number) -> 'SvgPathBuilder':
        self.commands.append(f"M {x:.3f} {y:.3f}")
        return self

    def line_to(self, x: Number, y: Number) -> 'SvgPathBuilder':
        self.commands.append(f"L {x:.3f} {y:.3f}")
        return self

    def curve_to(self, x1: Number, y1: Number, x2: Number, y2: Number, x: Number,
                 y: Number) -> 'SvgPathBuilder':
        self.commands.append(f"C {x1:.3f} {y1:.3f}, {x2:.3f} {y2:.3f}, {x:.3f} {y:.3f}")
        return self

    def close_path(self) -> 'SvgPathBuilder':
        self.commands.append("Z")
        return self

    def __str__(self) -> str:
        return " ".join(self.commands)


@beartype
def svg_path_cmd() -> SvgPathBuilder:
    return SvgPathBuilder()


@beartype
class svg_path(tags.html_tag):
    tagname = "path"

    def __init__(self, d: SvgPathBuilder, *args, **kwargs):
        super().__init__(*args, d=str(d), **kwargs)


@beartype
def toSvg(res: GraphLayoutIRResult) -> svg:
    r = 0
    result = svg(
        width=res.bbox.width + r,
        height=res.bbox.height + r,
        viewBox="0 0 {:.3f} {:.3f}".format(
            res.bbox.width + r,
            res.bbox.height + r,
        ),
    )

    for rect_idx, rect in enumerate(res.fixed):
        result.add(
            svg_rect(
                x=str(round(rect.left, ndigits=3)),
                y=str(round(rect.top, ndigits=3)),
                width=round(rect.width, ndigits=3),
                height=round(rect.height, ndigits=3),
                fill="none",
                stroke="black",
                stroke_width=2,
                rect_idx=str(rect_idx),
            ))

    for line_idx, line in enumerate(res.lines.values()):
        cmd = svg_path_cmd()
        for it in line.paths:
            cmd.move_to(it.points[0].x, it.points[0].y)
            for point in it.points[1:]:
                cmd.line_to(point.x, point.y)

            # cmd.close_path()
            # cmd.move_to(it.points[-1].x + x_offset, it.points[-1].y)

        result.add(
            svg_path(d=cmd,
                     stroke="black",
                     fill="none",
                     **{
                         "line-idx": str(line_idx),
                         "stroke-linecap": "butt",
                         "stroke-width": "1",
                         "fill-rule": "nonzero",
                         "stroke-linejoin": "miter",
                         "stroke-opacity": "1",
                         "stroke-miterlimit": "10",
                     }))

    return result


@beartype
def toSvgFileText(node: svg) -> str:
    tmp = copy.copy(node)
    tmp["xmlns"] = "http://www.w3.org/2000/svg"
    tmp["xmlns:xlink"] = "http://www.w3.org/1999/xlink"
    return "{}\n{}".format('<?xml version="1.0" encoding="UTF-8"?>', str(tmp))
