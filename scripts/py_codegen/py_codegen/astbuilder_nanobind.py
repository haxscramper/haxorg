from dataclasses import dataclass, field, replace
import itertools

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Union
from py_codegen import codegen_ir
import py_codegen.astbuilder_cpp as cpp
import py_codegen.astbuilder_py as pya
from py_codegen.astbuilder_nanobind_config import NanobindAstbuilderConfig
from py_codegen.codegen_ir import GenTuDoc, GenTuFunction, GenTuIdent, QualType
from py_haxorg.layout.wrap import BlockId
from py_scriptutils.algorithm import maybe_splice
from py_scriptutils.script_logging import log

CAT = __name__


@beartype
def maybe_list(it: Any) -> Any:
    if it:
        return [it]
    else:
        return []


@beartype
def get_doc_literal(ast: cpp.ASTBuilder, doc: GenTuDoc) -> Optional[BlockId]:
    if doc.brief == "" and doc.full == "":
        return None
    else:
        return ast.StringLiteral(doc.brief +
                                 ("" if doc.full == "" else "\n\n" + doc.full),
                                 forceRawStr=True)


@beartype
def id_self(Typ: QualType) -> cpp.ParmVarParams:
    return cpp.ParmVarParams(Typ, "_self")


@beartype
@dataclass
class NbFunction:
    "Intermediate representation for the C++ function wrapped for nanobind"
    PyName: str
    "Final python name for wrapper"
    Func: GenTuFunction
    "Original C++ function"
    Body: Optional[List[BlockId]] = None
    """
    Extra logic for the wrapper body -- if present the function would be
    wrapped as lambda.
    """
    DefParams: Optional[List[BlockId]] = None
    "Additional parameters for the `.def` call in nanobind module"

    def build_typedef(self, ast: pya.ASTBuilder) -> pya.FunctionDefParams:
        "Get type stub for the wrapper"
        return pya.FunctionDefParams(
            Name=self.conf.getSanitizedIdent(self.PyName),
            ResultTy=self.conf.getBackendType(self.Func.ReturnType)
            if self.Func.ReturnType else None,
            Args=[
                pya.IdentParams(self.conf.getBackendType(Arg.Type), Arg.Name)
                for Arg in self.Func.Args
            ],
            IsStub=True,
        )

    def __init__(
        self,
        Func: GenTuFunction,
        conf: NanobindAstbuilderConfig,
        Body: Optional[List[BlockId]] = None,
        PyName: Optional[str] = None,
        DefParams: Optional[List[BlockId]] = None,
    ):
        name = ""

        if PyName:
            name = PyName

        elif Func.ReflectionParams.wrapper_name:
            name = Func.ReflectionParams.wrapper_name

        else:
            name = conf.getSanitizedIdent(Func.Name + (
                ("_static" if "_" in Func.Name else "Static") if Func.IsStatic else ""))

        self.PyName = name
        self.Body = Body
        self.Func = Func
        self.DefParams = DefParams
        self.conf = conf

    def build_argument_binder(self, Args: List[GenTuIdent],
                              ast: cpp.ASTBuilder) -> list[BlockId]:
        "Generate nanobind wrapper block exposing the original function arguments"
        argument_binder: list[BlockId] = []
        b = ast.b

        for Arg in Args:
            if Arg.Type.Name == "kwargs":
                continue

            elif Arg.Value is None:
                argument_binder.append(ast.XCall("nanobind::arg",
                                                 [ast.Literal(Arg.Name)]))

            else:
                argument_binder.append(
                    ast.line([
                        ast.XCall("nanobind::arg", [ast.Literal(Arg.Name)]),
                        b.text(" = "),
                        b.text(Arg.Value) if isinstance(Arg.Value, str) else Arg.Value
                    ]))

        return argument_binder

    def build_call_pass(
        self,
        ast: cpp.ASTBuilder,
        Args: List[GenTuIdent],
        FunctionQualName: BlockId,
        Class: Optional[QualType] = None,
        IsConst: bool = False,
    ) -> BlockId:
        "Generate nanobind wrapper block passing the function to the `.def*`"
        if self.Body is None:
            function_type = self.Func.get_function_type(Class=Class)

            return ast.XCall(
                "static_cast",
                args=[ast.Addr(FunctionQualName)],
                Params=[function_type],
            )

        else:
            return ast.Lambda(
                cpp.LambdaParams(
                    ResultTy=self.Func.ReturnType,
                    Args=[cpp.ParmVarParams(Arg.Type, Arg.Name) for Arg in Args],
                    Body=self.Body,
                    IsLine=False,
                ))

    def build_doc_comment(self, ast: cpp.ASTBuilder) -> list[BlockId]:
        "Create python docstring"
        if self.Func.Doc.brief:
            return [ast.StringLiteral(self.Func.Doc.brief, forceRawStr=True)]

        else:
            return []

    def build_bind(self, ast: cpp.ASTBuilder) -> BlockId:
        "Return nanobind block wrapping the C++ function"
        if self.Func.spaces:
            full_name = ast.Scoped(
                QualType(Name=self.Func.spaces[-1].Name, Spaces=self.Func.spaces[:-1]),
                ast.string(self.Func.Name))

        else:
            full_name = ast.string(self.Func.Name)

        return ast.XCall(
            "m.def",
            [
                ast.Literal(self.PyName),
                self.build_call_pass(
                    ast,
                    self.Func.Args,
                    FunctionQualName=full_name,
                ),
                *self.build_argument_binder(self.Func.Args, ast),
                *self.build_doc_comment(ast),
                *(self.DefParams if self.DefParams else []),
            ],
            Line=len(self.Func.Args) == 0,
            Stmt=True,
        )


