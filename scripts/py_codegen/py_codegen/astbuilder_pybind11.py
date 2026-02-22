from dataclasses import dataclass, field, replace
import itertools

from beartype import beartype
from beartype.typing import List, Optional
import py_codegen.astbuilder_py as pya
from py_codegen.gen_tu_cpp import *
from py_codegen.gen_tu_cpp import GenTuDoc, GenTuFunction, GenTuIdent, QualType
from py_haxorg.layout.wrap import BlockId
from py_scriptutils.algorithm import maybe_splice


@beartype
def maybe_list(it: Any) -> Any:
    if it:
        return [it]
    else:
        return []


@beartype
def flat_scope(Typ: QualType) -> List[str]:
    res: List[str] = []
    for S in Typ.Spaces:
        res += flat_scope(S)

    res += [Typ.name]
    return res


@beartype
def py_type(Typ: QualType, base_map: GenTypeMap) -> pya.PyType:
    "Map C++ type to the python"
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

            case ["Str"] | ["string"] | ["std", "string"] | ["basic_string" \
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

            case ["nanobind", "bytes"]:
                name = "bytes"

            case ["nanobind", "callable"] | [*_, "PyFunc"]:
                name = "function"

            case ["py", "object"] | ["nanobind", "object"]:
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

    return sanitize_ident(name, python_keywords)


@beartype
def id_self(Typ: QualType) -> ParmVarParams:
    return ParmVarParams(Typ, "_self")


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

    def build_typedef(self, ast: pya.ASTBuilder,
                      base_map: GenTypeMap) -> pya.FunctionDefParams:
        "Get type stub for the wrapper"
        return pya.FunctionDefParams(
            Name=py_ident(self.PyName),
            ResultTy=py_type(self.Func.result, base_map=base_map)
            if self.Func.result else None,
            Args=[
                pya.IdentParams(py_type(Arg.type, base_map=base_map), Arg.name)
                for Arg in self.Func.arguments
            ],
            IsStub=True,
        )

    def __init__(
        self,
        Func: GenTuFunction,
        Body: Optional[List[BlockId]] = None,
        PyName: Optional[str] = None,
        DefParams: Optional[List[BlockId]] = None,
    ):
        name = ""

        if PyName:
            name = PyName

        elif Func.reflectionParams.wrapper_name:
            name = Func.reflectionParams.wrapper_name

        else:
            name = py_ident(Func.name + ("Static" if Func.isStatic else ""))

        self.PyName = name
        self.Body = Body
        self.Func = Func
        self.DefParams = DefParams

    def build_argument_binder(self, Args: List[GenTuIdent],
                              ast: ASTBuilder) -> list[BlockId]:
        "Generate nanobind wrapper block exposing the original function arguments"
        argument_binder: list[BlockId] = []
        b = ast.b

        for Arg in Args:
            if Arg.type.name == "kwargs":
                continue

            elif Arg.value is None:
                argument_binder.append(ast.XCall("nanobind::arg",
                                                 [ast.Literal(Arg.name)]))

            else:
                argument_binder.append(
                    ast.line([
                        ast.XCall("nanobind::arg", [ast.Literal(Arg.name)]),
                        b.text(" = "),
                        b.text(Arg.value) if isinstance(Arg.value, str) else Arg.value
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
                LambdaParams(
                    ResultTy=self.Func.result,
                    Args=[ParmVarParams(Arg.type, Arg.name) for Arg in Args],
                    Body=self.Body,
                    IsLine=False,
                ))

    def build_doc_comment(self, ast: ASTBuilder) -> list[BlockId]:
        "Create python docstring"
        if self.Func.doc.brief:
            return [ast.StringLiteral(self.Func.doc.brief, forceRawStr=True)]

        else:
            return []

    def build_bind(self, ast: ASTBuilder) -> BlockId:
        "Return nanobind block wrapping the C++ function"
        if self.Func.spaces:
            full_name = ast.Scoped(
                QualType(name=self.Func.spaces[-1].name, Spaces=self.Func.spaces[:-1]),
                ast.string(self.Func.name))

        else:
            full_name = ast.string(self.Func.name)

        return ast.XCall(
            "m.def",
            [
                ast.Literal(self.PyName),
                self.build_call_pass(
                    ast,
                    self.Func.arguments,
                    FunctionQualName=full_name,
                ),
                *self.build_argument_binder(self.Func.arguments, ast),
                *self.build_doc_comment(ast),
                *(self.DefParams if self.DefParams else []),
            ],
            Line=len(self.Func.arguments) == 0,
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
        Body: Optional[List[BlockId]] = None,
        PyName: Optional[str] = None,
        HasExplicitClassParam: bool = False,
        DefParams: Optional[List[BlockId]] = None,
    ):
        super().__init__(Func, Body, PyName, DefParams=DefParams)
        self.HasExplicitClassParam = HasExplicitClassParam

    def build_typedef(  # type: ignore[override]
        self,
        ast: pya.ASTBuilder,
        base_map: GenTypeMap,
        is_overload: bool = False,
    ) -> pya.MethodParams:
        "Generate typedef for C++ method"
        return pya.MethodParams(Func=pya.FunctionDefParams(
            Name="__init__" if self.Func.IsConstructor else py_ident(self.PyName),
            ResultTy=self.Func.result and
            py_type(self.Func.result, base_map),  # type: ignore
            Args=[
                pya.IdentParams(py_type(Arg.type, base_map=base_map), Arg.name)
                for Arg in self.Func.arguments
            ],
            IsStub=True,
            Decorators=[
                *maybe_splice(self.Func.isStatic, pya.DecoratorParams("staticmethod")),
                *maybe_splice(is_overload, pya.DecoratorParams("overload")),
            ]))

    def build_bind(self, Class: QualType, ast: ASTBuilder) -> BlockId:
        "Generate binding block for C++ method"
        b = ast.b

        Args: List[GenTuIdent] = []
        if self.Func.IsConstructor or self.HasExplicitClassParam:
            pass

        elif self.Body:
            Args = [GenTuIdent(type=Class.asConstRef(), name="_self")]

        Args += self.Func.arguments

        if self.Func.IsConstructor and not self.Body:
            call_pass = ast.XCall("nanobind::init",
                                  Params=[t.type for t in self.Func.arguments])
            argument_binder = []

        else:
            call_pass = self.build_call_pass(
                ast,
                FunctionQualName=ast.Scoped(Class, ast.string(self.Func.name)),
                Class=None if self.Func.isStatic else Class,
                IsConst=self.Func.isConst,
                Args=Args,
            )

            if self.HasExplicitClassParam and not self.Func.IsConstructor:
                argument_binder = self.build_argument_binder(self.Func.arguments[1:],
                                                             ast=ast)
            else:
                argument_binder = self.build_argument_binder(self.Func.arguments, ast=ast)

        if self.Func.isStatic and not self.Func.IsConstructor:
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
            Line=len(self.Func.arguments) == 0,
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
        Field: GenTuEnumField,
        pyNameOverride: Optional[str] = None,
    ):
        self.PyName = Field.name if pyNameOverride is None else pyNameOverride
        self.CxxName = Field.name
        self.Doc = Field.doc

    def build_bind(self, Enum: 'NbEnum', ast: ASTBuilder) -> BlockId:
        "Generate binding block for enum field"
        return ast.XCall(".value", [
            ast.Literal(self.PyName),
            ast.Type(QualType.ForName(self.CxxName, Spaces=[Enum.Enum.name]))
        ] + maybe_list(get_doc_literal(ast, self.Doc)))


@beartype
@dataclass
class NbEnum:
    "Wrapped C++ enum"
    Enum: GenTuEnum
    "Original C++ enum"
    Fields: List[NbEnumField]
    "Wrapped enum fields"

    def __init__(self, Enum: GenTuEnum) -> None:
        self.Enum = Enum
        self.Fields = [NbEnumField(F) for F in Enum.fields]

    def getPyName(self, base_map: GenTypeMap) -> str:
        return py_type(self.Enum.name, base_map=base_map).Name

    def build_typedef(self, base_map: GenTypeMap) -> pya.EnumParams:
        count = 0
        return pya.EnumParams(
            Name=self.getPyName(base_map),
            Fields=[
                pya.EnumFieldParams(
                    ("_" +
                     F.PyName if F.PyName in ["None", "True", "False"] else F.PyName),
                    str(count := count + 1)) for F in self.Fields
            ])

    def build_bind(self, ast: ASTBuilder, base_map: GenTypeMap) -> BlockId:
        "Generate wrapped enum binding"
        b = ast.b
        iter_type = QualType(
            name="PyEnumIterator",
            Parameters=[self.Enum.name],
            Spaces=[n_org(), t_namespace("bind"),
                    t_namespace("python")],
        )
        return b.stack([
            ast.XCall(
                "bind_enum_iterator",
                args=[
                    b.text("m"),
                    ast.Literal(self.getPyName(base_map)),
                    ast.string("type_registry_guard"),
                ],
                Params=[self.Enum.name],
                Stmt=True,
            ),
            ast.XCall(
                "nanobind::enum_",
                [b.text("m"), ast.Literal(self.getPyName(base_map))],
                Params=[self.Enum.name],
            ),
            b.indent(
                2,
                b.stack([Field.build_bind(self, ast) for Field in self.Fields] + [
                    NbMethod(
                        PyName="__iter__",
                        Func=GenTuFunction(name="", result=iter_type),
                        Body=[
                            ast.Return(ast.b.line([ast.Type(iter_type),
                                                   ast.string("()")])),
                        ],
                    ).build_bind(self.Enum.name, ast),
                    NbMethod(
                        PyName="__eq__",
                        Func=GenTuFunction(
                            name="",
                            result=QualType(name="bool"),
                            arguments=[
                                GenTuIdent(self.Enum.name, "lhs"),
                                GenTuIdent(self.Enum.name, "rhs"),
                            ],
                        ),
                        Body=[
                            ast.Return(
                                ast.XCall("==", [ast.string("lhs"),
                                                 ast.string("rhs")])),
                        ],
                        HasExplicitClassParam=True,
                    ).build_bind(self.Enum.name, ast),
                    NbMethod(
                        PyName="__hash__",
                        Func=GenTuFunction(
                            result=QualType(name="int"),
                            arguments=[GenTuIdent(self.Enum.name, "it")],
                        ),
                        Body=[
                            ast.Return(
                                ast.XCall("static_cast", [ast.string("it")],
                                          Params=[QualType(name="int")])),
                        ],
                        HasExplicitClassParam=True,
                    ).build_bind(self.Enum.name, ast),
                ] + [b.text(";")]),
            )
        ])


@beartype
@dataclass
class Py11Field:
    """
    Wrapped C++ class field
    """
    Field: GenTuField
    "Original C++ class field"
    GetImpl: Optional[List[BlockId]] = None
    "Optional body for the getter callback for the field"
    SetImpl: Optional[List[BlockId]] = None
    "Optional body for the setter callback for the field"

    def getPyName(self) -> str:
        return py_ident(self.Field.name)

    def __init__(self,
                 Field: GenTuField,
                 GetImpl: Optional[List[BlockId]] = None,
                 SetImpl: Optional[List[BlockId]] = None):

        self.Field = Field
        self.GetImpl = GetImpl
        self.SetImpl = SetImpl

    def build_typedef(self, ast: pya.ASTBuilder, base_map: GenTypeMap) -> pya.FieldParams:
        if self.Field.type is None:
            raise ValueError(f"Field {self.Field.name} has no type")
        return pya.FieldParams(py_type(self.Field.type, base_map=base_map),
                               self.getPyName())

    def build_bind(self, Class: QualType, ast: ASTBuilder) -> BlockId:
        "Generate binding block for field"
        b = ast.b
        _self = id_self(Class)
        if self.GetImpl and self.SetImpl:
            assert self.Field.type
            return ast.XCall(
                ".def_prop_rw",
                [
                    ast.Literal(self.getPyName()),
                    ast.Lambda(
                        LambdaParams(
                            ResultTy=self.Field.type,
                            Body=self.GetImpl,
                            Args=[_self],
                        )),
                    ast.Lambda(
                        LambdaParams(
                            ResultTy=None,
                            Body=[b.text(f"{_self.name}->{self.Field.name} = _arg;")],
                            Args=[_self, ParmVarParams(self.Field.type, "_arg")],
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
                    b.text(self.Field.name)
                ]), *maybe_list(get_doc_literal(ast, self.Field.doc))
            ])


@beartype
class NbClass:
    "C++ class wrapped for the binding generation"
    Struct: GenTuStruct
    "Original C++ class/structure/union"
    Fields: List[Py11Field]
    "Wrapped fields"
    Methods: List[NbMethod]
    "Wrapped methods excluding constructor"
    InitImpls: List[NbMethod]
    "Constructor implementations"

    def getPyName(self, base_map: GenTypeMap) -> str:
        "Get python name for the wrapped C++ class"
        return self.Struct.reflectionParams.wrapper_name or py_type(
            self.Struct.name, base_map=base_map).Name

    def getCxxName(self) -> QualType:
        "Get original C++ name"
        return self.Struct.declarationQualName()

    def __init__(self, ast: ASTBuilder, value: GenTuStruct, base_map: GenTypeMap) -> None:
        self.Struct = value
        self.Fields = []
        self.Methods = []
        self.InitImpls = []

        for meth in value.methods:
            if meth.isExposedForWrap and not meth.isPureVirtual:
                if meth.IsConstructor:
                    self.InitImpls.append(NbMethod(meth))
                else:
                    self.Methods.append(NbMethod(meth))

        for _field in value.fields:
            if _field.isExposedForWrap:
                self.Fields.append(Py11Field(_field))

        if not value.IsAbstract and value.reflectionParams.default_constructor:
            self.InitDefault(ast, filter_init_fields(self.Fields))

        self.InitMagicMethods(ast=ast, base_map=base_map)

    def InitDefault(self, ast: ASTBuilder, Fields: List[Py11Field]) -> None:
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
                    Func=GenTuFunction(
                        name="",
                        arguments=[
                            GenTuIdent(result_type.asPtr(), "result"),
                            GenTuIdent(
                                QualType(
                                    name="kwargs",
                                    Spaces=[QualType.ForName("nanobind")],
                                    isConst=True,
                                    RefKind=ReferenceKind.LValue,
                                ), "kwargs")
                        ],
                        IsConstructor=True,
                    ),
                    Body=body_impl,
                    HasExplicitClassParam=True,
                ))

    def InitMagicMethods(self, ast: ASTBuilder, base_map: GenTypeMap) -> None:
        """
        Init magic methods for `__repr__`, `__getattr__` etc.
        """
        str_type = QualType.ForName("string", Spaces=[QualType.ForName("std")])
        pyobj_type = QualType.ForName("object", Spaces=[QualType.ForName("nanobind")])

        if not self.Struct.IsAbstract:
            if self.Struct.IsDescribedRecord:
                self.Methods.append(
                    NbMethod(
                        PyName="__repr__",
                        Func=GenTuFunction(
                            name="",
                            result=str_type,
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
                        Func=GenTuFunction(
                            name="",
                            result=pyobj_type,
                            arguments=[GenTuIdent(str_type.asConstRef(), "name")],
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
            if m.Func.reflectionParams and m.Func.reflectionParams.function_api and m.Func.reflectionParams.function_api.is_get_item:
                getitem_list.append(replace(m, PyName="__getitem__"))

        self.Methods += getitem_list

        if self.Struct.reflectionParams.type_api and self.Struct.reflectionParams.type_api.has_begin_end_iteration:
            self.Methods.append(
                NbMethod(
                    PyName="__iter__",
                    Func=GenTuFunction(
                        name="at",
                        result=QualType.ForName("auto"),
                        arguments=[GenTuIdent(self.getCxxName().asConstRef(), "node")],
                    ),
                    Body=[
                        ast.Return(
                            ast.XCall(
                                "nanobind::make_iterator",
                                [
                                    ast.XCall("nanobind::type", Params=[self.Struct.name
                                                                       ]),
                                    ast.Literal(
                                        self.getPyName(base_map=base_map) + "__iter__"),
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
                                             (M.Func.name, M.Func.arguments)):
            group: List[NbMethod] = list(_group)
            if len(group) == 1:
                res.append(group[0])

            elif len(group) == 2 and group[1].Func.arguments == group[0].Func.arguments:
                res.append(group[0 if group[1].Func.isConst else 1])

            else:
                print(len(group))
                pass

        return res

    def build_typedef(self, ast: pya.ASTBuilder, base_map: GenTypeMap) -> pya.ClassParams:
        "Generate type definition stub"
        res = pya.ClassParams(
            Name=self.getPyName(base_map=base_map),
            Bases=[
                py_type(T, base_map=base_map)
                for T in self.Struct.bases
                if T.name not in ["SharedPtrApi"]
            ],
        )

        Init = NbMethod(
            PyName="__init__",
            Func=GenTuFunction(
                name="",
                result=QualType.ForName("None"),
                arguments=[
                    GenTuIdent(
                        name=it.getPyName(),
                        type=it.Field.type,  # type: ignore
                        value=ast.b.text("None")) for it in self.Fields
                ],
            ),
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
        "Generate code binding logic"
        b = ast.b

        sub: List[BlockId] = []

        for Init in self.InitImpls:
            sub.append(Init.build_bind(self.getCxxName(), ast))

        for Field in self.Fields:
            sub.append(Field.build_bind(self.getCxxName(), ast))

        for Meth in self.dedup_methods():
            if Meth.Func.result is None:
                # do not bind constructors as function pointers
                pass

            else:
                sub.append(Meth.build_bind(self.getCxxName(), ast))

        sub.append(b.text(";"))

        return b.stack([
            ast.XCall(
                "nanobind::class_",
                [b.text("m"), ast.Literal(self.getPyName(base_map=base_map))],
                Params=[self.getCxxName()] +
                [B for B in self.Struct.bases if base_map.is_known_type(B)],
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
    name: pya.PyType
    "Newly declared name"
    base: pya.PyType
    "Original underlying type"

    def __init__(self, typedef: GenTuTypedef, base_map: GenTypeMap) -> None:
        self.name = py_type(typedef.name, base_map)
        self.base = py_type(typedef.base, base_map)


Py11Entry = Union[NbEnum, NbClass, NbBindPass, NbTypedefPass, NbFunction]


def filter_init_fields(Fields: List[Py11Field]) -> List[Py11Field]:
    return [F for F in Fields if F.Field.type.name not in ["SemId"]]  # type: ignore


@beartype
@dataclass
class NbModule:
    "Full wrapper object for the nanobind module"
    PyName: str
    "Name of the final python module"
    Decls: List[Py11Entry] = field(default_factory=list)
    "Wrapped declarations in the module"
    Before: List[BlockId] = field(default_factory=list)
    "Extra code on the toplevel before the module definition"
    After: List[BlockId] = field(default_factory=list)
    "Additional text after the module declaration"

    nameTrack: Dict[str, QualType] = field(default_factory=dict)
    "Map python name to the original declaration"

    def add_all(self, decls: List[GenTuUnion], ast: ASTBuilder,
                base_map: GenTypeMap) -> None:
        for decl in decls:
            self.add_decl(decl, ast=ast, base_map=base_map)

    def add_type_specializations(
        self,
        ast: ASTBuilder,
        specializations: List[TypeSpecialization],
    ) -> None:
        "Register used type specializations in the module"

        opaque_declarations: List[BlockId] = []
        specialization_calls: List[BlockId] = [
            ast.string("org::bind::python::PyTypeRegistryGuard type_registry_guard{};")
        ]

        for spec in specializations:
            if spec.used_type.name in ["Opt", "optional"]:
                continue

            if spec.std_type:
                opaque_declarations.append(
                    ast.XCall("NB_MAKE_OPAQUE", [ast.Type(spec.std_type)]))

            opaque_declarations.append(
                ast.XCall("NB_MAKE_OPAQUE", [ast.Type(spec.used_type)]))

            specialization_calls.append(
                ast.XCall(
                    f"bind_{spec.getFlatUsed()}",
                    [
                        ast.string("m"),
                        ast.StringLiteral(spec.bind_name),
                        ast.string("type_registry_guard"),
                    ],
                    Params=spec.used_type.Parameters,
                    Stmt=True,
                ))

        for decl in opaque_declarations:
            self.Before.append(decl)

        self.Decls = [NbBindPass(D) for D in specialization_calls] + self.Decls

    def add_decl(self, decl: GenTuUnion, ast: ASTBuilder, base_map: GenTypeMap) -> None:
        "Add extra declaration to the module"

        def append_decl(d: Py11Entry) -> None:
            "nodoc"
            name = None
            match d:
                case NbClass():
                    name = d.getPyName(base_map=base_map)
                    orig_name = d.Struct.name

                case NbEnum():
                    name = d.getPyName(base_map=base_map)
                    orig_name = d.Enum.name

            if name:
                # assert name not in self.nameTrack, f"{name} is already registered for the module for {self.nameTrack[name]}, attempting to map{orig_name} to the same name"
                if name not in self.nameTrack:
                    self.Decls.append(d)

                self.nameTrack[name] = orig_name

            else:
                self.Decls.append(d)

        match decl:
            case GenTuStruct():
                visit_context: List[Any] = []

                def codegenConstructCallback(value: Any) -> None:
                    "nodoc"
                    if isinstance(value, GenTuStruct):
                        if value.reflectionParams.type_api and value.reflectionParams.type_api.is_org_ast_value and value.name.name.startswith(
                                "Imm"):
                            pass

                        else:
                            # log(CAT).info(f"{'  ' * len(visit_context)} {value.name}")
                            append_decl(NbClass(ast=ast, value=value, base_map=base_map))

                    elif isinstance(value, GenTuEnum):
                        append_decl(NbEnum(value))

                    elif isinstance(value, GenTuTypedef):
                        append_decl(NbTypedefPass(value, base_map))

                def tree_visit_repr(value: Any, context: List[Any]) -> str:
                    match value:
                        case GenTuStruct():
                            return str(value.name)

                        case _:
                            return ""

                iterate_object_tree(
                    decl,
                    visit_context,
                    post_visit=codegenConstructCallback,
                    # item_visit_format=tree_visit_repr,
                )

            case GenTuFunction():
                append_decl(NbFunction(decl))

            case GenTuEnum():
                append_decl(NbEnum(decl))

            case GenTuTypedef():
                append_decl(NbTypedefPass(decl, base_map=base_map))

    def build_typedef(self, ast: pya.ASTBuilder, base_map: GenTypeMap) -> BlockId:
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
                case NbEnum():
                    passes.append(ast.Enum(item.build_typedef(base_map=base_map)))
                    passes.append(ast.string(""))

                case NbClass():
                    passes.append(ast.Class(item.build_typedef(ast, base_map)))
                    passes.append(ast.string(""))

                case NbFunction():
                    passes.append(ast.Function(item.build_typedef(ast,
                                                                  base_map=base_map)))
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

    def build_bind(self, ast: ASTBuilder, base_map: GenTypeMap) -> BlockId:
        "Generate full binding for the module"
        b = ast.b

        passes: List[BlockId] = []

        for entry in self.Decls:
            match entry:
                case NbBindPass():
                    passes.append(entry.Id)

                case NbClass():
                    passes.append(entry.build_bind(ast, base_map=base_map))

                case NbEnum():
                    passes.append(entry.build_bind(ast, base_map=base_map))

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
