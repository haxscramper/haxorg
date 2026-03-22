import copy
from dataclasses import replace

from beartype import beartype
from beartype.typing import Any, List, Sequence, Tuple

from py_codegen import codegen_ir
import py_codegen.astbuilder_cpp as cpp
from py_codegen.codegen_ir import GenTuFunction, QualType, n_org
from py_haxorg.astbuilder import astbuilder_utils
from py_scriptutils.algorithm import iterate_object_tree
from py_scriptutils.script_logging import log

CAT = __name__


@beartype
def rewrite_type_to_immutable(obj: QualType) -> QualType:
    """
    Recursively rewrite input type to the immutable AST counterpart.
    """

    def get_update(o: QualType, **kwargs) -> QualType:
        "Get updated version of the type"
        return o.model_copy(
            update={
                "Params": [rewrite_type_to_immutable(P) for P in o.Params],
                "DbgOrigin": o.DbgOrigin + "imm_write",
                **kwargs,
            })

    def map_spaces(o: QualType) -> List[QualType]:
        "Recursively map used type spaces"
        return [rewrite_type_to_immutable(S) for S in o.Spaces]

    match obj:
        case QualType(Name="SemId", Params=[]):
            return get_update(obj, Name="ImmId", Spaces=[codegen_ir.n_imm()])

        case QualType(Name="SemId"):
            return get_update(obj, Name="ImmIdT", Spaces=[codegen_ir.n_imm()])

        case QualType(Name="Vec"):
            return get_update(obj, Name="ImmVec", Spaces=[codegen_ir.n_hstd_ext()])

        case QualType(Name="UnorderedMap"):
            return get_update(obj, Name="ImmMap", Spaces=[codegen_ir.n_hstd_ext()])

        case _:
            flat_namespace = obj.flatQualFullName()
            match flat_namespace:
                case [QualType(Name="org"), QualType(Name="sem"), *rest]:
                    if rest and rest[0].isOrgType():
                        if 1 == len(rest):
                            return get_update(obj,
                                              Name=f"Imm{obj.Name}",
                                              Spaces=[codegen_ir.n_imm()])

                        elif 1 < len(rest):
                            reuse_spaces = copy.copy(rest)
                            reuse_spaces.pop(0)
                            reuse_spaces.pop(-1)
                            return get_update(
                                obj,
                                Spaces=[
                                    codegen_ir.n_imm(),
                                    rest[0].copy_update(Name="Imm" + rest[0].Name),
                                    *reuse_spaces,
                                ],
                            )

                        else:
                            return get_update(obj, Spaces=map_spaces(obj))

                case _:
                    return get_update(obj, Spaces=map_spaces(obj))

    return obj


@beartype
def rewrite_ident_to_immutable(obj: codegen_ir.GenTuIdent) -> codegen_ir.GenTuIdent:
    "Rewrite typed identifier to immutable AST version"
    return replace(obj, Type=rewrite_type_to_immutable(obj.Type))


@beartype
def rewrite_field_to_immutable(obj: codegen_ir.GenTuField) -> codegen_ir.GenTuField:
    "Convert sem org AST field to immutable version"
    IMM_BOX = codegen_ir.t("ImmBox", [codegen_ir.n_hstd_ext()], DbgOrigin="rewrite_field")
    if obj.Type is None:
        return obj

    match obj:
        case codegen_ir.GenTuField(Type=QualType(Name="SemId", Params=[])):
            new_type = rewrite_type_to_immutable(obj.Type)
            return replace(
                obj,
                Type=new_type,
                Value="org::imm::ImmId::Nil()",
            )

        case codegen_ir.GenTuField(Type=QualType(Name="SemId")):
            par0 = obj.Type.par0()
            assert par0
            new_type = rewrite_type_to_immutable(obj.Type)
            return replace(
                obj,
                Type=new_type,
                Value=f"org::imm::ImmIdT<org::imm::Imm{par0.Name}>::Nil()",
            )

        case codegen_ir.GenTuField(Type=QualType(Name="Opt")):
            par0 = obj.Type.par0()
            assert par0
            new_type = rewrite_type_to_immutable(par0)
            new_type = new_type.withWrapperType(
                QualType(Name="Opt",
                         Spaces=[codegen_ir.n_hstd()])).withWrapperType(IMM_BOX)

            return replace(obj, Type=new_type)

        case codegen_ir.GenTuField(Type=QualType(Name="Str")):
            new_type = obj.Type.withWrapperType(IMM_BOX)
            return replace(obj, Type=new_type)

        case _:
            return replace(
                obj,
                Type=rewrite_type_to_immutable(obj.Type),
            )


