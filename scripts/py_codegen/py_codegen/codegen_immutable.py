import copy
from dataclasses import replace

from beartype import beartype
from beartype.typing import Any, List, Sequence, Tuple
import py_codegen.astbuilder_cpp as cpp
from py_codegen.gen_tu_cpp import GenTuFunction, QualType
import py_codegen.gen_tu_cpp as tu
from py_scriptutils.algorithm import iterate_object_tree


@beartype
def rewrite_type_to_immutable(obj: QualType) -> QualType:
    """
    Recursively rewrite input type to the immutable AST counterpart.
    """

    def get_update(o: QualType, **kwargs) -> QualType:
        "Get updated version of the type"
        return o.model_copy(
            update={
                "Parameters": [rewrite_type_to_immutable(P) for P in o.Parameters],
                "dbg_origin": o.dbg_origin + "imm_write",
                **kwargs,
            })

    def map_spaces(o: QualType) -> List[QualType]:
        "Recursively map used type spaces"
        return [rewrite_type_to_immutable(S) for S in o.Spaces]

    match obj:
        case QualType(name="SemId", Parameters=[]):
            return get_update(obj, name="ImmId", Spaces=[tu.n_imm()])

        case QualType(name="SemId"):
            return get_update(obj, name="ImmIdT", Spaces=[tu.n_imm()])

        case QualType(name="Vec"):
            return get_update(obj, name="ImmVec", Spaces=[tu.n_hstd_ext()])

        case QualType(name="UnorderedMap"):
            return get_update(obj, name="ImmMap", Spaces=[tu.n_hstd_ext()])

        case _:
            flat_namespace = obj.flatQualFullName()
            match flat_namespace:
                case [QualType(name="org"), QualType(name="sem"), *rest]:
                    if rest and rest[0].isOrgType():
                        if 1 == len(rest):
                            return get_update(obj,
                                              name=f"Imm{obj.name}",
                                              Spaces=[tu.n_imm()])

                        elif 1 < len(rest):
                            reuse_spaces = copy.copy(rest)
                            reuse_spaces.pop(0)
                            reuse_spaces.pop(-1)
                            return get_update(
                                obj,
                                Spaces=[
                                    tu.n_imm(),
                                    rest[0].model_copy(update=dict(name="Imm" +
                                                                   rest[0].name)),
                                    *reuse_spaces,
                                ],
                            )

                        else:
                            return get_update(obj, Spaces=map_spaces(obj))

                case _:
                    return get_update(obj, Spaces=map_spaces(obj))

    return obj


@beartype
def rewrite_ident_to_immutable(obj: tu.GenTuIdent) -> tu.GenTuIdent:
    "Rewrite typed identifier to immutable AST version"
    return replace(obj, type=rewrite_type_to_immutable(obj.type))


@beartype
def rewrite_field_to_immutable(obj: tu.GenTuField) -> tu.GenTuField:
    "Convert sem org AST field to immutable version"
    IMM_BOX = tu.t("ImmBox", [tu.n_hstd_ext()])
    match obj:
        case tu.GenTuField(type=QualType(name="SemId", Parameters=[])):
            new_type = rewrite_type_to_immutable(obj.type)
            return replace(
                obj,
                type=new_type,
                value="org::imm::ImmId::Nil()",
            )

        case tu.GenTuField(type=QualType(name="SemId")):
            par0 = obj.type.par0()
            assert par0
            new_type = rewrite_type_to_immutable(obj.type)
            return replace(
                obj,
                type=new_type,
                value=f"org::imm::ImmIdT<org::imm::Imm{par0.name}>::Nil()",
            )

        case tu.GenTuField(type=QualType(name="Opt")):
            par0 = obj.type.par0()
            assert par0
            new_type = rewrite_type_to_immutable(par0)
            new_type = new_type.withWrapperType(QualType(
                name="Opt", Spaces=[tu.n_hstd()])).withWrapperType(IMM_BOX)

            return replace(obj, type=new_type)

        case tu.GenTuField(type=QualType(name="Str")):
            new_type = obj.type.withWrapperType(IMM_BOX)
            return replace(obj, type=new_type)

        case _:
            return replace(
                obj,
                type=rewrite_type_to_immutable(obj.type),
            )


@beartype
def rewrite_function_to_immutable(func: tu.GenTuFunction) -> tu.GenTuFunction:
    "Rewrite all arguments, return types and parameters for a function to immutable AST"
    return replace(
        func,
        result=rewrite_any_to_immutable(func.result),
        arguments=rewrite_any_to_immutable(func.arguments),
        params=rewrite_any_to_immutable(func.params),
    )


