import py_haxorg.pyhaxorg_wrap as org

def test_conversion():
    node = org.parseString("random paragraph")
    context = org.initImmutableAstContext()
