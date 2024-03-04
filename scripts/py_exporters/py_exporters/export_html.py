from beartype import beartype
import dominate
from dominate.util import text
from py_exporters.export_base import ExporterBase
import py_haxorg.pyhaxorg_wrap as org

@beartype
class ExporterHtml(ExporterBase):
    def __init__(self):
        super().__init__(self)

    def newOrg(self, node: org.Org) -> text:
        return text("TODO" + str(node.getKind()))

    def evalDocument(self, node: org.Subtree) -> dominate.document:
        doc = dominate.document()



        return doc
