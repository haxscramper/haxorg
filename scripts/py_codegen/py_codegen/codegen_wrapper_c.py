from dataclasses import dataclass, field, replace

from beartype import beartype
from beartype.typing import cast, List, Optional
from py_codegen import codegen_ir
from py_codegen.astbuilder_base_config import BUILTIN_TYPES
from py_codegen.astbuilder_c_config import CAstbuilderConfig
import py_codegen.astbuilder_cpp as cpp
from py_codegen.codegen_algo import (
    collect_type_specializations,
    instantiate_template,
    match_specializations,
    match_specializations_for_struct,
    rewrite_any_typedefs,
    SpecializationMatchResult,
    TemplateUnificationMatcher,
    TypedefExpansionMatcher,
)
from py_codegen.codegen_ir import n_org, n_sem, QualType
from py_codegen.codegen_type_groups import PyhaxorgTypeGroups, topological_sort_entries
from py_codegen.org_codegen_data import get_types
from py_haxorg.layout.wrap import BlockId
from py_scriptutils.script_logging import log

CAT = __name__

_CONTEXT_ARG = codegen_ir.GenTuIdent(
    Type=QualType(Name="OrgContext", PtrCount=1),
    Name="org_context",
)

_SELF_IDENT_STR = "__self"

_LINK_ANNOTATION = codegen_ir.GenTuAnnotation(
    Attribute=codegen_ir.GenTuAnnotation.Freeform(Body="HAXORG_C_API_LINKAGE"))

_PAYLOAD_TYPE = QualType(Name="haxorg_ptr_payload")
_VOID_TYPE = QualType(Name="void", PtrCount=1, IsConst=True)


@beartype
def _get_func_base_name(func: codegen_ir.GenTuFunction) -> str:
    if func.ReflectionParams.unique_name:
        FuncBaseName = func.ReflectionParams.unique_name

    else:
        FuncBaseName = codegen_ir.sanitize_ident(func.Name, set())

    if func.IsConst:
        FuncBaseName += "_const"

    return FuncBaseName


@beartype
def _get_vtable_type(Type: QualType, conf: CAstbuilderConfig) -> QualType:
    Unwrap = conf.getResolvedType(Type)
    if isinstance(conf.getTypeDefinition(Unwrap), codegen_ir.GenTuEnum):
        return QualType(Name="haxorg_builtin_vtable")

    match Unwrap.flatQualNameWithParams():
        case ["std", "shared_ptr", _]:
            return _get_vtable_type(Unwrap.par0(), conf)

        case builtin if builtin in BUILTIN_TYPES:
            return QualType(Name="haxorg_builtin_vtable")

        case _:
            Name = conf.getBackendType(Unwrap)
            return QualType(Name=f"{Name.Name}_vtable")


@beartype
def _gen_direct_function_call(
    func: codegen_ir.GenTuFunction,
    ast: cpp.ASTBuilder,
    conf: CAstbuilderConfig,
    ThisIdent: Optional[codegen_ir.GenTuIdent],
) -> BlockId:
    if func.IsConstructor:
        Params = cpp.LambdaParams(IsPtrCast=True,)
        assert func.ParentClass

        Params.Args = [cpp.ParmVarParams(type=a.Type, name=a.Name) for a in func.Args]

        if func.ReflectionParams.backend.c.holder_type == "shared":
            Params.ResultTy = QualType(
                Name="make_shared",
                Spaces=[QualType(Name="std")],
                Params=[func.ParentClass],
            )

            Params.Body = [
                ast.Return(
                    ast.XCall(
                        "std::make_shared",
                        args=[ast.string(a.name) for a in Params.Args],
                    ))
            ]

        else:
            Params.ResultTy = func.ParentClass

            Params.Body = [
                ast.Return(
                    ast.Call(
                        ast.Type(func.ParentClass),
                        Args=[ast.string(a.name) for a in Params.Args],
                    ))
            ]

        FuncPtr = ast.Lambda(Params)
    else:
        FuncPtr = ast.XCall(
            "static_cast",
            args=[ast.Addr(ast.Type(func.get_full_qualified_name()))],
            Params=[func.get_function_type()],
        )

    pass_args = [FuncPtr, ast.string("org_context")]

    if ThisIdent:
        pass_args.append(ast.string(ThisIdent.Name))

    pass_args += [ast.string(a.Name) for a in func.Args]

    return ast.XCall(
        "org::bind::c::execute_cpp",
        args=pass_args,
        Params=[conf.getBackendType(func.ReturnType)],
    )


