import json
from dataclasses import dataclass, field
from typing import Any, Sequence

import glom
import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from beartype import beartype
from beartype.typing import List, Optional, Tuple, cast
from hstd_py_codegen.gen_cpp import codegen_ir
from hstd_py_codegen.gen_cpp.codegen_ir import (
    GenTuBackendParams,
    GenTuDoc,
    GenTuEntry,
    GenTuEnum,
    GenTuEnumField,
    GenTuField,
    GenTuFunction,
    GenTuIdent,
    GenTuPass,
    GenTuReflParams,
    GenTuStruct,
    GenTuTypeApiTraits,
    GenTuTypeGroup,
    QualType,
    QualTypeKind,
    ReferenceKind,
)
from hstd_py_codegen.gen_cpp.codegen_type_order import expand_type_groups
from hstd_py_lib.external_packages.rich_utils import render_rich
from hstd_py_text_layout.base.wrap import BlockId, TextLayout
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    ArrayT,
    CheckDef,
    DynT,
    EnumDef,
    ExplicitDefault,
    ExprNode,
    ExternalT,
    FieldDef,
    ListT,
    MapT,
    MethodDef,
    ModelDef,
    NamedT,
    OpId,
    OptT,
    PrimKind,
    PrimT,
    QName,
    RecordDef,
    TupleT,
    TypeParamT,
    TypeRef,
    UnresolvedT,
    VariantDef,
    VariantT,
    expr_tree_repr,
)
from loguru import logger
from repo_py_orchestrate.codegen_config.codegen_type_groups import (
    OrgTypeGroup,
    PyhaxorgTypeGroups,
    get_concrete_types,
    populate_immutable_type_groups,
)

DEFAULT_NAMESPACES: dict[str, tuple[str, ...]] = {
    "org.sem.shared": ("org", "sem"),
    "org.sem.model": ("org", "sem"),
    "org.sem.native": ("org", "sem"),
    "org.parse": ("org", "parse"),
    "org.syntax": ("org", "sem"),
    "hstd": ("hstd",),
}

AST_KIND_NAME = "org::sem::OrgSemKind"

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


@dataclass
class CppModelConfig:
    namespaces: dict[str, tuple[str, ...]] = field(
        default_factory=lambda: dict(DEFAULT_NAMESPACES),
    )


def cpp_config(declaration: RecordDef | EnumDef | MethodDef) -> dict[str, Any]:
    return dict(declaration.backend.get("cpp", {}))


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


def named_cpp_type(
    name: str,
    params: Sequence[QualType] = (),
) -> QualType:
    parts = name.split("::")
    return qualified_type(
        parts,
        namespace_count=len(parts) - 1,
        params=params,
    )


def const_ref(typ: QualType) -> QualType:
    return typ.model_copy(
        update=dict(
            IsConst=True,
            RefKind=ReferenceKind.LValue,
        ),
    )


def cpp_type_text(typ: QualType) -> str:
    prefix = "::".join([space.Name for space in typ.Spaces] + [typ.Name])
    if typ.Params:
        params = ", ".join(cpp_type_text(param) for param in typ.Params)
        prefix += f"<{params}>"

    return prefix


def enum_member_name(name: str) -> str:
    if name == "None_":
        return "None"

    return name


