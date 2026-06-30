import py_haxorg.pyhaxorg_wrap as org

ctx = org.ParseContext()
node = ctx.parseString("*bold*", "<input>")
assert node.getKind() == org.OrgSemKind.Document
assert node[0].getKind() == org.OrgSemKind.Paragraph
print(org.treeRepr(node))
