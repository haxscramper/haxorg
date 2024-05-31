from py_scriptutils.repo_files import get_haxorg_repo_root_path
from beartype import beartype
from py_scriptutils.rich_utils import render_rich
from beartype.typing import Union, Optional, List
from dataclasses import dataclass, field
from pygments.token import _TokenType



@beartype
def abbreviate_token_name(token: _TokenType) -> str:
    # Remove the base "Token" from the token type
    token_path = str(token).split('.')[1:]

    # Take the first letter of each part of the token type
    abbreviation = ''.join(part[0] for part in token_path).lower()

    return abbreviation

