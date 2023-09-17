#!/usr/bin/env python

from dataclasses import field, dataclass
from typing import *
from enum import Enum

import setup_imports

# Now you should be able to import your C++ library
from py_textlayout import TextLayout, TextOptions
from astbuilder_cpp import *
from gen_tu_cpp import *

from org_codegen_data import *


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
          isinstance(tree, type)):
        pass

    elif isinstance(tree, object):
        # If any object -- walk all slots (attributes)
        class_of_obj = type(tree)
        name = class_of_obj.__name__
        slots = vars(tree)
        for slot, value in slots.items():
            iterate_object_tree(value, callback, context)

    # Walk over every item in list
    # Otherwise, print the value -- if something is missing it will be added later
    else:
        print(f"? {tree}")

    context.pop()


def get_type_base_fields(value, base_map):
    fields = []
    for base_sym in value.bases:
        base = base_map.get(base_sym)
        if base:
            fields.extend(base.fields)
            fields.extend(get_type_base_fields(base, base_map))

    return fields


def get_type_group_fields(value):
    return [
        GenTuField(QualType(group.variantName), group.variantField, GenTuDoc(""))
        for group in get_nested_groups(value)
    ]


def get_nested_groups(value):
    return [
        nested for nested in value.nested
        if isinstance(nested, GenTuTypeGroup) and nested.variantField
    ]


def get_base_map():
    base_map = {}

    def callback(obj):
        if isinstance(obj, GenTuStruct):
            base_map[obj.name] = obj

    context = []
    iterate_object_tree(get_types(), callback, context)
    base_map["Org"] = GenTuStruct(
        "Org",
        GenTuDoc(""),
        [
            GenTuField(QualType("OrgSemPlacement"), "placementContext", GenTuDoc("")),
            GenTuField(t_vec(t_id()), "subnodes", GenTuDoc("")),
        ],
    )

    return base_map


def get_exporter_methods(forward):
    methods = []
    iterate_tree_context = []
    base_map = get_base_map()

    def callback(value):
        nonlocal methods
        nonlocal base_map
        nonlocal iterate_tree_context
        if isinstance(value, GenTuStruct):
            scope_full = [scope for scope in iterate_tree_context if isinstance(scope, GenTuStruct)]
            scope_names = [scope.name for scope in scope_full]
            name = value.name
            full_scoped_name = scope_names + [name]
            fields = [
                field for field in (value.fields + get_type_base_fields(value, base_map) +
                                    get_type_group_fields(value)) if not (field.isStatic)
            ]

            scoped_target = t_cr(
                QualType(name, Spaces=[QualType("sem")] + [QualType(t) for t in scope_names]))
            decl_scope = "" if forward else "Exporter<V, R>::"
            t_params = [] if forward else [GenTuParam("V"), GenTuParam("R")]

            variant_methods = [
                GenTuFunction(
                    QualType("void"),
                    f"{decl_scope}visit",
                    GenTuDoc(""),
                    params=t_params,
                    arguments=[
                        GenTuIdent(QualType("R", isRef=True), "res"),
                        GenTuIdent(
                            t_cr(
                                QualType(
                                    group.variantName,
                                    Spaces=[QualType("sem")] +
                                    [QualType(t) for t in full_scoped_name],
                                )),
                            "object",
                        ),
                    ],
                    impl=None if forward else
                    f"visitVariants(res, sem::{'::'.join(full_scoped_name)}::{group.kindGetter}(object), object);",
                ) for group in get_nested_groups(value)
            ]

            if len(scope_full) == 0:
                method = GenTuFunction(
                    QualType("void"),
                    f"{decl_scope}visit{name}",
                    GenTuDoc(""),
                    params=t_params,
                    arguments=[
                        GenTuIdent(QualType("R", isRef=True), "res"),
                        GenTuIdent(QualType("In", [QualType(f"sem::{name}")]), "object"),
                    ],
                    impl=None if forward else f"__visit_specific_kind(res, object);\n%s" %
                    "\n".join([f"__org_field(res, object, {a.name});" for a in fields]),
                )
            else:
                method = GenTuFunction(
                    QualType("void"),
                    f"{decl_scope}visit",
                    GenTuDoc(""),
                    params=t_params,
                    arguments=[
                        GenTuIdent(QualType("R", isRef=True), "res"),
                        GenTuIdent(scoped_target, "object"),
                    ],
                    impl=None if forward else "\n".join(
                        [f"__obj_field(res, object, {a.name});" for a in fields]),
                )

            methods += variant_methods + [method]

    iterate_object_tree(get_types(), callback, iterate_tree_context)
    return methods


