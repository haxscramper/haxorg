from py_codegen.gen_tu_cpp import *
from beartype import beartype
from dataclasses import dataclass, field
from beartype.typing import List, Optional, NewType
from py_scriptutils.algorithm import maybe_splice

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

IGNORED_NAMESPACES = ["sem", "org", "hstd", "ext", "algo", "bind", "python", "imm"]


@beartype
def py_type_bind(Typ: QualType) -> pya.PyType:
    fullname = "".join([py_type_bind(T).Name for T in Typ.Spaces])
    if Typ.name not in IGNORED_NAMESPACES:
        fullname += Typ.name

    if 0 < len(Typ.Parameters):
        fullname += "Of"
        fullname += "".join([py_type_bind(T).Name for T in Typ.Parameters])

    return pya.PyType(fullname)


@beartype
def flat_scope(Typ: QualType) -> List[str]:
    res: List[str] = []
    for S in Typ.Spaces:
        res += flat_scope(S)

    res += [Typ.name]
    return res


@beartype
def py_type(Typ: QualType, base_map: GenTypeMap) -> pya.PyType:
    is_target = "ImmAdapterT" in Typ.name
    wrapper_override = base_map.get_wrapper_type(Typ)

    if wrapper_override:
        name = wrapper_override

    else:
        flat = [N for N in flat_scope(Typ) if N not in IGNORED_NAMESPACES]

        if flat == ["std", "shared_ptr"] and 1 == len(
                Typ.Parameters) and base_map.is_known_type(
                    Typ.Parameters[0]) and base_map.get_one_type_for_qual_name(
                        Typ.Parameters[0]
                    ).reflectionParams.backend.python.holder_type == "shared":
            return py_type(Typ.Parameters[0], base_map=base_map)

        elif flat == ["ImmIdT"]:
            return pya.PyType("ImmIdT" + Typ.Parameters[0].name.replace("Imm", "", 1))

        match flat:
            case ["Vec"]:
                name = "List"

            case ["Opt"] | ["std", "optional"]:
                name = "Optional"

            case ["std", "variant"] | ["Var"]:
                name = "Union"

            case ["immer", "box"]:
                name = "ImmBox"

            case ["immer", "flex_vector"]:
                name = "ImmFlexVector"

            case ["immer", "vector"]:
                name = "ImmVector"

            case ["immer", "map"]:
                name = "ImmMap"

            case ["Str"] | ["string"] | ["std", "string"] | ["basic_string"
                                                            ] | ["std", "basic_string"]:
                name = "str"

            case ["SemId"]:
                name = Typ.Parameters[0].name

            case "Bool":
                name = "bool"

            case "double":
                name = "float"

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

    struct = base_map.get_struct_for_qual_name(Typ)
    if not struct or struct.reflectionParams.wrapper_has_params:
        res = pya.PyType(name)
        if Typ.name != "SemId":
            for param in Typ.Parameters:
                res.Params.append(py_type(param, base_map=base_map))

        return res

    else:
        return pya.PyType(name)


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
    """
    Convert C++ identifiers to valid Python identifiers.
    Handles keywords, operator overloads, and special characters.
    """
    # Python keywords that need to be escaped
    python_keywords = {
        "and",
        "as",
        "assert",
        "async",
        "await",
        "break",
        "class",
        "continue",
        "def",
        "del",
        "elif",
        "else",
        "except",
        "False",
        "finally",
        "for",
        "from",
        "global",
        "if",
        "import",
        "in",
        "is",
        "lambda",
        "None",
        "nonlocal",
        "not",
        "or",
        "pass",
        "raise",
        "return",
        "True",
        "try",
        "while",
        "with",
        "yield",
    }

    # Operator mappings from C++ to Python
    operator_mappings = {
        # Comparison operators
        "operator==": "__eq__",
        "operator!=": "__ne__",
        "operator>": "__gt__",
        "operator<": "__lt__",
        "operator>=": "__ge__",
        "operator<=": "__le__",

        # Arithmetic operators
        "operator+": "__add__",
        "operator-": "__sub__",
        "operator*": "__mul__",
        "operator/": "__truediv__",
        "operator%": "__mod__",
        "operator//": "__floordiv__",
        "operator**": "__pow__",

        # Unary operators
        "operator++": "__next__",  # Note: not exact equivalent
        "operator--": "__prev__",  # Note: not exact equivalent
        "operator-@": "__neg__",  # Unary minus
        "operator+@": "__pos__",  # Unary plus
        "operator~": "__invert__",  # Bitwise NOT

        # Bitwise operators
        "operator&": "__and__",
        "operator|": "__or__",
        "operator^": "__xor__",
        "operator<<": "__lshift__",
        "operator>>": "__rshift__",

        # Assignment operators (in-place operations)
        "operator+=": "__iadd__",
        "operator-=": "__isub__",
        "operator*=": "__imul__",
        "operator/=": "__itruediv__",
        "operator%=": "__imod__",
        "operator&=": "__iand__",
        "operator|=": "__ior__",
        "operator^=": "__ixor__",
        "operator<<=": "__ilshift__",
        "operator>>=": "__irshift__",

        # Subscript operator
        "operator[]": "__getitem__",

        # Function call operator
        "operator()": "__call__",

        # Conversion operators
        "operator bool": "__bool__",
        "operator int": "__int__",
        "operator float": "__float__",
        "operator str": "__str__",

        # Smart pointer operations
        "operator*": "__deref__",  # Dereference (conflicts with multiply)
        "operator->": "__arrow__",  # Arrow operator (no direct Python equivalent)

        # Memory management
        "operator new": "__new__",
        "operator delete": "__del__",

        # Stream operators
        "operator<<": "__lshift__",  # Also used for stream insertion
        "operator>>": "__rshift__",  # Also used for stream extraction

        # Comma operator
        "operator,": "__comma__",  # No direct Python equivalent
    }

    # Check if it's an operator
    if name in operator_mappings:
        return operator_mappings[name]

    # Check if it's a Python keyword
    if name in python_keywords:
        return name + "_"

    # Handle special characters
    # Replace invalid characters with underscores
    result = ""
    for char in name:
        if char.isalnum() or char == '_':
            result += char
        else:
            result += '_'

    # Ensure the identifier doesn't start with a digit
    if result and result[0].isdigit():
        result = '_' + result

    # Ensure the identifier isn't empty
    if not result:
        result = '_empty_'

    return result