@beartype
def _gen_vtable_function_call(
    *,
    func: codegen_ir.GenTuFunction,
    ast: cpp.ASTBuilder,
    vtable_ptr: BlockId,
    c_vtable_type: QualType,
    args: list[codegen_ir.GenTuIdent],
) -> BlockId:
    return ast.Call(
        ast.pars(
            ast.Arrow(
                ast.XCall("static_cast",
                          Params=[c_vtable_type.asConstPtr()],
                          args=[vtable_ptr]),
                ast.string(_get_func_base_name(func)),
            )),
        Args=[ast.string(a.Name) for a in args],
    )


@beartype
def _gen_func(
    func: codegen_ir.GenTuFunction,
    ast: cpp.ASTBuilder,
    conf: CAstbuilderConfig,
    Class: Optional[QualType] = None,
) -> codegen_ir.GenTuFunction:

    FuncArgs = [_CONTEXT_ARG]

    ThisIdent: Optional[codegen_ir.GenTuIdent] = None

    if Class and not func.IsConstructor and not func.IsStatic:
        ThisIdent = codegen_ir.GenTuIdent(conf.getBackendType(Class), "__this")
        FuncArgs.append(ThisIdent)

    for arg in func.Args:
        FuncArgs.append(
            codegen_ir.GenTuIdent(
                Type=conf.getBackendType(arg.Type),
                Name=arg.Name,
            ))

    if func.IsConstructor:
        assert func.ParentClass
        FuncName = f"haxorg_create_{conf.getTypeBindName(func.ParentClass)}_{_get_func_base_name(func)}"

    elif Class:
        FuncName = f"haxorg_{conf.getTypeBindName(Class)}_{_get_func_base_name(func)}"

    else:
        FuncName = f"haxorg_{_get_func_base_name(func)}"

    impl_call = _gen_direct_function_call(func, ast, conf, ThisIdent)

    if func.ReturnType != "void":
        impl_call = ast.Return(impl_call)

    return codegen_ir.GenTuFunction(
        ReturnType=conf.getBackendType(func.ReturnType),
        Name=FuncName,
        Args=FuncArgs,
        Body=ast.stack([impl_call]),
        Annotations=[_LINK_ANNOTATION],
    )


@beartype
def _gen_func_vtable(
    *,
    func: codegen_ir.GenTuFunction,
    ast: cpp.ASTBuilder,
    conf: CAstbuilderConfig,
    Class: QualType,
    VTable: QualType,
) -> codegen_ir.GenTuFunction:

    FuncArgs = [_CONTEXT_ARG]

    ThisIdent: Optional[codegen_ir.GenTuIdent] = None

    if not func.IsConstructor and not func.IsStatic:
        ThisIdent = codegen_ir.GenTuIdent(conf.getBackendType(Class), "__this")
        FuncArgs.append(ThisIdent)

    for arg in func.Args:
        FuncArgs.append(
            codegen_ir.GenTuIdent(
                Type=conf.getBackendType(arg.Type),
                Name=arg.Name,
            ))

    if func.IsConstructor:
        assert func.ParentClass
        FuncName = f"haxorg_create_{conf.getTypeBindName(func.ParentClass)}_{_get_func_base_name(func)}"

    else:
        FuncName = f"haxorg_{conf.getTypeBindName(Class)}_{_get_func_base_name(func)}"

    assert Class
    assert ThisIdent
    impl_call = _gen_vtable_function_call(
        func=func,
        ast=ast,
        vtable_ptr=ast.Dot(ast.string(ThisIdent.Name), ast.string("data.vtable")),
        c_vtable_type=VTable,
        args=[_CONTEXT_ARG, ThisIdent] + func.Args,
    )

    if func.ReturnType != "void":
        impl_call = ast.Return(impl_call)

    return codegen_ir.GenTuFunction(
        ReturnType=_aux_public_api_type(func.ReturnType, conf),
        Name=FuncName,
        Args=FuncArgs,
        Body=ast.stack([impl_call]),
        Annotations=[_LINK_ANNOTATION],
    )


