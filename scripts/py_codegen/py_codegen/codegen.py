#!/usr/bin/env python

from dataclasses import dataclass, field, replace
import itertools
from typing import *

import py_codegen.astbuilder_py as pya
from py_codegen.org_codegen_data import *
from py_textlayout.py_textlayout_wrap import TextLayout, TextOptions
from py_codegen.refl_read import conv_proto_file, ConvTu, open_proto_file
from py_scriptutils.script_logging import log
import py_codegen.astbuilder_proto as pb
from py_scriptutils.algorithm import cond
from py_scriptutils.script_logging import pprint_to_file
from py_codegen.astbuilder_pybind11 import (
    Py11Method,
    Py11Module,
    Py11Field,
    Py11Class,
    Py11BindPass,
    Py11TypedefPass,
    Py11Enum,
    Py11Function,
    flat_scope,
    id_self,
    py_type_bind,
    py_type,
)

from py_scriptutils.repo_files import get_haxorg_repo_root_path

CAT = "codegen"


def with_enum_reflection_api(body: List[Any]) -> List[Any]:
    return [
        GenTuPass("#pragma once"),
        GenTuPass("#include <hstd/system/basic_templates.hpp>"),
        GenTuPass("#include <hstd/system/reflection.hpp>"),
        GenTuPass("#include <hstd/stdlib/Opt.hpp>"),
    ] + body


@beartype
def get_exporter_methods(forward: bool,
                         expanded: List[GenTuStruct]) -> Sequence[GenTuFunction]:
    methods: List[GenTuFunction] = []
    iterate_tree_context = []
    base_map = get_base_map(expanded)

    def callback(value: Any) -> None:
        nonlocal methods
        nonlocal base_map
        nonlocal iterate_tree_context
        if isinstance(value, GenTuStruct):
            scope_full: List[GenTuStruct] = [
                scope for scope in iterate_tree_context if isinstance(scope, GenTuStruct)
            ]
            scope_names: List[str] = [scope.name.name for scope in scope_full]
            name: str = value.name.name
            full_scoped_name: List[str] = scope_names + [name]
            fields: List[GenTuField] = [
                field for field in (value.fields + get_type_base_fields(value, base_map))
                if field.isExposedForWrap
            ]

            scoped_target = t_cr(
                QualType.ForName(name,
                                 Spaces=[QualType.ForName("sem")] +
                                 [QualType.ForName(t) for t in scope_names]))
            decl_scope = "" if forward else "Exporter<V, R>::"
            t_params = [] if forward else [GenTuParam("V"), GenTuParam("R")]

            variant_methods: List[GenTuFunction] = []
            for field in fields:
                if hasattr(field, "isVariantField"):
                    kindGetter = getattr(field, "variantGetter")
                    variant_methods.append(
                        GenTuFunction(
                            QualType.ForName("void"),
                            f"{decl_scope}visit",
                            GenTuDoc(""),
                            params=t_params,
                            arguments=[
                                GenTuIdent(
                                    QualType.ForName("R", RefKind=ReferenceKind.LValue),
                                    "res"),
                                GenTuIdent(
                                    t_cr(field.type),
                                    "object",
                                ),
                            ],
                            impl=None if forward else
                            f"visitVariants(res, sem::{'::'.join(full_scoped_name)}::{kindGetter}(object), object);",
                        ))

            if value.name.isOrgType() and len(scope_full) == 0:
                method = GenTuFunction(
                    QualType.ForName("void"),
                    f"{decl_scope}visit{name}",
                    GenTuDoc(""),
                    params=t_params,
                    arguments=[
                        GenTuIdent(QualType.ForName("R", RefKind=ReferenceKind.LValue),
                                   "res"),
                        GenTuIdent(
                            QualType.ForName(
                                "In", Parameters=[QualType.ForName(f"sem::{name}")]),
                            "object"),
                    ],
                    impl=cond(
                        forward,
                        None,
                        "auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));\n{}"
                        .format(
                            "\n".join([
                                f"__org_field(res, object, {a.name});" for a in fields
                            ]),),
                    ),
                )
            else:
                method = GenTuFunction(
                    QualType.ForName("void"),
                    f"{decl_scope}visit",
                    GenTuDoc(""),
                    params=t_params,
                    arguments=[
                        GenTuIdent(QualType.ForName("R", RefKind=ReferenceKind.LValue),
                                   "res"),
                        GenTuIdent(scoped_target, "object"),
                    ],
                    impl=None if forward else "\n".join(
                        [f"__obj_field(res, object, {a.name});" for a in fields]),
                )

            methods += variant_methods + [method]

    iterate_object_tree(expanded, iterate_tree_context, pre_visit=callback)
    return methods


