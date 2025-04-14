from py_codegen.gen_tu_cpp import *
from beartype import beartype
from dataclasses import dataclass, field
from beartype.typing import Union
import py_codegen.astbuilder_cpp as cpp
from collections import defaultdict
from py_codegen.astbuilder_base import pascal_case

N_SPACE = QualType(name="Napi", isNamespace=True)
T_CALLBACK_INFO = QualType(name="CallbackInfo", Spaces=[N_SPACE])
T_VALUE = QualType(name="Value", Spaces=[N_SPACE])
T_OBJECT = QualType(name="Object", Spaces=[N_SPACE])
T_ENV = QualType(name="Env", Spaces=[N_SPACE])


@beartype
class NapiField():
    Field: GenTuField

    def __init__(self, Field: GenTuField):
        self.Field = Field


@beartype
def build_callable_argument_list(Func: GenTuFunction, b: cpp.ASTBuilder) -> BlockId:
    return b.CallStatic(
        typ=QualType(name="std"),
        opc="make_tuple",
        Args=[
            b.XConstructObj(
                obj=arg.type.withoutCVRef().withWrapperType(QualType(name="CxxArgSpec")),
                Args=cond(
                    arg.value,
                    [b.StringLiteral(arg.name),
                     b.ToBlockId(arg.value)],
                    [b.StringLiteral(arg.name)],
                ),
            ) for arg in Func.arguments
        ],
        Line=len(Func.arguments) <= 1,
    )


@beartype
def get_function_napi_name(Func: GenTuFunction):
    if Func.reflectionParams.unique_name:
        return Func.reflectionParams.unique_name

    elif Func.reflectionParams.wrapper_name:
        return Func.reflectionParams.wrapper_name

    else:
        return Func.name


@beartype
class NapiMethod():
    Func: GenTuFunction

    def getNapiName(self) -> str:
        return get_function_napi_name(self.Func)

    def build_bind(self, Class: QualType, OriginalClass: QualType,
                   b: cpp.ASTBuilder) -> cpp.MethodDeclParams:
        f = cpp.FunctionParams(Name=self.getNapiName())
        f.Args.append(cpp.ParmVarParams(name="info", type=T_CALLBACK_INFO.asConstRef()))
        f.ResultTy = T_VALUE
        f.AllowOneLine = False

        f.Body = [
            b.Return(
                b.XCall(
                    opc="WrapConstMethod" if self.Func.isConst else "WrapMethod",
                    args=[
                        b.string("info"),
                        b.Call(b.string("getPtr")),
                        b.XCall(
                            "makeCallable",
                            args=[
                                b.XCall(
                                    "static_cast",
                                    args=[
                                        b.Addr(
                                            b.line([
                                                b.Scoped(
                                                    OriginalClass,
                                                    b.string(self.Func.name),
                                                ),
                                            ]))
                                    ],
                                    Params=[self.Func.get_function_type(OriginalClass)],
                                ),
                                build_callable_argument_list(self.Func, b=b),
                            ],
                            Line=False,
                        ),
                    ],
                    Line=False,
                ))
        ]
        m = cpp.MethodDeclParams(f)

        return m

    def __init__(self, Func: GenTuFunction):
        self.Func = Func


@beartype
class NapiEnum():
    Enum: GenTuEnum

    def __init__(self, Enum: GenTuEnum):
        self.Enum = Enum

    def build_module_registration(self, b: cpp.ASTBuilder) -> BlockId:
        return b.CallStatic(
            QualType(name="JsEnumWrapper", Parameters=[self.Enum.name]),
            opc="Init",
            Args=[
                b.string("env"),
                b.string("exports"),
                b.StringLiteral(
                    self.Enum.name.getBindName(ignored_spaces=IGNORED_NAMESPACES,)),
            ],
            Stmt=True,
        )


