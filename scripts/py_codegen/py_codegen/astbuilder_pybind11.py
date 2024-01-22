from py_codegen.gen_tu_cpp import *
from beartype import beartype
from dataclasses import dataclass, field
from beartype.typing import List, Optional, NewType

from typing import TYPE_CHECKING

from py_codegen.gen_tu_cpp import (GenTuFunction, GenTuIdent, GenTuDoc, QualType,
                                   QualTypeKind)
import py_codegen.astbuilder_py as pya
import itertools
from rich.pretty import pprint

from py_scriptutils.script_logging import pprint_to_file


@beartype
def maybe_list(it: Any) -> Any:
    if it:
        return [it]
    else:
        return []


if TYPE_CHECKING:
    from py_textlayout.py_textlayout_wrap import BlockId

else:
    BlockId = NewType('BlockId', int)


@beartype
def py_type_bind(Typ: QualType) -> pya.PyType:
    return pya.PyType(Typ.name + ("Of" if Typ.Parameters else "") +
                      "".join([py_type_bind(T).Name for T in Typ.Parameters]))


@beartype
def flat_scope(Typ: QualType) -> List[str]:
    res: List[str] = []
    for S in Typ.Spaces:
        res += flat_scope(S)

    res += [Typ.name]
    return res


@beartype
def py_type(Typ: QualType) -> pya.PyType:
    flat = [N for N in flat_scope(Typ) if N != "sem"]
    match flat:
        case ["Vec"]:
            name = "List"

        case ["Opt"]:
            name = "Optional"

        case ["Str"] | ["string"] | ["std", "string"] | ["basic_string"
                                                        ] | ["std", "basic_string"]:
            name = "str"

        case ["SemIdT"]:
            name = "Sem" + Typ.Parameters[0].name

        case "Bool":
            name = "bool"

        case ["void"]:
            name = "None"

        case ["pybind11", "function"] | ["PyFunc"]:
            name = "function"

        case ["py", "object"] | ["pybind11", "object"]:
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
def get_doc_literal(ast: ASTBuilder, doc: GenTuDoc) -> Optional[BlockId]:
    if doc.brief == "" and doc.full == "":
        return None
    else:
        return ast.StringLiteral(doc.brief +
                                 ("" if doc.full == "" else "\n\n" + doc.full),
                                 forceRawStr=True)


@beartype
def py_ident(name: str) -> str:
    match name:
        case "from":
            return "from_"
        case _:
            return name


@beartype
def id_self(Typ: QualType) -> ParmVarParams:
    return ParmVarParams(Typ, "_self")