@beartype
def get_imm_serde(types: List[GenTuStruct], ast: ASTBuilder) -> List[GenTuPass]:
    serde: List[GenTuStruct] = []

    base_map = get_base_map(types)

    def aux(it):
        match it:
            case GenTuStruct():
                if not it.concreteKind:
                    return

                sem_type = it.name
                respace = it.name.flatQualScope()[2:] + [
                    it.name.withoutAllScopeQualifiers()
                ]
                respace[0].name = "Imm" + respace[0].name
                respace = [n_imm()] + respace
                imm_type = respace[-1].model_copy(update=dict(Spaces=respace[:-1]))

                writer_body: List[BlockId] = [
                    ast.line(
                        ast.Type(imm_type),
                        ast.string(" result = "),
                        ast.CallStatic(
                            typ=QualType(
                                name="SerdeDefaultProvider",
                                Parameters=[imm_type],
                                Spaces=[n_hstd()],
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
                                Spaces=[n_hstd()],
                            ),
                            opc="get",
                        ),
                        ast.string(";"),
                    )
                ]

                def field_aux(sub: GenTuStruct):
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
                        if base.name in base_map:
                            it_base = base_map[base.name]
                            assert it_base.name.name != sub.name.name
                            field_aux(it_base)

                # sys.setrecursionlimit(32)
                field_aux(it)

                writer_body.append(ast.Return(ast.string("result")))
                reader_body.append(ast.Return(ast.string("result")))

                writer = MethodDeclParams(
                    Params=FunctionParams(
                        Name="to_immer",
                        ResultTy=imm_type,
                        Args=[
                            ParmVarParams(name="value", type=sem_type.asConstRef()),
                            ParmVarParams(
                                name="ctx",
                                type=QualType(name="ImmAstEditContext").asRef()),
                        ],
                        Body=writer_body,
                        AllowOneLine=False,
                    ),
                    isStatic=True,
                )

                reader = MethodDeclParams(
                    Params=FunctionParams(
                        Name="from_immer",
                        ResultTy=sem_type,
                        Args=[
                            ParmVarParams(name="value", type=imm_type.asConstRef()),
                            ParmVarParams(
                                name="ctx",
                                type=QualType(name="ImmAstContext").asConstRef()),
                        ],
                        Body=reader_body,
                        AllowOneLine=False,
                    ),
                    isStatic=True,
                )

                rec = RecordParams(
                    name=QualType(name="ImmSemSerde"),
                    NameParams=[sem_type, imm_type],
                    Template=TemplateParams(Stacks=[TemplateGroup(Params=[])]),
                    members=[writer, reader],
                )

                serde.append(GenTuPass(ast.Record(rec)))

    iterate_object_tree(types, [], pre_visit=aux)

    return serde


@beartype
def get_concrete_types(expanded: List[GenTuStruct]) -> Sequence[GenTuStruct]:
    return [struct for struct in expanded if struct.concreteKind]


org_type_names: List[str] = []

from copy import deepcopy, copy


def filter_init_fields(Fields: List[Py11Field]) -> List[Py11Field]:
    return [F for F in Fields if F.Type.name not in ["SemId"]]


@beartype
def pybind_org_id(ast: ASTBuilder, b: TextLayout, typ: GenTuStruct,
                  base_map: Mapping[str, GenTuStruct]) -> Py11Class:
    base_type = QualType.ForName(typ.name.name, Spaces=[n_sem()])
    id_type = QualType.ForName(
        "SemId",
        Parameters=[base_type],
        Spaces=[n_sem()],
    )

    res = Py11Class(
        PyName=typ.name.name,
        Class=base_type,
        PyHolderType=id_type,
    )

    for base in typ.bases:
        res.Bases.append(base)

    _self = id_self(id_type)

    def map_obj_fields(Record: GenTuStruct):
        for _field in Record.fields:
            if _field.isExposedForWrap:
                res.Fields.append(Py11Field.FromGenTu(_field))

    def map_obj_methods(Record: GenTuStruct):
        for meth in Record.methods:
            if not meth.isPureVirtual and meth.isExposedForWrap:
                res.Methods.append(Py11Method.FromGenTu(meth))

    def map_bases(Record: GenTuStruct):
        for base in Record.bases:
            if base.name != "Org":
                map_obj_fields(base_map[base.name])
                map_obj_methods(base_map[base.name])
                map_bases(base_map[base.name])

    map_obj_fields(typ)
    map_obj_methods(typ)
    map_bases(typ)

    if typ.concreteKind and typ.name.name != "Org":
        rec_fields: List[Py11BindPass] = []

        def cb(it: GenTuStruct):
            for field in it.fields:
                if field.isExposedForWrap:
                    rec_fields.append(Py11Field.FromGenTu(field))

            for base in it.bases:
                cb(base_map[base.name])

        cb(typ)

        res.InitDefault(ast=ast, Fields=filter_init_fields(rec_fields))
        res.InitMagicMethods(ast=ast)

    return res


@beartype
def pybind_nested_type(ast: ASTBuilder, value: GenTuStruct) -> Py11Class:
    res = Py11Class(
        PyName=py_type(value.name).Name,
        Class=value.name,
        Bases=value.bases,
    )

    for meth in value.methods:
        if meth.isExposedForWrap:
            res.Methods.append(Py11Method.FromGenTu(meth))

    for _field in value.fields:
        if _field.isExposedForWrap:
            res.Fields.append(Py11Field.FromGenTu(_field))

    if not value.IsAbstract:
        res.InitDefault(ast, filter_init_fields(res.Fields))
        res.InitMagicMethods(ast=ast)

    return res


@beartype
def get_osk_enum(expanded: List[GenTuStruct]) -> GenTuEnum:
    return GenTuEnum(
        QualType.ForName(t_osk().name),
        GenTuDoc(""),
        fields=[
            GenTuEnumField(struct.name.name, GenTuDoc(""))
            for struct in get_concrete_types(expanded)
        ],
    )


@beartype
def add_structures(res: Py11Module, ast: ASTBuilder, structs: List[GenTuStruct]):
    b: TextLayout = ast.b

    base_map = get_base_map(structs)

    def codegenConstructCallback(value: Any) -> None:
        if isinstance(value, GenTuStruct):
            if hasattr(value, "isOrgType") or value.name.name == "Org":
                res.Decls.append(pybind_org_id(ast, b, value, base_map))

            else:
                new = pybind_nested_type(ast, value)
                res.Decls.append(new)

        elif isinstance(value, GenTuEnum):
            res.Decls.append(Py11Enum.FromGenTu(value, PyName=py_type(value.name).Name))

        elif isinstance(value, GenTuTypedef):
            res.Decls.append(
                Py11TypedefPass(
                    name=py_type(value.name),
                    base=py_type(value.base),
                ))

    # Map data definitions into python wrappers
    iterate_object_tree(
        GenTuNamespace(n_sem(), structs),
        [],
        post_visit=codegenConstructCallback,
    )


