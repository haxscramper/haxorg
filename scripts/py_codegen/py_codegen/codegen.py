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

    iterate_object_tree(expanded, iterate_tree_context, pre_visit=callback)
    return methods


@beartype
def get_concrete_types(expanded: List[GenTuStruct]) -> Sequence[GenTuStruct]:
    return [struct for struct in expanded if struct.concreteKind]


org_type_names: List[str] = []

from copy import deepcopy, copy


@beartype
def in_sem(typ: QualType) -> QualType:
    typ = deepcopy(typ)
    if typ.name in ["SemId", "Param"] + org_type_names:
        typ.Spaces.insert(0, QualType.ForName("sem"))

    typ.Parameters = [in_sem(P) for P in typ.Parameters]

    return typ


def filter_init_fields(Fields: List[Py11Field]) -> List[Py11Field]:
    return [F for F in Fields if F.Type.name not in ["SemId"]]


@beartype
def pybind_org_id(ast: ASTBuilder, b: TextLayout, typ: GenTuStruct,
                  base_map: Mapping[str, GenTuStruct]) -> Py11Class:
    base_type = QualType.ForName(typ.name.name, Spaces=[QualType.ForName("sem")])
    id_type = QualType.ForName(
        "SemId",
        Parameters=[base_type],
        Spaces=[QualType.ForName("sem")],
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
            if _field.isStatic or hasattr(_field, "ignore"):
                continue

            res.Fields.append(Py11Field.FromGenTu(_field))

    def map_obj_methods(Record: GenTuStruct):
        for meth in Record.methods:
            if meth.isStatic or meth.isPureVirtual or (meth.name == "getKind" and
                                                       Record.name.name != "Org"):
                continue

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
                if not field.isStatic:
                    rec_fields.append(Py11Field.FromGenTu(field))

            for base in it.bases:
                cb(base_map[base.name])

        cb(typ)

        res.InitDefault(ast=ast, Fields=filter_init_fields(rec_fields))

    return res


@beartype
def pybind_nested_type(ast: ASTBuilder, value: GenTuStruct) -> Py11Class:
    res = Py11Class(
        PyName=py_type(value.name).Name,
        Class=value.name,
        Bases=value.bases,
    )

    for meth in value.methods:
        if meth.isStatic or meth.isPureVirtual:
            continue

        res.Methods.append(Py11Method.FromGenTu(meth))

    for _field in value.fields:
        if _field.isStatic or hasattr(_field, "ignore"):
            continue

        res.Fields.append(Py11Field.FromGenTu(_field))

    if not value.IsAbstract:
        res.InitDefault(ast, filter_init_fields(res.Fields))

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
def get_bind_methods(ast: ASTBuilder, expanded: List[GenTuStruct]) -> Py11Module:
    res = Py11Module("pyhaxorg")
    b: TextLayout = ast.b

    res.Before.append(ast.Include("pyhaxorg_manual_impl.hpp"))
    res.Decls.append(ast.Include("pyhaxorg_manual_wrap.hpp"))

    base_map = get_base_map(expanded)

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
        GenTuNamespace("sem", expanded),
        [],
        post_visit=codegenConstructCallback,
    )

    for item in get_enums() + [get_osk_enum(expanded)]:
        wrap = Py11Enum.FromGenTu(item, py_type(item.name).Name)
        res.Decls.append(wrap)

    return res


