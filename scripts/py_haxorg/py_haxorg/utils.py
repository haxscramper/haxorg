import py_haxorg.pyhaxorg as org


def toTree(path: str, node: org.SemId):
    tree = org.OrgExporterTree()
    opts = org.ExporterTreeOpts()
    opts.withColor = False
    tree.toFile(node, path, opts)