@beartype
@dataclass
class NbMethod(NbFunction):
    "Nanobind-wrapped C++ method"
    HasExplicitClassParam: bool = False
    "Whether the function arguments will explicitly provide a custom class parameter"

    def __init__(
        self,
        Func: GenTuFunction,
        conf: NanobindAstbuilderConfig,
        Body: Optional[List[BlockId]] = None,
        PyName: Optional[str] = None,
        HasExplicitClassParam: bool = False,
        DefParams: Optional[List[BlockId]] = None,
    ):
        super().__init__(Func, conf, Body, PyName, DefParams=DefParams)
        self.HasExplicitClassParam = HasExplicitClassParam

    def build_typedef(  # type: ignore[override]
        self,
        ast: pya.ASTBuilder,
        is_overload: bool = False,
    ) -> pya.MethodParams:
        "Generate typedef for C++ method"
        def_params = pya.FunctionDefParams(
            Name="__init__"
            if self.Func.IsConstructor else self.conf.getSanitizedIdent(self.PyName),
            ResultTy=self.Func.ReturnType and
            self.conf.getBackendType(self.Func.ReturnType),
            Args=[
                pya.IdentParams(self.conf.getBackendType(Arg.Type), Arg.Name)
                for Arg in self.Func.Args
            ],
            IsStub=True,
            Decorators=[
                *maybe_splice(self.Func.IsStatic, pya.DecoratorParams("staticmethod")),
                *maybe_splice(is_overload, pya.DecoratorParams("overload")),
            ])

        if self.Func.Name == "operator==":
            def_params.Args[0].Type = QualType(Name="object")

        return pya.MethodParams(Func=def_params, IsStatic=self.Func.IsStatic)

    def build_bind(self, Class: QualType, ast: cpp.ASTBuilder) -> BlockId:
        "Generate binding block for C++ method"
        b = ast.b

        Args: List[GenTuIdent] = []
        if self.Func.IsConstructor or self.HasExplicitClassParam:
            pass

        elif self.Body:
            Args = [GenTuIdent(Type=Class.asConstRef(), Name="_self")]

        Args += self.Func.Args

        if self.Func.IsConstructor and not self.Body:
            call_pass = ast.XCall("nanobind::init",
                                  Params=[t.Type for t in self.Func.Args])
            argument_binder = []

        else:
            call_pass = self.build_call_pass(
                ast,
                FunctionQualName=ast.Scoped(Class, ast.string(self.Func.Name)),
                Class=None if self.Func.IsStatic else Class,
                IsConst=self.Func.IsConst,
                Args=Args,
            )

            if self.HasExplicitClassParam and not self.Func.IsConstructor:
                argument_binder = self.build_argument_binder(self.Func.Args[1:], ast=ast)
            else:
                argument_binder = self.build_argument_binder(self.Func.Args, ast=ast)

        if self.Func.IsStatic and not self.Func.IsConstructor:
            bind_head = ".def_static"

        else:
            bind_head = ".def"

        if self.Func.IsConstructor:
            if self.Body:
                function_name = [ast.Literal("__init__")]

            else:
                function_name = []

        else:
            function_name = [ast.Literal(self.PyName)]

        return ast.XCall(
            bind_head,
            [
                *function_name,
                call_pass,
                *argument_binder,
                *self.build_doc_comment(ast),
                *(self.DefParams if self.DefParams else []),
            ],
            Line=len(self.Func.Args) == 0,
        )


