#!/usr/bin/env python

from dataclasses import dataclass, field, replace
import itertools
from typing import *
from copy import deepcopy

import py_codegen.astbuilder_py as pya
import py_codegen.astbuilder_embind as napi
import py_codegen.astbuilder_cpp as cpp
from py_codegen.org_codegen_data import *
from py_textlayout.py_textlayout_wrap import TextLayout, TextOptions
from py_codegen.refl_read import conv_proto_file, ConvTu, open_proto_file
from py_scriptutils.script_logging import log
import py_codegen.astbuilder_proto as pb
from py_scriptutils.algorithm import cond
from py_scriptutils.script_logging import pprint_to_file
from graphlib import TopologicalSorter, CycleError
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
    py_type,
)

import yaml

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
def get_exporter_methods(
    forward: bool,
    expanded: List[GenTuStruct],
    base_map: GenTypeMap,
) -> Sequence[GenTuFunction]:
    methods: List[GenTuFunction] = []
    iterate_tree_context = []

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
def get_imm_serde(
    types: List[GenTuStruct],
    ast: ASTBuilder,
    base_map: GenTypeMap,
) -> List[GenTuPass]:
    serde: List[GenTuStruct] = []

    def aux(it):
        match it:
            case GenTuStruct():
                if it.IsAbstract:
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
                        base_type = base_map.get_one_type_for_name(base.name)
                        if base_type:
                            assert base_type.name.name != sub.name.name
                            field_aux(base_type)

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
    return [struct for struct in expanded if not struct.IsAbstract]


from copy import deepcopy, copy


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


def topological_sort_entries(entries: List[GenTuUnion]) -> List[GenTuUnion]:
    entry_by_hash: Dict[int, GenTuUnion] = {}
    cant_have_dependants: List[GenTuUnion] = []

    for it in entries:
        match it:
            case GenTuStruct():
                qual_hash = it.declarationQualName().qual_hash()
                assert qual_hash not in entry_by_hash, f"Duplicate hash for {it.declarationQualName()}, already mapped to {it}"
                entry_by_hash[qual_hash] = it

            case GenTuTypedef():
                entry_by_hash[it.name.qual_hash()] = it

            case _:
                cant_have_dependants.append(it)

    assert (len(entry_by_hash) + len(cant_have_dependants)) == len(
        entries
    ), f"Sorting order mismatch len(hash): {len(entry_by_hash)} + len(no-deps): {len(cant_have_dependants)} len(entries): {len(entries)}"

    graph = {}
    for entry in entries:
        match entry:
            case GenTuStruct():
                entry_hash = entry.declarationQualName().qual_hash()
                graph[entry_hash] = {
                    base.qual_hash()
                    for base in entry.bases
                    if base.qual_hash() in entry_by_hash
                }

            case GenTuTypedef():
                entry_hash = entry.name.qual_hash()
                if entry.base.qual_hash() in entry_by_hash:
                    graph[entry_hash] = {entry.base.qual_hash()}

    ts = TopologicalSorter(graph)
    try:
        sorted_hashes = list(ts.static_order())
        result = [entry_by_hash[h] for h in sorted_hashes] + cant_have_dependants

        # assert len(result) == len(
        #     entries
        # ), f"Sorting order mismatch len(in): {len(entries)} len(out): {len(result)} len(no-deps): {len(cant_have_dependants)} len(hash): {len(entry_by_hash)}"

        return result
    except CycleError:
        raise ValueError("Cyclic inheritance detected")