def get_concrete_types():
    return [struct for struct in get_types() if struct.concreteKind]


@beartype
def pybind_property(ast: ASTBuilder,
                    field: GenTuField,
                    Self: ParmVarParams,
                    PtrType: bool = False) -> BlockId:
    b = ast.b
    if PtrType:
        return ast.XCall(
            ".def_property",
            [
                ast.Literal(field.name),
                ast.Lambda(
                    LambdaParams(
                        ResultTy=field.type,
                        Body=[b.text(f"return {Self.name}->{field.name};")],
                        Args=[Self],
                    )),
                ast.Lambda(
                    LambdaParams(
                        ResultTy=None,
                        Body=[b.text(f"{Self.name}->{field.name} = {field.name};")],
                        Args=[Self, ParmVarParams(field.type, field.name)],
                    )),
            ],
            Line=False,
        )

    else:
        return ast.XCall(
            ".def_readwrite",
            [
                ast.Literal(field.name),
                b.line([b.text("&"),
                        ast.Type(Self.type),
                        b.text("::"),
                        b.text(field.name)]),
                *([ast.Literal(field.doc.brief)] if field.doc.brief else [])
            ]
        )


@beartype
def pybind_method(ast: ASTBuilder, meth: GenTuFunction, Self: ParmVarParams,
                  Body: List[BlockId]) -> BlockId:
    b = ast.b
    return ast.XCall(
        ".def",
        [
            ast.Literal(meth.name),
            ast.Lambda(
                LambdaParams(
                    ResultTy=meth.result,
                    Args=[Self] + [ParmVarParams(Arg.type, Arg.name) for Arg in meth.arguments],
                    Body=Body,
                )),
            *([ast.Literal(meth.doc.brief)] if meth.doc.brief else []),
            *[
                ast.XCall("pybind11::arg", [ast.Literal(Arg.name)]) if Arg.value is None else
                ast.XCall("pybind11::arg_v",
                          [ast.Literal(Arg.name), b.text(Arg.value)]) for Arg in meth.arguments
            ],
        ],
        Line=False,
    )


def pybind_org_id(ast: ASTBuilder, b: TextLayout, typ: GenTuStruct) -> BlockId:
    id_type = t_id("sem::" + typ.name)
    id_type.Spaces.append(QualType("sem"))

    sub: List[BlockId] = []

    # sub.append(b.text(".def(pybind11::init([](){ return %s::Nil(); }))" % (id_type)))
    sub.append(
        ast.XCall(
            ".def",
            [
                ast.XCall(
                    "pybind11::init",
                    [ast.Lambda(LambdaParams(Body=[ast.Return(ast.CallStatic(id_type, "Nil"))]))],
                )
            ],
        ))

    id_self = ParmVarParams(id_type, "id")
    for field in typ.fields:
        if field.isStatic:
            continue
        sub.append(pybind_property(ast, field, id_self, PtrType=True))

    for meth in typ.methods:
        if meth.isStatic or meth.isPureVirtual:
            continue

        passcall = ast.XCallPtr(b.text("id"), meth.name,
                                [b.text(arg.name) for arg in meth.arguments])
        if meth.result and meth.result != "void":
            passcall = ast.Return(passcall)

        sub.append(pybind_method(ast, meth, Self=id_self, Body=[passcall]))

    sub.append(b.text(";"))
    return b.stack([
        ast.Comment(["Binding for ID type"]),
        ast.XCall("pybind11::class_", [b.text("m"), ast.Literal(typ.name)], Params=[id_type]),
        b.indent(2, b.stack(sub))
    ])