@beartype
def rewrite_function_to_immutable(
        func: codegen_ir.GenTuFunction) -> codegen_ir.GenTuFunction:
    "Rewrite all arguments, return types and parameters for a function to immutable AST"
    return replace(
        func,
        ReturnType=rewrite_any_to_immutable(func.ReturnType),
        Args=rewrite_any_to_immutable(func.Args),
        Params=rewrite_any_to_immutable(func.Params),
        ParentClass=rewrite_type_to_immutable(func.ParentClass)
        if func.ParentClass else None,
    )


@beartype
def rewrite_struct_to_immutable(obj: codegen_ir.GenTuStruct) -> codegen_ir.GenTuStruct:
    """
    Rewrite all nested structure content and the structure name
    for use in the immutable AST
    """
    new_fields = [rewrite_field_to_immutable(f) for f in obj.Fields]

    new_methods = [
        rewrite_any_to_immutable(it)
        for it in obj.Methods
        if (it.Name in ["getKind"] or it.Name == obj.Name.Name)
    ]

    new_nested = [it for it in obj.Nested if not isinstance(it, codegen_ir.GenTuPass)]
    new_nested = [rewrite_any_to_immutable(it) for it in new_nested]

    self_arg = obj.Name.asConstRef()

    new_methods.append(
        codegen_ir.GenTuFunction(
            ReturnType=QualType.ForName("bool"),
            Name="operator==",
            IsConst=True,
            Args=[
                codegen_ir.GenTuIdent(Type=rewrite_type_to_immutable(self_arg),
                                      Name="other")
            ],
        ))

    new_reflection_params = copy.deepcopy(obj.ReflectionParams)
    if new_reflection_params.backend.wasm.holder_type:
        new_reflection_params.backend.wasm.holder_type = None

    prefix_nested = []
    if hasattr(obj, "isOrgType"):
        prefix_nested = [
            codegen_ir.GenTuPass(
                f"using Imm{obj.Bases[0].Name}::Imm{obj.Bases[0].Name};"),
            codegen_ir.GenTuPass(f"virtual ~Imm{obj.Name.Name}() = default;"),
        ]

    return replace(
        obj,
        Name=rewrite_type_to_immutable(obj.Name),
        Fields=new_fields,
        Methods=new_methods,
        Nested=prefix_nested + new_nested,
        GenDescribeMethods=False,
        Bases=[rewrite_type_to_immutable(b) for b in obj.Bases],
        ReflectionParams=new_reflection_params,
    )


@beartype
def rewrite_any_to_immutable(
    it: codegen_ir.GenTuUnion | codegen_ir.GenTuTypeGroup | QualType | list | None |
    codegen_ir.GenTuTypeGroup
) -> Any:
    """
    Recursively rewrite any input item to the immutable AST version
    and return a new instance.
    """
    match it:
        case None:
            return it

        case codegen_ir.GenTuStruct():
            return rewrite_struct_to_immutable(it)

        case codegen_ir.GenTuField():
            return rewrite_field_to_immutable(it)

        case codegen_ir.GenTuPass():
            return it

        case codegen_ir.GenTuEnum():
            return codegen_ir.GenTuTypedef(
                Base=it.Name,
                Name=rewrite_type_to_immutable(it.Name),
            )

        case codegen_ir.GenTuFunction():
            return rewrite_function_to_immutable(it)

        case QualType():
            return rewrite_type_to_immutable(it)

        case list():
            return [rewrite_any_to_immutable(i) for i in it]

        case codegen_ir.GenTuTypeGroup():
            return replace(
                it,
                types=rewrite_any_to_immutable(it.types),
                enumName=rewrite_any_to_immutable(it.enumName),
                variantName=rewrite_any_to_immutable(it.variantName),
            )

        case _:
            raise TypeError(f"Unexpected input type for immutable rewrite: {type(it)}")


@beartype
def rewrite_to_immutable(
        recs: Sequence[codegen_ir.GenTuStruct]) -> List[codegen_ir.GenTuStruct]:
    "Rewrite collection of structures to immutable AST"
    return [rewrite_struct_to_immutable(rec) for rec in recs]


