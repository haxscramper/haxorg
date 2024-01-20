#!/usr/bin/env python

from dataclasses import dataclass, field, replace
import itertools
from typing import *

import py_codegen.astbuilder_py as pya
from py_codegen.org_codegen_data import *
from py_textlayout.py_textlayout_wrap import TextLayout, TextOptions
from py_codegen.refl_read import conv_proto_file, ConvTu, open_proto_file
from py_scriptutils.script_logging import log
from py_codegen.astbuilder_pybind11 import (
    Py11Method,
    Py11Module,
    Py11Field,
    Py11Class,
    Py11BindPass,
    Py11Enum,
    flat_scope,
    id_self,
    py_type_bind,
)

if TYPE_CHECKING:
    from py_textlayout.py_textlayout_wrap import BlockId

else:
    BlockId = NewType('BlockId', int)


def with_enum_reflection_api(body: List[Any]) -> List[Any]:
    return [
        GenTuPass("#pragma once"),
        GenTuPass("#include <hstd/system/basic_templates.hpp>"),
        GenTuPass("#include <hstd/system/reflection.hpp>"),
        GenTuPass("#include <hstd/stdlib/Opt.hpp>"),
    ] + body


def iterate_object_tree(tree, callback, context: List[Any]):
    callback(tree)
    context.append(tree)

    if isinstance(tree, list):
        for it in tree:
            iterate_object_tree(it, callback, context)

    elif isinstance(tree, dict):
        for key, value in tree.items():
            iterate_object_tree(value, callback, context)

    # Primitive types cannot be walked over, end iteration
    elif (tree is True or tree is False or tree is None or isinstance(tree, str) or
          isinstance(tree, type) or isinstance(tree, int)):
        pass

    elif isinstance(tree, object):
        # If any object -- walk all slots (attributes)
        for slot, value in vars(tree).items():
            iterate_object_tree(value, callback, context)

    # Walk over every item in list
    # Otherwise, print the value -- if something is missing it will be added later
    else:
        print(f"? {tree}")

    context.pop()


def get_type_base_fields(value: GenTuStruct,
                         base_map: Mapping[str, GenTuStruct]) -> List[GenTuField]:
    fields = []
    for base_sym in value.bases:
        base = base_map.get(base_sym.name)
        if base:
            fields.extend(base.fields)
            fields.extend(get_type_base_fields(base, base_map))

    return fields


@beartype
def get_base_map(expanded: List[GenTuStruct]) -> Mapping[str, GenTuStruct]:
    base_map: Mapping[str, GenTuStruct] = {}

    def callback(obj):
        if isinstance(obj, GenTuStruct):
            base_map[obj.name.name] = obj

    context = []
    iterate_object_tree(expanded, callback, context)
    base_map["Org"] = GenTuStruct(
        QualType.ForName("Org"),
        GenTuDoc(""),
        [
            GenTuField(QualType.ForName("OrgSemPlacement"), "placementContext",
                       GenTuDoc("")),
            GenTuField(t_vec(t_id()), "subnodes", GenTuDoc("")),
        ],
    )

    return base_map


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
                if not (field.isStatic)
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

            if len(scope_full) == 0:
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
                    impl=None if forward else "__visit_specific_kind(res, object);\n%s" %
                    "\n".join([f"__org_field(res, object, {a.name});" for a in fields]),
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

    iterate_object_tree(expanded, callback, iterate_tree_context)
    return methods


@beartype
def get_concrete_types(expanded: List[GenTuStruct]) -> Sequence[GenTuStruct]:
    return [struct for struct in expanded if struct.concreteKind]


org_type_names: List[str] = []

from copy import deepcopy


@beartype
def in_sem(typ: QualType) -> QualType:
    typ = deepcopy(typ)
    if typ.name in ["SemId", "SemIdT", "Param"] + org_type_names:
        typ.Spaces.insert(0, QualType.ForName("sem"))

    typ.Parameters = [in_sem(P) for P in typ.Parameters]

    return typ