@beartype
def _gen_typedef(tdef: codegen_ir.GenTuTypedef, ast: cpp.ASTBuilder,
                 conf: CAstbuilderConfig) -> codegen_ir.GenTuTypedef:
    return codegen_ir.GenTuTypedef(
        Name=conf.getBackendType(tdef.Name),
        Base=conf.getBackendType(tdef.Base),
        Is_PlainC=True,
    )


@beartype
def _gen_enum(en: codegen_ir.GenTuEnum, ast: cpp.ASTBuilder,
              conf: CAstbuilderConfig) -> codegen_ir.GenTuEnum:
    return replace(
        en,
        Name=conf.getBackendType(en.Name),
        GenEnumDescription=False,
    )


def _should_substitude_for_payload(Type: QualType, conf: CAstbuilderConfig) -> bool:
    # Public API of the method is a template type parameter
    # to create a static methods for vtable with all signature
    # types matching, it is necessary to unpack the result
    # into the opaque handle.
    has_template_substitution = False

    def aux_type(Type: QualType):
        nonlocal has_template_substitution
        if Type.OriginalSubstitutedTemplate:
            has_template_substitution = True

    Type.visit_recursive(aux_type)
    return has_template_substitution


def _aux_public_api_type(Type: QualType, conf: CAstbuilderConfig) -> QualType:
    if _should_substitude_for_payload(Type, conf):
        return _PAYLOAD_TYPE

    else:
        return conf.getBackendType(Type)


@beartype
def _gen_vtable_method_specialization(
    *,
    _meth: codegen_ir.GenTuFunction,
    struct: codegen_ir.GenTuStruct,
    ast: cpp.ASTBuilder,
    conf: CAstbuilderConfig,
    c_type: QualType,
    cpp_vtable_type: QualType,
) -> codegen_ir.GenTuFunction:
    assert _meth.ParentClass, f"No parent class for method {_meth.Name} of class {struct.declarationQualName()}"

    ExecuteArgs = list()

    if _meth.ReflectionParams.backend.c.pointer_through_lambda:
        ExecuteArgs.append(
            ast.Lambda(
                cpp.LambdaParams(
                    Args=[
                        cpp.ParmVarParams(
                            type=struct.declarationQualName().asConstRef(),
                            name=_SELF_IDENT_STR,
                        ),
                    ] + [cpp.ParmVarParams(type=p.Type, name=p.Name) for p in _meth.Args],
                    IsPtrCast=True,
                    ResultTy=_meth.ReturnType,
                    Body=[
                        ast.Return(
                            ast.XCallRef(
                                ast.string(_SELF_IDENT_STR),
                                _meth.Name,
                                args=[ast.string(arg.Name) for arg in _meth.Args]))
                    ])))

    else:
        ExecuteArgs.append(
            ast.XCall(
                "static_cast",
                args=[ast.Addr(ast.Type(_meth.get_full_qualified_name()))],
                Params=[_meth.get_function_type()],
            ))

    ExecuteArgs.append(ast.string(_CONTEXT_ARG.Name))
    if not _meth.IsStatic:
        ExecuteArgs.append(ast.string(_SELF_IDENT_STR))

    for _arg in _meth.Args:
        ExecuteArgs.append(ast.string(_arg.Name))

    Impl = ast.XCall(
        "org::bind::c::execute_cpp",
        args=ExecuteArgs,
        Params=[_aux_public_api_type(_meth.ReturnType, conf)],
    )

    Impl = ast.Return(Impl)

    return codegen_ir.GenTuFunction(
        ReturnType=_aux_public_api_type(_meth.ReturnType, conf),
        Args=[
            _CONTEXT_ARG,
            codegen_ir.GenTuIdent(Type=c_type, Name=_SELF_IDENT_STR),
        ] + [
            codegen_ir.GenTuIdent(Type=_aux_public_api_type(A.Type, conf), Name=A.Name)
            for A in _meth.Args
        ],
        IsStatic=True,
        Name=_get_func_base_name(_meth),
        Body=Impl,
        ParentClass=cpp_vtable_type,
    )