@beartype
@dataclass
class NbEnumField:
    "Wrapped C++ enum field"
    PyName: str
    "Wrapped python name"
    CxxName: str
    "Original C++ field name"
    Doc: GenTuDoc
    "Documentation for the field"

    def __init__(
        self,
        Field: codegen_ir.GenTuEnumField,
        pyNameOverride: Optional[str] = None,
    ):
        self.PyName = Field.Name if pyNameOverride is None else pyNameOverride
        self.CxxName = Field.Name
        self.Doc = Field.Doc

    def build_bind(self, Enum: 'NbEnum', ast: cpp.ASTBuilder) -> BlockId:
        "Generate binding block for enum field"
        return ast.XCall(".value", [
            ast.Literal(self.PyName),
            ast.Type(QualType.ForName(self.CxxName, Spaces=[Enum.Enum.Name]))
        ] + maybe_list(get_doc_literal(ast, self.Doc)))


@beartype
@dataclass
class NbEnum:
    "Wrapped C++ enum"
    Enum: codegen_ir.GenTuEnum
    "Original C++ enum"
    Fields: List[NbEnumField]
    "Wrapped enum fields"

    def __init__(self, Enum: codegen_ir.GenTuEnum,
                 conf: NanobindAstbuilderConfig) -> None:
        self.Enum = Enum
        self.Fields = [NbEnumField(F) for F in Enum.Fields]
        self.conf = conf

    def getPyName(self) -> str:
        return self.conf.getBackendType(self.Enum.Name).Name

    def build_typedef(self) -> pya.EnumParams:
        count = 0
        return pya.EnumParams(
            Name=self.getPyName(),
            Fields=[
                pya.EnumFieldParams(
                    ("_" +
                     F.PyName if F.PyName in ["None", "True", "False"] else F.PyName),
                    str(count := count + 1)) for F in self.Fields
            ])

    def build_bind(self, ast: cpp.ASTBuilder) -> BlockId:
        "Generate wrapped enum binding"
        b = ast.b
        iter_type = QualType(
            Name="PyEnumIterator",
            Params=[self.Enum.Name],
            Spaces=[
                codegen_ir.n_org(),
                codegen_ir.t_namespace("bind"),
                codegen_ir.t_namespace("python")
            ],
        )
        return b.stack([
            ast.XCall(
                "bind_enum_iterator",
                args=[
                    b.text("m"),
                    ast.Literal(self.getPyName()),
                    ast.string("type_registry_guard"),
                ],
                Params=[self.Enum.Name],
                Stmt=True,
            ),
            ast.XCall(
                "nanobind::enum_",
                [b.text("m"), ast.Literal(self.getPyName())],
                Params=[self.Enum.Name],
            ),
            b.indent(
                2,
                b.stack([Field.build_bind(self, ast) for Field in self.Fields] + [
                    NbMethod(
                        conf=self.conf,
                        PyName="__iter__",
                        Func=GenTuFunction(Name="", ReturnType=iter_type),
                        Body=[
                            ast.Return(ast.b.line([ast.Type(iter_type),
                                                   ast.string("()")])),
                        ],
                    ).build_bind(self.Enum.Name, ast),
                    NbMethod(
                        conf=self.conf,
                        PyName="__int__",
                        Func=GenTuFunction(
                            Name="",
                            ReturnType=QualType(Name="int"),
                        ),
                        Body=[
                            ast.Return(
                                ast.XCall("static_cast",
                                          args=[ast.string("_self")],
                                          Params=[
                                              QualType(Name="int"),
                                          ]))
                        ],
                    ).build_bind(self.Enum.Name, ast),
                    NbMethod(
                        conf=self.conf,
                        PyName="__index__",
                        Func=GenTuFunction(
                            Name="",
                            ReturnType=QualType(Name="int"),
                        ),
                        Body=[
                            ast.Return(
                                ast.XCall("static_cast",
                                          args=[ast.string("_self")],
                                          Params=[
                                              QualType(Name="int"),
                                          ]))
                        ],
                    ).build_bind(self.Enum.Name, ast),
                    NbMethod(
                        conf=self.conf,
                        PyName="__eq__",
                        Func=GenTuFunction(
                            Name="",
                            ReturnType=QualType(Name="bool"),
                            Args=[
                                GenTuIdent(self.Enum.Name, "lhs"),
                                GenTuIdent(self.Enum.Name, "rhs"),
                            ],
                        ),
                        Body=[
                            ast.Return(
                                ast.XCall("==", [ast.string("lhs"),
                                                 ast.string("rhs")])),
                        ],
                        HasExplicitClassParam=True,
                    ).build_bind(self.Enum.Name, ast),
                    NbMethod(
                        conf=self.conf,
                        PyName="__hash__",
                        Func=GenTuFunction(
                            ReturnType=QualType(Name="int"),
                            Args=[GenTuIdent(self.Enum.Name, "it")],
                        ),
                        Body=[
                            ast.Return(
                                ast.XCall("static_cast", [ast.string("it")],
                                          Params=[QualType(Name="int")])),
                        ],
                        HasExplicitClassParam=True,
                    ).build_bind(self.Enum.Name, ast),
                ] + [b.text(";")]),
            )
        ])