@beartype
def expand_type_groups(ast: ASTBuilder, types: List[GenTuStruct]) -> List[GenTuStruct]:

    @beartype
    def rec_expand_group(
        record: GenTuTypeGroup,
        context: List[QualType],
    ) -> List[GenTuEntry | GenTuField]:
        result = []
        typeNames: List[QualType] = []

        for item in record.types:
            expanded = rec_expand_type(item, context)
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
            enum_type = QualType.ForName(record.enumName, Spaces=context)
            variant_type = QualType.ForName(record.variantName, Spaces=context)
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
                for isConst in [True, False]:
                    result.append(
                        GenTuFunction(
                            doc=GenTuDoc(""),
                            name="get" + (T.name[0].upper() + T.name[1:]),
                            result=T.model_copy(update=dict(
                                RefKind=ReferenceKind.LValue,
                                isConst=isConst,
                                Spaces=context,
                            )),
                            isConst=isConst,
                            impl=ast.Return(
                                ast.XCall(
                                    "std::get",
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
    def rec_expand_type(typ: GenTuStruct, context: List[QualType]) -> GenTuStruct:
        converted = []
        methods: List[GenTuFunction] = []
        fields: List[GenTuField] = []
        for item in typ.nested:
            match item:
                case GenTuStruct():
                    converted.append(rec_expand_type(item, context + [typ.name]))

                case GenTuTypeGroup():
                    for res in rec_expand_group(item, context + [typ.name]):
                        if isinstance(res, GenTuField):
                            fields.append(res)

                        elif isinstance(res, GenTuFunction):
                            methods.append(res)

                        else:
                            converted.append(res)

                case GenTuEnum():
                    converted.append(
                        replace(item,
                                name=item.name.model_copy(update=dict(Spaces=context +
                                                                      [typ.name]))))

                case GenTuPass():
                    converted.append(item)

                case _:
                    assert False, type(item)

        result = replace(
            typ,
            name=typ.name.model_copy(update=dict(Spaces=context)),
            nested=converted,
            methods=typ.methods + methods,
            fields=typ.fields + fields,
        )

        if hasattr(typ, "isOrgType"):
            setattr(result, "isOrgType", getattr(typ, "isOrgType"))

        return result

    return [rec_expand_type(T, [QualType.ForName("sem")]) for T in types]


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
def gen_pybind11_wrappers(ast: ASTBuilder, expanded: List[GenTuStruct],
                          tu: ConvTu) -> Py11Module:
    autogen_structs = get_bind_methods(ast, expanded)

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

            autogen_structs.Decls.insert(0, org_decl)

        elif _struct.name.name == "LineCol":
            autogen_structs.Decls.insert(0, pybind_nested_type(ast, _struct))

        else:
            autogen_structs.Decls.append(pybind_nested_type(ast, _struct))

    for _enum in tu.enums:
        autogen_structs.Decls.append(Py11Enum.FromGenTu(_enum, py_type(_enum.name).Name))

    for _func in tu.functions:
        autogen_structs.Decls.append(Py11Function.FromGenTu(_func))

    opaque_declarations: List[BlockId] = []
    specialization_calls: List[BlockId] = []

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

                    specialization_calls.append(
                        ast.XCall(
                            f"bind_{std_type}",
                            [
                                ast.string("m"),
                                ast.StringLiteral(py_type_bind(T).Name),
                            ],
                            Params=T.Parameters,
                            Stmt=True,
                        ))

                else:
                    for P in T.Parameters:
                        rec_type(P)

            rec_type(value)

    iterate_object_tree(
        autogen_structs,
        type_use_context,
        pre_visit=record_specializations,
    )

    for decl in opaque_declarations:
        autogen_structs.Before.append(decl)

    autogen_structs.Decls = [Py11BindPass(D) for D in specialization_calls
                            ] + autogen_structs.Decls

    return autogen_structs


@beartype
@dataclass
class QmlWrap():
    wrapped: List[GenTuEntry]
    toplevel: List[GenTuEntry]
    implementation: List[GenTuEntry]


@beartype
def gen_qml_wrap(ast: ASTBuilder, expanded: List[GenTuStruct], tu: ConvTu) -> QmlWrap:
    qml_wrapped: List[GenTuEntry] = []
    qml_toplevel: List[GenTuEntry] = []

    def qml_type(typ: QualType) -> QualType:
        if typ.name == "Str" or typ.name == "string":
            return QualType.ForName("QString")

        elif typ.name == "SemId":
            return typ.par0().withChangedSpace("org_qml")

        else:
            return typ

    def gen_qml_wrap_struct(struct: GenTuStruct) -> GenTuStruct:
        result = GenTuStruct(
            name=struct.name.withoutSpace("sem").withExtraSpace("org_qml"),
            GenDescribe=False,
            bases=[b.withoutSpace("sem") for b in struct.bases],
        )

        result.nested.append(GenTuPass("Q_GADGET"))
        result.nested.append(GenTuPass("public:"))
        qml_toplevel.append(
            GenTuPass(ast.Call(
                ast.string("Q_DECLARE_METATYPE"),
                [ast.Type(result.name)],
            )))

        BASE_NODE_FIELD = "__data"

        if hasattr(struct, "isOrgType"):
            pass

        else:
            result.fields.append(
                GenTuField(
                    type=struct.name.withGlobalSpace(),
                    name=BASE_NODE_FIELD,
                ))

        def capitalize_first(s: str) -> str:
            return s[0].upper() + s[1:] if s else ""

        if hasattr(struct, "isOrgType"):
            result.nested.append(GenTuPass(
                ast.string(f"{struct.name.name}() = default;")))

            result.nested.append(
                GenTuPass(
                    ast.string(
                        "{name}(sem::SemId<sem::Org> const& id) : {base}(id) {{}}".format(
                            name=struct.name.name,
                            base=struct.bases[0].name,
                        ))))

        for field in struct.fields:
            if field.isStatic:
                continue

            elif field.type.name in [
                    "Opt",
                    "Vec",
                    "vector",
                    "optional",
                    "Org",
                    "UnorderedMap",
            ]:
                continue

            else:
                result.nested.append(
                    GenTuPass(
                        ast.b.join([
                            ast.string("Q_PROPERTY("),
                            ast.Type(qml_type(field.type)),
                            ast.string(field.name),
                            ast.string("READ"),
                            ast.string("get" + capitalize_first(field.name)),
                            ast.string("WRITE"),
                            ast.string("set" + capitalize_first(field.name)),
                            ast.string(")"),
                        ], ast.b.text(" "))))

                if hasattr(struct, "isOrgType"):
                    field_access = ast.string(
                        f"{BASE_NODE_FIELD}.getAs<sem::{struct.name.name}>()->{field.name}"
                    )

                else:
                    field_access = ast.string(f"{BASE_NODE_FIELD}.{field.name}")

                serde_type = QualType(
                    name="serde",
                    Spaces=[QualType.ForName("org_qml")],
                    Parameters=[qml_type(field.type), field.type],
                )

                result.methods.append(
                    GenTuFunction(
                        result=qml_type(field.type),
                        name="get" + capitalize_first(field.name),
                        impl=ast.Return(
                            ast.CallStatic(
                                serde_type,
                                opc="cxx_to_qml",
                                Args=[field_access],
                            )),
                    ))

                result.methods.append(
                    GenTuFunction(
                        result=QualType.ForName("void"),
                        name="set" + capitalize_first(field.name),
                        arguments=[
                            GenTuIdent(
                                type=qml_type(field.type),
                                name=field.name,
                            )
                        ],
                        impl=ast.b.line([
                            field_access,
                            ast.string(" = "),
                            ast.CallStatic(
                                serde_type,
                                opc="qml_to_cxx",
                                Args=[ast.string(field.name)],
                            ),
                            ast.string(";"),
                        ]),
                    ))

        return result

    for item in tu.structs:
        if item.name.name in ["LineCol"]:
            qml_wrapped.append(gen_qml_wrap_struct(item))

    for item in expanded:
        qml_wrapped.append(gen_qml_wrap_struct(item))

    qml_implementation: List[GenTuEntry] = []
    gen = GenConverter(ast)
    for item in qml_wrapped:
        match item:
            case GenTuStruct():
                for meth in item.methods:
                    declaration: MethodDeclParams = gen.convertMethod(meth)
                    meth.impl = None
                    qml_implementation.append(
                        GenTuPass(ast.MethodDef(declaration.asMethodDef(item.name))))

    return QmlWrap(
        wrapped=qml_wrapped,
        toplevel=qml_toplevel,
        implementation=qml_implementation,
    )


@beartype
def gen_value(ast: ASTBuilder, pyast: pya.ASTBuilder, reflection_path: str) -> GenFiles:
    expanded = expand_type_groups(ast, get_types())
    proto = pb.ProtoBuilder(get_enums() + [get_osk_enum(expanded)] + expanded, ast)

    protobuf = proto.build_protobuf()
    protobuf_writer_declarations, protobuf_writer_implementation = proto.build_protobuf_writer(
    )

    import yaml

    full_enums = get_enums() + [get_osk_enum(expanded)]
    tu: ConvTu = conv_proto_file(reflection_path)

    with open("/tmp/reflection_data.yaml", "w") as file:
        yaml.safe_dump(to_base_types(tu), stream=file)

    with open("/tmp/reflection_data.json", "w") as file:
        file.write(open_proto_file(reflection_path).to_json(2))

    global org_type_names
    org_type_names = [Typ.name for Typ in expanded]

    autogen_structs = gen_pybind11_wrappers(ast, expanded, tu)
    qml = gen_qml_wrap(ast, expanded, tu)

    return GenFiles([
        GenUnit(
            GenTu(
                "{root}/scripts/py_haxorg/py_haxorg/pyhaxorg.pyi",
                [GenTuPass(autogen_structs.build_typedef(pyast))],
            )),
        GenUnit(
            GenTu(
                "{root}/src/editor/gui_lib/org_qml.hpp",
                [
                    GenTuPass("#pragma once"),
                    GenTuPass("#include \"org_qml_manual.hpp\""),
                    GenTuNamespace("org_qml", qml.wrapped),
                ] + qml.toplevel,
            ),
            GenTu(
                "{root}/src/editor/gui_lib/org_qml.cpp",
                [
                    GenTuPass("#include \"org_qml_manual2.hpp\""),
                ] + qml.implementation,
            ),
        ),
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
                    GenTuPass("#pragma once"),
                    GenTuPass("#include <sem/SemOrgSerde.hpp>"),
                    GenTuPass(ast.Macro(proto.get_any_node_field_mapping())),
                ] + [
                    GenTuPass(t.stack([ast.Any(rec), t.text("")]))
                    for rec in protobuf_writer_declarations
                ],
            ),
            GenTu(
                "{base}/sem/SemOrgSerdeDefinitions.cpp",
                [
                    GenTuPass("#include <sem/SemOrgSerde.hpp>"),
                    GenTuPass("#include <sem/SemOrgSerdeDeclarations.hpp>"),
                ] + [
                    GenTuPass(t.stack([ast.Any(rec), t.text("")]))
                    for rec in protobuf_writer_implementation
                ],
            ),
        ),
        GenUnit(
            GenTu(
                "{base}/exporters/Exporter.tcc",
                get_exporter_methods(False, expanded),
            ),),
        GenUnit(
            GenTu("{base}/exporters/ExporterMethods.tcc",
                  get_exporter_methods(True, expanded))),
        GenUnit(
            GenTu(
                "{base}/py_libs/pyhaxorg/pyhaxorg.cpp",
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
