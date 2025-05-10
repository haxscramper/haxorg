from py_codegen.gen_tu_cpp import *
from beartype import beartype
from dataclasses import dataclass, field
from beartype.typing import Union
import py_codegen.astbuilder_cpp as cpp
from collections import defaultdict
from py_codegen.astbuilder_base import pascal_case


@beartype
def js_ident(name: str) -> str:
    return sanitize_ident(name, set())


@beartype
def get_function_wasm_name(Func: GenTuFunction):
    if Func.reflectionParams.unique_name:
        return Func.reflectionParams.unique_name

    elif Func.reflectionParams.wrapper_name:
        return Func.reflectionParams.wrapper_name

    else:
        return js_ident(Func.name)


GEN = "haxorg_wasm"


@beartype
def ts_type(Typ: QualType, base_map: GenTypeMap) -> QualType:
    flat = [N for N in Typ.flatQualName() if N not in IGNORED_NAMESPACES]

    match flat:
        case ["int"]:
            name = "number"

        case ["bool"]:
            name = "boolean"

        case ["Str"] | ["string"] | ["std", "string"] | ["basic_string"
                                                        ] | ["std", "basic_string"]:
            name = "string"

        case ["void"]:
            name = "void"

        case ["SemId"]:
            return ts_type(Typ.par0(), base_map)

        case ["Opt"] | ["std", "optional"]:
            name = GEN + ".Optional"

        case _:
            name = Typ.getBindName(
                ignored_spaces=IGNORED_NAMESPACES,
                withParams=False,
            )

    return QualType(
        name=name,
        Parameters=[ts_type(
            P,
            base_map=base_map,
        ) for P in Typ.Parameters],
    )


@beartype
class WasmField():
    Field: GenTuField

    def __init__(self, Field: GenTuField):
        self.Field = Field

    def get_typedef(self, ast: ASTBuilder, base_map: GenTypeMap) -> List[BlockId]:
        return [
            ast.line([
                ast.string(self.Field.name),
                ast.string(": "),
                ast.Type(ts_type(self.Field.type, base_map)),
            ])
        ]

    def build_bind(self, ast: ASTBuilder, Class: QualType) -> BlockId:
        return ast.XCall(
            ".property",
            args=[
                ast.StringLiteral(self.Field.name),
                ast.Addr(ast.Scoped(Class, ast.string(self.Field.name))),
            ],
        )


@beartype
@dataclass
class WasmBindPass:
    Id: BlockId


@beartype
class WasmFunction():
    Func: GenTuFunction
    Body: List[BlockId] = []

    def getWasmName(self) -> str:
        return get_function_wasm_name(self.Func)

    def __init__(self, Func: GenTuFunction, Body: List[BlockId] = []):
        self.Func = Func
        self.Body = Body

    def get_module_use(self, ast: ASTBuilder, base_map: GenTypeMap) -> List[BlockId]:
        return self.get_typedef(ast, base_map)

    def get_typedef(self, ast: ASTBuilder, base_map: GenTypeMap) -> List[BlockId]:
        return [
            ast.line([
                ast.string(self.getWasmName()),
                ast.pars(
                    ast.csv([
                        ast.line([
                            ast.string(F.name),
                            ast.string(": "),
                            ast.Type(ts_type(F.type, base_map)),
                        ]) for F in self.Func.arguments
                    ])),
                ast.string(": "),
                ast.Type(ts_type(self.Func.result, base_map))
                if self.Func.result else ast.string("void"),
                ast.string(";"),
            ])
        ]

    def build_call_pass(
        self,
        ast: ASTBuilder,
        Args: List[GenTuIdent],
        FunctionQualName: BlockId,
        Class: Optional[QualType] = None,
        IsConst: bool = False,
    ) -> BlockId:
        if self.Body:
            return ast.Lambda(
                LambdaParams(
                    ResultTy=self.Func.result,
                    Args=[
                        ParmVarParams(Arg.type, Arg.name) for Arg in self.Func.arguments
                    ],
                    Body=self.Body,
                    IsLine=False,
                ))

        else:
            function_type = self.Func.get_function_type(Class=Class)

            return ast.XCall(
                "static_cast",
                args=[ast.Addr(FunctionQualName)],
                Params=[function_type],
            )

    def build_bind(self, b: ASTBuilder) -> BlockId:

        if self.Func.spaces:
            full_name = b.Scoped(
                QualType(name=self.Func.spaces[-1].name, Spaces=self.Func.spaces[:-1]),
                b.string(self.Func.name))

        else:
            full_name = b.string(self.Func.name)

        return b.XCall(
            "emscripten::function",
            [
                b.Literal(self.getWasmName()),
                self.build_call_pass(
                    b,
                    self.Func.arguments,
                    FunctionQualName=full_name,
                ),
            ],
            Stmt=True,
        )


