from py_codegen.astbuilder_base_config import BUILTIN_TYPES
from py_codegen.astbuilder_c_config import CAstbuilderConfig
import py_codegen.astbuilder_cpp as cpp
from dataclasses import dataclass, field, replace
from py_codegen import codegen_ir
from py_codegen.codegen_ir import QualType, n_org, n_sem
from beartype import beartype
from beartype.typing import List, Optional, cast
from py_codegen.codegen_type_groups import PyhaxorgTypeGroups, topological_sort_entries
from py_codegen.org_codegen_data import get_types
from py_scriptutils.script_logging import log
from py_codegen.codegen_algo import instantiate_template

CAT = __name__

_CONTEXT_ARG = codegen_ir.GenTuIdent(
    Type=QualType(Name="OrgContext", PtrCount=1),
    Name="org_context",
)

_LINK_ANNOTATION = codegen_ir.GenTuAnnotation(
    Attribute=codegen_ir.GenTuAnnotation.Freeform(Body="HAXORG_C_API_LINKAGE"))


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

    impl_call = ast.XCall(
        "org::bind::c::execute_cpp",
        args=pass_args,
        Params=[conf.getBackendType(func.ReturnType)],
    )

    if func.IsConstructor:
        assert func.ParentClass
        FuncName = f"haxorg_create_{conf.getTypeBindName(func.ParentClass)}_{_get_func_base_name(func)}"

    elif Class:
        FuncName = f"haxorg_{conf.getTypeBindName(Class)}_{_get_func_base_name(func)}"

    else:
        FuncName = f"haxorg_{_get_func_base_name(func)}"

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


@beartype
@dataclass
class _StructGenResult():
    wrappers: list[codegen_ir.GenTuEntry] = field(default_factory=list)
    forward_decls: list[codegen_ir.GenTuEntry] = field(default_factory=list)


@beartype
def _gen_struct(struct: codegen_ir.GenTuStruct, ast: cpp.ASTBuilder,
                conf: CAstbuilderConfig) -> _StructGenResult:

    result = _StructGenResult()
    basename = conf.getBackendType(struct.declarationQualName()).Name.replace(
        "haxorg_", "")

    wrap_struct = codegen_ir.GenTuStruct(
        Name=QualType(Name=f"haxorg_{basename}"),
        GenDescribeFields=False,
        GenDescribeMethods=False,
        Doc=codegen_ir.GenTuDoc(
            f"{struct.declarationQualName().flatQualNameWithParams()}"))

    result.forward_decls.append(
        codegen_ir.GenTuStruct(Name=wrap_struct.Name, IsForwardDecl=True))

    payload_type = QualType(Name="haxorg_ptr_payload")
    wrap_struct.Fields.append(codegen_ir.GenTuField(
        Type=payload_type,
        Name="data",
    ))

    for _meth in struct.Methods:
        if conf.isAcceptedByBackend(_meth):
            gen_fu = _gen_func(_meth, ast, conf, struct.declarationQualName())
            result.wrappers.append(gen_fu)

    for entry in struct.Nested:
        match entry:
            case codegen_ir.GenTuStruct():
                if conf.isAcceptedByBackend(entry):
                    conv = _gen_struct(entry, ast, conf)
                    result.forward_decls.extend(conv.forward_decls)
                    result.wrappers.extend(conv.wrappers)

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

    result.wrappers.append(wrap_struct)

    result.wrappers.append(
        codegen_ir.GenTuFunction(
            Name=f"haxorg_destroy_{basename}",
            Args=[
                _CONTEXT_ARG,
                codegen_ir.GenTuIdent(Name="obj",
                                      Type=wrap_struct.Name.copy_update(PtrCount=1))
            ],
            Body=ast.XCall(
                "org::bind::c::execute_destroy",
                args=[ast.string(_CONTEXT_ARG.Name),
                      ast.string("obj")],
                Params=[struct.declarationQualName()],
                Stmt=True,
            ),
            Annotations=[_LINK_ANNOTATION],
        ))

    return result


@beartype
def gen_haxorg_c_wrappers(groups: PyhaxorgTypeGroups,
                          ast: cpp.ASTBuilder) -> codegen_ir.GenFiles:
    "Generate C wrappers"
    conf = CAstbuilderConfig(type_map=groups.type_map)

    standalone_funcs: List[codegen_ir.GenTuFunction] = list()
    wrapped_structs: List[codegen_ir.GenTuEntry] = list()
    header_only: list[codegen_ir.GenTuEntry] = list()

    def _add_struct(entry: codegen_ir.GenTuStruct):
        structs = _gen_struct(entry, ast, conf)
        wrapped_structs.extend(structs.wrappers)
        header_only.extend(structs.forward_decls)

    def _add_instantiated_struct(entry: codegen_ir.GenTuStruct,
                                 substitution_map: dict[str, QualType]):
        instantiated = instantiate_template(
            entry,
            substitution_map=substitution_map,
            type_map=conf.type_map,
        )

        assert isinstance(instantiated, codegen_ir.GenTuStruct)

        log(CAT).info(f"Created struct {instantiated.declarationQualName()}")
        _add_struct(instantiated)

    for entry in groups.get_entries_for_wrapping():
        if isinstance(entry, codegen_ir.GenTuStruct) and "SemId" in str(entry.Name):
            log(CAT).info(f"declaration qual name: {entry}")

        if isinstance(entry, codegen_ir.GenTuStruct
                     ) and entry.IsTemplateRecord and not entry.IsExplicitInstantiation:
            match entry.declarationQualName().flatQualNameWithParams():
                case ["org", "sem", "SemId", _]:
                    log(CAT).info("Found sem ID emplate structure without parameters")
                    _add_instantiated_struct(
                        entry, {"O": QualType(Name="Org", Spaces=[n_sem()])})

                    # for org_type in get_types():
                    #     if org_type.Name.isOrgType():
                    #         _add_instantiated_struct(entry, {"O": org_type.Name})

    for entry in groups.get_entries_for_wrapping():
        if conf.isAcceptedByBackend(entry):
            match entry:
                case codegen_ir.GenTuFunction():
                    standalone_funcs.append(_gen_func(entry, ast, conf))

                case codegen_ir.GenTuStruct():
                    if entry.IsTemplateRecord and not entry.IsExplicitInstantiation:
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
                ],
            ),
            source=codegen_ir.GenTu(
                "{root}/src/wrappers/c/haxorg_c_vtables.cpp",
                [
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c.h", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_utils.hpp", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_vtables.hpp", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_vtables_manual.hpp",
                                            True),
                ],
            ),
        )
    ])
