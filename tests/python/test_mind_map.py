from py_cli.scratch_scripts.mind_map import mind_map
import py_haxorg.pyhaxorg_wrap as org
from beartype.typing import Any, Dict, Optional
from beartype import beartype
from py_scriptutils.rich_utils import render_rich_pprint

def getJsonGraph(str: str) -> mind_map.JsonGraph:
    node = org.parseString(str)
    graph = mind_map.getGraph([node])
    return graph.toJsonGraph()


def test_empty_file():
    getJsonGraph("")

def dbg(map: mind_map.JsonGraph) -> str:
    return render_rich_pprint(map.model_dump(), width=200, color=False)

def get_edge(map: mind_map.JsonGraph, source: str, target: str) -> Optional[mind_map.JsonGraphEdge]:
    for edge in map.edges:
        if edge.source == source and edge.target == target:
            return edge

def test_single_subtree():
    map = getJsonGraph("* Subtree")

    assert len(map.edges) == 1, dbg(map)
    assert len(map.nodes) == 2, dbg(map)
    assert map.nodes["0"].metadata.title == None
    assert map.nodes["1"].metadata.title == "Subtree"
    assert map.edges[0].metadata.kind == "NestedIn"

def test_nested_subtree():
    map = getJsonGraph("""
* Top
** Nest
""")
    
    assert len(map.edges) == 2, dbg(map)
    assert len(map.nodes) == 3, dbg(map)
    assert map.nodes["1"].metadata.title == "Top"
    assert map.nodes["2"].metadata.title == "Nest"
    assert map.edges[0].metadata.kind == "NestedIn"
    assert map.edges[1].metadata.kind == "NestedIn"

def test_link_to_subtree():
    map = getJsonGraph("""
* Node
:properties:
:id: tree-id
:end:

[[id:tree-id][description]]
""")
    
    assert len(map.edges) == 4, dbg(map)
    assert len(map.nodes) == 3, dbg(map)

    assert map.nodes["tree-id"].metadata.title == "Node"

    entry_to_tree = get_edge(map, "1", "tree-id")
    assert entry_to_tree, dbg(map)
    assert entry_to_tree.metadata.kind == "RefersTo", dbg(map)
    
    self_link = get_edge(map, "tree-id", "tree-id")
    assert self_link, dbg(map)
    assert self_link.metadata.kind == "InternallyRefers", dbg(map)
