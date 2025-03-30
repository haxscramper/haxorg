import py_haxorg.pyhaxorg_wrap as org

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

    context = org.initImmutableAstContext()
    version = context.addRoot(node)

    graph_state: org.graphMapGraphState = org.graphMapGraphState.FromAstContextStatic(context)
    conf = org.graphMapConfig()
    root = version.getRootAdapter()

    print(root.treeReprString())
    # graph_state.
    conf.setTraceFileStr("/tmp/test_immutable_ast_mind_map.log", True)

    org.addNode(graph_state, root.at(0), conf)
    assert graph_state.graph.nodeCount() == 1
    assert graph_state.graph.edgeCount() == 0
    # assert graph_state.

    org.addNode(graph_state, root.at(2), conf)

    assert graph_state.graph.nodeCount() == 2
    assert graph_state.graph.edgeCount() == 1