@beartype
def rewrite_struct_to_immutable(obj: tu.GenTuStruct) -> tu.GenTuStruct:
    """
    Rewrite all nested structure content and the structure name
    for use in the immutable AST
    """
    new_fields = [rewrite_field_to_immutable(f) for f in obj.fields]

    new_methods = [
        rewrite_any_to_immutable(it)
        for it in obj.methods
        if (it.name in ["getKind"] or it.name == obj.name.name)
    ]

    new_nested = [it for it in obj.nested if not isinstance(it, tu.GenTuPass)]
    new_nested = [rewrite_any_to_immutable(it) for it in new_nested]

    self_arg = obj.name.asConstRef()

    new_methods.append(
        tu.GenTuFunction(
            result=QualType.ForName("bool"),
            name="operator==",
            isConst=True,
            arguments=[
                tu.GenTuIdent(type=rewrite_type_to_immutable(self_arg), name="other")
            ],
        ))

    new_reflection_params = copy.deepcopy(obj.reflectionParams)
    if new_reflection_params.backend.wasm.holder_type:
        new_reflection_params.backend.wasm.holder_type = None

    prefix_nested = []
    if hasattr(obj, "isOrgType"):
        prefix_nested = [
            tu.GenTuPass(f"using Imm{obj.bases[0].name}::Imm{obj.bases[0].name};"),
            tu.GenTuPass(f"virtual ~Imm{obj.name.name}() = default;"),
        ]

    return replace(
        obj,
        name=rewrite_type_to_immutable(obj.name),
        fields=new_fields,
        methods=new_methods,
        nested=prefix_nested + new_nested,
        GenDescribeMethods=False,
        bases=[rewrite_type_to_immutable(b) for b in obj.bases],
        reflectionParams=new_reflection_params,
    )


@beartype
def rewrite_any_to_immutable(
        it: tu.GenTuUnion | tu.GenTuTypeGroup | QualType | list | None) -> Any:
    """
    Recursively rewrite any input item to the immutable AST version
    and return a new instance.
    """
    match it:
        case None:
            return it

        case tu.GenTuStruct():
            return rewrite_struct_to_immutable(it)

        case tu.GenTuField():
            return rewrite_field_to_immutable(it)

        case tu.GenTuPass() | tu.GenTuEnum():
            return it

        case tu.GenTuFunction():
            return rewrite_function_to_immutable(it)

        case QualType():
            return rewrite_type_to_immutable(it)

        case list():
            return [rewrite_any_to_immutable(i) for i in it]

        case tu.GenTuTypeGroup():
            return replace(
                it,
                types=rewrite_any_to_immutable(it.types),
                enumName=rewrite_any_to_immutable(it.enumName),
                variantName=rewrite_any_to_immutable(it.variantName),
            )

        case _:
            raise TypeError(f"Unexpected input type for immutable rewrite: {type(it)}")


@beartype
def rewrite_to_immutable(recs: List[tu.GenTuStruct]) -> List[tu.GenTuStruct]:
    "Rewrite collection of structures to immutable AST"
    return [rewrite_struct_to_immutable(rec) for rec in recs]


@beartype
def generate_adapter_specializations(
        ast: cpp.ASTBuilder,
        types: List[tu.GenTuStruct]) -> Tuple[List[tu.GenTuStruct], List[tu.GenTuStruct]]:
    """
    Create value reader types and explicit instantiations of the adapter template structures.
    """
    adapters: List[tu.GenTuStruct] = list()
    readers: List[tu.GenTuStruct] = list()
    imm_space = [QualType.ForName("org"), QualType.ForName("imm")]

    def for_final_type(sem_base: tu.GenTuStruct):
        "Create immutable AST adapter specialization for sem struct"
        derived_base: str = sem_base.name.name
        Derived = QualType(name=f"Imm{derived_base}", Spaces=imm_space)
        DerivedValueRead = QualType(name=f"Imm{derived_base}ValueRead", Spaces=imm_space)
        Api = QualType(name=f"ImmAdapter{derived_base}API", Spaces=imm_space)
        Base = QualType(name="ImmAdapterTBase", Spaces=imm_space, Parameters=[Derived])

        readers.append(
            tu.GenTuStruct(
                name=DerivedValueRead.withoutAllScopeQualifiers(),
                reflectionParams=tu.GenTuReflParams(default_constructor=True),
                methods=[
                    tu.GenTuFunction(
                        name=f"get{cpp.pascal_case(f.name)}",
                        isConst=True,
                        result=rewrite_field_to_immutable(f).type.asConstRef(),
                    ) for f in sem_base.fields if not f.isStatic
                ] + [
                    tu.GenTuFunction(
                        IsConstructor=True,
                        name=DerivedValueRead.name,
                        arguments=[tu.GenTuIdent(
                            name="ptr",
                            type=Derived.asConstPtr(),
                        )],
                        InitList=[
                            ast.XConstructObj(ast.string("ptr"), [
                                ast.XCall("const_cast", [ast.string("ptr")],
                                          Params=[
                                              Derived.asPtr(1),
                                          ])
                            ])
                        ])
                ],
                fields=[
                    tu.GenTuField(name="ptr",
                                  type=Derived.asPtr(1),
                                  isExposedForDescribe=False)
                ]))

        adapters.append(
            tu.GenTuStruct(
                name=QualType(name="ImmAdapterT", Spaces=imm_space),
                IsTemplateRecord=True,
                IsExplicitInstantiation=True,
                ExplicitTemplateParams=[Derived],
                bases=[Base, Api],
                TemplateParams=tu.GenTuTemplateParams.FinalSpecialization(),
                reflectionParams=tu.GenTuReflParams(
                    wrapper_has_params=False,
                    wrapper_name=f"{Derived.name}Adapter",
                    default_constructor=False,
                ),
                nested=[
                    tu.GenTuPass(ast.XCall("USE_IMM_ADAPTER_BASE", [ast.Type(Derived)])),
                    tu.GenTuPass(
                        ast.Using(cpp.UsingParams(newName="api_type", baseType=Api)))
                ],
                methods=[
                    tu.GenTuFunction(
                        arguments=[
                            tu.GenTuIdent(
                                type=QualType(name="ImmAdapter",
                                              Spaces=imm_space).asConstRef(),
                                name="other",
                            )
                        ],
                        name="ImmAdapterT",
                        IsConstructor=True,
                        InitList=[ast.XConstructObj(Base, Args=[ast.string("other")])],
                        impl=ast.XCall("LOGIC_ASSERTION_CHECK_FMT", [
                            ast.Literal(
                                "Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}"
                            ),
                            ast.Literal(derived_base),
                            ast.XCallRef(ast.string("other"), "getKind"),
                        ])),
                    tu.GenTuFunction(
                        isConst=True,
                        name="getValue",
                        result=DerivedValueRead,
                        impl=ast.Return(
                            ast.XConstructObj(
                                DerivedValueRead,
                                [ast.Addr(ast.XCallPtr(
                                    ast.string("this"),
                                    "value",
                                ))]))),
                ]))

    for t in types:
        for_final_type(t)

    return adapters, readers


