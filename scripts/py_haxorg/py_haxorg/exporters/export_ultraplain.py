from beartype import beartype
from py_haxorg.exporters.export_base import ExporterBase
from py_haxorg.pyhaxorg_wrap import OrgSemKind as osk
import py_haxorg.pyhaxorg_wrap as org
from py_textlayout.py_textlayout_wrap import *


@beartype
class ExporterUltraplain(ExporterBase):
    """
    Exporter org-mode node into ultraplain format: leave only word nodes
    and some newline structure with spaces.
    """

    def __init__(self) -> None:  # type: ignore
        super().__init__(self)
        self.result = ""

    def newOrg(self, node: org.Org) -> str:
        return ""

    def visitWord(self, res: str, node: org.Word) -> None:
        self.result += node.text

    def visitSpace(self, res: str, node: org.Space) -> None:
        self.result += node.text

    def visitRawText(self, res: str, node: org.RawText) -> None:
        self.result += node.text

    def visitBigIdent(self, res: str, node: org.BigIdent) -> None:
        self.result += node.text

    @staticmethod
    def getStr(node: org.Org) -> str:
        exp = ExporterUltraplain()  # type: ignore
        exp.exp.evalTop(node)
        return exp.result
