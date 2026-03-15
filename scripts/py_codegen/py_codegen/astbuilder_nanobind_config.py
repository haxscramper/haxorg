from py_codegen.astbuilder_base_config import AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir
from beartype.typing import Optional


class NanobindAstbuilderConfig(AstbulderConfig):
    "Configuration for the nanobind wrapper generators"

    def isAcceptedByBackend(self, entry: codegen_ir.GenTuDeclaration) -> bool:
        return self._isExposedByBackendImpl(entry, "python")

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

    def isRegisteredForBacked(self, Type: QualType) -> bool:
        match Type.flatQualNameWithParams():
            case l if l in []:
                return True

            case ["nanobind", *rest]:
                return True

            case ["std", "variant", *rest]:
                return all(self.isRegisteredForBacked(P) for P in Type.Params)

            case _:
                return super().isRegisteredForBacked(Type)

    def getBackendType(self, Type: QualType) -> QualType:
        "Map C++ type to the python"
        wrapper_override = self.type_map.get_wrapper_type(Type)

        if wrapper_override:
            name = wrapper_override

        else:
            match Type.flatQualNameWithParams():
                case ["std", "shared_ptr", _] if self.isKnownClass(Type.par0()):
                    return self.getBackendType(Type.par0())

                case ["org", "imm", "ImmIdT", _]:
                    return QualType(Name="ImmIdT" +
                                    Type.par0().Name.replace("Imm", "", 1))

                case ["org", "imm", "ImmAdapterT", _]:
                    return QualType(Name=Type.par0().Name + "Adapter")

                case ["hstd", "Vec", _]:
                    name = "list"

                case ["hstd", "Opt", _] | ["std", "optional", _]:
                    name = "Optional"

                case ["std", "variant"] | ["hstd", "Var"]:
                    name = "Union"

                case ["std", "pair", _, _]:
                    name = "tuple"

                case ["hstd", "Pair", _, _]:
                    name = "tuple"

                case ["immer", "box", _]:
                    name = "ImmBox"

                case ["immer", "flex_vector", _]:
                    name = "ImmFlexVector"

                case ["immer", "vector", _]:
                    name = "ImmVector"

                case ["immer", "map", _, _]:
                    name = "ImmMap"

                case ["hstd", "Str"] | ["string"] | ["std", "string"] | ["basic_string" \
                                                                 ] | ["std", "basic_string"]:
                    name = "str"

                case ["org", "sem", "SemId"]:
                    name = Type.par0().Name

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

                case ["hstd", "UnorderedMap", _, _]:
                    name = "Dict"

                case ["int64_t"]:
                    name = "int"

                case ["char"] if Type.PtrCount == 1:
                    name = "str"

                case _:
                    name = self.getTypeBindName(Type, withParams=False)

        struct = self.type_map.get_struct_for_qual_name(Type)
        if not struct or struct.ReflectionParams.wrapper_has_params:
            res = QualType(Name=name)
            if Type.Name != "SemId":
                for param in Type.Params:
                    res.Params.append(self.getBackendType(param))

            return res

        else:
            return QualType(Name=name)
