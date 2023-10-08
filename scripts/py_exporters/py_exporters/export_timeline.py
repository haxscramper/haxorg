import py_haxorg.pyhaxorg as org
from py_textlayout.py_textlayout import *
from py_haxorg.pyhaxorg import OrgSemKind as osk

from beartype.typing import *
from enum import Enum
from beartype import beartype

from py_exporters.export_base import ExporterBase

if not TYPE_CHECKING:
    BlockId = NewType('BlockId', int)

@beartype
class ExporterTimeline(ExporterBase):
    t: TextLayout
    count: int = 0

    def __init__(self):
        super().__init__(self)
        self.t = TextLayout()

    def newOrg(self, node: org.SemId):
        return None

    def visitAnyHook(self, res, node: org.SemId):
        self.count += 1

