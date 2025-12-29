import py_haxorg.pyhaxorg_wrap as org


def toTree(path: str, node: org.Org) -> None:
    tree = org.OrgExporterTree()  # type: ignore[attr-defined]
    opts = org.ExporterTreeOpts()  # type: ignore[attr-defined]
    opts.withColor = False
    tree.toFile(node, path, opts)