@beartype
def _gen_vtable_specialization(
    struct: codegen_ir.GenTuStruct,
    ast: cpp.ASTBuilder,
    conf: CAstbuilderConfig,
    c_type: QualType,
    c_type_vtable: QualType,
) -> codegen_ir.GenTuStruct:

    Methods = list()

    cpp_vtable_type = QualType(
        Name="VTable",
        Spaces=[
            QualType.ForSpace("org"),
            QualType.ForSpace("bind"),
            QualType.ForSpace("c"),
        ],
    )

    for _meth in struct.Methods:
        if conf.isAcceptedByBackend(_meth) and not _meth.IsConstructor:
            Methods.append(
                _gen_vtable_method_specialization(
                    _meth=_meth,
                    struct=struct,
                    ast=ast,
                    conf=conf,
                    c_type=c_type,
                    cpp_vtable_type=cpp_vtable_type,
                ))

    vtable_struct = codegen_ir.GenTuStruct(
        Name=cpp_vtable_type,
        IsExplicitInstantiation=True,
        IsTemplateRecord=True,
        ExplicitTemplateParams=[struct.declarationQualName()],
        TemplateParams=codegen_ir.GenTuTemplateParams.FinalSpecialization(),
        Methods=Methods,
    )

    get_vtable_method = codegen_ir.GenTuFunction(
        Name="get_vtable",
        IsStatic=True,
        ReturnType=c_type_vtable.asConstPtr(),
        Body=ast.stack([
            ast.Using(
                cpp.UsingParams(newName="VtableType",
                                baseType=vtable_struct.declarationQualName())),
            ast.VarDecl(
                cpp.ParmVarParams(
                    type=c_type_vtable,
                    name="vtable",
                    IsConst=True,
                    storage=cpp.StorageClass.Static,
                    defWithAssign=False,
                    defArg=ast.pars(
                        ast.stack([
                            ast.line([
                                ast.string(f".{_meth.Name} = "),
                                ast.Addr(
                                    ast.Scoped(QualType(Name="VtableType"),
                                               ast.string(_meth.Name))),
                                ast.string(","),
                            ]) for _meth in vtable_struct.Methods
                        ]),
                        left="{",
                        right="}",
                    ),
                )),
            ast.Return(ast.Addr(ast.string("vtable"))),
        ]))

    vtable_struct.Methods.append(get_vtable_method)

    return vtable_struct


@beartype
@dataclass
class _StructGenResult():
    wrappers: list[codegen_ir.GenTuEntry] = field(default_factory=list)
    forward_decls: list[codegen_ir.GenTuEntry] = field(default_factory=list)
    vtables: list[codegen_ir.GenTuEntry] = field(default_factory=list)


@beartype
def _gen_struct_destructor_vtable(
    *,
    struct: codegen_ir.GenTuStruct,
    basename: str,
    ast: cpp.ASTBuilder,
    wrap_struct: codegen_ir.GenTuStruct,
    conf: CAstbuilderConfig,
) -> codegen_ir.GenTuFunction:

    Impl = ast.XCall(
        "org::bind::c::execute_destroy_vtable",
        args=[
            ast.string(_CONTEXT_ARG.Name),
            ast.string("obj"),
        ],
        Params=[_get_vtable_type(struct.declarationQualName(), conf)],
        Stmt=True,
    )

    return codegen_ir.GenTuFunction(
        Name=f"haxorg_destroy_{basename}",
        Args=[
            _CONTEXT_ARG,
            codegen_ir.GenTuIdent(Name="obj",
                                  Type=wrap_struct.Name.copy_update(PtrCount=1))
        ],
        Body=Impl,
        Annotations=[_LINK_ANNOTATION],
    )


@beartype
def _gen_struct_destructor_direct(
        *, struct: codegen_ir.GenTuStruct, basename: str, ast: cpp.ASTBuilder,
        wrap_struct: codegen_ir.GenTuStruct) -> codegen_ir.GenTuFunction:
    Impl = ast.XCall(
        "org::bind::c::execute_destroy",
        args=[ast.string(_CONTEXT_ARG.Name),
              ast.string("obj")],
        Params=[struct.declarationQualName()],
        Stmt=True,
    )

    return codegen_ir.GenTuFunction(
        Name=f"haxorg_destroy_{basename}",
        Args=[
            _CONTEXT_ARG,
            codegen_ir.GenTuIdent(Name="obj",
                                  Type=wrap_struct.Name.copy_update(PtrCount=1))
        ],
        Body=Impl,
        Annotations=[_LINK_ANNOTATION],
    )


