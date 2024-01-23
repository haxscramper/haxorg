from py_textlayout.py_textlayout import TextLayout, TextOptions

from typing import TYPE_CHECKING
from beartype.typing import NewType

if TYPE_CHECKING:
    from py_textlayout.py_textlayout import BlockId

else:
    BlockId = NewType('BlockId', int)
