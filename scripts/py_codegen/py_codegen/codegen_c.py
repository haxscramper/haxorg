from py_codegen.astbuilder_c_config import CAstbuilderConfig
import py_codegen.astbuilder_cpp as cpp
from py_codegen import codegen_ir
from py_codegen.codegen_ir import QualType
from beartype import beartype
from beartype.typing import List
from py_codegen.codegen_type_groups import PyhaxorgTypeGroups


@beartype
def _gen_func(func: codegen_ir.GenTuFunction, ast: cpp.ASTBuilder,
              conf: CAstbuilderConfig) -> codegen_ir.GenTuFunction:
    impl_call = ast.XCall(
        "convert_cpp_execution",
        args=[
            ast.Addr(ast.Type(func.get_full_qualified_name())),
            ast.string("org_context"),
        ] + [ast.string(a.Name) for a in func.Args],
        Params=[
            conf.getBackendType(func.ReturnType),
            func.get_function_type(),
        ] + [conf.getBackendType(arg.Type) for arg in func.Args],
    )

    if func.ReturnType != "void":
        impl_call = ast.Return(impl_call)

    return codegen_ir.GenTuFunction(
        ReturnType=conf.getBackendType(func.ReturnType),
        Name=func.Name,
        Args=[
            codegen_ir.GenTuIdent(
                Type=conf.getBackendType(arg.Type),
                Name=arg.Name,
            ) for arg in func.Args
        ] + [
            codegen_ir.GenTuIdent(
                Type=QualType(Name="OrgContext", PtrCount=1),
                Name="org_context",
            )
        ],
        Body=ast.stack([impl_call]),
        Annotations=[
            codegen_ir.GenTuAnnotation(Attribute=codegen_ir.GenTuAnnotation.Freeform(
                Body="HAXORG_C_API_LINKAGE"))
        ])


@beartype
def _gen_struct(
        struct: codegen_ir.GenTuStruct, ast: cpp.ASTBuilder, conf: CAstbuilderConfig
) -> list[codegen_ir.GenTuStruct | codegen_ir.GenTuFunction]:

    decls = list()
    basename = conf.getBackendType(struct.declarationQualName()).Name.replace(
        "haxorg_", "")

    wrap_struct = codegen_ir.GenTuStruct(
        Name=QualType(Name=f"haxorg_{basename}"),
        GenDescribeFields=False,
        GenDescribeMethods=False,
        Doc=codegen_ir.GenTuDoc(f"{struct.declarationQualName()}"))

    vtable_struct = codegen_ir.GenTuStruct(
        Name=QualType(Name=f"haxorg_{basename}_vtable"),
        GenDescribeFields=False,
        GenDescribeMethods=False,
    )

    for field in struct.Fields:
        if field.IsExposedForWrap:
            assert field.Type
            vtable_struct.Fields.append(
                codegen_ir.GenTuField(
                    Name=f"get_{field.Name}",
                    Type=QualType.ForFunction(
                        ReturnType=conf.getBackendType(field.Type).asConstPtr(),
                        Args=list(),
                    ),
                ))

    wrap_struct.Fields.append(
        codegen_ir.GenTuField(
            Type=vtable_struct.Name.asConstPtr(),
            Name="vtable",
        ))

    if struct.ReflectionParams and struct.ReflectionParams.backend.c.holder_type == "shared":
        payload_type = QualType(Name="haxorg_ptr_payload")

    else:
        payload_type = QualType(Name="haxorg_shared_ptr_payload")

    wrap_struct.Fields.append(codegen_ir.GenTuField(
        Type=payload_type,
        Name="data",
    ))

    decls.append(vtable_struct)
    decls.append(wrap_struct)

    decls.append(
        codegen_ir.GenTuFunction(
            Name=f"haxorg_destroy_{basename}",
            Args=[
                codegen_ir.GenTuIdent(Name="obj",
                                      Type=wrap_struct.Name.copy_update(PtrCount=1))
            ],
            Body=ast.XCall(
                "execute_destroy",
                args=[ast.string("obj")],
                Params=[struct.Name],
                Stmt=True,
            ),
        ))

    return decls


@beartype
def gen_haxorg_c_wrappers(groups: PyhaxorgTypeGroups,
                          ast: cpp.ASTBuilder) -> codegen_ir.GenFiles:
    "Generate C wrappers"
    conf = CAstbuilderConfig(type_map=groups.type_map)

    standalone_funcs: List[codegen_ir.GenTuFunction] = list()
    wrapped_structs: List[codegen_ir.GenTuEntry] = list()

    for entry in groups.get_entries_for_wrapping():
        match entry:
            case codegen_ir.GenTuFunction():
                if conf.isAcceptedByBackend(entry.ReflectionParams):
                    standalone_funcs.append(_gen_func(entry, ast, conf))

            case codegen_ir.GenTuStruct():
                if conf.isAcceptedByBackend(entry.ReflectionParams):
                    wrapped_structs.extend(_gen_struct(entry, ast, conf))

    return codegen_ir.GenFiles([
        codegen_ir.GenUnit(
            header=codegen_ir.GenTu(
                "{root}/src/wrappers/c/haxorg_c.h",
                [
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_api.h", True),
                ] + wrapped_structs + standalone_funcs,
            ),
            source=codegen_ir.GenTu(
                "{root}/src/wrappers/c/haxorg_c.cpp",
                [
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c.h", True),
                    codegen_ir.GenTuInclude("wrappers/c/haxorg_c_utils.hpp", True),
                ] + wrapped_structs + standalone_funcs,
            ),
        )
    ])