@beartype
@dataclass
class Py11Field:
    """
    Wrapped C++ class field
    """
    Field: codegen_ir.GenTuField
    "Original C++ class field"
    GetImpl: Optional[List[BlockId]] = None
    "Optional body for the getter callback for the field"
    SetImpl: Optional[List[BlockId]] = None
    "Optional body for the setter callback for the field"

    def getPyName(self) -> str:
        return self.conf.getSanitizedIdent(self.Field.Name)

    def __init__(self,
                 Field: codegen_ir.GenTuField,
                 conf: NanobindAstbuilderConfig,
                 GetImpl: Optional[List[BlockId]] = None,
                 SetImpl: Optional[List[BlockId]] = None):

        self.conf = conf
        self.Field = Field
        self.GetImpl = GetImpl
        self.SetImpl = SetImpl

    def build_typedef(self, ast: pya.ASTBuilder) -> pya.FieldParams:
        if self.Field.Type is None:
            raise ValueError(f"Field {self.Field.Name} has no type")
        return pya.FieldParams(self.conf.getBackendType(self.Field.Type),
                               self.getPyName())

    def build_bind(self, Class: QualType, ast: cpp.ASTBuilder) -> BlockId:
        "Generate binding block for field"
        b = ast.b
        _self = id_self(Class)
        if self.GetImpl and self.SetImpl:
            assert self.Field.Type
            return ast.XCall(
                ".def_prop_rw",
                [
                    ast.Literal(self.getPyName()),
                    ast.Lambda(
                        cpp.LambdaParams(
                            ResultTy=self.Field.Type,
                            Body=self.GetImpl,
                            Args=[_self],
                        )),
                    ast.Lambda(
                        cpp.LambdaParams(
                            ResultTy=None,
                            Body=[b.text(f"{_self.name}->{self.Field.Name} = _arg;")],
                            Args=[_self,
                                  cpp.ParmVarParams(self.Field.Type, "_arg")],
                        )),
                ],
                Line=False,
            )
        else:
            return ast.XCall(".def_rw", [
                ast.Literal(self.getPyName()),
                b.line([
                    b.text("&"),
                    ast.Type(Class),
                    b.text("::"),
                    b.text(self.Field.Name)
                ]), *maybe_list(get_doc_literal(ast, self.Field.Doc))
            ])


