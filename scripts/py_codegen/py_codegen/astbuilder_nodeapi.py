from py_codegen.gen_tu_cpp import *
from beartype import beartype
from dataclasses import dataclass, field
from beartype.typing import Union
import py_codegen.astbuilder_cpp as cpp
from collections import defaultdict

N_SPACE = QualType(name="Napi", isNamespace=True)
T_CALLBACK_INFO = QualType(name="CallbackInfo", Spaces=[N_SPACE])
T_VALUE = QualType(name="Value", Spaces=[N_SPACE])


@beartype
class NapiField():
    Field: GenTuField

    def __init__(self, Field: GenTuField):
        self.Field = Field


@beartype
class NapiMethod():
    Func: GenTuFunction

    def getNapiName(self):
        if self.Func.reflectionParams.unique_name:
            return self.Func.reflectionParams.unique_name

        elif self.Func.reflectionParams.wrapper_name:
            return self.Func.reflectionParams.wrapper_name

        else:
            return self.Func.name

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
                    Params=[
                        OriginalClass,
                        self.Func.result or QualType(name="void"),
                    ],
                    args=[
                        b.string("info"),
                        b.Call(b.string("getPtr")),
                        b.XCall(
                            "static_cast",
                            args=[
                                b.Addr(
                                    b.line([
                                        b.Type(OriginalClass),
                                        b.string("::"),
                                        b.string(self.Func.name),
                                    ]))
                            ],
                            Params=[self.Func.get_function_type(OriginalClass)],
                        ),
                        b.CallStatic(
                            typ=QualType(name="std"),
                            opc="make_tuple",
                            Args=[
                                b.XConstructObj(
                                    obj=arg.type.withoutCVRef().withWrapperType(
                                        QualType(name="CxxArgSpec")),
                                    Args=cond(arg.value, [b.ToBlockId(arg.value)], []),
                                ) for arg in self.Func.arguments
                            ],
                            Line=len(self.Func.arguments) <= 1,
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
class NapiClass():
    ClassMethods: List[NapiMethod]

    def __init__(self, Record: GenTuStruct):
        self.Record = Record
        self.ClassMethods = [NapiMethod(m) for m in Record.methods]
        self.FieldAccessors = []

    def getNapiName(self) -> str:
        if self.Record.reflectionParams.wrapper_name:
            return self.Record.reflectionParams.wrapper_name

        else:
            return self.Record.name.name + "Js"

    def getCxxName(self) -> QualType:
        return self.Record.declarationQualName()

    def build_module_registration(self, b: cpp.ASTBuilder) -> BlockId:
        return b.CallStatic(QualType(name=self.getNapiName()),
                            opc="Init",
                            Args=[
                                b.string("env"),
                                b.string("exports"),
                            ])

    def build_bind(self, ast: ASTBuilder, b: cpp.ASTBuilder) -> BlockId:
        WrapperClass = cpp.RecordParams(name=QualType(name=self.getNapiName()))

        WrapperClass.bases.append(
            QualType(
                name="ObjectWrap",
                Spaces=[N_SPACE],
                Parameters=[QualType(name=self.getNapiName())],
            ))

        wrapper_methods: List[cpp.MethodDeclParams] = []

        override_counts: Dict[str, int] = defaultdict(lambda: 0)

        for m in self.ClassMethods:
            if m.Func.IsConstructor:
                continue
            
            override_counts[m.getNapiName()] += 1
            bind = m.build_bind(
                Class=QualType(name=self.getNapiName()),
                OriginalClass=self.getCxxName(),
                b=b,
            )
            WrapperClass.members.append(bind)
            wrapper_methods.append(bind)

        for key, value in override_counts.items():
            if 1 < value:
                log(CAT).warning(f"{self.Record.name}::{key} is overloaded without unique name, has {value} overloads")

        WrapperClass.members.append(
            cpp.RecordField(
                params=ParmVarParams(name="_stored",
                                     type=QualType(
                                         name="shared_ptr",
                                         Spaces=[QualType(name="std", isNamespace=True)],
                                         Parameters=[self.getCxxName()],
                                     ))))

        WrapperClass.members.append(
            cpp.MethodDeclParams(Params=cpp.FunctionParams(
                Name="getPtr",
                ResultTy=self.getCxxName().asPtr(),
                Body=[b.Return(b.Call(b.Dot(b.string("_stored"), b.string("get"))))],
            )))

        return b.Record(WrapperClass)


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

    def add_decl(self, item: GenTuUnion):
        match item:
            case GenTuStruct():
                self.items.append(NapiClass(item))

            case GenTuEnum():
                pass

            case GenTuFunction():
                pass

            case NapiBindPass():
                self.items.append(item)

            case _:
                raise ValueError(f"Unhandled declaration type {type(item)}")

    def build_bind(self, ast: ASTBuilder, b: cpp.ASTBuilder) -> BlockId:
        Result = b.b.stack()

        Body = []

        for it in self.Header:
            b.b.add_at(Result, it.Id)

        for item in self.items:
            match item:
                case NapiClass():
                    b.b.add_at(Result, item.build_bind(ast=ast, b=b))
                    Body.append(item.build_module_registration(b=b))

                case _:
                    raise ValueError("Unahn")

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
