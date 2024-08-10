import py_wrappers.py_adaptagrams_wrap as wrap


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
    print(conv)
