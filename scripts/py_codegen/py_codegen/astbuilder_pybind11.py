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
    return pya.PyType(
        "".join([py_type_bind(T).Name for T in Typ.withoutSpace("sem").Spaces]) +
        Typ.name + ("Of" if Typ.Parameters else "") +
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

        case ["Opt"] | ["std", "optional"]:
            name = "Optional"

        case ["std", "variant"] | ["Var"]:
            name = "Union"

        case ["Str"] | ["string"] | ["std", "string"] | ["basic_string"
                                                        ] | ["std", "basic_string"]:
            name = "str"

        case ["SemId"]:
            name = Typ.Parameters[0].name

        case "Bool":
            name = "bool"

        case ["void"]:
            name = "None"

        case ["pybind11", "function"] | [*_, "PyFunc"]:
            name = "function"

        case ["py", "object"] | ["pybind11", "object"]:
            name = "object"

        case ["UnorderedMap"]:
            name = "Dict"

        case _:
            name = "".join(flat)

    res = pya.PyType(name)
    if Typ.name != "SemId":
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
        case "from" | "is":
            return name + "_"

        case _:
            return name


@beartype
def id_self(Typ: QualType) -> ParmVarParams:
    return ParmVarParams(Typ, "_self")


@beartype
@dataclass
class Py11Function:
    PyName: str
    CxxName: str
    ResultTy: QualType
    Args: List[GenTuIdent] = field(default_factory=list)
    Body: Optional[List[BlockId]] = None
    Doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    DefParams: Optional[List[BlockId]] = None
    Spaces: List[QualType] = field(default_factory=list)

    def build_typedef(self, ast: pya.ASTBuilder) -> pya.FunctionDefParams:
        return pya.FunctionDefParams(
            Name=py_ident(self.PyName),
            ResultTy=py_type(self.ResultTy),
            Args=[pya.IdentParams(py_type(Arg.type), Arg.name) for Arg in self.Args],
            IsStub=True,
        )

    @staticmethod
    def FromGenTu(
        meth: GenTuFunction,
        Body: Optional[List[BlockId]] = None,
        pySideOverride: Optional[str] = None,
    ) -> 'Py11Function':

        return Py11Function(
            PyName=py_ident(meth.name) if pySideOverride is None else pySideOverride,
            Body=Body,
            ResultTy=meth.result,
            CxxName=meth.name,
            Doc=meth.doc,
            Args=meth.arguments,
            Spaces=meth.spaces,
        )

    def build_argument_binder(self, Args: List[GenTuIdent],
                              ast: ASTBuilder) -> list[BlockId]:
        argument_binder: list[BlockId] = []
        b = ast.b

        for Arg in Args:
            if Arg.type.name == "kwargs":
                continue

            elif Arg.value is None:
                argument_binder.append(ast.XCall("pybind11::arg",
                                                 [ast.Literal(Arg.name)]))

            else:
                argument_binder.append(
                    ast.XCall("pybind11::arg_v", [
                        ast.Literal(Arg.name),
                        b.text(Arg.value) if isinstance(Arg.value, str) else Arg.value,
                    ]))

        return argument_binder

    def build_call_pass(
        self,
        ast: ASTBuilder,
        Args: List[GenTuIdent],
        FunctionQualName: BlockId,
        Class: Optional[QualType] = None,
        IsConst: bool = False,
    ) -> BlockId:
        if self.Body is None:
            function_type = QualType(
                func=QualType.Function(
                    ReturnTy=self.ResultTy,
                    Args=[A.type for A in Args],
                    Class=Class,
                    IsConst=IsConst,
                ),
                Kind=QualTypeKind.FunctionPtr,
            )

            return ast.XCall(
                "static_cast",
                args=[ast.Addr(FunctionQualName)],
                Params=[function_type],
            )

        else:
            return ast.Lambda(
                LambdaParams(
                    ResultTy=self.ResultTy,
                    Args=[ParmVarParams(Arg.type, Arg.name) for Arg in Args],
                    Body=self.Body,
                    IsLine=False,
                ))

    def build_doc_comment(self, ast: ASTBuilder) -> list[BlockId]:
        if self.Doc.brief:
            return [ast.StringLiteral(self.Doc.brief, forceRawStr=True)]

        else:
            return []

    def build_bind(self, ast: ASTBuilder) -> BlockId:
        if self.Spaces:
            full_name = ast.Scoped(
                QualType(name=self.Spaces[0].name, Spaces=self.Spaces[1:]),
                ast.string(self.CxxName))

        else:
            full_name = ast.string(self.CxxName)

        return ast.XCall(
            "m.def",
            [
                ast.Literal(self.PyName),
                self.build_call_pass(
                    ast,
                    self.Args,
                    FunctionQualName=full_name,
                ),
                *self.build_argument_binder(self.Args, ast),
                *self.build_doc_comment(ast),
                *(self.DefParams if self.DefParams else []),
            ],
            Line=len(self.Args) == 0,
            Stmt=True,
        )


@beartype
@dataclass
class Py11Method(Py11Function):
    IsConst: bool = False
    IsInit: bool = False
    ExplicitClassParam: bool = False

    @staticmethod
    def FromGenTu(
        meth: GenTuFunction,
        Body: Optional[List[BlockId]] = None,
        pySideOverride: Optional[str] = None,
    ) -> 'Py11Method':

        return Py11Method(
            PyName=py_ident(meth.name) if pySideOverride is None else pySideOverride,
            Body=Body,
            ResultTy=meth.result,
            CxxName=meth.name,
            Doc=meth.doc,
            IsConst=meth.isConst,
            Args=meth.arguments,
        )

    def build_typedef(self, ast: pya.ASTBuilder) -> pya.MethodParams:
        return pya.MethodParams(Func=pya.FunctionDefParams(
            Name=py_ident(self.PyName),
            ResultTy=py_type(self.ResultTy),
            Args=[pya.IdentParams(py_type(Arg.type), Arg.name) for Arg in self.Args],
            IsStub=True,
        ))

    def build_bind(self, Class: QualType, ast: ASTBuilder) -> BlockId:
        b = ast.b

        Args: List[GenTuIdent] = []
        if self.IsInit or self.ExplicitClassParam:
            pass

        elif self.Body:
            Args = [GenTuIdent(type=Class, name="_self")]

        Args += self.Args

        call_pass = self.build_call_pass(
            ast,
            FunctionQualName=ast.Scoped(Class, ast.string(self.CxxName)),
            Class=Class,
            IsConst=self.IsConst,
            Args=Args,
        )

        if self.IsInit:
            call_pass = ast.XCall("pybind11::init", args=[call_pass])

        if self.ExplicitClassParam and not self.IsInit:
            argument_binder = self.build_argument_binder(self.Args[1:], ast=ast)
        else:
            argument_binder = self.build_argument_binder(self.Args, ast=ast)

        return ast.XCall(
            ".def",
            [
                *([] if self.IsInit else [ast.Literal(self.PyName)]),
                call_pass,
                *argument_binder,
                *self.build_doc_comment(ast),
                *(self.DefParams if self.DefParams else []),
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
    def FromGenTu(Enum: GenTuEnum, PyName: str) -> 'Py11Enum':
        return Py11Enum(
            PyName=PyName,
            Enum=Enum.name,
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
        iter_type = QualType(name="PyEnumIterator", Parameters=[self.Enum])
        return b.stack([
            ast.XCall(
                "bind_enum_iterator",
                args=[b.text("m"), ast.Literal(self.PyName)],
                Params=[self.Enum],
                Stmt=True,
            ),
            ast.XCall(
                "pybind11::enum_",
                [b.text("m"), ast.Literal(self.PyName)],
                Params=[self.Enum],
            ),
            b.indent(
                2,
                b.stack([Field.build_bind(self, ast) for Field in self.Fields] + [
                    Py11Method(
                        PyName="__iter__",
                        CxxName="",
                        ResultTy=iter_type,
                        Body=[
                            ast.string("return "),
                            ast.Type(iter_type),
                            ast.string("();"),
                        ],
                    ).build_bind(self.Enum, ast)
                ] + [b.text(";")]),
            )
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
    Default: Optional[Union[BlockId, str]] = None

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
            SetImpl=SetImpl,
            Default=Field.value,
        )

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
    PyHolderType: Optional[QualType] = None
    Fields: List[Py11Field] = field(default_factory=list)
    Methods: List[Py11Method] = field(default_factory=list)
    InitImpls: List[Py11Method] = field(default_factory=list)

    @staticmethod
    def FromGenTu(ast: ASTBuilder,
                  value: GenTuStruct,
                  pyNameOveride: Optional[str] = None) -> 'Py11Class':
        res = Py11Class(
            PyName=pyNameOveride or py_type(value.name).Name,
            Class=value.name,
        )

        for base in value.bases:
            res.Bases.append(base)

        for meth in value.methods:
            res.Methods.append(Py11Method.FromGenTu(meth))

        for _field in value.fields:
            res.Fields.append(Py11Field.FromGenTu(_field))

        return res

    def InitDefault(self, ast: ASTBuilder, Fields: List[Py11Field]):

        def to_arg(f: Py11Field) -> GenTuIdent:
            value = f.Default
            if f.Type.name == "Vec" and f.Default == "{}":
                value = ast.b.line([ast.Type(f.Type), ast.string("{}")])

            elif f.Type.name == "UnorderedMap" and not f.Default:
                value = ast.b.line([ast.Type(f.Type), ast.string("{}")])

            elif f.Type.name in ["Str", "string"] and not f.Default:
                value = ast.Literal("")

            return GenTuIdent(type=f.Type, name=f.PyName, value=value)

        self.InitImpls.append(
            Py11Method(
                "",
                "",
                self.Class,
                Args=[
                    GenTuIdent(
                        QualType(
                            name="kwargs",
                            Spaces=[QualType.ForName("pybind11")],
                            isConst=True,
                            RefKind=ReferenceKind.LValue,
                        ), "kwargs")
                ],
                Body=[
                    ast.b.line([ast.Type(self.Class),
                                ast.string(" result{};")]),
                    ast.XCall(
                        "init_fields_from_kwargs",
                        args=[ast.string("result"),
                              ast.string("kwargs")],
                        Stmt=True,
                    ),
                    ast.Return(ast.string("result")),
                ],
                IsInit=True,
                ExplicitClassParam=True,
            ))

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
            sub.append(Init.build_bind(self.Class, ast))

        for Field in self.Fields:
            sub.append(Field.build_bind(self.Class, ast))

        for Meth in self.dedup_methods():
            sub.append(Meth.build_bind(self.Class, ast))

        sub.append(b.text(";"))

        return b.stack([
            ast.XCall(
                "pybind11::class_",
                [b.text("m"), ast.Literal(self.PyName)],
                Params=[self.Class] + ([self.PyHolderType] if self.PyHolderType else []) +
                self.Bases,
            ),
            b.indent(2, b.stack(sub))
        ])


@beartype
@dataclass
class Py11BindPass:
    Id: BlockId


@beartype
@dataclass
class Py11TypedefPass:
    name: pya.PyType
    base: pya.PyType


Py11Entry = Union[Py11Enum, Py11Class, Py11BindPass, Py11TypedefPass, Py11Function]


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

        for item in self.Decls:
            match item:
                case Py11Enum():
                    passes.append(ast.Enum(item.build_typedef()))
                    passes.append(ast.string(""))

                case Py11Class():
                    passes.append(ast.Class(item.build_typedef(ast)))
                    passes.append(ast.string(""))

                case Py11Function():
                    passes.append(ast.Function(item.build_typedef(ast)))
                    passes.append(ast.string(""))

                case Py11TypedefPass():
                    passes.append(
                        ast.b.line([
                            ast.Type(item.name),
                            ast.b.text(" = "),
                            ast.Type(item.base),
                        ]))

                case Py11BindPass() | int():
                    pass

                case _:
                    assert False, type(item)

        return ast.b.stack(passes)

    def build_bind(self, ast: ASTBuilder) -> BlockId:
        b = ast.b

        passes: List[BlockId] = []

        for entry in self.Decls:
            match entry:
                case Py11BindPass():
                    passes.append(entry.Id)

                case Py11Class():
                    passes.append(entry.build_bind(ast))

                case Py11Enum():
                    passes.append(entry.build_bind(ast))

                case Py11Function():
                    passes.append(entry.build_bind(ast))

                case int() | Py11TypedefPass():
                    pass

                case _:
                    assert False, type(entry)

        return b.stack([
            *self.Before,
            b.text("PYBIND11_MODULE(pyhaxorg, m) {"),
            b.indent(2, b.stack(passes)),
            b.text("}"), *self.After
        ])