@beartype
def _gen_struct_field_vtable(
        *, conf: CAstbuilderConfig, f: codegen_ir.GenTuField,
        wrap_struct: codegen_ir.GenTuStruct) -> codegen_ir.GenTuField:
    assert f.Type
    return codegen_ir.GenTuField(
        Name=f"get_{f.Name}",
        Type=QualType.ForFunction(
            ReturnType=_aux_public_api_type(f.Type, conf).asConstPtr(),
            Args=[_CONTEXT_ARG.Type, wrap_struct.Name.asConstPtr()],
        ))


@beartype
def _gen_struct_field_getter(
    *,
    conf: CAstbuilderConfig,
    wrap_struct: codegen_ir.GenTuStruct,
    struct: codegen_ir.GenTuStruct,
    f: codegen_ir.GenTuField,
    ast: cpp.ASTBuilder,
) -> codegen_ir.GenTuFunction:
    assert f.Type
    return codegen_ir.GenTuFunction(
        Name=f"{wrap_struct.Name.Name}_get_{f.Name}",
        ReturnType=conf.getBackendType(f.Type),
        Args=[_CONTEXT_ARG,
              codegen_ir.GenTuIdent(wrap_struct.Name, "__this")],
        Body=ast.Return(
            ast.XCall(
                "org::bind::c::get_cpp_field",
                args=[
                    ast.string(_CONTEXT_ARG.Name),
                    ast.string("__this"),
                    ast.Addr(ast.Scoped(
                        struct.declarationQualName(),
                        ast.string(f.Name),
                    )),
                ],
                Params=[
                    conf.getBackendType(f.Type),
                    struct.declarationQualName(),
                    f.Type,
                    conf.getBackendType(struct.declarationQualName()),
                ],
            )),
        Annotations=[_LINK_ANNOTATION],
    )


@beartype
def _gen_struct_basename(struct: codegen_ir.GenTuStruct, conf: CAstbuilderConfig) -> str:
    return conf.getBackendType(struct.declarationQualName()).Name.replace("haxorg_", "")


@beartype
def _gen_wrap_struct_base(struct: codegen_ir.GenTuStruct,
                          conf: CAstbuilderConfig) -> codegen_ir.GenTuStruct:
    basename = _gen_struct_basename(struct, conf)

    wrap_struct = codegen_ir.GenTuStruct(
        Name=QualType(Name=f"haxorg_{basename}"),
        GenDescribeFields=False,
        GenDescribeMethods=False,
        Doc=codegen_ir.GenTuDoc(
            f"{struct.declarationQualName().flatQualNameWithParams()}"))

    wrap_struct.Fields.append(codegen_ir.GenTuField(
        Type=_PAYLOAD_TYPE,
        Name="data",
    ))

    return wrap_struct


@beartype
def _append_forward_decl(result: _StructGenResult,
                         wrap_struct: codegen_ir.GenTuStruct) -> None:
    result.forward_decls.append(
        codegen_ir.GenTuStruct(Name=wrap_struct.Name, IsForwardDecl=True))


@beartype
def _append_nested_entries(result: _StructGenResult, struct: codegen_ir.GenTuStruct,
                           ast: cpp.ASTBuilder, conf: CAstbuilderConfig) -> None:
    for entry in struct.Nested:
        match entry:
            case codegen_ir.GenTuStruct():
                if conf.isAcceptedByBackend(entry):
                    conv = _gen_struct_direct(entry, ast, conf)
                    result.forward_decls.extend(conv.forward_decls)
                    result.wrappers.extend(conv.wrappers)
                    result.vtables.extend(conv.vtables)

            case codegen_ir.GenTuEnum():
                if conf.isAcceptedByBackend(entry):
                    result.wrappers.append(_gen_enum(entry, ast, conf))

            case codegen_ir.GenTuTypedef():
                if conf.isAcceptedByBackend(entry):
                    result.wrappers.append(_gen_typedef(entry, ast, conf))

            case codegen_ir.GenTuPass():
                pass

            case _:
                raise TypeError(type(entry))


@beartype
def _append_direct_fields(result: _StructGenResult, struct: codegen_ir.GenTuStruct,
                          wrap_struct: codegen_ir.GenTuStruct, ast: cpp.ASTBuilder,
                          conf: CAstbuilderConfig) -> None:
    for f in struct.Fields:
        if conf.isAcceptedByBackend(f):
            result.wrappers.append(
                _gen_struct_field_getter(f=f,
                                         struct=struct,
                                         conf=conf,
                                         wrap_struct=wrap_struct,
                                         ast=ast))


