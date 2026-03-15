from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir

GEN = "haxorg_wasm"


class EmbindAstbuilderConfig(AstbulderConfig):

    def isAcceptedByBackend(self, params: codegen_ir.GenTuReflParams) -> bool:
        return params.isAcceptedBackend("wasm")

    def getSanitizedIdent(self, s: str) -> str:
        return codegen_ir.sanitize_ident(s, {
            "function",
        })

    def getBackendType(self, Type: QualType) -> QualType:
        wrapper_override = self.type_map.get_wrapper_type(Type)

        name = "DEFAULT"
        match Type.flatQualNameWithParams():
            case _ if wrapper_override:
                name = wrapper_override

            case ["std", "shared_ptr",
                  _] if self.isKnownClass(Type.par0()) and self.type_map.is_known_type(
                      Type.par0()) and self.getReflectionParams(
                          Type.par0()).backend.wasm.holder_type == "shared":
                return self.getBackendType(Type.par0())

            case ["int"] | ["float"] | ["double"]:
                name = "number"

            case ["char"] if Type.PtrCount == 1:
                name = "string"

            case ["bool"]:
                name = "boolean"

            case ["Str"] | ["string"] | ["std", "string"] | ["basic_string" \
                                                             ] | ["std", "basic_string"]:
                name = "string"

            case ["void"]:
                name = "void"

            case ["org", "sem", "SemId", _]:
                return self.getBackendType(Type.par0())

            case ["hstd", "Opt", _] | ["std", "optional", _]:
                name = GEN + ".Optional"

            case ["hstd", "Vec", _] | \
                ["immer", "box", _] | \
                ["org", "imm", "ImmIdT", _] | \
                ["immer", "flex_vector", _] | \
                ["hstd", "UnorderedMap", _, _] | \
                ["std", "variant", *_] | \
                ["hstd", "Variant", *_] | \
                ["org", "imm", "ImmBox", _] | \
                ["org", "imm", "ImmVec", _] | \
                ["hstd", "IntSet", _]:
                name = GEN + "." + self.getTypeBindName(Type, withParams=False)

            case _:
                name = self.getTypeBindName(Type, withParams=False)

        struct = self.type_map.get_struct_for_qual_name(Type)
        if not struct or struct.ReflectionParams.wrapper_has_params:
            return QualType(
                Name=name,
                Params=[self.getBackendType(P) for P in Type.Params],
            )

        else:
            return QualType(Name=name)
