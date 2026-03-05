from collections import defaultdict
from dataclasses import dataclass, field

from beartype import beartype
from beartype.typing import Union, List, Optional, Dict
import py_codegen.astbuilder_cpp as cpp
from py_codegen import codegen_ir
from py_codegen.astbuilder_embind_config import EmbindAstbuilderConfig
from py_codegen.codegen_ir import QualType
from py_haxorg.layout.wrap import BlockId
from py_haxorg.astbuilder.astbuilder_base import pascal_case


@beartype
def get_function_wasm_name(Func: codegen_ir.GenTuFunction,
                           conf: EmbindAstbuilderConfig) -> str:
    if Func.ReflectionParams.unique_name:
        return Func.ReflectionParams.unique_name

    elif Func.ReflectionParams.wrapper_name:
        return Func.ReflectionParams.wrapper_name

    else:
        return conf.getSanitizedIdent(Func.Name)


@beartype
class WasmField():
    Field: codegen_ir.GenTuField

    def __init__(self, Field: codegen_ir.GenTuField,
                 conf: EmbindAstbuilderConfig) -> None:
        self.Field = Field
        self.conf = conf

    def get_typedef(self, ast: cpp.ASTBuilder) -> List[BlockId]:
        return [
            ast.line([
                ast.string(self.Field.Name),
                ast.string(": "),
                ast.Type(self.conf.getBackendType(self.Field.Type))
                if self.Field.Type else ast.string("any"),
            ])
        ]

    def build_bind(self, ast: cpp.ASTBuilder, Class: QualType) -> BlockId:
        return ast.XCall(
            ".property",
            args=[
                ast.StringLiteral(self.Field.Name),
                ast.Addr(ast.Scoped(Class, ast.string(self.Field.Name))),
            ],
        )


@beartype
@dataclass
class WasmBindPass:
    Id: BlockId


@beartype
class WasmTypedef:
    Def: codegen_ir.GenTuTypedef
    conf: EmbindAstbuilderConfig

    def __init__(self, Def: codegen_ir.GenTuTypedef,
                 conf: EmbindAstbuilderConfig) -> None:
        self.Def = Def
        self.conf = conf

    def get_typedef(self, ast: cpp.ASTBuilder) -> List[BlockId]:
        return [
            ast.line([
                ast.string("export type "),
                ast.Type(self.conf.getBackendType(self.Def.name)),
                ast.string(" = "),
                ast.Type(self.conf.getBackendType(self.Def.base)),
                ast.string(";"),
            ])
        ]

    def build_bind(self, ast: cpp.ASTBuilder) -> List[BlockId]:
        return []

    def get_module_use(self, ast: cpp.ASTBuilder) -> List[BlockId]:
        return []