@beartype
class WasmMethod():
    Func: GenTuFunction


@beartype
class WasmEnum():
    Enum: GenTuEnum

    def __init__(self, Enum: GenTuEnum):
        self.Enum = Enum

    def getWasmName(self) -> str:
        return self.Enum.name.getBindName()

    def get_module_use(self, ast: ASTBuilder, base_map: GenTypeMap) -> List[BlockId]:
        return [
            ast.string(
                f"format_{self.getWasmName()}(value: {self.getWasmName()}): string;")
        ]

    def get_typedef(self, ast: ASTBuilder, base_map: GenTypeMap) -> List[BlockId]:
        body = []
        for field in self.Enum.fields:
            if field.value:
                body.append(ast.string(f"{field.name} = {field.value},"))

            else:
                body.append(ast.string(f"{field.name},"))

        return [
            ast.block(
                head=ast.string(f"export enum {self.getWasmName()}"),
                content=body,
            )
        ]

    def build_bind(self, b: ASTBuilder) -> BlockId:
        return b.Call(
            func=b.string("org::bind::js::bind_enum"),
            Params=[
                self.Enum.name,
            ],
            Args=[b.StringLiteral(self.Enum.name.getBindName())],
            Stmt=True,
        )


@beartype
@dataclass
class WasmMethod(WasmFunction):
    ExplicitClassParam: bool = False

    def __init__(
        self,
        Func: GenTuFunction,
        ExplicitClassParam: bool = False,
    ):
        super().__init__(Func)
        self.ExplicitClassParam = ExplicitClassParam

    def build_bind(self, Class: QualType, ast: ASTBuilder) -> BlockId:
        b = ast.b

        Args: List[GenTuIdent] = []
        if self.Func.IsConstructor or self.ExplicitClassParam:
            pass

        elif self.Func.impl:
            Args = [GenTuIdent(type=Class.asConstRef(), name="_self")]

        Args += self.Func.arguments

        if self.Func.IsConstructor:
            return ast.XCall(
                ".constructor",
                Params=[arg.type for arg in self.Func.arguments],
                Line=True,
            )

        else:
            call_pass = self.build_call_pass(
                ast,
                FunctionQualName=ast.Scoped(Class, ast.string(self.Func.name)),
                Class=None if self.Func.isStatic else Class,
                IsConst=self.Func.isConst,
                Args=Args,
            )

            if self.Func.IsConstructor:
                call_pass = ast.XCall("pybind11::init", args=[call_pass])

            def_args = []
            if not self.Func.IsConstructor:
                def_args.append(ast.Literal(self.getWasmName()))

            def_args.append(call_pass)

            if self.Func.isPureVirtual:
                def_args.append(ast.XCall("emscripten::pure_virtual"))

            if self.Func.isStatic:
                return ast.XCall(".class_function", def_args, Line=True)

            else:
                return ast.XCall(".function", def_args, Line=True)


@beartype
class WasmClass():

    def __init__(self, Record: GenTuStruct):
        self.Record = Record

    def getWasmName(self) -> str:
        if self.Record.reflectionParams.wrapper_name:
            return self.Record.reflectionParams.wrapper_name

        else:
            return self.Record.name.getBindName(ignored_spaces=IGNORED_NAMESPACES)

    def getCxxName(self) -> QualType:
        return self.Record.declarationQualName()

    def get_module_use(self, ast: ASTBuilder, base_map: GenTypeMap) -> List[BlockId]:
        return [ast.string(f"{self.getWasmName()}: {self.getWasmName()}Constructor;")]

    def get_typedef(self, ast: ASTBuilder, base_map: GenTypeMap) -> List[BlockId]:
        body = []

        for Meth in self.Record.methods:
            body.extend(WasmMethod(Meth).get_typedef(ast, base_map=base_map))

        for Field in self.Record.fields:
            if Field.isStatic:
                continue

            else:
                body.extend(WasmField(Field).get_typedef(ast, base_map=base_map))

        return [
            ast.block(
                head=ast.string(f"export interface {self.getWasmName()}Constructor"),
                content=[ast.string(f"new(): {self.getWasmName()};")],
            ),
            ast.block(
                head=ast.string(f"export interface {self.getWasmName()}"),
                content=body,
            )
        ]

    def build_bind(self, ast: ASTBuilder, base_map: GenTypeMap) -> BlockId:
        b = ast.b

        sub: List[BlockId] = []

        HolderType = None

        if self.Record.reflectionParams:
            match self.Record.reflectionParams.backend.wasm.holder_type:
                case QualType():
                    HolderType = self.Record.reflectionParams.backend.wasm.holder_type.withTemplateParams(
                        [self.getCxxName()])

                case "shared":
                    HolderType = self.getCxxName().withWrapperType(
                        QualType.ForName("shared_ptr", Spaces=[QualType.ForName("std")]))

                case "unique":
                    HolderType = self.getCxxName().withWrapperType(
                        QualType.ForName("unique_ptr", Spaces=[QualType.ForName("std")]))

                case holder:
                    if holder is not None:
                        HolderType = self.getCxxName().withWrapperType(
                            QualType.ForName(holder))

        if HolderType:
            sub.append(
                ast.XCall(
                    ".smart_ptr",
                    Params=[HolderType],
                    args=[ast.StringLiteral(self.getWasmName())],
                ))

        for Field in self.Record.fields:
            if Field.isStatic:
                continue

            else:
                sub.append(WasmField(Field).build_bind(ast, self.getCxxName()))

        for Meth in self.Record.methods:
            # Skip explicit wrapping of default constructors
            if Meth.IsConstructor and len(Meth.arguments) == 0:
                continue

            elif Meth.name.startswith("sub_variant_get"):
                continue

            else:
                sub.append(WasmMethod(Meth).build_bind(self.getCxxName(), ast=ast))

        sub.append(b.text(";"))

        HolderType = None

        return b.stack([
            ast.XCall(
                "emscripten::class_",
                [ast.Literal(self.getWasmName())],
                Params=[self.getCxxName()] + [
                    QualType(name="emscripten::base", Parameters=[B])
                    for B in self.Record.bases
                    if base_map.is_known_type(B)
                ],
            ),
            b.indent(2, b.stack(sub))
        ])