@beartype
def add_enums(res: Py11Module, ast: ASTBuilder, enums: List[GenTuEnum]):
    for item in enums:
        wrap = Py11Enum.FromGenTu(item, py_type(item.name).Name)
        res.Decls.append(wrap)


@beartype
def add_translation_unit(res: Py11Module, ast: ASTBuilder, tu: ConvTu):
    for _struct in tu.structs:
        # There is no topological sorting on the type declarations, so to make the initialization
        # work in correct order I need to push some of the [[refl]] annotated types at the top.
        if _struct.name.name == "Org":
            from py_scriptutils.script_logging import pprint_to_file
            pprint_to_file(_struct, "/tmp/sem_org_struct.py")
            org_decl = pybind_org_id(ast, ast.b, _struct, {})
            org_decl.Methods.append(
                Py11Method(
                    "__getitem__",
                    "at",
                    t_id(),
                    [GenTuIdent(QualType.ForName("int"), "idx")],
                    IsConst=True,
                    IsStatic=False,
                ))

            org_decl.Methods.append(
                Py11Method(
                    PyName="__iter__",
                    CxxName="at",
                    ResultTy=QualType.ForName("auto"),
                    Args=[GenTuIdent(t_id().par0().asConstRef(), "node")],
                    Body=[
                        ast.b.text(
                            "return pybind11::make_iterator(node.subnodes.begin(), node.subnodes.end());"
                        )
                    ],
                    DefParams=[ast.b.text("pybind11::keep_alive<0, 1>()")],
                    ExplicitClassParam=True,
                ))

            res.Decls.insert(0, org_decl)

        elif _struct.name.name == "LineCol":
            res.Decls.insert(0, pybind_nested_type(ast, _struct))

        else:
            res.Decls.append(pybind_nested_type(ast, _struct))

    for _enum in tu.enums:
        res.Decls.append(Py11Enum.FromGenTu(_enum, py_type(_enum.name).Name))

    for _func in tu.functions:
        res.Decls.append(Py11Function.FromGenTu(_func))


@beartype
def add_type_specializations(res: Py11Module, ast: ASTBuilder):

    opaque_declarations: List[BlockId] = []
    specialization_calls: List[BlockId] = [
        ast.string("org::bind::python::PyTypeRegistryGuard type_registry_guard{};")
    ]

    type_use_context: List[Any] = []
    seen_types: Set[QualType] = set()

    def record_specializations(value: Any):
        nonlocal type_use_context
        if isinstance(value, QualType):

            def rec_type(T: QualType):

                def rec_drop(T: QualType) -> QualType:
                    return T.model_copy(update=dict(
                        isConst=False,
                        RefKind=ReferenceKind.NotRef,
                        ptrCount=0,
                        isNamespace=False,
                        meta=dict(),
                        Spaces=[rec_drop(S) for S in T.Spaces],
                        Parameters=[rec_drop(P) for P in T.Parameters],
                    ))

                T = rec_drop(T)

                if hash(T) in seen_types:
                    return

                else:
                    seen_types.add(hash(T))

                if T.name in ["Vec", "UnorderedMap", "IntSet"]:
                    std_type: str = {
                        "Vec": "vector",
                        "UnorderedMap": "unordered_map",
                        "IntSet": "int_set",
                    }.get(T.name, None)

                    if T.name not in ["IntSet"]:
                        stdvec_t = QualType.ForName(std_type,
                                                    Spaces=[QualType.ForName("std")],
                                                    Parameters=T.Parameters)

                        opaque_declarations.append(
                            ast.XCall("PYBIND11_MAKE_OPAQUE", [ast.Type(stdvec_t)]))

                    opaque_declarations.append(
                        ast.XCall("PYBIND11_MAKE_OPAQUE", [ast.Type(T)]))

                    # opaque_declarations.append(ast.Comment(str(T)))

                    specialization_calls.append(
                        ast.XCall(
                            f"bind_{std_type}",
                            [
                                ast.string("m"),
                                ast.StringLiteral(py_type_bind(T).Name),
                                ast.string("type_registry_guard"),
                            ],
                            Params=T.Parameters,
                            Stmt=True,
                        ))

                else:
                    for P in T.Parameters:
                        rec_type(P)

            rec_type(value)

    iterate_object_tree(
        res,
        type_use_context,
        pre_visit=record_specializations,
    )

    for decl in opaque_declarations:
        res.Before.append(decl)

    res.Decls = [Py11BindPass(D) for D in specialization_calls] + res.Decls


