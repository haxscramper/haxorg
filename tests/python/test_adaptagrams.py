import py_wrappers.py_adaptagrams_wrap as wrap

from pprint import pprint, pformat
from py_scriptutils.script_logging import to_debug_json, pprint_to_file
from pathlib import Path
from dataclasses import dataclass, field
from beartype import beartype
from beartype.typing import List, Optional, Tuple, Dict, Any
import pytest


def make_disconnected_graph(count: int, mult: int) -> wrap.GraphLayout:
    ir = wrap.GraphLayout()

    for i in range(0, count):
        ir.rect(20 * mult, 20 * mult)

    ir.ir.width = 100 * mult
    ir.ir.height = 100 * mult

    return ir


def make_chain_graph(count: int, mult: int) -> wrap.GraphLayout:
    ir = make_disconnected_graph(count=count, mult=mult)
    for i in range(0, count - 1):
        ir.edge(i, i + 1)

    return ir


class ConvTest():

    def __init__(self, conv: wrap.GraphLayout) -> None:
        self.conv = conv.ir.doColaConvert()
        self.ir = conv.ir

    def rect(self, idx: int) -> wrap.GraphRect:
        return self.conv.fixed[idx]

    def rect_center(self, idx: int) -> wrap.GraphPoint:
        r = self.rect(idx)
        return wrap.GraphPoint(x=r.left + r.width / 2, y=r.top + r.height / 2)

    def path(self, source: int, target: int) -> wrap.GraphLayoutIREdge:
        return self.conv.lines[wrap.GraphEdge(source=source, target=target)]

    def debug(
            self,
            rect_debug_map: Dict[int, Dict[str, Any]] = dict(),
    ):
        dump = to_debug_json(self.conv, skip_cyclic_data=False)
        pre_fmt = pformat(dump, width=120)

        def aux(it):
            match it:
                case dict():
                    if "x" in it:
                        it["x"] = it["x"] - self.conv.bbox.left

                    if "y" in it:
                        it["y"] = it["y"] - self.conv.bbox.top

                    for key, value in it.items():
                        if isinstance(value, float):
                            it[key] = round(value, ndigits=3)

                        else:
                            aux(value)

                case list() | tuple():
                    for item in it:
                        aux(item)

                case float() | int() | str() | None:
                    pass

                case _:
                    raise TypeError(str(type(it)))

        aux(dump)

        post_fmt = pformat(dump, width=120)
        Path("/tmp/dbg.txt").write_text(f"{pre_fmt}\n{post_fmt}")
        sformat = str(
            wrap.svg.toSvgFileText(
                wrap.toSvg(
                    self.conv,
                    rect_debug_map=rect_debug_map,
                    ir=self.ir,
                )))
        # print(sformat)
        Path("/tmp/result2.svg").write_text(sformat)
        # self.conv.doColaSvgWrite("/tmp/result.svg")


def test_ir_align_two():
    ir = wrap.GraphLayoutIR()
    ir.edges.append(wrap.GraphEdge(source=0, target=1))
    ir.edges.append(wrap.GraphEdge(source=1, target=2))
    ir.edges.append(wrap.GraphEdge(source=2, target=3))
    ir.rectangles.append(wrap.GraphSize(w=5, h=5))
    ir.rectangles.append(wrap.GraphSize(w=5, h=5))
    ir.rectangles.append(wrap.GraphSize(w=5, h=5))
    ir.rectangles.append(wrap.GraphSize(w=5, h=5))

    ir.nodeConstraints.append(
        wrap.GraphNodeConstraint.InitAlignStatic(
            wrap.GraphNodeConstraintAlign(
                nodes=[
                    wrap.GraphNodeConstraintAlignSpec(node=0),
                    wrap.GraphNodeConstraintAlignSpec(node=1),
                ],
                dimension=wrap.GraphDimension.XDIM,
            )))

    ir.nodeConstraints.append(
        wrap.GraphNodeConstraint.InitAlignStatic(
            wrap.GraphNodeConstraintAlign(
                nodes=[
                    wrap.GraphNodeConstraintAlignSpec(node=1),
                    wrap.GraphNodeConstraintAlignSpec(node=3),
                ],
                dimension=wrap.GraphDimension.YDIM,
            )))

    conv = ir.doColaConvert()
    assert len(conv.fixed) == 4
    assert len(conv.lines) == 3


def test_py_util_align_two():
    ir = wrap.GraphLayout()
    ir.edge(0, 1)
    ir.edge(1, 2)
    ir.edge(2, 3)
    for _ in range(0, 4):
        ir.rect(5, 5)

    ir.alignXDim2(0, 1)
    ir.alignYDim2(1, 3)
    conv = ir.ir.doColaConvert()
    assert len(conv.fixed) == 4
    assert len(conv.lines) == 3
    assert conv.fixed[1].top == conv.fixed[3].top
    assert conv.fixed[0].left == conv.fixed[1].left


