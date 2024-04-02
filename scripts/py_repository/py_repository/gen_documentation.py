#!/usr/bin/env python

from tree_sitter import Language, Parser
import tree_sitter
from py_scriptutils.files import get_haxorg_repo_root_path
from pathlib import Path

thirdparty = get_haxorg_repo_root_path().joinpath("thirdparty")
build_dir = get_haxorg_repo_root_path().joinpath("build_treesitter")
build_so = build_dir.joinpath("lang.so")

Language.build_library(
    build_so,
    [thirdparty.joinpath("tree-sitter-cpp")],
)

CPP_LANG = Language(build_so, "cpp")


def parse_cxx(file: Path) -> tree_sitter.Tree:
    parser = Parser()
    parser.set_language(CPP_LANG)
    return parser.parse(file.read_bytes())


def tree_repr(node: tree_sitter.Tree) -> str:

    def aux(node: tree_sitter.Node, indent: int) -> str:
        result = "  " * indent
        if node.is_named:
            result += node.type
            if 0 < len(node.children):
                for subnode in node.children:
                    if subnode.is_named:
                        result += "\n"
                        result += aux(subnode, indent + 1)

            else:
                result += " \"" + node.text.decode() + "\""

        else:
            result += "\"" + node.text.decode() + "\""

        return result

    return aux(node.root_node, 0)


for glob in {"*.cpp", "*.hpp"}:
    for file in get_haxorg_repo_root_path().joinpath("src").rglob(glob):
        tree = parse_cxx(file)
        Path(f"/tmp/{file.name}.txt").write_text(tree_repr(tree))

print("done")