@beartype
class NapiClass():
    ClassMethods: List[NapiMethod]

    def __init__(self, Record: GenTuStruct):
        self.Record = Record

    def getNapiName(self) -> str:
        if self.Record.reflectionParams.wrapper_name:
            return self.Record.reflectionParams.wrapper_name

        else:
            return self.Record.name.getBindName(ignored_spaces=IGNORED_NAMESPACES) + "Js"

    def getCxxName(self) -> QualType:
        return self.Record.declarationQualName()

    def build_module_registration(self, b: cpp.ASTBuilder) -> BlockId:
        return b.CallStatic(
            QualType(name=self.getNapiName()),
            opc="Init",
            Args=[
                b.string("env"),
                b.string("exports"),
            ],
            Stmt=True,
        )

    def build_bind(
        self,
        ast: ASTBuilder,
        b: cpp.ASTBuilder,
        base_map: GenTypeMap,
    ) -> BlockId:
        WrapperClass = cpp.RecordParams(name=QualType(name=self.getNapiName()))

        BaseWrap = QualType(
            name="SharedPtrWrapBase",
            Parameters=[
                QualType(name=self.getNapiName()),
                self.getCxxName(),
            ],
        )

        WrapperClass.bases.append(BaseWrap)
        wrapper_methods: List[cpp.MethodDeclParams] = []
        overload_counts: Dict[str, int] = defaultdict(lambda: 0)
        override_groups: Dict[Tuple[str, int], List[NapiMethod]] = defaultdict(list)

        def rec_methods(Record: GenTuStruct):
            for base in Record.bases:
                base_type = base_map.get_one_type_for_name(base.name)
                if base_type:
                    rec_methods(base_type)

            for _m in Record.methods:
                if _m.IsConstructor or _m.isStatic:
                    continue

                elif _m.name in ["sub_variant_get_name", "sub_variant_get_data"]:
                    continue

                override_groups[(_m.name, _m.get_function_type().qual_hash())].append(
                    NapiMethod(_m))

        rec_methods(self.Record)

        for override_key, method_list in override_groups.items():
            m = method_list[-1]
            # log(CAT).info(f"{m.getNapiName()}")
            overload_counts[m.getNapiName()] += 1
            bind = m.build_bind(
                Class=QualType(name=self.getNapiName()),
                OriginalClass=self.getCxxName(),
                b=b,
            )
            WrapperClass.members.append(bind)
            wrapper_methods.append(bind)

        for key, value in overload_counts.items():
            if 1 < value:
                log(CAT).warning(
                    f"{self.Record.name}::{key} is overloaded without unique name, has {value} overloads"
                )

        BindCalls = [
            b.XCall("InstanceMethod",
                    args=[
                        b.StringLiteral(m.Params.Name),
                        b.Addr(
                            b.line([
                                b.string(self.getNapiName()),
                                b.string("::"),
                                b.string(m.Params.Name),
                            ]))
                    ]) for m in wrapper_methods
        ]

        WrapperClass.nested.append(
            b.Using(
                cpp.UsingParams(baseType=QualType(
                    name="SharedPtrWrapBase",
                    Spaces=[BaseWrap],
                ))))

        WrapperClass.members.append(
            cpp.MethodDeclParams(
                Params=cpp.FunctionParams(
                    Name="Init",
                    Args=[
                        ParmVarParams(type=T_ENV, name="env"),
                        ParmVarParams(type=T_OBJECT, name="exports"),
                    ],
                    ResultTy=T_OBJECT,
                    Body=[
                        b.Return(
                            b.XCall(
                                "InitSharedWrap",
                                args=[
                                    b.string("env"),
                                    b.string("exports"),
                                    b.StringLiteral(self.getNapiName()),
                                    b.pars(b.csv(BindCalls, isLine=False),
                                           left="{",
                                           right="}"),
                                ],
                            )),
                    ],
                ),
                isStatic=True,
            ))

        shared_stored_ptr_type = QualType(
            name="shared_ptr",
            Spaces=[QualType(name="std", isNamespace=True)],
            Parameters=[self.getCxxName()],
        )

        return b.stack([
            b.Record(WrapperClass),
            b.Record(
                cpp.RecordParams(
                    name=QualType(name="js_to_org_type",
                                  Parameters=[QualType(name=self.getNapiName())]),
                    Template=TemplateParams(Stacks=[TemplateGroup()]),
                    IsTemplateSpecialization=True,
                    nested=[
                        b.Using(
                            cpp.UsingParams(newName="type",
                                            baseType=self.Record.declarationQualName()))
                    ],
                )),
            b.Record(
                cpp.RecordParams(
                    name=QualType(name="org_to_js_type",
                                  Parameters=[self.Record.declarationQualName()]),
                    Template=TemplateParams(Stacks=[TemplateGroup()]),
                    IsTemplateSpecialization=True,
                    nested=[
                        b.Using(
                            cpp.UsingParams(newName="type",
                                            baseType=QualType(name=self.getNapiName())))
                    ],
                )),
        ])