@beartype
def expand_type_groups(ast: ASTBuilder, types: List[GenTuStruct]) -> List[GenTuStruct]:

    @beartype
    def rec_expand_group(record: GenTuTypeGroup,) -> List[GenTuEntry | GenTuField]:
        result = []
        typeNames: List[QualType] = []

        for item in record.types:
            expanded = rec_expand_type(item)
            result.append(expanded)
            if not item.IsAbstract:
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
                            reflectionParams=GenTuReflParams(
                                unique_name="get" + kindName +
                                ("Const" if isConst else "Mut")),
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
                    reflectionParams=GenTuReflParams(unique_name=record.kindGetter +
                                                     "Static"),
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
def mutate_type_to_immutable(obj: QualType):
    obj.dbg_origin += "imm_write"
    match obj:
        case QualType(name="SemId", parameters=[]):
            obj.name = "ImmId"
            obj.Spaces = [n_imm()]

        case QualType(name="SemId"):
            obj.name = "ImmIdT"
            obj.Spaces = [n_imm()]

        case QualType(name="Vec"):
            obj.name = "ImmVec"
            obj.Spaces = [n_hstd_ext()]

        case QualType(name="UnorderedMap"):
            obj.name = "ImmMap"
            obj.Spaces = [n_hstd_ext()]

        case _:
            flat_namespace = obj.flatQualFullName()
            match flat_namespace:
                case [QualType(name="org"), QualType(name="sem"), *rest]:
                    if rest and rest[0].isOrgType():
                        if 1 == len(rest):
                            obj.name = "Imm" + obj.name
                            obj.Spaces = [n_imm()]

                        elif 1 < len(rest):
                            reuse_spaces = copy(rest)
                            reuse_spaces.pop(0)
                            reuse_spaces.pop(-1)
                            obj.Spaces = [
                                n_imm(), rest[0].model_copy(update=dict(name="Imm" +
                                                                        rest[0].name)),
                                *reuse_spaces
                            ]

                        else:
                            pass


