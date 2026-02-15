import sys
from typing import TYPE_CHECKING

from beartype import beartype
from beartype.typing import Iterable, List, NewType, Union
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import ci_log

if TYPE_CHECKING:
    from py_haxorg.layout.types import BlockId, TextOptions
    import py_haxorg.layout.types as lyt

else:
    from py_textlayout_cpp import TextOptions
    import py_textlayout_cpp as lyt
    BlockId = NewType('BlockId', int)


@beartype
class TextLayout(lyt.TextLayout):
    """
    Python wrapper around C++ text layouter class
    """

    def pars(self, arg: BlockId, left: str = "(", right: str = ")") -> BlockId:
        "Wrap argument block in a new line surronded by left/right delimiter"
        return self.line([self.text(left), arg, self.text(right)])

    def add_if_not_empty(self, arg: BlockId, other: BlockId) -> None:
        "Add `other` to `arg` if `other` is non-empty and the `arg` is a line/stack entry"
        if (self.isLine(other) or self.isStack(other)) and self.size(other) == 0:
            pass

        else:
            self.add_at(arg, other)

    @beartype
    def csv(
        self,
        items: Union[Iterable[str], Iterable[BlockId]],
        isLine: bool = True,
        isTrailing: bool = False,
        sep: str = ", ",
    ) -> BlockId:
        "Format values in a comma-separated line"
        items2 = [self.text(Base) if isinstance(Base, str) else Base for Base in items]
        assert isinstance(items2, list)
        return self.join(items2, self.text(sep), isLine, isTrailing)

    def wrap_quote(self, text: str) -> BlockId:
        "Wrap text in quotes and return block"
        return self.text(f"\"{text}\"")
