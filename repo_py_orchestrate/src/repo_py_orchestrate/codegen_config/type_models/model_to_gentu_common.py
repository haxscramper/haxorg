import json
from dataclasses import dataclass
from typing import Sequence

import glom
from beartype import beartype
from beartype.typing import Any, Dict, List, Optional
from hstd_py_codegen.gen_cpp.codegen_ir import (
    GenTuFunction,
    QualType,
    QualTypeKind,
)
from hstd_py_text_layout.base.wrap import BlockId
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    ArrayT,
    DynT,
    EnumDef,
    ExplicitDefault,
    ExternalT,
    ListT,
    MapT,
    MethodDef,
    ModelDef,
    NamedT,
    OptT,
    PrimKind,
    PrimT,
    QName,
    RecordDef,
    TupleT,
    TypeParamT,
    TypeRef,
    UnresolvedT,
    VariantT,
)
from loguru import logger

CPP_SPACE_T = QualType(
    Name="unidata",
    IsNamespace=True,
    Spaces=[
        QualType(Name="hstd", IsNamespace=True),
        QualType(Name="ext", IsNamespace=True),
    ],
)

CPP_RESULT_T = QualType(Name="VerifyResult", Spaces=[CPP_SPACE_T])
CPP_CONTEXT_T = QualType(Name="VerifyContext", Spaces=[CPP_SPACE_T])
CPP_CB_T = QualType(Name="VerifyCb", Spaces=[CPP_SPACE_T])
CPP_CB_LIST_T = QualType(Name="VerifyCbList", Spaces=[CPP_SPACE_T])
CPP_KEY_T = QualType(Name="VerifyKey", Spaces=[CPP_SPACE_T])
CPP_VERIFY_COLLECTION_T = QualType(Name="VerifyCheckCollection", Spaces=[CPP_SPACE_T])


@beartype
@dataclass
class ExpressionEvaluation:
    statements: List[BlockId]
    value: BlockId


@beartype
@dataclass
class CheckFunction:
    class_type_name: str
    "Class type ID (fully qualified name as a string) for the check"
    impl: List[GenTuFunction]
    "Static method for the class to perform the check"
    class_field: Optional[str] = None
    "Which field this check applies to -- if empty, apply check to class"


# TODO: Move this logic into the QualType and simplify the
# Type usages for the qualified types in the code, it should
# be possible to use some sort of DSL/`[]` operation
# to make it easier to create `QualType`
@beartype
def qualified_type(
    parts: Sequence[str],
    *,
    namespace_count: int = 0,
    params: Sequence[QualType] = (),
) -> QualType:
    if not parts:
        raise ValueError("A C++ type name cannot be empty")

    return QualType(
        Name=parts[-1],
        Spaces=[
            QualType(Name=part, IsNamespace=index < namespace_count)
            for index, part in enumerate(parts[:-1])
        ],
        Params=list(params),
    )


def enum_member_name(name: str) -> str:
    if name == "None_":
        return "None"

    else:
        return name


# TODO: See above
@beartype
def named_cpp_type(name: str, params: Sequence[QualType] = ()) -> QualType:
    parts = name.split("::")
    return qualified_type(
        parts,
        namespace_count=len(parts) - 1,
        params=params,
    )


def cpp_type_text(typ: QualType) -> str:
    prefix = "::".join([space.Name for space in typ.Spaces] + [typ.Name])
    if typ.Params:
        params = ", ".join(cpp_type_text(param) for param in typ.Params)
        prefix += f"<{params}>"

    return prefix


@beartype
def cpp_config(declaration: RecordDef | EnumDef | MethodDef) -> dict[str, Any]:
    return dict(declaration.backend.get("cpp", {}))


@beartype
def normalize(text: str) -> str:
    return "".join(char if char.isalnum() else "_" for char in text)


