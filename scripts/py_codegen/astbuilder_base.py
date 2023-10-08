import setup_imports
from py_textlayout.py_textlayout import *
from dataclasses import dataclass, field
from beartype.typing import *
from enum import Enum
from beartype import beartype
import inspect
import os

if not TYPE_CHECKING:
    BlockId = NewType('BlockId', int)


@beartype
class AstbuilderBase:
    b: TextLayout

    def string(self, text: str) -> BlockId:
        return self.b.text(text)

    def brace(self, elements: List[BlockId]) -> BlockId:
        return self.b.stack([self.string("{"), self.b.stack(elements), self.string("}")])

    def pars(self, arg: BlockId) -> BlockId:
        return self.b.line([self.string("("), arg, self.string(")")])

    def csv(self,
            items: Union[List[str], List[BlockId]],
            isLine=True,
            isTrailing=False) -> BlockId:
        return self.b.join(
            [self.string(Base) if isinstance(Base, str) else Base for Base in items],
            self.string(", "), isLine, isTrailing)