@beartype
def expand_type_groups(ast: ASTBuilder, types: List[GenTuStruct]) -> List[GenTuStruct]:

    @beartype
    def rec_expand_group(record: GenTuTypeGroup,) -> List[GenTuEntry | GenTuField]:
        result = []
        typeNames: List[QualType] = []

        for item in record.types:
            expanded = rec_expand_type(item)
            result.append(expanded)
            if item.concreteKind:
                typeNames.append(expanded.name)

        if record.iteratorMacroName:
            iteratorMacro = MacroParams(
                name=record.iteratorMacroName,
                params=[MacroParams.Param("__IMPL")],
                doc=DocParams(""),
            )

            for typeItem in typeNames:
                iteratorMacro.definition.append(f"__IMPL({typeItem.name})")

            result.append(GenTuPass(ast.Macro(iteratorMacro)))

        if record.variantName and record.enumName:
            enum_type = record.enumName
            variant_type = record.variantName
            result.append(
                GenTuTypedef(
                    name=variant_type,
                    base=QualType(
                        name="variant",
                        Spaces=[QualType.ForName("std")],
                        Parameters=typeNames,
                    ),
                ))

            result.append(
                GenTuEnum(
                    name=enum_type,
                    doc=GenTuDoc(""),
                    fields=[GenTuEnumField(N.name, GenTuDoc("")) for N in typeNames],
                ))

            for idx, T in enumerate(typeNames):
                kindName = T.name[0].upper() + T.name[1:]
                result.append(
                    GenTuFunction(
                        doc=GenTuDoc(""),
                        name="is" + kindName,
                        result=QualType.ForName("bool"),
                        isConst=True,
                        impl=ast.Return(
                            ast.XCall("==", [
                                ast.XCall(record.kindGetter, []),
                                ast.string(f"{enum_type.name}::{kindName}"),
                            ])),
                    ))

                for isConst in [True, False]:
                    result.append(
                        GenTuFunction(
                            doc=GenTuDoc(""),
                            name="get" + kindName,
                            result=T.model_copy(update=dict(
                                RefKind=ReferenceKind.LValue,
                                isConst=isConst,
                            )),
                            isConst=isConst,
                            impl=ast.Return(
                                ast.XCall(
                                    "hstd::variant_get",
                                    [ast.string(record.variantField)],
                                    Params=[QualType.ForName(str(idx))],
                                )),
                        ))

            result.append(
                GenTuFunction(
                    isStatic=True,
                    doc=GenTuDoc(""),
                    name=record.kindGetter,
                    result=enum_type,
                    arguments=[GenTuIdent(t_cr(variant_type), "__input")],
                    impl=ast.Return(
                        ast.XCall(
                            "static_cast",
                            args=[ast.XCallRef(ast.string("__input"), "index")],
                            Params=[enum_type],
                        )),
                ))

            result.append(
                GenTuFunction(
                    name=record.kindGetter,
                    result=enum_type,
                    impl=ast.Return(
                        ast.XCall(record.kindGetter, [ast.string(record.variantField)])),
                    doc=GenTuDoc(""),
                    isConst=True,
                ))

            result.append(
                GenTuFunction(
                    name="sub_variant_get_name",
                    result=QualType(name="char", ptrCount=1, isConst=True),
                    impl=ast.Return(ast.StringLiteral(record.variantField)),
                    doc=GenTuDoc(""),
                    isConst=True,
                ))

            result.append(
                GenTuFunction(
                    name="sub_variant_get_data",
                    result=record.variantName.asConstRef(),
                    impl=ast.Return(ast.string(record.variantField)),
                    doc=GenTuDoc(""),
                    isConst=True,
                ))

            result.append(
                GenTuFunction(
                    name="sub_variant_get_kind",
                    result=record.enumName,
                    impl=ast.Return(ast.XCall(record.kindGetter)),
                    doc=GenTuDoc(""),
                    isConst=True,
                ))

            result.append(
                GenTuPass(
                    ast.Using(UsingParams(newName="variant_enum_type",
                                          baseType=enum_type))))

            result.append(
                GenTuPass(
                    ast.Using(
                        UsingParams(newName="variant_data_type", baseType=variant_type))))

            variant_field = GenTuField(
                type=deepcopy(variant_type),
                name=record.variantField,
                doc=GenTuDoc(""),
                value=ast.string(record.variantValue) if record.variantValue else None,
            )

            setattr(variant_field, "isVariantField", True)
            setattr(variant_field, "variantGetter", record.kindGetter)

            result.append(variant_field)

        return result

    @beartype
    def rec_expand_type(typ: GenTuStruct) -> GenTuStruct:
        converted = []
        methods: List[GenTuFunction] = []
        fields: List[GenTuField] = []
        for item in typ.nested:
            match item:
                case GenTuStruct():
                    converted.append(rec_expand_type(item))

                case GenTuTypeGroup():
                    for res in rec_expand_group(item):
                        if isinstance(res, GenTuField):
                            fields.append(res)

                        elif isinstance(res, GenTuFunction):
                            methods.append(res)

                        else:
                            converted.append(res)

                case GenTuEnum():
                    converted.append(replace(item, name=item.name))

                case GenTuPass():
                    converted.append(item)

                case _:
                    assert False, type(item)

        result = replace(
            typ,
            # name=typ.name.model_copy(update=dict(Spaces=context)),
            nested=converted,
            methods=typ.methods + methods,
            fields=typ.fields + fields,
        )

        if hasattr(typ, "isOrgType"):
            setattr(result, "isOrgType", getattr(typ, "isOrgType"))

        return result

    return [rec_expand_type(T) for T in types]


