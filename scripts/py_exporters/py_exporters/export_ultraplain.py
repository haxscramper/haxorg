from py_exporters.export_base import ExporterBase
import py_haxorg.pyhaxorg as org
from py_textlayout.py_textlayout_wrap import *
from py_haxorg.pyhaxorg import OrgSemKind as osk
from beartype import beartype


@beartype
class ExporterUltraplain(ExporterBase):

    def __init__(self):
        super().__init__(self)

    def newOrg(self, node: org.Org):
        return ""

    def visitWord(self, res: str, node: org.Word):
        res += node.text

    def visitSpace(self, res: str, node: org.Space):
        res += node.text

    @staticmethod
    def getStr(node: org.Org) -> str:
        exp = ExporterUltraplain()
        return exp.exp.evalTop(node)