class ModelToGenTu:
    def __init__(
        self,
        model: ModelDef,
        *,
        ast: cpp.ASTBuilder,
        dependencies: Sequence[ModelDef] = (),
        config: CppModelConfig | None = None,
    ) -> None:
        self.model = model
        self.config = config if config is not None else CppModelConfig()
        self.ast = ast

        models = [*dependencies, model]
        self.models: dict[str, ModelDef] = {}
        for item in models:
            if item.package in self.models:
                raise ValueError(f"Duplicate model package: {item.package}")
            self.models[item.package] = item

        self.indexes = {
            package: ModelIndex(item) for package, item in self.models.items()
        }
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
        if package in self.config.namespaces:
            return self.config.namespaces[package]

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
                return const_ref(result)

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

    @staticmethod
    def normalize(text: str) -> str:
        return "".join(char if char.isalnum() else "_" for char in text)

    def expression_name(self, stem: str = "expr") -> str:
        result = f"{stem}{self.expression_counter}"
        self.expression_counter += 1
        return result

    def expression_code(self, *parts: str | BlockId) -> BlockId:
        blocks = [
            self.ast.string(part) if isinstance(part, str) else part for part in parts
        ]

        if not blocks:
            return self.ast.string("")

        result = blocks[0]
        for block in blocks[1:]:
            result = self.ast.Trail(result, block, space="")

        return result

    def expression_call(
        self,
        name: str,
        args: Sequence[BlockId] = (),
        params: Sequence[QualType] = (),
    ) -> BlockId:
        return self.ast.CallStatic(
            CPP_SPACE_T,
            name,
            Args=list(args),
            Params=list(params) if params else None,
        )

    def expression_local(
        self,
        value: BlockId,
        statements: Sequence[BlockId] = (),
    ) -> ExpressionEvaluation:
        name = self.expression_name()

        declaration = self.ast.VarDecl(
            cpp.ParmVarParams(
                type=const_ref(QualType(Name="auto")),
                name=name,
                defArg=value,
                IsLine=False,
            )
        )

        return ExpressionEvaluation(
            statements=[*statements, declaration],
            value=self.ast.string(name),
        )

    def expression_assign(self, target: BlockId, value: BlockId) -> BlockId:
        return self.expression_code(target, " = ", value, ";")

    def expression_cast(self, typ: QualType, value: BlockId) -> BlockId:
        return self.ast.XCall(
            "static_cast",
            args=[value],
            Params=[typ],
        )

    def expression_native_type(
        self,
        typ: TypeRef,
        package: Optional[str] = None,
    ) -> QualType:
        package = self.model.package if package is None else package

        match typ:
            case DynT():
                return QualType(Name="EvalDynamic", Spaces=[CPP_SPACE_T])

            case ListT():
                return named_cpp_type(
                    "hstd::Vec",
                    [self.expression_native_type(typ.elem, package)],
                )

            case ArrayT():
                return named_cpp_type(
                    "std::array",
                    [
                        self.expression_native_type(typ.elem, package),
                        QualType(
                            Kind=QualTypeKind.TypeExpr,
                            Expr=str(typ.size),
                        ),
                    ],
                )

            case MapT():
                return named_cpp_type(
                    "hstd::UnorderedMap",
                    [
                        self.expression_native_type(typ.key, package),
                        self.expression_native_type(typ.value, package),
                    ],
                )

            case OptT():
                return named_cpp_type(
                    "hstd::Opt",
                    [self.expression_native_type(typ.elem, package)],
                )

            case TupleT():
                return named_cpp_type(
                    "std::tuple",
                    [self.expression_native_type(elem, package) for elem in typ.elems],
                )

            case _:
                return self.type(typ, package)

    def expression_result_type(self, expr: ExprNode) -> QualType:
        if expr.typed_as is None:
            raise ValueError(
                f"Cannot lower '{expr.op.value}' at {expr.loc.render()}: "
                "the finalized expression has no inferred type"
            )

        return self.expression_native_type(expr.typed_as)

    def expression_slot(
        self,
        typ: QualType,
    ) -> Tuple[BlockId, BlockId]:
        name = self.expression_name("result")
        value = self.ast.string(name)

        declaration = self.ast.VarDecl(
            cpp.ParmVarParams(
                type=named_cpp_type("std::optional", [typ]),
                name=name,
                defArg=self.ast.string("std::nullopt"),
                IsLine=False,
            )
        )

        return value, declaration

    def expression_emplace(
        self,
        slot: BlockId,
        value: BlockId,
    ) -> BlockId:
        return self.ast.XCallRef(
            slot,
            "emplace",
            args=[value],
            Stmt=True,
        )

    def expression_slot_value(self, slot: BlockId) -> BlockId:
        return self.ast.XCallRef(slot, "value")

    def expression_args(
        self,
        args: Sequence[ExprNode],
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> Tuple[List[BlockId], List[BlockId]]:
        statements: List[BlockId] = []
        values: List[BlockId] = []

        for arg in args:
            lowered = self.gen_expression_eval(arg, this_expr, bindings)
            statements.extend(lowered.statements)
            values.append(lowered.value)

        return statements, values

    def expression_callback(
        self,
        body: ExprNode,
        binders: Sequence[str],
        this_expr: BlockId,
        bindings: dict[str, BlockId],
    ) -> BlockId:
        local_bindings = dict(bindings)
        parameters: List[cpp.ParmVarParams] = []

        for binder in binders:
            name = self.expression_name("item")
            parameters.append(
                cpp.ParmVarParams(
                    type=const_ref(QualType(Name="auto")),
                    name=name,
                )
            )
            local_bindings[binder] = self.ast.string(name)

        lowered = self.gen_expression_eval(
            body,
            this_expr,
            local_bindings,
        )

        return self.ast.Lambda(
            cpp.LambdaParams(
                Args=parameters,
                ResultTy=None,
                CaptureList=[cpp.LambdaCapture(ByRef=True)],
                Body=[
                    *lowered.statements,
                    self.ast.Return(lowered.value),
                ],
                IsLine=False,
            )
        )

    def expression_enum_value(
        self,
        typ: TypeRef,
        name: str,
    ) -> BlockId:
        match typ:
            case NamedT():
                package = self.model.package
                qname = typ.qname

            case ExternalT():
                package = typ.package
                qname = typ.qname

            case _:
                raise TypeError(
                    f"Cannot generate enum member {name!r}: "
                    f"expected a named enum type, got {type_text(typ)}"
                )

        index = self.indexes[package]
        enum = index.enums.get(qname)

        if enum is None:
            raise ValueError(
                f"Cannot generate enum member {name!r}: "
                f"{package}:{qname.to_id()} is not an indexed enum"
            )

        if not any(member.name == name for member in enum.enum_values):
            expected = ", ".join(member.name for member in enum.enum_values)
            raise ValueError(
                f"Unknown member {name!r} of {qname.to_id()}; expected one of: {expected}"
            )

        cpp_name = (
            cpp_config(enum)
            .get("value_names", {})
            .get(
                name,
                enum_member_name(name),
            )
        )

        return self.ast.Scoped(
            self.declaration_type(package, qname),
            self.ast.string(cpp_name),
        )

    def expression_record_field(
        self,
        package: str,
        record: RecordDef,
        name: str,
    ) -> Optional[Tuple[RecordDef, FieldDef]]:
        for member in record.fields:
            if member.name == name:
                return record, member

        index = self.indexes[package]

        for base in record.bases:
            found = self.expression_record_field(
                package,
                index.record(base),
                name,
            )
            if found is not None:
                return found

        return None

    def expression_field_access(
        self,
        expr: ExprNode,
        source: BlockId,
    ) -> BlockId:
        assert expr.str_val is not None

        source_type = expr.args[0].typed_as
        package: Optional[str] = None
        qname: Optional[QName] = None

        match source_type:
            case NamedT():
                package = self.model.package
                qname = source_type.qname

            case ExternalT():
                package = source_type.package
                qname = source_type.qname

            case _:
                pass

        if package is not None and qname is not None:
            index = self.indexes[package]

            if not index.is_enum(qname):
                record = index.record(qname)
                found = self.expression_record_field(
                    package,
                    record,
                    expr.str_val,
                )

                if found is not None:
                    owner, member = found
                    cpp_name = (
                        cpp_config(owner)
                        .get(
                            "field_names",
                            {},
                        )
                        .get(member.name, member.name)
                    )

                    if self.is_ast(package, qname):
                        return self.ast.Arrow(
                            source,
                            self.ast.string(cpp_name),
                        )

                    return self.ast.Dot(
                        source,
                        self.ast.string(cpp_name),
                    )

        return self.expression_call(
            "eval_get_field",
            args=[source, self.ast.StringLiteral(expr.str_val)],
            params=[self.expression_result_type(expr)],
        )

    def expression_case_test(
        self,
        expr: ExprNode,
        source: BlockId,
    ) -> BlockId:
        assert expr.str_val is not None

        source_type = expr.args[0].typed_as

        match source_type:
            case VariantT():
                package = self.model.package
                record = self.indexes[package].record(source_type.owner)
                variant = next(
                    variant
                    for variant in record.variants
                    if variant.field == source_type.field
                )

                case = next(
                    (case for case in variant.cases if case.case.name == expr.str_val),
                    None,
                )

                if case is None:
                    expected = ", ".join(case.case.name for case in variant.cases)
                    raise ValueError(
                        f"Unknown variant case {expr.str_val!r} at "
                        f"{expr.loc.render()}; expected one of: {expected}"
                    )

                return self.ast.XCall(
                    "std::holds_alternative",
                    args=[source],
                    Params=[
                        self.declaration_type(package, case.case),
                    ],
                )

            case NamedT() | ExternalT():
                return self.ast.XCallRef(
                    source,
                    f"is{expr.str_val}",
                )

            case _:
                raise TypeError(
                    f"Cannot lower case test at {expr.loc.render()}: "
                    f"unsupported subject type {source_type!r}"
                )

    def expression_case_kind(
        self,
        expr: ExprNode,
        source: BlockId,
    ) -> BlockId:
        source_type = expr.args[0].typed_as

        match source_type:
            case VariantT():
                return self.expression_cast(
                    self.expression_result_type(expr),
                    self.ast.XCallRef(source, "index"),
                )

            case NamedT() | ExternalT():
                package = (
                    source_type.package
                    if isinstance(source_type, ExternalT)
                    else self.model.package
                )

                record = self.indexes[package].record(source_type.qname)

                if len(record.variants) != 1:
                    fields = ", ".join(variant.field for variant in record.variants)
                    raise ValueError(
                        f"Cannot choose a variant kind getter for "
                        f"{record.qname.to_id()} at {expr.loc.render()}: "
                        f"expected one variant, got fields [{fields}]"
                    )

                variant = record.variants[0]
                getter = self.variant_config(
                    package,
                    record.qname,
                    variant.field,
                ).get("kind_getter", "getKind")

                return self.ast.XCallRef(source, getter)

            case _:
                raise TypeError(
                    f"Cannot lower case-kind access at {expr.loc.render()}: "
                    f"unsupported subject type {source_type!r}"
                )

    def expression_runtime_call(
        self,
        method: str,
        args: Sequence[BlockId],
        params: Sequence[QualType] = (),
    ) -> BlockId:
        return self.ast.XCallRef(
            self.ast.string("expression_runtime"),
            method,
            args=list(args),
            Params=list(params) if params else None,
        )

    def gen_expression_eval(
        self,
        expr: ExprNode,
        this_expr: BlockId,
        bindings: Optional[dict[str, BlockId]] = None,
    ) -> ExpressionEvaluation:
        bindings = {} if bindings is None else bindings

        match expr.op:
            case OpId.THIS:
                return ExpressionEvaluation([], this_expr)

            case OpId.VAR:
                assert expr.str_val is not None

                if expr.str_val not in bindings:
                    available = ", ".join(sorted(bindings))
                    raise ValueError(
                        f"Unbound expression variable {expr.str_val!r} at "
                        f"{expr.loc.render()}; available bindings: [{available}]"
                    )

                return ExpressionEvaluation([], bindings[expr.str_val])

            case OpId.CONST_INT:
                assert expr.int_val is not None
                return self.expression_local(
                    self.expression_cast(
                        self.expression_result_type(expr),
                        self.ast.Literal(expr.int_val),
                    )
                )

            case OpId.CONST_FLOAT:
                assert expr.float_val is not None
                return self.expression_local(
                    self.expression_cast(
                        self.expression_result_type(expr),
                        self.ast.string(json.dumps(expr.float_val, allow_nan=False)),
                    )
                )

            case OpId.CONST_BOOL:
                assert expr.bool_val is not None
                return self.expression_local(
                    self.ast.string("true" if expr.bool_val else "false")
                )

            case OpId.CONST_STR:
                assert expr.str_val is not None
                return self.expression_local(
                    self.ast.XConstructObj(
                        self.expression_result_type(expr),
                        Args=[self.ast.StringLiteral(expr.str_val)],
                    )
                )

            case OpId.AND | OpId.OR:
                name = self.expression_name("condition")
                result = self.ast.string(name)
                is_and = expr.op == OpId.AND

                statements = [
                    self.ast.VarDecl(
                        cpp.ParmVarParams(
                            type=QualType(Name="bool"),
                            name=name,
                            defArg=self.ast.string("true" if is_and else "false"),
                            IsLine=False,
                        )
                    )
                ]

                for arg in expr.args:
                    lowered = self.gen_expression_eval(
                        arg,
                        this_expr,
                        bindings,
                    )

                    condition = (
                        result if is_and else self.expression_code("!(", result, ")")
                    )

                    statements.append(
                        self.ast.IfStmt(
                            cpp.IfStmtParams(
                                Branches=[
                                    cpp.IfStmtParams.Branch(
                                        Cond=condition,
                                        Then=self.ast.stack(
                                            [
                                                *lowered.statements,
                                                self.expression_assign(
                                                    result,
                                                    lowered.value,
                                                ),
                                            ]
                                        ),
                                    )
                                ]
                            )
                        )
                    )

                return ExpressionEvaluation(statements, result)

            case OpId.NOT:
                arg = self.gen_expression_eval(
                    expr.args[0],
                    this_expr,
                    bindings,
                )

                return self.expression_local(
                    self.expression_code("!(", arg.value, ")"),
                    arg.statements,
                )

            case OpId.COND:
                condition = self.gen_expression_eval(
                    expr.args[0],
                    this_expr,
                    bindings,
                )
                then_value = self.gen_expression_eval(
                    expr.args[1],
                    this_expr,
                    bindings,
                )
                else_value = self.gen_expression_eval(
                    expr.args[2],
                    this_expr,
                    bindings,
                )

                slot, declaration = self.expression_slot(
                    self.expression_result_type(expr)
                )

                branch = self.ast.IfStmt(
                    cpp.IfStmtParams(
                        Branches=[
                            cpp.IfStmtParams.Branch(
                                Cond=condition.value,
                                Then=self.ast.stack(
                                    [
                                        *then_value.statements,
                                        self.expression_emplace(
                                            slot,
                                            then_value.value,
                                        ),
                                    ]
                                ),
                            ),
                            cpp.IfStmtParams.Branch(
                                Then=self.ast.stack(
                                    [
                                        *else_value.statements,
                                        self.expression_emplace(
                                            slot,
                                            else_value.value,
                                        ),
                                    ]
                                )
                            ),
                        ]
                    )
                )

                return ExpressionEvaluation(
                    [
                        *condition.statements,
                        declaration,
                        branch,
                    ],
                    self.expression_slot_value(slot),
                )

            case OpId.LET:
                value = self.gen_expression_eval(
                    expr.args[0],
                    this_expr,
                    bindings,
                )

                local_bindings = dict(bindings)
                local_bindings[expr.binders[0]] = value.value

                body = self.gen_expression_eval(
                    expr.args[1],
                    this_expr,
                    local_bindings,
                )

                return ExpressionEvaluation(
                    [*value.statements, *body.statements],
                    body.value,
                )

            case OpId.TYPE_COND:
                subject = self.gen_expression_eval(
                    expr.args[0],
                    this_expr,
                    bindings,
                )

                ignore_unhandled = bool(expr.bool_val)

                if ignore_unhandled:
                    if not isinstance(expr.typed_as, OptT):
                        raise TypeError(
                            f"Optional type dispatch at {expr.loc.render()} "
                            f"must have an optional result, got {expr.typed_as!r}"
                        )

                    value_type = self.expression_native_type(expr.typed_as.elem)
                else:
                    value_type = self.expression_result_type(expr)

                slot, declaration = self.expression_slot(value_type)
                statements = [*subject.statements, declaration]

                for case in expr.args[1:]:
                    if case.op != OpId.TYPE_CASE or case.type_val is None:
                        raise ValueError(
                            f"Invalid type-dispatch branch at "
                            f"{case.loc.render()}: expected TYPE_CASE with "
                            f"a target type, got {case.op.value}"
                        )

                    candidate_name = self.expression_name("candidate")
                    candidate = self.ast.string(candidate_name)

                    candidate_declaration = self.ast.VarDecl(
                        cpp.ParmVarParams(
                            type=QualType(Name="auto").asConstPtr(),
                            name=candidate_name,
                            defArg=self.expression_runtime_call(
                                "try_as",
                                args=[subject.value],
                                params=[self.expression_native_type(case.type_val)],
                            ),
                            IsLine=False,
                        )
                    )

                    local_bindings = dict(bindings)
                    local_bindings[case.binders[0]] = self.expression_code(
                        "(*",
                        candidate,
                        ")",
                    )

                    body = self.gen_expression_eval(
                        case.args[0],
                        this_expr,
                        local_bindings,
                    )

                    match_branch = self.ast.IfStmt(
                        cpp.IfStmtParams(
                            Branches=[
                                cpp.IfStmtParams.Branch(
                                    Cond=self.expression_code(
                                        candidate,
                                        " != nullptr",
                                    ),
                                    Then=self.ast.stack(
                                        [
                                            *body.statements,
                                            self.expression_emplace(
                                                slot,
                                                body.value,
                                            ),
                                        ]
                                    ),
                                )
                            ]
                        )
                    )

                    statements.append(
                        self.ast.IfStmt(
                            cpp.IfStmtParams(
                                Branches=[
                                    cpp.IfStmtParams.Branch(
                                        Cond=self.expression_code(
                                            "!(",
                                            self.ast.XCallRef(
                                                slot,
                                                "has_value",
                                            ),
                                            ")",
                                        ),
                                        Then=self.ast.stack(
                                            [
                                                candidate_declaration,
                                                match_branch,
                                            ]
                                        ),
                                    )
                                ]
                            )
                        )
                    )

                if not ignore_unhandled:
                    expected = ", ".join(
                        type_text(case.type_val)
                        for case in expr.args[1:]
                        if case.type_val is not None
                    )

                    message = (
                        f"No type case matched at {expr.loc.render()}; "
                        f"expected one of: {expected}"
                    )

                    statements.append(
                        self.ast.IfStmt(
                            cpp.IfStmtParams(
                                Branches=[
                                    cpp.IfStmtParams.Branch(
                                        Cond=self.expression_code(
                                            "!(",
                                            self.ast.XCallRef(
                                                slot,
                                                "has_value",
                                            ),
                                            ")",
                                        ),
                                        Then=self.expression_code(
                                            "throw std::runtime_error{",
                                            self.ast.StringLiteral(message),
                                            "};",
                                        ),
                                    )
                                ]
                            )
                        )
                    )

                return ExpressionEvaluation(
                    statements,
                    slot if ignore_unhandled else self.expression_slot_value(slot),
                )

            case OpId.TYPE_CASE:
                raise ValueError(
                    f"TYPE_CASE at {expr.loc.render()} cannot be evaluated "
                    "independently; it must be a branch of TYPE_COND"
                )

            case (
                OpId.ALL
                | OpId.EXISTS
                | OpId.EXISTS_ONE
                | OpId.MAP
                | OpId.FILTER
                | OpId.FILTER_MAP
                | OpId.TAKE_WHILE
                | OpId.GROUP_BY
            ):
                collection = self.gen_expression_eval(
                    expr.args[0],
                    this_expr,
                    bindings,
                )

                callback = self.expression_callback(
                    expr.args[1],
                    expr.binders,
                    this_expr,
                    bindings,
                )

                callback_name = self.expression_name("callback")
                callback_value = self.ast.string(callback_name)

                declaration = self.ast.VarDecl(
                    cpp.ParmVarParams(
                        type=QualType(Name="auto"),
                        name=callback_name,
                        defArg=callback,
                        IsLine=False,
                    )
                )

                function = {
                    OpId.ALL: "eval_all",
                    OpId.EXISTS: "eval_exists",
                    OpId.EXISTS_ONE: "eval_exists_one",
                    OpId.MAP: "eval_map",
                    OpId.FILTER: "eval_filter",
                    OpId.FILTER_MAP: "eval_filter_map",
                    OpId.TAKE_WHILE: "eval_take_while",
                    OpId.GROUP_BY: "eval_group_by",
                }[expr.op]

                params = (
                    []
                    if expr.op in {OpId.ALL, OpId.EXISTS, OpId.EXISTS_ONE}
                    else [self.expression_result_type(expr)]
                )

                return self.expression_local(
                    self.expression_call(
                        function,
                        args=[collection.value, callback_value],
                        params=params,
                    ),
                    [*collection.statements, declaration],
                )

            case OpId.FOLD:
                statements, args = self.expression_args(
                    expr.args[:2],
                    this_expr,
                    bindings,
                )

                callback_name = self.expression_name("callback")
                callback = self.expression_callback(
                    expr.args[2],
                    expr.binders,
                    this_expr,
                    bindings,
                )

                statements.append(
                    self.ast.VarDecl(
                        cpp.ParmVarParams(
                            type=QualType(Name="auto"),
                            name=callback_name,
                            defArg=callback,
                            IsLine=False,
                        )
                    )
                )

                return self.expression_local(
                    self.expression_call(
                        "eval_fold",
                        args=[
                            *args,
                            self.ast.string(callback_name),
                        ],
                        params=[self.expression_result_type(expr)],
                    ),
                    statements,
                )

            case OpId.LIST_EMPTY | OpId.MAP_EMPTY:
                return self.expression_local(
                    self.ast.XConstructObj(
                        self.expression_result_type(expr),
                        Args=[],
                    )
                )

            case _:
                statements, args = self.expression_args(
                    expr.args,
                    this_expr,
                    bindings,
                )

        match expr.op:
            case OpId.EQ | OpId.NE:
                value = self.expression_call(
                    "eval_equal",
                    args=args,
                )

                if expr.op == OpId.NE:
                    value = self.expression_code("!(", value, ")")

            case OpId.LT | OpId.LE:
                operator = "<" if expr.op == OpId.LT else "<="
                value = self.expression_code(
                    "(",
                    args[0],
                    f" {operator} ",
                    args[1],
                    ")",
                )

            case OpId.ADD | OpId.SUB | OpId.MUL | OpId.DIV:
                operator = {
                    OpId.ADD: "+",
                    OpId.SUB: "-",
                    OpId.MUL: "*",
                    OpId.DIV: "/",
                }[expr.op]

                result_type = self.expression_result_type(expr)

                left = args[0]
                right = args[1]

                if expr.op == OpId.DIV:
                    left = self.expression_cast(result_type, left)
                    right = self.expression_cast(result_type, right)

                value = self.expression_cast(
                    result_type,
                    self.expression_code(
                        "(",
                        left,
                        f" {operator} ",
                        right,
                        ")",
                    ),
                )

            case OpId.GET_FIELD:
                value = self.expression_field_access(expr, args[0])

            case OpId.STR_SIZE:
                value = self.expression_call(
                    "eval_str_size",
                    args=[self.ast.Addr(args[0])],
                )

            case OpId.LIST_SIZE | OpId.MAP_SIZE:
                value = self.expression_cast(
                    self.expression_result_type(expr),
                    self.ast.XCallRef(args[0], "size"),
                )

            case OpId.STR_MATCHES:
                assert expr.str_val is not None
                value = self.expression_call(
                    "eval_str_matches",
                    args=[
                        args[0],
                        self.ast.StringLiteral(expr.str_val),
                    ],
                )

            case OpId.STR_FORMAT:
                assert expr.str_val is not None
                value = self.expression_call(
                    "eval_str_format",
                    args=[
                        self.ast.StringLiteral(expr.str_val),
                        *args,
                    ],
                )

            case OpId.LIST_CONTAINS:
                value = self.expression_call(
                    "eval_list_contains",
                    args=args,
                )

            case OpId.LIST_AT | OpId.MAP_GET:
                value = self.ast.XCallRef(
                    args[0],
                    "at",
                    args=[args[1]],
                )

            case OpId.MAP_CONTAINS:
                value = self.ast.XCallRef(
                    args[0],
                    "contains",
                    args=[args[1]],
                )

            case (
                OpId.LIST_SLICE
                | OpId.LIST_CONCAT
                | OpId.MAP_INSERT
                | OpId.MAP_KEYS
                | OpId.MAP_VALUES
                | OpId.SUM
                | OpId.MIN
                | OpId.MAX
            ):
                function = {
                    OpId.LIST_SLICE: "eval_list_slice",
                    OpId.LIST_CONCAT: "eval_list_concat",
                    OpId.MAP_INSERT: "eval_map_insert",
                    OpId.MAP_KEYS: "eval_map_keys",
                    OpId.MAP_VALUES: "eval_map_values",
                    OpId.SUM: "eval_sum",
                    OpId.MIN: "eval_min",
                    OpId.MAX: "eval_max",
                }[expr.op]

                value = self.expression_call(
                    function,
                    args=args,
                    params=[self.expression_result_type(expr)],
                )

            case OpId.OPT_HAS_VALUE:
                value = self.ast.XCallRef(args[0], "has_value")

            case OpId.OPT_VALUE:
                value = self.ast.XCallRef(args[0], "value")

            case OpId.CASE_IS:
                value = self.expression_case_test(expr, args[0])

            case OpId.CASE_WHICH:
                value = self.expression_case_kind(expr, args[0])

            case OpId.ENUM_IS:
                assert expr.str_val is not None
                source_type = expr.args[0].typed_as

                if source_type is None:
                    raise ValueError(
                        f"Enum comparison at {expr.loc.render()} "
                        "has no inferred subject type"
                    )

                value = self.expression_code(
                    "(",
                    args[0],
                    " == ",
                    self.expression_enum_value(
                        source_type,
                        expr.str_val,
                    ),
                    ")",
                )

            case OpId.NTH_GET:
                assert expr.int_val is not None
                value = self.ast.XCall(
                    "std::get",
                    args=[args[0]],
                    Params=[
                        QualType(
                            Kind=QualTypeKind.TypeExpr,
                            Expr=str(expr.int_val),
                        )
                    ],
                )

            case OpId.WALK:
                value = self.expression_call(
                    "eval_walk",
                    args=[
                        self.ast.string("expression_runtime"),
                        args[0],
                    ],
                    params=[self.expression_result_type(expr)],
                )

            case OpId.IS_DERIVED:
                if expr.type_val is None:
                    raise ValueError(
                        f"Derived-type test at {expr.loc.render()} has no target type"
                    )

                value = self.expression_code(
                    "(",
                    self.expression_runtime_call(
                        "try_as",
                        args=[args[0]],
                        params=[self.expression_native_type(expr.type_val)],
                    ),
                    " != nullptr)",
                )

            case OpId.PATH_OF:
                value = self.expression_runtime_call(
                    "path_of",
                    args=[args[0]],
                )

            case OpId.TYPE_OF:
                value = self.expression_runtime_call(
                    "type_of",
                    args=[args[0]],
                )

            case _:
                raise ValueError(
                    f"Unhandled expression '{expr.op.value}' at "
                    f"{expr.loc.render()}: "
                    f"{render_rich(expr_tree_repr(expr))}"
                )

        return self.expression_local(value, statements)

    def expression_needs_runtime(self, expr: ExprNode) -> bool:
        match expr.op:
            case (
                OpId.WALK | OpId.TYPE_COND | OpId.IS_DERIVED | OpId.PATH_OF | OpId.TYPE_OF
            ):
                return True

            case _:
                return any(self.expression_needs_runtime(arg) for arg in expr.args)

    def gen_expression_runtime(self) -> List[BlockId]:
        runtime = self.ast.string("expression_runtime")

        statements = [
            self.ast.VarDecl(
                cpp.ParmVarParams(
                    type=QualType(
                        Name="EvalRuntime",
                        Spaces=[CPP_SPACE_T],
                    ),
                    name="expression_runtime",
                    defArg=self.ast.XConstructObj(
                        QualType(
                            Name="EvalRuntime",
                            Spaces=[CPP_SPACE_T],
                        ),
                        Args=[self.ast.string("ctx")],
                    ),
                    IsLine=False,
                )
            )
        ]

        for package, model in self.models.items():
            for declaration in (*model.records, *model.enums):
                statements.append(
                    self.ast.XCallRef(
                        runtime,
                        "register_type",
                        args=[self.ast.StringLiteral(declaration.qname.to_id())],
                        Params=[
                            self.declaration_type(
                                package,
                                declaration.qname,
                            )
                        ],
                        Stmt=True,
                    )
                )

            index = self.indexes[package]

            for record in model.records:
                for base in model.records:
                    if record.qname != base.qname and index.derived_from(
                        record.qname,
                        base.qname,
                    ):
                        statements.append(
                            self.ast.XCallRef(
                                runtime,
                                "register_base",
                                Params=[
                                    self.declaration_type(
                                        package,
                                        record.qname,
                                    ),
                                    self.declaration_type(
                                        package,
                                        base.qname,
                                    ),
                                ],
                                Stmt=True,
                            )
                        )

        statements.append(
            self.ast.XCallRef(
                runtime,
                "index",
                args=[
                    self.expression_code(
                        "(*",
                        self.ast.string("this_obj"),
                        ")",
                    )
                ],
                Stmt=True,
            )
        )

        return statements

    def gen_check_eval(self, check: CheckDef, this_expr: BlockId) -> BlockId:
        self.expression_counter = 0

        statements: List[BlockId] = []

        if self.expression_needs_runtime(check.cond) or self.expression_needs_runtime(
            check.message
        ):
            statements.extend(self.gen_expression_runtime())

        root = self.expression_local(self.expression_code("(*(", this_expr, "))"))
        statements.extend(root.statements)

        condition = self.gen_expression_eval(
            check.cond,
            root.value,
        )
        message = self.gen_expression_eval(
            check.message,
            root.value,
        )

        statements.extend(condition.statements)

        statements.append(
            self.ast.IfStmt(
                cpp.IfStmtParams(
                    Branches=[
                        cpp.IfStmtParams.Branch(
                            Cond=condition.value,
                            Then=self.ast.Return(
                                self.ast.CallStatic(
                                    CPP_RESULT_T,
                                    "Ok",
                                )
                            ),
                        ),
                        cpp.IfStmtParams.Branch(
                            Then=self.ast.stack(
                                [
                                    *message.statements,
                                    self.ast.Return(
                                        self.ast.CallStatic(
                                            CPP_RESULT_T,
                                            "Error",
                                            Args=[message.value],
                                        )
                                    ),
                                ]
                            )
                        ),
                    ]
                )
            )
        )

        return self.ast.stack(statements)

    def gen_record_check(
        self,
        owner: RecordDef,
        check: CheckDef,
        parentClass: QualType,
    ) -> GenTuFunction:
        return GenTuFunction(
            Name=f"__check_record_{self.normalize(check.id)}",
            ReturnType=CPP_RESULT_T,
            Args=[
                GenTuIdent(Type=CPP_CONTEXT_T.asConstPtr(), Name="ctx"),
                GenTuIdent(Type=QualType(Name="void").asConstPtr(), Name="value"),
            ],
            IsStatic=True,
            ParentClass=parentClass,
            Body=self.ast.stack(
                [
                    self.ast.VarDecl(
                        cpp.ParmVarParams(
                            type=QualType(Name="auto").asConstPtr(),
                            name="this_obj",
                            defArg=self.ast.XCall(
                                "static_cast",
                                args=[self.ast.string("value")],
                                Params=[
                                    self.declaration_type(
                                        self.model.package,
                                        owner.qname,
                                    ).asConstPtr()
                                ],
                            ),
                        )
                    ),
                    self.gen_check_eval(
                        check,
                        this_expr=self.ast.string("this_obj"),
                    ),
                ]
            ),
        )

    def gen_field_check(
        self,
        owner: RecordDef,
        field: FieldDef,
        check: CheckDef,
        parentClass: QualType,
    ) -> GenTuFunction:
        "Generate a single static function used to perform the runtime check on the field state"

        cpp_name = (
            cpp_config(owner)
            .get("field_names", {})
            .get(
                field.name,
                field.name,
            )
        )

        this_expr = self.ast.Addr(
            self.ast.Arrow(
                self.ast.string("this_obj"),
                self.ast.string(cpp_name),
            )
        )

        return GenTuFunction(
            Name=f"__check_{field.name}_{self.normalize(check.id)}",
            ReturnType=CPP_RESULT_T,
            Args=[
                GenTuIdent(Type=CPP_CONTEXT_T.asConstPtr(), Name="ctx"),
                GenTuIdent(Type=QualType(Name="void").asConstPtr(), Name="value"),
            ],
            IsStatic=True,
            ParentClass=parentClass,
            Body=self.ast.stack(
                [
                    self.ast.VarDecl(
                        cpp.ParmVarParams(
                            type=QualType(Name="auto").asConstPtr(),
                            name="this_obj",
                            defArg=self.ast.XCall(
                                "static_cast",
                                args=[self.ast.string("value")],
                                Params=[
                                    self.declaration_type(
                                        self.model.package, owner.qname
                                    ).asConstPtr()
                                ],
                            ),
                        )
                    ),
                    self.gen_check_eval(check, this_expr=this_expr),
                ]
            ),
        )

    def field(
        self,
        owner: RecordDef,
        item: FieldDef,
        parentClass: QualType,
    ) -> Tuple[GenTuField, Optional[CheckFunction]]:
        options = cpp_config(owner)
        field_options = options.get("fields", {}).get(item.name, {})
        names = options.get("field_names", {})
        defaults = options.get("field_defaults", {})
        check_functions: Optional[CheckFunction] = None

        if item.checks:
            logger.info(f"Have checks for the field {item.name}")
            impl_cb = list()
            for ch in item.checks:
                impl_cb.append(
                    self.gen_field_check(
                        owner,
                        item,
                        ch,
                        parentClass=parentClass,
                    )
                )

            check_functions = CheckFunction(
                class_type_name=owner.qname.to_id(),
                impl=impl_cb,
                class_field=item.name,
            )

        field_type = self.type(item.type, self.model.package)
        if "type" in field_options:
            field_type = named_cpp_type(field_options["type"])

        if item.name in defaults:
            value = defaults[item.name]
        else:
            value = self.default_value(
                item.type,
                self.model.package,
                item.default,
            )

        field = GenTuField(
            Type=field_type,
            Name=names.get(item.name, item.name),
            Doc=GenTuDoc(item.doc),
            Value=value,
        )

        return (field, check_functions)

    def argument_const_ref(self, typ: TypeRef, package: str) -> bool:
        match typ:
            case PrimT():
                return typ.prim in {PrimKind.STRING, PrimKind.PATH}
            case NamedT():
                return not self.is_enum(package, typ.qname)
            case ExternalT():
                return not self.is_enum(typ.package, typ.qname)
            case TypeParamT():
                return False
            case _:
                return True

    def method(self, owner: RecordDef, item: MethodDef) -> GenTuFunction:
        if item.type_params:
            raise NotImplementedError(
                "Generic methods require GenTuTemplateParams lowering",
            )

        options = cpp_config(item)
        args: list[GenTuIdent] = []

        for arg in item.args:
            if arg.is_vararg or arg.is_kwarg:
                raise NotImplementedError(
                    f"Variadic model method: {owner.qname.to_id()}.{item.name}",
                )

            arg_options = options.get("args", {}).get(arg.name, {})
            arg_type = self.type(arg.type, self.model.package)

            if "type" in arg_options:
                # A container override preserves its model element parameters.
                arg_type = named_cpp_type(
                    arg_options["type"],
                    arg_type.Params,
                )

            by_const_ref = arg_options.get(
                "const_ref",
                self.argument_const_ref(arg.type, self.model.package),
            )
            if by_const_ref:
                arg_type = const_ref(arg_type)

            args.append(
                GenTuIdent(
                    Type=arg_type,
                    Name=arg_options.get("name", arg.name),
                    Value=(
                        self.default_value(
                            arg.type,
                            self.model.package,
                            arg.default,
                        )
                        if arg.default is not None
                        else None
                    ),
                ),
            )

        result_type = self.type(item.return_type, self.model.package)
        if options.get("return_const_ref", False):
            result_type = const_ref(result_type)

        is_constructor = item.is_constructor
        return GenTuFunction(
            Name=(owner.qname.name if is_constructor else options.get("name", item.name)),
            ReturnType=result_type,
            Doc=GenTuDoc(item.doc),
            Args=args,
            Body=options.get("body"),
            IsConst=options.get(
                "is_const",
                not item.is_static and not is_constructor,
            ),
            IsStatic=item.is_static,
            IsConstructor=is_constructor,
            IsVirtual=options.get("is_virtual", False),
            IsPureVirtual=options.get("is_pure_virtual", False),
            IsOverride=options.get("is_override", False),
            IsExposedForWrap=options.get("exposed", True),
            ParentClass=self.declaration_type(
                self.model.package,
                owner.qname,
            ),
        )

    def enum(self, item: EnumDef) -> GenTuEnum:
        names = cpp_config(item).get("value_names", {})
        return GenTuEnum(
            Name=self.declaration_type(self.model.package, item.qname),
            Doc=GenTuDoc(item.doc),
            Fields=[
                GenTuEnumField(
                    Name=names.get(value.name, enum_member_name(value.name)),
                    Doc=GenTuDoc(value.doc),
                    Value=value.value,
                )
                for value in item.enum_values
            ],
        )

    def variant(self, owner: RecordDef, item: VariantDef) -> GenTuTypeGroup:
        options = self.variant_config(
            self.model.package,
            owner.qname,
            item.field,
        )
        index = self.indexes[self.model.package]

        return GenTuTypeGroup(
            types=[self.record(index.record(case.case)) for case in item.cases],
            enumName=self.declaration_type(
                self.model.package,
                item.kind_enum,
            ),
            variantName=self.variant_type(
                self.model.package,
                owner.qname,
                item.field,
            ),
            variantField=item.field,
            variantValue=options.get("default"),
            kindGetter=options.get("kind_getter", "getKind"),
        )

    def add_ast_members(self, item: RecordDef, result: GenTuStruct) -> None:
        options = cpp_config(item)
        kind_type = named_cpp_type(AST_KIND_NAME)

        result.Name.Meta["isOrgType"] = True
        setattr(result, "isOrgType", True)
        result.ReflectionParams.backend.python.holder_type = "shared"
        result.ReflectionParams.backend.wasm.holder_type = named_cpp_type(
            "org::sem::SemId",
        )
        result.ReflectionParams.type_api = GenTuTypeApiTraits(
            is_org_ast_value=True,
        )

        result.Nested.insert(
            0,
            GenTuPass(f"virtual ~{item.qname.name}() = default;"),
        )

        if options.get("ast_root", False):
            result.Nested.append(
                GenTuPass(
                    "Org(hstd::Vec<org::sem::SemId<Org>> const& subnodes)"
                    " : subnodes(subnodes) {}",
                ),
            )
            result.Methods.insert(
                0,
                GenTuFunction(
                    Name="getKind",
                    ReturnType=kind_type,
                    IsConst=True,
                    IsVirtual=True,
                    IsPureVirtual=True,
                    IsExposedForWrap=False,
                    ParentClass=result.Name,
                ),
            )
            return

        for base in result.Bases:
            result.Nested.insert(
                0,
                GenTuPass(
                    f"using {cpp_type_text(base)}::{base.Name};",
                ),
            )

        if result.IsAbstract:
            return

        kind_name = f"{AST_KIND_NAME}::{item.qname.name}"
        result.Fields.insert(
            0,
            GenTuField(
                Type=kind_type,
                Name="staticKind",
                Doc=GenTuDoc(""),
                IsStatic=True,
                IsConst=True,
                IsExposedForWrap=False,
            ),
        )
        result.Methods.insert(
            0,
            GenTuFunction(
                Name="getKind",
                ReturnType=kind_type,
                IsConst=True,
                IsVirtual=True,
                IsOverride=True,
                Body=f"return {kind_name};",
                IsExposedForWrap=False,
                ParentClass=result.Name,
            ),
        )

    def record(self, item: RecordDef) -> GenTuStruct:
        package = self.model.package
        index = self.indexes[package]
        options = cpp_config(item)
        is_ast = self.is_ast(package, item.qname)

        variant_cases = {case.case for variant in item.variants for case in variant.cases}
        variant_enums = {variant.kind_enum for variant in item.variants}
        variant_fields = {variant.field for variant in item.variants}

        # Use QName.scope rather than relying on RecordDef.nested containing
        # synthetic variant enums in a particular finalizer implementation.
        nested: list[GenTuEntry] = []
        for record in self.model.records:
            if record.qname.scope == item.qname and record.qname not in variant_cases:
                nested.append(self.record(record))

        for enum in self.model.enums:
            if enum.qname.scope == item.qname and enum.qname not in variant_enums:
                nested.append(self.enum(enum))

        for variant in item.variants:
            nested.append(self.variant(item, variant))

        # Section code follows generated variants, so constructors can refer
        # to generated aliases such as NamedProperty::Data.
        for section in options.get("section_code", []):
            kind = section.get("kind", "public")
            if kind != "public":
                raise NotImplementedError(
                    "GenTuPass section lowering currently supports public code only",
                )
            nested.append(GenTuPass(section["text"]))

        DeclClass = self.declaration_type(package, item.qname)

        fields: List[GenTuField]
        check_functions: List[CheckFunction]
        fields, check_functions = glom.glom(
            cast(
                List[Tuple[GenTuField, List[Optional[CheckFunction]]]],
                [
                    self.field(item, member, parentClass=DeclClass)
                    for member in item.fields
                    if member.name not in variant_fields
                ],
            ),
            glom.Fold(
                glom.T,
                init=lambda: ([], []),
                op=lambda acc, item: (
                    acc[0].append(item[0]),
                    acc[1].append(item[1]) if item[1] else None,
                    acc,
                )[-1],
            ),
        )

        fields.append(
            GenTuField(
                Name="unidata_id",
                Type=QualType.ForName("std::string"),
                Value=self.ast.StringLiteral(item.qname.to_id()),
                IsStatic=True,
                IsConst=True,
                IsConstexpr=True,
            )
        )

        if item.checks:
            check_functions.append(
                CheckFunction(
                    class_type_name=item.qname.to_id(),
                    class_field=None,
                    impl=[
                        self.gen_record_check(
                            owner=item,
                            check=check,
                            parentClass=DeclClass,
                        )
                        for check in item.checks
                    ],
                )
            )

        impl_functions: List[GenTuFunction] = list()

        if 0 < len(check_functions):
            assign_stack = list()

            for check in check_functions:
                for impl in check.impl:
                    impl_functions.append(impl)

                assign_stack.append(
                    self.ast.init_list(
                        [
                            self.ast.XConstructObj(
                                CPP_KEY_T,
                                [
                                    self.ast.StringLiteral(check.class_type_name),
                                    self.ast.StringLiteral(check.class_field)
                                    if check.class_field
                                    else self.ast.string("std::nullopt"),
                                ],
                            ),
                            self.ast.XConstructObj(
                                CPP_CB_LIST_T,
                                Args=[
                                    self.ast.XConstructObj(
                                        CPP_CB_T,
                                        Args=[self.ast.Addr(self.ast.string(impl.Name))],
                                    )
                                    for impl in check.impl
                                ],
                            ),
                        ]
                    )
                )

            impl_functions.append(
                GenTuFunction(
                    Name="get_unidata_checks",
                    ParentClass=DeclClass,
                    IsStatic=True,
                    ReturnType=CPP_VERIFY_COLLECTION_T.asConstPtr(),
                    Body=self.ast.stack(
                        [
                            self.ast.VarDecl(
                                cpp.ParmVarParams(
                                    type=CPP_VERIFY_COLLECTION_T,
                                    name="checks",
                                    storage=cpp.StorageClass.Static,
                                    defArg=self.ast.init_list(
                                        [self.ast.init_list(assign_stack)]
                                    ),
                                    IsLine=False,
                                )
                            ),
                            self.ast.Return(self.ast.Addr(self.ast.string("checks"))),
                        ]
                    ),
                )
            )

        result = GenTuStruct(
            Name=DeclClass,
            Doc=GenTuDoc(item.doc),
            Fields=fields,
            Methods=[self.method(item, method) for method in item.methods]
            + impl_functions,
            Bases=[self.declaration_type(package, base) for base in item.bases],
            Nested=nested,
            IsAbstract=options.get("abstract", False),
            IsDescribedRecord=True,
        )

        default_constructor = options.get("default_constructor", False)

        # If the class is nested and uses `{}` for the default values it
        # might trigger a trait evaluation ordering issue, where the
        # compiler evaluates the class as non-default-constructible and
        # the does not re-run the eval afterwards.
        #
        # Example:
        #
        # ```c++
        # class Parent {
        #     class Nested {
        #         hstd::Str value = {}; // default constructor is declared
        #     };
        #
        #     class Nested2 {
        #         hstd::Str value = {};
        #     };
        #
        #     // instantiating the variant will trigger the `is_default_constructible`
        #     // check for the types, but it will evaluate to false at this stage
        #     using Data = std::variant<Nested, Nested2>;
        # }
        # ```
        #
        # There is no user-declared constructor, so the compiler
        # implicitly declares one. Determining its properties can
        # require examining the default member initializer.
        #
        # Default member initializers have special deferred-processing
        # rules: they can refer to members declared later in the
        # enclosing class. In this nested-class situation, the trait
        # check occurs before the compiler has finished the enclosing
        # definition and because of that the code fails.
        #
        # To have default-constructible class:
        #
        # - do not use any default initializer values for any fields,
        # in this case the class is a properly default-initialized
        # and can be used as an aggregate
        # - annotate with `default_field_pass_constructor` or
        # `default_constructor` to explicitly declare default no-arg
        # constructor.

        if options.get("default_field_pass_constructor", False):
            # Create two constructors, one with zero arguments and
            # everything defaulted, and another with 1+ arguments,
            # presence of the explicitly zero-argument constructor
            # allows for the nested types to evaluate the type check
            # `is_default_constructible` trait even if the parent
            # class has not been finished yet.
            fields = [self.field(item, f, parentClass=DeclClass)[0] for f in item.fields]
            result.Methods.append(
                GenTuFunction(
                    Name=item.qname.name,
                    IsConstructor=True,
                    ParentClass=result.Name,
                    ReflectionParams=GenTuReflParams(
                        unique_name=f"init_{item.qname.name}_field_pass",
                        backend=GenTuBackendParams(target_backends=["python"]),
                    ),
                    Args=[
                        GenTuIdent(
                            Type=const_ref(f.Type),
                            Name=f.Name,
                            Value=self.default_value(
                                f_orig.type,
                                package,
                                f_orig.default,
                                infer_default=True,
                            )
                            if 0 < idx
                            else None,
                        )
                        for idx, (f, f_orig) in enumerate(zip(fields, item.fields))
                    ],
                    InitList=[
                        self.ast.XConstructObj(
                            self.ast.string(f.Name), [self.ast.string(f.Name)]
                        )
                        for f in fields
                    ],
                )
            )

            result.Methods.append(
                GenTuFunction(
                    Name=item.qname.name,
                    IsConstructor=True,
                    Body="",
                    ParentClass=result.Name,
                    ReflectionParams=GenTuReflParams(
                        unique_name=f"init_{item.qname.name}_default"
                    ),
                ),
            )

        elif default_constructor:
            result.Methods.append(
                GenTuFunction(
                    Name=item.qname.name,
                    IsConstructor=True,
                    Body="",
                    ParentClass=result.Name,
                ),
            )

        default_equality = options.get("default_eq", False)
        if default_equality and not any(
            method.Name == "operator==" for method in result.Methods
        ):
            result.Methods.append(
                GenTuFunction(
                    Name="operator==",
                    ReturnType=named_cpp_type("bool"),
                    Args=[
                        GenTuIdent(
                            Type=const_ref(result.Name),
                            Name="other",
                        ),
                    ],
                    IsConst=True,
                    ParentClass=result.Name,
                ),
            )

        if is_ast:
            self.add_ast_members(item, result)

        return result

    def ast_kind_enum(self) -> GenTuEnum | None:
        concrete = [
            item
            for item in self.model.records
            if self.is_ast(self.model.package, item.qname)
            and not cpp_config(item).get("abstract", False)
        ]
        if not concrete:
            return None

        names = [item.qname.name for item in concrete]
        if len(names) != len(set(names)):
            raise ValueError(
                "OrgSemKind requires unique short names for concrete AST records",
            )

        org_sem_kind = named_cpp_type(AST_KIND_NAME)
        logger.info(f"Created org sem type {org_sem_kind}")
        return GenTuEnum(
            Name=org_sem_kind,
            Doc=GenTuDoc("Concrete semantic AST node kinds"),
            Fields=[
                GenTuEnumField(
                    Name=item.qname.name,
                    Doc=GenTuDoc(item.doc),
                    Value=index,
                )
                for index, item in enumerate(concrete)
            ],
        )

    def convert(self) -> list[GenTuEntry]:
        result: list[GenTuEntry] = []

        kind_enum = self.ast_kind_enum()
        if kind_enum is not None:
            result.append(kind_enum)

        result.extend(
            self.enum(item) for item in self.model.enums if item.qname.scope is None
        )
        result.extend(
            self.record(item) for item in self.model.records if item.qname.scope is None
        )
        return result


def model_to_gentu(
    model: ModelDef,
    *,
    dependencies: Sequence[ModelDef] = (),
    config: CppModelConfig | None = None,
) -> list[GenTuEntry]:
    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    return ModelToGenTu(
        model,
        dependencies=dependencies,
        config=config,
        ast=builder,
    ).convert()


def get_pyhaxorg_type_groups_via_dsl(ast: cpp.ASTBuilder) -> PyhaxorgTypeGroups:
    from .org_mode_model import get_model as get_ast_model
    from .org_shared_model import get_model as get_shared_model

    shared = get_shared_model()
    sem_model = get_ast_model()
    converters = [
        ModelToGenTu(shared, ast=ast),
        ModelToGenTu(sem_model, dependencies=[shared], ast=ast),
    ]
    shared_types: list[GenTuStruct] = []
    sem_types: list[GenTuStruct] = []
    enums: list[GenTuEnum] = []

    for converter in converters:
        declarations = [
            item
            for item in (*converter.model.enums, *converter.model.records)
            if item.qname.scope is None
        ]
        entries = converter.convert()
        if converter.ast_kind_enum() is not None:
            entries = entries[1:]

        for declaration, entry in zip(declarations, entries, strict=True):
            group = cpp_config(declaration).get("org_groups")
            match (group, entry):
                case (OrgTypeGroup.SHARED_TYPES, GenTuStruct()):
                    shared_types.append(entry)
                case (OrgTypeGroup.SEM_NODE_DEFINITIONS, GenTuStruct()):
                    sem_types.append(entry)
                case (OrgTypeGroup.FULL_ENUMS, GenTuEnum()):
                    enums.append(entry)
                case (OrgTypeGroup.AST_ROOT, GenTuStruct()):
                    pass
                case _:
                    raise ValueError(
                        f"Cannot assign {converter.model.package}.{declaration.qname.to_id()} "
                        f"to an Org type group: got {group!r} for {type(entry).__name__}; "
                        "expected a group compatible with the declaration kind"
                    )

    result = PyhaxorgTypeGroups()
    result.shared_types = expand_type_groups(ast, shared_types)
    populate_immutable_type_groups(ast, result, sem_types)

    osk_enum = codegen_ir.GenTuEnum(
        named_cpp_type(AST_KIND_NAME),
        codegen_ir.GenTuDoc(""),
        Fields=[
            codegen_ir.GenTuEnumField(struct.Name.Name, codegen_ir.GenTuDoc(""))
            for struct in get_concrete_types(result.sem_node_definitions)
        ],
    )

    result.full_enums = enums + [osk_enum]
    return result
