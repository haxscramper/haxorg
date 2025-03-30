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
    node = org.parseString("""
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
    """)

    context = org.initImmutableAstContext()
    version = context.addRoot(node)

    graph_state = org.graphMapGraphState.FromAstContextStatic(context)
    conf = org.graphMapConfig()
    org.addNode(graph_state, version.getRootAdapter(), conf)
