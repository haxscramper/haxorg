from py_textlayout.py_textlayout_wrap import TextLayout
from dataclasses import dataclass, field
from typing import TYPE_CHECKING, NewType
from beartype.typing import List, Optional, Dict
from beartype import beartype
import py_codegen.astbuilder_base as base
from pydantic import BaseModel, Field
from pathlib import Path
import toml
from py_scriptutils.algorithm import cond, maybe_splice

if TYPE_CHECKING:
    from py_textlayout.py_textlayout_wrap import BlockId
else:
    BlockId = NewType('BlockId', int)


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
class ASTBuilder(base.AstbuilderBase):

    def __init__(self, in_b: Optional[TextLayout] = None):
        b = in_b if in_b else TextLayout()
        super().__init__(b)

    def string(self, node: str | BlockId) -> BlockId:
        if isinstance(node, str):
            return self.b.text(node)

        else:
            return node

    def escape(self, text: str) -> str:
        res = ""
        for ch in text:
            if ch in ["@", "#", "<", "*"]:
                res += "\\" + ch

            else:
                res += ch

        return res

    def surround(self, text: str, nodes: List[BlockId]) -> BlockId:
        return self.line(self.string(text), *nodes, self.string(text))

    def content(self, content: BlockId) -> BlockId:
        return self.line(self.string("["), content, self.string("]"))

    def set(self, name: str, args: Dict[str, BlockId | str] = dict()) -> BlockId:
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

    def add_at(self, target: BlockId, other: BlockId | List[BlockId]):
        self.b.add_at(target, other)

    def litPt(self, value: float) -> RawStr:
        return RawStr(f"{value}pt")

    def call(
        self,
        name: str,
        args: Dict[str, BlockId | str] = dict(),
        body: List[BlockId] | BlockId = list(),
        positional: List[BlockId | str | RawBlock | RawStr] | BlockId | str = list(),
        post_positional: List[BlockId | str | RawBlock | RawStr] | BlockId | str = list(),
        isContent: bool = False,
        isLine: bool = False,
        isFirst: bool = True,
    ) -> BlockId:
        b = body if isinstance(body, list) else [body]
        arglist = []

        prefix = "#" if isFirst else ""

        def add_direct_arglist(values):
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

    def expr(self, value, isLine: bool = False) -> BlockId:
        match value:
            case bool():
                return self.string("true" if value else "false")

            case int() | float():
                return self.string(str(value))

            case RawStr():
                return self.string(value.value)

            case RawBlock():
                return self.string(value.value)

            case str():
                return self.b.wrap_quote(value)

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
