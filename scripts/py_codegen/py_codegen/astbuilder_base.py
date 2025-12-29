from dataclasses import dataclass, field
from typing import TYPE_CHECKING, NewType

from beartype import beartype
from beartype.typing import List, Optional, Union, overload
from py_textlayout.py_textlayout_wrap import TextLayout, TextOptions
import itertools

if TYPE_CHECKING:
    from py_textlayout.py_textlayout_wrap import BlockId
else:
    BlockId = NewType('BlockId', int)


def pascal_case(s: str) -> str:
    return s[0].upper() + s[1:] if s else ""


class AstLineCtx:

    def __init__(self, builder: 'AstbuilderBase') -> None:
        self.builder = builder
        self.block_ids: List[BlockId] = []

    def __enter__(self) -> 'AstLineCtx':
        self.builder.context_stack.append(self)
        return self

    def __exit__(self, exc_type: object, exc_val: object, exc_tb: object) -> None:
        line_id = self.builder.b.line(self.block_ids)
        self.builder.last_result = line_id
        self.builder.context_stack.pop()
        if self.builder.context_stack:
            self.builder.context_stack[-1].block_ids.append(line_id)


class AstIndentCtx:

    def __init__(self, builder: "AstbuilderBase", indent: int) -> None:
        self.builder = builder
        self.indent_size = indent
        self.block_ids: List[BlockId] = []

    def __enter__(self) -> "AstIndentCtx":
        self.builder.context_stack.append(self)
        return self

    def __exit__(self, exc_type: object, exc_val: object, exc_tb: object) -> None:
        Indent_id = self.builder.b.indent(self.indent_size,
                                          self.builder.b.stack(self.block_ids))
        self.builder.last_result = Indent_id
        self.builder.context_stack.pop()
        if self.builder.context_stack:
            self.builder.context_stack[-1].block_ids.append(Indent_id)


class AstStackCtx:

    def __init__(self, builder: "AstbuilderBase") -> None:
        self.builder = builder
        self.block_ids: List[BlockId] = []

    def __enter__(self) -> "AstStackCtx":
        self.builder.context_stack.append(self)
        return self

    def __exit__(self, exc_type: object, exc_val: object, exc_tb: object) -> None:
        stack_id = self.builder.b.stack(self.block_ids)
        self.builder.last_result = stack_id
        self.builder.context_stack.pop()
        if self.builder.context_stack:
            self.builder.context_stack[-1].block_ids.append(stack_id)


@beartype
@dataclass
class AstbuilderBase:
    b: TextLayout
    context_stack: List[Union[AstLineCtx, AstStackCtx,
                              AstIndentCtx]] = field(default_factory=list)
    last_result: Optional[BlockId] = None

    def toString(self, block: BlockId) -> str:
        return self.b.toString(block, TextOptions())

    def __repr__(self) -> str:
        # Beartype cannot run default repr because it fails with missing context state value.
        return "astbuilder-base"

    def Spatial(self, stack: bool) -> Union["AstLineCtx", "AstStackCtx"]:
        if stack:
            return self.Stack()

        else:
            return self.Line()

    def ToBlockId(self, value: str | BlockId | None) -> BlockId:
        if value is None:
            return self.b.empty()

        elif isinstance(value, str):
            return self.string(value)

        else:
            return value

    def Line(self) -> AstLineCtx:
        return AstLineCtx(self)

    def Stack(self) -> AstStackCtx:
        return AstStackCtx(self)

    def Indent(self, indent: int) -> AstIndentCtx:
        return AstIndentCtx(self, indent)

    def Item(self, value: Union[str, BlockId]) -> None:
        match value:
            case str():
                block_id = self.b.text(value)

            case _:
                block_id = value

        self.context_stack[-1].block_ids.append(block_id)

    def Result(self) -> BlockId:
        assert self.last_result
        return self.last_result

    def string(self, text: str) -> BlockId:
        return self.b.text(text)

    def stack(self, *args: BlockId | List[BlockId]) -> BlockId:
        if any(isinstance(arg, list) for arg in args):
            return self.b.stack(list(itertools.chain(*args)))
        else:
            return self.b.stack(args)

    def line(self, *args: BlockId | List[BlockId]) -> BlockId:
        if any(isinstance(arg, list) for arg in args):
            return self.b.line(list(itertools.chain(*args)))
        else:
            return self.b.line(args)

    def spatial(self, isLine: bool, *args: BlockId | List[BlockId]) -> BlockId:
        if isLine:
            return self.line(*args)

        else:
            return self.stack(*args)

    def indent(self, indent: int, *args: BlockId) -> BlockId:
        return self.b.indent(indent, self.b.stack(args))

    def brace(self,
              elements: List[BlockId],
              left: str = "{",
              right: str = "}") -> BlockId:
        return self.b.stack([
            self.string(left),
            self.b.stack(elements),
            self.string(right),
        ])

    def pars(self, arg: BlockId, left: str = "(", right: str = ")") -> BlockId:
        return self.b.line([self.string(left), arg, self.string(right)])

    def sep_stack(self, args: List[BlockId]) -> BlockId:
        res: List[BlockId] = []
        for idx, value in enumerate(args):
            if idx != 0:
                res.append(self.string(""))

            res.append(value)

        return self.b.stack(res)

    def csv(
        self,
        items: Union[List[str], List[BlockId]],
        isLine: bool = True,
        isTrailing: bool = False,
        sep: str = ", ",
    ) -> BlockId:
        if 0 < len(items):
            return self.b.join(
                [self.string(Base) if isinstance(Base, str) else Base for Base in items],
                self.string(", "),
                isLine,
                isTrailing,
            )

        else:
            return self.string("")
