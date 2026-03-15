from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir


class CAstbuilderConfig(AstbulderConfig):

    def isAcceptedByBackend(self, params: codegen_ir.GenTuReflParams) -> bool:
        return params.isAcceptedBackend("c")

    def getTypeBindName(self, Type: QualType, withParams: bool = True) -> str:
        return super().getTypeBindName(Type, withParams)

    def getBackendType(self, Type: QualType) -> QualType:
        match Type.flatQualNameWithParams():
            case ["hstd", "Vec", _]:
                return QualType(Name="haxorg_CHstdVec")

            case ["hstd", "UnorderedMap", _]:
                return QualType(Name="haxorg_CHstdUnorderedMap")

            case [builtin] if builtin in {
                "void",
                "int",
                "float",
                "double",
                "bool",
            }:
                return Type

            case _:
                return QualType(Name="haxorg_" +
                                self.getTypeBindName(Type, withParams=True))
