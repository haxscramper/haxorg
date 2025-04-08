from py_codegen.gen_tu_cpp import *
from beartype import beartype
from dataclasses import dataclass, field
from beartype.typing import Union
import py_codegen.astbuilder_cpp as cpp

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

    def build_bind(self, Class: str, b: cpp.ASTBuilder) -> cpp.MethodDeclParams:
        f = cpp.FunctionParams(Name=self.getNapiName())
        f.Args.append(cpp.ParmVarParams(name="info", type=T_CALLBACK_INFO.asConstRef()))
        f.ResultTy = T_VALUE
        f.Body = [
            b.Return(
                b.Call(
                    b.string("WrapConstMethod" if self.Func.isConst else "WrapMethod"),
                    Args=[
                        b.string("info"),
                        b.Call(b.string("getPtr")),
                        b.Addr(
                            b.line([
                                b.string(Class),
                                b.string("::"),
                                b.string(self.getNapiName()),
                            ]))
                    ],
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

    def build_bind(self, ast: ASTBuilder, b: cpp.ASTBuilder) -> BlockId:
        WrapperClass = cpp.RecordParams(name=QualType(name=self.getNapiName()))

        WrapperClass.bases.append(
            QualType(
                name="ObjectWrap",
                Spaces=[N_SPACE],
                Parameters=[QualType(name=self.getNapiName())],
            ))

        wrapper_methods: List[cpp.MethodDeclParams] = []

        for m in self.ClassMethods:
            bind = m.build_bind(self.getNapiName(), b=b)
            WrapperClass.members.append(bind)
            wrapper_methods.append(bind)

        return b.Record(WrapperClass)


NapiUnion = Union[NapiClass]


@beartype
@dataclass
class NapiModule():
    name: str
    items: List[NapiUnion] = field(default_factory=list)

    def add_decl(self, item: GenTuUnion):
        match item:
            case GenTuStruct():
                self.items.append(NapiClass(item))

            case GenTuEnum():
                pass

            case GenTuFunction():
                pass

            case _:
                raise ValueError(f"Unhandled declaration type {type(item)}")

    def build_bind(self, ast: ASTBuilder, b: cpp.ASTBuilder) -> BlockId:
        Result = b.b.stack()

        Body = []
        for item in self.items:
            match item:
                case NapiClass():
                    b.b.add_at(Result, item.build_bind(ast=ast, b=b))
                    Body.append(
                        b.CallStatic(QualType(name=item.getNapiName()),
                                     opc="Init",
                                     Args=[
                                         b.string("env"),
                                         b.string("exports"),
                                     ]))

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