@beartype
def pybind_org_id(ast: ASTBuilder, b: TextLayout, typ: GenTuStruct,
                  base_map: Mapping[str, GenTuStruct]) -> Py11Class:
    base_type = QualType.ForName(typ.name.name, Spaces=[QualType.ForName("sem")])
    id_type = QualType.ForName("SemIdT",
                               Parameters=[base_type],
                               Spaces=[QualType.ForName("sem")])
    res = Py11Class(PyName="Sem" + typ.name.name, Class=id_type, PyBases=typ.bases)

    res.AddInit([], [ast.Return(ast.CallStatic(id_type, "Nil"))])
    res.Bases.append(QualType.ForName("SemId", Spaces=[QualType.ForName("sem")]))

    _self = id_self(id_type)

    def map_obj_fields(Record: GenTuStruct):
        for _field in Record.fields:
            if _field.isStatic or hasattr(_field, "ignore"):
                continue

            res.Fields.append(
                Py11Field.FromGenTu(
                    _field,
                    GetImpl=[b.text(f"return {_self.name}->{_field.name};")],
                    SetImpl=[b.text(f"{_self.name}->{_field.name} = {_field.name};")]))

    def map_obj_methods(Record: GenTuStruct):
        for meth in Record.methods:
            if meth.isStatic or meth.isPureVirtual or meth.name in ["getKind"]:
                continue

            passcall = ast.XCallPtr(b.text(_self.name), meth.name,
                                    [b.text(arg.name) for arg in meth.arguments])
            if meth.result and meth.result != "void":
                passcall = ast.Return(passcall)

            res.Methods.append(Py11Method.FromGenTu(meth, Body=[passcall]))

    def map_bases(Record: GenTuStruct):
        for base in Record.bases:
            if base.name != "Org":
                map_obj_fields(base_map[base.name])
                map_obj_methods(base_map[base.name])
                map_bases(base_map[base.name])

    map_obj_fields(typ)
    map_obj_methods(typ)
    map_bases(typ)

    return res


@beartype
def pybind_nested_type(value: GenTuStruct, scope: List[QualType]) -> Py11Class:
    name = "".join([typ.name for typ in scope if typ.name != "sem"] + [value.name.name])

    res = Py11Class(PyName=name, Class=QualType.ForName(value.name.name, Spaces=scope))
    res.InitDefault()

    for meth in value.methods:
        if meth.isStatic or meth.isPureVirtual:
            continue

        res.Methods.append(Py11Method.FromGenTu(meth))

    for _field in value.fields:
        if _field.isStatic or hasattr(_field, "ignore"):
            continue

        res.Fields.append(Py11Field.FromGenTu(_field))

    return res


@beartype
def filter_walk_scope(iterate_context) -> List[QualType]:
    scope: List[QualType] = []

    for s in iterate_context:
        match s:
            case GenTuStruct():
                scope.append(s.name)

            case GenTuNamespace():
                scope.append(QualType.ForName(s.name))

    return scope


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
def get_bind_methods(ast: ASTBuilder, expanded: List[GenTuStruct]) -> Py11Module:
    res = Py11Module("pyhaxorg")
    b: TextLayout = ast.b

    iterate_context: List[Any] = []

    res.Before.append(
        ast.PPIfStmt(
            PPIfStmtParams([
                ast.PPIfNDef("IN_CLANGD_PROCESSING", [
                    ast.Define("PY_HAXORG_COMPILING"),
                    ast.Include("pyhaxorg_manual_impl.hpp")
                ])
            ])))

    res.Decls.append(
        Py11BindPass(
            ast.PPIfStmt(
                PPIfStmtParams([
                    ast.PPIfNDef("IN_CLANGD_PROCESSING", [
                        ast.Define("PY_HAXORG_COMPILING"),
                        ast.Include("pyhaxorg_manual_wrap.hpp")
                    ])
                ]))))

    base_map: dict[str, GenTuStruct] = {}

    def baseCollectorCallback(value: Any) -> None:
        if isinstance(value, GenTuStruct):
            base_map[value.name.name] = value

    iterate_object_tree(GenTuNamespace("sem", expanded), baseCollectorCallback,
                        iterate_context)

    iterate_context = []

    def codegenConstructCallback(value: Any) -> None:
        nonlocal iterate_context
        scope: List[QualType] = filter_walk_scope(iterate_context)

        if isinstance(value, GenTuStruct):
            if hasattr(value, "isOrgType"):
                res.Decls.append(pybind_org_id(ast, b, value, base_map))

            else:
                new = pybind_nested_type(value, scope)
                res.Decls.append(new)

        elif isinstance(value, GenTuEnum):
            PyName = "".join([
                N for N in flat_scope(QualType.ForName(value.name.name, Spaces=scope))
                if N != "sem"
            ])
            res.Decls.append(Py11Enum.FromGenTu(value, scope, pyNameOverride=PyName))

    iterate_object_tree(GenTuNamespace("sem", expanded), codegenConstructCallback,
                        iterate_context)

    for item in get_enums() + [get_osk_enum(expanded)]:
        res.Decls.append(Py11Enum.FromGenTu(item, []))

    return res


