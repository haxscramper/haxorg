from py_haxorg.pyhaxorg import *

SemSet = set[OrgSemKind]



def treeRepr(node: Org, colored: bool = True) -> str:
    tree = OrgExporterTree()
    opts = ExporterTreeOpts()
    opts.withColor = colored
    return tree.toString(node, opts)