WasmUnion = Union[WasmClass, WasmBindPass, WasmFunction]


@beartype
@dataclass
class WasmModule():
    name: str
    items: List[WasmUnion] = field(default_factory=list)
    Header: List[WasmBindPass] = field(default_factory=list)

    def add_specializations(
        self,
        b: cpp.ASTBuilder,
        specializations: List[TypeSpecialization],
    ):
        for spec in specializations:
            self.items.append(
                WasmBindPass(
                    b.Call(
                        func=b.string("org::bind::js::" + spec.getFlatUsed() + "_bind"),
                        Params=spec.used_type.Parameters,
                        Args=[
                            b.string("g"),
                            b.StringLiteral(spec.bind_name),
                        ],
                        Stmt=True,
                    )))

    def add_decl(self, item: GenTuUnion | WasmBindPass):
        match item:
            case GenTuStruct():
                self.items.append(WasmClass(item))

                for nested in item.nested:
                    if not isinstance(nested, GenTuPass):
                        self.add_decl(nested)

            case GenTuEnum():
                self.items.append(WasmEnum(item))

            case GenTuFunction():
                self.items.append(WasmFunction(item))

            case WasmBindPass():
                self.items.append(item)

            case GenTuTypedef():
                pass

            case _:
                raise ValueError(f"Unhandled declaration type {type(item)}")

    def build_typedef(self, ast: ASTBuilder, base_map: GenTypeMap) -> BlockId:
        body = []
        iface = []

        for item in self.items:
            match item:
                case WasmClass() | WasmEnum() | WasmFunction():
                    iface.extend(item.get_module_use(ast, base_map=base_map))
                    body.extend(item.get_typedef(ast, base_map=base_map))

        return ast.stack([
            ast.string("import * as haxorg_wasm from \"./haxorg_utility_types\";"),
            ast.block(
                ast.string(f"declare module \"{self.name}_types\""),
                content=[
                    ast.block(
                        ast.string(f"export interface {self.name}_module"),
                        iface,
                    ),
                ] + body,
            )
        ])

    def build_bind(self, ast: ASTBuilder, b: cpp.ASTBuilder,
                   base_map: GenTypeMap) -> BlockId:
        Result = b.b.stack()

        Body = []

        for it in self.Header:
            b.b.add_at(Result, it.Id)

        overload_counts: Dict[str, int] = defaultdict(lambda: 0)

        Body.append(b.string("org::bind::js::type_registration_guard g;"))

        for item in self.items:
            match item:
                case WasmClass():
                    Body.append(item.build_bind(ast=ast, base_map=base_map))

                case WasmFunction():
                    overload_counts[item.getWasmName()] += 1
                    Body.append(item.build_bind(b=b))

                case WasmBindPass():
                    Body.append(item.Id)

                case WasmEnum():
                    Body.append(item.build_bind(b=b))

                case _:
                    raise ValueError("Unexpected ")

        for key, value in overload_counts.items():
            if 1 < value:
                log(CAT).warning(
                    f"{key} is overloaded without unique name, has {value} overloads")

        b.b.add_at(
            Result,
            b.stack([
                b.string(f"EMSCRIPTEN_BINDINGS({self.name}) {{"),
                b.indent(2, b.stack(Body)),
                b.string("}"),
            ]))

        return Result
