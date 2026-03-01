import abc
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir
from beartype import beartype
from beartype.typing import List, Optional

from py_haxorg.astbuilder.astbuilder_utils import pascal_case
from py_scriptutils.script_logging import log

CAT = __name__


@beartype
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

    def isKnownClass(self, t: QualType) -> bool:
        "Check if type name refers to registered entry"
        return self.base_map.is_known_type(t)

    def isTypedef(self, t: QualType) -> bool:
        "Check if a type is a typedef alias"
        return self.base_map.is_typedef(t)

    def getResolvedType(self, t: QualType) -> "QualType":
        "Resolve all type aliases"
        if self.isTypedef(t):
            return self.getResolvedType(self.getUnderlyingType(t))

        else:
            return t

    def getTypeDefinition(
            self, t: QualType) -> Optional[codegen_ir.GenTuEnum | codegen_ir.GenTuStruct]:
        mapped = self.base_map.get_types_for_qual_name(t)
        if 0 < len(mapped):
            assert len(mapped) == 1, f"{t} maps to more than one type"
            assert isinstance(mapped[0], (codegen_ir.GenTuEnum, codegen_ir.GenTuStruct))
            return mapped[0]

        else:
            return None

    def getUnderlyingType(self, t: QualType) -> QualType:
        "Resolve typedef"
        return self.base_map.get_underlying_type(t)

    def getSanitizedIdent(self, s: str) -> str:
        return s

    def isUnwrappedTemplateInstantiation(self, t: QualType) -> bool:
        """
        Check if the type represents a template instantion that has to be
        explicitly wrapped as an extra type for codegen backend.
        """
        match tuple(t.flatQualName()):
            case name if name in {
                ("org", "sem", "SemId"),
                ("std", "shared_ptr"),
                ("hstd", "SharedPtrApi"),
                ("org", "imm", "ImmAdapterT"),
                ("org", "algo", "Exporter"),
            }:
                return False

            case _:
                return 0 < len(t.Parameters)

    def getBindName(self, t: QualType, withParams: bool = False) -> str:
        """
        Get name of the wrapped type for backend.
        """
        res = ""
        wrapper = self.base_map.get_wrapper_type(t)

        if wrapper:
            res += wrapper

        else:
            match t.flatQualName():
                case ["immer", "box"] | ["hstd", "ImmBox"]:
                    res += "ImmBox"

                case ["immer", "flex_vector"] | ["immer", "vector"] | ["hstd", "ImmVec"]:
                    res += "ImmVec"

                case ["std", "vector"]:
                    res += "StdVec"

                case ["hstd", "Vec"]:
                    res += "HstdVec"

                case ["std", "unordered_map"]:
                    res += "StdMap"

                case ["hstd", "UnorderedMap"]:
                    res += "HstdMap"

                case ["std", "unordered_set"]:
                    res += "StdSet"

                case ["hstd", "UnorderedSet"]:
                    res += "HstdSet"

                case ["std", "map"]:
                    res += "StdSortedMap"

                case ["hstd", "SortedMap"]:
                    res += "HstdSortedMap"

                case ["std", "set"]:
                    res += "StdSortedSet"

                case ["hstd", "SortedSet"]:
                    res += "HstdSortedSet"

                case _:
                    for N in t.Spaces:
                        res += self.getBindName(N, withParams=withParams)

                    if t.name not in codegen_ir.IGNORED_NAMESPACES:
                        res += pascal_case(t.name)

        if withParams and 0 < len(t.Parameters):
            res += "Of"
            res += "".join(
                [self.getBindName(T, withParams=withParams) for T in t.Parameters])

        return res

    def getBaseClassSpecializations(self, derived: QualType) -> List[QualType]:
        """
        For generic types, return a list of base classes that might
        need to be wrapped as specializations.
        """

        def get_base(spaces: List[str], name: str, params: List[QualType]) -> QualType:
            return QualType(name=name,
                            Spaces=[QualType(name=S, isNamespace=True) for S in spaces],
                            Parameters=params)

        def get_base_par0(spaces: List[str], name: str) -> QualType:
            return QualType(name=name,
                            Spaces=[QualType(name=S, isNamespace=True) for S in spaces],
                            Parameters=[derived.par0()])

        match derived.flatQualName():
            case ["hstd", "Vec"]:
                return [get_base_par0(["std"], "vector")]

            case ["hstd", "ImmBox"]:
                return [get_base_par0(["immer"], "box")]

            case ["hstd", "ImmVec"]:
                return [get_base_par0(["immer"], "flex_vector")]

            case ["hstd", "UnorderedMap"]:
                return [
                    get_base(["std"], "unordered_map",
                             [derived.par0(), derived.par1()])
                ]

            case ["hstd", "ImmMap"]:
                return [get_base(["immer"], "map", [derived.par0(), derived.par1()])]

            case _:
                return []
