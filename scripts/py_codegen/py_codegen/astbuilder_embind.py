from py_codegen.gen_tu_cpp import *
from beartype import beartype
from dataclasses import dataclass, field
from beartype.typing import Union
import py_codegen.astbuilder_cpp as cpp
from collections import defaultdict
from py_codegen.astbuilder_base import pascal_case


@beartype
def get_function_wasm_name(Func: GenTuFunction):
    if Func.reflectionParams.unique_name:
        return Func.reflectionParams.unique_name

    elif Func.reflectionParams.wrapper_name:
        return Func.reflectionParams.wrapper_name

    else:
        return Func.name


@beartype
class WasmField():
    Field: GenTuField

    def __init__(self, Field: GenTuField):
        self.Field = Field


@beartype
@dataclass
class WasmBindPass:
    Id: BlockId


@beartype
class WasmFunction():
    Func: GenTuFunction

    def getNapiName(self) -> str:
        return get_function_wasm_name(self.Func)


@beartype
class WasmMethod():
    Func: GenTuFunction


@beartype
class WasmEnum():
    Enum: GenTuEnum


@beartype
class WasmClass():
    ClassMethods: List[WasmMethod]


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
                        spec=b.string(spec.getFlatUsed() + "_bind"),
                        Params=[spec.used_type.Parameters],
                        Args=[
                            b.StringLiteral(spec.bind_name),
                        ],
                        Stmt=True,
                    )))

    def build_bind(self, ast: ASTBuilder, b: cpp.ASTBuilder,
                   base_map: GenTypeMap) -> BlockId:
        Result = b.b.stack()

        Body = []

        for it in self.Header:
            b.b.add_at(Result, it.Id)

        overload_counts: Dict[str, int] = defaultdict(lambda: 0)

        for item in self.items:
            match item:
                case WasmClass():
                    b.b.add_at(Result, item.build_bind(ast=ast, b=b, base_map=base_map))
                    Body.append(item.build_module_registration(b=b))

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

        Body.append(b.Return(b.string("exports")))

        b.b.add_at(
            Result,
            b.stack([
                b.string(f"EMSCRIPTEN_BINDINGS({self.name}) {{"),
                b.indent(2, Body),
                b.string("}"),
            ]))

        return Result
