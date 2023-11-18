from py_textlayout.py_textlayout import TextLayout
from beartype.typing import List, Union
from beartype import beartype
from typing import TYPE_CHECKING, NewType

if TYPE_CHECKING:
    from py_textlayout.py_textlayout import BlockId
else:
    BlockId = NewType('BlockId', int)


@beartype
class AstbuilderBase:
    b: TextLayout

    def string(self, text: str) -> BlockId:
        return self.b.text(text)

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

    def csv(self,
            items: Union[List[str], List[BlockId]],
            isLine=True,
            isTrailing=False) -> BlockId:
        return self.b.join(
            [self.string(Base) if isinstance(Base, str) else Base for Base in items],
            self.string(", "), isLine, isTrailing)