@beartype
def rewrite_to_immutable(recs: List[GenTuStruct]) -> List[GenTuStruct]:
    result = deepcopy(recs)

    IMM_BOX = t("ImmBox", [n_hstd_ext()])
    ORG_SPACE = n_imm()

    def conv_type(obj: QualType):
        match obj:
            case QualType(name="SemId", parameters=[]):
                obj.name = "ImmId"
                obj.Spaces = [ORG_SPACE]

            case QualType(name="SemId"):
                obj.name = "ImmIdT"
                obj.Spaces = [ORG_SPACE]

            # case QualType(meta={"isOrgType": True}):
            #     if len(obj.Spaces) == 0:
            #         obj.name = "Imm" + obj.name

            #     elif len(obj.Spaces) == 1:
            #         obj.name = "Imm" + obj.name
            #         obj.Spaces = [ORG_SPACE]

            #     else:
            #         spaces = obj.flatQualScope() + [obj.withoutAllScopeQualifiers()]
            #         obj.Spaces = [
            #             ORG_SPACE,
            #             spaces[1].model_copy(update=dict(name="Imm" + spaces[1].name)),
            #             *(spaces[2:-1] if 1 < len(spaces) else []),
            #         ]

            # case QualType(name=TypeName,
            #               Spaces=[QualType(name="sem")]) if "Id" not in TypeName:
            #     match obj:
            #         case QualType(meta={"isOrgType": False}):
            #             pass

            #         case _:
            #             obj.name = "Imm" + obj.name
            #             obj.Spaces = [ORG_SPACE]

            case QualType(name="Vec"):
                obj.name = "ImmVec"
                obj.Spaces = [n_hstd_ext()]

            case QualType(name="UnorderedMap"):
                obj.name = "ImmMap"
                obj.Spaces = [n_hstd_ext()]

            case _:
                flat_namespace = obj.flatQualFullName()
                # obj.dbg_origin += f"{flat_namespace} {obj.withoutAllScopeQualifiers()}"
                match flat_namespace:
                    case [QualType(name="org"), QualType(name="sem"), *rest]:
                        if rest and rest[0].isOrgType():
                            if 1 == len(rest):
                                obj.name = "Imm" + obj.name
                                obj.Spaces = [ORG_SPACE]
                                # obj.dbg_origin = "1"
                                # obj = QualType(name="Imm" + rest[0].name, Spaces=[ORG_SPACE, *(rest[1:] if 1 < len(rest) else [])])

                            elif 1 < len(rest):
                                # log(CAT).info(f"{obj} {rest}")
                                # obj.name = "Imm" + rest[0].name
                                reuse_spaces = copy(rest)
                                reuse_spaces.pop(0)
                                reuse_spaces.pop(-1)
                                # obj.dbg_origin += f"rest? {rest} -> {reuse_spaces}"
                                obj.Spaces = [
                                    ORG_SPACE,
                                    rest[0].model_copy(update=dict(name="Imm" +
                                                                   rest[0].name)),
                                    *reuse_spaces
                                ]

                            else:
                                pass
                                # obj.dbg_origin += "?"
                                # log(CAT).info(f"{obj.__dict__} {flat_namespace}")

                    # case _:
                    #     obj.dbg_origin = f"{flat_namespace}"

                    # case _:
                    # obj = res

                    # if 1 < len(rest):
                    #     obj.name = rest[-1].name
                    #     obj.Spaces[1].name = "Imm" + obj.Spaces[1].name
                    #     obj.dbg_origin += f"org sem qual name 1 {flat_namespace}"

                    # else:
                    #     obj.name = "Imm" + rest[-1].name
                    #     obj.dbg_origin += f"org sem qual name 2 {flat_namespace}"

    def impl(obj: Any):
        match obj:
            case QualType():
                conv_type(obj)

            case GenTuField(type=QualType(name="SemId", parameters=[])):
                conv_type(obj.type)
                obj.value = "org::imm::ImmId::Nil()"

            case GenTuField(type=QualType(name="SemId")):
                conv_type(obj.type)
                obj.value = f"org::imm::ImmIdT<org::imm::Imm{obj.type.par0().name}>::Nil()"

            case GenTuField(type=QualType(name="Opt")):
                obj.type = obj.type.par0().withWrapperType(
                    QualType(name="Opt", Spaces=[n_hstd()])).withWrapperType(IMM_BOX)

            case GenTuField(type=QualType(name="Str")):
                obj.type = obj.type.withWrapperType(IMM_BOX)

            case GenTuStruct():
                obj.methods = [
                    it for it in obj.methods
                    if (it.name in ["getKind"] or it.name == obj.name.name)
                ]
                obj.GenDescribeMethods = False
                obj.nested = [it for it in obj.nested if not isinstance(it, GenTuPass)]
                self_arg = obj.name.asConstRef()
                # conv_type(self_arg)
                obj.methods.append(
                    GenTuFunction(
                        result=QualType.ForName("bool"),
                        name="operator==",
                        isConst=True,
                        arguments=[GenTuIdent(type=self_arg, name="other")],
                    ))

                if hasattr(obj, "isOrgType"):

                    # conv_type(obj.name)
                    # obj.name.name = "Imm" + obj.name.name
                    # obj.name.Spaces = [ORG_SPACE]
                    obj.nested = [
                        GenTuPass(
                            f"using Imm{obj.bases[0].name}::Imm{obj.bases[0].name};"),
                        GenTuPass(f"virtual ~Imm{obj.name.name}() = default;"),
                    ] + obj.nested

    iterate_object_tree(result, [], pre_visit=impl)

    return result


def to_base_types(obj):

    def aux(obj, seen):
        if isinstance(obj, Enum):
            return obj.name

        elif isinstance(obj, (str, int, float, bool)) or obj is None:
            return obj

        obj_id = id(obj)
        if obj_id in seen:
            return 'recursive - {}'.format(type(obj).__name__)

        seen.add(obj_id)

        if isinstance(obj, dict):
            return {k: aux(v, seen) for k, v in obj.items()}

        elif isinstance(obj, list):
            return [aux(i, seen) for i in obj]

        elif hasattr(obj, '__dict__'):
            return aux(obj.__dict__, seen)

        elif hasattr(obj, '__iter__') and not isinstance(obj, str):
            return [aux(i, seen) for i in obj]

        else:
            return 'Type({}) - {}'.format(type(obj).__name__, str(obj))

    seen = set()
    return aux(obj, seen)