def test_py_util_align_many():
    ir = wrap.GraphLayout()
    ir.edge(0, 1)
    ir.edge(1, 2)
    ir.edge(2, 3)
    ir.edge(3, 4)
    ir.edge(4, 5)
    ir.edge(5, 6)
    for _ in range(0, 7):
        ir.rect(5, 5)

    ir.alignXDimN([
        ir.newAlignSpec(0),
        ir.newAlignSpec(1),
        ir.newAlignSpec(2),
    ])

    ir.alignYDimN([
        ir.newAlignSpec(2),
        ir.newAlignSpec(4),
        ir.newAlignSpec(5),
    ])

    ir.alignXDimN([
        ir.newAlignSpec(5),
        ir.newAlignSpec(6),
    ])

    conv = ir.ir.doColaConvert()

    def rect(idx: int) -> wrap.GraphRect:
        return conv.fixed[idx]

    assert len(set([rect(0).left, rect(1).left, rect(2).left])) == 1
    assert len(set([rect(2).top, rect(4).top, rect(5).top])) == 1
    assert len(set([rect(5).left, rect(6).left])) == 1


def test_align_axis_separation():
    ir = wrap.GraphLayout()
    mult = 5
    ir.edge(0, 1)
    ir.edge(1, 2)
    ir.edge(2, 3)
    ir.edge(3, 4)
    ir.rect(20 * mult, 20 * mult)
    ir.rect(15 * mult, 15 * mult)
    ir.rect(10 * mult, 10 * mult)
    ir.rect(5 * mult, 5 * mult)
    ir.rect(5 * mult, 5 * mult)

    ir.alignXDimN([
        ir.newAlignSpec(0, offset=50.0 * mult),
        ir.newAlignSpec(1, offset=-50.0 * mult),
        ir.newAlignSpec(2, offset=20.0 * mult),
        ir.newAlignSpec(3),
        ir.newAlignSpec(4),
    ])

    ir.ir.width = 100 * mult
    ir.ir.height = 100 * mult

    t = ConvTest(ir)
    assert t.rect(3).left == t.rect(4).left

    path_01 = t.path(3, 4)
    assert len(path_01.paths) == 1
    assert len(path_01.paths[0].points) == 2
    path_01_first = path_01.paths[0].points[0]
    path_01_last = path_01.paths[0].points[1]

    assert path_01_first.x == path_01_last.x

    assert path_01_last.x == t.rect_center(3).x
    assert int(t.rect_center(3).x + 20 * mult) == int(t.rect_center(2).x)
    assert int(t.rect_center(3).x - 50 * mult) == int(t.rect_center(1).x)
    assert int(t.rect_center(3).x + 50 * mult) == int(t.rect_center(0).x)
    assert int(t.rect_center(4).x) == int(t.rect_center(3).x)


def test_align_axis_separate_2():
    mult = 5
    ir = make_chain_graph(6, mult)

    ir.separateXDim2(
        left=ir.newAlignX([
            ir.newAlignSpec(0),
            ir.newAlignSpec(1),
        ]),
        right=ir.newAlignX([
            ir.newAlignSpec(2),
            ir.newAlignSpec(3),
        ]),
        distance=50 * mult,
    )

    ir.alignYDimN([
        ir.newAlignSpec(3),
        ir.newAlignSpec(4),
        ir.newAlignSpec(5),
    ])

    t = ConvTest(ir)


def test_align_axis_multi_separate_equal_sizes():
    mult = 5
    ir = make_disconnected_graph(9, mult)

    ir.separateXDimN(
        lines=[
            ir.newAlignX([
                ir.newAlignSpec(0),
                ir.newAlignSpec(3),
                ir.newAlignSpec(6),
            ]),
            ir.newAlignX([
                ir.newAlignSpec(1),
                ir.newAlignSpec(4),
                ir.newAlignSpec(7),
            ]),
            ir.newAlignX([
                ir.newAlignSpec(2),
                ir.newAlignSpec(5),
                ir.newAlignSpec(8),
            ]),
        ],
        distance=50 * mult,
    )

    ir.separateYDimN(
        lines=[
            ir.newAlignY([
                ir.newAlignSpec(0),
                ir.newAlignSpec(1),
                ir.newAlignSpec(2),
            ]),
            ir.newAlignY([
                ir.newAlignSpec(3),
                ir.newAlignSpec(4),
                ir.newAlignSpec(5),
            ]),
            ir.newAlignY([
                ir.newAlignSpec(6),
                ir.newAlignSpec(7),
                ir.newAlignSpec(8),
            ]),
        ],
        distance=50 * mult,
    )

    t = ConvTest(ir)
    t.debug()


