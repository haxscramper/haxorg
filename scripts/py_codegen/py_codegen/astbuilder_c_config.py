from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir
from beartype.typing import Optional


class CAstbuilderConfig(AstbulderConfig):

    def isAcceptedByBackend(self, params: Optional[codegen_ir.GenTuReflParams]) -> bool:
        return not params or params.isAcceptedBackend("c")

    def getTypeBindName(self, Type: QualType, withParams: bool = True) -> str:
        return super().getTypeBindName(Type, withParams)

    def getBackendType(self, Type: QualType) -> QualType:
        prefix = "haxorg_"
        match Type.flatQualNameWithParams():
            case ["hstd", "Vec", _]:
                return QualType(Name=prefix + "CHstdVec")

            case ["hstd", "UnorderedMap", _]:
                return QualType(Name=prefix + "CHstdUnorderedMap")

            case ["org", "sem", "SemId", _]:
                return QualType(Name=prefix + "SemId")

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
                return QualType(Name=prefix + self.getTypeBindName(Type, withParams=True))