@beartype
def gen_adaptagrams_wrappers(
    ast: ASTBuilder,
    pyast: pya.ASTBuilder,
    reflection_path: Path,
) -> GenFiles:
    tu: ConvTu = conv_proto_file(reflection_path)
    res = Py11Module("py_adaptagrams")
    add_translation_unit(res, ast=ast, tu=tu)
    add_type_specializations(res, ast=ast)

    with open("/tmp/adaptagrams_reflection.json", "w") as file:
        log(CAT).debug(f"Debug reflection data to {file.name}")
        file.write(open_proto_file(reflection_path).to_json(2))

    return GenFiles([
        GenUnit(
            GenTu(
                "{root}/scripts/py_wrappers/py_wrappers/py_adaptagrams.pyi",
                [GenTuPass(res.build_typedef(pyast))],
                clangFormatGuard=False,
            )),
        GenUnit(
            GenTu(
                "{root}/src/py_libs/py_adaptagrams/adaptagrams_py_wrap.cpp",
                [
                    GenTuPass("#undef slots"),
                    GenTuPass("#define PYBIND11_DETAILED_ERROR_MESSAGES"),
                    GenTuInclude("adaptagrams/adaptagrams_ir.hpp", True),
                    GenTuInclude("py_libs/pybind11_utils.hpp", True),
                    GenTuInclude("pybind11/pybind11.h", True),
                    GenTuInclude("pybind11/stl.h", True),
                    GenTuPass(res.build_bind(ast)),
                ],
            )),
    ])


@beartype
@dataclass
class PyhaxorgTypenameGroups:
    nested_records: List[Tuple[str, str, str]] = field(default_factory=list)
    nested_enums: List[Tuple[str, str, str]] = field(default_factory=list)
    all_records: List[Tuple[str, str]] = field(default_factory=list)


@beartype
@dataclass
class PyhaxorgTypeDesc:
    fields: List[GenTuField]
    parent_fields: List[GenTuField]
    bases: List[QualType]
    name: str


@beartype
@dataclass
class PyhaxorgTypeFieldGroup:
    types: List[PyhaxorgTypeDesc] = field(default_factory=list)


@beartype
def collect_type_field_groups(
        types: List[GenTuStruct],
        base_map: Mapping[str, GenTuStruct]) -> PyhaxorgTypeFieldGroup:

    def aux(t: GenTuStruct) -> List[GenTuField]:
        result: List[GenTuField] = []
        for base in t.bases:
            if base.name in base_map:
                result += aux(base_map[base.name])

        return result

    def filter_fields(f: List[GenTuField]) -> List[GenTuField]:
        return [it for it in f if not it.isStatic]

    result = PyhaxorgTypeFieldGroup()

    for t in types:
        group = PyhaxorgTypeDesc(
            fields=filter_fields(t.fields),
            parent_fields=filter_fields(aux(t)),
            bases=list(t.bases),
            name=t.name.name,
        )

        result.types.append(group)

    return result


@beartype
def collect_pyhaxorg_typename_groups(types: List[GenTuStruct]) -> PyhaxorgTypenameGroups:
    res = PyhaxorgTypenameGroups()

    def aux(it):
        match it:
            case GenTuStruct() | GenTuEnum():
                flat = it.name.flatQualScope() + [it.name.withoutAllScopeQualifiers()]
                without_namespaces = [
                    i for i in range(len(flat)) if not flat[i].isNamespace
                ]
                # log(CAT).info(f"{it.name} {flat} {name_start} {without_namespaces}")
                name_start = without_namespaces[0]
                if 1 < len(without_namespaces):
                    parent = flat[name_start]
                    nested = flat[without_namespaces[1]:]
                    value = (
                        parent.name,
                        "::".join(it.name for it in nested),
                        "({})".format(", ".join(it.name for it in nested)),
                    )
                    if isinstance(it, GenTuStruct):
                        res.nested_records.append(value)

                    else:
                        res.nested_enums.append(value)

                if isinstance(it, GenTuStruct):
                    res.all_records.append((
                        "::".join(it.name for it in flat[name_start:]),
                        "({})".format(", ".join(it.name for it in flat[name_start:])),
                    ))

    iterate_object_tree(types, [], pre_visit=aux)

    return res


@beartype
def gen_iteration_macros(res: PyhaxorgTypenameGroups,
                         macro_group: str) -> List[GenTuPass]:
    result: List[GenTuPass] = []

    result.append(
        GenTuPass(f"#define EACH_{macro_group}_ORG_RECORD_NESTED(__IMPL) \\\n" +
                  (" \\\n".join(
                      ["    __IMPL({}, {}, {})".format(*it)
                       for it in res.nested_records]))))

    result.append(
        GenTuPass(f"#define EACH_{macro_group}_ORG_ENUM_NESTED(__IMPL) \\\n" +
                  (" \\\n".join(
                      ["    __IMPL({}, {}, {})".format(*it)
                       for it in res.nested_enums]))))

    result.append(
        GenTuPass(f"#define EACH_{macro_group}_ORG_RECORD(__IMPL) \\\n" + (
            " \\\n".join(["    __IMPL({}, {})".format(*it) for it in res.all_records]))))

    return result


@beartype
def gen_pyhaxorg_shared_iteration_macros(types: List[GenTuStruct]) -> List[GenTuPass]:
    return gen_iteration_macros(collect_pyhaxorg_typename_groups(types), "SHARED")


