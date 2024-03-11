from py_exporters.export_base import ExporterBase
import py_haxorg.pyhaxorg_wrap as org
from py_textlayout.py_textlayout_wrap import *
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk
from beartype import beartype


@beartype
class ExporterUltraplain(ExporterBase):

    def __init__(self):
        super().__init__(self)
        self.result = ""

    def newOrg(self, node: org.Org):
        return ""

    def visitWord(self, res: str, node: org.Word):
        self.result += node.text

    def visitSpace(self, res: str, node: org.Space):
        self.result += node.text

    def visitRawText(self, res: str, node: org.RawText):
        self.result += node.text

    @staticmethod
    def getStr(node: org.Org) -> str:
        exp = ExporterUltraplain()
        exp.exp.evalTop(node)
        return exp.result
