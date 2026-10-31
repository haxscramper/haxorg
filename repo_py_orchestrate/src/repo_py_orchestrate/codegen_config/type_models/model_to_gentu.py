from typing import Sequence

import glom
import hstd_py_codegen.lang_build.astbuilder_cpp as cpp
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
)
from hstd_py_codegen.gen_cpp.codegen_type_order import (
    expand_type_groups,
    rec_expand_group,
)
from hstd_py_text_layout.base.wrap import TextLayout
from hstd_py_unidata.model_index import ModelIndex
from hstd_py_unidata.model_ir import (
    EnumDef,
    ExternalT,
    FieldDef,
    MethodDef,
    ModelDef,
    NamedT,
    PrimKind,
    PrimT,
    RecordDef,
    TypeParamT,
    TypeRef,
    VariantDef,
)
from loguru import logger
from repo_py_orchestrate.codegen_config.codegen_type_groups import (
    OrgTypeGroup,
    PyhaxorgTypeGroups,
    get_concrete_types,
    populate_immutable_type_groups,
)
from repo_py_orchestrate.codegen_config.type_models.model_to_cpp_validate import CheckGen
from repo_py_orchestrate.codegen_config.type_models.model_to_gentu_common import (
    CPP_CB_LIST_T,
    CPP_CB_T,
    CPP_KEY_T,
    CPP_VERIFY_COLLECTION_T,
    CheckFunction,
    TypeTranslation,
    cpp_config,
    cpp_type_text,
    enum_member_name,
    named_cpp_type,
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


class ModelToGenTu:
    def __init__(
        self,
        model: ModelDef,
        *,
        ast: cpp.ASTBuilder,
        dependencies: Sequence[ModelDef] = (),
    ) -> None:
        self.model = model
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

        self.type_map = TypeTranslation(
            namespaces=DEFAULT_NAMESPACES,
            indexes=self.indexes,
            models=self.models,
            is_internal_codegen=False,
        )

        self.check_gen = CheckGen(
            ast=self.ast,
            model=self.model,
            indexes=self.indexes,
            type_map=TypeTranslation(
                namespaces=self.type_map.namespaces,
                indexes=self.type_map.indexes,
                models=self.type_map.models,
                is_internal_codegen=self.type_map.is_internal_codegen,
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
                    self.check_gen.gen_field_check(
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

        field_type = self.type_map.type(item.type, self.model.package)
        if "type" in field_options:
            field_type = named_cpp_type(field_options["type"])

        if item.name in defaults:
            value = defaults[item.name]
        else:
            value = self.type_map.default_value(
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
                return not self.type_map.is_enum(package, typ.qname)
            case ExternalT():
                return not self.type_map.is_enum(typ.package, typ.qname)
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
            arg_type = self.type_map.type(arg.type, self.model.package)

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
                arg_type = arg_type.asConstRef()

            args.append(
                GenTuIdent(
                    Type=arg_type,
                    Name=arg_options.get("name", arg.name),
                    Value=(
                        self.type_map.default_value(
                            arg.type,
                            self.model.package,
                            arg.default,
                        )
                        if arg.default is not None
                        else None
                    ),
                ),
            )

        result_type = self.type_map.type(item.return_type, self.model.package)
        if options.get("return_const_ref", False):
            result_type = result_type.asConstRef()

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
            ParentClass=self.type_map.declaration_type(
                self.model.package,
                owner.qname,
            ),
        )

    def enum(self, item: EnumDef) -> GenTuEnum:
        names = cpp_config(item).get("value_names", {})
        return GenTuEnum(
            Name=self.type_map.declaration_type(self.model.package, item.qname),
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
        options = self.type_map.variant_config(
            self.model.package,
            owner.qname,
            item.field,
        )
        index = self.indexes[self.model.package]

        return GenTuTypeGroup(
            types=[self.record(index.record(case.case)) for case in item.cases],
            enumName=self.type_map.declaration_type(
                self.model.package,
                item.kind_enum,
            ),
            variantName=self.type_map.variant_type(
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
        is_ast = self.type_map.is_ast(package, item.qname)

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

        DeclClass = self.type_map.declaration_type(package, item.qname)
        fields: List[GenTuField] = list()
        impl_functions: List[GenTuFunction] = list()

        for variant in item.variants:
            type_group = self.variant(item, variant)
            for entry in rec_expand_group(self.ast, type_group, parent_class=DeclClass):
                match entry:
                    case GenTuField():
                        fields.append(entry)

                    case GenTuFunction():
                        impl_functions.append(entry)

                    case _:
                        nested.append(entry)

        # Section code follows generated variants, so constructors can refer
        # to generated aliases such as NamedProperty::Data.
        for section in options.get("section_code", []):
            kind = section.get("kind", "public")
            if kind != "public":
                raise NotImplementedError(
                    "GenTuPass section lowering currently supports public code only",
                )
            nested.append(GenTuPass(section["text"]))

        check_functions: List[CheckFunction]
        model_fields, check_functions = glom.glom(
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

        fields.extend(model_fields)

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
                        self.check_gen.gen_record_check(
                            owner=item,
                            check=check,
                            parentClass=DeclClass,
                        )
                        for check in item.checks
                    ],
                )
            )

        if 0 < len(check_functions):
            impl_functions.append(
                self.check_gen.gen_populate_expression_runtime(
                    parentClass=DeclClass,
                )
            )

            assign_stack = list()

            for check in check_functions:
                for impl in check.impl:
                    impl_functions.append(impl)

                assign_stack.append(
                    self.ast.init_list(
                        [
                            self.ast.XConstructObj(
                                CPP_KEY_T(),
                                [
                                    self.ast.StringLiteral(check.class_type_name),
                                    self.ast.StringLiteral(check.class_field)
                                    if check.class_field
                                    else self.ast.string("std::nullopt"),
                                ],
                            ),
                            self.ast.XConstructObj(
                                CPP_CB_LIST_T(),
                                Args=[
                                    self.ast.XConstructObj(
                                        CPP_CB_T(),
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
                    ReturnType=CPP_VERIFY_COLLECTION_T().asConstPtr(),
                    Body=self.ast.stack(
                        [
                            self.ast.VarDecl(
                                cpp.ParmVarParams(
                                    type=CPP_VERIFY_COLLECTION_T(),
                                    name="checks",
                                    storage=cpp.StorageClass.Static,
                                    defArg=self.ast.init_list(
                                        [self.ast.init_list(assign_stack, isLine=False)]
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
            Bases=[self.type_map.declaration_type(package, base) for base in item.bases],
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
                            Type=f.Type.asConstRef(),
                            Name=f.Name,
                            Value=self.type_map.default_value(
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
                            Type=result.Name.asConstRef(),
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
            if self.type_map.is_ast(self.model.package, item.qname)
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
    model: ModelDef, *, dependencies: Sequence[ModelDef] = ()
) -> list[GenTuEntry]:
    t = TextLayout()
    builder = cpp.ASTBuilder(t)
    return ModelToGenTu(
        model,
        dependencies=dependencies,
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
