import abc
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir
from beartype import beartype
from beartype.typing import List, Optional

from py_haxorg.astbuilder.astbuilder_utils import pascal_case
from py_scriptutils.script_logging import log

CAT = __name__

BUILTIN_TYPES = [
    ["char"],
    ["bool"],
    ["void"],
    ["int8_t"],
    ["int16_t"],
    ["int32_t"],
    ["int64_t"],
    ["uint8_t"],
    ["uint16_t"],
    ["uint32_t"],
    ["uint64_t"],
    ["unsigned short"],
    ["unsigned int"],
    ["unsigned long"],
    ["unsigned long long"],
    ["short"],
    ["int"],
    ["long"],
    ["long long"],
    ["float"],
    ["double"],
]


@beartype
class AstbulderConfig(abc.ABC):
    """
    Base class for backend-specific configuration options for code
    generation.
    """

    def __init__(self, type_map: codegen_ir.GenTypeMap):
        self.type_map = type_map

    def _isExposedByBackendImpl(self, entry: codegen_ir.GenTuDeclaration,
                                backend: str) -> bool:
        match entry:
            case codegen_ir.GenTuStruct() | codegen_ir.GenTuField(
            ) | codegen_ir.GenTuFunction() | codegen_ir.GenTuTypedef():
                if not entry.IsExposedForWrap:
                    return False

        return not entry.ReflectionParams or entry.ReflectionParams.isAcceptedBackend(
            backend)

    @abc.abstractmethod
    def isAcceptedByBackend(self, entry: codegen_ir.GenTuDeclaration) -> bool:
        "Check if the entry with these reflection params is accepted for the backend"
        ...

    @abc.abstractmethod
    def getBackendType(self, Type: QualType) -> QualType:
        "Rewrite the IR type to the backend-specific counterpart"
        ...

    def isRegisteredForBacked(self, Type: QualType) -> bool:
        """
        Check if the specific type was registered for wrapping for backend -- either as
        an explicit class to be wrapped, or as a backend-specific type that is already
        present by default
        """
        match Type.flatQualNameWithParams():
            case l if l in [
                # Universally registered types -- if some backend does not expose them,
                # it can override the method to return false.
                ["std", "string"],
                ["hstd", "Str"],
            ] + BUILTIN_TYPES:
                return True

            case ["hstd", "SharedPtrApi", _]:
                return False

            case ["std", "shared_ptr", _]:
                return self.isRegisteredForBacked(Type.par0())

            case _:
                return self.isKnownClass(Type)

    def isKnownClass(self, Type: QualType) -> bool:
        "Check if type name refers to registered entry"
        return self.type_map.is_known_type(Type)

    def isTypedef(self, Type: QualType) -> bool:
        "Check if a type is a typedef alias"
        return self.type_map.is_typedef(Type)

    def getResolvedType(self, Type: QualType) -> "QualType":
        "Resolve all type aliases"
        if self.isTypedef(Type):
            assert self.getUnderlyingType(Type)
            return self.getResolvedType(self.getUnderlyingType(Type))

        else:
            return Type

    def getTypeDefinition(
            self, t: QualType) -> Optional[codegen_ir.GenTuEnum | codegen_ir.GenTuStruct]:
        mapped = self.type_map.get_types_for_qual_name(t)
        if 0 < len(mapped):
            assert len(mapped) == 1, f"{t} maps to more than one type"
            assert isinstance(mapped[0], (codegen_ir.GenTuEnum, codegen_ir.GenTuStruct))
            return mapped[0]

        else:
            return None

    def getReflectionParams(self, Type: QualType) -> codegen_ir.GenTuReflParams:
        result = self.getTypeDefinition(Type)
        assert result, f"Type {Type} is not mapped to the known type"
        return result.ReflectionParams

    def getUnderlyingType(self, Type: QualType) -> Optional[QualType]:
        "Resolve typedef"
        return self.type_map.get_underlying_type(Type)

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
                ("org", "imm", "ImmAdapterTBase"),
                ("org", "imm", "ImmIdT"),
            }:
                return False

            case _:
                return 0 < len(t.Params)

    def getTypeBindName(self, Type: QualType, withParams: bool = True) -> str:
        """
        Get name of the wrapped type for backend. Default name generation logic
        for all backends. Some backends might overwrite this for a more fitting
        name construction.
        """
        res = ""
        wrapper = self.type_map.get_wrapper_type(Type)

        if wrapper:
            res += wrapper

        else:
            match Type.flatQualName():
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
                    for N in Type.Spaces:
                        res += pascal_case(self.getTypeBindName(N, withParams=withParams))

                    if Type.Name in ["bool", "int", "char", "float"]:
                        res += Type.Name

                    # Skip verbose namespaces for name generation
                    elif Type.Name not in [
                            "sem",
                            "org",
                            "hstd",
                            "ext",
                            "algo",
                            "bind",
                            "python",
                            "imm",
                    ]:
                        res += pascal_case(Type.Name)

        if withParams and 0 < len(Type.Params):
            res += "Of"
            res += "".join([
                pascal_case(self.getTypeBindName(T, withParams=withParams))
                for T in Type.Params
            ])

        return res

    def getBaseClassSpecializations(self, derived: QualType) -> List[QualType]:
        """
        For generic types, return a list of base classes that might
        need to be wrapped as specializations.
        """

        def get_base(spaces: List[str], name: str, params: List[QualType]) -> QualType:
            return QualType(Name=name,
                            Spaces=[QualType(Name=S, IsNamespace=True) for S in spaces],
                            Params=params)

        def get_base_par0(spaces: List[str], name: str) -> QualType:
            return QualType(Name=name,
                            Spaces=[QualType(Name=S, IsNamespace=True) for S in spaces],
                            Params=[derived.par0()])

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