@beartype
class NbClass:
    "C++ class wrapped for the binding generation"
    Struct: codegen_ir.GenTuStruct
    "Original C++ class/structure/union"
    Fields: List[Py11Field]
    "Wrapped fields"
    Methods: List[NbMethod]
    "Wrapped methods excluding constructor"
    InitImpls: List[NbMethod]
    "Constructor implementations"

    def getPyName(self) -> str:
        "Get python name for the wrapped C++ class"
        return self.Struct.ReflectionParams.wrapper_name or self.conf.getBackendType(
            self.Struct.Name).Name

    def getCxxName(self) -> QualType:
        "Get original C++ name"
        return self.Struct.declarationQualName()

    def getEntryForName(self, name: str) -> Any:
        result = list()

        for m in self.Methods:
            if m.PyName == name:
                result.append(m)

        for f in self.Fields:
            if f.getPyName() == name:
                result.append(f)

        return result

    def __init__(self, ast: cpp.ASTBuilder, value: codegen_ir.GenTuStruct,
                 conf: NanobindAstbuilderConfig) -> None:
        self.Struct = value
        self.Fields = []
        self.Methods = []
        self.InitImpls = []
        self.conf = conf

        for meth in value.Methods:
            if meth.IsExposedForWrap:
                if meth.IsConstructor:
                    self.InitImpls.append(NbMethod(meth, conf))
                else:
                    self.Methods.append(NbMethod(meth, conf))

        for _field in value.Fields:
            if _field.IsExposedForWrap:
                self.Fields.append(Py11Field(_field, conf))

        if not value.IsAbstract and value.ReflectionParams.default_constructor:
            self.InitDefault(ast, filter_init_fields(self.Fields))

        self.InitMagicMethods(ast=ast)

    def InitDefault(self, ast: cpp.ASTBuilder, Fields: List[Py11Field]) -> None:
        "Generate default constructor for the class"
        # FIXME Undocumented logic affecting the code generation
        # features -- the type can be marked as a reflection target
        # in the source code, but the default init is not generated
        # here -- provide 'else' fallback, and/or diagnostics for
        # missing reflection description.
        if self.Struct.IsDescribedRecord:
            body_impl = []
            result_type = self.getCxxName()
            body_impl.append(
                ast.b.line([
                    ast.string("new(result) "),
                    ast.Type(self.getCxxName()),
                    ast.string("();"),
                ]))

            body_impl.append(
                ast.XCall(
                    "org::bind::python::init_fields_from_kwargs",
                    args=[ast.string("*result"),
                          ast.string("kwargs")],
                    Stmt=True,
                ))

            self.InitImpls.append(
                NbMethod(
                    PyName="",
                    conf=self.conf,
                    Func=GenTuFunction(
                        Name="",
                        Args=[
                            GenTuIdent(result_type.asPtr(), "result"),
                            GenTuIdent(
                                QualType(
                                    Name="kwargs",
                                    Spaces=[QualType.ForName("nanobind")],
                                    IsConst=True,
                                    RefKind=codegen_ir.ReferenceKind.LValue,
                                ), "kwargs")
                        ],
                        IsConstructor=True,
                    ),
                    Body=body_impl,
                    HasExplicitClassParam=True,
                ))

    def InitMagicMethods(self, ast: cpp.ASTBuilder) -> None:
        """
        Init magic methods for `__repr__`, `__getattr__` etc.
        """
        str_type = QualType.ForName("string", Spaces=[QualType.ForName("std")])
        pyobj_type = QualType.ForName("object", Spaces=[QualType.ForName("nanobind")])

        if not self.Struct.IsAbstract:
            if self.Struct.IsDescribedRecord:
                self.Methods.append(
                    NbMethod(
                        conf=self.conf,
                        PyName="__repr__",
                        Func=GenTuFunction(
                            Name="",
                            ReturnType=str_type,
                        ),
                        Body=[
                            ast.Return(
                                ast.XCall("org::bind::python::py_repr_impl",
                                          args=[ast.string("_self")])),
                        ],
                    ))

                self.Methods.append(
                    NbMethod(
                        PyName="__getattr__",
                        conf=self.conf,
                        Func=GenTuFunction(
                            Name="",
                            ReturnType=pyobj_type,
                            Args=[GenTuIdent(str_type.asConstRef(), "name")],
                        ),
                        Body=[
                            ast.Return(
                                ast.XCall("org::bind::python::py_getattr_impl", [
                                    ast.string("_self"),
                                    ast.string("name"),
                                ])),
                        ],
                    ))

            # else:
            #     log(CAT).warning(f"Non-abstract type {self.Class} is missing boost reflection annotation")

        getitem_list = []
        for m in self.Methods:
            if m.Func.ReflectionParams and m.Func.ReflectionParams.function_api and m.Func.ReflectionParams.function_api.is_get_item:
                getitem_list.append(replace(m, PyName="__getitem__", conf=m.conf))

        self.Methods += getitem_list

        if self.Struct.ReflectionParams.type_api and self.Struct.ReflectionParams.type_api.has_begin_end_iteration:
            self.Methods.append(
                NbMethod(
                    PyName="__iter__",
                    conf=self.conf,
                    Func=GenTuFunction(
                        Name="at",
                        ReturnType=QualType.ForName("auto"),
                        Args=[GenTuIdent(self.getCxxName().asConstRef(), "node")],
                    ),
                    Body=[
                        ast.Return(
                            ast.XCall(
                                "nanobind::make_iterator",
                                [
                                    ast.XCall("nanobind::type", Params=[self.Struct.Name
                                                                       ]),
                                    ast.Literal(self.getPyName() + "__iter__"),
                                    ast.string("node.begin()"),
                                    ast.string("node.end()"),
                                ],
                            ))
                    ],
                    DefParams=[ast.b.text("nanobind::keep_alive<0, 1>()")],
                    HasExplicitClassParam=True,
                ))

    def dedup_methods(self) -> List[NbMethod]:
        """
        Remove duplicate `const` methods from the list.
        """
        res: List[NbMethod] = []
        for key, _group in itertools.groupby(self.Methods, lambda M:
                                             (M.Func.Name, M.Func.Args)):
            group: List[NbMethod] = list(_group)
            if len(group) == 1:
                res.append(group[0])

            elif len(group) == 2 and group[1].Func.Args == group[0].Func.Args:
                res.append(group[0 if group[1].Func.IsConst else 1])

            else:
                print(len(group))
                pass

        return res

    def build_typedef(self, ast: pya.ASTBuilder) -> pya.ClassParams:
        "Generate type definition stub"
        res = pya.ClassParams(
            Name=self.getPyName(),
            Bases=[
                self.conf.getBackendType(T)
                for T in self.Struct.Bases
                if self.conf.isRegisteredForBacked(T)
            ],
        )

        Init = NbMethod(
            PyName="__init__",
            conf=self.conf,
            Func=GenTuFunction(
                Name="",
                ReturnType=QualType.ForName("None"),
                Args=[
                    GenTuIdent(
                        Name=it.getPyName(),
                        Type=it.Field.Type,  # type: ignore
                        Value=ast.b.text("None")) for it in self.Fields
                ],
            ),
        )

        res.Methods.append(Init.build_typedef(ast))

        method_names = [M.PyName for M in self.dedup_methods()]

        for Meth in self.dedup_methods():
            res.Methods.append(
                Meth.build_typedef(
                    ast,
                    is_overload=1 < method_names.count(Meth.PyName),
                ))

        for Field in self.Fields:
            res.Fields.append(Field.build_typedef(ast))

        return res

    def build_bind(self, ast: cpp.ASTBuilder) -> BlockId:
        "Generate code binding logic"
        b = ast.b

        sub: List[BlockId] = []

        for Init in self.InitImpls:
            sub.append(Init.build_bind(self.getCxxName(), ast))

        for Field in self.Fields:
            sub.append(Field.build_bind(self.getCxxName(), ast))

        for Meth in self.dedup_methods():
            if Meth.Func.ReturnType is None:
                # do not bind constructors as function pointers
                pass

            else:
                sub.append(Meth.build_bind(self.getCxxName(), ast))

        sub.append(b.text(";"))

        return b.stack([
            ast.XCall(
                "nanobind::class_",
                [b.text("m"), ast.Literal(self.getPyName())],
                Params=[self.getCxxName()] +
                [B for B in self.Struct.Bases if self.conf.isKnownClass(B)],
            ),
            b.indent(2, b.stack(sub))
        ])


