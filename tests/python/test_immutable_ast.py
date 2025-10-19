import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from pathlib import Path
from py_scriptutils.script_logging import log

CAT = __name__

def test_immutable_ast_conversion():
    node = org.parseString("random paragraph", "<test>")
    context = org.initImmutableAstContext()
    version = context.addRoot(node)
    root_adapter = version.getRootAdapter()
    assert root_adapter.getKind() == org.OrgSemKind.Document
    paragraph0 = root_adapter.at(0)
    assert paragraph0.getKind() == org.OrgSemKind.Paragraph


def test_immutable_ast_mind_map():
    node = org.parseString("""Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
    """, "<test>")

    initial_context = org.initImmutableAstContext()
    version = initial_context.addRoot(node)

    graph_state: org.graphMapGraphState = org.graphMapGraphState.FromAstContextStatic(
        version.getContext())
    conf = org.graphMapConfig()
    root = version.getRootAdapter()

    # print(root.treeReprString())
    # graph_state.
    # conf.setTraceFileStr("/tmp/test_immutable_ast_mind_map.log", True)

    graph_state.addNode(root.at(0), conf)
    assert graph_state.graph.nodeCount() == 1
    assert graph_state.graph.edgeCount() == 0
    # assert graph_state.

    graph_state.addNode(root.at(2), conf)

    assert graph_state.graph.nodeCount() == 2
    assert graph_state.graph.edgeCount() == 1

    nodes = [n for n, _ in graph_state.graph.nodeProps.items()]
    edges = [e for e, _ in graph_state.graph.edgeProps.items()]

    assert len(nodes) == 2
    assert len(edges) == 1

    stable_nodes = sorted(nodes)
    assert edges[0].source == stable_nodes[1]
    assert edges[0].target == stable_nodes[0]


corpus_dir = get_haxorg_repo_root_path().joinpath("tests/org/corpus")


def test_mind_map_from_directory():
    dir = corpus_dir.joinpath("mind_map_directory")
    dir_opts = org.OrgDirectoryParseParameters()
    node = org.parseDirectoryOpts(str(dir), dir_opts)

    initial_version = org.initImmutableAstContext()
    version = initial_version.addRoot(node)

    graph_state: org.graphMapGraphState = org.graphMapGraphState.FromAstContextStatic(
        version.getContext())

    conf = org.graphMapConfig()
    root = version.getRootAdapter()

    graph_state.addNodeRec(version.getContext(), root, conf)

    assert root.getKind() == org.OrgSemKind.Directory
    root_dir = org.ImmDirectoryAdapter(root)

    subdir1 = root_dir.getFsSubnode("subdir1")
    assert subdir1.getKind() == org.OrgSemKind.Directory

    subdir1_spec = org.ImmDirectoryAdapter(subdir1)
    file1 = subdir1_spec.getFsSubnode("subdir_file1.org")
    file2 = subdir1_spec.getFsSubnode("subdir_file2.org")

    assert file1
    assert file2 

    assert file1.getKind() == org.OrgSemKind.File
    assert file2.getKind() == org.OrgSemKind.File
