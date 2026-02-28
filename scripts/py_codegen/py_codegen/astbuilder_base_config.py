import abc
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir


class AstbulderConfig(abc.ABC):
    """
    Base class for backend-specific configuration options for code
    generation.
    """

    def __init__(self, base_map: codegen_ir.GenTypeMap):
        self.base_map = base_map

    @abc.abstractmethod
    def getBackendType(self, t: QualType) -> QualType:
        "Rewrite the IR type to the backend-specific counterpart"
        ...

    @abc.abstractmethod
    def getBindName(self, t: QualType) -> str:
        "Get stable string for binding IR type"
        ...

    def isKnownClass(self, t: QualType) -> bool:
        "Check if type name refers to registered entry"
        return self.base_map.is_known_type(t)

    def getSanitizedIdent(self, s: str) -> str:
        return s