def test_align_axis_multi_separate_different_sizes():
    mult = 5
    ir = wrap.GraphLayout()

    for i in range(0, 9):
        ir.rect(5 * mult * (i + 1), 2 * mult * (i + 1))

    ir.ir.width = 100 * mult
    ir.ir.height = 100 * mult

    ir.separateXDimN(
        lines=[
            ir.newAlignX([
                ir.newAlignSpec(0),
                ir.newAlignSpec(3),
                ir.newAlignSpec(6),
            ]),
            ir.newAlignX([
                ir.newAlignSpec(1),
                ir.newAlignSpec(4),
                ir.newAlignSpec(7),
            ]),
            ir.newAlignX([
                ir.newAlignSpec(2),
                ir.newAlignSpec(5),
                ir.newAlignSpec(8),
            ]),
        ],
        distance=100 * mult,
    )

    ir.separateYDimN(
        lines=[
            ir.newAlignY([
                ir.newAlignSpec(0),
                ir.newAlignSpec(1),
                ir.newAlignSpec(2),
            ]),
            ir.newAlignY([
                ir.newAlignSpec(3),
                ir.newAlignSpec(4),
                ir.newAlignSpec(5),
            ]),
            ir.newAlignY([
                ir.newAlignSpec(6),
                ir.newAlignSpec(7),
                ir.newAlignSpec(8),
            ]),
        ],
        distance=50 * mult,
    )

    t = ConvTest(ir)
    t.debug()


def test_node_pin_connections():
    mult = 5
    ir = wrap.GraphLayout()
    shape1 = ir.rect(20 * mult, 20 * mult)
    shape2 = ir.rect(20 * mult, 20 * mult)
    shape3 = ir.rect(20 * mult, 20 * mult)

    ir.edge(shape1, shape3)
    ir.edge(shape2, shape3)

    ir.edgePorts(
        shape1,
        shape3,
        sourcePort=wrap.GraphEdgeConstraintPort.East,
        targetPort=wrap.GraphEdgeConstraintPort.West,
    )

    ir.edgePorts(
        shape2,
        shape3,
        sourcePort=wrap.GraphEdgeConstraintPort.East,
        targetPort=wrap.GraphEdgeConstraintPort.West,
    )

    ir.separateXDim2(
        left=ir.newAlignX([shape1, shape2]),
        right=ir.newAlignX([shape3]),
        distance=50 * mult,
    )

    ir.ir.width = 100 * mult
    ir.ir.height = 100 * mult
    ir.ir.doColaSvgWrite("/tmp/test_node_pin_connections.svg")

    t = ConvTest(ir)
    t.debug()


@beartype
@dataclass
class Tree():
    content: List[str] = field(default_factory=list)
    sub: List["Tree"] = field(default_factory=list)


@beartype
@dataclass
class Cell():
    content: str
    rect_idx: int = -1


