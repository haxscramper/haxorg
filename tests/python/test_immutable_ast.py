import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from pathlib import Path
from py_scriptutils.script_logging import log

CAT = __name__

def test_immutable_ast_conversion():
    node = org.parseString("random paragraph")
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
    """)

    initial_context = org.initImmutableAstContext()
    version = initial_context.addRoot(node)

    graph_state: org.graphMapGraphState = org.graphMapGraphState.FromAstContextStatic(
        version.getContext())
    conf = org.graphMapConfig()
    root = version.getRootAdapter()

    # print(root.treeReprString())
    # graph_state.
    # conf.setTraceFileStr("/tmp/test_immutable_ast_mind_map.log", True)

    org.addNode(graph_state, root.at(0), conf)
    assert graph_state.graph.nodeCount() == 1
    assert graph_state.graph.edgeCount() == 0
    # assert graph_state.

    org.addNode(graph_state, root.at(2), conf)

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

    org.addNodeRec(graph_state, root, conf)


def test_mind_map_large_dir():
    dir = Path("/home/haxscramper/tmp/org_test_dir")
    if not dir.exists():
        return

    dir_opts = org.OrgDirectoryParseParameters()
    node = org.parseDirectoryOpts(str(dir), dir_opts)

    initial_version = org.initImmutableAstContext()
    version = initial_version.addRoot(node)

    graph_state: org.graphMapGraphState = org.graphMapGraphState.FromAstContextStatic(
        version.getContext())

    conf = org.graphMapConfig()
    root = version.getRootAdapter()

    assert root

    org.addNodeRec(graph_state, root, conf)

    log(CAT).info(f"Collected {graph_state.graph.nodeCount()} nodes and {graph_state.graph.edgeCount()} edges")

    plantuml_result = []

    def aux_main(a: org.ImmAdapter):
      nonlocal plantuml_result

    print(root.getKind())
    assert root.getKind() == org.OrgSemKind.Directory
    main_dir = root.getFsSubnode("main", False)
