from py_scriptutils.repo_files import get_haxorg_repo_root_path
import sys 

build_dir = get_haxorg_repo_root_path().joinpath("build/haxorg")
if str(build_dir) not in sys.path:
    sys.path.append(str(build_dir))

from typing import TYPE_CHECKING
from beartype.typing import NewType

if TYPE_CHECKING:
    from py_textlayout.py_textlayout import TextLayout, TextOptions, BlockId

else:
    import py_textlayout_cpp as lyt
    print(lyt.__file__)
    print(dir(lyt))
    from py_textlayout_cpp import TextLayout, TextOptions
    BlockId = NewType('BlockId', int)
