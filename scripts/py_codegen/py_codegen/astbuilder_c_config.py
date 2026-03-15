from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir


class CAstbuilderConfig(AstbulderConfig):

    def getBackendType(self, Type: QualType) -> QualType:
        match Type.flatQualNameWithParams():
            case ["hstd", "Vec", _]:
                return QualType(Name="haxorg_CHstdVec")

            case ["hstd", "UnorderedMap", _]:
                return QualType(Name="haxorg_CHstdUnorderedMap")

            case _:
                return QualType(Name=self.getTypeBindName(Type, withParams=True))
