from py_scriptutils.repo_files import get_haxorg_repo_root_path
from tree_sitter import Language, Parser
from beartype import beartype
import tree_sitter
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


thirdparty = get_haxorg_repo_root_path().joinpath("thirdparty")
build_dir = get_haxorg_repo_root_path().joinpath("build_treesitter")
build_so = build_dir.joinpath("lang.so")

Language.build_library(
    build_so,
    [
        thirdparty.joinpath("tree-sitter-cpp"),
        thirdparty.joinpath("tree-sitter-python"),
    ],
)

CPP_LANG = Language(build_so, "cpp")
PY_LANG = Language(build_so, "python")


@beartype
def tree_repr(node: Union[tree_sitter.Tree, tree_sitter.Node]) -> str:

    def aux(node: tree_sitter.Node, indent: int, name: Optional[str] = None) -> str:
        result = "  " * indent
        if name:
            result += f"[green]{name}[/green]: "

        result += f"{node.start_point[0]}:{node.start_point[1]} "

        if node.is_named:
            result += f"[cyan]{node.type}[/cyan]"
            if 0 < len(node.children):
                for idx, subnode in enumerate(node.children):
                    if subnode.is_named:
                        result += "\n"
                        result += aux(subnode, indent + 1, node.field_name_for_child(idx))

            else:
                result += " [yellow]\"" + node.text.decode() + "\"[/yellow]"

        else:
            result += "\"" + node.text.decode() + "\""

        return result

    if isinstance(node, tree_sitter.Node):
        return aux(node, 0)

    else:
        return aux(node.root_node, 0)


@beartype
def fail_node(node: tree_sitter.Node, name: str) -> ValueError:
    result = ValueError("Unhandled type tree structure in {}\n\n{}\n\n{}".format(
        name,
        render_rich(tree_repr(node), color=False),
        node.text.decode(),
    ))

    setattr(result, "__rich_msg__", tree_repr(node))

    return result


@beartype
@dataclass
class DocNodeGroup():
    comments: List[tree_sitter.Node] = field(default_factory=list)
    node: Optional[tree_sitter.Node] = None
    nested: List["DocNodeGroup"] = field(default_factory=list)
