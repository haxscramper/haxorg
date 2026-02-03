from pathlib import Path
from pprint import pformat

from beartype.typing import Any
from beartype.typing import Dict
from py_scriptutils.script_logging import to_debug_json
from py_wrappers.py_adaptagrams_wrap import *
import py_wrappers.py_adaptagrams_wrap as wrap


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
    ) -> None:
        dump = to_debug_json(self.conv, skip_cyclic_data=False)
        pre_fmt = pformat(dump, width=120)

        def aux(it: Any) -> None:
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
