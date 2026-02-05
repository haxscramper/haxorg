import sys

from beartype import beartype
from beartype.typing import Iterable, List, Union
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import ci_log

build_dir = get_haxorg_repo_root_path().joinpath("build/haxorg")
if str(build_dir) not in sys.path:
    sys.path.append(str(build_dir))

# for p in sys.path:
#     ci_log().info(p)

from typing import TYPE_CHECKING

from beartype.typing import NewType

if TYPE_CHECKING:
    from py_textlayout.py_textlayout import BlockId, TextOptions
    import py_textlayout.py_textlayout as lyt

else:
    from py_textlayout_cpp import TextOptions
    import py_textlayout_cpp as lyt
    BlockId = NewType('BlockId', int)


@beartype
class TextLayout(lyt.TextLayout):

    def pars(self, arg: BlockId, left: str = "(", right: str = ")") -> BlockId:
        return self.line([self.text(left), arg, self.text(right)])

    def add_if_not_empty(self, arg: BlockId, other: BlockId) -> None:
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
        items2 = [self.text(Base) if isinstance(Base, str) else Base for Base in items]
        assert isinstance(items2, list)
        return self.join(items2, self.text(sep), isLine, isTrailing)

    def wrap_quote(self, text: str) -> BlockId:
        return self.text(f"\"{text}\"")
