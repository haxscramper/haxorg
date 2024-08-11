import py_wrappers.py_adaptagrams_wrap as wrap

from pprint import pprint
from py_scriptutils.script_logging import to_debug_json
from pathlib import Path

class ConvTest():
    def __init__(self, conv: wrap.GraphLayoutIRResult) -> None:
        self.conv = conv

    def rect(self, idx: int) -> wrap.GraphRect:
        return self.conv.fixed[idx]

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
        ir.alignSpec(0),
        ir.alignSpec(1),
        ir.alignSpec(2),
    ])

    ir.alignYDimN([
        ir.alignSpec(2),
        ir.alignSpec(4),
        ir.alignSpec(5),
    ])

    ir.alignXDimN([
        ir.alignSpec(5),
        ir.alignSpec(6),
    ])

    conv = ir.ir.doColaConvert()

    def rect(idx: int) -> wrap.GraphRect:
        return conv.fixed[idx]

    assert len(set([rect(0).left, rect(1).left, rect(2).left])) == 1
    assert len(set([rect(2).top, rect(4).top, rect(5).top])) == 1
    assert len(set([rect(5).left, rect(6).left])) == 1

def test_align_axis_separation():
    ir = wrap.GraphLayout()
    ir.edge(0, 1)
    ir.edge(1, 2)
    ir.edge(2, 3)
    ir.edge(3, 4)
    ir.rect(20, 20)
    ir.rect(15, 15)
    ir.rect(10, 10)
    ir.rect(5, 5)
    ir.rect(5, 5)
    

    ir.alignXDimN([
        ir.alignSpec(0, offset=50.0),
        ir.alignSpec(1, offset=-50.0),
        ir.alignSpec(2, offset=20.0),
        ir.alignSpec(3),
        ir.alignSpec(4),
    ])

    t = ConvTest(ir.ir.doColaConvert())
    sformat = str(wrap.toSvgFileText(wrap.toSvg(t.conv)))
    # print(sformat)
    Path("/tmp/result2.svg").write_text(sformat)
    center = t.rect(3).left
    ir.ir.doColaSvgWrite("/tmp/result.svg")
    assert t.rect(3).left == t.rect(4).left
    assert (t.rect(3).left + t.rect(3).width) == (t.rect(2).left + 20)
