from py_codegen.astbuilder_base_config import BUILTIN_TYPES, AstbulderConfig
from py_codegen.codegen_ir import QualType
from py_codegen import codegen_ir
from beartype.typing import Optional
from beartype import beartype
from py_scriptutils.script_logging import log

CAT = __name__


@beartype
class CAstbuilderConfig(AstbulderConfig):

    def isAcceptedByBackend(self, entry: codegen_ir.GenTuDeclaration) -> bool:
        return self._isExposedByBackendImpl(entry, "c")

    def getTypeBindName(self, Type: QualType, withParams: bool = True) -> str:
        return super().getTypeBindName(Type, withParams)

    def getBackendType(self, Type: QualType) -> QualType:
        prefix = "haxorg_"

        match Type.flatQualNameWithParams():
            case ["hstd", "UnorderedSet", _]:
                return QualType(Name=prefix + "HstdUnorderedSet")

            case ["hstd", "IntSet", _]:
                return QualType(Name=prefix + "HstdIntSet")

            case ["hstd", "Str"]:
                return QualType(Name=prefix + "HstdStr")

            case ["std", "optional", _]:
                return QualType(Name=prefix + "StdOptional")

            case ["hstd", "SortedMap", _, _]:
                return QualType(Name=prefix + "HstdMap")

            case ["haxorg_ptr_payload"]:
                return Type

            case ["org", "sem", "SemId", _]:
                # To avoid creating almost a hundred distinct type instantiations,
                # all versions of the sem ID are mapped to the same type, and in the
                # C code the developer can cast the results of `get()` to retrieve the
                # correct type of the node.
                #
                # TODO: This hardcoded edge case can be replaced with the custom
                # reflection configuration: similar to `void-handle`, I can define a
                # `common-parameter-base` or something like that, and instead of
                # using `void*` for all placeholder returns, I can use `{"Name": "Org"}`
                # as a default template type parameter and map all types to this one.
                return QualType(
                    Name=prefix + self.getTypeBindName(Type, withParams=False) + "OfOrg",
                    DbgOrigin=str(Type.flatQualNameWithParams()),
                )

            case ["org", "imm", "ImmIdT", _]:
                return QualType(Name=prefix + "ImmId")

            case ["hstd", "ext", "ImmBox", _]:
                return self.getBackendType(Type.par0())

            case ["hstd", "SPtr", _] | ["std", "shared_ptr", _]:
                return self.getBackendType(Type.par0())

            case ["hstd", "ext", "ImmVec", _]:
                return QualType(Name=prefix + "ImmVec")

            case ["immer", "flex_vector", _]:
                return QualType(Name=prefix + "immer_flex_vector")

            case ["org", "imm", "ImmAdapterT", _]:
                return QualType(Name=prefix + self.getTypeBindName(Type.par0()) +
                                "Adapter")

            case ["hstd", bit_int
                 ] if bit_int in {"i8", "i16", "i32", "i64", "u8", "u16", "u32", "u64"}:
                sign = bit_int[0]
                if sign == "u":
                    return QualType(Name=f"uint{bit_int[1:]}_t")

                else:
                    return QualType(Name=f"int{bit_int[1:]}_t")

            case ["std", "shared_ptr", _]:
                refl = self.getReflectionParams(Type.par0())
                if refl and refl.backend.c.holder_type == "shared":
                    return self.getBackendType(Type.par0())

                else:
                    return QualType(Name=prefix +
                                    self.getTypeBindName(Type, withParams=True))

            case builtin if builtin in BUILTIN_TYPES:
                return Type

            case _:
                template_type = self.type_map.get_structs_for_template_name(Type)
                # FIXME: This assumes the type does not have a template specializations
                # that are wrapped as independent structures.
                if template_type and template_type[
                        0].ReflectionParams.backend.c.instantiation_mode == "void-handle":
                    useParams = False

                else:
                    useParams = True

                return QualType(
                    Name=prefix + self.getTypeBindName(Type, withParams=useParams),
                    DbgOrigin=str(Type.flatQualNameWithParams()),
                )