@beartype
def expand_type_groups(ast: ASTBuilder, types: List[GenTuStruct]) -> List[GenTuStruct]:

    @beartype
    def rec_expand_group(
        record: GenTuTypeGroup,
        context: List[QualType],
    ) -> List[Union[GenTuStruct, GenTuEnum, GenTuField, GenTuFunction, GenTuPass]]:
        result = []
        for item in record.types:
            result.append(rec_expand_type(item, context))

        typeNames: List[QualType] = []

        for item in record.types:
            if item.concreteKind:
                typeNames.append(item.name)

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
            result.append(
                GenTuPass(
                    ast.Using(
                        UsingParams(newName=record.variantName,
                                    baseType=QualType(name="variant",
                                                      Spaces=[QualType.ForName("std")],
                                                      Parameters=typeNames)))))

            result.append(
                GenTuEnum(
                    name=QualType.ForName(record.enumName),
                    doc=GenTuDoc(""),
                    fields=[GenTuEnumField(N.name, GenTuDoc("")) for N in typeNames]))

            for idx, T in enumerate(typeNames):
                for isConst in [True, False]:
                    result.append(
                        GenTuFunction(
                            doc=GenTuDoc(""),
                            name="get" + (T.name[0].upper() + T.name[1:]),
                            result=T.model_copy(update=dict(RefKind=ReferenceKind.LValue,
                                                            isConst=isConst,
                                                            Spaces=context)),
                            isConst=isConst,
                            impl=ast.Return(
                                ast.XCall("std::get", [ast.string(record.variantField)],
                                          Params=[QualType.ForName(str(idx))]))))

            enum_type = QualType.ForName(record.enumName, Spaces=context)
            variant_type = QualType.ForName(record.variantName, Spaces=context)

            result.append(
                GenTuFunction(isStatic=True,
                              doc=GenTuDoc(""),
                              name=record.kindGetter,
                              result=enum_type,
                              arguments=[GenTuIdent(t_cr(variant_type), "__input")],
                              impl=ast.Return(
                                  ast.XCall(
                                      "static_cast",
                                      args=[ast.XCallRef(ast.string("__input"), "index")],
                                      Params=[enum_type]))))

            result.append(
                GenTuFunction(name=record.kindGetter,
                              result=enum_type,
                              impl=ast.Return(
                                  ast.XCall(record.kindGetter,
                                            [ast.string(record.variantField)])),
                              doc=GenTuDoc(""),
                              isConst=True))

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
                value=ast.string(record.variantValue) if record.variantValue else None)

            setattr(variant_field, "isVariantField", True)
            setattr(variant_field, "variantGetter", record.kindGetter)

            result.append(variant_field)

        return result

    @beartype
    def rec_expand_type(typ: GenTuStruct, context: List[QualType]) -> GenTuStruct:
        converted = []
        methods: List[GenTuFunction] = []
        fields: List[GenTuField] = []
        for item in typ.nested:
            if isinstance(item, GenTuStruct):
                converted.append(rec_expand_type(item, context + [item.name]))

            elif isinstance(item, GenTuTypeGroup):
                for res in rec_expand_group(item, context):
                    if isinstance(res, GenTuField):
                        fields.append(res)

                    elif isinstance(res, GenTuFunction):
                        methods.append(res)

                    else:
                        converted.append(res)

            elif isinstance(item, GenTuPass) or isinstance(item, GenTuEnum):
                converted.append(item)

            else:
                assert False, type(item)

        result = replace(typ,
                         nested=converted,
                         methods=typ.methods + methods,
                         fields=typ.fields + fields)

        if hasattr(typ, "isNested"):
            setattr(result, "isNested", getattr(typ, "isNested"))

        if hasattr(typ, "isOrgType"):
            setattr(result, "isOrgType", getattr(typ, "isOrgType"))

        return result

    return [rec_expand_type(T, [QualType.ForName("sem"), T.name]) for T in types]