@beartype
@dataclass
class NbBindPass:
    "Pass code to the python binding directly"
    Id: BlockId
    "Code to pas"


@beartype
@dataclass
class NbTypedefPass:
    "Pass the typedef alias to python"
    name: QualType
    "Newly declared name"
    base: QualType
    "Original underlying type"

    def __init__(self, typedef: codegen_ir.GenTuTypedef,
                 conf: NanobindAstbuilderConfig) -> None:
        self.conf = conf
        self.name = self.conf.getBackendType(typedef.Name)
        self.base = self.conf.getBackendType(typedef.Base)


Py11Entry = Union[NbEnum, NbClass, NbBindPass, NbTypedefPass, NbFunction]


def filter_init_fields(Fields: List[Py11Field]) -> List[Py11Field]:
    return [F for F in Fields if F.Field.Type.Name not in ["SemId"]]  # type: ignore


@beartype
@dataclass
class NbModule:
    "Full wrapper object for the nanobind module"
    PyName: str
    conf: NanobindAstbuilderConfig
    "Name of the final python module"
    Decls: List[Py11Entry] = field(default_factory=list)
    "Wrapped declarations in the module"
    Before: List[BlockId] = field(default_factory=list)
    "Extra code on the toplevel before the module definition"
    After: List[BlockId] = field(default_factory=list)
    "Additional text after the module declaration"

    nameTrack: Dict[str, QualType] = field(default_factory=dict)
    "Map python name to the original declaration"

    def getEntryForName(self, name: str) -> list[Py11Entry | Py11Field]:
        result = list()

        for e in self.Decls:
            match e:
                case NbFunction() | NbMethod():
                    if e.PyName == name:
                        result.append(e)

                case NbEnum():
                    if e.getPyName() == name:
                        result.append(e)

                case NbClass():
                    if e.getPyName() == name:
                        result.append(e)

                    result.extend(e.getEntryForName(name))

                case NbTypedefPass() | NbBindPass():
                    pass

                case _:
                    raise TypeError(str(type(e)))

        return result

    def add_all(self, decls: List[codegen_ir.GenTuUnion], ast: cpp.ASTBuilder) -> None:
        for decl in decls:
            self.add_decl(decl, ast=ast)

    def add_type_specializations(
        self,
        ast: cpp.ASTBuilder,
        specializations: List[codegen_ir.TypeSpecialization],
    ) -> None:
        "Register used type specializations in the module"

        opaque_declarations: List[BlockId] = []

        self.Decls.append(NbBindPass(ast.string("nanobind::set_leak_warnings(false);")))
        # Disabling warnings. Trivial test in `"tests/python/test_coverall.py::test_run_typst_construction"` reports
        # two leaked instances, while valgrind does not report any issues. I'm going to treat
        # this as a false positive until I get more information on what might be causing this.
        # The test I mentioned above constructs two objects, and they are both leaked, even though
        # it does not call any methods, return shared pointers or anything of that nature.
        # Exporter python is not a complex class. Text layout wrapper is even more trivial, and it is
        # also marked as leaked.

        specialization_calls: List[BlockId] = [
            ast.string("org::bind::python::PyTypeRegistryGuard type_registry_guard{};")
        ]

        for spec in specializations:
            if spec.used_type.Name in ["Opt", "optional"]:
                continue

            opaque_declarations.append(
                ast.XCall("NB_MAKE_OPAQUE", [ast.Type(spec.used_type)]))

            specialization_calls.append(
                ast.XCall(
                    f"org::bind::python::bind_{spec.getFlatUsed()}",
                    [
                        ast.string("m"),
                        ast.StringLiteral(spec.bind_name),
                        ast.string("type_registry_guard"),
                    ],
                    Params=spec.used_type.Params,
                    Stmt=True,
                ))

        for decl in opaque_declarations:
            self.Before.append(decl)

        self.Decls = [NbBindPass(D) for D in specialization_calls] + self.Decls

    def add_decl(self, decl: codegen_ir.GenTuUnion, ast: cpp.ASTBuilder) -> None:
        "Add extra declaration to the module"

        def append_decl(d: Py11Entry) -> None:
            "nodoc"
            name = None
            match d:
                case NbClass():
                    name = d.getPyName()
                    orig_name = d.Struct.Name

                case NbEnum():
                    name = d.getPyName()
                    orig_name = d.Enum.Name

            if name:
                # assert name not in self.nameTrack, f"{name} is already registered for the module for {self.nameTrack[name]}, attempting to map{orig_name} to the same name"
                if name not in self.nameTrack:
                    self.Decls.append(d)

                self.nameTrack[name] = orig_name

            else:
                self.Decls.append(d)

        match decl:
            case codegen_ir.GenTuStruct():
                visit_context: List[Any] = []

                def codegenConstructCallback(value: Any) -> None:
                    "nodoc"
                    if isinstance(value, codegen_ir.GenTuStruct):
                        value: codegen_ir.GenTuStruct
                        if value.ReflectionParams.type_api and value.ReflectionParams.type_api.is_org_ast_value and value.Name.Name.startswith(
                                "Imm"):
                            pass

                        else:
                            append_decl(NbClass(ast=ast, value=value, conf=self.conf))

                    elif isinstance(value, codegen_ir.GenTuEnum):
                        append_decl(NbEnum(value, self.conf))

                    elif isinstance(value, codegen_ir.GenTuTypedef):
                        append_decl(NbTypedefPass(value, self.conf))

                def tree_visit_repr(value: Any, context: List[Any]) -> str:
                    match value:
                        case codegen_ir.GenTuStruct():
                            return str(value.Name)

                        case _:
                            return ""

                codegen_ir.iterate_object_tree(
                    decl,
                    visit_context,
                    post_visit=codegenConstructCallback,
                    # item_visit_format=tree_visit_repr,
                )

            case GenTuFunction():
                append_decl(NbFunction(decl, self.conf))

            case codegen_ir.GenTuEnum():
                append_decl(NbEnum(decl, self.conf))

            case codegen_ir.GenTuTypedef():
                append_decl(NbTypedefPass(decl, self.conf))

            case _:
                raise TypeError(f"Unhandled top-level type {type(decl)}")

    def build_typedef(self, ast: pya.ASTBuilder) -> BlockId:
        "Generate full typedef list"
        passes: List[BlockId] = []

        passes.append(ast.string("from typing import *"))
        passes.append(ast.string("from enum import Enum"))
        passes.append(ast.string("from datetime import datetime, date, time"))
        passes.append(
            ast.string("""
T = TypeVar("T")

class ImmBox[T]():
    def get(self) -> T: ...

class ImmFlexVec[T]():
    def at(self, idx: int) -> T: ...
    def __len__(self) -> int: ...

class ImmVec[T]():
    def at(self, idx: int) -> T: ...
    def __len__(self) -> int: ...

class IntSet[T]():
    def __len__(self) -> int: ...

class ImmAdapterTBase[T](ImmAdapter):
    pass
        """))

        for item in self.Decls:
            match item:
                case NbEnum():
                    passes.append(ast.Enum(item.build_typedef()))
                    passes.append(ast.string(""))

                case NbClass():
                    passes.append(ast.Class(item.build_typedef(ast)))
                    passes.append(ast.string(""))

                case NbFunction():
                    passes.append(ast.Function(item.build_typedef(ast)))
                    passes.append(ast.string(""))

                case NbTypedefPass():
                    passes.append(
                        ast.b.line([
                            ast.Type(item.name),
                            ast.b.text(" = "),
                            ast.Type(item.base),
                        ]))

                case NbBindPass() | int():
                    pass

                case _:
                    assert False, type(item)

        return ast.b.stack(passes)

    def build_bind(self, ast: cpp.ASTBuilder) -> BlockId:
        "Generate full binding for the module"
        b = ast.b

        passes: List[BlockId] = []

        for entry in self.Decls:
            match entry:
                case NbBindPass():
                    passes.append(entry.Id)

                case NbClass():
                    passes.append(entry.build_bind(ast))

                case NbEnum():
                    passes.append(entry.build_bind(ast))

                case NbFunction():
                    passes.append(entry.build_bind(ast))

                case int() | NbTypedefPass():
                    pass

                case _:
                    assert False, type(entry)

        return b.stack([
            *self.Before,
            b.text(f"NB_MODULE({self.PyName}, m) {{"),
            b.indent(2, b.stack(passes)),
            b.text("}"),
            *self.After,
        ])