@beartype
def get_adapter_field_getter(ast: cpp.ASTBuilder, f: codegen_ir.GenTuField,
                             T: QualType) -> codegen_ir.GenTuFunction:
    "Generate getter function for immutable data access for adapter specialization"
    field_access = ast.Dot(ast.XCallPtr(
        ast.string("this"),
        "value",
    ), ast.string(f.Name))

    field_type = rewrite_field_to_immutable(f).Type
    assert field_type

    # log(CAT).info(
    #     f"{T.Name}::{f.Name} {field_type.flatQualNameWithParams()} {field_type}")

    def use_get_adapter_field(field_par0: QualType) -> QualType:
        is_specialization = field_par0.Name != "ImmOrg"

        nonlocal field_access
        field_access = ast.XCall("org::imm::get_adapter_field", [
            ast.string("this"),
            ast.Addr(ast.Scoped(T, ast.string(f.Name))),
        ])

        if is_specialization:
            # log(CAT).info(f"field_par0 = {field_par0}")
            return QualType(Name="ImmAdapterT",
                            Spaces=[codegen_ir.n_imm()],
                            Params=[field_par0])

        else:
            return QualType(Name="ImmAdapter", Spaces=[codegen_ir.n_imm()])

    imm_org = QualType(Name="ImmOrg", Spaces=[codegen_ir.n_imm()])

    match field_type.flatQualNameWithParams():
        case ["org", "imm", "ImmIdT", _]:
            result_type = use_get_adapter_field(imm_org)

        case ["org", "imm", "ImmId"]:
            result_type = use_get_adapter_field(field_type.par0())

        case ["hstd", "ext", "ImmBox", [["hstd", "Opt", [["org", "imm", "ImmIdT", _]]]]]:
            result_type = codegen_ir.t_opt(
                use_get_adapter_field(field_type.par0().par0().par0()))

        case ["hstd", "ext", "ImmBox", [["hstd", "Opt", [["org", "imm", "ImmId"]]]]]:
            result_type = codegen_ir.t_opt(use_get_adapter_field(imm_org))

        case ["hstd", "ext", "ImmBox", _]:
            # Unwrap first level of immer boxing for more convenient API
            result_type = field_type.par0().asConstRef()
            field_access = ast.XCallRef(field_access, "get")

        case _:
            result_type = field_type

    return codegen_ir.GenTuFunction(
        Name=f"get{astbuilder_utils.pascal_case(f.Name)}",
        IsConst=True,
        ReturnType=result_type,
        Body=ast.Return(field_access),
        IsExposedForWrap=f.IsExposedForWrap,
    )


@beartype
def generate_adapter_specializations(
        ast: cpp.ASTBuilder,
        types: List[codegen_ir.GenTuStruct]) -> List[codegen_ir.GenTuStruct]:
    """
    Create value reader types and explicit instantiations of the adapter template structures.
    """
    adapters: List[codegen_ir.GenTuStruct] = list()
    imm_space = [QualType.ForName("org"), QualType.ForName("imm")]

    def for_final_type(sem_base: codegen_ir.GenTuStruct):
        "Create immutable AST adapter specialization for sem struct"
        derived_base: str = sem_base.Name.Name
        Derived = QualType(Name=f"Imm{derived_base}", Spaces=imm_space)
        Api = QualType(Name=f"ImmAdapter{derived_base}API", Spaces=imm_space)
        Base = QualType(Name="ImmAdapterTBase", Spaces=imm_space, Params=[Derived])

        Specialization = codegen_ir.GenTuStruct(
            Name=QualType(Name="ImmAdapterT", Spaces=imm_space),
            IsTemplateRecord=True,
            IsExplicitInstantiation=True,
            ExplicitTemplateParams=[Derived],
            Bases=[Base, Api],
            TemplateParams=codegen_ir.GenTuTemplateParams.FinalSpecialization(),
            ReflectionParams=codegen_ir.GenTuReflParams(
                wrapper_has_params=False,
                wrapper_name=f"{Derived.Name}Adapter",
                default_constructor=False,
            ),
            Nested=[
                codegen_ir.GenTuPass(
                    ast.XCall("USE_IMM_ADAPTER_BASE", [ast.Type(Derived)])),
                codegen_ir.GenTuPass(
                    ast.Using(cpp.UsingParams(newName="api_type", baseType=Api)))
            ],
            Methods=[
                get_adapter_field_getter(ast, f, Derived)
                for f in sem_base.Fields
                if not f.IsStatic
            ])

        Specialization.Methods.append(
            codegen_ir.GenTuFunction(
                Args=[
                    codegen_ir.GenTuIdent(
                        Type=QualType(Name="ImmAdapter", Spaces=imm_space).asConstRef(),
                        Name="other",
                    )
                ],
                Name="ImmAdapterT",
                IsConstructor=True,
                ParentClass=Specialization.declarationQualName(),
                InitList=[ast.XConstructObj(Base, Args=[ast.string("other")])],
                Body=ast.XCall("LOGIC_ASSERTION_CHECK_FMT", [
                    ast.Literal(
                        "Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}"
                    ),
                    ast.Literal(derived_base),
                    ast.XCallRef(ast.string("other"), "getKind"),
                ]),
            ))

        adapters.append(Specialization)

    for t in types:
        for_final_type(t)

    return adapters