@beartype
def gen_pyhaxorg_iteration_macros(
    types: List[GenTuStruct],
    base_map: Mapping[str, GenTuStruct],
    ast: ASTBuilder,
) -> List[GenTuPass]:
    res = collect_pyhaxorg_typename_groups(types)

    result: List[GenTuPass] = gen_iteration_macros(res, "SEM")
    result.append(
        GenTuPass("#define EACH_SEM_ORG_KIND(__IMPL) \\\n" + (" \\\n".join(
            [f"    __IMPL({struct.name.name})"
             for struct in get_concrete_types(types)]))))

    result.append(
        GenTuPass("#define EACH_SEM_ORG_FINAL_TYPE_BASE(__IMPL) \\\n" + (" \\\n".join([
            f"    __IMPL({struct.name.name}, {struct.bases[0].name})"
            for struct in get_concrete_types(types)
        ]))))

    result.append(
        GenTuPass("#define EACH_SEM_ORG_TYPE_BASE(__IMPL) \\\n" + (" \\\n".join([
            f"    __IMPL({struct.name.name}, {struct.bases[0].name})" for struct in types
        ]))))

    field_groups = collect_type_field_groups(types, base_map=base_map)

    for group in field_groups.types:
        for with_base_fields in [True, False]:
            def_stack = ast.b.stack([])

            if with_base_fields:
                ast.b.add_at(
                    def_stack,
                    ast.string(
                        "#define EACH_SEM_ORG_{}_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \\".
                        format(group.name,)))

            else:
                ast.b.add_at(
                    def_stack,
                    ast.string(
                        "#define EACH_SEM_ORG_{}_FIELD_WITH_BASES(__IMPL_BASE) \\".format(
                            group.name,)))

            def impl_field(field: GenTuField):
                ast.b.add_at(
                    def_stack,
                    ast.b.line([
                        ast.string("    "),
                        ast.XCall("__IMPL_FIELD", [
                            ast.pars(ast.Type(field.type)),
                            ast.string(field.name),
                            ast.string(field.name.capitalize()),
                        ]),
                        ast.string(" \\"),
                    ]))

            if with_base_fields:
                for field in group.parent_fields:
                    impl_field(field)

            else:
                for base in group.bases:
                    ast.b.add_at(
                        def_stack,
                        ast.b.line([
                            ast.string("    "),
                            ast.XCall("__IMPL_BASE", [
                                ast.pars(ast.Type(base)),
                            ]),
                            ast.string(" \\"),
                        ]))

            for field in group.fields:
                impl_field(field)

            ast.b.add_at(def_stack, ast.string(""))


            result.append(GenTuPass(def_stack))

    return result


@beartype
def gen_pyhaxorg_wrappers(
    ast: ASTBuilder,
    pyast: pya.ASTBuilder,
    reflection_path: Path,
) -> GenFiles:
    shared_types = expand_type_groups(ast, get_shared_sem_types())
    expanded = expand_type_groups(ast, get_types())
    immutable = expand_type_groups(ast, rewrite_to_immutable(get_types()))
    proto = pb.ProtoBuilder(
        get_shared_sem_enums() + get_enums() + [get_osk_enum(expanded)] + shared_types +
        expanded, ast)
    t = ast.b

    protobuf = proto.build_protobuf()
    protobuf_writer_declarations, protobuf_writer_implementation = proto.build_protobuf_writer(
    )

    import yaml

    full_enums = get_shared_sem_enums() + get_enums() + [get_osk_enum(expanded)]
    tu: ConvTu = conv_proto_file(reflection_path)

    with open("/tmp/pyhaxorg_reflection_data.yaml", "w") as file:
        yaml.safe_dump(to_base_types(tu), stream=file)

    with open("/tmp/pyhaxorg_reflection_data.json", "w") as file:
        log(CAT).debug(f"Debug reflection data to {file.name}")
        file.write(open_proto_file(reflection_path).to_json(2))

    global org_type_names
    org_type_names = [Typ.name for Typ in expanded]

    res = Py11Module("pyhaxorg")
    add_structures(res, ast, shared_types)
    add_structures(res, ast, expanded)
    add_enums(res, ast, get_shared_sem_enums() + get_enums() + [get_osk_enum(expanded)])
    add_translation_unit(res, ast, tu)
    add_type_specializations(res, ast)
    res.Decls.append(ast.Include("pyhaxorg_manual_wrap.hpp"))

    base_map = get_base_map(expanded)

    return GenFiles([
        GenUnit(
            GenTu(
                "{root}/scripts/py_haxorg/py_haxorg/pyhaxorg.pyi",
                [GenTuPass(res.build_typedef(pyast))],
                clangFormatGuard=False,
            )),
        GenUnit(
            GenTu("{base}/sem/SemOrgProto.proto", [
                GenTuPass('syntax = "proto3";'),
                GenTuPass("package orgproto;"),
                GenTuPass('import "SemOrgProtoManual.proto";'),
                GenTuPass(protobuf),
            ])),
        GenUnit(
            GenTu(
                "{base}/sem/SemOrgSerdeDeclarations.hpp",
                [
                    GenTuPass("#ifdef ORG_DEPS_USE_PROTOBUF"),
                    GenTuPass("#pragma once"),
                    GenTuPass("#include <haxorg/sem/SemOrgSerde.hpp>"),
                    GenTuPass(ast.Macro(proto.get_any_node_field_mapping())),
                ] + [
                    GenTuPass(t.stack([ast.Any(rec), t.text("")]))
                    for rec in protobuf_writer_declarations
                ] + [
                    GenTuPass("#endif"),
                ],
            ),
            GenTu(
                "{base}/sem/SemOrgSerdeDefinitions.cpp",
                [
                    GenTuPass("#ifdef ORG_DEPS_USE_PROTOBUF"),
                    GenTuPass("#include <haxorg/sem/SemOrgSerde.hpp>"),
                    GenTuPass("#include <haxorg/sem/SemOrgSerdeDeclarations.hpp>"),
                ] + [
                    GenTuPass(t.stack([ast.Any(rec), t.text("")]))
                    for rec in protobuf_writer_implementation
                ] + [
                    GenTuPass("#endif"),
                ],
            ),
        ),
        GenUnit(
            GenTu(
                "{base}/exporters/Exporter.tcc",
                get_exporter_methods(False, shared_types) +
                get_exporter_methods(False, expanded),
            ),),
        GenUnit(
            GenTu(
                "{base}/sem/ImmOrgSerde.tcc",
                get_imm_serde(types=expanded, ast=ast),
            ),),
        GenUnit(
            GenTu(
                "{base}/exporters/ExporterMethods.tcc",
                get_exporter_methods(True, shared_types) +
                get_exporter_methods(True, expanded))),
        GenUnit(
            GenTu(
                "{root}/src/py_libs/pyhaxorg/pyhaxorg.cpp",
                [
                    GenTuPass("#undef slots"),
                    GenTuPass("#define PYBIND11_DETAILED_ERROR_MESSAGES"),
                    GenTuInclude("pybind11/pybind11.h", True),
                    GenTuInclude("haxorg/sem/SemOrg.hpp", True),
                    GenTuInclude("pybind11/stl.h", True),
                    GenTuInclude("pyhaxorg_manual_impl.hpp", False),
                    GenTuPass(res.build_bind(ast)),
                ],
            )),
        GenUnit(
            GenTu(
                "{base}/sem/SemOrgEnums.hpp",
                with_enum_reflection_api(
                    gen_pyhaxorg_shared_iteration_macros(shared_types) +
                    gen_pyhaxorg_iteration_macros(expanded, base_map=base_map, ast=ast)) +
                full_enums + ([
                    GenTuPass("""
template <>
struct std::formatter<OrgSemKind> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(OrgSemKind const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format(::hstd::enum_serde<OrgSemKind>::to_string(p), ctx);
    }
};
                    """)
                ]),
            ),
            GenTu(
                "{base}/sem/SemOrgEnums.cpp",
                [GenTuPass('#include "SemOrgEnums.hpp"')] + full_enums,
            ),
        ),
        GenUnit(
            GenTu(
                "{base}/sem/SemOrgTypes.hpp",
                [
                    GenTuPass("#pragma once"),
                    GenTuInclude("haxorg/sem/SemOrgEnums.hpp", True),
                    GenTuInclude("hstd/stdlib/Vec.hpp", True),
                    GenTuInclude("hstd/stdlib/Variant.hpp", True),
                    GenTuInclude("hstd/stdlib/Time.hpp", True),
                    GenTuInclude("hstd/stdlib/Opt.hpp", True),
                    GenTuInclude("hstd/stdlib/Str.hpp", True),
                    GenTuInclude("haxorg/parse/OrgTypes.hpp", True),
                    GenTuInclude("boost/describe.hpp", True),
                    GenTuInclude("hstd/system/macros.hpp", True),
                    GenTuInclude("haxorg/sem/SemOrgBase.hpp", True),
                    GenTuInclude("haxorg/sem/SemOrgEnums.hpp", True),
                    GenTuNamespace(n_sem(), shared_types + expanded),
                ],
            )),
        GenUnit(
            GenTu(
                "{base}/sem/ImmOrgTypes.hpp",
                [
                    GenTuPass("#pragma once"),
                    GenTuInclude("haxorg/sem/ImmOrgBase.hpp", True),
                    GenTuNamespace(n_imm(), immutable),
                ],
            )),
    ])


