import py_wrappers.py_adaptagrams_wrap as wrap

from pprint import pprint, pformat
from py_scriptutils.script_logging import to_debug_json
from pathlib import Path


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

    def __init__(self, conv: wrap.GraphLayoutIRResult) -> None:
        self.conv = conv

    def rect(self, idx: int) -> wrap.GraphRect:
        return self.conv.fixed[idx]

    def rect_center(self, idx: int) -> wrap.GraphPoint:
        r = self.rect(idx)
        return wrap.GraphPoint(x=r.left + r.width / 2, y=r.top + r.height / 2)

    def path(self, source: int, target: int) -> wrap.GraphLayoutIREdge:
        return self.conv.lines[wrap.GraphEdge(source=source, target=target)]

    def debug(self):
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
        sformat = str(wrap.toSvgFileText(wrap.toSvg(self.conv)))
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

    ir.constraints.append(
        wrap.GraphConstraint.InitAlignStatic(
            wrap.GraphConstraintAlign(
                nodes=[
                    wrap.GraphConstraintAlignSpec(node=0),
                    wrap.GraphConstraintAlignSpec(node=1),
                ],
                dimension=wrap.GraphDimension.XDIM,
            )))

    ir.constraints.append(
        wrap.GraphConstraint.InitAlignStatic(
            wrap.GraphConstraintAlign(
                nodes=[
                    wrap.GraphConstraintAlignSpec(node=1),
                    wrap.GraphConstraintAlignSpec(node=3),
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

    t = ConvTest(ir.ir.doColaConvert())
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

    t = ConvTest(ir.ir.doColaConvert())


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

    t = ConvTest(ir.ir.doColaConvert())
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

    t = ConvTest(ir.ir.doColaConvert())
    t.debug()
