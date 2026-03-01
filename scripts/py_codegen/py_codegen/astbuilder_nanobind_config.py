from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir


class NanobindAstbuilderConfig(AstbulderConfig):

    # def isUnwrappedTemplateInstantiation(self, t: QualType) -> bool:
    #     match tuple(t.flatQualName()):
    #         case ("std", "variant"):
    #             return False
    #
    #         case _:
    #             return super().isUnwrappedTemplateInstantiation(t)

    def getSanitizedIdent(self, s: str) -> str:
        """
        Convert C++ identifiers to valid Python identifiers.
        Handles keywords, operator overloads, and special characters.
        """
        # Python keywords that need to be escaped
        python_keywords = {
            "and",
            "as",
            "assert",
            "async",
            "await",
            "break",
            "class",
            "continue",
            "def",
            "del",
            "elif",
            "else",
            "except",
            "False",
            "finally",
            "for",
            "from",
            "global",
            "if",
            "import",
            "in",
            "is",
            "lambda",
            "None",
            "nonlocal",
            "not",
            "or",
            "pass",
            "raise",
            "return",
            "True",
            "try",
            "while",
            "with",
            "yield",
        }

        return codegen_ir.sanitize_ident(s, python_keywords)

    def getBackendType(self, Typ: QualType) -> QualType:
        "Map C++ type to the python"
        wrapper_override = self.base_map.get_wrapper_type(Typ)

        if wrapper_override:
            name = wrapper_override

        else:
            flat = [
                N for N in Typ.flatQualName() if N not in codegen_ir.IGNORED_NAMESPACES
            ]

            if flat == ["std", "shared_ptr"] and 1 == len(
                    Typ.Parameters) and self.base_map.is_known_type(
                        Typ.Parameters[0]) and self.base_map.get_one_type_for_qual_name(
                            Typ.Parameters[0]
                        ).reflectionParams.backend.python.holder_type == "shared":
                return self.getBackendType(Typ.Parameters[0])

            elif flat == ["ImmIdT"]:
                return QualType(name="ImmIdT" +
                                Typ.Parameters[0].name.replace("Imm", "", 1))

            match flat:
                case ["Vec"]:
                    name = "List"

                case ["Opt"] | ["std", "optional"]:
                    name = "Optional"

                case ["std", "variant"] | ["Var"]:
                    name = "Union"

                case ["immer", "box"]:
                    name = "ImmBox"

                case ["immer", "flex_vector"]:
                    name = "ImmFlexVector"

                case ["immer", "vector"]:
                    name = "ImmVector"

                case ["immer", "map"]:
                    name = "ImmMap"

                case ["Str"] | ["string"] | ["std", "string"] | ["basic_string" \
                                                                 ] | ["std", "basic_string"]:
                    name = "str"

                case ["SemId"]:
                    name = Typ.Parameters[0].name

                case "Bool":
                    name = "bool"

                case "double":
                    name = "float"

                case ["void"]:
                    name = "None"

                case ["nanobind", "bytes"]:
                    name = "bytes"

                case ["nanobind", "callable"] | [*_, "PyFunc"]:
                    name = "function"

                case ["py", "object"] | ["nanobind", "object"]:
                    name = "object"

                case ["UnorderedMap"]:
                    name = "Dict"

                case _:
                    name = "".join(flat)

        struct = self.base_map.get_struct_for_qual_name(Typ)
        if not struct or struct.reflectionParams.wrapper_has_params:
            res = QualType(name=name)
            if Typ.name != "SemId":
                for param in Typ.Parameters:
                    res.Parameters.append(self.getBackendType(param))

            return res

        else:
            return QualType(name=name)