def gen_description_files(
    description: GenFiles,
    builder: ASTBuilder,
    t: TextLayout,
    tmp: bool,
):
    for tu in description.files:
        for i in range(2):
            if i == 1 and not tu.source:
                continue

            isHeader = i == 0
            define = tu.header if isHeader else tu.source
            if not define:
                continue

            out_root = Path("/tmp") if tmp else get_haxorg_repo_root_path()

            path = define.path.format(base=out_root.joinpath("src/haxorg"), root=out_root)

            result = builder.TranslationUnit([
                GenConverter(
                    builder,
                    isSource=not isHeader).convertTu(tu.header if isHeader else tu.source)
            ])

            directory = os.path.dirname(path)
            if not os.path.exists(directory):
                os.makedirs(directory)
                log(CAT).info(f"Created dir for {path}")

            opts = TextOptions()
            opts.rightMargin = 160
            newCode = t.toString(result, opts)

            # continue

            if os.path.exists(path):
                with open(path, "r") as f:
                    oldCode = f.read()

                if oldCode != newCode:
                    with open(path, "w") as out:
                        out.write(newCode)
                    log(CAT).info(f"[red]Updated code[/red] in {define.path}")
                else:
                    log(CAT).info(f"[green]No changes[/green] on {define.path}")
            else:
                with open(path, "w") as out:
                    out.write(newCode)
                log(CAT).info(f"[red]Wrote[/red] to {define.path}")


from py_scriptutils.toml_config_profiler import apply_options, options_from_model, get_context
import rich_click as click


class CodegenOptions(BaseModel):
    reflection_path: str
    codegen_task: Literal["pyhaxorg", "adaptagrams"]
    tmp: bool = False


def codegen_options(f):
    return apply_options(f, options_from_model(CodegenOptions))


@click.command()
@codegen_options
@click.pass_context
def impl(ctx: click.Context, config: Optional[str] = None, **kwargs):
    opts: CodegenOptions = get_context(ctx, CodegenOptions, config=config, kwargs=kwargs)

    impl = None
    match opts.codegen_task:
        case "adaptagrams":
            impl = gen_adaptagrams_wrappers

        case "pyhaxorg":
            impl = gen_pyhaxorg_wrappers

    t = TextLayout()
    builder = ASTBuilder(t)
    pyast = pya.ASTBuilder(t)
    description: GenFiles = impl(
        builder,
        pyast,
        reflection_path=Path(opts.reflection_path),
    )

    gen_description_files(
        description=description,
        builder=builder,
        t=t,
        tmp=opts.tmp,
    )


if __name__ == "__main__":
    impl()