def get_bind_methods(ast: ASTBuilder) -> GenTuPass:
    passes: List[BlockId] = []
    typ: GenTuStruct
    b: TextLayout = ast.b

    iterate_context = []

    def callback(value):
        nonlocal iterate_context
        scope: List[QualType] = [
            QualType(scope.name) for scope in iterate_context if isinstance(scope, GenTuStruct)
        ]

        if isinstance(value, QualType):
            if hasattr(value, "isNested"):
                value.Spaces = [QualType("sem")] + scope

        elif isinstance(value, GenTuStruct):
            if len(scope) == 0:
                passes.append(pybind_org_id(ast, b, value))
            else:
                sub: List[BlockId] = []
                id_self = ParmVarParams(QualType(value.name, Spaces=[QualType("sem")] + scope), "value")
                for field in value.fields:
                    sub.append(pybind_property(ast, field, id_self))

                sub.append(b.text(";"))

                passes.append(b.stack([
                    ast.Comment(["Binding for nested type"]),
                    ast.XCall("pybind11::class_", [
                        b.text("m"),
                        ast.Literal("".join([typ.name for typ in scope] + [value.name]))
                    ], Params=[id_self.type]),
                    b.indent(2, b.stack(sub))
                ]))

    iterate_object_tree(get_types(), callback, iterate_context)
    return GenTuPass(b.stack(passes))


def gen_value(ast: ASTBuilder) -> GenFiles:
    full_enums = get_enums() + [
        GenTuEnum(
            t_osk().name,
            GenTuDoc(""),
            fields=[GenTuEnumField(struct.name, GenTuDoc("")) for struct in get_concrete_types()],
        )
    ]

    return GenFiles([
        GenUnit(
            GenTu(
                "{base}/exporters/exporternlp_enums.hpp",
                with_enum_reflection_api(get_nlp_enums()),
            ),
            GenTu(
                "{base}/exporters/exporternlp_enums.cpp",
                [GenTuPass('#include "exporternlp_enums.hpp"')] + get_nlp_enums(),
            ),
        ),
        GenUnit(GenTu("{base}/exporters/Exporter.tcc", get_exporter_methods(False))),
        GenUnit(GenTu("{base}/exporters/ExporterMethods.tcc", get_exporter_methods(True))),
        GenUnit(
            GenTu(
                "/tmp/org_pybind.cpp",
                [GenTuInclude("pybind11/pubind11.hpp", True)] + [get_bind_methods(ast)],
            )),
        GenUnit(
            GenTu(
                "{base}/sem/SemOrgEnums.hpp",
                with_enum_reflection_api([
                    GenTuPass("#define EACH_SEM_ORG_KIND(__IMPL) \\\n" + (" \\\n".join(
                        [f"    __IMPL({struct.name})" for struct in get_concrete_types()])))
                ]) + full_enums,
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
                    GenTuInclude("QDateTime", True),
                    GenTuInclude("sem/SemOrgBase.hpp", True),
                    GenTuInclude("sem/SemOrgEnums.hpp", True),
                    GenTuNamespace("sem", [GenTuTypeGroup(get_types(), enumName="")]),
                ],
            )),
    ])


if __name__ == "__main__":
    from pprint import pprint
    import os
    import sys

    t = TextLayout()
    builder = ASTBuilder(t)
    description: GenFiles = gen_value(builder)
    trace_file = open("/tmp/trace.txt", "w")
    indent = 0

    for tu in description.files:
        for i in range(2):
            if i == 1 and not tu.source:
                continue

            with open("/tmp/current_tu_data.py", "w") as file:
                pprint(tu, width=200, stream=file)

            isHeader = i == 0
            define = tu.header if isHeader else tu.source
            path = define.path.format(base="/mnt/workspace/repos/haxorg/src")
            log.info(f"Formatting {path}, isSource={not isHeader}")
            result = builder.TranslationUnit([
                GenConverter(builder,
                             isSource=not isHeader).convertTu(tu.header if isHeader else tu.source)
            ])

            directory = os.path.dirname(path)
            if not os.path.exists(directory):
                os.makedirs(directory)
                print(f"Created dir for {path}")

            newCode = t.toString(result, TextOptions())

            if os.path.exists(path):
                with open(path, "r") as f:
                    oldCode = f.read()

                if oldCode != newCode:
                    with open(path, "w") as out:
                        out.write(newCode)
                    log.info(f"Updated code in {path} pattern was {define.path}")
                else:
                    log.info(f"No changes on {path} pattern was {define.path}")
            else:
                with open(path, "w") as out:
                    out.write(newCode)
                log.info(f"Wrote to {path} pattern was {define.path}")

    print("Done all")
