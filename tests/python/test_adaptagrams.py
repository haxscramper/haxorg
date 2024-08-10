import py_wrappers.py_adaptagrams_wrap as wrap

from pprint import pprint
from py_scriptutils.script_logging import to_debug_json


def test_1():
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


def test_2():
    ir = wrap.GraphLayout()
    ir.edge(0, 1)
    ir.edge(1, 2)
    ir.edge(2, 3)
    for _ in range(0, 4):
        ir.rect(5, 5)

    ir.alignXDim(0, 1)
    ir.alignYDim(1, 3)
    conv = ir.ir.doColaConvert()
    assert len(conv.fixed) == 4
    assert len(conv.lines) == 3
    assert conv.fixed[1].top == conv.fixed[3].top
    assert conv.fixed[0].left == conv.fixed[1].left

    pprint(to_debug_json(conv))
