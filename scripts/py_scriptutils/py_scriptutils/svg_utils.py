import copy
from numbers import Number

from beartype import beartype
from beartype.typing import Any
from beartype.typing import Dict
from dominate import tags


def rename_kwargs_for_svg(kwargs: Dict[str, Any]) -> Dict[str, Any]:
    result = {}
    for key, value in kwargs.items():
        result[key.replace("_", "-")] = value

    return result


class svg(tags.html_tag):

    def __init__(self, width: int, height: int, *args: Any, **kwargs: Any) -> None:
        super().__init__(
            *args,
            width=width,
            height=height,
            **rename_kwargs_for_svg(kwargs),
        )


class svg_circle(tags.html_tag):
    tagname = "circle"

    def __init__(self, x: int, y: int, r: int, *args: Any, **kwargs: Any) -> None:
        super().__init__(*args, cx=x, cy=y, r=r, **rename_kwargs_for_svg(kwargs))


class svg_rect(tags.html_tag):
    tagname = "rect"

    def __init__(self, x: int, y: int, width: int, height: int, *args: Any,
                 **kwargs: Any) -> None:
        super().__init__(
            *args,
            x=x,
            y=y,
            width=width,
            height=height,
            **rename_kwargs_for_svg(kwargs),
        )


class svg_text(tags.html_tag):
    tagname = "text"

    def __init__(self, text: str, *args: Any, **kwargs: Any) -> None:
        super().__init__(text, *args, **rename_kwargs_for_svg(kwargs))


class svg_line(tags.html_tag):
    tagname = "line"

    def __init__(self, x1: Number, y1: Number, x2: Number, y2: Number, *args: Any,
                 **kwargs: Any) -> None:
        super().__init__(
            x1=x1,
            x2=x2,
            y1=y1,
            y2=y2,
            *args,
            **rename_kwargs_for_svg(kwargs),
        )


class svg_tspan(tags.html_tag):
    tagname = "tspan"

    def __init__(self, text: str, *args: Any, **kwargs: Any) -> None:
        super().__init__(text, *args, **rename_kwargs_for_svg(kwargs))


class svg_g(tags.html_tag):
    tagname = "g"

    def __init__(self, *args: Any, **kwargs: Any) -> None:
        super().__init__(*args, **rename_kwargs_for_svg(kwargs))


@beartype
class SvgPathBuilder:

    def __init__(self) -> None:
        self.commands: list[str] = []

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

    def __init__(self, d: SvgPathBuilder, *args: Any, **kwargs: Any) -> None:
        super().__init__(*args, d=str(d), **rename_kwargs_for_svg(kwargs))


@beartype
def toSvgFileText(node: svg) -> str:
    tmp = copy.copy(node)
    tmp["xmlns"] = "http://www.w3.org/2000/svg"
    tmp["xmlns:xlink"] = "http://www.w3.org/1999/xlink"
    return "{}\n{}".format('<?xml version="1.0" encoding="UTF-8"?>', str(tmp))