@beartype
class WasmFunction():
    conf: EmbindAstbuilderConfig
    Func: codegen_ir.GenTuFunction
    Body: List[BlockId] = []

    def getWasmName(self) -> str:
        return get_function_wasm_name(self.Func, self.conf)

    def __init__(self,
                 Func: codegen_ir.GenTuFunction,
                 conf: EmbindAstbuilderConfig,
                 Body: List[BlockId] = []) -> None:
        self.Func = Func
        self.Body = Body
        self.conf = conf

    def get_module_use(self, ast: cpp.ASTBuilder) -> List[BlockId]:
        return self.get_typedef(ast)

    def get_typedef(self, ast: cpp.ASTBuilder) -> List[BlockId]:
        return [
            ast.line([
                ast.string(self.getWasmName()),
                ast.pars(
                    ast.csv([
                        ast.line([
                            ast.string(self.conf.getSanitizedIdent(F.Name)),
                            ast.string(": "),
                            ast.Type(self.conf.getBackendType(F.Type)),
                        ]) for F in self.Func.Args
                    ])),
                ast.string(": "),
                ast.Type(self.conf.getBackendType(self.Func.ReturnType))
                if self.Func.ReturnType else ast.string("void"),
                ast.string(";"),
            ])
        ]

    def build_call_pass(
        self,
        ast: cpp.ASTBuilder,
        Args: List[codegen_ir.GenTuIdent],
        FunctionQualName: BlockId,
        Class: Optional[QualType] = None,
        IsConst: bool = False,
    ) -> BlockId:
        if self.Body:
            return ast.Lambda(
                cpp.LambdaParams(
                    ResultTy=self.Func.ReturnType,
                    Args=[
                        cpp.ParmVarParams(Arg.Type, Arg.Name) for Arg in self.Func.Args
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

    def build_bind(self, b: cpp.ASTBuilder) -> BlockId:

        if self.Func.spaces:
            full_name = b.Scoped(
                QualType(Name=self.Func.spaces[-1].Name, Spaces=self.Func.spaces[:-1]),
                b.string(self.Func.Name))

        else:
            full_name = b.string(self.Func.Name)

        return b.XCall(
            "emscripten::function",
            [
                b.Literal(self.getWasmName()),
                self.build_call_pass(
                    b,
                    self.Func.Args,
                    FunctionQualName=full_name,
                ),
            ],
            Stmt=True,
        )


@beartype
class WasmEnum():
    Enum: codegen_ir.GenTuEnum
    conf: EmbindAstbuilderConfig

    def __init__(self, Enum: codegen_ir.GenTuEnum, conf: EmbindAstbuilderConfig) -> None:
        self.Enum = Enum
        self.conf = conf

    def getWasmName(self) -> str:
        return self.conf.getBindName(self.Enum.Name)

    def get_module_use(self, ast: cpp.ASTBuilder) -> List[BlockId]:
        return [
            ast.block(head=ast.string(f"{self.getWasmName()}:"),
                      content=[
                          ast.string(f"{F.Name}: {self.getWasmName()},")
                          for F in self.Enum.Fields
                      ]),
            ast.string(
                f"format_{self.getWasmName()}(value: {self.getWasmName()}): string;")
        ]

    def get_typedef(self, ast: cpp.ASTBuilder) -> List[BlockId]:
        body = []
        for field in self.Enum.Fields:
            if field.Value:
                body.append(ast.string(f"{field.Name} = {field.Value},"))

            else:
                body.append(ast.string(f"{field.Name},"))

        return [
            ast.block(
                head=ast.string(f"export enum {self.getWasmName()}"),
                content=body,
            )
        ]

    def build_bind(self, b: cpp.ASTBuilder) -> BlockId:
        return b.Call(
            func=b.string("org::bind::js::bind_enum"),
            Params=[
                self.Enum.Name,
            ],
            Args=[b.StringLiteral(self.conf.getBindName(self.Enum.Name))],
            Stmt=True,
        )


@beartype
@dataclass
class WasmMethod(WasmFunction):
    ExplicitClassParam: bool = False

    def __init__(
        self,
        Func: codegen_ir.GenTuFunction,
        conf: EmbindAstbuilderConfig,
        ExplicitClassParam: bool = False,
    ):
        super().__init__(Func, conf)
        self.ExplicitClassParam = ExplicitClassParam

    def build_bind(self, Class: QualType, ast: cpp.ASTBuilder) -> BlockId:
        b = ast.b

        Args: List[codegen_ir.GenTuIdent] = []
        if self.Func.IsConstructor or self.ExplicitClassParam:
            pass

        elif self.Func.Body:
            Args = [codegen_ir.GenTuIdent(Type=Class.asConstRef(), Name="_self")]

        Args += self.Func.Args

        call_pass = self.build_call_pass(
            ast,
            FunctionQualName=ast.Scoped(Class, ast.string(self.Func.Name)),
            Class=None if self.Func.IsStatic else Class,
            IsConst=self.Func.IsConst,
            Args=Args,
        )

        if self.Func.IsConstructor:
            call_pass = ast.XCall("nanobind::init", args=[call_pass])

        def_args = []
        if not self.Func.IsConstructor:
            def_args.append(ast.Literal(self.getWasmName()))

        def_args.append(call_pass)

        if self.Func.IsPureVirtual:
            def_args.append(ast.XCall("emscripten::pure_virtual"))

        if self.Func.IsStatic:
            return ast.XCall(".class_function", def_args, Line=True)

        else:
            return ast.XCall(".function", def_args, Line=True)


@beartype
class WasmClass():
    conf: EmbindAstbuilderConfig

    def __init__(self, Record: codegen_ir.GenTuStruct,
                 conf: EmbindAstbuilderConfig) -> None:
        self.Record = Record
        self.conf = conf

    def getWasmName(self) -> str:
        return self.conf.getBindName(self.Record.Name)

    def getCxxName(self) -> QualType:
        return self.Record.declarationQualName()

    def get_module_use(self, ast: cpp.ASTBuilder) -> List[BlockId]:
        return [ast.string(f"{self.getWasmName()}: {self.getWasmName()}Constructor;")]

    def get_typedef(self, ast: cpp.ASTBuilder) -> List[BlockId]:
        body = []

        for Meth in self.Record.Methods:
            body.extend(WasmMethod(Meth, self.conf).get_typedef(ast))

        for Field in self.Record.fields:
            if Field.IsStatic:
                continue

            else:
                body.extend(WasmField(Field, self.conf).get_typedef(ast))

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

    def build_bind(self, ast: cpp.ASTBuilder) -> BlockId:
        b = ast.b

        sub: List[BlockId] = []

        HolderType = None

        if self.Record.ReflectionParams:
            match self.Record.ReflectionParams.backend.wasm.holder_type:
                case QualType():
                    HolderType = self.Record.ReflectionParams.backend.wasm.holder_type.withTemplateParams(
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
            if Field.IsStatic:
                continue

            else:
                sub.append(WasmField(Field, self.conf).build_bind(ast, self.getCxxName()))

        has_constructor = False
        for Meth in self.Record.Methods:
            # Skip explicit wrapping of default constructors
            if Meth.IsConstructor:
                if HolderType:
                    sub.append(
                        ast.XCall(
                            ".constructor",
                            args=[
                                ast.Addr(
                                    ast.Type(
                                        QualType(
                                            Name="org::bind::js::holder_type_constructor",
                                            Params=[
                                                self.getCxxName(),
                                            ] + [M.Type for M in Meth.Args])))
                            ]))

                    has_constructor = True

            elif Meth.Name.startswith("sub_variant_get"):
                continue

            else:
                sub.append(
                    WasmMethod(Meth, self.conf).build_bind(self.getCxxName(), ast=ast))

        if not has_constructor and not self.Record.IsAbstract:
            # If the type has non-default holder type, `new` in JS will still create a raw pointer
            # to the type, to fix this it necessary to provide own implementation for the constructor
            if self.Record.ReflectionParams.default_constructor:
                if HolderType:
                    sub.append(
                        ast.XCall(
                            ".constructor",
                            args=[
                                ast.Addr(
                                    ast.Type(
                                        QualType(
                                            Name="org::bind::js::holder_type_constructor",
                                            Params=[
                                                HolderType,
                                            ])))
                            ]))

                else:
                    sub.append(ast.XCall(".constructor", Params=[]))

        sub.append(b.text(";"))

        HolderType = None

        return b.stack([
            ast.XCall(
                "emscripten::class_",
                [ast.Literal(self.getWasmName())],
                Params=[self.getCxxName()] + [
                    QualType(Name="emscripten::base", Params=[B])
                    for B in self.Record.Bases
                    if self.conf.isKnownClass(B)
                ],
            ),
            b.indent(2, b.stack(sub))
        ])


WasmUnion = Union[WasmClass, WasmBindPass, WasmFunction, WasmEnum, WasmTypedef]


@beartype
@dataclass
class WasmModule():
    name: str
    conf: EmbindAstbuilderConfig
    items: List[WasmUnion] = field(default_factory=list)
    Header: List[WasmBindPass] = field(default_factory=list)

    def add_specializations(
        self,
        b: cpp.ASTBuilder,
        specializations: List[codegen_ir.TypeSpecialization],
    ) -> None:
        for spec in specializations:
            self.items.append(
                WasmBindPass(
                    b.Call(
                        func=b.string("org::bind::js::" + spec.getFlatUsed() + "_bind"),
                        Params=spec.used_type.Params,
                        Args=[
                            b.string("g"),
                            b.StringLiteral(spec.bind_name),
                        ],
                        Stmt=True,
                    )))

    def add_decl(
        self, item: codegen_ir.GenTuUnion | WasmBindPass | codegen_ir.GenTuEnum |
        codegen_ir.GenTuTypedef | codegen_ir.GenTuFunction | codegen_ir.GenTuStruct
    ) -> None:
        match item:
            case codegen_ir.GenTuStruct():
                self.items.append(WasmClass(item, self.conf))

                for nested in item.Nested:
                    if not isinstance(nested, codegen_ir.GenTuPass):
                        self.add_decl(nested)  # type: ignore

            case codegen_ir.GenTuEnum():
                self.items.append(WasmEnum(item, self.conf))

            case codegen_ir.GenTuFunction():
                self.items.append(WasmFunction(item, self.conf))

            case WasmBindPass():
                self.items.append(item)

            case codegen_ir.GenTuTypedef():
                self.items.append(WasmTypedef(item, self.conf))

            case _:
                raise ValueError(f"Unhandled declaration type {type(item)}")

    def build_typedef(self, ast: cpp.ASTBuilder) -> BlockId:
        body = []
        iface = []

        for item in self.items:
            match item:
                case WasmClass() | WasmEnum() | WasmTypedef():
                    iface.extend(item.get_module_use(ast))
                    body.extend(item.get_typedef(ast))

                case WasmFunction():
                    iface.extend(item.get_typedef(ast))

        return ast.stack([
            ast.string("import * as haxorg_wasm from \"./haxorg_utility_types\";"),
            ast.block(
                ast.string(f"export interface {self.name}_module_auto"),
                iface,
            ),
            ast.string(
                f"type {self.name}_module = {self.name}_module_auto & haxorg_wasm.{self.name}_manual; "
            ),
            *body,
        ])

    def build_bind(self, ast: cpp.ASTBuilder, b: cpp.ASTBuilder) -> BlockId:
        Result = b.b.stack()

        Body = []
        SubdivideBody: List[BlockId] = []
        subivide_count = 0

        def add_subdivide_body() -> None:
            nonlocal SubdivideBody
            nonlocal subivide_count
            Body.append(
                ast.XCall(
                    f"subdivide_{subivide_count}",
                    Stmt=True,
                    args=[ast.string("g")],
                ))
            b.b.add_at(
                Result,
                ast.Function(
                    cpp.FunctionParams(
                        Name=f"subdivide_{subivide_count}",
                        Args=[
                            cpp.ParmVarParams(
                                type=QualType(
                                    Name="org::bind::js::type_registration_guard",
                                    RefKind=codegen_ir.ReferenceKind.LValue,
                                ),
                                name="g",
                            )
                        ],
                        Body=SubdivideBody,
                    )))

            subivide_count += 1
            SubdivideBody = []

        def add_binding_statement(stmt: BlockId) -> None:
            SubdivideBody.append(stmt)

            if 100 < len(SubdivideBody):
                add_subdivide_body()

        for it in self.Header:
            b.b.add_at(Result, it.Id)

        overload_counts: Dict[str, int] = defaultdict(lambda: 0)

        Body.append(b.string("org::bind::js::type_registration_guard g;"))

        for item in self.items:
            match item:
                case WasmClass():
                    add_binding_statement(item.build_bind(ast=ast))

                case WasmFunction():
                    overload_counts[item.getWasmName()] += 1
                    add_binding_statement(item.build_bind(b=b))

                case WasmBindPass():
                    add_binding_statement(item.Id)

                case WasmEnum():
                    add_binding_statement(item.build_bind(b=b))

                case WasmTypedef():
                    pass

                case _:
                    raise ValueError("Unexpected ")

        if len(SubdivideBody) != 0:
            add_subdivide_body()

        for key, value in overload_counts.items():
            if 1 < value:
                raise ValueError(
                    f"{key} is overloaded without unique name, has {value} overloads")

        b.b.add_at(
            Result,
            b.stack([
                b.string(f"EMSCRIPTEN_BINDINGS({self.name}) {{"),
                b.indent(2, b.stack(Body)),
                b.string("}"),
            ]))

        return Result