@beartype
@dataclass
class Py11Method:
    PyName: str
    CxxName: str
    ResultTy: QualType
    Args: List[GenTuIdent] = field(default_factory=list)
    Body: Optional[List[BlockId]] = None
    Doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    IsConst: bool = False

    @staticmethod
    def FromGenTu(meth: GenTuFunction,
                  Body: Optional[List[BlockId]] = None,
                  pySideOverride: Optional[str] = None) -> 'Py11Method':

        if meth.name == "enableFileTrace":
            pprint_to_file(meth, "/tmp/enableFileTrace_FromGenTu.py")

        return Py11Method(PyName=meth.name if pySideOverride is None else pySideOverride,
                          Body=Body,
                          ResultTy=meth.result,
                          CxxName=meth.name,
                          Doc=meth.doc,
                          IsConst=meth.isConst,
                          Args=meth.arguments)

    def build_typedef(self, ast: pya.ASTBuilder) -> pya.MethodParams:
        return pya.MethodParams(Func=pya.FunctionDefParams(
            Name=self.PyName,
            ResultTy=py_type(self.ResultTy),
            Args=[pya.IdentParams(py_type(Arg.type), Arg.name) for Arg in self.Args],
            IsStub=True))

    def build_bind(self, Class: QualType, ast: ASTBuilder) -> BlockId:
        if self.CxxName == "enableFileTrace":
            pprint_to_file(self, "/tmp/enableFileTrace_build_bind.py")

        b = ast.b
        if self.Body is None:
            function_type = QualType(func=QualType.Function(
                ReturnTy=self.ResultTy,
                Args=[A.type for A in self.Args],
                Class=Class,
                IsConst=self.IsConst,
            ),
                                     Kind=QualTypeKind.FunctionPtr)
            call_pass = ast.XCall(
                "static_cast",
                args=[ast.Addr(ast.Scoped(Class, ast.string(self.CxxName)))],
                Params=[function_type])

        else:
            function_type = None
            call_pass = ast.Lambda(
                LambdaParams(
                    ResultTy=self.ResultTy,
                    Args=[ParmVarParams(Class, "_self")] +
                    [ParmVarParams(Arg.type, Arg.name) for Arg in self.Args],
                    Body=self.Body,
                ))

        argument_binder = [
            ast.XCall("pybind11::arg", [ast.Literal(Arg.name)]) if Arg.value is None else
            ast.XCall("pybind11::arg_v",
                      [ast.Literal(Arg.name), b.text(Arg.value)]) for Arg in self.Args
        ]

        doc_comment = [ast.StringLiteral(self.Doc.brief, forceRawStr=True)
                      ] if self.Doc.brief else []

        return ast.XCall(
            ".def",
            [
                ast.Literal(self.PyName),
                call_pass,
                *argument_binder,
                *doc_comment,
            ],
            Line=len(self.Args) == 0,
        )


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
            ast.Type(QualType.ForName(self.CxxName, Spaces=[Enum.Enum]))
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
        return Py11Enum(
            PyName="".join(flat_scope(QualType.ForName(Enum.name.name, Spaces=Scope)))
            if pyNameOverride is None else pyNameOverride,
            Enum=QualType.ForName(Enum.name.name, Spaces=Scope),
            Doc=Enum.doc,
            Fields=[Py11EnumField.FromGenTu(F) for F in Enum.fields],
        )

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
@dataclass
class Py11Field:
    PyName: str
    CxxName: str
    Type: QualType
    GetImpl: Optional[List[BlockId]] = None
    SetImpl: Optional[List[BlockId]] = None
    Doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))

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

    @staticmethod
    def FromGenTu(value: GenTuStruct, pyNameOveride: Optional[str] = None) -> 'Py11Class':
        res = Py11Class(PyName=pyNameOveride or py_type(value.name).Name,
                        Class=value.name)
        res.InitDefault()

        for base in value.bases:
            res.Bases.append(base)

        for meth in value.methods:
            res.Methods.append(Py11Method.FromGenTu(meth))

        for _field in value.fields:
            res.Fields.append(Py11Field.FromGenTu(_field))

        return res

    def InitDefault(self):
        self.InitImpls.append(Py11Method("", "", QualType.ForName("")))

    def AddInit(self, Args: List[ParmVarParams], Impl: List[BlockId]):
        self.InitImpls.append(Py11Method("", "", QualType.ForName(""), Args, Body=Impl))

    def dedup_methods(self) -> List[Py11Method]:
        res: List[Py11Method] = []
        for key, _group in itertools.groupby(self.Methods, lambda M: (M.CxxName, M.Args)):
            group: List[Py11Method] = list(_group)
            if len(group) == 1:
                res.append(group[0])

            elif len(group) == 2 and group[1].Args == group[0].Args:
                res.append(group[0 if group[1].IsConst else 1])

            else:
                print(len(group))
                pass

        return res

    def build_typedef(self, ast: pya.ASTBuilder) -> pya.ClassParams:
        res = pya.ClassParams(Name=self.PyName, Bases=[py_type(T) for T in self.Bases])
        for Meth in self.dedup_methods():
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

        for Meth in self.dedup_methods():
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

        for _enum in [E for E in self.Decls if isinstance(E, Py11Enum)]:
            passes.append(ast.Enum(_enum.build_typedef()))
            passes.append(ast.string(""))

        for _class in [E for E in self.Decls if isinstance(E, Py11Class)]:
            passes.append(ast.string(f"{_class.PyName}: Type"))

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

        for _class in [E for E in self.Decls if isinstance(E, Py11Class)]:
            passes.append(ast.Class(_class.build_typedef(ast)))
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