@beartype
def id_self(Typ: QualType) -> ParmVarParams:
    return ParmVarParams(Typ, "_self")


@beartype
@dataclass
class Py11Function:
    PyName: str
    CxxName: str
    ResultTy: Optional[QualType]
    Args: List[GenTuIdent] = field(default_factory=list)
    Body: Optional[List[BlockId]] = None
    Doc: GenTuDoc = field(default_factory=lambda: GenTuDoc(""))
    DefParams: Optional[List[BlockId]] = None
    Spaces: List[QualType] = field(default_factory=list)

    def build_typedef(self, ast: pya.ASTBuilder,
                      base_map: GenTypeMap) -> pya.FunctionDefParams:
        return pya.FunctionDefParams(
            Name=py_ident(self.PyName),
            ResultTy=self.ResultTy and py_type(self.ResultTy, base_map=base_map),
            Args=[
                pya.IdentParams(py_type(Arg.type, base_map=base_map), Arg.name)
                for Arg in self.Args
            ],
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
                QualType(name=self.Spaces[-1].name, Spaces=self.Spaces[:-1]),
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
    IsStatic: bool = False
    ExplicitClassParam: bool = False

    @staticmethod
    def FromGenTu(
        meth: GenTuFunction,
        Body: Optional[List[BlockId]] = None,
        pySideOverride: Optional[str] = None,
    ) -> 'Py11Method':

        return Py11Method(
            PyName=pySideOverride if pySideOverride else
            py_ident(meth.name + ("Static" if meth.isStatic else "")),
            Body=Body,
            ResultTy=meth.result,
            CxxName=meth.name,
            Doc=meth.doc,
            IsConst=meth.isConst,
            Args=meth.arguments,
            IsStatic=meth.isStatic,
            IsInit=meth.IsConstructor,
        )

    def build_typedef(
        self,
        ast: pya.ASTBuilder,
        base_map: GenTypeMap,
        is_overload: bool = False,
    ) -> pya.MethodParams:
        return pya.MethodParams(Func=pya.FunctionDefParams(
            Name="__init__" if self.IsInit else py_ident(self.PyName),
            ResultTy=self.ResultTy and py_type(self.ResultTy, base_map),
            Args=[
                pya.IdentParams(py_type(Arg.type, base_map=base_map), Arg.name)
                for Arg in self.Args
            ],
            IsStub=True,
            Decorators=[
                *maybe_splice(self.IsStatic, pya.DecoratorParams("staticmethod")),
                *maybe_splice(is_overload, pya.DecoratorParams("overload")),
            ]))

    def build_bind(self, Class: QualType, ast: ASTBuilder) -> BlockId:
        b = ast.b

        Args: List[GenTuIdent] = []
        if self.IsInit or self.ExplicitClassParam:
            pass

        elif self.Body:
            Args = [GenTuIdent(type=Class.asConstRef(), name="_self")]

        Args += self.Args

        if self.IsInit and not self.Body:
            call_pass = ast.XCall("pybind11::init", Params=[t.type for t in self.Args])
            argument_binder = []

        else:
            call_pass = self.build_call_pass(
                ast,
                FunctionQualName=ast.Scoped(Class, ast.string(self.CxxName)),
                Class=None if self.IsStatic else Class,
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
            (".def_static" if (self.IsStatic and not self.IsInit) else ".def"),
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
    def FromGenTu(
        Field: GenTuEnumField,
        pyNameOverride: Optional[str] = None,
    ) -> 'Py11EnumField':
        return Py11EnumField(
            PyName=Field.name if pyNameOverride is None else pyNameOverride,
            CxxName=Field.name,
            Doc=Field.doc,
        )

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
        iter_type = QualType(
            name="PyEnumIterator",
            Parameters=[self.Enum],
            Spaces=[n_org(), t_namespace("bind"),
                    t_namespace("python")],
        )
        return b.stack([
            ast.XCall(
                "bind_enum_iterator",
                args=[
                    b.text("m"),
                    ast.Literal(self.PyName),
                    ast.string("type_registry_guard"),
                ],
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
                            ast.Return(ast.b.line([ast.Type(iter_type),
                                                   ast.string("()")])),
                        ],
                    ).build_bind(self.Enum, ast),
                    Py11Method(
                        PyName="__eq__",
                        CxxName="",
                        ResultTy=QualType(name="bool"),
                        Args=[
                            GenTuIdent(self.Enum, "lhs"),
                            GenTuIdent(self.Enum, "rhs"),
                        ],
                        Body=[
                            ast.Return(
                                ast.XCall("==", [ast.string("lhs"),
                                                 ast.string("rhs")])),
                        ],
                    ).build_bind(self.Enum, ast),
                    Py11Method(
                        PyName="__hash__",
                        CxxName="",
                        ResultTy=QualType(name="int"),
                        Args=[
                            GenTuIdent(self.Enum, "it"),
                        ],
                        Body=[
                            ast.Return(
                                ast.XCall("static_cast", [ast.string("it")],
                                          Params=[QualType(name="int")])),
                        ],
                    ).build_bind(self.Enum, ast),
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

    def build_typedef(self, ast: pya.ASTBuilder, base_map: GenTypeMap) -> pya.FieldParams:
        return pya.FieldParams(py_type(self.Type, base_map=base_map), self.PyName)

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
    ReflectionParams: Optional[GenTuReflParams]
    Bases: List[QualType] = field(default_factory=list)
    PyHolderType: Optional[QualType] = None
    Fields: List[Py11Field] = field(default_factory=list)
    Methods: List[Py11Method] = field(default_factory=list)
    InitImpls: List[Py11Method] = field(default_factory=list)
    IsAbstract: bool = False

    @staticmethod
    def FromGenTu(ast: ASTBuilder,
                  value: GenTuStruct,
                  base_map: GenTypeMap,
                  pyNameOveride: Optional[str] = None) -> 'Py11Class':
        res = Py11Class(
            PyName=value.reflectionParams.wrapper_name or pyNameOveride or
            py_type(value.name, base_map=base_map).Name,
            Class=value.declarationQualName(),
            ReflectionParams=value.reflectionParams,
        )

        res.ReflectionParams = value.reflectionParams
        res.IsAbstract = value.IsAbstract

        for base in value.bases:
            res.Bases.append(base)

        for meth in value.methods:
            res.Methods.append(Py11Method.FromGenTu(meth))

        for _field in value.fields:
            res.Fields.append(Py11Field.FromGenTu(_field))

        return res

    def InitDefault(self, ast: ASTBuilder, Fields: List[Py11Field]):

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
                        "org::bind::python::init_fields_from_kwargs",
                        args=[ast.string("result"),
                              ast.string("kwargs")],
                        Stmt=True,
                    ),
                    ast.Return(ast.string("result")),
                ],
                IsInit=True,
                ExplicitClassParam=True,
            ))

    def InitMagicMethods(self, ast: ASTBuilder):
        str_type = QualType.ForName("string", Spaces=[QualType.ForName("std")])
        pyobj_type = QualType.ForName("object", Spaces=[QualType.ForName("pybind11")])

        if not self.IsAbstract:
            self.Methods.append(
                Py11Method(
                    PyName="__repr__",
                    CxxName="",
                    ResultTy=str_type,
                    Body=[
                        ast.Return(
                            ast.XCall("org::bind::python::py_repr_impl",
                                      args=[ast.string("_self")])),
                    ],
                ))

            self.Methods.append(
                Py11Method(
                    PyName="__getattr__",
                    CxxName="",
                    ResultTy=pyobj_type,
                    Args=[GenTuIdent(str_type.asConstRef(), "name")],
                    Body=[
                        ast.Return(
                            ast.XCall("org::bind::python::py_getattr_impl", [
                                ast.string("_self"),
                                ast.string("name"),
                            ])),
                    ],
                ))

        if self.ReflectionParams.type_api and self.ReflectionParams.type_api.has_begin_end_iteration:
            self.Methods.append(
                Py11Method(
                    PyName="__iter__",
                    CxxName="at",
                    ResultTy=QualType.ForName("auto"),
                    Args=[GenTuIdent(self.Class.asConstRef(), "node")],
                    Body=[
                        ast.b.text(
                            "return pybind11::make_iterator(node.begin(), node.end());")
                    ],
                    DefParams=[ast.b.text("pybind11::keep_alive<0, 1>()")],
                    ExplicitClassParam=True,
                ))

        # self.Methods.append(
        #     Py11Method(
        #         PyName="__setattr__",
        #         CxxName="",
        #         ResultTy=None,
        #         Args=[GenTuIdent(str_type, "name"),
        #               GenTuIdent(pyobj_type, "value")],
        #         Body=[
        #             ast.XCall("py_setattr_impl", [
        #                 ast.string("_self"),
        #                 ast.string("name"),
        #                 ast.string("value"),
        #             ], Stmt=True),
        #         ]))

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

    def build_typedef(self, ast: pya.ASTBuilder, base_map: GenTypeMap) -> pya.ClassParams:
        res = pya.ClassParams(Name=self.PyName,
                              Bases=[py_type(T, base_map=base_map) for T in self.Bases])

        Init = Py11Method(
            PyName="__init__",
            CxxName="",
            ResultTy=QualType.ForName("None"),
            Args=[
                GenTuIdent(name=it.PyName, type=it.Type, value=ast.b.text("None"))
                for it in self.Fields
            ],
        )

        res.Methods.append(Init.build_typedef(ast, base_map=base_map))

        method_names = [M.PyName for M in self.dedup_methods()]

        for Meth in self.dedup_methods():
            res.Methods.append(
                Meth.build_typedef(
                    ast,
                    base_map=base_map,
                    is_overload=1 < method_names.count(Meth.PyName),
                ))

        for Field in self.Fields:
            res.Fields.append(Field.build_typedef(ast, base_map=base_map))

        return res

    def build_bind(self, ast: ASTBuilder, base_map: GenTypeMap) -> BlockId:
        b = ast.b

        sub: List[BlockId] = []

        for Init in self.InitImpls:
            sub.append(Init.build_bind(self.Class, ast))

        for Field in self.Fields:
            sub.append(Field.build_bind(self.Class, ast))

        for Meth in self.dedup_methods():
            if Meth.ResultTy is None:
                # do not bind constructors as function pointers
                pass

            else:
                sub.append(Meth.build_bind(self.Class, ast))

        sub.append(b.text(";"))

        HolderType = None

        if self.PyHolderType:
            HolderType = self.PyHolderType

        elif self.ReflectionParams:
            match self.ReflectionParams.backend.python.holder_type:
                case QualType():
                    HolderType = self.ReflectionParams.backend.python.holder_type.withTemplateParams(
                        [self.Class])

                case "shared":
                    HolderType = self.Class.withWrapperType(
                        QualType.ForName("shared_ptr", Spaces=[QualType.ForName("std")]))

                case "unique":
                    HolderType = self.Class.withWrapperType(
                        QualType.ForName("unique_ptr", Spaces=[QualType.ForName("std")]))

                case holder:
                    if holder is not None:
                        HolderType = self.Class.withWrapperType(QualType.ForName(holder))

        return b.stack([
            ast.XCall(
                "pybind11::class_",
                [b.text("m"), ast.Literal(self.PyName)],
                Params=[self.Class] + ([HolderType] if HolderType else []) +
                [B for B in self.Bases if base_map.is_known_type(B)],
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

    @staticmethod
    def FromGenTu(typedef: GenTuTypedef, base_map: GenTypeMap) -> "Py11TypedefPass":
        return Py11TypedefPass(
            name=py_type(typedef.name, base_map),
            base=py_type(typedef.base, base_map),
        )


Py11Entry = Union[Py11Enum, Py11Class, Py11BindPass, Py11TypedefPass, Py11Function]


@beartype
@dataclass
class Py11Module:
    PyName: str
    Decls: List[Py11Entry] = field(default_factory=list)
    Before: List[BlockId] = field(default_factory=list)
    After: List[BlockId] = field(default_factory=list)

    def build_typedef(self, ast: pya.ASTBuilder, base_map: GenTypeMap) -> BlockId:
        passes: List[BlockId] = []

        passes.append(ast.string("from typing import *"))
        passes.append(ast.string("from enum import Enum"))
        passes.append(ast.string("from datetime import datetime, date, time"))
        passes.append(
            ast.string("""
T = TypeVar("T")

class ImmBox[T]():
    def get(self) -> T: ...

class ImmFlexVector[T]():
    def at(self, idx: int) -> T: ...
    def __len__(self) -> int: ...

class ImmVector[T]():
    def at(self, idx: int) -> T: ...
    def __len__(self) -> int: ...

class ImmAdapterTBase[T](ImmAdapter):
    pass
        """))

        for item in self.Decls:
            match item:
                case Py11Enum():
                    passes.append(ast.Enum(item.build_typedef()))
                    passes.append(ast.string(""))

                case Py11Class():
                    passes.append(ast.Class(item.build_typedef(ast, base_map)))
                    passes.append(ast.string(""))

                case Py11Function():
                    passes.append(ast.Function(item.build_typedef(ast,
                                                                  base_map=base_map)))
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

    def build_bind(self, ast: ASTBuilder, base_map: GenTypeMap) -> BlockId:
        b = ast.b

        passes: List[BlockId] = []

        for entry in self.Decls:
            match entry:
                case Py11BindPass():
                    passes.append(entry.Id)

                case Py11Class():
                    passes.append(entry.build_bind(ast, base_map=base_map))

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
            b.text(f"PYBIND11_MODULE({self.PyName}, m) {{"),
            b.indent(2, b.stack(passes)),
            b.text("}"), *self.After
        ])