@beartype
def get_imm_serde(
    types: List[codegen_ir.GenTuStruct],
    ast: cpp.ASTBuilder,
    type_map: codegen_ir.GenTypeMap,
) -> Sequence[codegen_ir.GenTuPass | codegen_ir.GenTuStruct]:
    "Create immutable AST serde types for msgpack"
    serde: List[codegen_ir.GenTuStruct | codegen_ir.GenTuPass] = []

    def aux(it: Any) -> None:
        match it:
            case codegen_ir.GenTuStruct():
                if it.IsAbstract:
                    return

                sem_type = it.Name
                respace = it.Name.flatQualScope()[2:] + [
                    it.Name.withoutAllScopeQualifiers()
                ]
                respace[0].Name = "Imm" + respace[0].Name
                respace = [codegen_ir.n_imm()] + respace
                imm_type = respace[-1].copy_update(Spaces=respace[:-1])

                writer_body: List[BlockId] = [
                    ast.line(
                        ast.Type(imm_type),
                        ast.string(" result = "),
                        ast.CallStatic(
                            typ=QualType(
                                Name="SerdeDefaultProvider",
                                Params=[imm_type],
                                Spaces=[codegen_ir.n_hstd()],
                            ),
                            opc="get",
                        ),
                        ast.string(";"),
                    )
                ]

                reader_body: List[BlockId] = [
                    ast.line(
                        ast.Type(sem_type),
                        ast.string(" result = "),
                        ast.CallStatic(
                            typ=QualType(
                                Name="SerdeDefaultProvider",
                                Params=[sem_type],
                                Spaces=[codegen_ir.n_hstd()],
                            ),
                            opc="get",
                        ),
                        ast.string(";"),
                    )
                ]

                def field_aux(sub: codegen_ir.GenTuStruct) -> None:
                    for field in sub.Fields:
                        if not field.IsStatic:
                            writer_body.append(
                                ast.Call(
                                    func=ast.string("assign_immer_field"),
                                    Args=[
                                        ast.string(f"result.{field.Name}"),
                                        ast.string(f"value.{field.Name}"),
                                        ast.string("ctx"),
                                    ],
                                    Stmt=True,
                                ))

                            reader_body.append(
                                ast.Call(
                                    func=ast.string("assign_sem_field"),
                                    Args=[
                                        ast.string(f"result.{field.Name}"),
                                        ast.string(f"value.{field.Name}"),
                                        ast.string("ctx"),
                                    ],
                                    Stmt=True,
                                ))

                    for base in sub.Bases:
                        assert sub.Name.Name != base.Name, f"{sub.Name} ->>>> {base}"
                        base_type = type_map.get_one_type_for_name(base.Name)
                        if base_type:
                            assert isinstance(base_type, codegen_ir.GenTuStruct)
                            assert base_type.Name.Name != sub.Name.Name
                            field_aux(base_type)

                # sys.setrecursionlimit(32)
                field_aux(it)

                writer_body.append(ast.Return(ast.string("result")))
                reader_body.append(ast.Return(ast.string("result")))

                writer = cpp.MethodDeclParams(
                    Params=cpp.FunctionParams(
                        Name="to_immer",
                        ResultTy=imm_type,
                        Args=[
                            cpp.ParmVarParams(name="value", type=sem_type.asConstRef()),
                            cpp.ParmVarParams(
                                name="ctx",
                                type=QualType(Name="ImmAstEditContext").asRef()),
                        ],
                        Body=writer_body,
                        AllowOneLine=False,
                    ),
                    IsStatic=True,
                )

                reader = cpp.MethodDeclParams(
                    Params=cpp.FunctionParams(
                        Name="from_immer",
                        ResultTy=sem_type,
                        Args=[
                            cpp.ParmVarParams(name="value", type=imm_type.asConstRef()),
                            cpp.ParmVarParams(
                                name="ctx",
                                type=QualType(Name="ImmAstContext").asConstRef()),
                        ],
                        Body=reader_body,
                        AllowOneLine=False,
                    ),
                    IsStatic=True,
                )

                rec = cpp.RecordParams(
                    name=QualType(Name="ImmSemSerde"),
                    NameParams=[sem_type, imm_type],
                    Template=cpp.GenTuTemplateParams(
                        Stacks=[codegen_ir.GenTuTemplateGroup(Params=[])]),
                    members=[writer, reader],
                )

                serde.append(codegen_ir.GenTuPass(ast.Record(rec)))

    iterate_object_tree(types, [], pre_visit=aux)

    return serde
