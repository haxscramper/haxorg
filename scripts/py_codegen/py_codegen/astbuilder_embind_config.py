from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir

GEN = "haxorg_wasm"


class EmbindAstbuilderConfig(AstbulderConfig):

    def getSanitizedIdent(self, s: str) -> str:
        return codegen_ir.sanitize_ident(s, {
            "function",
        })

    def getBackendType(self, Typ: QualType) -> QualType:
        flat = [N for N in Typ.flatQualName() if N not in codegen_ir.IGNORED_NAMESPACES]

        wrapper_override = self.base_map.get_wrapper_type(Typ)

        par0 = Typ.par0()

        if flat == ["std", "shared_ptr"]:
            assert par0, Typ

        if flat == [
                "std", "shared_ptr"
        ] and 1 == len(Typ.Parameters) and self.base_map.is_known_type(
                par0) and self.base_map.get_one_type_for_qual_name(  # type: ignore
                    par0
                ).reflectionParams.backend.wasm.holder_type == "shared":  # type: ignore
            assert par0
            return self.getBackendType(par0)

        elif wrapper_override:
            name = wrapper_override

        elif Typ.name == "char" and Typ.isConst and Typ.ptrCount == 1:
            name = "string"

        else:
            match flat:
                case ["int"] | ["float"] | ["double"]:
                    name = "number"

                case ["bool"]:
                    name = "boolean"

                case ["Str"] | ["string"] | ["std", "string"] | ["basic_string" \
                                                                 ] | ["std", "basic_string"]:
                    name = "string"

                case ["void"]:
                    name = flat[0]

                case ["SemId"]:
                    assert par0
                    return self.getBackendType(par0)

                case ["Opt"] | ["std", "optional"]:
                    name = GEN + ".Optional"

                case ["Vec"] | ["immer", "box"] | ["ImmIdT"] | ["immer", "flex_vector"] | [
                    "hstd", "UnorderedMap"
                ] | ["UnorderedMap"] | ["std", "variant"] | ["hstd", "Variant"] | [ \
                         "ImmBox" \
                         ] | ["ImmVec"] | ["hstd", "IntSet"] | ["IntSet"]:
                    name = GEN + "." + self.getBindName(Typ, withParams=False)

                case _:
                    name = self.getBindName(Typ, withParams=False)

        struct = self.base_map.get_struct_for_qual_name(Typ)
        if not struct or struct.reflectionParams.wrapper_has_params:
            return QualType(
                name=name,
                Parameters=[self.getBackendType(P) for P in Typ.Parameters],
            )

        else:
            return QualType(name=name)
