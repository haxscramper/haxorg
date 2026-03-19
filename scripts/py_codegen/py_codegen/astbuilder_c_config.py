from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir
from beartype.typing import Optional
from beartype import beartype


@beartype
class CAstbuilderConfig(AstbulderConfig):

    def isAcceptedByBackend(self, entry: codegen_ir.GenTuDeclaration) -> bool:
        return self._isExposedByBackendImpl(entry, "c")

    def getTypeBindName(self, Type: QualType, withParams: bool = True) -> str:
        return super().getTypeBindName(Type, withParams)

    def getBackendType(self, Type: QualType) -> QualType:
        prefix = "haxorg_"
        match Type.flatQualNameWithParams():
            case ["hstd", "Vec", _]:
                return QualType(Name=prefix + "HstdVec")

            case ["hstd", "UnorderedSet", _]:
                return QualType(Name=prefix + "HstdUnorderedSet")

            case ["hstd", "Opt", _]:
                return QualType(Name=prefix + "HstdOpt")

            case ["hstd", "Str"]:
                return QualType(Name=prefix + "HstdStr")

            case ["std", "optional", _]:
                return QualType(Name=prefix + "StdOptional")

            case ["hstd", "UnorderedMap", _, _]:
                return QualType(Name=prefix + "HstdUnorderedMap")

            case ["hstd", "SortedMap", _, _]:
                return QualType(Name=prefix + "HstdMap")

            case ["org", "sem", "SemId", _]:
                return QualType(Name=prefix + "SemId")

            case ["org", "imm", "ImmIdT", _]:
                return QualType(Name=prefix + "ImmId")

            case ["hstd", "ext", "ImmBox", _]:
                return self.getBackendType(Type.par0())

            case ["hstd", "ext", "ImmVec", _]:
                return QualType(Name=prefix + "ImmVec")

            case ["immer", "flex_vector", _]:
                return QualType(Name=prefix + "immer_flex_vector")

            case ["org", "imm", "ImmAdapterT", _]:
                return QualType(Name=prefix + self.getTypeBindName(Type.par0()) +
                                "Adapter")

            case ["std", "shared_ptr", _]:
                refl = self.getReflectionParams(Type.par0())
                if refl and refl.backend.c.holder_type == "shared":
                    return self.getBackendType(Type.par0())

                else:
                    return QualType(Name=prefix +
                                    self.getTypeBindName(Type, withParams=True))

            case [builtin] if builtin in {
                "void",
                "int",
                "float",
                "double",
                "bool",
            }:
                return Type

            case _:
                return QualType(
                    Name=prefix + self.getTypeBindName(Type, withParams=True),
                    DbgOrigin=str(Type.flatQualNameWithParams()),
                )
