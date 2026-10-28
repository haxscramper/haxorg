import json
from dataclasses import dataclass, field
from typing import Any, Sequence

import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
from hstd_py_codegen.gen_cpp.codegen_ir import (
    GenTuDoc,
    GenTuEntry,
    GenTuEnum,
    GenTuEnumField,
    GenTuField,
    GenTuFunction,
    GenTuIdent,
    GenTuPass,
    GenTuStruct,
    GenTuTypeApiTraits,
    GenTuTypeGroup,
    QualType,
    QualTypeKind,
    ReferenceKind,
)
from hstd_py_codegen.gen_cpp.codegen_type_order import expand_type_groups
from hstd_py_text_layout.base.wrap import TextLayout
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    ArrayT,
    DynT,
    EnumDef,
    ExplicitDefault,
    ExternalT,
    FieldDef,
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
    VariantDef,
    VariantT,
)
from repo_py_orchestrate.codegen_config.codegen_type_groups import (
    OrgTypeGroup,
    PyhaxorgTypeGroups,
    get_osk_enum,
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


@dataclass
class CppModelConfig:
    namespaces: dict[str, tuple[str, ...]] = field(
        default_factory=lambda: dict(DEFAULT_NAMESPACES),
    )
    default_shared_equality: bool = True


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
        return self.config.namespaces[package]

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

                return named_cpp_type(primitive_types[typ.prim])

            case NamedT():
                return self.reference_type(package, typ.qname)

            case ExternalT():
                return self.reference_type(typ.package, typ.qname)

            case ListT():
                return named_cpp_type(
                    "hstd::Vec",
                    [self.type(typ.elem, package)],
                )

            case ArrayT():
                return named_cpp_type(
                    "std::array",
                    [
                        self.type(typ.elem, package),
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
                        self.type(typ.key, package),
                        self.type(typ.value, package),
                    ],
                )

            case OptT():
                return named_cpp_type(
                    "hstd::Opt",
                    [self.type(typ.elem, package)],
                )

            case TupleT():
                return named_cpp_type(
                    "std::tuple",
                    [self.type(elem, package) for elem in typ.elems],
                )

            case VariantT():
                return self.variant_type(package, typ.owner, typ.field)

            case TypeParamT():
                return QualType(
                    Name=typ.name,
                    IsTemplateTypeParam=True,
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
    ) -> str | None:
        if default is None:
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

    def field(self, owner: RecordDef, item: FieldDef) -> GenTuField:
        options = cpp_config(owner)
        field_options = options.get("fields", {}).get(item.name, {})
        names = options.get("field_names", {})
        defaults = options.get("field_defaults", {})

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

        return GenTuField(
            Type=field_type,
            Name=names.get(item.name, item.name),
            Doc=GenTuDoc(item.doc),
            Value=value,
        )

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

        result = GenTuStruct(
            Name=self.declaration_type(package, item.qname),
            Doc=GenTuDoc(item.doc),
            Fields=[
                self.field(item, member)
                for member in item.fields
                if member.name not in variant_fields
            ],
            Methods=[self.method(item, method) for method in item.methods],
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

        # Example:

        # ```c++
        # class Parent {
        #     class Nested {
        #         hstd::Str value = {}; // default constructor is declared
        #     };

        #     class Nested2 {
        #         hstd::Str value = {};
        #     };

        #     // instantiating the variant will trigger the `is_default_constructible`
        #     // check for the types, but it will evaluate to false at this stage
        #     using Data = std::variant<Nested, Nested2>;
        # }
        # ```

        # There is no user-declared constructor, so the compiler
        # implicitly declares one. Determining its properties can
        # require examining the default member initializer.

        # Default member initializers have special deferred-processing
        # rules: they can refer to members declared later in the
        # enclosing class. In this nested-class situation, the trait
        # check occurs before the compiler has finished the enclosing
        # definition and because of that the code fails.

        # To have default-constructible class:

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
            result.Methods.append(
                GenTuFunction(
                    Name=item.qname.name,
                    IsConstructor=True,
                    ParentClass=result.Name,
                    Args=[
                        GenTuIdent(
                            Type=const_ref(self.type(f.type, package)),
                            Name=f.name,
                            Value=self.default_value(f.type, package, f.default)
                            if 0 < idx
                            else None,
                        )
                        for idx, f in enumerate(item.fields)
                    ],
                    InitList=[
                        self.ast.XConstructObj(
                            self.ast.string(f.name), [self.ast.string(f.name)]
                        )
                        for f in item.fields
                    ],
                )
            )

            result.Methods.append(
                GenTuFunction(
                    Name=item.qname.name,
                    IsConstructor=True,
                    Body="",
                    ParentClass=result.Name,
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

        default_equality = options.get(
            "default_eq",
            self.config.default_shared_equality and not is_ast,
        )
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

        return GenTuEnum(
            Name=named_cpp_type(AST_KIND_NAME),
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
    result.full_enums = enums + [get_osk_enum(result.sem_node_definitions)]
    return result