@beartype
class TypeTranslation:
    namespaces: dict[str, tuple[str, ...]]

    def __init__(
        self,
        namespaces: dict[str, tuple[str, ...]],
        indexes: Dict[str, ModelIndex],
        models: dict[str, ModelDef],
    ) -> None:
        self.namespaces = namespaces
        self.indexes = indexes
        self.models = models

        self.ast_records: set[tuple[str, QName]] = set()

        for package, index in self.indexes.items():
            roots = [
                record.qname
                for record in index.model.records
                if cpp_config(record).get("ast_root", False)
            ]
            for root in roots:
                for record in index.model.records:
                    if index.derived_from(record.qname, root):
                        self.ast_records.add((package, record.qname))

    def namespace(self, package: str) -> tuple[str, ...]:
        if package in self.namespaces:
            return self.namespaces[package]

        else:
            return tuple(package.split("."))

    def declaration_type(self, package: str, qname: QName) -> QualType:
        namespaces = self.namespace(package)
        result = qualified_type(
            (*namespaces, *qname.parts()),
            namespace_count=len(namespaces),
        )
        outer = qname

        while outer.scope is not None:
            outer = outer.scope

        if self.is_ast(package, outer):
            if qname.scope is None:
                result.Meta["isOrgType"] = True
            else:
                result.Spaces[len(namespaces)].Meta["isOrgType"] = True

        return result

    # FIXME: This is a backend-specific type, the type conversion config
    # should be similar to the type mapping `AstbulderConfig` where conversion
    # from the input type is done using virtual method, and the specific
    # derived cases can override this.
    def is_ast(self, package: str, qname: QName) -> bool:
        return (package, qname) in self.ast_records

    def is_enum(self, package: str, qname: QName) -> bool:
        index = self.indexes.get(package)
        return index is not None and index.is_enum(qname)

    def reference_type(self, package: str, qname: QName) -> QualType:
        result = self.declaration_type(package, qname)
        if self.is_ast(package, qname):
            return named_cpp_type("org::sem::SemId", [result])

        return result

    def variant_config(
        self,
        package: str,
        owner: QName,
        field_name: str,
    ) -> dict[str, Any]:
        record = self.indexes[package].record(owner)
        return dict(
            cpp_config(record).get("variants", {}).get(field_name, {}),
        )

    def variant_type(
        self,
        package: str,
        owner: QName,
        field_name: str,
    ) -> QualType:
        options = self.variant_config(package, owner, field_name)
        name = options.get("variant_name", "Data")
        return self.declaration_type(package, owner.nested(name))

    def type(self, typ: TypeRef, package: str) -> QualType:
        def wrap_annotation(result: QualType) -> QualType:
            if glom.glom(typ, "annotation.backend.cpp.is_ref", default=None):
                logger.info("Got ref annotation")
                return result.asConstRef()

            else:
                return result

        match typ:
            case PrimT():
                primitive_types = {
                    PrimKind.INT8: "int8_t",
                    PrimKind.INT16: "int16_t",
                    PrimKind.INT32: "int",
                    PrimKind.INT64: "int64_t",
                    PrimKind.UINT8: "uint8_t",
                    PrimKind.UINT16: "uint16_t",
                    PrimKind.UINT32: "uint32_t",
                    PrimKind.UINT64: "uint64_t",
                    PrimKind.FLOAT32: "float",
                    PrimKind.FLOAT64: "double",
                    PrimKind.STRING: "hstd::Str",
                    PrimKind.BOOL: "bool",
                    PrimKind.NONE: "void",
                    PrimKind.PATH: "std::filesystem::path",
                }
                if typ.prim == PrimKind.ANY:
                    raise NotImplementedError(
                        "PrimKind.ANY requires an explicit C++ type mapping",
                    )

                return wrap_annotation(named_cpp_type(primitive_types[typ.prim]))

            case NamedT():
                return wrap_annotation(self.reference_type(package, typ.qname))

            case ExternalT():
                return wrap_annotation(self.reference_type(typ.package, typ.qname))

            case ListT():
                return wrap_annotation(
                    named_cpp_type(
                        "hstd::Vec",
                        [self.type(typ.elem, package)],
                    )
                )

            case ArrayT():
                return wrap_annotation(
                    named_cpp_type(
                        "std::array",
                        [
                            self.type(typ.elem, package),
                            QualType(
                                Kind=QualTypeKind.TypeExpr,
                                Expr=str(typ.size),
                            ),
                        ],
                    )
                )

            case MapT():
                return wrap_annotation(
                    named_cpp_type(
                        "hstd::UnorderedMap",
                        [
                            self.type(typ.key, package),
                            self.type(typ.value, package),
                        ],
                    )
                )

            case OptT():
                return wrap_annotation(
                    named_cpp_type(
                        "hstd::Opt",
                        [self.type(typ.elem, package)],
                    )
                )

            case TupleT():
                return wrap_annotation(
                    named_cpp_type(
                        "std::tuple",
                        [self.type(elem, package) for elem in typ.elems],
                    )
                )

            case VariantT():
                return wrap_annotation(self.variant_type(package, typ.owner, typ.field))

            case TypeParamT():
                return wrap_annotation(
                    QualType(
                        Name=typ.name,
                        IsTemplateTypeParam=True,
                    )
                )

            case DynT():
                raise NotImplementedError(
                    "DynT has no fixed C++ storage representation",
                )

            case UnresolvedT():
                raise ValueError(
                    f"Unresolved type in finalized model: {typ.text}",
                )

        raise TypeError(f"Unsupported model type: {typ!r}")

    def enum_default(
        self,
        typ: NamedT | ExternalT,
        package: str,
        value: Any,
    ) -> str:
        enum_package = typ.package if isinstance(typ, ExternalT) else package
        enum_def = self.indexes[enum_package].enums[typ.qname]
        cpp_name = cpp_type_text(
            self.declaration_type(enum_package, typ.qname),
        )

        for member in enum_def.enum_values:
            if value == member.name or value == member.value:
                return f"{cpp_name}::{enum_member_name(member.name)}"

        raise ValueError(
            f"Invalid default {value!r} for enum {typ.qname.to_id()}",
        )

    def default_value(
        self,
        typ: TypeRef,
        package: str,
        default: ExplicitDefault | None,
        infer_default: bool = False,
    ) -> str | None:

        if default is None:
            if infer_default:
                match typ:
                    case OptT():
                        return "std::nullopt"
                    case NamedT() if self.is_ast(package, typ.qname):
                        return f"{cpp_type_text(self.type(typ, package))}::Nil()"
                    case ExternalT() if self.is_ast(typ.package, typ.qname):
                        return f"{cpp_type_text(self.type(typ, package))}::Nil()"
                    case _:
                        return "{}"

            else:
                return None

        value = default.value

        match typ:
            case OptT():
                if value is None:
                    return "std::nullopt"

                inner = self.default_value(
                    typ.elem,
                    package,
                    ExplicitDefault(value=value),
                )
                return f"{cpp_type_text(self.type(typ, package))}{{{inner}}}"

            case NamedT() if self.is_enum(package, typ.qname):
                return self.enum_default(typ, package, value)

            case ExternalT() if self.is_enum(typ.package, typ.qname):
                return self.enum_default(typ, package, value)

            case PrimT():
                integer_kinds = {
                    PrimKind.INT8,
                    PrimKind.INT16,
                    PrimKind.INT32,
                    PrimKind.INT64,
                    PrimKind.UINT8,
                    PrimKind.UINT16,
                    PrimKind.UINT32,
                    PrimKind.UINT64,
                }
                match typ.prim:
                    case PrimKind.BOOL if isinstance(value, bool):
                        return "true" if value else "false"
                    case PrimKind.STRING if isinstance(value, str):
                        return json.dumps(value, ensure_ascii=False)
                    case _ if typ.prim in integer_kinds and type(value) is int:
                        return str(value)
                    case PrimKind.FLOAT32 | PrimKind.FLOAT64:
                        if type(value) not in {int, float}:
                            raise TypeError(f"Invalid floating default: {value!r}")

                        literal = json.dumps(float(value), allow_nan=False)
                        if typ.prim == PrimKind.FLOAT32:
                            literal += "f"
                        return literal

            case ListT() | ArrayT() if isinstance(value, list):
                elements = [
                    self.default_value(
                        typ.elem,
                        package,
                        ExplicitDefault(value=item),
                    )
                    for item in value
                ]
                return "{" + ", ".join(elements) + "}"

        raise NotImplementedError(
            f"Unsupported explicit default for {typ!r}: {value!r}",
        )
