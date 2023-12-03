from py_textlayout.py_textlayout import TextLayout
from beartype.typing import List, Union, Optional
from beartype import beartype
from typing import TYPE_CHECKING, NewType
from dataclasses import dataclass, field

if TYPE_CHECKING:
    from py_textlayout.py_textlayout import BlockId
else:
    BlockId = NewType('BlockId', int)


class AstLineCtx:

    def __init__(self, builder):
        self.builder = builder
        self.block_ids = []

    def __enter__(self):
        self.builder.context_stack.append(self)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        line_id = self.builder.b.line(self.block_ids)
        self.builder.last_result = line_id
        self.builder.context_stack.pop()
        if self.builder.context_stack:
            self.builder.context_stack[-1].block_ids.append(line_id)


class AstIndentCtx:

    def __init__(self, builder, indent):
        self.builder = builder
        self.indent_size = indent
        self.block_ids = []

    def __enter__(self):
        self.builder.context_stack.append(self)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        Indent_id = self.builder.b.indent(self.indent_size,
                                          self.builder.b.stack(self.block_ids))
        self.builder.last_result = Indent_id
        self.builder.context_stack.pop()
        if self.builder.context_stack:
            self.builder.context_stack[-1].block_ids.append(Indent_id)


class AstStackCtx:

    def __init__(self, builder):
        self.builder = builder
        self.block_ids = []

    def __enter__(self):
        self.builder.context_stack.append(self)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        stack_id = self.builder.b.stack(self.block_ids)
        self.builder.last_result = stack_id
        self.builder.context_stack.pop()
        if self.builder.context_stack:
            self.builder.context_stack[-1].block_ids.append(stack_id)


class AstItemCtx:

    def __init__(self, builder, value: Union[str, BlockId]):
        self.builder = builder
        self.value = value

    def __enter__(self):
        match self.value:
            case str():
                block_id = self.builder.b.text(self.value)

            case _:
                block_id = self.value

        if self.builder.context_stack:
            self.builder.context_stack[-1].block_ids.append(block_id)

        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        pass


@beartype
@dataclass
class AstbuilderBase:
    b: TextLayout
    context_stack: List[Union[AstLineCtx, AstStackCtx,
                              AstIndentCtx]] = field(default_factory=list)
    last_result: Optional[BlockId] = None

    def Line(self):
        return AstLineCtx(self)

    def Stack(self):
        return AstStackCtx(self)

    def Indent(self, indent: int):
        return AstIndentCtx(self, indent)

    def Item(self, value: Union[str, BlockId]):
        return AstItemCtx(self, value)

    def Result(self) -> BlockId:
        assert self.last_result
        return self.last_result

    def string(self, text: str) -> BlockId:
        return self.b.text(text)

    def stack(self, *args: BlockId) -> BlockId:
        return self.b.stack(args)

    def line(self, *args: BlockId) -> BlockId:
        return self.b.line(args)

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

    def csv(self,
            items: Union[List[str], List[BlockId]],
            isLine=True,
            isTrailing=False) -> BlockId:
        return self.b.join(
            [self.string(Base) if isinstance(Base, str) else Base for Base in items],
            self.string(", "), isLine, isTrailing)
