from dataclasses import dataclass
from numbers import Number
from pathlib import Path
from typing import TypeAlias

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional
import py_haxorg.astbuilder.astbuilder_base as base
from py_haxorg.layout.wrap import BlockId, TextLayout
from py_scriptutils.algorithm import cond, maybe_splice
from pydantic import BaseModel
import toml


class TypstPackageFields(BaseModel):
    name: str
    version: str
    entrypoint: str
    authors: List[str]
    license: str
    description: str


class TypstPackageModel(BaseModel):
    package: TypstPackageFields


def get_typst_export_package(path: Path) -> TypstPackageModel:
    return TypstPackageModel.model_validate(toml.loads(path.read_text()))


@beartype
class RawStr():

    def __init__(self, value: str) -> None:
        self.value = value


@beartype
class RawBlock():

    def __init__(self, value: BlockId) -> None:
        self.value = value


@beartype
@dataclass
class RawLiteral():
    value: str


AnyBlock: TypeAlias = BlockId | List[BlockId] | RawBlock | List[RawBlock]
AnySingleValue: TypeAlias = BlockId | str | RawBlock | RawStr | RawLiteral


@beartype
class ASTBuilder(base.AstbuilderBase):

    def __init__(self, in_b: Optional[TextLayout] = None) -> None:
        b = in_b if in_b else TextLayout()
        super().__init__(b)

    def string(self, node: str | BlockId) -> BlockId:
        if isinstance(node, str):
            return self.b.text(node)

        else:
            return node

    def toBlockList(self, blocks: AnyBlock) -> List[BlockId]:
        match blocks:
            case int():
                return [blocks]

            case RawBlock():
                return [blocks.value]

            case list():
                result = []
                for it in blocks:
                    match it:
                        case int():
                            result.append(it)

                        case RawBlock():
                            result.append(it.value)

                        case _:
                            raise TypeError(type(it))

                return result

            case _:
                raise TypeError(type(blocks))

    def escape(self, text: str) -> str:
        res = ""
        for ch in text:
            if ch in ["@", "#", "<", "*", "[", "$", "]"]:
                res += "\\" + ch

            else:
                res += ch

        return res

    def escape_str_lit(self, text: str) -> str:
        res = ""
        for ch in text:
            if ch in ["\""]:
                res += "\\" + ch

            else:
                res += ch

        return res

    def surround(self, text: str, nodes: List[BlockId]) -> BlockId:
        return self.line(self.string(text), *nodes, self.string(text))

    def content(self, content: AnyBlock, isLine: bool = True) -> BlockId:
        if isLine:
            return self.line(
                self.string("["),
                *self.toBlockList(content),
                self.string("]"),
            )

        else:
            return self.stack(
                self.string("["),
                self.indent(2, *self.toBlockList(content)),
                self.string("]"),
            )

    def place(
        self,
        anchor: str,
        dx: str | Number,
        dy: str | Number,
        body: BlockId,
        isLine: bool = False,
    ) -> BlockId:
        return self.call(
            "place",
            positional=[self.litRaw(anchor)],
            post_positional=[self.litRaw(body)],
            args=dict(dx=self.litPt(dx), dy=self.litPt(dy)),
            isLine=isLine,
        )

    def set(self, name: str, args: Dict[str, AnySingleValue] = dict()) -> BlockId:
        return self.cmd("set", self.call(
            name=name,
            args=args,
            isFirst=False,
            isLine=True,
        ))

    def cmd(self, name: str, body: BlockId) -> BlockId:
        return self.line(self.string(f"#{name} "), body)

    def litRaw(self, value: str | BlockId) -> RawStr | RawBlock:
        if isinstance(value, str):
            return RawStr(value)

        else:
            return RawBlock(value)

    def add_at(self, target: BlockId, other: BlockId | List[BlockId]) -> None:
        self.b.add_at(target, other)

    def litPt(self, value: Number) -> RawStr:
        return RawStr(f"{value}pt")

    def call(
        self,
        name: str,
        args: Dict[str, AnySingleValue | List[AnySingleValue]] = dict(),
        body: AnyBlock = list(),
        positional: List[AnySingleValue] | AnySingleValue = list(),
        post_positional: List[AnySingleValue] | AnySingleValue = list(),
        isContent: bool = False,
        isLine: bool = False,
        isFirst: bool = True,
    ) -> BlockId:
        body_list: List[BlockId | RawBlock] = body if isinstance(body, list) else [body]
        b: List[BlockId] = [
            (it.value if isinstance(it, RawBlock) else it) for it in body_list
        ]
        arglist = []

        prefix = "#" if isFirst else ""

        def add_direct_arglist(values: List[AnySingleValue] | AnySingleValue) -> None:
            if isinstance(values, list):
                for it in values:
                    arglist.append(
                        self.b.line([
                            self.expr(it),
                            self.string(cond(isLine, ", ", ",")),
                        ]))

            else:
                arglist.append(values)

        add_direct_arglist(positional)

        for key in sorted(args.keys()):
            arglist.append(
                self.b.line([
                    self.string(key),
                    self.string(": "),
                    self.expr(args[key]),
                    self.string(cond(isLine, ", ", ",")),
                ]))

        add_direct_arglist(post_positional)

        result = cond(isLine, self.b.line, self.b.stack)([
            self.string(
                cond([
                    (arglist, f"{prefix}{name}("),
                    (b and not isLine, f"{prefix}{name}["),
                    (True, f"{prefix}{name}"),
                ])),
            *maybe_splice(
                arglist,
                self.b.line(arglist) if isLine else self.b.indent(
                    2,
                    self.b.stack(arglist),
                )),
            *maybe_splice(
                arglist,
                self.string(
                    cond([
                        (b and arglist and not isLine, ")["),
                        (arglist, ")"),
                        (True, ""),
                    ]))),
        ] + [
            cond(isLine, self.b.line, self.b.stack)([
                *maybe_splice(isLine, self.string("[")),
                self.b.indent(cond(isLine, 0, 2), b[idx]),
                self.string("]") if idx == len(b) - 1 else self.string("]["),
            ]) for idx in range(len(b))
        ])

        if isContent:
            return self.content(result)

        else:
            return result

    def expr(self, value: Any, isLine: bool = False) -> BlockId:
        match value:
            case bool():
                return self.string("true" if value else "false")

            case int() | float():
                return self.string(str(value))

            case RawLiteral():
                return self.string(value.value)

            case RawStr():
                return self.string(value.value)

            case RawBlock():
                return self.string(value.value)

            case str():
                return self.b.wrap_quote(self.escape_str_lit(value))

            case list():
                if all(isinstance(it, (int, str, float)) for it in value):
                    return self.b.pars(
                        self.b.csv([self.expr(it, isLine=isLine) for it in value] +
                                   [self.string("")]))

                else:
                    return self.spatial(
                        isLine,
                        self.string("("),
                        self.csv(
                            [self.expr(it, isLine=isLine) for it in value],
                            isLine=isLine,
                            isTrailing=True,
                        ),
                        self.string(")"),
                    )

            case None:
                return self.string("null")

            case dict():
                return self.b.pars(
                    self.b.csv([
                        self.b.line([
                            self.string(key),
                            self.string(": "),
                            self.expr(value[key], isLine=isLine),
                        ]) for key in sorted(value.keys())
                    ]))

            case _:
                raise ValueError(
                    f"Unexpected type for `expr()` conversion: {type(value)}")
