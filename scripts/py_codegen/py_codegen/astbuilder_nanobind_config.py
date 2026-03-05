from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir


class NanobindAstbuilderConfig(AstbulderConfig):
    "Configuration for the nanobind wrapper generators"

    def isUnwrappedTemplateInstantiation(self, t: QualType) -> bool:
        "Exclude nanobind-specific templates from instantiations"
        match tuple(t.flatQualName()):
        # nanobind has explicit casters for this
            case ("std", "variant") | ("std", "pair"):
                return False

            case _:
                return super().isUnwrappedTemplateInstantiation(t)

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
        wrapper_override = self.type_map.get_wrapper_type(Typ)

        if wrapper_override:
            name = wrapper_override

        else:
            flat = [
                N for N in Typ.flatQualName() if N not in codegen_ir.IGNORED_NAMESPACES
            ]

            if flat == ["std", "shared_ptr"] and 1 == len(
                    Typ.Params) and self.type_map.is_known_type(
                        Typ.Params[0]) and self.type_map.get_one_type_for_qual_name(
                            Typ.Params[0]
                        ).ReflectionParams.backend.python.holder_type == "shared":
                return self.getBackendType(Typ.Params[0])

            elif flat == ["ImmIdT"]:
                return QualType(Name="ImmIdT" + Typ.Params[0].Name.replace("Imm", "", 1))

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
                    name = Typ.Params[0].Name

                case ["Bool"]:
                    name = "bool"

                case ["double"]:
                    name = "float"

                case ["void"]:
                    name = "None"

                case ["nanobind", "bytes"]:
                    name = "bytes"

                case ["nanobind", "callable"] | [*_, "PyFunc"]:
                    name = "Callable"

                case ["py", "object"] | ["nanobind", "object"]:
                    name = "object"

                case ["UnorderedMap"]:
                    name = "Dict"

                case ["int64_t"]:
                    name = "int"

                case _:
                    name = "".join(flat)

        struct = self.type_map.get_struct_for_qual_name(Typ)
        if not struct or struct.ReflectionParams.wrapper_has_params:
            res = QualType(Name=name)
            if Typ.Name != "SemId":
                for param in Typ.Params:
                    res.Params.append(self.getBackendType(param))

            return res

        else:
            return QualType(Name=name)