@beartype
def get_imm_serde(
    types: List[tu.GenTuStruct],
    ast: cpp.ASTBuilder,
    base_map: tu.GenTypeMap,
) -> Sequence[tu.GenTuPass | tu.GenTuStruct]:
    "Create immutable AST serde types for msgpack"
    serde: List[tu.GenTuStruct | tu.GenTuPass] = []

    def aux(it: Any) -> None:
        match it:
            case tu.GenTuStruct():
                if it.IsAbstract:
                    return

                sem_type = it.name
                respace = it.name.flatQualScope()[2:] + [
                    it.name.withoutAllScopeQualifiers()
                ]
                respace[0].name = "Imm" + respace[0].name
                respace = [tu.n_imm()] + respace
                imm_type = respace[-1].model_copy(update=dict(Spaces=respace[:-1]))

                writer_body: List[BlockId] = [
                    ast.line(
                        ast.Type(imm_type),
                        ast.string(" result = "),
                        ast.CallStatic(
                            typ=QualType(
                                name="SerdeDefaultProvider",
                                Parameters=[imm_type],
                                Spaces=[tu.n_hstd()],
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
                                name="SerdeDefaultProvider",
                                Parameters=[sem_type],
                                Spaces=[tu.n_hstd()],
                            ),
                            opc="get",
                        ),
                        ast.string(";"),
                    )
                ]

                def field_aux(sub: tu.GenTuStruct) -> None:
                    for field in sub.fields:
                        if not field.isStatic:
                            writer_body.append(
                                ast.Call(
                                    func=ast.string("assign_immer_field"),
                                    Args=[
                                        ast.string(f"result.{field.name}"),
                                        ast.string(f"value.{field.name}"),
                                        ast.string("ctx"),
                                    ],
                                    Stmt=True,
                                ))

                            reader_body.append(
                                ast.Call(
                                    func=ast.string("assign_sem_field"),
                                    Args=[
                                        ast.string(f"result.{field.name}"),
                                        ast.string(f"value.{field.name}"),
                                        ast.string("ctx"),
                                    ],
                                    Stmt=True,
                                ))

                    for base in sub.bases:
                        assert sub.name.name != base.name, f"{sub.name} ->>>> {base}"
                        base_type = base_map.get_one_type_for_name(base.name)
                        if base_type:
                            assert isinstance(base_type, tu.GenTuStruct)
                            assert base_type.name.name != sub.name.name
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
                                type=QualType(name="ImmAstEditContext").asRef()),
                        ],
                        Body=writer_body,
                        AllowOneLine=False,
                    ),
                    isStatic=True,
                )

                reader = cpp.MethodDeclParams(
                    Params=cpp.FunctionParams(
                        Name="from_immer",
                        ResultTy=sem_type,
                        Args=[
                            cpp.ParmVarParams(name="value", type=imm_type.asConstRef()),
                            cpp.ParmVarParams(
                                name="ctx",
                                type=QualType(name="ImmAstContext").asConstRef()),
                        ],
                        Body=reader_body,
                        AllowOneLine=False,
                    ),
                    isStatic=True,
                )

                rec = cpp.RecordParams(
                    name=QualType(name="ImmSemSerde"),
                    NameParams=[sem_type, imm_type],
                    Template=cpp.GenTuTemplateParams(
                        Stacks=[tu.GenTuTemplateGroup(Params=[])]),
                    members=[writer, reader],
                )

                serde.append(tu.GenTuPass(ast.Record(rec)))

    iterate_object_tree(types, [], pre_visit=aux)

    return serde