@beartype
class NapiFunction():
    Func: GenTuFunction

    def __init__(self, Func: GenTuFunction):
        self.Func = Func

    def getNapiName(self) -> str:
        return get_function_napi_name(self.Func)

    def build_bind(self, b: cpp.ASTBuilder) -> BlockId:
        return b.block(None, [
            b.VarDecl(
                cpp.ParmVarParams(
                    type=QualType(name="auto"),
                    name="callable",
                    defArg=b.XCall(
                        "makeCallable",
                        args=[
                            b.Addr(b.Type(self.Func.get_full_qualified_name())),
                            build_callable_argument_list(self.Func, b=b),
                        ],
                    ),
                )),
            b.XCallRef(
                b.string("exports"),
                "Set",
                args=[
                    b.StringLiteral(self.getNapiName()),
                    b.CallStatic(
                        typ=QualType(name="Function",
                                     Spaces=[QualType(name="Napi", isNamespace=True)]),
                        opc="New",
                        Args=[
                            b.string("env"),
                            b.Lambda(
                                cpp.LambdaParams(
                                    CaptureList=[
                                        cpp.LambdaCapture(Name="callable", ByRef=False)
                                    ],
                                    Args=[
                                        ParmVarParams(type=T_CALLBACK_INFO.asConstRef(),
                                                      name="info")
                                    ],
                                    Body=[
                                        b.Return(
                                            b.XCall("WrapFunction",
                                                    args=[
                                                        b.string("info"),
                                                        b.string("callable")
                                                    ]))
                                    ],
                                )),
                        ],
                    ),
                ],
                Stmt=True,
            ),
        ])


@beartype
@dataclass
class NapiBindPass:
    Id: BlockId


NapiUnion = Union[NapiClass, NapiBindPass]


@beartype
@dataclass
class NapiModule():
    name: str
    items: List[NapiUnion] = field(default_factory=list)
    Header: List[NapiBindPass] = field(default_factory=list)

    def add_specializations(self, b: cpp.ASTBuilder,
                            specializations: List[TypeSpecialization]):
        for spec in specializations:
            self.items.append(
                NapiBindPass(
                    b.CallStatic(
                        QualType(
                            name=spec.getFlatUsed() + "_bind",
                            Parameters=spec.used_type.Parameters,
                        ),
                        opc="Init",
                        Args=[
                            b.string("env"),
                            b.string("exports"),
                            b.StringLiteral(spec.bind_name),
                        ],
                        Stmt=True,
                    )))

    def add_decl(self, item: GenTuUnion):
        match item:
            case GenTuStruct():
                self.items.append(NapiClass(item))

                for nested in item.nested:
                    if not isinstance(nested, GenTuPass):
                        self.add_decl(nested)

            case GenTuEnum():
                self.items.append(NapiEnum(item))

            case GenTuFunction():
                self.items.append(NapiFunction(item))

            case NapiBindPass():
                self.items.append(item)

            case GenTuTypedef():
                pass

            case _:
                raise ValueError(f"Unhandled declaration type {type(item)}")

    def build_bind(self, ast: ASTBuilder, b: cpp.ASTBuilder,
                   base_map: GenTypeMap) -> BlockId:
        Result = b.b.stack()

        Body = []

        for it in self.Header:
            b.b.add_at(Result, it.Id)

        overload_counts: Dict[str, int] = defaultdict(lambda: 0)

        for item in self.items:
            match item:
                case NapiClass():
                    b.b.add_at(Result, item.build_bind(ast=ast, b=b, base_map=base_map))
                    Body.append(item.build_module_registration(b=b))

                case NapiFunction():
                    overload_counts[item.getNapiName()] += 1
                    Body.append(item.build_bind(b=b))

                case NapiBindPass():
                    Body.append(item.Id)

                case NapiEnum():
                    Body.append(item.build_module_registration(b=b))

                case _:
                    raise ValueError("Unexpected ")

        for key, value in overload_counts.items():
            if 1 < value:
                log(CAT).warning(
                    f"{key} is overloaded without unique name, has {value} overloads")

        Body.append(b.Return(b.string("exports")))

        Init = cpp.FunctionParams(
            Name="InitModule",
            ResultTy=QualType(name="Object", Spaces=[N_SPACE]),
            Args=[
                cpp.ParmVarParams(QualType(name="Env", Spaces=[N_SPACE]), name="env"),
                cpp.ParmVarParams(QualType(name="Object", Spaces=[N_SPACE]),
                                  name="exports"),
            ],
            Body=Body,
        )

        b.b.add_at(Result, b.Function(Init))
        b.b.add_at(Result, b.string(f"NODE_API_MODULE({self.name}, InitModule);"))

        return Result