@beartype
def update_namespace_annotations(expanded: List[GenTuStruct]):
    iterate_context: Sequence[GenTuStruct] = []

    def callback(value):
        nonlocal iterate_context
        if isinstance(value, QualType):
            if "isNested" in value.meta:
                value.Spaces = filter_walk_scope(iterate_context) + value.Spaces

    iterate_object_tree(GenTuNamespace("sem", expanded), callback, iterate_context)


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
def build_protobuf_writer(expanded: List[GenTuStruct],
                          ast: ASTBuilder) -> List[FunctionParams]:
    t = ast.b
    base_map = get_base_map(expanded)

    def aux_item(it: GenTuUnion) -> FunctionParams:
        match it:
            case GenTuStruct():
                out = t.text("out")
                _in = t.text("in")
                Body: List[BlockId] = []
                for field in get_type_base_fields(it, base_map) + it.fields:
                    opc = "add_" + field.name
                    Body.append(
                        ast.XCall(
                            "protobuf_write",
                            [ast.XCallPtr(out, opc),
                             ast.Dot(_in, t.text(field.name))],
                            Params=[field.type],
                            Stmt=True,
                        ))

                return FunctionParams(
                    Name="protobuf_write",
                    Args=[
                        ParmVarParams(name="in",
                                      type=it.name.withExtraSpace(
                                          QualType(name="sem")).asConstRef()),
                        ParmVarParams(name="out", type=it.name.asPtr())
                    ],
                    Template=TemplateParams(Stacks=[TemplateGroup(Params=[])]),
                    doc=DocParams(""),
                    Body=Body)

    return list(
        itertools.filterfalse(lambda it: not it, [aux_item(it) for it in get_enums()] +
                              [aux_item(it) for it in expanded]))


@beartype
def build_protobuf(expanded: List[GenTuStruct], t: TextLayout) -> BlockId:
    base_map = get_base_map(expanded)

    def braced(name: str, content: Iterable[BlockId]) -> BlockId:
        return t.stack([
            t.text(f"{name} {{"),
            t.indent(2, t.stack(list(content))),
            t.text("}"),
            t.text(""),
        ])

    def aux_type(it: QualType) -> str:
        match it.name:
            case "Vec":
                return "repeated " + aux_type(it.Parameters[0])

            case "Str":
                return "string"

            case "Opt":
                if it.Parameters[0].name == "Vec":
                    return aux_type(it.Parameters[0])

                else:
                    return "optional " + aux_type(it.Parameters[0])

            case "SemId":
                return "AnyNode"

            case "SemIdT":
                return aux_type(it.Parameters[0])

            case _:
                return it.name

    def aux_field(it: GenTuField, idx: int) -> BlockId:
        return t.text(f"{aux_type(it.type):<32} {it.name:<32} = {idx};")

    def aux_enum(it: GenTuEnumField, idx: int) -> BlockId:
        return t.text(f"{it.name:<32} = {idx};")

    def aux_item(it: GenTuUnion | GenTuField) -> BlockId:
        match it:
            case GenTuStruct():
                return braced(
                    "message " + it.name.name,
                    itertools.chain(
                        [aux_item(sub) for sub in it.nested],
                        [
                            aux_field(sub, idx) for idx, sub in enumerate(
                                get_type_base_fields(it, base_map) + it.fields)
                        ],
                    ))

            case GenTuEnum():
                return braced("enum " + it.name.name,
                              [aux_enum(sub, idx) for idx, sub in enumerate(it.fields)])

            case GenTuPass():
                return t.text("")

            case _:
                assert False, type(it)

    declared_types = [aux_item(it) for it in expanded]

    return t.stack([aux_item(it) for it in get_enums()] + declared_types)