@beartype
def rewrite_to_immutable(recs: List[GenTuStruct]) -> List[GenTuStruct]:
    result = deepcopy(recs)

    IMM_BOX = t("ImmBox", [n_hstd_ext()])
    ORG_SPACE = n_imm()

    def impl(obj: Any):
        match obj:
            case QualType():
                mutate_type_to_immutable(obj)

            case GenTuField(type=QualType(name="SemId", parameters=[])):
                mutate_type_to_immutable(obj.type)
                obj.value = "org::imm::ImmId::Nil()"

            case GenTuField(type=QualType(name="SemId")):
                mutate_type_to_immutable(obj.type)
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

                if obj.reflectionParams.backend.wasm.holder_type:
                    obj.reflectionParams.backend.wasm.holder_type = None

                obj.methods.append(
                    GenTuFunction(
                        result=QualType.ForName("bool"),
                        name="operator==",
                        isConst=True,
                        arguments=[GenTuIdent(type=self_arg, name="other")],
                    ))

                if hasattr(obj, "isOrgType"):
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
    base_map = get_base_map(tu.enums + tu.structs + tu.typedefs)
    res = Py11Module("py_adaptagrams")
    res.add_all(tu.get_all(), ast=ast, base_map=base_map)
    specializations = collect_type_specializations(tu.get_all(), base_map=base_map)
    res.add_type_specializations(
        ast=ast,
        specializations=specializations,
    )

    with open("/tmp/adaptagrams_reflection.json", "w") as file:
        log(CAT).debug(f"Debug reflection data to {file.name}")
        file.write(open_proto_file(reflection_path).to_json(2))

    return GenFiles([
        GenUnit(
            GenTu(
                "{root}/scripts/py_wrappers/py_wrappers/py_adaptagrams.pyi",
                [GenTuPass(res.build_typedef(pyast, base_map=base_map))],
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
                    GenTuPass(res.build_bind(ast, base_map=base_map)),
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
    typ: QualType


@beartype
@dataclass
class PyhaxorgTypeFieldGroup:
    types: List[PyhaxorgTypeDesc] = field(default_factory=list)


@beartype
def collect_type_field_groups(types: List[GenTuStruct],
                              base_map: GenTypeMap) -> PyhaxorgTypeFieldGroup:

    def aux(t: GenTuStruct) -> List[GenTuField]:
        result: List[GenTuField] = []
        for base in t.bases:
            base_type = base_map.get_one_type_for_name(base.name)
            if base_type:
                result += aux(base_type)

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
            typ=t.name,
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
def gen_pyhaxorg_field_iteration_macros(
    types: List[GenTuStruct],
    base_map: GenTypeMap,
    ast: ASTBuilder,
    macro_namespace: str,
) -> List[GenTuPass]:

    result: List[GenTuPass] = []

    field_groups = collect_type_field_groups(types, base_map=base_map)

    for group in field_groups.types:
        for with_base_fields in [True, False]:
            def_stack = ast.b.stack([])

            if with_base_fields:
                ast.b.add_at(
                    def_stack,
                    ast.string(
                        f"#define EACH_{macro_namespace}_ORG_{group.name}_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \\"
                    ))

            else:
                ast.b.add_at(
                    def_stack,
                    ast.string(
                        f"#define EACH_{macro_namespace}_ORG_{group.name}_FIELD_WITH_BASES(__IMPL_BASE) \\"
                    ))

            def impl_field(field: GenTuField):
                ast.b.add_at(
                    def_stack,
                    ast.b.line([
                        ast.string("    "),
                        ast.XCall(
                            "__IMPL_FIELD",
                            [
                                # Type of the field
                                ast.pars(ast.Type(field.type)),
                                # field name without changes
                                ast.string(field.name),
                                # field name for `getField` etc.
                                ast.string(field.name.capitalize()),
                                # Parent type for field, in case you need to define methods for each field
                                # outside of the class body.
                                ast.pars(ast.Type(group.typ)),
                                ast.string(group.name.replace("Imm", "")),
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
def gen_pyhaxorg_iteration_macros(types: List[GenTuStruct]) -> List[GenTuPass]:
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

    return result


@beartype
@dataclass
class PyhaxorgTypeGroups():
    shared_types: List[GenTuStruct] = field(default_factory=list)
    expanded: List[GenTuStruct] = field(default_factory=list)
    immutable: List[GenTuStruct] = field(default_factory=list)
    tu: ConvTu = field(default_factory=lambda: ConvTu())
    base_map: GenTypeMap = field(default_factory=lambda: GenTypeMap)
    full_enums: List[GenTuEnum] = field(default_factory=list)
    imm_id_specializations: List[GenTuStruct] = field(default_factory=list)
    specializations: List[TypeSpecialization] = field(default_factory=list)

    def get_entries_for_wrapping(self) -> List[GenTuUnion]:

        def aux(e: GenTuEntry, ind: int):
            match e:
                case GenTuStruct():
                    log(CAT).info(
                        f"{'  ' * ind}{e.name.name} {e.name} wrapper:{e.reflectionParams.wrapper_name} py:{py_type(e.name, self.base_map)}"
                    )
                    for sub in e.nested:
                        aux(sub, ind + 1)

        # for e in self.immutable:
        #     aux(e, 0)

        result = self.full_enums + \
            self.tu.enums + \
            self.tu.structs + \
            self.tu.typedefs + \
            self.shared_types + \
            self.expanded + \
            self.tu.functions + \
            self.immutable + \
            self.imm_id_specializations

        # return result

        return topological_sort_entries(result)


@beartype
def get_pyhaxorg_type_groups(
    ast: ASTBuilder,
    reflection_path: Path,
) -> PyhaxorgTypeGroups:
    res = PyhaxorgTypeGroups()
    res.shared_types = expand_type_groups(ast, get_shared_sem_types())
    res.expanded = expand_type_groups(ast, get_types())
    res.immutable = expand_type_groups(ast, rewrite_to_immutable(get_types()))

    res.tu = conv_proto_file(reflection_path)
    res.base_map = get_base_map(res.expanded + res.shared_types + res.immutable +
                                res.tu.enums + res.tu.structs + res.tu.typedefs)
    res.full_enums = get_shared_sem_enums() + get_enums() + [get_osk_enum(res.expanded)]

    res.specializations = collect_type_specializations(
        res.get_entries_for_wrapping(),
        base_map=res.base_map,
    )

    for org_type in get_types():
        original_id = org_type.name.model_copy()
        mutate_type_to_immutable(original_id)
        res.imm_id_specializations.append(
            GenTuStruct(
                OriginName="imm ID explicit",
                name=QualType.ForName(
                    "ImmIdT", Spaces=[QualType.ForName("org"),
                                      QualType.ForName("imm")]),
                IsExplicitInstantiation=True,
                ExplicitTemplateParams=[original_id],
                reflectionParams=GenTuReflParams(wrapper_name="ImmIdT" +
                                                 org_type.name.name),
                IsDescribedRecord=False,
                bases=[
                    QualType.ForName(
                        "ImmId",
                        Spaces=[QualType.ForName("org"),
                                QualType.ForName("imm")]),
                ],
            ))

    return res


@beartype
def gen_pyhaxorg_python_wrappers(
    groups: PyhaxorgTypeGroups,
    ast: ASTBuilder,
    pyast: pya.ASTBuilder,
) -> GenFiles:

    res = Py11Module("pyhaxorg")

    for decl in groups.get_entries_for_wrapping():
        if decl.reflectionParams.isAcceptedBackend("python"):
            res.add_decl(decl, ast=ast, base_map=groups.base_map)

    res.add_type_specializations(
        ast,
        specializations=groups.specializations,
    )

    res.Decls.append(ast.Include("pyhaxorg_manual_wrap.hpp"))

    return GenFiles([
        GenUnit(
            GenTu(
                "{root}/scripts/py_haxorg/py_haxorg/pyhaxorg.pyi",
                [GenTuPass(res.build_typedef(pyast, base_map=groups.base_map))],
                clangFormatGuard=False,
            )),
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
                    GenTuPass(res.build_bind(ast, base_map=groups.base_map)),
                ],
            )),
    ])


@beartype
def gen_pyhaxorg_napi_wrappers(
    groups: PyhaxorgTypeGroups,
    ast: ASTBuilder,
    base_map: GenTypeMap,
) -> GenFiles:

    cpp_builder = cpp.ASTBuilder(ast.b)

    res = napi.WasmModule("haxorg_wasm")

    res.add_specializations(
        b=ast,
        specializations=groups.specializations,
    )

    for decl in groups.get_entries_for_wrapping():
        if decl.reflectionParams.isAcceptedBackend("wasm"):
            res.add_decl(decl)

    res.Header.append(napi.WasmBindPass(ast.Include("node_utils.hpp")))
    res.Header.append(napi.WasmBindPass(ast.Include("node_org_include.hpp")))
    res.Header.append(napi.WasmBindPass(ast.Include("haxorg_wasm_manual.hpp")))
    res.Header.append(napi.WasmBindPass(ast.string("using namespace org::bind::js;")))

    res.add_decl(napi.WasmBindPass(ast.string("haxorg_wasm_manual_register();")))

    return GenFiles([
        GenUnit(
            GenTu("{root}/src/wrappers/js/haxorg_wasm.cpp", [
                GenTuPass(res.build_bind(
                    ast=ast,
                    b=cpp_builder,
                    base_map=base_map,
                )),
            ])),
        GenUnit(
            GenTu("{root}/src/wrappers/js/haxorg_wasm_types.d.ts", [
                GenTuPass(res.build_typedef(
                    ast=ast,
                    base_map=base_map,
                )),
            ])),
    ])


@beartype
def gen_pyhaxorg_source(
    ast: ASTBuilder,
    groups: PyhaxorgTypeGroups,
) -> GenFiles:
    proto = pb.ProtoBuilder(
        wrapped=groups.full_enums + groups.shared_types + groups.expanded,
        ast=ast,
        base_map=groups.base_map,
    )
    t = ast.b

    protobuf = proto.build_protobuf()
    protobuf_writer_declarations, protobuf_writer_implementation = proto.build_protobuf_writer(
    )

    return GenFiles([
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
                    GenTuPass("#if ORG_DEPS_USE_PROTOBUF && !ORG_EMCC_BUILD"),
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
                    GenTuPass("#if ORG_DEPS_USE_PROTOBUF && !ORG_EMCC_BUILD"),
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
                get_exporter_methods(False, groups.shared_types, base_map=groups.base_map)
                + get_exporter_methods(False, groups.expanded, base_map=groups.base_map),
            ),),
        GenUnit(
            GenTu(
                "{base}/sem/ImmOrgSerde.tcc",
                get_imm_serde(types=groups.expanded, ast=ast, base_map=groups.base_map),
            ),),
        GenUnit(
            GenTu(
                "{base}/exporters/ExporterMethods.tcc",
                get_exporter_methods(True, groups.shared_types, base_map=groups.base_map)
                + get_exporter_methods(True, groups.expanded, base_map=groups.base_map))),
        GenUnit(
            GenTu(
                "{base}/sem/SemOrgEnums.hpp",
                with_enum_reflection_api(
                    gen_pyhaxorg_shared_iteration_macros(groups.shared_types) +
                    gen_pyhaxorg_iteration_macros(types=groups.expanded)) +
                gen_pyhaxorg_field_iteration_macros(
                    types=groups.expanded,
                    base_map=groups.base_map,
                    ast=ast,
                    macro_namespace="SEM",
                ) + gen_pyhaxorg_field_iteration_macros(
                    types=groups.immutable,
                    base_map=groups.base_map,
                    ast=ast,
                    macro_namespace="IMM",
                ) + groups.full_enums + ([
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
                [GenTuPass('#include "SemOrgEnums.hpp"')] + groups.full_enums,
            ),
        ),
                GenUnit(
            GenTu(
                "{base}/sem/SemOrgSharedTypes.hpp",
                [
                    GenTuPass("#pragma once"),
                    GenTuInclude("haxorg/sem/SemOrgEnums.hpp", True),
                    GenTuInclude("hstd/stdlib/Vec.hpp", True),
                    GenTuInclude("hstd/stdlib/Variant.hpp", True),
                    GenTuInclude("hstd/stdlib/Time.hpp", True),
                    GenTuInclude("hstd/stdlib/Opt.hpp", True),
                    GenTuInclude("hstd/stdlib/Str.hpp", True),
                    GenTuInclude("boost/describe.hpp", True),
                    GenTuInclude("hstd/system/macros.hpp", True),
                    GenTuInclude("haxorg/sem/SemOrgBaseSharedTypes.hpp", True),
                    GenTuInclude("haxorg/sem/SemOrgEnums.hpp", True),
                    GenTuNamespace(n_sem(), groups.shared_types ),
                ],
            )),
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
                    GenTuInclude("haxorg/sem/SemOrgSharedTypes.hpp", True),
                    GenTuNamespace(n_sem(), groups.expanded),
                ],
            )),
        GenUnit(
            GenTu(
                "{base}/sem/ImmOrgTypes.hpp",
                [
                    GenTuPass("#pragma once"),
                    GenTuInclude("haxorg/sem/ImmOrgBase.hpp", True),
                    GenTuNamespace(n_imm(), groups.immutable),
                ],
            )),
    ])


def gen_description_files(
    description: GenFiles,
    builder: ASTBuilder,
    t: TextLayout,
    tmp: bool,
) -> None:
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
def impl(ctx: click.Context, config: Optional[str] = None, **kwargs: Any) -> None:
    opts: CodegenOptions = get_context(ctx, CodegenOptions, config=config, kwargs=kwargs)

    t = TextLayout()
    pyast = pya.ASTBuilder(t)
    builder = ASTBuilder(t)

    def write_files_group(impl: GenFiles) -> None:
        gen_description_files(
            description=impl,
            builder=builder,
            t=t,
            tmp=opts.tmp,
        )

    match opts.codegen_task:
        case "adaptagrams":
            write_files_group(
                gen_adaptagrams_wrappers(
                    builder,
                    pyast,
                    reflection_path=Path(opts.reflection_path),
                ))

        case "pyhaxorg":
            groups: PyhaxorgTypeGroups = get_pyhaxorg_type_groups(
                ast=builder,
                reflection_path=Path(opts.reflection_path),
            )

            with open("/tmp/pyhaxorg_reflection_data.yaml", "w") as file:
                yaml.safe_dump(to_base_types(groups.tu), stream=file)

            with open("/tmp/pyhaxorg_reflection_data.json", "w") as file:
                log(CAT).debug(f"Debug reflection data to {file.name}")
                file.write(open_proto_file(Path(opts.reflection_path)).to_json(2))


            write_files_group(
                gen_pyhaxorg_napi_wrappers(
                    groups=groups,
                    ast=builder,
                    base_map=groups.base_map,
                ))

            write_files_group(
                gen_pyhaxorg_python_wrappers(
                    groups=groups,
                    ast=builder,
                    pyast=pyast,
                ))

            write_files_group(gen_pyhaxorg_source(
                ast=builder,
                groups=groups,
            ))


if __name__ == "__main__":
    impl()
