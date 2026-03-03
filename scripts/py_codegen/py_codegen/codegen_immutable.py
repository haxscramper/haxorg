import copy
from dataclasses import replace

from beartype import beartype
from beartype.typing import Any, List, Sequence, Tuple
from py_codegen import codegen_ir
import py_codegen.astbuilder_cpp as cpp
from py_codegen.codegen_ir import GenTuFunction, QualType
from py_haxorg.astbuilder import astbuilder_utils
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
            return get_update(obj, name="ImmId", Spaces=[codegen_ir.n_imm()])

        case QualType(name="SemId"):
            return get_update(obj, name="ImmIdT", Spaces=[codegen_ir.n_imm()])

        case QualType(name="Vec"):
            return get_update(obj, name="ImmVec", Spaces=[codegen_ir.n_hstd_ext()])

        case QualType(name="UnorderedMap"):
            return get_update(obj, name="ImmMap", Spaces=[codegen_ir.n_hstd_ext()])

        case _:
            flat_namespace = obj.flatQualFullName()
            match flat_namespace:
                case [QualType(name="org"), QualType(name="sem"), *rest]:
                    if rest and rest[0].isOrgType():
                        if 1 == len(rest):
                            return get_update(obj,
                                              name=f"Imm{obj.name}",
                                              Spaces=[codegen_ir.n_imm()])

                        elif 1 < len(rest):
                            reuse_spaces = copy.copy(rest)
                            reuse_spaces.pop(0)
                            reuse_spaces.pop(-1)
                            return get_update(
                                obj,
                                Spaces=[
                                    codegen_ir.n_imm(),
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
def rewrite_ident_to_immutable(obj: codegen_ir.GenTuIdent) -> codegen_ir.GenTuIdent:
    "Rewrite typed identifier to immutable AST version"
    return replace(obj, type=rewrite_type_to_immutable(obj.type))


@beartype
def rewrite_field_to_immutable(obj: codegen_ir.GenTuField) -> codegen_ir.GenTuField:
    "Convert sem org AST field to immutable version"
    IMM_BOX = codegen_ir.t("ImmBox", [codegen_ir.n_hstd_ext()])
    match obj:
        case codegen_ir.GenTuField(type=QualType(name="SemId", Parameters=[])):
            new_type = rewrite_type_to_immutable(obj.type)
            return replace(
                obj,
                type=new_type,
                value="org::imm::ImmId::Nil()",
            )

        case codegen_ir.GenTuField(type=QualType(name="SemId")):
            par0 = obj.type.par0()
            assert par0
            new_type = rewrite_type_to_immutable(obj.type)
            return replace(
                obj,
                type=new_type,
                value=f"org::imm::ImmIdT<org::imm::Imm{par0.name}>::Nil()",
            )

        case codegen_ir.GenTuField(type=QualType(name="Opt")):
            par0 = obj.type.par0()
            assert par0
            new_type = rewrite_type_to_immutable(par0)
            new_type = new_type.withWrapperType(
                QualType(name="Opt",
                         Spaces=[codegen_ir.n_hstd()])).withWrapperType(IMM_BOX)

            return replace(obj, type=new_type)

        case codegen_ir.GenTuField(type=QualType(name="Str")):
            new_type = obj.type.withWrapperType(IMM_BOX)
            return replace(obj, type=new_type)

        case _:
            return replace(
                obj,
                type=rewrite_type_to_immutable(obj.type),
            )


@beartype
def rewrite_function_to_immutable(
        func: codegen_ir.GenTuFunction) -> codegen_ir.GenTuFunction:
    "Rewrite all arguments, return types and parameters for a function to immutable AST"
    return replace(
        func,
        result=rewrite_any_to_immutable(func.result),
        arguments=rewrite_any_to_immutable(func.arguments),
        params=rewrite_any_to_immutable(func.params),
    )


@beartype
def rewrite_struct_to_immutable(obj: codegen_ir.GenTuStruct) -> codegen_ir.GenTuStruct:
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

    new_nested = [it for it in obj.nested if not isinstance(it, codegen_ir.GenTuPass)]
    new_nested = [rewrite_any_to_immutable(it) for it in new_nested]

    self_arg = obj.name.asConstRef()

    new_methods.append(
        codegen_ir.GenTuFunction(
            result=QualType.ForName("bool"),
            name="operator==",
            isConst=True,
            arguments=[
                codegen_ir.GenTuIdent(type=rewrite_type_to_immutable(self_arg),
                                      name="other")
            ],
        ))

    new_reflection_params = copy.deepcopy(obj.reflectionParams)
    if new_reflection_params.backend.wasm.holder_type:
        new_reflection_params.backend.wasm.holder_type = None

    prefix_nested = []
    if hasattr(obj, "isOrgType"):
        prefix_nested = [
            codegen_ir.GenTuPass(
                f"using Imm{obj.bases[0].name}::Imm{obj.bases[0].name};"),
            codegen_ir.GenTuPass(f"virtual ~Imm{obj.name.name}() = default;"),
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
    it: codegen_ir.GenTuUnion | codegen_ir.GenTuTypeGroup | QualType | list | None
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

        case codegen_ir.GenTuPass() | codegen_ir.GenTuEnum():
            return it

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
        recs: List[codegen_ir.GenTuStruct]) -> List[codegen_ir.GenTuStruct]:
    "Rewrite collection of structures to immutable AST"
    return [rewrite_struct_to_immutable(rec) for rec in recs]


@beartype
def generate_adapter_specializations(
    ast: cpp.ASTBuilder, types: List[codegen_ir.GenTuStruct]
) -> Tuple[List[codegen_ir.GenTuStruct], List[codegen_ir.GenTuStruct]]:
    """
    Create value reader types and explicit instantiations of the adapter template structures.
    """
    adapters: List[codegen_ir.GenTuStruct] = list()
    readers: List[codegen_ir.GenTuStruct] = list()
    imm_space = [QualType.ForName("org"), QualType.ForName("imm")]

    def for_final_type(sem_base: codegen_ir.GenTuStruct):
        "Create immutable AST adapter specialization for sem struct"
        derived_base: str = sem_base.name.name
        Derived = QualType(name=f"Imm{derived_base}", Spaces=imm_space)
        DerivedValueRead = QualType(name=f"Imm{derived_base}ValueRead", Spaces=imm_space)
        Api = QualType(name=f"ImmAdapter{derived_base}API", Spaces=imm_space)
        Base = QualType(name="ImmAdapterTBase", Spaces=imm_space, Parameters=[Derived])

        readers.append(
            codegen_ir.GenTuStruct(
                name=DerivedValueRead.withoutAllScopeQualifiers(),
                reflectionParams=codegen_ir.GenTuReflParams(default_constructor=True),
                methods=[
                    codegen_ir.GenTuFunction(
                        name=f"get{astbuilder_utils.pascal_case(f.name)}",
                        isConst=True,
                        result=rewrite_field_to_immutable(f).type.asConstRef(),
                    ) for f in sem_base.fields if not f.isStatic
                ] + [
                    codegen_ir.GenTuFunction(
                        IsConstructor=True,
                        name=DerivedValueRead.name,
                        arguments=[
                            codegen_ir.GenTuIdent(
                                name="ptr",
                                type=Derived.asConstPtr(),
                            )
                        ],
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
                    codegen_ir.GenTuField(name="ptr",
                                          type=Derived.asPtr(1),
                                          isExposedForDescribe=False)
                ]))

        adapters.append(
            codegen_ir.GenTuStruct(
                name=QualType(name="ImmAdapterT", Spaces=imm_space),
                IsTemplateRecord=True,
                IsExplicitInstantiation=True,
                ExplicitTemplateParams=[Derived],
                bases=[Base, Api],
                TemplateParams=codegen_ir.GenTuTemplateParams.FinalSpecialization(),
                reflectionParams=codegen_ir.GenTuReflParams(
                    wrapper_has_params=False,
                    wrapper_name=f"{Derived.name}Adapter",
                    default_constructor=False,
                ),
                nested=[
                    codegen_ir.GenTuPass(
                        ast.XCall("USE_IMM_ADAPTER_BASE", [ast.Type(Derived)])),
                    codegen_ir.GenTuPass(
                        ast.Using(cpp.UsingParams(newName="api_type", baseType=Api)))
                ],
                methods=[
                    codegen_ir.GenTuFunction(
                        arguments=[
                            codegen_ir.GenTuIdent(
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
                    codegen_ir.GenTuFunction(
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

                sem_type = it.name
                respace = it.name.flatQualScope()[2:] + [
                    it.name.withoutAllScopeQualifiers()
                ]
                respace[0].name = "Imm" + respace[0].name
                respace = [codegen_ir.n_imm()] + respace
                imm_type = respace[-1].model_copy(update=dict(Spaces=respace[:-1]))

                writer_body: List[BlockId] = [
                    ast.line(
                        ast.Type(imm_type),
                        ast.string(" result = "),
                        ast.CallStatic(
                            typ=QualType(
                                name="SerdeDefaultProvider",
                                Parameters=[imm_type],
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
                                name="SerdeDefaultProvider",
                                Parameters=[sem_type],
                                Spaces=[codegen_ir.n_hstd()],
                            ),
                            opc="get",
                        ),
                        ast.string(";"),
                    )
                ]

                def field_aux(sub: codegen_ir.GenTuStruct) -> None:
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
                        base_type = type_map.get_one_type_for_name(base.name)
                        if base_type:
                            assert isinstance(base_type, codegen_ir.GenTuStruct)
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
                        Stacks=[codegen_ir.GenTuTemplateGroup(Params=[])]),
                    members=[writer, reader],
                )

                serde.append(codegen_ir.GenTuPass(ast.Record(rec)))

    iterate_object_tree(types, [], pre_visit=aux)

    return serde
