from py_cli.scratch_scripts import mind_map
import py_haxorg.pyhaxorg_wrap as org
from beartype.typing import Any, Dict, Optional, List, Union
from beartype import beartype
from py_scriptutils.rich_utils import render_rich_pprint
from py_scriptutils.script_logging import to_debug_json
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_haxorg.pyhaxorg_utils import NodeIdProvider


def getJsonGraph(str: str) -> mind_map.JsonGraph:
    node = org.parseString(str)
    idProvider = NodeIdProvider()
    graph = mind_map.getGraph(idProvider, [node])
    return graph.toJsonGraph()


def getGvGraph(str: str) -> mind_map.GvGraph:
    node = org.parseString(str)
    idProvider = NodeIdProvider()
    graph = mind_map.getGraph(idProvider, [node])
    return graph.toGraphvizGraph()


def test_empty_file():
    getJsonGraph("")


def dbg(map: Union[mind_map.JsonGraph, mind_map.GvGraph]) -> str:
    return render_rich_pprint(map.model_dump(), width=200, color=False)


def get_edge(map: mind_map.JsonGraph, source: str,
             target: str) -> List[mind_map.JsonGraphEdge]:
    result = []
    for edge in map.edges:
        if edge.source == source and edge.target == target:
            result.append(edge)

    return result


def test_single_subtree():
    map = getJsonGraph("* Subtree")

    assert len(map.edges) == 0, dbg(map)
    assert len(map.nodes) == 2, dbg(map)
    assert map.nodes["0"].metadata.title == None
    assert map.nodes["1"].metadata.title == "Subtree"


def test_nested_subtree():
    map = getJsonGraph("""
* Top
** Nest
""")

    assert len(map.edges) == 0, dbg(map)
    assert len(map.nodes) == 3, dbg(map)
    assert map.nodes["1"].metadata.title == "Top"
    assert map.nodes["2"].metadata.title == "Nest"


def test_link_to_subtree():
    map = getJsonGraph("""
* Node
:properties:
:id: tree-id
:end:

[[id:tree-id][description]]
""")

    assert len(map.edges) == 2, dbg(map)
    assert len(map.nodes) == 3, dbg(map)

    assert map.nodes["tree-id"].metadata.title == "Node"

    entry_to_tree = get_edge(map, "1", "tree-id")
    assert entry_to_tree, dbg(map)
    assert entry_to_tree[0].metadata.kind == "RefersTo", dbg(map)

    self_link = get_edge(map, "tree-id", "tree-id")
    assert self_link, dbg(map)
    assert self_link[0].metadata.kind == "InternallyRefers", dbg(map)


def test_cross_tree_links():
    map = getJsonGraph("""
* Tree1
  :properties:
  :id: tree-id-1
  :end:

[[id:tree-id-2][description-1]]

* Tree2
  :properties:
  :id: tree-id-2
  :end:

[[id:tree-id-1][description-2]]

""")

    assert len(map.nodes) == 5, dbg(map)
    # Document node
    assert map.nodes["0"].metadata.kind == "Subtree", dbg(map)
    assert map.nodes["0"].metadata.title == None, dbg(map)
    assert map.nodes["0"].metadata.subtrees == ["tree-id-1", "tree-id-2"], dbg(map)

    id1 = map.nodes["tree-id-1"]
    id2 = map.nodes["tree-id-2"]

    assert id1.metadata.title == "Tree1", dbg(map)
    assert id2.metadata.title == "Tree2", dbg(map)
    assert id1.metadata.ordered == ["1"], dbg(map)
    assert id2.metadata.ordered == ["2"], dbg(map)

    e1 = map.nodes["1"]
    e2 = map.nodes["2"]

    assert e1.metadata.parent == "tree-id-1", dbg(map)
    assert e2.metadata.parent == "tree-id-2", dbg(map)

    e1_to_id2 = get_edge(map, "1", "tree-id-2")
    assert e1_to_id2, dbg(map)
    assert e1_to_id2[0].metadata.kind == "RefersTo"

    e2_to_id1 = get_edge(map, "2", "tree-id-1")
    assert e2_to_id1, dbg(map)
    assert e2_to_id1[0].metadata.kind == "RefersTo"


def test_description_list_for_links():
    map = getJsonGraph("""
* Tree1

- [[id:tree-id-2][description-1]] :: Full description

* Tree2
  :properties:
  :id: tree-id-2
  :end:
""")

    assert len(map.edges) == 1, dbg(map)
    assert len(map.nodes) == 3, dbg(map)
    e1_to_id2 = get_edge(map, "1", "tree-id-2")
    assert e1_to_id2, dbg(map)
    assert e1_to_id2[0].metadata.description == "Full description"


mind_map_org = get_haxorg_repo_root_path().joinpath("tests/assets/mind_map.org")


def test_gv_graph():
    gv = getGvGraph(mind_map_org.read_text())

    dot = gv.to_graphviz()
    from pathlib import Path
    Path("/tmp/result.py").write_text(dbg(gv))
    dot.render("/tmp/result.dot", format="dot")
    # dot.render("/tmp/result.png", format="png")

    map = getJsonGraph(mind_map_org.read_text())

    Path("/tmp/result.json").write_text(map.model_dump_json(indent=2))


def test_node_properties():
    map = getJsonGraph("""
* Tree
  :properties:
  :id: some-id
  :other_prop: value
  :effort: 12:0
  :created: [2024-12-02]
  :visibility: all
  :ordered: t
  :end:
""")
    
    meta = map.nodes["some-id"].metadata

    assert meta.level == 1
    assert meta.properties["id"]["id"] == "some-id"
    assert meta.properties["other_prop"]["value"] == "value"
    assert meta.properties["Effort"]["hours"] == 12
    assert meta.properties["Effort"]["minutes"] == 0

