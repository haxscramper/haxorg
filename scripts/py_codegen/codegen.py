#!/usr/bin/env python

from dataclasses import field, dataclass, replace
from typing import *
from enum import Enum
import re

import setup_imports

from scripts.py_textlayout.py_textlayout import TextLayout, TextOptions
from astbuilder_cpp import *
from gen_tu_cpp import *

from org_codegen_data import *

import astbuilder_py as pya


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
            base_map[obj.name] = obj

    context = []
    iterate_object_tree(expanded, callback, context)
    base_map["Org"] = GenTuStruct(
        "Org",
        GenTuDoc(""),
        [
            GenTuField(QualType("OrgSemPlacement"), "placementContext", GenTuDoc("")),
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

    def callback(value):
        nonlocal methods
        nonlocal base_map
        nonlocal iterate_tree_context
        if isinstance(value, GenTuStruct):
            scope_full = [
                scope for scope in iterate_tree_context if isinstance(scope, GenTuStruct)
            ]
            scope_names = [scope.name for scope in scope_full]
            name = value.name
            full_scoped_name = scope_names + [name]
            fields = [
                field for field in (value.fields + get_type_base_fields(value, base_map))
                if not (field.isStatic)
            ]

            scoped_target = t_cr(
                QualType(name,
                         Spaces=[QualType("sem")] + [QualType(t) for t in scope_names]))
            decl_scope = "" if forward else "Exporter<V, R>::"
            t_params = [] if forward else [GenTuParam("V"), GenTuParam("R")]

            variant_methods: List[GenTuFunction] = []
            for field in fields:
                if hasattr(field, "isVariantField"):
                    kindGetter = getattr(field, "variantGetter")
                    variant_methods.append(
                        GenTuFunction(
                            QualType("void"),
                            f"{decl_scope}visit",
                            GenTuDoc(""),
                            params=t_params,
                            arguments=[
                                GenTuIdent(QualType("R", isRef=True), "res"),
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
                    QualType("void"),
                    f"{decl_scope}visit{name}",
                    GenTuDoc(""),
                    params=t_params,
                    arguments=[
                        GenTuIdent(QualType("R", isRef=True), "res"),
                        GenTuIdent(QualType("In", [QualType(f"sem::{name}")]), "object"),
                    ],
                    impl=None if forward else "__visit_specific_kind(res, object);\n%s" %
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
        typ.Spaces.insert(0, QualType("sem"))

    typ.Parameters = [in_sem(P) for P in typ.Parameters]

    return typ


@beartype
def flat_scope(Typ: QualType) -> List[str]:
    res: List[str] = []
    for S in Typ.Spaces:
        res += flat_scope(S)

    res += [Typ.name]
    return res


@beartype
@dataclass
class Py11EnumField:
    PyName: str
    CxxName: str
    Doc: GenTuDoc

    @staticmethod
    def FromGenTu(Field: GenTuEnumField,
                  pyNameOverride: Optional[str] = None) -> 'Py11EnumField':
        return Py11EnumField(
            PyName=Field.name if pyNameOverride is None else pyNameOverride,
            CxxName=Field.name,
            Doc=Field.doc)

    def build_bind(self, Enum: 'Py11Enum', ast: ASTBuilder) -> BlockId:
        return ast.XCall(".value", [
            ast.Literal(self.PyName),
            ast.Type(QualType(self.CxxName, Spaces=[Enum.Enum]))
        ] + maybe_list(get_doc_literal(ast, self.Doc)))


@beartype
@dataclass
class Py11Enum:
    PyName: str
    Enum: QualType
    Fields: List[Py11EnumField]
    Doc: GenTuDoc

    @staticmethod
    def FromGenTu(Enum: GenTuEnum,
                  Scope: List[QualType] = [],
                  pyNameOverride: Optional[str] = None) -> 'Py11Enum':
        return Py11Enum(PyName="".join(flat_scope(QualType(Enum.name, Spaces=Scope)))
                        if pyNameOverride is None else pyNameOverride,
                        Enum=QualType(Enum.name, Spaces=Scope),
                        Doc=Enum.doc,
                        Fields=[Py11EnumField.FromGenTu(F) for F in Enum.fields])

    def build_typedef(self) -> pya.EnumParams:
        count = 0
        return pya.EnumParams(
            Name=self.PyName,
            Fields=[
                pya.EnumFieldParams(
                    ("_" +
                     F.PyName if F.PyName in ["None", "True", "False"] else F.PyName),
                    str(count := count + 1)) for F in self.Fields
            ])

    def build_bind(self, ast: ASTBuilder) -> BlockId:
        b = ast.b

        return b.stack([
            ast.XCall("pybind11::enum_",
                      [b.text("m"), ast.Literal(self.PyName)],
                      Params=[self.Enum]),
            b.indent(
                2,
                b.stack([Field.build_bind(self, ast) for Field in self.Fields] +
                        [ast.XCall(".export_values", []),
                         b.text(";")]))
        ])


@beartype
def id_self(Typ: QualType) -> ParmVarParams:
    return ParmVarParams(Typ, "_self")


@beartype
def py_type_bind(Typ: QualType) -> pya.PyType:
    return pya.PyType(Typ.name + ("Of" if Typ.Parameters else "") +
                      "".join([py_type_bind(T).Name for T in Typ.Parameters]))


@beartype
def py_type(Typ: QualType) -> pya.PyType:

    name = ""
    flat = [N for N in flat_scope(Typ) if N != "sem"]
    match flat:
        case ["Vec"]:
            name = "List"

        case ["Opt"]:
            name = "Optional"

        case ["Str"] | ["string"] | ["QString"] | ["basic_string"
                                                  ] | ["std", "basic_string"]:
            name = "str"

        case ["SemIdT"]:
            name = "Sem" + Typ.Parameters[0].name

        case "Bool":
            name = "bool"

        case ["void"]:
            name = "None"

        case ["py", "object"]:
            name = "object"

        case ["UserTime"]:
            name = "datetime"

        case _:
            name = "".join(flat)

    res = pya.PyType(name)
    if Typ.name not in ["SemIdT"]:
        for param in Typ.Parameters:
            res.Params.append(py_type(param))

    return res


@beartype
@dataclass
class Py11Method:
    PyName: str
    CxxName: str
    ResultTy: QualType
    Args: List[GenTuIdent] = field(default_factory=list)
    Body: Optional[List[BlockId]] = None
    Doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))

    @staticmethod
    def FromGenTu(meth: GenTuFunction,
                  Body: Optional[List[BlockId]] = None,
                  pySideOverride: Optional[str] = None) -> 'Py11Method':

        return Py11Method(PyName=meth.name if pySideOverride is None else pySideOverride,
                          Body=Body,
                          ResultTy=meth.result,
                          CxxName=meth.name,
                          Doc=meth.doc,
                          Args=meth.arguments)

    def build_typedef(self, ast: pya.ASTBuilder) -> pya.MethodParams:
        return pya.MethodParams(Func=pya.FunctionDefParams(
            Name=self.PyName,
            ResultTy=py_type(self.ResultTy),
            Args=[pya.IdentParams(py_type(Arg.type), Arg.name) for Arg in self.Args],
            IsStub=True))

    def build_bind(self, Class: QualType, ast: ASTBuilder) -> BlockId:
        b = ast.b

        call_pass: BlockId = None
        if self.Body is None:
            call_pass = ast.Addr(ast.Scoped(Class, ast.string(self.CxxName)))

        else:
            call_pass = ast.Lambda(
                LambdaParams(
                    ResultTy=self.ResultTy,
                    Args=[ParmVarParams(Class, "_self")] +
                    [ParmVarParams(Arg.type, Arg.name) for Arg in self.Args],
                    Body=self.Body,
                ))

        return ast.XCall(
            ".def",
            [
                ast.Literal(self.PyName), call_pass, *[
                    ast.XCall("pybind11::arg", [ast.Literal(Arg.name)])
                    if Arg.value is None else ast.XCall(
                        "pybind11::arg_v",
                        [ast.Literal(Arg.name), b.text(Arg.value)]) for Arg in self.Args
                ], *([ast.StringLiteral(self.Doc.brief, forceRawStr=True)]
                     if self.Doc.brief else [])
            ],
            Line=False,
        )


@beartype
def get_doc_literal(ast: ASTBuilder, doc: GenTuDoc) -> Optional[BlockId]:
    if doc.brief == "" and doc.full == "":
        return None
    else:
        return ast.StringLiteral(doc.brief +
                                 ("" if doc.full == "" else "\n\n" + doc.full),
                                 forceRawStr=True)


@beartype
def maybe_list(it: Any) -> Any:
    if it:
        return [it]
    else:
        return []


@beartype
def py_ident(name: str) -> str:
    match name:
        case "from":
            return "from_"
        case _:
            return name


@beartype
@dataclass
class Py11Field:
    PyName: str
    CxxName: str
    Type: QualType
    GetImpl: Optional[List[BlockId]] = None
    SetImpl: Optional[List[BlockId]] = None
    Doc: GenTuDoc = field(default_factory=GenTuDoc(""))

    @staticmethod
    def FromGenTu(Field: GenTuField,
                  pyNameOveride: Optional[str] = None,
                  GetImpl: Optional[List[BlockId]] = None,
                  SetImpl: Optional[List[BlockId]] = None) -> 'Py11Field':
        return Py11Field(
            PyName=py_ident(Field.name) if pyNameOveride is None else pyNameOveride,
            Type=Field.type,
            CxxName=Field.name,
            GetImpl=GetImpl,
            Doc=Field.doc,
            SetImpl=SetImpl)

    def build_typedef(self, ast: pya.ASTBuilder) -> pya.FieldParams:
        return pya.FieldParams(py_type(self.Type), self.PyName)

    def build_bind(self, Class: QualType, ast: ASTBuilder) -> BlockId:
        b = ast.b
        _self = id_self(Class)
        if self.GetImpl and self.SetImpl:
            return ast.XCall(
                ".def_property",
                [
                    ast.Literal(self.PyName),
                    ast.Lambda(
                        LambdaParams(
                            ResultTy=self.Type,
                            Body=self.GetImpl,
                            Args=[_self],
                        )),
                    ast.Lambda(
                        LambdaParams(
                            ResultTy=None,
                            Body=[
                                b.text(f"{_self.name}->{self.CxxName} = {self.CxxName};")
                            ],
                            Args=[_self, ParmVarParams(self.Type, self.CxxName)],
                        )),
                ],
                Line=False,
            )
        else:
            return ast.XCall(".def_readwrite", [
                ast.Literal(self.PyName),
                b.line([b.text("&"),
                        ast.Type(Class),
                        b.text("::"),
                        b.text(self.CxxName)]),
                *maybe_list(get_doc_literal(ast, self.Doc))
            ])


@beartype
@dataclass
class Py11Class:
    PyName: str
    Class: QualType
    Bases: List[QualType] = field(default_factory=list)
    Fields: List[Py11Field] = field(default_factory=list)
    Methods: List[Py11Method] = field(default_factory=list)
    InitImpls: List[Py11Method] = field(default_factory=list)
    PyBases: List[QualType] = field(default_factory=list)

    def InitDefault(self):
        self.InitImpls.append(Py11Method("", "", QualType("")))

    def AddInit(self, Args: List[ParmVarParams], Impl: List[BlockId]):
        self.InitImpls.append(Py11Method("", "", QualType(""), Args, Body=Impl))

    def build_typedef(self, ast: pya.ASTBuilder) -> pya.ClassParams:
        res = pya.ClassParams(Name=self.PyName, Bases=[py_type(T) for T in self.Bases])
        for Meth in self.Methods:
            res.Methods.append(Meth.build_typedef(ast))

        for Field in self.Fields:
            res.Fields.append(Field.build_typedef(ast))

        return res

    def build_bind(self, ast: ASTBuilder) -> BlockId:
        b = ast.b

        sub: List[BlockId] = []

        for Init in self.InitImpls:
            if Init.Body:
                sub.append(
                    ast.XCall(
                        ".def",
                        [
                            ast.XCall(
                                "pybind11::init",
                                [
                                    ast.Lambda(
                                        LambdaParams(ResultTy=self.Class, Body=Init.Body))
                                ],
                            )
                        ],
                    ))

            else:
                sub.append(
                    ast.XCall(
                        ".def",
                        [ast.XCall(
                            "pybind11::init",
                            [],
                            Params=[],
                        )],
                    ))

        for Field in self.Fields:
            sub.append(Field.build_bind(self.Class, ast))

        for Meth in self.Methods:
            sub.append(Meth.build_bind(self.Class, ast))

        sub.append(b.text(";"))

        return b.stack([
            ast.XCall("pybind11::class_",
                      [b.text("m"), ast.Literal(self.PyName)],
                      Params=[self.Class] + self.Bases),
            b.indent(2, b.stack(sub))
        ])


@beartype
@dataclass
class Py11BindPass:
    Id: BlockId


Py11Entry = Union[Py11Enum, Py11Class, Py11BindPass]


@beartype
@dataclass
class Py11Module:
    PyName: str
    Decls: List[Py11Entry] = field(default_factory=list)
    Before: List[BlockId] = field(default_factory=list)
    After: List[BlockId] = field(default_factory=list)

    def build_typedef(self, ast: pya.ASTBuilder) -> BlockId:
        passes: List[BlockId] = []

        passes.append(ast.string("from typing import *"))
        passes.append(ast.string("from enum import Enum"))
        passes.append(ast.string("from datetime import datetime, date, time"))

        for entry in [E for E in self.Decls if isinstance(E, Py11Enum)]:
            passes.append(ast.Enum(entry.build_typedef()))
            passes.append(ast.string(""))

        for entry in [E for E in self.Decls if isinstance(E, Py11Class)]:
            passes.append(ast.string(f"{entry.PyName}: Type"))

        passes.append(
            ast.string("""
class SemId:
    def getKind(self) -> OrgSemKind: ...
    def __iter__(self) -> Iterator[SemId]: ...
    def __len__(self) -> int: ...
    def getDocument(self) -> Optional[SemId]

    @overload
    def __getitem__(self, idx: int) -> SemId: ...

    @overload
    def __getitem__(self, slice) -> List[SemId]: ...

    def eachSubnodeRec(self, cb) -> None: ...
    def _is(self, kind: OrgSemKind) -> bool: ...
"""))

        for entry in [E for E in self.Decls if isinstance(E, Py11Class)]:
            passes.append(ast.Class(entry.build_typedef(ast)))
            passes.append(ast.string(""))

        return ast.b.stack(passes)

    def build_bind(self, ast: ASTBuilder) -> BlockId:
        b = ast.b

        passes: List[BlockId] = []

        for entry in self.Decls:
            if isinstance(entry, Py11BindPass):
                passes.append(entry.Id)

            elif isinstance(entry, Py11Class):
                passes.append(entry.build_bind(ast))

            elif isinstance(entry, Py11Enum):
                passes.append(entry.build_bind(ast))

        return b.stack([
            *self.Before,
            b.text("PYBIND11_MODULE(pyhaxorg, m) {"),
            b.indent(2, b.stack(passes)),
            b.text("}"), *self.After
        ])


@beartype
def pybind_org_id(ast: ASTBuilder, b: TextLayout, typ: GenTuStruct,
                  base_map: Mapping[str, GenTuStruct]) -> Py11Class:
    base_type = QualType(typ.name, Spaces=[QualType("sem")])
    id_type = QualType("SemIdT", [base_type], Spaces=[QualType("sem")])
    res = Py11Class(PyName="Sem" + typ.name, Class=id_type, PyBases=typ.bases)

    res.AddInit([], [ast.Return(ast.CallStatic(id_type, "Nil"))])
    res.Bases.append(QualType("SemId", Spaces=[QualType("sem")]))

    _self = id_self(id_type)

    def map_obj_fields(Record: GenTuStruct):
        for field in Record.fields:
            if field.isStatic or hasattr(field, "ignore"):
                continue

            res.Fields.append(
                Py11Field.FromGenTu(
                    field,
                    GetImpl=[b.text(f"return {_self.name}->{field.name};")],
                    SetImpl=[b.text(f"{_self.name}->{field.name} = {field.name};")]))

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
    name = "".join([typ.name for typ in scope if typ.name != "sem"] + [value.name])

    res = Py11Class(PyName=name, Class=QualType(value.name, Spaces=scope))
    res.InitDefault()

    for meth in value.methods:
        if meth.isStatic or meth.isPureVirtual:
            continue

        res.Methods.append(Py11Method.FromGenTu(meth))

    for field in value.fields:
        if field.isStatic or hasattr(field, "ignore"):
            continue

        res.Fields.append(Py11Field.FromGenTu(field))

    return res


@beartype
def filter_walk_scope(iterate_context) -> List[QualType]:
    scope: List[QualType] = []

    for s in iterate_context:
        if isinstance(s, GenTuStruct):
            scope.append(QualType(s.name))

        elif isinstance(s, GenTuNamespace):
            scope.append(QualType(s.name))

    return scope


@beartype
def get_osk_enum(expanded: List[GenTuStruct]) -> GenTuEnum:
    return GenTuEnum(
        t_osk().name,
        GenTuDoc(""),
        fields=[
            GenTuEnumField(struct.name, GenTuDoc(""))
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

    base_map: Mapping[str, GenTuStruct] = {}

    def baseCollectorCallback(value: Any) -> None:
        if isinstance(value, GenTuStruct):
            base_map[value.name] = value

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

                if new.PyName in ["CodeSwitch", "SubtreeProperty", "SubtreePeriod"]:
                    return

                res.Decls.append(new)

        elif isinstance(value, GenTuEnum):
            PyName = "".join(
                [N for N in flat_scope(QualType(value.name, Spaces=scope)) if N != "sem"])
            res.Decls.append(Py11Enum.FromGenTu(value, scope, pyNameOverride=PyName))

    iterate_object_tree(GenTuNamespace("sem", expanded), codegenConstructCallback,
                        iterate_context)

    for item in get_enums() + [get_osk_enum(expanded)]:
        res.Decls.append(Py11Enum.FromGenTu(item, []))

    return res


import proto_lib.reflection_defs as pb


@beartype
def conv_doc_comment(comment: str) -> GenTuDoc:
    if not comment:
        return GenTuDoc("")

    # Helper function to process content after stripping comment markers
    def process_content(content: List[str]) -> GenTuDoc:
        brief, full = [], []
        is_brief = True

        for line in content:
            line = line.strip()
            if not line:
                is_brief = False
                continue

            if is_brief:
                brief.append(line)
            else:
                full.append(line)

        return GenTuDoc('\n'.join(brief), '\n'.join(full))

    def drop_leading(prefix: re.Pattern, text: str) -> List[str]:
        result: List[str] = []
        for line in text.strip().splitlines():
            result.append(re.sub(prefix, "", line))

        return result

    # Identify and strip comment markers, then delegate to process_content
    if comment.startswith("///") or comment.startswith("//!"):
        return process_content(drop_leading("///", comment))
    elif comment.startswith("/**") or comment.startswith("/*!"):
        # Removing the leading /** or /*! and trailing */
        content = comment[3:-2].strip()
        # Remove any '*' prefixes that might exist on each line
        content = '\n'.join(line.lstrip('* ') for line in content.splitlines())
        return process_content(content.splitlines())
    elif comment.startswith("//"):
        return process_content(comment[2:].splitlines())
    elif comment.startswith("/*"):
        # Removing the leading /* and potential trailing */
        content = comment[2:]
        if content.endswith("*/"):
            content = content[:-2]
        content = '\n'.join(line.lstrip('* ') for line in content.splitlines())
        return process_content(content.splitlines())
    else:
        raise ValueError(f"Unrecognized comment style: {comment}")


@beartype
def conv_proto_type(typ: pb.QualType) -> QualType:
    res: QualType = QualType(typ.name)
    for space in typ.spaces:
        res.Spaces.append(conv_proto_type(space))

    for param in typ.parameters:
        res.Parameters.append(conv_proto_type(param))

    res.isConst = typ.is_const
    res.isNamespace = typ.is_namespace
    res.isRef = typ.is_ref

    return res


@beartype
def conv_proto_record(record: pb.Record) -> GenTuStruct:
    result = GenTuStruct(record.name, GenTuDoc(""))
    for field in record.fields:
        result.fields.append(
            GenTuField(type=conv_proto_type(field.type),
                       name=field.name,
                       doc=conv_doc_comment(field.doc)))

    for meth in record.methods:
        if meth.kind != pb.RecordMethodKind.Base:
            continue

        result.methods.append(
            GenTuFunction(
                result=conv_proto_type(meth.return_ty),
                name=meth.name,
                doc=conv_doc_comment(meth.doc),
                arguments=[
                    GenTuIdent(conv_proto_type(arg.type), arg.name) for arg in meth.args
                ]))

    return result


@beartype
def conv_proto_enum(en: pb.Enum) -> GenTuEnum:
    result = GenTuEnum(en.name, GenTuDoc(""), [])
    for field in en.fields:
        result.fields.append(GenTuEnumField(field.name, GenTuDoc("")))

    return result


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

        typeNames: List[str] = []

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
                iteratorMacro.definition.append(f"__IMPL({typeItem})")

            result.append(GenTuPass(ast.Macro(iteratorMacro)))

        if record.variantName and record.enumName:
            result.append(
                GenTuPass(
                    ast.Using(
                        UsingParams(newName=record.variantName,
                                    baseType=QualType(
                                        "variant",
                                        Spaces=[QualType("std")],
                                        Parameters=[QualType(T) for T in typeNames])))))

            result.append(
                GenTuEnum(name=record.enumName,
                          doc=GenTuDoc(""),
                          fields=[GenTuEnumField(N, GenTuDoc("")) for N in typeNames]))

            for idx, T in enumerate(typeNames):
                for isConst in [True, False]:
                    result.append(
                        GenTuFunction(doc=GenTuDoc(""),
                                      name="get" + (T[0].upper() + T[1:]),
                                      result=QualType(T,
                                                      isConst=isConst,
                                                      Spaces=deepcopy(context)),
                                      isConst=isConst,
                                      impl=ast.Return(
                                          ast.XCall("std::get",
                                                    [ast.string(record.variantField)],
                                                    Params=[QualType(str(idx))]))))

            enum_type = QualType(record.enumName, Spaces=context)
            variant_type = QualType(record.variantName, Spaces=context)

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
                converted.append(rec_expand_type(item, context + [QualType(item.name)]))

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

    return [rec_expand_type(T, [QualType("sem"), QualType(T.name)]) for T in types]


@beartype
def update_namespace_annotations(expanded: List[GenTuStruct]):
    iterate_context: Sequence[GenTuStruct] = []

    def callback(value):
        nonlocal iterate_context
        if isinstance(value, QualType):
            if hasattr(value, "isNested"):
                value.Spaces = filter_walk_scope(iterate_context) + value.Spaces

    iterate_object_tree(GenTuNamespace("sem", expanded), callback, iterate_context)


@beartype
def gen_value(ast: ASTBuilder, pyast: pya.ASTBuilder, reflection_path: str) -> GenFiles:
    expanded = expand_type_groups(ast, get_types())
    update_namespace_annotations(expanded)

    full_enums = get_enums() + [get_osk_enum(expanded)]

    unit = pb.TU()
    assert os.path.exists(reflection_path)
    with open(reflection_path, "rb") as f:
        unit = pb.TU.FromString(f.read())

    with open("/tmp/reflection-structs.py", "w") as file:
        pprint(unit, width=200, stream=file)

    gen_structs: List[GenTuStruct] = [conv_proto_record(rec) for rec in unit.records]
    gen_enums: List[GenTuEnum] = [conv_proto_enum(rec) for rec in unit.enums]

    with open("/tmp/reflection_data.py", "w") as file:
        pprint(gen_structs, width=200, stream=file)
        pprint(gen_enums, width=200, stream=file)

    global org_type_names
    org_type_names = [Typ.name for Typ in expanded]

    autogen_structs = get_bind_methods(ast, expanded)

    for item in gen_structs:
        autogen_structs.Decls.append(pybind_nested_type(item, []))

    for item in gen_enums:
        autogen_structs.Decls.append(Py11Enum.FromGenTu(item, []))

    opaque_declarations: List[BlockId] = []
    specialization_calls: List[BlockId] = []

    type_use_context = []
    seen_types: Set[QualType] = set()

    def record_specializations(value: Any):
        nonlocal type_use_context
        if isinstance(value, QualType):

            def rec_type(T: QualType):
                def rec_drop(T: QualType) -> QualType:
                    return replace(T, isConst=False, isRef=False, isPtr=False, isNamespace=False,
                     Spaces=[rec_drop(S) for S in T.Spaces], Parameters=[rec_drop(P) for P in T.Parameters])

                T = rec_drop(T)

                if T in seen_types:
                    return

                else:
                    seen_types.add(T)


                if T.name == "Vec":                      
                    stdvec_t = QualType("vector",
                                        Spaces=[QualType("std")],
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
                "{root}/scripts/py_haxorg/pyhaxorg.pyi",
                [GenTuPass(autogen_structs.build_typedef(pyast))],
            )),
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
        GenUnit(
            GenTu("{base}/exporters/Exporter.tcc", get_exporter_methods(False,
                                                                        expanded))),
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
                        f"    __IMPL({struct.name})"
                        for struct in get_concrete_types(expanded)
                    ])))
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
                    GenTuNamespace("sem", [GenTuTypeGroup(expanded, enumName="")]),
                ],
            )),
    ])


if __name__ == "__main__":
    from pprint import pprint, pformat
    import os
    import sys
    import json

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
                log.info(f"Created dir for {path}")

            opts = TextOptions()
            opts.rightMargin = 160
            newCode = t.toString(result, opts)

            if os.path.exists(path):
                with open(path, "r") as f:
                    oldCode = f.read()

                if oldCode != newCode:
                    with open(path, "w") as out:
                        out.write(newCode)
                    log.info(f"[red]Updated code[/red] in {define.path}")
                else:
                    log.info(f"[green]No changes[/green] on {define.path}")
            else:
                with open(path, "w") as out:
                    out.write(newCode)
                log.info(f"[red]Wrote[/red] to {define.path}")