@beartype
def _make_vtable_struct(basename: str) -> codegen_ir.GenTuStruct:
    return codegen_ir.GenTuStruct(
        Name=QualType(Name=f"haxorg_{basename}_vtable"),
        GenDescribeFields=False,
        GenDescribeMethods=False,
    )


@beartype
def _gen_struct_direct(struct: codegen_ir.GenTuStruct, ast: cpp.ASTBuilder,
                       conf: CAstbuilderConfig) -> _StructGenResult:
    result = _StructGenResult()
    wrap_struct = _gen_wrap_struct_base(struct, conf)

    _append_forward_decl(result, wrap_struct)
    _append_direct_fields(result, struct, wrap_struct, ast, conf)

    for _meth in struct.Methods:
        if conf.isAcceptedByBackend(_meth):
            gen_fu = _gen_func(
                _meth,
                ast,
                conf,
                struct.declarationQualName(),
            )
            result.wrappers.append(gen_fu)

    _append_nested_entries(result, struct, ast, conf)

    result.wrappers.append(wrap_struct)
    result.wrappers.append(
        _gen_struct_destructor_direct(
            struct=struct,
            basename=_gen_struct_basename(struct, conf),
            ast=ast,
            wrap_struct=wrap_struct,
        ))

    return result


@beartype
def _gen_void_handle_template_instantiation(
        struct: codegen_ir.GenTuStruct,
        conf: CAstbuilderConfig) -> codegen_ir.GenTuStruct:
    return cast(
        codegen_ir.GenTuStruct,
        instantiate_template(
            struct,
            substitution_map={T.Name: _PAYLOAD_TYPE for T in struct.getTemplateParams()},
            type_map=conf.type_map,
        ))


@beartype
def _gen_haxorg_vtable_template_instantiation(
    *,
    struct: codegen_ir.GenTuStruct,
    conf: CAstbuilderConfig,
    ast: cpp.ASTBuilder,
    specializations: List[SpecializationMatchResult],
) -> _StructGenResult:
    result = _StructGenResult()

    wrap_struct = _gen_wrap_struct_base(struct, conf)
    public_instrantiation_api = _gen_void_handle_template_instantiation(struct, conf)

    result.wrappers.append(wrap_struct)
    vtable_type = _get_vtable_type(struct.Name, conf=conf)

    vtable_struct = _make_vtable_struct(_gen_struct_basename(struct, conf))

    for f in public_instrantiation_api.Fields:
        if conf.isAcceptedByBackend(f):
            vtable_struct.Fields.append(
                _gen_struct_field_vtable(f=f, conf=conf, wrap_struct=wrap_struct))

    for m in public_instrantiation_api.Methods:
        if conf.isAcceptedByBackend(m):
            cpp_vtable_method_type = m.get_function_type().model_copy(deep=True)
            assert cpp_vtable_method_type.Func
            vtable_method_type = conf.getBackendType(cpp_vtable_method_type)

            assert vtable_method_type.Func
            if not m.IsStatic:
                vtable_method_type.Func.Args.insert(0, wrap_struct.declarationQualName())

            vtable_method_type.Func.ReturnType = _aux_public_api_type(
                cpp_vtable_method_type.Func.ReturnType,
                conf=conf,
            )

            vtable_method_type.Func.Args.insert(0, _CONTEXT_ARG.Type)
            vtable_struct.Fields.append(
                codegen_ir.GenTuField(
                    Type=vtable_method_type,
                    Name=_get_func_base_name(m),
                ))

    for _meth in public_instrantiation_api.Methods:
        if conf.isAcceptedByBackend(_meth):
            gen_fu = _gen_func_vtable(
                func=_meth,
                ast=ast,
                conf=conf,
                Class=struct.declarationQualName(),
                VTable=vtable_type,
            )

            result.wrappers.append(gen_fu)

    for spec in specializations:
        result.vtables.append(
            _gen_vtable_specialization(
                struct=cast(
                    codegen_ir.GenTuStruct,
                    instantiate_template(
                        struct,
                        substitution_map=spec.substitution_map,
                        type_map=conf.type_map,
                    )),
                ast=ast,
                conf=conf,
                c_type=wrap_struct.declarationQualName(),
                c_type_vtable=vtable_type,
            ))

    result.wrappers.append(vtable_struct)

    return result


