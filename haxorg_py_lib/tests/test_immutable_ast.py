import haxorg_py_lib.pyhaxorg_wrap as org


def test_immutable_ast_conversion() -> None:
    parse = org.ParseContext()
    node = parse.parseString("random paragraph", "<test>")
    context = org.initImmutableAstContext()
    version = context.addRoot(node)
    root_adapter = version.getRootAdapter()
    assert root_adapter.getKind() == org.OrgSemKind.Document
    paragraph0 = root_adapter.at(0)
    assert paragraph0.getKind() == org.OrgSemKind.Paragraph
