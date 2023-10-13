from py_textlayout.py_textlayout import *
from dataclasses import dataclass, field
from typing import TYPE_CHECKING, NewType
from beartype.typing import List, Union, Tuple
from beartype import beartype
import astbuilder_base as base

if not TYPE_CHECKING:
    BlockId = NewType('BlockId', int)


@beartype
@dataclass
class PyType:
    Name: str
    Params: List['PyType'] = field(default_factory=list)


@beartype
@dataclass
class IdentParams:
    Type: PyType
    Name: str


@beartype
@dataclass
class DecoratorParams:
    Name: str


@beartype
@dataclass
class FunctionDefParams:
    Name: str
    ResultTy: PyType
    Args: List[IdentParams] = field(default_factory=list)
    Decorators: List[DecoratorParams] = field(default_factory=list)
    Doc: str = ""
    Body: List[BlockId] = field(default_factory=list)
    IsStub: bool = False


@beartype
@dataclass
class MethodParams:
    Func: FunctionDefParams


@beartype
@dataclass
class FieldParams:
    Type: PyType
    Name: str


@beartype
@dataclass
class ClassParams:
    Name: str
    Methods: List[MethodParams] = field(default_factory=list)
    Bases: List[PyType] = field(default_factory=list)
    Fields: List[FieldParams] = field(default_factory=list)


@beartype
@dataclass
class EnumFieldParams:
    Name: str
    Value: str


@beartype
@dataclass
class EnumParams:
    Name: str
    Fields: List[EnumFieldParams]


@beartype
class ASTBuilder(base.AstbuilderBase):

    def __init__(self, in_b: TextLayout):
        self.b = in_b

    def Decorator(self, p: DecoratorParams) -> BlockId:
        return self.b.line([self.string("@"), self.string(p.Name)])

    def Type(self, p: PyType) -> BlockId:
        if p.Params:
            return self.b.line([
                self.string(p.Name),
                self.string("["),
                self.csv([self.Type(T) for T in p.Params]),
                self.string("]")
            ])

        else:
            return self.string(p.Name)

    def Arg(self, p: IdentParams) -> BlockId:
        return self.b.line([self.string(p.Name), self.string(": "), self.Type(p.Type)])

    def FuncHead(self, p: FunctionDefParams) -> List[BlockId]:
        b = self.b
        return [
            b.text("def "),
            b.text(p.Name),
            self.pars(self.csv([self.Arg(A) for A in p.Args])),
            b.text(" -> "),
            self.Type(p.ResultTy),
            b.text(":")
        ]

    def Method(self, p: MethodParams) -> BlockId:
        b = self.b

        def_head = self.FuncHead(p.Func)

        if p.Func.IsStub:
            def_head.append(b.text(" ..."))
            return b.line(def_head)

        else:
            return b.stack([b.line(def_head), b.indent(4, b.stack(p.Func.Body))])

    def Field(self, p: FieldParams) -> BlockId:
        return self.b.line([self.string(p.Name), self.string(": "), self.Type(p.Type)])

    def Enum(self, p: EnumParams) -> BlockId:
        b = self.b
        return b.stack([
            b.line([b.text("class "), b.text(p.Name),
                    b.text("(Enum):")]),
            b.indent(4, b.stack([b.text(f"{F.Name} = {F.Value}") for F in p.Fields]))
        ])

    def Class(self, p: ClassParams) -> BlockId:
        b = self.b

        methods: List[BlockId] = [self.Method(M) for M in p.Methods]
        fields: List[BlockId] = [self.Field(F) for F in p.Fields]

        if len(methods) == 0 and len(fields) == 0:
            methods = [b.text("pass")]

        return self.b.stack([
            b.line([
                b.text("class "),
                b.text(p.Name),
                *([self.pars(self.csv([self.Type(B)
                                       for B in p.Bases]))] if p.Bases else []),
                b.text(":"),
            ]),
            b.indent(4, b.stack(methods + fields))
        ])