@beartype
def _get_entries_for_wrapping(groups: PyhaxorgTypeGroups,
                              conf: CAstbuilderConfig) -> list[codegen_ir.GenTuUnion]:
    typedefs_to_expand = list()
    entries_to_rewrite = list()

    for entry in groups.get_entries_for_wrapping():
        if conf.isAcceptedByBackend(entry) and isinstance(
                entry, codegen_ir.GenTuTypedef) and entry.ReflectionParams.expand_typedef:
            log(CAT).info(f"Typedef entry {entry}")
            typedefs_to_expand.append(entry)

        else:
            entries_to_rewrite.append(entry)

    expansion_matcher = TypedefExpansionMatcher(typedefs_to_expand)

    return cast(
        list[codegen_ir.GenTuUnion],
        [rewrite_any_typedefs(e, matcher=expansion_matcher) for e in entries_to_rewrite],
    )


@beartype
def gen_haxorg_c_wrappers(groups: PyhaxorgTypeGroups,
                          ast: cpp.ASTBuilder) -> codegen_ir.GenFiles:
    "Generate C wrappers"
    conf = CAstbuilderConfig(type_map=groups.type_map)

    standalone_funcs: List[codegen_ir.GenTuFunction] = list()
    wrapped_structs: List[codegen_ir.GenTuEntry] = list()
    header_only: list[codegen_ir.GenTuEntry] = list()
    vtables: list[codegen_ir.GenTuEntry] = list()

    def _add_struct_result(structs: _StructGenResult):
        wrapped_structs.extend(structs.wrappers)
        header_only.extend(structs.forward_decls)
        vtables.extend(structs.vtables)

    def _add_struct(entry: codegen_ir.GenTuStruct):
        structs = _gen_struct_direct(entry, ast, conf)
        _add_struct_result(structs)

    expanded_entries = _get_entries_for_wrapping(groups, conf)

    reflection_template_types: List[codegen_ir.GenTuStruct] = list()
    for entry in expanded_entries:
        if isinstance(entry, codegen_ir.GenTuStruct
                     ) and entry.IsTemplateRecord and not entry.IsExplicitInstantiation:
            match entry.declarationQualName().flatQualNameWithParams():
                case ["org", "sem", "SemId", _]:
                    # TODO: This edge case can be replaced by the reflection
                    # parameters in the type annotations.
                    _add_struct(
                        cast(
                            codegen_ir.GenTuStruct,
                            instantiate_template(
                                entry,
                                substitution_map={
                                    "O": QualType(Name="Org", Spaces=[n_sem()])
                                },
                                type_map=conf.type_map,
                            )))

                case _:
                    reflection_template_types.append(entry)

    specializations = collect_type_specializations(
        expanded_entries,
        conf,
    )

    void_handle_instantiations = list()
    for template_type in reflection_template_types:
        assert template_type.TemplateParams
        template_usage_types = match_specializations_for_struct(
            specializations=[spec.used_type for spec in specializations],
            template=template_type,
        )

        for target_type in [
                # "hstd::Opt",
        ]:
            for s in specializations:
                if target_type in str(s.used_type) and target_type in str(template_type):
                    log(CAT).debug(f"{s.used_type}")
                    debug = list()
                    match_result = match_specializations_for_struct(
                        [s.used_type],
                        template_type,
                        debug=True,
                        debug_sink=debug,
                    )

                    if not match_result:
                        log(CAT).warning("\n" + "\n".join(debug))

        if template_type.ReflectionParams.backend.c.instantiation_mode == "each-specialization":
            log(CAT).info(f"Found template type with each-specialization {template_type}")
            for match in template_usage_types:
                _add_struct(
                    cast(
                        codegen_ir.GenTuStruct,
                        instantiate_template(
                            template_type,
                            substitution_map=match.substitution_map,
                            type_map=conf.type_map,
                        )))

        elif template_type.ReflectionParams.backend.c.instantiation_mode == "void-handle":
            log(CAT).info(f"Found void-handle type {template_type}")
            assert template_type.ReflectionParams.backend.c.value_template_parameters, (
                "void-handle must provide names for the template type parameters")

            for inst in template_usage_types:
                log(CAT).debug(f"> {inst.instantiated_name}")
                void_handle_instantiations.append(
                    cast(
                        codegen_ir.GenTuStruct,
                        instantiate_template(
                            template_type,
                            substitution_map=inst.substitution_map,
                            type_map=conf.type_map,
                        )))

            _add_struct_result(
                _gen_haxorg_vtable_template_instantiation(
                    struct=template_type,
                    specializations=template_usage_types,
                    conf=conf,
                    ast=ast,
                ))

    void_handle_specializations = collect_type_specializations(void_handle_instantiations,
                                                               conf)

    if False:
        for template_type in reflection_template_types:
            if template_type.ReflectionParams.backend.c.instantiation_mode == "each-specialization":
                matches: list[tuple[SpecializationMatchResult,
                                    Optional[codegen_ir.GenTuEntry]]] = list()
                for spec in void_handle_specializations:
                    match1 = match_specializations_for_struct(
                        specializations=[spec.used_type],
                        template=template_type,
                    )

                    if match1:
                        matches.append((match1[0], spec.used_in))

                if 1 < len(matches):
                    raise RuntimeError("""
{template_name} was used with multiple different type parameters when substituting the public API for void-handle types: API for void-handle needs to the type with distinct instances.

{template_usages}

The type cannot be used in each-instantiation mode as there are void-handle API that need to return the instantiations as void handle.

!! TO RESOLVE THIS ISSUE, MARK {template_name} AS `void-handle` !!
                    """.format(
                        template_name=str(template_type.Name),
                        template_usages="\n".join("- {} (used in {})".format(
                            m[0].instantiated_name.format(native=True),
                            m[1],
                        ) for m in matches),
                    ))

    for entry in expanded_entries:
        if conf.isAcceptedByBackend(entry):
            match entry:
                case codegen_ir.GenTuFunction():
                    standalone_funcs.append(_gen_func(entry, ast, conf))

                case codegen_ir.GenTuStruct():
                    if entry.IsTemplateRecord and not entry.IsExplicitInstantiation:
                        log(CAT).info(f"Skipping {entry}")
                        continue

                    match entry.declarationQualName().flatQualNameWithParams():
                        case ["org", "imm", "ImmIdT", _]:
                            # Ignore explicit specializations for immutable ID
                            # in the C backend.
                            continue

                        case _:
                            _add_struct(entry)

                case codegen_ir.GenTuEnum():
                    header_only.append(_gen_enum(entry, ast, conf))

                case codegen_ir.GenTuTypedef():
                    tdef = _gen_typedef(entry, ast, conf)
                    wrapped_structs.append(tdef)

                case _:
                    raise TypeError(type(entry))

    def is_forward_declared(Type: QualType) -> bool:
        return False

    wrapped_structs = topological_sort_entries(
        wrapped_structs,  # type: ignore
        use_api=True,
        is_forward_declared=is_forward_declared,
    )

    return codegen_ir.GenFiles([
        codegen_ir.GenUnit(
            header=codegen_ir.GenTu(
                "{root}/src/wrappers/c/haxorg_c.h",
                [
                    codegen_ir.GenTuPass(ast.string("#pragma once")),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_api.h", True),
                ] + header_only + wrapped_structs + standalone_funcs,
            ),
            source=codegen_ir.GenTu(
                "{root}/src/wrappers/c/haxorg_c.cpp",
                [
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c.h", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_vtables.hpp", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_vtables_manual.hpp",
                                            True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_utils.hpp", True),
                ] + wrapped_structs + standalone_funcs,
            ),
        ),
        codegen_ir.GenUnit(
            header=codegen_ir.GenTu(
                "{root}/src/wrappers/c/haxorg_c_vtables.hpp",
                [
                    codegen_ir.GenTuPass(ast.string("#pragma once")),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c.h", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_utils.hpp", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_vtables_manual.hpp",
                                            True),
                ] + vtables,
            ),
            source=codegen_ir.GenTu(
                "{root}/src/wrappers/c/haxorg_c_vtables.cpp",
                [
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c.h", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_utils.hpp", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_vtables.hpp", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_vtables_manual.hpp",
                                            True),
                ] + vtables,
            ),
        )
    ])