def test_tree_sheet_constraint():
    mult = 5
    ir = wrap.GraphLayout()

    tree = Tree(sub=[
        Tree(sub=[
            Tree(content=["AA", "AB", "AC", "AD"]),
            Tree(content=["BA", "BB", "BC", "BD"]),
            Tree(content=["CA", "CB", "CC", "CD"]),
        ]),
        Tree(sub=[
            Tree(content=["RR", "RE", "RL", "RQ"]),
            Tree(content=["ER", "EE", "EL", "EQ"]),
            Tree(content=["LR", "LE", "LL", "LQ"]),
        ]),
    ])

    def get_depth(t: Tree):
        subs = [get_depth(s) for s in t.sub]
        if 1 < len(subs):
            return max(*subs) + 1

        elif len(subs) == 1:
            return subs[0] + 1

        else:
            return 1

    def get_cols(t: Tree):
        subs = [get_cols(s) for s in t.sub]
        if len(subs) == 1:
            return max(subs[0], len(t.content))

        elif 1 < len(subs):
            return max(max(*subs), len(t.content))

        else:
            return len(t.content)

    def get_rows(t: Tree):
        res = sum(get_rows(s) for s in t.sub) + 1
        if 0 < len(t.content):
            res += 1

        return res

    max_depth = get_depth(tree)
    col_count = max_depth + get_cols(tree)
    row_count = get_rows(tree) + 1

    #[row][col]
    grid: List[List[Optional[Cell]]] = [[None] * col_count for _ in range(0, row_count)]
    dfs_row: int = 0

    rect_debug_map: Dict[int, Dict[str, Any]] = dict()

    def aux(t: Tree, level: int):
        nonlocal dfs_row
        this_row = dfs_row
        rect = ir.rect(width=20 * mult, height=10 * mult)
        grid[dfs_row][level] = Cell(content="**", rect_idx=rect)

        rect_debug_map[rect] = dict(pos=f"{dfs_row}/{level}")

        if 0 < len(t.content):
            dfs_row += 1
            for cell_idx, cell in enumerate(t.content):
                rect = ir.rect(width=20 * mult, height=10 * mult)
                grid[dfs_row][max_depth + cell_idx] = Cell(content=cell, rect_idx=rect)
                rect_debug_map[rect] = dict(pos=f"{dfs_row}/{max_depth + cell_idx}")

            source_rect = grid[this_row][level].rect_idx
            target_rect = grid[dfs_row][max_depth].rect_idx

            ir.edge(source=source_rect, target=target_rect)
            ir.edgePorts(
                source=source_rect,
                target=target_rect,
                sourcePort=wrap.GraphEdgeConstraintPort.South,
                targetPort=wrap.GraphEdgeConstraintPort.West,
            )

            for cell_idx in range(0, len(t.content) - 1):
                source_rect = grid[dfs_row][max_depth + cell_idx].rect_idx
                target_rect = grid[dfs_row][max_depth + cell_idx + 1].rect_idx

                ir.edge(source=source_rect, target=target_rect)
                ir.edgePorts(
                    source=source_rect,
                    target=target_rect,
                    sourcePort=wrap.GraphEdgeConstraintPort.East,
                    targetPort=wrap.GraphEdgeConstraintPort.West,
                )

        dfs_row += 1
        sub_rows: List[int] = []

        for s in t.sub:
            sub_rows.append(dfs_row)
            aux(s, level + 1)

        for row in sub_rows:
            source_rect = grid[this_row][level].rect_idx
            target_rect = grid[row][level + 1].rect_idx

            ir.edge(source=source_rect, target=target_rect)
            ir.edgePorts(
                source=source_rect,
                target=target_rect,
                sourcePort=wrap.GraphEdgeConstraintPort.South,
                targetPort=wrap.GraphEdgeConstraintPort.West,
            )

    aux(tree, 0)

    y_aligns: List[wrap.GraphNodeConstraintAlign] = []
    x_aligns: List[wrap.GraphNodeConstraintAlign] = []

    grid_fmt = "\n".join(" ".join(
        f"{cell.rect_idx:>02} {cell.content}" if cell else "_____"
        for cell in row)
                         for row in grid)

    for row in grid:
        row_nodes: List[int] = [cell.rect_idx for cell in row if cell]
        if 0 < len(row_nodes):
            y_aligns.append(ir.newAlignY(row_nodes))

    ir.separateYDimN(
        y_aligns,
        distance=15 * mult,
        isExactSeparation=True,
    )

    for col in range(0, col_count):
        col_nodes: List[int] = [row[col].rect_idx for row in grid if row[col]]
        if 0 < len(col_nodes):
            pass
            x_aligns.append(ir.newAlignX(col_nodes))

    ir.separateXDimN(
        x_aligns,
        distance=30 * mult,
        isExactSeparation=True,
    )

    ir.ir.width = 150 * mult
    ir.ir.height = 100 * mult
    ir.ir.leftBBoxMargin = 100

    t = ConvTest(ir)
    t.debug(rect_debug_map)

    def rect_at(row: int, col: int) -> int:
        return grid[row][col].rect_idx

    assert rect_at(0, 0) == 0

    # Roughly assert the edge shape between main root node and the second
    # subtree of the main root -- it must have an L-shape and two segments
    path_0_1 = t.path(rect_at(0, 0), rect_at(8, 1)).paths[0]
    assert len(path_0_1.points) == 3
    assert int(path_0_1.points[0].x) == int(path_0_1.points[1].x)
    assert int(path_0_1.points[1].y) == int(path_0_1.points[2].y)


def test_page_boundary():
    mult = 5
    ir = wrap.GraphLayout()
    ir.ir.width = 150 * mult
    ir.ir.height = 100 * mult

    r1 = ir.rect(width=10 * mult, height=10 * mult)
    r2 = ir.rect(width=10 * mult, height=10 * mult)
    r3 = ir.rect(width=10 * mult, height=10 * mult)
    r4 = ir.rect(width=10 * mult, height=10 * mult)

    ir.edge(r1, r2)
    ir.edge(r3, r4)

    # ir.pageBoundary(
    #     [r1, r2],
    #     wrap.GraphRect(left=0, top=0, width=40 * mult, height=40 * mult),
    #     weight=10,
    # )

    # ir.pageBoundary(
    #     [r3, r4],
    #     wrap.GraphRect(left=50 * mult, top=0, width=40 * mult, height=40 * mult),
    #     weight=10,
    # )

    t = ConvTest(ir)
    t.debug()


if __name__ == "__main__":
    test_tree_sheet_constraint()