@beartype
def gen_value(ast: ASTBuilder, pyast: pya.ASTBuilder, reflection_path: str) -> GenFiles:
    expanded = expand_type_groups(ast, get_types())
    update_namespace_annotations(expanded)

    protobuf = build_protobuf(expanded, ast.b)
    with open("/tmp/result.proto", "w") as file:
        file.write(ast.b.toString(protobuf, TextOptions()))

    protobuf_writer = build_protobuf_writer(expanded, ast)
    with open("/tmp/result.cpp", "w") as file:
        for item in protobuf_writer:
            if item:
                file.write(ast.b.toString(ast.Function(item), TextOptions()))
                file.write("\n\n")

    import yaml

    full_enums = get_enums() + [get_osk_enum(expanded)]
    tu: ConvTu = conv_proto_file(reflection_path)

    with open("/tmp/reflection_data.yaml", "w") as file:
        yaml.safe_dump(to_base_types(tu), stream=file)

    with open("/tmp/reflection_data.json", "w") as file:
        file.write(open_proto_file(reflection_path).to_json(2))

    global org_type_names
    org_type_names = [Typ.name for Typ in expanded]

    autogen_structs = get_bind_methods(ast, expanded)

    for _struct in tu.structs:
        autogen_structs.Decls.append(pybind_nested_type(_struct, []))

    for _enum in tu.enums:
        autogen_structs.Decls.append(Py11Enum.FromGenTu(_enum, []))

    opaque_declarations: List[BlockId] = []
    specialization_calls: List[BlockId] = []

    type_use_context: List[Any] = []
    seen_types: Set[QualType] = set()

    def record_specializations(value: Any):
        nonlocal type_use_context
        if isinstance(value, QualType):

            def rec_type(T: QualType):

                def rec_drop(T: QualType) -> QualType:
                    return T.model_copy(
                        update=dict(isConst=False,
                                    RefKind=ReferenceKind.NotRef,
                                    ptrCount=0,
                                    isNamespace=False,
                                    meta=dict(),
                                    Spaces=[rec_drop(S) for S in T.Spaces],
                                    Parameters=[rec_drop(P) for P in T.Parameters]))

                T = rec_drop(T)

                if T in seen_types:
                    return

                else:
                    seen_types.add(T)

                if T.name == "Vec":
                    stdvec_t = QualType.ForName("vector",
                                                Spaces=[QualType.ForName("std")],
                                                Parameters=[T.Parameters[0]])
                    opaque_declarations.append(
                        ast.XCall("PYBIND11_MAKE_OPAQUE", [ast.Type(stdvec_t)]))
                    opaque_declarations.append(
                        ast.XCall("PYBIND11_MAKE_OPAQUE", [ast.Type(T)]))

                    specialization_calls.append(
                        ast.XCall(
                            "bind_vector",
                            [ast.string("m"),
                             ast.StringLiteral(py_type_bind(T).Name)],
                            Params=[T.Parameters[0]],
                            Stmt=True))

                else:
                    for P in T.Parameters:
                        rec_type(P)

            rec_type(value)

    iterate_object_tree(autogen_structs, record_specializations, type_use_context)

    for decl in opaque_declarations:
        autogen_structs.Before.append(decl)

    autogen_structs.Decls = [Py11BindPass(D) for D in specialization_calls
                            ] + autogen_structs.Decls

    return GenFiles([
        GenUnit(
            GenTu(
                # "{root}/scripts/py_haxorg/py_haxorg/pyhaxorg.pyi",
                "/tmp/pyhaxorg.pyi",
                [GenTuPass(autogen_structs.build_typedef(pyast))],
            )),
        # GenUnit(GenTu("{base}/sem/SemOrg.proto", [GenTuPass(protobuf)])),
        GenUnit(
            GenTu("{base}/exporters/Exporter.tcc", get_exporter_methods(False,
                                                                        expanded))),
        GenUnit(
            GenTu("{base}/exporters/ExporterMethods.tcc",
                  get_exporter_methods(True, expanded))),
        GenUnit(
            GenTu(
                "{base}/py_libs/pyhaxorg/pyhaxorg.cpp",
                # "/tmp/pyhaxorg.cpp",
                [
                    GenTuPass("#undef slots"),
                    GenTuInclude("pybind11/pybind11.h", True),
                    GenTuInclude("sem/SemOrg.hpp", True),
                    GenTuInclude("pybind11/stl.h", True),
                    GenTuPass(autogen_structs.build_bind(ast)),
                ],
            )),
        GenUnit(
            GenTu(
                "{base}/sem/SemOrgEnums.hpp",
                with_enum_reflection_api([
                    GenTuPass("#define EACH_SEM_ORG_KIND(__IMPL) \\\n" + (" \\\n".join([
                        f"    __IMPL({struct.name.name})"
                        for struct in get_concrete_types(expanded)
                    ])))
                ]) + full_enums + ([
                    GenTuPass("""
template <>
struct std::formatter<OrgSemKind> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(OrgSemKind const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format(enum_serde<OrgSemKind>::to_string(p), ctx);
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
                    GenTuInclude("sem/SemOrgEnums.hpp", True),
                    GenTuInclude("hstd/stdlib/Vec.hpp", True),
                    GenTuInclude("hstd/stdlib/Variant.hpp", True),
                    GenTuInclude("hstd/stdlib/Time.hpp", True),
                    GenTuInclude("hstd/stdlib/Opt.hpp", True),
                    GenTuInclude("hstd/stdlib/Str.hpp", True),
                    GenTuInclude("parse/OrgTypes.hpp", True),
                    GenTuInclude("boost/describe.hpp", True),
                    GenTuInclude("hstd/system/macros.hpp", True),
                    GenTuInclude("functional", True),
                    GenTuInclude("sem/SemOrgBase.hpp", True),
                    GenTuInclude("sem/SemOrgEnums.hpp", True),
                    GenTuNamespace("sem", [GenTuTypeGroup(expanded, enumName="")]),
                ],
            )),
    ])


if __name__ == "__main__":
    import os
    import sys
    from pprint import pprint

    t = TextLayout()
    builder = ASTBuilder(t)
    pyast = pya.ASTBuilder(t)
    description: GenFiles = gen_value(builder,
                                      pyast,
                                      reflection_path=os.path.join(
                                          sys.argv[1], "reflection.pb"))
    trace_file = open("/tmp/trace.txt", "w")
    indent = 0

    for tu in description.files:
        for i in range(2):
            if i == 1 and not tu.source:
                continue

            isHeader = i == 0
            define = tu.header if isHeader else tu.source
            if not define:
                continue

            path = define.path.format(base=os.path.join(sys.argv[2], "src"),
                                      root=sys.argv[2])
            result = builder.TranslationUnit([
                GenConverter(
                    builder,
                    isSource=not isHeader).convertTu(tu.header if isHeader else tu.source)
            ])

            directory = os.path.dirname(path)
            if not os.path.exists(directory):
                os.makedirs(directory)
                log().info(f"Created dir for {path}")

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
                    log().info(f"[red]Updated code[/red] in {define.path}")
                else:
                    log().info(f"[green]No changes[/green] on {define.path}")
            else:
                with open(path, "w") as out:
                    out.write(newCode)
                log().info(f"[red]Wrote[/red] to {define.path}")
